import java.io.BufferedReader;
import java.io.IOException;
import java.io.*;
import java.lang.*;
import java.util.*;

class Data implements Comparable<Data> {
    private final int lo;
    private final long v;

    Data(int lo, long v) {
        this.lo = lo;
        this.v = v;
    }
    
    public int getLo(){ return this.lo; }
    public long getV(){ return this.v; }

    @Override
    public int compareTo(Data o) {
        return Long.compare(this.v, o.getV());
    }

}
public class Main {
    public static void main(String[] args) throws IOException {

        long inf = 0x3f3f3f3f3f3f3f3fL;
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        String []parse = bf.readLine().split(" ");
        long [][]arr = new long[3001][3001];
        long [][]nj = new long[3001][3001];
        long []dq = new long[3001];
        long []dq_lo = new long[3001];
        int dq_front = 0;
        int dq_back = 0;
        int r = Integer.parseInt(parse[0]);
        int c = Integer.parseInt(parse[1]);
        parse = bf.readLine().split(" ");
        int h1 = Integer.parseInt(parse[0]);
        int h2 = Integer.parseInt(parse[1]);
        int w1 = Integer.parseInt(parse[2]);
        int w2 = Integer.parseInt(parse[3]);
        PriorityQueue<Data> pq = new PriorityQueue<>();
        for(int i=1; i<=r; i++){
            parse = bf.readLine().split(" ");
            for(int j=0; j<parse.length; j++)
                arr[i][j+1] = Long.parseLong(parse[j]);
        }
        for(int i=1; i<=r; i++)
            for(int j=1; j<=c; j++)
                nj[i][j] = nj[i-1][j] + nj[i][j-1] - nj[i-1][j-1] + arr[i][j];
        long mini = inf;
        for(int h=h1+1; h<=h2+1; h++){
            if(h > r) break;
            long base = -(arr[1][c-w1] + arr[h][c-w1]);
            int h0 = h-1;
            pq.clear();
            for(int w=c-w1; w>=1; w--){
                base += (arr[1][w] + arr[h][w]);
                long dig = calc_dig(1, w, w1, h0, nj, arr);
                long real = dig - base;
                /*
                while(dq_front < dq_back){
                    if(dq[dq_back-1] < real)
                        break;
                    dq_back--;
                }
                dq[dq_back] = real;
                dq_lo[dq_back++] = w+w1;
                 */
                pq.add(new Data(w+w1, real));
                while(!pq.isEmpty()){
                    Data item = pq.peek();
                    if(item.getLo() <= w + w2) break;
                    pq.poll();
                }
                long a = inf;
                if(!pq.isEmpty())
                    a = pq.peek().getV();
                a += base;
                a += (calc(1, w, h, w, nj) - arr[1][w] - arr[h][w]);
                mini = Math.min(mini, a);
            }
        }

        if(mini == inf)
            System.out.println("No");
        else
            System.out.println(mini);
    }

    private static long calc_dig(int x1, int y1, int ww, int hh, long [][]nj, long [][]arr) {
        long bottom = calc(x1, y1, x1, y1+ww, nj);
        long up = calc(x1+hh, y1, x1+hh, y1+ww, nj);
        long ss = calc(x1, y1+ww, x1+hh, y1+ww, nj);
        return bottom + up + ss - arr[x1][y1+ww] - arr[x1+hh][y1+ww];
    }

    private static long calc(int x1, int y1, int x2, int y2, long [][]nj) {
        return nj[x2][y2] - nj[x2][y1-1] - nj[x1-1][y2] + nj[x1-1][y1-1];
    }
}