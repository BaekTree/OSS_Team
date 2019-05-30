#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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