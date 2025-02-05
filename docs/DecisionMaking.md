# 制定简单决策

- $Result(s_0,a)$：表示 Agent 在状态 $s_0$ 采取行动 $a$ 得到的确定性输出结果。
- $Result(a)$：一个随机变量，表示 Agent 在不知道当前状态状态的情况下采取行动 $a$ 得到的可能的输出结果。
- $P(Result(a)=s'|a,\bm{e})$：给定观察 $\bm{e}$，输出 $s'$ 的概率。

## 概念

### 效用函数

$$U(s)$$
**效用函数**可以分配一个数值给出对状态 $s$ 的评估。

### 一个动作的期望效用

$$EU(a|\bm{e})=\sum_{i}P(Result(a)=s'|a,\bm{e})U(s')$$
行为 $a$ 在观察 $\bm{e}$ 的**期望效用**，是输出结果的加权平均效用值。

### 最大期望效用（MEU）

$$action=\underset{a}{argmax}EU(a|\bm{e})$$

Agent “应该能做正确的事情”。

## 理性偏好的约束

偏好的描述：

- $A\succ B$：Agent 偏好 $A$ 甚于 $B$。
- $A\sim B$：Agent 对 $A$ 和 $B$ 的偏好相同。
- $A\succsim B$：Agent 偏好 $A$ 甚于 $B$ 或者偏好相同。

### 效用理论公理

1. **有序性**
   不能回避决策。
   如偏好 $(A\succ B)$，$(B\succ A)$ 和 $(A\sim B)$ 中必须有且只有一个成立。
2. **传递性**
   $$(A\succ B)\wedge(B\succ C)\rightarrow(A\succ C)$$
3. **连续性**
   $$A\succ B\succ C\rightarrow \exists p[p,A;1-p,C]\sim B$$
4. **可替换性**
   1
5. **单调性**
   1
6. **可分解性**
   1

## 效用

### 金钱的效用

现在你面临一个选择，直接获得 100000 奖金，或者抛硬币，以 $\frac{1}{2}$ 概率获得 250000 或 0 奖金。
接受和拒绝赌博的期望效用为
$$EU(Accept)=\frac{1}{2}U(S_k)+\frac{1}{2}U(S_{k+250000}) \\
EU(Decline)=U(S_{k+100000})$$

关键是初始状态和效用函数。

- **确定性等价物**（Certainty Equivalent）
  一个 Agent 能接受的代替某次抽奖的价值。比如大部分人接受用 400 替代一次一半机会赢 100 一半机会赢 0 的赌博。
- **风险规避**（Risk-averse）
  效用函数（段）：凸曲线。
- **风险追求**（Risk-seeking）
  效用函数（段）：凹曲线。
