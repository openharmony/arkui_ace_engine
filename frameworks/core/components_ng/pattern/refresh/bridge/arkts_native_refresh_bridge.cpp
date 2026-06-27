/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/refresh/bridge/arkts_native_refresh_bridge.h"

#include "compatible/components/refresh/refresh_controller.h"

#include "bridge/common/utils/utils.h"
#include "core/components/refresh/refresh_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "frameworks/base/geometry/calc_dimension.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/utils/string_utils.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace::NG {
constexpr int32_t CALL_ARG_0 = 0;
constexpr int32_t CALL_ARG_1 = 1;
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t DEFAULT_FRICTION = 62;
constexpr int32_t MAX_FRICTION = 100;
namespace {
void ParseFrictionData(EcmaVM* vm, const Local<JSValueRef>& frictionVal, ArkUINodeHandle nativeNode)
{
    int32_t frictionNumber = DEFAULT_FRICTION;
    if (frictionVal->IsString(vm)) {
        std::string frictionStr = frictionVal->ToString(vm)->ToString(vm);
        frictionNumber = StringUtils::StringToInt(frictionStr);
        if ((frictionNumber == 0 && frictionStr != "0") || frictionNumber < 0 || frictionNumber > MAX_FRICTION) {
            frictionNumber = DEFAULT_FRICTION;
        }
    } else if (frictionVal->IsNumber()) {
        frictionNumber = static_cast<int32_t>(frictionVal->ToNumber(vm)->Value());
        if (frictionNumber < 0 || frictionNumber > MAX_FRICTION) {
            frictionNumber = DEFAULT_FRICTION;
        }
    }
    GetArkUINodeModifiers()->getRefreshModifier()->setFriction(nativeNode, static_cast<float>(frictionNumber));
}

void ParseRefreshingChangeEvent(ArkUIRuntimeCallInfo* runtimeCallInfo, const Local<JSValueRef>& changeEventVal)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(changeEventVal->IsFunction(vm));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    bool isJsView = ArkTSUtils::IsJsView(vm, runtimeCallInfo->GetCallArgRef(CALL_ARG_0));
    panda::Local<panda::FunctionRef> func = changeEventVal->ToObject(vm);
    std::function<void(const std::string&)> changeEvent = [vm, isJsView, weakNode = AceType::WeakClaim(frameNode),
                                                              func = panda::CopyableGlobal(vm, func)](
                                                              const std::string& param) {
        if (param != "true" && param != "false") {
            return;
        }
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        bool newValue = (param == "true");
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::BooleanRef::New(vm, newValue) };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getRefreshModifier()->setOnChangeEvent(nullptr, reinterpret_cast<void*>(&changeEvent));
}

bool ParseCustomBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo, const Local<JSValueRef>& paramObject)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, false);
    auto builder = paramObject->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "builder"));
    if (!builder->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRefreshModifier()->resetBuilder(nullptr);
        return false;
    }

    auto targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    panda::Local<panda::FunctionRef> func = builder->ToObject(vm);
    bool isJsView = ArkTSUtils::IsJsView(vm, runtimeCallInfo->GetCallArgRef(CALL_ARG_0));
    std::function<void()> builderFunc = [vm, isJsView, func = panda::CopyableGlobal(vm, func), node = targetNode]() {
        auto vm = func.GetEcmaVM();
        panda::LocalScope scope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getRefreshModifier()->setBuilder(nullptr, reinterpret_cast<void*>(&builderFunc));
    return true;
}

bool ParseRefreshingContent(EcmaVM* vm, const Local<JSValueRef>& paramObject, ArkUINodeHandle nativeNode)
{
    auto contentParam = paramObject->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "refreshingContent"));
    if (!contentParam->IsObject(vm)) {
        return false;
    }
    auto contentObj = contentParam->ToObject(vm);
    auto builderNodeVal = contentObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "builderNode_"));
    if (!builderNodeVal->IsObject(vm)) {
        return false;
    }
    auto builderNodeObj = builderNodeVal->ToObject(vm);
    auto nodePtrVal = builderNodeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "nodePtr_"));
    if (nodePtrVal->IsUndefined() || !nodePtrVal->IsNativePointer(vm)) {
        return false;
    }
    auto* node = nodePtrVal->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    GetArkUINodeModifiers()->getRefreshModifier()->setRefreshContent(
        nativeNode, reinterpret_cast<ArkUINodeHandle>(frameNode));
    GetArkUINodeModifiers()->getRefreshModifier()->setIsCustomBuilderExist(nativeNode, false);
    return true;
}
} // namespace

void RefreshBridge::RegisterRefreshAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setRefreshOffset", "resetRefreshOffset", "setPullToRefresh",
        "resetPullToRefresh", "setPullUpToCancelRefresh", "resetPullUpToCancelRefresh", "setPullDownRatio",
        "resetPullDownRatio", "setOnOffsetChange", "resetOnOffsetChange", "setOnStateChange", "resetOnStateChange",
        "setOnRefreshing", "resetOnRefreshing", "setMaxPullDownDistance", "resetMaxPullDownDistance" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::CreateRefresh),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::SetRefreshOffset),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::ResetRefreshOffset),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::SetPullToRefresh),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::ResetPullToRefresh),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::SetPullUpToCancelRefresh),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::ResetPullUpToCancelRefresh),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::SetPullDownRatio),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::ResetPullDownRatio),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::SetOnOffsetChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::ResetOnOffsetChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::SetOnStateChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::ResetOnStateChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::SetOnRefreshing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::ResetOnRefreshing),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::SetMaxPullDownDistance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridge::ResetMaxPullDownDistance),
    };

    auto refresh = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "refresh"), refresh);
}

ArkUINativeModuleValue RefreshBridge::CreateRefresh(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> paramRef = firstArg;
    if (firstArg->IsNativePointer(vm)) {
        paramRef = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    }

    if (!paramRef->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getRefreshModifier()->createRefresh();
    ArkUINodeHandle nativeNode = firstArg->IsNativePointer(vm)
        ? nodePtr(firstArg->ToNativePointer(vm)->Value())
        : reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());

    auto paramObject = paramRef->ToObject(vm);
    auto refreshing = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "refreshing"));
    auto jsOffset = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "offset"));
    auto friction = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "friction"));
    auto promptText = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "promptText"));
    Local<JSValueRef> changeEventVal;

    if (refreshing->IsBoolean()) {
        GetArkUINodeModifiers()->getRefreshModifier()->setRefreshing(nativeNode, refreshing->ToBoolean(vm)->Value());
        changeEventVal = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "$refreshing"));
        ParseRefreshingChangeEvent(runtimeCallInfo, changeEventVal);
    } else if (refreshing->IsObject(vm)) {
        auto refreshingObj = refreshing->ToObject(vm);
        changeEventVal = refreshingObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));
        ParseRefreshingChangeEvent(runtimeCallInfo, changeEventVal);
        GetArkUINodeModifiers()->getRefreshModifier()->setRefreshing(
            nativeNode, refreshingObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"))->ToBoolean(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getRefreshModifier()->setRefreshing(nativeNode, false);
    }

    CalcDimension offset;
    RefPtr<ResourceObject> offsetResObj;
    if (ArkTSUtils::ParseJsDimensionVp(vm, jsOffset, offset, offsetResObj)) {
        if (GreatOrEqual(offset.Value(), 0.0) && offset.Unit() != DimensionUnit::PERCENT) {
            GetArkUINodeModifiers()->getRefreshModifier()->setIndicatorOffset(
                nativeNode, offset.Value(), static_cast<int>(offset.Unit()), offsetResObj.GetRawPtr());
        }
    }

    ParseFrictionData(vm, friction, nativeNode);

    if (!ParseRefreshingContent(vm, paramObject, nativeNode)) {
        bool isCustomBuilderExist = ParseCustomBuilder(runtimeCallInfo, paramObject);
        GetArkUINodeModifiers()->getRefreshModifier()->setIsCustomBuilderExist(nativeNode, isCustomBuilderExist);
    }

    std::string loadingStr = "";
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (ArkTSUtils::ParseJsString(vm, promptText, loadingStr, resObj)) {
            GetArkUINodeModifiers()->getRefreshModifier()->setLoadingText(
                nativeNode, loadingStr.c_str(), resObj.GetRawPtr());
        } else {
            GetArkUINodeModifiers()->getRefreshModifier()->resetLoadingText(nativeNode);
        }
    } else if (ArkTSUtils::ParseJsString(vm, promptText, loadingStr)) {
        GetArkUINodeModifiers()->getRefreshModifier()->setLoadingText(
            nativeNode, loadingStr.c_str(), nullptr);
    } else {
        GetArkUINodeModifiers()->getRefreshModifier()->resetLoadingText(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::SetRefreshOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    CalcDimension value(0.0f);
    RefPtr<ResourceObject> resObj;
    if (valueArg->IsNull() || valueArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, valueArg, value, resObj)) {
        GetArkUINodeModifiers()->getRefreshModifier()->resetRefreshOffset(nativeNode);
    } else {
        GetArkUINodeModifiers()->getRefreshModifier()->setRefreshOffset(
            nativeNode, value.Value(), static_cast<int>(value.Unit()), resObj.GetRawPtr());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::ResetRefreshOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRefreshModifier()->resetRefreshOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::SetPullToRefresh(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    if (valueArg->IsBoolean()) {
        bool value = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getRefreshModifier()->setPullToRefresh(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getRefreshModifier()->resetPullToRefresh(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::ResetPullToRefresh(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRefreshModifier()->resetPullToRefresh(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::SetPullUpToCancelRefresh(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    if (valueArg->IsBoolean()) {
        bool value = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getRefreshModifier()->setPullUpToCancelRefresh(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getRefreshModifier()->resetPullUpToCancelRefresh(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::ResetPullUpToCancelRefresh(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRefreshModifier()->resetPullUpToCancelRefresh(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::SetPullDownRatio(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    if (valueArg->IsNumber()) {
        float number = static_cast<float>(valueArg->ToNumber(vm)->Value());
        if (std::isnan(number)) {
            GetArkUINodeModifiers()->getRefreshModifier()->resetPullDownRatio(nativeNode);
        } else {
            float value = std::clamp(number, 0.f, 1.f);
            GetArkUINodeModifiers()->getRefreshModifier()->setPullDownRatio(nativeNode, value);
        }
    } else {
        GetArkUINodeModifiers()->getRefreshModifier()->resetPullDownRatio(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::ResetPullDownRatio(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRefreshModifier()->resetPullDownRatio(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::SetOnStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    bool isJsView = ArkTSUtils::IsJsView(vm, firstArg);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getRefreshModifier()->resetRefreshOnStateChangeCallback(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(RefreshStatus)> callback = [vm, isJsView, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                      RefreshStatus stateChange) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, static_cast<int>(stateChange)) };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            UiSessionManager::GetInstance()->ReportComponentChangeEvent(
                "event", "Refresh.OnStateChange", ComponentEventType::COMPONENT_EVENT_SCROLL);
        }
    };
    GetArkUINodeModifiers()->getRefreshModifier()->setRefreshOnStateChangeCallback(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::ResetOnStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRefreshModifier()->resetRefreshOnStateChangeCallback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::SetOnRefreshing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    bool isJsView = ArkTSUtils::IsJsView(vm, firstArg);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getRefreshModifier()->resetOnRefreshingCallback(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void()> callback = [vm, isJsView, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto result = func->Call(vm, func.ToLocal(), nullptr, NUM_0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getRefreshModifier()->setOnRefreshingCallback(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::ResetOnRefreshing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRefreshModifier()->resetOnRefreshingCallback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::SetOnOffsetChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    bool isJsView = ArkTSUtils::IsJsView(vm, firstArg);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRefreshModifier()->resetRefreshOnOffsetChangeCallback(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const float)> callback = [vm, isJsView, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                    const float offsetChange) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, offsetChange) };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getRefreshModifier()->setRefreshOnOffsetChangeCallback(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::ResetOnOffsetChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRefreshModifier()->resetRefreshOnOffsetChangeCallback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::SetMaxPullDownDistance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, nodeArg);
    if (!valueArg->IsNull() && valueArg->IsObject(vm) && !valueArg->IsUndefined()) {
        double maxPullDownDistance = 0.0f;
        RefPtr<ResourceObject> resObj;
        bool parsed = ArkTSUtils::ParseJsDouble(vm, valueArg, maxPullDownDistance, resObj);
        if (parsed) {
            GetArkUINodeModifiers()->getRefreshModifier()->setMaxPullDownDistance(
                nativeNode, static_cast<float>(maxPullDownDistance), resObj.GetRawPtr());
        } else {
            GetArkUINodeModifiers()->getRefreshModifier()->resetMaxPullDownDistance(
                nativeNode, resObj.GetRawPtr());
        }
    } else if (valueArg->IsNumber()) {
        float value = static_cast<float>(valueArg->ToNumber(vm)->Value());
        if (isJsView && std::isnan(value)) {
            GetArkUINodeModifiers()->getRefreshModifier()->resetMaxPullDownDistance(nativeNode, nullptr);
        } else {
            value = std::max(value, 0.0f);
            GetArkUINodeModifiers()->getRefreshModifier()->setMaxPullDownDistance(nativeNode, value, nullptr);
        }
    } else {
        GetArkUINodeModifiers()->getRefreshModifier()->resetMaxPullDownDistance(nativeNode, nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RefreshBridge::ResetMaxPullDownDistance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRefreshModifier()->resetMaxPullDownDistance(nativeNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
