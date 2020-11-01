#include <stdio.h>
#include <unistd.h>

extern char *optarg;
extern int optind, opterr, optopt;

/*
    验证代码:
    输入命令
    ./main aa bb cc dd -abc ww
    结论：
    1 会对命令行重新排序
    2 如果必须带参数的没有带参数 会自动报错
    3 可选参数项不能使用 空格分隔符去分割 因为可选项 和 参数公用一个 字段了
    。。。。
    以上 
    等待遍历完参数之后 后面就是 命令的参数了
    
*/
int main(int argc, char *argv[])
{
    printf("参数个数为: %d \n", argc);
    for (int i = 0; i < argc; i++)
        printf(" %s ", argv[i]);
    
    printf("\n下面验证getopt函数对参数重排之后的结果\n\n");
    
    //getopt(argc, argv, "abc:de::");
    char ret = -1;
    while ((ret = getopt(argc, argv, "abc:de::")) > 0)
    {
        switch (ret)
        {
            case 'a':
                printf("假装执行a选项\n");
                break;
            case 'b':
                printf("假装执行b选项\n");
                break;
            case 'c':
                printf("假装执行c选项\n");
                break;
            case 'd':
                printf("假装执行d选项\n");
                break;
            case 'e':
                printf("假装执行e选项\n");
                break;
            case '?':
                printf("输入选项不对\n");
                break;
        }
        
    }

    printf("\ngetopt 选项结束咯\n可以开始输出命令参数试试看了\n");
    for (int i = 0; i < argc; i++)
        printf(" %s ", argv[i]);
    printf("\n");
    while (optind < argc)
    {   
        printf(" %s ", argv[optind]);
        usleep(20 * 1000);
        optind++;
    }
    return 0;
}
