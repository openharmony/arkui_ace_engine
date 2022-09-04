/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
#include <dlfcn.h>
#endif

#include "base/image/pixel_map.h"
#include "base/log/ace_trace.h"
#include "core/components_ng/pattern/image/image_view.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

#define SET_PROP_FOR_NG(propName, propType, propValue)                      \
    do {                                                                    \
        if (Container::IsCurrentUseNewPipeline()) {                         \
            NG::ImageView::Set##propName(static_cast<propType>(propValue)); \
            return;                                                         \
        }                                                                   \
    } while (0);

JSRef<JSVal> LoadImageSuccEventToJSValue(const LoadImageSuccessEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("width", eventInfo.GetWidth());
    obj->SetProperty("height", eventInfo.GetHeight());
    obj->SetProperty("componentWidth", eventInfo.GetComponentWidth());
    obj->SetProperty("componentHeight", eventInfo.GetComponentHeight());
    obj->SetProperty("loadingStatus", eventInfo.GetLoadingStatus());
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
        LOGE("The argv is wrong, it it supposed to have at least 1 argument");
        return;
    }

    std::string src;
    if (!ParseJsMedia(args[0], src)) {
        return;
    }

    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetAlt(src);
    }
}

void JSImage::SetObjectFit(int32_t value)
{
    SET_PROP_FOR_NG(ObjectFit, ImageFit, value);
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetImageFit(static_cast<ImageFit>(value));
    }
}

void JSImage::SetMatchTextDirection(bool value)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetMatchTextDirection(value);
    }
}

void JSImage::SetFitOriginalSize(bool value)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetFitMaxSize(!value);
    }
}

RefPtr<Decoration> JSImage::GetFrontDecoration()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto decoration = box->GetFrontDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
        box->SetFrontDecoration(decoration);
    }

    return decoration;
}

const Border& JSImage::GetBorder()
{
    return GetFrontDecoration()->GetBorder();
}

BorderEdge JSImage::GetLeftBorderEdge()
{
    return GetBorder().Left();
}

BorderEdge JSImage::GetTopBorderEdge()
{
    return GetBorder().Top();
}

BorderEdge JSImage::GetRightBorderEdge()
{
    return GetBorder().Right();
}

BorderEdge JSImage::GetBottomBorderEdge()
{
    return GetBorder().Bottom();
}

void JSImage::SetBorderEdge(const BorderEdge& edge)
{
    Border border = GetBorder();
    border.SetBorderEdge(edge);
    SetBorder(border);
}

void JSImage::SetLeftBorderEdge(const BorderEdge& edge)
{
    Border border = GetBorder();
    border.SetLeftEdge(edge);
    SetBorder(border);
}

void JSImage::SetTopBorderEdge(const BorderEdge& edge)
{
    Border border = GetBorder();
    border.SetTopEdge(edge);
    SetBorder(border);
}

void JSImage::SetRightBorderEdge(const BorderEdge& edge)
{
    Border border = GetBorder();
    border.SetRightEdge(edge);
    SetBorder(border);
}

void JSImage::SetBottomBorderEdge(const BorderEdge& edge)
{
    Border border = GetBorder();
    border.SetBottomEdge(edge);
    SetBorder(border);
}

void JSImage::SetBorder(const Border& border)
{
    GetFrontDecoration()->SetBorder(border);
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetBorder(border);
    }
}

void JSImage::SetLeftBorderColor(const Color& color)
{
    BorderEdge edge = GetLeftBorderEdge();
    edge.SetColor(color);
    SetLeftBorderEdge(edge);
}

void JSImage::SetTopBorderColor(const Color& color)
{
    BorderEdge edge = GetTopBorderEdge();
    edge.SetColor(color);
    SetTopBorderEdge(edge);
}

void JSImage::SetRightBorderColor(const Color& color)
{
    BorderEdge edge = GetRightBorderEdge();
    edge.SetColor(color);
    SetRightBorderEdge(edge);
}

void JSImage::SetBottomBorderColor(const Color& color)
{
    BorderEdge edge = GetBottomBorderEdge();
    edge.SetColor(color);
    SetBottomBorderEdge(edge);
}

void JSImage::SetLeftBorderWidth(const Dimension& value)
{
    BorderEdge edge = GetLeftBorderEdge();
    edge.SetWidth(value);
    SetLeftBorderEdge(edge);
}

void JSImage::SetTopBorderWidth(const Dimension& value)
{
    BorderEdge edge = GetTopBorderEdge();
    edge.SetWidth(value);
    SetTopBorderEdge(edge);
}

void JSImage::SetRightBorderWidth(const Dimension& value)
{
    BorderEdge edge = GetRightBorderEdge();
    edge.SetWidth(value);
    SetRightBorderEdge(edge);
}

void JSImage::SetBottomBorderWidth(const Dimension& value)
{
    BorderEdge edge = GetBottomBorderEdge();
    edge.SetWidth(value);
    SetBottomBorderEdge(edge);
}

void JSImage::OnComplete(const JSCallbackInfo& args)
{
    LOGD("JSImage V8OnComplete");
    if (args[0]->IsFunction()) {
        auto jsLoadSuccFunc = AceType::MakeRefPtr<JsEventFunction<LoadImageSuccessEvent, 1>>(
            JSRef<JSFunc>::Cast(args[0]), LoadImageSuccEventToJSValue);

        if (Container::IsCurrentUseNewPipeline()) {
            auto onComplete = [execCtx = args.GetExecutionContext(), func = std::move(jsLoadSuccFunc)](
                                  const LoadImageSuccessEvent& info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("Image.onComplete");
                func->Execute(info);
            };
            NG::ImageView::SetOnComplete(std::move(onComplete));
            return;
        }

        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        image->SetLoadSuccessEvent(EventMarker(
            [execCtx = args.GetExecutionContext(), func = std::move(jsLoadSuccFunc)](const BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                auto eventInfo = TypeInfoHelper::DynamicCast<LoadImageSuccessEvent>(info);
                ACE_SCORING_EVENT("Image.onComplete");
                func->Execute(*eventInfo);
            }));
    } else {
        LOGE("args not function");
    }
}

void JSImage::OnError(const JSCallbackInfo& args)
{
    LOGD("JSImage V8OnError");
    if (args[0]->IsFunction()) {
        auto jsLoadFailFunc = AceType::MakeRefPtr<JsEventFunction<LoadImageFailEvent, 1>>(
            JSRef<JSFunc>::Cast(args[0]), LoadImageFailEventToJSValue);
        if (Container::IsCurrentUseNewPipeline()) {
            auto onError = [execCtx = args.GetExecutionContext(), func = std::move(jsLoadFailFunc)](const LoadImageFailEvent& info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("Image.onError");
                func->Execute(info);
            };
            NG::ImageView::SetOnError(std::move(onError));
            return;
        }
        auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        image->SetLoadFailEvent(EventMarker(
            [execCtx = args.GetExecutionContext(), func = std::move(jsLoadFailFunc)](const BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                auto eventInfo = TypeInfoHelper::DynamicCast<LoadImageFailEvent>(info);
                ACE_SCORING_EVENT("Image.onError");
                func->Execute(*eventInfo);
            }));
    } else {
        LOGE("args not function");
    }
}

void JSImage::OnFinish(const JSCallbackInfo& info)
{
    LOGD("JSImage V8OnFinish");
    if (!info[0]->IsFunction()) {
        LOGE("info[0] is not a function.");
        return;
    }
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto eventMarker = EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Image.onFinish");
        func->Execute();
    });
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetSvgAnimatorFinishEvent(eventMarker);
}

void JSImage::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    std::string src;
    auto noPixMap = ParseJsMedia(info[0], src);

    if (Container::IsCurrentUseNewPipeline() && noPixMap) {
        NG::ImageView::Create(src);
        return;
    }

    RefPtr<ImageComponent> imageComponent = AceType::MakeRefPtr<OHOS::Ace::ImageComponent>(src);
    ViewStackProcessor::GetInstance()->ClaimElementId(imageComponent);
    imageComponent->SetUseSkiaSvg(false);
    ViewStackProcessor::GetInstance()->Push(imageComponent);
    JSInteractableView::SetFocusable(false);
    JSInteractableView::SetFocusNode(true);
    if (noPixMap) {
        return;
    }

#if defined(IMAGE_SUPPORTED)
    imageComponent->SetPixmap(CreatePixelMapFromNapiValue(info[0]));
#endif
}

void JSImage::JsBorder(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBorder(info);
    SetBorder(GetBackDecoration()->GetBorder());
}

void JSImage::JsBorderRadius(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBorderRadius(info);
    SetBorder(GetBackDecoration()->GetBorder());
}

void JSImage::SetSourceSize(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        std::pair<Dimension, Dimension> sourceSize = JSViewAbstract::ParseSize(info);
        NG::ImageView::SetImageSourceSize(sourceSize);
        return;
    }
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetImageSourceSize(JSViewAbstract::ParseSize(info));
}

void JSImage::SetImageFill(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    Color color;
    if (!ParseJsColor(info[0], color)) {
        return;
    }
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetImageFill(color);
}

void JSImage::SetImageRenderMode(int32_t imageRenderMode)
{
    SET_PROP_FOR_NG(ImageRenderMode, ImageRenderMode, imageRenderMode);
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetImageRenderMode(static_cast<ImageRenderMode>(imageRenderMode));
}

void JSImage::SetImageInterpolation(int32_t imageInterpolation)
{
    SET_PROP_FOR_NG(ImageInterpolation, ImageInterpolation, imageInterpolation);
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetImageInterpolation(static_cast<ImageInterpolation>(imageInterpolation));
}

void JSImage::SetImageRepeat(int32_t imageRepeat)
{
    SET_PROP_FOR_NG(ImageRepeat, ImageRepeat, imageRepeat);
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    image->SetImageRepeat(static_cast<ImageRepeat>(imageRepeat));
}

void JSImage::JsTransition(const JSCallbackInfo& info)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image && image->IsSrcSvgImage()) {
        JSViewAbstract::JsTransition(info);
    } else {
        JSViewAbstract::JsTransitionPassThrough(info);
    }
}

void JSImage::JsOpacity(const JSCallbackInfo& info)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image && image->IsSrcSvgImage()) {
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
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto mainComp = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto image = AceType::DynamicCast<ImageComponent>(mainComp);
    if (image) {
        double blur = 0.0;
        if (ParseJsDouble(info[0], blur)) {
            image->SetBlur(blur);
        }
    }
#endif
}

void JSImage::SetAutoResize(bool autoResize)
{
    SET_PROP_FOR_NG(AutoResize, bool, autoResize);
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetAutoResize(autoResize);
    }
}

void JSImage::SetSyncLoad(const JSCallbackInfo& info)
{
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetSyncMode(info[0]->ToBoolean());
    }
}

void JSColorFilter::ConstructorCallback(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        LOGE("The argv is wrong, it it supposed to have at least 1 argument");
        return;
    }
    if (!args[0]->IsArray()) {
        LOGE("jscallback is not object or array");
        return;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(args[0]);
    if (array->Length() != COLOR_FILTER_MATRIX_SIZE) {
        LOGE("arg length illegal");
        return;
    }
    auto jscolorfilter = Referenced::MakeRefPtr<JSColorFilter>();
    if (jscolorfilter == nullptr) {
        LOGE("make jscolorfilter object failed");
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
        LOGE("colorfilter length illegal");
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
    if (info.Length() != 1 || !info[0]->IsObject()) {
        LOGE("The arg is wrong, it is supposed to have 1 arguments");
        return;
    }
    JSColorFilter* colorfilter = JSRef<JSObject>::Cast(info[0])->Unwrap<JSColorFilter>();
    CHECK_NULL_VOID(colorfilter);
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetColorFilterMatrix(colorfilter->GetColorFilterMatrix());
    }
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
    JSClass<JSImage>::StaticMethod("borderStyle", &JSViewAbstract::JsBorderStyle);
    JSClass<JSImage>::StaticMethod("borderColor", &JSViewAbstract::JsBorderColor);
    JSClass<JSImage>::StaticMethod("border", &JSImage::JsBorder);
    JSClass<JSImage>::StaticMethod("borderWidth", &JSViewAbstract::JsBorderWidth);
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
    JSClass<JSImage>::StaticMethod("onDragStart", &JSImage::JsOnDragStart);
    JSClass<JSImage>::StaticMethod("onDragEnter", &JSImage::JsOnDragEnter);
    JSClass<JSImage>::StaticMethod("onDragMove", &JSImage::JsOnDragMove);
    JSClass<JSImage>::StaticMethod("onDragLeave", &JSImage::JsOnDragLeave);
    JSClass<JSImage>::StaticMethod("onDrop", &JSImage::JsOnDrop);
    JSClass<JSImage>::StaticMethod("copyOption", &JSImage::SetCopyOption);
    // override method
    JSClass<JSImage>::StaticMethod("opacity", &JSImage::JsOpacity);
    JSClass<JSImage>::StaticMethod("blur", &JSImage::JsBlur);
    JSClass<JSImage>::StaticMethod("transition", &JSImage::JsTransition);
    JSClass<JSImage>::Inherit<JSViewAbstract>();
    JSClass<JSImage>::Bind<>(globalObj);

    JSClass<JSColorFilter>::Declare("ColorFilter");
    JSClass<JSColorFilter>::Bind(globalObj, JSColorFilter::ConstructorCallback, JSColorFilter::DestructorCallback);
}

void JSImage::JsOnDragStart(const JSCallbackInfo& info)
{
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragStartId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc)](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) -> DragItemInfo {
        DragItemInfo itemInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, itemInfo);

        auto ret = func->Execute(info, extraParams);
        if (!ret->IsObject()) {
            LOGE("builder param is not an object.");
            return itemInfo;
        }
        auto component = ParseDragItemComponent(ret);
        if (component) {
            LOGI("use custom builder param.");
            itemInfo.customComponent = component;
            return itemInfo;
        }

        auto builderObj = JSRef<JSObject>::Cast(ret);
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
        auto pixmap = builderObj->GetProperty("pixelMap");
        itemInfo.pixelMap = CreatePixelMapFromNapiValue(pixmap);
#endif
        auto extraInfo = builderObj->GetProperty("extraInfo");
        ParseJsString(extraInfo, itemInfo.extraInfo);
        component = ParseDragItemComponent(builderObj->GetProperty("builder"));
        itemInfo.customComponent = component;
        return itemInfo;
    };
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetOnDragStartId(onDragStartId);
    }
}

void JSImage::JsOnDragEnter(const JSCallbackInfo& info)
{
    RefPtr<JsDragFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragEnterId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc)](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragEnter");
        func->Execute(info, extraParams);
    };
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetOnDragEnterId(onDragEnterId);
    }
}

void JSImage::JsOnDragMove(const JSCallbackInfo& info)
{
    RefPtr<JsDragFunction> jsOnDragMoveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragMoveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragMoveFunc)](
                            const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragMove");
        func->Execute(info, extraParams);
    };
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetOnDragMoveId(onDragMoveId);
    }
}

void JSImage::JsOnDragLeave(const JSCallbackInfo& info)
{
    RefPtr<JsDragFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragLeaveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragLeaveFunc)](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragLeave");
        func->Execute(info, extraParams);
    };
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetOnDragLeaveId(onDragLeaveId);
    }
}

void JSImage::JsOnDrop(const JSCallbackInfo& info)
{
    RefPtr<JsDragFunction> jsOnDropFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDropId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc)](
                        const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDrop");
        func->Execute(info, extraParams);
    };
    auto image = AceType::DynamicCast<ImageComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (image) {
        image->SetOnDropId(onDropId);
    }
}

void JSImage::SetCopyOption(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    if (!stack) {
        return;
    }
    auto component = AceType::DynamicCast<ImageComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is not valid");
        return;
    }
    auto copyOptions = CopyOptions::None;
    if (info[0]->IsNumber()) {
        auto emunNumber = info[0]->ToNumber<int>();
        copyOptions = static_cast<CopyOptions>(emunNumber);
    }
    LOGI("copy option: %{public}d", copyOptions);
    component->SetCopyOption(copyOptions);
}

} // namespace OHOS::Ace::Framework
