/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_item_bridge.h"

namespace OHOS::Ace::NG {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;

ArkUINativeModuleValue GridItemBridge::SetGridItemSelectable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> selectabledArg = runtimeCallInfo->GetCallArgRef(NUM_1); // selectabled value
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (selectabledArg->IsBoolean()) {
        bool selectable = selectabledArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetGridItemModifier().SetGridItemSelectable(nativeNode, selectable);
    } else {
        GetArkUIInternalNodeAPI()->GetGridItemModifier().ResetGridItemSelectable(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemSelectable(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridItemModifier().ResetGridItemSelectable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> selectedArg = runtimeCallInfo->GetCallArgRef(NUM_1); // selected value
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (selectedArg->IsBoolean()) {
        bool selected = selectedArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetGridItemModifier().SetGridItemSelected(nativeNode, selected);
    } else {
        GetArkUIInternalNodeAPI()->GetGridItemModifier().ResetGridItemSelected(nativeNode);
    }
    
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridItemBridge::ResetGridItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridItemModifier().ResetGridItemSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemRowStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> rowStartArg = runtimeCallInfo->GetCallArgRef(NUM_1); // rowStart value
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (rowStartArg->IsNumber()) {
        int32_t stars = rowStartArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetGridItemModifier().SetGridItemRowStart(nativeNode, stars);
    } else {
        GetArkUIInternalNodeAPI()->GetGridItemModifier().ResetGridItemRowStart(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemRowStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridItemModifier().ResetGridItemRowStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemRowEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> rowEndArg = runtimeCallInfo->GetCallArgRef(NUM_1); // rowEnd value
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (rowEndArg->IsNumber()) {
        int32_t end = rowEndArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetGridItemModifier().SetGridItemRowEnd(nativeNode, end);
    } else {
        GetArkUIInternalNodeAPI()->GetGridItemModifier().ResetGridItemRowEnd(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemRowEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridItemModifier().ResetGridItemRowEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemColumnStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> columnStartArg = runtimeCallInfo->GetCallArgRef(NUM_1); // columnStart value
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (columnStartArg->IsNumber()) {
        int32_t stars = columnStartArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetGridItemModifier().SetGridItemColumnStart(nativeNode, stars);
    } else {
        GetArkUIInternalNodeAPI()->GetGridItemModifier().ResetGridItemColumnStart(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemColumnStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridItemModifier().ResetGridItemColumnStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemColumnEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> columnEndArg = runtimeCallInfo->GetCallArgRef(NUM_1); // columnEnd value
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (columnEndArg->IsNumber()) {
        int32_t columnEnd = columnEndArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetGridItemModifier().SetGridItemColumnEnd(nativeNode, columnEnd);
    } else {
        GetArkUIInternalNodeAPI()->GetGridItemModifier().ResetGridItemColumnEnd(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemColumnEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridItemModifier().ResetGridItemColumnEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG