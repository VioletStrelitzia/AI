#pragma once
#include "core.h"

namespace yuki {
	template <class ElemType = f64>
	class Matrix {
	protected:
		u64 _rows, _cols;
		vector<ElemType> _data;

        void printInfo(u64 const& width = 6) const {
			for (u64 r = 0, i = 0; r < _rows; ++r) {
				for (u64 c = 0; c < _cols; ++c, ++i)
					cout << _data[i] << " ";
				cout << "\n";
			}
			cout << typeid(*this).name() << " (" << _rows << ", " << _cols << ")";
		}

		/**
		 * @brief 递归计算行列式
		 * 
		 * @param mat 矩阵
		 * @return ElemType 行列式的值
		 */
		auto detRecursion(Matrix<ElemType> mat) const -> ElemType {
			if (mat.rows() == 1) return mat.at(0, 0);
			ElemType sum = 0;
			// 按第一行展开
			for (auto i = 0; i < mat._rows; ++i) {
				Matrix<ElemType> cofactor = mat.cofactor(0, i);
				// 计算 (0, i) 的代数余子式
				sum += mat._DataBase[i] * cofactorAlgebraic(cofactor, i);
			}
			return sum;
		}

	public:
		Matrix(): _rows(0), _cols(0), _data() {}

		Matrix(u64 const& rows, u64 const& cols) :
			_rows(rows), _cols(cols), _data(rows * cols) {}

		Matrix(u64 const& rows, u64 const& cols, ElemType const& value, bool const& all = false) :
			_rows(rows), _cols(cols), _data(rows * cols, all ? value : 0) {
			if (!all) {
				for (u64 i = 0; i < rows; ++i) {
					_data[i * cols + i] = value;
				}
			}
		}

		~Matrix() = default;

		friend ostream& operator << (ostream& os, Matrix const& MatB) {
			for (u64 r = 0, i = 0; r < MatB._rows; ++r) {
				for (u64 c = 0; c < MatB._cols; ++c, ++i)
					cout << MatB._data[i] << " ";
				cout << "\n";
			}
			cout << typeid(MatB).name() << " (" << MatB._rows << ", " << MatB._cols << ")";
			return os;
		}

		friend istream& operator >> (istream& is, Matrix& MatB) {
			for (u64 i = 0; i < MatB._size; ++i)
                cin >> MatB._data[i];
			return is;
		}

		u64 getRows() const { return _rows; }

		u64 rows() const { return _rows; }

		u64 getCols() const { return _cols; }

		u64 cols() const { return _cols; }

		// 重载[]运算符（内存不安全）
		ElemType const* operator [] (u64 const& row) const {
			return _data[row];
		}

		ElemType* operator [] (u64 const& row) {
			return _data[row];
		}

		// at访问函数（内存安全版本）
		virtual ElemType const& at(u64 const& row, u64 const& col) const {
			return _data[row * _cols + col];
		}

		virtual ElemType& at(u64 const& row, u64 const& col) {
			return _data[row * _cols + col];
		}

		void reshape(u64 const& row, u64 const& col) {
			_rows = row;
			_cols = col;
		}

		void transpose() {
			vector<ElemType> data(_data);

			for (auto r = 0; r < _rows; ++r)
				for (auto c = 0; c < _cols; ++c)
					_data[c * _rows + r] = data[r * _cols + c];
            
            swap(_rows, _cols);
		}

		/**
		 * @brief 所有元素化为 value 的值
		 * 
		 * @param value 
		 */
		auto equalize(ElemType const& value) -> void {
			for(auto& it: _data) {
				it = value;
			}
		}

		/**
		 * @brief 四周填充
		 * 
		 * @param padding 填充的层数
		 * @param value 填充的值
		 */
		auto pad(u64 const& padding, ElemType const& value) -> void {
			u64 newRows = rows() + padding * 2,
				newCols = cols() + padding * 2;
			// 创建新数据数组并用填充值初始化
			vector<ElemType> newData(newRows * newCols, value);
			
			// 复制原矩阵数据到新数组中心位置
			for(u64 r = 0; r < _rows; ++r) {
				for(u64 c = 0; c < _cols; ++c) {
					u64 newIndex = (r + padding) * newCols + (c + padding);
					newData[newIndex] = at(r, c);
				}
			}
			
			// 更新矩阵参数
			_rows = newRows;
			_cols = newCols;
			_data.swap(newData);
		}
	};

}

