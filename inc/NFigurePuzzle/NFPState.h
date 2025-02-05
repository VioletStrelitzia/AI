#pragma once
#include "YPosition2.h"
#include "Ycore.h"

namespace yuki::atri::nfp {
    /**
     * @brief 用来描述棋盘状态的类。
     * @param data 状态压缩存进里面，64位每4位存一个数，最多可以测试到15数码问题
     * @param zeroPos 0的位置
     * @param depth 深度
     * @param nextActions 该状态的可行的后继动作序列
     * @param prevActions 该状态的前序动作序列
     */
    class State {
    public:
        // 修改以下两个参数，整个框架可以自动转换到 rows * cols 数码问题（需要保证 rows * cols <= 16）
        static int const rows     = 3;  ///< 数码盘的行数
        static int const cols     = 3;  ///< 数码盘的列数
        static int const maxDepth = 20; ///< 最大深度
        static int const size = rows * cols; ///< 数码盘的总大小

        using Action = Vector2; ///< 使用 Vector2 作为动作类型，向哪里走就相当于加上哪个方向的单位方向向量

        static int const     actionsNum = 4;             ///< 可能的 Action 总数有四种
        static Action const  actions[actionsNum];        ///< 可能的 Action 初始化存在 actions 里
        static string const  actionInfo[actionsNum];     ///< actionInfo[i] 对应 actions[i] 的具体信息（如向上走等）
        static State         _targetNFPState;            ///< 目标状态
        static vector<State> allNFPStates;               ///< 存放 最优解在 0~maxDepth 深度的所有 NFPState
        static int           depthIndexs[maxDepth + 1];  ///< 索引数组

        usize    data;    ///< 状态压缩，64位每4位存一个数，最多可以测试到15数码问题
        Vector2 zeroPos;  ///< 0 的位置
        int      depth;   ///< 深度

        vector<Action const*> nextActions; ///< 可行的后继动作序列
        vector<Action const*> prevActions; ///< 前序动作序列
    private:
        static usize mask[rows][cols]; ///< 掩码，用于提取压缩进 data 的数码信息，需要在 main函数 显式调用 initMask() 初始化

        static string const precisionFilename; ///< 设置文件的名称

        static random_device rd;  ///< 真随机数生成器
        static mt19937       gen; ///< 以真随机数为种子的伪随机数生成器

    public:
        /**
         * @brief 初始化，一定要执行。
         * @param targetNFPState 目标状态
         */
        static void init(State const& targetNFPState);

        /**
         * @brief 获取row行col列的数码。
         * @param row 行
         * @param col 列
         * @return 数码
         */
        usize at(int const& row, int const& col) const;

        /**
         * @brief 消耗一个可行后继动作生成一个后继 NFPState。
         * 会导致本节点减少一个后继动作。
         * 生成的后继节点默认已经初始化了可行后继动作序列并且继承了本节点的前序动作序列，并且深度+1。
         * @return 后继 NFPState
         */
        State genNextNFPState();

        /**
         * @brief 检测本节点是否存在可行后继动作。
         */
        bool hasNextAction() const;

        /**
         * @brief 对本节点执行动作，产生的后继节点直接覆盖在本节点变量上。
         */
        void executeAction(Action const* const& action);

        /**
         * @brief 重置状态的深度、后继动作以及前序动作。
         */
        void reset();

        /**
         * @brief 将 0 移动到 swapPos。
         * @param swapPos 和 0 交换位置的数码的位置
         */
        void zeroMoveTo(Vector2 const& swapPos);

        /**
         * @brief 更新本节点的后继节点序列。可以输入上一步的动作来避免序列中生成其反动作导致走回头。
         * @param lastAction 上一步的动作
         */
        void updateNextActions(Action const* const& lastAction = nullptr);

        /**
         * @brief 从本节点的后继节点序列随机获取一个动作指针返回（不消耗动作）。
         * @return 指向动作的指针
         */
        Action const* genRandomAction() const;

        /**
         * @brief 随机生成深度。
         * @return 随机深度
         */
        int genRandomDepth(int const& min, int const& max) const;

        /**
         * @brief 随机生成最优解深度为depth的初始状态。
         * @param depth 最优解深度的
         * @return 最优解深度为depth的初始状态
         */
        static State genRandomNFPState(int const& depth = -1);

        // 各种构造函数
        State(usize const& data, Vector2 const& pZero, int const& depth = 0);
        State(initializer_list<initializer_list<usize>> const& listList);
        State(State const& other);
        State(State&& other) noexcept;

        // 赋值函数
        State& operator=(State const& other);

        bool operator<(State const& other) const;

        // 判相等（每个位置上数码一样即为相等）
        bool operator==(State const& other) const;

        // 判不相等（有某个位置上数码不一样即为不相等）
        bool operator!=(State const& other) const;

        // 输出路径
        void printPath() const;

        friend ostream& operator<<(ostream& os, State const& NFPState);

    private:
        void static genPrecision(State const& originalNFPState);
    };

    std::ostream& operator<<(std::ostream& os, yuki::atri::nfp::State const& NFPState);
}