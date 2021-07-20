import java.io.*;
import java.util.*;

public class gh_java2 {
    private static class Node {
        String str;
        String extension;

        public Node(String str, String extension) {
            this.str = str;
            this.extension = extension;
        }

        public String getStr() {
            return str;
        }

        public String getExtension() {
            return extension;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());

        // 파일 리스트
        List<Node> list = new ArrayList<>();
        while (n-- > 0) {
            st = new StringTokenizer(br.readLine(), ".");
            list.add(new Node(st.nextToken(), st.nextToken()));
        }

        // OS에서 인식하는 파일확장자 정보
        Set<String> extInfo = new HashSet<>();
        while (m-- > 0) {
            extInfo.add(br.readLine());
        }

        // Comparator 의 thenComparing 이용한 다중 정렬
        // 람다를 쓰기 위해선 마지막 thenComparing 에서 가능하기 때문에
        // OS 가 인식하는 파일 확장자 정렬조건 chk 추가
        Comparator<Node> chk = Comparator.comparingInt(o -> (extInfo.contains(o.extension) == true ? -1 : 1));
        list.sort(Comparator.comparing(Node::getStr).thenComparing(chk).thenComparing(Node::getExtension));


        // 출력
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < list.size(); i++) {
            sb.append(list.get(i).str).append(".").append(list.get(i).extension).append("\n");
        }
        System.out.print(sb.toString());
    }
}