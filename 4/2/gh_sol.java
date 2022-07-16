import java.io.*;
import java.lang.*;
import java.util.*;
import java.util.stream.Stream;

public class Main {
    public static void main(String []args) throws IOException {
        Map <String, Integer> time = Map.of(
            "10MIN", 10,
            "30MIN", 30,
            "50MIN", 50,
            "2HOUR", 120,
            "4HOUR", 240,
            "9HOUR", 540
        );
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        String []parse = bf.readLine().split(":");
        int hh = Integer.parseInt(parse[0]);
        int mm = Integer.parseInt(parse[1]);
        int curMin = 60*hh + mm;
        int []hp = Stream
                .of(bf.readLine().split(" "))
                .mapToInt(Integer::parseInt)
                .toArray();
        int Q = Integer.parseInt(bf.readLine());
        for(int i=0; i<Q; i++) {
            parse = bf.readLine().split(" ");
            if (parse[1].compareTo("^") == 0)
                hp[curMin / 120] = -100;
            else
                curMin = (curMin + time.get(parse[1])) % 720;
        }
        int ans = Arrays.stream(hp).filter(h -> h > 0).sum();
        if(ans > 100)
            ans = 100;
        System.out.println(ans);
    }
}