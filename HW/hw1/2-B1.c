#include <stdio.h>
#include <math.h>
int main()
{
    float result[6],result2[6],t;
    float x[6];
    float y[6];
    int num[6];
    int k,j;
    for(k = 0;k<6;k++){
        scanf("(%f,%f)", &x[k],&y[k]);
        getchar();
        result[k]=hypot(x[k],y[k]);
        result2[k]=k;
    }

    for(k=0;k<6;k++){
        for (j=k+1;j<6;j++)
            if(result2[k]>result2[j])    //如果前一个数比后一个数大，则利用中间变量t实现两值互换
            {
                t=result2[k];
                result2[k]=result2[j];
                result2[j]=t;
                num[k] = j;
            }
    }
    for(k=0;k<6;k++){
        printf("%f\n", result2[k]);  
        printf("1:%f\n", result[k]);  
        printf("%d\n", num[k]);  
    }
    return 0;
}

