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

def try_move(pos, dir, apply=True):
    # Cannot move wall
    if board[pos['y']][pos['x']] == '#':
        return False, pos

    # Can move onto free point
    if board[pos['y']][pos['x']] == '.':
        return True, pos
    
    # Box pushes
    if board[pos['y']][pos['x']] == '[' or board[pos['y']][pos['x']] == ']':

        # Box pushes itself
        if dir['y'] == 0:
            possible, target_pos = try_move({'x': pos['x']+dir['x'], 'y':pos['y']+dir['y']}, dir, apply=apply)

            if not possible:
                return False, pos

            if apply:
                board[target_pos['y']][target_pos['x']] = board[pos['y']][pos['x']]
                board[pos['y']][pos['x']] = '.'

            return True, pos

        # Box needs to push its counterpart as well
        other_pos = {'x': pos['x']+1, 'y':pos['y']} if board[pos['y']][pos['x']] == '[' else {'x': pos['x']-1, 'y':pos['y']}

        possible, target_pos = try_move({'x': pos['x']+dir['x'], 'y':pos['y']+dir['y']}, dir, apply=False)
        possible_other, target_pos_other = try_move({'x': other_pos['x']+dir['x'], 'y':other_pos['y']+dir['y']}, dir, apply=False)

        if not possible or not possible_other:
            return False, pos
        
        if apply:
            possible, target_pos = try_move({'x': pos['x']+dir['x'], 'y':pos['y']+dir['y']}, dir, apply=apply)
            possible_other, target_pos_other = try_move({'x': other_pos['x']+dir['x'], 'y':other_pos['y']+dir['y']}, dir, apply=apply)

            board[target_pos['y']][target_pos['x']] = board[pos['y']][pos['x']]
            board[target_pos_other['y']][target_pos_other['x']] = board[other_pos['y']][other_pos['x']]

            board[pos['y']][pos['x']] = '.'
            board[other_pos['y']][other_pos['x']] = '.'

        return True, pos
        

    # Player move
    if board[pos['y']][pos['x']] == '@':
        possible, target_pos = try_move({'x': pos['x']+dir['x'], 'y':pos['y']+dir['y']}, dir, apply=apply)

        if not possible:
            return False, pos

        if apply:
            board[target_pos['y']][target_pos['x']] = board[pos['y']][pos['x']]
            board[pos['y']][pos['x']] = '.'

        if board[target_pos['y']][target_pos['x']] == '@' and apply:
            return True, target_pos # Return position moved to for robot
        else:
            return True, pos
        

for line in lines:
    if len(line) == 0:
        read_board = False
        continue

    if read_board:
        line = line.replace('#', '##').replace('.', '..').replace('O', '[]').replace('@', '@.')
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
    #print_board()
    print(success, player_pos)


print_board()

total = 0
for y in range(n):
    for x in range(m):
        if board[y][x] != '[':
            continue
        total += 100*y+x

print("Total: ", total)