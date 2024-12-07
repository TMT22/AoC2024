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
def get_val(numbers, bin, target_val):
    rem_val = target_val
    bin_rem = bin


    for i in reversed(range(1, len(numbers))):
        if bin_rem%3 == 0: 
            rem_val -= numbers[i]
            if rem_val <= 0:
                break

        if bin_rem%3 == 1:
            if rem_val % numbers[i] != 0:
                rem_val = -1
                break

            rem_val //= numbers[i]

        if bin_rem%3 == 2:
            num = str(numbers[i])

            if str(rem_val)[-len(num):] != num:
                rem_val = -1
                break
            
            rem_val = int('0' + str(rem_val)[:-len(num)])

        bin_rem = bin_rem // 3

    return rem_val == numbers[0]


total = 0
for equation in equations:
    total_val, operators = equation
    m = len(operators)-1
    for bin in range(3**m):
        if get_val(operators, bin, total_val):
            print(total_val, bin, operators)

            total += total_val
            break

print(max_k, n)
print("Total: ", total)