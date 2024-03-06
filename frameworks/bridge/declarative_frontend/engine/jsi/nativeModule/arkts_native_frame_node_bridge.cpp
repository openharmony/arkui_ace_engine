/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue FrameNodeBridge::IsModifiable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, false));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::BooleanRef::New(vm, false));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto result = GetArkUINodeModifiers()->getFrameNodeModifier()->isModifiable(nativeNode);
    return panda::BooleanRef::New(vm, result);
}
ArkUINativeModuleValue FrameNodeBridge::AppendChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, true));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::BooleanRef::New(vm, true));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto childNativeNode = nodePtr(secondArg->ToNativePointer(vm)->Value());
    auto result = GetArkUINodeModifiers()->getFrameNodeModifier()->appendChild(nativeNode, childNativeNode);
    return panda::BooleanRef::New(vm, result);
}
ArkUINativeModuleValue FrameNodeBridge::InsertChildAfter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, true));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::BooleanRef::New(vm, true));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto child = nodePtr(secondArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2); // 2 : index to get the insert node
    if (thirdArg.IsNull()) {
        GetArkUINodeModifiers()->getFrameNodeModifier()->insertChildAfter(nativeNode, child, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    auto sibling = nodePtr(thirdArg->ToNativePointer(vm)->Value());
    auto result = GetArkUINodeModifiers()->getFrameNodeModifier()->insertChildAfter(nativeNode, child, sibling);
    return panda::BooleanRef::New(vm, result);
}
ArkUINativeModuleValue FrameNodeBridge::RemoveChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto childNativeNode = nodePtr(secondArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFrameNodeModifier()->removeChild(nativeNode, childNativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue FrameNodeBridge::ClearChildren(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFrameNodeModifier()->clearChildren(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue FrameNodeBridge::GetChildrenNumber(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NumberRef::New(vm, -1));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NumberRef::New(vm, -1));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto number = GetArkUINodeModifiers()->getFrameNodeModifier()->getChildrenNumber(nativeNode);
    return panda::NumberRef::New(vm, number);
}
ArkUINativeModuleValue FrameNodeBridge::GetChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    int index = secondArg->ToNumber(vm)->Value();
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getChild(nativeNode, index);
    return panda::NativePointerRef::New(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetFirst(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getFirst(nativeNode);
    return panda::NativePointerRef::New(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetNextSibling(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getNextSibling(nativeNode);
    return panda::NativePointerRef::New(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetPreviousSibling(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getPreviousSibling(nativeNode);
    return panda::NativePointerRef::New(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetParent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getParent(nativeNode);
    return panda::NativePointerRef::New(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetIdByNodePtr(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeId = GetArkUINodeModifiers()->getFrameNodeModifier()->getIdByNodePtr(nativeNode);
    return panda::NumberRef::New(vm, nodeId);
}
} // namespace OHOS::Ace::NG
