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



mem = dict()
def expand_group(node_set):
    k = tuple(sorted(list(node_set)))
    if k in mem.keys():
        return mem[k]

    parts = [graph[node] for node in node_set]
    commons = set.intersection(*parts)

    
    mem[k] = node_set

    if len(commons) == 0:
        return mem[k]
    

    for c in commons:
        poss_group = expand_group(node_set.union({c}))
        if len(poss_group) > len(largest_group):
            mem[k] = poss_group
    
    return mem[k]

largest_group = set()

for line in lines:
    parts = set(line.split('-'))
    poss_group = expand_group(parts)
    if len(poss_group) > len(largest_group):
        largest_group = poss_group
    #print(largest_group)



print("PW: ", ','.join(sorted(list(largest_group))))

