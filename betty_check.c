#include <stdio.h>

/**
*main - entry point
*
*Return: 0 ( success)
*/

void my_function(void)
{
    int a = 3;
    int b = 2;
    int sum;

    sum = a + b;

    printf("the sum is: %d\n", sum);
}

int main(void)
{
    my_function();
    return (0);
}
