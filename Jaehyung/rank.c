#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *country_name;
    char *capital_name;
    char language[4][30];
    double gdp;
    char *population;
    char *currency;
    char legislature[6][30];
    char *continent;
} country_t;

#define NUM_CTR 10
void rank(country_t* ctr, int n);
void printRank(country_t *rk, int n);
void sortABC(country_t *ctr, int n);
void sortGDP(country_t *ctr, int n);



int main(){
    country_t ctr[NUM_CTR];

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
    printf("     Country     \n");
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

        printf("    Rank : Country : GDP\n");
    for(int i = 0 ; i <n; i ++){
        printf("    %2d  : %8s : %10d", i + 1, rk[i].country_name, rk[i].gdp);
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
        while (j >= 0 && strcmp(ctr[i].country_name, key.country_name) > 0)
        {
            ctr[j + 1] = ctr[j];
            j = j - 1;
        }
        ctr[j + 1] = key;
    }
}