#include <algorithm>
#include <random>
#include <iostream>
#include <vector>

using namespace std;
#define RANK2USER 3
#define RANK3USER 4
#define MAXFILE 2

struct file
{                        //单个文件
    int user;            //用户
    int fileName;        //文件名
    int proctectCode[4]; //保护码，前三位第一级访问限制，中间三位第二级，最后三位第三级
    file(int user, int fileName, int *proctectCode)
    {
        this->user = user;
        this->fileName = fileName;
        for (int i = 0; i < 9; i++)
        {
            this->proctectCode[i] = proctectCode[i];
        }
    }
};
struct rank3
{                           //运行文件目录
    int user;               //用户
    vector<file> rank3file; //文件
    rank3()
    {
        ;
    }
};
struct rank2
{                           //用户文件目录
    int user;               //用户，十位数
    vector<file> rank2file; //文件
    vector<rank3> rank3class;
    rank2()
    {
        ;
    }
};
struct rank1
{                           //主文件目录结构体
    int user;               //用户，个位数
    vector<file> rank1file; //文件
    vector<rank2> rank2class;
    rank1()
    {
        ;
    }
};

rank1 headmaster;
int filenum = 1;

void front() //初始化
{
    //第一级文件初始化
    int i;
    for (i = 0; i < 1 * MAXFILE; i++)
    {
        int pc[4];
        for (int j = 0; j < 2; j++)
            pc[j] =  rand() % 2;
        for (int j = 2; j < 4; j++)
            pc[j] = rand() % 2;
        file newFile(1, filenum, pc);
        headmaster.rank1file.push_back(newFile);
        filenum++;
    }
    headmaster.user = 1;
    //第二级文件初始化
    int k;
    for (k = 0; k < RANK2USER; k++)
    {
        rank2 newrank;
        headmaster.rank2class.push_back(newrank);
        headmaster.rank2class[k].user = (k + 1) * 10;
        for (i = 0; i < 1 * MAXFILE; i++)
        {
            int pc[4];
            for (int j = 0; j < 2; j++)
                pc[j] =  rand() % 2;
            for (int j = 2; j < 4; j++)
                pc[j] = rand() % 2;
            file newFile((k + 1) * 10, filenum, pc);
            headmaster.rank2class[k].rank2file.push_back(newFile);
            filenum++;
        }
    }
    int p;
    for (p = 0; p < RANK2USER; p++)
    {

        for (k = 0; k < RANK3USER; k++)
        {
            rank3 newrank;
            headmaster.rank2class[p].rank3class.push_back(newrank);
            headmaster.rank2class[p].rank3class[k].user = (p + 1) * 100 + k;
            for (i = 0; i < 1 * MAXFILE; i++)
            {
                int pc[4];
                for (int j = 0; j < 2; j++)
                    pc[j] =  rand() % 2;
                for (int j = 2; j < 4; j++)
                    pc[j] = rand() % 2;
                file newFile((p + 1) * 100 + k, filenum, pc);
                headmaster.rank2class[p].rank3class[k].rank3file.push_back(newFile);
                filenum++;
            }
        }
    }
    cout << " ";
}
int find(int filename)
{
    int i, j, k;
    for (k = 0; k < MAXFILE; k++)
    {
        if (headmaster.rank1file[k].fileName == filename)
        {
            cout << headmaster.rank1file[k].fileName << " " << headmaster.rank1file[k].user << " ";
            for (int j = 0; j < 4; j++)
                cout << headmaster.rank1file[k].proctectCode[j];
            cout << endl;
            return headmaster.user;
        }
    }
    for (i = 0; i < RANK2USER; i++)
    {
        for (k = 0; k < MAXFILE; k++)
        {
            if (headmaster.rank2class[i].rank2file[k].fileName == filename)
            {
                cout << headmaster.rank2class[i].rank2file[k].fileName << " " << headmaster.rank2class[i].rank2file[k].user << " ";
                for (int j = 0; j < 4; j++)
                    cout << headmaster.rank2class[i].rank2file[k].proctectCode[j];
                cout << endl;
                return headmaster.rank2class[i].user;
            }
        }
    }
    for (i = 0; i < RANK2USER; i++)
    {
        for (j = 0; j < RANK3USER; j++)
        {
            for (k = 0; k < MAXFILE; k++)
            {
                if (headmaster.rank2class[i].rank3class[j].rank3file[k].fileName == filename)
                {
                    cout << headmaster.rank2class[i].rank3class[j].rank3file[k].fileName << " " << headmaster.rank2class[i].rank3class[j].rank3file[k].user << " ";
                    for (int j = 0; j < 4; j++)
                        cout << headmaster.rank2class[i].rank3class[j].rank3file[k].proctectCode[j];
                    cout << endl;
                    return headmaster.rank2class[i].rank3class[j].rank3file[k].user;
                }
            }
        }
    }
}
void printUser() //打印用户及文件
{
    cout << "Users' names represent as number: 1 for headmaster, 10 or 20 for sec class, 100 or 101 for third class from 10. Inside () are files of this department." << endl;
    cout << headmaster.user << "( ";
    for (int k = 0; k < MAXFILE; k++)
    {
        cout << headmaster.rank1file[k].fileName << " ";
    }
    cout << ") " << endl;
    int i;
    for (i = 0; i < RANK2USER - 1; i++)
    {
        cout << headmaster.rank2class[i].user << " -( ";
        for (int k = 0; k < MAXFILE; k++)
        {
            cout << headmaster.rank2class[i].rank2file[k].fileName << " ";
        }
        cout << ") ";
    }
    cout << headmaster.rank2class[i].user << "( ";
    for (int k = 0; k < MAXFILE; k++)
    {
        cout << headmaster.rank2class[i].rank2file[k].fileName << " ";
    }
    cout << ") " << endl;

    int j;
    for (j = 0; j < RANK2USER; j++)
    {
        for (i = 0; i < RANK3USER - 1; i++)
        {
            cout << headmaster.rank2class[j].rank3class[i].user << " -( ";
            for (int k = 0; k < MAXFILE; k++)
            {
                cout << headmaster.rank2class[j].rank3class[i].rank3file[k].fileName << " ";
            }
            cout << ") ";
        }
        cout << headmaster.rank2class[j].rank3class[i].user << "( ";
        for (int k = 0; k < MAXFILE; k++)
        {
            cout << headmaster.rank2class[j].rank3class[i].rank3file[k].fileName << " ";
        }
        cout << ")  ";
    }
    cout << endl;
}
void visit(int myUser)
{
    cout << "Please choose a file to visit: ";
    int myFile;
    cin >> myFile;
    if (myUser == headmaster.user) //一级访问全体
    {
        cout << "Visit success! Fir class have highest priority." << endl;
        return;
    }
    int VUser;
    VUser = find(myFile);
    if (myUser < 100 && VUser < 100&&VUser>1) //二级同级间
    {
        cout << "Visit success! Sec visit same class." << endl;
        return;
    }
    if (myUser < 100 && VUser / 100 == myUser / 10) //二级访问下级
    {
        cout << "Visit success! Sec visit next class" << endl;
        return;
    }
    if (myUser >= 100 && VUser >= 100 && VUser / 100 == myUser / 100) //三级同级间
    {
        cout << "Visit success! Thir visit same class." << endl;
        return;
    }
    if (myUser < 100 && VUser == headmaster.user) //二层访问一层
    {
        for (int k = 0; k < MAXFILE; k++)
        {
            if (headmaster.rank1file[k].fileName == myFile)
            {
                headmaster.rank1file[k].proctectCode[0] == 1;
                cout << "Visit success! Sec visit fir & protect code permit." << endl;
                return;
            }
        }
    }
    if (myUser > 100 && VUser < 100 && VUser > 1 && myUser / 100 == VUser / 10) //三层访问二层
    {
        for (int i = 0; i < RANK2USER; i++)
        {
            if (headmaster.rank2class[i].user == VUser)
            {
                for (int k = 0; k < MAXFILE; k++)
                {
                    if (headmaster.rank2class[i].rank2file[k].fileName == myFile)
                    {
                        headmaster.rank2class[i].rank2file[k].proctectCode[2] == 1;
                        cout << "Visit success! Thir visit sec & protect code permit." << endl;
                        return;
                    }
                }
            }
        }
    }
    if(myUser>100&&VUser==headmaster.user)
    {
        for (int k = 0; k < MAXFILE; k++)
        {
            if (headmaster.rank1file[k].fileName == myFile)
            {
                headmaster.rank1file[k].proctectCode[2] == 1;
                cout << "Visit success! Thir visit fir & protect code permit." << endl;
                return;
            }
        }
    }
    cout << "Visit fail!" << endl;
    return;
}
void change(int myUser)
{
    cout << "Please choose a file to change: ";
    int myFile;
    cin >> myFile;
    if (myUser == headmaster.user) //一级访问全体
    {
        cout << "Change success! Fir class have highest priority." << endl;
        return;
    }
    int VUser;
    VUser = find(myFile);
    if (myUser < 100 && VUser < 100&&VUser>1) //二级同级间
    {
        cout << "Change success! Sec Change same class." << endl;
        return;
    }
    if (myUser < 100 && VUser / 100 == myUser / 10) //二级访问下级
    {
        cout << "Change success! Sec Change next class" << endl;
        return;
    }
    if (myUser >= 100 && VUser >= 100 && VUser / 100 == myUser / 100) //三级同级间
    {
        cout << "Change success! Thir Change same class." << endl;
        return;
    }
    cout << "Change fail!" << endl;
    return;
}
int main()
{
    front();
    printUser();
    cout << "Please choose user: ";
    int myUser;
    cin >> myUser;
    int option;
    cout << "INPUT OPTION: (1 FOR VISIT, 2 FOR CHANGE)  ";
    while (cin >> option)
    {
        switch (option)
        {
        case 1: //添加文件
        {
            visit(myUser);
            break;
        }
        case 2:
        {
            change(myUser);
            break;
        }
        default:
        {
            cout << "OPTION USELESS!" << endl;
            break;
        }
        }
        cout << "INPUT OPTION: (1 FOR VISIT, 2 FOR CHANGE)  ";
    }
}