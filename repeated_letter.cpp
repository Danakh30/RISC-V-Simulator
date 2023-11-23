#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;

string letter_count(string w)
{
    string temp;
    char delimiter =' ';
    istringstream iss(w);
    vector<string> tokens;
    vector<int> occurences;
    while(getline(iss, temp, delimiter))
    {
        tokens.push_back(temp);
    }
    for(auto i : tokens)
    {
        int max_occurence=0;
        unordered_map <char, int> letters;
        for(int j=0; j<i.length(); j++)
        {
            letters[i[j]] = count(i.begin(), i.end(), i[j]);
        }
        for(auto k : letters)
        {
            if(k.second > max_occurence)
            {
                max_occurence = k.second;
            }
        }
        occurences.push_back(max_occurence);
    }
    int index;
    int temp_max=0;
    for(int i=0; i<occurences.size(); i++)
    {
        if(occurences[i]>temp_max)
        {
            index=i;
            temp_max = occurences[i];
        }
    }
    return tokens[index];

}

int main()
{
    string test = "ever together";
    cout << letter_count(test) << endl;
}