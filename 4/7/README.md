# 🔒 가희와 영상 추천 시스템
자료 구조
<details>
<summary>🔑힌트 1</summary>
추천 영상 1위를 얻고 싶다. 하나만 필요합니다.
</details> 
<details>
<summary>🔑힌트 2</summary>
기준에 따라 순위가 결정 된다. 제일 높은 것을 가지고 온다. <br>
우선 순위가 가장 높은 것을 필요로 하는 것이군요.
</details>
<details>
<summary>🔑힌트 3</summary>
우선 순위는 어떻게 결정되나요? 아래와 같이 결정됩니다.
<ul>
  <li> 카테고리 별 조회수 <br>
  <li> 영상 자체 조회수  <br>
</ul>
그렇다면, 어떤 것을 관리하는 자료구조가 필요할까요?
</details>
<details>
<summary>🔑힌트 4</summary>
영상의 카데고리가 바뀌는 일이 있나요? <br> 
만약 없다면, 오프라인 쿼리로 처리해도 되겠네요. 그러면
<ul>
  <li> 카테고리 별 정렬해서 구간 업데이트 <br>
  <li> 영상의 조회수 업데이트  <br>
  <li> 구간 최대값
</ul>
이 세 연산만 지원되면 되겠군요.
</details>
<details>
<summary>🪤함정 1</summary>
시간 관련 처리는 어떻게 해야 할까요?
</details>