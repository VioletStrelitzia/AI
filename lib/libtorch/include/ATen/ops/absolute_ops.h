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


struct TORCH_API absolute {
  using schema = at::Tensor (const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::absolute";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "absolute(Tensor self) -> Tensor";
  static at::Tensor call(const at::Tensor & self);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self);
};

struct TORCH_API absolute_ {
  using schema = at::Tensor & (at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::absolute_";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "absolute_(Tensor(a!) self) -> Tensor(a!)";
  static at::Tensor & call(at::Tensor & self);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, at::Tensor & self);
};

struct TORCH_API absolute_out {
  using schema = at::Tensor & (const at::Tensor &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::absolute";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "absolute.out(Tensor self, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, at::Tensor & out);
};

}} // namespace at::_ops
