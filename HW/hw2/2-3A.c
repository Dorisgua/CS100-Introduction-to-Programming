#include "stdio.h"
#include "stdlib.h"

int** MagicSquare(int n){
    // YOUR CODE HERE
    int i,j;
    int row = n, column = n, **arr;
	for (j = 0; j < column; j ++){
		arr = (int **)malloc(sizeof(int *) * row); // 分配所有行的首地址
		for (i = 0; i < row; i ++) { // 按行分配每一列
			arr[i] = (int *)malloc(sizeof(int) * column);	
		}
	}
    i = 0;
    j = (row-1)/2;
    arr[i][j] = 1;
    //printf("%d",arr[0][7]);
    for (j = 1; j < column; j ++){
		for (i = 0; i < row; i ++) {
			if(arr[i-1][j+1]==0){
                arr[i-1][j+1] = j+1;
                i = i-1;
                j = j+1;
            }
            else if(arr[i-1][j+1]<-1000||arr[i-1][j+1]>1000){
                i = i-1;
                j = j+1;
                i = i%n;
                j = j%n;
                if (i<0){
                    i = i+n;
                }
                if (j<0){
                    j = j+n;
                }
                arr[i][j] = j+1;
            }
            else{
                arr[i+1][j] = j+1;
            }
            printf("i,j:%d,%d",i,j);
		}
	}
    printf("i,j:%d,%d",i,j);
	return arr;
}

void FreeMagicSquare(int** magicSquare, int n){
    // YOUR CODE HERE 
    int row = n;
    for (int i = 0; i < row; ++i){
		free(*(magicSquare + i));
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
