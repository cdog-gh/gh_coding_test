import java.io.*;
import java.util.*;
class Point{
    private final int x;
    private final int y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
}
class Gyeongsaro{
    private final int x;
    private final int y;
    private final char dirChar;
    private final int componentA;
    private final int componentB;

    public Gyeongsaro(int x, int y, char dirChar, int componentA, int componentB) {
        this.x = x;
        this.y = y;
        this.dirChar = dirChar;
        this.componentA = componentA;
        this.componentB = componentB;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public char getDirChar() {
        return dirChar;
    }

    public int getComponentA() {
        return componentA;
    }

    public int getComponentB() {
        return componentB;
    }
}
public class Main {
    private static final Map<Character, Integer> stateMap = new HashMap<>();
    private static final Map<Character, Point> dirMap = new HashMap<>();
    private static final boolean [][]visit = new boolean[1001][1001];
    private static final boolean []visitComp = new boolean[1001*1001];

    private static final int []dx = {1, 0, -1, 0};
    private static final int []dy = {0, 1, 0, -1};

    private static int [][]stateMa;
    private static int [][]componentNo;

    private static final List<List<Gyeongsaro>> gConn = new ArrayList<>();
    private static final List<List<Integer>> cConn = new ArrayList<>();

    private static final boolean []isPB = new boolean[1001*1001];
    public static void main(String []args) throws IOException {
        init();
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        String []tokens;
        tokens = bf.readLine().split(" ");
        int R = Integer.parseInt(tokens[0]);
        int C = Integer.parseInt(tokens[1]);
        String []ma = new String[R];
        stateMa = new int[R][C];
        componentNo = new int[R][C];

        for(int i=0; i<1000*1000; i++)
            cConn.add(new ArrayList<>());

        for(int i=0; i<R; i++)
            ma[i] = bf.readLine();
        tokens = bf.readLine().split(" ");
        int x = Integer.parseInt(tokens[0]);
        int y = Integer.parseInt(tokens[1]);

        int no = 1;
        //(1) ma to state conversion!
        for(int i=0; i<R; i++)
            for(int j=0; j<C; j++)
                stateMa[i][j] = stateMap.get(ma[i].charAt(j));
        //System.out.println("YA");
        for(int i=0; i<R; i++) {
            for (int j = 0; j < C; j++) {
                if(visit[i][j])
                    continue;
                bfs(i, j, R, C, no);
                no++;
            }
        }
        //System.out.println("YA");
        for(int i=0; i<R; i++) {
            for (int j = 0; j < C; j++) {
                if(ma[i].charAt(j) == 'P')
                    isPB[componentNo[i][j]] = true;
                if(ma[i].charAt(j) == 'B')
                    isPB[componentNo[i][j]] = true;
            }
        }
        //(3) Gyeongsaro Build
        int gNum = 0;
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++){
                if(ma[i].charAt(j) != '?')
                    continue;
                build(i, j, R, C, gNum,'N');
                build(i, j, R, C, gNum,'W');
                build(i, j, R, C, gNum,'E');
                build(i, j, R, C, gNum,'S');

                while(gConn.get(gNum).size() != 2)
                    gConn.get(gNum).add(new Gyeongsaro(i, j, 'N', -1, -1));
                gNum++;
            }
        }
        for(int t=0; t<(1<<gNum); t++) {
            //(3) graph build!
            for(int i=0; i<gNum; i++){
                int a;
                int b;
                if((t & (1<<i)) == 0){
                    a = gConn.get(i).get(0).getComponentA();
                    b = gConn.get(i).get(0).getComponentB();
                }
                else{
                    a = gConn.get(i).get(1).getComponentA();
                    b = gConn.get(i).get(1).getComponentB();
                }
                if(a != -1 && b != -1){
                    cConn.get(a).add(b);
                    cConn.get(b).add(a);
                }
            }

            //(4) do_work!
            if(doWork(componentNo[x-1][y-1])){
                //print 하고
                for(int i=0; i<gNum; i++){
                    int tx;
                    int ty;
                    char ch;
                    if((t & (1<<i)) == 0){
                        tx = gConn.get(i).get(0).getX();
                        ty = gConn.get(i).get(0).getY();
                        ch = gConn.get(i).get(0).getDirChar();
                    }
                    else{
                        tx = gConn.get(i).get(1).getX();
                        ty = gConn.get(i).get(1).getY();
                        ch = gConn.get(i).get(1).getDirChar();
                    }
                    StringBuilder sb = new StringBuilder(ma[tx]);
                    sb.setCharAt(ty, ch);
                    ma[tx] = sb.toString();
                }
                for(int i=0; i<R; i++)
                    System.out.println(ma[i]);
                return;
            }
            //(5) graph clear!
            for(int i=0; i<gNum; i++){
                int a;
                int b;
                if((t & (1<<i)) == 0){
                    a = gConn.get(i).get(0).getComponentA();
                    b = gConn.get(i).get(0).getComponentB();
                }
                else{
                    a = gConn.get(i).get(1).getComponentA();
                    b = gConn.get(i).get(1).getComponentB();
                }
                if(a != -1 && b != -1){
                    cConn.get(a).clear();
                    cConn.get(b).clear();
                }
            }
        }
        System.out.println("-1");
    }

    private static boolean doWork(int s) {
        //gConn?
        List <Integer> vc = new ArrayList<>();
        Deque<Integer> queue = new ArrayDeque<>();
        visitComp[s] = true; vc.add(s); queue.push(s);
        boolean flag = false;
        while(!queue.isEmpty()){
            int item = queue.poll();
            if(isPB[item])
                flag = true;
            for(int i=0; i<cConn.get(item).size(); i++){
                int next = cConn.get(item).get(i);

                if(visitComp[next])
                    continue;
                visitComp[next] = true;
                vc.add(next);
                queue.add(next);
            }
        }

        //recovery
        for(int i=0; i<vc.size(); i++)
            visitComp[vc.get(i)] = false;

        return flag;
    }

    private static void build(int x, int y, int R, int C, int gNum, char ch) {
        gConn.add(new ArrayList<>());

        Point dirPoint = dirMap.get(ch);

        //Gyeong dir = '1', no Gyeong = '0'
        //stateMa = 2 <- 1
        int tx1 = x + dirPoint.getX();
        int ty1 = y + dirPoint.getY();

        int tx2 = x - dirPoint.getX();
        int ty2 = y - dirPoint.getY();

        if(tx1 < 0 || ty1 < 0 || tx2 < 0 || ty2 < 0)
            return;

        if(tx1 >= R || ty1 >= C || tx2 >= R || ty2 >= C)
            return;

        if(stateMa[tx1][ty1] == 2 && stateMa[tx2][ty2] == 1) {
            Gyeongsaro g = new Gyeongsaro(x, y, ch, componentNo[tx1][ty1], componentNo[tx2][ty2]);
            gConn.get(gNum).add(g);
        }
    }

    private static void bfs(int x, int y, int R, int C, int no) {
        Point cur = new Point(x, y);
        Deque<Point> queue = new ArrayDeque<>();
        visit[x][y] = true;
        queue.push(cur);
        while(!queue.isEmpty()){
            cur = queue.poll();
            componentNo[cur.getX()][cur.getY()] = no;
            for(int i=0; i<4; i++){
                int tx = cur.getX() + dx[i];
                int ty = cur.getY() + dy[i];
                if(tx < 0 || ty < 0 || tx >= R || ty >= C)
                    continue;
                if(stateMa[x][y] != stateMa[tx][ty])
                    continue;
                if(visit[tx][ty])
                    continue;
                Point next = new Point(tx, ty);
                visit[tx][ty] = true;
                queue.push(next);
            }
        }
    }

    private static void init(){
        stateMap.put('.', 1);
        stateMap.put('P', 1);
        stateMap.put('B', 1);

        stateMap.put('1', 2);

        stateMap.put('?', 3);

        stateMap.put('#', 4);

        dirMap.put('N', new Point(-1, 0));
        dirMap.put('W', new Point(0, -1));
        dirMap.put('E', new Point(0, 1));
        dirMap.put('S', new Point(1, 0));
    }
}
