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


struct TORCH_API softshrink_backward_grad_input {
  using schema = at::Tensor & (const at::Tensor &, const at::Tensor &, const at::Scalar &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::softshrink_backward";
  static constexpr const char* overload_name = "grad_input";
  static constexpr const char* schema_str = "softshrink_backward.grad_input(Tensor grad_output, Tensor self, Scalar lambd, *, Tensor(a!) grad_input) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & grad_output, const at::Tensor & self, const at::Scalar & lambd, at::Tensor & grad_input);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & grad_output, const at::Tensor & self, const at::Scalar & lambd, at::Tensor & grad_input);
};

struct TORCH_API softshrink_backward {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &, const at::Scalar &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::softshrink_backward";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "softshrink_backward(Tensor grad_output, Tensor self, Scalar lambd) -> Tensor";
  static at::Tensor call(const at::Tensor & grad_output, const at::Tensor & self, const at::Scalar & lambd);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & grad_output, const at::Tensor & self, const at::Scalar & lambd);
};

}} // namespace at::_ops
