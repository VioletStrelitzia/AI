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


struct TORCH_API masked_select_backward {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &, const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::masked_select_backward";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "masked_select_backward(Tensor grad, Tensor input, Tensor mask) -> Tensor";
  static at::Tensor call(const at::Tensor & grad, const at::Tensor & input, const at::Tensor & mask);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & grad, const at::Tensor & input, const at::Tensor & mask);
};

}} // namespace at::_ops
