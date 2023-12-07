import java.io.*;
import java.lang.*;
import java.util.*;
class Union
{
    private final int []p;
    Union(int sz){
        this.p = new int[sz + 1];
        Arrays.fill(p, -1);
    }
    public int find(int x){
        if(p[x] == -1)
            return x;
        p[x] = find(p[x]);
        return p[x];
    }
    public void merge(int a, int b){
        int ta = find(a);
        int tb = find(b);
        if(ta == tb)
            return;
        p[tb] = ta;
    }
}
class Edge implements Comparable<Edge>
{
    private final int from;
    private final int to;
    private final int cost;
    private final int time;

    Edge(int from, int to, int cost, int time) {
        this.from = from;
        this.to = to;
        this.cost = cost;
        this.time = time;
    }

    public int getFrom(){
        return this.from;
    }
    public int getTo(){
        return this.to;
    }
    public int getCost(){
        return this.cost;
    }
    public int getTime(){
        return this.time;
    }

    @Override
    public int compareTo(Edge o) {
        if(this.cost != o.getCost())
            return this.cost - o.getCost();
        return this.time - o.getTime();
    }

    public String toString(){
        return "from: " + from + ", to: " + to + ", time: " + time + ", cost: " + cost;
    }
}
public class Main {
    public static void main(String []args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        String []parse = bf.readLine().split(" ");
        int n = Integer.parseInt(parse[0]);
        int q = Integer.parseInt(parse[1]);
        int ye = 1;
        ArrayList <Edge> edgeList = new ArrayList<>();
        for(int i=0; i<q; i++){
            parse = bf.readLine().split(" ");
            // a, b, cost, time
            int from = Integer.parseInt(parse[0]);
            int to = Integer.parseInt(parse[1]);
            int cost = Integer.parseInt(parse[2]);
            int time = Integer.parseInt(parse[3]);
            Edge e = new Edge(from, to, cost, time);
            // System.out.println("!");
            edgeList.add(e);
        }
        Collections.sort(edgeList);
        Union u = new Union(n);
        long time = 0;
        long cost = 0;
        /*
        cost가 같을 때 time이 더 큰 것을 뽑아도 이득이 되지 않음.
        이는 몇 가지 case로 증명할 수 있음.
        */
        for(Edge item: edgeList){
            int a = item.getFrom();
            int b = item.getTo();
            if(u.find(a) == u.find(b))
                continue;
            ye += 1;
            u.merge(a, b);
            cost += item.getCost();
            time = Math.max(time, item.getTime());
        }
        if(ye != n)
            System.out.println(-1);
        else
            System.out.println(time + " " + cost);
    }
}
