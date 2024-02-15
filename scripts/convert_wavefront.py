import argparse
import json

parser = argparse.ArgumentParser(description="Convert wavefront.obj files to internal mesh format")

parser.add_argument("input", help="specify input file", type=argparse.FileType('r', encoding='UTF-8'))
parser.add_argument("-m", "--material", nargs='*', help="provide materials used", default=[])
parser.add_argument("-o", "--output", help="specify output file", type=argparse.FileType('w', encoding='UTF-8'))

args = parser.parse_args()

input_file = args.input
output_file = args.output 

def get_coordinates(line):
    return list(map(lambda s: float(s.strip()), line))

geometric_vertices = []
texture_vertices = []
vertex_normals = []

lines = input_file.readlines()
for line in lines:
    match line[0]:
        case "m":
            entry = line.split(' ')
            if entry[0] == "mtllib":
                material_name = entry[1].strip()
                if material_name in args.material:
                    # thingy for material
                    pass
                else:
                    parser.exit(status=0, message="Material %s not specified in command call. Use -m to specify material files used on object\n" % (material_name))
            else:
                continue
        case "v":
            entry = line.split(' ')
            vertex = entry[0]

            match vertex:
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
                case _:
                    continue
        case _:
            continue

data = {"positions": geometric_vertices, 
        "normals": vertex_normals, 
        "uv": texture_vertices}

json.dump(data, output_file, ensure_ascii=False, indent=2)
