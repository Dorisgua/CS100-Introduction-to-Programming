#include <stdio.h>
int main()//256accept,0考虑到了。
{
    int num; //次数 shi
    float current_s = 0,current_v = 3,a = 0.2,before_v = 3,before_s = 0,s3 = 0,t,t2,current_s2;
    int k;
    scanf("%d", &num);
    float arr[num];
    char cha[num];
    while(1){
    if (num == 0){
        current_s = 22.5;
        printf("The stone has slided for %.3fm\n",current_s);
        return 0;
    }
    for(k = 0;k<num;k++){
        scanf("%f-%c", &arr[k],&cha[k]);
        before_s = before_v*(arr[k]-arr[k-1])-0.5*a*(arr[k]-arr[k-1])*(arr[k]-arr[k-1]);
        //printf("before_s:%.3f\n",before_s);
        current_s2 = current_s;
        current_s = current_s+before_s;
        current_v = before_v-a*(arr[k]-arr[k-1]);
        if (current_v<=0){
            current_s = current_s2;
            t2 = before_v/a;
            s3 = before_v*t2-0.5*a*t2*t2;
            break;
        }
        before_v = current_v;
       
        if (cha[k] == 'H'){
            a = 0.1;
        }
        if (cha[k] == 'W'){
            a = 0.2;
        }
        //while (num[k]<30){
          //  printf("The stone has slided for %.3fm\n",current_s);
            //return 0;
         //}
        printf("before_s:%.3f\n",before_s);
        printf("before_v:%.3f\n",before_v);
    }
    if ((current_v>0) && before_v>0){
        //printf("before_v:%.3f\n",before_v);
        t = before_v/a;
        s3 = before_v*t-0.5*a*t*t;
        //printf("s3:%.3f\n",s3);
        //printf("current_s:%.3f\n",current_s);
        }
        break;
    }
    current_s = current_s+s3;
    printf("The stone has slided for %.3fm\n",current_s);
    return 0;
}
