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
#include <ATen/ops/softplus_meta.h>

namespace at {
namespace native {
struct TORCH_API structured_softplus_out : public at::meta::structured_softplus {
void impl(const at::Tensor & self, const at::Scalar & beta, const at::Scalar & threshold, const at::Tensor & out);
};
} // namespace native
} // namespace at
