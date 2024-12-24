#pragma once
#include "core.h"

namespace yuki {
const i32 DYNAMIC = 0;

enum FlipMode {
    AR180 = 0,	///< 右转180°
    AR90,		///< 右转90°
    AL90		///< 左转90°
};

/**
 * @brief 矩阵基类
 * 
 * @tparam Derived 
 */
template <typename Derived>
class MatrixBase {
public:
    /**
     * @brief 获取矩阵 (row, col) 位置的元素的值
     * 
     * @param row 行索引
     * @param col 列索引
     * @return Derived::Scalar 元素
     */
    auto operator () (i32 const& row, i32 const& col) const {
        return static_cast<Derived const&>(*this).atImpl(row, col);
    }

    /**
     * @brief 获取矩阵 (row, col) 位置的元素的引用
     * 
     * @param row 行索引
     * @param col 列索引
     * @return Derived::Scalar& 元素
     */
    auto& operator () (i32 const& row, i32 const& col) {
        return static_cast<Derived&>(*this).atImpl(row, col);
    }

    /**
     * @brief 获取矩阵一维索引 idx 位置的元素的值
     * 
     * @param idx 一维索引
     * @return Derived::Scalar 元素
     */
    auto operator () (i32 const& idx) const {
        return static_cast<Derived const&>(*this).atImpl(idx);
    }

    /**
     * @brief 获取矩阵一维索引 idx 位置的元素的引用
     * 
     * @param idx 一维索引
     * @return Derived::Scalar& 元素
     */
    auto& operator () (i32 const& idx) {
        return static_cast<Derived&>(*this).atImpl(idx);
    }

    /**
     * @brief 获取矩阵行数
     * 
     * @return i32 矩阵行数
     */
    auto rows() const -> i32 {
        return static_cast<Derived const&>(*this).rowsImpl();
    }
    
    /**
     * @brief 获取矩阵列数
     * 
     * @return i32 矩阵列数
     */
    auto cols() const -> i32 {
        return static_cast<Derived const&>(*this).colsImpl();
    }

    /**
     * @brief 获取矩阵容量
     * 
     * @return i32 矩阵容量
     */
    auto capacity() const -> i32 {
        return static_cast<Derived const&>(*this).capacityImpl();
    }

    /**
     * @brief 获取矩阵大小
     * 
     * @return i32 矩阵大小
     */
    auto size() const -> i32 {
        return static_cast<Derived const&>(*this).sizeImpl();
    }

    auto push_back(auto const& val) {
        return static_cast<Derived&>(*this).push_backImpl(val);
    }

    auto push_back(auto&& val) {
        return static_cast<Derived&>(*this).push_backImpl(val);
    }

    auto back() {
        return static_cast<Derived&>(*this).backImpl();
    }

    auto back() const {
        return static_cast<Derived const&>(*this).backImpl();
    }

    auto begin() {
        return static_cast<Derived&>(*this).beginImpl();
    }

    auto cbegin() const {
        return static_cast<Derived const&>(*this).cbeginImpl();
    }

    auto end() {
        return static_cast<Derived&>(*this).endImpl();
    }

    auto cend() const {
        return static_cast<Derived const&>(*this).cendImpl();
    }

    template <typename _Derived>
    auto operator + (MatrixBase<_Derived> const& other) const {
        cout << "base plus called\n";
        return static_cast<Derived const&>(*this).plus(static_cast<_Derived const&>(other));
    }

    template <typename _Derived>
    auto operator += (MatrixBase<_Derived> const& other) {
        cout << "base sub equal called\n";
        return static_cast<Derived&>(*this).plusEqual(static_cast<_Derived const&>(other));
    }

    template <typename _Derived>
    auto operator - (MatrixBase<_Derived> const& other) const {
        cout << "base sub called\n";
        return static_cast<Derived const&>(*this).sub(static_cast<_Derived const&>(other));
    }

    template <typename _Derived>
    auto operator -= (MatrixBase<_Derived> const& other) {
        cout << "base sub equal called\n";
        return static_cast<Derived&>(*this).subEqual(static_cast<_Derived const&>(other));
    }

    template <typename _Derived>
    auto operator * (MatrixBase<_Derived> const& other) const {
        cout << "base mult called\n";
        return static_cast<Derived const&>(*this).mult(static_cast<_Derived const&>(other));
    }

    template <typename Derived>
    friend auto operator << (ostream& os, MatrixBase<Derived> const& mat) -> ostream&;
};

}