input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

read_board = True

board = []
moves = ""
player_pos = None
n, m = None, None


def print_board():
    print('\n'.join(list(map(lambda s: ''.join(s), board))))

def try_move(pos, dir):
    # Cannot move wall
    if board[pos['y']][pos['x']] == '#':
        return False, pos

    # Can move onto free point
    if board[pos['y']][pos['x']] == '.':
        return True, pos
    
    if board[pos['y']][pos['x']] == '@' or board[pos['y']][pos['x']] == 'O':
        possible, target_pos = try_move({'x': pos['x']+dir['x'], 'y':pos['y']+dir['y']}, dir)

        if not possible:
            return False, pos

        board[target_pos['y']][target_pos['x']] = board[pos['y']][pos['x']]
        board[pos['y']][pos['x']] = '.'

        if board[target_pos['y']][target_pos['x']] == '@':
            return True, target_pos # Return position moved to for robot
        else:
            return True, pos
        

for line in lines:
    if len(line) == 0:
        read_board = False
        continue

    if read_board:
        if line.find('@') > 0:
            player_pos = {'x': line.find('@'), 'y': len(board)}
        board.append(list(line))
    
    else:
        moves += line

n, m  = len(board), len(board[0])

print_board()
print(moves)
print(player_pos)
print(n, m, len(moves))
print()


move_to_dir = {
    '<': {'x': -1, 'y': 0},
    '>': {'x': 1, 'y': 0},
    '^': {'x': 0, 'y': -1},
    'v': {'x': 0, 'y': 1},
}

for move in moves:
    success, player_pos = try_move(player_pos, move_to_dir[move])
    #print(success, player_pos)

print_board()

total = 0
for y in range(n):
    for x in range(m):
        if board[y][x] != 'O':
            continue
        total += 100*y+x

print("Total: ", total)