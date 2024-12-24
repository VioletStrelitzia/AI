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


struct TORCH_API _local_scalar_dense {
  using schema = at::Scalar (const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_local_scalar_dense";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_local_scalar_dense(Tensor self) -> Scalar";
  static at::Scalar call(const at::Tensor & self);
  static at::Scalar redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self);
};

}} // namespace at::_ops
