#include <stdio.h>
#include <mysql/mysql.h>

//字符串替换函数，在字符串 string 中查找 source， 找到则替换为destination，找不到则返回NULL
static char * replace_string (char * string, const char * source, const char * destination )
{
	char* sk = strstr (string, source);
	if (sk == NULL) return NULL;

	char* tmp;
	size_t size = strlen(string)+strlen(destination)+1;

	char* newstr = (char*)calloc (1, size);
	if (newstr == NULL) return NULL;

	char* retstr = (char*)calloc (1, size);
	if (retstr == NULL)
	{
		free (newstr);
		return NULL;
	}
	
	snprintf (newstr, size-1, "%s", string);
	sk = strstr (newstr, source);

	while (sk != NULL)
	{
		int pos = 0;
		memcpy (retstr+pos, newstr, sk - newstr);
		pos += sk - newstr;
		sk += strlen(source);
		memcpy (retstr+pos, destination, strlen(destination));
		pos += strlen(destination);
		memcpy (retstr+pos, sk, strlen(sk));

		tmp = newstr;
		newstr = retstr;
		retstr = tmp;

		memset (retstr, 0, size);
		sk = strstr (newstr, source);
	}
	free (retstr);
	return newstr;
}

MYSQL conn;

// 1 OK , 0 False
int login_select(char* username , char* passwd)//登录检查
{                        
    char* sqlcmd1 = "select passwprd from user where UID = $$";
    char* sqlcmd2;
    MYSQL_RES* res;
    //mysql_query(&conn , sqlcmd1);
    //res = mysql_store_result(&conn);
    if(res == 0)
    {
        int number = mysql_num_rows(res);
        if(!number) return 0;
        else//密码正确，读取好友信息
        {
            sqlcmd2 = replace_string("select friend from user where UID = '$$';", "$$", username);
            res=mysql_query(&conn,sqlcmd2); 
            return 1;


            /*********************
            ********接口**********
            *********************/


        }
    }
}

void registe_insert(char *username , char* passwd)
{
    char* msg1;
    char* msg2;
    MYSQL_RES* res;
    msg1 = replace_string("insert into user values('$$','&&',null,null);" , "$$" , username);
    msg2 = replace_string(msg1 , "&&" , passwd);
    res = mysql_query(&conn,msg2);

}
/*
void single_chat_insert(char* sender , char* receiver , char* msg)
{

}

char* single_chat_select(char* sender , char* receiver)
{

}

void group_chat_insert(char* GID,char* SID , char* msg)
{

}

char* group_char_select(char* GID , char* SID)
{

}
*/


int main(int argc,char *argv[])
{
    int flag;    // 服务器发送的指令代号
    int res;
    char* name = "tian";
    char* passwd = "250";
    mysql_init(&conn);
    if(mysql_real_connect(&conn,"localhost","root","8520","chat",0,NULL,CLIENT_FOUND_ROWS))
    //"root":数据库管理员 "":root密码 "test":数据库的名字
    {
        printf("connect success!\n");
        //msg = replace_string("insert into test values('$$',1)" , "$$" , input);
        //printf("%s\n" , msg);
        //res=mysql_query(&conn,msg);
        flag = 2;
        switch(flag)
        {
            case 1: login_select(name, passwd);break;
            case 2: registe_insert(name, passwd);break;
        }
        if(res)
        {
            printf("error\n");
        }
        else
        {
            printf("OK\n");
        }
        mysql_close(&conn);
    }
    else
    {
        printf("Database can not connect!!!!");
    }
    return 0;
}