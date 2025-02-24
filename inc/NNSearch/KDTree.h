#pragma once
#include "Ycore.h"
#include "YTreeNodeBase.h"
#include "Ytools.h"

namespace yuki::atri::nns {
    class KDTreeNode: public TreeNodeBase {
    public:
        vector<f64> data;
        i32         splitDimension;

        shared_ptr<KDTreeNode> lchild = nullptr;
        shared_ptr<KDTreeNode> rchild = nullptr;

        KDTreeNode() = default;

        ~KDTreeNode() = default;

        auto printTree(i32 const& depth = 0) const -> void override {

        }

        auto dot(ofstream& outFile, i32& idx, string const& fromParent) const -> void override {
            outFile << format("{} [label=\"{}\\nSplit by d: {}\", fillcolor=\"{}\"];\n",
                idx, fromParent, splitDimension, "#e58139");
            i32 curIdx = idx;
            if (lchild) {
                ++idx;
                outFile << format("{} -> {};", curIdx, idx);
                lchild->dot(outFile, idx, format("[{}]: < {}", splitDimension, data[splitDimension]));
            }
            if (rchild) {
                ++idx;
                outFile << format("{} -> {};", curIdx, idx);
                rchild->dot(outFile, idx, format("[{}]: > {}", splitDimension, data[splitDimension]));
            }
        }

        friend class KDTree;
    private:
        /// @brief 获取各个维度上的方差
        /// @param examples 样本集
        /// @return 各个维度上的方差
        auto getVariance(vector<vector<f64> const*> const& examples) const -> vector<f64> {
            f64 n = static_cast<f64>(examples.size());
            i32 d = static_cast<i32>(examples[0]->size());
            vector<f64> average(d, 0.), variance(d, 0.);
            for (vector<f64> const* const& vec: examples) {
                for (i32 i = 0; i < d; ++i) {
                    average[i] += (*vec)[i];
                }
            }

            for (i32 i = 0; i < d; ++i) {
                average[i] /= n;
            }

            for (vector<f64> const* const& vec: examples) {
                for (i32 i = 0; i < d; ++i) {
                    variance[i] += ((*vec)[i] - average[i]) * ((*vec)[i] - average[i]);
                }
            }

            return variance;
        }

        /// @brief 按照指定维度将样本集排序
        /// @param examples 样本集
        /// @param dimension 排序维度
        auto insertSort(vector<vector<f64> const*>& examples, i32 const& dimension) -> void {
            vector<f64> const* temp;
            for (i32 i = 1, j, end = (i32)examples.size(); i < end; ++i) {
                temp = examples[i];
                j = i;
                while (j > 0 && (*examples[j - 1])[dimension] < (*temp)[dimension]) {
                    examples[j] = examples[j - 1];
                    --j;
                }
                examples[j] = temp;
            }
        }

        auto build(vector<vector<f64> const*>& examples) -> void {
            i32 n = static_cast<i32>(examples.size());
            if (n == 1) {
                data = *examples[0];
                return;
            }
            i32 d = static_cast<i32>(examples[0]->size());
        
            vector<f64> variance = getVariance(examples);
            cout << variance << endl;

            vector<i32> splitDimensions(1, 0);
            for (i32 i = 1; i < d; ++i) {
                // 选方差大的维度，提高分辨率
                if (variance[splitDimensions.back()] < variance[i]) {
                    splitDimensions.clear();
                    splitDimensions.push_back(i);
                } else if(variance[splitDimensions.back()] == variance[i]) {
                    splitDimensions.push_back(i);
                }
            }
            splitDimension = random::choose(splitDimensions);

            rg::sort(examples, [this](vector<f64> const*& v1, vector<f64> const*v2) -> bool {
                return (*v1)[splitDimension] > (*v2)[splitDimension];
            });
            
            //insertSort(examples, splitDimension);
            data = *examples[n >> 1];

            vector<vector<f64> const*> leftExamples(examples.begin(), examples.begin() + (n >> 1));
            if (!leftExamples.empty()) {
                lchild = shared_ptr<KDTreeNode>(new KDTreeNode());
                lchild->build(leftExamples);
            }
            vector<vector<f64> const*> rightExamples(examples.begin() + (n >> 1) + 1, examples.end());
            if (!rightExamples.empty()) {
                rchild = shared_ptr<KDTreeNode>(new KDTreeNode());
                rchild->build(rightExamples);
            }
        }

        auto search(vector<f64> const& target, vector<f64> const*& nearest) -> void {
            if (distanceEuclidean(target, data) < distanceEuclidean(target, *nearest)) {
                nearest = &data;
            }

            if (target[splitDimension] < data[splitDimension]) {
                if (lchild) {
                    lchild->search(target, nearest);                
                }
                if (rchild && distanceEuclidean(target, *nearest) >= abs(target[splitDimension] - data[splitDimension])) {
                    rchild->search(target, nearest);
                }
            } else {
                if (rchild) {
                    rchild->search(target, nearest);
                }
                if (lchild && distanceEuclidean(target, *nearest) >= abs(target[splitDimension] - data[splitDimension])) {
                    lchild->search(target, nearest);
                }
            }
        }

    };

    class KDTree {
    private:
        i32 dimension = 0;
        shared_ptr<KDTreeNode> root;

    public:
        KDTree(i32 const& dimension):
            dimension(dimension), root(new KDTreeNode()) {}
        ~KDTree() = default;

        auto build(vector<vector<f64>> const& examples) -> void {
            vector<vector<f64> const*> exs;
            for (vector<f64> const& example: examples) {
                exs.push_back(&example);
            }
            root->build(exs);
        }

        auto search(vector<f64> const& target) -> vector<f64> {
            vector<f64> const* nearest = &root->data;
            root->search(target, nearest);
            return *nearest;
        }

        auto dot(string path, bool const& genGraph = true, string const& extension = "pdf") -> void {
            ofstream outFile;
            outFile.open(path, std::ios::out);
            if (outFile.is_open()) {
                outFile << "digraph Tree {\nnode [shape=box, style=\"filled\", color=\"black\", fontname=\"Microsoft YaHei\", fontsize=26];\nedge [fontname=\"Microsoft YaHei\", fontsize=26];\n";
                i32 idx = 0;
                root->dot(outFile, idx, "Root");
                outFile << "}";
            }
            outFile.close();

            if (genGraph) {
                while (path.back() != '.') {
                    path.pop_back();
                }
                path.pop_back();
                system(format("dot -T{} {}.dot -o {}.{}", extension, path, path, extension).c_str());
            }
        }

    };
    
}
