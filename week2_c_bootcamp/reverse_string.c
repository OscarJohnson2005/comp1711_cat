# include <stdio.h>
# include <string.h>

int main()
{
    char string[15];
    int len;

    printf("Enter your string: ");
    scanf("%s", string);

//reverse the string here
    len = strlen(string);
    for (int x = len-1; x >= 0; x--)
    {
        printf("%c", string[x]);
    };


    return 0;
}