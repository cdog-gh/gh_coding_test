import java.io.*;
import java.lang.*;
import java.util.*;
class Card{
    private final int op;
    private final int id;
    private final int resource;
    Card(int op, int id, int resource){
        this.op = op;
        this.id = id;
        this.resource = resource;
    }

    public int getOp() {
        return op;
    }

    public int getId() {
        return id;
    }

    public int getResource() {
        return resource;
    }
}
/*
manager 안에 gamestate를 넣음. 
manager가 gamestate를 가지고 판단하기 때문.
*/
class manager{
	/*
	manager 바깥에서 gameState의 상태를 변경하지 못하도록 처리함.
	cardDeck은 바깥에서 한 번 초기화 하면 여기에서만 변경될 수 있도록 처리.
	*/
    private final gameState gs;
    manager(Deque<Card> deck){
        gs = new gameState(deck);
    }

    public int doTurn(int peopleNum) {
        Card curCard = gs.getCurCard(peopleNum);
        if(curCard.getOp() == 1)
            gs.discardCard(peopleNum);
        else if(curCard.getOp() == 2)
        {
            if(!gs.checkOccupyResource(curCard.getResource())){
                gs.getResource(curCard.getResource());
                gs.discardCard(peopleNum);
            }
        }
        else
        {
            gs.releaseResource(curCard.getResource());
            gs.discardCard(peopleNum);
        }
        return curCard.getId();
    }
	/*
	gameState는 resource의 occupy 상태, 누가 어떤 카드를 들고 있는지, deck이 들어가 있음.
	*/
    static class gameState{
        private final HashSet<Integer> resource = new HashSet<>();
        private final Card []card = new Card[500001];
        private final Deque<Card> deck;
        gameState(Deque<Card> deck){
            this.deck = deck;
        }
        public Card getCurCard(int peopleNum){
            if(card[peopleNum] == null)
                card[peopleNum] = deck.pollFirst();
            return card[peopleNum];
        }

        public void discardCard(int peopleNum) {
            card[peopleNum] = null;
        }

        public void getResource(int resourceNum){
            resource.add(resourceNum);
        }

        public void releaseResource(int resourceNum) {
            resource.remove(resourceNum);
        }

        public boolean checkOccupyResource(int resourceNum) {
            return resource.contains(resourceNum);
        }
    }
}
public class Main {
    public static void main(String []args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        String []line = bf.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int T = Integer.parseInt(line[1]);
        int []game = new int[T];
        Deque<Card> cList = new ArrayDeque<>();

        line = bf.readLine().split(" ");
        for(int i=0;i<T;i++)
            game[i] = Integer.parseInt(line[i]);
        for(int i=0;i<T;i++){
            line = bf.readLine().split(" ");
            int id = Integer.parseInt(line[0]);
            int op = 0;
            if(line[1].compareTo("next") == 0)
                op = 1;
            else if(line[1].compareTo("acquire") == 0)
                op = 2;
            else
                op = 3;
            if(op == 1)
                cList.add(new Card(1, id,-1));
            else
                cList.add(new Card(op, id, Integer.parseInt(line[2])));
        }
        manager mg = new manager(new ArrayDeque<>(cList));
        StringBuilder sb = new StringBuilder();
        for(int i=0;i<T;i++){
            int peopleNum = game[i];
            int ret = mg.doTurn(peopleNum);
            sb.append(ret+"\n");
        }
        System.out.println(sb.toString());
    }
}
