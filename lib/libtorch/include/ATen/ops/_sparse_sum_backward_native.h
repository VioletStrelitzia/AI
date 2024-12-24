#pragma once

// @generated by torchgen/gen.py from NativeFunction.h

#include <c10/core/Scalar.h>
#include <c10/core/Storage.h>
#include <c10/core/TensorOptions.h>
#include <c10/util/Deprecated.h>
#include <optional>
#include <c10/core/QScheme.h>
#include <ATen/core/Reduction.h>
#include <ATen/core/Tensor.h>
#include <tuple>
#include <vector>


namespace at {
namespace native {
TORCH_API at::Tensor & _sparse_sum_backward_out(const at::Tensor & grad, const at::Tensor & self, at::IntArrayRef dim, at::Tensor & out);
TORCH_API at::Tensor _sparse_sum_backward_cpu(const at::Tensor & grad, const at::Tensor & self, at::IntArrayRef dim);
TORCH_API at::Tensor _sparse_sum_backward_cuda(const at::Tensor & grad, const at::Tensor & self, at::IntArrayRef dim);
} // namespace native
} // namespace at
