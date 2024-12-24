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
#include <ATen/ops/upsample_linear1d_backward_meta.h>

namespace at {
namespace native {
struct TORCH_API structured_upsample_linear1d_backward_out_cpu : public at::meta::structured_upsample_linear1d_backward {
void impl(const at::Tensor & grad_output, at::ArrayRef<int64_t> output_size, at::ArrayRef<int64_t> input_size, bool align_corners, ::std::optional<double> scales, const at::Tensor & grad_input);
};
struct TORCH_API structured_upsample_linear1d_backward_out_cuda : public at::meta::structured_upsample_linear1d_backward {
void impl(const at::Tensor & grad_output, at::ArrayRef<int64_t> output_size, at::ArrayRef<int64_t> input_size, bool align_corners, ::std::optional<double> scales, const at::Tensor & grad_input);
};
} // namespace native
} // namespace at
