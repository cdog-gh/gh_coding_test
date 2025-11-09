# 🔒 가희와 사직 구장
구현, 브루트 포스, 정렬
<details>
<summary>🔑힌트 1</summary>
제한을 보니까, 아이돌 3명을 일일히 다 배치해 봐도 통과할 것 같습니다.
</details> 
<details>
<summary>🔑힌트 2</summary>
얻을 수 있는 점수가 큰 순서대로 정렬을 한 후, 어떻게 처리하면 될까요?
</details>
<details>
<summary>🔑힌트 3</summary>
상위 r명의 아이돌을 모두 선택했을 때 점수는 빠르게 구할 수 있습니다.
<ul>
  <li> 1위부터 r위까지 점수만 누적하면 되지 않나요? <br>
  <li> 결국 누적합입니다.  <br>
</ul>
문제는 세 명이 상위 n-3 위에 속햐냐는 것입니다.
</details>
<details>
<summary>🔑힌트 4</summary>
세 명이 상위 n-3위에 속한다고 해도, n+1위까지 볼 이유가 있을까요?
<ul>
  <li> 상위 n-3위에 속한다면 일단 누적에서 빼 주고 <br>
  <li> 최후에 3명에 대해 누적시켜 주면 됩니다.  <br>
</ul>
</details>