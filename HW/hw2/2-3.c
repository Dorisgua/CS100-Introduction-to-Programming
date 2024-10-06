#include "stdio.h"
#include "stdlib.h"

int** MagicSquare(int n){
    // YOUR CODE HERE
    //p = malloc(n * sizeof(int ) * n);     //申请5行的地址空间
    //int matrix[n][n];
    
    //int i = (n-1)/2;
    //int j = 0;
    //matrix[i][j] = 1;
    int i = 0,j = 0;
    int **a;  
    for(i=0;i<n;i++)  {
        for(j=0;j<n;j++){
            a[i][j]=(int**)malloc(sizeof(int)*n); 
            a[i][j] = 0;
            printf("%p\n",&a[i][j]);     //输出每个元素地址，每行的列与列之间的地址时连续的，行与行之间的地址不连续  
            printf("%d\n",a[i][j]); 
        }
    }
    return a;
}

void FreeMagicSquare(int** magicSquare, int n){
    // YOUR CODE HERE 
    int i,j;
    for(i=0;i<n;i++)  {
        for(j=0;j<n;j++){
            free(magicSquare[i][j]); 
        }
    }
}

int main(){
    int n;
    scanf("%d", &n); // Please input a positive odd number.
    int** magicSquare = MagicSquare(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%4d", magicSquare[i][j]);
        }
        printf("\n");
    }
    FreeMagicSquare(magicSquare, n);
    return 0;
}
