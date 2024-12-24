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


struct TORCH_API sym_stride_int {
  using schema = c10::SymInt (const at::Tensor &, int64_t);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::sym_stride";
  static constexpr const char* overload_name = "int";
  static constexpr const char* schema_str = "sym_stride.int(Tensor self, int dim) -> SymInt";
  static c10::SymInt call(const at::Tensor & self, int64_t dim);
  static c10::SymInt redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, int64_t dim);
};

}} // namespace at::_ops
