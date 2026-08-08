#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

//dynamic Buffer structure to hold HTTP response body
struct MemoryChunk{
    char *memory; //holds the address of the raw byte buffer allocated in heap
    size_t size; //total num of bytes stored in memory
};

//Callback function used by libcurl to append incoming chunks of data
static size_t WriteMemoryCallBack(void *contents, size_t size, size_t nmemb, void *userp){
    size_t realsize=size*nmemb;
    struct MemoryChunk *mem = (struct MemoryChunk*)userp;

    char *ptr = realloc(mem->memory,mem->size+realsize+1); //resized memory address to previous size + additional data + 1 byte for null terminator
    if(ptr==NULL){
        printf("Not enough memory (realloc failed)\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]),contents,realsize);
    mem->size+=realsize;
    mem->memory[mem->size]=0;

    return realsize;
}

cJSON *JSON_data(struct MemoryChunk chunk,char* username){
    cJSON *json = cJSON_Parse(chunk.memory);
    if(json!=NULL && cJSON_IsArray(json)){
        int event_count = cJSON_GetArraySize(json);
        printf("Retrived %d events for '%s':\n\n",event_count,username);
        int limit;
        //maximum events to print is 5
        if(event_count<5){
            limit=event_count;
        }else{
            limit=5;
        }
        for(int i=0;i<limit;i++){
            cJSON *event = cJSON_GetArrayItem(json,i);

            cJSON *type = cJSON_GetObjectItemCaseSensitive(event,"type");
            cJSON *created_at = cJSON_GetObjectItemCaseSensitive(event,"created at");
            cJSON *repo = cJSON_GetObjectItemCaseSensitive(event,"Repo");
            cJSON *repo_name = repo ? cJSON_GetObjectItemCaseSensitive(repo,"name") : NULL;

            printf("- [%s] %s on %s\n",
                    created_at ? created_at->valuestring : "N/A",
                    type ? type->valuestring : "UnknownEvent",
                    repo_name ? repo_name->valuestring : "UnknownRepo");
            
        }
    }
    return json;
}