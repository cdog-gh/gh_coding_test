import java.io.*;
import java.util.*;


class Segment {
    private final int len;
    private final int s;
    private final int e;

    Segment(int s, int e, int len){
        this.len = len;
        this.s = s;
        this.e = e;
    }
    public int getLen() {
        return len;
    }

    public int getS() {
        return s;
    }

    public int getE() {
        return e;
    }

    public String toString() {
        return "[ " + s + ", " + e + "]";
    }
}
class SegmentCompareWithLenLong implements Comparator<Segment>{

    @Override
    public int compare(Segment o1, Segment o2) {
        int o1Len = o1.getLen();
        int o2Len = o2.getLen();
        int o1S = o1.getS();
        int o2S = o2.getS();
        if(o1Len > o2Len) return -1;
        else if(o1Len < o2Len) return 1;

        if(o1S < o2S) return -1;
        else if(o1S > o2S) return 1;
        return 0;
    }
}
class SegmentCompareWithLenShort implements Comparator<Segment>{

    @Override
    public int compare(Segment o1, Segment o2) {
        int o1Len = o1.getLen();
        int o2Len = o2.getLen();
        int o1S = o1.getS();
        int o2S = o2.getS();
        if(o1Len < o2Len) return -1;
        else if(o1Len > o2Len) return 1;

        if(o1S < o2S) return -1;
        else if(o1S > o2S) return 1;
        return 0;
    }
}
class DataStruct{
    private final TreeSet<Segment> segmentShort;
    private final TreeSet<Segment> segmentLong;
    private final TreeSet<Integer> zeroPoint;
    private final TreeMap <Integer, Integer> SE;
    private final TreeMap <Integer, Integer> ES;
    private final int []map;
    private int tunnelNum;
    DataStruct(String mapInfo){
        segmentShort = new TreeSet<>(new SegmentCompareWithLenShort());
        segmentLong = new TreeSet<>(new SegmentCompareWithLenLong());
        zeroPoint = new TreeSet<>();
        SE = new TreeMap<>();
        ES = new TreeMap<>();
        map = new int[mapInfo.length() + 1];
        for(int i = 0; i<mapInfo.length(); i++) {
            int status = mapInfo.charAt(i) - '0';
            if(status == 0) addZeroPoint(i + 1);
            else if(status == 1) addOnePoint(i + 1);
            map[i + 1] = status;
        }
    }
    public void processOne(int s, int e){
        while(true){
            Integer lower = zeroPoint.ceiling(s);
            if(lower == null || lower >= e) break;
            addOnePoint(lower);
        }
    }
    public String processTwo(){
        String ret = "";
        if(tunnelNum == 0)
            return "-1\n";
        Segment shortest = segmentShort.first();
        Segment longest = segmentLong.first();
        int longE = longest.getE() + 1;
        int shortE = shortest.getE() + 1;
        ret = ret + tunnelNum + " " + longest.getS() + " " + longE + " " + shortest.getS() + " " + shortE;
        ret = ret + "\n";
        return ret;
    }
    private void addZeroPoint(int x){
        zeroPoint.add(x);
    }
    private void addOnePoint(int x){
        if(map[x] != 0) return;

        if(map[x - 1] != 1 && map[x + 1] != 1) {
            Segment sg = new Segment(x, x, 1);
            segmentShort.add(sg); segmentLong.add(sg);
            SE.put(x, x); ES.put(x, x);
            zeroPoint.remove(x);
            tunnelNum++;
        }
        else if(map[x - 1] == 1 && map[x + 1] != 1) {
            int prevS = ES.get(x - 1);
            int prevE = x - 1;
            Segment prevSg = new Segment(prevS, prevE, prevE - prevS + 1);
            SE.remove(prevS); ES.remove(prevE);
            segmentShort.remove(prevSg); segmentLong.remove(prevSg);

            Segment newSg = new Segment(prevS, x, x - prevS + 1);
            segmentShort.add(newSg); segmentLong.add(newSg);
            SE.put(prevS, x); ES.put(x, prevS);
            zeroPoint.remove(x);
        }
        else if(map[x - 1] != 1 && map[x + 1] == 1) {
            int nextS = x + 1;
            int nextE = SE.get(x + 1);
            Segment nextSg = new Segment(nextS, nextE, nextE - nextS + 1);
            SE.remove(nextS); SE.remove(nextE);
            segmentShort.remove(nextSg); segmentLong.remove(nextSg);

            Segment newSg = new Segment(x, nextE, nextE - x + 1);
            segmentShort.add(newSg); segmentLong.add(newSg);
            SE.put(x, nextE); ES.put(nextE, x);
            zeroPoint.remove(x);
        }
        else if(map[x - 1] == 1 && map[x + 1] == 1) {
            int prevS = ES.get(x - 1);
            int prevE = x - 1;
            Segment prevSg = new Segment(prevS, prevE, prevE - prevS + 1);
            SE.remove(prevS); ES.remove(prevE);
            segmentShort.remove(prevSg); segmentLong.remove(prevSg);
            int nextS = x + 1;
            int nextE = SE.get(x + 1);
            Segment nextSg = new Segment(nextS, nextE, nextE - nextS + 1);
            SE.remove(nextS); SE.remove(nextE);
            segmentShort.remove(nextSg); segmentLong.remove(nextSg);

            Segment newSg = new Segment(prevS, nextE, nextE - prevS + 1);
            segmentShort.add(newSg); segmentLong.add(newSg);
            SE.put(prevS, nextE); ES.put(nextE, prevS);
            zeroPoint.remove(x);
            tunnelNum--;
        }
        map[x] = 1;
    }
}
class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        bf.readLine();
        String str = bf.readLine();
        DataStruct ds = new DataStruct(str);
        int Q = Integer.parseInt(bf.readLine());
        StringBuilder sb = new StringBuilder();
        for(int i=1; i<=Q; i++){
            String []token = bf.readLine().split(" ");
            int op = Integer.parseInt(token[0]);
            if(op == 1) ds.processOne(Integer.parseInt(token[1]), Integer.parseInt(token[2]));
            else sb.append(ds.processTwo());
        }
        System.out.println(sb);
    }
}