#include <stdio.h>

int main()
{
    char filename[] = "squares.dat";
    FILE *file = fopen(filename, "w");
    if(file == NULL)
    {
        perror(" ");
        return 1;
    }
    int n;
    scanf("How many numbers? ", n);
    for(int i; i <= n; i++)
    {
        fprintf(file, "")
    }


}