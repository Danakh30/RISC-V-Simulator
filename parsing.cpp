#include<bits/stdc++.h>
using namespace std;

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
vector<instruction> program;

vector<string> removeSubstring(string& originalString, const string& substringToRemove) 
{
    size_t pos = originalString.find(substringToRemove);

    if (pos != string::npos) {
        originalString.erase(pos, substringToRemove.length());
    }
    originalString.erase(remove_if(originalString.begin(), originalString.end(), ::isspace), originalString.end());
    vector<string> tokens;
    istringstream iss(originalString);
    string temp;
    char delimiter = ',';
    while(getline(iss, temp, delimiter))
    {
        tokens.push_back(temp);
    }
    return tokens;
}

void parseGroup1(string g1) //Parsing LUI and AUIPC
{
    instruction temp;
    vector<string> tokens;
    if(g1[0] == 'L')
    {
        tokens = removeSubstring(g1, "LUI");
        temp.opcode = "LUI";
    }
    else
    {
        tokens = removeSubstring(g1, "AUIPC");
        temp.opcode = "AUIPC";        
    }
    temp.rd=stoi(tokens[0].substr(1));
    temp.immidiate=stoi(tokens[1]);
    program.push_back(temp);
}

void parseJAL(string JAL)
{
    instruction temp;
    vector<string> tokens = removeSubstring(JAL, "JAL");
    temp.opcode = "JAL";
    temp.rd=stoi(tokens[0].substr(1));
    temp.immidiate=stoi(tokens[1]);
    program.push_back(temp);
}

void parseGroup2(string g2) //JALR - ADDI - SLTI - SLTIU - XORI - ORI - ANDI - SLLI - SRLI - SRAI
{
    instruction temp;
    vector<string> tokens;
    if(g2.find("JALR") != string::npos)
    {
        tokens = removeSubstring(g2, "JALR");
        temp.opcode = "JALR";
    }
    else if(g2.find("ADDI") != string::npos)
    {
        tokens = removeSubstring(g2, "ADDI");
        temp.opcode = "ADDI";       
    }
    else if(g2.find("SLTIU") != string::npos)
    {
        tokens = removeSubstring(g2, "SLTIU");
        temp.opcode = "SLTIU";       
    }
    else if(g2.find("SLTI") != string::npos)
    {
        tokens = removeSubstring(g2, "SLTI");
        temp.opcode = "SLTI";       
    }
    else if(g2.find("XORI") != string::npos)
    {
        tokens = removeSubstring(g2, "XORI");
        temp.opcode = "XORI";       
    }
    else if(g2.find("ORI") != string::npos)
    {
        tokens = removeSubstring(g2, "ORI");
        temp.opcode = "ORI";       
    }
    else if(g2.find("ANDI") != string::npos)
    {
        tokens = removeSubstring(g2, "ANDI");
        temp.opcode = "ANDI";       
    }
    else if(g2.find("SLLI") != string::npos)
    {
        tokens = removeSubstring(g2, "SLLI");
        temp.opcode = "SLLI";       
    }
    else if(g2.find("SRLI") != string::npos)
    {
        tokens = removeSubstring(g2, "SRLI");
        temp.opcode = "SRLI";       
    }
    else if(g2.find("SRAI") != string::npos)
    {
        tokens = removeSubstring(g2, "SRAI");
        temp.opcode = "SRAI";       
    }
    temp.rd=stoi(tokens[0].substr(1));
    temp.r1=stoi(tokens[1].substr(1));
    temp.immidiate=stoi(tokens[2]);
    program.push_back(temp);
}

void parseGroup3(string g3) //LB - LH - LW - LBU - LHU
{
    instruction temp;
    vector<string> tokens;
    if(g3.find("LBU") != string::npos)
    {
        tokens = removeSubstring(g3, "LBU");
        temp.opcode = "LBU";
    }
    else if(g3.find("LHU") != string::npos)
    {
        tokens = removeSubstring(g3, "LHU");
        temp.opcode = "LHU";       
    }
    else if(g3.find("LW") != string::npos)
    {
        tokens = removeSubstring(g3, "LW");
        temp.opcode = "LW";       
    }
    else if(g3.find("LB") != string::npos)
    {
        tokens = removeSubstring(g3, "LB");
        temp.opcode = "LB";       
    }
    else 
    {
        tokens = removeSubstring(g3, "LH");
        temp.opcode = "LH";       
    }
    temp.rd = stoi(tokens[0].substr(1));
    size_t pos = tokens[1].find('(');
    size_t pos2= tokens[1].find(')');
    temp.immidiate = stoi(tokens[1].substr(0,pos));
    temp.r1 = stoi(tokens[1].substr(pos+2,pos2));
    program.push_back(temp);   
}

void parseGroup4(string g4) //BEQ - BNE - BLT - BGE - BLTU - BGEU
{
    instruction temp;
    vector<string> tokens;
    if(g4.find("BEQ") != string::npos)
    {
        tokens = removeSubstring(g4, "BEQ");
        temp.opcode = "BEQ";
    }
    else if(g4.find("BNE") != string::npos)
    {
        tokens = removeSubstring(g4, "BNE");
        temp.opcode = "BNE";       
    }
    else if(g4.find("BLTU") != string::npos)
    {
        tokens = removeSubstring(g4, "BLTU");
        temp.opcode = "BLTU";       
    }
    else if(g4.find("BLT") != string::npos)
    {
        tokens = removeSubstring(g4, "BLT");
        temp.opcode = "BLT";       
    }
    else if(g4.find("BGEU") != string::npos)
    {
        tokens = removeSubstring(g4, "BGEU");
        temp.opcode = "BGEU";       
    }

    else 
    {
        tokens = removeSubstring(g4, "BGE");
        temp.opcode = "BGE";       
    }
    temp.r1=stoi(tokens[0].substr(1));
    temp.r2=stoi(tokens[1].substr(1));
    temp.immidiate=stoi(tokens[2]);
    program.push_back(temp); 
}

void parseGroup5(string g5) //SB - SH - SW
{
    instruction temp;
    vector<string> tokens;
    if(g5.find("SB") != string::npos)
    {
        tokens = removeSubstring(g5, "SB");
        temp.opcode = "SB";
    }
    else if(g5.find("SH") != string::npos)
    {
        tokens = removeSubstring(g5, "SH");
        temp.opcode = "SH";       
    }
    else 
    {
        tokens = removeSubstring(g5, "SW");
        temp.opcode = "SW";       
    }
    temp.r2 = stoi(tokens[0].substr(1));
    size_t pos = tokens[1].find('(');
    size_t pos2= tokens[1].find(')');
    temp.immidiate = stoi(tokens[1].substr(0,pos));
    temp.r1 = stoi(tokens[1].substr(pos+2,pos2));
    program.push_back(temp);  
}

void parseGroup6(string g6) //ADD - SUB - SLL - SLT - SLTU - XOR - SRL - SRA - OR - AND 
{
    instruction temp;
    vector<string> tokens;
    if(g6.find("ADD") != string::npos)
    {
        tokens = removeSubstring(g6, "ADD");
        temp.opcode = "ADD";
    }
    else if(g6.find("SUB") != string::npos)
    {
        tokens = removeSubstring(g6, "SUB");
        temp.opcode = "SUB";       
    }
    else if(g6.find("SLL") != string::npos)
    {
        tokens = removeSubstring(g6, "SLL");
        temp.opcode = "SLL";       
    }
    else if(g6.find("SLTU") != string::npos)
    {
        tokens = removeSubstring(g6, "SLTU");
        temp.opcode = "SLTU";       
    }
    else if(g6.find("SLT") != string::npos)
    {
        tokens = removeSubstring(g6, "SLT");
        temp.opcode = "SLT";       
    }
    else if(g6.find("XOR") != string::npos)
    {
        tokens = removeSubstring(g6, "XOR");
        temp.opcode = "XOR";       
    }
    else if(g6.find("SRL") != string::npos)
    {
        tokens = removeSubstring(g6, "SRL");
        temp.opcode = "SRL";       
    }
    else if(g6.find("SRA") != string::npos)
    {
        tokens = removeSubstring(g6, "SRA");
        temp.opcode = "SRA";       
    }
    else if(g6.find("OR") != string::npos)
    {
        tokens = removeSubstring(g6, "OR");
        temp.opcode = "OR";       
    }
    else 
    {
        tokens = removeSubstring(g6, "AND");
        temp.opcode = "AND";       
    }
    temp.rd=stoi(tokens[0].substr(1));
    temp.r1=stoi(tokens[1].substr(1));
    temp.r2=stoi(tokens[2].substr(1));
    program.push_back(temp); 
} 

void parseGroup7(string g7) //FENCE - ECALL - EBREAK
{
    instruction temp;
    temp.opcode="FENCE";
    program.push_back(temp);
}

using FunctionPointer = void (*)(string);
unordered_map<string, FunctionPointer> parseFunctions=
{
    {"LUI", &parseGroup1},
    {"AUIPC", &parseGroup1},
    {"JAL", &parseJAL},
    {"JALR", &parseGroup2},
    {"ADDI", &parseGroup2},
    {"SLTI", &parseGroup2},
    {"SLTIU", &parseGroup2},
    {"XORI", &parseGroup2},
    {"ORI", &parseGroup2},
    {"ANDI", &parseGroup2},
    {"SLLI", &parseGroup2},
    {"SRLI", &parseGroup2},
    {"SRAI", &parseGroup2},
    {"LB", &parseGroup3},
    {"LH", &parseGroup3},
    {"LW", &parseGroup3},
    {"LBU", &parseGroup3},
    {"LHU", &parseGroup3},
    {"BEQ", &parseGroup4},
    {"BNE", &parseGroup4},
    {"BLT", &parseGroup4},
    {"BGE", &parseGroup4},
    {"BLTU", &parseGroup4},
    {"BGEU", &parseGroup4},
    {"SB", &parseGroup5},
    {"SH", &parseGroup5},
    {"SW", &parseGroup5},
    {"ADD", &parseGroup6},
    {"SUB", &parseGroup6},
    {"SLL", &parseGroup6},
    {"SLT", &parseGroup6},
    {"SLTU", &parseGroup6},
    {"XOR", &parseGroup6},
    {"SRL", &parseGroup6},
    {"SRA", &parseGroup6},
    {"OR", &parseGroup6},
    {"AND", &parseGroup6},
    {"FENCE", &parseGroup7},
    {"ECALL", &parseGroup7},
    {"EBREAK", &parseGroup7}
};

void parse(string inst)
{
    size_t space = inst.find(' ');
    string temp = inst.substr(0,space);
    FunctionPointer func = parseFunctions[temp];
    func(inst);
}

void extractCode()
{
    fstream file;
    file.open("program.txt");
    string temp;
    if(file.is_open())
    {
        while(getline(file, temp))
        {
            parse(temp);
        }
    }
    else
    {
        cout << "Error loading program, terminating" << endl;
        exit(0);
    }
}

// int main()
// {
//     extractCode();
//     for(auto i: program)
//     {
//         cout << i.opcode << '\t' << i.rd << '\t' << i.immidiate << '\t' << i.r1 << '\t' << i.r2 << endl; 
//     }
// }