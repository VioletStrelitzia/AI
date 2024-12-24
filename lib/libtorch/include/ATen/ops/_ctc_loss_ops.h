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


struct TORCH_API _ctc_loss {
  using schema = ::std::tuple<at::Tensor,at::Tensor> (const at::Tensor &, const at::Tensor &, at::IntArrayRef, at::IntArrayRef, int64_t, bool);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_ctc_loss";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_ctc_loss(Tensor log_probs, Tensor targets, int[] input_lengths, int[] target_lengths, int blank=0, bool zero_infinity=False) -> (Tensor, Tensor)";
  static ::std::tuple<at::Tensor,at::Tensor> call(const at::Tensor & log_probs, const at::Tensor & targets, at::IntArrayRef input_lengths, at::IntArrayRef target_lengths, int64_t blank, bool zero_infinity);
  static ::std::tuple<at::Tensor,at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & log_probs, const at::Tensor & targets, at::IntArrayRef input_lengths, at::IntArrayRef target_lengths, int64_t blank, bool zero_infinity);
};

struct TORCH_API _ctc_loss_Tensor {
  using schema = ::std::tuple<at::Tensor,at::Tensor> (const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, int64_t, bool);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_ctc_loss";
  static constexpr const char* overload_name = "Tensor";
  static constexpr const char* schema_str = "_ctc_loss.Tensor(Tensor log_probs, Tensor targets, Tensor input_lengths, Tensor target_lengths, int blank=0, bool zero_infinity=False) -> (Tensor, Tensor)";
  static ::std::tuple<at::Tensor,at::Tensor> call(const at::Tensor & log_probs, const at::Tensor & targets, const at::Tensor & input_lengths, const at::Tensor & target_lengths, int64_t blank, bool zero_infinity);
  static ::std::tuple<at::Tensor,at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & log_probs, const at::Tensor & targets, const at::Tensor & input_lengths, const at::Tensor & target_lengths, int64_t blank, bool zero_infinity);
};

struct TORCH_API _ctc_loss_out {
  using schema = ::std::tuple<at::Tensor &,at::Tensor &> (const at::Tensor &, const at::Tensor &, at::IntArrayRef, at::IntArrayRef, int64_t, bool, at::Tensor &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_ctc_loss";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "_ctc_loss.out(Tensor log_probs, Tensor targets, int[] input_lengths, int[] target_lengths, int blank=0, bool zero_infinity=False, *, Tensor(a!) out0, Tensor(b!) out1) -> (Tensor(a!), Tensor(b!))";
  static ::std::tuple<at::Tensor &,at::Tensor &> call(const at::Tensor & log_probs, const at::Tensor & targets, at::IntArrayRef input_lengths, at::IntArrayRef target_lengths, int64_t blank, bool zero_infinity, at::Tensor & out0, at::Tensor & out1);
  static ::std::tuple<at::Tensor &,at::Tensor &> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & log_probs, const at::Tensor & targets, at::IntArrayRef input_lengths, at::IntArrayRef target_lengths, int64_t blank, bool zero_infinity, at::Tensor & out0, at::Tensor & out1);
};

struct TORCH_API _ctc_loss_Tensor_out {
  using schema = ::std::tuple<at::Tensor &,at::Tensor &> (const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, int64_t, bool, at::Tensor &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_ctc_loss";
  static constexpr const char* overload_name = "Tensor_out";
  static constexpr const char* schema_str = "_ctc_loss.Tensor_out(Tensor log_probs, Tensor targets, Tensor input_lengths, Tensor target_lengths, int blank=0, bool zero_infinity=False, *, Tensor(a!) out0, Tensor(b!) out1) -> (Tensor(a!), Tensor(b!))";
  static ::std::tuple<at::Tensor &,at::Tensor &> call(const at::Tensor & log_probs, const at::Tensor & targets, const at::Tensor & input_lengths, const at::Tensor & target_lengths, int64_t blank, bool zero_infinity, at::Tensor & out0, at::Tensor & out1);
  static ::std::tuple<at::Tensor &,at::Tensor &> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & log_probs, const at::Tensor & targets, const at::Tensor & input_lengths, const at::Tensor & target_lengths, int64_t blank, bool zero_infinity, at::Tensor & out0, at::Tensor & out1);
};

}} // namespace at::_ops
