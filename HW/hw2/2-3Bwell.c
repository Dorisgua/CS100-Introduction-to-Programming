#include "stdio.h"
#include "stdlib.h"

int** MagicSquare(int n){
    // YOUR CODE HERE
    int i,j;
    int row = n, column = n, **arr;
	for (j = 0; j < column; j ++){
		arr = (int **)malloc(sizeof(int *) * row); 
		for (i = 0; i < row; i ++) { 
			arr[i] = (int *)malloc(sizeof(int) * column);	
		}
	}
    i = 0;
    j = (row-1)/2;
    //arr[i][j] = 1;
    for (int num = 1; num <= n * n;num++) {
        if (i <0 && j == n) { 
            i = (i+n) % n;
            j = j %n;
        } 
        else {
            if (j == n){
                j = j %n ;
            }
            if (i < 0){
                i = (i+n) %n;
            }
        }
        if (arr[i][j] != 0 &&arr[i][j] <= 1000&&arr[i][j] >= -1000) {
            j--;
            j = (j+n)%n;
            i=(i+2)%n;//回到原来的i，j
            //i++;
            //printf("i,j:%d,%d",i,j);
            arr[i][j] = num;
            j++;
            i--;
            continue;
        }
        if (arr[i][j] == 0) {
            arr[i][j] = num;  
        j++;
        i--;
        }
    }
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
