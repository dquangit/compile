/*author: Pham Van Quang*/
#include "global.h"
#include "error.cpp"
#include "scanner.cpp"
#define khkt 100
#define khkkt 100

struct data
{
    string luatsinh;
};

data M_table[khkkt][khkt];
data rule[khkkt*khkt];
map <char,int> not_end_char;

void init_list_not_end_char()
{
    not_end_char['E']=1;
    not_end_char['e']=1;
    not_end_char['T']=1;
    not_end_char['t']=1;
    not_end_char['F']=1;
    not_end_char['S']=1;
    not_end_char['L']=1;
}

void assigned(char a,int b,int i)
{
    M_table[(int)a][(int)b]=rule[i];
}

void init_rule()
{
    rule[1].luatsinh="Te";
    rule[2].luatsinh="+Te";
    rule[3].luatsinh="-Te";
    rule[4].luatsinh=none;
    rule[5].luatsinh="Ft";
    rule[6].luatsinh="*Ft";
    rule[7].luatsinh="/Ft";
    rule[8].luatsinh="dFt";
    rule[9].luatsinh="mFt";
    rule[10].luatsinh=none;
    rule[11].luatsinh="i";
    rule[12].luatsinh="n";
    rule[13].luatsinh="(E)";
    rule[14].luatsinh="Lo";
    rule[15].luatsinh="E;L";
    rule[16].luatsinh=none;

    assigned('E',id,1);
    assigned('E',num,1);
    assigned('E',lpara,1);
    assigned('e',plus,2);
    assigned('e',minus,3);
    assigned('e',rpara,4);
    assigned('e',Semicolon,4);
    assigned('T',id,5);
    assigned('T',num,5);
    assigned('T',lpara,5);
    assigned('t',plus,4);
    assigned('t',minus,4);
    assigned('t',star,6);
    assigned('t',division,7);
    assigned('t',div,8);
    assigned('t',mod,9);
    assigned('t',rpara,10);
    assigned('t',Semicolon,10);
    //assigned('t',$,10);
    assigned('F',id,11);
    assigned('F',num,12);
    assigned('F',lpara,13);
    assigned('S',num,14);
    assigned('S',id,14);
    assigned('S',lpara,14);
    assigned('S',$,16);
    assigned('L',id,15);
    assigned('L',num,15);
    assigned('L',lpara,15);
    assigned('L',EOF,16);
    assigned('L',$,16);


}
int num_loop(char *filename)
{
    char x,tmp;
    int d=0;
    file.open(filename,ios::in);
    while (file)
    {
        file>>x;
        tmp=x;
        if (x==$)
        d++;
    }
    file.close();
    //cout<<tmp<<endl;
    if (tmp=='$')
    return d;
    return d+1;
}
int solve(char X)
{
    if (X=='i') return 257;
    if (X=='n') return 256;
    if (X=='d') return 259;
    if (X=='m') return 260;
    if (X=='o') return -1;
}

void emit_rule(char X,string a)
{
    switch (X)
    {
        case 'e': {cout<<"E'";break;}
        case 't': {cout<<"T'";break;}
        case 'S': {cout<<"Start";break;}
        case 'L': {cout<<"List";break;}
        default: {cout<<X;break;}
    }
    cout<<"->";
    for (int i=0;i<a.size();i++)
    switch (a[i])
    {
        case 'i': {cout<<"id";break;}
        case 'n': {cout<<"num";break;}
        case 'm': {cout<<"mod";break;}
        case 'd': {cout<<"div";break;}
        case 'e': {cout<<"E'";break;}
        case 't': {cout<<"T'";break;}
        case '#': {cout<<"null";break;}
        case 'S': {cout<<"Start";break;}
        case 'L': {cout<<"List";break;}
        case 'o': {cout<<"EOF";break;}
        default: {cout<<a[i];break;}
    }
}

void parse(char* filename)
{
    stack <char> status;
    string a;
    init_rule();
    init_typetoken_table();
    init_lexbuf();
    init_list_not_end_char();
    status.push('$');
    status.push('S');
    cout<<"Entry\tLexptr\tToken\tTypeToken\tRule";
    file.open(filename,ios::in);
    emit();
    do{
    while (status.top()=='#')
    {
        status.pop();
    }
    char X=status.top();
    if (not_end_char[X]==0)
    {
        if (solve(X)==typetoken)
        {

            if (X==36) break;
            else
            {
                status.pop();
                emit();
            }
        }
        else
        {
            //cout<<X<<" "<<typetoken<<endl;
            error("Syntax Error",lineno);
        }
    }
    else
    {
        a=M_table[(int)X][typetoken].luatsinh;
        if (a!="")
        {
            status.pop();
            if (X!='#')
            for (int i=a.size()-1;i>=0;i--)
                status.push(a[i]);
            emit_rule(X,a);
            cout<<"\t";
        }
        else
        {
            error("Syntax Error",lineno);
        }
    }
    }while (true);
    file.close();
}


int main()
{   char fname[50];
    system("clear");
    cout<<"Source path: ";cin>>fname;
    parse(fname);
    cout<<endl;
    cout<<"Compile Success"<<endl;
}
