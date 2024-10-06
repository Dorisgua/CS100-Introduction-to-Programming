#include<stdio.h>
#include<string.h>
enum JumpType {
    T, S, Lo, F, Lz, A
};
static double scoreTable[4][6] = { {0.4, 0.4, 0.5, 0.5, 0.6, 1.1},
                                   {1.3, 1.3, 1.7, 1.8, 2.1, 3.3},
                                   {4.2, 4.3, 4.9, 5.3, 5.9, 8.0},
                                   {9.5, 9.7, 10.5, 11.0, 11.5, 12.5} };
//Score(2,T);
double Score(int rotations, enum JumpType type){
    if (rotations < 1 || rotations > 4){
        return -1;
    }
    return scoreTable[rotations - 1][type];
}
double getpoints(char jump[100])
{
    char* a;
    const char* split = "+";
    double score,score1=0;
    int len1,flag=0;
    a=strtok(jump,split); 
    while(a!=NULL)//对于每一跳
    { 
        score=0;
        len1=strlen(a);
        if(len1==2&&a[0]-48>0&&a[0]-48<5){
            if(a[1]=='T'){
                score=Score(a[0]-48,T);
            }
            else if(a[1]=='S'){
                score=Score(a[0]-48,S);
            }
            else if(a[1]=='A'){
                score=Score(a[0]-48,A);
            }
            else if(a[1]=='F'){
                score=Score(a[0]-48,F);
            }
            else{
                flag=-1;
            }
        }
        else if(len1==3&&a[0]-48>0&&a[0]-48<5){
            if(a[1]=='T'&&a[2]=='q'){
                score=Score(a[0]-48,T);
            }
            else if(a[1]=='S'&&a[2]=='q'){
                score=Score(a[0]-48,S);
            }
            else if(a[1]=='A'&&a[2]=='q'){
                score=Score(a[0]-48,A);
            }
            else if(a[1]=='T'&&a[2]=='<'){
                score=Score(a[0]-48,T)*0.7;
            }
            else if(a[1]=='S'&&a[2]=='<'){
                score=Score(a[0]-48,S)*0.7;
            }
            else if(a[1]=='A'&&a[2]=='<'){
                score=Score(a[0]-48,A)*0.7;
            }
            else if((a[1]=='F'&&a[2]=='!')||(a[1]=='F'&&a[2]=='q')){
                score=Score(a[0]-48,F);
            }
            else if((a[1]=='F'&&a[2]=='<')||(a[1]=='F'&&a[2]=='e')){
                score=Score(a[0]-48,F)*0.7;
            }
            else if(a[1]=='L'&&a[2]=='o'){
                score=Score(a[0]-48,Lo);
            }
            else if(a[1]=='L'&&a[2]=='z'){
                score=Score(a[0]-48,Lz);
            }
            else{
                flag=-1;
            }
        }
        else if(len1==4&&a[0]-48>0&&a[0]-48<5){
            if(a[0]-48>1&&a[0]-48<5&&a[1]=='T'&&a[2]=='<'&&a[3]=='<'){
                score=Score(a[0]-48-1,T);
            }
            else if(a[0]-48>1&&a[0]-48<5&&a[1]=='S'&&a[2]=='<'&&a[3]=='<'){
                score=Score(a[0]-48-1,S);
            }
            else if(a[0]-48>1&&a[0]-48<5&&a[1]=='A'&&a[2]=='<'&&a[3]=='<'){
                score=Score(a[0]-48-1,A);
            }
            else if(a[0]-48==1&&(a[1]=='T'||a[1]=='S'||a[1]=='A')&&a[2]=='<'&&a[3]=='<'){
                score=0;
            }
            else if(a[1]=='F'&&a[2]=='!'&&a[3]=='q'){
                score=Score(a[0]-48,F);
            }
            else if((a[1]=='F'&&a[2]=='!'&&a[3]=='<')||(a[1]=='F'&&a[2]=='e'&&a[3]=='q')){
                score=Score(a[0]-48,F)*0.7;
            }
            else if(a[1]=='F'&&a[2]=='e'&&a[3]=='<'){
                score=Score(a[0]-48,F)*0.49;
            }
            else if(a[0]-48>1&&a[0]-48<5&&a[1]=='F'&&a[2]=='<'&&a[3]=='<'){
                score=Score(a[0]-48-1,F);
            }
            else if(a[0]-48==1&&a[1]=='F'&&a[2]=='<'&&a[3]=='<'){
                score=0;
            }
            else if(a[1]=='L'&&a[2]=='o'&&a[3]=='q'){
                score=Score(a[0]-48,Lo);
            }
            else if(a[1]=='L'&&a[2]=='o'&&a[3]=='<'){
                score=Score(a[0]-48,Lo)*0.7;
            }
            else if(a[1]=='L'&&a[2]=='z'&&(a[3]=='q'||a[3]=='!')){
                score=Score(a[0]-48,Lz);
            }
            else if(a[1]=='L'&&a[2]=='z'&&(a[3]=='e'||a[3]=='<')){
                score=Score(a[0]-48,Lz)*0.7;
            }
            else{
                flag=-1;
            }
        }
        else if(len1==5&&a[0]-48>0&&a[0]-48<5){
            if(a[0]-48==1&&a[1]=='F'&&a[2]=='!'&&a[3]=='<'&&a[4]=='<'){
                score=0;
            }
            else if(a[0]-48>1&&a[0]-48<5&&a[1]=='F'&&a[2]=='!'&&a[3]=='<'&&a[4]=='<'){
                score=Score(a[0]-48-1,F);
            }
            else if(a[0]-48==1&&a[1]=='F'&&a[2]=='e'&&a[3]=='<'&&a[4]=='<'){
                score=0;
            }
            else if(a[0]-48>1&&a[0]-48<5&&a[1]=='F'&&a[2]=='e'&&a[3]=='<'&&a[4]=='<'){
                score=Score(a[0]-48-1,F)*0.7;
            }
            else if(a[0]-48==1&&a[1]=='L'&&a[2]=='o'&&a[3]=='<'&&a[4]=='<'){
                score=0;
            }
            else if(a[0]-48>1&&a[0]-48<5&&a[1]=='L'&&a[2]=='o'&&a[3]=='<'&&a[4]=='<'){
                score=Score(a[0]-48-1,Lo);
            }
            else if(a[1]=='L'&&a[2]=='z'&&a[3]=='!'&&a[4]=='q'){
                score=Score(a[0]-48,Lz);
            }
            else if(a[1]=='L'&&a[2]=='z'&&(a[3]=='!'&&a[4]=='<')||(a[3]=='e'&&a[4]=='q')){
                score=Score(a[0]-48,Lz)*0.7;
            }
            else if(a[0]-48>1&&a[0]-48<5&&a[1]=='L'&&a[2]=='z'&&a[3]=='<'&&a[4]=='<'){
                score=Score(a[0]-48-1,Lz);
            }
            else if(a[0]-48==1&&a[1]=='L'&&a[2]=='z'&&a[3]=='<'&&a[4]=='<'){
                score=0;
            }
            else{
                flag=-1;
            }
        }
        else if(len1==6&&a[0]-48>0&&a[0]-48<5){
            if(a[0]-48==1&&a[1]=='L'&&a[2]=='z'&&a[3]=='!'&&a[4]=='<'&&a[5]=='<'){
                score=0;
            }
            else if(a[0]-48>1&&a[0]-48<5&&a[1]=='L'&&a[2]=='z'&&a[3]=='!'&&a[4]=='<'&&a[5]=='<'){
                score=Score(a[0]-48-1,Lz);
            }
            else if(a[0]-48==1&&a[1]=='L'&&a[2]=='z'&&a[3]=='e'&&a[4]=='<'&&a[5]=='<'){
                score=0;
            }
            else if(a[0]-48>1&&a[0]-48<5&&a[1]=='L'&&a[2]=='z'&&a[3]=='e'&&a[4]=='<'&&a[5]=='<'){
                score=Score(a[0]-48-1,Lz)*0.7;
            }
            else{
                flag=-1;
            }
        }
        else{
            flag=-1;//不合法的情况
        }
        if(score>=0){
            score1+=score;
        }
        a=strtok(NULL,split); 
    }
    if(flag==-1){
        return -1;
    }
    else{
        return score1;
    }
}

int main(){
double score,score1,ans;
int loop,len,num;
char jump[10010];
for(loop=1;loop<=3;loop++)//每一行
{
    memset(jump,0,sizeof(jump));
    gets(jump);
    num=0;
    len=strlen(jump);
    for(int i=0;i<len;i++)//统计+的个数
    {
        if(jump[i]=='+') num++;
    }
    if(num>=3)//+个数大于三个
    {
        printf("0.00\n");
        continue;
    }
    if(jump[0]=='+'||jump[len-1]=='+'){
        printf("0.00\n");
    }
    else if(jump[len-1]=='x')//最后一位是x的情况
    {
        jump[len-1]='\0';
        ans=getpoints(jump);
        if(ans==-1){
            printf("0.00\n");
        }
        else{
            printf("%.2lf\n",ans*1.1);
        }
        continue;
    }
    else{
        ans=getpoints(jump);
        if(ans==-1){
            printf("0.00\n");
        }
        else{
            printf("%.2lf\n",ans);
        }
        continue;
    }
}
return 0;
}
