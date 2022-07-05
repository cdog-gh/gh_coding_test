import java.io.*;
import java.util.*;
class Balloon{
    private final int sTime;
    private final int eTime;
    private final int balloonId;
    private final int balloonLv;
    private final boolean isCamo;
    private final boolean isLead;

    public Balloon(int sTime, int eTime, int balloonId, int balloonLv, boolean isCamo, boolean isLead) {
        this.sTime = sTime;
        this.eTime = eTime;
        this.balloonId = balloonId;
        this.balloonLv = balloonLv;
        this.isCamo = isCamo;
        this.isLead = isLead;
    }

    public int getsTime() {
        return sTime;
    }

    public int geteTime() {
        return eTime;
    }

    public int getBalloonId() {
        return balloonId;
    }

    public int getBalloonLv() {
        return balloonLv;
    }

    public boolean isCamo() {
        return isCamo;
    }

    public boolean isLead() {
        return isLead;
    }
}
class Monkey{
    private String skill;
    private String targetPriority;

    public Monkey(String skill, String targetPriority) {
        this.skill = skill;
        this.targetPriority = targetPriority;
    }

    public String getSkill() {
        return skill;
    }

    public void learnSkill(String skill) {
        this.skill += skill;
    }

    public String getTargetPriority() {
        return targetPriority;
    }

    public void setTargetPriority(String targetPriority) {
        this.targetPriority = targetPriority;
    }
}
public class Main {
    private final static List <String> []balloonEventList = new ArrayList[300003];
    private final static List <String> []monkeyEventList = new ArrayList[300003];
    private final static Monkey []monkey = new Monkey[1001];
    private final static int []route = new int[11];
    private final static TreeMap <Long, Balloon> []first = new TreeMap[2];
    private final static TreeMap <Long, Balloon> []last = new TreeMap[2];
    private final static TreeMap <Long, Balloon> []strong = new TreeMap[2];
    private final static StringBuilder sb = new StringBuilder();
    public static void main(String []args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        for(int i=0; i<300003; i++)
            balloonEventList[i] = new ArrayList<>();
        for(int i=0; i<300003; i++)
            monkeyEventList[i] = new ArrayList<>();
        String []tokens;

        tokens = bf.readLine().replaceAll("\n", "").split(" ");
        int R = Integer.parseInt(tokens[0]);
        int U = Integer.parseInt(tokens[1]);

        tokens = bf.readLine().split(" ");

        for(int i=0; i<2; i++){
            first[i] = new TreeMap<>();
            last[i] = new TreeMap<>();
            strong[i] = new TreeMap<>();
        }
        for(int i=1; i<=R; i++)
            route[i] = Integer.parseInt(tokens[i-1]);

        for(int i=1; i<=R; i++)
            bf.readLine();

        for(int i=0; i<U; i++){
            //400 - FIRST
            tokens = bf.readLine().replaceAll("\n", "").split(" ");
            int idx = Integer.parseInt(tokens[0]);
            monkey[idx % 1000] = new Monkey(tokens[1], tokens[2]);
        }

        int E = Integer.parseInt(bf.readLine());
        for(int i=0; i<E; i++){
            String temp = bf.readLine().replaceAll("\n","");
            tokens = temp.split(" ");
            int t = parseTime(tokens[0]);
            if("BALLOON".compareTo(tokens[1]) == 0)
                balloonEventList[t].add(temp);
            else
                monkeyEventList[t].add(temp);
        }

        for(int t=0; t<=300001; t++){
            //balloon delete
            balloonRm(t);
            for(int i=0; i<balloonEventList[t].size(); i++)
                balloonAdd(t, balloonEventList[t].get(i));
            for(int i=0; i<monkeyEventList[t].size(); i++)
                monkeyEvent(monkeyEventList[t].get(i));
            //monkey target
            Balloon target = monkeyTarget(t);
            //monkey attack
            monkeyAttack(t, target);
        }

        System.out.println(sb.toString());
    }

    private static void monkeyAttack(int t, Balloon target) {
        if(target == null)
            return;
        if(monkey[t % 1000] == null)
            return;
        boolean ableLeadAtt = (monkey[t % 1000].getSkill().indexOf('R') != -1);
        if((!ableLeadAtt) && target.isLead())
            return;
        //Attack the balloon
        int monkeyId = ((t % 1000 == 0)?1000:t%1000);
        int bId = target.getBalloonId();

        //bId monkeyId\n
        String temp = bId + " " + monkeyId + "\n";
        sb.append(temp);
        int isCamo = (target.isCamo()?1:0);
        balloonRm(isCamo, target);

        //Lead 이상일 때, 풍선 다시 넣기.
        if(target.getBalloonLv() >= 3){
            Balloon te = new Balloon(target.getsTime(), target.geteTime(), target.getBalloonId(), target.getBalloonLv()-2, target.isCamo(), false);
            balloonAdd(te);
        }
    }

    private static Balloon monkeyTarget(int t) {
        if(t == 0)
            return null;
        if(monkey[t % 1000] == null)
            return null;
        Balloon ret = null;
        long mn = 0x3f3f3f3f3f3f3f3fL;
        int lim = ((monkey[t % 1000].getSkill().indexOf('L') != -1)?1:0);

        for(int i=0; i<=lim; i++){
            String tp = monkey[t % 1000].getTargetPriority();
            switch(tp){
                case "FIRST":
                    if(!first[i].isEmpty()){
                        long kei = first[i].firstKey();
                        if(kei < mn){
                            mn = kei;
                            ret = first[i].get(kei);
                        }
                    }
                    break;
                case "LAST":
                    if(!last[i].isEmpty()){
                        long kei = last[i].firstKey();
                        if(kei < mn){
                            mn = kei;
                            ret = last[i].get(kei);
                        }
                    }
                    break;
                case "STRONG":
                    if(!strong[i].isEmpty()){
                        long kei = strong[i].firstKey();
                        if(kei < mn){
                            mn = kei;
                            ret = strong[i].get(kei);
                        }
                    }
                    break;
            }
        }
        return ret;
    }

    private static void monkeyEvent(String s) {
        String []tokens = s.split(" ");
        int monkeyId = Integer.parseInt(tokens[2]);
        switch(tokens[1]){
            case "ADD":
                monkey[monkeyId % 1000] = new Monkey("-", "FIRST");
                break;
            case "UPGRADE":
                monkey[monkeyId % 1000].learnSkill(tokens[3]);
                break;
            case "REMOVE":
                monkey[monkeyId % 1000] = null;
                break;
            case "CHANGEPRIORITY":
                monkey[monkeyId % 1000].setTargetPriority(tokens[3]);
                break;
        }
    }

    //s.T BALLOON (balloon_name) balloon_id route_id
    private static void balloonAdd(int t, String s) {
        String []tokens = s.split(" ");
        int len = tokens.length;
        int bId = Integer.parseInt(tokens[len - 2]);
        int rId = Integer.parseInt(tokens[len - 1]);

        StringBuilder sb = new StringBuilder();
        for(int i=2; i<len-2; i++)
            sb.append(tokens[i]);
        String bName = sb.toString();

        switch(bName){
            case "RedBalloon":
                balloonAdd(new Balloon(t, t + 100*route[rId], bId, 1, false, false));
                break;
            case "CamoRedBalloon":
                balloonAdd(new Balloon(t, t + 100*route[rId], bId, 2, true, false));
                break;
            case "LeadBalloon":
                balloonAdd(new Balloon(t, t + 100*route[rId], bId, 3, false, true));
                break;
            case "CamoLeadBalloon":
                balloonAdd(new Balloon(t, t + 100*route[rId], bId, 4, true, true));
                break;
        }
    }

    private static void balloonAdd(Balloon balloon) {
        int camo = (balloon.isCamo()?1:0);
        long kei1 = getFirstKey(balloon);
        long kei2 = getLastKey(balloon);
        long kei3 = getStrongKey(balloon);
        first[camo].put(kei1, balloon);
        last[camo].put(kei2, balloon);
        strong[camo].put(kei3, balloon);
    }

    private static void balloonRm(int t) {
        for(int i=0; i<2; i++){
            //first
            while(!first[i].isEmpty()){
                Balloon b = first[i].get(first[i].firstKey());
                if(b.geteTime() > t)
                    break;
                balloonRm(i, b);
            }
        }
    }

    private static void balloonRm(int isCamo, Balloon b) {
        long kei1 = getFirstKey(b);
        long kei2 = getLastKey(b);
        long kei3 = getStrongKey(b);
        first[isCamo].remove(kei1);
        last[isCamo].remove(kei2);
        strong[isCamo].remove(kei3);
    }

    private static int parseTime(String token) {
        String []tokens = token.split("\\.");
        return 1000 * Integer.parseInt(tokens[0]) + Integer.parseInt(tokens[1]);
    }
    private static long getStrongKey(Balloon balloon) {
        return 1010101L * (1010100L - balloon.getBalloonLv()) + balloon.getBalloonId();
    }

    private static long getLastKey(Balloon balloon) {
        return 1010101L * (1010100L - balloon.getsTime()) + balloon.getBalloonId();
    }

    private static long getFirstKey(Balloon balloon) {
        return 1010101L * balloon.geteTime() + balloon.getBalloonId();
    }
}
