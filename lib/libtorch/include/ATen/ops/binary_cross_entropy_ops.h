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


struct TORCH_API binary_cross_entropy {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &, const ::std::optional<at::Tensor> &, int64_t);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::binary_cross_entropy";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "binary_cross_entropy(Tensor self, Tensor target, Tensor? weight=None, int reduction=Mean) -> Tensor";
  static at::Tensor call(const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction);
};

struct TORCH_API binary_cross_entropy_out {
  using schema = at::Tensor & (const at::Tensor &, const at::Tensor &, const ::std::optional<at::Tensor> &, int64_t, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::binary_cross_entropy";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "binary_cross_entropy.out(Tensor self, Tensor target, Tensor? weight=None, int reduction=Mean, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, at::Tensor & out);
};

}} // namespace at::_ops
