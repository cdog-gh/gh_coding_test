import java.util.*;

class Main {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        long Q = sc.nextLong();
        for(int i=1; i<=Q; i++){
            long a = sc.nextLong();
            long b = sc.nextLong();
            long ans = (1056 * a * b) / (600000);
            System.out.println(ans);
        }
    }
}