/*author: Pham Van Quang*/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <stack>
#include <map>

#define bsize 512   //size of buffer
#define lpara 40    //(
#define rpara 41    //)
#define none 35     //#
#define plus 43     //+
#define num 256     //number
#define minus 45    //-
#define division 47 // /
#define star 42     // *
#define equal 61    // =
#define id 257      // id
#define done 258    // done
#define div 259
#define mod 260
#define Semicolon 59
#define strmax 999 //size of Lexemes
#define sysmax 100 //size of Symtable
#define EOS '\0'
#define space 32
#define $ 36
using namespace std;
fstream file;
char* filename;

string str;
int tokenval;   //value of token
int lineno=0;     //line number
int typetoken;
int lexptr=0;

struct entry
{
    int lexptr;     //vi tri token trong day lexemes
    int token;   //token
};
entry symtable[sysmax];
char lexbuf[2*bsize+2]; //lexbuf gom 2phan va 2 ptu EOS cam canh
char lexemes[strmax];
int lastentry=0,lastchar=0;
int p=2*bsize+1; //con tro lexbuf dang nam o tan cung ben phai cua lexbuf
string aline;
int counts=0;

map <int,string> ttoken;
void init_typetoken_table()
{
    ttoken[40]=ttoken[41]="Parenthesis";
    ttoken[257]="id";
    ttoken[256]="num";
    ttoken[42]=ttoken[43]=ttoken[45]=ttoken[47]=ttoken[259]=ttoken[260]="Operation";
    ttoken[36]="Done";
    //ttoken[35]="None";
    ttoken[59]="Semicolon";
    ttoken[-1]="EOF";
}
