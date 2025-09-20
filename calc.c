#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define maxInputChars 100

char symbols[5] = {'+', '-', '*', '/', '\0'};

void detectInput(char*, size_t);
int countOccurences(char*, char);

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

int main(void) {
    //Creating the input
    char input[maxInputChars];
    char* inputPtr = input;
    
    //detecting the input
    detectInput(inputPtr, sizeof(input));
    printf("%s\n", inputPtr); //double check to ensure the value was inputted

    //getting the amounts of symbols in the input
    int numSplits = 1;
    for (int i = 0; i < strlen(symbols); i++) {
        numSplits += countOccurences(inputPtr, symbols[i]);
    }
    printf("Number of symbols is: %d\n", numSplits);

int computedMaxSet = (int)getMaxSet();
   
    printf("max set, %d\n", computedMaxSet);
    
    char (*splits)[6] = malloc(computedMaxSet * sizeof(*splits));
    char (*symbolSplits)[2] = malloc(numSplits * sizeof(*symbolSplits));
    // int setIndex = 0;
    // char currSet[6];
    // for (int i = 0; i < strlen(inputPtr); i++)
    // {
    //     /* code */
    //     char currChar = inputPtr[i];
    //     printf("The current character is: %c\n", currChar);
        

    // }

    printf("\n");
    
    
    //splitting the string based on the num of splits 
    // int currLen = 0;
    // for (int i = 0; i < numSplits + 1; i++) {
    //     int len = strcspn(inputPtr + currLen + 1, "+-*/");
        
    //     currLen = len + 1;
    //     inputPtr[len] = '\0';

    //     printf("%i\n",currLen);
    //     printf("%s\n",inputPtr);
    //     printf("%s\n",inputPtr + currLen + 1);
    //     printf("The %i text is %s\n", i, inputPtr);
    //     inputPtr = inputPtr + currLen + 1;

    //     strcat(splits[i], inputPtr);
    //     printf("Splitted string is: %s\n", splits[i]);
    // }
    
    int numIndex = 0;
    int currLen = 0;
    char *symbolsPtr = strtok(inputPtr, symbols);

    // strtok splits around delimiters
    
    while (symbolsPtr != NULL) {
        strcpy(splits[numIndex++], symbolsPtr);
        symbolsPtr = strtok(NULL, "+-*/");
    }

    // print results
    for (int j = 0; j < numIndex; j++) {
        printf("Splitted string is: %s\n", splits[j]);
    }

    free(splits);

    // while (input[currLen] != '\0') {
    //     //if current char is an operator, store it directly
    //     if (strchr("+-*/", input[currLen])) {
    //         splits[numIndex][0] = input[currLen];  // copy operator
    //         splits[numIndex][1] = '\0';
    //         numIndex++;
    //         currLen++;
    //     } 
    //     else {
    //         //copy number until next operator
    //         int k = 0;
    //         while (input[currLen] != '\0' && !strchr("+-*/", input[currLen])) {
    //             splits[numIndex][k++] = input[currLen++];
    //         }
    //         splits[numIndex][k] = '\0';  // terminate string
    //         numIndex++;
    //     }
    // }

    // // print results
    // for (int j = 0; j < numIndex; j++) {
    //     printf("Splitted string is: %s\n", splits[j]);
    // }


    free(splits);
    return 0;
}

