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


struct TORCH_API narrow {
  using schema = at::Tensor (const at::Tensor &, int64_t, c10::SymInt, c10::SymInt);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::narrow";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "narrow(Tensor(a) self, int dim, SymInt start, SymInt length) -> Tensor(a)";
  static at::Tensor call(const at::Tensor & self, int64_t dim, c10::SymInt start, c10::SymInt length);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, int64_t dim, c10::SymInt start, c10::SymInt length);
};

struct TORCH_API narrow_Tensor {
  using schema = at::Tensor (const at::Tensor &, int64_t, const at::Tensor &, c10::SymInt);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::narrow";
  static constexpr const char* overload_name = "Tensor";
  static constexpr const char* schema_str = "narrow.Tensor(Tensor(a) self, int dim, Tensor start, SymInt length) -> Tensor(a)";
  static at::Tensor call(const at::Tensor & self, int64_t dim, const at::Tensor & start, c10::SymInt length);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, int64_t dim, const at::Tensor & start, c10::SymInt length);
};

}} // namespace at::_ops
