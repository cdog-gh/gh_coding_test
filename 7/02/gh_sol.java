import java.util.*;

class Main {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int r = sc.nextInt();
        int f1 = sc.nextInt();
        int f2 = sc.nextInt();
        int f3 = sc.nextInt();
        int f = f1 + f2 + f3;
        if(r <= f || r <= 240) System.out.println("high speed rail");
        else System.out.println("flight");
    }
}