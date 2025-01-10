input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

switch_read = False

get_val = dict()


def comb_to_func(a, comb, b):
    if comb == 'AND':
        return lambda: 1 if get_val[a]() == 1 and get_val[b]() == 1 else 0
    if comb == 'OR':
        return lambda: 1 if  get_val[a]() == 1 or get_val[b]() == 1 else 0
    if comb == 'XOR':
        return lambda: 0 if get_val[a]() == get_val[b]() else 1

def ret_val(val):
    return lambda: val

for line in lines:
    if len(line) == 0:
        switch_read = True
        continue
    
    if not switch_read:
        target, val = line.split(': ')
        val = int(val)
        get_val[target] = ret_val(val)
        
    else:
        operands, target = line.split(' -> ')
        op1, comb, op2 = operands.split()
        assert target not in get_val.keys()
        get_val[target] = comb_to_func(op1, comb, op2)




zs = reversed(sorted(list(filter(lambda e: e[0]=='z', get_val.keys()))))

total = 0

string = ""

for z in zs:
    total *= 2
    total += get_val[z]()
    print(z, get_val[z]())
    string += str(get_val[z]())

print("Total: ", total, string)