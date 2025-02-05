#pragma once
#include "Ycore.h"

namespace yuki::atri::ga {

enum SelectionType {
    RANDOM = 0,
    RANK,
    ROULETTE_WHEEL,
    TOURNAMENT,
    ELITISM,
    DENSITY_BASED,
    BORDA_COUNT
};

enum CrossoverType {
    SINGLE_POINT = 0
};

/**
 * @brief 遗传算法框架
 * 
 * @tparam Gene 基因，染色体中的元素，编码中的元素
 */
template <typename Gene>
class GA {
public:

/// @brief 个体
/// @details 要处理的基本对象、结构，可行解
struct Individual {
    vector<Gene> chromosome;  ///< 染色体，个体的表现形式，可行解的编码
};

/// @brief 种群
/// @details 个体的集合，被选定的一组可行解
using Population = vector<Individual>;

struct FitnessInfo {
    f64 sum = 0.;
    vector<f64> fitnesses;

    auto print() -> void {
        for (i32 i = 0; i < fitnesses.size(); ++i) {
            for (i32 j = 0; j < 5 && i < fitnesses.size(); ++j, ++i) {
                cout << std::setw(5) << fitnesses[i] << ' ';
            }
            cout << endl;
        }
        cout << sum << endl;
    }
};

Population population;

function<f64(Individual const&)> fitnessFunc;

public:
    GA() = default;
    ~GA() = default;

    auto init(i32 const& popSize = 32, i32 const& chromosomeLen = 16) -> void {
        if constexpr (is_same_v<Gene, bool>) {
            for (i32 i = 0; i < popSize; ++i) {
                Individual temp;
                temp.chromosome.resize(chromosomeLen);
                for (i32 j = 0; j < chromosomeLen; ++j) {
                    temp.chromosome[j] = random::uniformInt(0, 1);
                }
                population.push_back(temp);
            }
        } else if constexpr (is_same_v<Gene, i32>) {

        } else if constexpr (is_same_v<Gene, f64>) {

        } else {

        }
    }

    auto fitness(Population const& pop) -> FitnessInfo {
        FitnessInfo fi;
        for (auto const& individual: population) {
            f64 fitness = fitnessFunc(individual);
            fi.fitnesses.push_back(fitness);
            fi.sum += fitness;
        }
        return fi;
    }

    template <SelectionType Type = SelectionType::RANDOM>
    auto select(i32 newPopSize = -1) -> Population {
        if (newPopSize = -1) {
            newPopSize = static_cast<i32>(population.size());
        }
        Population selectedPopulation(newPopSize);
        if constexpr (Type == SelectionType::RANDOM) {
            for (i32 i = 0; i < newPopSize; ++i) {
                //selectedPopulation[i] = random::choose<bool, FunctionReturnType::VALUE>(population);
            }
        } else if constexpr (Type == SelectionType::RANK) {
            FitnessInfo fi = fitness(population);
            for (i32 i = 0; i < newPopSize; ++i) {
                selectedPopulation[i] = population[random::chooseByWeights(fi.fitnesses, fi.sum)];
            }
        } else {

        }
        return selectedPopulation;
    }

    template <CrossoverType Type = SINGLE_POINT>
    auto crossover(Individual const& parent1, Individual const& parent2) -> pair<Individual, Individual> {
        pair<Individual, Individual> children;
        i32 len = static_cast<i32>(parent1.chromosome.size());
        children.first.chromosome.resize(len);
        children.second.chromosome.resize(len);
        if constexpr (Type == SINGLE_POINT) {
            i32 splitPoint = random::uniformInt(1, len);
            for (i32 i = 0; i < splitPoint; ++i) {
                children.first.chromosome[i] = parent1.chromosome[i];
            }
            for (i32 i = splitPoint; i < len; ++i) {
                children.second.chromosome[i] = parent1.chromosome[i];
            }
            for (i32 i = 0; i < splitPoint; ++i) {
                children.second.chromosome[i] = parent2.chromosome[i];
            }
            for (i32 i = splitPoint; i < len; ++i) {
                children.first.chromosome[i] = parent2.chromosome[i];
            }
        } else {

        }
        return children;
    }

    /**
     * @brief 染色体交叉互换产生后代
     * 
     */
    auto crossover(Population pop) -> Population {
        Population newPop;
        while (pop.size() > 1) {
            i32 size = static_cast<i32>(pop.size());
            swap(pop[random::uniformInt(0, size - 1)], pop[size - 1]);
            swap(pop[random::uniformInt(0, size - 2)], pop[size - 2]);
            auto children = crossover(pop[size - 1], pop[size - 2]);
            newPop.push_back(children.first);
            newPop.push_back(children.second);
            pop.pop_back();
            pop.pop_back();
        }
        return newPop;
    }

    /**
     * @brief 突变
     * 
     */
    auto mutation(Population& pop) -> void {
        for (Individual& individual: pop) {
            while (random::trigger(0.03)) {
                if constexpr (is_same_v<Gene, bool>) {
                    i32 idx = random::uniformInt(0, static_cast<i32>(individual.chromosome.size() - 1));
                    individual.chromosome[idx] = !individual.chromosome[idx];
                } else if constexpr (is_same_v<Gene, i32>) {

                } else if constexpr (is_same_v<Gene, f64>) {

                } else {
                    auto& x = random::choose(individual.chromosome);
                    x = !x;
                }
            }
        }
    }

    f64 getNum(Individual const& individual) {
        f64 x = 0., base = 1.;
        for (auto i: individual.chromosome) {
            if constexpr (is_same_v<Gene, bool>) {
                if (i) x += base;
                base /= 2.;
            } else {
                x += i * base;
                base /= 2.;
            }
        }
        return x;
    }

    auto solution(i32 const& t = 32) -> void {
        vector<pair<f64, f64>> record;
        init();
        cout << "i = " << 0 << endl;
        /*
        for (Individual const& i: population) {
            cout << std::setw(6) << getNum(i) << ' ';
            cout << i.chromosome << endl;
        }
        */
        FitnessInfo fi = fitness(population);
        fi.print();
        i32 idx = 0;
        for (i32 j = 1; j < fi.fitnesses.size(); ++j) {
            if (fi.fitnesses[j] > fi.fitnesses[idx]) {
                idx = j;
            }
        }
        cout << std::setw(5) << getNum(population[idx]) << "max " << fi.fitnesses[idx] << endl;
        record.push_back({ getNum(population[idx]), fi.fitnesses[idx] });

        for (i32 i = 0; i < t; ++i) {
            cout << "i = " << i + 1 << endl;
            population = crossover(select<SelectionType::RANK>());
            mutation(population);

            /*
            cout << endl;
            for (Individual const& i: population) {
                cout << std::setw(5) << getNum(i) << ' ';
                cout << i.chromosome << endl;
            }
            */
            fi = fitness(population);
            fi.print();
            idx = 0;
            for (i32 j = 1; j < fi.fitnesses.size(); ++j) {
                if (fi.fitnesses[j] > fi.fitnesses[idx]) {
                    idx = j;
                }
            }
            cout << std::setw(5) << getNum(population[idx]) << " max " << fi.fitnesses[idx] << endl;
            record.push_back({ getNum(population[idx]), fi.fitnesses[idx] });
        }

        for (size_t i = 0; i < record.size(); i++) {
            cout << std::setw(5) << record[i].first << ' ' << record[i].second << endl;
        }
        
    }

};

/**
 * @brief bool 类型特化的遗传算法框架
 * 
 * @details 用于解决寻找函数区间内的极值
 */
template <>
class GA<bool> {
public:

/// @brief 个体
/// @details 要处理的基本对象、结构，可行解
struct Individual {
    vector<bool> chromosome;  ///< 染色体，个体的表现形式，可行解的编码
};

/// @brief 种群
/// @details 个体的集合，被选定的一组可行解
using Population = vector<Individual>;

struct FitnessInfo {
    f64 sum = 0.;
    vector<f64> fitnesses;

    auto print() -> void {
        for (i32 i = 0; i < fitnesses.size(); ++i) {
            for (i32 j = 0; j < 5 && i < fitnesses.size(); ++j, ++i) {
                cout << std::setw(5) << fitnesses[i] << ' ';
            }
            cout << endl;
        }
        cout << sum << endl;
    }
};

Population population;

f64 inf, sub, highBase;
i32 chromosomeLen, initPopSize;

function<f64(f64 const&)> fitFunc;

public:
    auto fitnessFunc(Individual const& individual) -> f64 {
        return max(fitFunc(getNum(individual)), 0.);
    }

    /**
     * @brief Construct a new GA object
     * 
     * @param inf 区间上界
     * @param sub 区间下界
     * @param accuracy 精确度
     * @param initPopSize 初始种群大小
     * @param fitFunc 需要寻找极值的函数
     */
    GA(f64 const& inf,
        f64 const& sub,
        f64 const& accuracy,
        i32 const& initPopSize,
        function<f64(f64 const&)> const& fitFunc):
        inf(inf),
        sub(sub),
        highBase(1.),
        chromosomeLen(1),
        initPopSize(initPopSize),
        fitFunc(fitFunc) {
        f64 absMax = max(abs(inf), abs(sub));
        while (absMax >= accuracy) {
            ++chromosomeLen;
            if (absMax > 1.) {
                highBase *= 2;
            }
            absMax /= 2.;
        }
    }
    
    ~GA() = default;

    f64 getNum(Individual const& individual) {
        f64 x = 0., base = highBase;
        for (i32 i = 1; i < individual.chromosome.size(); ++i) {
            if (individual.chromosome[i]) x += base;
            base /= 2.;
        }
        return individual.chromosome[0] ? -x : x;
    }

    auto init() -> void {
        for (i32 i = 0; i < initPopSize; ++i) {
            Individual temp;
            temp.chromosome.resize(chromosomeLen);
            if (inf > 0 && sub < 0) {
                temp.chromosome[0] = random::uniformInt(0, 1);
            } else if (inf > 0 && sub > 0) {
                temp.chromosome[0] = 0;
            } else if (inf < 0 && sub < 0) {
                temp.chromosome[0] = 1;
            }
            
            f64 x;
            do {
                for (i32 j = 1; j < chromosomeLen; ++j) {
                    temp.chromosome[j] = random::uniformInt(0, 1);
                }                
                x = getNum(temp);
            } while (x < sub || inf < x);
            
            population.push_back(temp);
        }
    }

    auto fitness(Population const& pop) -> FitnessInfo {
        FitnessInfo fi;
        for (Individual const& individual: population) {
            f64 fitness = fitnessFunc(individual);
            fi.fitnesses.push_back(fitness);
            fi.sum += fitness;
        }
        return fi;
    }

    template <SelectionType SelType = SelectionType::RANDOM>
    auto select(i32 newPopSize = -1) -> Population {
        if (newPopSize = -1) {
            newPopSize = static_cast<i32>(population.size());
        }
        Population selectedPopulation(newPopSize);
        if constexpr (SelType == SelectionType::RANDOM) {
            for (i32 i = 0; i < newPopSize; ++i) {
                selectedPopulation[i] = random::choose<bool, FunctionReturnType::VALUE>(population);
            }
        } else if constexpr (SelType == SelectionType::RANK) {
            FitnessInfo fi = fitness(population);
            for (i32 i = 0; i < newPopSize; ++i) {
                selectedPopulation[i] = population[random::chooseByWeights(fi.fitnesses, fi.sum)];
            }
        } else {

        }
        return selectedPopulation;
    }

    template <CrossoverType CroType = CrossoverType::SINGLE_POINT>
    auto crossover(Individual const& parent1, Individual const& parent2) -> pair<Individual, Individual> {
        pair<Individual, Individual> children;
        i32 len = chromosomeLen;
        children.first.chromosome.resize(len);
        children.second.chromosome.resize(len);
        if constexpr (CroType == SINGLE_POINT) {
            i32 splitPoint = random::uniformInt(1, len);
            for (i32 i = 0; i < splitPoint; ++i) {
                children.first.chromosome[i] = parent1.chromosome[i];
            }
            for (i32 i = splitPoint; i < len; ++i) {
                children.second.chromosome[i] = parent1.chromosome[i];
            }
            for (i32 i = 0; i < splitPoint; ++i) {
                children.second.chromosome[i] = parent2.chromosome[i];
            }
            for (i32 i = splitPoint; i < len; ++i) {
                children.first.chromosome[i] = parent2.chromosome[i];
            }
        } else {

        }
        return children;
    }

    /**
     * @brief 染色体交叉互换产生后代
     * 
     */
    auto crossover(Population pop) -> Population {
        Population newPop;
        while (pop.size() > 1) {
            i32 size = static_cast<i32>(pop.size());
            swap(pop[random::uniformInt(0, size - 1)], pop[size - 1]);
            swap(pop[random::uniformInt(0, size - 2)], pop[size - 2]);
            auto children = crossover(pop[size - 1], pop[size - 2]);
            newPop.push_back(children.first);
            newPop.push_back(children.second);
            pop.pop_back();
            pop.pop_back();
        }
        return newPop;
    }

    /**
     * @brief 突变
     * 
     */
    auto mutation(Population pop) -> void {
        for (Individual& individual: pop) {
            while (random::trigger(0.03)) {
                f64 x;
                while (true) {
                    i32 idx = random::uniformInt(0, static_cast<i32>(individual.chromosome.size() - 1));
                    individual.chromosome[idx] = !individual.chromosome[idx];
                    x = getNum(individual);
                    if (sub < x || x < inf) {
                        break;
                    }
                    individual.chromosome[idx] = !individual.chromosome[idx];
                } ;
            }
        }
    }

    auto solution(i32 const& t = 32) -> void {
        vector<pair<f64, f64>> record;
        init();
        cout << "i = " << 0 << endl;
        /*
        for (Individual const& i: population) {
            cout << std::setw(6) << getNum(i) << ' ';
            cout << i.chromosome << endl;
        }
        */

        FitnessInfo fi = fitness(population);
        fi.print();
        i32 idx = 0;
        for (i32 j = 1; j < fi.fitnesses.size(); ++j) {
            if (fi.fitnesses[j] > fi.fitnesses[idx]) {
                idx = j;
            }
        }
        cout << std::setw(5) << getNum(population[idx]) << "max " << fi.fitnesses[idx] << endl;
        record.push_back({ getNum(population[idx]), fi.fitnesses[idx] });

        for (i32 i = 0; i < t; ++i) {
            cout << "i = " << i + 1 << endl;
            population = crossover(select<SelectionType::RANK>());
            mutation(population);

            /*
            cout << endl;
            for (Individual const& i: population) {
                cout << std::setw(5) << getNum(i) << ' ';
                cout << i.chromosome << endl;
            }
            */
            fi = fitness(population);
            fi.print();
            idx = 0;
            for (i32 j = 1; j < fi.fitnesses.size(); ++j) {
                if (fi.fitnesses[j] > fi.fitnesses[idx]) {
                    idx = j;
                }
            }
            cout << std::setw(5) << getNum(population[idx]) << " max " << fi.fitnesses[idx] << endl;
            record.push_back({ getNum(population[idx]), fi.fitnesses[idx] });
        }

        for (size_t i = 0; i < record.size(); i++) {
            cout << std::setw(5) << record[i].first << ' ' << record[i].second << endl;
        }
        
    }

};

}