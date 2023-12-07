import java.util.*;
class Main {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int p = sc.nextInt();
        int r = sc.nextInt();
        int v = (100 * p) / r;
        if(v < 20)
            System.out.println("weak");
        else if(v < 40)
            System.out.println("normal");
        else if(v < 60)
            System.out.println("strong");
        else
            System.out.println("very strong");
    }
}
