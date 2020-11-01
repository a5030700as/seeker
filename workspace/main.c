#include <stdio.h>
#include <unistd.h>

#include <curl/curl.h>


/*
    了解一下 其他命令吧
    wget去下载文件
    ./main www.sina.com
    了解 curl这个API 怎么使用吧 
*/
int main(int argc, char *argv[])
{
    printf("hello curl \n");
    printf("%s\n",curl_version());

    CURL *curl;
    curl = curl_easy_init();        //初始化一个CURL类型的指针
    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);  
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return 0;
}
