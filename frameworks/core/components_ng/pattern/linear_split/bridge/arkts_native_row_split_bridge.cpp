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
#include "core/components_ng/pattern/linear_split/bridge/arkts_native_row_split_bridge.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/linear_split/bridge/arkts_native_column_split_bridge.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG {
void RowSplitBridge::RegisterRowSplitAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setResizeable", "resetResizeable", "setRowSplitClip" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowSplitBridge::CreateRowSplit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowSplitBridge::SetResizable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowSplitBridge::ResetResizable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowSplitBridge::SetRowSplitClip),
    };
    auto rowSplit = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "rowSplit"), rowSplit);
}

ArkUINativeModuleValue RowSplitBridge::CreateRowSplit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    GetArkUINodeModifiers()->getRowSplitModifier()->createRowSplit();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RowSplitBridge::SetResizable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> resizableArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(
        ColumnSplitBridge::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool resizable = false;
    if (resizableArg->IsBoolean()) {
        resizable = resizableArg->ToBoolean(vm)->BooleaValue(vm);
    }
    GetArkUINodeModifiers()->getRowSplitModifier()->setRowSplitResizable(nativeNode, resizable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RowSplitBridge::ResetResizable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRowSplitModifier()->resetRowSplitResizable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RowSplitBridge::SetRowSplitClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> clipArg = runtimeCallInfo->GetCallArgRef(1);
    bool resizable = true;
    if (clipArg->IsBoolean()) {
        resizable = clipArg->ToBoolean(vm)->BooleaValue(vm);
    } else if (clipArg->IsObject(vm)) {
        Local<panda::ObjectRef> obj = clipArg->ToObject(vm);
        auto clipPtr = ArkTSUtils::GetBasicShape(vm, obj);
        if (clipPtr != nullptr) {
            GetArkUINodeModifiers()->getRowSplitModifier()->setRowSplitClipShape(
                nullptr, reinterpret_cast<void*>(AceType::RawPtr(clipPtr)));
            return panda::JSValueRef::Undefined(vm);
        }
    }
    GetArkUINodeModifiers()->getRowSplitModifier()->setRowSplitClip(nullptr, resizable);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
