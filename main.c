
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert a decimal number to its binary equivalent
void convertDecimalToBinary(int noOfMinterm,int noOfVariables, int decimal[noOfMinterm],int binaryArray[noOfMinterm][noOfVariables]) {
   for(int j=noOfMinterm-1; j >=0 ; j--){
    for (int i = noOfVariables - 1; i >= 0; i--) {
        binaryArray[j][i] = decimal[j] % 2;  // Store the least significant bit
        decimal[j] = decimal[j]/ 2;  // Move to the next bit
    }
}
}

int add(int a, int b){
    return a + b;
}

void InputHandler( int noOfminterms,int noOfvariables,int array[noOfminterms][noOfvariables],int Method)
{
    if(Method == 1){
             printf("\n ENTER the decimal minterms\n ");
            int Decimal[noOfminterms];
        for(int u=0; u< noOfminterms; u++){
            scanf("%d",&Decimal[u]);
        }
    for(int m=0; m<noOfminterms; m++){
            printf("%d,",Decimal[m]);
    }
    convertDecimalToBinary(noOfminterms,noOfvariables,Decimal ,array);


    }else{
    printf("\n ENTER the binary minterms\n ");
for(int i=0; i<noOfminterms ; i++){

    for(int j=0; j< noOfvariables ; j++){
    scanf("%d",&array[i][j]);

}
}
    }
printf("\n displaying the minterms\n ");
for(int k=0; k< noOfminterms ; k++){
            printf("Minterm %d:",k+1);
    for(int l=0; l< noOfvariables ; l++){
    printf("%d",array[k][l]);
}
printf("\n");
}
}

void countOnes(int noOfMinterms, int noOfVariables, int array[noOfMinterms][noOfVariables], int onesCount[noOfMinterms]) {
    for (int i = 0; i < noOfMinterms; i++) {
        int count = 0;
        for (int j = 0; j < noOfVariables; j++) {
            count = count +  array[i][j];
        }
        onesCount[i] = count; // Store the number of ones in each minterm
    }
}

void PrintTables(int noOfMinterms, int noOfVariables, int array[noOfMinterms][noOfVariables]) {
    int onesCount[noOfMinterms]; // Array to store the number of 1s in each minterm
    countOnes(noOfMinterms, noOfVariables, array, onesCount);

    printf(" Table:\n");
    printf("minterms\t|\tnumber of 1s\n");
    printf("--------------------------------\n");

    // Print the first table (minterms with number of 1s)
    for (int i = 0; i < noOfMinterms; i++) {
        printf("minterm %d\t\t|\t%d\n", i+1, onesCount[i]);
    }
    printf("--------------------------------\n");


}

#define MAX_PRIME_IMPLICANTS 100 // Maximum number of prime implicants

char primeImplicants[MAX_PRIME_IMPLICANTS][100]; // Array to store all prime implicants
int primeCount = 0; // Counter for the number of prime implicants

void compare(int noOfMinterms, int noOfVariables, int array[noOfMinterms][noOfVariables]) {
    char charArray[noOfMinterms][noOfVariables + 1]; // Character representation of minterms
    char newArrays[noOfMinterms * noOfMinterms][noOfVariables + 1]; // Array to hold new terms with dashes
    char groupedMinterms[noOfMinterms * noOfMinterms][100];         // Array to store grouped minterm numbers
    int used[noOfMinterms]; // Array to track whether a term has been combined
    memset(used, 0, sizeof(used)); // Initialize all to 0

    int newRowCount = 0; // Count for rows in newArrays

    // Convert integer array to character array
    for (int i = 0; i < noOfMinterms; i++) {
        for (int j = 0; j < noOfVariables; j++) {
            charArray[i][j] = array[i][j] == -1 ? '-' : (array[i][j] + '0');
        }
        charArray[i][noOfVariables] = '\0'; // Null-terminate the string
    }

    printf("\nComparing minterms and marking differences:\n");
    for (int p = 0; p < noOfMinterms; p++) {
        for (int j = p + 1; j < noOfMinterms; j++) {
            // Check for consecutive differing bits
            int diffCount = 0, diffIndex = -1;
            for (int k = 0; k < noOfVariables; k++) {
                if (charArray[p][k] != charArray[j][k]) {
                    diffCount++;
                    diffIndex = k;}
            }
            // If they differ by exactly one bit
            if (diffCount == 1) {
                used[p] = 1;
                used[j] = 1;

                // Combine the two minterms into a new one
                for (int k = 0; k < noOfVariables; k++) {
                    newArrays[newRowCount][k] = (k == diffIndex) ? '-' : charArray[p][k];
                }
                newArrays[newRowCount][noOfVariables] = '\0'; // Null-terminate the string

                // Record the minterm numbers being grouped
                sprintf(groupedMinterms[newRowCount], "(%d,%d)", p + 1, j + 1);
                newRowCount++;
            }
        }

        // If a term is unused, store it as a prime implicant
        if (!used[p]) {
            strcpy(primeImplicants[primeCount], charArray[p]);
            primeCount++;
        }
    }

    // Print new table with grouped minterms and dashes
    printf("\nNew Table with Grouped Minterms and Dashes:\n");
    printf("Grouped Minterms\t|\tResulting Term\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < newRowCount; i++) {
        printf("%s\t\t|\t%s\n", groupedMinterms[i], newArrays[i]);
    }

    // Print unused rows as prime implicants for this stage
    printf("\nPrime Implicants (Unused Terms at this stage):\n");
    for (int i = 0; i < noOfMinterms; i++) {
        if (!used[i]) {
            printf("%s\n", charArray[i]);
        }
    }

    // Recursive call if new rows were generated
    if (newRowCount > 0) {
        // Prepare next array for recursive call
        int nextArray[newRowCount][noOfVariables];
        for (int i = 0; i < newRowCount; i++) {
            for (int j = 0; j < noOfVariables; j++) {
                if (newArrays[i][j] == '-') {
                    nextArray[i][j] = -1; // Use -1 for internal representation
                } else {
                    nextArray[i][j] = newArrays[i][j] - '0'; // Convert back to integer
                }
            }
        }
        compare(newRowCount, noOfVariables, nextArray);
    } else {
        // Print all prime implicants
        printSimplifiedForm(primeImplicants,primeCount, noOfVariables );
    }
}


void printSimplifiedForm(char Mintermresult[][100], int count, int vars) {
    printf("\nSimplified Boolean Expression in SOP form:\n");

    for (int i = 0; i < count; i++) {
        if (i > 0) {
            printf(" + ");  // Add '+' between terms
        }

        for (int j = 0; j < vars; j++) {
            if (Mintermresult[i][j] == '1') {
                printf("%c", 'A' + j);  // Print variable (A, B, C, ...)
            } else if (Mintermresult[i][j] == '0') {
                printf("%c'", 'A' + j);  // Print complemented variable (A', B', C', ...)
            }
            // If '-', skip the variable (don't print anything)
        }
    }
    printf("\n");
}


int main() {
int NoOfVariables, NoOfMinterms,method;

printf("Please enter the number of variables :\n");
scanf("%d",&NoOfVariables);
printf("Please enter the number of minterms :\n");
scanf("%d",&NoOfMinterms);
printf("Please enter either 1 OR 2:\n method 1: Entering the minterms as decimal digits\n method 2: Entering the minterms as binary digits\n");
scanf("%d",&method);
while(method != 1 && method != 2 ){

    printf("Please enter either 1 or 2:\n");
scanf("%d",&method);
}


int FirstArray[NoOfMinterms][NoOfVariables];
InputHandler( NoOfMinterms, NoOfVariables,FirstArray,method);

 PrintTables(NoOfMinterms, NoOfVariables,FirstArray);
compare( NoOfMinterms, NoOfVariables, FirstArray);
return 0;
}
