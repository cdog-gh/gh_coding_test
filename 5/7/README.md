# 🔒 가희와 지하철역 저장 시스템 2
객체 지향 프로그래밍, 구현, 최단 거리 알고리즘
<details>
<summary>🔑힌트 1</summary>
어떻게 기능을 분리해야 할까요?
</details>
<details>
<summary>🔑힌트 2</summary>
문제에서 설명한 캐시 알고리즘은 어떻게 동작하나요?
</details>
<details>
<summary>🔑힌트 3</summary>
프로그램을 이렇게 나누어 볼까요?
<ul>
  <li> lru cache를 구현한 class <br>
  <li> 최단 거리를 미리 전처리 하는 코드 <br>
  <li> bucket 노드 x가 주어졌을 때 가장 가까운 캐시 노드 c를 가져오는 함수 <br>
</ul>
</details>
<details>
<summary>🔑힌트 4</summary>
힌트 3의 기능들을 어떻게 구현할까요?
<ul>
  <li> python orderedDict이나, java LinkedHashMap 등을 이용하면 되겠군요. <br>
  <li> 노드 수가 많아야 300이네요? 그러면 floyd도 이용할 수 있겠군요. <br>
  <li> 전처리 된 dist 배열을 가지고, 제일 가까운 캐시 노드 c를 전처리 해야 겠군요. <br>
</ul>
</details>
<details>
<summary>💡생각해 볼 만한 것 1</summary>
만약에 java LinkedHashMap이나 python orderedDict를 사용하지 못하면 어떻게 구현하면 될까요? 
<ul>
  <li> hashmap + queue <br>
  <li> hashmap + linkedlist <br>
</ul>
두 번째 방법으로 구할 때 시간 복잡도는 어떻게 될까요?
</details>
<details>
<summary>💡생각해 볼 만한 것 2</summary>
언어별로 제공되는 순서가 유지되는 hash 자료구조에 대해 알아보세요.
</details>