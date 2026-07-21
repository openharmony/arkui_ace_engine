/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_item_bridge.h"

#include "core/components_ng/pattern/grid/grid_item_theme.h"
namespace OHOS::Ace::NG {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t DEFAULT_GRIDITEM_STYLE = static_cast<int32_t>(GridItemStyle::NONE);

ArkUINativeModuleValue GridItemBridge::SetGridItemSelectable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> selectableArg = runtimeCallInfo->GetCallArgRef(NUM_1); // selectable value
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (selectableArg->IsBoolean()) {
        bool selectable = selectableArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getGridItemModifier()->setGridItemSelectable(nativeNode, selectable);
    } else {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemSelectable(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemSelectable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemSelectable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> selectedArg = runtimeCallInfo->GetCallArgRef(NUM_1); // selected value
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (selectedArg->IsBoolean()) {
        bool selected = selectedArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getGridItemModifier()->setGridItemSelected(nativeNode, selected);
    } else {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemSelected(nativeNode);
    }
    
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridItemBridge::ResetGridItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemRowStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> rowStartArg = runtimeCallInfo->GetCallArgRef(NUM_1); // rowStart value
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (rowStartArg->IsNumber()) {
        int32_t stars = rowStartArg->Int32Value(vm);
        GetArkUINodeModifiers()->getGridItemModifier()->setGridItemRowStart(nativeNode, stars);
    } else {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemRowStart(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemRowStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemRowStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemRowEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> rowEndArg = runtimeCallInfo->GetCallArgRef(NUM_1); // rowEnd value
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (rowEndArg->IsNumber()) {
        int32_t end = rowEndArg->Int32Value(vm);
        GetArkUINodeModifiers()->getGridItemModifier()->setGridItemRowEnd(nativeNode, end);
    } else {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemRowEnd(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemRowEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemRowEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemColumnStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> columnStartArg = runtimeCallInfo->GetCallArgRef(NUM_1); // columnStart value
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (columnStartArg->IsNumber()) {
        int32_t stars = columnStartArg->Int32Value(vm);
        GetArkUINodeModifiers()->getGridItemModifier()->setGridItemColumnStart(nativeNode, stars);
    } else {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemColumnStart(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemColumnStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemColumnStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemColumnEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> columnEndArg = runtimeCallInfo->GetCallArgRef(NUM_1); // columnEnd value
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (columnEndArg->IsNumber()) {
        int32_t columnEnd = columnEndArg->Int32Value(vm);
        GetArkUINodeModifiers()->getGridItemModifier()->setGridItemColumnEnd(nativeNode, columnEnd);
    } else {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemColumnEnd(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemColumnEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemColumnEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeVal = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> styleVal = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeVal->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeVal->ToNativePointer(vm)->Value());

    int32_t gridItemStyle = DEFAULT_GRIDITEM_STYLE;
    if (styleVal->IsNumber() && styleVal->Int32Value(vm) >= static_cast<int32_t>(GridItemStyle::NONE) &&
        styleVal->Int32Value(vm) <= static_cast<int32_t>(GridItemStyle::PLAIN)) {
        gridItemStyle = styleVal->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getGridItemModifier()->setGridItemOptions(nativeNode, gridItemStyle);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridItemBridge::SetGridItemOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemOnSelect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(bool)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](bool isSelected) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::BooleanRef::New(vm, isSelected) };
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getGridItemModifier()->setGridItemOnSelect(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemOnSelect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG