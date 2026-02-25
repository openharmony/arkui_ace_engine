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
#include "core/components_ng/pattern/counter/bridge/arkts_native_counter_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/interfaces/native/node/node_api.h"
#include "ui/base/ace_type.h"

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
void CounterBridge::RegisterCounterAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    LOGE("Start RegisterCounterAttributes nativeModule");

    const char* functionNames[] = { "create", "setEnableInc", "resetEnableInc", "setEnableDec", "resetEnableDec",
        "setCounterHeight", "resetCounterHeight", "setCounterWidth", "resetCounterWidth", "setCounterBackgroundColor",
        "resetCounterBackgroundColor", "setCounterSize", "resetCounterSize", "setCounterOnInc", "resetCounterOnInc",
        "setCounterOnDec", "resetCounterOnDec", "controlWidth", "state" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::CreateCounter),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetEnableInc),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetEnableInc),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetEnableDec),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetEnableDec),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetCounterHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetCounterHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetCounterWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetCounterWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetCounterBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetCounterBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetCounterSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetCounterSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetCounterOnInc),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetCounterOnInc),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetCounterOnDec),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetCounterOnDec),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetControlWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetStateChange)
    };

    auto counter = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "counter"), counter);
    LOGE("Finish RegisterCounterAttributes nativeModule");
}

ArkUINativeModuleValue CounterBridge::CreateCounter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    GetArkUINodeModifiers()->getCounterModifier()->createModel();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetEnableInc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> flagArg = runtimeCallInfo->GetCallArgRef(1);

    bool isJsView = IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    bool hasValidFlag = flagArg->IsBoolean();
    bool flagValue = hasValidFlag ? flagArg->ToBoolean(vm)->Value() : true;

    if (!hasValidFlag && !isJsView) {
        GetArkUINodeModifiers()->getCounterModifier()->resetEnableInc(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getCounterModifier()->setEnableInc(nativeNode, flagValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetEnableInc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCounterModifier()->resetEnableInc(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetEnableDec(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> flagArg = runtimeCallInfo->GetCallArgRef(1);

    bool isJsView = IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    bool hasValidFlag = flagArg->IsBoolean();
    bool flagValue = hasValidFlag ? flagArg->ToBoolean(vm)->Value() : true;

    if (!isJsView && !hasValidFlag) {
        GetArkUINodeModifiers()->getCounterModifier()->resetEnableDec(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getCounterModifier()->setEnableDec(nativeNode, flagValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetEnableDec(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCounterModifier()->resetEnableDec(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetCounterHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> heightValue = runtimeCallInfo->GetCallArgRef(1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    CalcDimension height;
    CalcDimension jsHeight;
    RefPtr<ResourceObject> heightResObj;
    ArkTSUtils::ParseJsDimensionVp(vm, heightValue, height, heightResObj, false);
    auto state = ArkTSUtils::ConvertFromJSValue(vm, heightValue, jsHeight, heightResObj);
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView && !state) {
        UpdateLayoutPolicy(runtimeCallInfo, false);
        return panda::JSValueRef::Undefined(vm);
    }

    if (!isJsView) {
        if (heightValue->IsObject(vm)) {
            auto obj = heightValue->ToObject(vm);
            auto layoutPolicy = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
            if (layoutPolicy->IsString(vm)) {
                auto policy = ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
                ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(policy, false);
                return panda::JSValueRef::Undefined(vm);
            }
        } else {
            ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
        }
    }
    auto heightRawPtr = AceType::RawPtr(heightResObj);
    if (isJsView) {
        if (LessNotEqual(jsHeight.Value(), 0.0)) {
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getCounterModifier()->setCounterHeightRes(
            nativeNode, jsHeight.Value(), static_cast<int>(jsHeight.Unit()), heightRawPtr);
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessNotEqual(height.Value(), 0.0)) {
        GetArkUINodeModifiers()->getCounterModifier()->resetCounterHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getCounterModifier()->setCounterHeightRes(
        nativeNode, height.Value(), static_cast<int>(height.Unit()), heightRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetCounterHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    GetArkUINodeModifiers()->getCounterModifier()->resetCounterHeight(nativeNode);
    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    return panda::JSValueRef::Undefined(vm);
}

void CounterBridge::UpdateLayoutPolicy(ArkUIRuntimeCallInfo* runtimeCallInfo, bool isWidth)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> value = runtimeCallInfo->GetCallArgRef(1);
    LayoutCalPolicy policy = LayoutCalPolicy::NO_MATCH;

    if (value->IsObject(vm)) {
        auto obj = value->ToObject(vm);
        CHECK_NULL_VOID(!obj.IsEmpty());
        auto layoutPolicy = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
        CHECK_NULL_VOID(!layoutPolicy.IsEmpty());
        if (layoutPolicy->IsString(vm)) {
            policy = ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
        }
    }
    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(policy, isWidth);
}

ArkUINativeModuleValue CounterBridge::SetCounterWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthValue = runtimeCallInfo->GetCallArgRef(1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    CalcDimension width;
    CalcDimension jsWidth;
    RefPtr<ResourceObject> widthResObj;
    ArkTSUtils::ParseJsDimensionVp(vm, widthValue, width, widthResObj, false);
    auto state = ArkTSUtils::ConvertFromJSValue(vm, widthValue, jsWidth, widthResObj);
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView && !state) {
        UpdateLayoutPolicy(runtimeCallInfo, true);
        return panda::JSValueRef::Undefined(vm);
    }

    if (!isJsView) {
        if (widthValue->IsObject(vm)) {
            auto obj = widthValue->ToObject(vm);
            auto layoutPolicy = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
            if (layoutPolicy->IsString(vm)) {
                auto policy = ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
                ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(policy, true);
                return panda::JSValueRef::Undefined(vm);
            }
        } else {
            ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
        }
    }
    auto widthRawPtr = AceType::RawPtr(widthResObj);
    if (isJsView) {
        if (LessNotEqual(jsWidth.Value(), 0.0)) {
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getCounterModifier()->setCounterWidthRes(
            nativeNode, jsWidth.Value(), static_cast<int>(jsWidth.Unit()), widthRawPtr);
        return panda::JSValueRef::Undefined(vm);
    }

    if (LessNotEqual(width.Value(), 0.0)) {
        GetArkUINodeModifiers()->getCounterModifier()->resetCounterWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getCounterModifier()->setCounterWidthRes(
        nativeNode, width.Value(), static_cast<int>(width.Unit()), widthRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetCounterWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    GetArkUINodeModifiers()->getCounterModifier()->resetCounterWidth(nativeNode);
    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetControlWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthValue = runtimeCallInfo->GetCallArgRef(1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    CalcDimension width;
    RefPtr<ResourceObject> widthResObj;

    if (!ArkTSUtils::ConvertFromJSValue(vm, widthValue, width, widthResObj)) {
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getCounterModifier()->setControlWidth(
        nativeNode, width.Value(), static_cast<int>(width.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> flagArg = runtimeCallInfo->GetCallArgRef(1);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (flagArg->IsBoolean()) {
        GetArkUINodeModifiers()->getCounterModifier()->setStateChange(nativeNode, flagArg->ToBoolean(vm)->Value());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetCounterBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getCounterModifier()->resetCounterBackgroundColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getCounterModifier()->setCounterBackgroundColorRes(
            nativeNode, color.GetValue(), color.GetColorSpace(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetCounterBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    GetArkUINodeModifiers()->getCounterModifier()->resetCounterBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetCounterSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> widthValue = runtimeCallInfo->GetCallArgRef(1);  // 1: width Value
    Local<JSValueRef> heightValue = runtimeCallInfo->GetCallArgRef(2); // 2: height Value
    CalcDimension width;
    CalcDimension jsWidth;
    RefPtr<ResourceObject> widthResObj;
    ArkTSUtils::ParseJsDimensionVp(vm, widthValue, width, widthResObj, false);
    auto widthState = ArkTSUtils::ConvertFromJSValue(vm, widthValue, jsWidth, widthResObj);
    CalcDimension height;
    CalcDimension jsHeight;
    RefPtr<ResourceObject> heightResObj;
    ArkTSUtils::ParseJsDimensionVp(vm, heightValue, height, heightResObj, false);
    auto heightState = ArkTSUtils::ConvertFromJSValue(vm, heightValue, jsHeight, heightResObj);

    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView) {
        if (widthState && jsWidth.IsValid() && GreatNotEqual(jsWidth.Value(), 0.0)) {
            auto widthRawPtr = AceType::RawPtr(widthResObj);
            GetArkUINodeModifiers()->getCounterModifier()->setCounterWidthRes(
                nativeNode, jsWidth.Value(), static_cast<int>(jsWidth.Unit()), widthRawPtr);
        }
        if (heightState && jsHeight.IsValid() && GreatNotEqual(jsHeight.Value(), 0.0)) {
            auto heightRawPtr = AceType::RawPtr(heightResObj);
            GetArkUINodeModifiers()->getCounterModifier()->setCounterHeightRes(
                nativeNode, jsHeight.Value(), static_cast<int>(jsHeight.Unit()), heightRawPtr);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (GreatNotEqual(width.Value(), 0.0)) {
        auto widthRawPtr = AceType::RawPtr(widthResObj);
        GetArkUINodeModifiers()->getCounterModifier()->setCounterWidthRes(
            nativeNode, width.Value(), static_cast<int>(width.Unit()), widthRawPtr);
    } else {
        GetArkUINodeModifiers()->getCounterModifier()->resetCounterWidth(nativeNode);
    }

    if (GreatNotEqual(height.Value(), 0.0)) {
        auto heightRawPtr = AceType::RawPtr(heightResObj);
        GetArkUINodeModifiers()->getCounterModifier()->setCounterHeightRes(
            nativeNode, height.Value(), static_cast<int>(height.Unit()), heightRawPtr);
    } else {
        GetArkUINodeModifiers()->getCounterModifier()->resetCounterHeight(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetCounterSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    GetArkUINodeModifiers()->getCounterModifier()->resetCounterWidth(nativeNode);
    GetArkUINodeModifiers()->getCounterModifier()->resetCounterHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetCounterOnInc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);

    bool isJsView = IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isValidCallback = callbackArg->IsFunction(vm);
    if (!isJsView && (!isValidCallback || callbackArg->IsUndefined() || callbackArg->IsNull())) {
        GetArkUINodeModifiers()->getCounterModifier()->resetCounterOnInc(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (isJsView && !isValidCallback) {
        return panda::JSValueRef::Undefined(vm);
    }
    FrameNode* frameNode = nullptr;
    if (isJsView) {
        frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    } else {
        frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void()> callback = [vm, isJsView, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getCounterModifier()->setCounterOnInc(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetCounterOnInc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    GetArkUINodeModifiers()->getCounterModifier()->resetCounterOnInc(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetCounterOnDec(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);

    bool isJsView = IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isValidCallback = callbackArg->IsFunction(vm);
    if (!isJsView && (!isValidCallback || callbackArg->IsUndefined() || callbackArg->IsNull())) {
        GetArkUINodeModifiers()->getCounterModifier()->resetCounterOnDec(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (isJsView && !isValidCallback) {
        return panda::JSValueRef::Undefined(vm);
    }
    FrameNode* frameNode = nullptr;
    if (isJsView) {
        frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    } else {
        frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void()> callback = [vm, isJsView, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getCounterModifier()->setCounterOnDec(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetCounterOnDec(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    GetArkUINodeModifiers()->getCounterModifier()->resetCounterOnDec(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
