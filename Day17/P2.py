input_file = "Inputs/Input2.txt"

with open(input_file) as f:
    lines = [line.rstrip() for line in f]

REGISTERS = [0, 0, 0]
INSTRUCTION_POINTER = 0
OUTPUT = []
def get_value(combo_command):
    global REGISTERS
    assert combo_command != 7

    if 0 <= combo_command and combo_command <= 3:
        return combo_command
    
    return REGISTERS[combo_command-4]

def set_value(combo_command, val):
    global REGISTERS

    assert combo_command != 7
    assert combo_command > 3
    
    REGISTERS[combo_command-4] = val

def adv(inp):
    set_value(4, int(get_value(4)/(1 << get_value(inp))))

def bxl(inp):
    set_value(5, get_value(5) ^ inp)

def bst(inp):
    set_value(5, get_value(inp)%8)

def jnz(inp):
    global INSTRUCTION_POINTER
    if get_value(4) == 0:
        return
    INSTRUCTION_POINTER = inp
    INSTRUCTION_POINTER -= 2

def bxc(inp):
    set_value(5, get_value(5)^get_value(6))

def out(inp):
    global OUTPUT
    OUTPUT.append(str(get_value(inp)%8))

def bdv(inp):
    set_value(5, int(get_value(4)/(1 << get_value(inp))))

def cdv(inp):
    set_value(6, int(get_value(4)/(1 << get_value(inp))))


INSTRUCTIONS = [adv, bxl, bst, jnz, bxc, out, bdv, cdv]

def run_programm(programm, A_val):
    global INSTRUCTION_POINTER, OUTPUT, REGISTERS
    
    REGISTERS[0] = A_val
    REGISTERS[1] = 0
    REGISTERS[2] = 0

    OUTPUT = []

    INSTRUCTION_POINTER = 0
    success = True
    l = 0

    while INSTRUCTION_POINTER < len(programm):
        ins, inp = programm[INSTRUCTION_POINTER], programm[INSTRUCTION_POINTER+1]
        INSTRUCTIONS[ins](inp)

        if len(OUTPUT) > 0 and (len(OUTPUT) > len(programm) or int(OUTPUT[-1]) != programm[len(OUTPUT)-1]):
            l = len(OUTPUT)
            success = False
            break
            
        INSTRUCTION_POINTER += 2

    if len(OUTPUT) != len(programm):
        success = False
    
    return success, l



program_text = list(map(int, lines[4].split()[1].strip().split(',')))
ans = 2312312312312313123123 # 164545858203325


def backtrack(curr_pos, curr_val):
    global ans, program_text
    s, l = run_programm(program_text, curr_val)
    
    print((curr_pos, curr_val), (s, l))

    if curr_pos > 50:
        return False

    if len(OUTPUT) < curr_pos // 4:
        return False

    if s:
        print(curr_val)
        ans = min(curr_val, ans)
        return True
    
    backtrack(curr_pos+1, curr_val)
    backtrack(curr_pos+1, curr_val + (1 << curr_pos))

    return False
    

print(REGISTERS)
print(program_text)

backtrack(0, 0)
print(f"{ans:0b}")
print(ans)
