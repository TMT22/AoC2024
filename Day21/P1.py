import itertools

input_file = "Inputs/Input.txt"

with open(input_file) as f:
    codes = [line.rstrip() for line in f]


get_pos_key = {
    '7': (0, 0),
    '8': (1, 0),
    '9': (2, 0),

    '4': (0, 1),
    '5': (1, 1),
    '6': (2, 1),

    '1': (0, 2),
    '2': (1, 2),
    '3': (2, 2),

    '0': (1, 3),
    'A': (2, 3),
}

get_pos_dir = {
    '^': (1, 0),
    '<': (0, 1),
    'v': (1, 1),
    '>': (2, 1),
  
    'A': (2, 0),
}

get_move = {
    '^': (0, -1),
    '<': (-1, 0),
    'v': (0, 1),
    '>': (1, 0)
}


# Get all valid paths from one pos to another

mem_paths = dict()

def paths_key(start, end, invalid):
    if (start, end, invalid) in mem_paths.keys():
        return mem_paths[(start, end, invalid)]

    total_y = abs(end[1] - start[1])
    total_x = abs(end[0] - start[0])
    
    char_y = '^' if end[1] < start[1] else 'v'
    char_x = '<' if end[0] < start[0] else '>'

    chars = list([char_y for i in range(total_y)]) + list([char_x for i in range(total_x)])
    perms = list(itertools.permutations(chars))

    final_perms = set()

    for perm in perms:
        curr_pos = list(start)
        include = True
        for c in perm:
            curr_pos[0] += get_move[c][0]
            curr_pos[1] += get_move[c][1]

            if curr_pos[0] == invalid[0] and curr_pos[1] == invalid[1]: 
                include = False
                break

        if include:
            final_perms.add(perm)

    mem_paths[(start, end, invalid)] = final_perms

    return mem_paths[(start, end, invalid)]  

def paths_code(code, invalid, pos_retrieve):
    steps = []

    for i in range(len(code)-1):
        steps.append(paths_key(pos_retrieve[code[i]], pos_retrieve[code[i+1]], invalid))

    possible_entries = set()

    def build_entries(idx, curr_str):

        if idx >= len(steps):
            possible_entries.add(tuple(curr_str))
            return len(curr_str)
        
        min_len = 213213123131231231
        for poss in steps[idx]:
            min_len = min(min_len, build_entries(idx+1, curr_str + list(poss) + ['A']))
        
        return min_len

    min_len = build_entries(0, [])

    possible_entries = set(map(lambda l: "".join(l), filter(lambda l: len(l) == min_len, possible_entries)))
    
    return min_len, possible_entries


def process_code(code, iters = 2):
    curr_min_len, possible_entries = paths_code("A"+code, (0, 3), get_pos_key)

    print(curr_min_len)
    for iter in range(iters):
        new_possible_entries = set()
        new_min_len = 2131231231231231231231

        for k in possible_entries:
            min_len, possible_codes = paths_code("A"+"".join(k), (0, 0), get_pos_dir)
            new_possible_entries = new_possible_entries.union(possible_codes)
            new_min_len = min(new_min_len, min_len)
            
        
        possible_entries = set(filter(lambda l: len(l)==new_min_len, new_possible_entries))
        curr_min_len = new_min_len
        print(curr_min_len)

    return curr_min_len



total = 0
for code in codes:
    m = process_code(code)
    num = int(code.replace('A', ''))
    print(code, m, num)

    total += m*num

print("Total: ", total)





