input_file = "Inputs/Test01.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

graph = dict()

# Build graph
for line in lines:
    parts = line.split('-')
    if parts[0] not in graph.keys():
        graph[parts[0]] = set()
    
    if parts[1] not in graph.keys():
        graph[parts[1]] = set()
    
    graph[parts[0]].add(parts[1])
    graph[parts[1]].add(parts[0])

final_sets = set()

for line in lines:
    parts = line.split('-')
    commons = graph[parts[0]].intersection(graph[parts[1]])

    for e in commons:
        final_sets.add(tuple(sorted([parts[0], parts[1], e])))

total = 0
for s in final_sets:
    contains_t = False
    for e in s:
        if 't' == e[0]:
            contains_t = True
            break
    if contains_t:
        total += 1
        print(s)

print("Total: ", total)