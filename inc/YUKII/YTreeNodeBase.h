#pragma once
#include "Ycore.h"

namespace yuki {
/**
 * @brief 树结点基类
 * @details 用于规范树的可视化接口
 */
class TreeNodeBase {
public:
    TreeNodeBase() = default;
    virtual ~TreeNodeBase() = default;

    /**
     * @brief 在命令行窗口打印树（递归）
     * 
     * @param depth 当前结点深度
     */
    virtual auto printTree(i32 const& depth = 0) const -> void = 0;

    /**
     * @brief 为树生成 dot 文件
     * 
     * @param outFile 文件输出类
     * @param idx 结点的序号
     * @param fromParent 双亲结点传递的信息
     */
    virtual auto dot(ofstream& outFile, i32& idx, string const& fromParent) const -> void = 0; 
};
}