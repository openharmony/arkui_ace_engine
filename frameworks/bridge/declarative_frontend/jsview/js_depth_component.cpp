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

#include "bridge/declarative_frontend/jsview/js_depth_component.h"

#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

#include "base/image/pixel_map.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_event_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/depth_component/depth_component_model.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Framework {

namespace {
constexpr char RESOURCE_RAW_URI_PREFIX[] = "resource://RAWFILE/";
constexpr char RESOURCE_URI_PREFIX[] = "resource:///";
constexpr char OHOS_RAWFILE_PREFIX[] = "OhosRawFile://";
constexpr char FILE_PREFIX[] = "file://";
constexpr uint32_t NUM_4 = 4;
constexpr uint32_t NUM_5 = 5;
constexpr uint32_t NUM_8 = 8;
constexpr uint32_t NUM_16 = 16;
}

void JSDepthComponent::Create(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("DepthComponent::Create len=%d", info.Length());
    if (info.Length() < 1) {
        TAG_LOGW(AceLogTag::ACE_DEPTH_COMPONENT, "DepthComponent background is required parameter");
        return;
    }

#if defined(PIXEL_MAP_SUPPORTED)
    auto pixelMap = CreatePixelMapFromNapiValue(info[0]);
    if (pixelMap) {
        auto background = DepthBackgroundSource::CreateImage(ImageSourceInfo(pixelMap));

        NG::DepthComponentModel::Create(background);
        if (info.Length() > 1) {
            ParseAndSetOptions(info[1]);
        }
        return;
    }
#endif
    auto background = ParseBackgroundSource(info[0]);
    NG::DepthComponentModel::Create(background);
    if (info.Length() > 1) {
        ParseAndSetOptions(info[1]);
    }
}

void JSDepthComponent::SetDepthMap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        TAG_LOGW(AceLogTag::ACE_DEPTH_COMPONENT, "DepthComponent depthMap parameter is required");
        return;
    }

    // Parse optional callback
    RefPtr<JsFunction> jsFunc;
    if (info.Length() > 1 && info[1]->IsFunction()) {
        jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[1]));
    }

    auto setDepthMapWithCallback = [&info, &jsFunc](const ImageSourceInfo& imageSourceInfo) {
        if (jsFunc) {
            auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto onError = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                            node = frameNode](int32_t code, const std::string& msg) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("DepthComponent.depthMap");
                PipelineContext::SetCallBackNode(node);
                JSRef<JSObject> errorObj = JSRef<JSObject>::New();
                errorObj->SetProperty<int32_t>("code", code);
                errorObj->SetProperty<std::string>("name", "BusinessError");
                errorObj->SetProperty<std::string>("message", msg);
                JSRef<JSVal> param = JSRef<JSVal>::Cast(errorObj);
                func->ExecuteJS(1, &param);
            };
            NG::DepthComponentModel::SetDepthMap(imageSourceInfo, std::move(onError));
        } else {
            NG::DepthComponentModel::SetDepthMap(imageSourceInfo);
        }
    };

#if defined(PIXEL_MAP_SUPPORTED)
    auto pixelMap = CreatePixelMapFromNapiValue(info[0]);
    if (pixelMap) {
        setDepthMapWithCallback(ImageSourceInfo(pixelMap));
        TAG_LOGI(AceLogTag::ACE_DEPTH_COMPONENT, "DepthComponent depthMap set from PixelMap");
        info.ReturnSelf();
        return;
    }
#endif

    auto backgroundSource = ParseBackgroundSource(info[0]);
    if (backgroundSource.IsImage()) {
        setDepthMapWithCallback(backgroundSource.imageSourceInfo);
        TAG_LOGI(AceLogTag::ACE_DEPTH_COMPONENT, "DepthComponent depthMap set");
    } else {
        setDepthMapWithCallback(ImageSourceInfo());
    }
    info.ReturnSelf();
}

void JSDepthComponent::SetCamera(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("DepthComponent::SetCamera len=%d", info.Length());
    if (info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_DEPTH_COMPONENT, "DepthComponent camera parameter must be an object");
        return;
    }

    auto jsObject = JSRef<JSObject>::Cast(info[0]);
    OHOS::Ace::DepthCameraParams cameraParams;
    auto positionValue = jsObject->GetProperty("position");
    if (positionValue->IsObject()) {
        cameraParams.position = ParseVector3(positionValue);
    }

    auto quaternionValue = jsObject->GetProperty("quaternion");
    if (quaternionValue->IsObject()) {
        cameraParams.quaternion = ParseVector4(quaternionValue);
    }

    auto yFovValue = jsObject->GetProperty("yFov");
    if (yFovValue->IsNumber()) {
        cameraParams.yFov = yFovValue->ToNumber<float>();
    }

    auto zNearValue = jsObject->GetProperty("zNear");
    if (zNearValue->IsNumber()) {
        cameraParams.zNear = zNearValue->ToNumber<float>();
    }

    auto zFarValue = jsObject->GetProperty("zFar");
    if (zFarValue->IsNumber()) {
        cameraParams.zFar = zFarValue->ToNumber<float>();
    }

    auto cameraBufferCropValue = jsObject->GetProperty("cameraBufferCrop");
    if (cameraBufferCropValue->IsObject()) {
        cameraParams.cameraBufferCrop = ParseCameraBufferCrop(cameraBufferCropValue);
    }

    NG::DepthComponentModel::SetCamera(cameraParams);
    info.ReturnSelf();
}

void JSDepthComponent::SetLight(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_DEPTH_COMPONENT, "DepthComponent light parameter must be an object");
        return;
    }

    auto jsObject = JSRef<JSObject>::Cast(info[0]);
    OHOS::Ace::DepthLightParams lightParams;
    auto directionValue = jsObject->GetProperty("direction");
    if (directionValue->IsObject()) {
        lightParams.direction = ParseVector3(directionValue);
    }

    auto colorValue = jsObject->GetProperty("color");
    if (colorValue->IsNumber() || colorValue->IsObject()) {
        lightParams.color = ParseLightColor(colorValue);
    }

    auto intensityValue = jsObject->GetProperty("intensity");
    if (intensityValue->IsNumber()) {
        lightParams.intensity = intensityValue->ToNumber<float>();
    }
    NG::DepthComponentModel::SetLight(lightParams);
    info.ReturnSelf();
}

void JSDepthComponent::SetOnComplete(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    RefPtr<JsFunction> jsFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onComplete = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                       node = frameNode](const DepthComponentCompleteEvent& completeEvent) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("DepthComponent.onComplete");
        PipelineContext::SetCallBackNode(node);
        JSRef<JSObject> eventObj = JSRef<JSObject>::New();
        eventObj->SetProperty<double>("componentWidth", completeEvent.componentWidth);
        eventObj->SetProperty<double>("componentHeight", completeEvent.componentHeight);
        JSRef<JSVal> param = JSRef<JSVal>::Cast(eventObj);
        func->ExecuteJS(1, &param);
    };
    NG::DepthComponentModel::SetOnComplete(std::move(onComplete));
    info.ReturnSelf();
}

void JSDepthComponent::SetOnError(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    RefPtr<JsFunction> jsFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onError = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                    node = frameNode](const DepthComponentErrorEvent& errorEvent) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("DepthComponent.onError");
        PipelineContext::SetCallBackNode(node);
        JSRef<JSObject> eventObj = JSRef<JSObject>::New();
        eventObj->SetProperty<double>("componentWidth", errorEvent.componentWidth);
        eventObj->SetProperty<double>("componentHeight", errorEvent.componentHeight);
        if (errorEvent.errorCode != 0 || !errorEvent.errorMessage.empty()) {
            JSRef<JSObject> errorObj = JSRef<JSObject>::New();
            errorObj->SetProperty<int32_t>("code", errorEvent.errorCode);
            errorObj->SetProperty<std::string>("name", "BusinessError");
            errorObj->SetProperty<std::string>("message", errorEvent.errorMessage);
            eventObj->SetProperty<JSRef<JSObject>>("error", errorObj);
        }
        JSRef<JSVal> param = JSRef<JSVal>::Cast(eventObj);
        func->ExecuteJS(1, &param);
    };
    NG::DepthComponentModel::SetOnError(std::move(onError));
    info.ReturnSelf();
}

void JSDepthComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSDepthComponent>::Declare("DepthComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSDepthComponent>::StaticMethod("create", &JSDepthComponent::Create, opt);
    JSClass<JSDepthComponent>::StaticMethod("depthMap", &JSDepthComponent::SetDepthMap, opt);
    JSClass<JSDepthComponent>::StaticMethod("camera", &JSDepthComponent::SetCamera, opt);
    JSClass<JSDepthComponent>::StaticMethod("light", &JSDepthComponent::SetLight, opt);
    JSClass<JSDepthComponent>::StaticMethod("onComplete", &JSDepthComponent::SetOnComplete, opt);
    JSClass<JSDepthComponent>::StaticMethod("onError", &JSDepthComponent::SetOnError, opt);
    JSClass<JSDepthComponent>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSDepthComponent>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSDepthComponent>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSDepthComponent>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSDepthComponent>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSDepthComponent>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSDepthComponent>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSDepthComponent>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSDepthComponent>::InheritAndBind<JSContainerBase>(globalObj);
}

OHOS::Ace::DepthBackgroundSource JSDepthComponent::ParseBackgroundSource(const JSRef<JSVal>& imageInfo)
{
    ACE_FUNCTION_TRACE();
    std::string src;
    std::string bundleName;
    std::string moduleName;
    int32_t resId = 0;
    RefPtr<ResourceObject> resObj;

    ParseJsMediaWithBundleName(imageInfo, src, bundleName, moduleName, resId, resObj);
    if (src.empty()) {
        TAG_LOGW(AceLogTag::ACE_DEPTH_COMPONENT, "DepthComponent background parse failed");
        return {};
    }

    if (IsGltfSource(src)) {
        ACE_SCOPED_TRACE("DepthComponent::ParseBackgroundSource gltf src=%s", src.c_str());
        std::string ohosPath;
        if (!SetOhosPath(src, ohosPath)) {
            TAG_LOGW(AceLogTag::ACE_DEPTH_COMPONENT, "DepthComponent gltf path conversion failed");
            return {};
        }
        return OHOS::Ace::DepthBackgroundSource::CreateGltf(ohosPath, src, bundleName, moduleName);
    }
    return OHOS::Ace::DepthBackgroundSource::CreateImage(
        ImageSourceInfo(src, bundleName, moduleName), src, bundleName, moduleName);
}

bool JSDepthComponent::IsGltfSource(const std::string& src)
{
    if (src.empty()) {
        return false;
    }

    auto queryPos = src.find('?');
    std::string cleanSrc = (queryPos == std::string::npos) ? src : src.substr(0, queryPos);
    if (cleanSrc.size() <= NUM_5) {
        return false;
    }
    StringUtils::TransformStrCase(cleanSrc, StringUtils::TEXT_CASE_LOWERCASE);
    return cleanSrc.rfind(".gltf") == cleanSrc.size() - NUM_5 || cleanSrc.rfind(".glb") == cleanSrc.size() - NUM_4;
}

bool JSDepthComponent::SetOhosPath(const std::string& uri, std::string& ohosPath)
{
    ACE_SCOPED_TRACE("DepthComponent::SetOhosPath uri=%s", uri.c_str());
    if (uri.empty()) {
        return false;
    }

    if (uri.find(RESOURCE_RAW_URI_PREFIX) == 0) {
        ohosPath = std::string(OHOS_RAWFILE_PREFIX) + uri.substr(strlen(RESOURCE_RAW_URI_PREFIX));
        return true;
    }

    if (uri.find(OHOS_RAWFILE_PREFIX) == 0 || uri.find(FILE_PREFIX) == 0 || uri.find(RESOURCE_URI_PREFIX) == 0) {
        ohosPath = uri;
        return true;
    }

    if (!uri.empty() && uri.front() == '/') {
        ohosPath = std::string(FILE_PREFIX) + uri;
        return true;
    }
    ohosPath = std::string(FILE_PREFIX) + uri;
    return true;
}

void JSDepthComponent::ParseAndSetOptions(const JSRef<JSVal>& optionsValue)
{
    if (!optionsValue->IsObject()) {
        return;
    }

    auto jsObject = JSRef<JSObject>::Cast(optionsValue);
    auto depthSpaceValue = jsObject->GetProperty("depthSpace");
    if (depthSpaceValue->IsNumber()) {
        int32_t depthSpace = depthSpaceValue->ToNumber<int32_t>();
        OHOS::Ace::DepthSpaceType depthSpaceEnum = static_cast<OHOS::Ace::DepthSpaceType>(depthSpace);
        NG::DepthComponentModel::SetDepthSpace(depthSpaceEnum);
    }

    auto render3DScaleValue = jsObject->GetProperty("render3DScale");
    if (render3DScaleValue->IsNumber()) {
        float render3DScale = render3DScaleValue->ToNumber<float>();
        if (GreatNotEqual(render3DScale, 0.0f) && LessOrEqual(render3DScale, 1.0f)) {
            NG::DepthComponentModel::SetRender3DScale(render3DScale);
        }
    }
}

OHOS::Ace::CropOffset JSDepthComponent::ParseCropOffset(const JSRef<JSVal>& offsetValue)
{
    OHOS::Ace::CropOffset offset;
    if (!offsetValue->IsObject()) {
        return offset;
    }
    auto offsetObj = JSRef<JSObject>::Cast(offsetValue);
    auto xValue = offsetObj->GetProperty("x");
    if (xValue->IsNumber()) {
        offset.x = xValue->ToNumber<float>();
    }

    auto yValue = offsetObj->GetProperty("y");
    if (yValue->IsNumber()) {
        offset.y = yValue->ToNumber<float>();
    }
    return offset;
}

OHOS::Ace::CameraBufferCrop JSDepthComponent::ParseCameraBufferCrop(const JSRef<JSVal>& cropValue)
{
    OHOS::Ace::CameraBufferCrop crop;
    if (!cropValue->IsObject()) {
        return crop;
    }
    auto cropObj = JSRef<JSObject>::Cast(cropValue);
    auto bufferWidthValue = cropObj->GetProperty("bufferWidth");
    if (bufferWidthValue->IsNumber()) {
        crop.bufferWidth = bufferWidthValue->ToNumber<int32_t>();
    }
    auto bufferHeightValue = cropObj->GetProperty("bufferHeight");
    if (bufferHeightValue->IsNumber()) {
        crop.bufferHeight = bufferHeightValue->ToNumber<int32_t>();
    }
    auto cropOffsetValue = cropObj->GetProperty("cropOffset");
    if (cropOffsetValue->IsObject()) {
        crop.cropOffset = ParseCropOffset(cropOffsetValue);
    }
    auto cropScaleValue = cropObj->GetProperty("cropScale");
    if (cropScaleValue->IsNumber()) {
        crop.cropScale = cropScaleValue->ToNumber<float>();
    }
    return crop;
}

OHOS::Ace::DepthVector3 JSDepthComponent::ParseVector3(const JSRef<JSVal>& vectorValue)
{
    OHOS::Ace::DepthVector3 vector;
    if (!vectorValue->IsObject()) {
        return vector;
    }

    auto vectorObj = JSRef<JSObject>::Cast(vectorValue);
    auto xValue = vectorObj->GetProperty("x");
    if (xValue->IsNumber()) {
        vector.x = xValue->ToNumber<float>();
    }

    auto yValue = vectorObj->GetProperty("y");
    if (yValue->IsNumber()) {
        vector.y = yValue->ToNumber<float>();
    }

    auto zValue = vectorObj->GetProperty("z");
    if (zValue->IsNumber()) {
        vector.z = zValue->ToNumber<float>();
    }
    return vector;
}

OHOS::Ace::DepthVector4 JSDepthComponent::ParseVector4(const JSRef<JSVal>& vectorValue)
{
    OHOS::Ace::DepthVector4 vector;
    if (!vectorValue->IsObject()) {
        return vector;
    }

    auto vectorObj = JSRef<JSObject>::Cast(vectorValue);
    auto xValue = vectorObj->GetProperty("x");
    if (xValue->IsNumber()) {
        vector.x = xValue->ToNumber<float>();
    }

    auto yValue = vectorObj->GetProperty("y");
    if (yValue->IsNumber()) {
        vector.y = yValue->ToNumber<float>();
    }

    auto zValue = vectorObj->GetProperty("z");
    if (zValue->IsNumber()) {
        vector.z = zValue->ToNumber<float>();
    }

    auto wValue = vectorObj->GetProperty("w");
    if (wValue->IsNumber()) {
        vector.w = wValue->ToNumber<float>();
    }
    return vector;
}

OHOS::Ace::DepthColorRGB JSDepthComponent::ParseLightColor(const JSRef<JSVal>& colorValue)
{
    OHOS::Ace::DepthColorRGB color;
    if (colorValue->IsNumber()) {
        uint32_t colorRGB = colorValue->ToNumber<uint32_t>();
        color.red = static_cast<float>(((colorRGB >> NUM_16) & 0xFF) / 255.0f);
        color.green = static_cast<float>(((colorRGB >> NUM_8) & 0xFF) / 255.0f);
        color.blue = static_cast<float>((colorRGB & 0xFF) / 255.0f);
        return color;
    }

    if (colorValue->IsObject()) {
        auto colorObj = JSRef<JSObject>::Cast(colorValue);
        auto redValue = colorObj->GetProperty("red");
        if (redValue->IsNumber()) {
            color.red = redValue->ToNumber<float>() / 255.0f;
        }
        auto greenValue = colorObj->GetProperty("green");
        if (greenValue->IsNumber()) {
            color.green = greenValue->ToNumber<float>() / 255.0f;
        }
        auto blueValue = colorObj->GetProperty("blue");
        if (blueValue->IsNumber()) {
            color.blue = blueValue->ToNumber<float>() / 255.0f;
        }
    }
    return color;
}

} // namespace OHOS::Ace::Framework
