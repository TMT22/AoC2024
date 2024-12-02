input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

board = []
for line in lines:
    board.append(list(map(int, line.split())))




def check_safe(line):
    sign = None
    safe = True

    for i in range(len(line)-1):
        delta = line[i+1] - line[i]

        if abs(delta) < 1 or abs(delta) > 3:
            safe = False
            break

        if sign is None:
            sign = -1 if delta < 0 else 1

        if delta*sign < 0:
            safe = False
            break
    
    return safe

safe_num = 0

for line in board:
    if check_safe(line):
        safe_num += 1
        continue
        

    for i in range(len(line)):
        new_line = []
        for j in range(len(line)):
            if j != i : new_line.append(line[j])

        print(new_line)

        if check_safe(new_line):
            print("safe:", line, new_line)
            safe_num += 1
            break
    

print("Safe: ", safe_num)