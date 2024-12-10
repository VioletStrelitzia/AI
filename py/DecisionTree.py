from sklearn.datasets import load_iris
from sklearn import tree
from sklearn.tree import export_text
import numpy as np
import pandas as pd
import graphviz

'''
iris = load_iris()


with open('resources/iris.csv', 'w') as file:
    # 写入列名和目标列名作为文件的头部
    header = ','.join(iris.feature_names + ['target']) + '\n'
    file.write(header)
    
    # 写入数据和目标
    for data_row, target in zip(iris.data, iris.target):
        row = ','.join(map(str, data_row)) + ',' + ','.join(str(target)) + '\n'
        file.write(row)

X, y = iris.data, iris.target
# 直接对X进行排序
X_sorted = X[np.lexsort((X[:, 2], X[:, 1], X[:, 0]))]  # 按照特征3、2、1的顺序排序

# 对应的目标值也需要按照相同的顺序排序
y_sorted = y[np.lexsort((X[:, 2], X[:, 1], X[:, 0]))]
'''
'''
# 打印排序后的结果
print(X_sorted)
print(y_sorted)
'''

# 使用pandas读取CSV文件
df = pd.read_csv('resources/BDTTrainData.csv', skiprows=[1])

# 分离特征和目标
X = df.drop('WILLWAIT', axis=1).values  # 去掉'target'列，剩下的就是特征
y = df['WILLWAIT'].values  # 'target'列就是目标值

feature_names = ['ALTERNATE','BAR','FRI/SAT ','HUNGRY','PATRONS','PRICE','RAINING','RESERVATION','TYPE','WAITESTIMATE']

clf = tree.DecisionTreeClassifier(criterion='entropy')
clf = clf.fit(X, y)

# 打印结果以验证
print("Features (X):")
print(X)
print("\nTargets (y):")
print(y)

# clf.predict([[2., 2.]]) # 输出类别预测结果
# clf.predict_proba([[2., 2.]]) # 输出各类别预测的概率
tree.plot_tree(clf) #绘制决策树
# 输出txt格式的决策树
r = export_text(clf, feature_names = feature_names)
print(r)

tree.export_graphviz(clf,
                     out_file = "tree.dot",
                     feature_names = feature_names, 
                     class_names = 'WIIWAIT',
                     filled = True)