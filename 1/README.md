# 1회 (패스트캠퍼스 초격차 모의고사 4회) [바로 가기](https://www.acmicpc.net/contest/view/644) 
5월 23일 13시부터 18시까지 1회 코딩테스트가 열렸습니다.   

* 가희야 거기서 자는 거 아니야  [바로가기](https://www.acmicpc.net/problem/21771)
* 가희의 고구마 먹방  [바로가기](https://www.acmicpc.net/problem/21772) [분석](https://codingdog.tistory.com/529) 
* 가희와 프로세스 1  [바로가기](https://www.acmicpc.net/problem/21773) [분석](https://codingdog.tistory.com/537) 
* 가희와 로그 파일  [바로가기](https://www.acmicpc.net/problem/21774) [분석](https://codingdog.tistory.com/519) 
* 가희의 자원 놀이  [바로가기](https://www.acmicpc.net/problem/21775) [분석](https://codingdog.tistory.com/666) 
* 가희와 읽기 쓰기 놀이  [바로가기](https://www.acmicpc.net/problem/21776) [분석](https://codingdog.tistory.com/581) 
* 리버스 가희와 프로세스 1  [바로가기](https://www.acmicpc.net/problem/21777) [분석](https://codingdog.tistory.com/626) 
* 가희와 프로세스 2  [바로가기](https://www.acmicpc.net/problem/21778) [분석](https://codingdog.tistory.com/668) 


## 21771. 가희야 거기서 자는 거 아니야 [바로가기](https://www.acmicpc.net/problem/21771)  
* **베개 중의 일부가 가희에 의해서 가려진 상태**라면, 가희는 베게 위에서 자고 있습니다.  
* 가희는 베개 위에서 자고 있거나, 베개 아래에서 자고 있습니다.  

즉, 가희의 일부도 가려지고, 베개의 일부도 가려지는 경우는 없음을 알 수 있습니다. 따라서,  _P_ 와 _G_ 가 몇 번 나오는지만 보면 됩니다.  

## 21774. 가희와 로그 파일 [바로가기](https://www.acmicpc.net/problem/21774)  [분석](https://codingdog.tistory.com/519)
시간 제한을 보면 2초로 꽤 넉넉함을 알 수 있습니다. 시각 데이터는 60만개 주어집니다.  문자열의 길이는 최대 20자이고, 60만개의 시각이 들어올 때, 1200만 x 20 = 2.4억이 됩니다.  이 부분은 구분자를 가지고 _long long_ 형으로 압축한다면, 20이 빠질 수 있습니다.  
  
이 문제에서 더 중요했던 점은 아래 2가지 입니다.  
* 주어진 시작 시각과 종료 시각 **사이**에, ~
* 시각은 **YYYY-MM-DD hh:mm:ss형식**으로 주어진다.
  
형식이 같고 **시각의 선후 관계**만 파악하면 되므로, 문자열로 처리하면 됩니다.

## 21775. 가희의 자원놀이 [바로가기](https://www.acmicpc.net/problem/21775)  [분석](https://codingdog.tistory.com/666)
문제가 상당히 긴 편이여서, 조건을 잡기가 쉽지 않았습니다.  체감 난이도를 결정지었던 결정적인 조건은 아래와 같습니다.
 
* 자원 카드  _n_ 을 획득한 사람이 다시 _acquire  n_ 을 수행하지 않는다.
* 획득하지 않은 자원 카드를 시각은 _release_ 하는 경우는 없다.
  
그렇기 때문에, **자원을 누군가 가지고 있는지**만 관리하면 됩니다. 

## 21776. 가희와 읽기 쓰기 놀이 [바로가기](https://www.acmicpc.net/problem/21776)  [분석](https://codingdog.tistory.com/581) 
문제가 상당히 긴 편이여서, 21775번과 같이 조건을 잡기 쉽지 않았습니다. 문제를 이해하기 위해 파악해야 하는 조건은 아래와 같습니다. 
* i번 사람이 내야 하는 **카드의 순서**는 정해져 있습니다.
* 각 턴을 수행하는 사람은 1명이다.
  * 만약에 2명 이상이라면, 상황이 매우 복잡해 졌을 겁니다.
* 턴을 수행할 때, 카드에 있는 연산을 모두 수행하고 종료한다.
  * 단위 연산이 카드에 있는 연산 모두를 수행하는 것임을 알 수 있습니다.
  * 예제 1번에 있는 설명을 보면 조금 더 쉽게 이해할 수 있습니다.
  
그리고 이 문제는 _N_ 과 _C_ 가 9 입니다. **9! = 40320** 이고 문자열의 길이는 많아봐야 10입니다. 따라서 brute force를 이용해도 문제 없습니다. 
