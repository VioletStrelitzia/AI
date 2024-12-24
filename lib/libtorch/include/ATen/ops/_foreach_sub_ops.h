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


struct TORCH_API _foreach_sub_Scalar {
  using schema = ::std::vector<at::Tensor> (at::TensorList, const at::Scalar &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_foreach_sub";
  static constexpr const char* overload_name = "Scalar";
  static constexpr const char* schema_str = "_foreach_sub.Scalar(Tensor[] self, Scalar scalar) -> Tensor[]";
  static ::std::vector<at::Tensor> call(at::TensorList self, const at::Scalar & scalar);
  static ::std::vector<at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList self, const at::Scalar & scalar);
};

struct TORCH_API _foreach_sub__Scalar {
  using schema = void (at::TensorList, const at::Scalar &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_foreach_sub_";
  static constexpr const char* overload_name = "Scalar";
  static constexpr const char* schema_str = "_foreach_sub_.Scalar(Tensor(a!)[] self, Scalar scalar) -> ()";
  static void call(at::TensorList self, const at::Scalar & scalar);
  static void redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList self, const at::Scalar & scalar);
};

struct TORCH_API _foreach_sub_List {
  using schema = ::std::vector<at::Tensor> (at::TensorList, at::TensorList, const at::Scalar &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_foreach_sub";
  static constexpr const char* overload_name = "List";
  static constexpr const char* schema_str = "_foreach_sub.List(Tensor[] self, Tensor[] other, *, Scalar alpha=1) -> Tensor[]";
  static ::std::vector<at::Tensor> call(at::TensorList self, at::TensorList other, const at::Scalar & alpha);
  static ::std::vector<at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList self, at::TensorList other, const at::Scalar & alpha);
};

struct TORCH_API _foreach_sub__List {
  using schema = void (at::TensorList, at::TensorList, const at::Scalar &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_foreach_sub_";
  static constexpr const char* overload_name = "List";
  static constexpr const char* schema_str = "_foreach_sub_.List(Tensor(a!)[] self, Tensor[] other, *, Scalar alpha=1) -> ()";
  static void call(at::TensorList self, at::TensorList other, const at::Scalar & alpha);
  static void redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList self, at::TensorList other, const at::Scalar & alpha);
};

struct TORCH_API _foreach_sub_ScalarList {
  using schema = ::std::vector<at::Tensor> (at::TensorList, at::ArrayRef<at::Scalar>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_foreach_sub";
  static constexpr const char* overload_name = "ScalarList";
  static constexpr const char* schema_str = "_foreach_sub.ScalarList(Tensor[] self, Scalar[] scalars) -> Tensor[]";
  static ::std::vector<at::Tensor> call(at::TensorList self, at::ArrayRef<at::Scalar> scalars);
  static ::std::vector<at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList self, at::ArrayRef<at::Scalar> scalars);
};

struct TORCH_API _foreach_sub__ScalarList {
  using schema = void (at::TensorList, at::ArrayRef<at::Scalar>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_foreach_sub_";
  static constexpr const char* overload_name = "ScalarList";
  static constexpr const char* schema_str = "_foreach_sub_.ScalarList(Tensor(a!)[] self, Scalar[] scalars) -> ()";
  static void call(at::TensorList self, at::ArrayRef<at::Scalar> scalars);
  static void redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList self, at::ArrayRef<at::Scalar> scalars);
};

struct TORCH_API _foreach_sub_Scalar_out {
  using schema = void (at::TensorList, const at::Scalar &, at::TensorList);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_foreach_sub";
  static constexpr const char* overload_name = "Scalar_out";
  static constexpr const char* schema_str = "_foreach_sub.Scalar_out(Tensor[] self, Scalar scalar, *, Tensor(a!)[] out) -> ()";
  static void call(at::TensorList self, const at::Scalar & scalar, at::TensorList out);
  static void redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList self, const at::Scalar & scalar, at::TensorList out);
};

struct TORCH_API _foreach_sub_List_out {
  using schema = void (at::TensorList, at::TensorList, const at::Scalar &, at::TensorList);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_foreach_sub";
  static constexpr const char* overload_name = "List_out";
  static constexpr const char* schema_str = "_foreach_sub.List_out(Tensor[] self, Tensor[] other, *, Scalar alpha=1, Tensor(a!)[] out) -> ()";
  static void call(at::TensorList self, at::TensorList other, const at::Scalar & alpha, at::TensorList out);
  static void redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList self, at::TensorList other, const at::Scalar & alpha, at::TensorList out);
};

struct TORCH_API _foreach_sub_ScalarList_out {
  using schema = void (at::TensorList, at::ArrayRef<at::Scalar>, at::TensorList);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_foreach_sub";
  static constexpr const char* overload_name = "ScalarList_out";
  static constexpr const char* schema_str = "_foreach_sub.ScalarList_out(Tensor[] self, Scalar[] scalars, *, Tensor(a!)[] out) -> ()";
  static void call(at::TensorList self, at::ArrayRef<at::Scalar> scalars, at::TensorList out);
  static void redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList self, at::ArrayRef<at::Scalar> scalars, at::TensorList out);
};

}} // namespace at::_ops
