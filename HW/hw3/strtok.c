#include <stdio.h> 
#include <string.h> 
//���ո����ķ��ŷָ
int main () 
{ 
char jump[] ="1Tq+3Tx"; 
const char* split = "+"; 
char* a; 
int len;
a = strtok(jump,split); 
while(a!=NULL)
{ 
    len=strlen(a);
    printf("%s\n",a);
    printf("%d\n",len);
    a=strtok(NULL,split); 
} 
getchar(); 
return 0; 
} 