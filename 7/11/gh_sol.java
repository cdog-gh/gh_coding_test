import java.io.*;
import java.lang.*;
import java.util.*;


class Graph {
    private final ArrayList<ArrayList<Integer>> graph = new ArrayList<>();
    Graph(int n){
        for(int i=0; i<=n; i++)
            graph.add(new ArrayList<>());
    }
    public void addEdge(int a, int b){
        graph.get(a).add(b);
        graph.get(b).add(a);
    }
    public ArrayList<Integer> getConInfo(int a){
        return new ArrayList<>(graph.get(a));
    }
}
public class Main {
    public static void main(String []args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(bf.readLine());
        int []temp = Arrays.stream(bf.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int []func = new int[500001];
        int []in = new int[500001];
        Graph g = new Graph(n);
        int []visit = new int[500001];

        System.arraycopy(temp, 0, func, 1, temp.length);

        for(int i=1; i<=n; i++) {
            in[func[i]]++; g.addEdge(i, func[i]); g.addEdge(func[i], i);
        }

        // order.
        ordering(n, in, func);

        // bfs
        int compoNum = 0;
        for(int i=1; i<=n; i++)
        {
            if(visit[i] != 0) continue;
            compoNum++; bfs(i, g, visit, compoNum);
        }

        int []cycle = new int[500001];
        int []oneDist = new int[500001];
        int []tempAns = new int[500001];
        int []ans = new int[2000001];
        for(int i=1; i<=n; i++){
            int curCompoNum = visit[i];
            if(in[i] > 0) cycle[curCompoNum]++;
            else if(in[func[i]] > 0) oneDist[curCompoNum]++;
        }
        ans[0] = n;
        for(int i=1; i<=compoNum; i++){
            int v = cycle[i] + oneDist[i];
            int c = cycle[i];
            tempAns[c] += v;
        }
        for(int i=1; i<=500000; i++){
            if(tempAns[i] == 0)
                continue;
            for(int j=i; j<=2000000; j=j+i)
                ans[j] += tempAns[i];
        }

        int Q = Integer.parseInt(bf.readLine());
        StringBuilder sb = new StringBuilder();
        for(int i=1; i<=Q; i++){
            int a = Integer.parseInt(bf.readLine()); a--;
            sb.append(ans[a]).append("\n");
        }
        System.out.println(sb);
    }

    private static void bfs(int s, Graph g, int []visit, int num) {
        Queue <Integer> Q = new ArrayDeque<>();
        visit[s] = num; Q.add(s);
        while(!Q.isEmpty()){
            int cur = Q.poll();
            ArrayList <Integer> neighborList = g.getConInfo(cur);
            for(Integer next: neighborList){
                if(visit[next] != 0) continue;
                visit[next] = num; Q.add(next);
            }
        }
    }

    private static void ordering(int n, int []in, int []f) {
        Queue <Integer> Q = new ArrayDeque<>();
        for(int i=1; i<=n; i++){
            if(in[i] > 0) continue;
            Q.add(i); in[i]--;
        }
        while(!Q.isEmpty()){
            int cur = Q.poll();

            int next = f[cur]; in[next]--;
            if(in[next] == 0)
            {
                in[next] = -1;  Q.add(next);
            }
        }
    }
}