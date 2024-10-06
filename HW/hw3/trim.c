#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//É¾³ý×Ö·û´®Ê×Î²¿Õ¸ñ
void trim(char *S, char *s){
    int m, n ;
    m = 0;
    n = strlen(S) - 1;
    while(S[m] == ' ')
        ++m;
    while(S[n] == ' ')
        --n;
    strncpy(s,S+m,n-m+1);
    s[n-m+1] ='\0';
}

void main(){
    char *S = "   ak kl  p  ";
    char s[100];
    trim(S,s);
    printf("%s\n",s);
    system("pause");
}