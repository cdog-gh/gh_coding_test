# 🔒 gahui and sousenkyo 6
수학, 해 구성하기
<details>
<summary>🔑힌트 1</summary>
xor 연산의 특징은 무엇인가요?
</details>
<details>
<summary>🔑힌트 2</summary>
0부터 x까지 xor를 해 봅시다. <br> 특정한 수까지 xor을 했을 때 xor 값이 0이 되는 순간이 존재하지 않나요?
</details>
<details>
<summary>🔑힌트 3</summary>
2진수 100100을 만드는 방법은 어떻게 만들면 될까요?
<ul>
  <li> 바로 100100을 넣는 방법도 있습니다만 <br>
  <li> 111111에 무엇을 xor 하면 될까요? <br>
</ul>
</details>
<details>
<summary>🔑힌트 4</summary>
힌트 3을 다시 봅시다. 0이 있는 상황보다 1만 있는 상황이 컨트롤 하기 쉬워 보입니다.
<ul>
  <li> 그러면 0인 bit가 있는 값을 컨트롤 하는 것 보다 <br>
  <li> bit가 1로만 채워진 것을 컨트롤 하는 게 더 쉽지 않을까요? <br>
</ul>
</details>
<details>
<summary>💡다른 방법</summary>
수를 random 하게 n - 1개 선택하면 어떨까요? 그것과 x를 xor한 값과 겹칠 확률은 얼머나 될까요? <br>
설령 그게 안 된다고 해도 10번, 20번 시도할 시간은 충분하지 않을까요?
</details>