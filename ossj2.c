
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum tokenType
{
    STRING,
    NUMBER,
    BRACE
};
// typedef enum{
//     UNDEFINED = 0,
//     OBJECT = 1,
//     ARRAY = 2,
//     STRING = 3,
//     PRIMITIVE = 4
// } type_t;

typedef struct
{
    int start;
    int end;
    int size;
} tok_t;

tok_t arr[1024];
// tok_t* arr;

void braceRecursion(int tupleS, int tupleE, char *data, int *num);
int getColon(int tupleStart, int tupleEnd, char *data);
int NTokStart(int tupleStart, int colon, char *data);
int NTokEnd(int colon, int tokenStart, char *data);
int VTokStart(int colon, int tupleEnd, char *data, int *flag, int *braceStart);
int VTokEnd(int tokenStart, int tupleEnd, int *flag, char *data, int dataLen, int *braceE, int *index);
void braceRecursion(int tupleS, int tupleE, char *data, int *num);
void braceArr(int tupleS, int tupleE, char *data, int *num);

int main(int argc, char ** argv){
    char* fpName = argv[1];
    FILE* fpIn;
    FILE* fpOut;

    const int maxBufLen = 500;
    char buffer[maxBufLen];
    char data[maxBufLen];

    fpIn = fopen(fpName, "r");
    if(fpIn == NULL)
        printf("reading error\n");
    fpOut = fopen("test.json", "w");
    if(fpOut == NULL)
        printf("writing error\n");
 

//using strtok. But seems like required to have index in integer.
//shoud use the character loop.
    
    int len = 0;
    while (fgets(buffer, maxBufLen, fpIn) != NULL)
    {
        sprintf(data+len,"%s",buffer);
        len += strlen(buffer);
    }
    // int index = 0;
    // char* ptr = strtok(data,"\"");  //until the start of the name
    // index = strlen(ptr) ;   //2까지. 따옴표까지 넣어준다. 

//total data Len
    int dataLen = strlen(data);
//index consideration: start, comma, end
/**
 * 
 * abcd"efg"h:{ij"kl"},"mn"abc"nn"def",...
 * 012345678901234567890123456789
 * { "name"
 * 01234567
 * **/


//count the number of object
    // int count =0;
    // for (int i = 0; i < maxBufLen; i++){
    //     if(data[i] == ',')
    //         count ++;
    // }
    // count *= 2;
    // arr = (tok_t *)malloc(sizeof(tok_t) * count);


    /**
 * module 1
 * definition:
 *  from , to another ,
 *  the string becomes the tuple? a pair!
 * 
 * 
 * **/
    int index = 0;
    char *str = NULL;
    int num = 0;
    
    //extracting each pair
    str = strtok(data, ",");
/***********************************************************************/
    do{
        int tokS = 0 ,tokE = 0, tupleLen = 0, tupleEnd = 0,
            tupleStart = 0, colon = 0, braceS = 0,braceE = 0;

        tupleStart = index;
        tupleLen = strlen(str);
        tupleEnd = tupleStart + tupleLen;
        index = tupleEnd + 1;// include , and + 1 for new start
        //"   " : " "   ,______
        //              ㄴ쉼표까지 포함 함. 그 다음 index부터 다음 쉼표까지.


        /**
         * module 2-2
         *  functionize 1
         * **/


        //get colon index
        colon = getColon(tupleStart,tupleEnd,data);

        //get name token
        //n = tupleLen.
        //average under O(n).
        //worst case O(n).
        tokS = NTokStart(tupleStart, colon,data);
        tokE = NTokEnd(colon, tokS,data);

        //store name token
        arr[num].start = tokS;
        arr[num].end = tokE;
        arr[num].size = 1;
        num++;

        #if DEBUG
        printf("tokS: %d, tokE:%d ",tokS, tokE);
        for (int i = tokS; i < tokE; i++){
            printf("%c", data[i]);
        }
        printf("\n");

        #endif

/***********************************************************************/
        /**
         * module 2-3
         *  functionize 2
         * **/
        
        //get value toekn
        int flag;
        tokS = VTokStart(colon,tupleEnd,data,&flag,&braceS);
        tokE = VTokEnd(tokS,tupleEnd,&flag, data, dataLen,&braceE, &index);

       
        // printf("colon: %d, tokS: %d, tokE:%d\n",colon, tokS, tokE);
        //store value token
        arr[num].start = tokS;
        arr[num].end = tokE;
        arr[num].size = 0;
        if(flag == BRACE){
            int many = 0;
            for(int i = braceS; i < braceE; i++){
                if(data[i] == ',')
                    many++;
            }
            arr[num].size = many+1;

        }
        num++;
        
        #if DEBUG
        printf("tokS: %d, tokE:%d ",tokS, tokE);
        for (int i = tokS; i < tokE; i++){
            printf("%c", data[i]);
        }
        printf("\n");
        #endif

         /**
         * module 3
         *  recursion function
         * 
         * **/    
        if(flag == BRACE){
            if(data[braceS]=='{')
                braceRecursion(braceS, braceE,data,&num);
            else
                braceArr(braceS,braceE,data,&num);
        }

        if(index >= dataLen) break;
        str = strtok(data+index, ",");

    }while(str != NULL);

/***************************************************************************/

    //print out tokens
    printf("***** ALL TOKENS *****\n");
    printf("num %d\n", num);
    for (int j = 0; j < num; j++)
    {
        printf("[%3d] ",j);
        for (int i = arr[j].start; i < arr[j].end; i++){
            printf("%c", data[i]);
        }
        printf(" (size=%d, %d~%d)\n",arr[j].size,arr[j].start,arr[j].end);
    }
    fclose(fpOut);

    fclose(fpIn);
    printf("program done!\n");

    return 0;


}

int getColon(int tupleStart, int tupleEnd, char *data)
{
    //get colon index
    for (int i = tupleStart; i < tupleEnd; i++)
    {
        if (data[i] == ':')
        {
            return i;
        }
    }
}

//get colon index
int NTokStart(int tupleStart, int colon, char *data)
{
    for (int i = tupleStart; i < colon; i++)
    {
        if (data[i] == '\"')
        {
            return i + 1;
        }
    }
}

//get name token
//n = tupleLen.
//average under O(n).
//worst case O(n).
int NTokEnd(int colon, int tokenStart, char *data)
{
    for (int j = colon - 1; j >= tokenStart; j--)
    {
        if (data[j] == '\"')
        {
            return j;
            // break;
        }
    }
}

//get value toekn
//colon: start 1칸 전부터. 양끝을 포함하지 않는다.
int VTokStart(int colon, int tupleEnd, char *data, int *flag, int *braceStart)
{
    int tokenStart;
    for (int i = colon + 1; i < tupleEnd; i++)
    {

        if (data[i] == '{')
        {
            *braceStart = i;
            tokenStart = *braceStart;
            *flag = BRACE;
            data[tupleEnd] = ',';

            return tokenStart;
        }
#if 1
        if (data[i] == '[')
        {
            *braceStart = i;
            tokenStart = *braceStart;
            *flag = BRACE;
            data[tupleEnd] = ',';

            return tokenStart;
        }
#endif

        /**module 1**/

        if (data[i] == '\"')
        {
            tokenStart = i + 1;
            *flag = STRING;
            // break;
            return tokenStart;
        }

        if (data[i] >= '0' && data[i] <= '9')
        {
            *flag = NUMBER;
            tokenStart = i;
            return tokenStart;
            // break;
        }
    }
}

//when token is ... number, string, or object...
int VTokEnd(int tokenStart, int tupleEnd, int *flag, char *data,
            int dataLen, int *braceE, int *index)
{
    int tokenEnd;
    //when token is number
    if (*flag == NUMBER)
    {
        for (int k = tokenStart + 1; k <= tupleEnd; k++)
        {
            if (!(data[k] >= '0' && data[k] <= '9'))
            {
                tokenEnd = k;
                // break;
                return tokenEnd;
            }
        }
    }
    //when token is string
    else if (*flag == STRING)
    {
        for (int j = tupleEnd; j >= tokenStart; j--)
        {
            if (data[j] == '\"')
            {
                tokenEnd = j;
                return tokenEnd;
            }
        }
    }
    //WHEN token is object
    else if (*flag == BRACE)
    {
        char *str = NULL;
        int tupleLen;
        for (int j = tokenStart; j < dataLen; j++)
        {
            if (data[j] == '}')
            {

                tokenEnd = j + 1;
                *braceE = tokenEnd;
                str = strtok(data + *index, ",");

                tupleLen = strlen(str);
                tupleEnd += tupleLen + 1; //including ,
                *index = tupleEnd + 1;

                return tokenEnd;
            }

#if 1
            if (data[j] == ']')
            {
                tokenEnd = j + 1;
                *braceE = tokenEnd;
                str = strtok(data + *index, ",");

                tupleLen = strlen(str);
                tupleEnd += tupleLen + 1; //including ,
                *index = tupleEnd + 1;

                return tokenEnd;
            }
#endif
        }
    }
}

void braceArr(int tupleS, int tupleE, char *data, int *num)
{
    /**
     * 
     * [과 ] 의 index을 이미 알고 있다.
     * braceS과 braceE
     * braceS에서 braceE으로 이동.
     * ,갯수를 파악?
     * ,을 만나면... 
     * 맨 앞의 index와 ,의 인덱스 사이에서 ...
     * value을 만나면 되지 않나...
     * 
     * **/
    int tokS = tupleS, tokE = tupleS;
    int flag = 0;
    int braceS = 0, braceE = 0;
    int index = tupleS;
    for (int i = tupleS; i < tupleE; i++)
    {
        if (data[i] == ',' || data[i] == ']')
        {

            tokS = VTokStart(tokE, i, data, &flag, &braceS);
            tokE = VTokEnd(tokS, i, &flag, data, tupleE, &braceE, &index);

            arr[*num].start = tokS;
            arr[*num].end = tokE;
            arr[*num].size = 0;
            if (flag == BRACE)
            {
                int many = 0;
                for (int i = braceS; i < braceE; i++)
                {
                    if (data[i] == ',')
                        many++;
                }
                arr[*num].size = many + 1;
            }
            (*num)++;

            if (flag == BRACE)
            {
                braceRecursion(braceS, braceE, data, num);
            }

#if DEBUGARR
            printf("tokS: %d, tokE:%d ", tokS, tokE);
            for (int i = tokS; i < tokE; i++)
            {
                printf("%c", data[i]);
            }
            printf("\n");

#endif
        }
    }
}

void braceRecursion(int tupleS, int tupleE, char *data, int *num)
{
    // printf("\n\n\n in the recursion!\n\n\n");
    int indexB = tupleS;
    char *strRc = NULL;
    int dataLen = tupleE - tupleS;
    int len;
    int braceS = 0;
    int braceE = 0;
    int tokS = 0;
    int tokE = 0;
    int tupleEnd = 0;
    int tupleStart = 0;
    int colon = 0;
    strRc = strtok(data + tupleS, ",");
    // printf("------------recursion test------------\n");

    do
    {
        tupleStart = indexB;
        len = strlen(strRc);
        tupleEnd = tupleStart + len;
        indexB = tupleEnd + 1; // include , and + 1 for new start
        //"   " : " "   ,______
        //              ㄴ쉼표까지 포함 함. 그 다음 index부터 다음 쉼표까지.

        //get colon index
        colon = getColon(tupleStart, tupleEnd, data);

        //get name token
        //n = tupleLen.
        //average under O(n).
        //worst case O(n).
        tokS = NTokStart(tupleStart, colon, data);
        tokE = NTokEnd(colon, tokS, data);
        //store name token
        arr[*num].start = tokS;
        arr[*num].end = tokE;
        arr[*num].size = 1;
        (*num)++;
#if 0
        printf("tokS: %d, tokE:%d ",tokS, tokE);
        for (int i = tokS; i < tokE; i++){
            printf("%c", data[i]);
        }
        printf("\n");

        printf("recursion num: %d\n",*num);
#endif

        /***********************************************************************/
        /**
         * module 2-3
         *  functionize 2
         * **/

        //get value toekn
        int flag;
        tokS = VTokStart(colon, tupleEnd, data, &flag, &braceS);
        tokE = VTokEnd(tokS, tupleEnd, &flag, data, dataLen, &braceE, &indexB);

        /**
         * module 3
         *  recursion function
         * 
         * **/

        //store value token
        arr[*num].start = tokS;
        arr[*num].end = tokE;
        arr[*num].size = 0;
        if (flag == BRACE)
        {
            int many = 0;
            for (int i = braceS; i < braceE; i++)
            {
                if (data[i] == ',')
                    many++;
            }
            arr[*num].size = many + 1;
        }
        (*num)++;

#if DEBUG
        printf("tokS: %d, tokE:%d ", tokS, tokE);
        for (int i = tokS; i < tokE; i++)
        {
            printf("%c", data[i]);
        }
        printf("\n");
        printf("recursion num: %d\n", *num);

#endif

        if (flag == BRACE)
        {
            braceRecursion(braceS, braceE, data, num);
        }

        strRc = strtok(NULL, ",");
        // if(strRc == NULL)
        // printf("\n\n\n%s\n\n\n",strRc);
    } while (strRc != NULL);

#if 0
    printf("\n\n\n----------recursion Test---------\n");
    // printf("tokS: %d, tokE:%d ",tokS, tokE);
    for (int i = tupleS; i < tupleE; i++){
        printf("%c", data[i]);
    }
    printf("\n----------recursion Test---------\n\n\n");
#endif
    // printf("recursion num: %d\n",*num);

    // printf("recursion test done!\n-------------------\n");
}
