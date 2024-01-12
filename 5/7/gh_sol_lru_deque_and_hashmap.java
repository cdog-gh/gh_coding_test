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
        private final int accessTime;
        reqData(String key, int access_time){
            this.key = key;
            this.accessTime = access_time;
        }
    }
    // save key "k" last access time "t"
    private final Map<String, reqData> cache;

    // save event key "k" accessed time "t"
    // monotone queue (sorted by access time order by asc)
    private final Queue<reqData> queue;
    private final int capacity;
    private int reqTime = 0;
    lruCache(int capacity){
        this.cache = new HashMap<>();
        this.queue = new ArrayDeque<>();
        this.capacity = capacity;
    }
    /*
    hashmap put vs queue add If key already exists.
    */
    public boolean accessCache(String key){
        reqTime++;
        // already exist.
        if(cache.containsKey(key)){
            cache.put(key, new reqData(key, reqTime));
            queue.add(new reqData(key, reqTime));
            return false;
        }
        // not exist.
        cache.put(key, new reqData(key, reqTime));
        queue.add(new reqData(key, reqTime));
        if(cache.size() > capacity)
            remove_oldest();
        return true;
    }

    private void remove_oldest() {
        while(!queue.isEmpty()){
            reqData item = queue.peek();
            String key = item.key;
            int accessTime = item.accessTime;
            int realAccessTime = cache.get(key).accessTime;
            queue.poll();
            if(accessTime == realAccessTime){
                cache.remove(key);
                break;
            }
        }
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