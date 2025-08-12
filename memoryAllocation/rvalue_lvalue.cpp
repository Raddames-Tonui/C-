#include <iostream>

using namespace std;

// lvalue backed by memory space
// rvalue are just temporary
// && -> Takes rvalue
// & -> lvalue
void printName(string&& name) {
    cout<< name << endl;
}


int main (){
    string name1 = "Job";
    string name2 = "bockyman";
    string name3 = name1 +  name2;
        // cout << "name1: " << name1 << endl;


    printName( name1 +  name2);
    return 0;
};