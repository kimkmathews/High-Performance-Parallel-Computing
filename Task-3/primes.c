#include <stdio.h>

int is_prime(int n){
    for (int i=2;i<n/2;i++)
        if (n%i==0)
            return 0;
    return 1;
}

int main() {
    int M;
    printf("Enter a value for M: ");
    scanf("%d", &M);
    
    int count = 0;
    for (int i=2; i<=M; i++) {
        if (is_prime(i)) {
            count++;
        }
    }
    
    printf("There are %d prime numbers in the range of 1 to %d.\n", count, M);
    return 0;
}
