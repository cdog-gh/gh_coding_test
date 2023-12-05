import java.util.*;
import java.util.stream.Stream;

class Main {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int []arr = Stream.of(sc.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int []res = Arrays.stream(arr)
            .filter(k -> k != arr[0])
            .filter(k -> arr[0] - k <= 1000)
            .toArray();
        System.out.println(res.length);
    }
}
