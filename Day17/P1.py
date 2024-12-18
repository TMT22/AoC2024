input_file = "Inputs/Test01.txt"

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

def run_programm(programm):
    global INSTRUCTION_POINTER

    while INSTRUCTION_POINTER < len(programm):
        ins, inp = programm[INSTRUCTION_POINTER], programm[INSTRUCTION_POINTER+1]
        INSTRUCTIONS[ins](inp)
        if INSTRUCTION_POINTER < 0:
            print()

        INSTRUCTION_POINTER += 2


        print(ins, inp, REGISTERS, INSTRUCTION_POINTER)


for i in range(3):
    REGISTERS[i] = int(lines[i].split()[-1])

program_text = list(map(int, lines[4].split()[1].strip().split(',')))

print(REGISTERS)
print(program_text)

run_programm(program_text)
print(','.join(OUTPUT))