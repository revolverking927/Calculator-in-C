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

void printText(char text[]) {
    // Check for NULL pointer
    if (text == NULL) {
        printf("Error: text is NULL\n");
        return;
    }

    printf("%s\n", text);
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

void printRows(char (*arr)[2], int numRows) {
    for (int i = 0; i < numRows; i++) {
        printf("%c\n", arr[i][0]);  // print only the first character
    }
}


void insertElement(char* arr, int pos, char element) {
    int n = strlen(arr); // Current number of elements in the array
    

    // Check if there's space in the array
    if (n >= 10) {
        printf("Array is full, cannot insert element.\n");
    }

    // Shift elements to the right
    for (int i = n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }

    // Insert the new element
    arr[pos] = element;
    n++; // Increment the size of the array

    // Print the updated array
    printf("Updated array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
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
    int symbolsIndex = 0;
    int currLen = 0;
    char inputCpy[100];
    strcpy(inputCpy, inputPtr);//created a copy of the input pointer
    char *symbolsPtr = strtok(inputCpy, symbols);//cuts the copied input pointer
    printText(inputPtr);
    printText(inputCpy);
    // strtok splits around delimiters
    
    while (symbolsPtr != NULL) {
        strcpy(splits[numIndex++], symbolsPtr);
        symbolsPtr = strtok(NULL, "+-*/");
    }

      for (int i = 0; i < computedMaxSet + 1; i++) {   // loop through the full string
        if (strchr("+-*/", inputPtr[i])) {         // check for operator
            char c = inputPtr[i];
            //insertElement(symbols[symbolsIndex++], symbolsIndex, c);
            printf("Operator '%c' found at position %d\n", c, i);
            symbolSplits[symbolsIndex][0] = c;
            symbolSplits[symbolsIndex][1] = '\0';
            symbolsIndex++;
        }
    }
    printRows(symbolSplits, numSplits);
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

