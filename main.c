#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "client_functions.h"
#include <curl/curl.h>
#include "libcurl.h"


int main(){
    CURL *curl;
    CURLcode res;
    FILE *fp;

    fp=fopen("curlGET.txt","w");

    curl_global_init(CURL_GLOBAL_DEFAULT); //initialising global libcurl environment

    char User_name[40]; //Alloctes space for 19 charanters + '\0'
    printf("Github Activity : ");
    if(fgets(User_name,sizeof(User_name),stdin)!=NULL){
        User_name[strcspn(User_name,"\r\n")]='\0';

        Str_Mod_Space(User_name);
        User_name_check(User_name);
    }


    curl_global_cleanup();
    fclose(fp);
    return 0;
}