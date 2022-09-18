import java.util.*;
import java.lang.*;
import java.io.*;
class Memo{
    private static Map<String, String> blogKeyword = new HashMap<>();
    Memo(List<String> keywordList){
        for(String k:keywordList)
            blogKeyword.put(k, "");
    }
    Memo(String keywords){
        for(String k:keywords.split(","))
            blogKeyword.put(k, "");
    }
    public void posting(String keywordData){
        for(String k:keywordData.split(","))
            blogKeyword.computeIfPresent(k, (ke, ve)->null);
    }
    public int getKeywordNumInMemo(){
        return blogKeyword.size();
    }
}
class Test {
    public static void test(){
        System.out.println("start test");
        없는_원소_하나_빼기();
        있는_원소_하나_빼기();
        있는_원소_여러개_빼기();
        없는_원소_여러개_빼기();
        있는_원소_없는_원소_여러개_빼기();
    }
    private static void 없는_원소_하나_빼기(){
        Memo memo = new Memo("a,b,c,d,e,f,g");
        memo.posting("h");
        assert memo.getKeywordNumInMemo() == 7;
    }
    private static void 있는_원소_하나_빼기(){
        Memo memo = new Memo("a,b,c,d,e,f,g");
        memo.posting("a");
        assert memo.getKeywordNumInMemo() == 6;
    }
    private static void 있는_원소_여러개_빼기(){
        Memo memo = new Memo("a,b,c,d,e,f,g");
        memo.posting("c,d");
        assert memo.getKeywordNumInMemo() == 5;
    }
    private static void 없는_원소_여러개_빼기(){
        Memo memo = new Memo("a,b,c,d,e,f,g");
        memo.posting("h,i,j");
        assert memo.getKeywordNumInMemo() == 7;
    }
    private static void 있는_원소_없는_원소_여러개_빼기(){
        String exist = "a,f";
        String notExist = "h,i,j";
        String query = exist + "," + notExist;
        Memo memo = new Memo("a,b,c,d,e,f,g");
        memo.posting(query);
        assert memo.getKeywordNumInMemo() == 5;
    }
}
class Main {
    public static void main(String []args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        String []parse = bf.readLine().split(" ");
        int n = Integer.parseInt(parse[0]);
        int m = Integer.parseInt(parse[1]);
        List <String> keywordList = new ArrayList<>();
        for(int i=0;i<n;i++)
            keywordList.add(bf.readLine());
        Memo memo = new Memo(keywordList);
        StringBuilder sb = new StringBuilder();
        for(int i=0;i<m;i++){
            memo.posting(bf.readLine());
            sb.append(memo.getKeywordNumInMemo()+"\n");
        }
        System.out.println(sb.toString());
         
        Test.test();
    }
}