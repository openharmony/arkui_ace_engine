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

#include "core/components_ng/pattern/video/bridge/arkts_native_video_bridge.h"

#include <algorithm>
#include <utility>

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_video_controller.h"
#include "bridge/declarative_frontend/jsview/js_video_controller_async.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/video/bridge/video_create_controller_param.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"
#ifdef SUPPORT_JSSTACK
#include "xpower_event_jsvm.h"
#endif

namespace OHOS::Ace::NG {

constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr double DEFAULT_PROGRESS_RATE = 1.0;

namespace {
constexpr double VALID_SPEEDS[] = { 0.125, 0.25, 0.50, 0.75, 1.00, 1.25, 1.50, 1.75, 2.00, 3.00 };
using VideoEventCallback = std::function<void(const std::string&)>;

bool ParseColorMetricsToColor(const EcmaVM* vm, const Local<JSValueRef>& jsValue, Color& result)
{
    return ArkTSUtils::ParseColorMetricsToColor(vm, jsValue, result);
}

Local<JSValueRef> GetObjectProperty(const EcmaVM* vm, const Local<panda::ObjectRef>& obj, const char* propertyName)
{
    return obj->Get(vm, panda::StringRef::NewFromUtf8(vm, propertyName));
}

bool GetNativeNode(ArkUINodeHandle& nativeNode, EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return ArkTSUtils::GetNativeNode(nativeNode, runtimeCallInfo->GetCallArgRef(NUM_0), vm);
}

bool IsValidSpeed(double speed)
{
    return std::find(std::begin(VALID_SPEEDS), std::end(VALID_SPEEDS), speed) != std::end(VALID_SPEEDS);
}

void SetContentTransition(ContentTransitionType contentTransitionType)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    VideoModelNG::SetContentTransition(frameNode, contentTransitionType);
}

RefPtr<VideoControllerV2> ParseVideoController(const EcmaVM* vm, const Local<JSValueRef>& controllerArg)
{
    if (!controllerArg->IsObject(vm)) {
        return nullptr;
    }
    auto controllerObj = controllerArg->ToObject(vm);
    if (controllerObj->GetNativePointerFieldCount(vm) < NUM_1) {
        return nullptr;
    }
    auto* jsController = static_cast<Framework::JSVideoController*>(controllerObj->GetNativePointerField(vm, NUM_0));
    CHECK_NULL_RETURN(jsController, nullptr);
    jsController->SetInstanceId(Container::CurrentId());
    return jsController->GetController();
}

RefPtr<VideoControllerAsync> ParseVideoControllerAsync(const EcmaVM* vm, const Local<JSValueRef>& controllerArg)
{
    if (!controllerArg->IsObject(vm)) {
        return nullptr;
    }
    auto controllerObj = controllerArg->ToObject(vm);
    if (controllerObj->GetNativePointerFieldCount(vm) < NUM_1) {
        return nullptr;
    }
    auto* jsController =
        static_cast<Framework::JSVideoControllerAsync*>(controllerObj->GetNativePointerField(vm, NUM_0));
    CHECK_NULL_RETURN(jsController, nullptr);
    jsController->SetInstanceId(Container::CurrentId());
    return jsController->GetController();
}

void ParsePosterOptions(const EcmaVM* vm, const Local<JSValueRef>& posterOptionsValue, bool& showFirstFrame)
{
    if (!posterOptionsValue->IsObject(vm)) {
        return;
    }
    auto posterOptionsObj = posterOptionsValue->ToObject(vm);
    auto showFirstFrameValue = GetObjectProperty(vm, posterOptionsObj, "showFirstFrame");
    if (showFirstFrameValue->IsBoolean()) {
        showFirstFrame = showFirstFrameValue->ToBoolean(vm)->Value();
    }
    auto contentTransitionValue = GetObjectProperty(vm, posterOptionsObj, "contentTransitionEffect");
    ContentTransitionType contentTransitionType = ContentTransitionType::IDENTITY;
    ArkTSUtils::ParseContentTransitionEffect(vm, contentTransitionValue, contentTransitionType);
    SetContentTransition(contentTransitionType);
}

void SetJsViewPosterSource(const EcmaVM* vm, const Local<JSValueRef>& previewUriValue)
{
    auto* videoModifier = GetArkUINodeModifiers()->getVideoModifier();
    CHECK_NULL_VOID(videoModifier);
    std::string previewUri;
    std::string bundleName;
    std::string moduleName;
    ArkTSUtils::GetJsMediaBundleInfo(vm, previewUriValue, bundleName, moduleName);
    if (previewUriValue->IsUndefined() || previewUriValue->IsNull()) {
        videoModifier->setPosterSourceInfo(previewUri.c_str(), "", "");
        return;
    }
    auto noPixMap = ArkTSUtils::ParseJsMedia(vm, previewUriValue, previewUri, true);
    if (noPixMap) {
        videoModifier->setPosterSourceInfo(previewUri.c_str(), bundleName.c_str(), moduleName.c_str());
        return;
    }
#if defined(PIXEL_MAP_SUPPORTED)
    RefPtr<PixelMap> pixMap = ArkTSUtils::CreatePixelMapFromNapiValue(vm, previewUriValue);
    videoModifier->setPosterSourceByPixelMap(&pixMap);
#endif
}

void SetJsViewImageAIOptions(const EcmaVM* vm, const Local<JSValueRef>& imageAIOptionsValue)
{
    if (!imageAIOptionsValue->IsObject(vm)) {
        return;
    }
    auto* videoModifier = GetArkUINodeModifiers()->getVideoModifier();
    CHECK_NULL_VOID(videoModifier);
    auto optionsValue = ArkTSUtils::CreateNapiValue(vm, imageAIOptionsValue);
    CHECK_NULL_VOID(optionsValue);
    videoModifier->setImageAIOptions(optionsValue);
}

bool SetNodeAnalyzerConfig(const EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& configValue)
{
    auto* videoModifier = GetArkUINodeModifiers()->getVideoModifier();
    CHECK_NULL_RETURN(videoModifier, false);
    auto nativeValue = ArkTSUtils::CreateNapiValue(vm, configValue);
    CHECK_NULL_RETURN(nativeValue, false);
    videoModifier->setAnalyzerConfig(nativeNode, nativeValue);
    return true;
}

FrameNode* GetFrameNodeForCallback(bool isJsView, ArkUINodeHandle nativeNode)
{
    if (isJsView) {
        return ViewStackProcessor::GetInstance()->GetMainFrameNode();
    }
    return reinterpret_cast<FrameNode*>(nativeNode);
}
} // namespace

Local<JSValueRef> VideoBridge::GetArgRef(ArkUIRuntimeCallInfo* runtimeCallInfo, int32_t argIndex)
{
    return runtimeCallInfo->GetCallArgRef(argIndex);
}

ArkUINativeModuleValue VideoBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (!firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto videoObj = firstArg->ToObject(vm);
    auto srcValue = GetObjectProperty(vm, videoObj, "src");
    auto posterOptionsValue = GetObjectProperty(vm, videoObj, "posterOptions");
    auto previewUriValue = GetObjectProperty(vm, videoObj, "previewUri");
    auto currentProgressRateValue = GetObjectProperty(vm, videoObj, "currentProgressRate");
    auto controllerAsyncValue = GetObjectProperty(vm, videoObj, "controllerAsync");
    auto controllerValue = GetObjectProperty(vm, videoObj, "controller");
    auto imageAIOptionsValue = GetObjectProperty(vm, videoObj, "imageAIOptions");
    auto* videoModifier = GetArkUINodeModifiers()->getVideoModifier();
    CHECK_NULL_RETURN(videoModifier, panda::JSValueRef::Undefined(vm));

    VideoCreateControllerParam createParam;
    createParam.controllerAsync = ParseVideoControllerAsync(vm, controllerAsyncValue);
    if (createParam.controllerAsync) {
        createParam.type = VideoCreateControllerType::ASYNC;
    } else {
        createParam.controller = ParseVideoController(vm, controllerValue);
        createParam.type = createParam.controller ? VideoCreateControllerType::SYNC : VideoCreateControllerType::NONE;
    }
    videoModifier->createModel(&createParam);

    std::string bundleNameSrc;
    std::string moduleNameSrc;
    std::string src;
    ArkTSUtils::ParseJsMedia(vm, srcValue, src, true);
    ArkTSUtils::GetJsMediaBundleInfo(vm, srcValue, bundleNameSrc, moduleNameSrc);
    videoModifier->setSrc(src.c_str(), bundleNameSrc.c_str(), moduleNameSrc.c_str());

    bool showFirstFrame = false;
    ParsePosterOptions(vm, posterOptionsValue, showFirstFrame);
    videoModifier->setShowFirstFrame(showFirstFrame);

    double currentProgressRate = DEFAULT_PROGRESS_RATE;
    ArkTSUtils::ParseJsDouble(vm, currentProgressRateValue, currentProgressRate);
    if (currentProgressRateValue->IsNumber() || IsValidSpeed(currentProgressRate)) {
        videoModifier->setProgressRate(currentProgressRate);
    } else {
        videoModifier->setProgressRate(DEFAULT_PROGRESS_RATE);
    }

    SetJsViewImageAIOptions(vm, imageAIOptionsValue);
    SetJsViewPosterSource(vm, previewUriValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetAutoPlay(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> secondArg = GetArgRef(runtimeCallInfo, 1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        bool autoPlay = false;
        if (secondArg->IsBoolean()) {
            autoPlay = secondArg->ToBoolean(vm)->Value();
#ifdef SUPPORT_JSSTACK
            HiviewDFX::ReportXPowerJsStackSysEvent(vm, "STREAM_CHANGE", "SRC=Video");
#endif
        }
        GetArkUINodeModifiers()->getVideoModifier()->setAutoPlay(nativeNode, static_cast<uint32_t>(autoPlay));
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsBoolean()) {
        uint32_t autoPlay = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getVideoModifier()->setAutoPlay(nativeNode, autoPlay);
    } else {
        GetArkUINodeModifiers()->getVideoModifier()->resetAutoPlay(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetAutoPlay(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetAutoPlay(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetControls(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = GetArgRef(runtimeCallInfo, 1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t controlsValue = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getVideoModifier()->setVideoControls(nativeNode, controlsValue);
    } else {
        GetArkUINodeModifiers()->getVideoModifier()->resetVideoControls(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetControls(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetVideoControls(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetObjectFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> secondArg = GetArgRef(runtimeCallInfo, NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        ImageFit imageFit = ImageFit::COVER;
        if (secondArg->IsUndefined()) {
            GetArkUINodeModifiers()->getVideoModifier()->setVideoObjectFit(nativeNode, static_cast<int32_t>(imageFit));
            return panda::JSValueRef::Undefined(vm);
        }
        if (secondArg->IsNumber()) {
            imageFit = static_cast<ImageFit>(secondArg->Int32Value(vm));
        }
        GetArkUINodeModifiers()->getVideoModifier()->setVideoObjectFit(nativeNode, static_cast<int32_t>(imageFit));
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsNumber()) {
        int32_t imageFit = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getVideoModifier()->setVideoObjectFit(nativeNode, imageFit);
    } else {
        GetArkUINodeModifiers()->getVideoModifier()->resetVideoObjectFit(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetObjectFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetVideoObjectFit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = GetArgRef(runtimeCallInfo, 1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getVideoModifier()->setVideoLoop(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getVideoModifier()->resetVideoLoop(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetVideoLoop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetMuted(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> secondArg = GetArgRef(runtimeCallInfo, 1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        bool muted = false;
        if (secondArg->IsBoolean()) {
            muted = secondArg->ToBoolean(vm)->Value();
#ifdef SUPPORT_JSSTACK
            HiviewDFX::ReportXPowerJsStackSysEvent(vm, "VOLUME_CHANGE", "SRC=Video");
#endif
        }
        GetArkUINodeModifiers()->getVideoModifier()->setVideoMuted(nativeNode, static_cast<uint32_t>(muted));
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getVideoModifier()->setVideoMuted(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getVideoModifier()->resetVideoMuted(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetMuted(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetVideoMuted(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> opacityArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    double opacity;
    if (!ArkTSUtils::ParseJsDouble(vm, opacityArg, opacity)) {
        GetArkUINodeModifiers()->getVideoModifier()->resetVideoOpacity(nativeNode);
    } else {
        GetArkUINodeModifiers()->getVideoModifier()->setVideoOpacity(nativeNode, static_cast<ArkUI_Float32>(opacity));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getVideoModifier()->resetVideoOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    CommonBridge::SetTransitionPassThrough(runtimeCallInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    CommonBridge::ResetTransitionPassThrough(runtimeCallInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetVideoSurfaceBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = GetArgRef(runtimeCallInfo, 1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    Color color;
    if (!ParseColorMetricsToColor(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getVideoModifier()->resetVideoSurfaceBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getVideoModifier()->setVideoSurfaceBackgroundColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetVideoSurfaceBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetVideoSurfaceBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetShortcutKeyEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> secondArg = GetArgRef(runtimeCallInfo, 1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        bool value = secondArg->IsBoolean() ? secondArg->ToBoolean(vm)->Value() : false;
        GetArkUINodeModifiers()->getVideoModifier()->setVideoShortcutKeyEnabled(
            nativeNode, static_cast<uint32_t>(value));
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getVideoModifier()->setVideoShortcutKeyEnabled(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getVideoModifier()->resetVideoShortcutKeyEnabled(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetShortcutKeyEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetVideoShortcutKeyEnabled(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetOnStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> callbackArg = GetArgRef(runtimeCallInfo, 1);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (isJsView && !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getVideoModifier()->resetOnStart(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNodeForCallback(isJsView, nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto weakNode = AceType::WeakClaim(frameNode);
    VideoEventCallback callback = [vm, isJsView, weakNode, func = panda::CopyableGlobal(vm, func)](
                                      const std::string& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        const char* keys[] = { "start" };
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(value);
        CHECK_NULL_VOID(argsPtr);
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, argsPtr->GetString(keys[0]).c_str()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(const_cast<std::string*>(&value)));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getVideoModifier()->setOnStart(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetOnStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetOnStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetOnPause(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> callbackArg = GetArgRef(runtimeCallInfo, 1);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (isJsView && !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getVideoModifier()->resetOnPause(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNodeForCallback(isJsView, nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto weakNode = AceType::WeakClaim(frameNode);
    VideoEventCallback callback = [vm, isJsView, weakNode, func = panda::CopyableGlobal(vm, func)](
                                      const std::string& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        const char* keys[] = { "pause" };
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(value);
        CHECK_NULL_VOID(argsPtr);
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, argsPtr->GetString(keys[0]).c_str()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(const_cast<std::string*>(&value)));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getVideoModifier()->setOnPause(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetOnPause(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetOnPause(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetOnFinish(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> callbackArg = GetArgRef(runtimeCallInfo, 1);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (isJsView && !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getVideoModifier()->resetOnFinish(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNodeForCallback(isJsView, nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto weakNode = AceType::WeakClaim(frameNode);
    VideoEventCallback callback = [vm, isJsView, weakNode, func = panda::CopyableGlobal(vm, func)](
                                      const std::string& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        const char* keys[] = { "finish" };
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(value);
        CHECK_NULL_VOID(argsPtr);
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, argsPtr->GetString(keys[0]).c_str()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(const_cast<std::string*>(&value)));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getVideoModifier()->setOnFinish(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetOnFinish(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetOnFinish(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetOnFullscreenChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> callbackArg = GetArgRef(runtimeCallInfo, 1);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (isJsView && !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getVideoModifier()->resetOnFullscreenChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNodeForCallback(isJsView, nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto weakNode = AceType::WeakClaim(frameNode);
    VideoEventCallback callback = [vm, isJsView, weakNode, func = panda::CopyableGlobal(vm, func)](
                                      const std::string& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        const char* keys[] = { "fullscreen" };
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(value);
        CHECK_NULL_VOID(argsPtr);
        Local<JSValueRef> values[] = { panda::BooleanRef::New(vm, argsPtr->GetBool(keys[0])) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(const_cast<std::string*>(&value)));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getVideoModifier()->setOnFullscreenChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetOnFullscreenChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetOnFullscreenChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetOnPrepared(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> callbackArg = GetArgRef(runtimeCallInfo, 1);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (isJsView && !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getVideoModifier()->resetOnPrepared(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNodeForCallback(isJsView, nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto weakNode = AceType::WeakClaim(frameNode);
    VideoEventCallback callback = [vm, isJsView, weakNode, func = panda::CopyableGlobal(vm, func)](
                                      const std::string& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        const char* keys[] = { "duration" };
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(value);
        CHECK_NULL_VOID(argsPtr);
        auto durationValue = isJsView ? panda::NumberRef::New(vm, argsPtr->GetDouble(keys[0]))
                                      : panda::NumberRef::New(vm, argsPtr->GetInt(keys[0]));
        Local<JSValueRef> values[] = { durationValue };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(const_cast<std::string*>(&value)));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getVideoModifier()->setOnPrepared(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetOnPrepared(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetOnPrepared(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetOnSeeking(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> callbackArg = GetArgRef(runtimeCallInfo, 1);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (isJsView && !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getVideoModifier()->resetOnSeeking(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNodeForCallback(isJsView, nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto weakNode = AceType::WeakClaim(frameNode);
    VideoEventCallback callback = [vm, isJsView, weakNode, func = panda::CopyableGlobal(vm, func)](
                                      const std::string& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        const char* keys[] = { "time" };
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(value);
        CHECK_NULL_VOID(argsPtr);
        auto durationValue = isJsView ? panda::NumberRef::New(vm, argsPtr->GetDouble(keys[0]))
                                      : panda::NumberRef::New(vm, argsPtr->GetInt(keys[0]));
        Local<JSValueRef> values[] = { durationValue };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(const_cast<std::string*>(&value)));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getVideoModifier()->setOnSeeking(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetOnSeeking(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetOnSeeking(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetOnSeeked(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> callbackArg = GetArgRef(runtimeCallInfo, 1);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (isJsView && !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getVideoModifier()->resetOnSeeked(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNodeForCallback(isJsView, nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto weakNode = AceType::WeakClaim(frameNode);
    VideoEventCallback callback = [vm, isJsView, weakNode, func = panda::CopyableGlobal(vm, func)](
                                      const std::string& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        const char* keys[] = { "time" };
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(value);
        CHECK_NULL_VOID(argsPtr);
        auto durationValue = isJsView ? panda::NumberRef::New(vm, argsPtr->GetDouble(keys[0]))
                                      : panda::NumberRef::New(vm, argsPtr->GetInt(keys[0]));
        Local<JSValueRef> values[] = { durationValue };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(const_cast<std::string*>(&value)));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getVideoModifier()->setOnSeeked(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetOnSeeked(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetOnSeeked(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetOnUpdate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> callbackArg = GetArgRef(runtimeCallInfo, 1);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (isJsView && !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getVideoModifier()->resetOnUpdate(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNodeForCallback(isJsView, nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto weakNode = AceType::WeakClaim(frameNode);
    VideoEventCallback callback = [vm, isJsView, weakNode, func = panda::CopyableGlobal(vm, func)](
                                      const std::string& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        const char* keys[] = { "time" };
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(value);
        CHECK_NULL_VOID(argsPtr);
        auto durationValue = isJsView ? panda::NumberRef::New(vm, argsPtr->GetDouble(keys[0]))
                                      : panda::NumberRef::New(vm, argsPtr->GetInt(keys[0]));
        Local<JSValueRef> values[] = { durationValue };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(const_cast<std::string*>(&value)));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getVideoModifier()->setOnUpdate(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetOnUpdate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetOnUpdate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetOnError(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> callbackArg = GetArgRef(runtimeCallInfo, 1);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (isJsView && !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getVideoModifier()->resetOnError(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNodeForCallback(isJsView, nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto weakNode = AceType::WeakClaim(frameNode);
    VideoEventCallback callback = [vm, isJsView, weakNode, func = panda::CopyableGlobal(vm, func)](
                                      const std::string& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        const char* keys[] = { "code", "name", "message" };
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(value);
        CHECK_NULL_VOID(argsPtr);
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, argsPtr->GetInt(keys[0])),
            panda::StringRef::NewFromUtf8(vm, argsPtr->GetString(keys[1]).c_str()),
            panda::StringRef::NewFromUtf8(vm, argsPtr->GetString(keys[2]).c_str()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(const_cast<std::string*>(&value)));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getVideoModifier()->setOnError(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetOnError(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetOnError(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetOnStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> callbackArg = GetArgRef(runtimeCallInfo, 1);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (isJsView && !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isJsView && (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm))) {
        GetArkUINodeModifiers()->getVideoModifier()->resetOnStop(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNodeForCallback(isJsView, nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto weakNode = AceType::WeakClaim(frameNode);
    VideoEventCallback callback = [vm, isJsView, weakNode, func = panda::CopyableGlobal(vm, func)](
                                      const std::string& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        const char* keys[] = { "stop" };
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(value);
        CHECK_NULL_VOID(argsPtr);
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, argsPtr->GetString(keys[0]).c_str()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(const_cast<std::string*>(&value)));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getVideoModifier()->setOnStop(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetOnStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetOnStop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetEnableAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    Local<JSValueRef> flagArg = GetArgRef(runtimeCallInfo, 1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        GetArkUINodeModifiers()->getVideoModifier()->setEnableAnalyzer(
            nativeNode, flagArg->IsBoolean() && flagArg->ToBoolean(vm)->Value());
        return panda::JSValueRef::Undefined(vm);
    }
    if (flagArg->IsUndefined() || !flagArg->IsBoolean()) {
        GetArkUINodeModifiers()->getVideoModifier()->resetEnableAnalyzer(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool flag = flagArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getVideoModifier()->setEnableAnalyzer(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetEnableAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetEnableAnalyzer(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::SetAnalyzerConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = GetArgRef(runtimeCallInfo, NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> configValue = GetArgRef(runtimeCallInfo, 1);
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        if (configValue->IsNull() || !configValue->IsObject(vm)) {
            return panda::JSValueRef::Undefined(vm);
        }
    }
    CHECK_NULL_RETURN(SetNodeAnalyzerConfig(vm, nativeNode, configValue), panda::JSValueRef::Undefined(vm));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue VideoBridge::ResetAnalyzerConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NULL_RETURN(GetNativeNode(nativeNode, vm, runtimeCallInfo), panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getVideoModifier()->resetAnalyzerConfig(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void VideoBridge::RegisterVideoAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "setAutoPlay",
        "resetAutoPlay",
        "setControls",
        "resetControls",
        "setObjectFit",
        "resetObjectFit",
        "setLoop",
        "resetLoop",
        "setMuted",
        "resetMuted",
        "setShortcutKeyEnabled",
        "resetShortcutKeyEnabled",
        "setVideoSurfaceBackgroundColor",
        "resetVideoSurfaceBackgroundColor",
        "setOnStart",
        "resetOnStart",
        "setOnPause",
        "resetOnPause",
        "setOnFinish",
        "resetOnFinish",
        "setOnFullscreenChange",
        "resetOnFullscreenChange",
        "setOnPrepared",
        "resetOnPrepared",
        "setOnSeeking",
        "resetOnSeeking",
        "setOnSeeked",
        "resetOnSeeked",
        "setOnUpdate",
        "resetOnUpdate",
        "setOnError",
        "resetOnError",
        "setOnStop",
        "resetOnStop",
        "setEnableAnalyzer",
        "resetEnableAnalyzer",
        "setAnalyzerConfig",
        "resetAnalyzerConfig",
        "setOpacity",
        "resetOpacity",
        "setTransition",
        "resetTransition",
    };

#ifdef PREVIEW
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent),
    };
#else
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::Create),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetAutoPlay),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetAutoPlay),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetControls),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetControls),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetObjectFit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetObjectFit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetLoop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetLoop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetMuted),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetMuted),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetShortcutKeyEnabled),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetShortcutKeyEnabled),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetVideoSurfaceBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetVideoSurfaceBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetOnStart),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetOnStart),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetOnPause),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetOnPause),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetOnFinish),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetOnFinish),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetOnFullscreenChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetOnFullscreenChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetOnPrepared),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetOnPrepared),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetOnSeeking),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetOnSeeking),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetOnSeeked),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetOnSeeked),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetOnUpdate),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetOnUpdate),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetOnError),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetOnError),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetOnStop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetOnStop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetEnableAnalyzer),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetEnableAnalyzer),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetAnalyzerConfig),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetAnalyzerConfig),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetOpacity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetOpacity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetTransition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetTransition),
    };
#endif

    auto video = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "video"), video);
}
} // namespace OHOS::Ace::NG
