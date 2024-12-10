#include "NQueen.h"

namespace yuki::atri::csp {
    bool nQueenBinaryConstraint(pair<Vector2, Vector2> const& scope, CSP<Vector2> const& csp) {
        return scope.first.r != scope.second.r && // scope.first.c != scope.second.c &&
        abs(scope.first.r - scope.second.r) != abs(scope.first.c - scope.second.c);
    }

    void testBacktrackingSearch(i32 const& maxN) {
        for (i32 n = 1; n <= maxN; ++n) {
            // 构造变量集合 X
            vector<Queen> X;
            for (i32 c = 0; c < n; ++c) {
                X.emplace_back(Queen());
                for (i32 r = 0; r < n; ++r) {
                    X[c].domain.emplace_back(r, c);
                }
            }

            // 用变量集合 X 初始化 csp 问题
            CSP<Vector2> csp(X);

            // 向变量之间添加二元约束
            for (i32 c1 = 0; c1 < n; ++c1) {
                for (i32 c2 = 0; c2 < n; ++c2) {
                    if (c2 == c1) continue;
                    csp.addBinaryConstraint(c1, c2, nQueenBinaryConstraint);
                }
            }

            time_t t = clock();
            vector<Queen> assignment = csp.backtrackingSearch();
            t = clock() - t;

            if (assignment.empty()) {
                cout << "无效答案...\n";
            } else {
                vector<vector<bool>> grid;
                for (i32 i = 0; i < n; ++i) {
                    grid.push_back(vector<bool>(n));
                    for (i32 j = 0; j < n; ++j) {
                        grid[i][j] = false;
                    }
                }

                for (i32 i = 0; i < n; ++i) {
                    if (assignment[i].value.r > -1 && assignment[i].value.r < n &&
                        assignment[i].value.c > -1 && assignment[i].value.c < n) {
                        grid[assignment[i].value.r][assignment[i].value.c] = true;
                    }
                }

                cout << "n = " << n << ", solution:" << endl;
                cout << "cost time " << (double)(t) / CLOCKS_PER_SEC << endl; 
                for (i32 i = 0; i < n; ++i) {
                    for (i32 j = 0; j < n; ++j) {
                        cout << grid[i][j] << "  ";
                    }
                    cout << endl;
                }
            }
        }
    }

    void testMinConflict(i32 const& n, i32 const& end) {
        f64 count = 0;
        vector<Queen> X;
        for (i32 c = 0; c < n; ++c) {
            X.emplace_back(Queen());
            for (i32 r = 0; r < n; ++r) {
                X[c].domain.emplace_back(r, c);
            }
        }
        CSP<Vector2> csp(X);
        for (i32 c1 = 0; c1 < n; ++c1) {
            for (i32 c2 = 0; c2 < n; ++c2) {
                if (c2 == c1) continue;
                csp.addBinaryConstraint(c1, c2, nQueenBinaryConstraint);
            }
        }

        for (i32 k = 0; k < end; ++k) {
            csp.variables = X;
            vector<Queen> assignment = csp.minConflict();

            if (assignment.empty()) {
                cout << k + 1 << " N\n";
                ++count; 
                continue;
            } else {
                //cout << k + 1 << " Y\n";
            }
        }
        cout << "ok rate: " << 1 - count / end << endl;
    }

}