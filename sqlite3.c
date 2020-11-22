#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sqlite3.h>
/*


sqlite3
使用 .命令前缀
数据库操作:
	
	首先，你需要建立一个目录 然后再 建立一个 表 然后再 插入内容 
	.open test.bd  创建一个数据库
	sqlite> create table student(id int, name varchar(20), age int); 记得 带分号 
	sqlite> insert into student values(1, "snail", 25);				记得带分号  \" 记得转义啊 

	sqlite> .tables 查询当前数据库有什么 表
	
	select * from student;
	select * from table_name ;
	
	sqlite> .databases  查询当前有什么数据库 
	seq  name             file                                                      
	---  ---------------  ----------------------------------------------------------
	0    main             /home/snail/vs_code/sqlite3_study/test.db 
	
	
	原来会被解析为数据库的这几种类型:
	int ---> INTEGER
	varchar ----> TEXT
	BLOB ----> BLOB
	FLOAT ---> REAL
	NUMERIC ----> NUMERIC
	
	现在看看
	(id int , name varchar(20), blob isTrue, float length);
	
	===============================================================
	可以 去 debian.org去查询 根据 头文件 安装指定的 数据包 就行了
	
	=================================================================
	int sqlite3_open(
  const char *filename,   /* Database filename (UTF-8) */
  sqlite3 **ppDb          /* OUT: SQLite db handle */
);


	==================================================================
	
	create table if no exists student 
	
	查询的时候 可能需要回调函数 而已
	
	=====================================================================
	int sqlite3_exec(
  sqlite3*,                                  /* An open database */
  const char *sql,                           /* SQL to be evaluated */
  int (*callback)(void*,int,char**,char**),  /* Callback function */
  void *,                                    /* 1st argument to callback */
  char **errmsg                              /* Error msg written here */
);

	sqlite3_exec(sqlite3*, const char *sql, int (*callback)(void*,int,char**,char**),void *, char **errmsg);
	==========================
	drop table if exists [tableName];
	CREATE TABLE IF NOT EXISTS [tableName] SELECT...
	=========================================================
	

*/
/*
    第一步创建一个 数据库文件 

    	sqlite3_exec(sqlite3*, const char *sql, int (*callback)(void*,int,char**,char**),void *, char **errmsg);
*/
sqlite3 *ppDb = NULL;

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i = 0; i < argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;    
}

int main(void)
{
    printf("hello !\n");
    int ret = 0;
    ret = sqlite3_open("company.bd", &ppDb);

    //char err_buff[200] = {0};
    char cmd_buff[256];
    char *p_err = NULL;

    if (ret != SQLITE_OK )
        printf("error line %d !!! %s \n", __LINE__, sqlite3_errmsg(ppDb));

    memset(cmd_buff, 0, sizeof(cmd_buff));
    sprintf(cmd_buff, "create table if not exists student(id int, name varchar(20), age int);");

    ret = sqlite3_exec(ppDb, cmd_buff, NULL, NULL, &p_err);
    if (ret != SQLITE_OK)
    {
        if (p_err != NULL)
            printf(" %s \n", p_err);
    }
/*    
    int id, age;
    char name[20];

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        printf("请输入id 名称: 以及 年龄: \n");
        scanf(" %d %s %d", &id, name, &age);
        sprintf(cmd_buff, "insert into student values(%d,\"%s\",%d);", id, name, age);
        ret = sqlite3_exec(ppDb, cmd_buff, NULL, NULL, &p_err);
        if (ret != SQLITE_OK)
        {
            if (p_err != NULL)
                printf(" %s \n", p_err);
        }
    }
    printf("done \n");
*/
/*
    其实 就 是 传 入 key = value 以及有多少个 对于当前的 记录而言
    static int callback(void *NotUsed, int argc, char **argv, char **azColName)
    也可以了解一下 关于 get table 的返回参数 是 一维数组的问题
    数组的维度 不影响 数组在内存里面的 线性排列的特点！！！！
*/
    sprintf(cmd_buff, "select * from student;");
    ret = sqlite3_exec(ppDb, cmd_buff, callback, NULL, &p_err);
    if (ret != SQLITE_OK)
    {
        if (p_err != NULL)
            printf(" %s \n", p_err);
    }
    return 0;
}
