#include<bits/stdc++.h>
using namespace std;


register_file reg;
map<uint32_t, uint8_t> memory; 
int pc;//address, value (byte value)
// unordered_map<uint32_t, string> instructions;

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
struct instruction
{
    string opcode;
    int r1, r2, rd, immidiate;

    instruction()
    {
        opcode = "";
        r1 = 0;
        r2 = 0;
        rd = 0;
        immidiate = 0;
    }    
};

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
        reg[index] |= (memory[address + i] << (8 * i));

    }
}
//LW x1, 32(x18) 
//SW rs2, offset(rs1)


 void AND(instruction exe)
{
    // And x1, x1, x2
    reg[exe.rd] = reg[exe.r1] & reg[exe.r2];
    pc+=4;
    // R3=R1&R2;
 }
 void ANDI(instruction exe)
{
    reg[exe.rd] = reg[exe.r1] & exe.immidiate;
    pc+=4;
 }
 void OR (instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] | reg[exe.r2];
    pc+=4;
 }
void ORI(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] | exe.immidiate;
    pc+=4;
 }
 void ADD(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] + reg[exe.r2];
    pc+=4;
 }
void SUB(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] - reg[exe.r2];
    pc+=4;
 }
 void ADDI(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] + exe.immidiate;
    pc+=4;
 }
 void XOR(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] ^ reg[exe.r2];
    pc+=4;
 }
 void XORI(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] ^ exe.immidiate;
    pc+=4;
 }
void SLL(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] << reg[exe.r2];
    pc+=4;
 }
void SLLI(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] << uint32_t(exe.immidiate);
    pc+=4;
 }
void SLT(instruction exe)
 {
    reg[exe.rd] = int32_t(reg[exe.r1]) < int32_t(reg[exe.r2]);
    pc+=4;
 }
void SLTU(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] < reg[exe.r2];
    pc+=4;
 } 
void SLTIU(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] < exe.immidiate;
    pc+=4;
 }
void SRA(instruction exe)
 {
    reg[exe.rd] = int32_t(reg[exe.r1]) >> int32_t(reg[exe.r2]);
    pc+=4;
 }
void SRAI(instruction exe)
 {
    reg[exe.rd] = int32_t(reg[exe.r1]) >> exe.immidiate;
    pc+=4;
 }
void SRLI(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] >> uint32_t(exe.immidiate);
    pc+=4;
 }
void SRL(instruction exe)
 {
    reg[exe.rd] = reg[exe.r1] >> reg[exe.r2];
    pc+=4;
 }
void SLTI(instruction exe)
{
    reg[exe.rd] = int32_t(reg[exe.r1]) < exe.immidiate;
    pc+=4;
}
void EBREAK() {
    exit(0);
    pc+=4;
}
void ECALL() {
    exit(0);
    pc+=4;
}
void FENCE() {
    exit(0);
    pc+=4;
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