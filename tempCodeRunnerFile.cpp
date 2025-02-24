#include <gtest/gtest.h>
#include <iostream>
#include <vector>

// 导入待测函数
void print() {
    std::vector<int> fitnesses = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = 55;

    for (int i = 0; i < fitnesses.size(); ++i) {
        for (int j = 0; j < 5 && i < fitnesses.size(); ++j, ++i) {
            std::cout << std::setw(5) << fitnesses[i] <<'';
        }
        std::cout << std::endl;
    }
    std::cout << sum << std::endl;
}

TEST(PrintTest, Basic) {
    // 模拟 fitnesses 数据
    std::vector<int> fitnesses = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = 55;

    // 调用待测函数
    print();

    // 可以根据输出结果进行进一步的验证
}

TEST(PrintTest, EmptyFitnesses) {
    std::vector<int> fitnesses;
    int sum = 0;

    // 调用待测函数
    print();

    // 验证输出是否符合预期
}

TEST(PrintTest, SmallFitnesses) {
    std::vector<int> fitnesses = {1, 2, 3};
    int sum = 6;

    // 调用待测函数
    print();

    // 验证输出是否符合预期
}
