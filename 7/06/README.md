# 🔒 가희와 클럽 오디션 3
수학, dp
<details>
<summary>🔑힌트 1</summary>
문제에서 물어보는 것이 무엇인가요? 중요한 factor는 무엇인가요?
</details>
<details>
<summary>🔑힌트 2</summary>
역방향 노트를 lv개 중 k개 뽑고 생각해 봅시다. 
</details>
<details>
<summary>🔑힌트 3</summary>
정방향 노트에 대해서 역방향 노트 하나씩 존재한다고 했나요? <br>
그러면 정방향 lv개 해 놓고, 그 중 몇 개를 선택해서 역방향으로 설정하면 어떨까요?
</details>
<details>
<summary>💡풀이 2</summary>
dp[lv][rev]를 아래와 같이 정의하면 어떨까요? <br>
키 노트의 레벨이 lv이고, 역 방향 키 노트의 개수가 rev인 가짓수.
</details>