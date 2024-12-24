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


struct TORCH_API cosine_embedding_loss {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &, const at::Tensor &, double, int64_t);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::cosine_embedding_loss";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "cosine_embedding_loss(Tensor input1, Tensor input2, Tensor target, float margin=0.0, int reduction=Mean) -> Tensor";
  static at::Tensor call(const at::Tensor & input1, const at::Tensor & input2, const at::Tensor & target, double margin, int64_t reduction);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & input1, const at::Tensor & input2, const at::Tensor & target, double margin, int64_t reduction);
};

}} // namespace at::_ops
