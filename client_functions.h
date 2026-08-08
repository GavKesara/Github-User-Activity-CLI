#include <stdio.h>
#include <stdlib.h>
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

void User_name_check(char* name,int max_size){
    if(max_size>=40){
        printf("Error! Username should be below 40 characters.");
        exit(-1);
    }

    if(name[0]=='-'){
        printf("Error! Cannot contain - in beginning.");
        exit(-1);
    }else if(name[max_size-1]=='-'){
        printf("Error! Cannot end with - .");
        exit(-1);
    }else{
        for(int i=0;name[i]!='\0';i++){
            if(check(name[i])){
                printf("Error! Check Username Rules");
                exit(-1);
            }
            if(name[i]=='-' && name[i+1]=='-'){
                printf("Error! consecutive '-' not allowed.");
                exit(-1);
            }
        }
    }
}