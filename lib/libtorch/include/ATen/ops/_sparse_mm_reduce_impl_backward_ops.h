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


struct TORCH_API _sparse_mm_reduce_impl_backward {
  using schema = ::std::tuple<at::Tensor,at::Tensor> (const at::Tensor &, const at::Tensor &, const at::Tensor &, c10::string_view, const at::Tensor &, ::std::array<bool,2>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_sparse_mm_reduce_impl_backward";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_sparse_mm_reduce_impl_backward(Tensor self, Tensor grad_out, Tensor weight, str reduce, Tensor arg_out, bool[2] output_mask) -> (Tensor, Tensor)";
  static ::std::tuple<at::Tensor,at::Tensor> call(const at::Tensor & self, const at::Tensor & grad_out, const at::Tensor & weight, c10::string_view reduce, const at::Tensor & arg_out, ::std::array<bool,2> output_mask);
  static ::std::tuple<at::Tensor,at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & grad_out, const at::Tensor & weight, c10::string_view reduce, const at::Tensor & arg_out, ::std::array<bool,2> output_mask);
};

}} // namespace at::_ops
