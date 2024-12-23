input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

MOD = 16777216

def generate_seq(k, iters):
    global MOD

    ret = []
    changes = []

    ret.append(k%10)
    
    for iter in range(iters):
        k = ((k * 64)^k) % MOD
        k = ((k // 32)^k) % MOD
        k = ((k * 2048)^k) % MOD
        ret.append(k%10)
        changes.append(ret[-1]-ret[-2])

    return ret, changes

"""
change_seq_vals = dict()

for i0 in range(-11, 12):
    for i1 in range(-11, 12):
        for i2 in range(-11, 12):
            for i3 in range(-11, 12):
                change_seq_vals[(i0, i1, i2, i3)] = 0
"""

change_seq_vals = [0 for i in range(24*24*24*24)]

def process_sequence(seq, changes):
    global change_seq_vals

    seen = set()

    for i in range(len(changes)-4):
        change_seq = tuple(changes[i:i+4])
        val = seq[i+4]

        if change_seq in seen:
            continue

        change_seq_vals[(change_seq[0]+11)*24*24*24 + (change_seq[1]+11)*24*24 + (change_seq[2]+11)*24 + (change_seq[3]+11)] += val
        seen.add(change_seq)


for line in lines:
    seq, changes = generate_seq(int(line), 2000)
    process_sequence(seq, changes)

best = -1
best_change_seq = None

"""
for key in change_seq_vals.keys():
    poss_best = change_seq_vals[key]
    if best < poss_best:
        best = poss_best
        best_change_seq = key
"""

for i in range(len(change_seq_vals)):
    poss_best = change_seq_vals[i]
    if best < poss_best:
        best = poss_best
        best_change_seq = i

print(best, best_change_seq)





