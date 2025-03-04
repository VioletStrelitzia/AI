#include "NFPAlgorithm.h"

namespace yuki::atri::nfp {
    bool Algorithm::printPath = true;
    i32 Algorithm::nodeCountTemp = 0;
    bool Algorithm::underExperiment = false;

    void Algorithm::statisticalExperiment() {
        underExperiment = true;
        clock_t t;
        i32 sampleNum = 100;
        i32 timeCosts[5][State::maxDepth / 2] = { 0 };
        i32 nodeCounts[5][State::maxDepth / 2] = { 0 };
        i32 ans;
        
        for (i32 d = 2; d <= State::maxDepth; d += 2) {
            i32 j = (d - 2) / 2;
            for (i32 i = 0; i < sampleNum; ++i) {
                State originalNFPState(State::genRandomNFPState(d));

                nodeCountTemp = 0;
                t = clock();
                BFS(originalNFPState, State::_targetNFPState);
                t = clock() - t;
                timeCosts[0][j] += t;
                nodeCounts[0][j] += nodeCountTemp;

                nodeCountTemp = 0;
                t = clock();
                if (d < 8) {
                    DLS(originalNFPState, State::_targetNFPState);
                }
                t = clock() - t;
                timeCosts[1][j] += t;
                nodeCounts[1][j] += nodeCountTemp;

                nodeCountTemp = 0;
                t = clock();
                AStar(originalNFPState, State::_targetNFPState, incorrectCount);
                t = clock() - t;
                timeCosts[2][j] += t;
                nodeCounts[2][j] += nodeCountTemp;

                nodeCountTemp = 0;
                t = clock();
                AStar(originalNFPState, State::_targetNFPState, manhattanDistance);
                t = clock() - t;
                timeCosts[3][j] += t;
                nodeCounts[3][j] += nodeCountTemp;

                nodeCountTemp = 0;
                t = clock();
                IDS(originalNFPState, State::_targetNFPState, originalNFPState.zeroPos, d, ans);
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
        for (i32 d = 2; d <= State::maxDepth; d += 2) {
            i32 j = (d - 2) / 2;
            cout << std::setw(10) << std::left << d;
            for (i32 i = 0; i < 5; ++i) {
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
        for (i32 d = 2; d <= State::maxDepth; d += 2) {
            i32 j = (d - 2) / 2;
            cout << std::setw(10) << std::left << d;
            for (i32 i = 0; i < 5; ++i) {
                cout << std::setw(10) << std::left << (double)timeCosts[i][j] / sampleNum;
            }
            cout << endl;
        }
        cout << endl;
        underExperiment = false;
    }
    
    auto Algorithm::IDS(State& originalNFPState, State const& targetNFPState, Vector2 const& preZeroPos, i32 const& depthLimit, i32& ans) -> bool {
        if (originalNFPState == targetNFPState) {
            ans = originalNFPState.depth;
            return true;
        }

        // 当前步数（深度） + 估价 > 深度限制，立即回溯 
        if (manhattanDistance(originalNFPState, targetNFPState) > depthLimit) {
            return false;
        }

        // 枚举可以执行的action，即每次向上、下、左、右移动
        for (i32 actionId = 0; actionId < State::actionsNum; ++actionId) {
            Vector2 zeroPos = originalNFPState.zeroPos; // 0 的位置
            Vector2 swapPos = zeroPos + State::actions[actionId]; // 要交换的数 的位置

            // 优化：如果 0 将要回到回到上一次的位置，会判断直接跳过这次 action 而不往下搜索，避免提前回溯重复搜索
            // 以及越界判断
            if (preZeroPos == swapPos ||
                swapPos.r < 0 || swapPos.r >= State::rows ||
                swapPos.c < 0 || swapPos.c >= State::cols) {
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
                    cout << "第" << originalNFPState.depth << "步:" << State::actionInfo[actionId] << endl;// << originalNFPState << endl << endl;
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

    i32 Algorithm::BFS_Demo(State& originalNFPState, State const& targetNFPState) {
        originalNFPState.reset();
        queue<State> q;
        StateSet set;
        q.push(originalNFPState);
        if (underExperiment) {
            ++nodeCountTemp;
        }
        while (!q.empty()) {
            State curNFPState = q.front();
            if (curNFPState == targetNFPState) {
                if (printPath) {
                    curNFPState.printPath();
                }
                return curNFPState.depth;
            }
            set.visit(curNFPState);
            while (curNFPState.hasNextAction()) {
                State nextNFPState(curNFPState.genNextNFPState());
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

    i32 Algorithm::BFS(State& originalNFPState, State const& targetNFPState) {
        originalNFPState.reset();

        queue<State> q;
        StateSet set;
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
                State nextNFPState(q.front().genNextNFPState());
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

    i32 Algorithm::DLS(State& originalNFPState, State const& targetNFPState, i32 const& depthLimit) {
        originalNFPState.reset();

        stack<State> s;
        StateSet set;
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
                    State nextNFPState(s.top().genNextNFPState());
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

    i32 Algorithm::incorrectCount(State const& originalNFPState, State const& targetNFPState) {
        i32 incorrectCount = 0;
        static Vector2 pos[2][State::size];

        for (i32 r = 0; r < State::rows; ++r) {
            for (i32 c = 0; c < State::cols; ++c) {
                pos[0][originalNFPState.at(r, c)] = { r, c };
                pos[1][targetNFPState.at(r, c)] = { r, c };
            }
        }

        for (i32 i = 1; i < State::size; ++i) {
            if (pos[0][i] != pos[1][i]) {
                ++incorrectCount;
            }
        }

        return incorrectCount + originalNFPState.depth;
    }

    i32 Algorithm::manhattanDistance(State const& originalNFPState, State const& targetNFPState) {
        i32 manhattanDis = 0;
        static Vector2 pos[2][State::size];

        for (i32 r = 0, i = 0; r < State::rows; ++r) {
            for (i32 c = 0; c < State::cols; ++c, i += 4) {
                pos[0][originalNFPState.at(r, c)] = { r, c };
                pos[1][targetNFPState.at(r, c)] = { r, c };
            }
        }

        for (i32 i = 1; i < State::size; ++i) {
            manhattanDis += abs(pos[0][i].r - pos[1][i].r) + abs(pos[0][i].c - pos[1][i].c);
        }

        return manhattanDis + originalNFPState.depth;
    }

    i32 Algorithm::AStar(State& originalNFPState, State const& targetNFPState, function<i32(State const&, State const&)> const& heuristicFunc) {
        originalNFPState.reset();

        priority_queue<pair<i32, State>, vector<pair<i32, State>>, std::greater<pair<i32, State>>> pq;
        StateSet set;
        pq.push({ heuristicFunc(originalNFPState, targetNFPState), originalNFPState });
        if (underExperiment) {
            ++nodeCountTemp;
        }
        while (!pq.empty()) {
            State curNFPState = pq.top().second;
            if (curNFPState == targetNFPState) {
                if (printPath) {
                    curNFPState.printPath();
                }
                return curNFPState.depth;
            }
            set.visit(curNFPState);
            pq.pop();
            while (curNFPState.hasNextAction()) {
                State nextNFPState(curNFPState.genNextNFPState());
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

    void Algorithm::interactiveMode() {
        i32 depth = -1;
        while (true) {
            cout << "生成一个最优解深度为d（0 <= d <= " << State::maxDepth << ")的初始状态，请输入d（输入-1则退出程序）：";
            cin >> depth;
            while (depth < 0 || depth > State::maxDepth) {
                if (depth == -1) {
                    return;
                }
                cout << "输入错误，请重新输入：";
                cin >> depth;
            }

            State originalNFPState = State::genRandomNFPState(depth);
            cout << "初始状态为：\n" << originalNFPState << endl;
            i32 res[6]{ -2, -2, -2, -2, -2, -2 };

            cout << "\nBFS_Demo路径输出：\n";
            res[0] = Algorithm::BFS_Demo(originalNFPState, State::_targetNFPState);

            cout << "\nBFS路径输出：\n";
            res[1] = Algorithm::BFS(originalNFPState, State::_targetNFPState);

            cout << "\nDLS路径输出：\n";
            res[2] = Algorithm::DLS(originalNFPState, State::_targetNFPState);

            cout << "\nA*_1路径输出：\n";
            res[3] = Algorithm::AStar(originalNFPState, State::_targetNFPState, Algorithm::incorrectCount);

            cout << "\nA*_2路径输出：\n";
            res[4] = Algorithm::AStar(originalNFPState, State::_targetNFPState, Algorithm::manhattanDistance);

            cout << "\nIDS路径输出：\n";
            i32 dep = 0;
            while (dep <= State::maxDepth &&
                !Algorithm::IDS(originalNFPState, State::_targetNFPState, originalNFPState.zeroPos, dep, res[5])) {
                ++dep;
            }

            cout << "\n\t\tDemo\tBFS\tDLS\tA*_1\tA*_2\tIDS\n输出步数\t";
            for (auto const& ans : res) {
                cout << ans << '\t';
            }
            cout << "\n是否正确\t";
            bool pass = true, IDSPass = true;
            for (i32 i = 0; i < 5; ++i) {
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

    void Algorithm::testSearch() {
        bool pass = true;
        i32 res = -1;
        // 依次遍历深度为1~10的状态用于测试BFS
        for (i32 d = 1; d <= 10; ++d) {
            i32 end = State::depthIndexs[d] - 1;
            for (i32 i = State::depthIndexs[d - 1]; i < end; ++i) {
                res = Algorithm::BFS(State::allNFPStates[i], State::_targetNFPState);
                if (res != d) {
                    cout << State::allNFPStates[i] << '\n';
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
        for (i32 d = 1; d <= 8; ++d) {
            i32 end = State::depthIndexs[d] - 1;
            for (i32 i = State::depthIndexs[d - 1]; i < end; ++i) {
                res = Algorithm::DLS(State::allNFPStates[i], State::_targetNFPState);
                if (res < 0) {
                    cout << State::allNFPStates[i] << '\n';
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
        for (i32 d = 5; d <= 14; ++d) {
            i32 end = State::depthIndexs[d] - 1;
            for (i32 i = State::depthIndexs[d - 1]; i < end; ++i) {
                res = Algorithm::AStar(State::allNFPStates[i], State::_targetNFPState, Algorithm::incorrectCount);
                if (res != d) {
                    cout << State::allNFPStates[i] << '\n';
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
        for (i32 d = 8; d <= 16; ++d) {
            i32 end = State::depthIndexs[d] - 1;
            for (i32 i = State::depthIndexs[d - 1]; i < end; ++i) {
                res = Algorithm::AStar(State::allNFPStates[i], State::_targetNFPState, Algorithm::manhattanDistance);
                if (res != d) {
                    cout << State::allNFPStates[i] << '\n';
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
        for (i32 d = 8; d <= 13; ++d) {
            i32 end = State::depthIndexs[d] - 1;
            for (i32 i = State::depthIndexs[d - 1]; i < end; ++i) {
                i32 dep = d;
                res = -1;
                while (dep <= State::maxDepth && !Algorithm::IDS(State::allNFPStates[i], State::_targetNFPState, State::allNFPStates[i].zeroPos, dep, res)) {
                    ++dep;
                }
                if (res != d) {
                    cout << State::allNFPStates[i] << '\n';
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
        State::init({ { 0, 1, 2 },
                         { 3, 4, 5 },
                         { 6, 7, 8 } });

        // 你可以修改这个以进入交互模式或者测试模式
        Algorithm::printPath = true;

        if (Algorithm::printPath) {
            cout << "交互模式\n";
            Algorithm::interactiveMode();
        } else {
            cout << "测试模式\n";
            Algorithm::statisticalExperiment();
            Algorithm::testSearch();
        }
    }
}
