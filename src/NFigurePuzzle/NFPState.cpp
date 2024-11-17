#include "NFPState.h"

namespace yuki::atri::nfp {
    usize State::mask[State::rows][State::cols];
    Position2 const State::actions[4] = { { -1, 0 }, { 1 , 0 }, { 0, -1 }, { 0, 1 } };
    string const State::actionInfo[State::actionsNum] = { "向上移动", "向下移动", "向左移动", "向右移动" };
    State State::_targetNFPState(0, Position2{ 0, 0 });

    vector<State> State::allNFPStates;
    int State::depthIndexs[maxDepth + 1];
    string const State::precisionFilename = "../../resources/precision.ini";
    random_device State::rd;
    mt19937 State::gen(rd());

    void State::init(State const& originalNFPState) {
        _targetNFPState = originalNFPState;
        _targetNFPState.depth = 0;
        _targetNFPState.updateNextActions();
        _targetNFPState.prevActions.clear();

        ifstream inFile;
        inFile.open(precisionFilename, std::ios::binary);
        if (inFile.is_open()) {
            int buffer0[3] = { 0 };
            inFile.read(reinterpret_cast<char*>(&buffer0), sizeof buffer0);
            if (buffer0[0] != rows || buffer0[1] != cols || buffer0[2] != maxDepth) {
                cout << "generating precision...\n";
                genPrecision(originalNFPState);
                cout << "generation completed!\n";
                inFile.close();
                return;
            }
            cout << "reading precision...\n";
            inFile.read(reinterpret_cast<char*>(*mask), sizeof(usize) * rows * cols);

            usize buffer1 = 1;
            Position2 buffer2{ 0, 0 };
            allNFPStates.clear();

            while (true) {
                inFile.read(reinterpret_cast<char*>(&buffer1), sizeof buffer1);
                inFile.read(reinterpret_cast<char*>(&buffer2), sizeof buffer2);
                
                if (buffer1 == 0) {
                    break;
                }
                allNFPStates.emplace_back(buffer1, buffer2);
            }

            inFile.read(reinterpret_cast<char*>(depthIndexs), sizeof depthIndexs);
            cout << "read completed!\n";
            //for (int i = 0; i <= maxDepth; ++i) {
            //    cout << depthIndexs[i] << endl;
            //}
            cout << endl;
        }
        inFile.close();
    }

    int State::genRandomDepth(int const& min, int const& max) const {
        uniform_int_distribution<int> distrib(min, max);
        return distrib(gen);
    }

    State State::genRandomNFPState(int const& depth) {
        if (depth <= 0) {
            return _targetNFPState;
        }
        uniform_int_distribution<int> distrib(depthIndexs[depth - 1], depthIndexs[depth] - 1);
        return allNFPStates[distrib(gen)];
    }

    State::State(usize const& data, Position2 const& pZero, int const& depth) :
        data(data), zeroPos(pZero), depth(depth) {
        updateNextActions();
    }

    State::State(initializer_list<initializer_list<usize>> const& listList) :
        data(0), depth(0) {
        int offset = 0, r = 0, c = 0;
        for (auto const& list : listList) {
            for (usize const& x : list) {
                if (x == 0) {
                    zeroPos = { r, c };
                }
                data += x << offset;
                offset += 4;
                ++c;
            }
            ++r;
        }
        updateNextActions();
    }

    State::State(State const& other) :
        data(other.data),
        zeroPos(other.zeroPos),
        depth(other.depth),
        nextActions(other.nextActions),
        prevActions(other.prevActions) {}

    State::State(State&& other) noexcept :
        data(move(other.data)),
        zeroPos(move(other.zeroPos)),
        depth(move(other.depth)),
        nextActions(move(other.nextActions)),
        prevActions(move(other.prevActions)) {}

    State& State::operator=(State const& other) {
        zeroPos = other.zeroPos;
        data = other.data;
        depth = other.depth;
        nextActions = other.nextActions;
        prevActions = other.prevActions;
        return *this;
    }

    usize State::at(int const& row, int const& col) const {
        return (data & mask[row][col]) >> ((row * rows + col) << 2);
    }

    bool State::operator<(State const& other) const {
        return depth < other.depth;
    }

    bool State::operator==(State const& other) const {
        return data == other.data;
    }

    bool State::operator!=(State const& other) const {
        return data != other.data;
    }

    bool State::hasNextAction() const {
        return !nextActions.empty();
    }

    void State::executeAction(Action const* const& action) {
        //prevActions.push_back(action);

        zeroMoveTo(zeroPos + *action);

        ++depth;

        // 这里默认不会把上个动作的反动作加入后继可行动作，比如上一个动作是是向下走，更新的后继可行动作就不会考虑向上走
        // 如果需要加入上个动作的反动作，则将输入参数 action 去掉
        updateNextActions(action);
    }

    void State::reset() {
        depth = 0;
        updateNextActions();
        prevActions.clear();
    }

    State State::genNextNFPState() {
        State nextNFPState(*this);
        if (hasNextAction()) { // 后继动作序列不为空
            // 取出一个可行动作
            Action const*& action = nextActions.back();
            // 执行动作
            nextNFPState.executeAction(action);
            // 记录动作
            nextNFPState.prevActions.push_back(action);
            // 将执行过的动作移除
            nextActions.pop_back();
        }
        return nextNFPState;
    }

    void State::zeroMoveTo(Position2 const& swapPos) {
        // 单线程环境下使用静态变量减少生成临时变量反复申请内存
        // 多线程环境下就不要用静态变量以防数据竞争
        static usize tmp1, tmp2;
        static unsigned idx1, idx2, offset;

        tmp1 = data & mask[zeroPos.r][zeroPos.c];
        tmp2 = data & mask[swapPos.r][swapPos.c];
        data -= tmp1;
        data -= tmp2;
        idx1 = zeroPos.r * rows + zeroPos.c;
        idx2 = swapPos.r * rows + swapPos.c;
        if (idx1 > idx2) {
            offset = (idx1 - idx2) << 2;
            tmp1 >>= offset;
            tmp2 <<= offset;
        }
        else {
            offset = (idx2 - idx1) << 2;
            tmp1 <<= offset;
            tmp2 >>= offset;
        }
        data ^= tmp1;
        data ^= tmp2;

        zeroPos = swapPos;
    }

    void State::updateNextActions(Action const* const& lastAction) {
        nextActions.clear();
        if (zeroPos.r > 0        && lastAction != actions + 1) nextActions.push_back(actions);
        if (zeroPos.r < rows - 1 && lastAction != actions)     nextActions.push_back(actions + 1);
        if (zeroPos.c > 0        && lastAction != actions + 3) nextActions.push_back(actions + 2);
        if (zeroPos.c < cols - 1 && lastAction != actions + 2) nextActions.push_back(actions + 3);
    }

    State::Action const* State::genRandomAction() const {
        if (nextActions.empty()) {
            return nullptr;
        }
        uniform_int_distribution<int> distrib(0, static_cast<int>(nextActions.size()) - 1);
        return nextActions[distrib(gen)];
    }

    void State::printPath() const {
        auto len = prevActions.size();
        for (int i = 0; i < len; ++i) {
            cout << "第";
            if (i < 9) {
                cout << ' ';
            }
            cout << i + 1 << "步：" << actionInfo[prevActions[i] - actions] << endl;
        }
        if (len == 0) {
            cout << "无需移动\n";
        }
        cout << *this << endl;
    }

    void State::genPrecision(State const& originalNFPState) {
        ofstream outFile(precisionFilename, std::ios::binary);
        if (outFile.good()) {
            outFile.write(reinterpret_cast<char const*>(&rows), sizeof rows);
            outFile.write(reinterpret_cast<char const*>(&cols), sizeof cols);
            outFile.write(reinterpret_cast<char const*>(&maxDepth), sizeof maxDepth);

            usize m = 0b1111;
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    mask[r][c] = m;
                    outFile.write(reinterpret_cast<char*>(& m), sizeof m);
                    m <<= 4;
                }
            }

            allNFPStates.clear();

            allNFPStates.push_back(_targetNFPState);
            outFile.write(reinterpret_cast<char*>(&_targetNFPState), 16);
            depthIndexs[0] = 1;
            set<usize> s;

            bool flag = false;
            int index = 0;
            while (index < allNFPStates.size()) {
                s.insert(allNFPStates[index].data);

                for (Action const* const& action : allNFPStates[index].nextActions) {
                    State nextNFPState(allNFPStates[index]);
                    nextNFPState.executeAction(action);
                    if (nextNFPState.depth > maxDepth) {
                        flag = true;
                        break;
                    }
                    if (s.find(nextNFPState.data) == s.end()) {
                        outFile.write(reinterpret_cast<char*>(&nextNFPState), 16);
                        allNFPStates.emplace_back(nextNFPState);
                        depthIndexs[nextNFPState.depth] = static_cast<int>(allNFPStates.size());
                    }
                }

                if (flag) {
                    break;
                }
                ++index;
            }
        }
        unsigned zero[4] = { 0 };
        outFile.write(reinterpret_cast<char*>(zero), 16);
        outFile.write(reinterpret_cast<char*>(&depthIndexs), sizeof depthIndexs);
        for (int i = 0; i <= maxDepth; ++i) {
            cout << depthIndexs[i] << endl;
        }
        cout << "allNFPStates.size() = " << allNFPStates.size() << endl;

        outFile.close();
    }

    ostream& operator<<(ostream& os, State const& NFPState) {
        for (int r = 0, i = 0; r < State::rows; ++r) {
            cout << "    ";
            for (int c = 0; c < State::cols; ++c, i += 4) {
                cout << ((NFPState.data & State::mask[r][c]) >> i) << ' ';
            }
            cout << '\n';
        }
        cout << "data = " << NFPState.data;
        return os;
    }
}