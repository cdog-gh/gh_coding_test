import java.io.*;
import java.util.*;
class Ref{
    private int from;
    private int to;
    private boolean isRemoved;
    public Ref(int from, int to) {
        this.from = from;
        this.to = to;
        this.isRemoved = false;
    }
    public int getFrom() {
        return from;
    }
    public int getTo() {
        return to;
    }
    public void setRemoved(boolean isRemoved){
        this.isRemoved = isRemoved;
    }

    public boolean getRemoved(){
        return this.isRemoved;
    }
}
public class Main {
    private static Map <Integer, Integer> objMap  = new HashMap<>();
    private static Set <Integer> rootObj = new HashSet<>();
    private static Map <Integer, Integer> refMap = new HashMap<>();
    private static List <Integer> [][]con = new ArrayList[400004][2];
    private static Ref []ref = new Ref[400004];
    private static int []weakness = new int[400004];
    public static void main(String []args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        String []tokens;

        tokens = bf.readLine().split(" ");
        int O = Integer.parseInt(tokens[0]);
        int E = Integer.parseInt(tokens[1]);


        for(int i=0; i<400004; i++)
            for(int j=0; j<2; j++)
                con[i][j] = new ArrayList<>();



        for(int i=0; i<O; i++){
            tokens = bf.readLine().split(" ");
            int objId = Integer.parseInt(tokens[0]);
            objMap.putIfAbsent(objId, objMap.size());
            if("ROOT".compareTo(tokens[1]) == 0)
                rootObj.add(objMap.get(objId));
        }

        for(int i=0; i<E; i++){
            tokens = bf.readLine().split(" ");
            switch(tokens[0]){
                case "M":
                    System.out.println(bfs(0));
                    break;
                case "m":
                    System.out.println(bfs(1));
                    break;
                case "MADE":
                    //MADE object_id is_root
                    int objId = Integer.parseInt(tokens[1]);
                    objMap.putIfAbsent(objId, objMap.size());
                    if("ROOT".compareTo(tokens[2]) == 0)
                        rootObj.add(objMap.get(objId));
                    break;
                case "ADD":
                    //ADD ref_id object_id_1 -> object_id_2
                    //ADD ref_id object_id_2 => object_id_2
                    int objectId1 = Integer.parseInt(tokens[2]);
                    int objectId2 = Integer.parseInt(tokens[4]);
                    int from = objMap.get(objectId1);
                    int to = objMap.get(objectId2);

                    int refId = Integer.parseInt(tokens[1]);
                    refMap.putIfAbsent(refId, refMap.size());

                    int realRefId = refMap.get(refId);
                    int flag = 0;
                    if("->".compareTo(tokens[3]) == 0) flag = 1;
                    ref[realRefId] = new Ref(from, to);
                    con[from][flag].add(realRefId);
                    weakness[realRefId] = flag;
                    break;
                case "REMOVE":
                    //REMOVE ref_id
                    int rrefId = Integer.parseInt(tokens[1]);
                    int realRid = refMap.get(rrefId);
                    ref[realRid].setRemoved(true);
                    break;
            }
        }
    }

    private static int bfs(int limit) {
        //con[][0] ~ con[][limit] search
        boolean []visit = new boolean[400004];
        //boolean []refMarked = new boolean[400004];
        Deque<Integer> queue = new ArrayDeque<>();

        //RootObj 돌리기
        for(Integer cur : rootObj){
            visit[cur] = true;
            queue.add(cur);
        }
        int ans = 0;

        //탐색하기
        while(!queue.isEmpty()){
            int cur = queue.poll();
            ans++;
            for(int t=0; t<=limit; t++){
                for(Integer refId : con[cur][t]){
                    if(ref[refId].getRemoved())
                        continue;
                    if(weakness[refId] != t)
                        continue;
                    int next = ref[refId].getTo();
                    if(visit[next])
                        continue;
                    visit[next] = true;
                    queue.add(next);
                }
            }
        }

        //옵젝이 제거되던 제거 안 되던 상관 없기는 한데 어찌 되었던
        for(int i=0; i<400004; i++){
            //볼 필요 전혀 없음.
            if(ref[i] == null)
                continue;
            if(!visit[ref[i].getFrom()])
                ref[i].setRemoved(true);
            if(!visit[ref[i].getTo()])
                ref[i].setRemoved(true);
        }
        return ans;
    }
}
