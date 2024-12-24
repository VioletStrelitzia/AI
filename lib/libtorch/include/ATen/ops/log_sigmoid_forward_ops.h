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


struct TORCH_API log_sigmoid_forward_output {
  using schema = ::std::tuple<at::Tensor &,at::Tensor &> (const at::Tensor &, at::Tensor &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::log_sigmoid_forward";
  static constexpr const char* overload_name = "output";
  static constexpr const char* schema_str = "log_sigmoid_forward.output(Tensor self, *, Tensor(a!) output, Tensor(b!) buffer) -> (Tensor(a!), Tensor(b!))";
  static ::std::tuple<at::Tensor &,at::Tensor &> call(const at::Tensor & self, at::Tensor & output, at::Tensor & buffer);
  static ::std::tuple<at::Tensor &,at::Tensor &> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, at::Tensor & output, at::Tensor & buffer);
};

struct TORCH_API log_sigmoid_forward {
  using schema = ::std::tuple<at::Tensor,at::Tensor> (const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::log_sigmoid_forward";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "log_sigmoid_forward(Tensor self) -> (Tensor output, Tensor buffer)";
  static ::std::tuple<at::Tensor,at::Tensor> call(const at::Tensor & self);
  static ::std::tuple<at::Tensor,at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self);
};

}} // namespace at::_ops
