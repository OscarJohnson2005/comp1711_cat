# include <stdio.h>

int main()
{
    char hello[6] = "Hello";
    int i = 6;

    while(i >=0)
    {
        printf("%c\n", hello[i]);
        i--;
    }

    return 0;

}