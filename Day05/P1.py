input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

rules = []
lists = []

read_rules = True
for line in lines:

    if len(line) < 3:
        read_rules = False
        continue

    if read_rules:
        rules.append(tuple(map(int, line.split('|'))))
    else:
        lists.append(list(map(int, line.split(','))))

def check_list(list):
    n = len(list)
    for i in range(n):
        for j in range(i+1, n):
            if (list[j], list[i]) in rules:
                return False, (i, j), (list[j], list[i])
    return True, None, None


total = 0

for list in lists:
    correct, index, rule_broken = check_list(list)
    print((correct, index, rule_broken), list, list[len(list)//2])

    if correct:
        total += list[len(list)//2]

print("Total: ", total)