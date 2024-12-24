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
TORCH_API at::Tensor _chunk_cat(at::TensorList tensors, int64_t dim, int64_t num_chunks);
TORCH_API at::Tensor & _chunk_cat_out(at::TensorList tensors, int64_t dim, int64_t num_chunks, at::Tensor & out);
TORCH_API at::Tensor _chunk_cat_cuda(at::TensorList tensors, int64_t dim, int64_t num_chunks);
TORCH_API at::Tensor & _chunk_cat_out_cuda(at::TensorList tensors, int64_t dim, int64_t num_chunks, at::Tensor & out);
} // namespace native
} // namespace at
