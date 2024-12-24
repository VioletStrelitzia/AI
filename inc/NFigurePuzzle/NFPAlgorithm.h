#pragma once
#include "NFPState.h"
#include "NFPStateSet.h"

namespace yuki::atri::nfp {
    class Algorithm {
    public:
        static bool printPath;

        static i32 nodeCountTemp;
        static bool underExperiment;
    public:
        /// @brief 统计测试函数，在这个函数里设计并输出统计数据
        static auto statisticalExperiment() -> void;

        /// @brief 曼哈顿距离优化的迭代加深搜索
        /// @param originalState 目前的 state
        /// @param targetState 目标 state
        /// @param preZeroPos 上一个 state 的 0 的位置
        /// @param depthLimit 搜索深度限制
        /// @param ans 答案步数
        /// @return 在深度限制内的搜索是否成功
        static auto IDS(State& originalState,
                        State const& targetState,
                        Vector2 const& preZeroPos,
                        i32 const& depthLimit, i32& ans) -> bool;

        /// @brief 宽度优先搜素示例
        /// @param originalState 目前的 state
        /// @param targetState 目标 state
        /// @return i32 答案步数
        /// @retval -1 未搜索到有效路径
        /// @retval 其他 答案步数
        static auto BFS_Demo(State& originalState, State const& targetState) -> i32;

        /// @brief 宽度优先搜素
        /// @param originalState 目前的 state
        /// @param targetState 目标 state
        /// @return i32 答案步数
        /// @retval -1 未搜索到有效路径
        /// @retval 其他 答案步数
        static auto BFS(State& originalState, State const& targetState) -> i32;

        /// @brief 深度有限搜素
        /// @param originalState 目前的 state
        /// @param targetState 目标 state
        /// @param depthLimit 
        /// @return i32 答案步数
        /// @retval -1 未搜索到有效路径
        /// @retval 其他 答案步数
        static auto DLS(State& originalState, State const& targetState, i32 const& depthLimit = State::maxDepth) -> i32;

        /// @brief 启发函数 1 ：错位数码数
        /// @param originalState 目前的 state
        /// @param targetState 目标 state
        /// @return i32 错位数码数
        static auto incorrectCount(State const& originalState, State const& targetState) -> i32;

        /// @brief 启发函数 2 ：曼哈顿距离
        /// @param originalState 目前的 state
        /// @param targetState 目标 state
        /// @return i32 曼哈顿距离
        static auto manhattanDistance(State const& originalState, State const& targetState) -> i32;

        /// @brief 启发式搜索
        /// @param originalState 目前的 state
        /// @param targetState 目标 state
        /// @param heuristicFunc 启发函数
        /// @return i32 答案步数
        /// @retval -1 未搜索到有效路径
        /// @retval 其他 答案步数
        static auto AStar(State& originalState, State const& targetState, function<i32(State const&, State const&)> const& heuristicFunc) -> i32;

        /// @brief 交互模式
        static auto interactiveMode() -> void;

        /// @brief 正确性测试函数
        static auto testSearch() -> void;
    };
    
    auto test() -> void;
}