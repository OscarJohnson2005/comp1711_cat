# include <stdio.h>

int main()
{
    int numsToSum[6] = {6, 10, 2, 8, 5};
    int i = 0;
    int total = 0;
    while(i < 6)
    {
        total = total + numsToSum[i];
        i++;
    }
    printf("Total = %d\n", total);
    return 0;

}