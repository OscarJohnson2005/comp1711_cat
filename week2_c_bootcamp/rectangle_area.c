# include <stdio.h>

int main(){
    int a;
    int b;
    int c;

    printf("Width of rectangle: ");
    scanf("%d", &a);
    printf("Length of rectangle: ");
    scanf("%d", &b);

    c = a * b;
    printf("Area = %d\n", c);
    return 0;
}