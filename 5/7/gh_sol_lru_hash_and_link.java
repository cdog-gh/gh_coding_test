import java.io.*;
import java.lang.*;
import java.util.*;
class graph{
    private final int [][] dist = new int[300][300];
    private int bucket;
    private final TreeMap<Integer, Integer> cache = new TreeMap<>();
    private final HashMap<Integer, Integer> region = new HashMap<>();
    graph(){
        for(int i=0; i<300; i++)
            for(int j=0; j<300; j++)
                dist[i][j] = 0x3f3f3f3f;
    }
    public void addNode(int nodeNum, char color) {
        if(color == 'B')
            this.bucket = nodeNum;
        if(color == 'C')
            this.cache.put(nodeNum, 0);
        if(color == 'R')
            this.region.put(nodeNum, 0);
    }
    public void addRoad(int node1, int node2, int cost){
        int n1 = getNodeNum(node1);
        int n2 = getNodeNum(node2);
        dist[n1][n2] = dist[n2][n1] = cost;
    }
    public void nodeInit(){
        int lo = 1;
        for(Integer item: cache.keySet()){
            cache.put(item, lo);
            lo = lo + 1;
        }
        for(Integer item: region.keySet()){
            region.put(item, lo);
            lo = lo + 1;
        }
    }
    public void graphInit(){
        for(int k=0; k<300; k++){
            for(int i=0; i<300; i++){
                for(int j=0; j<300; j++){
                    if(dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    public int getNodeNum(int x){
        if(x == this.bucket)
            return 0;
        if(cache.containsKey(x))
            return cache.get(x);
        return region.get(x);
    }

    public int getNearestCacheServer(int region) {
        int cacheServerNum = cache.size();
        int mmn = 0x3f3f3f3f;
        int lo = -1;
        for(int i=1; i<=cacheServerNum; i++){
            if(dist[region][i] < mmn){
                mmn = dist[region][i];
                lo = i;
            }
        }
        return lo;
    }
    public int getDist(int n1, int n2){
        return dist[n1][n2];
    }
}
class lruCache{
    static class reqData{
        private final String key;
        private reqData prev;
        private reqData next;
        reqData(String key){
            this.key = key;
        }
    }
    private final Map<String, reqData> cache;
    private final reqData head;
    private final reqData tail;
    private final int capacity;

    lruCache(int capacity){
        this.cache = new HashMap<>();
        this.capacity = capacity;
        // here is dummy data
        this.head = new reqData("");
        this.tail = new reqData("");
        this.head.next = this.tail;
        this.tail.prev = this.head;
    }

    private void add_last(String key){
        reqData next_item = tail;
        reqData prev_item = tail.prev;
        reqData cur_item = new reqData(key);
        prev_item.next = cur_item;
        cur_item.next = next_item;
        next_item.prev = cur_item;
        cur_item.prev = prev_item;
        cache.put(key, cur_item);
    }

    private void remove_key(String key){
        reqData cur_item = cache.get(key);
        if(cur_item == null) return;
        reqData prev_item = cur_item.prev;
        reqData next_item = cur_item.next;
        prev_item.next = next_item;
        next_item.prev = prev_item;
        cache.remove(key);
    }

    private void remove_oldest(){
        if(cache.size() == 0) return;
        String key = head.next.key;
        remove_key(key);
    }

    public boolean accessCache(String key){
        // already exist.
        if(cache.containsKey(key)){
            remove_key(key);
            add_last(key);
            return false;
        }
        // not exist.
        add_last(key);
        if(cache.size() > capacity)
            remove_oldest();
        return true;
    }
}
public class Main {
    public static void main(String []args) throws IOException {
        //Input..
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        String []parse;
        StringBuilder sb = new StringBuilder();

        graph g = new graph();
        //n, m, c, Q
        parse = bf.readLine().split(" ");
        int n = Integer.parseInt(parse[0]);
        int m = Integer.parseInt(parse[1]);
        int c = Integer.parseInt(parse[2]);
        int Q = Integer.parseInt(parse[3]);
        lruCache []lru = new lruCache[300];

        for(int i=0; i<n; i++)
            bf.readLine();

        for(int i=0; i<m; i++){
            parse = bf.readLine().split(" ");
            int nodeNum = Integer.parseInt(parse[0]);
            char color = parse[1].charAt(0);
            g.addNode(nodeNum, color);
        }
        g.nodeInit();

        parse = bf.readLine().split(" ");
        int r = Integer.parseInt(parse[0]);
        for(int i=0; i<r; i++){
            parse = bf.readLine().split(" ");
            int n1 = Integer.parseInt(parse[0]);
            int n2 = Integer.parseInt(parse[1]);
            int cost = Integer.parseInt(parse[2]);
            g.addRoad(n1, n2, cost);
        }

        for(int i=0; i<300; i++)
            lru[i] = new lruCache(c);
        g.graphInit();

        for(int i=0; i<Q; i++){
            parse = bf.readLine().split(" ");
            int region = g.getNodeNum(Integer.parseInt(parse[0]));
            String station = parse[1];

            //region -> cache_server
            int cache = g.getNearestCacheServer(region);
            int dist1 = g.getDist(region, cache);

            //cache_server -> bucket
            if(lru[cache].accessCache(station)){
                dist1 = dist1 + g.getDist(cache, 0);
            }
            sb.append(2*dist1 + "\n");
        }
        System.out.println(sb);
    }
}