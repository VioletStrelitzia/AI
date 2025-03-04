#pragma once
#include "core.h"
#include "Default.h"

namespace yuki {
	/* 动态矩阵类 */
	template <typename ElemType = f64>
	class Matrix : public Matrix<ElemType> {
	private:
		using MBE = Matrix<ElemType>;
		/******************************************************************************************
		* 递归计算行列式
		******************************************************************************************/
		auto DetRecursion(Matrix<ElemType> mat) const -> ElemType {
			if (mat._rows == 1) return mat._DataBase[0];
			ElemType sum = 0;
			// 按第一行展开
			for (auto i = 0; i < mat._rows; ++i) {
				Matrix<ElemType> cofactor = mat.cofactor(0, i);
				// 计算(0, i)的代数余子式
				sum += mat._DataBase[i] * CofactorAlgebraic(cofactor, i);
			}
			return sum;
		}

		/*****************************************************************************************/
	public:
		/******************************************************************************************
		* 无参初始化
		******************************************************************************************/
		Matrix() :
			MBE() {}

		/******************************************************************************************
		* 含参初始化
		* rows : 行
		* cols : 列
		******************************************************************************************/
		Matrix(size_t const& rows, size_t const& cols) :
			MBE(rows, cols) {}

		/******************************************************************************************
		* 含参初始化
		* rows : 行
		* cols : 列
		* value : 元素初始化模板
		* all = true : 修改全体元素
		* all = false : 修改主对角线元素
		******************************************************************************************/
		Matrix(size_t const& rows, size_t const& cols, const ElemType& value) :
			MBE(rows, cols, value) {}

		Matrix(size_t const& rows, size_t const& cols, const ElemType& value, bool const& all = false) :
			MBE(rows, cols) {
			memset(MBE::_DataBase, 0x00, MBE::_size * sizeof(ElemType));
			for (size_t i = 0; i < rows || i < cols; ++i) MBE::_data[i][i] = value;
		}

		/******************************************************************************************
		* 复制构造
		******************************************************************************************/
		Matrix(Matrix<ElemType> const& mat) :
			MBE(mat._rows, mat._cols) {
			memcpy(MBE::_DataBase, mat._DataBase, MBE::_size * sizeof(ElemType));
		}

		/******************************************************************************************
		* 提供数组风格的初始化
		******************************************************************************************/
		//LAM(const vector<vector<ElemType>>& init) : _rows(init.size()), _cols(0) {
		//	for (size_t i = 0; i < init.size(); ++i) {
		//		if (MBE::_cols < init[i].size()) {
		//			MBE::_cols = init[i].size();
		//		}
		//	}
		//		
		//	MBE::_data = new ElemType*[MBE::_rows];
		//	for (size_t i = 0; i < MBE::_rows; ++i) {
		//		MBE::_data[i] = new ElemType[MBE::_cols]();
		//	}
		//	for (size_t r = 0; r < MBE::_rows; ++r) {
		//		size_t c = 0;
		//		for (; c < init[r].size(); ++c) {
		//			MBE::_data[r][c] = init[r][c];
		//		}
		//		for (; c < MBE::_cols; ++c) {
		//			MBE::_data[r][c] = 0;
		//		}
		//	}
		//}

		/******************************************************************************************
		* 析构函数
		******************************************************************************************/
		~Matrix() {}

		/******************************************************************************************
		* resize
		******************************************************************************************/
		void resize(size_t const& NewRows, size_t const& NewCols) {
			/*if (NewRows != 0 && NewCols != 0) {
				if (MBE::_data != nullptr) {
					for (size_t i = 0; i < MBE::_rows; ++i) {
						delete[] MBE::_data[i];
					}
					delete[] MBE::_data;
				}
				MBE::_rows = NewRows;
				MBE::_cols = NewCols;
				MBE::_data = new ElemType*[NewRows];
				for (size_t i = 0; i < NewRows; ++i) {
					MBE::_data[i] = new ElemType[NewCols];
				}
			}
			else {
				if (MBE::_data != nullptr) {
					for (size_t i = 0; i < MBE::_rows; ++i) {
						delete[] MBE::_data[i];
					}
					delete[] MBE::_data;
				}
				MBE::_data = nullptr;
				MBE::_rows = 0;
				MBE::_cols = 0;
			}*/
		}


		///******************************************************************************************
		//* 对(row, col)位置的元素进行操作
		//******************************************************************************************/
		//ElemType& at(size_t const& row, size_t const& col) {
		//	assert(row < MBE::_rows && col < MBE::_cols);
		//	return MBE::_data[row][col];
		//}

		//ElemType at(size_t const& row, size_t const& col) const {
		//	assert(row < MBE::_rows && col < MBE::_cols);
		//	return MBE::_data[row][col];
		//}

		/* 四周填充操作 */
		auto pad(size_t const& padding, const ElemType& value) -> void {
			size_t NewRows = MBE::_rows + padding * 2, NewCols = MBE::_cols + padding * 2;
			MBE::_size = NewRows * NewCols;

			ElemType* DataBase = new ElemType[MBE::_size];
			ElemType tmpv = value;
			size_t i = 1, j = 2, sizei = sizeof(ElemType);
			memcpy(DataBase, &tmpv, sizei);
			for (; j < MBE::_size; i += i, j += j, sizei += sizei) memcpy(DataBase + i, DataBase, sizei);
			memcpy(DataBase + i, DataBase, (MBE::_size - i) * sizeof(ElemType));

			ElemType** data = new ElemType * [NewRows];
			for (size_t r = 0, i = 0; r < NewRows; ++r, i += NewCols) data[r] = DataBase + i;

			/* 复制中间 */
			for (size_t r = padding; r < MBE::_rows + padding; ++r)
				memcpy(DataBase + r * NewCols + padding, MBE::_DataBase + (r - padding) * MBE::_cols, MBE::_cols * sizeof(ElemType));

			delete[] MBE::_DataBase;
			delete[] MBE::_data;
			MBE::_DataBase = DataBase;
			MBE::_data = data;
			MBE::_rows = NewRows;
			MBE::_cols = NewCols;
		}

		/* 初等行变换 */
		/******************************************************************************************
		* 行交换
		******************************************************************************************/
		auto RowSwap(size_t const& row1, size_t const& row2) -> void {
			// 避免自我交换
			if (row1 == row2) return;

			for (size_t c = 0; c < MBE::_cols; ++c) {
				ElemType tmp;
				tmp = MBE::_data[row1][c];
				MBE::_data[row1][c] = MBE::_data[row2][c];
				MBE::_data[row2][c] = tmp;
			}
		}

		/******************************************************************************************
		* 行乘标量
		******************************************************************************************/
		auto RowScale(size_t const& row, const ElemType& scale) -> void {
			if (scale == 1) return;

			for (size_t c = 0; c < MBE::_cols; ++c)
				MBE::_data[row][c] = MBE::_data[row][c] * scale;
		}

		/******************************************************************************************
		* 行乘标量加法
		******************************************************************************************/
		auto RowAddMultiple(size_t const& row1, size_t const& row2, const ElemType& scale) -> void {
			if (scale == 0) return;

			for (size_t c = 0; c < MBE::_cols; ++c)
				MBE::_data[row1][c] = MBE::_data[row1][c] + MBE::_data[row2][c] * scale;
		}

		/* 初等列变换 */
		/******************************************************************************************
		* 列交换
		******************************************************************************************/
		auto ColSwap(size_t const& col1, size_t const& col2) -> void {
			// 避免自我交换
			if (col1 == col2) return;

			for (size_t r = 0; r < MBE::_rows; ++r) {
				ElemType tmp;
				tmp = MBE::_data[r][col1];
				MBE::_data[r][col1] = MBE::_data[r][col2];
				MBE::_data[r][col2] = tmp;
			}
		}

		/******************************************************************************************
		* 列乘标量
		******************************************************************************************/
		auto ColScale(size_t const& col, const ElemType& scale) -> void {
			if (scale == 1) return;

			for (size_t r = 0; r < MBE::_rows; ++r)
				MBE::_data[r][col] = MBE::_data[r][col] * scale;
		}

		/******************************************************************************************
		* 列乘标量加法
		******************************************************************************************/
		auto ColAddMultiple(size_t const& col1, size_t const& col2, const ElemType& scale) -> void {
			if (scale == 0) return;

			for (size_t r = 0; r < MBE::_rows; ++r)
				MBE::_data[r][col1] = MBE::_data[r][col1] + MBE::_data[r][col2] * scale;
		}

		/* 初等行变换 const version */
		/******************************************************************************************
		* 行交换 const version
		******************************************************************************************/
		auto RowSwap(size_t const& row1, size_t const& row2) const -> Matrix<ElemType> {
			// 避免自我交换
			if (row1 == row2) return *this;

			Matrix<ElemType> dst(*this);
			for (size_t c = 0; c < dst._cols; ++c) {
				ElemType tmp;
				tmp = dst._data[row1][c];
				dst._data[row1][c] = dst._data[row2][c];
				dst._data[row2][c] = tmp;
			}
			return dst;
		}

		/******************************************************************************************
		* 行乘标量 const version
		******************************************************************************************/
		auto RowScale(size_t const& row, const ElemType& scale) const -> Matrix<ElemType> {
			if (scale == 1) return *this;

			Matrix<ElemType> dst(*this);
			for (size_t c = 0; c < dst._cols; ++c)
				dst._data[row][c] = dst._data[row][c] * scale;
			return dst;
		}

		/******************************************************************************************
		* 行乘标量加法 const version
		******************************************************************************************/
		auto RowAddMultiple(size_t const& row1, size_t const& row2, const ElemType& scale) const -> Matrix<ElemType> {
			if (scale == 0) return *this;

			Matrix<ElemType> dst(*this);
			for (size_t c = 0; c < dst._cols; ++c)
				dst._data[row1][c] = dst._data[row1][c] + dst._data[row2][c] * scale;
			return dst;
		}

		/* 初等列变换 const version */
		/******************************************************************************************
		* 列交换 const version
		******************************************************************************************/
		auto ColSwap(size_t const& col1, size_t const& col2) const -> Matrix<ElemType> {
			// 避免自我交换
			if (col1 == col2) return *this;

			Matrix<ElemType> dst(*this);
			for (size_t r = 0; r < dst._rows; ++r) {
				ElemType tmp;
				tmp = dst._data[r][col1];
				dst._data[r][col1] = dst._data[r][col2];
				dst._data[r][col2] = tmp;
			}
			return dst;
		}

		/******************************************************************************************
		* 列乘标量 const version
		******************************************************************************************/
		auto ColScale(size_t const& col, const ElemType& scale) const -> Matrix<ElemType> {
			if (scale == 0) return *this;

			Matrix<ElemType> dst(*this);
			for (size_t r = 0; r < dst._rows; ++r)
				dst._data[r][col] = dst._data[r][col] * scale;
			return dst;
		}

		/******************************************************************************************
		* 列乘标量加法 const version
		******************************************************************************************/
		auto ColAddMultiple(size_t const& col1, size_t const& col2, const ElemType& scale) const -> Matrix<ElemType> {
			if (scale == 0) return *this;

			Matrix<ElemType> dst(*this);
			for (size_t r = 0; r < dst._rows; ++r)
				dst._data[r][col1] = dst._data[r][col1] + dst._data[r][col2] * scale;
			return dst;
		}

		/******************************************************************************************
		* 消元模式
		******************************************************************************************/
		enum PivotMode {
			all = 0,
			down = 1,
			up = 2,
			right = 3,
			left = 4
		};

		/******************************************************************************************
		* 行消元操作函数
		******************************************************************************************/
		void RowPivot(size_t& row, size_t& col, const PivotMode& RowPivotMode = all) {
			// 错误：除数为0
			if (MBE::_data[row][col] == 0) throw dflt::DivideByZero();

			// 错误：模式错误
			if (RowPivotMode != all && RowPivotMode != down && RowPivotMode == up) throw dflt::UnexpectedEnumParameter();

			// 消元：从第0行到第row行
			if (RowPivotMode == all || RowPivotMode == up) {
				for (size_t r = 0; r < row; ++r)
					this->RowAddMultiple(r, row, -MBE::_data[r][col] / MBE::_data[row][col]);
			}
			// 消元：从第row+1行到第MBE::_rows-1行
			if (RowPivotMode == all || RowPivotMode == down) {
				for (size_t r = row + 1; r < MBE::_rows; ++r)
					this->RowAddMultiple(r, row, -MBE::_data[r][col] / MBE::_data[row][col]);
			}
		}

		/******************************************************************************************
		* 列消元操作函数
		******************************************************************************************/
		void ColPivot(size_t& row, size_t& col, const PivotMode& ColPivotMode = all) {
			// 错误：除数为0
			if (MBE::_data[row][col] == 0) throw dflt::DivideByZero();

			// 错误：模式错误
			if (ColPivotMode != all && ColPivotMode != right && ColPivotMode == left) throw dflt::UnexpectedEnumParameter();

			// 消元：从第0列到第col列
			if (ColPivotMode == all || ColPivotMode == left) {
				for (size_t c = 0; c < col; ++c)
					this->ColAddMultiple(c, col, -MBE::_data[row][c] / MBE::_data[row][col]);
			}
			// 消元：从第col+1列到第MBE::_cols-1列
			if (ColPivotMode == all || ColPivotMode == right) {
				for (size_t c = col + 1; c < MBE::_cols; ++c)
					this->ColAddMultiple(c, col, -MBE::_data[row][c] / MBE::_data[row][col]);
			}
		}

		/******************************************************************************************
		* 行阶梯型（上三角）
		******************************************************************************************/
		auto RowEchelon() const -> Matrix<ElemType> {
			Matrix<ElemType> dst(*this);
			// min：化简后最多有min(dst._rows, dst._cols)个非零行
			size_t min = dst._rows < dst._cols ? dst._rows : dst._cols;
			// CIndex：寻找第r行的非零首元的起始行数
			for (size_t r = 0, CIndex = 0; r < min; ++r) {
				bool flag = false;
				// for：从CIndex列开始向后面的列寻找非零列
				for (size_t c = CIndex; c < dst._cols; ++c) {
					// for：从第r行开始向后面的行寻找第c列是否存在非零元
					for (size_t i = r; i < dst._rows; ++i) {
						if (dst._data[i][c] != 0) {
							// 找到了就交换此行与第r行
							dst.RowSwap(i, r);
							// 消元
							dst.RowPivot(r, c, down);
							CIndex = c + 1;
							flag = true;
							break;
						}
					}
					if (flag) break;
				}
			}
			return dst;
		}

		/******************************************************************************************
		* 列阶梯型（下三角）
		******************************************************************************************/
		Matrix<ElemType> ColEchelon() const {
			Matrix<ElemType> dst(*this);

			/*dst = dst.transpose();
			dst = dst.RowEchelon();
			dst = dst.transpose();*/

			// min：化简后最多有min(dst._rows, dst._cols)个非零列
			size_t min = dst._rows < dst._cols ? dst._rows : dst._cols;
			// RIndex：寻找第c列的非零首元的起始行数
			for (size_t c = 0, RIndex = 0; c < min; ++c) {
				bool flag = false;
				// for：从RIndex行开始向后面的行寻找非零行
				for (size_t r = RIndex; r < dst._rows; ++r) {
					// for：从第c列开始向后面的列寻找第r行是否存在非零元
					for (size_t i = c; i < dst._cols; ++i) {
						if (dst._data[r][i] != 0) {
							// 找到了就交换此列与第c列
							dst.ColSwap(i, c);
							// 消元
							dst.ColPivot(r, c, right);
							RIndex = r + 1;
							flag = true;
							break;
						}
					}
					if (flag) break;
				}
			}
			return dst;
		}

		/******************************************************************************************
		* 行最简型
		******************************************************************************************/
		Matrix<ElemType> RowSimplest() const {
			Matrix<ElemType> dst(*this);
			// min：化简后最多有min(dst._rows, dst._cols)个非零行
			size_t min = dst._rows < dst._cols ? dst._rows : dst._cols;
			// CIndex：寻找第r行的非零首元的起始行数
			for (size_t r = 0, CIndex = 0; r < min; ++r) {
				bool flag = false;
				// for：从CIndex列开始向后面的列寻找非零列
				for (size_t c = CIndex; c < dst._cols; ++c) {
					// for：从第r行开始向后面的行寻找第c列是否存在非零元
					for (size_t i = r; i < dst._rows; ++i) {
						if (dst._data[i][c] != 0) {
							// 找到了就交换此行与第r行
							dst.RowSwap(i, r);
							// 消元
							dst.RowPivot(r, c, all);
							// 归一
							dst.RowScale(r, 1 / dst._data[r][c]);
							CIndex = c + 1;
							flag = true;
							break;
						}
					}
					if (flag) break;
				}
			}
			return dst;
		}

		/******************************************************************************************
		* 列最简型
		******************************************************************************************/
		Matrix<ElemType> ColSimplest() const {
			Matrix<ElemType> dst(*this);

			/*dst = dst.transpose();
			dst = dst.RowSimplest();
			dst = dst.transpose();*/

			// min：化简后最多有min(dst._rows, dst._cols)个非零列
			size_t min = dst._rows < dst._cols ? dst._rows : dst._cols;
			// RIndex：寻找第c列的非零首元的起始行数
			for (size_t c = 0, RIndex = 0; c < min; ++c) {
				bool flag = false;
				// for：从RIndex行开始向后面的行寻找非零行
				for (size_t r = RIndex; r < dst._rows; ++r) {
					// for：从第c列开始向后面的列寻找第r行是否存在非零元
					for (size_t i = c; i < dst._cols; ++i) {
						if (dst._data[r][i] != 0) {
							// 找到了就交换此列与第c列
							dst.ColSwap(i, c);
							// 消元
							dst.ColPivot(r, c, all);
							// 归一
							dst.ColScale(c, 1 / dst._data[r][c]);
							RIndex = r + 1;
							flag = true;
							break;
						}
					}
					if (flag) break;
				}
			}

			return dst;
		}

		/******************************************************************************************
		* 获取余子式矩阵
		******************************************************************************************/
		Matrix<ElemType> CofactorMatrix(size_t const& row, size_t const& col) const {
			if (row > MBE::_rows || col > MBE::_cols)
				throw "Error: Index out of range | in CofactorMatrix(size_t const& row, size_t const& col) const";

			if (MBE::_rows == 1) return Matrix<ElemType>(*this);

			Matrix<ElemType> cofactor(MBE::_rows - 1, MBE::_cols - 1);
			for (size_t r = 0, RIndex = 0; r < MBE::_rows; ++r, ++RIndex) {
				if (r == row) continue;
				size_t CIndex = 0;

				for (size_t c = 0; c < MBE::_cols; ++c) {
					if (c == col) continue;
					cofactor._data[RIndex][CIndex++] = MBE::_data[r][c];
				}

			}

			return cofactor;
		}

		/******************************************************************************************
		* 计算代数余子式
		******************************************************************************************/
		ElemType CofactorAlgebraic(Matrix<ElemType>& mat, size_t const& sum_of_row_col) const {
			ElemType sign = -1;
			if (sum_of_row_col % 2 == 0) sign = 1;
			if (mat._rows == 1) return mat._DataBase[0] * sign;
			ElemType sum = 0;

			// 按第一行展开
			for (size_t i = 0; i < mat._cols; ++i) {
				Matrix<ElemType> cofactor = mat.CofactorMatrix(0, i);
				// 计算(0, i)的代数余子式
				sum += mat._DataBase[i] * CofactorAlgebraic(cofactor, i);
			}
			return sum * sign;
		}

		/******************************************************************************************
		* 计算行列式
		******************************************************************************************/
		ElemType det(int const& mode = 0) const {
			assert(MBE::_rows == MBE::_cols);

			Matrix<ElemType> tmp(*this);
			ElemType determinant;
			size_t min = tmp._rows < tmp._cols ? tmp._rows : tmp._cols, count = 0;
			switch (mode) {
			case 0:
				determinant = 1;
				for (size_t r = 0, CIndex = 0; r < min; ++r) {
					bool flag = false;
					for (size_t c = CIndex; c < tmp._cols; ++c) {
						for (size_t i = r; i < tmp._rows; ++i) {
							if (tmp._data[i][c] != 0) {
								tmp.RowSwap(i, r);
								tmp.RowPivot(r, c, down);
								CIndex = c + 1;
								if (i != r) ++count;
								flag = true;
								break;
							}
						}
						if (flag) break;
					}
				}

				for (size_t i = 0; i < tmp._rows; ++i)
					determinant *= tmp._data[i][i];

				determinant *= (count % 2 == 1 ? -1 : 1);

				break;
			case 1:
				if (tmp._rows == 1) {
					determinant = tmp._data[0][0];
					break;
				}
				determinant = 0;

				// 按第一行展开
				for (size_t i = 0; i < tmp._rows; ++i) {
					Matrix<ElemType> cofactor = tmp.CofactorMatrix(0, i);
					// 计算(0, i)的代数余子式
					determinant += tmp._data[0][i] * CofactorAlgebraic(cofactor, i);
				}

				break;
			default:
				throw "Error: Mode does not exist | in ElemType det(int const mode = 1) const ";
			}
			return determinant;
		}

		/******************************************************************************************
		* 连接两个矩阵 direction = true : horizontal 横向拼接 | direction = false : vertical 纵向拼接
		******************************************************************************************/
		static Matrix<ElemType> concatenate(Matrix<ElemType> const& mat1, Matrix<ElemType> const& mat2, bool const& direction = true) {
			if (direction) {
				// 横向拼接
				// 错误：两个矩阵行数不等
				assert(mat1._rows == mat2._rows);

				Matrix<ElemType> dst(mat1._rows, mat1._cols + mat2._cols);
				for (size_t r = 0; r < mat1._rows; ++r) {
					memcpy(dst._data[r], mat1._data[r], mat1._cols * sizeof(ElemType));
					memcpy(dst._data[r] + mat1._cols, mat2._data[r], mat2._cols * sizeof(ElemType));
					/*for (size_t c = 0; c < mat1._cols; ++c)
						dst._data[r][c] = mat1._data[r][c];
					for (size_t c = mat1._cols; c < mat1._cols + mat2._cols; ++c)
						dst._data[r][c] = mat2._data[r][c - mat1._cols];*/
				}
				return dst;
			} else {
				// 纵向拼接
				// 错误：两个矩阵列数不等
				assert(mat1._cols == mat2._cols);

				Matrix<ElemType> dst(mat1._rows + mat2._rows, mat1._cols);
				memcpy(dst._DataBase, mat1._DataBase, mat1._size * sizeof(ElemType));
				memcpy(dst._DataBase + mat1._size, mat2._DataBase, mat2._size * sizeof(ElemType));

				return dst;
			}
		}

		/******************************************************************************************
		* 获取子矩阵
		******************************************************************************************/
		Matrix<ElemType> subLAM(size_t const& StartRow, size_t const& EndRow, size_t const& StartCol, size_t const& EndCol) const {
			// 错误：越界
			assert(EndRow < MBE::_rows && StartRow < EndRow && EndCol < MBE::_cols && StartCol < EndCol);

			Matrix<ElemType> dst(EndRow - StartRow + 1, EndCol - StartCol + 1);
			// 剪切矩阵
			for (size_t r = StartRow; r <= EndRow; ++r)
				for (size_t c = StartCol; c <= EndCol; ++c)
					dst._data[r - StartRow][c - StartCol] = MBE::_data[r][c];

			return dst;
		}

		/******************************************************************************************
		* 转置
		******************************************************************************************/
		Matrix<ElemType> transpose() const {
			Matrix<ElemType> dst(MBE::_cols, MBE::_rows);
			for (size_t r = 0; r < dst._rows; ++r)
				for (size_t c = 0; c < dst._cols; ++c)
					dst._data[r][c] = MBE::_data[c][r];

			return dst;
		}

		/******************************************************************************************
		* 计算矩阵的秩
		******************************************************************************************/
		size_t rank() const {
			Matrix<ElemType> dst(*this);
			// min：化简后最多有min(dst._rows, dst._cols)个非零行
			size_t min = dst._rows < dst._cols ? dst._rows : dst._cols, rank = 0;
			// CIndex：寻找第r行的非零首元的起始行数
			for (size_t r = 0, CIndex = 0; r < min; ++r) {
				bool flag = false;
				// for：从CIndex列开始向后面的列寻找非零列
				for (size_t c = CIndex; c < dst._cols; ++c) {
					// for：从第r行开始向后面的行寻找第c列是否存在非零元
					for (size_t i = r; i < dst._rows; ++i) {
						if (dst._data[i][c] != 0) {
							// 找到了就交换此行与第r行
							dst.RowSwap(i, r);
							// 消元
							dst.RowPivot(r, c, down);
							CIndex = c + 1;
							// 找到说明最后的行阶梯型非零行+1
							++rank;
							flag = true;
							break;
						}
					}
					if (flag) break;
				}
			}
			return rank;
		}

		/******************************************************************************************
		* 计算矩阵的迹
		******************************************************************************************/
		ElemType tr() const {
			assert(MBE::_rows == MBE::_cols);

			ElemType tr = 0;
			for (size_t i = 0; i < MBE::_rows; ++i) tr += MBE::_data[i][i];

			return tr;
		}

		/******************************************************************************************
		* 计算逆矩阵
		******************************************************************************************/
		Matrix<ElemType> inverse() const {
			// 错误：矩阵不可逆
			assert(this->det() != 0);
			return concatenate(*this, Matrix<ElemType>(MBE::_rows, MBE::_cols, 1, true)).RowSimplest().subLAM(0, MBE::_rows - 1, MBE::_cols, MBE::_cols * 2 - 1);
		}

		/******************************************************************************************
		* 计算伴随矩阵
		******************************************************************************************/
		Matrix<ElemType> adjoint() const {
			ElemType det = this->det();
			Matrix<ElemType> dst(MBE::_rows, MBE::_cols);
			if (det == 0) {
				std::cout << "\n" << "definition method" << "\n";
				for (size_t r = 0; r < dst._rows; ++r)
					for (size_t c = 0; c < dst._cols; ++c)
						dst._data[r][c] = dst.CofactorAlgebraic(MBE::CofactorMatrix(r, c), r + c);

				dst = dst.transpose();
			} else {
				std::cout << "\n" << "inverse method" << "\n";
				dst = MBE::inverse() * det;
			}
			return dst;
		}

		/******************************************************************************************
		* 施密特正交化
		******************************************************************************************/
		Matrix<ElemType> orthogonalize() const {
			// Error: ElemTypehis is not a full rank LAM
			assert(MBE::rank() >= (MBE::_rows < MBE::_cols ? MBE::_rows : MBE::_cols));

			Matrix<ElemType> self(*this);
			vector<Matrix<ElemType>> beta;

			beta.push_back(self.subLAM(0, self._rows - 1, 0, 0));

			for (size_t c = 1; c < MBE::_cols; ++c) {
				Matrix<ElemType> tmp1(self.subLAM(0, self._rows - 1, c, c)), tmp2(tmp1);

				for (size_t i = 0; i < c; ++i)
					tmp1 -= beta[i] * ((beta[i].transpose() * tmp2)._data[0][0] / (beta[i].transpose() * beta[i])._data[0][0]);

				beta.push_back(tmp1);
			}
			Matrix<ElemType> dst(beta[0]);

			for (size_t c = 1; c < MBE::_cols; ++c) dst = concatenate(dst, beta[c]);

			return dst;
		}

		//*****************************************************************************************
		// 重载 << 
		friend std::ostream& operator << (std::ostream& os, Matrix<ElemType> const& mat) {
			os << '[';
			for (size_t r = 0; r < mat._rows; ++r) {
				if (r != 0) os << " ";

				os << mat._data[r][0];

				for (size_t c = 1; c < mat._cols; ++c) os << ' ' << mat._data[r][c];

				if (r == mat._rows - 1)os << ']';

				os << "\n";
			}
			os << "{LAM<" << typeid(ElemType).name() << "> | rows = " << mat._rows << " | cols = " << mat._cols << "}";
			return os;
		}

		//*****************************************************************************************
		// 重载 this = ElemType
		Matrix<ElemType>& operator = (const ElemType& value) {
			assert(MBE::_rows == MBE::_cols);
			memset(MBE::_DataBase, 0x00, MBE::_size * sizeof(ElemType));
			for (size_t i = 0; i < MBE::_rows; ++i) MBE::_data[i][i] = value;
			return *this;
		}

		//*****************************************************************************************
		// 重载 ==
		// 重载 this == LAM
		bool operator == (Matrix<ElemType> const& mat) const {
			if (MBE::_rows != mat._rows || MBE::_cols != mat._cols) return false;
			for (size_t i = 0; i < MBE::_size; ++i)
				if (MBE::_DataBase[i] != mat._DataBase[i])
					return false;
			return true;
		}

		//*****************************************************************************************
		// 重载 +
		// 重载 this + LAM
		Matrix<ElemType> operator + (Matrix<ElemType> const& mat) const {
			Matrix<ElemType> dst(mat);
			
			for (size_t i = 0; i < dst._size; ++i)
				dst._DataBase[i] += MBE::_DataBase[i];

			return dst;
		}

		// 重载 this + ElemType
		Matrix<ElemType> operator + (const ElemType& value) const {
			Matrix<ElemType> dst(*this);
			for (auto i = 0; i < dst._rows; ++i)
				dst._data[i][i] = dst._data[i][i] + value;

			return dst;
		}

		//*****************************************************************************************
		// 重载 -
		// 重载 this - LAM
		Matrix<ElemType> operator - (Matrix<ElemType> const& mat) const {
			Matrix<ElemType> dst(*this);
			for (size_t r = 0; r < dst._rows; ++r)
				for (size_t c = 0; c < dst._cols; ++c)
					dst._data[r][c] = dst._data[r][c] - mat._data[r][c];

			return dst;
		}

		// 重载 this - ElemType
		Matrix<ElemType> operator - (const ElemType& value) const {
			assert(MBE::_rows == mat._rows && MBE::_cols == mat._cols);

			Matrix<ElemType> dst(*this);
			for (size_t i = 0; i < dst._rows; ++i)
				dst._data[i][i] = dst._data[i][i] - value;

			return dst;
		}

		//*****************************************************************************************
		// 重载 *
		// 重载 this * Matrix
		Matrix<ElemType> operator * (Matrix<ElemType> const& mat) const {
			assert(MBE::_cols == mat._rows);

			Matrix<ElemType> dst(MBE::_rows, mat._cols, 0, true);
			for (size_t r = 0; r < dst._rows; ++r)
				for (size_t c = 0; c < dst._cols; ++c)
					for (size_t i = 0; i < MBE::_cols; ++i)
						dst._data[r][c] = dst._data[r][c] + MBE::_data[r][i] * mat._data[i][c];

			return dst;
		}

		// 重载 this * ElemType
		Matrix<ElemType> operator * (const ElemType& a) const {
			assert(MBE::_cols == mat._rows);

			Matrix<ElemType> dst(*this);
			for (size_t r = 0; r < dst._rows; ++r)
				for (size_t c = 0; c < dst._cols; ++c)
					dst._data[r][c] = dst._data[r][c] * a;

			return dst;
		}

		//*****************************************************************************************
		// 重载 /
		// 重载 this / Matrix
		Matrix<ElemType> operator / (Matrix<ElemType> const& mat) const {
			return *this * mat.inverse();
		}

		// 重载 this / ElemType
		Matrix<ElemType> operator / (const ElemType& value) const {
			assert(value != 0);

			Matrix<ElemType> dst(*this);
			for (size_t i = 0; i < dst._size; ++i)
				dst._data[i] = dst._data[i] / value;

			return dst;
		}

		//*****************************************************************************************

	};


}
