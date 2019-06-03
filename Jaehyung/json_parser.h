typedef enum {
    UNDEFINED = 0, 
    OBJECT = 1, 
    ARRAY = 2, 
    STRING = 3, 
    PRIMITIVE = 4
} type_t;

typedef struct {
    type_t type; // Token type
    int start; // Token start position
    int end;  // Token end position
    int size; // Number of child (nested) tokens
} tok_t;

typedef struct {
    char country_name[128];
    char capital_name[128];
    char language[8][64];
    double gdp;
    char population[32];
    char currency[4];
    char legislature[8][64];
    char continent[32];
} country_t;