import java.util.*;

class Main {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int Q = sc.nextInt();
        for(int i=1; i<=Q; i++){
            int a = sc.nextInt();
            int b = sc.nextInt();
            int inner = 0;
            int outer = 0;
            // 총 86 => 43
            if(a > b){
                // 출발 228, 도착 216
                outer = (a - b);
                inner = 43 - outer;
            }
            else {
                // 출발 216, 도착 228
                inner = (b - a);
                outer = 43 - inner;
            }
            if(inner < outer)
                System.out.println("Inner circle line");
            else
                System.out.println("Outer circle line");
        }
    }
}