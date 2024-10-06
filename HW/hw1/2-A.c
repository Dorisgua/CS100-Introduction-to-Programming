#include <stdio.h>
int main()
{
    int a; // Store the number of students in classes A, B, and C.
    float x1,x2;
    char ch1,ch2;
    float s1,v1,s2,v2,t3,s3,s;
    scanf("%d\n", &a);
    scanf("%f-%c\n", &x1,&ch1);
    scanf("%f-%c", &x2,&ch2);
    //printf("%.3f",b);
    while (1){
        if (ch1 == 'H'){
            s1 = 3*x1-0.5*0.2*x1*x1;
            v1 = 3-0.2*x1;
            if (v1<=0){
                break;
            }
            s2 = v1*(x2-x1)-0.5*0.1*(x2-x1)*(x2-x1);
            v2 = v1-0.1*(x2-x1);
            if (v2<=0){
                break;
            }
            t3 = v2/0.2;
            s3 = v2*t3-0.5*0.2*t3*t3;
            s = s1+s2+s3;
            //printf("%.3f\n",x1);
            // printf("%.3f\n",s1);
            //printf("%.3f\n",s);
            printf("The stone has slided for %.3fm\n",s);
        }
        //if (ch1 == 'W')
        if (ch1 == 'W'){
            s1 = 3*x1-0.5*0.2*x1*x1;
            v1 = 3-0.2*x1;
            if (v1<=0){
                break;
            }
            s2 = v1*(x2-x1)-0.5*0.2*(x2-x1)*(x2-x1);
            v2 = v1-0.1*(x2-x1);
            if (v2<=0){
                break;
            }
            t3 = v2/0.2;
            s3 = v2*t3-0.5*0.2*t3*t3;
            s = s1+s2+s3;
            //printf("%.3f\n",s);
            printf("The stone has slided for %.3fm\n.",s);
        }
        break;
    }
    return 0;
}
