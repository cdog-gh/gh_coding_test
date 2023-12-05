import java.util.*;
import java.util.stream.IntStream;

public class Main {
    public static void main(String []args){
        Scanner sc = new Scanner(System.in);
        int s = sc.nextInt();
        int k = sc.nextInt();
        int []res = IntStream.range(1, s+1)
                .map(v -> s-v)
                .filter(v -> (v % (2*k) < k))
                .sorted()
                .map(v -> s-v).toArray();
        System.out.println(res.length);
        for(int item: res)
            System.out.println(item);
    }
}
