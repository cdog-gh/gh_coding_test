# 🔒 가희와 중부 내륙선
구현, parsing, 자료 구조
<details>
<summary>🔑힌트 1</summary>
이벤트는 어떤 순서로 일어나나요?
</details> 
<details>
<summary>🔑힌트 2</summary>
열차가 둘 이상 접근하면 안 되는 곳이 있습니다. 어떻게 컨트롤 되나요?
</details>
<details>
<summary>🔑힌트 3</summary>
힌트 1과 2를 조합해 보았을 때, 구간을 운행하는 이벤트는 어떤 순으로 이루어 지나요?
<ul>
  <li> 구간을 운행할 수 있는지 검사한다. <br>
  <li> 운행할 수 있으면 운행한다. <br>
</ul>
이 순서로 일어납니다.
</details>
<details>
<summary>🔑힌트 4</summary>
각 구간에 대해서는 어떻게 관리하면 될까요?
<ul>
  <li> 구간을 운행할 수 있는지 없는지를 관리하면 되겠네요. <br>
  <li> 즉, 운행 열차가 있는지 없는지 관리하면 됩니다. <br>
</ul>
이 순서로 일어납니다.
</details>
<details>
<summary>🔑힌트 5</summary>
열차는 어떻게 하면 되나요?
<ul>
  <li> 구간을 운행 시작할 때, 소요 시간 뒤에 운행 종료한다는 event를 뿌리면 됩니다. <br>
  <li> 즉 lock을 걸고 t분 후에 lock을 풀겠다는 이벤트를 넣으면 됩니다. <br>
</ul>
lock을 걸고 풀고는 이벤트 개념으로 보시면 되겠네요?
</details>
<details>
<summary>🔑힌트 6</summary>
열차는 나중에 출발하면 번호가 크네요?
<ul>
  <li> 번호가 작으면 시발역에서 먼저 출발한 거죠? <br>
  <li> 따라서 대기 큐는 그냥 FIFO로 관리해도 됩니다. PQ로 관리해도 상관 없습니다. <br>
</ul>
결국, 대기하는 것도 event로 관리하면 됩니다.
</details>
<details>
<summary>💻cs</summary>
<ul>
  <li> event driven <br>
  <li> lock <br>
</ul>
</details>