import java.util.*;

class Main {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String s = sc.nextLine();
        ArrayList<String> res = new ArrayList<>(
            Arrays.asList(s.replaceAll("[()]", "#").split("#"))
        );
        if(res.size() < 2) {
            res.add("-");
            res.add("-");
        }
        System.out.println(res.get(0));
        System.out.println(res.get(1));
    }
}