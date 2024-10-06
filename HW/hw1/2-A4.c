#include <stdio.h>
int main(){
    int num; //次数 
    int k;//用来循环
    float current_s,a = 0.2,current_v = 3,before_v = 3,current_v2 = 3,t,sjia;
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
        getchar();
    }
    for(k = 0;k<num;k++){
        current_v2 = before_v-a*(arr[k]-arr[k-1]);
        if (current_v2<0){
            t = current_v/a;
            sjia = current_v*t-0.5*a*t*t;
            current_v =0;
            //printf("sjia: %.3fm\n",sjia);
        }
        else{
            current_v = current_v2;
            sjia = before_v*(arr[k]-arr[k-1])-0.5*a*(arr[k]-arr[k-1])*(arr[k]-arr[k-1]);
            //printf("sjia: %.3fm\n",sjia);
        }
        before_v = current_v;
        //最后再换a
        if (cha[k] == 'H'){
            a = 0.1;
        }
        if (cha[k] == 'W'){
            a = 0.2;
        }
        current_s = current_s+sjia;
        if (current_v<=0){
            printf("hahaha");
            return 0;
        }
        //printf("The stone has slided for %.3fm\n",current_s);
    }
    if (current_v>0){
            t = current_v/a;
            sjia = current_v*t-0.5*a*t*t;
            current_s = current_s+sjia;
            //printf("sjia: %.3fm\n",sjia);
        }
    printf("The stone has slided for %.3fm\n",current_s);

}