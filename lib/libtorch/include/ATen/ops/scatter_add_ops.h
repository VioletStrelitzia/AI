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


struct TORCH_API scatter_add {
  using schema = at::Tensor (const at::Tensor &, int64_t, const at::Tensor &, const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::scatter_add";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "scatter_add(Tensor self, int dim, Tensor index, Tensor src) -> Tensor";
  static at::Tensor call(const at::Tensor & self, int64_t dim, const at::Tensor & index, const at::Tensor & src);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, int64_t dim, const at::Tensor & index, const at::Tensor & src);
};

struct TORCH_API scatter_add_ {
  using schema = at::Tensor & (at::Tensor &, int64_t, const at::Tensor &, const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::scatter_add_";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "scatter_add_(Tensor(a!) self, int dim, Tensor index, Tensor src) -> Tensor(a!)";
  static at::Tensor & call(at::Tensor & self, int64_t dim, const at::Tensor & index, const at::Tensor & src);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, at::Tensor & self, int64_t dim, const at::Tensor & index, const at::Tensor & src);
};

struct TORCH_API scatter_add_out {
  using schema = at::Tensor & (const at::Tensor &, int64_t, const at::Tensor &, const at::Tensor &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::scatter_add";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "scatter_add.out(Tensor self, int dim, Tensor index, Tensor src, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, int64_t dim, const at::Tensor & index, const at::Tensor & src, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, int64_t dim, const at::Tensor & index, const at::Tensor & src, at::Tensor & out);
};

struct TORCH_API scatter_add_dimname {
  using schema = at::Tensor (const at::Tensor &, at::Dimname, const at::Tensor &, const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::scatter_add";
  static constexpr const char* overload_name = "dimname";
  static constexpr const char* schema_str = "scatter_add.dimname(Tensor self, Dimname dim, Tensor index, Tensor src) -> Tensor";
  static at::Tensor call(const at::Tensor & self, at::Dimname dim, const at::Tensor & index, const at::Tensor & src);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, at::Dimname dim, const at::Tensor & index, const at::Tensor & src);
};

}} // namespace at::_ops
