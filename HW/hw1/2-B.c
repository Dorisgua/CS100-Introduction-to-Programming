
#include <stdio.h>
#include <math.h>
int main()
{
    float result[6];
    float x[6];
    float y[6];
    int k,min = 0,min2 = 3;
    for(k = 0;k<6;k++){
        scanf("(%f,%f)", &x[k],&y[k]);
        getchar();
        result[k]=hypot(x[k],y[k]);
    }
    for(k = 0;k<6;k++){
        if (result[k]<result[min]){
            min = k;
        }
        printf("The hypotenuse is: %f\n",result[k]);
    }
    for(k = 3;k<6;k++){
        if (result[k]<result[min2]){
            min2 = k;
        }
    }
    printf("min2 is: %f\n",result[min2]);
    printf("The hypotenuse is: %f\n",result[min]);
    if (min <= 3){
        printf("RED SCORES %f\n",result[min]);
    }
    return 0;
}
