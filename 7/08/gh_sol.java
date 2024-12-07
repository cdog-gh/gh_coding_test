import java.util.*;
class Main {
    static long M = 1000000007;
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        long n = sc.nextLong(); sc.nextLine();
        long []ch = new long[128];

        String s = sc.nextLine();
        long ans = 0;
        for(int i=0; i<s.length(); i++)
            ch[s.charAt(i)]++;
        ans = combi_two(n);
        for(int i=0; i<128; i++){
            if(ch[i] < 2) continue;
            // System.out.println(ch[i]);
            long r = pow_two(ch[i]);
            r = (r - 1 + M) % M;
            r = (r - ch[i] + M) % M;
            r = (r - combi_two(ch[i]) % M + M) % M;
            // System.out.println(r);
            ans += r;
            ans %= M;
        }
        System.out.println(ans);
    }

    private static long combi_two(long n) {
        return (n * (n-1)) / 2;
    }
    private static long pow_two(long n){
        long res = 1;
        for(int i=1; i<=n; i++) res = (res * 2) % M;
        return res;
    }
}