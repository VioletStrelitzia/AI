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


struct TORCH_API hstack {
  using schema = at::Tensor (at::TensorList);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::hstack";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "hstack(Tensor[] tensors) -> Tensor";
  static at::Tensor call(at::TensorList tensors);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList tensors);
};

struct TORCH_API hstack_out {
  using schema = at::Tensor & (at::TensorList, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::hstack";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "hstack.out(Tensor[] tensors, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(at::TensorList tensors, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList tensors, at::Tensor & out);
};

}} // namespace at::_ops
