#include <stdio.h>
int Inner[303][303];
int Outer[303][303];
int main(void)
{
    for(int s=201; s<=243; s++)
    {
        for(int j=1; j<=42; j++){
            int e1 = (s + j);
            if(e1 > 243) e1 -= 43;
            int e2 = (s - j);
            if(e2 < 201) e2 += 43;
            Inner[s][e1] = j;
            Outer[s][e2] = j;
        }
    }
    int Q, a, b; scanf("%d", &Q);
    for(int i=0; i<Q; i++){
        scanf("%d%d", &a, &b);
        if(Inner[a][b] < Outer[a][b])
            printf("Inner circle line\n");
        else
            printf("Outer circle line\n");
    }
}