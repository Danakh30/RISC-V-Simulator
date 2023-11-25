#include"parsing.cpp"

int PC;
unordered_map<uint32_t, int8_t> memory;

class register_file {
private:
    uint32_t r[32]; 
public:
    register_file() {
        for (int i = 0; i < 32; ++i) {
            r[i] = 0;
        }
    }
    uint32_t& operator[](int index) {
        r[0] = 0;
        return r[index];
    }
};
register_file reg;

void writeNBytes(uint32_t address, uint32_t value, int byte_count)
{
    for (uint32_t i = 0; i < byte_count; ++i) {
        memory[address + i] = value & 0xFF;
        value >>= 8;
    }

 }
void readNBytes(uint32_t address, int byte_count, int index)
{
    reg[index] = 0;

    for (uint32_t i = 0; i < byte_count; ++i) 
    {
        reg[index] |= (uint32_t(memory[address + i]) << (8 * i));

    }
}

void InputToMemory()
{
    uint32_t value;
    uint32_t address;
    ifstream memoryload("memoryload.txt");

    while(memoryload >> address >> value) {
       writeNBytes(address, value, 1);
    }
}
void LUI(instruction exe)
{
    reg[exe.rd] = exe.immidiate << 12;
    PC+=4;
}

void AUIPC(instruction exe)
{
    reg[exe.rd] = (exe.immidiate << 12) + PC;
    PC+=4;
}

void JAL(instruction exe)
{
    reg[exe.rd] = PC + 4;
    PC += (exe.immidiate * 4);
}

void JALR(instruction exe)
{
    reg[exe.rd] = PC + 4;
    PC = 4*(reg[exe.r1] + exe.immidiate);
}

void BEQ(instruction exe)
{
    if(reg[exe.r1]==reg[exe.r2])
    {
        PC += (exe.immidiate * 4);
    }
    else{PC += 4;}
}

void BNE(instruction exe)
{
    if(reg[exe.r1]!=reg[exe.r2])
    {
        PC += (exe.immidiate * 4);
    }
    else{PC += 4;}
}

void BLT(instruction exe)
{
    if(reg[exe.r1] < reg[exe.r2])
    {
        PC += (exe.immidiate * 4);
    }
    else{PC += 4;}
}

void BGE(instruction exe)
{
    if(reg[exe.r1] >= reg[exe.r2])
    {
        PC += (exe.immidiate * 4);
    }
    else{PC += 4;}
}

void BLTU(instruction exe)
{
    unsigned int unsignedValue1 = static_cast<unsigned int>(reg[exe.r1]);
    unsigned int unsignedValue2 = static_cast<unsigned int>(reg[exe.r2]);
    if(unsignedValue1 < unsignedValue2)
    {
        PC += (4*exe.immidiate);
    }
    else{PC += 4;}
}

void BGEU(instruction exe)
{
    unsigned int unsignedValue1 = static_cast<unsigned int>(exe.r1);
    unsigned int unsignedValue2 = static_cast<unsigned int>(exe.r2);
    if(unsignedValue1 >= unsignedValue2)
    {
        PC += (4*exe.immidiate);
    }
    else{PC += 4;} 
}

void LB(instruction exe)
{
    int8_t loadedByte=static_cast<int8_t>(memory[reg[exe.r1]+exe.immidiate]);
    reg[exe.rd] = static_cast<int32_t>(loadedByte);
    PC+=4;
}

void LH(instruction exe) 
{
    int16_t halfword = (memory[reg[exe.r1] + exe.immidiate + 1] << 8) | memory[reg[exe.r1] + exe.immidiate];
    reg[exe.rd] = static_cast<int32_t>(halfword);
}

void LW(instruction exe)
{
    int32_t word = 0;
    // Little-endian byte order: lowest address contains least significant byte
    for (int i = 0; i < 4; ++i) 
    {
        word |= (static_cast<uint32_t>(memory[reg[exe.r1] + exe.immidiate + i]) & 0xFF) << (i * 8);
    }
    reg[exe.rd] = word;
    PC+=4;
}

void LBU(instruction exe)
{
    int8_t eightBit = memory[reg[exe.r1]+exe.immidiate];
    reg[exe.rd] = static_cast<uint32_t>(static_cast<uint8_t>(eightBit));
    PC+=4;
}

void LHU(instruction exe) 
{
    uint32_t address = reg[exe.r1] + exe.immidiate;
    uint16_t halfword = static_cast<uint16_t>(memory[address]) |
                        (static_cast<uint16_t>(memory[address + 1]) << 8);
    reg[exe.rd] = static_cast<uint32_t>(halfword);
    PC += 4;
}

void SB(instruction exe) 
{
    uint32_t address = reg[exe.r1] + exe.immidiate;
    uint8_t valueToStore = static_cast<uint8_t>(reg[exe.r2]);
    memory[address] = valueToStore;
    PC += 4;
}

void SH(instruction exe) 
{
    uint32_t address = reg[exe.r1] + exe.immidiate;
    uint16_t valueToStore = static_cast<uint16_t>(reg[exe.r2]);
    memory[address] = static_cast<uint8_t>(valueToStore & 0xFF);
    memory[address + 1] = static_cast<uint8_t>((valueToStore >> 8) & 0xFF);
    PC += 4;
}

void SW(instruction exe) 
{
    uint32_t address = reg[exe.r1] + exe.immidiate;
    uint32_t valueToStore = reg[exe.r2];
    memory[address] = static_cast<uint8_t>(valueToStore & 0xFF);
    memory[address + 1] = static_cast<uint8_t>((valueToStore >> 8) & 0xFF);
    memory[address + 2] = static_cast<uint8_t>((valueToStore >> 16) & 0xFF);
    memory[address + 3] = static_cast<uint8_t>((valueToStore >> 24) & 0xFF);
    PC += 4;
}

void ADDI(instruction exe) 
{
    reg[exe.rd] = reg[exe.r1] + exe.immidiate;
    PC += 4;
}

void SLTI(instruction exe) 
{
    reg[exe.rd] = (static_cast<int32_t>(reg[exe.r1]) < static_cast<int32_t>(exe.immidiate)) ? 1 : 0;
    PC += 4;
}

  void AND(instruction exe)
{
    reg[exe.rd] = reg[exe.r1] & reg[exe.r2];
    PC+=4;
 }
 void ANDI(instruction exe)
{
    reg[exe.rd] = reg[exe.r1] & exe.immidiate;
    PC+=4;
 }
 void OR (instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] | reg[exe.r2];
    PC+=4;
 }
void ORI(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] | exe.immidiate;
    PC+=4;
 }
 void ADD(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] + reg[exe.r2];
    PC+=4;
 }
void SUB(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] - reg[exe.r2];
    PC+=4;
 }
 void ADDI(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] + exe.immidiate;
    PC+=4;
 }
 void XOR(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] ^ reg[exe.r2];
    PC+=4;
 }
 void XORI(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] ^ exe.immidiate;
    PC+=4;
 }
void SLL(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] << reg[exe.r2];
    PC+=4;
 }
void SLLI(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] << uint32_t(exe.immidiate);
    PC+=4;
 }
void SLT(instruction exe)
 {
    reg[exe.rd] = int32_t(reg[exe.r1]) < int32_t(reg[exe.r2]);
    PC+=4;
 }
void SLTU(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] < reg[exe.r2];
    PC+=4;
 } 
void SLTIU(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] < exe.immidiate;
    PC+=4;
 }
void SRA(instruction exe)
 {
    reg[exe.rd] = int32_t(reg[exe.r1]) >> int32_t(reg[exe.r2]);
    PC+=4;
 }
void SRAI(instruction exe)
 {
    reg[exe.rd] = int32_t(reg[exe.r1]) >> exe.immidiate;
    PC+=4;
 }
void SRLI(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] >> uint32_t(exe.immidiate);
    PC+=4;
 }
void SRL(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] >> reg[exe.r2];
    PC+=4;
 }
void SLTI(instruction exe)
{
    reg[exe.rd] = int32_t(reg[exe.r1]) < exe.immidiate;
    PC+=4;
}
void EBREAK(instruction exe) {
    exit(0);
    PC+=4;
}
void ECALL(instruction exe) {
    exit(0);
    PC+=4;
}
void FENCE(instruction exe) {
    exit(0);
    PC+=4;
}

void print(uint32_t &value, char base/*b: binary, h:hex, d:decimal*/) {
    switch (base) {
        case 'h':
            cout << hex << value;
            break;
        case 'b':
            cout << bitset<32>(value);
            break;
        case 'd':
            cout << value;
            break;
        default:
            cout << "Error: Unrecognized base " << base << '\n';
    }
    cout.setf(std::ios_base::dec, std::ios_base::basefield);
}
void output() {
    cout << "PC: " << PC << '\n';
    cout << "Registers:\n";
    char bases[] = {'b', 'd', 'h'};
    for (char base : bases) {
        for (int i = 0; i < 32; ++i) {
            cout << "X" << i << ' ';
            print(reg[i], base);
            cout << '\n';
        }
        cout << '\n';
    }
}
using FunctionPointer2 = void (*)(instruction);
unordered_map<string, FunctionPointer2> instructionFunctions=
{
    {"LUI", &LUI},
    {"AUIPC", &AUIPC},
    {"JAL", &JAL},
    {"JALR", &JALR},
    {"ADDI", &ADDI},
    {"SLTI", &SLTI},
    {"SLTIU", &SLTIU},
    {"XORI", &XORI},
    {"ORI", &ORI},
    {"ANDI", &ANDI},
    {"SLLI", &SLLI},
    {"SRLI", &SRLI},
    {"SRAI", &SRAI},
    {"LB", &LB},
    {"LH", &LH},
    {"LW", &LW},
    {"LBU", &LBU},
    {"LHU", &LHU},
    {"BEQ", &BEQ},
    {"BNE", &BNE},
    {"BLT", &BLT},
    {"BGE", &BGE},
    {"BLTU", &BLTU},
    {"BGEU", &BGEU},
    {"SB", &SB},
    {"SH", &SH},
    {"SW", &SW},
    {"ADD", &ADD},
    {"SUB", &SUB},
    {"SLL", &SLL},
    {"SLT", &SLT},
    {"SLTU", &SLTU},
    {"XOR", &XOR},
    {"SRL", &SRL},
    {"SRA", &SRA},
    {"OR", &OR},
    {"AND", &AND},
    {"FENCE", &FENCE},
    {"ECALL", &ECALL},
    {"EBREAK", &EBREAK}
}; 

void execute()
{
    InputToMemory();
    extractCode();
    int PC_int;
    while(1)
    {
        PC_int=PC/4;
        cout << "PC --> " << PC << endl;
        FunctionPointer2 func2 = instructionFunctions[program[PC_int].opcode];
        func2(program[PC_int]);
        output();
    }
}

int main() 
{
    reg[1] = 5;
    reg[2] = 3;
    PC = 0;
    execute();
}