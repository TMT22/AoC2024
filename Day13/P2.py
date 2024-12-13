input_file = "Inputs/Test01.txt"
oo = 231231231231233123

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

test_cases = []

for i in range(len(lines)):
    if i%4 != 0: continue

    delta_a = list(map(int, lines[i][10:].replace('X+', '').replace('Y+', '').split(',')))
    delta_b = list(map(int, lines[i+1][10:].replace('X+', '').replace('Y+', '').split(',')))
    prize = list(map(lambda e: 10000000000000+e, map(int, lines[i+2][7:].replace('X=', '').replace('Y=', '').replace(" ", '').split(','))))

    test_cases.append((delta_a, delta_b, prize))

def process_case(delta_a, delta_b, prize):

    det = delta_a[0]*delta_b[1] - delta_b[0]*delta_a[1]
    if det == 0:
        print("NO INVERSE")
        return oo
    

    a_up = prize[0] * delta_b[1] - prize[1] * delta_b[0]
    b_up = -prize[0] * delta_a[1] + prize[1] * delta_a[0]
    
    if a_up%det != 0:
        return oo
    
    a = a_up//det

    if b_up%det != 0:
        return oo
    
    b = b_up//det

    if a < 0 or b < 0:
        return oo
    
    print(det, a_up, b_up, a_up/det, b_up/det)
    print(prize)

    return a*3 + b

total = 0
for test_case in test_cases: 
    lowest_cost = process_case(*test_case)
    if lowest_cost < oo:
        total += lowest_cost

print("Total: ", total)