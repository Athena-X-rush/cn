#include <stdio.h>

#define MAX 20

int data[MAX];
int n;


int onesComplement(int num) {
    return ~num;
}


int generateChecksum() {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    int checksum = onesComplement(sum);
    return checksum;
}


int verifyChecksum(int checksum) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    sum += checksum;
   
    return (onesComplement(sum) == 0);
}

int main() {
    printf("=====================================================\n");
    printf("  Data Link Layer Framing - Checksum\n");
    printf("  Computer Networks-II Lab | Mayank Bisht | 2361323\n");
    printf("=====================================================\n\n");

    /* ---- SENDER SIDE ---- */
    printf("============ SENDER SIDE ============\n");
    printf("Enter number of data blocks: ");
    scanf("%d", &n);

    printf("Enter %d data blocks:\n", n);
    for (int i = 0; i < n; i++) {
        printf("  Block[%d]: ", i + 1);
        scanf("%d", &data[i]);
    }


    int sum = 0;
    for (int i = 0; i < n; i++) sum += data[i];

    int checksum = onesComplement(sum);

    printf("\n  Data blocks    : ");
    for (int i = 0; i < n; i++) printf("%d ", data[i]);
    printf("\n");
    printf("  Sum of blocks  : %d\n", sum);
    printf("  Checksum (1's complement of sum): %d\n", checksum);
    printf("\n  Sender transmits: [data blocks] + [checksum = %d]\n", checksum);

    /* ---- RECEIVER SIDE ---- */
    printf("\n============ RECEIVER SIDE ============\n");

    char choice;
    printf("\nSimulate transmission error? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        int idx, errVal;
        printf("Enter block index to corrupt (1 to %d): ", n);
        scanf("%d", &idx);
        printf("Enter new (corrupted) value: ");
        scanf("%d", &errVal);
        data[idx - 1] = errVal;
        printf("  Block[%d] corrupted to: %d\n", idx, errVal);
    }

    int receivedSum = 0;
    for (int i = 0; i < n; i++) receivedSum += data[i];
    receivedSum += checksum;

    printf("\n  Received data  : ");
    for (int i = 0; i < n; i++) printf("%d ", data[i]);
    printf("\n");
    printf("  Checksum       : %d\n", checksum);
    printf("  Total sum      : %d\n", receivedSum);
    printf("  1's complement : %d\n", onesComplement(receivedSum));

    printf("\n-----------------------------------------------------\n");
    if (onesComplement(receivedSum) == 0) {
        printf("  RESULT: No Error in transmission. Data accepted.\n");
    } else {
        printf("  RESULT: Error detected in transmission!\n");
    }
    printf("-----------------------------------------------------\n");

    return 0;
}

