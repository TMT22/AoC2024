input_file = "Inputs/Test01.txt"
W, H = 101, 103

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

robots = []

for line in lines:
    pos, vel = line.split(' ')
    pos = list(map(int, pos[2:].split(',')))
    vel = list(map(int, vel[2:].split(',')))

    print(pos, vel)
    robots.append({"pos": pos, "vel": vel})

quads = [0, 0, 0, 0]

for r in range(len(robots)):
    robots[r]['pos'][0] = ((robots[r]['pos'][0] + 100 * robots[r]['vel'][0])%W+W)%W
    robots[r]['pos'][1] = ((robots[r]['pos'][1] + 100 * robots[r]['vel'][1])%H+H)%H

    if robots[r]['pos'][0] < W//2 and robots[r]['pos'][1] < H//2:
        quads[0]+=1
    
    if robots[r]['pos'][0] > W//2 and robots[r]['pos'][1] < H//2:
        quads[1]+=1

    if robots[r]['pos'][0] < W//2 and robots[r]['pos'][1] > H//2:
        quads[2]+=1
    
    if robots[r]['pos'][0] > W//2 and robots[r]['pos'][1] > H//2:
        quads[3]+=1

print(quads)
print("Total:", quads[0]*quads[1]*quads[2]*quads[3])
