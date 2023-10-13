# include <stdio.h>

int main()
{
    int numsToMax[6] = {6, 10, 2, 8, 5};
    int i = 0;
    int max = 0;
    int temp = 0;
    int swapMade = 0;
    int x = 0;

    while(x = 0)
    {
        if(numsToMax[i] < numsToMax[i+1])
        {
            temp = numsToMax[i];
            numsToMax[i] = numsToMax[i+1];
            numsToMax[i+1] = temp;
            i++;
            swapMade = 1;
        }
        else if(i == 5)
        {
            i = 0;
            if(swapMade = 1)
            {
                x = 1;
            }
        }
        else
        {
            i++;
        }
    }
    max = numsToMax[0];
    printf("Maximum = %d\n", max);
    return 0;

}