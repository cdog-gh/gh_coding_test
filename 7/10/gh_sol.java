import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;
import java.util.stream.Collectors;

enum Stop{
    MUST(),
    SELECT(),
    PASS()
}
enum StationType{
    START(),
    BOTH(),
    NOTHING()
}

// Data Object
class Station{
    private final int stationNum;
    private final double dist;
    private final StationType stationType;
    private final Map<String, Stop> stopInfo;

    private Station(int stationNum, double dist, StationType stationType, Map<String, Stop> stopInfo){
        this.stationNum = stationNum;
        this.dist = dist;
        this.stationType = stationType;
        this.stopInfo = stopInfo;
    }

    public double getDist(){
        return dist;
    }

    public int getStationNum(){
        return stationNum;
    }

    public StationType getStationType(){
        return stationType;
    }

    public Stop getStopInfo(String grade){
        return stopInfo.getOrDefault(grade, Stop.PASS);
    }

    public static class StationBuilder{
        private final int stationNum;
        private final double dist;
        private StationType stationType = StationType.NOTHING;
        private final Map<String, Stop> stopInfo = new HashMap<>();

        public StationBuilder(int stationNum, double dist) {
            this.stationNum = stationNum;
            this.dist = dist;
        }

        public StationBuilder setStationType(StationType stationType){
            this.stationType = stationType;
            return this;
        }

        public StationBuilder setStopInfo(String grade, Stop stopInfo){
            this.stopInfo.put(grade, stopInfo);
            return this;
        }

        public Station build(){
            return new Station(this.stationNum, this.dist, this.stationType, this.stopInfo);
        }
    }
}
class StationData{
    private final Map <String, Station> stations = new HashMap<>();
    private final String[] stationNum = new String[20];
    StationData(){
        String[] stationData = new String[]{
            "Tokyo O O 도쿄도 치요다구 0 0",
            "Shinagawa O O 도쿄도 미나토구 6.8 6.8",
            "Shin-Yokohama O O 가나가와현 요코하마시 코호쿠구 28.8 25.5",
            "Odawara △  가나가와현 오다와라시 83.9 76.7",
            "Atami △  시즈오카현 아타미시 104.6 95.4",
            "Mishima △  시즈오카현 미시마시 120.7 111.3",
            "Shin-Fuji   시즈오카현 후지시 146.2 135.0",
            "Shizuoka △  시즈오카현 시즈오카시 아오이구 180.2 167.4",
            "Kakegawa   시즈오카현 카케가와시 229.3 211.3",
            "Hamamatsu △  시즈오카현 하마마츠시 주오구 257.1 238.9",
            "Toyohashi △  아이치현 토요하시시 293.6 274.2",
            "Mikawa-Anjo   아이치현 안조시 336.3 312.8",
            "Nagoya O O 아이치현 나고야시 나카무라구 366.0 342.0",
            "Gifu-Hashima △  기후현 하시마시 396.3 367.1",
            "Maibara △  시가현 마이바라시 445.9 408.2",
            "Kyoto O O 교토부 교토시 시모교구 513.6 476.3",
            "Shin-Osaka O O 오사카부 오사카시 요도가와구 552.6 515.4",
        };
        Map<String, StationType> stationType = Map.of(
            "Tokyo", StationType.BOTH,
            "Shinagawa", StationType.START,
            "Shin-Yokohama", StationType.START,
            "Mishima", StationType.START,
            "Shizuoka", StationType.BOTH,
            "Hamamatsu", StationType.BOTH,
            "Nagoya", StationType.BOTH,
            "Shin-Osaka", StationType.BOTH
        );
        Map<String, Stop> stop = Map.of(
            "O", Stop.MUST,
            "△", Stop.SELECT,
            "", Stop.PASS
        );
        for(int i=0; i < stationData.length; i++){
            String []tokens = stationData[i].split(" ");
            int tokenNum = tokens.length;
            // stationName : token[0]
            // hikari : token[1]
            // nozomi : token[2]
            // costDist : token[tokenNum-2]
            // realDist : token[tokenNum-1]
            Station station = new Station.StationBuilder(i, Double.parseDouble(tokens[tokenNum-2]))
                .setStationType(stationType.getOrDefault(tokens[0], StationType.NOTHING))
                .setStopInfo("kodama", Stop.MUST)
                .setStopInfo("hikari", stop.get(tokens[1]))
                .setStopInfo("nozomi", stop.get(tokens[2]))
                .build();
            stationNum[i] = tokens[0];
            stations.put(tokens[0], station);
        }
    }
    public Station getStationData(String station){
        return stations.get(station);
    }
    public String getStationName(int num){
        return stationNum[num];
    }
}
class Processor{
    // kodama cost calc.
    private static boolean possibleKodama(int s, int e, StationData stationData){
        int ts = (Math.min(s, e));
        int te = (Math.max(s, e));
        Station sData = stationData.getStationData(stationData.getStationName(ts));
        Station eData = stationData.getStationData(stationData.getStationName(te));
        if(ts == 0)
            return 200.0 * 6.8 + 300.0 * (eData.getDist() - 6.8) >= 5000.0;
        else
            // Only rapid.
            return 300.0 * (eData.getDist() - sData.getDist()) >= 33000.0;
    }
    private static boolean isKodama(List<String> stations, StationData stationData){
        Station sData = stationData.getStationData(stations.get(0));
        Station eData = stationData.getStationData(stations.get(stations.size() - 1));
        int s = sData.getStationNum();
        int e = eData.getStationNum();
        int stopNum = Math.abs(e - s) + 1;
        if(stopNum != stations.size()) return false;
        if(sData.getStationType() != StationType.START && sData.getStationType() != StationType.BOTH) return false;
        if(eData.getStationType() != StationType.BOTH) return false;

        // specific.
        if(s == 5 && s < e) return false;
        if(s == 12 && e == 16) return false;
        if(s == 16 && e == 12) return false;
        return possibleKodama(s, e, stationData);
    }
    private static boolean rapidGradeCheck(List<String> stations, StationData stationData, String grade){
        Station sData = stationData.getStationData(stations.get(0));
        Station eData = stationData.getStationData(stations.get(stations.size() - 1));
        int s = sData.getStationNum();
        int e = eData.getStationNum();
        int stopNum = Math.abs(e - s) + 1;
        if(stopNum == stations.size()) return false;
        if(sData.getStationType() != StationType.START && sData.getStationType() != StationType.BOTH) return false;
        if(eData.getStationType() != StationType.BOTH) return false;
        if(sData.getStopInfo(grade) != Stop.MUST) return false;
        if(eData.getStopInfo(grade) != Stop.MUST) return false;
        for(String station: stations){
            Station chkData = stationData.getStationData(station);
            if(chkData.getStopInfo(grade) != Stop.MUST && chkData.getStopInfo(grade) != Stop.SELECT) return false;
        }
        for(int i=1; i<stations.size(); i++){
            int prevStationNum = stationData.getStationData(stations.get(i-1)).getStationNum();
            int curStationNum = stationData.getStationData(stations.get(i)).getStationNum();
            for(int j=prevStationNum+1; j<curStationNum; j++){
                Station chkData = stationData.getStationData(stationData.getStationName(j));
                if(chkData.getStopInfo(grade) == Stop.MUST) return false;
            }
        }
        if(s == 12 && e == 16) return false;
        if(s == 16 && e == 12) return false;
        return true;
    }
    public static int checker(List<String> stations, StationData stationData){
        Map <String, Integer> visitCount = new HashMap<>();
        // return 200
        for(String station: stations){
            if(stationData.getStationData(station) == null){
                return 200;
            }
        }
        // return 300
        for(String station: stations){
            visitCount.put(
                station,
                visitCount.getOrDefault(station, 0) + 1
            );
            if(visitCount.get(station) > 1)
                return 300;
        }
        // return 400
        double dir = stationData.getStationData(stations.get(1)).getDist() -
            stationData.getStationData(stations.get(0)).getDist();
        for(int i=1; i<stations.size(); i++){
            double prevDist = stationData.getStationData(stations.get(i-1)).getDist();
            double curDist = stationData.getStationData(stations.get(i)).getDist();
            if((curDist - prevDist) * dir < 0) return 400;
        }
        if(isKodama(stations, stationData)) return -1;
        if(rapidGradeCheck(stations, stationData, "nozomi")) return -3;
        if(!rapidGradeCheck(stations, stationData, "hikari")) return 500;

        // 추가 체크
        List <String> t1 = stations.stream().filter(
            station -> (
                stationData.getStationData("Shin-Yokohama").getStationNum() < stationData.getStationData(station).getStationNum()
                && stationData.getStationData(station).getStationNum() < stationData.getStationData("Nagoya").getStationNum()
            )
        ).collect(Collectors.toList());

        List <String> t2 = stations.stream().filter(
            station -> (
                stationData.getStationData("Nagoya").getStationNum() < stationData.getStationData(station).getStationNum()
                    && stationData.getStationData(station).getStationNum() < stationData.getStationData("Kyoto").getStationNum()
            )
        ).collect(Collectors.toList());
        boolean rapid1 = (t1.size() <= 2 || !t1.contains("Shizuoka"));
        if(!stations.contains("Shin-Osaka")){
            if(rapid1) return 500;
        }
        else{
            boolean rapid2 = (t2.size() == 0);
            if(t2.contains("Gifu-Hashima") && t2.size() == 1) return 500;
            if(rapid1 && rapid2) return 500;
        }
        return -2;
    }
}

public class Main{
    public static void main(String[] args) throws IOException{
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int Q = Integer.parseInt(bf.readLine());
        StationData stationData = new StationData();
        for(int q=1; q<=Q; q++){
            int n = Integer.parseInt(bf.readLine());
            ArrayList<String> stations = new ArrayList<>();
            for(int i=1; i<=n; i++){
                String s = bf.readLine();
                if(s.endsWith(" station"))
                    s = s.substring(0, s.length() - " station".length());
                stations.add(s);
            }
            int code = Processor.checker(stations, stationData);
            if(code > 0)
                System.out.println("ERROR " + code);
            else if(code == -3)
                System.out.println("nozomi");
            else if(code == -2)
                System.out.println("hikari");
            else
                System.out.println("kodama");
        }
    }
}