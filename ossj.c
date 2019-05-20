
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    UNDEFINED = 0,
    OBJECT = 1,
    ARRAY = 2,
    STRING = 3,
    PRIMITIVE = 4
} type_t;

typedef struct {
    int start;
    int end;
    int size;
}tok_t;

int getIDX(int end, int idx_str, int* idx_data, char* data, char *ptr, int* brEnd){
    int brStart = end + idx_str + 1; 
    *idx_data = end + strlen(ptr) + 1;
    ptr = strtok(NULL, "}");
    *idx_data = *idx_data + strlen(ptr) + 1;
    data[*idx_data] = '}';                  
    *brEnd = *idx_data + 1;        

    return brStart;
}

void addToken(tok_t** arr, int* num, int brStart, int brEnd, int size, int* count){
    (*arr)[*num].start = brStart;
    (*arr)[*num].end = brEnd;
    (*arr)[*num].size = size; ///dummy size 999
    (*num)++;

    if (*num >= *count)
    {
        *arr = (tok_t*)realloc(*arr, sizeof(tok_t) * (*count) * 2);
        *count *= 2;
    }
}

int main(int argc, char ** argv){
    char* fpName = argv[1];
    FILE* fpIn;
    FILE* fpOut;

    const int maxBufLen = 500;
    char buffer[maxBufLen];
    char data[maxBufLen];

    fpIn = fopen(fpName, "r");
    if(fpIn == NULL)
        printf("reading error\n");
    fpOut = fopen("test.json", "w");
    if(fpOut == NULL)
        printf("writing error\n");
 

//using strtok. But seems like required to have index in integer.
//shoud use the character loop.
    
    int len = 0;
    while (fgets(buffer, maxBufLen, fpIn) != NULL)
    {
        sprintf(data+len,"%s",buffer);
        len += strlen(buffer);
    }
    int index = 0;
    char* ptr = strtok(data,"\"");  //until the start of the name
    index = strlen(ptr) ;   //2까지. 따옴표까지 넣어준다. 

//index consideration: start, comma, end
/**
 * 
 * abcd"efg"h:{ij"kl"},"mn"abc"nn"def",...
 * 012345678901234567890123456789
 * { "name"
 * 01234567
 * **/

//count the number of object
    int count =0;
    for (int i = 0; i < maxBufLen; i++){
        if(data[i] == ',')
            count ++;
    }
    count *= 2;

    tok_t *arr = (tok_t *)malloc(sizeof(tok_t) * count);

    int start = 0, end = 0, comma =0, num=0;
    start = index + 1;  //3부터 시작.
    arr[0].size=0;
    int name=1; //if 0, value.

//while start
    while(ptr != NULL){
        ptr = strtok(NULL, "\""); // inside name and value domain
        if(ptr == NULL)
            break;
        index = start + strlen(ptr);   
        end = index; 
        addToken(&arr,&num,start,end,name,&count);

        ptr = strtok(NULL, "\"");//move until next string or ,
        if (ptr == NULL)
            break;

        char between[500];
        strcpy(between,ptr);
        name = 0;
        for(int i = 0 ; i < strlen(between); i++){
            if(between[i] == '{'){
                int brEnd;
                int brStart = getIDX(end,i,&index,data,ptr,&brEnd);
                int size = 999;

                addToken(&arr,&num, brStart,brEnd,size,&count);

                ptr = strtok(NULL, "\"");
                if (ptr == NULL)
                    return -1;
                // printf("ptr: %s, len: %d\n",ptr,strlen(ptr));
            }

            if(between[i] == ','){
                name=1; //when next token is name.
                break;
            }
        }

//start index
        index = index + strlen(ptr) + 1; //12까지. 따옴표 까지
        start = index + 1;               // 13부터 시작. 따옴표 바로 다음부터 시작
    }

//print out tokens
    printf("***** ALL TOKENS *****\n");
    for(int j = 0 ; j < num; j++){
        printf("[%3d] ",j);
        for (int i = arr[j].start; i < arr[j].end; i++){
            printf("%c", data[i]);
        }
        printf(" (size=%d, %d~%d)\n",arr[j].size,arr[j].start,arr[j].end);
    }

    fclose(fpIn);
    fclose(fpOut);
    printf("program done!\n");

    return 0;


}