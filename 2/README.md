# 2회 (패스트캠퍼스 초격차 모의고사 6회) [바로가기](https://www.acmicpc.net/contest/view/658) 
7월 18일 13시부터 18시까지 2회 코딩테스트가 열렸습니다. 
 
* 가희와 파일 탐색기  [바로가기](https://www.acmicpc.net/problem/22232) [분석](https://codingdog.tistory.com/554) 
* 가희와 키워드  [바로가기](https://www.acmicpc.net/problem/22233) [분석](https://codingdog.tistory.com/669) 
* 가희와 은행  [바로가기](https://www.acmicpc.net/problem/22234) [분석](https://codingdog.tistory.com/567) 
* 가희와 btd5  [바로가기](https://www.acmicpc.net/problem/22238) [분석](https://codingdog.tistory.com/620)
* 가희와 수인 분당선 1  [바로가기](https://www.acmicpc.net/problem/22235) [분석](https://codingdog.tistory.com/597) [다른풀이](https://boomrabbit.tistory.com/170) 
* 가희와 비행기  [바로가기](https://www.acmicpc.net/problem/22236) [분석](https://codingdog.tistory.com/653) 
* 가희와 거북이 인형  [바로가기](https://www.acmicpc.net/problem/22237) [분석](https://codingdog.tistory.com/564) [분석2](https://codingdog.tistory.com/590) 
* 가희와 읽기 쓰기 놀이 2  [바로가기](https://www.acmicpc.net/problem/22239) 

#### 연계 문제들
|문제번호|내용|연계문제|
|:------:|:-------------:|:-----:|
|22234|스케쥴링 알고리즘 구현 연계|21773|
|22235|시각 파싱 유형 연계|21774|
|22237|상대 속도와 절대 속도 개념 연계|21773|
|22232|string 파싱 및 equal, range query 간접 연계|21771|
|22233|string 파싱 연계|21772|

## 22232. 가희와 파일탐색기 [바로가기](https://www.acmicpc.net/problem/22232) [분석](https://codingdog.tistory.com/554)  
간단한 정렬문제입니다. 잘못 구현할 수 있는 포인트는 아래와 같습니다.
* compare(a, b)가 True 이면서 **compare(b, a)가 True가 되게 리턴**하는 경우  
* string을 long long으로 압축할 때, 10자 미만인 string에 대한 처리

*equal*이 아닌 상대 비교 처리가 필요하므로, 2번째의 경우, 10자 미만일 때, 나머지 부분을 *padding* 처리하시면 됩니다. 

## 22233. 가희와 키워드 [바로가기](https://www.acmicpc.net/problem/22233) [분석](https://codingdog.tistory.com/669) 
반대로 이것은 키워드의 *equal*이 중요하므로 *padding* 처리를 하지 않고 압축하셔도 됩니다. 이 문제는 아래를 주의하셔야 합니다.
* 나올 수 있는 *keyword* 수가 **최대 220만**개여서 set, map을 이용하면 시간초과가 난다.
* 문자열 정렬을 할 때, 두 key의 *compare* 시간이 오래 걸릴 수도 있다.


## 22234. 가희와 은행 [바로가기](https://www.acmicpc.net/problem/22234) [분석](https://codingdog.tistory.com/567)  
잘 읽어보면 *Round Robin*과 비슷함을 알 수 있습니다. 출력해야 하는 시간이 **20만 이하**이니, 이 부분만 이벤트 배열에 넣으면 됩니다.
* N+M명의 사람들을 sort() 메서드로 정렬하는 경우
  * sort 메서드는 **stable 하지 않으므로** 조심하셔야 합니다. 비슷한 개념의 문제 중에는, [2910번](https://www.acmicpc.net/problem/2910)이 있습니다.
  * 이는 맨 처음에 온 사람들은 **입력 받은 순서대로 줄을 서야 하기 때문**입니다.
* 1초마다 처리하는 게 아니라, 특정 시간 초마다 처리하는 경우 구현이 복잡해 질 수 있음.
* 업무를 처리하는 데 필요한 시간이 **W보다 작은 경우**

를 주의하시면 됩니다.

## 22238. 가희와 btd5 [바로가기](https://www.acmicpc.net/problem/22238) 
풍선들이 있는 위치를 잘 읽어야 합니다. 공격할 때 풍선들을 못 맞출 수도 있습니다. 그런데, 이것 말고도 매력적인 함정이 몇 가지 있었습니다.
* double, float 등으로 처리할 때 **실수 오차**
* (x, 0), (0, x) 방향으로 공격하는 데이터 (단, **x는 0이 아닌 정수**)
* 음수에 대한 처리

double이나 float와 같은 실수 데이터는 정밀도를 신경써야 합니다. 실수 오차에 대한 데이터는 [여기](https://github.com/cdog-gh/gh_coding_test/blob/main/2/4/double_att.in)에 있습니다.  
실제로 이 함정에만 걸려서, *ccw* 알고리즘으로 선회하신 분도 계셨습니다.

## 22235. 가희와 수인분당선 [바로가기](https://www.acmicpc.net/problem/22235) 
쉽지 않은 문제입니다만, 아래 두 가지 질문에 잘 생각해 보시면 난이도가 다소 쉬워집니다.
* 왕십리발 오이도행 열차를 죽전역에서 탑승했다고 했을 때
  * 죽전역에서 열차를 내린 다음에 바로 타나, 해당 열차를 그대로 타고 가나 별 차이가 없습니다.
  * 그러면 종착역이 되는 죽전, 고색, 오이도, 인천에서 **열차에 내리는 action** 을 취하면 되지 않을까요?
* 역 a에서 역 b으로 가장 빠르게 가려면, b역 방향으로 가는 **가장 빨리 오는 열차**를 타면 됩니다.

## 22237. 가희와 거북이 인형 [바로가기](https://www.acmicpc.net/problem/22237) [분석](https://codingdog.tistory.com/590) 
넓은 맵 크기, 거북이 컴포넌트에 비해 매우 **적은 장애물** 개수가 키 포인트입니다. 거북이의 맨 위, 왼쪽 꼭대기를 기준 좌표로 삼아봅시다. 
그러면, 해당 위치가 거북이가 있을 수 있는 위치인지, 그렇지 않은 위치인지 파악해야 하는 문제로 환원됨을 알 수 있습니다.
* 거북이 전체가 1칸 
  * 왼쪽으로 이동한 것 = 장애물 전체가 1칸 ?쪽으로 이동한 것
  * 오른쪽으로 이동한 것 = 장애물 전체가 1칸 ?쪽으로 이동한 것
  * 위로 이동한 것 = 장애물 전체가 1칸 ?쪽으로 이동한 것
  * 아래로 이동한 것 = 장애물 전체가 1칸 ?쪽으롤 이동한 것
* 고려해야 하는 요소는 **집**과 **장애물** 외에 무엇이 있을까요?