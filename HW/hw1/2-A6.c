#include <stdio.h>
int main(){
    int num; //次数 
    int k;//用来循环
    float current_s,a = 0.2,current_v = 3,before_v = 3,current_v2 = 3,t,sjia;
    scanf("%d", &num);
    float arr[num];
    char cha[num];
    
    if (num!=0){
        for(k = 0;k<num;k++){
            scanf("%f-%c", &arr[k],&cha[k]);
            getchar();
            //getchar();
            current_v2 = before_v-a*(arr[k]-arr[k-1]);
            if (current_v2<=0){
                t = before_v/a;
                sjia = current_v*t-0.5*a*t*t;
                current_v =0;
                current_s = current_s+sjia;
                break;
                //printf("sjia: %.3fm\n",sjia);
            }
            else{
                current_v = current_v2;
                sjia = before_v*(arr[k]-arr[k-1])-0.5*a*(arr[k]-arr[k-1])*(arr[k]-arr[k-1]);
                before_v = current_v;
                //current_v = arr[k];
                //printf("sjia: %.3fm\n",sjia);
                if (cha[k] == 'H'){
                    a = 0.1;
                }
                if (cha[k] == 'W'){
                    a = 0.2;
                }
                current_s = current_s+sjia;
            }
            //printf("current_s: %.3fm\n",current_s);
            if (current_v<=0){
                break;
            }
        }  
    }
    else if (num == 0){
        current_s = 22.5;
        printf("The stone has slided for %.3fm\n",current_s);
        return 0;
    } 
    if (current_v>0){
        t = current_v/a;
        //printf("a:%f\n",a);
        //printf("current_v:%f",current_v);
        sjia = current_v*t-0.5*a*t*t;
        current_s = current_s+sjia;
        //printf("sjia: %.3fm\n",sjia);
    }
    printf("The stone has slided for %.3fm\n",current_s);
    return 0;
}