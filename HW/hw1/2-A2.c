#include <stdio.h>
int main()//256accept
{
    int num; //次数 shi
    float current_s = 0,current_v = 3,a = 0.2,before_v = 3,before_s = 0,s3 = 0,t;
    int k;
    scanf("%d", &num);
    float arr[num];
    char cha[num];
    if (num == 0){
        current_s = 22.5;
        printf("The stone has slided for %.3fm\n",current_s);
        return 0;
    }
    for(k = 0;k<num;k++){
        scanf("%f-%c", &arr[k],&cha[k]);
        before_s = before_v*(arr[k]-arr[k-1])-0.5*a*(arr[k]-arr[k-1])*(arr[k]-arr[k-1]);
        current_s = current_s+before_s;
        current_v = before_v-a*(arr[k]-arr[k-1]);
        before_v = current_v;
        if (cha[k] == 'H'){
            a = 0.1;
        }
        if (cha[k] == 'W'){
            a = 0.2;
        }
        //printf("before_s:%.3f\n",before_s);
        //printf("before_v:%.3f\n",before_v);
    }
    if (before_v>0){
        t = before_v/a;
        s3 = before_v*t-0.5*a*t*t;
    }
    current_s = current_s+s3;
    printf("The stone has slided for %.3fm\n",current_s);
    return 0;
}
