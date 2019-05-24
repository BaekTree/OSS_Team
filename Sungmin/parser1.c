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
    tok_t * tArr[100];
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
                            //inner object or array size does not count
                            if (cbcounter < 2) tsize++;
                            //else nothing
                        }                        
                    }
                    else {
                        if (cbcounter == 0 && sbcounter == 0) {
                            // tsize = 0;
                            tArr[ntok]->start = startCursor;
                            tArr[ntok]->end = endCursor;
                            tArr[ntok]->size = tsize;
                            tsize = 0;
                            ntok++;
                        } 
                        // else if (sbcounter > 0) {
                        else if (sbcounter == 1) {
                            //name과 value가 페어가 아니라면
                            if ((data[startCursor-2] != ':') || (data[startCursor-3] != ':') || (data[startCursor-4] != ':')) {
                                tsize++;
                            }
                            // else 페어이기 때문에 페어일 경우 값을 가지지 않는다.
                        } //else nothing
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
                    tArr[ntok]->end = i+1; // +1?
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
            else if (data[i] == ']' && cbcounter == 0 && sbcounter > 0) {
                sbcounter--;
                if (sbcounter == 0) {
                    tArr[ntok]->size = tsize; //
                    tArr[ntok]->end = i+1;
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
                //double num = 1.234E+11;
            }
        }
    }

    for (int i = 0; i < ntok; i++) {
        printf("[%3d] ", i );
        for (int j = tArr[i]->start; j < tArr[i]->end; j++ ) {
            printf("%c", data[j]);
        }
        printf (" (size=%d, %d~%d)\n",tArr[i]->size, tArr[i]->start, tArr[i]->end);
        
    }



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
