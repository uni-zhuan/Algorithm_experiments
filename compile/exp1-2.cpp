#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
using namespace std;
//用于识别是基本字或标识符
void Base(string str,ofstream &outfile)
{
    //字符不区分大小写，进行转换
    string strtran = str;
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    // 识别基本字
    if (str == "begin" || str == "call" || str == "const" || str == "do" || str == "end" || str == "if"|| str == "odd"
     || str == "procedure" || str == "read" || str == "then" || str == "while" || str == "var" || str == "write")
        outfile<< "("<< str << "sym," << strtran << ")" << endl;
    else
        outfile<< "(ident," << strtran << ")" << endl;
}

bool isSign(char c)
{
    if(c!=' '&& c != '\n'&&c!='\t'&&c!=';'&&c!='+'&&c!='-'&&c!='*'&&c!='/'&&c!='='&&c!='#'&&c!='<'&&c!='>'
    &&c!=':'&&c!='('&&c!=')'&&c!=','&&c!='.')
        return false;
    else
        return true;
}

int Sign(string str, int i,ofstream &outfile)
{
    switch (str[i])
    {
    // 识别运算符
    case '+':
        outfile<< "(plus,+)" << endl;
        return i;
        break;
    case '-':
        outfile<< "(minus,-)" << endl;
        return i;
        break;
    case '*':
        outfile<< "(times,*)" << endl;
        return i;
        break;
    case '/':
        outfile<< "(slash,/)" << endl;
        return i;
        break;
    case '=':
        outfile<< "(eql,=)" << endl;
        return i;
        break;
    case '#':
        outfile<< "(neq,#)" << endl;
        return i;
        break;
    case '<':
        i++;
        if (str[i] == '=')
        {
            outfile<< "(leq,<=)" << endl;
        }
        else
        {
            i--;
            outfile<< "(lss,<)" << endl;
        }
        return i;

        break;
    case '>':
        i++;
        if (str[i] == '=')
        {
            outfile<< "(geq,>=)" << endl;
        }
        else
        {
            i--;
            outfile<< "(gtr,>)" << endl;
        }
        return i;
        break;
    case ':':
        i++;
        if (str[i] == '=')
        {
            outfile<< "(becomes,:=)" << endl;
        }
        else
        {
            outfile<< "error!";
            //错误处理
        }
        return i;

        break;
    // 识别界符
    case '(':
        outfile<< "(lparen,()" << endl;
        return i;
        break;
    case ')':
        outfile<< "(rparen,))" << endl;
        return i;
        break;
    case ',':
        outfile<< "(comma,,)" << endl;
        return i;
        break;
    case ';':
        outfile<< "(semicolon,;)" << endl;
        return i;
        break;
    case '.':
        outfile<< "(period,.)" << endl;
        return i;
        break;

    // 非法字符错误处理
    default:
        outfile<< "(error,";
        while (!isSign(str[i]))
        {
            outfile << str[i];
            i++;
        }
        i--;
        outfile << ")" << endl;
        return i;
        //错误处理
        break;
    }
}



int main()
{

    ifstream input_file("in.txt");
    string outstr;
    string single_line, str,str1;
    while (getline(input_file, single_line))
    {
        //读入代码
        // str1 = str1 + ' ' + single_line;
        str = str + ' ' + single_line;
    }
    input_file.close();
    // str=str1;
    ofstream outfile("out.txt");
    //开始处理读入的代码
    int length_str = str.length();

    for (int i = 0; i < length_str; i++)
    {

        if (str[i] == ' ' || str[i] == '\n'||str[i]=='\t') //当遇到空格或换行时，跳过继续执行
            continue;
        //识别常数
        else if (isdigit(str[i]))
        {
            string digit;
            while (isdigit(str[i]))
            {
                digit += str[i];
                i++;
            }
            if(str[i]=='.'||!isSign(str[i]))
            {
                while (str[i]=='.'||!isSign(str[i]))
                {
                    digit += str[i];
                    i++;
                }
                outfile<<"(error,"<< digit << ")\n" ;
            }
            else
                outfile<< "(number," << digit << ")\n" ;
            i--;
        }

        // 识别基本字/标识符
        else if (isalpha(str[i]))
        {

            //字母
            string base;
            while (isdigit(str[i]) || isalpha(str[i]))
            {
                base += str[i];
                i++;
            }
            i--;
            Base(base,outfile);
        }
        // odd运算符按基本字处理
        else
        {
            i = Sign(str, i,outfile);
        }
        // outfile<<i<<endl;
    }
    outfile.close();
    //return 0;
}

