#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
fstream file;
int main()
{
    string a="a";
    int x;
    x=EOF;
    cout<<x<<endl;
    file.open("b.dq",ios::in);
    while (file)
    {
        getline(file,a);
        cout<<a<<endl;
        if (!file) cout<<"true"<<endl;
        a="eof";
    }
    file.close();
}
