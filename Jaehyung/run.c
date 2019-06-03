#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "json_parser.h"

// typedef struct
// {
//     char country_name[30];
//     char capital_name[30];
//     char language[10][30]; 
//     double gdp;            
//     char population[30];
//     char currency[5];
//     char legislature[10][30]; 
//     char continent[30];
// } country_t;
// #define NUM_CTR 30

void Options();
void sortABC(country_t *ctr, int n);
void sortGDP(country_t *ctr, int n);
void printRank(country_t *rk, int n);
void rank(country_t* ctr, int n);
void ABCD(country_t* ctr, int n);
void Quiz(country_t *country, int n);
void Search_Continent(country_t *cty, char *search);
void Search_Country(country_t *cty, char *search);

#if 0
int main(){

    //***********************************Test Dummies********************************//
    // country_t *test;
    // test = (country_t *)malloc(sizeof(country_t) * 30);
    // char str[20];

    // for (int i = 0; i < 30; i++){
    //     sprintf(str, "%d", i);

    //     strcpy(test[i].country_name, "country_name ");
    //     strcat(test[i].country_name, str);

    //     strcpy(test[i].capital_name, "capital_name ");
    //     strcat(test[i].capital_name, str);

    //     strcpy(test[i].continent, "continent ");
    //     strcat(test[i].continent, str);

    //     strcpy(test[i].currency, "CUR");

    //     strcpy(test[i].population, "population ");
    //     strcat(test[i].population, str);

    //     test[i].gdp = i + 10000.123;
    //     memset(str, 0, sizeof str);
    // }

    // printf("%s\n", test[0].country_name);

    // for (int i = 0; i < 30; i++) {
    //     printf("%s\n", test[i].country_name);
    //     printf("%s\n", test[i].capital_name);
    //     printf("%s\n", test[i].continent);
    //     printf("%s\n", test[i].currency);
    //     printf("%s\n", test[i].population);
    //     printf("%f\n", test[i].gdp);
    // }
    //***********************************Test Dummies set done********************************//

    int option;
    char Input[100];

    
    int i=0;

    while(1){
        system("cls");
        printf("\n\nChoose the information you would like to see");
        printf("\n\t 1 : List the country names according to the continent");
        printf("\n\t 2: List the information of a country");
        printf("\n\t 3 : List the countries according to the GDP");
        printf("\n\t 4 : Test your Knowledge (Quiz)");
        printf("\n\t 0: Quit the application");
        printf("\nYour Input: ");
        
	    scanf("%d", &option);

        switch(option){
            case 1: 
                printf("Enter the name of the continent you would like to see\n");
                scanf("%s", Input);
                Search_Continent(test,Input);
                // CountryNamesList(Input);
                break;

            case 2:
                 printf("Enter the country name you would like to see\n");
                scanf("%s", Input);
                Search_Country(test,Input);
                // CountryInformation(Input);
                 break;

            case 3: 
                rank(test,NUM_CTR);
                break;

            case 4: 
                Quiz(test);
                break;

            case 0:
                printf("Application is closed\n"); 
                exit(0);

            default: 
                printf("You have entered a wrong value\n"); 
                break;

        }
    }


    return 1;
}
#endif
void Options(){
	
    int option;
    char Input[100];

    
    int i=0;
	
    printf("\n\nChoose the information you would like to see");
    printf("\n\t 1 : List the country names according to the continent");
	printf("\n\t 2: List the information of a country");
	printf("\n\t 3 : List the countries according to the GDP");
	printf("\n\t 4 : Test your Knowledge (Quiz)");
    printf("\n\t 0: Quit the application");
	printf("\n");
    
    while(1){
	    scanf("%d", &option);

        switch(option){
            case 1: 
                printf("Enter the name of the continent you would like to see\n");
                scanf("%s", Input);
                // CountryNamesList(Input);
                break;

            case 2:
                 printf("Enter the country name you would like to see\n");
                scanf("%s", Input);
                //CountryInformation(Input);
                 break;

            case 3: 
                
                break;

            case 4: 
                // Quiz();
                break;

            case 0:
                printf("Application is closed\n"); 
                exit(0);

            default: 
                printf("You have entered a wrong value\n"); 
                break;

        }
        char next;
        scanf("Enter any key to proceed: %c",&next);
    }
}



void Search_Continent(country_t *cty, char *search)
{

    for (int i = 0; i < 24; i++)
    {
        if (!strcmp(cty[i].continent,search))
            printf("%s\n", cty[i].country_name);
    }
}


void Search_Country(country_t *cty, char *search)
{
    for (int i = 0, j = 0; i < 24; i++)
    {
        if (!strcmp(cty[i].country_name,search)){
            printf("Country You Selected: %s \nCapital: %s \nLanguage:", cty[i].country_name, cty[i].capital_name);
        while (cty[i].language[j + 1] != "\n")
        {
            printf(" %s /", cty[i].language[j]);
            j++;
        }
        j = 0;
        printf("\ngdp: %e /nPopulation: %s \nCurrency: %s \nLegislature:", cty[i].gdp, cty[i].population, cty[i].currency);
        while (cty[i].legislature[j + 1] != "\n")
        {
            printf(" %s /", cty[i].legislature[j]);
            j++;
        }
        printf("\nContinent: %s", cty[i].continent);
        break;
        }
    }
}

#if 0
int main()
{
    country_t *cty;
    int a = 0, b = 0;
    //0. save tokens into "country" structure.

    
    //1. Search Country by Continent
    printf("\nSelect Continent Number \n[ 1.Asia 2.Europe 3.Austrailia 4.Africa 5.N/America 6.S/America ] : ");
    scanf("%d", &a);

    if (a == 1)
        Search_Continent(cty, "Asia");

    else if (a == 2)
        Search_Continent(cty, "Europe");

    else if (a == 3)
        Search_Continent(cty, "Australia");

    else if (a == 4)
        Search_Continent(cty, "Africa");

    else if (a == 5)
        Search_Continent(cty, "North America");

    else if (a == 6)
        Search_Continent(cty, "South America");

    else
        printf("Inappropriate Input.\n");

    //2. Search Informations by Country
    printf("\n\nSelect Country Number \n [ 1.Argentina 2.Australia 3.Brazil 4.Canada 5.China 6.Cambodia 7.Egypt 8.Germany 9.Greece \n10.India 11.Indonesia 12.Japan 13.Korea 14.Mexico 15.New Zealand 16.Morocco 17.Portugal \n18.Peru 19.Republic of Turkey 20.Republic of Kazakhstan 21.South Africa 22.United Kingdom \n23.United States of America] \n: ");
    scanf("%d", &b);

    if (b == 1)
        Search_Country(cty, "Argentina");

    else if (b == 2)
        Search_Country(cty, "Australia");

    else if (b == 3)
        Search_Country(cty, "Brazil");

    else if (b == 4)
        Search_Country(cty, "Canada");

    else if (b == 5)
        Search_Country(cty, "China");

    else if (b == 6)
        Search_Country(cty, "Cambodia");

    else if (b == 7)
        Search_Country(cty, "Egypt");

    else if (b == 8)
        Search_Country(cty, "Germany");

    else if (b == 9)
        Search_Country(cty, "Greece");

    else if (b == 10)
        Search_Country(cty, "India");

    else if (b == 11)
        Search_Country(cty, "Indonesia");

    else if (b == 12)
        Search_Country(cty, "Japan");

    else if (b == 13)
        Search_Country(cty, "Korea");

    else if (b == 14)
        Search_Country(cty, "Mexico");

    else if (b == 15)
        Search_Country(cty, "New Zealand");

    else if (b == 16)
        Search_Country(cty, "Morocco");

    else if (b == 17)
        Search_Country(cty, "Portugal");

    else if (b == 18)
        Search_Country(cty, "Peru");

    else if (b == 19)
        Search_Country(cty, "Republic of Turkey");

    else if (b == 20)
        Search_Country(cty, "Republic of Kazakhstan");

    else if (b == 21)
        Search_Country(cty, "South Africa");

    else if (b == 22)
        Search_Country(cty, "United Kingdom");

    else if (b == 23)
        Search_Country(cty, "United States of America");

    else
        printf("Inappropriate Input.\n");

    //3. Rank Countries(TOP5) by gdp/Population

    //4. Capital Quiz
}
#endif


void Quiz(country_t *country, int n){
    
    char answer[50];

    int number_of_quiz_question = 10;
    int num = n;
    int score = 0;

    srand(time(NULL));

    int* array = (int*)malloc(sizeof(int*)*num);

    for (int i = 0; i < num; i++)
    { // fill array
        array[i] = i;
    }

    for (int i = 0; i < num; i++)
    { // shuffle array
        int temp = array[i];
        int randomIndex = rand() % num;

        array[i]  = array[randomIndex];
        array[randomIndex] = temp;
    }


    for(int i=0; i<number_of_quiz_question; i++){
        
        int n = array[i];
        int q= rand()%2+1;

        printf("%d. ", i+1);

        if(q==1){
            printf("Which country has the capital %s?\n", country[n].capital_name);
            scanf("%s", answer);

            if(strcmp(answer, country[n].country_name)!=0){
                printf("Correct Answer!!\n");
                score++;
            }
            else if(strcmp(answer, "quit")!=0){
                break;
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
            }else if(strcmp(answer, "quit")!=0){
                break;
            }
            else{
                printf("Wrong Answer!!\n");
            }
        }

    }
    fflush(stdin);
    printf("\n\nYour score is %d", score);
    free(array);
}


void ABCD(country_t* ctr, int n){
    country_t* rk = (country_t *)malloc(sizeof(country_t)*n);
    for(int i = 0 ; i < n ; i ++){
        rk[i] = ctr[i];
    }

    //sort by abc
    sortABC(rk, n);

    //print
    printf("     ----------Country List----------    \n");
    for(int i = 0 ; i < n ; i ++){
        printf("     %s\n",rk[i].country_name);
    }
    free(rk);
}


/**
 * Function rank
 * definition: rank the tokeny array in GDP and print the result
 * **/
void rank(country_t* ctr, int n){
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", ctr[i].country_name);
        // printf("%s\n", ctr[i].capital_name);
        // for (int j = 0; ctr[i].language[j][0] != '\0'; j++)
        // {
        //     printf("%s\n", ctr[i].language[j]);
        // }
        // printf("%f\n", ctr[i].gdp);
        // printf("%s\n", ctr[i].population);
        // printf("%s\n", ctr[i].currency);
        // printf("%s\n", ctr[i].continent);
        // for (int j = 0; ctr[i].legislature[j][0] != '\0'; j++)
        // {
        //     printf("%s\n", ctr[i].legislature[j]);
        // }
    }
    printf("/////////////////////////////////////////////////\n");
    //copy the array not to influence the original array
    country_t* rk = (country_t *)malloc(sizeof(country_t)*n);
    for(int i = 0 ; i < n ; i ++){
        rk[i]=ctr[i];
        printf("    %2d  : %8s : %10lf\n", i + 1,ctr[i].country_name, ctr[i].gdp);
    }
    // printRank(rk, n);
    //sort
    sortGDP(rk,n);
    
    //print
    printRank(rk,n);

    free(rk);
}

/**
 * Functoin printRank
 * definition: print the GDP rank array
 * **/
void printRank(country_t *rk, int n){
    printf("     ----------Country Rank----------    \n");
    printf("    Rank : Country : GDP\n");
    for(int i = 0 ; i <n; i ++){
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
        while (j >= 0 && ctr[i].gdp > key.gdp)
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
        
        while (j >= 0 && strcmp( key.country_name, ctr[i].country_name ) > 0)
        {
            ctr[j + 1] = ctr[j];
            j = j - 1;
        }
        ctr[j + 1] = key;
    }
}