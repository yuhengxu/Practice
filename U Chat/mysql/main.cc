#include "MySQLManager.h"
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    MySQLManager *mysql = new MySQLManager("127.0.0.1", "root", "xufeiyang", "mytest", (unsigned int)3306);
    mysql->initConnection();
    if(mysql->getConnectionStatus())
    {
        if(mysql->runSQLCommand("select * from student"))
        {
            vector<vector<std::string> > result = mysql->getResult();
            for(auto & vec : result)
            {
                for(auto &str : vec)
                {cout << str.c_str() << " ";}
                    cout << endl;
            }
        }
        else
        cout << "执行失败" << endl;
    }
    else
    cout << "连接未建立" << endl;
    return 0;
}
