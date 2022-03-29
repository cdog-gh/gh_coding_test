import java.lang.*;
import java.util.*;
public class Main {
    public static void main(String []args){
        Scanner sc = new Scanner(System.in);
        int R = sc.nextInt(); sc.nextInt();
        int ans = 0;
        sc.nextInt(); sc.nextInt();
        int Rp = sc.nextInt();
        int Cp = sc.nextInt();
        sc.nextLine();
        for(int i=0;i<R;i++)
            ans += sc.nextLine().chars().filter(v -> v == 'P').count();
        if(ans != Rp * Cp)
            System.out.println("1");
        else
            System.out.println("0");
    }
}