#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "json_parser.h"

// partial string to double
double toDouble(char* s, int start, int stop);

// print out the token num_check_array in form
void print_num_check_array(int num_of_t, tok_t *t_arr, char *data);

// filling the country num_check_array and returns number of countries
int country_maker(int num_of_tok, tok_t *t_arr, char *data, country_t *c_arr);

// parsing the json file returns the number of tokens
int json_parser(int length, int token_num_check_array_size, tok_t* token_arr, char* data);

// display menu
void menu(int number_of_country, country_t *country_arr);

// country quiz asking capital and name
void Quiz(int n_of_con, country_t *country);

int main(int argc, char *argv[]) {
    FILE *fp;
    const int maxLen = 256;
    char buffer[maxLen];
    char *data = (char *)malloc(maxLen * sizeof(char));
    int token_num_check_array_size = 1024;

    //file open
    if (argc == 1) {        // if there is no argument
        fp = fopen("../Testfiles/countries.json", "r");
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

    // 한 글자씩 읽어서 한 줄이 되면 data num_check_array에 넣고 버퍼는 초기화 
    for (int i = 0, j = 0; (ch = fgetc(fp)) != EOF; i++, j++){
        buffer[j] = ch;
        length++;
        if (ch == '\n' ){
            // printf("%s\n", buffer);
            data = (char *) realloc(data, strlen(data) + strlen(buffer));
            strcat(data, buffer);
            memset(buffer, 0, sizeof buffer);
            j = -1;
        }
    }
    if (buffer[0] != '\0') {
        length++;
        data = (char *) realloc(data, strlen(data) + strlen(buffer));
        strcat(data, buffer);
        memset(buffer, 0, sizeof buffer);
        data[++length] = '\0';
    }
    fclose(fp);

    //dynamic structure num_check_array
    tok_t *token_arr;
    token_arr = (tok_t *)malloc(sizeof(tok_t) * token_num_check_array_size);
    for (int i = 0; i < token_num_check_array_size; i++) {
        token_arr[i].type = UNDEFINED;
    }

    // parse and return number of tokens total
    int num_of_token = json_parser(length, token_num_check_array_size, token_arr, data);       // number of tokens

    // print out the token num_check_array
    print_num_check_array(num_of_token, token_arr, data);

    // declaring country num_check_array dynamically
    country_t *country_arr;
    country_arr = (country_t *)malloc(sizeof(country_t) * 100);

    // fill num_check_array
    int number_of_country = country_maker(num_of_token, token_arr, data, country_arr);

    //print out the country num_check_array
    /*
    for (int i = 0; i < number_of_country; i++) {
        printf("%s\n", country_arr[i].country_name);
        printf("%s\n", country_arr[i].capital_name);
        for (int j = 0; country_arr[i].language[j][0] != '\0'; j++){
            printf("%s\n", country_arr[i].language[j]);
        }
        printf("%f\n", country_arr[i].gdp);
        printf("%s\n", country_arr[i].population);
        printf("%s\n", country_arr[i].currency);
        printf("%s\n", country_arr[i].continent);
        for (int j = 0; country_arr[i].legislature[j][0] != '\0'; j++){
            printf("%s\n", country_arr[i].legislature[j]);
        }
    }
    */

    // memory free
    free(data);
    free(token_arr);
    free(country_arr);

    return 0;
}

/* Functions */
double toDouble(char* s, int start, int stop) {
    char d_arr[16];
    double d;
    for (int i = start, j = 0; i <= stop; i++, j++) {
        d_arr[j] = s[i];
    }
    d = atof(d_arr);
    return d;
}

void print_num_check_array(int num_of_t, tok_t *t_arr, char *data) {
    // print out
    for (int i = 0; i < num_of_t; i++) {
        printf("[%3d] ", i+1 );
        for (int j = t_arr[i].start; j < t_arr[i].end; j++ ) {
            printf("%c", data[j]);
        }
        char * type;
        if (t_arr[i].type == 0) type = "UNDEFINED";
        else if (t_arr[i].type == 1) type = "OBJECT";
        else if (t_arr[i].type == 2) type = "num_check_ARRAY";
        else if (t_arr[i].type == 3) type = "STRING";
        else type = "PRIMITIVE";
        printf (" (size=%d, %d~%d, JSMN_%s)\n",t_arr[i].size, t_arr[i].start, t_arr[i].end, type);
    }
}

int country_maker(int num_of_tok, tok_t *t_arr, char *data, country_t *c_arr){
    int length;
    int num_of_con = 0;
    double gdp;

    for (int i = 4, j = 0; i < num_of_tok; i++, j++) {
        num_of_con++;

        // country name
        length = t_arr[i].end - t_arr[i].start;
        strncpy(c_arr[j].country_name, data + t_arr[i].start, length);
        i += 3;

        // capital name
        length = t_arr[i].end - t_arr[i].start;
        strncpy(c_arr[j].capital_name, data + t_arr[i].start, length);
        i += 3;

        // languages
        for(int k = 0; ; k++, i++) {
            if(data[t_arr[i].start] == 'G' && data[t_arr[i].start+1] == 'D' && data[t_arr[i].end - 1] == 'P') break;
            length = t_arr[i].end - t_arr[i].start;
            strncpy(c_arr[j].language[k], data + t_arr[i].start, length);
        }
        i++;

        //GDP
        gdp = toDouble(data, t_arr[i].start, t_arr[i].end-1);
        c_arr[j].gdp = gdp;
        i += 2;

        // population
        length = t_arr[i].end - t_arr[i].start;
        strncpy(c_arr[j].population, data + t_arr[i].start, length);
        i += 2;

        // currency
        length = t_arr[i].end - t_arr[i].start;
        strncpy(c_arr[j].currency, data + t_arr[i].start, length);
        i += 3;

        // legislature
        for(int k = 0; ; k++, i++) {
            if (data[t_arr[i].start] == 'C' && data[t_arr[i].start+1] == 'o' && data[t_arr[i].start+2] == 'n' 
             && data[t_arr[i].end - 3] == 'e' && data[t_arr[i].end - 2] == 'n' && data[t_arr[i].end - 1] == 't') break;
            length = t_arr[i].end - t_arr[i].start;
            strncpy(c_arr[j].legislature[k], data + t_arr[i].start, length);
        }
        i++;

        // continent
        length = t_arr[i].end - t_arr[i].start;
        strncpy(c_arr[j].continent, data + t_arr[i].start, length);
        i++;
    }
    return num_of_con;
}

int json_parser(int length, int token_num_check_array_size, tok_t* token_arr, char* data) {
    int num_of_token = 0;       // number of tokens
    int start_cursor = 0;       // start index of the token
    int end_cursor;             // end index of the token
    int token_size = 0;         // size of token ( :pairs )
    int is_primitive;           // flag to identify
    int cbracket_counter = 0;   // { } counter
    int sbracket_counter = 0;   // [ ] counter

    for (int i = 0; i < length; i++) {
        //if number of tokens exceed the max size -> increase the size of the token num_check_array
        if (num_of_token == token_num_check_array_size - 1) {
            token_num_check_array_size = token_num_check_array_size * 2;
            token_arr = (tok_t *)realloc(token_arr, token_num_check_array_size);
        }
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
                            token_arr[num_of_token].start = start_cursor;
                            token_arr[num_of_token].end = end_cursor;
                            token_arr[num_of_token].size = token_size;
                            token_arr[num_of_token].type = STRING;         //is STRING
                            token_size = 0;
                            num_of_token++;
                            i++;
                        }
                        // can't be in the num_check_array
                        else { 
                            if (cbracket_counter == 1 && sbracket_counter == 0) token_size++;
                            //else nothing
                        }                        
                    }
                    // if token is string "value"
                    else {
                        if (cbracket_counter == 0 && sbracket_counter == 0) {
                            // token_size = 0;
                            token_arr[num_of_token].start = start_cursor;
                            token_arr[num_of_token].end = end_cursor;
                            token_arr[num_of_token].size = token_size;
                            token_arr[num_of_token].type = STRING;         //is STRING
                            token_size = 0;
                            num_of_token++;
                        } 
                        // else if (sbracket_counter > 0) {
                        else if (sbracket_counter == 1 && cbracket_counter == 0) {
                            //name and value is not pair
                            if ((data[start_cursor-2] != ':') || (data[start_cursor-3] != ':') || (data[start_cursor-4] != ':')) {
                                token_size++;
                            }
                            // else if the string value is pair with 'name'(key) it does not increase the size
                        } //else nothing
                    }
                }
                else continue;
            }
            // object
            else if (data[i] == '{' && sbracket_counter == 0){
                cbracket_counter++;
                if (cbracket_counter == 1) {
                    token_arr[num_of_token].start = start_cursor;
                } // else nothing when counter > 1
            }
            else if (data[i] == '{' && cbracket_counter == 0 && sbracket_counter == 1){ 
                cbracket_counter++;
            }
            else if (data[i] == '}' && sbracket_counter == 0  && cbracket_counter > 0) {
                cbracket_counter--;
                if (cbracket_counter == 0) {
                    token_arr[num_of_token].size = token_size; // size of the token
                    token_arr[num_of_token].end = i+1;         // +1 to print out the value
                    token_arr[num_of_token].type = OBJECT;     // is OBJECT
                    i = token_arr[num_of_token].start + 1;
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
            // num_check_array
            else if (data[i] == '[' && cbracket_counter == 0) {
                sbracket_counter++;
                if (sbracket_counter == 1) {
                    token_arr[num_of_token].start = start_cursor;
                } // else nothing is counter > 1
            }
            else if (data[i] == ']' && cbracket_counter == 0 && sbracket_counter > 0) {
                sbracket_counter--;
                if (sbracket_counter == 0) {
                    token_arr[num_of_token].size = token_size; //
                    token_arr[num_of_token].end = i+1;
                    i = token_arr[num_of_token].start + 1;
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
                        token_arr[num_of_token].start = start_cursor;
                        token_arr[num_of_token].end = end_cursor;
                        token_arr[num_of_token].size = 0;
                        token_arr[num_of_token].type = PRIMITIVE;         //is PRIMITIVE
                        num_of_token++;
                        i = end_cursor;
                    }
                    // if it is in num_check_array only token size ++
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
    return num_of_token;
}

void menu(int number_of_country, country_t *country_arr) {
    int option;
    
	while(1){
        printf("\n\nChoose the information you would like to see");
        printf("\n\t 1 : Display the parsed tokens");
        printf("\n\t 2 : List names of all the countries");
        printf("\n\t 3 : List the country names according to the continent");
        printf("\n\t 4 : List country names according to GDP ranking");
        printf("\n\t 4 : Test your Knowledge (Quiz)");
        printf("\n\t 0: Quit the application");
        printf("\n");
    
	    scanf("%d", &option);

        switch(option){
            case 1: // Parser output

                break;

            case 2: // All countries

                 break;

            case 3: // Countries by continent
                
                break;            
            
            case 4: // GDP Rank
                
                break;
            case 5: // Quiz
                Quiz(number_of_country, country_arr);
                break;

            case 0: // Exit
                printf("Application is closed\n");
                return;

            default: // Wrong input
                printf("You have entered a wrong value\n"); 
                break;

        }
}

void Quiz(int number_of_countries, country_t *country) {
    char answer[128];
    int number_of_quiz_question = 10;
    int score = 0;
    int num_check_array[number_of_countries];

    srand(time(NULL));

    for (int i = 0; i < number_of_countries; i++) {     // fill num_check_array
        num_check_array[i] = i;
    }

    for (int i = 0; i < number_of_countries; i++) {    // shuffle num_check_array
        int temp = num_check_array[i];
        int randomIndex = rand() % number_of_countries;

        num_check_array[i]  = num_check_array[randomIndex];
        num_check_array[randomIndex] = temp;
    }

    for(int i = 0; i < number_of_quiz_question; i++){
        int n = num_check_array[i];
        int q = rand()%2+1;

        printf("%d. ", i+1);

        if(q==1){
            printf("Which country has the capital %s?\n", country[n].capital_name);
            scanf("%s", answer);

            if(strcmp(answer, country[n].country_name)!=0){
                printf("Correct Answer!!\n");
                score++;
            }
            else{
                printf("Wrong Answer!!\n");
            }

        }
        if(q==2){
            printf("What is the capital of %s?\n", country[n].country_name);
            scanf("%s", answer);

            if(strcmp(answer, country[n].capital_name)!=0){
                printf("Correct Answer!!\n");
                score++;
            }
            else{
                printf("Wrong Answer!!\n");
            }
        }

    }
    printf("\n\nYour score is %d", score);
    exit;
    
}