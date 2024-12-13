input_file = "Inputs/Test01.txt"
oo = 231231231231233123

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

test_cases = []

for i in range(len(lines)):
    if i%4 != 0: continue

    delta_a = list(map(int, lines[i][10:].replace('X+', '').replace('Y+', '').split(',')))
    delta_b = list(map(int, lines[i+1][10:].replace('X+', '').replace('Y+', '').split(',')))
    prize = list(map(int, lines[i+2][7:].replace('X=', '').replace('Y=', '').split(',')))

    test_cases.append((delta_a, delta_b, prize))

def process_case(delta_a, delta_b, prize):
    lowest_cost = oo
    for a in range(110):
        for b in range(110):
            if prize[0] == a*delta_a[0]+b*delta_b[0] and prize[1] == a*delta_a[1]+b*delta_b[1]:
                lowest_cost = min(lowest_cost, a*3+b)
    
    return lowest_cost

total = 0
for test_case in test_cases: 
    lowest_cost = process_case(*test_case)
    if lowest_cost < oo:
        total += lowest_cost

print("Total: ", total)