import java.util.*;
public class Main {
    public static void main(String []args){
        long M = 998244353;
        long [][]dp = new long[55000][7];
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        long mi = 0;
        dp[0][0] = 1;
        for(int i=1; i<=n; i++){
            for(int j=0; j<=6; j++){
                //dp[i-1][j] -> dp[i][j] :: 6*
                dp[i][j] += dp[i-1][j] * 6;
                if(j > 0) dp[i][j] += dp[i-1][j-1];
                //dp[i-1][j-1] -> dp[i][j] :: 1*
                dp[i][j] %= M;
            }
        }
        for(int i=0; i<=6; i++)
            mi += dp[n][i];
        mi %= M;
        long tot = 1;
        for(int i=1; i<=n; i++) {
            tot *= 7;
            tot %= M;
        }
        long ans = (tot - mi + M) % M;
        System.out.println(ans);
    }
}
