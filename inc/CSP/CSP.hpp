#pragma once
#include "Ytools.h"
#include "Variable.hpp"

namespace yuki::atri::csp {
/**
 * @brief CSP算法（基于 ac3 算法）
 * 
 * @tparam ValueType 变量的值的类型
 */
template <typename ValueType>
class CSP {
public:
	/// @brief 变量类型
	using Var = Variable<ValueType>;

	/// @brief 二元约束的变量二元变量值元组
	using BinaryScope = pair<ValueType, ValueType>;

	/// @brief 弧类型
	using Arc = pair<usize, usize>;

	/// @brief 满足二元约束，则返回true
	using BinaryConstraint = function<bool(BinaryScope const&, CSP const&)>;
	//using BinaryConstraint = bool(*)(BinaryScope const&, CSP const&);

	vector<Var> 					 variables;			 ///< 变量
	vector<vector<BinaryConstraint>> binaryConstraints;	 ///< 二元约束
	queue<Arc> 						 arcs;				 ///< 弧

public:
	CSP() = delete;
	~CSP() = default;

	/// @brief 构造函数，必须用变量集合初始化，然后再使用 addBinaryConstraint 函数添加变量之间的二元约束
	/// @param variables 变量集合（需要初始化好值域） 
	CSP(vector<Var> const& variables);

	/// @brief 为序号为 varId1，varId2 的 var 添加二元约束
	/// @param varId1 var1 的Id
	/// @param varId2 var2 的Id
	/// @param bc 二元约束
	auto addBinaryConstraint(usize const& varId1, usize const& varId2, BinaryConstraint const& bc) -> void;

private:
	/// @brief 检查 var1，var2 分别在 value1，value2 的取值下的二元约束是否成立（根据 varId1 和 varId2 获取二元约束）
	/// @param value1 var1 的取值
	/// @param varId1 var1 的ID
	/// @param value2 var2 的取值
	/// @param varId2 var2 的ID
	/// @return var1，var2 在 value1，value2 的取值下是否满足二元约束
	auto checkBinaryConstraint(ValueType const& value1, usize const& varId1, ValueType const& value2, usize const& varId2) const -> bool;

	/// @brief 检查以 varId 为序号的 var 在 value 的取值下是否能和其他已赋值的 var 相容
	/// @param value var 的取值
	/// @param varId var 的Id
	/// @return var 是否相容
	auto consistent(ValueType const& value, usize const& varId) const -> bool;

	/// @brief 检查 var2 是否对 var1 弧相容
	/// @param value1 var1 的取值
	/// @param varId1 var1 的ID
	/// @param varId2 var2 的ID
	/// @return var2 是否对 var1 弧相容
	auto satisfy(ValueType const& value1, usize const& varId1, usize const& varId2) const -> bool;

	/// @brief 使 var1 对于 var2 弧相容（对于 var1 值域中的任意取值 value1，
	/// 只要 var2 的值域中存在一个取值 value2 可以满足 var1 和 var2 的二元约束即可，否则将 value1 从 var1 的值域中删除）
	/// @param varId1 var1 的ID
	/// @param varId2 var2 的ID
	/// @return var1 的值域是否发生了改变
	auto revise(usize const& varId1, usize const& varId2) -> bool;

	/// @brief ac3 算法
	/// @return 是否有变量的值域为空（失败）
	auto ac3() -> bool;

	/// @brief 推断，将值域内只有一个值的变量赋值为这个取值
	/// @return 是否未失败（是否没有变量的值域为空）
	auto inference() -> bool;

	/// @brief 检查 variables 是否已经是解决方案
	/// @return variables 是否已经是解决方案
	auto isSolution() -> bool;

	/// @brief 记录 CSP 的状态
	/// @return CSP 的状态
	auto record() -> vector<Var>;

	/// @brief 从 record 恢复 CSP 的状态
	/// @param record CSP 状态的记录
	auto recover(vector<Var> const& record) -> void;

	/// @brief 选择一个未被赋值的 var
	/// @return var 的 ID
	auto selectUnassignedVariableId() -> usize;

	/// @brief 返回不排序的值域序列
	/// @param varId var 的 ID
	/// @return 不排序的值域序列
	auto orderDomainValues(usize const& varId) -> vector<ValueType>&;

	/// @brief 回溯算法
	auto backtrack() -> void;
	
	/**
	 * @brief 获取一个取值为 value 的 var 的冲突数
	 * 
	 * @param value var 的取值
	 * @param varId var 的 ID
	 * @return usize 冲突数
	 */
	auto getConflictsNum(ValueType const& value, usize const& varId) -> usize;

	/**
	 * @brief 随机选择一个冲突数大于 0 的 var
	 * 
	 * @return usize 该 var 的 ID
	 */
	auto randomChooseConflictVariable() -> usize;

	/**
	 * @brief 选择一个 var 冲突数最小的取值（有多个则从中随机取一个）
	 * 
	 * @param varId var 的 ID
	 * @return ValueType 一个使 var 冲突数最小的取值
	 */
	auto minConflictsNumValue(usize const& varId) -> ValueType;

	/**
	 * @brief 对 variables 的所有 var 从其值域里随机赋值（不重置值域）
	 * 
	 */
	auto randomAssign() -> void;


public:
	/// @brief 回溯搜索算法（基于ac3）
	/// @return 一个解决方案
	auto backtrackingSearch() -> vector<Var>;

	/// @brief 最小冲突算法
	/// @param maxStep 最大搜索步数
	/// @return 一个解决方案
	auto minConflict(usize const& maxStep = 200) -> vector<Var> {
		randomAssign();
		for (usize i = 0; i < maxStep; ++i) {
			if (isSolution()) {
				//cout << i + 1 << " staps used!\n";
				return variables;
			}
			usize varId = randomChooseConflictVariable();
			variables[varId].value = minConflictsNumValue(varId);
		}
		return vector<Var>();
	}
};

template <typename ValueType>
CSP<ValueType>::CSP(vector<Var> const& vars) :
	variables(vars),
	binaryConstraints(vars.size(), vector<BinaryConstraint>(vars.size(), nullptr)),
	arcs() {}

template <typename ValueType>
auto CSP<ValueType>::addBinaryConstraint(usize const& varId1, usize const& varId2, BinaryConstraint const& bc) -> void {
	binaryConstraints[varId1][varId2] = bc;
	arcs.emplace(varId1, varId2);
}

template <typename ValueType>
auto CSP<ValueType>::checkBinaryConstraint(ValueType const& value1, usize const& varId1, ValueType const& value2, usize const& varId2) const -> bool {
	BinaryConstraint const& bc = binaryConstraints[varId1][varId2];
	if (bc) {
		return bc({ value1, value2 }, *this);
	}
	return true;
}

template <typename ValueType>
auto CSP<ValueType>::consistent(ValueType const& value, usize const& varId) const -> bool {
	usize i, end = variables.size();
	for (i = 0; i < varId; ++i) {
		if (!variables[i].unassigned) {
			ValueType const& value_i = variables[i].value;
			if (!checkBinaryConstraint(value_i, i, value, varId) ||
				!checkBinaryConstraint(value, varId, value_i, i)) {
				return false;
			}
		}
	}
	for (i = varId + 1; i < end; ++i) {
		if (!variables[i].unassigned) {
			ValueType const& value_i = variables[i].value;
			if (!checkBinaryConstraint(value_i, i, value, varId) ||
				!checkBinaryConstraint(value, varId, value_i, i)) {
				return false;
			}
		}
	}
	return true;
}

template <typename ValueType>
auto CSP<ValueType>::satisfy(ValueType const& value1, usize const& varId1, usize const& varId2) const -> bool {
	for (ValueType const& value2 : variables[varId2].domain) {
		if (checkBinaryConstraint(value1, varId1, value2, varId2) &&
			checkBinaryConstraint(value2, varId2, value1, varId1)) {
			return true;
		}
	}
	return false;
}

template <typename ValueType>
auto CSP<ValueType>::revise(usize const& varId1, usize const& varId2) -> bool {
	bool revised = false;
	vector<ValueType>& D1 = variables[varId1].domain;
	auto it = D1.begin();
	while (it != D1.end()) {
		if (satisfy(*it, varId1, varId2)) {
			++it;
		} else {
			it = D1.erase(it);
			revised = true;
		}
	}
	return revised;
}

template <typename ValueType>
auto CSP<ValueType>::ac3() -> bool {
	queue<Arc> arcQueue = arcs;
	while (!arcQueue.empty()) {
		Arc& currentArc = arcQueue.front();
		usize& i = currentArc.first;
		usize& j = currentArc.second;
		// 维护Xi对Xj的弧相容
		if (revise(i, j)) {
			// Xi的值域发生了更改
			if (variables[i].domain.empty()) {
				return false;
			}
			// 将以Xi为tail的弧入队
			for (usize k = 0; k < variables.size(); ++k) {
				if (binaryConstraints[k][i] && k != i) {
					arcQueue.emplace(k, i);
				}
			}
		}

		arcQueue.pop();
	}
	return true;
}

template <typename ValueType>
auto CSP<ValueType>::inference() -> bool {
	if (ac3()) {
		for (Var& var : variables) {
			if (var.unassigned && next(var.domain.begin()) == var.domain.end()) {
				var.assign(var.domain.front(), false);
			}
		}
		return true;
	}
	return false;
}

template <typename ValueType>
auto CSP<ValueType>::isSolution() -> bool {
	for (Var& var : variables) {
		if (var.unassigned) {
			return false;
		}
	}
	for (usize i = 0; i < variables.size(); ++i) {
		for (usize j = 0; j < variables.size(); ++j) {
			if (j == i) {
				continue;
			}
			if (!checkBinaryConstraint(variables[i].value, i, variables[j].value, j) ||
				!checkBinaryConstraint(variables[j].value, j, variables[i].value, i)) {
				return false;
			}
		}
	}
	return true;
}

template <typename ValueType>
auto CSP<ValueType>::record() -> vector<Var> {
	return variables;
}

template <typename ValueType>
auto CSP<ValueType>::recover(vector<Var> const& record) -> void {
	variables = record;
}

template <typename ValueType>
auto CSP<ValueType>::selectUnassignedVariableId() -> usize {
	for (usize i = 0, end = variables.size(); i < end; ++i) {
		if (variables[i].unassigned) {
			return i;
		}
	}
	return SIZE_MAX;
}

template <typename ValueType>
auto CSP<ValueType>::orderDomainValues(usize const& varId) -> vector<ValueType>& {
	return variables[varId].domain;
}

template <typename ValueType>
auto CSP<ValueType>::backtrack() -> void {
	if (isSolution()) {
		return;
	}
	usize varId = selectUnassignedVariableId();
	vector<ValueType> orderDomain = orderDomainValues(varId);
	for (ValueType& value : orderDomain) {
		if (consistent(value, varId)) {
			auto rcd = record();
			variables[varId].assign(value);
			if (inference()) {
				backtrack();
				if (isSolution()) {
					return;
				}
			}

			recover(rcd);
		}
	}
}

template <typename ValueType>
auto CSP<ValueType>::getConflictsNum(ValueType const& value, usize const& varId) -> usize {
	usize i, end = variables.size(), conflictsNum = 0;
	for (i = 0; i < varId; ++i) {
		if (!variables[i].unassigned) {
			ValueType const& value_i = variables[i].value;
			if (!checkBinaryConstraint(value_i, i, value, varId) ||
				!checkBinaryConstraint(value, varId, value_i, i)) {
				++conflictsNum;
			}
		}
	}
	for (i = varId + 1; i < end; ++i) {
		if (!variables[i].unassigned) {
			ValueType const& value_i = variables[i].value;
			if (!checkBinaryConstraint(value_i, i, value, varId) ||
				!checkBinaryConstraint(value, varId, value_i, i)) {
				++conflictsNum;
			}
		}
	}
	return conflictsNum;
}

template <typename ValueType>
auto CSP<ValueType>::randomChooseConflictVariable() -> usize {
	usize i = 0;
	vector<usize> conflictVariablesId;
	for (Var const& var : variables) {
		if (!var.unassigned && getConflictsNum(var.value, i) > 0) {
			conflictVariablesId.push_back(i);
		}
		++i;
	}
	if (conflictVariablesId.empty()) {
		return 0;
	} else {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<usize> dis(0, conflictVariablesId.size() - 1);
		return conflictVariablesId[dis(gen)];
	}
}

template <typename ValueType>
auto CSP<ValueType>::minConflictsNumValue(usize const& varId) -> ValueType {
	vector<ValueType> minConflictsValues;
	usize curConflictsNum, minConflictsNum = variables.size();
	for (ValueType const& val : variables[varId].domain) {
		curConflictsNum = getConflictsNum(val, varId);
		if (curConflictsNum < minConflictsNum) {
			minConflictsValues.clear();
			minConflictsValues.push_back(val);
			minConflictsNum = curConflictsNum;
		} else if (curConflictsNum == minConflictsNum) {
			minConflictsValues.push_back(val);
		}
	}
	if (minConflictsValues.size() == 1) {
		return minConflictsValues[0];
	} else {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<usize> dis(0, minConflictsValues.size() - 1);
		return minConflictsValues[dis(gen)];
	}
}

template <typename ValueType>
auto CSP<ValueType>::randomAssign() -> void {
	random_device rd;
	mt19937 gen(rd());
	for (Var& var : variables) {
		var.assign(random::choose(var.domain), false);
	}
}

template <typename ValueType>
auto CSP<ValueType>::backtrackingSearch() -> vector<Var> {
	backtrack();
	return variables;
}
}