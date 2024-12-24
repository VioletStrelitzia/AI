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


struct TORCH_API _make_per_channel_quantized_tensor {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &, const at::Tensor &, int64_t);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_make_per_channel_quantized_tensor";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_make_per_channel_quantized_tensor(Tensor self, Tensor scale, Tensor zero_point, int axis) -> Tensor";
  static at::Tensor call(const at::Tensor & self, const at::Tensor & scale, const at::Tensor & zero_point, int64_t axis);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & scale, const at::Tensor & zero_point, int64_t axis);
};

struct TORCH_API _make_per_channel_quantized_tensor_out {
  using schema = at::Tensor & (const at::Tensor &, const at::Tensor &, const at::Tensor &, int64_t, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_make_per_channel_quantized_tensor";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "_make_per_channel_quantized_tensor.out(Tensor self, Tensor scale, Tensor zero_point, int axis, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, const at::Tensor & scale, const at::Tensor & zero_point, int64_t axis, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & scale, const at::Tensor & zero_point, int64_t axis, at::Tensor & out);
};

}} // namespace at::_ops
