#include "NFPAlgorithm.h"

namespace yuki::nfp {
    bool NFPAlgorithm::printPath = true;
    int NFPAlgorithm::nodeCountTemp = 0;
    bool NFPAlgorithm::underExperiment = false;

    // 统计测试函数，在这个函数里设计并输出统计数据
    void NFPAlgorithm::statisticalExperiment() {
        underExperiment = true;
        clock_t t;
        int sampleNum = 100;
        int timeCosts[5][NFPState::maxDepth / 2] = { 0 };
        int nodeCounts[5][NFPState::maxDepth / 2] = { 0 };
        int ans;
        
        for (int d = 2; d <= NFPState::maxDepth; d += 2) {
            int j = (d - 2) / 2;
            for (int i = 0; i < sampleNum; ++i) {
                NFPState originalNFPState(NFPState::genRandomNFPState(d));

                nodeCountTemp = 0;
                t = clock();
                BFS(originalNFPState, NFPState::_targetNFPState);
                t = clock() - t;
                timeCosts[0][j] += t;
                nodeCounts[0][j] += nodeCountTemp;

                nodeCountTemp = 0;
                t = clock();
                if (d < 8) {
                    DLS(originalNFPState, NFPState::_targetNFPState);
                }
                t = clock() - t;
                timeCosts[1][j] += t;
                nodeCounts[1][j] += nodeCountTemp;

                nodeCountTemp = 0;
                t = clock();
                AStar(originalNFPState, NFPState::_targetNFPState, incorrectCount);
                t = clock() - t;
                timeCosts[2][j] += t;
                nodeCounts[2][j] += nodeCountTemp;

                nodeCountTemp = 0;
                t = clock();
                AStar(originalNFPState, NFPState::_targetNFPState, manhattanDistance);
                t = clock() - t;
                timeCosts[3][j] += t;
                nodeCounts[3][j] += nodeCountTemp;

                nodeCountTemp = 0;
                t = clock();
                IDS(originalNFPState, NFPState::_targetNFPState, originalNFPState.zeroPos, d, ans);
                t = clock() - t;
                timeCosts[4][j] += t;
                nodeCounts[4][j] += nodeCountTemp;
            }
            cout << d << "p ";
        }
        
        cout << endl << "不同最优解深度不同算法平均拓展结点总数\n";
        cout << std::setw(10) << std::left << "depth";
        cout << std::setw(10) << std::left << "BFS";
        cout << std::setw(10) << std::left << "DLS";
        cout << std::setw(10) << std::left << "A*_1";
        cout << std::setw(10) << std::left << "A*_2";
        cout << std::setw(10) << std::left << "IDS" << endl;
        for (int d = 2; d <= NFPState::maxDepth; d += 2) {
            int j = (d - 2) / 2;
            cout << std::setw(10) << std::left << d;
            for (int i = 0; i < 5; ++i) {
                cout << std::setw(10) << std::left << (double)nodeCounts[i][j] / sampleNum;
            }
            cout << endl;
        }

        cout << endl;
        cout << endl << "不同最优解深度不同算法平均平均耗时/ms\n";
        cout << std::setw(10) << std::left << "depth";
        cout << std::setw(10) << std::left << "BFS";
        cout << std::setw(10) << std::left << "DLS";
        cout << std::setw(10) << std::left << "A*_1";
        cout << std::setw(10) << std::left << "A*_2";
        cout << std::setw(10) << std::left << "IDS" << endl;
        for (int d = 2; d <= NFPState::maxDepth; d += 2) {
            int j = (d - 2) / 2;
            cout << std::setw(10) << std::left << d;
            for (int i = 0; i < 5; ++i) {
                cout << std::setw(10) << std::left << (double)timeCosts[i][j] / sampleNum;
            }
            cout << endl;
        }
        cout << endl;
        underExperiment = false;
    }

    /// @brief 曼哈顿距离优化的迭代加深搜索
    /// @param originalNFPState 目前的NFPState
    /// @param targetNFPState 目标NFPState
    /// @param now 目前已走过的步数
    /// @param preZeroPos 上一个NFPState的0的位置
    /// @param depthLimit 搜索深度限制
    /// @return 在深度限制内的搜索是否成功
    bool NFPAlgorithm::IDS(NFPState& originalNFPState, NFPState const& targetNFPState, NFPPosition const& preZeroPos, int const& depthLimit, int& ans) {
        if (originalNFPState == targetNFPState) {
            ans = originalNFPState.depth;
            return true;
        }

        // 当前步数（深度） + 估价 > 深度限制，立即回溯 
        if (manhattanDistance(originalNFPState, targetNFPState) > depthLimit) {
            return false;
        }

        // 枚举可以执行的action，即每次向上、下、左、右移动
        for (int actionId = 0; actionId < NFPState::actionsNum; ++actionId) {
            NFPPosition zeroPos = originalNFPState.zeroPos; // 0 的位置
            NFPPosition swapPos = zeroPos + NFPState::actions[actionId]; // 要交换的数 的位置

            // 优化：如果 0 将要回到回到上一次的位置，会判断直接跳过这次 action 而不往下搜索，避免提前回溯重复搜索
            // 以及越界判断
            if (preZeroPos == swapPos ||
                swapPos.r < 0 || swapPos.r >= NFPState::rows ||
                swapPos.c < 0 || swapPos.c >= NFPState::cols) {
                continue;
            }

            // 交换 0 和 交换的数码 的位置
            originalNFPState.zeroMoveTo(swapPos);
            ++originalNFPState.depth;

            if (underExperiment) {
                ++nodeCountTemp;
            }
            if (IDS(originalNFPState, targetNFPState, swapPos, depthLimit, ans)) {
                // 回溯的过程中顺便输出步骤
                if (printPath) {
                    cout << "第" << originalNFPState.depth << "步:" << NFPState::actionInfo[actionId] << endl;// << originalNFPState << endl << endl;
                }

                originalNFPState.zeroMoveTo(zeroPos);
                --originalNFPState.depth;
                return true;
            }

            // 回溯，交换回来 空格0 和 旁边要交换的数 的位置，并回溯 originalNFPState 零的位置，预备下一个 action 的搜索
            originalNFPState.zeroMoveTo(zeroPos);
            --originalNFPState.depth;
        }
        return false;
    }

    // 宽度优先搜索示例
    int NFPAlgorithm::BFS_Demo(NFPState& originalNFPState, NFPState const& targetNFPState) {
        originalNFPState.reset();
        queue<NFPState> q;
        NFPStateSet set;
        q.push(originalNFPState);
        if (underExperiment) {
            ++nodeCountTemp;
        }
        while (!q.empty()) {
            NFPState curNFPState = q.front();
            if (curNFPState == targetNFPState) {
                if (printPath) {
                    curNFPState.printPath();
                }
                return curNFPState.depth;
            }
            set.visit(curNFPState);
            while (curNFPState.hasNextAction()) {
                NFPState nextNFPState(curNFPState.genNextNFPState());
                if (!set.visited(nextNFPState)) {
                    if (underExperiment) {
                        ++nodeCountTemp;
                    }
                    q.emplace(nextNFPState);
                }
            }
            q.pop();
        }
        return -1;
    }

    // 宽度优先搜索
    int NFPAlgorithm::BFS(NFPState& originalNFPState, NFPState const& targetNFPState) {
        originalNFPState.reset();

        queue<NFPState> q;
        NFPStateSet set;
        q.push(originalNFPState);
        if (underExperiment) {
            ++nodeCountTemp;
        }
        while (!q.empty()) {
            if (q.front() == targetNFPState) {
                if (printPath) {
                    q.front().printPath();
                }
                return q.front().depth;
            }
            set.visit(q.front());
            while (q.front().hasNextAction()) {
                NFPState nextNFPState(q.front().genNextNFPState());
                if (!set.visited(nextNFPState)) {
                    q.emplace(nextNFPState);
                    if (underExperiment) {
                        ++nodeCountTemp;
                    }
                }
            }
            q.pop();
        }

        return -1;
    }

    // 深度有限搜索
    int NFPAlgorithm::DLS(NFPState& originalNFPState, NFPState const& targetNFPState, int const& depthLimit) {
        originalNFPState.reset();

        stack<NFPState> s;
        NFPStateSet set;
        s.push(originalNFPState);
        if (underExperiment) {
            ++nodeCountTemp;
        }
        while (!s.empty()) {
            if (s.top() == targetNFPState) {
                if (printPath) {
                    s.top().printPath();
                }
                return s.top().depth;
            }
            set.visit(s.top());
            bool flag = true;
            if (s.top().depth < depthLimit) {
                while (s.top().hasNextAction()) {
                    NFPState nextNFPState(s.top().genNextNFPState());
                    if (!set.visited(nextNFPState)) {
                        s.emplace(nextNFPState);
                        if (underExperiment) {
                            ++nodeCountTemp;
                        }
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                set.remove(s.top());
                s.pop();
            }
        }

        return -1;
    }

    // 启发函数1：错位数码数
    int NFPAlgorithm::incorrectCount(NFPState const& originalNFPState, NFPState const& targetNFPState) {
        int incorrectCount = 0;
        static NFPPosition pos[2][NFPState::size];

        for (int r = 0; r < NFPState::rows; ++r) {
            for (int c = 0; c < NFPState::cols; ++c) {
                pos[0][originalNFPState.at(r, c)] = { r, c };
                pos[1][targetNFPState.at(r, c)] = { r, c };
            }
        }

        for (int i = 1; i < NFPState::size; ++i) {
            if (pos[0][i] != pos[1][i]) {
                ++incorrectCount;
            }
        }

        return incorrectCount + originalNFPState.depth;
    }

    // 启发函数2：曼哈顿距离
    int NFPAlgorithm::manhattanDistance(NFPState const& originalNFPState, NFPState const& targetNFPState) {
        int manhattanDis = 0;
        static NFPPosition pos[2][NFPState::size];

        for (int r = 0, i = 0; r < NFPState::rows; ++r) {
            for (int c = 0; c < NFPState::cols; ++c, i += 4) {
                pos[0][originalNFPState.at(r, c)] = { r, c };
                pos[1][targetNFPState.at(r, c)] = { r, c };
            }
        }

        for (int i = 1; i < NFPState::size; ++i) {
            manhattanDis += abs(pos[0][i].r - pos[1][i].r) + abs(pos[0][i].c - pos[1][i].c);
        }

        return manhattanDis + originalNFPState.depth;
    }

    // 启发式搜索
    int NFPAlgorithm::AStar(NFPState& originalNFPState, NFPState const& targetNFPState, function<int(NFPState const&, NFPState const&)> const& heuristicFunc) {
        originalNFPState.reset();

        priority_queue<pair<int, NFPState>, vector<pair<int, NFPState>>, greater<pair<int, NFPState>>> pq;
        NFPStateSet set;
        pq.push({ heuristicFunc(originalNFPState, targetNFPState), originalNFPState });
        if (underExperiment) {
            ++nodeCountTemp;
        }
        while (!pq.empty()) {
            NFPState curNFPState = pq.top().second;
            if (curNFPState == targetNFPState) {
                if (printPath) {
                    curNFPState.printPath();
                }
                return curNFPState.depth;
            }
            set.visit(curNFPState);
            pq.pop();
            while (curNFPState.hasNextAction()) {
                NFPState nextNFPState(curNFPState.genNextNFPState());
                if (!set.visited(nextNFPState)) {
                    pq.emplace(heuristicFunc(nextNFPState, targetNFPState), nextNFPState);
                    if (underExperiment) {
                        ++nodeCountTemp;
                    }
                }
            }

        }

        return -1;
    }

    // 交互模式
    void NFPAlgorithm::interactiveMode() {
        int depth = -1;
        while (true) {
            cout << "生成一个最优解深度为d（0 <= d <= " << NFPState::maxDepth << ")的初始状态，请输入d（输入-1则退出程序）：";
            cin >> depth;
            while (depth < 0 || depth > NFPState::maxDepth) {
                if (depth == -1) {
                    return;
                }
                cout << "输入错误，请重新输入：";
                cin >> depth;
            }

            NFPState originalNFPState = NFPState::genRandomNFPState(depth);
            cout << "初始状态为：\n" << originalNFPState << endl;
            int res[6]{ -2, -2, -2, -2, -2, -2 };

            cout << "\nBFS_Demo路径输出：\n";
            res[0] = NFPAlgorithm::BFS_Demo(originalNFPState, NFPState::_targetNFPState);

            cout << "\nBFS路径输出：\n";
            res[1] = NFPAlgorithm::BFS(originalNFPState, NFPState::_targetNFPState);

            cout << "\nDLS路径输出：\n";
            res[2] = NFPAlgorithm::DLS(originalNFPState, NFPState::_targetNFPState);

            cout << "\nA*_1路径输出：\n";
            res[3] = NFPAlgorithm::AStar(originalNFPState, NFPState::_targetNFPState, NFPAlgorithm::incorrectCount);

            cout << "\nA*_2路径输出：\n";
            res[4] = NFPAlgorithm::AStar(originalNFPState, NFPState::_targetNFPState, NFPAlgorithm::manhattanDistance);

            cout << "\nIDS路径输出：\n";
            int dep = 0;
            while (dep <= NFPState::maxDepth &&
                !NFPAlgorithm::IDS(originalNFPState, NFPState::_targetNFPState, originalNFPState.zeroPos, dep, res[5])) {
                ++dep;
            }

            cout << "\n\t\tDemo\tBFS\tDLS\tA*_1\tA*_2\tIDS\n输出步数\t";
            for (auto const& ans : res) {
                cout << ans << '\t';
            }
            cout << "\n是否正确\t";
            bool pass = true, IDSPass = true;
            for (int i = 0; i < 5; ++i) {
                if (res[i] != -1 && res[i] >= depth) {
                    cout << "Y\t";
                } else {
                    cout << "N\t";
                    pass = false;
                }
            }
            if (res[5] != depth) {
                cout << "N\t";
                IDSPass = false;
            } else {
                cout << "Y\t";
            }
            if (pass) {
                cout << "Pass";
                if (!IDSPass) {
                    cout << " without IDS";
                }
            } else {
                cout << "Wrong";
            }
            cout << "\n是否最优\t";
            for (auto const& ans : res) {
                if (ans == depth) {
                    cout << "Y\t";
                } else {
                    cout << "N\t";
                }
            }
            if (pass) {
                cout << "\n\t\t本次测试输出正确!\n";
            } else {
                cout << "\n\t\t本次测试输出错误!\n";
            }
            cout << endl << endl;
        }
    }

    // 正确性测试函数
    void NFPAlgorithm::testSearch() {
        bool pass = true;
        int res = -1;
        // 依次遍历深度为1~10的状态用于测试BFS
        for (int d = 1; d <= 10; ++d) {
            int end = NFPState::depthIndexs[d] - 1;
            for (int i = NFPState::depthIndexs[d - 1]; i < end; ++i) {
                res = NFPAlgorithm::BFS(NFPState::allNFPStates[i], NFPState::_targetNFPState);
                if (res != d) {
                    cout << NFPState::allNFPStates[i] << '\n';
                    cout << d << " but " << res << '\n';
                    pass = false;
                    return;
                }
            }
            cout << d << "p ";
        }
        if (pass) {
            cout << "\nBFS\tPass\n\n";
        } else {
            cout << "\nBFS\tWrong\n\n";
            return;
        }

        // 依次遍历深度为1~8的状态用于测试DLS
        for (int d = 1; d <= 8; ++d) {
            int end = NFPState::depthIndexs[d] - 1;
            for (int i = NFPState::depthIndexs[d - 1]; i < end; ++i) {
                res = NFPAlgorithm::DLS(NFPState::allNFPStates[i], NFPState::_targetNFPState);
                if (res < 0) {
                    cout << NFPState::allNFPStates[i] << '\n';
                    cout << d << " but " << res << '\n';
                    pass = false;
                    return;
                }
            }
            cout << d << "p ";
        }
        if (pass) {
            cout << "\nDLS\tPass\n\n";
        } else {
            cout << "\nDLS\tWrong\n\n";
        }

        // 依次遍历深度为5~14的状态用于测试AStar1
        for (int d = 5; d <= 14; ++d) {
            int end = NFPState::depthIndexs[d] - 1;
            for (int i = NFPState::depthIndexs[d - 1]; i < end; ++i) {
                res = NFPAlgorithm::AStar(NFPState::allNFPStates[i], NFPState::_targetNFPState, NFPAlgorithm::incorrectCount);
                if (res != d) {
                    cout << NFPState::allNFPStates[i] << '\n';
                    cout << d << " but " << res << '\n';
                    pass = false;
                    return;
                }
            }
            cout << d << "p ";
        }
        if (pass) {
            cout << "\nA*_1\tPass\n\n";
        } else {
            cout << "\nA*_1\tWrong\n\n";
            return;
        }

        // 依次遍历深度为8~16的状态用于测试AStar2
        for (int d = 8; d <= 16; ++d) {
            int end = NFPState::depthIndexs[d] - 1;
            for (int i = NFPState::depthIndexs[d - 1]; i < end; ++i) {
                res = NFPAlgorithm::AStar(NFPState::allNFPStates[i], NFPState::_targetNFPState, NFPAlgorithm::manhattanDistance);
                if (res != d) {
                    cout << NFPState::allNFPStates[i] << '\n';
                    cout << d << " but " << res << '\n';
                    pass = false;
                    return;
                }
            }
            cout << d << "p ";
        }
        if (pass) {
            cout << "\nA*_2\tPass\n\n";
        } else {
            cout << "\nA*_2\tWrong\n\n";
            return;
        }

        // 依次遍历深度为8~13的状态用于测试IDS
        for (int d = 8; d <= 13; ++d) {
            int end = NFPState::depthIndexs[d] - 1;
            for (int i = NFPState::depthIndexs[d - 1]; i < end; ++i) {
                int dep = d;
                res = -1;
                while (dep <= NFPState::maxDepth && !NFPAlgorithm::IDS(NFPState::allNFPStates[i], NFPState::_targetNFPState, NFPState::allNFPStates[i].zeroPos, dep, res)) {
                    ++dep;
                }
                if (res != d) {
                    cout << NFPState::allNFPStates[i] << '\n';
                    cout << d << " but " << res << '\n';
                    pass = false;
                    return;
                }
            }
            cout << d << "p ";
        }
        if (pass) {
            cout << "\nIDS\tPass\n\n";
        } else {
            cout << "\nIDS\tWrong\n\n";
            return;
        }

        cout << "All\tPass";
    }

    auto test() -> void {
        NFPState::init({ { 0, 1, 2 },
                         { 3, 4, 5 },
                         { 6, 7, 8 } });

        // 你可以修改这个以进入交互模式或者测试模式
        NFPAlgorithm::printPath = true;

        if (NFPAlgorithm::printPath) {
            cout << "交互模式\n";
            NFPAlgorithm::interactiveMode();
        } else {
            cout << "测试模式\n";
            NFPAlgorithm::statisticalExperiment();
            NFPAlgorithm::testSearch();
        }
    }
}
