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
    fp = fopen("test.json", "r");
    int length = 0; //total length
    int nos = 0; // number of strings

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
            nos++;
            j = -1;
        }
    }
    buffer[length] = '\0';
    length++;


    // printf("The count is : \n%d\n", nos);
    // printf("The length of string is : %d\n", length);
    // printf("The string is : \n%s\n", data);
    fclose(fp);

    //dynamic structure array
    // struct tok_t *tArr;
    // tArr = (tok_t*)malloc(1 * sizeof(tArr));

    //not dynamic
    tok_t * tArr[40];
    // 구조체 포인터 배열 전체 크기에서 요소(구조체 포인터)의 크기로 나눠서 요소 개수를 구함
    for (int i = 0; i < sizeof(tArr) / sizeof(tok_t *); i++)    // 요소 개수만큼 반복
    {
        tArr[i] = malloc(sizeof(tok_t));    // 각 요소에 구조체 크기만큼 메모리 할당
    }

    int startCursor = 0;
    int endCursor;
    int tsize = 0;
    int ntok = 0; //mun of tok

    int cbcounter = 0;
    int sbcounter = 0;

    for (int i = 1; i < length; i++) {
        // start index marked when data[i] != '\n' and ' ' and '\t'
        if(data[i] != ' ' && data[i] != '\n' && data[i] != '\t') {
            startCursor = i;
            // token string (mostly)
            if(data[i] == '\"') {
                // check if it is \" character
                if (data[i-1] != '\\'){
                    startCursor++; //start index does not include first "
                    for (int j = startCursor; ;j++){
                        if (data[j] == '\"'){
                            endCursor = j;
                            i = j; //i++ will be happen at upper "for" condition
                            break;
                        }
                    }
                    if (data[i+1] == ':'){
                        if (cbcounter == 0 && sbcounter == 0) {
                            tsize = 1;
                            tArr[ntok]->start = startCursor;
                            tArr[ntok]->end = endCursor;
                            tArr[ntok]->size = tsize;
                            tsize = 0;
                            ntok++;
                            i++;
                        }
                        else { // if it is in the object or array size +1
                            tsize++;
                        }                        
                    }
                    else {
                        if (cbcounter == 0 && sbcounter == 0) {
                            tsize = 0;
                            tArr[ntok]->start = startCursor;
                            tArr[ntok]->end = endCursor;
                            tArr[ntok]->size = tsize;
                            ntok++;
                        } // else nothing
                    }
                }
                else continue;
            }
            // object
            else if (data[i] == '{' && sbcounter == 0){
                // startCursor = i;
                cbcounter++;
                if (cbcounter == 1) {
                    tArr[ntok]->start = startCursor;
                } // else nothing is counter > 1
            }
            else if (data[i] == '}' && sbcounter == 0  && cbcounter > 0) {
                cbcounter--;
                if (cbcounter == 0) {
                    tArr[ntok]->size = tsize; //
                    tArr[ntok]->end = i; // +1?
                    i = tArr[ntok]->start + 1;
                    ntok++;
                    tsize = 0;
                } //else nothing
            }

            // array
            else if (data[i] == '[' && cbcounter == 0) {
                // startCursor = i;
                sbcounter++;
                if (sbcounter == 1) {
                    tArr[ntok]->start = startCursor;
                } // else nothing is counter > 1
            }
            else if (data[i] == ']' && cbcounter == 0) {
                sbcounter--;
                if (sbcounter == 0) {
                    tArr[ntok]->size = tsize; //
                    tArr[ntok]->end = endCursor;
                    i = tArr[ntok]->start + 1;
                    ntok++;
                    tsize = 0;
                } //else nothing
            }

            // true false etc
            else if (data[i] == '0'){
            }
            // numeric 
            else if (data[i]){
            }
        }

    }





    //특수 문자 인식 필요
    //약속어 인식 필요 
    //key냐 value냐 인식 필요 (flag로? 아니면 :로?)
    //"가 스트링의 시작이면 ", 로 끝나는 단어를 만날 때까지 찾아야함 그러나 ", 앞에 \가 오면 안됨
    //"" , : 같은 문자 제거 (특문이랑 구분 필요)

    printf("\nEnd of Program\n");

    free(data);
    for (int i = 0; i < sizeof(tArr) / sizeof(struct tok_t *); i++)
    {
        free(tArr[i]);
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
