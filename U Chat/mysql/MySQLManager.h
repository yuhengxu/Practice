/*    
* MySQLManager.h    
*    
*    Created on: 8.18, 2012   
*            Author: Terry
*/
#ifndef MYSQLMANAGER_H_    
#define MYSQLMANAGER_H_     
#include <mysql.h>
#include <string>
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
class MySQLManager    
{
public:
        MySQLManager(std::string hosts, std::string userName, std::string password, std::string dbName, unsigned int port);
        ~MySQLManager();
        void initConnection();
        bool runSQLCommand(std::string sql);
        unsigned int insert(std::string sql);
        void destroyConnection();
        bool getConnectionStatus();
        vector< vector<string> > getResult();
protected:
        void setUserName(std::string userName);
        void setHosts(std::string hosts);
        void setPassword(std::string password);
        void setDBName(std::string dbName);
        void setPort(unsigned int port);
private:
        bool IsConnected;
        vector< vector<string> > resultList;
        MYSQL mySQLClient;
        unsigned int DEFAULTPORT;
        char * HOSTS;
        char * USERNAME;
        char * PASSWORD;
        char * DBNAME;
};
#endif /* MYSQLMANAGER_H_ */