#include"parsing.cpp"

int PC;
unordered_map<uint32_t, uint8_t> memory;
unordered_map<uint32_t, string> instructions;

class register_file {
private:
    uint32_t r[32]; //registers
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
        memory[address + i] = value & 0xFF; // 11111111
        value >>= 8;
    }
    // 909
    // 01110101 01111111 01110101 00010101
    // 00000000 00000000 00000000 11111111 &

    // 00000000 00000000 00000000 00010101
    // add + 3  add + 2  add + 1  add + 0
}
void readNBytes(uint32_t address, int byte_count, int index)
{
    reg[index] = 0;

    for (uint32_t i = 0; i < byte_count; ++i) {
        reg[index] |= (uint32_t(memory[address + i]) << (8 * i));

    }
}
//LW x1, 32(x18) 
//SW rs2, offset(rs1)
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
    unsigned int unsignedValue1 = static_cast<unsigned int>(exe.r1);
    unsigned int unsignedValue2 = static_cast<unsigned int>(exe.r2);
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

 void AND(int RD,int RS1, int RS2)
{
    // And x1, x1, x2
    reg[RD] = reg[RS1] & reg[RS2];
    PC++;
    // R3=R1&R2;
 }
 void OR (int RD,int RS1,int RS2)
 {
    reg[RD] = reg[RS1] | reg[RS2];
    PC++;
 }
void ORI(int RD,int RS1,int immediate)
 {
    reg[RD] = reg[RS1] | immediate;
    PC++;
 }
 void ADD(int RD,int RS1,int RS2)
 {
    reg[RD] = reg[RS1] + reg[RS2];
    PC++;
 }
void SUB(int RD,int RS1,int RS2)
 {
    reg[RD] = reg[RS1] - reg[RS2];
    PC++;
 }
 void ADDI(int RD,int RS1,int immediate)
 {
    reg[RD] = reg[RS1] + immediate;
    PC++;
 }
 void XOR(int RD,int RS1,int RS2)
 {
    reg[RD] = reg[RS1] ^ reg[RS2];
    PC++;
 }
 void XORI(int RD,int RS1,int immediate)
 {
    reg[RD] = reg[RS1] ^ immediate;
    PC++;
 }
void SLL(int RD,int RS1,int RS2)
 {
    reg[RD] = reg[RS1] << reg[RS2];
    PC++;
 }
void SLLI(int RD,int RS1,int shamt)
 {
    reg[RD] = reg[RS1] << uint32_t(shamt);
    PC++;
 }
void SLT(int RD,int RS1,int RS2)
 {
    reg[RD] = int32_t(reg[RS1]) < int32_t(reg[RS2]);
 }
void SLTU(int RD,int RS1,int RS2)
 {
    reg[RD] = reg[RS1] < reg[RS2];
 } 
void SLTIU(int RD,int RS1,int immediate)
 {
    reg[RD] = reg[RS1] < immediate;
 }
void SRA(int RD,int RS1,int RS2)
 {
    reg[RD] = int32_t(reg[RS1]) >> int32_t(reg[RS2]);
 }
void SRAI(int RD,int RS1,int shamt)
 {
    reg[RD] = int32_t(reg[RS1]) >> shamt;
 }
void SRLI(int RD,int RS1,int shamt)
 {
    reg[RD] = reg[RS1] >> uint32_t(shamt);
 }
void SRL(int RD,int RS1,int RS2)
 {
    reg[RD] = reg[RS1] >> reg[RS2];
 }
void SLTI(int RD, int RS1, int immediate)
{
    reg[RD] = int32_t(reg[RS1]) < immediate;
}
void EBREAK() {
    exit(0);
}
void ECALL() {
    exit(0);
}
void FENCE() {
    exit(0);
}

void print(uint32_t &value, char base/*b: binary, h:hex, d:decimal*/) {
    switch (base) {
        case 'h':
            cout << hex << value;
        case 'b':
            cout << bitset<32>(value);
        case 'd':
            cout << value;
        default:
            cout << "Error: Unrecognized base " << base << '\n';
    }
}


// int main() {
//     reg[0] = 100;
//     reg[1] = 100;
//     cout << reg[0] << ' ' << reg[1] << '\n';
//     return 0;
// }