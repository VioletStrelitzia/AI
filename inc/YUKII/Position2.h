#pragma once
#include "core.h"

namespace yuki::atri {
/**
 * @brief 二维整型向量类
 * 
 */
class Vector2 {
public:
    i32 r;  ///< 行数据
    i32 c;  ///< 列数据

public:
    /**
     * @brief Construct a new Vector 2 object
     * 
     */
    Vector2() = default;

    /**
     * @brief Destroy the Vector 2 object
     * 
     */
    ~Vector2() = default;

    /**
     * @brief Construct a new Vector 2 object
     * 
     * @param r 行
     * @param c 列
     */
    Vector2(i32 const& r, i32 const& c);

    /**
     * @brief 重载 + 运算
     * 
     * @param other 另一个向量
     * @return Vector2 两个向量的和
     */
    Vector2 operator + (Vector2 const& other);

    /**
     * @brief 重载 + 运算
     * 
     * @param other 另一个向量
     * @return Vector2 两个向量的差
     */
    Vector2 operator - (Vector2 const& other);

    /**
     * @brief 重载 == 运算
     * 
     * @param other 另一个向量
     * @return bool 两个向量是否相等
     * @retval 1 两个向量相等
     * @retval 0 两个向量不相等
     */
    bool operator == (Vector2 const& other) const;

    /**
     * @brief 重载 ！= 运算
     * 
     * @param other 另一个向量
     * @return bool 两个向量是否不相等
     * @retval 1 两个向量不相等
     * @retval 0 两个向量相等
     */
    bool operator != (Vector2 const& other) const;
};
}