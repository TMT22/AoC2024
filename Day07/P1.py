input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]


max_k = 0
equations = []
for line in lines:
    total_val, operators = line.split(':')

    total_val = int(total_val)
    operators = list(map(int, operators.rstrip().split()))

    equations.append((total_val, operators))

    max_k = max(max_k, len(operators))


n = len(equations)


# Evaluate left-to-right
def get_val(numbers, bin):
    val = numbers[0]
    bin_rem = bin

    for i in range(1, len(numbers)):
        if bin_rem%2 == 0: val += numbers[i]
        if bin_rem%2 == 1: val *= numbers[i]

        bin_rem = bin_rem // 2

    return val


total = 0
for equation in equations:
    total_val, operators = equation
    m = len(operators)-1
    for bin in range(1<<m):
        if get_val(operators, bin) == total_val:
            print(total_val, get_val(operators, bin), bin, operators)

            total += total_val
            break

print(max_k, n)
print("Total: ", total)