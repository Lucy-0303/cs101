#include <stdio.h>

int fractorial(int n)
{
    if(n == 1) return 1;
    return n * fractorial(n-1);
}    
int main() {
    int n = 5, m = fractorial(n);
    printf("fractorial %d = %d", n, m);
    return 0;
}
