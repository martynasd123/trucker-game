import argparse
parser = argparse.ArgumentParser(description="Convert wavefront.obj files to internal mesh format")

parser.add_argument("input", help="specify input file", type=argparse.FileType('r', encoding='UTF-8'))
parser.add_argument("-m", "--material", nargs='*', help="provide materials used", default=[])
parser.add_argument("-o", "--output", help="specify output file", type=argparse.FileType('w', encoding='UTF-8'))

args = parser.parse_args()

input_file = args.input
output_file = args.output 

first_line = input_file.readline()
output_file.write(first_line)
