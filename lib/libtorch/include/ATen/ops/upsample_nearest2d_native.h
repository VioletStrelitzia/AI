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
#include <ATen/ops/upsample_nearest2d_meta.h>

namespace at {
namespace native {
TORCH_API at::Tensor upsample_nearest2d(const at::Tensor & input, at::OptionalIntArrayRef output_size, ::std::optional<at::ArrayRef<double>> scale_factors);
TORCH_API at::Tensor & upsample_nearest2d_vec_out_symint(const at::Tensor & input, at::OptionalSymIntArrayRef output_size, ::std::optional<at::ArrayRef<double>> scale_factors, at::Tensor & out);
struct TORCH_API structured_upsample_nearest2d_out_cpu : public at::meta::structured_upsample_nearest2d {
void impl(const at::Tensor & self, at::ArrayRef<int64_t> output_size, ::std::optional<double> scales_h, ::std::optional<double> scales_w, const at::Tensor & out);
};
struct TORCH_API structured_upsample_nearest2d_out_cuda : public at::meta::structured_upsample_nearest2d {
void impl(const at::Tensor & self, at::ArrayRef<int64_t> output_size, ::std::optional<double> scales_h, ::std::optional<double> scales_w, const at::Tensor & out);
};
TORCH_API at::Tensor upsample_nearest2d_quantized_cpu(const at::Tensor & self, at::IntArrayRef output_size, ::std::optional<double> scales_h=::std::nullopt, ::std::optional<double> scales_w=::std::nullopt);
} // namespace native
} // namespace at
