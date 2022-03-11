#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
//用于识别是基本字或标识符
void Base(string str)
{
    //字符不区分大小写，进行转换
    string strtran=str;
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    // 识别基本字
    if (str == "begin")
        cout << "(beginsym," << strtran << ")" << endl;
    else if (str == "call")
        cout << "(callsym," << strtran << ")"<< endl;
    else if (str == "const")
        cout << "(constsym," << strtran << ")"<< endl;
    else if (str == "do")
        cout << "(dosym," << strtran << ")"<< endl;
    else if (str == "end")
        cout << "(endsym," << strtran << ")" << endl;
    else if (str == "if")
        cout << "(ifsym," << strtran << ")" << endl;
    else if (str == "odd")
        cout << "(oddsym," << strtran << ")" << endl;
    else if (str == "procedure")
        cout << "(proceduresym," << strtran << ")" << endl;
    else if (str == "read")
        cout << "(readsym," << strtran << ")" << endl;
    else if (str == "then")
        cout << "(thensym," << strtran << ")"<< endl;
    else if (str == "while")
        cout << "(whilesym," << strtran << ")" << endl;
    else if (str == "var")
        cout << "(varsym," << strtran << ")"<< endl;
    else if (str == "write")
        cout << "(writesym," << strtran << ")" << endl;
    else
        cout << "(ident," << strtran << ")" << endl;
}
int Sign(string str, int i)
{
    switch (str[i])
    {
    // 识别运算符
    case '+':
        cout << "(plus,+)" << endl;
        return i;
        break;
    case '-':
        cout << "(minus,-)" << endl;
        return i;
        break;
    case '*':
        cout << "(times,*)" << endl;
        return i;
        break;
    case '/':
        cout << "(slash,/)" << endl;
        return i;

        break;
    case '=':
        cout << "(eql,=)" << endl;
        return i;
        break;
    case '<':
        i++;
        if (str[i] == '>')
        {
            cout << "(neq,<>)" << endl;
        }
        else if (str[i] == '=')
        {
            cout << "(leq,<=)" << endl;
        }
        else
        {
            i--;
            cout << "(lss,<)" << endl;
        }
        return i;

        break;
    case '>':
        i++;
        if (str[i] == '=')
        {
            cout << "(geq,>=)" << endl;
        }
        else
        {
            i--;
            cout << "(gtr,>)" << endl;
        }
        return i;
        break;
    case ':':
        i++;
        if (str[i] == '=')
        {

            cout << "(becomes,:=)" << endl;
        }
        else
        {
            cout << "error!";
            //错误处理
        }
        return i;

        break;
    // 识别界符
    case '(':
        cout << "(lparen,()" << endl;
        return i;

        break;
    case ')':
        cout << "(rparen,))" << endl;
        return i;

        break;
    case ',':
        cout << "(comma,,)" << endl;
        return i;

        break;
    case ';':
        cout << "(semicolon,;)" << endl;
        return i;

        break;
    case '.':
        cout << "(period,.)" << endl;
        return i;
        break;

    // 非法字符错误处理
    default:
        //错误处理
        break;
    }
}
int main()
{

    string str1, str;
    while (cin >> str1)
    {
        //读入代码
        str = str + ' ' + str1;
    }
    //开始处理读入的代码
    int length_str = str.length();
    for (int i = 0; i < length_str; i++)
    {

        if (str[i] == ' ' || str[i] == '\n') //当遇到空格或换行时，跳过继续执行
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
            i--;
            cout << "(number," << digit << ")" << endl;
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
            Base(base);
        }
        // odd运算符按基本字处理
        else
        {
            i = Sign(str, i);
        }
    }
    return 0;
}

// 测试用例
/*
const a=10;
var b,c;
begin
    read(b);
    c:=a+b;
    write(c);
end.
*/

/*
const a=10;
var b,c;
begin
    READ(b);
    c:=a+b;
    write(C);
end.
*/
