#include <stdio.h>
#include <tuple>
#include <queue>
using namespace std;
typedef tuple<int,int,int> proc_data;
priority_queue <proc_data> pq;
int main(void)
{
    int n,T; scanf("%d%d",&T,&n);
    for(int i=0;i<n;i++){
        int id, t, prio;
        scanf("%d%d%d",&id,&t,&prio);
        pq.push(make_tuple(prio,-id,t));
    }
    for(int i=0;i<T;i++){
        proc_data pd = pq.top(); pq.pop();
        printf("%d\n",-get<1>(pd));
        if(get<2>(pd) -1 > 0)
            pq.push(make_tuple(get<0>(pd)-1, get<1>(pd), get<2>(pd)-1));
    }
}