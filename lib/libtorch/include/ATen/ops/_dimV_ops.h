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


struct TORCH_API _dimV {
  using schema = int64_t (const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_dimV";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_dimV(Tensor self) -> int";
  static int64_t call(const at::Tensor & self);
  static int64_t redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self);
};

}} // namespace at::_ops
