#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<ctype.h>  // for isspace()

#define maxInputChars 100

char symbols[5] = {'+', '-', '*', '/', '\0'};

struct numOf {
    char symbolName[16];
    int amountOfSymbol;
    int (*function)(int, int);
};

typedef struct {
    char key[32];
    char value[2];
    struct numOf symbol;
} keyValue;



void printKeyValue(keyValue[], int);
// void appendKeyValue(keyValue[], int*, char[], char[], struct numOf*);
void detectInput(char*, size_t);
int getMaxSet();
int countOccurences(char*, char);
void printRows(char (*)[2], int);

void printKeyValue(keyValue table[], int sizeCap) {
    for (int i = 0; i < sizeCap; i++) {
        printf("%s : %s\n", table[i].key,table[i].value);
    }
}
void appendKeyValue(keyValue table[], int* size, char key[], char value[], struct numOf** signs, int func(int, int)) {
    strcpy(table[*size].key, key);
    strcpy(table[*size].value, value);
    strcpy(table[*size].symbol.symbolName, value);
    table[*size].symbol.amountOfSymbol = 0;
    table[*size].symbol.function = func;
    *signs = &table[*size].symbol;
    (*size)++;
}

void detectInput(char* inputPtr, size_t inputSize) {
    printf("Enter your problem: ");
    //scanf("%98s", input); only detects input before a whitespace
    if (fgets(inputPtr, inputSize, stdin) != NULL) {
        //Succesfull
        inputPtr[strcspn(inputPtr, "\n")] = '\0'; //removes \n so it doesnt create a new line
        printf("Succesful input: %s\n", inputPtr);
    } else {
        //Unsuccesful
        printf("Error: unsuccesful input\n");
    }  
}

int stringToNum(char* string) {
    char *endPtr;
    int num = (int)strtol(string, &endPtr, 10);
    if (*endPtr == '\0') {
        // printf("The integer is: %d\n", num);
    } else {
        printf("Conversion failed. Invalid input: %s\n", endPtr);
    }
    return num;
}
char* removeWhitespaces(const char *str) {
    int i = 0, j = 0;
    int len = 0;
    while (str[len] != '\0') len++;  // get length

    // allocate enough memory for the result
    char *result = malloc((len + 1) * sizeof(char));
    if (!result) return NULL;  // allocation failed

    while (str[i] != '\0') {
        if (!isspace((unsigned char)str[i])) {  // keep non-whitespace
            result[j++] = str[i];
        }
        i++;
    }
    result[j] = '\0';  // null-terminate

    return result;
}

int getMaxSet() {
    int x = maxInputChars;
    int base = 10;
    int constant = 14;
    return (x * (base * (log(constant)/log(base) - 1)) / base);
}


int countOccurences(char *inputPtr, char target) {
    int count = 0;
    for (int i = 0; inputPtr[i] != '\0'; i++) {
        if (inputPtr[i] == target) {
            count++;
        }
    }
    return count;
}

int add(int num1, int num2) {
    return num1 + num2;
}

int subtract(int num1, int num2) {
    return num1 - num2;
}

int multiply(int num1, int num2) {
    return num1 * num2;
}

int divide(int num1, int num2) {
    return num1 / num2;
}

void printRows(char (*arr)[2], int numRows) {
    for (int i = 0; i < numRows; i++) {
        printf("Operator %i is: %c\n", i, arr[i][0]);  // print only the first character
    }
}

void shiftSplit(char (*arr)[6], int* numSplits, int result, int index) {
    // Convert result to string
    char buffer[50];
    sprintf(buffer, "%d", result);

    // Replace splits[i-1] with result
    strcpy(arr[index-1], buffer);
    

    // Shift elements after i+1 left by 2 positions
    int shiftStart = index;       // start at i (position of symbol)
    for (int j = shiftStart; j + 2 < *numSplits; j++) {
        strcpy(arr[j], arr[j + 2]);
        
    }

    // Update maxSplits
    *numSplits -= 2;
}
void calcMDAS(struct numOf* sign, char (*arr)[6], int* numSplits) {
    if (sign->amountOfSymbol > 0) {
        for (int i = 0; i < *numSplits - 1; i++) {
            
             if (i % 2 != 0 && arr[i][0] == sign->symbolName[0]) {
                char *endPtr1; char *endPtr2;
                int num1 = stringToNum(arr[i - 1]);
                int num2 = stringToNum(arr[i + 1]);
                int result = sign->function(num1, num2);
                printf("result of %i multiplied by %i is: %i", num1, num2, result);
                shiftSplit(arr, numSplits, result, i);
                
            }
        }
    }
    printf("\tThe result after operation is ");
    for (int i = 0; i < *numSplits; i++) {
        printf("%s", arr[i]);
    }
    // printf("\n");
}

int main(void) {
   
    //---Formatting the values and operators to calculate
    int operatorsCap = strlen(symbols);
    int operatorsCurrSize = 0;
    keyValue *operatorsTbl = malloc(operatorsCap * sizeof(keyValue));

    struct numOf* multiplySigns = NULL;
    struct numOf* divisionSigns = NULL;
    struct numOf* plusSigns     = NULL;
    struct numOf* minusSigns    = NULL;

    appendKeyValue(operatorsTbl, &operatorsCurrSize, "add", "+", &plusSigns, add);
    appendKeyValue(operatorsTbl, &operatorsCurrSize, "subtract", "-", &minusSigns, subtract);
    appendKeyValue(operatorsTbl, &operatorsCurrSize, "multiply", "*", &multiplySigns, multiply);
    appendKeyValue(operatorsTbl, &operatorsCurrSize, "divide", "/", &divisionSigns, divide);

    printKeyValue(operatorsTbl, operatorsCap);


    //Creating the input
    char input[maxInputChars];
    char* inputPtr = input;
    
    //detecting the input
    detectInput(inputPtr, sizeof(input));
    // printf("%s\n", inputPtr); //double check to ensure the value was inputted

    //getting the amounts of symbols in the input
    int numSymbols = 1;
    for (int i = 0; i < strlen(symbols); i++) {
        numSymbols += countOccurences(inputPtr, symbols[i]);
    }
    // printf("\nNumber of symbols is: %d\n", numSymbols);

    int computedMaxSet = (int)getMaxSet();
    // printf("max set of characters is: %d\n", computedMaxSet);
    
    char (*splits)[6] = malloc(computedMaxSet * sizeof(*splits));
    char (*symbolSplits)[2] = malloc(numSymbols * sizeof(*symbolSplits));
    
    int numIndex = 0;
    int symbolsIndex = 0;
    int currLen = 0;
    bool canSkip = false;
    int skipIndex = 0;
    char inputCpy[100];

    strcpy(inputCpy, inputPtr);//created a copy of the input pointer
    char *symbolsPtr = strtok(inputCpy, symbols);//cuts the copied input pointer
    // printf("\nsaves the first set of values, %s to the symbols pointer\n\n", inputCpy);
   
    while (symbolsPtr != NULL) {
        
        strcpy(splits[numIndex++ + skipIndex], symbolsPtr);
        symbolsPtr = strtok(NULL, "+-*/");
        if (!canSkip) {
            skipIndex++;
            //canSkip = true;
        }
    }

      for (int i = 0; i < computedMaxSet + 1; i++) {   // loop through the full string
        if (strchr("+-*/", inputPtr[i])) {         // check for operator
            char c = inputPtr[i];
            // printf("Operator '%c' found at position %d\n", c, i);
            symbolSplits[symbolsIndex][0] = c;
            symbolSplits[symbolsIndex][1] = '\0';
            symbolsIndex++;
        }
    }

    //increases the amount of individual symbols in their respective structs
    for (int i = 0; i < numSymbols - 1; i++) {
        for (int j = 0; j < operatorsCurrSize; j++) {
            if (*symbolSplits[i] == *operatorsTbl[j].value) {
                operatorsTbl[j].symbol.amountOfSymbol++;
            }
        }
    }
    printf("\n");
    for (int j = 0; j < operatorsCurrSize; j++) {
        // if (symbolSplits[i] == operatorsTbl[j].value) {
        printf("Amount of %s symbols is \t%d\n",operatorsTbl[j].symbol.symbolName, operatorsTbl[j].symbol.amountOfSymbol);
        // }
    }

    // printRows(symbolSplits, numSymbols); printf("\n");
    // print results
    canSkip = false;
    skipIndex = 0;
    int maxSplits;
    int *maxSplitsPtr = &maxSplits;
    for (int j = 0; j < numIndex; j++) {
        // printf("Splitted string is: %s, in position: %i\n", splits[j + skipIndex], j + skipIndex);
        if (!canSkip) {
            skipIndex++;
            //canSkip = true;
        }
        maxSplits = j + skipIndex;
    }
    printf("\n");
    
    int symbolIndex = 0;
    for (int i = 0; i < maxSplits; i++) {
        
        //inserting the symbols if i is odd
        if (i % 2 != 0) {
            char operator[2] = {symbolSplits[symbolIndex][0], '\0'}; 
            printf("symbol index for operator is %i and the symbol to be inserted is %c. ", symbolIndex, symbolSplits[symbolIndex][0]);
            
            strcpy(splits[i], operator);
            
            symbolIndex++;
        } else {
            //removing whitespaces from the values
            strcpy(splits[i], removeWhitespaces(splits[i]));
        }

        printf("New split string is: %s, in position: %i\n", splits[i], i);
    }
    
   
    printf("\n");
   

    // if (multiplySigns->amountOfSymbol > 0) {calcMDAS(multiplySigns, splits, maxSplitsPtr);}
    // printf("\n");
    // if (divisionSigns->amountOfSymbol > 0) {calcMDAS(divisionSigns, splits, maxSplitsPtr);}
    // printf("\n");
    
    while (maxSplits > 1)
    {
        /* code */
        for (int i = 0; i < maxSplits ; i++) {
        
        if (splits[i][0] == '+' || splits[i][0] == '-') {
            //calculate them in order of mdas - multiply, division, addition, subtraction
           
            char symbol[2];
            
            strcpy(symbol, splits[i]);
            //converting the values before and after the operator to numbers
            char *endPtr1; char *endPtr2;
            int num1 = stringToNum(splits[i - 1]);
            int num2 = stringToNum(splits[i + 1]);
            int result = 0;
            if (symbol[0] == '*') {
                result = multiply(num1, num2);
                printf("result of %i multiplied by %i is: %i", num1, num2, result);

            } else if (symbol[0] == '-') {
                result = divide(num1, num2);
                printf("result of %i divided by %i is: %i", num1, num2, result);

            } else if (symbol[0] == '+') {
                result = add(num1, num2);
                printf("result of %i added to %i is: %i", num1, num2, result);

            } else if (symbol[0] == '-') {
                result = subtract(num1, num2);
                printf("result of %i subtracted from %i is: %i", num1, num2, result);

            } else {
                //some error
            }
            printf("\tThe result after operation is ");
            for (int i = 0; i < maxSplits; i++) {
                printf("%s", splits[i]);
            }
            shiftSplit(splits, maxSplitsPtr, result, i);
            printf("\n");
            break;
        }
    }

    }
    //calcMDAS(plusSigns, splits, maxSplitsPtr);
    //calcMDAS(minusSigns, splits, maxSplitsPtr);
    printf("\nResult to the problem %s = ", input);
    for (int i = 0; i < maxSplits; i++) {
        printf("%s", splits[i]);
    }
   
    free(splits);

    return 0;
}

