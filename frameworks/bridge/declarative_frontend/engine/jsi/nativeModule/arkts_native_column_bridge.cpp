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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_column_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;

ArkUINativeModuleValue ColumnBridge::SetJustifyContent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t flexAlign = static_cast<int32_t>(FlexAlign::FLEX_START);
    if (secondArg->IsInt()) {
        flexAlign = secondArg->Int32Value(vm);
        if ((flexAlign == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
            (flexAlign == static_cast<int32_t>(FlexAlign::FLEX_END)) ||
            (flexAlign == static_cast<int32_t>(FlexAlign::CENTER)) ||
            (flexAlign == static_cast<int32_t>(FlexAlign::SPACE_BETWEEN)) ||
            (flexAlign == static_cast<int32_t>(FlexAlign::SPACE_AROUND)) ||
            (flexAlign == static_cast<int32_t>(FlexAlign::SPACE_EVENLY))) {
            GetArkUINodeModifiers()->getColumnModifier()->setColumnJustifyContent(nativeNode, flexAlign);
        } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            GetArkUINodeModifiers()->getColumnModifier()->resetColumnJustifyContent(nativeNode);
        }
    }
    GetArkUINodeModifiers()->getColumnModifier()->setColumnJustifyContent(nativeNode, flexAlign);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnBridge::ResetJustifyContent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getColumnModifier()->resetColumnJustifyContent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnBridge::SetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t value;
    if (secondArg->IsNumber()) {
        value = secondArg->Int32Value(vm);
        if ((value == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
            (value == static_cast<int32_t>(FlexAlign::FLEX_END)) ||
            (value == static_cast<int32_t>(FlexAlign::CENTER)) || (value == static_cast<int32_t>(FlexAlign::STRETCH))) {
            GetArkUINodeModifiers()->getColumnModifier()->setColumnAlignItems(nativeNode, value);
        } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            GetArkUINodeModifiers()->getColumnModifier()->resetColumnAlignItems(nativeNode);
        }
    } else {
        GetArkUINodeModifiers()->getColumnModifier()->resetColumnAlignItems(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnBridge::ResetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getColumnModifier()->resetColumnAlignItems(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnBridge::SetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension space;
    ArkTSUtils::ParseJsDimensionVp(vm, secondArg, space, false);
    if (LessNotEqual(space.Value(), 0.0)) {
        GetArkUINodeModifiers()->getColumnModifier()->resetColumnSpace(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getColumnModifier()->setColumnSpace(
        nativeNode, space.Value(), static_cast<int>(space.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnBridge::ResetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getColumnModifier()->resetColumnSpace(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnBridge::SetReverse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto hasValue = secondArg->IsBoolean();
    if (!hasValue) {
        GetArkUINodeModifiers()->getColumnModifier()->setColumnReverse(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    auto isReverse = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getColumnModifier()->setColumnReverse(nativeNode, isReverse);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ColumnBridge::ResetReverse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getColumnModifier()->resetColumnReverse(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
