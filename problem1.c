#include <stdio.h>
void swap_with_two(int *,int*);
int main()
{
    int a,b;
    a=5;
    b=10;
    printf("A is : %d , B is %d \n",a,b);
    swap_with_two(&a,&b);
    printf("A is : %d , B is %d \n",a,b);
}

void swap_with_two(int *a , int *b)
{
    *a = *a + *b ;
    *b = *a - *b ;
    *a = *a - *b ;
}