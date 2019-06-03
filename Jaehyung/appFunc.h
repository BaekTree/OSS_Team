#ifndef APPFUNC
#define APPFUNC

#include "json_parser.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Options();
void sortABC(country_t *ctr, int n);
void sortGDP(country_t *ctr, int n);
void printRank(country_t *rk, int n);
void rank(country_t *ctr, int n);
void ABCD(country_t *ctr, int n);
void Quiz(country_t *country);
void Search_Continent(country_t *cty, char *search);
void Search_Country(country_t *cty, char *search);


#endif