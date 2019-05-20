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

    //특수 문자 인식 필요
    //약속어 인식 필요 
    //key냐 value냐 인식 필요 (flag로? 아니면 :로?)
    //"가 스트링의 시작이면 ", 로 끝나는 단어를 만날 때까지 찾아야함 그러나 ", 앞에 \가 오면 안됨
    //"" , : 같은 문자 제거 (특문이랑 구분 필요)
    /*[ { 만나면 ] } 찾아서 오브젝트화 X
    일단 오브젝트를 만드는 방법?
    이렇게 하면 { 안에  {가 있어도 계속해서 만들면서 내려가기 때문에 좋다}}
    단 닫는 }를 만났을 때 거슬러 올라가면서 오브젝트를 개수를 카운트 하고 미완성된 오브젝트를 완성시켜줘야될 필요가 있다.
    */
   
    printf("\nEnd of Program\n");

    free(data);
    return 0;
}