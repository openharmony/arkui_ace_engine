/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_image.h"

#include <cstdint>
#include <memory>
#include <vector>
#if !defined(PREVIEW)
#include <dlfcn.h>
#endif

#include "interfaces/inner_api/ace/ai/image_analyzer.h"
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "base/geometry/ng/vector.h"
#include "base/image/drawing_color_filter.h"
#include "base/image/drawing_lattice.h"
#include "base/image/pixel_map.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/jsview/models/image_model_impl.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/image/image_event.h"
#include "core/components/image/image_theme.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/image/image_model.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/image/image_source_info.h"

namespace {
const std::vector<float> DEFAULT_COLORFILTER_MATRIX = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 };
constexpr float CEIL_SMOOTHEDGE_VALUE = 1.333f;
constexpr float FLOOR_SMOOTHEDGE_VALUE = 0.334f;
constexpr float DEFAULT_SMOOTHEDGE_VALUE = 0.0f;
constexpr uint32_t FIT_MATRIX = 16;
} // namespace

namespace OHOS::Ace {

namespace {
ImageSourceInfo CreateSourceInfo(const std::shared_ptr<std::string>& srcRef, RefPtr<PixelMap>& pixmap,
    const std::string& bundleName, const std::string& moduleName)
{
#if defined(PIXEL_MAP_SUPPORTED)
    if (pixmap) {
        return ImageSourceInfo(pixmap);
    }
#endif
    return { srcRef, bundleName, moduleName };
}
} // namespace

std::unique_ptr<ImageModel> ImageModel::instance_ = nullptr;
std::mutex ImageModel::mutex_;

ImageModel* __attribute__((optnone)) ImageModel::GetInstance()
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
    if (ImageModel::GetInstance()->GetIsAnimation()) {
        return;
    }
    if (args.Length() < 1) {
        return;
    }

    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    bool isCard = context->IsFormRender();

    std::string src;
    bool srcValid = false;
    if (args[0]->IsString()) {
        src = args[0]->ToString();
    } else {
        srcValid = ParseJsMedia(args[0], src);
    }
    if (ImageSourceInfo::ResolveURIType(src) == SrcType::NETWORK) {
        return;
    }
    int32_t resId = 0;
    if (args[0]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> tmp = jsObj->GetProperty("id");
        if (!tmp->IsNull() && tmp->IsNumber()) {
            resId = tmp->ToNumber<int32_t>();
        }
    }
    std::string bundleName;
    std::string moduleName;
    GetJsMediaBundleInfo(args[0], bundleName, moduleName);
    RefPtr<PixelMap> pixmap = nullptr;

    // input is Drawable
    if (!srcValid && !isCard) {
#if defined(PIXEL_MAP_SUPPORTED)
        pixmap = CreatePixelMapFromNapiValue(args[0]);
#endif
    }
    auto srcRef = std::make_shared<std::string>(src);
    auto srcInfo = CreateSourceInfo(srcRef, pixmap, bundleName, moduleName);
    srcInfo.SetIsUriPureNumber((resId == -1));
    ImageModel::GetInstance()->SetAlt(srcInfo);
}

void JSImage::SetObjectFit(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        ImageModel::GetInstance()->SetImageFit(ImageFit::COVER);
        return;
    }
    int32_t parseRes = 2;
    ParseJsInteger(args[0], parseRes);
    if (parseRes < static_cast<int32_t>(ImageFit::FILL) || parseRes > static_cast<int32_t>(ImageFit::MATRIX)) {
        parseRes = 2;
    }
    auto fit = static_cast<ImageFit>(parseRes);
    if (parseRes == FIT_MATRIX) {
        fit = ImageFit::MATRIX;
    }
    ImageModel::GetInstance()->SetImageFit(fit);
}

void JSImage::SetImageMatrix(const JSCallbackInfo& args)
{
    if (args.Length() > 0) {
        auto jsVal = args[0];
        if (!jsVal->IsObject()) {
            SetDefaultImageMatrix();
            return;
        }
        JSRef<JSVal> array = JSRef<JSObject>::Cast(jsVal)->GetProperty(static_cast<int32_t>(ArkUIIndex::MATRIX4X4));
        const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
        if (!array->IsArray()) {
            return;
        }
        JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(array);
        if (jsArray->Length() != matrix4Len) {
            return;
        }
        std::vector<float> matrix(matrix4Len);
        for (int32_t i = 0; i < matrix4Len; i++) {
            double value = 0.0;
            ParseJsDouble(jsArray->GetValueAt(i), value);
            matrix[i] = static_cast<float>(value);
        }
        Matrix4 setValue = Matrix4(
            matrix[0], matrix[4], matrix[8], matrix[12],
            matrix[1], matrix[5], matrix[9], matrix[13],
            matrix[2], matrix[6], matrix[10], matrix[14],
            matrix[3], matrix[7], matrix[11], matrix[15]);
        ImageModel::GetInstance()->SetImageMatrix(setValue);
    } else {
        SetDefaultImageMatrix();
        return;
    }
}

void JSImage::SetDefaultImageMatrix()
{
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    std::vector<float> matrix(matrix4Len);
    const int32_t initPosition = 5;
    for (int32_t i = 0; i < matrix4Len; i = i + initPosition) {
        matrix[i] = 1.0f;
    }
    Matrix4 setValue = Matrix4(
        matrix[0], matrix[4], matrix[8], matrix[12],
        matrix[1], matrix[5], matrix[9], matrix[13],
        matrix[2], matrix[6], matrix[10], matrix[14],
        matrix[3], matrix[7], matrix[11], matrix[15]);
    ImageModel::GetInstance()->SetImageMatrix(setValue);
}

void JSImage::SetMatchTextDirection(bool value)
{
    if (ImageModel::GetInstance()->GetIsAnimation()) {
        return;
    }
    ImageModel::GetInstance()->SetMatchTextDirection(value);
}

void JSImage::SetFitOriginalSize(bool value)
{
    if (ImageModel::GetInstance()->GetIsAnimation()) {
        return;
    }
    ImageModel::GetInstance()->SetFitOriginSize(value);
}

void JSImage::SetBorder(const Border& border)
{
    ImageModel::GetInstance()->SetBorder(border);
}

void JSImage::OnComplete(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto jsLoadSuccFunc = AceType::MakeRefPtr<JsEventFunction<LoadImageSuccessEvent, 1>>(
            JSRef<JSFunc>::Cast(args[0]), LoadImageSuccEventToJSValue);

        auto onComplete = [execCtx = args.GetExecutionContext(), func = std::move(jsLoadSuccFunc)](
                              const LoadImageSuccessEvent& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Image.onComplete");
            func->Execute(info);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
            UiSessionManager::GetInstance().ReportComponentChangeEvent("event", "Image.onComplete");
#endif
        };
        ImageModel::GetInstance()->SetOnComplete(std::move(onComplete));
    }
}

void JSImage::OnError(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto jsLoadFailFunc = AceType::MakeRefPtr<JsEventFunction<LoadImageFailEvent, 1>>(
            JSRef<JSFunc>::Cast(args[0]), LoadImageFailEventToJSValue);
        auto onError = [execCtx = args.GetExecutionContext(), func = std::move(jsLoadFailFunc)](
                           const LoadImageFailEvent& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Image.onError");
            func->Execute(info);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
            UiSessionManager::GetInstance().ReportComponentChangeEvent("event", "Image.onError");
#endif
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
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onFinish = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Image.onFinish");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };
    ImageModel::GetInstance()->SetSvgAnimatorFinishEvent(onFinish);
}

void JSImage::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CreateImage(info);
}

bool JSImage::CheckIsCard()
{
    auto container = Container::Current();
    if (!container) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "Container is null in CreateImage.");
        return false;
    }
    return container->IsFormRender() && !container->IsDynamicRender();
}

bool JSImage::CheckResetImage(const JSCallbackInfo& info)
{
    int32_t parseRes = -1;
    if (info.Length() < 1 || !ParseJsInteger(info[0], parseRes)) {
        return false;
    }
    ImageModel::GetInstance()->ResetImage();
    return true;
}

void JSImage::CreateImage(const JSCallbackInfo& info, bool isImageSpan)
{
    bool isCard = CheckIsCard();

    // Interim programme
    std::string bundleName;
    std::string moduleName;
    std::string src;
    auto imageInfo = info[0];
    int32_t resId = 0;
    bool srcValid = ParseJsMediaWithBundleName(imageInfo, src, bundleName, moduleName, resId);
    if (!srcValid && CheckResetImage(info)) {
        return;
    }
    if (isCard && imageInfo->IsString()) {
        SrcType srcType = ImageSourceInfo::ResolveURIType(src);
        bool notSupport = (srcType == SrcType::NETWORK || srcType == SrcType::FILE || srcType == SrcType::DATA_ABILITY);
        if (notSupport) {
            src.clear();
        }
    }
    RefPtr<PixelMap> pixmap = nullptr;

    // input is PixelMap / Drawable
    if (!srcValid) {
#if defined(PIXEL_MAP_SUPPORTED)
        std::vector<RefPtr<PixelMap>> pixelMaps;
        int32_t duration = -1;
        int32_t iterations = 1;
        if (IsDrawable(imageInfo)) {
            if (GetPixelMapListFromAnimatedDrawable(imageInfo, pixelMaps, duration, iterations)) {
                CreateImageAnimation(pixelMaps, duration, iterations);
                return;
            }
            pixmap = GetDrawablePixmap(imageInfo);
        } else {
            pixmap = CreatePixelMapFromNapiValue(imageInfo);
        }
#endif
    }
    ImageInfoConfig imageInfoConfig(
        std::make_shared<std::string>(src), bundleName, moduleName, (resId == -1), isImageSpan);
    ImageModel::GetInstance()->Create(imageInfoConfig, pixmap);

    if (info.Length() > 1) {
        auto options = info[1];
        if (!options->IsObject()) {
            return;
        }
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        panda::Local<JsiValue> value = options.Get().GetLocalHandle();
        JSValueWrapper valueWrapper = value;
        ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
        napi_value optionsValue = nativeEngine->ValueToNapiValue(valueWrapper);
        ImageModel::GetInstance()->SetImageAIOptions(optionsValue);
    }
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
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        JSViewAbstract::JsBorder(info);
        ImageModel::GetInstance()->SetBackBorder();
        return;
    }
    // handles generic property logic.
    JSViewAbstract::JsBorder(info);
    // handles the image component separately, aiming to extract and set the borderRadius property
    if (!info[0]->IsObject()) {
        CalcDimension borderRadius;
        ImageModel::GetInstance()->SetBorderRadius(borderRadius);
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);

    auto valueRadius = object->GetProperty(static_cast<int32_t>(ArkUIIndex::RADIUS));
    if (!valueRadius->IsUndefined()) {
        ParseBorderRadius(valueRadius);
    }
}

void JSImage::ParseBorderRadius(const JSRef<JSVal>& args)
{
    CalcDimension borderRadius;
    if (ParseJsDimensionVp(args, borderRadius)) {
        ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius);
        ImageModel::GetInstance()->SetBorderRadius(borderRadius);
    } else if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        CalcDimension topLeft;
        CalcDimension topRight;
        CalcDimension bottomLeft;
        CalcDimension bottomRight;
        if (ParseAllBorderRadiuses(object, topLeft, topRight, bottomLeft, bottomRight)) {
            ImageModel::GetInstance()->SetBorderRadius(
                GetLocalizedBorderRadius(topLeft, topRight, bottomLeft, bottomRight));
            ViewAbstractModel::GetInstance()->SetBorderRadius(
                GetLocalizedBorderRadius(topLeft, topRight, bottomLeft, bottomRight));
            return;
        }
        ImageModel::GetInstance()->SetBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
        ViewAbstractModel::GetInstance()->SetBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
    }
}

void JSImage::ParseResizableSlice(const JSRef<JSObject>& resizableObject)
{
    ImageResizableSlice sliceResult;
    if (resizableObject->IsEmpty()) {
        ImageModel::GetInstance()->SetResizableSlice(sliceResult);
        return;
    }
    auto sliceValue = resizableObject->GetProperty("slice");
    if (!sliceValue->IsObject()) {
        ImageModel::GetInstance()->SetResizableSlice(sliceResult);
        return;
    }
    JSRef<JSObject> sliceObj = JSRef<JSObject>::Cast(sliceValue);
    if (sliceObj->IsEmpty()) {
        ImageModel::GetInstance()->SetResizableSlice(sliceResult);
        return;
    }
    UpdateSliceResult(sliceObj, sliceResult);

    ImageModel::GetInstance()->SetResizableSlice(sliceResult);
}

void JSImage::ParseResizableLattice(const JSRef<JSObject>& resizableObject)
{
    auto latticeValue = resizableObject->GetProperty("lattice");
    if (latticeValue->IsUndefined() || latticeValue->IsNull()) {
        ImageModel::GetInstance()->ResetResizableLattice();
    }
    CHECK_NULL_VOID(latticeValue->IsObject());
    auto drawingLattice = CreateDrawingLattice(latticeValue);
    if (drawingLattice) {
        ImageModel::GetInstance()->SetResizableLattice(drawingLattice);
    } else {
        ImageModel::GetInstance()->ResetResizableLattice();
    }
}

void JSImage::JsImageResizable(const JSCallbackInfo& info)
{
    if (ImageModel::GetInstance()->GetIsAnimation()) {
        return;
    }
    auto infoObj = info[0];
    if (!infoObj->IsObject()) {
        ImageModel::GetInstance()->SetResizableSlice(ImageResizableSlice());
        return;
    }
    JSRef<JSObject> resizableObject = JSRef<JSObject>::Cast(infoObj);
    ParseResizableSlice(resizableObject);
    ParseResizableLattice(resizableObject);
}

void JSImage::UpdateSliceResult(const JSRef<JSObject>& sliceObj, ImageResizableSlice& sliceResult)
{
    // creatge a array has 4 elements for paresing sliceSize
    static std::array<int32_t, 4> keys = { static_cast<int32_t>(ArkUIIndex::LEFT),
        static_cast<int32_t>(ArkUIIndex::RIGHT), static_cast<int32_t>(ArkUIIndex::TOP),
        static_cast<int32_t>(ArkUIIndex::BOTTOM) };
    for (uint32_t i = 0; i < keys.size(); i++) {
        auto sliceSize = sliceObj->GetProperty(keys.at(i));
        CalcDimension sliceDimension;
        if (!ParseJsDimensionVp(sliceSize, sliceDimension)) {
            continue;
        }
        if (!sliceDimension.IsValid()) {
            continue;
        }
        switch (static_cast<BorderImageDirection>(i)) {
            case BorderImageDirection::LEFT:
                sliceResult.left = sliceDimension;
                break;
            case BorderImageDirection::RIGHT:
                sliceResult.right = sliceDimension;
                break;
            case BorderImageDirection::TOP:
                sliceResult.top = sliceDimension;
                break;
            case BorderImageDirection::BOTTOM:
                sliceResult.bottom = sliceDimension;
                break;
            default:
                break;
        }
    }
    ImageModel::GetInstance()->SetResizableSlice(sliceResult);
}

void JSImage::JsBorderRadius(const JSCallbackInfo& info)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        JSViewAbstract::JsBorderRadius(info);
        ImageModel::GetInstance()->SetBackBorder();
        return;
    }
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
        JSCallbackInfoType::OBJECT };
    auto jsVal = info[0];
    if (!CheckJSCallbackInfo("JsBorderRadius", jsVal, checkList)) {
        ViewAbstractModel::GetInstance()->SetBorderRadius(Dimension {});
        ImageModel::GetInstance()->SetBorderRadius(Dimension {});
        return;
    }
    ParseBorderRadius(jsVal);
}

void JSImage::SetSourceSize(const JSCallbackInfo& info)
{
    if (ImageModel::GetInstance()->GetIsAnimation()) {
        return;
    }
    ImageModel::GetInstance()->SetImageSourceSize(JSViewAbstract::ParseSize(info));
}

void JSImage::SetImageFill(const JSCallbackInfo& info)
{
    if (ImageModel::GetInstance()->GetIsAnimation()) {
        return;
    }
    if (info.Length() < 1) {
        return;
    }

    Color color;
    if (!ParseJsColor(info[0], color)) {
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_ELEVEN)) {
            return;
        }
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<ImageTheme>();
        CHECK_NULL_VOID(theme);
        color = theme->GetFillColor();
    }
    ImageModel::GetInstance()->SetImageFill(color);
}

void JSImage::SetImageRenderMode(const JSCallbackInfo& info)
{
    if (ImageModel::GetInstance()->GetIsAnimation()) {
        return;
    }
    if (info.Length() < 1) {
        ImageModel::GetInstance()->SetImageRenderMode(ImageRenderMode::ORIGINAL);
        return;
    }
    auto jsImageRenderMode = info[0];
    if (jsImageRenderMode->IsNumber()) {
        auto renderMode = static_cast<ImageRenderMode>(jsImageRenderMode->ToNumber<int32_t>());
        if (renderMode < ImageRenderMode::ORIGINAL || renderMode > ImageRenderMode::TEMPLATE) {
            renderMode = ImageRenderMode::ORIGINAL;
        }
        ImageModel::GetInstance()->SetImageRenderMode(renderMode);
    } else {
        ImageModel::GetInstance()->SetImageRenderMode(ImageRenderMode::ORIGINAL);
    }
}

void JSImage::SetImageInterpolation(int32_t imageInterpolation)
{
    if (ImageModel::GetInstance()->GetIsAnimation()) {
        return;
    }
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
    if (ImageModel::GetInstance()->GetIsAnimation()) {
        return;
    }
    ImageModel::GetInstance()->SetAutoResize(autoResize);
}

void JSImage::SetSyncLoad(const JSCallbackInfo& info)
{
    if (ImageModel::GetInstance()->GetIsAnimation()) {
        return;
    }
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
        ImageModel::GetInstance()->SetColorFilterMatrix(DEFAULT_COLORFILTER_MATRIX);
        return;
    }
    auto tmpInfo = info[0];
    if (!tmpInfo->IsArray() && !tmpInfo->IsObject()) {
        ImageModel::GetInstance()->SetColorFilterMatrix(DEFAULT_COLORFILTER_MATRIX);
        return;
    }
    if (tmpInfo->IsObject() && !tmpInfo->IsArray()) {
        auto drawingColorFilter = CreateDrawingColorFilter(tmpInfo);
        if (drawingColorFilter) {
            ImageModel::GetInstance()->SetDrawingColorFilter(drawingColorFilter);
            return;
        }
        JSColorFilter* colorFilter;
        if (!tmpInfo->IsUndefined() && !tmpInfo->IsNull()) {
            colorFilter = JSRef<JSObject>::Cast(tmpInfo)->Unwrap<JSColorFilter>();
        } else {
            ImageModel::GetInstance()->SetColorFilterMatrix(DEFAULT_COLORFILTER_MATRIX);
            return;
        }
        if (colorFilter && colorFilter->GetColorFilterMatrix().size() == COLOR_FILTER_MATRIX_SIZE) {
            ImageModel::GetInstance()->SetColorFilterMatrix(colorFilter->GetColorFilterMatrix());
            return;
        }
        ImageModel::GetInstance()->SetColorFilterMatrix(DEFAULT_COLORFILTER_MATRIX);
        return;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(tmpInfo);
    if (array->Length() != COLOR_FILTER_MATRIX_SIZE) {
        ImageModel::GetInstance()->SetColorFilterMatrix(DEFAULT_COLORFILTER_MATRIX);
        return;
    }
    std::vector<float> colorfilter;
    for (size_t i = 0; i < array->Length(); i++) {
        JSRef<JSVal> value = array->GetValueAt(i);
        if (value->IsNumber()) {
            colorfilter.emplace_back(value->ToNumber<float>());
        } else {
            ImageModel::GetInstance()->SetColorFilterMatrix(DEFAULT_COLORFILTER_MATRIX);
            return;
        }
    }
    ImageModel::GetInstance()->SetColorFilterMatrix(colorfilter);
}

void JSImage::SetSmoothEdge(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        ImageModel::GetInstance()->SetSmoothEdge(DEFAULT_SMOOTHEDGE_VALUE);
        return;
    }
    double parseRes = DEFAULT_SMOOTHEDGE_VALUE;
    ParseJsDouble(info[0], parseRes);
    // Effective range : (FLOOR_SMOOTHEDGE_VALUE, CEIL_SMOOTHEDGE_VALUE]
    // otherwise: DEFAULT_SMOOTHEDGE_VALUE
    if (GreatNotEqual(parseRes, CEIL_SMOOTHEDGE_VALUE) || LessNotEqual(parseRes, FLOOR_SMOOTHEDGE_VALUE)) {
        parseRes = DEFAULT_SMOOTHEDGE_VALUE;
    }
    ImageModel::GetInstance()->SetSmoothEdge(static_cast<float>(parseRes));
}

void JSImage::SetDynamicRangeMode(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        ImageModel::GetInstance()->SetDynamicRangeMode(DynamicRangeMode::STANDARD);
        return;
    }
    int32_t parseRes = static_cast<int32_t>(DynamicRangeMode::STANDARD);
    ParseJsInteger(info[0], parseRes);
    if (parseRes < static_cast<int32_t>(DynamicRangeMode::HIGH) ||
        parseRes > static_cast<int32_t>(DynamicRangeMode::STANDARD)) {
        parseRes = static_cast<int32_t>(DynamicRangeMode::STANDARD);
    }
    DynamicRangeMode dynamicRangeMode = static_cast<DynamicRangeMode>(parseRes);
    ImageModel::GetInstance()->SetDynamicRangeMode(dynamicRangeMode);
}

void JSImage::SetEnhancedImageQuality(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        ImageModel::GetInstance()->SetEnhancedImageQuality(AIImageQuality::LOW);
        return;
    }
    int32_t parseRes = static_cast<int32_t>(AIImageQuality::LOW);
    ParseJsInteger(info[0], parseRes);
    if (parseRes < static_cast<int32_t>(AIImageQuality::LOW) || parseRes > static_cast<int32_t>(AIImageQuality::HIGH)) {
        parseRes = static_cast<int32_t>(AIImageQuality::LOW);
    }
    AIImageQuality resolutionQuality = static_cast<AIImageQuality>(parseRes);
    ImageModel::GetInstance()->SetEnhancedImageQuality(resolutionQuality);
}

void JSImage::SetOrientation(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        ImageModel::GetInstance()->SetOrientation(ImageRotateOrientation::UP);
        return;
    }
    int32_t parseRes = 0;
    ParseJsInteger(info[0], parseRes);
    if (parseRes < static_cast<int>(ImageRotateOrientation::AUTO) ||
        parseRes > static_cast<int>(ImageRotateOrientation::LEFT)) {
        parseRes = static_cast<int>(ImageRotateOrientation::UP);
    }
    auto res = static_cast<ImageRotateOrientation>(parseRes);
    ImageModel::GetInstance()->SetOrientation(res);
}

void JSImage::CreateImageAnimation(std::vector<RefPtr<PixelMap>>& pixelMaps, int32_t duration, int32_t iterations)
{
    std::vector<ImageProperties> imageList;
    for (int i = 0; i < static_cast<int32_t>(pixelMaps.size()); i++) {
        ImageProperties image;
        image.pixelMap = pixelMaps[i];
        imageList.push_back(image);
    }
    ImageModel::GetInstance()->CreateAnimation(imageList, duration, iterations);
}

void JSImage::JSBind(BindingTarget globalObj)
{
    JSClass<JSImage>::Declare("Image");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSImage>::StaticMethod("create", &JSImage::Create, opt);
    JSClass<JSImage>::StaticMethod("alt", &JSImage::SetAlt, opt);
    JSClass<JSImage>::StaticMethod("objectFit", &JSImage::SetObjectFit, opt);
    JSClass<JSImage>::StaticMethod("imageMatrix", &JSImage::SetImageMatrix, opt);
    JSClass<JSImage>::StaticMethod("matchTextDirection", &JSImage::SetMatchTextDirection, opt);
    JSClass<JSImage>::StaticMethod("fitOriginalSize", &JSImage::SetFitOriginalSize, opt);
    JSClass<JSImage>::StaticMethod("sourceSize", &JSImage::SetSourceSize, opt);
    JSClass<JSImage>::StaticMethod("fillColor", &JSImage::SetImageFill, opt);
    JSClass<JSImage>::StaticMethod("renderMode", &JSImage::SetImageRenderMode, opt);
    JSClass<JSImage>::StaticMethod("objectRepeat", &JSImage::SetImageRepeat, opt);
    JSClass<JSImage>::StaticMethod("interpolation", &JSImage::SetImageInterpolation, opt);
    JSClass<JSImage>::StaticMethod("colorFilter", &JSImage::SetColorFilter, opt);
    JSClass<JSImage>::StaticMethod("edgeAntialiasing", &JSImage::SetSmoothEdge, opt);
    JSClass<JSImage>::StaticMethod("dynamicRangeMode", &JSImage::SetDynamicRangeMode, opt);
    JSClass<JSImage>::StaticMethod("enhancedImageQuality", &JSImage::SetEnhancedImageQuality, opt);
    JSClass<JSImage>::StaticMethod("orientation", &JSImage::SetOrientation, opt);

    JSClass<JSImage>::StaticMethod("border", &JSImage::JsBorder);
    JSClass<JSImage>::StaticMethod("borderRadius", &JSImage::JsBorderRadius);
    JSClass<JSImage>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSImage>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSImage>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSImage>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSImage>::StaticMethod("autoResize", &JSImage::SetAutoResize);
    JSClass<JSImage>::StaticMethod("resizable", &JSImage::JsImageResizable);

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
    JSClass<JSImage>::StaticMethod("enableAnalyzer", &JSImage::EnableAnalyzer);
    JSClass<JSImage>::StaticMethod("analyzerConfig", &JSImage::AnalyzerConfig);

    // override method
    JSClass<JSImage>::StaticMethod("opacity", &JSImage::JsOpacity);
    JSClass<JSImage>::StaticMethod("blur", &JSImage::JsBlur);
    JSClass<JSImage>::StaticMethod("transition", &JSImage::JsTransition);
    JSClass<JSImage>::StaticMethod("pointLight", &JSViewAbstract::JsPointLight, opt);
    JSClass<JSImage>::InheritAndBind<JSViewAbstract>(globalObj);

    JSClass<JSColorFilter>::Declare("ColorFilter");
    JSClass<JSColorFilter>::Bind(globalObj, JSColorFilter::ConstructorCallback, JSColorFilter::DestructorCallback);
}

void JSImage::JsSetDraggable(const JSCallbackInfo& info)
{
    bool draggable = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN);
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        draggable = info[0]->ToBoolean();
    }
    ImageModel::GetInstance()->SetDraggable(draggable);
}

void JSImage::JsOnDragStart(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsFunction()) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDragStartId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc), node = frameNode](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) -> NG::DragDropBaseInfo {
        NG::DragDropBaseInfo itemInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, itemInfo);
        PipelineContext::SetCallBackNode(node);
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
    if (ImageModel::GetInstance()->GetIsAnimation()) {
        return;
    }
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

void JSImage::EnableAnalyzer(bool isEnableAnalyzer)
{
    if (ImageModel::GetInstance()->GetIsAnimation()) {
        return;
    }
    ImageModel::GetInstance()->EnableAnalyzer(isEnableAnalyzer);
}

void JSImage::AnalyzerConfig(const JSCallbackInfo& info)
{
    auto configParams = info[0];
    if (configParams->IsNull() || !configParams->IsObject()) {
        return;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    panda::Local<JsiValue> value = configParams.Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value nativeValue = nativeEngine->ValueToNapiValue(valueWrapper);
    ImageModel::GetInstance()->SetImageAnalyzerConfig(nativeValue);

    // As an example, the function is not in effect.
    auto paramObject = JSRef<JSObject>::Cast(configParams);
    JSRef<JSVal> typeVal = paramObject->GetProperty("types");
    ImageAnalyzerConfig analyzerConfig;
    if (typeVal->IsArray()) {
        auto array = JSRef<JSArray>::Cast(typeVal);
        std::set<ImageAnalyzerType> types;
        for (size_t i = 0; i < array->Length(); ++i) {
            if (!array->GetValueAt(i)->IsNumber()) {
                continue;
            }
            int value = array->GetValueAt(i)->ToNumber<int>();
            ImageAnalyzerType type = static_cast<ImageAnalyzerType>(value);
            if (type != ImageAnalyzerType::SUBJECT && type != ImageAnalyzerType::TEXT) {
                continue;
            }
            types.insert(type);
        }
        analyzerConfig.types = std::move(types);
    }
    ImageModel::GetInstance()->SetImageAnalyzerConfig(analyzerConfig);
}

} // namespace OHOS::Ace::Framework
