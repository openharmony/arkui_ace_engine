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
#include "core/components_ng/pattern/xcomponent/bridge/arkts_native_xcomponent_bridge.h"

#include <limits>
#include <optional>

#include "ecmascript/cross_vm/jsnapi_expo_hybrid.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "jsnapi_expo.h"
#include "ui/base/utils/utils.h"

#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "core/common/statistic_event_reporter.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/xcomponent/bridge/xcomponent_dynamic_modifier.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_event_hub.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_property.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "frameworks/base/hiviewdfx/histogram_wrapper.h"
#include "frameworks/base/log/ace_scoring_log.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double FULL_DIMENSION = 100.0;
constexpr double HALF_DIMENSION = 50.0;
constexpr int32_t INVALID_HDR_TYPE = -1;
constexpr double ROUND_UNIT = 360.0;
constexpr double MAX_OPACITY = 1.0;
constexpr int32_t HDR_PARAM_SIZE = 5;
constexpr int32_t MAX_BG_ALIGN = 8;
constexpr int32_t INDEX_BG_POS_X = 0;
constexpr int32_t INDEX_BG_POS_Y = 1;
constexpr int32_t STRETCH_PARAM_SIZE = 4;
constexpr int32_t FRACTION_STOP_PAIR_SIZE = 2;
constexpr int32_t INVERT_OPTION_PARAM_SIZE = 4;

enum ArgIndices {
    ARG_FIRST = 0,
    ARG_ID = 1,
    ARG_TYPE = 2,
    ARG_IMAGE_AI_OPTIONS = 3,
    ARG_LIBRARY_NAME = 4,
    ARG_CONTROLLER = 5,
    ARG_INITIALIZE_MIN_COUNT = 6
};

void SendStatisticEvent(StatisticEventType type)
{
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto statisticEventReporter = context->GetStatisticEventReporter();
    CHECK_NULL_VOID(statisticEventReporter);
    statisticEventReporter->SendEvent(type);
}


void SetControllerOnCreatedCallback(EcmaVM* vm, FrameNode* frameNode, const Local<JSValueRef>& createdFunc)
{
    if (createdFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = createdFunc;
        auto onSurfaceCreated = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode)](
                                    const std::string& surfaceId, const std::string& /* xcomponentId */) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(node);
            panda::Local<panda::JSValueRef> para[1] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()) };
            func->Call(vm, func.ToLocal(), para, 1);
        };
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentControllerOnCreated(
            reinterpret_cast<ArkUINodeHandle>(frameNode), reinterpret_cast<void*>(&onSurfaceCreated));
    }
}

void SetControllerOnChangedCallback(EcmaVM* vm, FrameNode* frameNode, const Local<JSValueRef>& changedFunc)
{
    if (changedFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = changedFunc;
        auto onSurfaceChanged = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode)](
                                    const std::string& surfaceId, const NG::RectF& rect) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(node);
            const char* keys[] = { "offsetX", "offsetY", "surfaceWidth", "surfaceHeight" };
            Local<JSValueRef> rectValues[] = { panda::NumberRef::New(vm, rect.Left()),
                panda::NumberRef::New(vm, rect.Top()), panda::NumberRef::New(vm, rect.Width()),
                panda::NumberRef::New(vm, rect.Height()) };
            auto rectObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, rectValues);
            panda::Local<panda::JSValueRef> para[2] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()), rectObj };
            func->Call(vm, func.ToLocal(), para, 2);
        };
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentControllerOnChanged(
            reinterpret_cast<ArkUINodeHandle>(frameNode), reinterpret_cast<void*>(&onSurfaceChanged));
    }
}

void SetControllerOnDestroyedCallback(EcmaVM* vm, FrameNode* frameNode, const Local<JSValueRef>& destroyedFunc)
{
    if (destroyedFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = destroyedFunc;
        auto onSurfaceDestroyed = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode)](
                                      const std::string& surfaceId, const std::string& /* xcomponentId */) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(node);
            panda::Local<panda::JSValueRef> para[1] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()) };
            func->Call(vm, func.ToLocal(), para, 1);
        };
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentControllerOnDestroyed(
            reinterpret_cast<ArkUINodeHandle>(frameNode), reinterpret_cast<void*>(&onSurfaceDestroyed));
    }
}

void SetControllerOnCreated(
    EcmaVM* vm, FrameNode* frameNode, const Local<JSValueRef>& createdFunc, const Local<panda::ObjectRef>& thisObj)
{
    if (createdFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = createdFunc;
        SurfaceCreatedEvent onSurfaceCreated =
            [vm, func = panda::CopyableGlobal(vm, func), thisObj = panda::CopyableGlobal(vm, thisObj),
                node = AceType::WeakClaim(frameNode)](const std::string& surfaceId, const std::string& xcomponentId) {
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                PipelineContext::SetCallBackNode(node);
                panda::Local<panda::JSValueRef> para[1] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()) };
                func->Call(vm, thisObj.ToLocal(), para, 1);
                TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] ControllerOnCreated surfaceId:%{public}s",
                    xcomponentId.c_str(), surfaceId.c_str());
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, panda::JSValueRef::Undefined(vm));
            };
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentControllerOnCreated(
            reinterpret_cast<ArkUINodeHandle>(frameNode), reinterpret_cast<void*>(&onSurfaceCreated));
    }
}

void SetControllerOnChanged(
    EcmaVM* vm, FrameNode* frameNode, const Local<JSValueRef>& changedFunc, const Local<panda::ObjectRef>& thisObj)
{
    if (changedFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = changedFunc;
        SurfaceChangedEvent onSurfaceChanged = [vm, func = panda::CopyableGlobal(vm, func),
                                    thisObj = panda::CopyableGlobal(vm, thisObj), node = AceType::WeakClaim(frameNode)](
                                    const std::string& surfaceId, const NG::RectF& rect) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(node);
            const char* keys[] = { "offsetX", "offsetY", "surfaceWidth", "surfaceHeight" };
            Local<JSValueRef> rectValues[] = { panda::NumberRef::New(vm, rect.Left()),
                panda::NumberRef::New(vm, rect.Top()), panda::NumberRef::New(vm, rect.Width()),
                panda::NumberRef::New(vm, rect.Height()) };
            auto rectObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, rectValues);
            panda::Local<panda::JSValueRef> para[2] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()), rectObj };
            func->Call(vm, thisObj.ToLocal(), para, 2);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, panda::JSValueRef::Undefined(vm));
        };
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentControllerOnChanged(
            reinterpret_cast<ArkUINodeHandle>(frameNode), reinterpret_cast<void*>(&onSurfaceChanged));
    }
}

void SetControllerOnDestroyed(
    EcmaVM* vm, FrameNode* frameNode, const Local<JSValueRef>& destroyedFunc, const Local<panda::ObjectRef>& thisObj)
{
    if (destroyedFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = destroyedFunc;
        SurfaceDestroyedEvent onSurfaceDestroyed =
            [vm, func = panda::CopyableGlobal(vm, func), thisObj = panda::CopyableGlobal(vm, thisObj),
                node = AceType::WeakClaim(frameNode)](const std::string& surfaceId, const std::string& xcomponentId) {
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                PipelineContext::SetCallBackNode(node);
                panda::Local<panda::JSValueRef> para[1] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()) };
                func->Call(vm, thisObj.ToLocal(), para, 1);
                TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] ControllerOnDestroyed surfaceId:%{public}s",
                    xcomponentId.c_str(), surfaceId.c_str());
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, panda::JSValueRef::Undefined(vm));
            };
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentControllerOnDestroyed(
            reinterpret_cast<ArkUINodeHandle>(frameNode), reinterpret_cast<void*>(&onSurfaceDestroyed));
    }
}

void AddControllerToClientMap(const std::string& id, Framework::JSXComponentController* jsController)
{
#ifdef XCOMPONENT_SUPPORTED
    Framework::XComponentClient::GetInstance().AddControllerToJSXComponentControllersMap(id, jsController);
#endif
}

void RemoveControllerFromClientMap(const std::string& xcomponentId)
{
#ifdef XCOMPONENT_SUPPORTED
    Framework::XComponentClient::GetInstance().DeleteControllerFromJSXComponentControllersMap(xcomponentId);
    Framework::XComponentClient::GetInstance().DeleteFromJsValMapById(xcomponentId);
#endif
}

std::shared_ptr<InnerXComponentController> ParseXComponentController(
    EcmaVM* vm, const Local<JSValueRef>& controllerArg, const std::string& id)
{
    if (!controllerArg->IsObject(vm)) {
        return nullptr;
    }
    auto* jsController = static_cast<Framework::JSXComponentController*>(
        Local<panda::ObjectRef>(controllerArg)->GetNativePointerField(vm, 0));
    if (!jsController) {
        return nullptr;
    }
    jsController->SetInstanceId(Container::CurrentId());
    AddControllerToClientMap(id, jsController);
    return jsController->GetController();
}

void RegisterDetachCallback(ArkUINodeHandle nativeNode)
{
    DetachCallback detachCallback = [](const std::string& xcomponentId) {
        RemoveControllerFromClientMap(xcomponentId);
    };
    GetArkUINodeModifiers()->getXComponentModifier()->setXComponentDetachCallback(
        nativeNode, reinterpret_cast<void*>(&detachCallback));
}

void SetXComponentSoPath(EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    if (runtimeCallInfo->GetArgsNumber() <= ARG_ID) {
        return;
    }
    Local<JSValueRef> soPathArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    if (soPathArg->IsString(vm)) {
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentSoPath(
            soPathArg->ToString(vm)->ToString(vm).c_str());
    }
}

void* ConvertImageAIOptionsToNapi(const Local<JSValueRef>& imageAIOptionsArg)
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, nullptr);
    Local<JSValueRef> value = imageAIOptionsArg;
    JSValueWrapper valueWrapper = value;
    Framework::ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    return nativeEngine->ValueToNapiValue(valueWrapper);
}

XComponentType ToXComponentType(const std::string& type)
{
    if (type == "component") {
        return XComponentType::COMPONENT;
    }
    if (type == "node") {
        return XComponentType::NODE;
    }
    return XComponentType::SURFACE;
}

void ParseXComponentTypeToOptions(EcmaVM* vm, const Local<JSValueRef>& typeArg, XComponentOptions& options)
{
    if (!typeArg.IsNull() && typeArg->IsString(vm)) {
        SendStatisticEvent(StatisticEventType::XCOMPONENT_TYPE_USE_STRING);
        options.type = ToXComponentType(typeArg->ToString(vm)->ToString(vm));
        return;
    }
    if (!typeArg->IsNumber()) {
        return;
    }
    options.type = static_cast<XComponentType>(typeArg->Int32Value(vm));
    switch (options.type) {
        case XComponentType::COMPONENT:
            SendStatisticEvent(StatisticEventType::XCOMPONENT_TYPE_COMPONENT);
            break;
        case XComponentType::NODE:
            SendStatisticEvent(StatisticEventType::XCOMPONENT_TYPE_NODE);
            break;
        default:
            break;
    }
}

void SetControllerCallbacks(EcmaVM* vm, FrameNode* frameNode, const Local<panda::ObjectRef>& controllerObj)
{
    auto createdFunc = controllerObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceCreated"));
    SetControllerOnCreated(vm, frameNode, createdFunc, controllerObj);
    auto changedFunc = controllerObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceChanged"));
    SetControllerOnChanged(vm, frameNode, changedFunc, controllerObj);
    auto destroyedFunc = controllerObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceDestroyed"));
    SetControllerOnDestroyed(vm, frameNode, destroyedFunc, controllerObj);
}

bool ParseJsBlendMode(EcmaVM* vm, const Local<JSValueRef>& blendModeArg, const Local<JSValueRef>& blendApplyTypeArg,
    int32_t& blendModeValue, int32_t& blendApplyTypeValue)
{
    constexpr int32_t BACKWARD_COMPAT_MAGIC_NUMBER_OFFSCREEN = 1000;
    constexpr int32_t BACKWARD_COMPAT_SOURCE_IN_NUMBER_OFFSCREEN = 2000;
    constexpr int32_t BACKWARD_COMPAT_DESTINATION_IN_NUMBER_OFFSCREEN = 3000;
    constexpr int32_t BACKWARD_COMPAT_MAGIC_NUMBER_SRC_IN = 5000;
    if (blendModeArg->IsNumber()) {
        auto blendModeNum = blendModeArg->Int32Value(vm);
        if (blendModeNum >= 0 && blendModeNum < static_cast<int32_t>(BlendMode::MAX)) {
            blendModeValue = blendModeNum;
        } else if (blendModeNum == BACKWARD_COMPAT_MAGIC_NUMBER_OFFSCREEN) {
            blendModeValue = static_cast<int32_t>(BlendMode::SRC_OVER);
            blendApplyTypeValue = static_cast<int32_t>(BlendApplyType::OFFSCREEN);
        } else if (blendModeNum == BACKWARD_COMPAT_SOURCE_IN_NUMBER_OFFSCREEN) {
            blendModeValue = static_cast<int32_t>(BlendMode::SRC_IN);
            blendApplyTypeValue = static_cast<int32_t>(BlendApplyType::OFFSCREEN);
        } else if (blendModeNum == BACKWARD_COMPAT_DESTINATION_IN_NUMBER_OFFSCREEN) {
            blendModeValue = static_cast<int32_t>(BlendMode::DST_IN);
            blendApplyTypeValue = static_cast<int32_t>(BlendApplyType::OFFSCREEN);
        } else if (blendModeNum == BACKWARD_COMPAT_MAGIC_NUMBER_SRC_IN) {
            blendModeValue = static_cast<int32_t>(BlendMode::BACK_COMPAT_SOURCE_IN);
        }
    }
    if (blendApplyTypeArg->IsNumber()) {
        auto blendApplyTypeNum = blendApplyTypeArg->Int32Value(vm);
        if (blendApplyTypeNum >= static_cast<int32_t>(BlendApplyType::FAST) &&
            blendApplyTypeNum <= static_cast<int32_t>(BlendApplyType::OFFSCREEN)) {
            blendApplyTypeValue = blendApplyTypeNum;
        }
    }
    return true;
}
} // namespace

XComponentType XComponentBridge::ConvertToXComponentType(const std::string& type)
{
    if (type == "surface") {
        return XComponentType::SURFACE;
    }
    if (type == "component") {
        return XComponentType::COMPONENT;
    }
    if (type == "node") {
        return XComponentType::NODE;
    }
    return XComponentType::SURFACE;
}

void XComponentBridge::RegisterXComponentAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto xComponent = panda::ObjectRef::New(vm);

    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "create"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::Create));

    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setXComponentInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetXComponentInitialize));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetXComponentInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetXComponentInitialize));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetBackgroundColor));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetBackgroundColor));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundImage"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetBackgroundImage));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundImageSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetBackgroundImageSize));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundImagePosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetBackgroundImagePosition));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetOpacity));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetOpacity));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetBlur));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackdropBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetBackdropBlur));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGrayscale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetGrayscale));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGrayscale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetGrayscale));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetBrightness));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSaturate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetSaturate));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContrast"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetContrast));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setInvert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetInvert));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSepia"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetSepia));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHueRotate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetHueRotate));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColorBlend"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetColorBlend));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSphericalEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetSphericalEffect));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLightUpEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetLightUpEffect));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPixelStretchEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetPixelStretchEffect));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLinearGradientBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetLinearGradientBlur));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnLoad"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetOnLoad));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnLoad"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetOnLoad));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDestroy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetOnDestroy));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDestroy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetOnDestroy));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableAnalyzer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetEnableAnalyzer));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableAnalyzer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetEnableAnalyzer));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableSecure"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetEnableSecure));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableSecure"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetEnableSecure));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHdrBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetHdrBrightness));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHdrBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetHdrBrightness));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableTransparentLayer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetEnableTransparentLayer));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableTransparentLayer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetEnableTransparentLayer));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRenderFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetRenderFit));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRenderFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetRenderFit));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlendMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetBlendMode));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlendMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetBlendMode));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "isCommonEventAvailable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::IsCommonEventAvailable));

    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "xComponent"), xComponent);
}

void ParseImageAIOptions(const EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& aiOptions)
{
    if (!aiOptions->IsObject(vm)) {
        return;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    Local<JSValueRef> value = aiOptions;
    JSValueWrapper valueWrapper = value;
    Framework::ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value optionsValue = nativeEngine->ValueToNapiValue(valueWrapper);
    GetArkUINodeModifiers()->getXComponentModifier()->setImageAIOptions(nativeNode, optionsValue);
}

void XComponentBridge::ExtractInfoToXComponentOptions(XComponentOptions& options,
    panda::Local<panda::ObjectRef>& controllerObj, Local<panda::ObjectRef>& paramObject,
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);

    auto idArg = ArkTSUtils::GetProperty(vm, paramObject, "id");
    if (!idArg.IsNull() && idArg->IsString(vm)) {
        options.id = idArg->ToString(vm)->ToString(vm);
    }

    auto typeArg = ArkTSUtils::GetProperty(vm, paramObject, "type");
    ParseXComponentTypeToOptions(vm, typeArg, options);

    auto libraryNameArg = ArkTSUtils::GetProperty(vm, paramObject, "libraryname");
    if (!libraryNameArg.IsNull() && libraryNameArg->IsString(vm)) {
        options.libraryName = libraryNameArg->ToString(vm)->ToString(vm);
    }

    auto controllerArg = ArkTSUtils::GetProperty(vm, paramObject, "controller");
    if (!controllerArg.IsNull() && controllerArg->IsObject(vm)) {
        controllerObj = controllerArg->ToObject(vm);
        auto* jsController = static_cast<Framework::JSXComponentController*>(
            Local<panda::ObjectRef>(controllerArg)->GetNativePointerField(vm, 0));
        if (jsController) {
            jsController->SetInstanceId(Container::CurrentId());
            if (options.id.has_value()) {
                AddControllerToClientMap(options.id.value(), jsController);
            }
            options.xcomponentController = jsController->GetController();
        }
    }

    auto screenIdArg = ArkTSUtils::GetProperty(vm, paramObject, "screenId");
    if (screenIdArg->IsNumber()) {
        options.screenId = static_cast<uint64_t>(screenIdArg->Uint32Value(vm));
    }
}

ArkUINativeModuleValue XComponentBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(runtimeCallInfo->GetArgsNumber() > ARG_FIRST, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    if (arg.IsNull() || arg->IsUndefined() || !arg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    XComponentOptions options;
    Local<panda::ObjectRef> controllerObj;
    auto argObj = arg->ToObject(vm);
    auto aiOptions = ArkTSUtils::GetProperty(vm, argObj, "imageAIOptions");
    ExtractInfoToXComponentOptions(options, controllerObj, argObj, runtimeCallInfo);

    if (options.id == std::nullopt && options.xcomponentController == nullptr &&
        (options.type == XComponentType::SURFACE || options.type == XComponentType::TEXTURE)) {
        GetArkUINodeModifiers()->getXComponentModifier()->createXComponent(static_cast<ArkUI_Int32>(options.type));
    } else {
        GetArkUINodeModifiers()->getXComponentModifier()->createXComponentWithParam(
            options.id.has_value() ? options.id.value().c_str() : nullptr, static_cast<ArkUI_Int32>(options.type),
            options.libraryName.has_value() ? options.libraryName.value().c_str() : nullptr,
            &options.xcomponentController);
    }

    auto node = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto nativeNode = reinterpret_cast<ArkUINodeHandle>(node);
    ACE_UINODE_TRACE(AceType::WeakClaim(node));

    if (!options.libraryName.has_value() && options.xcomponentController && !controllerObj.IsNull() &&
        !controllerObj->IsUndefined()) {
        SetControllerCallbacks(vm, node, controllerObj);
    }
    RegisterDetachCallback(nativeNode);
    SetXComponentSoPath(vm, runtimeCallInfo);
    ParseImageAIOptions(vm, nativeNode, aiOptions);
    if (options.type == XComponentType::SURFACE && options.screenId.has_value()) {
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentScreenId(options.screenId.value());
    }
    return panda::JSValueRef::Undefined(vm);
}

void XComponentBridge::ParseParams(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Params& params)
{
    CHECK_NULL_VOID(runtimeCallInfo);
    ArkUI_XComponent_Params* xcParams = (ArkUI_XComponent_Params*)(&params);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(runtimeCallInfo->GetArgsNumber() > ARG_TYPE);
    Local<JSValueRef> paramsArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    CHECK_NULL_VOID(!paramsArg->IsNull() && paramsArg->IsObject(vm));
    auto obj = Local<panda::ObjectRef>(paramsArg);

    auto idArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    auto typeArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    auto libraryNameArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "libraryname"));
    auto controllerArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "controller"));
    auto imageAIOptionsArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "imageAIOptions"));
    auto screenIdArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "screenId"));

    xcParams->id = idArg->IsString(vm) ? idArg->ToString(vm)->ToString(vm) : "";
    if (libraryNameArg->IsString(vm)) {
        xcParams->libraryName = libraryNameArg->ToString(vm)->ToString(vm);
    }
    if (typeArg->IsString(vm)) {
        xcParams->type = ConvertToXComponentType(typeArg->ToString(vm)->ToString(vm));
    } else if (typeArg->IsNumber()) {
        xcParams->type = static_cast<XComponentType>(typeArg->Int32Value(vm));
    }
    xcParams->controller = nullptr;
    if (controllerArg->IsObject(vm)) {
        xcParams->controller = ParseXComponentController(vm, controllerArg, xcParams->id);
    }
    xcParams->aiOptions = nullptr;
    if (imageAIOptionsArg->IsObject(vm)) {
        xcParams->aiOptions = ConvertImageAIOptionsToNapi(imageAIOptionsArg);
    }
    if (screenIdArg->IsNumber()) {
        xcParams->screenId = screenIdArg->ToNumber(vm)->Value();
    }
}

void XComponentBridge::SetControllerOnCreated(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> paramsArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    CHECK_NULL_VOID(paramsArg->IsObject(vm));
    auto obj = Local<panda::ObjectRef>(paramsArg);
    auto controllerStr = panda::StringRef::NewFromUtf8(vm, "controller");
    auto controllerArg = obj->Get(vm, controllerStr);
    CHECK_NULL_VOID(controllerArg->IsObject(vm));
    auto object = controllerArg->ToObject(vm);
    auto createdFunc = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceCreated"));
    if (createdFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = createdFunc;
        auto onSurfaceCreated = [vm, func = panda::CopyableGlobal(vm, func),
                                    thisObj = panda::CopyableGlobal(vm, object), node = AceType::WeakClaim(frameNode)](
                                    const std::string& surfaceId, const std::string& xcomponentId) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(node);
            panda::Local<panda::JSValueRef> para[1] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()) };
            func->Call(vm, thisObj.ToLocal(), para, 1);
            TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponentNode[%{public}s] ControllerOnCreated surfaceId:%{public}s",
                xcomponentId.c_str(), surfaceId.c_str());
        };
        XComponentModelNG::SetControllerOnCreated(frameNode, std::move(onSurfaceCreated));
    }
}

void XComponentBridge::SetControllerOnChanged(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> paramsArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    CHECK_NULL_VOID(paramsArg->IsObject(vm));
    auto obj = Local<panda::ObjectRef>(paramsArg);
    auto controllerStr = panda::StringRef::NewFromUtf8(vm, "controller");
    auto controllerArg = obj->Get(vm, controllerStr);
    CHECK_NULL_VOID(controllerArg->IsObject(vm));
    auto object = controllerArg->ToObject(vm);
    auto changedFunc = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceChanged"));
    if (changedFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = changedFunc;
        auto onSurfaceChanged = [vm, func = panda::CopyableGlobal(vm, func),
                                    thisObj = panda::CopyableGlobal(vm, object), node = AceType::WeakClaim(frameNode)](
                                    const std::string& surfaceId, const NG::RectF& rect) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(node);
            const char* keys[] = { "offsetX", "offsetY", "surfaceWidth", "surfaceHeight" };
            Local<JSValueRef> rectValues[] = { panda::NumberRef::New(vm, rect.Left()),
                panda::NumberRef::New(vm, rect.Top()), panda::NumberRef::New(vm, rect.Width()),
                panda::NumberRef::New(vm, rect.Height()) };
            auto rectObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, rectValues);
            panda::Local<panda::JSValueRef> para[2] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()), rectObj };
            func->Call(vm, thisObj.ToLocal(), para, 2);
        };
        XComponentModelNG::SetControllerOnChanged(frameNode, std::move(onSurfaceChanged));
    }
}

void XComponentBridge::SetControllerOnDestroyed(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> paramsArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    CHECK_NULL_VOID(paramsArg->IsObject(vm));
    auto obj = Local<panda::ObjectRef>(paramsArg);
    auto controllerStr = panda::StringRef::NewFromUtf8(vm, "controller");
    auto controllerArg = obj->Get(vm, controllerStr);
    CHECK_NULL_VOID(controllerArg->IsObject(vm));
    auto object = controllerArg->ToObject(vm);
    auto destroyedFunc = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceDestroyed"));
    if (destroyedFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = destroyedFunc;
        auto onDestroyed = [vm, func = panda::CopyableGlobal(vm, func), thisObj = panda::CopyableGlobal(vm, object),
                               node = AceType::WeakClaim(frameNode)](
                               const std::string& surfaceId, const std::string& xcomponentId) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(node);
            panda::Local<panda::JSValueRef> para[1] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()) };
            func->Call(vm, thisObj.ToLocal(), para, 1);
            TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponentNode[%{public}s] ControllerOnDestroyed surfaceId:%{public}s",
                xcomponentId.c_str(), surfaceId.c_str());
        };
        XComponentModelNG::SetControllerOnDestroyed(frameNode, std::move(onDestroyed));
    }
}

void XComponentBridge::SetControllerCallback(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode)
{
    SetControllerOnCreated(runtimeCallInfo, frameNode);
    SetControllerOnChanged(runtimeCallInfo, frameNode);
    SetControllerOnDestroyed(runtimeCallInfo, frameNode);
}

void XComponentBridge::SetControllerCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> controllerArg = runtimeCallInfo->GetCallArgRef(ARG_CONTROLLER);
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    auto object = controllerArg->ToObject(vm);
    auto createdFunc = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceCreated"));
    SetControllerOnCreatedCallback(vm, frameNode, createdFunc);
    auto changedFunc = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceChanged"));
    SetControllerOnChangedCallback(vm, frameNode, changedFunc);
    auto destroyedFunc = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceDestroyed"));
    SetControllerOnDestroyedCallback(vm, frameNode, destroyedFunc);
}

ArkUINativeModuleValue XComponentBridge::SetXComponentInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(runtimeCallInfo->GetArgsNumber() >= ARG_INITIALIZE_MIN_COUNT, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> idArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    Local<JSValueRef> librarynameArg = runtimeCallInfo->GetCallArgRef(ARG_LIBRARY_NAME);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    if (!idArg->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> controllerArg = runtimeCallInfo->GetCallArgRef(ARG_CONTROLLER);
    Local<ObjectRef> controllerObj;
    std::shared_ptr<InnerXComponentController> xcomponentController = nullptr;
    if (controllerArg->IsObject(vm)) {
        controllerObj = controllerArg->ToObject(vm);
        xcomponentController = ParseXComponentController(vm, controllerArg, idArg->ToString(vm)->ToString(vm));
    }
    XComponentType xcomponentType = XComponentType::SURFACE;
    if (typeArg->IsString(vm)) {
        xcomponentType = ConvertToXComponentType(typeArg->ToString(vm)->ToString(vm));
    } else if (typeArg->IsNumber()) {
        xcomponentType = static_cast<XComponentType>(typeArg->Int32Value(vm));
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setXComponentId(
        nativeNode, idArg->ToString(vm)->ToString(vm).c_str());
    GetArkUINodeModifiers()->getXComponentModifier()->setXComponentType(
        nativeNode, static_cast<int32_t>(xcomponentType));
    if (librarynameArg->IsString(vm)) {
        auto libraryName = librarynameArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentLibraryname(nativeNode, libraryName.c_str());
    }
    if ((librarynameArg->IsNull() || librarynameArg->IsUndefined()) && xcomponentController &&
        !controllerObj->IsUndefined()) {
        SetControllerCallback(runtimeCallInfo);
    }
    HandleDetachCallback(runtimeCallInfo);
    HandleImageAIOptions(runtimeCallInfo);
    GetArkUINodeModifiers()->getXComponentModifier()->initXComponent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void XComponentBridge::HandleDetachCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CHECK_NULL_VOID(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(runtimeCallInfo->GetArgsNumber() > ARG_FIRST);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    CHECK_NULL_VOID(firstArg->IsNativePointer(vm));
    auto detachCallback = [](const std::string& xcomponentId) {
#ifdef XCOMPONENT_SUPPORTED
        Framework::XComponentClient::GetInstance().DeleteControllerFromJSXComponentControllersMap(xcomponentId);
        Framework::XComponentClient::GetInstance().DeleteFromJsValMapById(xcomponentId);
#endif
    };
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_VOID(frameNode);
    GetArkUINodeModifiers()->getXComponentModifier()->setXComponentDetachCallback(
        reinterpret_cast<ArkUINodeHandle>(frameNode), reinterpret_cast<void*>(&detachCallback));
}

void XComponentBridge::HandleImageAIOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CHECK_NULL_VOID(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(runtimeCallInfo->GetArgsNumber() > ARG_IMAGE_AI_OPTIONS);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> imageAIOptionsArg = runtimeCallInfo->GetCallArgRef(ARG_IMAGE_AI_OPTIONS);
    CHECK_NULL_VOID(firstArg->IsNativePointer(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_VOID(nativeNode);
    if (imageAIOptionsArg->IsObject(vm)) {
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        CHECK_NULL_VOID(nativeEngine);
        Local<JSValueRef> value = imageAIOptionsArg;
        JSValueWrapper valueWrapper = value;
        Framework::ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
        napi_value optionsValue = nativeEngine->ValueToNapiValue(valueWrapper);
        GetArkUINodeModifiers()->getXComponentModifier()->setImageAIOptions(nativeNode, optionsValue);
    }
}

ArkUINativeModuleValue XComponentBridge::ResetXComponentInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    if (secondArg.IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(
        ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::NativePointerRef::New(vm, nullptr));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    if (isJsView && secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentBackgroundColor(nativeNode, isJsView);
        return panda::JSValueRef::Undefined(vm);
    }
    Color color;
    RefPtr<ResourceObject> backgroundColorResObj;
    if (!ArkTSUtils::ParseJsColor(vm, secondArg, color, backgroundColorResObj)) {
        GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentBackgroundColor(nativeNode, isJsView);
    } else {
        auto bgColorRawPtr = AceType::RawPtr(backgroundColorResObj);
        auto headRoomOptional = color.GetHeadRoomColor();
        if (headRoomOptional.has_value()) {
            auto colorWithHeadRoom = headRoomOptional.value();
            ArkUI_Float32 hdrValues[HDR_PARAM_SIZE] = { static_cast<ArkUI_Float32>(colorWithHeadRoom.red),
                static_cast<ArkUI_Float32>(colorWithHeadRoom.green), static_cast<ArkUI_Float32>(colorWithHeadRoom.blue),
                static_cast<ArkUI_Float32>(colorWithHeadRoom.alpha),
                static_cast<ArkUI_Float32>(colorWithHeadRoom.headRoom) };
            GetArkUINodeModifiers()->getXComponentModifier()->setXComponentBackgroundColorForHDR(
                nativeNode, color.GetColorSpace(), hdrValues, bgColorRawPtr, isJsView);
        } else {
            GetArkUINodeModifiers()->getXComponentModifier()->setXComponentBackgroundColorWithColorSpace(
                nativeNode, color.GetValue(), color.GetColorSpace(), isJsView);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentBackgroundColor(nativeNode, false);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    if (secondArg.IsNull() || secondArg->IsUndefined()) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        if (type == XComponentType::SURFACE || type == XComponentType::COMPONENT) {
            return panda::JSValueRef::Undefined(vm);
        }
        RefPtr<ResourceObject> opacityResObj;
        double opacity;
        if (!ArkTSUtils::ParseJsDouble(vm, secondArg, opacity, opacityResObj)) {
            GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentOpacity(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        if (SystemProperties::ConfigChangePerform() && opacityResObj) {
            GetArkUINodeModifiers()->getXComponentModifier()->createWithOpacityResourceObj(
                nativeNode, AceType::RawPtr(opacityResObj));
            return panda::JSValueRef::Undefined(vm);
        }
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            opacity = std::clamp(opacity, 0.0, 1.0);
        } else {
            if (opacity > MAX_OPACITY || LessNotEqual(opacity, 0.0)) {
                opacity = MAX_OPACITY;
            }
        }
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentOpacity(nativeNode, opacity);
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<ResourceObject> opacityResObj;
    double opacity;
    if (!ArkTSUtils::ParseJsDouble(vm, secondArg, opacity, opacityResObj)) {
        GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentOpacity(nativeNode);
    } else {
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentOpacity(nativeNode, opacity);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetGrayscale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    ArkUINodeHandle nativeNode = nullptr;
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    }
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetGrayscale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetOnLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    if (secondArg.IsNull() || secondArg->IsUndefined() || !secondArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    panda::Local<panda::FunctionRef> func = secondArg->ToObject(vm);
    LoadEvent onLoad = [isJsView, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode)](
                           const std::string& xcomponentId) {
        auto vm = func.GetEcmaVM();
        CHECK_NULL_VOID(ArkTSUtils::CheckJavaScriptScope(vm));
        ACE_UINODE_TRACE(node);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT("XComponent.onLoad");
        PipelineContext::SetCallBackNode(node);
        std::vector<Local<JSValueRef>> argv;
#ifdef XCOMPONENT_SUPPORTED
        Local<JSValueRef> jsVal;
        if (Framework::XComponentClient::GetInstance().GetJSVal(const_cast<EcmaVM*>(vm), xcomponentId, jsVal)) {
            argv.emplace_back(jsVal);
        }
#endif
        auto result = func->Call(vm, func.ToLocal(), argv.data(), argv.size());
        if (isJsView) {
            TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] onLoad triggers", xcomponentId.c_str());
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        } else {
            TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] onLoad", xcomponentId.c_str());
        }
    };
    GetArkUINodeModifiers()->getXComponentModifier()->setXComponentOnLoad(nativeNode, reinterpret_cast<void*>(&onLoad));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetOnLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetOnDestroy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    if (secondArg.IsNull() || secondArg->IsUndefined() || !secondArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    panda::Local<panda::FunctionRef> func = secondArg->ToObject(vm);
    DestroyEvent onDestroy = [isJsView, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode)](
                                 const std::string& xcomponentId) {
        auto vm = func.GetEcmaVM();
        CHECK_NULL_VOID(ArkTSUtils::CheckJavaScriptScope(vm));
        ACE_UINODE_TRACE(node);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJsView) {
            TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] onDestroy", xcomponentId.c_str());
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        } else {
            TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponentNode[%{public}s] onDestroy", xcomponentId.c_str());
        }
    };
    GetArkUINodeModifiers()->getXComponentModifier()->setXComponentOnDestroy(
        nativeNode, reinterpret_cast<void*>(&onDestroy));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetOnDestroy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetEnableAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    if (secondArg.IsNull() || secondArg->IsUndefined()) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(
        ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::NativePointerRef::New(vm, nullptr));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));

    if (isJsView) {
        if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
            return panda::JSValueRef::Undefined(vm);
        }
        if (secondArg->IsNumber()) {
            bool boolValue = static_cast<bool>(secondArg->Uint32Value(vm));
            GetArkUINodeModifiers()->getXComponentModifier()->setXComponentEnableAnalyzer(nativeNode, boolValue);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsNumber()) {
        bool boolValue = static_cast<bool>(secondArg->Uint32Value(vm));
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentEnableAnalyzer(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentEnableAnalyzer(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetEnableAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentEnableAnalyzer(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetEnableSecure(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    if (secondArg.IsNull() || secondArg->IsUndefined()) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (isJsView) {
        if (type != XComponentType::SURFACE) {
            return panda::JSValueRef::Undefined(vm);
        }
        if (secondArg->IsNumber()) {
            bool boolValue = static_cast<bool>(secondArg->Uint32Value(vm));
            GetArkUINodeModifiers()->getXComponentModifier()->setXComponentEnableSecure(nativeNode, boolValue);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    if (secondArg->IsBoolean()) {
        bool boolValue = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentEnableSecure(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentEnableSecure(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetEnableSecure(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentEnableSecure(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetHdrBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    if (secondArg.IsNull() || secondArg->IsUndefined()) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));

    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        auto type = static_cast<XComponentType>(
            GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
        if (type != XComponentType::SURFACE) {
            return panda::JSValueRef::Undefined(vm);
        }
        float hdrBrightness = 1.0f;
        if (secondArg->IsNumber()) {
            hdrBrightness = static_cast<float>(secondArg->ToNumber(vm)->Value());
            hdrBrightness = std::clamp(hdrBrightness, 0.0f, 1.0f);
        }
        int32_t hdrType = INVALID_HDR_TYPE;
        if (!thirdArg.IsNull() && thirdArg->IsNumber()) {
            hdrType = thirdArg->Int32Value(vm);
            GetArkUINodeModifiers()->getXComponentModifier()->setXComponentHdrBrightness(
                nativeNode, hdrBrightness, hdrType);
        } else {
            GetArkUINodeModifiers()->getXComponentModifier()->setXComponentHdrBrightness(
                nativeNode, hdrBrightness, hdrType);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsNumber()) {
        float hdrBrightness = static_cast<float>(secondArg->ToNumber(vm)->Value());
        hdrBrightness = std::clamp(hdrBrightness, 0.0f, 1.0f);
        auto hdrType = thirdArg->IsNumber() ? thirdArg->Int32Value(vm) : INVALID_HDR_TYPE;
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentHdrBrightness(
            nativeNode, hdrBrightness, hdrType);
    } else {
        GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentHdrBrightness(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetHdrBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentHdrBrightness(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetEnableTransparentLayer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    if (secondArg.IsNull() || secondArg->IsUndefined()) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::SURFACE) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsNumber()) {
        bool enableTransparentLayer = static_cast<bool>(secondArg->Uint32Value(vm));
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentEnableTransparentLayer(
            nativeNode, enableTransparentLayer);
    } else if (isJsView) {
        return panda::JSValueRef::Undefined(vm);
    } else {
        GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentEnableTransparentLayer(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetEnableTransparentLayer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentEnableTransparentLayer(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetRenderFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    if (secondArg.IsNull() || secondArg->IsUndefined()) {
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(
        ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::NativePointerRef::New(vm, nullptr));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (isJsView) {
        if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
            return panda::JSValueRef::Undefined(vm);
        }
        auto renderFit = static_cast<int32_t>(RenderFit::RESIZE_FILL);
        if (type == XComponentType::TEXTURE) {
            renderFit = static_cast<int32_t>(RenderFit::TOP_LEFT);
        }
        if (secondArg->IsNumber()) {
            int32_t fitNumber = secondArg->Int32Value(vm);
            if (fitNumber >= static_cast<int32_t>(RenderFit::CENTER) &&
                fitNumber <= static_cast<int32_t>(RenderFit::RESIZE_COVER_BOTTOM_RIGHT)) {
                renderFit = fitNumber;
            }
        }
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentRenderFit(nativeNode, renderFit);
        return panda::JSValueRef::Undefined(vm);
    }

    auto renderFit = static_cast<int32_t>(RenderFit::TOP_LEFT);
    if (secondArg->IsNumber()) {
        renderFit = secondArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setXComponentRenderFit(nativeNode, renderFit);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetRenderFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentRenderFit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBlendMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> blendModeArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    Local<JSValueRef> blendApplyTypeArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type == XComponentType::TEXTURE && Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        int32_t blendModeValue = static_cast<int32_t>(BlendMode::NONE);
        int32_t blendApplyTypeValue = static_cast<int32_t>(BlendApplyType::FAST);
        if (blendModeArg.IsNull() || !blendModeArg->IsNumber()) {
            return panda::JSValueRef::Undefined(vm);
        }
        if (ParseJsBlendMode(vm, blendModeArg, blendApplyTypeArg, blendModeValue, blendApplyTypeValue)) {
            GetArkUINodeModifiers()->getXComponentModifier()->setXComponentBlendMode(
                nativeNode, static_cast<int32_t>(BlendMode::SRC_OVER), blendApplyTypeValue);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t blendModeValue = static_cast<int32_t>(BlendMode::NONE);
    int32_t blendApplyTypeValue = static_cast<int32_t>(BlendApplyType::FAST);
    if (ParseJsBlendMode(vm, blendModeArg, blendApplyTypeArg, blendModeValue, blendApplyTypeValue)) {
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentBlendMode(
            nativeNode, blendModeValue, blendApplyTypeValue);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBlendMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentBlendMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackgroundImage(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> srcArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    Local<JSValueRef> repeatArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::string src;
    std::string bundle;
    std::string module;
    RefPtr<PixelMap> pixmap = nullptr;
    ArkTSUtils::GetJsMediaBundleInfo(vm, srcArg, bundle, module);
    int32_t repeatIndex = 0;
    bool syncMode = false;
    CommonBridge::ParseJsBackgroundImageOptions(vm, repeatArg, repeatIndex, syncMode);
    GetArkUINodeModifiers()->getXComponentModifier()->setBackgroundImageSyncMode(nativeNode, syncMode);
    RefPtr<ResourceObject> backgroundImageResObj;
    auto bgImageRawPtr = AceType::RawPtr(backgroundImageResObj);
    auto theme = ArkTSUtils::GetThemeConstants(vm);
    auto themeRaw = AceType::RawPtr(theme);
    if (srcArg->IsString(vm)) {
        src = srcArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getXComponentModifier()->setBackgroundImage(
            nativeNode, src.c_str(), bundle.c_str(), module.c_str(), nullptr, themeRaw);
        GetArkUINodeModifiers()->getXComponentModifier()->clearResObj(nativeNode, "backgroundImageSrc");
    } else if (ArkTSUtils::ParseJsMedia(vm, srcArg, src, backgroundImageResObj)) {
        bgImageRawPtr = AceType::RawPtr(backgroundImageResObj);
        GetArkUINodeModifiers()->getXComponentModifier()->setBackgroundImage(
            nativeNode, src.c_str(), bundle.c_str(), module.c_str(), bgImageRawPtr, nullptr);
    } else {
#if defined(PIXEL_MAP_SUPPORTED)
        if (ArkTSUtils::IsDrawable(vm, srcArg)) {
            pixmap = ArkTSUtils::GetDrawablePixmap(vm, srcArg);
        } else {
            pixmap = ArkTSUtils::CreatePixelMapFromNapiValue(vm, srcArg);
        }
#endif
        if (pixmap) {
            auto pixelMapSharedPtr = pixmap->GetPixelMapSharedPtr();
            GetArkUINodeModifiers()->getXComponentModifier()->setBackgroundImagePixelMapByPixelMapPtr(
                nativeNode, &pixelMapSharedPtr);
        } else {
            GetArkUINodeModifiers()->getXComponentModifier()->setBackgroundImagePixelMapByPixelMapPtr(
                nativeNode, nullptr);
        }
        GetArkUINodeModifiers()->getXComponentModifier()->clearResObj(nativeNode, "backgroundImageSrc");
    }
    if (!repeatArg.IsNull() && !repeatArg->IsUndefined()) {
        if (repeatArg->IsNumber()) {
            repeatIndex = repeatArg->ToNumber(vm)->Value();
        }
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setBackgroundImageRepeat(nativeNode, repeatIndex);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackgroundImageSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> imageSizeArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (imageSizeArg.IsNull() || imageSizeArg->IsUndefined() ||
        (!imageSizeArg->IsNumber() && !imageSizeArg->IsObject(vm))) {
        GetArkUINodeModifiers()->getXComponentModifier()->setBackgroundImageSize(nativeNode, 0.0, 0.0,
            static_cast<int32_t>(BackgroundImageSizeType::AUTO), static_cast<int32_t>(BackgroundImageSizeType::AUTO),
            nullptr, nullptr);
        GetArkUINodeModifiers()->getXComponentModifier()->clearResObj(nativeNode, "backgroundImageSize");
        return panda::JSValueRef::Undefined(vm);
    }
    if (imageSizeArg->IsNumber()) {
        auto sizeType = static_cast<BackgroundImageSizeType>(imageSizeArg->Int32Value(vm));
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) &&
            (sizeType < BackgroundImageSizeType::CONTAIN || sizeType > BackgroundImageSizeType::FILL)) {
            sizeType = BackgroundImageSizeType::AUTO;
        }
        GetArkUINodeModifiers()->getXComponentModifier()->clearResObj(nativeNode, "backgroundImageSize");
        GetArkUINodeModifiers()->getXComponentModifier()->setBackgroundImageSize(
            nativeNode, 0.0, 0.0, static_cast<int32_t>(sizeType), static_cast<int32_t>(sizeType), nullptr, nullptr);
    } else {
        CalcDimension width;
        CalcDimension height;
        auto imageSizeObj = imageSizeArg->ToObject(vm);
        RefPtr<ResourceObject> resObjWidth;
        RefPtr<ResourceObject> resObjHeight;
        ArkTSUtils::ParseJsDimensionVp(
            vm, imageSizeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "width")), width, resObjWidth);
        ArkTSUtils::ParseJsDimensionVp(
            vm, imageSizeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "height")), height, resObjHeight);
        double valueWidth = width.ConvertToPx();
        double valueHeight = height.ConvertToPx();
        BackgroundImageSizeType typeWidth = BackgroundImageSizeType::LENGTH;
        BackgroundImageSizeType typeHeight = BackgroundImageSizeType::LENGTH;
        if (width.Unit() == DimensionUnit::PERCENT) {
            typeWidth = BackgroundImageSizeType::PERCENT;
            valueWidth = width.Value() * FULL_DIMENSION;
        }
        if (height.Unit() == DimensionUnit::PERCENT) {
            typeHeight = BackgroundImageSizeType::PERCENT;
            valueHeight = height.Value() * FULL_DIMENSION;
        }
        GetArkUINodeModifiers()->getXComponentModifier()->setBackgroundImageSize(nativeNode, 0.0, 0.0,
            static_cast<int32_t>(BackgroundImageSizeType::AUTO), static_cast<int32_t>(BackgroundImageSizeType::AUTO),
            AceType::RawPtr(resObjWidth), AceType::RawPtr(resObjHeight));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackgroundImagePosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> positionArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    double valueX = 0.0;
    double valueY = 0.0;
    DimensionUnit typeX = DimensionUnit::PX;
    DimensionUnit typeY = DimensionUnit::PX;
    bool isAlign = false;
    RefPtr<ResourceObject> resObjX;
    RefPtr<ResourceObject> resObjY;
    if (positionArg.IsNull() || positionArg->IsUndefined() ||
        (!positionArg->IsNumber() && !positionArg->IsObject(vm))) {
        constexpr int32_t size = 2;
        ArkUI_Float32 values[size] = { 0.0, 0.0 };
        ArkUI_Int32 types[size] = { static_cast<int32_t>(DimensionUnit::PX), static_cast<int32_t>(DimensionUnit::PX) };
        GetArkUINodeModifiers()->getXComponentModifier()->setBackgroundImagePosition(
            nativeNode, values, types, false, size, nullptr, nullptr);
        GetArkUINodeModifiers()->getXComponentModifier()->clearResObj(nativeNode, "backgroundImagePosition");
        return panda::JSValueRef::Undefined(vm);
    }
    if (positionArg->IsNumber()) {
        int32_t align = positionArg->Int32Value(vm);
        if (align >= 0 && align <= MAX_BG_ALIGN) {
            std::vector<std::pair<double, double>> vec = { { 0.0, 0.0 }, { HALF_DIMENSION, 0.0 },
                { FULL_DIMENSION, 0.0 }, { 0.0, HALF_DIMENSION }, { HALF_DIMENSION, HALF_DIMENSION },
                { FULL_DIMENSION, HALF_DIMENSION }, { 0.0, FULL_DIMENSION }, { HALF_DIMENSION, FULL_DIMENSION },
                { FULL_DIMENSION, FULL_DIMENSION } };
            valueX = vec[align].first;
            valueY = vec[align].second;
            typeX = DimensionUnit::PERCENT;
            typeY = DimensionUnit::PERCENT;
            isAlign = true;
        }
        GetArkUINodeModifiers()->getXComponentModifier()->clearResObj(nativeNode, "backgroundImagePosition");
    } else {
        auto positionObj = positionArg->ToObject(vm);
        CalcDimension x;
        CalcDimension y;
        ArkTSUtils::ParseJsDimensionVp(vm, positionObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "x")), x, resObjX);
        ArkTSUtils::ParseJsDimensionVp(vm, positionObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "y")), y, resObjY);
        valueX = x.Value();
        valueY = y.Value();
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            valueX = x.ConvertToPx();
            valueY = y.ConvertToPx();
        }
        if (x.Unit() == DimensionUnit::PERCENT) {
            valueX = x.Value();
            typeX = DimensionUnit::PERCENT;
        }
        if (y.Unit() == DimensionUnit::PERCENT) {
            valueY = y.Value();
            typeY = DimensionUnit::PERCENT;
        }
    }
    constexpr int32_t size = 2;
    ArkUI_Float32 values[size];
    ArkUI_Int32 types[size];
    values[INDEX_BG_POS_X] = static_cast<ArkUI_Float32>(valueX);
    types[INDEX_BG_POS_X] = static_cast<int32_t>(typeX);
    values[INDEX_BG_POS_Y] = static_cast<ArkUI_Float32>(valueY);
    types[INDEX_BG_POS_Y] = static_cast<int32_t>(typeY);
    auto xRawPtr = AceType::RawPtr(resObjX);
    auto yRawPtr = AceType::RawPtr(resObjY);
    GetArkUINodeModifiers()->getXComponentModifier()->setBackgroundImagePosition(
        nativeNode, values, types, isAlign, size, xRawPtr, yRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBlur(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> blurArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    Local<JSValueRef> grayscaleArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    Local<JSValueRef> disableSystemAdaptationArg = runtimeCallInfo->GetCallArgRef(ARG_LIBRARY_NAME);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    double blur = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, blurArg, blur)) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<ArkUI_Float32> grayscale;
    if (grayscaleArg->IsArray(vm)) {
        Local<panda::ArrayRef> params = Local<panda::ArrayRef>(grayscaleArg);
        auto grey1 = static_cast<ArkUI_Float32>(params->GetValueAt(vm, grayscaleArg, 0)->Uint32Value(vm));
        auto grey2 = static_cast<ArkUI_Float32>(params->GetValueAt(vm, grayscaleArg, 1)->Uint32Value(vm));
        grayscale = { grey1, grey2 };
    }
    bool disableSystemAdaptation = false;
    if (!disableSystemAdaptationArg.IsNull() && disableSystemAdaptationArg->IsObject(vm)) {
        auto disableSystemAdaptationArgObj = disableSystemAdaptationArg->ToObject(vm);
        auto disableAdaptationVal =
            disableSystemAdaptationArgObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "disableSystemAdaptation"));
        if (disableAdaptationVal->IsNumber()) {
            disableSystemAdaptation = static_cast<bool>(disableAdaptationVal->Int32Value(vm));
        }
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setBlur(nativeNode, static_cast<ArkUI_Float32>(blur),
        grayscale.data(), static_cast<ArkUI_Int32>(grayscale.size()), disableSystemAdaptation);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackdropBlur(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> blurArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    Local<JSValueRef> grayscaleArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    Local<JSValueRef> disableSystemAdaptationArg = runtimeCallInfo->GetCallArgRef(ARG_LIBRARY_NAME);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    double blur = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, blurArg, blur)) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<ArkUI_Float32> grayscale;
    if (grayscaleArg->IsArray(vm)) {
        Local<panda::ArrayRef> params = Local<panda::ArrayRef>(grayscaleArg);
        auto grey1 = static_cast<ArkUI_Float32>(params->GetValueAt(vm, grayscaleArg, 0)->Uint32Value(vm));
        auto grey2 = static_cast<ArkUI_Float32>(params->GetValueAt(vm, grayscaleArg, 1)->Uint32Value(vm));
        grayscale = { grey1, grey2 };
    }
    bool disableSystemAdaptation = false;
    if (!disableSystemAdaptationArg.IsNull() && disableSystemAdaptationArg->IsObject(vm)) {
        auto disableSystemAdaptationArgObj = disableSystemAdaptationArg->ToObject(vm);
        auto disableAdaptationVal =
            disableSystemAdaptationArgObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "disableSystemAdaptation"));
        if (disableAdaptationVal->IsNumber()) {
            disableSystemAdaptation = static_cast<bool>(disableAdaptationVal->Int32Value(vm));
        }
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setBackdropBlur(nativeNode, static_cast<ArkUI_Float32>(blur),
        grayscale.data(), static_cast<ArkUI_Int32>(grayscale.size()), disableSystemAdaptation);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBrightness(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> brightnessArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    CalcDimension value;
    if (!brightnessArg.IsNull() && !brightnessArg->IsUndefined()) {
        if (!ArkTSUtils::ParseJsDimensionVp(vm, brightnessArg, value)) {
            value.SetValue(1.0);
            GetArkUINodeModifiers()->getXComponentModifier()->setBrightness(
                nativeNode, static_cast<ArkUI_Float64>(value.Value()), static_cast<ArkUI_Int32>(value.Unit()));
            return panda::JSValueRef::Undefined(vm);
        }
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setBrightness(
        nativeNode, static_cast<ArkUI_Float64>(value.Value()), static_cast<ArkUI_Int32>(value.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetSaturate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> saturateArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension value;
    if (!saturateArg.IsNull() && !saturateArg->IsUndefined()) {
        if (!ArkTSUtils::ParseJsDimensionVp(vm, saturateArg, value)) {
            value.SetValue(1.0);
            GetArkUINodeModifiers()->getXComponentModifier()->setSaturate(
                nativeNode, static_cast<ArkUI_Float32>(value.Value()), static_cast<ArkUI_Int32>(value.Unit()));
            return panda::JSValueRef::Undefined(vm);
        }
        if (LessNotEqual(value.Value(), 0.0)) {
            value.SetValue(0.0);
        }
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setSaturate(
        nativeNode, static_cast<ArkUI_Float32>(value.Value()), static_cast<ArkUI_Int32>(value.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetContrast(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> contrastArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension value;
    if (!contrastArg.IsNull() && !contrastArg->IsUndefined()) {
        if (!ArkTSUtils::ParseJsDimensionVp(vm, contrastArg, value)) {
            value.SetValue(1.0);
            GetArkUINodeModifiers()->getXComponentModifier()->setContrast(
                nativeNode, static_cast<ArkUI_Float64>(value.Value()), static_cast<ArkUI_Int32>(value.Unit()));
            return panda::JSValueRef::Undefined(vm);
        }
        if (LessNotEqual(value.Value(), 0.0)) {
            value.SetValue(0.0);
        }
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setContrast(
        nativeNode, static_cast<ArkUI_Float64>(value.Value()), static_cast<ArkUI_Int32>(value.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetInvert(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> invertArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    double invertValue = 0.0;
    if (ArkTSUtils::ParseJsDouble(vm, invertArg, invertValue)) {
        invertValue = std::clamp(invertValue, 0.0, 1.0);
        ArkUI_Float32 invert[] = { static_cast<ArkUI_Float32>(invertValue) };
        GetArkUINodeModifiers()->getXComponentModifier()->setInvert(nativeNode, invert, 1);
    } else if (!invertArg.IsNull() || invertArg->IsObject(vm)) {
        auto invertObj = invertArg->ToObject(vm);
        double low = 0.0;
        if (ArkTSUtils::ParseJsDouble(vm, invertObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "low")), low)) {
            low = std::clamp(low, 0.0, 1.0);
        }
        double high = 0.0;
        if (ArkTSUtils::ParseJsDouble(vm, invertObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "high")), high)) {
            high = std::clamp(high, 0.0, 1.0);
        }
        double threshold = 0.0;
        if (ArkTSUtils::ParseJsDouble(
            vm, invertObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "threshold")), threshold)) {
            threshold = std::clamp(threshold, 0.0, 1.0);
        }
        double thresholdRange = 0.0;
        if (ArkTSUtils::ParseJsDouble(
            vm, invertObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "thresholdRange")), thresholdRange)) {
            thresholdRange = std::clamp(thresholdRange, 0.0, 1.0);
        }
        ArkUI_Float32 invert[] = { static_cast<ArkUI_Float32>(low), static_cast<ArkUI_Float32>(high),
            static_cast<ArkUI_Float32>(threshold), static_cast<ArkUI_Float32>(thresholdRange) };
        GetArkUINodeModifiers()->getXComponentModifier()->setInvert(nativeNode, invert, INVERT_OPTION_PARAM_SIZE);
    } else {
        GetArkUINodeModifiers()->getXComponentModifier()->resetInvert(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetSepia(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> sepiaArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    double sepia = 0.0;
    if (sepiaArg->IsNumber()) {
        sepia = sepiaArg->ToNumber(vm)->Value();
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setSepia(nativeNode, static_cast<ArkUI_Float32>(sepia));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetHueRotate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> hueRotateArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }

    std::optional<float> degree;
    if (!hueRotateArg.IsNull() && hueRotateArg->IsNumber()) {
        degree = static_cast<float>(hueRotateArg->ToNumber(vm)->Value());
    } else if (!hueRotateArg.IsNull() && hueRotateArg->IsString(vm)) {
        degree = static_cast<float>(StringUtils::StringToDegree(hueRotateArg->ToString(vm)->ToString(vm)));
    } else {
        GetArkUINodeModifiers()->getXComponentModifier()->resetHueRotate(nativeNode);
    }
    float deg = 0.0f;
    if (degree) {
        deg = degree.value();
        degree.reset();
    }
    deg = std::fmod(deg, ROUND_UNIT);
    if (deg < 0.0f) {
        deg += ROUND_UNIT;
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setHueRotate(nativeNode, deg);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetColorBlend(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    Color color;
    RefPtr<ResourceObject> colorBlendObj;
    if (!ArkTSUtils::ParseJsColor(vm, colorArg, color, colorBlendObj)) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            color = Color::TRANSPARENT;
        } else {
            return panda::JSValueRef::Undefined(vm);
        }
    }
    auto rawPtr = AceType::RawPtr(colorBlendObj);
    GetArkUINodeModifiers()->getXComponentModifier()->setColorBlend(nativeNode, color.GetValue(), rawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetSphericalEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> radioArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    double radio = 0.0;
    if (!radioArg.IsNull() && radioArg->IsNumber()) {
        radio = std::clamp(radioArg->ToNumber(vm)->Value(), 0.0, 1.0);
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setSphericalEffect(nativeNode, static_cast<ArkUI_Float64>(radio));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetLightUpEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> radioArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }
    double radio = 1.0;
    if (!radioArg.IsNull() && radioArg->IsNumber()) {
        radio = std::clamp(radioArg->ToNumber(vm)->Value(), 0.0, 1.0);
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setLightUpEffect(nativeNode, static_cast<ArkUI_Float32>(radio));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetPixelStretchEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }

    if (secondArg.IsNull() || secondArg->IsUndefined()) {
        return panda::JSValueRef::Undefined(vm);
    }

    if (!secondArg->IsObject(vm)) {
        PixStretchEffectOption option;
        option.ResetValue();
        return panda::JSValueRef::Undefined(vm);
    }
    auto effectObj = secondArg->ToObject(vm);
    RefPtr<ResourceObject> resObjLeft;
    RefPtr<ResourceObject> resObjRight;
    RefPtr<ResourceObject> resObjTop;
    RefPtr<ResourceObject> resObjBottom;
    CalcDimension left;
    CalcDimension right;
    CalcDimension top;
    CalcDimension bottom;
    PixStretchEffectOption option;
    if (!SystemProperties::ConfigChangePerform()) {
        ArkTSUtils::ParseJsDimensionVp(vm, effectObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "left")), left);
        ArkTSUtils::ParseJsDimensionVp(vm, effectObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "right")), right);
        ArkTSUtils::ParseJsDimensionVp(vm, effectObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "top")), top);
        ArkTSUtils::ParseJsDimensionVp(vm, effectObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bottom")), bottom);
    } else {
        ArkTSUtils::ParseJsDimensionVp(
            vm, effectObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "left")), left, resObjLeft);
        ArkTSUtils::ParseJsDimensionVp(
            vm, effectObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "top")), right, resObjRight);
        ArkTSUtils::ParseJsDimensionVp(
            vm, effectObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "right")), top, resObjTop);
        ArkTSUtils::ParseJsDimensionVp(
            vm, effectObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bottom")), bottom, resObjBottom);
    }
    ArkUI_Float32 values[] = { static_cast<ArkUI_Float32>(left.Value()), static_cast<ArkUI_Float32>(top.Value()),
        static_cast<ArkUI_Float32>(right.Value()), static_cast<ArkUI_Float32>(bottom.Value()) };
    int units[] = { static_cast<int>(left.Unit()), static_cast<int>(top.Unit()), static_cast<int>(right.Unit()),
        static_cast<int>(bottom.Unit()) };
    GetArkUINodeModifiers()->getXComponentModifier()->setPixelStretchEffect(
        nativeNode, values, units, STRETCH_PARAM_SIZE, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

void GetFractionStops(
    std::vector<std::pair<float, float>>& fractionStops, const Local<JSValueRef>& fractionStopsArg, const EcmaVM* vm)
{
    if (!fractionStopsArg->IsArray(vm)) {
        return;
    }
    auto array = panda::Local<panda::ArrayRef>(fractionStopsArg);
    auto length = ArkTSUtils::GetArrayLength(vm, array);
    if (length <= 1) {
        return;
    }
    float tmpPos = -1.0f;
    for (uint32_t index = 0; index < length; index++) {
        std::pair<float, float> fractionStop;
        auto item = panda::ArrayRef::GetValueAt(vm, array, index);
        if (!item->IsArray(vm)) {
            continue;
        }
        auto subArray = panda::Local<panda::ArrayRef>(item);
        if (ArkTSUtils::GetArrayLength(vm, subArray) < FRACTION_STOP_PAIR_SIZE) {
            continue;
        }

        double value = 0.0;
        if (ArkTSUtils::ParseJsDouble(vm, panda::ArrayRef::GetValueAt(vm, subArray, 0), value)) {
            value = std::clamp(value, 0.0, 1.0);
            fractionStop.first = static_cast<float>(value);
        }
        value = 0;
        if (ArkTSUtils::ParseJsDouble(vm, panda::ArrayRef::GetValueAt(vm, subArray, 1), value)) {
            value = std::clamp(value, 0.0, 1.0);
            fractionStop.first = static_cast<float>(value);
        }
        if (fractionStop.second <= tmpPos) {
            fractionStops.clear();
            return;
        }
        tmpPos = fractionStop.second;
        fractionStops.push_back(fractionStop);
    }
}

ArkUINativeModuleValue XComponentBridge::SetLinearGradientBlur(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> blurRadiusArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(frameNode);
    auto type =
        static_cast<XComponentType>(GetArkUINodeModifiers()->getXComponentModifier()->getXComponentType(nativeNode));
    if (type != XComponentType::NODE) {
        return panda::JSValueRef::Undefined(vm);
    }

    if (blurRadiusArg.IsNull() || blurRadiusArg->IsUndefined() || optionsArg.IsNull() || optionsArg->IsUndefined()) {
        return panda::JSValueRef::Undefined(vm);
    }
    double blurRadius = 0.0;
    ArkTSUtils::ParseJsDouble(vm, blurRadiusArg, blurRadius);
    std::vector<std::pair<float, float>> fractionStops;
    auto direction = static_cast<int32_t>(GradientDirection::BOTTOM);
    if (optionsArg->IsObject(vm)) {
        auto optionsObj = optionsArg->ToObject(vm);
        auto fractionStopsArray = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "fractionStops"));
        GetFractionStops(fractionStops, fractionStopsArray, vm);
        auto directionVal = optionsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "direction"));
        auto directionValue = static_cast<int32_t>(GradientDirection::BOTTOM);
        if (!directionVal->IsUndefined()) {
            directionValue = directionVal->Int32Value(vm);
            if (directionValue < static_cast<int8_t>(GradientDirection::LEFT) ||
                directionValue >= static_cast<int8_t>(GradientDirection::NONE)) {
                directionValue = static_cast<int8_t>(GradientDirection::BOTTOM);
            }
        }
        direction = directionValue;
    }
    if (static_cast<int32_t>(fractionStops.size()) <= 1) {
        fractionStops.clear();
        fractionStops.push_back(std::pair<float, float>(0.0f, 0.0f));
        fractionStops.push_back(std::pair<float, float>(0.0f, 1.0f));
    }
    CalcDimension dimensionRadius(static_cast<float>(blurRadius), DimensionUnit::PX);
    NG::LinearGradientBlurPara blurPara(dimensionRadius, fractionStops, static_cast<NG::GradientDirection>(direction));
    GetArkUINodeModifiers()->getXComponentModifier()->setLinearGradientBlur(
        nativeNode, reinterpret_cast<void*>(&blurPara));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::IsCommonEventAvailable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    ACE_UINODE_TRACE(reinterpret_cast<FrameNode*>(nativeNode));
    bool result = GetArkUINodeModifiers()->getXComponentModifier()->isCommonEventAvailable(nativeNode);
    return panda::BooleanRef::New(vm, result);
}
} // namespace OHOS::Ace::NG
