input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

stones = list(map(int, lines[0].split()))

def apply_transform(stone_line):
    new_stone_line = []

    for stone in stone_line:
        stone_str = str(stone)
        if stone == 0:
            new_stone_line.append(1)
        elif len(stone_str) % 2 == 0:
            new_stone_line.append(int(stone_str[:len(stone_str)//2]))
            new_stone_line.append(int(stone_str[len(stone_str)//2:]))
        else:
            new_stone_line.append(stone * 2024)

    return new_stone_line

n_trans = 25

for i in range(n_trans):
    stones = apply_transform(stones)


print("Total: ", len(stones))