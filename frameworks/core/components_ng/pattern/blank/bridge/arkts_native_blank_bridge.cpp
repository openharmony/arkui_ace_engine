/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/blank/bridge/arkts_native_blank_bridge.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
namespace {
bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
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

bool IsJsView(const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    return firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
}
} // namespace

void BlankBridge::RegisterBlankAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create", "setColor", "resetColor", "setBlankHeight", "resetBlankHeight", "setBlankMin", "resetBlankMin"
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::Create),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::SetColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::ResetColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::SetBlankHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::ResetBlankHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::SetBlankMin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::ResetBlankMin),
    };
    auto blank = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "blank"), blank);
}

ArkUINativeModuleValue BlankBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    CalcDimension blankMin(0.0, DimensionUnit::VP);
    GetArkUINodeModifiers()->getBlankModifier()->createModel();
    auto* frameNode = reinterpret_cast<FrameNode*>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (firstArg->IsUndefined()) {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getBlankModifier()->setBlankMin, panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getBlankModifier()->setBlankMin(
            reinterpret_cast<ArkUINodeHandle>(frameNode), blankMin.Value(), static_cast<int32_t>(blankMin.Unit()));
        return panda::JSValueRef::Undefined(vm);
    }

    if (ArkTSUtils::ParseJsDimensionVp(vm, firstArg, blankMin)) {
        if (blankMin.IsNegative() || blankMin.Unit() == DimensionUnit::PERCENT) {
            blankMin.SetValue(0.0);
        }
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getBlankModifier()->setBlankMin, panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getBlankModifier()->setBlankMin(
            reinterpret_cast<ArkUINodeHandle>(frameNode), blankMin.Value(), static_cast<int32_t>(blankMin.Unit()));
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue BlankBridge::SetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    Color color;
    RefPtr<ResourceObject> blankResObj;
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView) {
        nativeNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
        if (!ArkTSUtils::ParseJsColor(vm, secondArg, color, blankResObj)) {
            CHECK_NULL_RETURN(GetArkUINodeModifiers()->getBlankModifier()->setColor, panda::JSValueRef::Undefined(vm));
            GetArkUINodeModifiers()->getBlankModifier()->setColor(
                nativeNode, Color::TRANSPARENT.GetValue(), AceType::RawPtr(blankResObj));
            return panda::JSValueRef::Undefined(vm);
        }
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getBlankModifier()->setColor, panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getBlankModifier()->setColor(
            nativeNode, color.GetValue(), AceType::RawPtr(blankResObj));
        return panda::JSValueRef::Undefined(vm);
    }
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, blankResObj, nodeInfo)) {
        uint32_t value = color.GetValue();
        auto blankRawPtr = AceType::RawPtr(blankResObj);
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getBlankModifier()->setColor, panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getBlankModifier()->setColor(nativeNode, value, blankRawPtr);
    } else {
        CHECK_NULL_RETURN(GetArkUINodeModifiers()->getBlankModifier()->resetColor, panda::JSValueRef::Undefined(vm));
        GetArkUINodeModifiers()->getBlankModifier()->resetColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue BlankBridge::ResetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getBlankModifier()->resetColor, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getBlankModifier()->resetColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue BlankBridge::SetBlankHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));

    CalcDimension height;
    RefPtr<ResourceObject> heightResObj;
    std::string calcStr;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, valueArg, height, heightResObj)) {
        GetArkUINodeModifiers()->getCommonModifier()->resetHeight(nativeNode);
    } else {
        if (LessNotEqual(height.Value(), 0.0)) {
            height.SetValue(0.0);
        }
        auto heightRawResObj = AceType::RawPtr(heightResObj);
        if (height.Unit() == DimensionUnit::CALC) {
            GetArkUINodeModifiers()->getCommonModifier()->setHeight(nativeNode, height.Value(),
                static_cast<int32_t>(height.Unit()), height.CalcValue().c_str(), heightRawResObj);
        } else {
            GetArkUINodeModifiers()->getCommonModifier()->setHeight(
                nativeNode, height.Value(), static_cast<int32_t>(height.Unit()), calcStr.c_str(), heightRawResObj);
        }
    }
    if (!ArkTSUtils::ParseJsDimensionVp(vm, valueArg, height)) {
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getBlankModifier()->setBlankHeight, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getBlankModifier()->setBlankHeight(
        nativeNode, height.Value(), static_cast<int32_t>(height.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue BlankBridge::ResetBlankHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getBlankModifier()->resetBlankHeight, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getBlankModifier()->resetBlankHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue BlankBridge::SetBlankMin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));

    CalcDimension blankMin;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, valueArg, blankMin)) {
        return panda::JSValueRef::Undefined(vm);
    }

    if (blankMin.IsNegative() || blankMin.Unit() == DimensionUnit::PERCENT) {
        blankMin.SetValue(0.0);
    }
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getBlankModifier()->setBlankMin, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getBlankModifier()->setBlankMin(
        nativeNode, blankMin.Value(), static_cast<int32_t>(blankMin.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue BlankBridge::ResetBlankMin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(GetArkUINodeModifiers()->getBlankModifier()->resetBlankMin, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getBlankModifier()->resetBlankMin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
