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

#include "core/components_ng/pattern/navigator/bridge/arkts_native_navigator_bridge.h"
#include "jsnapi_expo.h"
#include "ui/base/ace_type.h"
#include "ui/base/utils/utils.h"

#include "core/components/navigator/navigator_component.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigator/navigator_pattern.h"
#include "core/interfaces/native/node/node_api.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
inline constexpr char NAVIGATOR_ETS_TAG[] = "Navigator";

} // namespace

void NavigatorBridge::RegisterNavigatorAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    const char* functionNames[] = { "setTarget", "resetTarget", "setType", "resetType", "setActive", "resetActive",
        "setParams", "resetParams", "setWidth", "setHeight", "setSize", "create" };

    Local<panda::JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetTarget),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::ResetTarget),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::ResetType),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetActive),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::ResetActive),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetParams),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::ResetParams),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::Create),
    };
    auto navigator = panda::ObjectRef::NewWithNamedProperties(
        vm, sizeof(functionNames) / sizeof(functionNames[0]), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "navigator"), navigator);
}

ArkUINativeModuleValue NavigatorBridge::SetTarget(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        std::string target = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getNavigatorModifier()->setTarget(nullptr, target.c_str());
        return panda::JSValueRef::Undefined(vm);
    }
    std::string target = secondArg->ToString(vm)->ToString(vm);
    GetArkUINodeModifiers()->getNavigatorModifier()->setTarget(nativeNode, target.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigatorBridge::ResetTarget(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigatorModifier()->resetTarget(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigatorBridge::SetType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        auto navigatorType = NavigatorType(secondArg->Int32Value(vm));
        if (navigatorType == NavigatorType::DEFAULT) {
            GetArkUINodeModifiers()->getNavigatorModifier()->setType(
                nullptr, static_cast<int32_t>(NavigatorType::PUSH));
        } else {
            GetArkUINodeModifiers()->getNavigatorModifier()->setType(nullptr, static_cast<int32_t>(navigatorType));
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getNavigatorModifier()->resetType(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t value = secondArg->Int32Value(vm);
    GetArkUINodeModifiers()->getNavigatorModifier()->setType(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigatorBridge::ResetType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigatorModifier()->resetType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigatorBridge::SetActive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        bool active = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavigatorModifier()->setActive(nullptr, active);
        return panda::JSValueRef::Undefined(vm);
    }
    bool active = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getNavigatorModifier()->setActive(nativeNode, active);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigatorBridge::ResetActive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigatorModifier()->resetActive(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigatorBridge::SetParams(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        std::string params = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getNavigatorModifier()->setParams(nullptr, params.c_str());
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getNavigatorModifier()->resetParams(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string params = secondArg->ToString(vm)->ToString(vm);
    GetArkUINodeModifiers()->getNavigatorModifier()->setParams(nativeNode, params.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigatorBridge::ResetParams(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigatorModifier()->resetParams(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigatorBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    return SetSizeDimension(vm, runtimeCallInfo->GetCallArgRef(NUM_0), true);
}

ArkUINativeModuleValue NavigatorBridge::SetHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    return SetSizeDimension(vm, runtimeCallInfo->GetCallArgRef(NUM_0), false);
}

ArkUINativeModuleValue NavigatorBridge::SetSizeDimension(EcmaVM* vm, Local<JSValueRef> jsValue, bool isWidth)
{
    GetArkUINodeModifiers()->getNavigatorModifier()->setIsDefSize(isWidth);
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ViewAbstract::ResetResObj(frameNode, isWidth ? "width" : "height");
    if (jsValue.IsEmpty() || jsValue->IsUndefined()) {
        ViewAbstract::UpdateLayoutPolicyProperty(frameNode, LayoutCalPolicy::NO_MATCH, isWidth);
        ViewAbstract::ClearWidthOrHeight(frameNode, isWidth);
        return panda::JSValueRef::Undefined(vm);
    }
    CalcDimension size;
    RefPtr<ResourceObject> sizeResObj;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, size, sizeResObj)) {
            ViewAbstract::ClearWidthOrHeight(frameNode, isWidth);
            if (!jsValue.IsEmpty() && jsValue->IsObject(vm)) {
                auto obj = jsValue->ToObject(vm);
                auto layoutPolicy = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
                if (layoutPolicy->IsString(vm)) {
                    auto policy = CommonBridge::ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
                    ViewAbstract::UpdateLayoutPolicyProperty(frameNode, policy, isWidth);
                    return panda::JSValueRef::Undefined(vm);
                }
            }
            ViewAbstract::UpdateLayoutPolicyProperty(frameNode, LayoutCalPolicy::NO_MATCH, isWidth);
            return panda::JSValueRef::Undefined(vm);
        }
    } else if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, size, sizeResObj)) {
        return panda::JSValueRef::Undefined(vm);
    }

    ViewAbstract::UpdateLayoutPolicyProperty(frameNode, LayoutCalPolicy::NO_MATCH, isWidth);
    if (!SystemProperties::ConfigChangePerform() ? LessNotEqual(size.Value(), 0.0)
                                                 : (LessNotEqual(size.Value(), 0.0) && !sizeResObj)) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            ViewAbstract::ClearWidthOrHeight(frameNode, isWidth);
            return panda::JSValueRef::Undefined(vm);
        }
        size.SetValue(0.0);
    }

    if (SystemProperties::ConfigChangePerform() && sizeResObj) {
        if (isWidth) {
            ViewAbstract::SetWidth(frameNode, sizeResObj);
        } else {
            ViewAbstract::SetHeight(frameNode, sizeResObj);
        }
    } else {
        if (isWidth) {
            ViewAbstract::SetWidth(frameNode, CalcLength(size));
        } else {
            ViewAbstract::SetHeight(frameNode, CalcLength(size));
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigatorBridge::SetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (firstArg.IsEmpty() || !firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto sizeObj = firstArg->ToObject(vm);
    auto widthProp = sizeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
    auto heightProp = sizeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
    SetSizeDimension(vm, widthProp, true);
    SetSizeDimension(vm, heightProp, false);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigatorBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        NAVIGATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavigatorPattern>(); });
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    stack->Push(frameNode);
    auto rawNode = AceType::RawPtr(frameNode);
    auto nativeNode = reinterpret_cast<ArkUINodeHandle>(rawNode);
    if (firstArg->IsObject(vm)) {
        auto obj = firstArg->ToObject(vm);
        auto targetProperty = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "target"));
        if (!targetProperty->IsNull() && !targetProperty->IsUndefined() && targetProperty->IsString(vm)) {
            GetArkUINodeModifiers()->getNavigatorModifier()->setTarget(
                nativeNode, targetProperty->ToString(vm)->ToString(vm).c_str());
        }
        auto typeProperty = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
        if (!typeProperty->IsNull() && !typeProperty->IsUndefined() && typeProperty->IsNumber()) {
            auto navigatorType = NavigatorType(typeProperty->ToNumber(vm)->Value());
            if (navigatorType == NavigatorType::DEFAULT) {
                GetArkUINodeModifiers()->getNavigatorModifier()->setType(
                    nativeNode, static_cast<int32_t>(NavigatorType::PUSH));
            } else {
                GetArkUINodeModifiers()->getNavigatorModifier()->setType(
                    nativeNode, static_cast<int32_t>(navigatorType));
            }
        }
    } else {
        GetArkUINodeModifiers()->getNavigatorModifier()->setType(
            nativeNode, static_cast<int32_t>(NavigatorType::BACK));
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
