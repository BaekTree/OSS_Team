#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int main(int argc, char *argv[]) {
    FILE *fp;
    const int maxLen = 256;
    char buffer[maxLen];
    char *data = (char *)malloc(maxLen * sizeof(char));

    //file open
    if (argc == 1) {        // if there is no argument
        fp = fopen("test1.json", "r");
    }
    else {                  // get the file name from input
        fp = fopen(argv[1], "r");
    }
    if(fp == NULL) {
        printf("Reading failed");
        return -1;
    }
    int length = 0;         // total length
    char ch;                 // character to read

    // 한 글자씩 읽어서 한 줄이 되면 data array에 넣고 버퍼는 초기화 
    for (int i = 0, j = 0; (ch = fgetc(fp)) != EOF; i++, j++){
        buffer[j] = ch;
        length++;
        if (ch == '\n'){
            // printf("%s\n", buffer);
            data = (char *) realloc(data, strlen(data) + strlen(buffer));
            strcat(data, buffer);
            memset(buffer, 0, sizeof buffer);
            j = -1;
        }
    }
    buffer[length] = '\0';
    length++;
    fclose(fp);

    //dynamic structure array
    // struct tok_t *token_arr;
    // token_arr = (tok_t*)malloc(50 * sizeof(token_arr));

    //not dynamic
    tok_t * token_arr[100];
    // 구조체 포인터 배열 전체 크기에서 요소(구조체 포인터)의 크기로 나눠서 요소 개수를 구함
    for (int i = 0; i < sizeof(token_arr) / sizeof(tok_t *); i++)    // 요소 개수만큼 반복
    {
        token_arr[i] = malloc(sizeof(tok_t));    // 각 요소에 구조체 크기만큼 메모리 할당
    }

    int start_cursor = 0;       // start index of the token
    int end_cursor;             // end index of the token
    int token_size = 0;         // size of token ( :pairs )
    int num_of_token = 0;       // number of tokens
    int is_primitive;           // flag to identify
    int cbracket_counter = 0;   // { } counter
    int sbracket_counter = 0;   // [ ] counter

    for (int i = 1; i < length; i++) {
        // start index marked when data[i] != '\n' and ' ' and '\t'
        if(data[i] != ' ' && data[i] != '\n' && data[i] != '\t') {
            start_cursor = i;
            // token string (mostly)
            if(data[i] == '\"') {
                // check if it is \" character
                if (data[i-1] != '\\'){
                    start_cursor++; //start index does not include first "
                    for (int j = start_cursor; ;j++){
                        if (data[j] == '\"'){
                            end_cursor = j;
                            i = j; //i++ will be happen at upper "for" condition
                            break;
                        }
                    }
                    // if this token is "name"
                    if (data[i+1] == ':'){
                        if (cbracket_counter == 0 && sbracket_counter == 0) {
                            token_size = 1;
                            token_arr[num_of_token]->start = start_cursor;
                            token_arr[num_of_token]->end = end_cursor;
                            token_arr[num_of_token]->size = token_size;
                            token_arr[num_of_token]->type = STRING;         //is STRING
                            token_size = 0;
                            num_of_token++;
                            i++;
                        }
                        // can't be in the array
                        else { 
                            if (cbracket_counter == 1 && sbracket_counter == 0) token_size++;
                            //else nothing
                        }                        
                    }
                    // if token is string "value"
                    else {
                        if (cbracket_counter == 0 && sbracket_counter == 0) {
                            // token_size = 0;
                            token_arr[num_of_token]->start = start_cursor;
                            token_arr[num_of_token]->end = end_cursor;
                            token_arr[num_of_token]->size = token_size;
                            token_arr[num_of_token]->type = STRING;         //is STRING
                            token_size = 0;
                            num_of_token++;
                        } 
                        // else if (sbracket_counter > 0) {
                        else if (sbracket_counter == 1 && cbracket_counter == 0) {
                            //name과 value가 페어가 아니라면
                            if ((data[start_cursor-2] != ':') || (data[start_cursor-3] != ':') || (data[start_cursor-4] != ':')) {
                                token_size++;
                            }
                            // else 페어이기 때문에 페어일 경우 값을 가지지 않는다.
                        } //else nothing
                    }
                }
                else continue;
            }
            // object
            else if (data[i] == '{' && sbracket_counter == 0){
                cbracket_counter++;
                if (cbracket_counter == 1) {
                    token_arr[num_of_token]->start = start_cursor;
                } // else nothing when counter > 1
            }
            else if (data[i] == '{' && cbracket_counter == 0 && sbracket_counter == 1){ 
                cbracket_counter++;
            }
            else if (data[i] == '}' && sbracket_counter == 0  && cbracket_counter > 0) {
                cbracket_counter--;
                if (cbracket_counter == 0) {
                    token_arr[num_of_token]->size = token_size; // size of the token
                    token_arr[num_of_token]->end = i+1;         // +1 to print out the value
                    token_arr[num_of_token]->type = OBJECT;     // is OBJECT
                    i = token_arr[num_of_token]->start + 1;
                    num_of_token++;
                    token_size = 0;
                } //else nothing
            }
             else if (data[i] == '}' && sbracket_counter == 1  && cbracket_counter > 0) {
                 cbracket_counter--;
                 if (cbracket_counter == 0) { 
                     token_size++;
                 }
             }
            // array
            else if (data[i] == '[' && cbracket_counter == 0) {
                sbracket_counter++;
                if (sbracket_counter == 1) {
                    token_arr[num_of_token]->start = start_cursor;
                } // else nothing is counter > 1
            }
            else if (data[i] == ']' && cbracket_counter == 0 && sbracket_counter > 0) {
                sbracket_counter--;
                if (sbracket_counter == 0) {
                    token_arr[num_of_token]->size = token_size; //
                    token_arr[num_of_token]->end = i+1;
                    i = token_arr[num_of_token]->start + 1;
                    num_of_token++;
                    token_size = 0;
                } //else nothing
            }
            // 아래 두 벨류 토큰들은 어레이와 오브젝트 안에 있는지 밖에 있는지에 따라서 토크나이징을 할지 안할지 결정된다.
            // true false numeric
            else if ((data[i] == 't' || data[i] == 'f') || (isdigit(data[i]) || data[i] == '-')) {  // Starts with t or f
                // check if it is primitive boolean type
                if (data[i] == 't' && data[i+1] == 'r' && data[i+2] == 'u' && data[i+3] == 'e') {
                    if (data[i+4] == ',' || data[i+4] == ' ' || data[i+4] == '\n' || data[i+4] == '\t'){
                        is_primitive = 1;
                        end_cursor = i+4;
                    }
                }
                else if (data[i] == 'f' && data[i+1] == 'a' && data[i+2] == 'l' && data[i+3] == 's' && data[i+4] == 'e') {
                    if (data[i+5] == ',' || data[i+5] == ' ' || data[i+5] == '\n' || data[i+5] == '\t'){
                        is_primitive = 1;
                        end_cursor = i+5;                        
                    }
                } 
                else is_primitive = 0;
                //numeric
                if((isdigit(data[i]) || data[i] == '-') && is_primitive == 0) {
                    int t = 0; // 0 - int , 1 - double, 2 - exponent
                    // int n = 0; // negative or not
                    // if (data[i] == '-') n = 1; //is negative
                    for(int j = start_cursor; ; j++) {
                        if (data[j] == ' ' || data[j] == '\n' || data[j] == ',' || data[j] == '\t') {
                            end_cursor = j;
                            is_primitive = 1;
                            break;
                        }
                    } 
                }
                if (is_primitive == 1) {
                    //just value
                    if (cbracket_counter == 0 && sbracket_counter == 0) {
                        token_arr[num_of_token]->start = start_cursor;
                        token_arr[num_of_token]->end = end_cursor;
                        token_arr[num_of_token]->size = 0;
                        token_arr[num_of_token]->type = PRIMITIVE;         //is PRIMITIVE
                        num_of_token++;
                        i = end_cursor;
                    }
                    // if it is in array only token size ++
                    else if (cbracket_counter == 0 && sbracket_counter == 1) {
                        if(((data[start_cursor-2] != ':') || (data[start_cursor-3] != ':'))) { 
                            i = end_cursor;
                            token_size++;
                        }   // else nothing
                    }
                }
            }
        }
    }
    // print out
    for (int i = 0; i < num_of_token; i++) {
        printf("[%3d] ", i );
        for (int j = token_arr[i]->start; j < token_arr[i]->end; j++ ) {
            printf("%c", data[j]);
        }
        char * type;
        if (token_arr[i]->type == 0) type = "UNDEFINED";
        else if (token_arr[i]->type == 1) type = "OBJECT";
        else if (token_arr[i]->type == 2) type = "ARRAY";
        else if (token_arr[i]->type == 3) type = "STRING";
        else type = "PRIMITIVE";
        printf (" (size=%d, %d~%d, JSMN_%s)\n",token_arr[i]->size, token_arr[i]->start, token_arr[i]->end, type);
    }
    // memory free
    free(data);
    for (int i = 0; i < sizeof(token_arr) / sizeof(struct tok_t *); i++)
    {
        free(token_arr[i]);
    }
    return 0;
}


