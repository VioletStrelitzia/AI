#pragma once

// @generated by torchgen/gen.py from Operator.h

#include <tuple>
#include <vector>

// Forward declarations of any types needed in the operator signatures.
// We can't directly include these classes because it will cause circular include dependencies.
// This file is included by TensorBody.h, which defines the Tensor class.
#include <ATen/core/ATen_fwd.h>

namespace at {
namespace _ops {


struct TORCH_API div_Tensor {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::div";
  static constexpr const char* overload_name = "Tensor";
  static constexpr const char* schema_str = "div.Tensor(Tensor self, Tensor other) -> Tensor";
  static at::Tensor call(const at::Tensor & self, const at::Tensor & other);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & other);
};

struct TORCH_API div__Tensor {
  using schema = at::Tensor & (at::Tensor &, const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::div_";
  static constexpr const char* overload_name = "Tensor";
  static constexpr const char* schema_str = "div_.Tensor(Tensor(a!) self, Tensor other) -> Tensor(a!)";
  static at::Tensor & call(at::Tensor & self, const at::Tensor & other);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, at::Tensor & self, const at::Tensor & other);
};

struct TORCH_API div_out {
  using schema = at::Tensor & (const at::Tensor &, const at::Tensor &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::div";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "div.out(Tensor self, Tensor other, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, const at::Tensor & other, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & other, at::Tensor & out);
};

struct TORCH_API div_Tensor_mode {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &, ::std::optional<c10::string_view>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::div";
  static constexpr const char* overload_name = "Tensor_mode";
  static constexpr const char* schema_str = "div.Tensor_mode(Tensor self, Tensor other, *, str? rounding_mode) -> Tensor";
  static at::Tensor call(const at::Tensor & self, const at::Tensor & other, ::std::optional<c10::string_view> rounding_mode);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & other, ::std::optional<c10::string_view> rounding_mode);
};

struct TORCH_API div__Tensor_mode {
  using schema = at::Tensor & (at::Tensor &, const at::Tensor &, ::std::optional<c10::string_view>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::div_";
  static constexpr const char* overload_name = "Tensor_mode";
  static constexpr const char* schema_str = "div_.Tensor_mode(Tensor(a!) self, Tensor other, *, str? rounding_mode) -> Tensor(a!)";
  static at::Tensor & call(at::Tensor & self, const at::Tensor & other, ::std::optional<c10::string_view> rounding_mode);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, at::Tensor & self, const at::Tensor & other, ::std::optional<c10::string_view> rounding_mode);
};

struct TORCH_API div_out_mode {
  using schema = at::Tensor & (const at::Tensor &, const at::Tensor &, ::std::optional<c10::string_view>, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::div";
  static constexpr const char* overload_name = "out_mode";
  static constexpr const char* schema_str = "div.out_mode(Tensor self, Tensor other, *, str? rounding_mode, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, const at::Tensor & other, ::std::optional<c10::string_view> rounding_mode, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & other, ::std::optional<c10::string_view> rounding_mode, at::Tensor & out);
};

struct TORCH_API div_Scalar {
  using schema = at::Tensor (const at::Tensor &, const at::Scalar &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::div";
  static constexpr const char* overload_name = "Scalar";
  static constexpr const char* schema_str = "div.Scalar(Tensor self, Scalar other) -> Tensor";
  static at::Tensor call(const at::Tensor & self, const at::Scalar & other);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Scalar & other);
};

struct TORCH_API div__Scalar {
  using schema = at::Tensor & (at::Tensor &, const at::Scalar &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::div_";
  static constexpr const char* overload_name = "Scalar";
  static constexpr const char* schema_str = "div_.Scalar(Tensor(a!) self, Scalar other) -> Tensor(a!)";
  static at::Tensor & call(at::Tensor & self, const at::Scalar & other);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, at::Tensor & self, const at::Scalar & other);
};

struct TORCH_API div_Scalar_mode {
  using schema = at::Tensor (const at::Tensor &, const at::Scalar &, ::std::optional<c10::string_view>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::div";
  static constexpr const char* overload_name = "Scalar_mode";
  static constexpr const char* schema_str = "div.Scalar_mode(Tensor self, Scalar other, *, str? rounding_mode) -> Tensor";
  static at::Tensor call(const at::Tensor & self, const at::Scalar & other, ::std::optional<c10::string_view> rounding_mode);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Scalar & other, ::std::optional<c10::string_view> rounding_mode);
};

struct TORCH_API div__Scalar_mode {
  using schema = at::Tensor & (at::Tensor &, const at::Scalar &, ::std::optional<c10::string_view>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::div_";
  static constexpr const char* overload_name = "Scalar_mode";
  static constexpr const char* schema_str = "div_.Scalar_mode(Tensor(a!) self, Scalar other, *, str? rounding_mode) -> Tensor(a!)";
  static at::Tensor & call(at::Tensor & self, const at::Scalar & other, ::std::optional<c10::string_view> rounding_mode);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, at::Tensor & self, const at::Scalar & other, ::std::optional<c10::string_view> rounding_mode);
};

struct TORCH_API div_Scalar_out {
  using schema = at::Tensor & (const at::Tensor &, const at::Scalar &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::div";
  static constexpr const char* overload_name = "Scalar_out";
  static constexpr const char* schema_str = "div.Scalar_out(Tensor self, Scalar other, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, const at::Scalar & other, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Scalar & other, at::Tensor & out);
};

struct TORCH_API div_Scalar_mode_out {
  using schema = at::Tensor & (const at::Tensor &, const at::Scalar &, ::std::optional<c10::string_view>, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::div";
  static constexpr const char* overload_name = "Scalar_mode_out";
  static constexpr const char* schema_str = "div.Scalar_mode_out(Tensor self, Scalar other, *, str? rounding_mode, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, const at::Scalar & other, ::std::optional<c10::string_view> rounding_mode, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Scalar & other, ::std::optional<c10::string_view> rounding_mode, at::Tensor & out);
};

}} // namespace at::_ops
