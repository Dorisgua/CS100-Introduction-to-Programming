#include<stdio.h>
#include<string.h>
#include<ctype.h>
char S[10000];
char s[10000];
char letter[10000];
char c;
char aim[10000];
char opposite[10000];
int main()
{
    int m,a,l,r,k,p,j,len,q,x,z,compare,i=0,flag=0;
    gets(S);
    scanf("%d", &m);
    for(i=0;i<m;i++)
    {
        scanf("%d", &a);
        if(a==0)
        {
            scanf("%d%d",&l,&r);
            if(l==r)
            {
                printf("Yes\n");
            }
            else
            {
                memset(aim,0,sizeof(aim));
                memset(letter,0,sizeof(letter));
                for(z=0;z<=r-l;z++)
                {
                    aim[z]=S[z+l];
                }
                z=0;
                //printf("%s\n",aim);
                len=strlen(aim);
                //printf("%d\n",len);
                p=0;
                for(j=0;j<len;j++)
                {
                    if((aim[j]>='a'&&aim[j]<='z')||(aim[j]>='A'&&aim[j]<='Z'))
                    {
                        letter[p]=aim[j];
                        p++;
                    }
                }
                //printf("%d\n",len1);
                for(q=0;q<p;q++)
                {
                    if(letter[q]>='A'&&letter[q]<='Z')
                    {
                        letter[q]=tolower(letter[q]);
                    }
                }
                q=0;
                //printf("%s\n",letter);
                memset(opposite,0,sizeof(opposite));
                for(x=0;x<p;x++)
                {
                    opposite[x]=letter[p-x-1];
                }
                
                //printf("%s\n",opposite);
                compare=strcmp(opposite,letter);
                if(compare==0)
                {
                    printf("Yes\n");
                }
                else
                {
                    printf("No\n");
                }
            }
        }
        else if(a==1)
        {
            scanf("%d", &k);
            getchar();
            scanf("%c", &c);
            S[k]=c;
            //printf("%c\n",c);
            //printf("%s",S);
        }
        else if(a==2)
        {
            getchar();
            gets(s);
            strcat(S,s);
            //printf("%s",S);
        }
    }
}