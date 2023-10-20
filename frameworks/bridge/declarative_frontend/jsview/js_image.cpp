/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"

#if !defined(PREVIEW)
#include <dlfcn.h>
#endif

#include "base/image/pixel_map.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/jsview/models/image_model_impl.h"
#include "core/common/container.h"
#include "core/components/image/image_event.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/image/image_model.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace {

std::unique_ptr<ImageModel> ImageModel::instance_ = nullptr;
std::mutex ImageModel::mutex_;

ImageModel* ImageModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ImageModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ImageModelNG());
            } else {
                instance_.reset(new Framework::ImageModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

JSRef<JSVal> LoadImageSuccEventToJSValue(const LoadImageSuccessEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("width", eventInfo.GetWidth());
    obj->SetProperty("height", eventInfo.GetHeight());
    obj->SetProperty("componentWidth", eventInfo.GetComponentWidth());
    obj->SetProperty("componentHeight", eventInfo.GetComponentHeight());
    obj->SetProperty("loadingStatus", eventInfo.GetLoadingStatus());
    obj->SetProperty("contentWidth", eventInfo.GetContentWidth());
    obj->SetProperty("contentHeight", eventInfo.GetContentHeight());
    obj->SetProperty("contentOffsetX", eventInfo.GetContentOffsetX());
    obj->SetProperty("contentOffsetY", eventInfo.GetContentOffsetY());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> LoadImageFailEventToJSValue(const LoadImageFailEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("componentWidth", eventInfo.GetComponentWidth());
    obj->SetProperty("componentHeight", eventInfo.GetComponentHeight());
    obj->SetProperty("message", eventInfo.GetErrorMessage());
    return JSRef<JSVal>::Cast(obj);
}

void JSImage::SetAlt(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }

    std::string src;
    if (!ParseJsMedia(args[0], src)) {
        return;
    }
    if (ImageSourceInfo::ResolveURIType(src) == SrcType::NETWORK) {
        return;
    }
    ImageModel::GetInstance()->SetAlt(src);
}

void JSImage::SetObjectFit(int32_t value)
{
    auto fit = static_cast<ImageFit>(value);
    if (fit < ImageFit::FILL || fit > ImageFit::SCALE_DOWN) {
        fit = ImageFit::COVER;
    }
    ImageModel::GetInstance()->SetImageFit(fit);
}

void JSImage::SetMatchTextDirection(bool value)
{
    ImageModel::GetInstance()->SetMatchTextDirection(value);
}

void JSImage::SetFitOriginalSize(bool value)
{
    ImageModel::GetInstance()->SetFitOriginSize(value);
}

void JSImage::SetBorder(const Border& border)
{
    ImageModel::GetInstance()->SetBorder(border);
}

void JSImage::OnComplete(const JSCallbackInfo& args)
{
    TAG_LOGD(AceLogTag::ACE_IMAGE, "JSImage OnComplete");
    if (args[0]->IsFunction()) {
        auto jsLoadSuccFunc = AceType::MakeRefPtr<JsEventFunction<LoadImageSuccessEvent, 1>>(
            JSRef<JSFunc>::Cast(args[0]), LoadImageSuccEventToJSValue);

        auto onComplete = [execCtx = args.GetExecutionContext(), func = std::move(jsLoadSuccFunc)](
                              const LoadImageSuccessEvent& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Image.onComplete");
            func->Execute(info);
        };
        ImageModel::GetInstance()->SetOnComplete(std::move(onComplete));
    }
}

void JSImage::OnError(const JSCallbackInfo& args)
{
    TAG_LOGD(AceLogTag::ACE_IMAGE, "JSImage OnError");
    if (args[0]->IsFunction()) {
        auto jsLoadFailFunc = AceType::MakeRefPtr<JsEventFunction<LoadImageFailEvent, 1>>(
            JSRef<JSFunc>::Cast(args[0]), LoadImageFailEventToJSValue);
        auto onError = [execCtx = args.GetExecutionContext(), func = std::move(jsLoadFailFunc)](
                           const LoadImageFailEvent& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Image.onError");
            func->Execute(info);
        };

        ImageModel::GetInstance()->SetOnError(onError);
    }
}

void JSImage::OnFinish(const JSCallbackInfo& info)
{
    auto tmpInfo = info[0];
    if (!tmpInfo->IsFunction()) {
        return;
    }
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(tmpInfo));
    auto onFinish = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Image.onFinish");
        func->Execute();
    };
    ImageModel::GetInstance()->SetSvgAnimatorFinishEvent(onFinish);
}

void JSImage::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    bool isCard = context->IsFormRender();

    // Interim programme
    std::string bundleName;
    std::string moduleName;
    std::string src;
    bool srcValid = ParseJsMedia(info[0], src);
    if (isCard && info[0]->IsString()) {
        SrcType srcType = ImageSourceInfo::ResolveURIType(src);
        bool notSupport = (srcType == SrcType::NETWORK || srcType == SrcType::FILE || srcType == SrcType::DATA_ABILITY);
        if (notSupport) {
            src.clear();
        }
    }
    GetJsMediaBundleInfo(info[0], bundleName, moduleName);
    RefPtr<PixelMap> pixmap = nullptr;

    // input is PixelMap / Drawable
    if (!srcValid) {
#if defined(PIXEL_MAP_SUPPORTED)
        if (isCard) {
            TAG_LOGD(AceLogTag::ACE_IMAGE, "Not supported pixmap when form render");
        } else {
            if (IsDrawable(info[0])) {
                pixmap = GetDrawablePixmap(info[0]);
            } else {
                pixmap = CreatePixelMapFromNapiValue(info[0]);
            }
        }
#else
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Pixmap not supported under this environment.");
#endif
    }

    ImageModel::GetInstance()->Create(src, pixmap, bundleName, moduleName);
}

bool JSImage::IsDrawable(const JSRef<JSVal>& jsValue)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    if (jsObj->IsUndefined()) {
        return false;
    }

    // if jsObject has function getPixelMap, it's a DrawableDescriptor object
    JSRef<JSVal> func = jsObj->GetProperty("getPixelMap");
    return (!func->IsNull() && func->IsFunction());
}

void JSImage::JsBorder(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBorder(info);
    ImageModel::GetInstance()->SetBackBorder();
}

void JSImage::JsBorderRadius(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBorderRadius(info);
    ImageModel::GetInstance()->SetBackBorder();
}

void JSImage::SetSourceSize(const JSCallbackInfo& info)
{
    ImageModel::GetInstance()->SetImageSourceSize(JSViewAbstract::ParseSize(info));
}

void JSImage::SetImageFill(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    Color color;
    if (!ParseJsColor(info[0], color)) {
        return;
    }
    ImageModel::GetInstance()->SetImageFill(color);
}

void JSImage::SetImageRenderMode(int32_t imageRenderMode)
{
    auto renderMode = static_cast<ImageRenderMode>(imageRenderMode);
    if (renderMode < ImageRenderMode::ORIGINAL || renderMode > ImageRenderMode::TEMPLATE) {
        renderMode = ImageRenderMode::ORIGINAL;
    }
    ImageModel::GetInstance()->SetImageRenderMode(renderMode);
}

void JSImage::SetImageInterpolation(int32_t imageInterpolation)
{
    auto interpolation = static_cast<ImageInterpolation>(imageInterpolation);
    if (interpolation < ImageInterpolation::NONE || interpolation > ImageInterpolation::HIGH) {
        interpolation = ImageInterpolation::NONE;
    }
    ImageModel::GetInstance()->SetImageInterpolation(interpolation);
}

void JSImage::SetImageRepeat(int32_t imageRepeat)
{
    auto repeat = static_cast<ImageRepeat>(imageRepeat);
    if (repeat < ImageRepeat::NO_REPEAT || repeat > ImageRepeat::REPEAT) {
        repeat = ImageRepeat::NO_REPEAT;
    }
    ImageModel::GetInstance()->SetImageRepeat(repeat);
}

void JSImage::JsTransition(const JSCallbackInfo& info)
{
    if (ImageModel::GetInstance()->IsSrcSvgImage()) {
        JSViewAbstract::JsTransition(info);
    } else {
        JSViewAbstract::JsTransitionPassThrough(info);
    }
}

void JSImage::JsOpacity(const JSCallbackInfo& info)
{
    if (ImageModel::GetInstance()->IsSrcSvgImage()) {
        JSViewAbstract::JsOpacity(info);
    } else {
        JSViewAbstract::JsOpacityPassThrough(info);
    }
}

void JSImage::JsBlur(const JSCallbackInfo& info)
{
// only flutter runs special image blur
#ifdef ENABLE_ROSEN_BACKEND
    JSViewAbstract::JsBlur(info);
#else
    if (info.Length() < 1) {
        return;
    }
    double blur = 0.0;
    if (ParseJsDouble(info[0], blur)) {
        ImageModel::GetInstance()->SetBlur(blur);
    }
#endif
}

void JSImage::SetAutoResize(bool autoResize)
{
    ImageModel::GetInstance()->SetAutoResize(autoResize);
}

void JSImage::SetSyncLoad(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto tmpInfo = info[0];
    if (!tmpInfo->IsBoolean()) {
        return;
    }
    ImageModel::GetInstance()->SetSyncMode(tmpInfo->ToBoolean());
}

void JSColorFilter::ConstructorCallback(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    auto tmpInfo = args[0];
    if (!tmpInfo->IsArray()) {
        return;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(tmpInfo);
    if (array->Length() != COLOR_FILTER_MATRIX_SIZE) {
        return;
    }
    auto jscolorfilter = Referenced::MakeRefPtr<JSColorFilter>();
    if (jscolorfilter == nullptr) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "make jscolorfilter object failed");
        return;
    }
    std::vector<float> colorfilter;
    for (size_t i = 0; i < array->Length(); i++) {
        JSRef<JSVal> value = array->GetValueAt(i);
        if (value->IsNumber()) {
            colorfilter.emplace_back(value->ToNumber<float>());
        }
    }
    if (colorfilter.size() != COLOR_FILTER_MATRIX_SIZE) {
        return;
    }
    jscolorfilter->SetColorFilterMatrix(std::move(colorfilter));
    jscolorfilter->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jscolorfilter));
}

void JSColorFilter::DestructorCallback(JSColorFilter* obj)
{
    if (obj != nullptr) {
        obj->DecRefCount();
    }
}

void JSImage::SetColorFilter(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        return;
    }
    auto tmpInfo = info[0];
    if (!tmpInfo->IsArray() && !tmpInfo->IsObject()) {
        return;
    }
    if (tmpInfo->IsObject() && !tmpInfo->IsArray()) {
        JSColorFilter* colorFilter;
        if (!tmpInfo->IsUndefined() && !tmpInfo->IsNull()) {
            colorFilter = JSRef<JSObject>::Cast(tmpInfo)->Unwrap<JSColorFilter>();
        } else {
            return;
        }
        if (colorFilter && colorFilter->GetColorFilterMatrix().size() == COLOR_FILTER_MATRIX_SIZE) {
            ImageModel::GetInstance()->SetColorFilterMatrix(colorFilter->GetColorFilterMatrix());
        } else {
            return;
        }
        return;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(tmpInfo);
    if (array->Length() != COLOR_FILTER_MATRIX_SIZE) {
        return;
    }
    std::vector<float> colorfilter;
    for (size_t i = 0; i < array->Length(); i++) {
        JSRef<JSVal> value = array->GetValueAt(i);
        if (value->IsNumber()) {
            colorfilter.emplace_back(value->ToNumber<float>());
        }
    }
    if (colorfilter.size() != COLOR_FILTER_MATRIX_SIZE) {
        return;
    }
    ImageModel::GetInstance()->SetColorFilterMatrix(colorfilter);
}

void JSImage::JSBind(BindingTarget globalObj)
{
    JSClass<JSImage>::Declare("Image");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSImage>::StaticMethod("create", &JSImage::Create, opt);
    JSClass<JSImage>::StaticMethod("alt", &JSImage::SetAlt, opt);
    JSClass<JSImage>::StaticMethod("objectFit", &JSImage::SetObjectFit, opt);
    JSClass<JSImage>::StaticMethod("matchTextDirection", &JSImage::SetMatchTextDirection, opt);
    JSClass<JSImage>::StaticMethod("fitOriginalSize", &JSImage::SetFitOriginalSize, opt);
    JSClass<JSImage>::StaticMethod("sourceSize", &JSImage::SetSourceSize, opt);
    JSClass<JSImage>::StaticMethod("fillColor", &JSImage::SetImageFill, opt);
    JSClass<JSImage>::StaticMethod("renderMode", &JSImage::SetImageRenderMode, opt);
    JSClass<JSImage>::StaticMethod("objectRepeat", &JSImage::SetImageRepeat, opt);
    JSClass<JSImage>::StaticMethod("interpolation", &JSImage::SetImageInterpolation, opt);
    JSClass<JSImage>::StaticMethod("colorFilter", &JSImage::SetColorFilter, opt);

    JSClass<JSImage>::StaticMethod("border", &JSImage::JsBorder);
    JSClass<JSImage>::StaticMethod("borderRadius", &JSImage::JsBorderRadius);
    JSClass<JSImage>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSImage>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSImage>::StaticMethod("autoResize", &JSImage::SetAutoResize);

    JSClass<JSImage>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSImage>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSImage>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSImage>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSImage>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSImage>::StaticMethod("onComplete", &JSImage::OnComplete);
    JSClass<JSImage>::StaticMethod("onError", &JSImage::OnError);
    JSClass<JSImage>::StaticMethod("onFinish", &JSImage::OnFinish);
    JSClass<JSImage>::StaticMethod("syncLoad", &JSImage::SetSyncLoad);
    JSClass<JSImage>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSImage>::StaticMethod("draggable", &JSImage::JsSetDraggable);
    JSClass<JSImage>::StaticMethod("onDragStart", &JSImage::JsOnDragStart);
    JSClass<JSImage>::StaticMethod("copyOption", &JSImage::SetCopyOption);
    // override method
    JSClass<JSImage>::StaticMethod("opacity", &JSImage::JsOpacity);
    JSClass<JSImage>::StaticMethod("blur", &JSImage::JsBlur);
    JSClass<JSImage>::StaticMethod("transition", &JSImage::JsTransition);
    JSClass<JSImage>::InheritAndBind<JSViewAbstract>(globalObj);

    JSClass<JSColorFilter>::Declare("ColorFilter");
    JSClass<JSColorFilter>::Bind(globalObj, JSColorFilter::ConstructorCallback, JSColorFilter::DestructorCallback);
}

void JSImage::JsSetDraggable(bool draggable)
{
    ImageModel::GetInstance()->SetDraggable(draggable);
}

void JSImage::JsOnDragStart(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsFunction()) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragStartId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc)](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) -> NG::DragDropBaseInfo {
        NG::DragDropBaseInfo itemInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, itemInfo);

        auto ret = func->Execute(info, extraParams);
        if (!ret->IsObject()) {
            return itemInfo;
        }
        if (ParseAndUpdateDragItemInfo(ret, itemInfo)) {
            return itemInfo;
        }

        auto builderObj = JSRef<JSObject>::Cast(ret);
#if defined(PIXEL_MAP_SUPPORTED)
        auto pixmap = builderObj->GetProperty("pixelMap");
        itemInfo.pixelMap = CreatePixelMapFromNapiValue(pixmap);
#endif
        auto extraInfo = builderObj->GetProperty("extraInfo");
        ParseJsString(extraInfo, itemInfo.extraInfo);
        ParseAndUpdateDragItemInfo(builderObj->GetProperty("builder"), itemInfo);
        return itemInfo;
    };
    ImageModel::GetInstance()->SetOnDragStart(std::move(onDragStartId));
}

void JSImage::SetCopyOption(const JSCallbackInfo& info)
{
    auto copyOptions = CopyOptions::None;
    if (info[0]->IsNumber()) {
        auto enumNumber = info[0]->ToNumber<int>();
        copyOptions = static_cast<CopyOptions>(enumNumber);
        if (copyOptions < CopyOptions::None || copyOptions > CopyOptions::Distributed) {
            copyOptions = CopyOptions::None;
        }
    }
    ImageModel::GetInstance()->SetCopyOption(copyOptions);
}

} // namespace OHOS::Ace::Framework
