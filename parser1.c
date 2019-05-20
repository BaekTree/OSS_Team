#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    const int maxBufLen = 255;
    char buffer[maxBufLen];
    const int maxDataLen = 255;
    // char data[maxDataLen];
    // char *data = (char *)malloc(maxDataLen * sizeof(char));
    char *data = (char *)malloc(maxDataLen * sizeof(char));

    
    //file open
    fp = fopen("test.json", "r");
    int length = 0;

    while (fscanf(fp, "%s", buffer) > 0)
    {
        data = (char *) realloc(data, strlen(data) + strlen(buffer));
        if (length > 1) {
            strcat(data, " ");
            strcat(data, buffer);
        }
        else {
            strcpy(data, buffer);
        }
        length += strlen(buffer) + 1;
    }

    length = strlen(data);
    // printf("The length of string is : %d\n", length);
    // printf("The string is : \n%s\n", data);
    fclose(fp);

    for (int i = 0; i <= length; i++) {
        if (i < 1) { //check if the beggining of the file is {
            if (data[i] != '{') {
                printf(".json file should begin with { \n");
                return 0;
            }
        }
    }





    printf("End of Program\n");

    return 0;
}

