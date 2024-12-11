input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

stones = list(map(int, lines[0].split()))

mem = dict()

def get_num(n, k):
    if k == 0:
        return 1

    if (n, k) in mem.keys():
        return mem[(n, k)]

    n_str = str(n)

    if n == 0:
        mem[(n, k)] = get_num(1, k-1)
    elif len(n_str) % 2 == 0: 
        mem[(n, k)] = get_num(int(n_str[:len(n_str)//2]), k-1) + get_num(int(n_str[len(n_str)//2:]), k-1)
    else:
        mem[(n, k)] = get_num(n*2024, k-1)

    return mem[(n, k)]

n_trans = 75

total = 0
for s in stones:
    total += get_num(s, n_trans)


print("Total: ", total)