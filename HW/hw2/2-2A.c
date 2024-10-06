#include <stdio.h>
#include <math.h>
void add(int a, int b){//7没过
    // YOUR CODE HERE
    float judge = a+b,judgea = a,judgeb = b;
    int number = a+b,len = 0,i,j,k,lena = 0,lenb = 0;//len 是 a+b 位数

    while(judge>=1){
        len++;
        judge =judge/10;
    }
    while(judgea>=1){
        lena++;
        judgea =judgea/10;
    }
    while(judgeb>=1){
        lenb++;
        judgeb =judgeb/10;
    }
    //printf("%d\n",len);
    //第一行
    for (k = 0;k<len+2-lena;k++){
        printf(" ");
    }
    printf("%d\n",a);
    //第二行
    printf("+");
    for (j = 0;j<len+1-lenb;j++){
        printf(" ");
    }
    printf("%d\n",b);
    //第三行
    for (i = 0;i<len+2;i++){
        printf("-");
    }
    if(a==0&&b==0){
        printf("-");
    }
    printf("\n");
    //最后一行
    printf("  %d\n",number);
    return;
}

void subtract(int a, int b){
    // YOUR CODE HERE
    float judge = a-b,judgea = a,judgeb = b;
    int number = a-b,len = 0,i,j,k,lena = 0,lenb = 0,len1 = 0;//len 是 a+b 位数
    //len1是number的位数
    if(a ==0 &&b==0){
        printf("  0\n");
        printf("- 0\n");
        printf("---\n");
        printf("  0\n");
        return;
    }
    while(judge>=1||judge<=-1){//判断number位数
        len++;
        len1++;
        judge =judge/10;
    }
    while(judgea>=1||judgea<=-1){
        lena++;
        judgea =judgea/10;
    }
    while(judgeb>=1||judgeb<=-1){
        lenb++;
        judgeb =judgeb/10;
    }
    if(number<0){
        len++;
        len1++;
    }
    if(a<0){
        lena++;
    }
    if(b<0){
        lenb++;
    }
    if (a==b){
        len = 1;
    }
    //len  = max(len,lena,lenb);
    if (lena>len){
        len = lena;
    }
    if (lenb>len){
        len = lenb;
    }
    //printf("%d",len);
    //第一行
    for (k = 0;k<len+2-lena;k++){
        printf(" ");
    }
    printf("%d\n",a);
    //第二行
    printf("-");
    for (j = 0;j<len+1-lenb;j++){
        printf(" ");
    }
    printf("%d\n",b);
    //第三行
    for (i = 0;i<len+2;i++){
        printf("-");
    }
    printf("\n");
    //最后一行
    int ddd;
    if(a==b){
        for (ddd = 0;ddd<len-len1+1;ddd++){
            printf(" ");
        }
    printf("%d\n",number);
    }
    else{
        printf("  %d\n",number);
    }
    
    return;
}

void multiply(int a, int b){
    // YOUR CODE HERE
    float judge = a*b,judgea = a,judgeb = b;
    int number = a*b,len = 0,i,j,k,lena = 0,lenb = 0,lena1 = 0,lenb1 = 0;//len 是 a+b 位数

    //lenb 是包括符号的b 的长度，lenb1不包括
    if (a==0 &&b==0){
        printf("  0\n");
        printf("x 0\n");
        printf("---\n");
        printf("---\n");
        printf("  0\n");
        return;
    }
    while(judge>=1||judge<=-1){//判断number位数
        len++;
        judge =judge/10;
    }
    while(judgea>=1||judgea<=-1){
        lena++;
        lena1++;
        judgea =judgea/10;
    }
    while(judgeb>=1||judgeb<=-1){
        lenb++;
        lenb1++;
        judgeb =judgeb/10;
    }
    if(number<0){
        len++;
    }
    if(a<0){
        lena++;
    }
    if(b<0){
        lenb++;
    }
    
    //第一行
    for (k = 0;k<len+2-lena;k++){
        printf(" ");
    }
    printf("%d\n",a);
    //第二行
    printf("x");
    for (j = 0;j<len+1-lenb;j++){
        printf(" ");
    }
    printf("%d\n",b);
    //第三行
    for (i = 0;i<len+2;i++){
        printf("-");
    }
    printf("\n");
    //第四行到倒数第三行
    int cheng[lenb1],lencheng = 0,w,m = 0,lencheng1 = 0,judgecheng;
    for (m = 0;m<lenb1;m++){
        lencheng = m;
        //printf("m:%d\n",m);
        int shu = pow(10,m);
        //printf("10^m:%d\n",shu);
        cheng[m] = (b/shu%10)*a;//分别取个位十位百位
        //printf("cheng[m]:%d\n",cheng[m]);
        //求lencheng
        judgecheng = cheng[m];
        while(judgecheng>=1||judgecheng<=-1){
            lencheng++;
            lencheng1++;
            judgecheng =judgecheng/10;
        }
        if(cheng[m]<0){
            lencheng++;//lencheng是带符号的cheng[m]的长度
        }
        //printf("len+2-lencheng1:%d\n",len+2-lencheng1);
        //printf("lencheng1:%d\n",lencheng1);
        if(cheng[m]!=0){
            for(w=0;w<len+2-lencheng;w++){
                printf(" ");
            }
            printf("%d\n",cheng[m]);
        }
        
    }
    //倒数第二行
    for (i = 0;i<len+2;i++){
        printf("-");
    }
    printf("\n");
    //最后一行
    printf("  %d\n",number);
    return;
}

int main(){
    int a, b;
    char op;
    scanf("%d %c %d", &a, &op, &b);
    switch (op) {
        case '+':
            add(a, b);
            break;
        case '-':
            subtract(a, b);
            break;
        case 'x':
            multiply(a, b);
            break;
        default:
            printf("Sample input: 12 + 34");
    }
    return 0;
}