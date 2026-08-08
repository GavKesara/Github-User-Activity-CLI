#include <stdio.h>
#include <string.h>
#include <ctype.h>

void Str_Mod_Space(char* name){
    for(int i=0;name[i]!='\0';i++){
        if(name[i]==' '){
            name[i]='-';
        }
    }
}

int check(char C){
    char lower_c=tolower(C);
    if((lower_c>='a'&& lower_c<='z') || (lower_c>='0'&&lower_c<='9')||(lower_c=='-')){
        return 0;
    }
    return 1;
}

void User_name_check(char* name){
    for(int i=0;name[i]!='\0';i++){
        if(name[0]=='-'){
            printf("Error! Cannot contain - in beginning.");
            break;
        }

        if(check(name[i])){
            printf("Error! Check Username Rules");
            break;
        }
    }
}