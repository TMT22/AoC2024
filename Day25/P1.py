input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

locks = []
keys = []

iter = 0

while iter < len(lines):
    current_board = []
    for i in range(7):
        current_board.append(lines[iter+i])
    
    to_add = []
    for i in range(5):
        k = 0
        for j in range(7):
            if current_board[j][i] == '#':
                k += 1
        to_add.append(k-1)


    if current_board[0] == '#####':
        # Lock
        locks.append(tuple(to_add))
    else:
        keys.append(tuple(to_add))

    iter += 8

#print(locks)
#print(keys)

total = 0
for l in locks:
    for k in keys:

        fits = True
        for i in range(5):
            if l[i]+ k[i] > 5:
                fits = False
                break
        if fits:
            total += 1

print("Total: ", total)