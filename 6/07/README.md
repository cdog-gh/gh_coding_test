# 🔒 가희와 여행 가요
그래프 이론, 그리디, 최소 스패닝 트리
<details>
<summary>🔑힌트 1</summary>
비용을 최소로 하는 조건이 걸려 있으면 어떻게 풀면 되나요?
</details>
<details>
<summary>🔑힌트 2</summary>
이제, 건설 시간을 최소로 하라고 했습니다.
<ul>
  <li> 비용이 같은 경우 <br>
  <li> 건설 시간이 더 큰 간선을 선택하면 어떻게 되나요? <br>
</ul>
건설 시간이 더 작은 간선을 선택해 보세요. 큰 것을 선택할 때 보다 항상 이득이 되게 만들 수 있나요?
</details>
<details>
<summary>💡생각해 볼 만한 것</summary>
크루스칼 알고리즘의 유니온 파인드를 구현할 때 아래 두 가지를 많이 이용합니다.
<ul>
  <li> by path compression <br>
  <li> by rank <br>
</ul>
두 번째 방법으로 구할 때 시간 복잡도는 어떻게 될까요?
</details>