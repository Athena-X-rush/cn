#include <stdio.h>
#include <math.h>

#define MAX 30

int data[MAX];   
int ham[MAX];   
int m;          
int r;           
int total;       


void calcParityBits() {
    r = 0;
    while ((int)pow(2, r) < (m + r + 1)) {
        r++;
    }
    total = m + r;
}


int isPowerOf2(int pos) {
    return (pos & (pos - 1)) == 0;
}


void buildHammingCode() {
    int j = m; 


    for (int i = total; i >= 1; i--) {
        if (isPowerOf2(i)) {
            ham[i] = 0;  
        } else {
            ham[i] = data[j - 1];
            j--;
        }
    }

  
    for (int i = 0; i < r; i++) {
        int pos = (int)pow(2, i);
        int parity = 0;
        for (int j = pos; j <= total; j += 2 * pos) {
            for (int k = j; k < j + pos && k <= total; k++) {
                parity ^= ham[k];
            }
        }
        ham[pos] = parity;
    }
}


void printHammingCode() {
    printf("  Generated Hamming Code (positions 1 to %d):\n  ", total);
    for (int i = 1; i <= total; i++) {
        printf("%d ", ham[i]);
    }
    printf("\n\n  Position labels:\n  ");
    for (int i = 1; i <= total; i++) {
        printf("%d ", i);
    }
    printf("\n  (P=parity bit at positions: ");
    for (int i = 0; i < r; i++) printf("%d ", (int)pow(2, i));
    printf(")\n");
}


void detectAndCorrect() {
    int error = 0;

  
    for (int i = 0; i < r; i++) {
        int pos = (int)pow(2, i);
        int parity = 0;
        for (int j = pos; j <= total; j += 2 * pos) {
            for (int k = j; k < j + pos && k <= total; k++) {
                parity ^= ham[k];
            }
        }
        if (parity != 0) {
            error += pos;
        }
    }

    printf("\n-----------------------------------------------------\n");
    if (error == 0) {
        printf("  No error detected. Data is correct.\n");
    } else {
        printf("  Error detected at bit position: %d\n", error);
        /* Correct the error by flipping that bit */
        ham[error] ^= 1;
        printf("  Bit flipped. Error corrected.\n");
        printf("  Corrected Hamming Code:\n  ");
        for (int i = 1; i <= total; i++) {
            printf("%d ", ham[i]);
        }
        printf("\n");
    }
    printf("-----------------------------------------------------\n");
}

int main() {
    printf("=====================================================\n");
    printf("  Hamming Code: Error Detection & Correction\n");
    printf("  Computer Networks-II Lab | Mayank Bisht | 2361323\n");
    printf("=====================================================\n\n");


    printf("============ SENDER SIDE ============\n");
    printf("Enter number of data bits: ");
    scanf("%d", &m);

    printf("Enter %d data bits (MSB first):\n  ", m);
    for (int i = m - 1; i >= 0; i--) {
        scanf("%d", &data[i]);
    }

    calcParityBits();
    printf("\n  Data bits (m) = %d\n", m);
    printf("  Parity bits (r) = %d\n", r);
    printf("  Total bits = %d\n\n", total);

    buildHammingCode();
    printHammingCode();

    
    printf("\n============ RECEIVER SIDE ============\n");
    printf("Enter received Hamming code (%d bits, position 1 to %d):\n  ", total, total);
    for (int i = 1; i <= total; i++) {
        scanf("%d", &ham[i]);
    }

    detectAndCorrect();

    printf("\nResult: Hamming Code implemented successfully.\n");
    printf("=====================================================\n");
    return 0;
}

