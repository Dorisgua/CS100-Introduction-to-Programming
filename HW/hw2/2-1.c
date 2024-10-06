#include <stdio.h>
#include <stdlib.h>

void FindSecondMaxAndMin(int numbers[], int size, int* secondMax, int* secondMin){
    // YOUR CODE HERE
    int i,j,Max = numbers[0],Max2 = numbers[0],Min = numbers[0],Min2 = numbers[0];

    for(i=0;i<size;i++){
        if(numbers[i]>Max){
            Max = numbers[i];
        }
        if(numbers[i]<Min){
            Min = numbers[i];
        }
    }
    if(Min==numbers[0]){
        Min2=numbers[1];
    }
    if(Max==numbers[0]){
        Max2=numbers[1];
    }
    for(j=0;j<size;j++){
        if(numbers[j]<Max && numbers[j]>Max2){
            Max2 = numbers[j];
        }
        if(numbers[j]>Min && numbers[j]<Min2){
            Min2 = numbers[j];
        }
    }
    *secondMax = Max2;
    *secondMin = Min2;
    return;
}

#define SIZE 8

int main(){
    int secondMax, secondMin;
    int numbers[SIZE] = {2, 3, 4, 7, 6, 10, 9, 8};
    FindSecondMaxAndMin(numbers, SIZE, &secondMax, &secondMin);
    printf("%d %d\n", secondMax, secondMin);
    return 0;
}