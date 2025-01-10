input_file = "Inputs/Test02.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

switch_read = False

get_val = dict()
get_OPs = dict()

get_comps = dict()

implied_names = dict()


def comb_to_func(a, comb, b):
    if comb == 'AND':
        return lambda: 1 if get_val[a]() == 1 and get_val[b]() == 1 else 0
    if comb == 'OR':
        return lambda: 1 if  get_val[a]() == 1 or get_val[b]() == 1 else 0
    if comb == 'XOR':
        return lambda: 0 if get_val[a]() == get_val[b]() else 1


import random
X = random.randint(0, 1 << 40)
Y = random.randint(0, 1 << 40)

def ret_val(id, bit):
    global X, Y
    return lambda: (X//(1<<bit))%2 if id == 'x' else (Y//(1<<bit))%2

swaps = dict()

swaps["z05"] = "dkr"
swaps["dkr"] = "z05"

swaps["z20"] = "hhh"
swaps["hhh"] = "z20"


swaps["htp"] = "z15"
swaps["z15"] = "htp"

swaps["rhv"] = "ggk"
swaps["ggk"] = "rhv"




for line in lines:
    if len(line) == 0:
        switch_read = True
        continue
    
    if not switch_read:
        target, val = line.split(': ')
        val = int(val)
        get_val[target] = ret_val(target[0], int(target[1:]))
        if target not in get_comps.keys():
            get_comps[target] = []
        implied_names[target] = {target}
        
    else:
        operands, target = line.split(' -> ')
        if target in swaps.keys():
            target = swaps[target]

        op1, comb, op2 = operands.split()
        assert target not in get_val.keys()
        get_val[target] = comb_to_func(op1, comb, op2)

        if op1 not in get_OPs.keys():
            get_OPs[op1] = []
        
        if op2 not in get_OPs.keys():
            get_OPs[op2] = []
        
        if target not in get_comps.keys():
            get_comps[target] = []


        get_OPs[op1].append((op2, comb, target))
        get_OPs[op2].append((op1, comb, target))

        get_comps[target] = (op1, comb, op2)

        if target[0] == 'z':
            implied_names[target] = set()
            implied_names[target].add(target)

BITS = 44


for i in range(0, BITS):

    in_x, in_y, in_c, out_z = f"x{i+1:02}", f"y{i+1:02}", f"c{i:02}", f"z{i+1:02}"

    target_x = sorted(get_OPs[in_x], key=lambda e: e[1])
    target_y = sorted(get_OPs[in_y], key=lambda e: e[1])

    assert target_x[0][2] == target_y[0][2]
    assert target_x[1][2] == target_y[1][2]

    b_i_in = target_x[0][2]
    t_i_in = target_x[1][2]


    c_t_i_out = [get_comps[out_z][0], get_comps[out_z][2]]

    if t_i_in not in c_t_i_out:
        print(in_x, in_y)#t_i_in, c_t_i_out, out_z)
        print(target_x, target_y)
        breakpoint()
        continue

    if c_t_i_out[0] == t_i_in:
        c_i = c_t_i_out[1]
    else:
        c_i = c_t_i_out[0]


    targets_t = sorted(get_OPs[t_i_in], key=lambda e: e[1])
    targets_c = sorted(get_OPs[c_i], key=lambda e: e[1])
    
    assert len(targets_t) == 2 and len(targets_c) == 2

    assert targets_t[0][2] == targets_c[0][2]
    assert targets_t[1][2] == targets_c[1][2]

    a_i_in = targets_t[0][2]

    print(targets_t)
    #print(a_i_in, get_comps[a_i_in])
    #print(a_i_in, get_OPs[a_i_in])



    #print(b_i_in, targets_t, targets_c)
    

    
xs = reversed(sorted(list(filter(lambda e: e[0]=='x', get_val.keys()))))
ys = reversed(sorted(list(filter(lambda e: e[0]=='y', get_val.keys()))))

total_x = 0
for x in xs:
    total_x *= 2
    total_x += get_val[x]()

total_y = 0
for y in ys:
    total_y *= 2
    total_y += get_val[y]()


zs = reversed(sorted(list(filter(lambda e: e[0]=='z', get_val.keys()))))



for i in range(1):

    total = 0
    string = ""
    X = random.randint(0, 1 << 40)
    Y = random.randint(0, 1 << 40)
    s = X + Y
    for z in zs:
        total *= 2
        total += get_val[z]()
        string += str(get_val[z]())
    
    print("Total: ", total, s, total - s, string)



gate_list = []

for key in swaps.keys():
    gate_list.append(str(key))

print(",".join(sorted(gate_list)))