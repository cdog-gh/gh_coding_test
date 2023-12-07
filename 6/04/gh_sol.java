import java.util.*;

class Main {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int lv = sc.nextInt();
        String verdict = sc.next();
        Map<String, Integer> verdictData = Map.of(
            "miss", 0, 
            "bad", 200, 
            "cool", 400,
            "great", 600, 
            "perfect", 1000
        );
        int ans = verdictData.get(verdict) * lv;
        System.out.println(ans);
    }
}
