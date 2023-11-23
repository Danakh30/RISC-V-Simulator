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
using FunctionPointer = void (*)(string);
unordered_map<string, FunctionPointer> parseFunctions;

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

void parseLUI(string LUI)
{
    instruction temp;
    vector<string> tokens = removeSubstring(LUI, "LUI");
    temp.opcode = "LUI";
    temp.rd=stoi(tokens[0].substr(1));
    temp.immidiate=stoi(tokens[1]);
    program.push_back(temp);
}

void parseAUIPC(string AUIPC)
{
    instruction temp;
    vector<string> tokens = removeSubstring(AUIPC, "AUIPC");
    temp.opcode = "AUIPC";
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

void parseJALR(string JALR)
{
    instruction temp;
    vector<string> tokens = removeSubstring(JALR, "JALR");
    temp.opcode = "JALR";
    temp.rd=stoi(tokens[0].substr(1));
    temp.r1=stoi(tokens[1].substr(1));
    temp.immidiate=stoi(tokens[2]);
    program.push_back(temp);
}

void parseBEQ(string BEQ)
{
    instruction temp;
    vector<string> tokens = removeSubstring(BEQ, "BEQ");
    temp.opcode = "BEQ";
    temp.r1=stoi(tokens[0].substr(1));
    temp.r2=stoi(tokens[1].substr(1));
    temp.immidiate=stoi(tokens[2]);
    program.push_back(temp); 
}

void parseBNE(string BNE)
{
    instruction temp;
    vector<string> tokens = removeSubstring(BNE, "BNE");
    temp.opcode = "BNE";
    temp.r1=stoi(tokens[0].substr(1));
    temp.r2=stoi(tokens[1].substr(1));
    temp.immidiate=stoi(tokens[2]);
    program.push_back(temp); 
}

void parseBLT(string BLT)
{
    instruction temp;
    vector<string> tokens = removeSubstring(BLT, "BLT");
    temp.opcode = "BLT";
    temp.r1=stoi(tokens[0].substr(1));
    temp.r2=stoi(tokens[1].substr(1));
    temp.immidiate=stoi(tokens[2]);
    program.push_back(temp); 
}

void parseBGE(string BGE)
{
    instruction temp;
    vector<string> tokens = removeSubstring(BGE, "BGE");
    temp.opcode = "BGE";
    temp.r1=stoi(tokens[0].substr(1));
    temp.r2=stoi(tokens[1].substr(1));
    temp.immidiate=stoi(tokens[2]);
    program.push_back(temp); 
}

void parseBLTU(string BLTU)
{
    instruction temp;
    vector<string> tokens = removeSubstring(BLTU, "BLTU");
    temp.opcode = "BLTU";
    temp.r1=stoi(tokens[0].substr(1));
    temp.r2=stoi(tokens[1].substr(1));
    temp.immidiate=stoi(tokens[2]);
    program.push_back(temp);   
}

void parseBGEU(string BGEU)
{
    instruction temp;
    vector<string> tokens = removeSubstring(BGEU, "BGEU");
    temp.opcode = "BGEU";
    temp.r1=stoi(tokens[0].substr(1));
    temp.r2=stoi(tokens[1].substr(1));
    temp.immidiate=stoi(tokens[2]);
    program.push_back(temp);   
}

void parseLB(string LB)
{
    instruction temp;
    vector<string> tokens = removeSubstring(LB, "LB");
    temp.opcode = "LB";
    temp.rd = stoi(tokens[0].substr(1));
    size_t pos = tokens[1].find('(');
    size_t pos2= tokens[1].find(')');
    temp.immidiate = stoi(tokens[1].substr(0,pos));
    temp.r1 = stoi(tokens[1].substr(pos+2,pos2));
    program.push_back(temp);
}

void parse(string inst)
{
    size_t space = inst.find(' ');
    string temp = inst.substr(0,space);
    FunctionPointer func = parseFunctions[temp];
    func(inst);
    // else if (temp == "LB"){}
    // else if (temp == "LH"){}
    // else if (temp == "LW"){}
    // else if (temp == "LBU"){}
    // else if (temp == "LHU"){}
    // else if (temp == "SB"){}
    // else if (temp == "SH"){}
    // else if (temp == "SW"){}
    // else if (temp == "ADDI"){}
    // else if (temp == "SLTI"){}
    // else if (temp == "SLTIU"){}
    // else if (temp == "XORI"){}
    // else if (temp == "ORI"){}
    // else if (temp == "BLT"){}
}

void extractCode()
{
    fstream file;
    //file.open("program.txt");
    string temp;
    if(file.is_open())
    {
        while(getline(file, temp))
        {

        }
    }
}



int main()
{
    parseFunctions["LB"] = &parseLB;
    parse("LB x10, 10(x5)");
    for(auto i: program)
    {
        cout << i.opcode << '\n' << i.rd << '\n' << i.immidiate << '\n' << i.r1 << '\n' << i.r2 << endl; 
    }
}