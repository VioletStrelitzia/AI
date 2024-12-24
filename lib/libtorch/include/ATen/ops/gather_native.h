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
#include <ATen/ops/gather_meta.h>

namespace at {
namespace native {
struct TORCH_API structured_gather_out : public at::meta::structured_gather {
void impl(const at::Tensor & self, int64_t dim, const at::Tensor & index, bool sparse_grad, const at::Tensor & out);
};
TORCH_API at::Tensor gather(const at::Tensor & self, at::Dimname dim, const at::Tensor & index, bool sparse_grad=false);
TORCH_API at::Tensor & gather_out(const at::Tensor & self, at::Dimname dim, const at::Tensor & index, bool sparse_grad, at::Tensor & out);
} // namespace native
} // namespace at
