#include "MatrixBase.h"

namespace yuki {

template <typename ElemType, i32 RowsAtCompileTime, i32 ColsAtCompileTime>
class Matrix;

template <typename ElemType, i32 RowsAtCompileTime1, i32 ColsAtCompileTime1, i32 RowsAtCompileTime2, i32 ColsAtCompileTime2>
using DstMat = Matrix<ElemType,
    (RowsAtCompileTime1 != DYNAMIC && RowsAtCompileTime2 != DYNAMIC) ? RowsAtCompileTime1 : DYNAMIC,
    (ColsAtCompileTime1 != DYNAMIC && ColsAtCompileTime2 != DYNAMIC) ? ColsAtCompileTime1 : DYNAMIC>;

template <typename ElemType, i32 RowsAtCompileTime1, i32 ColsAtCompileTime1, i32 RowsAtCompileTime2, i32 ColsAtCompileTime2>
using MultDstMat = Matrix<ElemType, RowsAtCompileTime1, ColsAtCompileTime2>;

template <typename ElemType, i32 RowsAtCompileTime = DYNAMIC, i32 ColsAtCompileTime = DYNAMIC>
class Matrix: public Matrix<Matrix<ElemType, RowsAtCompileTime, ColsAtCompileTime>> {
private:
    using Self = Matrix<ElemType, RowsAtCompileTime, ColsAtCompileTime>;
    friend Matrix<Self>;

protected:
    i32 _rows;
    i32 _cols;
    vector<ElemType> _data;

public:
    using Scalar = ElemType;
    using iterator = vector<ElemType>::iterator;
    using const_iterator = vector<ElemType>::const_iterator;

    Matrix():
        _rows(RowsAtCompileTime),
        _cols(ColsAtCompileTime),
        _data(RowsAtCompileTime * ColsAtCompileTime) {}

    Matrix(i32 const& rows, i32 const& cols):
        _rows(RowsAtCompileTime == DYNAMIC ? rows : RowsAtCompileTime),
        _cols(ColsAtCompileTime == DYNAMIC ? cols : ColsAtCompileTime),
        _data(_rows * _cols) {}

    Matrix(i32 const& rows, i32 const& cols, vector<ElemType> const& data):
        _rows(rows), _cols(cols), _data(data) {}

    ~Matrix() = default;

    operator Matrix<ElemType, DYNAMIC, DYNAMIC>() {
        cout << "operator Matrix<ElemType, DYNAMIC, DYNAMIC>\n";
        return Matrix<ElemType, DYNAMIC, DYNAMIC>(_rows, _cols, _data);
    }


private:
    auto rowsImpl() const -> i32 {
        return _rows;
    }

    auto colsImpl() const -> i32 {
        return _cols;
    }

    auto capacityImpl() const -> i32 {
        return static_cast<i32>(_data.capacity());
    }

    auto sizeImpl() const -> i32 {
        return static_cast<i32>(_data.size());
    }

public:
    auto push_backImpl(ElemType const& val) -> void {
        if constexpr (RowsAtCompileTime == DYNAMIC && ColsAtCompileTime == 1) {
            ++_rows;
            _data.push_back(val);
        } else if constexpr (RowsAtCompileTime == 1 && ColsAtCompileTime == DYNAMIC) {
            ++_cols;
            _data.push_back(val);
        }
    }

    auto push_backImpl(ElemType&& val) -> void {
        if constexpr (RowsAtCompileTime == DYNAMIC && ColsAtCompileTime == 1) {
            ++_rows;
            _data.emplace_back(val);
        } else if constexpr (RowsAtCompileTime == 1 && ColsAtCompileTime == DYNAMIC) {
            ++_cols;
            _data.emplace_back(val);
        }
    }

    auto backImpl() -> ElemType& {
        return _data.back();
    }

    auto backImpl() const -> ElemType const& {
        return _data.back();
    }

    auto beginImpl() -> iterator {
        return _data.begin();
    }

    auto cbeginImpl() const -> const_iterator {
        return _data.cbegin();
    }

    auto endImpl() -> iterator {
        return _data.end();
    }

    auto cendImpl() const -> const_iterator {
        return _data.cend();
    }

    auto atImpl(i32 const& row, i32 const& col) const -> ElemType {
        return _data[index(row, col)];
    }

    auto atImpl(i32 const& row, i32 const& col) -> ElemType& {
        return _data[index(row, col)];
    }

    auto atImpl(i32 const& idx) const -> ElemType {
        return _data[idx];
    }

    auto atImpl(i32 const& idx) -> ElemType& {
        return _data[idx];
    }

    auto index(i32 const& row, i32 const& col) const -> i32 {
        if constexpr (RowsAtCompileTime == 1) {
            return col;
        } else if constexpr (ColsAtCompileTime == 1) {
            return row;
        } else if constexpr (RowsAtCompileTime == DYNAMIC && ColsAtCompileTime != DYNAMIC) {
            return row * ColsAtCompileTime + col;
        } else if constexpr (RowsAtCompileTime != DYNAMIC && ColsAtCompileTime == DYNAMIC) {
            return col * RowsAtCompileTime + row;
        } else {
            return row * _cols + col;
        }
    }

    auto reshape(i32 const& rows, i32 const& cols) -> Matrix& {
        if constexpr (RowsAtCompileTime == DYNAMIC) {
            _rows = rows;
        }
        if constexpr (ColsAtCompileTime == DYNAMIC) {
            _cols = cols;
        }
        _data.resize(_rows * _cols);
        return *this;
    }

    auto flip(FlipMode const& mode) -> Matrix& {
        return *this;
    }

    template <typename ElemType, i32 RowsAtCompileTime, i32 ColsAtCompileTime>
    friend auto operator << (ostream& os, Matrix<ElemType, RowsAtCompileTime, ColsAtCompileTime> const& mat) -> ostream&;

    template <i32 _RowsAtCompileTime, i32 _ColsAtCompileTime>
    auto plus(Matrix<ElemType, _RowsAtCompileTime, _ColsAtCompileTime> const& other) const ->
        DstMat<ElemType, RowsAtCompileTime, ColsAtCompileTime, _RowsAtCompileTime, _ColsAtCompileTime> {
        #ifdef DEBUG
        if (_rows != other.rows() || _cols != other.cols()) {
            throw dflt::DimensionMismatch();
        }
        #endif
        DstMat<ElemType, RowsAtCompileTime, ColsAtCompileTime, _RowsAtCompileTime, _ColsAtCompileTime>
            dst(_rows, _cols);
        for (i32 i = 0, end = static_cast<i32>(_data.size()); i < end; ++i) {
            dst(i) = _data[i] + other(i);
        }
        return dst;
    }

    template <i32 _RowsAtCompileTime, i32 _ColsAtCompileTime>
    auto plusEqual(Matrix<ElemType, _RowsAtCompileTime, _ColsAtCompileTime> const& other) -> Matrix& {
        #ifdef DEBUG
        if (_rows != other.rows() || _cols != other.cols()) {
            throw dflt::DimensionMismatch();
        }
        #endif
        for (i32 i = 0, end = static_cast<i32>(_data.size()); i < end; ++i) {
            _data[i] += other(i);
        }
        return *this;
    }

    template <i32 _RowsAtCompileTime, i32 _ColsAtCompileTime>
    auto sub(Matrix<ElemType, _RowsAtCompileTime, _ColsAtCompileTime> const& other) const ->
        DstMat<ElemType, RowsAtCompileTime, ColsAtCompileTime, _RowsAtCompileTime, _ColsAtCompileTime> {
        #ifdef DEBUG
        if (_rows != other.rows() || _cols != other.cols()) {
            throw dflt::DimensionMismatch();
        }
        #endif
        DstMat<ElemType, RowsAtCompileTime, ColsAtCompileTime, _RowsAtCompileTime, _ColsAtCompileTime>
            dst(_rows, _cols);
        for (i32 i = 0, end = static_cast<i32>(_data.size()); i < end; ++i) {
            dst(i) = _data[i] - other(i);
        }
        return dst;
    }

    template <i32 _RowsAtCompileTime, i32 _ColsAtCompileTime>
    auto subEqual(Matrix<ElemType, _RowsAtCompileTime, _ColsAtCompileTime> const& other) -> Matrix& {
        #ifdef DEBUG
        if (_rows != other.rows() || _cols != other.cols()) {
            throw dflt::DimensionMismatch();
        }
        #endif
        for (i32 i = 0, end = static_cast<i32>(_data.size()); i < end; ++i) {
            _data[i] -= other(i);
        }
        return *this;
    }

    template <i32 _RowsAtCompileTime, i32 _ColsAtCompileTime>
    auto mult(Matrix<ElemType, _RowsAtCompileTime, _ColsAtCompileTime> const& other) const ->
        DstMat<ElemType, RowsAtCompileTime, ColsAtCompileTime, _RowsAtCompileTime, _ColsAtCompileTime> {
        #ifdef DEBUG
        if (_cols != other.rows()) {
            throw dflt::DimensionMismatch();
        }
        #endif
        Matrix<ElemType, RowsAtCompileTime, _ColsAtCompileTime> dst(_rows, other.cols());
        for (i32 r = 0; r < _rows; ++r) {
            for (i32 c = 0; c < other.cols(); ++c) {
                ElemType temp = atImpl(r, 0) * other(0, c);
                for (i32 i = 1; i < _cols; ++i) {
                    temp += atImpl(r, i) * other(i, c);
                }
                dst(r, c) = temp;
            }
        }
        return dst;
    }

    auto coutImpl(ostream& os) const -> ostream& {
        for (i32 r = 0; r < _rows; ++r) {
            for (i32 c = 0; c < _cols; ++c) {
                os << std::setw(6) << std::left << _data[index(r, c)] << ' ';
            }
            os << "\b\n";
        }
        os << "[ " << typeid(Matrix<ElemType, RowsAtCompileTime, ColsAtCompileTime>).name() << " ]";
        return os;
    }
    
};

template <typename ElemType, i32 RowsAtCompileTime, i32 ColsAtCompileTime>
auto operator << (ostream& os, Matrix<ElemType, RowsAtCompileTime, ColsAtCompileTime> const& mat) -> ostream& {
    for (i32 r = 0; r < mat._rows; ++r) {
        for (i32 c = 0; c < mat._cols; ++c) {
            os << std::setw(6) << std::left << mat(r, c) << ' ';
        }
        os << "\b\n";
    }
    os << "[ " << typeid(Matrix<ElemType, RowsAtCompileTime, ColsAtCompileTime>).name() << " ]";
    return os;
}

template <typename Derived>
auto operator << (ostream& os, Matrix<Derived> const& mat) -> ostream& {
    return static_cast<Derived const&>(mat).coutImpl(os);
}

using Vector3d = Matrix<f64, 3, 1>;
using Vector3f = Matrix<f32, 3, 1>;
using VectorXd = Matrix<f64, DYNAMIC, 1>;

using MatrixXd = Matrix<f64, DYNAMIC, DYNAMIC>;
}