#include <stdio.h>
int main()
{
    int arr[4],i;
    char cha[4];
    for (i = 0;i<4;i++){
        scanf("%d-%c",&arr[i],&cha[i]);
        getchar();
        printf("%d-%c\n",arr[i],cha[i]);
    }
    //printf("%d",arr[i]);
}