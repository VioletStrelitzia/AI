import torch

o = torch.arange(1, 16).reshape(4, 4)

x = torch.tensor([[1., 2., 3., 111],
                  [4.1, 5, 6, 112],
                  [7.2, 8, 9, 113],
                  [10, 11, 12, 114]])


print(x)

# 访问元素
print(x[1, 2])  # 一个
print(x[:, 1])  # 一列
print(x[1, :])  # 一行
print(x[1:3, 1:])  # 子区域
print(x[::3, ::2])  # 带跳转的子区域

# 形状
print(x.shape)

# 仅改变形状（不改变数量）
x2 = x.reshape(2, 8)
print(x2.shape)

# 标准运算 + - * / **，拓展为按元素运算
a = torch.tensor([1, 2, 3, 4], dtype=torch.float64)
b = torch.tensor([-2, -3, -4, -5], dtype=torch.float64)
print(a + b)
print(a - b)
print(a * b)
print(a / b)
print(a ** 2)

# 所有元素求和
print(x.sum())

# 广播机制

# 执行原地操作
z = torch.zeros_like(x)
print('id(z): ',id(z))
z[:] = z + x
print('id(z): ', id(z))
