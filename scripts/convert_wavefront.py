import argparse
import os
import json

parser = argparse.ArgumentParser(description="Convert wavefront.obj files to internal mesh format")

parser.add_argument("input", help="specify input file", type=argparse.FileType('r', encoding='UTF-8'))
parser.add_argument("material", nargs='*', help="provide materials used")
parser.add_argument("output", help="specify output file", type=argparse.FileType('w', encoding='UTF-8'))

args = parser.parse_args()

input_file = args.input
output_file = args.output 
material_files = {}

for arg in args.material:
    material_files[os.path.basename(arg)] = arg

def get_coordinates(line):
    return list(map(lambda s: float(s.strip()), line))

geometric_vertices = []
texture_vertices = []
vertex_normals = []
used_material_files = []
used_materials = []
primitives = []
groups = {}
group_id = 1
face_no = 0
materials = []
material_mapping = []

for line in input_file:
    entry = line.split(' ')
    match entry[0]:
        case "mtllib":
            material_names = entry[1::]
            for material_name in material_names:
                material_name = material_name.strip()
                try:
                    file = open(material_files[material_name], "r")
                    used_material_files.append(file)
                except:
                    parser.exit(status=0, message="Material %s not specified in command call. Use -m to specify material files used on object\n" % (material_name))
        case "v":
            try:
                coordinates = get_coordinates(entry[1:4])
                geometric_vertices.append(coordinates)
            except ValueError as err:
                parser.exit(status=0, message="Invalid coordinates of geometric vertex: %s\n" % (err.args))
            except:
                parser.exit(status=0, message="Could not parse coordinates of geometric vertex\n")
        case "vn":
            try:
                coordinates = get_coordinates(entry[1:4])
                vertex_normals.append(coordinates)
            except ValueError as err:
                parser.exit(status=0, message="Invalid vector of vertex normal: %s\n" % (err.args))
            except:
                parser.exit(status=0, message="Could not parse vector of vertex normal\n")
        case "vt":
            try:
                coordinates = get_coordinates(entry[1:3])
                texture_vertices.append(coordinates)
            except ValueError as err:
                parser.exit(status=0, message="Invalid coordinates of texture vertex: %s\n" % (err.args))
            except:
                parser.exit(status=0, message="Could not parse coordinates of texture vertex\n")
        case "usemtl":
            if entry[1] not in used_materials:
                used_materials.append(entry[1])
                groups["group-%i" % (group_id)] = []
                material_mapping.append(["group-%i" % (group_id)])
                group_id += 1
                material_found = False

                for m_file in used_material_files:
                    for m_line in m_file:
                        words = m_line.split(' ')
                        match words[0]:
                            case "newmtl":
                                if material_found:
                                    break
                                if words[1].strip() == entry[1].strip():
                                    curr_material = {"type": "bp-monochromatic"}
                                    material_found = True
                            case "d":
                                if material_found:
                                    words = m_line.split(' ')
                                    curr_material["dissolve"] = float(words[1].strip())
                            case "Ka":
                                if material_found:
                                    rgb_values = get_coordinates(words[1::])
                                    curr_material["ambient"] = rgb_values
                            case "Kd":
                                if material_found:
                                    rgb_values = get_coordinates(words[1::])
                                    curr_material["diffuse"] = rgb_values
                            case "Ks":
                                if material_found:
                                    rgb_values = get_coordinates(words[1::])
                                    curr_material["specular"] = rgb_values
                            case "Ke":
                                if material_found:
                                    rgb_values = get_coordinates(words[1::])
                                    curr_material["emissive"] = rgb_values
                            case "Ns":
                                if material_found:
                                    curr_material["shininess"] = float(words[1].strip())
                            case "Ni":
                                if material_found:
                                    curr_material["refraction"] = float(words[1].strip())
                            case "iillum":
                                if material_found:
                                    curr_material["illumination"] = float(words[1].strip())
                            case _:
                                continue
                    m_file.seek(0)
                if not material_found:
                    parser.exit(status=0, message="Could not find material %s in specified material files\n" % (entry[1].strip())) 
                materials.append(curr_material)
            else:
                index = used_materials.index(entry[1])
                groups["group-%i" % (group_id)] = []
                material_mapping[index].append("group-%i" % (group_id))
                group_id += 1
        case "f":
            face = []
            references = entry[1::]
            for reference in references:
                reference = reference.strip()
                numbers = list(map(lambda s: int(s.strip()) - 1, reference.split("/")))
                face.append(numbers)
            primitives.append(face)
            groups["group-%i" % (group_id - 1)].append(face_no)
            face_no += 1
        case _:
            continue

data = {"positions": geometric_vertices, 
        "normals": vertex_normals, 
        "uv": texture_vertices,
        "primitives": primitives,
        "groups": groups,
        "materials": materials,
        "material_mapping": material_mapping}

json.dump(data, output_file, ensure_ascii=False, indent=2)
