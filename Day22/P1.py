input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

MOD = 16777216

def get_secret(k, iters):
    global MOD
    for iter in range(iters):
        k = ((k * 64)^k) % MOD
        k = ((k // 32)^k) % MOD
        k = ((k * 2048)^k) % MOD

    return k

total = 0
for line in lines:
    print(int(line), get_secret(int(line), 2000))
    total += get_secret(int(line), 2000)

print("Total: ", total)





