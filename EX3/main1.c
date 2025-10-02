#include <stdio.h>
#define ROWS 6

void print_sp(int i, int n) {
    int j;
    for (j = 1; j <= n - i; j++) {
        printf(" ");
    }
}

void print_num(int n) {
    int j;
    for (j = 1; j <= n; j++) {
        printf("%d", n);
        if (j < n) {
            printf(" "); 
        }
    }
}

int main() {
    int i; 

    for (i = 1; i <= ROWS; i++) {
        print_sp(i, ROWS); 
        print_num(i);
        printf("\n");
    }

    return 0;
}
