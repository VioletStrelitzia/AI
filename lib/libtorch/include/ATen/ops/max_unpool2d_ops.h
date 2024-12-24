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


struct TORCH_API max_unpool2d_out {
  using schema = at::Tensor & (const at::Tensor &, const at::Tensor &, c10::SymIntArrayRef, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::max_unpool2d";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "max_unpool2d.out(Tensor self, Tensor indices, SymInt[2] output_size, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, const at::Tensor & indices, c10::SymIntArrayRef output_size, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & indices, c10::SymIntArrayRef output_size, at::Tensor & out);
};

struct TORCH_API max_unpool2d {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &, c10::SymIntArrayRef);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::max_unpool2d";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "max_unpool2d(Tensor self, Tensor indices, SymInt[2] output_size) -> Tensor";
  static at::Tensor call(const at::Tensor & self, const at::Tensor & indices, c10::SymIntArrayRef output_size);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & indices, c10::SymIntArrayRef output_size);
};

}} // namespace at::_ops
