#include<stdio.h>
#include<string.h>
char pai[20];
int ans=0,T,n,num,ans;
void dfs(int a)
{
    if(a>ans) return;
    /*printf("%d\n",a);
    for(int i=1;i<15;++i)
    {
        printf("%d%c",pai[i],i^14?' ':'\n');
    }*/
    //˳��
    int flag=0;
    for(int i=3;i<=14;i++){//��˳��
        if(pai[i]==0) flag=0;
        else{
            flag++;
            if(flag>=5){
                for(int j=i-flag+1;j<=i;j++) pai[j]--;
                dfs(a+1);
                for(int j=i-flag+1;j<=i;j++) pai[j]++;
            }
        }
    }
    flag=0;
    for(int i=3;i<=14;i++){//˫˳��
        if(pai[i]<2) flag=0;
        else{
            flag++;
            if(flag>=3){
                for(int j=i-flag+1;j<=i;j++) pai[j]-=2;
                dfs(a+1);
                for(int j=i-flag+1;j<=i;j++) pai[j]+=2;
            }
        }
    }
    flag=0;
    for(int i=3;i<=14;i++){//��˳��
        if(pai[i]<3) flag=0;
        else{
            flag++;
            if(flag>=2){
                for(int j=i-flag+1;j<=i;j++) pai[j]-=3;
                dfs(a+1);
                for(int j=i-flag+1;j<=i;j++) pai[j]+=3;
            }
        }
    }
    //����
    for(int i=3;i<=15;i++){//����һ��
        if(pai[i]==3||pai[i]==4){
            pai[i]-=3;
            for(int j=3;j<=15;j++){
                if(pai[j]>=2&&j!=i){
                    pai[j]-=2;
                    dfs(a+1);
                    pai[j]+=2; 
                }
            }
            pai[i]+=3;
        }
    }
    for(int i=3;i<=15;i++){//����һ
        if(pai[i]==3||pai[i]==4){
            pai[i]-=3;
            for(int j=3;j<=16;j++){
                if(pai[j]>=1&&j!=i){
                    pai[j]-=1;
                    dfs(a+1);
                    pai[j]+=1;    
                }
            }
            pai[i]+=3;
        }
    }
    for(int i=3;i<=15;i++){//������
        if(pai[i]==3||pai[i]==4){
            pai[i]-=3;
            dfs(a+1);
            pai[i]+=3;
        }
    }
    for(int i=3;i<=15;i++){//�Ĵ���
        if(pai[i]==4){
            pai[i]-=4;
            for(int j=3;j<=16;j++){
                if(pai[j]>=1&&j!=i){
                    pai[j]--;
                    for(int k=3;k<=16;k++){
                        if(pai[k]>=1&&k!=i&&k!=j){
                            pai[k]--;
                            dfs(a+1);
                            pai[k]++;
                        }
                    }
                    pai[j]++; 
                }
            }
            pai[i]+=4;
        }
    }
    for(int i=3;i<=15;i++){//�Ĵ�����
        if(pai[i]==4){
            pai[i]-=4;
            for(int j=3;j<=15;j++){
                if(pai[j]>=2&&j!=i){
                    pai[j]-=2;
                    for(int k=3;k<=15;k++){
                        if(pai[k]>=2&&k!=i&&k!=j){
                            pai[k]-=2;
                            dfs(a+1);
                            pai[k]+=2;
                        }
                    }
                    pai[j]+=2; 
                }
            }
            pai[i]+=4;
        }
    }
    for(int i=3;i<=15;i++){//������
        if(pai[i]==4){
            pai[i]-=4;
            dfs(a+1);
            pai[i]+=4;
        }
    }
    for(int i=3;i<=16;i++){
        if(pai[i]>0){
            a++;
        }
    }
    if(ans>a) ans=a;
    else ans=ans;
}

int main()
{
    scanf("%d%d",&T,&n);
    for(int i=0;i<T;i++)//T��
    {
        ans=50;
        memset(pai,0,sizeof(pai));
        for(int j=0;j<n;j++)//ÿһ��
        {
            scanf("%d",&num);
            if(num==2){
                pai[15]++;
            }
            else if(num==1){
                pai[14]++;
            }
            else if(num==14){
                pai[16]++;
            }
            else pai[num]++;
        }
        dfs(0);
        printf("%d\n",ans);
    }
}