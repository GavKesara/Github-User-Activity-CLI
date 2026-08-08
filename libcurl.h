#include <stdio.h>
#include <curl/curl.h>

void libcurl_GET(CURL *curl,CURLcode res,FILE* fp,char* username){
    
    curl=curl_easy_init(); //initialize a curl easy handle

    curl_easy_setopt(curl,CURLOPT_URL,"[https://api.github.com/users/](https://api.github.com/users/){username}/events");

    curl_easy_setopt(curl,CURLOPT_HTTPHEADER,"User-Agent: MyGitHubCLITool/1.0");
    
    curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1L); //Follow HTTP redirects if needed

    curl_easy_setopt(curl,CURLOPT_TIMEOUT,10L); //prevents CLI from waiting indefinitly.

    curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp); //writes outout data into fp

    res=curl_easy_perform(curl); //perform the GET request. res will return the code
    
    if(res!=CURLE_OK){
        fprintf(stderr,"curl_easy_perform() failed with error code : %s\n",curl_easy_strerr(res));
    }else{
        long response_code;
        curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,&response_code);
        printf("\nHTTP Response Code: %ld\n",response_code);
    }

    curl_easy_cleanup(curl);
}