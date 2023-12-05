import java.util.*;

class Main {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int a = sc.nextInt();
        int tot = 1;
        for(int i=1; i<n; i++){
            int b = sc.nextInt();
            if(b > a) tot++;
        }
        System.out.println(tot);
    }
}
