#include <stdio.h>
#include <string.h>
 
#define SEGNO 1
#define DAL_SEGNO 2
#define SEGNO_OR_DAL_SEGNO 3
 
long long A[500001], sum[500001], dp[500001];
char B[500001];
 
int isNumber(char *str){
    return !(str[0]=='D' || str[0]=='S' || str[0]=='o');
}
 
long long getNumber(char *str){
    int flag=0;
    if(str[0]=='-'){
        flag=1;
    }
    long long res=0;
    for(int i=flag; str[i]; ++i){
        res*=10;
        res+=(int)(str[i]-'0');
    }
    return flag ? -res : res;
}
 
int main(void){
    int N;
    char prev[10], str[10];
 
    scanf("%d", &N);
    int idx=1;
    while(scanf("%s", str)!=EOF){
        if(isNumber(str)){
            A[idx]=getNumber(str);
            ++idx;
        }
        else{
            if(!strcmp(prev, "or")){
                A[idx]=0;
                B[idx]=SEGNO_OR_DAL_SEGNO;
                ++idx;
            }
            else{
                if(!strcmp(str, "S")){
                    A[idx]=0;
                    B[idx]=SEGNO;
                    ++idx;
                }
                else if(!strcmp(str, "DS")){
                    A[idx]=0;
                    B[idx]=DAL_SEGNO;
                    ++idx;
                }
                else if(!strcmp(str, "or")){
                    --idx;
                }
            }
        }
        strcpy(prev, str);
    }
    --idx;
    long long ssum=0;
    for(int i=1; i<=N; ++i){
        sum[i]=sum[i-1]+A[i];
        ssum+=A[i];
    }
 
    // S S or S or 0
    long long tmp, min, max, res=ssum;
 
    // DS or DS S
    max=0;
    for(int i=1; i<=N; ++i){
        if((B[i]==DAL_SEGNO || B[i]==SEGNO_OR_DAL_SEGNO) && max<sum[i]){
            max=sum[i];
        }
    }
    if(res<ssum+max){
        res=ssum+max;
    }
 
    // S DS
    max=0x8000000000000000;
    tmp=min=0;
    for(int i=1; i<=N; ++i){
        if((B[i]==SEGNO || B[i]==SEGNO_OR_DAL_SEGNO) && min>sum[i]){
            min=sum[i];
            max=0x8000000000000000;
        }
        if((B[i]==DAL_SEGNO || B[i]==SEGNO_OR_DAL_SEGNO) && max<sum[i]){
            max=sum[i];
            if(tmp<max-min){
                tmp=max-min;
            }
        }
    }
    if(res<ssum+tmp){
        res=ssum+tmp;
    }
 
    printf("%lld", res);
 
    return 0;
}
