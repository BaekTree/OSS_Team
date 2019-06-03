#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char country_name[30];
    char capital_name[30];
    char language[10][30]; 
    double gdp;            
    char population[30];
    char currency[5];
    char legislature[10][30]; 
    char continent[30];
} country_t;

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