#include <stdio.h>
#include <math.h>
int main()//well
{
    float result[6],tmp;
    int result2[6];
    float x[6];
    float y[6];
    //int num[6];
    int k,i,tmp2,score = 1;
    for(k = 0;k<6;k++){
        scanf("(%f,%f)", &x[k],&y[k]);
        getchar();
        result[k]=hypot(x[k],y[k]);
        result2[k]=k+1;
    }
    for(k=0; k<6; k++){
        for(i=k; i<6; i++) 
		{
            if(result[k] > result[i]) 
            { 
                tmp = result[k]; 
                result[k] = result[i]; 
                result[i] = tmp; 

                tmp2 = result2[k]; 
                result2[k] = result2[i]; 
                result2[i] = tmp2; 
            }
		}
	} 
    for(k=0;k<6;k++){
        if(result[k]>1.8){
            result[k] = 100;
        }
    }
    if(result[0]>1.8&&result[1]>1.8&&result[2]>1.8&&result[3]>1.8&&result[4]>1.8&&result[5]>1.8){
        printf("BLANK END\n");
        return 0;
    }
    if(result2[0]<=3&&result[0]<1.8){
        if (result2[1]<=3&&result[1]<1.8){
            score = 2;
            if (result2[2]<=3&&result[2]<1.8)
                score = 3;
            }
        printf("RED SCORES %d\n",score);
    }
    else if(result2[0]<=3&&result[0]>1.8){
        printf("BLANK END\n");
        return 0;
    }
    else if(result2[0]>3&&result[0]<1.8){
        if (result2[1]>3&&result[1]<1.8){
            score = 2;
            if (result2[2]>3&&result[2]<1.8)
                score = 3;
            }
        printf("YELLOW SCORES %d\n",score);
    }
    else{
        printf("BLANK END\n");
        return 0;
    }
    return 0;
}
