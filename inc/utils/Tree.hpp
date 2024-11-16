#pragma once
#include "TreeNode.hpp"
#include "core.hpp"

namespace yuki {
    template <typename ElemType>
    class Tree {
    public:
        TreeNode<ElemType>* root = nullptr;
        
    private:
        // 相当于构造函数
        // 默认不会出现空括号(内容只有逗号的括号)
        TreeNode<ElemType>* CreateTree(string const& str) {
            if (str.empty()) {
                return nullptr;
            }

            TreeNode<ElemType>* root = nullptr;
            TreeNode<ElemType>* temp = nullptr;

            stack<TreeNode<ElemType>*> s;

            bool nextIsLeftChild = true;

            for (auto const& c : str) {
                switch (c) {
                // 找到左括号，将temp入栈，预备添加其孩子
                case '(':
                    s.push(temp);
                    break;
                // 找到逗号
                case ',':
                    break;
                // 找到右括号，说明栈顶结点的孩子已更新完毕，将其出栈
                case ')':
                    s.pop();
                    break;
                // 其他情况，说明是结点的data，新建结点并根据nextIsLeftChild将其添加为当前栈顶结点的左/右孩子（注意根节点的处理）
                default:
                    temp = new TreeNode<ElemType>();
                    temp->data = c;
                    if (root == nullptr) {
                        root = temp;
                        s.push(temp);
                    } else {
                        s.top()->child.push_back(temp);
                    }
                    break;
                }
            }
            return root;
        }

        // 递归地生成二叉树的括号表示串
        auto createDis(TreeNode<ElemType>* const& root) const -> string {
            string dst;
            dst += toString<ElemType>(root->data);
            if (root->child.size()) {
                dst.push_back('(');
                for (TreeNode<ElemType>* const& c : root->child) {
                    dst += createDis(c) + ", ";
                }
                dst.pop_back();
                dst.pop_back();
                dst.push_back(')');
            }
            return dst;
        }

        void deepCopy(TreeNode<ElemType>& newTree, TreeNode<ElemType> const& originalTree) {
            for (TreeNode<ElemType> const& c : originalTree.child) {
                newTree.child.push_back(new TreeNode<ElemType>(c.data));
                deepCopy(newTree.child.back());
            }
        }
    
    public:
        Tree() = default;

        Tree(string const& str):
            root(CreateTree(str)) {}

        Tree(Tree const& tree):
            root(new TreeNode(tree.root->data)) {
            deepCopy(root, tree);
        }

        Tree(Tree&& tree):
            root(tree.root) {
            tree.root = nullptr;
        }

        ~Tree() {
            queue<TreeNode<ElemType>*> q;
            q.push(root);
            // 层次遍历，出队时删除结点
            while (q.size()) {
                TreeNode<ElemType>*& curNode = q.front();
                for (TreeNode<ElemType>* const& c : curNode->child) {
                    q.push(c);
                }
                delete curNode;
                q.pop();
            }
        }

        // 返回二叉树的括号表示串
        string DisTree() const {
            return createDis(root);
        }

        // 在二叉树中查找值为x的结点
        TreeNode<ElemType>* FindNode(ElemType const& x) {
            queue<TreeNode<ElemType>*> q;
            q.push(root);
            // 层次遍历
            while (q.size()) {
                TreeNode<ElemType>*& curNode = q.front();
                // 找到则返回
                if (curNode->data == x) {
                    return curNode;
                }
                for (TreeNode<ElemType>* const& c : curNode->child) {
                    q.push(c);
                }
                q.pop();
            }
            return nullptr;
        }

        // 求二叉树的高度
        int Height() const {
            queue<pair<TreeNode<ElemType>*, int>> q;
            int height = 0;
            q.push({root, 1});
            // 层次遍历，并记录每个结点的高度
            while (q.size()) {
                pair<TreeNode<ElemType>*, int>& curPair = q.front();
                TreeNode<ElemType>*& curNode = curPair.first;
                int& curHeight = curPair.second;
                if (curHeight > height) {
                    height = curHeight;
                }
                for (TreeNode<ElemType>* const& c : curNode->child) {
                    q.emplace(c, curHeight + 1);
                }
                q.pop();
            }
            return height;
        }
    };
}