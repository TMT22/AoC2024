import itertools

input_file = "Inputs/Test01.txt"

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

chars = '^v<>A'

get_pair = dict()

k = 0
for c0 in chars:
    for c1 in chars:
        get_pair[c0+c1] = k
        k += 1




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

def to_dist(code):
    dist = [0 for i in range(len(get_pair.keys()))]
    
    for i in range(len(code)-1):
        dist[get_pair[code[i:i+2]]] += 1
    
    return tuple(dist)

def dist_step(dist):
    new_dist = dist


mem_lengths = dict()
def get_min_length(code, iters_left):
    if iters_left == 0:
        return len(code)
    
    if (code, iters_left) in mem_lengths.keys():
        return mem_lengths[(code, iters_left)]

    ret = None

    parts = []

    curr_str = ""
    for c in code:
        curr_str += c
        if c == 'A':
            parts.append(curr_str)
            curr_str = ""

    # Generate next step
    total_length = 0

    for part in parts:
        _, next_codes = paths_code("A" + part, (0, 0), get_pos_dir)

        len_part = -1

        for next_code in next_codes:
            new_min = get_min_length(next_code, iters_left-1)
            if len_part < 0:
                len_part = new_min
            else:
                len_part = min(new_min, len_part)

        total_length += len_part

    mem_lengths[(code, iters_left)] = total_length

    return mem_lengths[(code, iters_left)]

def process_code(code, iters = 0):
    curr_min_len, possible_entries = paths_code("A"+code, (0, 3), get_pos_key)


    min_len = -1

    for entry in possible_entries:
        new_min = get_min_length(entry, 50)
        if min_len < 0:
            min_len = new_min
        else:
            min_len = min(new_min, min_len)
    
    return min_len






total = 0
for code in codes:
    m = process_code(code)
    num = int(code.replace('A', ''))
    print(code, m, num)

    total += m*num

"""
for c0 in chars:
    for c1 in chars:
        #print(c0+c1, paths_code(c0+c1, (0, 0), get_pos_dir))
        l0, seqs = paths_code(c0+c1, (0, 0), get_pos_dir)
        for seq in seqs:
            print(seq, paths_code(seq, (0, 0), get_pos_dir))
            paths_code(seq, (0, 0), get_pos_dir)
            l1, seqs1 = paths_code(seq, (0, 0), get_pos_dir)
            for seq1 in seqs1:
                print(seq1, paths_code(seq1, (0, 0), get_pos_dir)[0])

        print()

"""


print("Total: ", total)





