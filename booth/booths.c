#include <stdio.h>
#include <math.h>

// Global variables
int a = 0, b = 0, c = 0, a1 = 0, b1 = 0, com[5] = { 1, 0, 0, 0, 0 };
int anum[5] = {0}, anumcp[5] = {0}, bnum[5] = {0};
int acomp[5] = {0}, bcomp[5] = {0}, pro[5] = {0}, res[5] = {0};

// Function to convert decimal numbers to binary
void binary() {
    // Obtain the absolute values of a and b
    a1 = fabs(a);
    b1 = fabs(b);

    int r, r2, i, temp;

    // Convert the absolute values of a and b to binary
    for (i = 0; i < 5; i++) {
        r = a1 % 2;
        a1 = a1 / 2;
        r2 = b1 % 2;
        b1 = b1 / 2;

        // Store binary representations in arrays
        anum[i] = r;
        anumcp[i] = r;
        bnum[i] = r2;

        // Calculate the one's complement of b
        if (r2 == 0) {
            bcomp[i] = 1;
        }

        // Calculate the one's complement of a
        if (r == 0) {
            acomp[i] = 1;
        }
    }

    // Initialize carry for two's complement calculation
    c = 0;

    // Calculate the two's complement of b
    for (i = 0; i < 5; i++) {
        res[i] = com[i] + bcomp[i] + c;

        // Update carry
        if (res[i] >= 2) {
            c = 1;
        } else {
            c = 0;
        }

        // Update result array
        res[i] = res[i] % 2;
    }

    // Copy the result to the bcomp array
    for (i = 4; i >= 0; i--) {
        bcomp[i] = res[i];
    }

    // Adjust for negative values of a
    if (a < 0) {
        c = 0;

        // Reset result array
        for (i = 4; i >= 0; i--) {
            res[i] = 0;
        }

        // Calculate two's complement of a
        for (i = 0; i < 5; i++) {
            res[i] = com[i] + acomp[i] + c;

            // Update carry
            if (res[i] >= 2) {
                c = 1;
            } else {
                c = 0;
            }

            // Update result array
            res[i] = res[i] % 2;
        }

        // Copy the result to the anum and anumcp arrays
        for (i = 4; i >= 0; i--) {
            anum[i] = res[i];
            anumcp[i] = res[i];
        }
    }

    // Adjust for negative values of b
    if (b < 0) {
        // Swap bnum and bcomp arrays for negative b
        for (i = 0; i < 5; i++) {
            temp = bnum[i];
            bnum[i] = bcomp[i];
            bcomp[i] = temp;
        }
    }
}

// Function to perform binary addition
void add(int num[]) {
    int i;
    c = 0;

    // Perform binary addition
    for (i = 0; i < 5; i++) {
        res[i] = pro[i] + num[i] + c;

        // Update carry
        if (res[i] >= 2) {
            c = 1;
        } else {
            c = 0;
        }

        // Update result array
        res[i] = res[i] % 2;
    }

    // Copy the result to the pro array and display intermediate result
    for (i = 4; i >= 0; i--) {
        pro[i] = res[i];
        printf("%d", pro[i]);
    }

    // Display separator
    printf("  :  ");

    // Display the content of anumcp array
    for (i = 4; i >= 0; i--) {
        printf("%d", anumcp[i]);
    }
}

// Function to perform arithmetic right shift
void arshift() {
    int temp = pro[4], temp2 = pro[0], i;

    // Perform right shift on pro array
    for (i = 1; i < 5; i++) {
        pro[i - 1] = pro[i];
    }

    // Update pro array
    pro[4] = temp;

    // Perform right shift on anumcp array
    for (i = 1; i < 5; i++) {
        anumcp[i - 1] = anumcp[i];
    }

    // Update anumcp array
    anumcp[4] = temp2;

    // Display the content of pro array and anumcp array
    printf("\nAR-SHIFT:\t");
    for (i = 4; i >= 0; i--) {
        printf("%d", pro[i]);
    }

    // Display separator
    printf("  :  ");

    for (i = 4; i >= 0; i--) {
        printf("%d", anumcp[i]);
    }
}

// Main function
void main() {
    int i, q = 0;

    // Display title
    printf("\t\tBOOTH'S MULTIPLICATION ALGORITHM");

    // Input two numbers to multiply
    printf("\nEnter two numbers to multiply: ");
    printf("\nBoth must be less than 16");

    do {
        printf("\nEnter A: ");
        scanf("%d", &a);
        printf("Enter B: ");
        scanf("%d", &b);
    } while (a >= 16 || b >= 16);

    // Display the expected product
    printf("\nExpected product = %d", a * b);

    // Perform binary conversion and display binary equivalents
    binary();
    printf("\n\nBinary Equivalents are: ");
    printf("\nA = ");
    for (i = 4; i >= 0; i--) {
        printf("%d", anum[i]);
    }
    printf("\nB = ");
    for (i = 4; i >= 0; i--) {
        printf("%d", bnum[i]);
    }
    printf("\nB' + 1 = ");
    for (i = 4; i >= 0; i--) {
        printf("%d", bcomp[i]);
    }
    printf("\n\n");

    // Display the operation header
    printf("Operation\t  A         Q      Qn+1     n");

    // Perform Booth's algorithm steps
    for (i = 0; i < 5; i++) {
        if (anum[i] == q) {
            arshift();
            q = anum[i];
        } else if (anum[i] == 1 && q == 0) {
            printf("\nSUB B   :\t");
            add(bcomp);
            arshift();
            q = anum[i];
        } else {
            printf("\nADD B   :\t");
            add(bnum);
            arshift();
            q = anum[i];
        }

        // Display Qn+1 and n
        printf("      %d      %d", q, 5 - i);
    }

    // Display the final product
    printf("\n\n\nProduct is = ");
    for (i = 4; i >= 0; i--) {
        printf("%d", pro[i]);
    }
    for (i = 4; i >= 0; i--) {
        printf("%d", anumcp[i]);
    }
}
