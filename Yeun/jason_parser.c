#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TOKEN_COUNT 1024

typedef enum {
    UNDEFINED = 0,
    OBJECT = 1,
    ARRAY = 2,
    STRING = 3,
    PRIMITIVE = 4
}type_t;

typedef struct {
    type_t type;
    int start;
    int end;
    int size;
    char *string;
}tok_t;

typedef struct _JSON{
    tok_t tokens[TOKEN_COUNT];
} JSON;

void array_parse(char*, JSON*, int*, int*); //array parsing function
void object_parse(char*, JSON*, int*, int*); //object parsing function

char* readfile(char* filename, int* filesize)
{
    FILE* fp = fopen(filename, "r");
    if (fp ==  NULL){
        return NULL;
    }

    int size;
    char* buffer;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buffer = (char*)malloc(size+1);
    memset(buffer, 0, size+1);

    if(fread(buffer,1, size, fp)<1){
        *filesize = 0;
        free(buffer);
        fclose(fp);
        return NULL;
    }

    *filesize = size;
    fclose(fp);
    return buffer;
}

void array_parse(char *doc, JSON *json, int *startPos, int *startTokenInx)
{
    int pos = *startPos;
    int tokenInx = *startTokenInx;
    int s, e;
    int arraytokenInx = tokenInx;        
    json->tokens[tokenInx].type = ARRAY;   
    tokenInx++;                            
    s = pos;                                
    json->tokens[arraytokenInx].start = s; 
    int arrSize = 0;
    while (doc[pos] != ']')
    { 
        pos++;
        switch (doc[pos])
        {
        case '"':
            arrSize++;                              
            json->tokens[tokenInx].type = STRING; 
            s = pos + 1;                            
            json->tokens[tokenInx].start = s;     
            while (doc[pos + 1] != '"'){
                pos++;
            }
            e = ++pos;                        
            json->tokens[tokenInx].end = e;  
            json->tokens[tokenInx].size = 0; 
            json->tokens[tokenInx].string = (char *)malloc(e - s + 1);
            memset(json->tokens[tokenInx].string, 0, e - s + 1);
            memcpy(json->tokens[tokenInx].string, doc + s, e - s);
            tokenInx++; //increase tokenInx for element found insdie array
            break;

        case '[':
            arrSize++;
            array_parse(doc, json, &pos, &tokenInx);
            break;

        case '{':
            arrSize++;
            object_parse(doc, json, &pos, &tokenInx);
            break;

	case '-': case '0': case '1': case '2':
        case '3': case '4': case '5': case '6':
        case '7': case '8': case '9': case 't':
        case 'f': case 'n':
            arrSize++;
            json->tokens[tokenInx].type = PRIMITIVE;
            s = pos;
            json->tokens[tokenInx].start = s;
            while (doc[pos + 1] != ','){
                if (doc[pos + 1] == '\n') break;
                else pos++;
            }
            e = ++pos; // the word ends when doc[pos] meets ',' or NULL
            json->tokens[tokenInx].end = e;
            json->tokens[tokenInx].size = 0;
            json->tokens[tokenInx].string = (char *)malloc(e - s + 1);
            memset(json->tokens[tokenInx].string, 0, e - s + 1);
            memcpy(json->tokens[tokenInx].string, doc + s, e - s);
            pos++;
            tokenInx++;
            break;

        default:
            break;
        }
    }
    e = ++pos;
    json->tokens[arraytokenInx].end = e;
    json->tokens[arraytokenInx].size = arrSize;
    json->tokens[arraytokenInx].string = (char *)malloc(e - json->tokens[arraytokenInx].start + 1);
    memset(json->tokens[arraytokenInx].string, 0, e - json->tokens[arraytokenInx].start + 1);
    memcpy(json->tokens[arraytokenInx].string, doc + json->tokens[arraytokenInx].start, e - json->tokens[arraytokenInx].start);
    *startTokenInx = tokenInx;
    *startPos = pos;
}

void object_parse(char *doc, JSON *json, int *startPos, int *startTokenInx)
{   
    int pos = *startPos;
    int tokenInx = *startTokenInx;
    int s, e;
    int objtokenInx = tokenInx; 
    json->tokens[tokenInx].type = OBJECT; 
    tokenInx++;                           
    s = pos;                                
    json->tokens[objtokenInx].start = s;  
    int objSize = 0;
    
    while (doc[pos] != '}')
    { 
        pos++;
        switch (doc[pos])
        {
        case '"':
            json->tokens[tokenInx].type = STRING;
            s = pos + 1;                          
            pos++;
            json->tokens[tokenInx].start = s;     
            while (doc[pos] != '"'){
                pos++;
            }
            e = pos;                         
            json->tokens[tokenInx].end = e;  
            json->tokens[tokenInx].size = 0; 
            while (doc[pos] != ':' && doc[pos] != '\n'){
                pos++;
            }
            if (doc[pos] == ':') json->tokens[tokenInx].size = 1;
            else objSize++;

            json->tokens[tokenInx].string = (char *)malloc(e - s + 1);
            memset(json->tokens[tokenInx].string, 0, e - s + 1);
            memcpy(json->tokens[tokenInx].string, doc + s, e - s);
            tokenInx++; //increase tokenInx for element found insdie array
            break;

	    case '[':
            objSize++;
            array_parse(doc, json, &pos, &tokenInx);
            break;

        case '{':
            objSize++;
            object_parse(doc, json, &pos, &tokenInx);
            break;          

        case '-': case '0': case '1': case '2':
        case '3': case '4': case '5': case '6':
        case '7': case '8': case '9': case 't':
        case 'f': case 'n':
            json->tokens[tokenInx].type = PRIMITIVE;
            s = pos;
            json->tokens[tokenInx].start = s;
            while (doc[pos + 1] != ','){
                if (doc[pos + 1] == '\n') break;
                else pos++;
            }
            objSize++;
            e = ++pos; // the word ends when doc[pos] meets ',' or NULL
            json->tokens[tokenInx].end = e;
            json->tokens[tokenInx].size = 0;
            json->tokens[tokenInx].string = (char *)malloc(e - s + 1);
            memset(json->tokens[tokenInx].string, 0, e - s + 1);
            memcpy(json->tokens[tokenInx].string, doc + s, e - s);
            pos++;
            tokenInx++;
            break;

        default:
            break;

        }
    }
    e = ++pos;
    json->tokens[objtokenInx].end = e;
    json->tokens[objtokenInx].size = objSize;
    //put doc[s]~doc[e+1] in token.string for the array
    json->tokens[objtokenInx].string = (char *)malloc(e - json->tokens[objtokenInx].start + 1);
    memset(json->tokens[objtokenInx].string, 0, e - json->tokens[objtokenInx].start + 1);
    memcpy(json->tokens[objtokenInx].string, doc + json->tokens[objtokenInx].start, e - json->tokens[objtokenInx].start);
    *startTokenInx = tokenInx;
    *startPos = pos;
}

void json_parse(char *doc, int size, JSON *json, int *b_cnt)
{
    int cnt = 0;
    int pos = 0; //for checking position in doc.
    int e,s; //ending, starting position for each token
    int tokenInx = 0; //Inx for token

    while(pos < size)
    {
        switch(doc[pos])
        {
            case '"':
            	json->tokens[tokenInx].type = STRING; // token.type is STRING
            	s = pos + 1;
            	pos++;                                   // the word starts after "
            	json->tokens[tokenInx].start = s;     // token.start = s
            	while (doc[pos] != '"'){ 
            	    pos++;
            	}

            	e = pos;                        // the word ends when doc[pos] meets ". (includes last ")
            	json->tokens[tokenInx].end = e; // token.end = e
            	json->tokens[tokenInx].size = 0; //if : is coming right after "" {size = 1}
            	while (doc[pos] != ':' && doc[pos] != '\n') {
            	    pos++;
            	}
            	if (doc[pos] != ':')
            	{ // else {size = 0}
            	    json->tokens[tokenInx].size = 1;
            	}
            	json->tokens[tokenInx].string = (char *)malloc(e - s + 1);
            	memset(json->tokens[tokenInx].string, 0, e - s + 1);
            	memcpy(json->tokens[tokenInx].string, doc + s, e - s);
	
                pos++;
           	tokenInx++;
           	break;

             
             case '[':
		array_parse(doc, json, &pos, &tokenInx);
                break;


	     case '{':
             	object_parse(doc, json, &pos, &tokenInx);
		break;

            case '-': case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case 't': case 'f': case 'n':
                json->tokens[tokenInx].type = PRIMITIVE;
                s = pos;
                json->tokens[tokenInx].start = s;
                while(doc[pos+1] != ',') { 
                    if(doc[pos+1] == '\n') break;
                    else pos++;
                }
                e = ++pos; 
                json->tokens[tokenInx].end = e;
                json->tokens[tokenInx].size = 0;
                json->tokens[tokenInx].string = (char *)malloc(e-s+1);
                memset(json->tokens[tokenInx].string, 0, e-s+1);
                memcpy(json->tokens[tokenInx].string, doc+s, e-s);
                pos++;
                tokenInx++;
                break;            

            default:
             pos++;
        }
    }
    *b_cnt = tokenInx;
}

void freeJson(JSON *json, int totalcnt){
    for (int i = 0; i<totalcnt; i++){
        if (json->tokens[i].type == STRING)
            free(json->tokens[i].string);
    }
}

void printResult(JSON *json, int totalcnt) {
    char *typetype;
    for(int i = 0; i<totalcnt; i++){
        if(json->tokens[i].type == 0) typetype = "JSMN_UNDEFINED";
        else if(json->tokens[i].type == 1) typetype = "JSMN_OBJECT";
        else if(json->tokens[i].type == 2) typetype ="JSMN_ARRAY";
        else if(json->tokens[i].type == 3) typetype ="JSMN_STRING";
        else typetype = "JSMN_PRIMITIVE";
        printf("[%02d] %s (size=%d, %d~%d, %s)\n", i, json->tokens[i].string, json->tokens[i].size, json->tokens[i].start, json->tokens[i].end, typetype);
    }
}

int main(int argc, char** argv)
{
    int filesize=0;
    char* doc = readfile(argv[1], &filesize);
    int totalcnt=0;

    if(doc == NULL){
        return -1;
    }

    JSON json = {0, };
    json_parse(doc, filesize, &json, &totalcnt);
    printResult(&json, totalcnt);
    freeJson(&json, totalcnt);
    return 0;
}