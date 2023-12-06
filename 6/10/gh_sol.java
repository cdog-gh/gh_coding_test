import java.util.*;

public class Main {
    public static void main(String []args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        long x = sc.nextLong();
        long mask = (1L << 31) - 1;
        long []ans = new long[n];
        for(int i=0; i<(n/4)*4; i++)
            ans[i] = (i+4)*(1L << 31);
        ans[0] += (mask - x);
        if(n % 4 == 0)
            ans[n-1] += mask;
        else if(n % 4 == 1)
            ans[n-1] += mask;
        else if(n % 4 == 2)
        {
            ans[n-2] += (1L << 30);
            ans[n-1] += mask - (1L << 30);
        }
        else
        {
            ans[n-3] += (1L << 30);
            ans[n-2] += (1L << 29);
            ans[n-1] += mask - (1L << 30) - (1L << 29);
        }
        String []str = Arrays.stream(ans)
                .map(v -> -v)
                .sorted()
                .map(v -> -v)
                .mapToObj(String::valueOf)
                .toArray(String[]::new);
        System.out.println(str.length);
        System.out.println(String.join("\n", str));
    }
}
