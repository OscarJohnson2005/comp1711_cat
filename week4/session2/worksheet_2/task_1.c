#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//create a datatype for storing coordinate points, two doubles

typedef struct 
{
    double x;
    double y;
}point;


int main()
{
    int i;
    point map[10];
    for(i; i < 10; i++)
    {
        int xcord = rand()%10;
        int ycord = rand()%10;
        map[i].x = xcord;
        map[i].y = ycord;

    }
    return 0;

}