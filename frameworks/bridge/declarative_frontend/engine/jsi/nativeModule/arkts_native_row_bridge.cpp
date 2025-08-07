/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_row_bridge.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue RowBridge::SetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> alignItemsArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (alignItemsArg->IsNumber()) {
        int32_t alignItems = alignItemsArg->Int32Value(vm);
        if ((alignItems == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
            (alignItems == static_cast<int32_t>(FlexAlign::FLEX_END)) ||
            (alignItems == static_cast<int32_t>(FlexAlign::CENTER)) ||
            (alignItems == static_cast<int32_t>(FlexAlign::STRETCH))) {
            GetArkUINodeModifiers()->getRowModifier()->setRowAlignItems(nativeNode, alignItems);
        } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            GetArkUINodeModifiers()->getRowModifier()->resetRowAlignItems(nativeNode);
        }
    } else {
        GetArkUINodeModifiers()->getRowModifier()->resetRowAlignItems(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RowBridge::ResetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRowModifier()->resetRowAlignItems(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RowBridge::SetJustifyContent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> justifyContentArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (justifyContentArg->IsNumber()) {
        int32_t justifyContent = justifyContentArg->Int32Value(vm);
        if ((justifyContent == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
            (justifyContent == static_cast<int32_t>(FlexAlign::FLEX_END)) ||
            (justifyContent == static_cast<int32_t>(FlexAlign::CENTER)) ||
            (justifyContent == static_cast<int32_t>(FlexAlign::SPACE_BETWEEN)) ||
            (justifyContent == static_cast<int32_t>(FlexAlign::SPACE_AROUND)) ||
            (justifyContent == static_cast<int32_t>(FlexAlign::SPACE_EVENLY))) {
            GetArkUINodeModifiers()->getRowModifier()->setRowJustifyContent(nativeNode, justifyContent);
        } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            GetArkUINodeModifiers()->getRowModifier()->resetRowJustifyContent(nativeNode);
        }
    } else {
        GetArkUINodeModifiers()->getRowModifier()->resetRowJustifyContent(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RowBridge::ResetJustifyContent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRowModifier()->resetRowJustifyContent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RowBridge::SetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension space;
    RefPtr<ResourceObject> spaceResObj;
    ArkTSUtils::ParseJsDimensionVp(vm, secondArg, space, spaceResObj, false);
    if (LessNotEqual(space.Value(), 0.0)) {
        GetArkUINodeModifiers()->getRowModifier()->resetRowSpace(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto spaceRawPtr = AceType::RawPtr(spaceResObj);
    GetArkUINodeModifiers()->getRowModifier()->setRowSpace(
        nativeNode, space.Value(), static_cast<int>(space.Unit()), spaceRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RowBridge::ResetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRowModifier()->resetRowSpace(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RowBridge::SetReverse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto hasValue = secondArg->IsBoolean();
    if (!hasValue) {
        GetArkUINodeModifiers()->getRowModifier()->setRowReverse(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    auto isReverse = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getRowModifier()->setRowReverse(nativeNode, isReverse);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RowBridge::ResetReverse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRowModifier()->resetRowReverse(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
