#include <iostream>

int factorial(int num) {
    if(num == 1) {
        return num;
    } else {
        return factorial(num - 1) * num;
    }
}

int main() {
    int num = 7;
    printf("Number:    %d\n", num);
    printf("Factorial: %d", factorial(num));
    return 0;
}