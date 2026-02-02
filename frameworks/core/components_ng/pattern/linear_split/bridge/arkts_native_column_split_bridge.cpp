/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "base/geometry/dimension.h"
#include "core/interfaces/native/node/node_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/linear_split/bridge/arkts_native_column_split_bridge.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;

bool ColumnSplitBridge::IsJsView(const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm)
{
    return jsVal->IsBoolean() && jsVal->ToBoolean(vm)->Value();
}

bool ColumnSplitBridge::GetNativeNode(
    ArkUINodeHandle& nativeNode, const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm)
{
    if (jsVal->IsNativePointer(vm)) {
        nativeNode = nodePtr(jsVal->ToNativePointer(vm)->Value());
        return true;
    }
    if (IsJsView(jsVal, vm)) {
        nativeNode = nullptr;
        return true;
    }
    return false;
}

void ColumnSplitBridge::RegisterColumnSplitAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setResizeable",  "resetResizeable", "setDivider",
        "resetDivider", "setColumnSplitClip" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnSplitBridge::CreateColumnSplit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnSplitBridge::SetResizable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnSplitBridge::ResetResizable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnSplitBridge::SetDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnSplitBridge::ResetDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnSplitBridge::SetColumnSplitClip),
    };
    auto columnSplit =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "columnSplit"), columnSplit);
}

ArkUINativeModuleValue ColumnSplitBridge::CreateColumnSplit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    GetArkUINodeModifiers()->getColumnSplitModifier()->createColumnSplit();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnSplitBridge::SetResizable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> resizableArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool resizable = false;
    if (resizableArg->IsBoolean()) {
        resizable = resizableArg->ToBoolean(vm)->BooleaValue(vm);
    }
    GetArkUINodeModifiers()->getColumnSplitModifier()->setColumnSplitResizable(nativeNode, resizable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnSplitBridge::ResetResizable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getColumnSplitModifier()->resetColumnSplitResizable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnSplitBridge::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> startMarginArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> endMarginArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension startMargin(0.0, DimensionUnit::VP);
    CalcDimension endMargin(0.0, DimensionUnit::VP);
    RefPtr<ResourceObject> startMarginResObj;
    RefPtr<ResourceObject> endMarginResObj;
    ArkTSUtils::ParseJsDimensionVp(vm, startMarginArg, startMargin, startMarginResObj);
    ArkTSUtils::ParseJsDimensionVp(vm, endMarginArg, endMargin, endMarginResObj);
    auto startMarginRawPtr = AceType::RawPtr(startMarginResObj);
    auto endMarginRawPtr = AceType::RawPtr(endMarginResObj);
    GetArkUINodeModifiers()->getColumnSplitModifier()->setColumnSplitDivider(nativeNode, startMargin.Value(),
        static_cast<int32_t>(startMargin.Unit()), endMargin.Value(), static_cast<int32_t>(endMargin.Unit()),
        startMarginRawPtr, endMarginRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnSplitBridge::ResetDivider(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getColumnSplitModifier()->resetColumnSplitDivider(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnSplitBridge::SetColumnSplitClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> clipArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    bool resizable = true;
    if (clipArg->IsBoolean()) {
        resizable = clipArg->ToBoolean(vm)->BooleaValue(vm);
    } else if (clipArg->IsObject(vm)) {
        Local<panda::ObjectRef> obj = clipArg->ToObject(vm);
        auto clipPtr = ArkTSUtils::GetBasicShape(vm, obj);
        if (clipPtr != nullptr) {
            GetArkUINodeModifiers()->getColumnSplitModifier()->setColumnSplitClipShape(
                nullptr, reinterpret_cast<void*>(AceType::RawPtr(clipPtr)));
            return panda::JSValueRef::Undefined(vm);
        }
    }
    GetArkUINodeModifiers()->getColumnSplitModifier()->setColumnSplitClip(nullptr, resizable);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
