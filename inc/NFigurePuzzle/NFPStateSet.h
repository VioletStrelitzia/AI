#pragma once
#include "NFPState.h"

namespace yuki::atri::nfp {
    /**
     * @brief 用于记录 State 是否被搜索过
     * 
     */
    class StateSet {
    private:
        set<usize> s;  ///< 用 set 记录

    public:
        StateSet() = default;
        ~StateSet() = default;

        /**
         * @brief 清空
         * 
         */
        void clear();

        /**
         * @brief 查询某个 State 是否已经被搜索过
         * 
         * @param state 要查询的 State
         * @return bool 某个 State 是否已经被搜索过
         * @retval true 该 State 已经被搜索过
         * @retval false 该 State 未被搜索过
         */
        bool visited(State const& state);

        /**
         * @brief 标记某个 State 是否已经被搜索过
         * 
         * @param state State
         */
        void visit(State const& state);

        /**
         * @brief 将某个 State 的已被搜索过的标记移除
         * 
         * @param state State
         */
        void remove(State const& state);
    };
}
