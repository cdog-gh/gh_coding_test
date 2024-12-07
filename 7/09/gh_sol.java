import java.util.*;
class Main {
    static long M = 1000000007;
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int [][]dp = new int[201][300001];
        int n = sc.nextInt();
        dp[0][0] = 1;
        for(int i=1; i<=n; i++){
            long a = sc.nextLong(); long m = sc.nextLong();
            long cost = (96 * a * m) / 60000;
            for(int j=0; j<=300000; j++){
                dp[i][j] = dp[i-1][j];
                if(j >= cost) dp[i][j] += dp[i-1][j-(int)cost];
                dp[i][j] %= M;
            }
        }
        long ans = 0;
        int c1 = sc.nextInt(); int c2 = sc.nextInt();
        for(int i=c1; i<=c2; i++)
            ans = (ans + dp[(int)n][i]) % M;
        System.out.println(ans);
    }
}