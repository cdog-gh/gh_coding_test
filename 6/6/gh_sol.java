import java.util.*;
public class Main {
    public static void main(String []args){
        LinkedHashMap<String, String> rev = new LinkedHashMap<>();
        rev.put("LU!", "3");
        rev.put("LD!", "9");
        rev.put("RU!", "1");
        rev.put("RD!", "7");
        rev.put("W!", "2");
        rev.put("A!", "6");
        rev.put("S!", "8");
        rev.put("D!", "4");
        LinkedHashMap<String, String> ori = new LinkedHashMap<>();
        ori.put("LU", "7");
        ori.put("LD", "1");
        ori.put("RU", "9");
        ori.put("RD", "3");
        ori.put("W", "8");
        ori.put("A", "4");
        ori.put("S", "2");
        ori.put("D", "6");
        Scanner sc = new Scanner(System.in);
        String note = sc.nextLine();
        String input = sc.nextLine();
        for(String key: rev.keySet())
            note = note.replaceAll(key, rev.get(key));
        for(String key: ori.keySet())
            note = note.replaceAll(key, ori.get(key));
        for(String key: ori.keySet())
            input = input.replaceAll(key, ori.get(key));
        int pos = 0;
        for(int i=0; i<input.length(); i++)
        {
            if(pos == note.length() || note.charAt(pos) != input.charAt(i)) pos = 0;
            else pos++;
        }
        if(pos == note.length())
            System.out.println("Yes");
        else
            System.out.println("No");
    }
}
