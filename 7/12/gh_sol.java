import java.util.*;
class Main {
    static long inf = 0x3f3f3f3f3f3f3f3fL;
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        long n = sc.nextLong(); sc.nextLine();
        long []arr = new long[500001];
        long []nj = new long[500001];
        long []S = new long[500001];
        long []DS = new long[500001];
        String s = sc.nextLine();
        s = s.replaceAll(" or ", "#or#");
        String []token = s.split(" ");
        for(int i=0; i<token.length; i++){
            switch (token[i]) {
                case "S": S[i] = 1; break;
                case "DS": DS[i] = 1; break;
                case "S#or#DS": case "DS#or#S": S[i] = DS[i] = 1; break;
                default: arr[i] = Long.parseLong(token[i]); break;
            }
        }
        long nj_v = 0;
        for(int i=0; i<arr.length; i++){
            nj_v += arr[i];
            nj[i] = nj_v;
        }
        long ans = nj[(int)n - 1];
        long t = -inf;
        for(int i=0; i<arr.length; i++){
            if(DS[i] == 0) continue;
            t = Math.max(t, nj[i]);
        }
        ans = Math.max(ans, nj[(int)n - 1] + t);
        // S -- DS
        long rv = -inf;
        long []dp_r = new long[500001];
        for(int i=arr.length-1; i>=0; i--){
            dp_r[i] = rv;
            if(DS[i] == 1) rv = Math.max(rv, nj[i]);
        }
        for(int i=0; i<arr.length; i++){
            if(S[i] == 0) continue;
            // DS?
            if(dp_r[i] == inf) continue;
            long te = dp_r[i] - nj[i];
            t = Math.max(te, t);
        }
        ans = Math.max(ans, nj[(int)n - 1] + t);
        System.out.println(ans);
    }
}