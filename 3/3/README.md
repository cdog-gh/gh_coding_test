# 🔒 가희와 쓰레기 놀이
bfs, dfs, 그래프 이론, 최적화
<details>
<summary>🔑힌트 1</summary>
몇 개의 연산을 없애 봅시다. <br>
<ul>
  <li> 강한 연결 관계만 있고 <br>
  <li> 강한 연결 관계만 끊는다고 해 봅시다. <br>
  <li> 그리고 M 연산만 있다고 해 봅시다. <br>
</ul>
가비지는 어떻게 없앨 수 있을까요?
</details> 
<details>
<summary>🔑힌트 2</summary>
강한 연결 관계와 약한 연결 관계는 어떤 속성만 다른가요?
</details>
<details>
<summary>🔑힌트 3</summary>
시간 제한이 빡빡해 보입니다. 연결 관계를 관리하는 데 hashmap이나 treemap이 왜 필요한가요?
</details>
<details>
<summary>🔑힌트 4</summary>
<ul>
  <li> a -> b의 연결 관계가 만들어진 시각이 3입니다. <br>
  <li> a -> b의 연결 관계가 제거된 시각이 7입니다. <br>
</ul>
이 두 정보가 저장되어 있을 때 쓸모없는 정보는 어떤 것인가요? <br>
그리고 이 쓸모 없는 정보는 어느 연산에서 처리하면 될까요?
</details>
<details>
<summary>🔑힌트 5</summary>
삭제 연산이 없다면, 동적 배열만으로 처리할 수 있을까요? 어떻게 처리할까요? <br>
</details>
<details>
<summary>💻cs</summary>
gc (garbage collection)
<ul>
  <li> 가비지 <br>
  <li> mark & sweep <br>
  <li> java reference class  <br>
</ul>
</details>
<details>
<summary>💡생각해 볼 만한 것</summary>
<ul>
  <li> 쓸모 없는 정보를 제거하는 트릭은 어떻게 쓰일까요? <br>
  <li> java reference class, 혹은 이와 유사한 역할을 하는 클래스를 조사해 보세요. <br>
</ul>
</details>