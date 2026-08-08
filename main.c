#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "client_functions.h"
#include <curl/curl.h>
#include "libcurl.h"
#include <cjson/cJSON.h>

int main(){

    char User_name[40]; //Alloctes space for 19 charanters + '\0'
    printf("Github Activity : ");
    if(fgets(User_name,sizeof(User_name),stdin)!=NULL){
        User_name[strcspn(User_name,"\r\n")]='\0';

        Str_Mod_Space(User_name);
        User_name_check(User_name);
    }
    libcurl_GET(User_name);

    return 0;
}