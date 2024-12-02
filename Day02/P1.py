input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

board = []
for line in lines:
    board.append(list(map(int, line.split())))

safe_num = 0

for line in board:
    
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

    if safe:
        safe_num += 1

print("Safe: ", safe_num)


