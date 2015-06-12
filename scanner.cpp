/*author:  Pham Van Quang*/
bool isDigit(char t)  //kiem tra ky tu nhap co phai la so hay ko
{
        if ((int)t<=57 && (int)t >=49)
        return true;
        return false;
}

bool isLetter(char t)
{
    int x=(int)t;
    if ((x>=65)&&(x<=90)) //t thuoc [A...Z]
    return true;
    else
    if (x>=97&&x<=122)    //t thuoc [a...z]
    return true;
    return false;
}


void insert(int lexptr,int typetoken)
{
    symtable[lastentry].token=typetoken;
    symtable[lastentry].lexptr=lexptr;
    lastentry++;
}

void get_line()
{
    getline(file,aline);
    if (!file)
    aline="EOF $";
    counts=0;
}

void loadLexbuf()
{
   if (lexbuf[p]==EOS)
    {
        if (p==bsize)
        {
            for (int i=bsize+1;i<(2*bsize+2);i++)
                {
                    lexbuf[i]=aline[counts];
                    counts++;
                    if (counts>aline.size())
                    {
                        lexbuf[i]='\n';
                        get_line();
                    }
                }
            p++;
        }
        else if (p==2*bsize+1)
        {
            for (int i=0;i<bsize;i++)
                {
                    lexbuf[i]=aline[counts];
                    counts++;
                    if (counts>aline.size())
                    {
                        lexbuf[i]='\n';
                        get_line();
                    }
                }
            p=0;
        }
    }
}

void init_lexbuf()
{
    lexbuf[bsize]=lexbuf[2*bsize+1]=EOS;    //khoi tao phan tu cam canh
}


int lookup(int lexptr)
{
    char a[100];
    int d1=0;
    int i=lexptr;
    while (lexemes[i]!=EOS)
    {
        a[d1]=lexemes[i];
        d1++;
        i++;
    }
    a[d1]=EOS;
    if (strcmp(a,"div")==0) return div;
    if (strcmp(a,"mod")==0) return mod;
    if (strcmp(a,"EOF")==0) return EOF;
    return id;
}

void scanner()
{
    char t;
    loadLexbuf();
    tokenval=0;
    while (lexbuf[p]=='\t'||lexbuf[p]=='\0'||lexbuf[p]==' '||lexbuf[p]=='\n')
    {
        if(lexbuf[p]=='\n')
        {
            lineno++;
        }
        p++;
        loadLexbuf();
    }
    t=lexbuf[p];
    if (isDigit(t))
    {
        while (isDigit(t))
        {
            tokenval=tokenval*10+(int)t-48;
            lexemes[lastchar]=t;
            p++;
            lastchar++;
            loadLexbuf();
            t=lexbuf[p];
        }
        typetoken=num;
        lexemes[lastchar]=EOS;
        lastchar++;
    }
    else if (isLetter(t))
    {
        while(isLetter(t)||isDigit(t))
        {
            lexemes[lastchar]=t;
            p++;
            lastchar++;
            loadLexbuf();
            t=lexbuf[p];
        }
        lexemes[lastchar]=EOS;
        lastchar++;
        typetoken=lookup(lexptr);

    }
    else
    {
        lexemes[lastchar]=t;
        p++;
        loadLexbuf();
        lastchar++;
        lexemes[lastchar]=EOS;
        lastchar++;
        typetoken=(int)t;
    }
    insert(lexptr,typetoken);
    lexptr=lastchar;
}


void emit()
{
    cout<<endl;
    scanner();
    cout<<lastentry<<"\t"<<symtable[lastentry-1].lexptr<<"\t";
    int k=symtable[lastentry-1].lexptr;
    while (lexemes[k]!=EOS)
    {
        cout<<lexemes[k];
        k++;
    }
    cout<<"\t";
    int tmp=symtable[lastentry-1].token;
    if (ttoken[tmp]!="")
    {
        cout<<ttoken[tmp];
        if (tmp!=42&&tmp!=43&&tmp!=45&&tmp!=47&&tmp!=259&&tmp!=260&&tmp!=59&&tmp!=40&&tmp!=41)
        cout<<"\t";
    }
    else
    {
        cout<<endl;
        cout<<"Syntax error "<<endl;
        cout<<"unknown symbol: \""<<(char)tmp<<"\"";
        error("",lineno);
    }
    cout<<"\t";
}
