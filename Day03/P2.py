import re

input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

in_text = "".join(lines)


matches = re.findall(r"mul\([1-9][0-9]{0,2},[1-9][0-9]{0,2}\)|do\(\)|don't\(\)", in_text)



total = 0
enabled = True

for match in matches:
    print(match)
    
    if match.startswith("do"):
        if match == "don't()":
            enabled = False
        elif match == "do()":
            enabled = True

    elif enabled:
        nums = list(map(int, match[4:-1].split(',')))
        total += nums[0]*nums[1]

print("Total: ", total)