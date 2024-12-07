import java.util.*;
import java.lang.Math;
class Main {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        long []F = {1L, 4L, 16L, 64L, 256L, 1024L};
        long []E = new long[50001];
        long mod = 1000000007L;
        E[0] = 1;
        for(int i=1; i<=50000; i++) E[i] = (8 * E[i-1]) % mod;
        long [][]C = new long[50001][11];

        for(int i=1; i<=50000; i++)
        {
            C[i][0] = 1; if(i <= 10) C[i][i] = 1;
        }
        for(int i=2; i<=50000; i++)
        {
            for(int j=1; j<Math.min(11, i); j++)
            {
                C[i][j] = C[i-1][j-1] + C[i-1][j];
                C[i][j] %= mod;
            }
        }
        int lv = sc.nextInt();

        if(lv <= 5) System.out.println(F[lv]);
        else
        {
            // (lvC0 + lvC1 + ... + lvC6) * 8^lv
            long a = C[lv][0] + C[lv][1] + C[lv][2] + C[lv][3] + C[lv][4] + C[lv][5] + C[lv][6];
            a %= mod;
            long b = E[lv];
            long ans = (a * b) % mod;
            System.out.println(ans);
        }
    }
}