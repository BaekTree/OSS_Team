#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "json_parser.h"
#define MAX_LIMIT 128

// partial string to double
double toDouble(char *s, int start, int stop);

// print out the token array in form
void print_array(int num_of_t, tok_t *t_arr, char *data);

// filling the c_arr array and returns number of countries
int country_maker(int num_of_tok, tok_t *t_arr, char *data, country_t *c_arr);

// parsing the json file returns the number of tokens
int json_parser(int length, int token_array_size, tok_t *token_arr, char *data);

// display menu
void menu(int num_of_t, int num_of_c, tok_t *t_arr, char *data, country_t *c_arr);

// scan integer input(select country) and distinguish cases --> call "Search_Country" function.
void Search_Country(int num_of_c, country_t *c_arr);

// find selected country from array and print info.
void Print_Country(int num_of_c, country_t *c_arr, char *search);

// scan integer input(select continent) and distinguish cases --> call "Search_Continent" function.
void Search_Continent(int num_of_c, country_t *c_arr);

// find countries that matches continent selected and print them.
void Print_Continent(int num_of_c, country_t *c_arr, char *search);

//concrete alpabetical sort function
void sortABC(country_t *ctr, int n);

//concrete GDP sort function
void sortGDP(country_t *ctr, int n);

//print GDP sort rank
void printRank(country_t *rk, int n);

//sort countries in GDP ranking
void rank(country_t *ctr, int n);

//sot countries in alphabetical order
void ABCD(country_t *ctr, int n);

// c_arr quiz asking capital and name
void Quiz(int num_of_c, country_t *c_arr);

void menutest();

int main(int argc, char *argv[])
{
    FILE *fp;
    const int maxLen = 256;
    char buffer[maxLen];
    char *data = (char *)malloc(maxLen * sizeof(char));
    int token_array_size = 1024;

    //file open
    if (argc == 1)
    { // if there is no argument
        // fp = fopen("countries.json", "r");
        fp = fopen("../Testfiles/countries.json", "r");
    }
    else
    { // get the file name from input
        fp = fopen(argv[1], "r");
    }
    if (fp == NULL)
    {
        printf("Reading failed");
        return -1;
    }
    int length = 0; // total length
    char ch;        // character to read

    // 한 글자씩 읽어서 한 줄이 되면 data array에 넣고 버퍼는 초기화
    for (int i = 0, j = 0; (ch = fgetc(fp)) != EOF; i++, j++)
    {
        buffer[j] = ch;
        length++;
        if (ch == '\n')
        {
            // printf("%s\n", buffer);
            data = (char *)realloc(data, strlen(data) + strlen(buffer));
            strcat(data, buffer);
            memset(buffer, 0, sizeof buffer);
            j = -1;
        }
    }
    if (buffer[0] != '\0')
    {
        length++;
        data = (char *)realloc(data, strlen(data) + strlen(buffer));
        strcat(data, buffer);
        memset(buffer, 0, sizeof buffer);
        data[++length] = '\0';
    }
    fclose(fp);

    //dynamic structure array
    tok_t *token_arr;
    token_arr = (tok_t *)malloc(sizeof(tok_t) * token_array_size);
    for (int i = 0; i < token_array_size; i++)
    {
        token_arr[i].type = UNDEFINED;
    }

    // parse and return number of tokens total
    int num_of_token = json_parser(length, token_array_size, token_arr, data); // number of tokens

    // print out the token array
    // print_array(num_of_token, token_arr, data);

    // declaring country array dynamically
    country_t *country_arr;
    country_arr = (country_t *)malloc(sizeof(country_t) * 100);

    // fill array
    int num_of_c = country_maker(num_of_token, token_arr, data, country_arr);

    // call menu
    menu(num_of_token, num_of_c, token_arr, data, country_arr);

    // memory free
    free(data);
    free(token_arr);
    free(country_arr);

    return 0;
}

/* Functions */
double toDouble(char *s, int start, int stop)
{
    char d_arr[16];
    double d;
    for (int i = start, j = 0; i <= stop; i++, j++)
    {
        d_arr[j] = s[i];
    }
    d = atof(d_arr);
    return d;
}

void print_array(int num_of_t, tok_t *t_arr, char *data)
{
    // print out
    for (int i = 0; i < num_of_t; i++)
    {
        printf("[%3d] ", i + 1);
        for (int j = t_arr[i].start; j < t_arr[i].end; j++)
        {
            printf("%c", data[j]);
        }
        char *type;
        if (t_arr[i].type == 0)
            type = "UNDEFINED";
        else if (t_arr[i].type == 1)
            type = "OBJECT";
        else if (t_arr[i].type == 2)
            type = "ARRAY";
        else if (t_arr[i].type == 3)
            type = "STRING";
        else
            type = "PRIMITIVE";
        printf(" (size=%d, %d~%d, JSMN_%s)\n", t_arr[i].size, t_arr[i].start, t_arr[i].end, type);
    }
}

int country_maker(int num_of_tok, tok_t *t_arr, char *data, country_t *c_arr)
{
    int length;
    int num_of_con = 0;
    double gdp;

    for (int i = 4, j = 0; i < num_of_tok; i++, j++)
    {
        num_of_con++;

        // c_arr name
        length = t_arr[i].end - t_arr[i].start;
        strncpy(c_arr[j].country_name, data + t_arr[i].start, length);
        i += 3;

        // capital name
        length = t_arr[i].end - t_arr[i].start;
        strncpy(c_arr[j].capital_name, data + t_arr[i].start, length);
        i += 3;

        // languages
        for (int k = 0;; k++, i++)
        {
            if (data[t_arr[i].start] == 'G' && data[t_arr[i].start + 1] == 'D' && data[t_arr[i].end - 1] == 'P')
                break;
            length = t_arr[i].end - t_arr[i].start;
            strncpy(c_arr[j].language[k], data + t_arr[i].start, length);
        }
        i++;

        //GDP
        gdp = toDouble(data, t_arr[i].start, t_arr[i].end - 1);
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
        for (int k = 0;; k++, i++)
        {
            if (data[t_arr[i].start] == 'C' && data[t_arr[i].start + 1] == 'o' && data[t_arr[i].start + 2] == 'n' && data[t_arr[i].end - 3] == 'e' && data[t_arr[i].end - 2] == 'n' && data[t_arr[i].end - 1] == 't')
                break;
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

int json_parser(int length, int token_array_size, tok_t *token_arr, char *data)
{
    int num_of_token = 0;     // number of tokens
    int start_cursor = 0;     // start index of the token
    int end_cursor;           // end index of the token
    int token_size = 0;       // size of token ( :pairs )
    int is_primitive;         // flag to identify
    int cbracket_counter = 0; // { } counter
    int sbracket_counter = 0; // [ ] counter

    for (int i = 0; i < length; i++)
    {
        //if number of tokens exceed the max size -> increase the size of the token array
        if (num_of_token == token_array_size - 1)
        {
            token_array_size = token_array_size * 2;
            token_arr = (tok_t *)realloc(token_arr, token_array_size);
        }
        // start index marked when data[i] != '\n' and ' ' and '\t'
        if (data[i] != ' ' && data[i] != '\n' && data[i] != '\t')
        {
            start_cursor = i;
            // token string (mostly)
            if (data[i] == '\"')
            {
                // check if it is \" character
                if (data[i - 1] != '\\')
                {
                    start_cursor++; //start index does not include first "
                    for (int j = start_cursor;; j++)
                    {
                        if (data[j] == '\"')
                        {
                            end_cursor = j;
                            i = j; //i++ will be happen at upper "for" condition
                            break;
                        }
                    }
                    // if this token is "name"
                    if (data[i + 1] == ':')
                    {
                        if (cbracket_counter == 0 && sbracket_counter == 0)
                        {
                            token_size = 1;
                            token_arr[num_of_token].start = start_cursor;
                            token_arr[num_of_token].end = end_cursor;
                            token_arr[num_of_token].size = token_size;
                            token_arr[num_of_token].type = STRING; //is STRING
                            token_size = 0;
                            num_of_token++;
                            i++;
                        }
                        // can't be in the array
                        else
                        {
                            if (cbracket_counter == 1 && sbracket_counter == 0)
                                token_size++;
                            //else nothing
                        }
                    }
                    // if token is string "value"
                    else
                    {
                        if (cbracket_counter == 0 && sbracket_counter == 0)
                        {
                            // token_size = 0;
                            token_arr[num_of_token].start = start_cursor;
                            token_arr[num_of_token].end = end_cursor;
                            token_arr[num_of_token].size = token_size;
                            token_arr[num_of_token].type = STRING; //is STRING
                            token_size = 0;
                            num_of_token++;
                        }
                        // else if (sbracket_counter > 0) {
                        else if (sbracket_counter == 1 && cbracket_counter == 0)
                        {
                            //name and value is not pair
                            if ((data[start_cursor - 2] != ':') || (data[start_cursor - 3] != ':') || (data[start_cursor - 4] != ':'))
                            {
                                token_size++;
                            }
                            // else if the string value is pair with 'name'(key) it does not increase the size
                        } //else nothing
                    }
                }
                else
                    continue;
            }
            // object
            else if (data[i] == '{' && sbracket_counter == 0)
            {
                cbracket_counter++;
                if (cbracket_counter == 1)
                {
                    token_arr[num_of_token].start = start_cursor;
                } // else nothing when counter > 1
            }
            else if (data[i] == '{' && cbracket_counter == 0 && sbracket_counter == 1)
            {
                cbracket_counter++;
            }
            else if (data[i] == '}' && sbracket_counter == 0 && cbracket_counter > 0)
            {
                cbracket_counter--;
                if (cbracket_counter == 0)
                {
                    token_arr[num_of_token].size = token_size; // size of the token
                    token_arr[num_of_token].end = i + 1;       // +1 to print out the value
                    token_arr[num_of_token].type = OBJECT;     // is OBJECT
                    i = token_arr[num_of_token].start + 1;
                    num_of_token++;
                    token_size = 0;
                } //else nothing
            }
            else if (data[i] == '}' && sbracket_counter == 1 && cbracket_counter > 0)
            {
                cbracket_counter--;
                if (cbracket_counter == 0)
                {
                    token_size++;
                }
            }
            // array
            else if (data[i] == '[' && cbracket_counter == 0)
            {
                sbracket_counter++;
                if (sbracket_counter == 1)
                {
                    token_arr[num_of_token].start = start_cursor;
                } // else nothing is counter > 1
            }
            else if (data[i] == ']' && cbracket_counter == 0 && sbracket_counter > 0)
            {
                sbracket_counter--;
                if (sbracket_counter == 0)
                {
                    token_arr[num_of_token].size = token_size; //
                    token_arr[num_of_token].end = i + 1;
                    i = token_arr[num_of_token].start + 1;
                    num_of_token++;
                    token_size = 0;
                } //else nothing
            }
            // 아래 두 벨류 토큰들은 어레이와 오브젝트 안에 있는지 밖에 있는지에 따라서 토크나이징을 할지 안할지 결정된다.
            // true false numeric
            else if ((data[i] == 't' || data[i] == 'f') || (isdigit(data[i]) || data[i] == '-'))
            { // Starts with t or f
                // check if it is primitive boolean type
                if (data[i] == 't' && data[i + 1] == 'r' && data[i + 2] == 'u' && data[i + 3] == 'e')
                {
                    if (data[i + 4] == ',' || data[i + 4] == ' ' || data[i + 4] == '\n' || data[i + 4] == '\t')
                    {
                        is_primitive = 1;
                        end_cursor = i + 4;
                    }
                }
                else if (data[i] == 'f' && data[i + 1] == 'a' && data[i + 2] == 'l' && data[i + 3] == 's' && data[i + 4] == 'e')
                {
                    if (data[i + 5] == ',' || data[i + 5] == ' ' || data[i + 5] == '\n' || data[i + 5] == '\t')
                    {
                        is_primitive = 1;
                        end_cursor = i + 5;
                    }
                }
                else
                    is_primitive = 0;
                //numeric
                if ((isdigit(data[i]) || data[i] == '-') && is_primitive == 0)
                {
                    int t = 0; // 0 - int , 1 - double, 2 - exponent
                    // int n = 0; // negative or not
                    // if (data[i] == '-') n = 1; //is negative
                    for (int j = start_cursor;; j++)
                    {
                        if (data[j] == ' ' || data[j] == '\n' || data[j] == ',' || data[j] == '\t')
                        {
                            end_cursor = j;
                            is_primitive = 1;
                            break;
                        }
                    }
                }
                if (is_primitive == 1)
                {
                    //just value
                    if (cbracket_counter == 0 && sbracket_counter == 0)
                    {
                        token_arr[num_of_token].start = start_cursor;
                        token_arr[num_of_token].end = end_cursor;
                        token_arr[num_of_token].size = 0;
                        token_arr[num_of_token].type = PRIMITIVE; //is PRIMITIVE
                        num_of_token++;
                        i = end_cursor;
                    }
                    // if it is in array only token size ++
                    else if (cbracket_counter == 0 && sbracket_counter == 1)
                    {
                        if (((data[start_cursor - 2] != ':') || (data[start_cursor - 3] != ':')))
                        {
                            i = end_cursor;
                            token_size++;
                        } // else nothing
                    }
                }
            }
        }
    }
    return num_of_token;
}

void menu(int num_of_t, int num_of_c, tok_t *t_arr, char *data, country_t *c_arr)
{
    ABCD(c_arr, num_of_c);

    int option;

    while (1)
    {
        //system("clear");
        printf("\n----------------------Menu--------------------------");
        printf("\n\nChoose the information you would like to see");
        printf("\n\t 1 : Display the parsed tokens");
        printf("\n\t 2 : Search country information by country names");
        printf("\n\t 3 : List the country names according to the continent");
        printf("\n\t 4 : List country names according to GDP ranking");
        printf("\n\t 5 : Test your Knowledge (Quiz)");
        printf("\n\t 0: Quit the application");
        printf("\n");
        printf("---------------------------------------------------\n");

        printf(": ");
        scanf("%d", &option);

        switch (option)
        {
        case 1: // Parser output
            // print out the token array
            print_array(num_of_t, t_arr, data);
            break;

        case 2: // Search Country Information
            Search_Country(num_of_c, c_arr);
            break;

        case 3: // Search Countries by Continent
            Search_Continent(num_of_c, c_arr);
            break;

        case 4: // GDP Rank
            rank(c_arr, num_of_c);
            break;
        case 5: // Quiz
            Quiz(num_of_c, c_arr);
            break;

        case 0: // Exit
            printf("Application is closed\n");
            return;

        default: // Wrong input
            printf("You have entered a wrong value\n");
            break;
        }
    }
}

// Search Informations by Country
void Search_Country(int num_of_c, country_t *c_arr)
{
    int b;
    while(1){
    printf("\n\nSelect Country Number \n[ 1.Argentina 2.Australia 3.Brazil 4.Canada 5.China 6.Cambodia 7.Egypt 8.Germany 9.Greece \n10.India 11.Indonesia 12.Japan 13.Korea 14.Mexico 15.New Zealand 16.Morocco 17.Portugal \n18.Peru 19.Republic of Turkey 20.Republic of Kazakhstan 21.South Africa 22.United Kingdom \n23.United States of America] \n 0.exit\n: ");

    scanf("%d", &b);

    if (b == 1)
        Print_Country(num_of_c, c_arr, "Argentina");

    else if (b == 2)
        Print_Country(num_of_c, c_arr, "Australia");

    else if (b == 3)
        Print_Country(num_of_c, c_arr, "Brazil");

    else if (b == 4)
        Print_Country(num_of_c, c_arr, "Canada");

    else if (b == 5)
        Print_Country(num_of_c, c_arr, "China");

    else if (b == 6)
        Print_Country(num_of_c, c_arr, "Cambodia");

    else if (b == 7)
        Print_Country(num_of_c, c_arr, "Egypt");

    else if (b == 8)
        Print_Country(num_of_c, c_arr, "Germany");

    else if (b == 9)
        Print_Country(num_of_c, c_arr, "Greece");

    else if (b == 10)
        Print_Country(num_of_c, c_arr, "India");

    else if (b == 11)
        Print_Country(num_of_c, c_arr, "Indonesia");

    else if (b == 12)
        Print_Country(num_of_c, c_arr, "Japan");

    else if (b == 13)
        Print_Country(num_of_c, c_arr, "Korea");

    else if (b == 14)
        Print_Country(num_of_c, c_arr, "Mexico");

    else if (b == 15)
        Print_Country(num_of_c, c_arr, "New Zealand");

    else if (b == 16)
        Print_Country(num_of_c, c_arr, "Morocco");

    else if (b == 17)
        Print_Country(num_of_c, c_arr, "Portugal");

    else if (b == 18)
        Print_Country(num_of_c, c_arr, "Peru");

    else if (b == 19)
        Print_Country(num_of_c, c_arr, "Republic of Turkey");

    else if (b == 20)
        Print_Country(num_of_c, c_arr, "Republic of Kazakhstan");

    else if (b == 21)
        Print_Country(num_of_c, c_arr, "South Africa");

    else if (b == 22)
        Print_Country(num_of_c, c_arr, "United Kingdom");

    else if (b == 23)
        Print_Country(num_of_c, c_arr, "United States of America");
    else if(b ==0)
        break;

    else
        printf("Inappropriate Input.\n");
    }
}

void Print_Country(int num_of_c, country_t *c_arr, char *search)
{
    int country_no = 0;

    //find country;
    for (int i = 0; i <= num_of_c; i++)
    {
        if (strcmp(c_arr[i].country_name, search)==0)
            country_no = i;
    }
    //print out the country
    printf("\n");
    printf("\n------------------------------------------------------------\n");
    printf("Country you selected: %s\n", c_arr[country_no].country_name);
    printf("Capital: %s\nLanguage: ", c_arr[country_no].capital_name);
    for (int j = 0; c_arr[country_no].language[j][0] != '\0'; j++)
    {
        printf("%s, ", c_arr[country_no].language[j]);
    }
    printf("\nGDP: %f\n", c_arr[country_no].gdp);
    printf("Poplulation: %s\n", c_arr[country_no].population);
    printf("Currency: %s\n", c_arr[country_no].currency);
    printf("Continent: %s\nLegislature:\n", c_arr[country_no].continent);
    for (int j = 0; c_arr[country_no].legislature[j][0] != '\0'; j++)
    {
        printf("\t%s\n", c_arr[country_no].legislature[j]);
    }
      printf("------------------------------------------------------------\n");
}

//Search Country by Continent
void Search_Continent(int num_of_c, country_t *c_arr)
{
    int a = 0, b = 0;

    while(1){

    printf("\nSelect Continent Number \n[ 1.Asia 2.Europe 3.Austrailia 4.Africa 5.N/America 6.S/America 0.Exit ] : ");
    scanf("%d", &a);

    if (a == 1)
        Print_Continent(num_of_c, c_arr, "Asia");

    else if (a == 2)
        Print_Continent(num_of_c, c_arr, "Europe");

    else if (a == 3)
        Print_Continent(num_of_c, c_arr, "Australasia");

    else if (a == 4)
        Print_Continent(num_of_c, c_arr, "Africa");

    else if (a == 5)
        Print_Continent(num_of_c, c_arr, "North America");

    else if (a == 6)
        Print_Continent(num_of_c, c_arr, "South America");
    else if (a ==0)
        break;

    else
        printf("Inappropriate Input.\n");
    }
}

void Print_Continent(int num_of_c, country_t *c_arr, char *search)
{
    printf("\n------------------------------------------------------------\n");
    for (int i = 0; i <= num_of_c; i++)
    {
        if (!strcmp(c_arr[i].continent, search))
            printf("%s\n", c_arr[i].country_name);
    }
      printf("------------------------------------------------------------\n");
}

void Quiz(int num_of_c, country_t *c_arr)
{
    char answer[MAX_LIMIT];
    int number_of_quiz_question = 10;
    int score = 0;
    int num_check_array[num_of_c];

    // srand(time(NULL));

    for (int i = 0; i < num_of_c; i++)
    { // fill num_check_array
        num_check_array[i] = i;
    }

    for (int i = 0; i < num_of_c; i++)
    { // shuffle num_check_array
        int temp = num_check_array[i];
        int randomIndex = rand() % num_of_c;

        num_check_array[i] = num_check_array[randomIndex];
        num_check_array[randomIndex] = temp;
    }

    for (int i = 0; i < number_of_quiz_question; i++)
    {
        if(i==0){
            getchar();
        }
        int n = num_check_array[i];
        int q = rand() % 2 + 1;

        printf("\n%d. ", i + 1);

        if(q==1){
           
            printf("Which country has the capital %s?\n", c_arr[n].capital_name);
            fgets(answer, MAX_LIMIT, stdin);
            answer[strlen(answer) - 1] = '\0';     
            
            

            if (strcmp(answer, c_arr[n].country_name) == 0)
            {
                printf("Correct Answer!!\n");
                score++;
            }
            else
            {
                printf("Wrong Answer!!\n");
                printf("The correct answer is \"%s\".\n", c_arr[n].country_name);
            }
        }
        if(q==2){
            //fflush(stdin);
            printf("What is the capital of %s?\n", c_arr[n].country_name);
            fgets(answer, MAX_LIMIT, stdin);
            answer[strlen(answer) - 1] = '\0'; 

           

            if (strcmp(answer, c_arr[n].capital_name) == 0)
            {
                printf("Correct Answer!!\n");
                score++;
            }
            else
            {
                printf("Wrong Answer!!\n");
                printf("The correct answer is \"%s\".\n", c_arr[n].capital_name);
            }
        }
    }
    printf("\n ******************");
    printf("\n\nYour score is %d", score);
    printf("\n ******************\n\n");
    
    return;
}

void ABCD(country_t *ctr, int n)
{
    country_t *rk = (country_t *)malloc(sizeof(country_t) * n);
    for (int i = 0; i < n; i++)
    {
        rk[i] = ctr[i];
    }

    //sort by abc
    sortABC(rk, n);

    //print
    printf("     ----------Country List----------    \n");
    for (int i = 0; i < n; i++)
    {
        printf("     %s\n", rk[i].country_name);
    }
    free(rk);
}

/**
 * Function rank
 * definition: rank the tokeny array in GDP and print the result
 * **/
void rank(country_t *ctr, int n)
{
    //copy the array not to influence the original array
    country_t *rk = (country_t *)malloc(sizeof(country_t) * n);
    for (int i = 0; i < n; i++)
    {
        rk[i] = ctr[i];
    }
    // printRank(rk, n);
    //sort
    sortGDP(rk, n);

    //print
    printRank(rk, n);

    free(rk);
}

/**
 * Functoin printRank
 * definition: print the GDP rank array
 * **/
void printRank(country_t *rk, int n)
{
    printf("     ----------Country Rank----------    \n");
    printf("    Rank : Country : GDP\n");
    for (int i = 0; i < n; i++)
    {
        printf("    %2d  : %8s : %10lf\n", i + 1, rk[i].country_name, rk[i].gdp);
    }
}

//insertionsort by GDP
void sortGDP(country_t *ctr, int n)
{
    int i, j;
    country_t key;
    for (i = 1; i < n; i++)
    {
        key = ctr[i];
        j = i - 1;
        /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
        while (j >= 0 && ctr[j].gdp < key.gdp)
        {

            ctr[j + 1] = ctr[j];
            j = j - 1;
        }
        ctr[j + 1] = key;
    }
}

//insertionsort by ABC
void sortABC(country_t *ctr, int n)
{
    int i, j;
    country_t key;
    for (i = 1; i < n; i++)
    {
        key = ctr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */

        while (j >= 0 && strcmp(key.country_name, ctr[j].country_name) < 0)
        {
            ctr[j + 1] = ctr[j];
            j = j - 1;
        }
        ctr[j + 1] = key;
    }
}
