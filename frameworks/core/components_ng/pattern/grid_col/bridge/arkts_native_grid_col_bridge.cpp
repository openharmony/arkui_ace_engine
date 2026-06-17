/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/grid_col/bridge/arkts_native_grid_col_bridge.h"

#include "core/common/container.h"
#include "core/components_ng/pattern/grid_col/grid_col_model_ng.h"
#include "core/components_v2/grid_layout/grid_container_utils.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_NUMBER_BREAKPOINT = 6;
constexpr int XS = 0;
constexpr int SM = 1;
constexpr int MD = 2;
constexpr int LG = 3;
constexpr int XL = 4;
constexpr int XXL = 5;
constexpr int32_t VALUE_ARG_INDEX = 1;
constexpr int32_t MIN_ARGS_WITH_VALUE = 2;

Local<JSValueRef> GetObjectProperty(EcmaVM* vm, const Local<panda::ObjectRef>& object, const char* name)
{
    return object->Get(vm, panda::StringRef::NewFromUtf8(vm, name));
}

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, EcmaVM* vm)
{
    if (firstArg->IsNativePointer(vm)) {
        nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        return true;
    }
    if (firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value()) {
        nativeNode = nullptr;
        return true;
    }
    return false;
}

bool IsJsView(const Local<JSValueRef>& firstArg, EcmaVM* vm)
{
    return firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
}

void ParseContainerSize(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, int32_t* containerSizeArray,
    int32_t argOffset = 1)
{
    Local<JSValueRef> xs = runtimeCallInfo->GetCallArgRef(XS + argOffset);
    Local<JSValueRef> sm = runtimeCallInfo->GetCallArgRef(SM + argOffset);
    Local<JSValueRef> md = runtimeCallInfo->GetCallArgRef(MD + argOffset);
    Local<JSValueRef> lg = runtimeCallInfo->GetCallArgRef(LG + argOffset);
    Local<JSValueRef> xl = runtimeCallInfo->GetCallArgRef(XL + argOffset);
    Local<JSValueRef> xxl = runtimeCallInfo->GetCallArgRef(XXL + argOffset);
    containerSizeArray[XS] = xs->IsNumber() && xs->Int32Value(vm) >= 0 ? xs->Int32Value(vm) : -1;
    containerSizeArray[SM] = sm->IsNumber() && sm->Int32Value(vm) >= 0 ? sm->Int32Value(vm) : -1;
    containerSizeArray[MD] = md->IsNumber() && md->Int32Value(vm) >= 0 ? md->Int32Value(vm) : -1;
    containerSizeArray[LG] = lg->IsNumber() && lg->Int32Value(vm) >= 0 ? lg->Int32Value(vm) : -1;
    containerSizeArray[XL] = xl->IsNumber() && xl->Int32Value(vm) >= 0 ? xl->Int32Value(vm) : -1;
    containerSizeArray[XXL] = xxl->IsNumber() && xxl->Int32Value(vm) >= 0 ? xxl->Int32Value(vm) : -1;
}

void ApplyGridColOffset(ArkUINodeHandle nativeNode, const RefPtr<V2::GridContainerSize>& offset)
{
    CHECK_NULL_VOID(offset);
    int32_t containerSizeArray[MAX_NUMBER_BREAKPOINT] = {
        offset->xs, offset->sm, offset->md, offset->lg, offset->xl, offset->xxl
    };
    GetArkUINodeModifiers()->getGridColModifier()->setGridColOffset(
        nativeNode, containerSizeArray, MAX_NUMBER_BREAKPOINT);
}

void InheritGridContainerSize(
    V2::GridContainerSize& gridContainerSize, std::optional<int32_t> (&containerSizeArray)[MAX_NUMBER_BREAKPOINT],
    int32_t defaultVal)
{
    if (!containerSizeArray[0].has_value()) {
        containerSizeArray[0] = defaultVal;
    }
    for (size_t i = 1; i < MAX_NUMBER_BREAKPOINT; i++) {
        if (!containerSizeArray[i].has_value()) {
            containerSizeArray[i] = containerSizeArray[i - 1].value();
        }
    }
    gridContainerSize.xs = containerSizeArray[XS].value();
    gridContainerSize.sm = containerSizeArray[SM].value();
    gridContainerSize.md = containerSizeArray[MD].value();
    gridContainerSize.lg = containerSizeArray[LG].value();
    gridContainerSize.xl = containerSizeArray[XL].value();
    gridContainerSize.xxl = containerSizeArray[XXL].value();
}

void InheritGridColumnsNG(
    V2::GridContainerSize& gridContainerSize, std::optional<int32_t> (&containerSizeArray)[MAX_NUMBER_BREAKPOINT])
{
    for (size_t i = 0; i < MAX_NUMBER_BREAKPOINT; ++i) {
        if (containerSizeArray[i].has_value()) {
            containerSizeArray[XS] = containerSizeArray[i].value();
            break;
        }
    }
    CHECK_NULL_VOID(containerSizeArray[XS].has_value());
    for (size_t i = 1; i < MAX_NUMBER_BREAKPOINT; ++i) {
        if (!containerSizeArray[i].has_value()) {
            containerSizeArray[i] = containerSizeArray[i - 1].value();
        }
    }
    gridContainerSize.xs = containerSizeArray[XS].value();
    gridContainerSize.sm = containerSizeArray[SM].value();
    gridContainerSize.md = containerSizeArray[MD].value();
    gridContainerSize.lg = containerSizeArray[LG].value();
    gridContainerSize.xl = containerSizeArray[XL].value();
    gridContainerSize.xxl = containerSizeArray[XXL].value();
}

RefPtr<V2::GridContainerSize> ParseGridContainerSize(EcmaVM* vm, const Local<JSValueRef>& jsValue, int32_t defaultVal)
{
    if (jsValue->IsNumber()) {
        double columnNumber = jsValue->ToNumber(vm)->Value();
        return columnNumber >= 0 ? AceType::MakeRefPtr<V2::GridContainerSize>(static_cast<int32_t>(columnNumber))
                                 : AceType::MakeRefPtr<V2::GridContainerSize>(defaultVal);
    }
    if (jsValue->IsObject(vm)) {
        auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>(defaultVal);
        auto gridParam = jsValue->ToObject(vm);
        std::optional<int32_t> containerSizeArray[MAX_NUMBER_BREAKPOINT];
        auto xs = GetObjectProperty(vm, gridParam, "xs");
        if (xs->IsNumber() && xs->Int32Value(vm) >= 0) {
            containerSizeArray[XS] = xs->Int32Value(vm);
        }
        auto sm = GetObjectProperty(vm, gridParam, "sm");
        if (sm->IsNumber() && sm->Int32Value(vm) >= 0) {
            containerSizeArray[SM] = sm->Int32Value(vm);
        }
        auto md = GetObjectProperty(vm, gridParam, "md");
        if (md->IsNumber() && md->Int32Value(vm) >= 0) {
            containerSizeArray[MD] = md->Int32Value(vm);
        }
        auto lg = GetObjectProperty(vm, gridParam, "lg");
        if (lg->IsNumber() && lg->Int32Value(vm) >= 0) {
            containerSizeArray[LG] = lg->Int32Value(vm);
        }
        auto xl = GetObjectProperty(vm, gridParam, "xl");
        if (xl->IsNumber() && xl->Int32Value(vm) >= 0) {
            containerSizeArray[XL] = xl->Int32Value(vm);
        }
        auto xxl = GetObjectProperty(vm, gridParam, "xxl");
        if (xxl->IsNumber() && xxl->Int32Value(vm) >= 0) {
            containerSizeArray[XXL] = xxl->Int32Value(vm);
        }
        InheritGridContainerSize(*gridContainerSize, containerSizeArray, defaultVal);
        return gridContainerSize;
    }
    return AceType::MakeRefPtr<V2::GridContainerSize>(defaultVal);
}

RefPtr<V2::GridContainerSize> ParseSpansNG(EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    if (jsValue->IsNumber()) {
        double spanNumber = jsValue->ToNumber(vm)->Value();
        return spanNumber >= 0 ? AceType::MakeRefPtr<V2::GridContainerSize>(static_cast<int32_t>(spanNumber))
                               : AceType::MakeRefPtr<V2::GridContainerSize>(NG::DEFAULT_SPAN_NUMBER);
    }
    if (jsValue->IsObject(vm)) {
        auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>(NG::DEFAULT_SPAN_NUMBER);
        auto gridParam = jsValue->ToObject(vm);
        std::optional<int32_t> containerSizeArray[MAX_NUMBER_BREAKPOINT];
        auto xs = GetObjectProperty(vm, gridParam, "xs");
        if (xs->IsNumber() && xs->Int32Value(vm) >= 0) {
            containerSizeArray[XS] = xs->Int32Value(vm);
        }
        auto sm = GetObjectProperty(vm, gridParam, "sm");
        if (sm->IsNumber() && sm->Int32Value(vm) >= 0) {
            containerSizeArray[SM] = sm->Int32Value(vm);
        }
        auto md = GetObjectProperty(vm, gridParam, "md");
        if (md->IsNumber() && md->Int32Value(vm) >= 0) {
            containerSizeArray[MD] = md->Int32Value(vm);
        }
        auto lg = GetObjectProperty(vm, gridParam, "lg");
        if (lg->IsNumber() && lg->Int32Value(vm) >= 0) {
            containerSizeArray[LG] = lg->Int32Value(vm);
        }
        auto xl = GetObjectProperty(vm, gridParam, "xl");
        if (xl->IsNumber() && xl->Int32Value(vm) >= 0) {
            containerSizeArray[XL] = xl->Int32Value(vm);
        }
        auto xxl = GetObjectProperty(vm, gridParam, "xxl");
        if (xxl->IsNumber() && xxl->Int32Value(vm) >= 0) {
            containerSizeArray[XXL] = xxl->Int32Value(vm);
        }
        InheritGridColumnsNG(*gridContainerSize, containerSizeArray);
        return gridContainerSize;
    }
    return AceType::MakeRefPtr<V2::GridContainerSize>(NG::DEFAULT_SPAN_NUMBER);
}
} // namespace

void GridColBridge::RegisterGridColAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "offset", "setSpan", "resetSpan", "setGridColOffset",
        "resetGridColOffset", "setOrder", "resetOrder" };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::Create),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::Offset),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::SetSpan),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::ResetSpan),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::SetGridColOffset),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::ResetGridColOffset),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::SetOrder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::ResetOrder),
    };
    auto gridCol = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "gridCol"), gridCol);
}

ArkUINativeModuleValue GridColBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (firstArg->IsObject(vm)) {
        auto gridParam = firstArg->ToObject(vm);
        auto spanParam = GetObjectProperty(vm, gridParam, "span");
        auto offsetParam = GetObjectProperty(vm, gridParam, "offset");
        auto orderParam = GetObjectProperty(vm, gridParam, "order");
        RefPtr<V2::GridContainerSize> span;
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
            span = ParseGridContainerSize(vm, spanParam, NG::DEFAULT_SPAN_NUMBER);
        } else {
            span = ParseSpansNG(vm, spanParam);
        }
        auto offset = ParseGridContainerSize(vm, offsetParam, 0);
        auto order = ParseGridContainerSize(vm, orderParam, 0);
        nodeModifiers->getGridColModifier()->create(static_cast<void*>(&span), static_cast<void*>(&offset),
            static_cast<void*>(&order));
    } else {
        nodeModifiers->getGridColModifier()->create(nullptr, nullptr, nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridColBridge::Offset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < MIN_ARGS_WITH_VALUE) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(VALUE_ARG_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto offset = ParseGridContainerSize(vm, secondArg, 0);
    ApplyGridColOffset(nativeNode, offset);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridColBridge::SetGridColOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t containerSizeArray[MAX_NUMBER_BREAKPOINT];
    ParseContainerSize(runtimeCallInfo, vm, containerSizeArray);
    GetArkUINodeModifiers()->getGridColModifier()->setGridColOffset(nativeNode, containerSizeArray,
        MAX_NUMBER_BREAKPOINT);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridColBridge::ResetGridColOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getGridColModifier()->resetGridColOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridColBridge::SetSpan(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t containerSizeArray[MAX_NUMBER_BREAKPOINT];
    if (IsJsView(firstArg, vm)) {
        if (runtimeCallInfo->GetArgsNumber() < MIN_ARGS_WITH_VALUE) {
            return panda::JSValueRef::Undefined(vm);
        }
        Local<JSValueRef> spanArg = runtimeCallInfo->GetCallArgRef(VALUE_ARG_INDEX);
        auto span = Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY)
                        ? ParseGridContainerSize(vm, spanArg, NG::DEFAULT_SPAN_NUMBER)
                        : ParseSpansNG(vm, spanArg);
        containerSizeArray[XS] = span->xs;
        containerSizeArray[SM] = span->sm;
        containerSizeArray[MD] = span->md;
        containerSizeArray[LG] = span->lg;
        containerSizeArray[XL] = span->xl;
        containerSizeArray[XXL] = span->xxl;
    } else {
        ParseContainerSize(runtimeCallInfo, vm, containerSizeArray);
    }
    GetArkUINodeModifiers()->getGridColModifier()->setSpan(nativeNode, containerSizeArray, MAX_NUMBER_BREAKPOINT);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridColBridge::ResetSpan(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getGridColModifier()->resetSpan(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridColBridge::SetOrder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t containerSizeArray[MAX_NUMBER_BREAKPOINT];
    if (IsJsView(firstArg, vm)) {
        if (runtimeCallInfo->GetArgsNumber() < MIN_ARGS_WITH_VALUE) {
            return panda::JSValueRef::Undefined(vm);
        }
        auto order = ParseGridContainerSize(vm, runtimeCallInfo->GetCallArgRef(VALUE_ARG_INDEX), 0);
        containerSizeArray[XS] = order->xs;
        containerSizeArray[SM] = order->sm;
        containerSizeArray[MD] = order->md;
        containerSizeArray[LG] = order->lg;
        containerSizeArray[XL] = order->xl;
        containerSizeArray[XXL] = order->xxl;
    } else {
        ParseContainerSize(runtimeCallInfo, vm, containerSizeArray);
    }
    GetArkUINodeModifiers()->getGridColModifier()->setOrder(nativeNode, containerSizeArray, MAX_NUMBER_BREAKPOINT);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridColBridge::ResetOrder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    if (!GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getGridColModifier()->resetOrder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG