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


struct TORCH_API _sparse_coo_tensor_unsafe {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &, c10::SymIntArrayRef, ::std::optional<at::ScalarType>, ::std::optional<at::Layout>, ::std::optional<at::Device>, ::std::optional<bool>, ::std::optional<bool>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_sparse_coo_tensor_unsafe";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_sparse_coo_tensor_unsafe(Tensor indices, Tensor values, SymInt[] size, *, ScalarType? dtype=None, Layout? layout=None, Device? device=None, bool? pin_memory=None, bool? is_coalesced=None) -> Tensor";
  static at::Tensor call(const at::Tensor & indices, const at::Tensor & values, c10::SymIntArrayRef size, ::std::optional<at::ScalarType> dtype, ::std::optional<at::Layout> layout, ::std::optional<at::Device> device, ::std::optional<bool> pin_memory, ::std::optional<bool> is_coalesced);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & indices, const at::Tensor & values, c10::SymIntArrayRef size, ::std::optional<at::ScalarType> dtype, ::std::optional<at::Layout> layout, ::std::optional<at::Device> device, ::std::optional<bool> pin_memory, ::std::optional<bool> is_coalesced);
};

}} // namespace at::_ops
