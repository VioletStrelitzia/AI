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


struct TORCH_API _foreach_tanh {
  using schema = ::std::vector<at::Tensor> (at::TensorList);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_foreach_tanh";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_foreach_tanh(Tensor[] self) -> Tensor[]";
  static ::std::vector<at::Tensor> call(at::TensorList self);
  static ::std::vector<at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList self);
};

struct TORCH_API _foreach_tanh_ {
  using schema = void (at::TensorList);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_foreach_tanh_";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_foreach_tanh_(Tensor(a!)[] self) -> ()";
  static void call(at::TensorList self);
  static void redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList self);
};

struct TORCH_API _foreach_tanh_out {
  using schema = void (at::TensorList, at::TensorList);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_foreach_tanh";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "_foreach_tanh.out(Tensor[] self, *, Tensor(a!)[] out) -> ()";
  static void call(at::TensorList self, at::TensorList out);
  static void redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList self, at::TensorList out);
};

}} // namespace at::_ops
