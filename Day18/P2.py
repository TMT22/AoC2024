input_file = "Inputs/Input.txt"

oo = 23123123123123451243615

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

n = m = 7 # 71
num_bytes = 102400000

board = [['.' for x in range(m+2)] for y in range(n+2)]

for i in range(n+2):
   board[i][0] = '#'
   board[0][i] = '#'
   board[i][m+1] = '#'
   board[n+1][i] = '#'


def BFS(start):
    # start: X, Y of start
    queue = []
    marked = [[False for x in range(m+2)] for y in range(n+2)]
    distances = [[-1 for x in range(m+2)] for y in range(n+2)]

    for y in range(n+2):
        for x in range(m+2):
            if board[y][x] == '#':
                marked[y][x] = True

    queue.append(start)
    marked[start[1]][start[0]] = True
    distances[start[1]][start[0]] = 0


    while len(queue) > 0:
        next_queue = []
        while len(queue) > 0:
            curr = queue.pop()

            next_coors = [
                (curr[0]+1, curr[1]),
                (curr[0], curr[1]+1),
                (curr[0]-1, curr[1]),
                (curr[0], curr[1]-1)
            ]

            for coor in next_coors:
                if marked[coor[1]][coor[0]]:
                    continue
                assert distances[curr[1]][curr[0]] >= 0
                distances[coor[1]][coor[0]] = distances[curr[1]][curr[0]]+1
                marked[coor[1]][coor[0]] = True
                next_queue.append(coor)
        queue = next_queue
    
    return distances, marked



iter = 0
for line in lines:
    if iter >= num_bytes:
        break
    coor = list(map(int, line.split(',')))
    board[coor[1]+1][coor[0]+1] = '#'
    dist, marked = BFS((1, 1))
    if dist[n][m]== -1:
        print(line)
        exit()
    iter+=1