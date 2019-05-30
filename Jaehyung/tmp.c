#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char* lt1 = "lt1";
    char* lt2 = "lt2";
    char ar[10];

    printf("strcmp between literal: %d\n", strcmp(lt1, lt2));//work
    printf("strcmp between literal and array: %d\n", strcmp(lt1, ar));//work

    strcpy(lt1, lt2);//not work
    printf("strcpy bet literal: %s\n",lt1);
    strcpy(ar, lt1);//work
    printf("strcpy from literal to array: %s\n",ar);   
    strcpy(lt1, ar);//not work
    printf("strcpy from array to lt1: %s\n",lt1);

    printf("done!\n");

    
}