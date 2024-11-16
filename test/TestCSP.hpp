#pragma once
#include "CSP.hpp"
#include "Variable.hpp"

namespace yuki::test {
    using yuki::csp::Variable;
    using yuki::csp::CSP;

    struct Position {
        int r, c;
    };

    using Queen = Variable<Position>;

    bool func(pair<Position, Position> const& scope, CSP<Position> const& csp) {
        return scope.first.r != scope.second.r && // scope.first.c != scope.second.c &&
        abs(scope.first.r - scope.second.r) != abs(scope.first.c - scope.second.c);
    }

    void demo2() {
        f32 count = 0, n = 24;
        vector<Queen> X;
        for (i32 c = 0; c < n; ++c) {
            X.emplace_back(Queen());
            for (i32 r = 0; r < n; ++r) {
                X[c].domain.emplace_back(r, c);
            }
        }
        CSP<Position> csp(X);
        for (i32 c1 = 0; c1 < n; ++c1) {
            for (i32 c2 = 0; c2 < n; ++c2) {
                if (c2 == c1) continue;
                csp.addBinaryConstraint(c1, c2, func);
            }
        }

        i32 end = 500;
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
        cout << "fail rate: " << count / end << endl;
    }

    void demo() {

        i32 k = 16;
        for (i32 n = 5; n <= k; ++n) {

            vector<Queen> X;
            for (i32 c = 0; c < n; ++c) {
                X.emplace_back(Queen());
                for (i32 r = 0; r < n; ++r) {
                    X[c].domain.emplace_back(r, c);
                }
            }
            CSP<Position> csp(X);

            for (i32 c1 = 0; c1 < n; ++c1) {
                for (i32 c2 = 0; c2 < n; ++c2) {
                    if (c2 == c1) continue;
                    csp.addBinaryConstraint(c1, c2, func);
                }
            }

            time_t t = clock();
            vector<Queen> assignment = csp.backtrackingSearch();
            t = clock() - t;

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
