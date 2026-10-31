#include <iostream>
#include <fstream>
#include <string>
#include "cppjson/json.hpp"
using namespace std;

// void printJson(string path)
// {
//     ifstream file(_PATH, ios::binary | ios::in);
//     if(!file)
//     {
//         cout << "Path " << path << " doesn't exist" << endl;
//         return;
//     }
//     string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
//     cout << content << endl;
// }

const string _PATH = "G:/Documents/Programs/cppDemos/cppjson/package.json";

int main()
{
    cppjson::Object package = cppjson::parse(_PATH);
    for(auto [key, val] : package["optionalDependencies"].to_object())
        cout << key << ": " << val << endl;

    return 0;
}