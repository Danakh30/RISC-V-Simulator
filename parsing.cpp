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

void parse(string inst)
{
    size_t space = inst.find(' ');
    string temp = inst.substr(0,space);
    FunctionPointer func = parseFunctions[temp];
    func(inst);
    // if(temp == "LUI"){}
    // else if (temp == "AUIPC"){}
    // else if (temp == "JAL"){}
    // else if (temp == "JALR"){}
    // else if (temp == "BEQ"){}
    // else if (temp == "BNE"){}
    // else if (temp == "BLT"){}
    // else if (temp == "BGE"){}
    // else if (temp == "BLTU"){}
    // else if (temp == "BGEU"){}
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
    parseFunctions["LUI"] = &parseLUI;
    parse("LUI x10, 10");
    for(auto i: program)
    {
        cout << i.opcode << '\n' << i.rd << '\n' << i.immidiate << '\n' << i.r1 << '\n' << i.r2 << endl; 
    }
}