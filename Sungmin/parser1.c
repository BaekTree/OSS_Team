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

int main() {
    FILE *fp;
    const int maxLen = 256;
    char buffer[maxLen];
    char *data = (char *)malloc(maxLen * sizeof(char));

    //file open
    fp = fopen("test2.json", "r");
    int length = 0; //total length
    int num_of_str = 0; // number of strings

    // reading file by character
    int ch;
    // for (int i = 0; (i < (sizeof(buffer)-1) && ((ch = fgetc(fp)) != EOF) && (ch != '\n')); i++){
    for (int i = 0, j = 0; (ch = fgetc(fp)) != EOF; i++, j++){
        buffer[j] = ch;
        length++;
        if (ch == '\n'){
            // printf("%s\n", buffer);
            data = (char *) realloc(data, strlen(data) + strlen(buffer));
            strcat(data, buffer);
            memset(buffer, 0, sizeof buffer);
            num_of_str++;
            j = -1;
        }
    }
    buffer[length] = '\0';
    length++;


    // printf("The count is : \n%d\n", num_of_str);
    // printf("The length of string is : %d\n", length);
    // printf("The string is : \n%s\n", data);
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

    int start_cursor = 0;
    int end_cursor;
    int token_size = 0;
    int number_of_tokens = 0; //mun of tok

    int cbracket_counter = 0;
    int sbracket_counter = 0;

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
                    if (data[i+1] == ':'){
                        if (cbracket_counter == 0 && sbracket_counter == 0) {
                            token_size = 1;
                            token_arr[number_of_tokens]->start = start_cursor;
                            token_arr[number_of_tokens]->end = end_cursor;
                            token_arr[number_of_tokens]->size = token_size;
                            token_size = 0;
                            number_of_tokens++;
                            i++;
                        }
                        else { // if it is in the object or array size +1
                            //inner object or array size does not count
                            if (cbracket_counter < 2) token_size++;
                            //else nothing
                        }                        
                    }
                    else {
                        if (cbracket_counter == 0 && sbracket_counter == 0) {
                            // token_size = 0;
                            token_arr[number_of_tokens]->start = start_cursor;
                            token_arr[number_of_tokens]->end = end_cursor;
                            token_arr[number_of_tokens]->size = token_size;
                            token_size = 0;
                            number_of_tokens++;
                        } 
                        // else if (sbracket_counter > 0) {
                        else if (sbracket_counter == 1) {
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
                // start_cursor = i;
                cbracket_counter++;
                if (cbracket_counter == 1) {
                    token_arr[number_of_tokens]->start = start_cursor;
                } // else nothing is counter > 1
            }
            else if (data[i] == '}' && sbracket_counter == 0  && cbracket_counter > 0) {
                cbracket_counter--;
                if (cbracket_counter == 0) {
                    token_arr[number_of_tokens]->size = token_size; //
                    token_arr[number_of_tokens]->end = i+1; // +1?
                    i = token_arr[number_of_tokens]->start + 1;
                    number_of_tokens++;
                    token_size = 0;
                } //else nothing
            }

            // array
            else if (data[i] == '[' && cbracket_counter == 0) {
                // start_cursor = i;
                sbracket_counter++;
                if (sbracket_counter == 1) {
                    token_arr[number_of_tokens]->start = start_cursor;
                } // else nothing is counter > 1
            }
            else if (data[i] == ']' && cbracket_counter == 0 && sbracket_counter > 0) {
                sbracket_counter--;
                if (sbracket_counter == 0) {
                    token_arr[number_of_tokens]->size = token_size; //
                    token_arr[number_of_tokens]->end = i+1;
                    i = token_arr[number_of_tokens]->start + 1;
                    number_of_tokens++;
                    token_size = 0;
                } //else nothing
            }

            // true false etc
            else if (data[i] == '0'){
            }
            // numeric 
            else if (data[i]){
                //double num = 1.234E+11;
            }
        }
    }

    for (int i = 0; i < number_of_tokens; i++) {
        printf("[%3d] ", i );
        for (int j = token_arr[i]->start; j < token_arr[i]->end; j++ ) {
            printf("%c", data[j]);
        }
        printf (" (size=%d, %d~%d)\n",token_arr[i]->size, token_arr[i]->start, token_arr[i]->end);
        
    }

    printf("\nEnd of Program\n");

    free(data);
    for (int i = 0; i < sizeof(token_arr) / sizeof(struct tok_t *); i++)
    {
        free(token_arr[i]);
    }

    return 0;
}

// Returns true (non-zero) if character-string parameter represents a signed or unsigned floating-point number. Otherwise returns false (zero).
int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}
