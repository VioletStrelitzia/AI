#include "core.h"

namespace yuki::atri {
    /// @brief 模型基类
    class ModelBase {
    public:
        ModelBase() = default;
        virtual ~ModelBase() = default;

        /// @brief 预测输入的结果
        /// @param input_ 输入
        virtual auto predict(void* input_) -> void {}

        /// @brief 训练模型
        /// @param dataset_ 用于训练的数据集
        virtual auto train(void* dataset_) -> void {}

        /// @brief 评估模型的性能
        /// @param dataset_ 用于评估的数据集
        virtual auto evaluate(void* dataset_) -> void {}

        /// @brief 导入模型
        /// @param path 文件名
        virtual auto load(string const& path) -> void {}

        /// @brief 保存模型
        /// @param path 文件名
        virtual auto save(string const& path) -> void {}
    };
}