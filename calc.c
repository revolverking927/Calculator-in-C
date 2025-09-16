#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define maxInputChars 100

void detectInput(char*, size_t);

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

int main(void) {

    char input[maxInputChars];
    char* inputPtr = input;
    
    detectInput(inputPtr, sizeof(input));
    printf("%s\n", inputPtr); //double check to ensure the value was inputted

    printf("max set, %d\n", (int)getMaxSet());
    int computedMaxSet = (int)getMaxSet();
    char (*splits)[6] = malloc(computedMaxSet * sizeof(*splits));
    
    int setIndex = 0;
    char currSet[6];
    for (int i = 0; i < strlen(inputPtr); i++)
    {
        /* code */
        char currChar = inputPtr[i];
        printf("The current character is: %c\n", currChar);
        
    }
    
    return 0;
}

