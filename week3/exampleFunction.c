#include <stdio.h>

//from minerva

int sum (int a, int b)
{
    int answer;
    answer = a + b;
    return answer;
}

int main () 
{
    int y = 2;
    int z = sum(5, y); // calling our new function

    int z1 = sum(10, y);

    printf ("The sum of 10 and %d is %d\n", y, z1);
}