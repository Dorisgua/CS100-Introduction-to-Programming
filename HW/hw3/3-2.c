#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//删除首尾空格
void trim(char *Sp, char *s){
    int m, n ;
    m = 0;
    n = strlen(Sp) - 1;
    while(Sp[m] == ' ')
        ++m;
    while(Sp[n] == ' ')
        --n;
    strncpy(s,Sp+m,n-m+1);
    s[n-m+1] ='\0';
}
int main()
{
    freopen("3-2.out","w",stdout);
    int n,i,j,k,l,p=0,q=0,r=0,len,num=0,num2=0;
    char S[10000];
    char* Sp;
    char s[10000];
    const char* split=";";
    scanf("%d\n",&n);
    for(i=0;i<n;i++)
    {
        gets(S);//每次取一行
        trim(S,S);
        len=strlen(S);
        p=0;
        q=0;
        r=0;
        k=num*4-num2*4;
        memset(s,0,sizeof(s));
        for(l=0;l<len;l++)
        {
            if(S[l]=='}')
            {
                p++;
                num2++;
            }
            if(S[l]==';')
            {
                q++;
            }
            if(S[l]=='{')
            {
                r++;
                num++;
            }
        }
        if((p==0&&q==0&&r!=0)||(p==0&&q!=0&&r!=0))//仅有{ 或有；和{的情况
        {
            if(k!=0)
            {
                printf("%*s",k," ");
            }
            for(j=len-1;j>0;j--)
            {
                if(S[j]!=' '&&S[j]!='{')
                {
                    S[j+1]=' ',S[j+2]='{',S[j+3]='\0';
                    break;
                }
            }
            printf("%s\n",S);
        }
        else if(p==0&&q!=0&&r==0)//仅有；的情况
        {
            Sp = strtok(S,split); 
            while(Sp!=NULL) 
            { 
            trim(Sp,s);
            if(k==0)
            {
                printf ("%s%c\n",s,';');
            }
            else
            {
                printf ("%*s%s%c\n",k," ",s,';');
            } 
            Sp = strtok(NULL,split); 
            } 
        }
        else if(p!=0&&q==0&&r==0)//仅有}的情况
        {
            if(k==4)
            {
                printf("%c\n",'}');
            }
            else
            {
                printf("%*s",k-4," ");
                printf("%c\n",'}');
            }
        }
        memset(S,0,sizeof(S));
    }
}