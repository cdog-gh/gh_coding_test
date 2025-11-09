# 🔒 가희와 파일 탐색기 2
구현, 자료구조
<details>
<summary>🔑힌트 1</summary>
Q번 수행하는 연산이 무엇인가요?
</details> 
<details>
<summary>🔑힌트 2</summary>
파일의 소유자와 그룹은 쉽게 구할 수 있습니다. 남은 건 무엇인가요?
</details>
<details>
<summary>🔑힌트 3</summary>
특정 그룹에 user가 속해있는지 빠르게 구하고 싶어요. 어떻게 하면 될까요?
<ul>
  <li> 일단 그룹을 key로 가집니다. <br>
  <li> 그룹에 대한 정보를 value로 가지는 자료구조를 하나 선언하면 되겠죠?  <br>
</ul>
여기서 무엇을 더 해야 할까요?
</details>
<details>
<summary>🔑힌트 4</summary>
그룹에 속하는 유저는 최대 몇 명일까요?
<ul>
  <li> 만약에 속할 수 있는 유저가 매우 많다면 <br>
  <li> 그룹에 속한 유저의 정보도 key를 기반으로 빠르게 찾는 자료 구조로 관리하면 되지 않을까요?  <br>
</ul>
</details>
<details>
<summary>🔑힌트 5</summary>
문제를 잘 읽어 보면, 유저가 속한 그룹 수는 최대 11개임을 알 수 있습니다. <br>
그런데 쿼리에서는 연산을 실행하는 유저 이름도 알고 있단 말이지요? 그렇다면
<ul>
  <li> 유저 이름을 key로 삼고 <br>
  <li> value로 group의 정보들을 관리해도 되겠네요.  <br>
</ul>
</details>
<details>
<summary>🔑힌트 6</summary>
권한은 어떻게 관리해야 할까요? 권한은 8개 밖에 없네요?
<ul>
  <li> 우직하게 구현해도 되지만 <br>
  <li> 8개 정도면 하드 코딩해도 큰 문제는 없지 않을까요?  <br>
</ul>
</details>
<details>
<summary>💻cs</summary>
<ul>
  <li> linux file permission <br>
  <li> 권한 <br>
</ul>
</details>