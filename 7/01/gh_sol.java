import java.util.*;

class Main {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int s = sc.nextInt();
        int f = sc.nextInt();
        if(f < s) System.out.println("flight");
        else System.out.println("high speed rail");
    }
}