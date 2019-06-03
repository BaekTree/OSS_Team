#include "appFunc.h"
void Quiz(country_t *country)
{

    char answer[50];

    int number_of_quiz_question = 10;
    int num = 23;
    int score = 0;

    srand(time(NULL));

    int *array = (int *)malloc(sizeof(int *) * num);

    for (int i = 0; i < num; i++)
    { // fill array
        array[i] = i;
    }

    for (int i = 0; i < num; i++)
    { // shuffle array
        int temp = array[i];
        int randomIndex = rand() % num;

        array[i] = array[randomIndex];
        array[randomIndex] = temp;
    }

    for (int i = 0; i < number_of_quiz_question; i++)
    {

        int n = array[i];
        int q = rand() % 2 + 1;

        printf("%d. ", i + 1);

        if (q == 1)
        {
            printf("Which country has the capital %s?\n", country[n].capital_name);
            scanf("%s", answer);

            if (strcmp(answer, country[n].country_name) != 0)
            {
                printf("Correct Answer!!\n");
                score++;
            }
            else if (strcmp(answer, "quit") != 0)
            {
                break;
            }
            else
            {
                printf("Wrong Answer!!\n");
            }
        }
        if (q == 2)
        {
            printf("What is the capital of %s?\n", country[n].country_name);
            scanf("%s", answer);

            if (strcmp(answer, country[n].capital_name) != 0)
            {
                printf("Correct Answer!!\n");
                score++;
            }
            else if (strcmp(answer, "quit") != 0)
            {
                break;
            }
            else
            {
                printf("Wrong Answer!!\n");
            }
        }
    }
    fflush(stdin);
    printf("\n\nYour score is %d", score);
    free(array);
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
    printRank(rk,n);

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