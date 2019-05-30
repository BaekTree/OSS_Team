1. randome information
2. 

정보: <br>
국가의 이름,<br>
언어,<br>
GDP,<br>
인구,<br>
정치,<br>
대륙

* data array: 토큰들의 시작과 끝
```
int Asia[] = {, , , }//index from the token array
int NAmerica[] = {}
int SAmerica[]
int Europe[]
int Africa[]
int Aust[]

int aisa, na, sa, eu, af, au = 0 all of them

//initialize each cont array
for index: 0 to size of tok_t array
    if strcmp tok_t_array[index] , "Asia"
        Asia[as] = index
        as++
    if strcmp tok_t_array[] , "NAmerica"
        NAmerica[na] = index
        na++
    if other continents...
        array[] = index
        array_idx++
    index++       
```
## Scenario 1: show continent list and the number
* show continent list and the number
```
    scanf country name
```
* put list number: North America
```   
    1: north america
```
* show list of North America countries
```
    if input = North America
            for index : 0 to as
                printf tok_array[Asia[index]] // name of the country
                printf tok_array[Asia[index] + 1 ]// object
```

## Scenario 2:search county
* ask the country
    scanf country_name
* int** countryList = {Asia, northAmerica, Aus,South America, Europe}
```
    #define numCont = 6
    int** countryList = {Asia, northAmerica, Aus,South America, Europe}
    for index : 0 to numCont
        for j : 0 to sizeof(countryList+index)/sizeof((countryList+index)[0]))
            if *(countyList + index)[j] = country_name
                break;
```
* show info of the counrty
```
    printf countryList[index][j]    //name of the cournty
    printf counrtyList[index][j + 1]    //the object of the counrty
```

## Scenario 3: Rank GDP or population
* figure out the GDP token index
```
countryList[i][j]
instead of J, following values points other toknes index...
countryList[i][j] + 1 //object
countryList[i][j] + 2 // capital
countryList[i][j] + 3 // capital value
countryList[i][j] + 4 // language
countryList[i][j] + 5 // language value array
countryList[i][j] + 5 + size_of_array // language value array value
countryList[i][j] + 5 + size_of_array + 1// GDP
countryList[i][j] + 5 + size_of_array + 1 + 1//GDP value
```
* creating GDP array to sort
```
#define GDP_INDEX = 5 + size_of_array + 1 + 1

struct GDP{
    int gdp
    int cont
    int cons
}

for index : 0 to numCont
    totalCountriesNum += sizeof(countryList+index)/sizeof((countryList+index)[0])

int GDP_ARR[totalCountriesNum]  //by dynamic allocation in practice

int k = 0
for i : 0 to numCont
    for j : 0 to sizeof(countryList + i)/sizeof((countryList + i)[0])
        GDP_ARR[k].gdp = countryList[i][j] + GDP_INDEX
        GDP_ARR[k].cont = i
        GDP_ARR[k++].gdp = j 
        
```
* sort GDP array: whatever sort algorithm

* print
```
for i : 0 to totalCountriesNum
    printf GDP[i].gdp, countryList[GDP[i].cons][[GDP[j].cons]]
```






struct America

Choose countries