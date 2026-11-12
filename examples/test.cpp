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

const string _PATH = "G:/Documents/Programs/cppDemos/cppjson/write_test.json";

int main()
{
    cppjson::Object package = cppjson::parse(_PATH);
    cppjson::Object pcl = package["PCL"];
    pcl.erase("type");
    pcl.insert("hello", "world");
    cout << pcl << endl;
    // for(auto [key, val] : package["optionalDependencies"].to_object())
    //     cout << key << ": " << val << endl;
    cppjson::dump(_PATH, pcl);


    return 0;
}