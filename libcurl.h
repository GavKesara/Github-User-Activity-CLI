#include <stdio.h>
#include <curl/curl.h>
#include "json_functions.h"

int libcurl_GET(char* username){

    CURL *curl;
    CURLcode res;

    struct MemoryChunk chunk;
    chunk.memory=malloc(1);
    chunk.size=0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    curl=curl_easy_init(); //initialize a curl easy handle

    char url[256];
    snprintf(url,sizeof(url),"https://api.github.com/users/%s/events/public",username);

    curl_easy_setopt(curl,CURLOPT_URL,url);

    struct curl_slist *headers = NULL;
    headers=curl_slist_append(headers,"User-Agent: MyGitHubCLITool/1.0");
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
    
    curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1L); //Follow HTTP redirects if needed

    curl_easy_setopt(curl,CURLOPT_TIMEOUT,10L); //prevents CLI from waiting indefinitly.

    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteMemoryCallBack); //writes outout data into function

    curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void*)&chunk); //writes data into memorychunk which resizes depending on packets

    res=curl_easy_perform(curl); //perform the GET request. res will return the code
    
    if(res!=CURLE_OK){
        fprintf(stderr,"curl_easy_perform() failed with error code : %s\n",curl_easy_strerror(res));
    }else{
        long response_code;
        curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,&response_code);
        printf("\nHTTP Response Code: %ld\n",response_code);
        if(response_code==200){
            cJSON *json = JSON_data(chunk,username);
            cJSON_Delete(json);
        }else if(response_code==404){
            printf("\nError 404 Username not found.\n");
            return -1;
        }
    }

    curl_slist_free_all(headers); //frees header
    curl_easy_cleanup(curl);

    curl_global_cleanup();
    free(chunk.memory); //frees memory
    return 0;
}