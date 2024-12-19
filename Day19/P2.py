import regex as re
input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

patterns = lines[0].split(', ')
targets = lines[2:]

def count_match(string):
    global patterns
    construction_count = [0 for i in range(len(string)+2)]
    construction_count[0] = 1

    for i in range(1, len(string)+1):
        for pattern in patterns:
            
            if len(pattern) > i:
                continue
            
            if string[i-len(pattern):i] == pattern:
                construction_count[i] += construction_count[i - len(pattern)]

    return construction_count




print(patterns)
print()
print(targets)


total = 0
for target in targets:
    counts = count_match(target)
    #print(target, counts[len(target)], counts)

    total += counts[len(target)]


print(total)
