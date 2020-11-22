#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sqlite3.h>

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
