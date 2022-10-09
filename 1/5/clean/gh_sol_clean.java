import java.io.*;
import java.lang.*;
import java.util.*;
class Resource{
    /*
    Key : resource number
    Value : people who occupy resource
    */
    private final Map<Integer, Integer> occupyCardInfo = new HashMap<>();

    public boolean occupy(int resourceNum, int peopleNum){
        if (occupyCardInfo.containsKey(resourceNum))
            return true;
        occupyCardInfo.put(resourceNum, peopleNum);
        return false;
    }
    public boolean release(int resourceNum, int peopleNum){
        if (occupyCardInfo.containsKey(resourceNum)){
            occupyCardInfo.remove(resourceNum);
            return true;
        }
        return false;
    }
}

// Card deck
class CardDeck{
    private final Deque<Card> cardDeck;
    CardDeck(List<Card> cardList){
        cardDeck = new LinkedList<>(cardList);
    }
    public Card selectTopOfCard(){
        return cardDeck.poll();
    }
}
// Card deck end

// Card class
interface Card{
    boolean action(Resource resource, int peopleNum);
    int getCardNumber();
}
class nextCard implements Card{
    private int cardNumber;
    nextCard(int cardNumber){
        this.cardNumber = cardNumber;
    }
    public boolean action(Resource resource, int peopleNum){
        return true;
    }
    public int getCardNumber(){
        return cardNumber;
    }
}
class acquireCard implements Card{
    private int resourceNum;
    private int cardNumber;
    acquireCard(int cardNumber, int resourceNum){
        this.cardNumber = cardNumber;
        this.resourceNum = resourceNum;
    }
    public boolean action(Resource resource, int peopleNum){
        return resource.occupy(resourceNum, peopleNum);
    }
    public int getCardNumber(){
        return cardNumber;
    }
}
class releaseCard implements Card{
    private int resourceNum;
    private int cardNumber;
    releaseCard(int cardNumber, int resourceNum){
        this.cardNumber = cardNumber;
        this.resourceNum = resourceNum;
    }
    public boolean action(Resource resource, int peopleNum) {
        return resource.release(resourceNum, peopleNum);
    }
    public int getCardNumber(){
        return cardNumber;
    }
}
// Card class end

class Game{
    private final Resource resource;
    private final CardDeck cardDeck;
    /*
    Key : card number
    Value : people who occupy card
    */
    private final Map<Integer, Card> cardOccupy = new HashMap<>();
    public Game(Resource resource, CardDeck cardDeck){
        this.resource = resource;
        this.cardDeck = cardDeck;
    }
    public int turn(int peopleNum) {
        cardOccupy.computeIfAbsent(peopleNum, k->cardDeck.selectTopOfCard());
        Card selected = cardOccupy.get(peopleNum);
        if(selected.action(resource, peopleNum))
            cardOccupy.remove(peopleNum);
        return selected.getCardNumber();
    }
}
public class Main {
    public static void main(String []args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        String []line = bf.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int T = Integer.parseInt(line[1]);
        int []turnPeople = new int[T];

        line = bf.readLine().split(" ");
        for(int i=0;i<T;i++)
            turnPeople[i] = Integer.parseInt(line[i]);

        List<Card> cardList = new ArrayList<>();
        for(int i=0;i<T;i++){
            line = bf.readLine().split(" ");
            int id = Integer.parseInt(line[0]);
            if(line[1].compareTo("next") == 0)
                cardList.add(new nextCard(id));
            else if(line[1].compareTo("acquire") == 0)
                cardList.add(new acquireCard(id, Integer.parseInt(line[2])));
            else
                cardList.add(new releaseCard(id, Integer.parseInt(line[2])));
        }
        Game game = new Game(new Resource(), new CardDeck(cardList));
        StringBuilder sb = new StringBuilder();
        for(int i=0;i<T;i++)
            sb.append(game.turn(turnPeople[i]) + "\n");
        System.out.println(sb);
    }
}
