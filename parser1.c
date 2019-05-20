#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    UNDEFINED = 0, 
    OBJECT = 1, 
    ARRAY = 2, 
    STRING = 3, 
    PRIMITIVE = 4
} type_t;

typedef struct {
    type_t type; // Token type
    int start; // Token start position
    int end;  // Token end position
    int size; // Number of child (nested) tokens
} tok_t;

int main() {
    FILE *fp;
    const int maxLen = 255;
    char buffer[maxLen];
    char *data = (char *)malloc(maxLen * sizeof(char));

    //file open
    fp = fopen("test.json", "r");
    int length = 0; //total length
    int ntok = 0; // number of tokens

    while (fscanf(fp, "%s", buffer) > 0)
    {
        // memory reallocation & string copy
        data = (char *) realloc(data, strlen(data) + strlen(buffer));

        if (length > 1) {
            strcat(data, " ");
            strcat(data, buffer);
        }
        else {
            if (buffer[0] != '{') {
                printf(".json file should begin with { \n");
                free(data);
                return 0;
            }
            strcpy(data, buffer);
        }
        length += strlen(buffer) + 1;
        ntok += 1;
    }
    length = strlen(data)+1;

    // printf("The count is : \n%d\n", ntok);
    // printf("The length of string is : %d\n", length);
    // printf("The string is : \n%s\n", data);
    fclose(fp);


    //특수 문자 인식 필요
    //약속어 인식 필요
    //key냐 value냐 인식 필요
    //"가 스트링의 시작이면 ", 로 끝나는 단어를 만날 때까지 찾아야함 그러나 ", 앞에 \가 오면 안됨
    //"" , : 같은 문자 제거 (특문이랑 구분 필요)
    //[ { 만나면 ] } 찾아서 오브젝트화


    //dynamic structure array
    struct tok_t *tArr;
    tArr = (tok_t*)malloc(1 * sizeof(tArr));

    //string token and tokenizing character
    char *token;
    const char s[2] = " ";
    int tCounter = 0;

    // startPinter + tokens length = endPointer
    int startPointer = 0;
    int endPointer;
    int nextPointer;
    int tokenLen;

    // get the first token
    token = strtok(data, s);

    // walk through other tokens
    while( token != NULL ) {
        tCounter++; // token counter
        tokenLen = strlen(token);
        endPointer = startPointer + tokenLen;
        nextPointer = endPointer + 1;        
        printf( " %s   %d %d %c\n", token, startPointer, endPointer, data[nextPointer]);



        token = strtok(NULL, s);
        startPointer = nextPointer;
    }




    printf("\nEnd of Program\n");

    free(data);
    return 0;
}