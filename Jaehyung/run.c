#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char country_name[30];
    char capital_name[30];
    char language[10][30];
    double gdp;
    char population[30];
    char currency[4];
    char legislature[10][30];
    char continent[30];
} country_t;

#define NUM_CTR 30
void rank(country_t* ctr, int n);
void printRank(country_t *rk, int n);
void sortABC(country_t *ctr, int n);
void sortGDP(country_t *ctr, int n);
void ABCD(country_t* ctr, int n);
void Quiz(country_t *country);
void Options();




int main(){

country_t *test;
    test = (country_t *)malloc(sizeof(country_t) * 30);
    char str[20];

    for (int i = 0; i < 30; i++){
        sprintf(str, "%d", i);

        strcpy(test[i].country_name, "country_name ");
        strcat(test[i].country_name, str);

        strcpy(test[i].capital_name, "capital_name ");
        strcat(test[i].capital_name, str);

        strcpy(test[i].continent, "continent ");
        strcat(test[i].continent, str);

        strcpy(test[i].currency, "CUR");

        strcpy(test[i].population, "population ");
        strcat(test[i].population, str);

        test[i].gdp = i + 10000.123;
        memset(str, 0, sizeof str);
    }

    // printf("%s\n", test[0].country_name);

    for (int i = 0; i < 30; i++) {
        printf("%s\n", test[i].country_name);
        printf("%s\n", test[i].capital_name);
        printf("%s\n", test[i].continent);
        printf("%s\n", test[i].currency);
        printf("%s\n", test[i].population);
        printf("%f\n", test[i].gdp);
    }


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
	    scanf(" %c", &option);

        switch(option){
            case 1: 
                printf("Enter the name of the continent you would like to see\n");
                scanf("%s", &Input);
                //CountryNamesList(Input);
                break;

            case 2:
                 printf("Enter the country name you would like to see\n");
                scanf("%s", &Input);
                //CountryInformation(Input);
                 break;

            case 3: 
                
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

    // ctr[0].country_name="korea";
    // ctr[0].gdp=10;

    // ctr[1].country_name="japan";
    // ctr[1].gdp = -10;

    ABCD(test,NUM_CTR);
    rank(test,NUM_CTR);
    //GDP rank
    /**
     * 국가를 정렬. 
     *  
     * countreis array: country_t
     * number of countreis: NUM_CTR.
     * 
     * 
     * sorting 할 기준:
     *  ctr[i].gdp
     * 
     * **/

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

    //copy the array not to influence the original array
    country_t* rk = (country_t *)malloc(sizeof(country_t)*n);
    for(int i = 0 ; i < n ; i ++){
        rk[i]=ctr[i];
    }
    
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
	    scanf(" %d", &option);

        switch(option){
            case 1: 
                printf("Enter the name of the continent you would like to see\n");
                scanf("%s", &Input);
                //CountryNamesList(Input);
                break;

            case 2:
                 printf("Enter the country name you would like to see\n");
                scanf("%s", &Input);
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
    }
}

void Quiz(country_t *country){
    
    char answer[50];

    int number_of_quiz_question = 10;
    // int NUM_CTR = 18;
    int score = 0;

    srand(time(NULL));

    int array[NUM_CTR];

    for (int i = 0; i < NUM_CTR; i++) {     // fill array
    array[i] = i;
    }


    for (int i = 0; i < NUM_CTR; i++) {    // shuffle array
        int temp = array[i];
        int randomIndex = rand() % NUM_CTR;

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
    printf("\n\nYour score is %d", score);
    
}
