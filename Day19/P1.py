import re
input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

patterns = lines[0].split(', ')
targets = lines[2:]


reg = "^("
for pattern in patterns:
    reg += pattern + "|"

reg = reg[:-1] 
reg += ")+$"

reg = re.compile(reg)

print(reg)
print(patterns)
print()
print(targets)

total = 0
for target in targets:
    match = reg.match(target)
    print(target, match)

    if match is not None:
        total += 1

print(total)
