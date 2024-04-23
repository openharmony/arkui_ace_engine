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

#include "bridge/declarative_frontend/jsview/js_canvas_renderer.h"

#include <cstdint>

#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/jsview/js_canvas_pattern.h"
#include "bridge/declarative_frontend/jsview/js_offscreen_rendering_context.h"
#include "core/components/common/properties/paint_state.h"

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#include "pixel_map_napi.h"
#endif

namespace OHOS::Ace {
constexpr uint32_t PIXEL_SIZE = 4;
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
std::unordered_map<int32_t, std::shared_ptr<Pattern>> JSCanvasRenderer::pattern_;
unsigned int JSCanvasRenderer::patternCount_ = 0;
namespace {

const std::set<std::string> FONT_WEIGHTS = {
    "normal", "bold", "lighter", "bolder",
    "100", "200", "300", "400", "500", "600", "700", "800", "900"
};
const std::set<std::string> FONT_STYLES = { "italic", "oblique", "normal" };
const std::set<std::string> FONT_FAMILIES = { "sans-serif", "serif", "monospace" };
const std::set<std::string> QUALITY_TYPE = { "low", "medium", "high" }; // Default value is low.
constexpr double DEFAULT_QUALITY = 0.92;
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr double DIFF = 1e-10;
template<typename T>
inline T ConvertStrToEnum(const char* key, const LinearMapNode<T>* map, size_t length, T defaultValue)
{
    int64_t index = BinarySearchFindIndex(map, length, key);
    return index != -1 ? map[index].value : defaultValue;
}

inline Rect GetJsRectParam(const JSCallbackInfo& info)
{
    // 4 parameters: rect(x, y, width, height)
    if (info.Length() != 4) {
        return Rect();
    }
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    JSViewAbstract::ParseJsDouble(info[0], x);
    JSViewAbstract::ParseJsDouble(info[1], y);
    JSViewAbstract::ParseJsDouble(info[2], width);
    JSViewAbstract::ParseJsDouble(info[3], height);
    x = PipelineBase::Vp2PxWithCurrentDensity(x);
    y = PipelineBase::Vp2PxWithCurrentDensity(y);
    width = PipelineBase::Vp2PxWithCurrentDensity(width);
    height = PipelineBase::Vp2PxWithCurrentDensity(height);

    Rect rect = Rect(x, y, width, height);
    return rect;
}

inline bool ParseJsDoubleArray(const JSRef<JSVal>& jsValue, std::vector<double>& result)
{
    if (!jsValue->IsArray() && !jsValue->IsObject()) {
        return false;
    }

    if (jsValue->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(jsValue);
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> value = array->GetValueAt(i);
            if (value->IsNumber()) {
                result.emplace_back(value->ToNumber<double>());
            } else if (value->IsObject()) {
                double singleResInt;
                if (JSViewAbstract::ParseJsDouble(value, singleResInt)) {
                    result.emplace_back(singleResInt);
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        return true;
    }
    return false;
}

inline bool ParseJsInt(const JSRef<JSVal>& jsValue, int32_t& result)
{
    if (!jsValue->IsNumber() && !jsValue->IsObject()) {
        return false;
    }

    if (jsValue->IsNumber()) {
        result = jsValue->ToNumber<int32_t>();
        return true;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> type = jsObj->GetProperty("type");
    if (!type->IsNumber()) {
        return false;
    }

    JSRef<JSVal> resId = jsObj->GetProperty("id");
    if (!resId->IsNumber()) {
        return false;
    }
    return false;
}

const LinearMapNode<TextBaseline> BASELINE_TABLE[] = {
    { "alphabetic", TextBaseline::ALPHABETIC },
    { "bottom", TextBaseline::BOTTOM },
    { "hanging", TextBaseline::HANGING },
    { "ideographic", TextBaseline::IDEOGRAPHIC },
    { "middle", TextBaseline::MIDDLE },
    { "top", TextBaseline::TOP },
};

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

#if !defined(PREVIEW)
RefPtr<PixelMap> CreatePixelMapFromNapiValue(JSRef<JSVal> obj)
{
    if (!obj->IsObject()) {
        return nullptr;
    }
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (!runtime) {
        return nullptr;
    }
    auto* nativeEngine = runtime->GetNativeEngine();
    if (nativeEngine == nullptr) {
        return nullptr;
    }
#ifdef USE_ARK_ENGINE
    panda::Local<JsiValue> value = obj.Get().GetLocalHandle();
#endif
    JSValueWrapper valueWrapper = value;

    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    napi_value napiValue = nativeEngine->ValueToNapiValue(valueWrapper);

    PixelMapNapiEntry pixelMapNapiEntry = JsEngine::GetPixelMapNapiEntry();
    if (!pixelMapNapiEntry) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }

    void* pixmapPtrAddr = pixelMapNapiEntry(env, napiValue);
    if (pixmapPtrAddr == nullptr) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    napi_close_handle_scope(env, scope);
    return PixelMap::CreatePixelMap(pixmapPtrAddr);
}
#endif
} // namespace

JSCanvasRenderer::JSCanvasRenderer()
{
    SetInstanceId(Container::CurrentIdSafely());
}

void JSCanvasRenderer::JsCreateLinearGradient(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    JSRef<JSObject> pasteObj = JSClass<JSCanvasGradient>::NewInstance();
    pasteObj->SetProperty("__type", "gradient");

    if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber()) {
        double x0 = 0.0;
        double y0 = 0.0;
        double x1 = 0.0;
        double y1 = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], x0);
        JSViewAbstract::ParseJsDouble(info[1], y0);
        JSViewAbstract::ParseJsDouble(info[2], x1);
        JSViewAbstract::ParseJsDouble(info[3], y1);
        x0 = PipelineBase::Vp2PxWithCurrentDensity(x0);
        y0 = PipelineBase::Vp2PxWithCurrentDensity(y0);
        x1 = PipelineBase::Vp2PxWithCurrentDensity(x1);
        y1 = PipelineBase::Vp2PxWithCurrentDensity(y1);
        Offset beginOffset = Offset(x0, y0);
        Offset endOffset = Offset(x1, y1);

        Gradient* gradient = new Gradient();
        gradient->SetType(GradientType::LINEAR);
        gradient->SetBeginOffset(beginOffset);
        gradient->SetEndOffset(endOffset);

        auto pasteData = Referenced::Claim(pasteObj->Unwrap<JSCanvasGradient>());
        pasteData->SetGradient(gradient);
        info.SetReturnValue(pasteObj);
    }
}

void JSCanvasRenderer::JsCreateRadialGradient(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    JSRef<JSObject> pasteObj = JSClass<JSCanvasGradient>::NewInstance();
    pasteObj->SetProperty("__type", "gradient");

    if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber() &&
        info[4]->IsNumber() && info[5]->IsNumber()) {
        double startX = 0.0;
        double startY = 0.0;
        double startRadial = 0.0;
        double endX = 0.0;
        double endY = 0.0;
        double endRadial = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], startX);
        JSViewAbstract::ParseJsDouble(info[1], startY);
        JSViewAbstract::ParseJsDouble(info[2], startRadial);
        JSViewAbstract::ParseJsDouble(info[3], endX);
        JSViewAbstract::ParseJsDouble(info[4], endY);
        JSViewAbstract::ParseJsDouble(info[5], endRadial);
        startX = PipelineBase::Vp2PxWithCurrentDensity(startX);
        startY = PipelineBase::Vp2PxWithCurrentDensity(startY);
        startRadial = PipelineBase::Vp2PxWithCurrentDensity(startRadial);
        endX = PipelineBase::Vp2PxWithCurrentDensity(endX);
        endY = PipelineBase::Vp2PxWithCurrentDensity(endY);
        endRadial = PipelineBase::Vp2PxWithCurrentDensity(endRadial);
        Offset innerCenter = Offset(startX, startY);
        Offset outerCenter = Offset(endX, endY);

        Gradient* gradient = new Gradient();
        gradient->SetType(GradientType::RADIAL);
        gradient->SetBeginOffset(innerCenter);
        gradient->SetEndOffset(outerCenter);
        gradient->SetInnerRadius(startRadial);
        gradient->SetOuterRadius(endRadial);

        auto pasteData = Referenced::Claim(pasteObj->Unwrap<JSCanvasGradient>());
        pasteData->SetGradient(gradient);
        info.SetReturnValue(pasteObj);
    }
}

void JSCanvasRenderer::JsCreateConicGradient(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() != 3) {
        return;
    }

    JSRef<JSObject> pasteObj = JSClass<JSCanvasGradient>::NewInstance();
    pasteObj->SetProperty("__type", "gradient");

    // in radian
    double startAngle = 0.0;
    double x = 0.0;
    double y = 0.0;
    if (info[0]->IsNumber()) {
        JSViewAbstract::ParseJsDouble(info[0], startAngle);
    } else {
        startAngle = 0.0;
    }
    if (info[1]->IsNumber()) {
        JSViewAbstract::ParseJsDouble(info[1], x);
    } else {
        x = 0.0;
    }
    if (info[2]->IsNumber()) {
        JSViewAbstract::ParseJsDouble(info[2], y);
    } else {
        y = 0.0;
    }

    x = PipelineBase::Vp2PxWithCurrentDensity(x);
    y = PipelineBase::Vp2PxWithCurrentDensity(y);
    startAngle = fmod(startAngle, (2 * M_PI));

    Gradient* gradient = new Gradient();
    gradient->SetType(GradientType::CONIC);
    gradient->GetConicGradient().startAngle = AnimatableDimension(Dimension(startAngle));
    gradient->GetConicGradient().centerX = AnimatableDimension(Dimension(x));
    gradient->GetConicGradient().centerY = AnimatableDimension(Dimension(y));

    auto pasteData = Referenced::Claim(pasteObj->Unwrap<JSCanvasGradient>());
    pasteData->SetGradient(gradient);
    info.SetReturnValue(pasteObj);
}

void JSCanvasRenderer::JsFillText(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsString() && info[1]->IsNumber() && info[2]->IsNumber()) {
        double x = 0.0;
        double y = 0.0;
        std::string text = "";
        JSViewAbstract::ParseJsString(info[0], text);
        JSViewAbstract::ParseJsDouble(info[1], x);
        JSViewAbstract::ParseJsDouble(info[2], y);
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        std::optional<double> maxWidth;
        if (info.Length() >= 4) {
            double width = 0.0;
            if (info[3]->IsUndefined()) {
                width = FLT_MAX;
            } else if (info[3]->IsNumber()) {
                JSViewAbstract::ParseJsDouble(info[3], width);
                width = PipelineBase::Vp2PxWithCurrentDensity(width);
            }
            maxWidth = width;
        }

        FillTextInfo fillTextInfo;
        fillTextInfo.text = text;
        fillTextInfo.x = x;
        fillTextInfo.y = y;
        fillTextInfo.maxWidth = maxWidth;

        renderingContext2DModel_->SetFillText(paintState_, fillTextInfo);
    }
}

void JSCanvasRenderer::JsStrokeText(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsString() && info[1]->IsNumber() && info[2]->IsNumber()) {
        double x = 0.0;
        double y = 0.0;
        std::string text = "";
        JSViewAbstract::ParseJsString(info[0], text);
        JSViewAbstract::ParseJsDouble(info[1], x);
        JSViewAbstract::ParseJsDouble(info[2], y);
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        std::optional<double> maxWidth;
        if (info.Length() >= 4) {
            double width = 0.0;
            if (info[3]->IsUndefined()) {
                width = FLT_MAX;
            } else if (info[3]->IsNumber()) {
                JSViewAbstract::ParseJsDouble(info[3], width);
                width = PipelineBase::Vp2PxWithCurrentDensity(width);
            }
            maxWidth = width;
        }

        FillTextInfo fillTextInfo;
        fillTextInfo.text = text;
        fillTextInfo.x = x;
        fillTextInfo.y = y;
        fillTextInfo.maxWidth = maxWidth;

        renderingContext2DModel_->SetStrokeText(paintState_, fillTextInfo);
    }
}

void JSCanvasRenderer::SetAntiAlias()
{
    renderingContext2DModel_->SetAntiAlias(anti_);
}

void JSCanvasRenderer::JsSetFont(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }
    std::string fontStr = "";
    JSViewAbstract::ParseJsString(info[0], fontStr);
    std::vector<std::string> fontProps;
    StringUtils::StringSplitter(fontStr.c_str(), ' ', fontProps);
    bool updateFontweight = false;
    bool updateFontStyle = false;
    for (const auto& fontProp : fontProps) {
        if (FONT_WEIGHTS.find(fontProp) != FONT_WEIGHTS.end()) {
            updateFontweight = true;
            auto weight = ConvertStrToFontWeight(fontProp);
            style_.SetFontWeight(weight);
            renderingContext2DModel_->SetFontWeight(weight);
        } else if (FONT_STYLES.find(fontProp) != FONT_STYLES.end()) {
            updateFontStyle = true;
            auto fontStyle = ConvertStrToFontStyle(fontProp);
            style_.SetFontStyle(fontStyle);
            renderingContext2DModel_->SetFontStyle(fontStyle);
        } else if (FONT_FAMILIES.find(fontProp) != FONT_FAMILIES.end()) {
            auto families = ConvertStrToFontFamilies(fontProp);
            style_.SetFontFamilies(families);
            renderingContext2DModel_->SetFontFamilies(families);
        } else if (fontProp.find("px") != std::string::npos || fontProp.find("vp") != std::string::npos) {
            Dimension size;
            if (fontProp.find("vp") != std::string::npos) {
                size = GetDimensionValue(fontProp);
            } else {
                std::string fontSize = fontProp.substr(0, fontProp.size() - 2);
                size = Dimension(StringToDouble(fontProp));
            }
            style_.SetFontSize(size);
            renderingContext2DModel_->SetFontSize(size);
        }
    }
    if (!updateFontStyle) {
        renderingContext2DModel_->SetFontStyle(FontStyle::NORMAL);
    }
    if (!updateFontweight) {
        renderingContext2DModel_->SetFontWeight(FontWeight::NORMAL);
    }
}

void JSCanvasRenderer::JsGetFont(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetFillStyle(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetStrokeStyle(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetLineCap(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetLineDash(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    std::vector<double> lineDash = renderingContext2DModel_->GetLineDash();

    JSRef<JSObject> lineDashObj = JSRef<JSObject>::New();
    for (size_t i = 0; i < lineDash.size(); i++) {
        lineDashObj->SetProperty<double>(std::to_string(i).c_str(), lineDash[i]);
    }
    info.SetReturnValue(lineDashObj);
}

void JSCanvasRenderer::JsGetLineJoin(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetMiterLimit(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetLineWidth(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetTextAlign(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetTextBaseline(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetGlobalAlpha(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetGlobalCompositeOperation(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetLineDashOffset(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetShadowBlur(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetShadowColor(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetShadowOffsetX(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetShadowOffsetY(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetImageSmoothingEnabled(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsGetImageSmoothingQuality(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::ParseFillGradient(const JSCallbackInfo& info)
{
    auto* jSCanvasGradient = JSRef<JSObject>::Cast(info[0])->Unwrap<JSCanvasGradient>();
    if (!jSCanvasGradient) {
        return;
    }
    Gradient* gradient = jSCanvasGradient->GetGradient();
    if (!gradient) {
        return;
    }

    renderingContext2DModel_->SetFillGradient(*gradient);
}

void JSCanvasRenderer::ParseFillPattern(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto* jSCanvasPattern = JSRef<JSObject>::Cast(info[0])->Unwrap<JSCanvasPattern>();
    CHECK_NULL_VOID(jSCanvasPattern);
    int32_t id = jSCanvasPattern->GetId();
    renderingContext2DModel_->SetFillPattern(GetPatternPtr(id));
}

void JSCanvasRenderer::JsSetFillStyle(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }
    if (info[0]->IsString()) {
        Color color;
        if (!JSViewAbstract::CheckColor(info[0], color, "CanvasRenderer", "fillStyle")) {
            return;
        }

        renderingContext2DModel_->SetFillColor(color, true);
        return;
    }
    if (info[0]->IsNumber()) {
        auto color = Color(ColorAlphaAdapt(info[0]->ToNumber<uint32_t>()));
        renderingContext2DModel_->SetFillColor(color, false);
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> typeValue = obj->GetProperty("__type");
    std::string type = "";
    JSViewAbstract::ParseJsString(typeValue, type);
    if (type == "gradient") {
        ParseFillGradient(info);
    } else if (type == "pattern") {
        ParseFillPattern(info);
    }
}

void JSCanvasRenderer::ParseStorkeGradient(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto* jSCanvasGradient = JSRef<JSObject>::Cast(info[0])->Unwrap<JSCanvasGradient>();
    if (!jSCanvasGradient) {
        return;
    }
    Gradient* gradient = jSCanvasGradient->GetGradient();
    if (!gradient) {
        return;
    }
    renderingContext2DModel_->SetStrokeGradient(*gradient);
}

void JSCanvasRenderer::ParseStrokePattern(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto* jSCanvasPattern = JSRef<JSObject>::Cast(info[0])->Unwrap<JSCanvasPattern>();
    CHECK_NULL_VOID(jSCanvasPattern);
    int32_t id = jSCanvasPattern->GetId();
    renderingContext2DModel_->SetStrokePattern(GetPatternPtr(id));
}

void JSCanvasRenderer::JsSetStrokeStyle(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsString()) {
        Color color;
        if (!JSViewAbstract::CheckColor(info[0], color, "CanvasRenderer", "strokeStyle")) {
            return;
        }
        renderingContext2DModel_->SetStrokeColor(color, true);
        return;
    }
    if (info[0]->IsNumber()) {
        auto color = Color(ColorAlphaAdapt(info[0]->ToNumber<uint32_t>()));
        renderingContext2DModel_->SetStrokeColor(color, false);
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> typeValue = obj->GetProperty("__type");
    std::string type;
    JSViewAbstract::ParseJsString(typeValue, type);
    if (type == "gradient") {
        ParseStorkeGradient(info);
    } else if (type == "pattern") {
        ParseStrokePattern(info);
    }
}

RefPtr<CanvasPath2D> JSCanvasRenderer::JsMakePath2D(const JSCallbackInfo& info)
{
    if (info.Length() == 1) {
        if (info[0]->IsString()) {
            std::string capStr = "";
            JSViewAbstract::ParseJsString(info[0], capStr);
            return AceType::MakeRefPtr<CanvasPath2D>(capStr);
        }
    }
    // Example: ctx.createPath2D()
    return AceType::MakeRefPtr<CanvasPath2D>();
}

JSRenderImage* JSCanvasRenderer::UnwrapNapiImage(const JSRef<JSObject> jsObject)
{
    ContainerScope scope(instanceId_);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (runtime == nullptr) {
        return nullptr;
    }
    auto vm = runtime->GetEcmaVm();
    panda::Local<JsiValue> value = jsObject.Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    Global<JSValueRef> arkValue = valueWrapper;
    napi_value napiValue = reinterpret_cast<napi_value>(*arkValue.ToLocal(vm));
    panda::Local<panda::JSValueRef> nativeValue(reinterpret_cast<uintptr_t>(napiValue));
    auto nativeObject = nativeValue->ToObject(vm);

    napi_value isImageBitmap = nullptr;
    Local<panda::StringRef> keyType = panda::StringRef::NewFromUtf8(vm, "isImageBitmap");
    Local<panda::JSValueRef> valueType = nativeObject->Get(vm, keyType);
    isImageBitmap = reinterpret_cast<napi_value>(*valueType);
    if (isImageBitmap == nullptr) {
        return nullptr;
    }
    int32_t type = 0;
    panda::Local<panda::JSValueRef> localType(reinterpret_cast<uintptr_t>(isImageBitmap));
    type = localType->Int32Value(vm);
    if (!type) {
        return nullptr;
    }

    JSRenderImage* jsImage = nullptr;
    Local<panda::StringRef> keyObj = panda::StringRef::GetNapiWrapperString(vm);
    Local<panda::JSValueRef> valObj = nativeObject->Get(vm, keyObj);
    if (valObj->IsObject()) {
        Local<panda::ObjectRef> ext(valObj);
        auto ref = reinterpret_cast<NativeReference*>(ext->GetNativePointerField(0));
        jsImage = ref != nullptr ? reinterpret_cast<JSRenderImage*>(ref->GetData()) : nullptr;
    }
    return jsImage;
}

void JSCanvasRenderer::JsDrawImage(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    CanvasImage image;
    ImageInfo imageInfo;
    bool isImage = false;
    if (!info[0]->IsObject()) {
        return;
    }
    JSRenderImage* jsImage = UnwrapNapiImage(info[0]);
#if !defined(PREVIEW)
    RefPtr<PixelMap> pixelMap = nullptr;
    RefPtr<NG::SvgDomBase> svgDom = nullptr;
    if ((jsImage && jsImage->IsSvg())) {
        svgDom = jsImage->GetSvgDom();
        CHECK_NULL_VOID(svgDom);
        ImageFit imageFit = jsImage->GetImageFit();
        isImage = true;
        imageInfo.svgDom = svgDom;
        imageInfo.isSvg = jsImage->IsSvg();
        imageInfo.imageFit = imageFit;
    } else {
        if (jsImage) {
            isImage = true;
            pixelMap = jsImage->GetPixelMap();
        } else {
            pixelMap = CreatePixelMapFromNapiValue(info[0]);
        }
        CHECK_NULL_VOID(pixelMap);
    }
    imageInfo.isImage = false;
    imageInfo.pixelMap = pixelMap;
#else
    CHECK_NULL_VOID(jsImage);
    isImage = true;
    std::string imageValue = jsImage->GetSrc();
    image.src = imageValue;
    imageInfo.imgWidth = jsImage->GetWidth();
    imageInfo.imgHeight = jsImage->GetHeight();
    imageInfo.isImage = true;
#endif
    ExtractInfoToImage(image, info, isImage);
    image.instanceId = jsImage ? jsImage->GetInstanceId() : 0;
    imageInfo.image = image;

    renderingContext2DModel_->DrawImage(imageInfo);
}

void JSCanvasRenderer::ExtractInfoToImage(CanvasImage& image, const JSCallbackInfo& info, bool isImage)
{
    ContainerScope scope(instanceId_);
    switch (info.Length()) {
        case 3:
            image.flag = 0;
            JSViewAbstract::ParseJsDouble(info[1], image.dx);
            JSViewAbstract::ParseJsDouble(info[2], image.dy);
            image.dx = PipelineBase::Vp2PxWithCurrentDensity(image.dx);
            image.dy = PipelineBase::Vp2PxWithCurrentDensity(image.dy);
            break;
        // 5 parameters: drawImage(image, dx, dy, dWidth, dHeight)
        case 5:
            image.flag = 1;
            JSViewAbstract::ParseJsDouble(info[1], image.dx);
            JSViewAbstract::ParseJsDouble(info[2], image.dy);
            JSViewAbstract::ParseJsDouble(info[3], image.dWidth);
            JSViewAbstract::ParseJsDouble(info[4], image.dHeight);
            image.dx = PipelineBase::Vp2PxWithCurrentDensity(image.dx);
            image.dy = PipelineBase::Vp2PxWithCurrentDensity(image.dy);
            image.dWidth = PipelineBase::Vp2PxWithCurrentDensity(image.dWidth);
            image.dHeight = PipelineBase::Vp2PxWithCurrentDensity(image.dHeight);
            break;
        // 9 parameters: drawImage(image, sx, sy, sWidth, sHeight, dx, dy, dWidth, dHeight)
        case 9:
            image.flag = 2;
            JSViewAbstract::ParseJsDouble(info[1], image.sx);
            JSViewAbstract::ParseJsDouble(info[2], image.sy);
            JSViewAbstract::ParseJsDouble(info[3], image.sWidth);
            JSViewAbstract::ParseJsDouble(info[4], image.sHeight);
            JSViewAbstract::ParseJsDouble(info[5], image.dx);
            JSViewAbstract::ParseJsDouble(info[6], image.dy);
            JSViewAbstract::ParseJsDouble(info[7], image.dWidth);
            JSViewAbstract::ParseJsDouble(info[8], image.dHeight);
            if (isImage) {
                image.sx = PipelineBase::Vp2PxWithCurrentDensity(image.sx);
                image.sy = PipelineBase::Vp2PxWithCurrentDensity(image.sy);
                image.sWidth = PipelineBase::Vp2PxWithCurrentDensity(image.sWidth);
                image.sHeight = PipelineBase::Vp2PxWithCurrentDensity(image.sHeight);
            }
            image.dx = PipelineBase::Vp2PxWithCurrentDensity(image.dx);
            image.dy = PipelineBase::Vp2PxWithCurrentDensity(image.dy);
            image.dWidth = PipelineBase::Vp2PxWithCurrentDensity(image.dWidth);
            image.dHeight = PipelineBase::Vp2PxWithCurrentDensity(image.dHeight);
            break;
        default:
            break;
    }
}

void JSCanvasRenderer::JsCreatePattern(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() != 2) {
        return;
    }
    if (info[0]->IsObject()) {
        JSRenderImage* jsImage = UnwrapNapiImage(info[0]);
        if (jsImage == nullptr) {
            return;
        }
        std::string imageSrc = jsImage->GetSrc();
        double imgWidth = jsImage->GetWidth();
        double imgHeight = jsImage->GetHeight();
        std::string repeat;

        JSViewAbstract::ParseJsString(info[1], repeat);
        auto pattern = std::make_shared<Pattern>();
        pattern->SetImgSrc(imageSrc);
        pattern->SetImageWidth(imgWidth);
        pattern->SetImageHeight(imgHeight);
        pattern->SetRepetition(repeat);
#if !defined(PREVIEW)
        auto pixelMap = jsImage->GetPixelMap();
        pattern->SetPixelMap(pixelMap);
#endif
        pattern_[patternCount_] = pattern;

        JSRef<JSObject> obj = JSClass<JSCanvasPattern>::NewInstance();
        obj->SetProperty("__type", "pattern");
        auto canvasPattern = Referenced::Claim(obj->Unwrap<JSCanvasPattern>());
        canvasPattern->SetCanvasRenderer(AceType::WeakClaim(this));
        canvasPattern->SetId(patternCount_);
        patternCount_++;
        info.SetReturnValue(obj);
    }
}

void JSCanvasRenderer::JsCreateImageData(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    double fWidth = 0.0;
    double fHeight = 0.0;
    uint32_t finalWidth = 0;
    uint32_t finalHeight = 0;
    int32_t width = 0;
    int32_t height = 0;

    if (info.Length() == 2) {
        JSViewAbstract::ParseJsDouble(info[0], fWidth);
        JSViewAbstract::ParseJsDouble(info[1], fHeight);
        fWidth = PipelineBase::Vp2PxWithCurrentDensity(fWidth);
        fHeight = PipelineBase::Vp2PxWithCurrentDensity(fHeight);
    }
    if (info.Length() == 1 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> widthValue = obj->GetProperty("width");
        JSRef<JSVal> heightValue = obj->GetProperty("height");
        JSViewAbstract::ParseJsDouble(widthValue, fWidth);
        JSViewAbstract::ParseJsDouble(heightValue, fHeight);
    }

    width = fWidth + DIFF;
    height = fHeight + DIFF;
    finalWidth = static_cast<uint32_t>(std::abs(width));
    finalHeight = static_cast<uint32_t>(std::abs(height));
    JSRef<JSArrayBuffer> arrayBuffer = JSRef<JSArrayBuffer>::New(finalWidth * finalHeight * PIXEL_SIZE);
    // return the black image
    auto* buffer = static_cast<uint32_t*>(arrayBuffer->GetBuffer());
    for (uint32_t idx = 0; idx < finalWidth * finalHeight; ++idx) {
        buffer[idx] = 0xffffffff;
    }

    JSRef<JSUint8ClampedArray> colorArray =
        JSRef<JSUint8ClampedArray>::New(arrayBuffer->GetLocalHandle(), 0, arrayBuffer->ByteLength());

    auto retObj = JSRef<JSObject>::New();
    retObj->SetProperty("width", finalWidth);
    retObj->SetProperty("height", finalHeight);
    retObj->SetPropertyObject("data", colorArray);
    info.SetReturnValue(retObj);
}

void JSCanvasRenderer::JsPutImageData(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    int32_t width = 0;
    int32_t height = 0;
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> widthValue = obj->GetProperty("width");
    JSRef<JSVal> heightValue = obj->GetProperty("height");
    ParseJsInt(widthValue, width);
    ParseJsInt(heightValue, height);

    ImageData imageData;
    std::vector<uint8_t> array;
    ParseImageData(info, imageData, array);

    for (int32_t i = std::max(imageData.dirtyY, 0); i < imageData.dirtyY + imageData.dirtyHeight; ++i) {
        for (int32_t j = std::max(imageData.dirtyX, 0); j < imageData.dirtyX + imageData.dirtyWidth; ++j) {
            uint32_t idx = 4 * (j + width * i);
            if (array.size() > idx + 3) {
                imageData.data.emplace_back(
                    Color::FromARGB(array[idx + 3], array[idx], array[idx + 1], array[idx + 2]));
            }
        }
    }

    renderingContext2DModel_->PutImageData(imageData);
}

void JSCanvasRenderer::ParseImageData(const JSCallbackInfo& info, ImageData& imageData, std::vector<uint8_t>& array)
{
    ContainerScope scope(instanceId_);
    int32_t width = 0;
    int32_t height = 0;

    if (info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> widthValue = obj->GetProperty("width");
        JSRef<JSVal> heightValue = obj->GetProperty("height");
        JSRef<JSVal> dataValue = obj->GetProperty("data");
        ParseJsInt(widthValue, width);
        ParseJsInt(heightValue, height);
        if (dataValue->IsUint8ClampedArray()) {
            JSRef<JSUint8ClampedArray> colorArray = JSRef<JSUint8ClampedArray>::Cast(dataValue);
            auto arrayBuffer = colorArray->GetArrayBuffer();
            auto* buffer = static_cast<uint8_t*>(arrayBuffer->GetBuffer());
            for (auto idx = 0; idx < arrayBuffer->ByteLength(); ++idx) {
                array.emplace_back(buffer[idx]);
            }
        }
    }

    Dimension value;
    if (info[1]->IsString()) {
        std::string imageDataXStr = "";
        JSViewAbstract::ParseJsString(info[1], imageDataXStr);
        value = GetDimensionValue(imageDataXStr);
        imageData.x = value.Value();
    } else {
        ParseJsInt(info[1], imageData.x);
        imageData.x = PipelineBase::Vp2PxWithCurrentDensity(imageData.x);
    }
    if (info[2]->IsString()) {
        std::string imageDataYStr = "";
        JSViewAbstract::ParseJsString(info[2], imageDataYStr);
        value = GetDimensionValue(imageDataYStr);
        imageData.y = value.Value();
    } else {
        ParseJsInt(info[2], imageData.y);
        imageData.y = PipelineBase::Vp2PxWithCurrentDensity(imageData.y);
    }

    imageData.dirtyWidth = width;
    imageData.dirtyHeight = height;

    if (info.Length() == 7) {
        ParseImageDataAsStr(info, imageData);
    }

    imageData.dirtyWidth = imageData.dirtyX < 0 ? std::min(imageData.dirtyX + imageData.dirtyWidth, width)
                                                : std::min(width - imageData.dirtyX, imageData.dirtyWidth);
    imageData.dirtyHeight = imageData.dirtyY < 0 ? std::min(imageData.dirtyY + imageData.dirtyHeight, height)
                                                 : std::min(height - imageData.dirtyY, imageData.dirtyHeight);
}

void JSCanvasRenderer::ParseImageDataAsStr(const JSCallbackInfo& info, ImageData& imageData)
{
    ContainerScope scope(instanceId_);
    Dimension value;
    if (info[3]->IsString()) {
        std::string imageDataDirtyXStr = "";
        JSViewAbstract::ParseJsString(info[3], imageDataDirtyXStr);
        value = GetDimensionValue(imageDataDirtyXStr);
        imageData.dirtyX = value.Value();
    } else {
        ParseJsInt(info[3], imageData.dirtyX);
        imageData.dirtyX = PipelineBase::Vp2PxWithCurrentDensity(imageData.dirtyX);
    }
    if (info[4]->IsString()) {
        std::string imageDataDirtyYStr = "";
        JSViewAbstract::ParseJsString(info[4], imageDataDirtyYStr);
        value = GetDimensionValue(imageDataDirtyYStr);
        imageData.dirtyY = value.Value();
    } else {
        ParseJsInt(info[4], imageData.dirtyY);
        imageData.dirtyY = PipelineBase::Vp2PxWithCurrentDensity(imageData.dirtyY);
    }
    if (info[5]->IsString()) {
        std::string imageDataDirtWidth = "";
        JSViewAbstract::ParseJsString(info[5], imageDataDirtWidth);
        value = GetDimensionValue(imageDataDirtWidth);
        imageData.dirtyWidth = value.Value();
    } else {
        ParseJsInt(info[5], imageData.dirtyWidth);
        imageData.dirtyWidth = PipelineBase::Vp2PxWithCurrentDensity(imageData.dirtyWidth);
    }
    if (info[6]->IsString()) {
        std::string imageDataDirtyHeight = "";
        JSViewAbstract::ParseJsString(info[6], imageDataDirtyHeight);
        value = GetDimensionValue(imageDataDirtyHeight);
        imageData.dirtyHeight = value.Value();
    } else {
        ParseJsInt(info[6], imageData.dirtyHeight);
        imageData.dirtyHeight = PipelineBase::Vp2PxWithCurrentDensity(imageData.dirtyHeight);
    }
}

void JSCanvasRenderer::JsCloseImageBitmap(const std::string& src)
{
    ContainerScope scope(instanceId_);
    renderingContext2DModel_->CloseImageBitmap(src);
}

void JSCanvasRenderer::JsGetImageData(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    double fLeft = 0.0;
    double fTop = 0.0;
    double fWidth = 0.0;
    double fHeight = 0.0;
    uint32_t finalWidth = 0;
    uint32_t finalHeight = 0;
    int32_t left = 0;
    int32_t top = 0;
    int32_t width = 0;
    int32_t height = 0;

    JSViewAbstract::ParseJsDouble(info[0], fLeft);
    JSViewAbstract::ParseJsDouble(info[1], fTop);
    JSViewAbstract::ParseJsDouble(info[2], fWidth);
    JSViewAbstract::ParseJsDouble(info[3], fHeight);

    fLeft = PipelineBase::Vp2PxWithCurrentDensity(fLeft);
    fTop = PipelineBase::Vp2PxWithCurrentDensity(fTop);
    fWidth = PipelineBase::Vp2PxWithCurrentDensity(fWidth);
    fHeight = PipelineBase::Vp2PxWithCurrentDensity(fHeight);

    left = fLeft;
    top = fTop;
    width = fWidth + DIFF;
    height = fHeight + DIFF;

    finalWidth = static_cast<uint32_t>(std::abs(width));
    finalHeight = static_cast<uint32_t>(std::abs(height));
    int32_t length = finalHeight * finalWidth * 4;
    JSRef<JSArrayBuffer> arrayBuffer = JSRef<JSArrayBuffer>::New(length);
    auto* buffer = static_cast<uint8_t*>(arrayBuffer->GetBuffer());

    ImageSize imageSize;
    imageSize.left = left;
    imageSize.top = top;
    imageSize.width = width;
    imageSize.height = height;
    renderingContext2DModel_->GetImageDataModel(imageSize, buffer);

    JSRef<JSUint8ClampedArray> colorArray =
        JSRef<JSUint8ClampedArray>::New(arrayBuffer->GetLocalHandle(), 0, arrayBuffer->ByteLength());

    auto retObj = JSRef<JSObject>::New();
    retObj->SetProperty("width", finalWidth);
    retObj->SetProperty("height", finalHeight);
    retObj->SetPropertyObject("data", colorArray);
    info.SetReturnValue(retObj);
}

void JSCanvasRenderer::JsGetPixelMap(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
#ifdef PIXEL_MAP_SUPPORTED
    // 0 Get input param
    double fLeft = 0.0;
    double fTop = 0.0;
    double fWidth = 0.0;
    double fHeight = 0.0;
    int32_t left = 0;
    int32_t top = 0;
    int32_t width = 0;
    int32_t height = 0;

    JSViewAbstract::ParseJsDouble(info[0], fLeft);
    JSViewAbstract::ParseJsDouble(info[1], fTop);
    JSViewAbstract::ParseJsDouble(info[2], fWidth);
    JSViewAbstract::ParseJsDouble(info[3], fHeight);

    fLeft = PipelineBase::Vp2PxWithCurrentDensity(fLeft);
    fTop = PipelineBase::Vp2PxWithCurrentDensity(fTop);
    fWidth = PipelineBase::Vp2PxWithCurrentDensity(fWidth);
    fHeight = PipelineBase::Vp2PxWithCurrentDensity(fHeight);

    left = fLeft;
    top = fTop;
    width = fWidth + DIFF;
    height = fHeight + DIFF;

    ImageSize imageSize;
    imageSize.left = left;
    imageSize.top = top;
    imageSize.width = width;
    imageSize.height = height;
    auto pixelmap = renderingContext2DModel_->GetPixelMap(imageSize);
    CHECK_NULL_VOID(pixelmap);

    // 3 pixelmap to NapiValue
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    CHECK_NULL_VOID(runtime);
    NativeEngine* nativeEngine = runtime->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    auto pixelmapSharedPtr = pixelmap->GetPixelMapSharedPtr();
    napi_value napiValue = OHOS::Media::PixelMapNapi::CreatePixelMap(env, pixelmapSharedPtr);

    // 4 NapiValue to JsValue
#ifdef USE_ARK_ENGINE
    auto jsValue = JsConverter::ConvertNapiValueToJsVal(napiValue);
    info.SetReturnValue(jsValue);
#else
    napi_value temp = nullptr;
    napi_create_int32(env, 0, &temp);
    napi_set_named_property(env, napiValue, "index", temp);
#endif
#else
    TAG_LOGI(
        AceLogTag::ACE_CANVAS, "[Engine Log] The function 'getPixelMap' is not supported on the current platform.");
#endif
}

void JSCanvasRenderer::JsSetPixelMap(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() != 1) {
        return;
    }
    CanvasImage image;
    RefPtr<PixelMap> pixelMap = nullptr;
    if (info[0]->IsObject()) {
#if !defined(PREVIEW)
        pixelMap = CreatePixelMapFromNapiValue(info[0]);
#endif
        if (!pixelMap) {
            return;
        }

        ImageInfo imageInfo;
        imageInfo.image = image;
        imageInfo.pixelMap = pixelMap;

        renderingContext2DModel_->DrawPixelMap(imageInfo);
    }
}

void JSCanvasRenderer::JsDrawBitmapMesh(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    RefPtr<AceType> OffscreenPattern;

    if (info.Length() != 4) {
        return;
    }

    if (info[0]->IsObject()) {
        uint32_t id = 0;
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> jsId = obj->GetProperty("__id");
        JSViewAbstract::ParseJsInteger(jsId, id);
        OffscreenPattern = JSOffscreenRenderingContext::GetOffscreenPattern(id);
    } else {
        return;
    }

    std::vector<double> mesh;
    double column;
    double row;
    if (!ParseJsDoubleArray(info[1], mesh)) {
        return;
    }
    if (!JSViewAbstract::ParseJsDouble(info[2], column)) {
        return;
    }
    if (!JSViewAbstract::ParseJsDouble(info[3], row)) {
        return;
    }

    BitmapMeshInfo bitmapMeshInfo;
    bitmapMeshInfo.pool = canvasPattern_;
    bitmapMeshInfo.offscreenPattern = OffscreenPattern;
    bitmapMeshInfo.mesh = mesh;
    bitmapMeshInfo.column = column;
    bitmapMeshInfo.row = row;
    renderingContext2DModel_->DrawBitmapMesh(bitmapMeshInfo);
}

void JSCanvasRenderer::JsGetFilter(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsSetFilter(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (!info[0]->IsString() || info[0]->IsUndefined() || info[0]->IsNull()) {
        return;
    }
    std::string filterStr = "none";
    JSViewAbstract::ParseJsString(info[0], filterStr);
    if (filterStr == "") {
        return;
    }

    renderingContext2DModel_->SetFilterParam(filterStr);
}

void JSCanvasRenderer::JsGetDirection(const JSCallbackInfo& info)
{
    return;
}

void JSCanvasRenderer::JsSetDirection(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (!info[0]->IsString()) {
        return;
    }
    std::string directionStr;
    JSViewAbstract::ParseJsString(info[0], directionStr);
    auto direction = ConvertStrToTextDirection(directionStr);

    renderingContext2DModel_->SetTextDirection(direction);
}

void JSCanvasRenderer::JsGetJsonData(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    std::string path = "";
    std::string jsonData = "";

    if (info[0]->IsString()) {
        JSViewAbstract::ParseJsString(info[0], path);
        jsonData = renderingContext2DModel_->GetJsonData(path);
        auto returnValue = JSVal(ToJSValue(jsonData));
        auto returnPtr = JSRef<JSVal>::Make(returnValue);
        info.SetReturnValue(returnPtr);
    }
}

void JSCanvasRenderer::JsToDataUrl(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    std::string dataUrl = "";
    std::string result = "";
    double quality = DEFAULT_QUALITY;
    if (info[0]->IsString()) {
        JSViewAbstract::ParseJsString(info[0], dataUrl);
    }
    if (info.Length() > 1 && info[1]->IsNumber()) {
        JSViewAbstract::ParseJsDouble(info[1], quality);
    }

    result = renderingContext2DModel_->ToDataURL(dataUrl, quality);

    auto returnValue = JSVal(ToJSValue(result));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSCanvasRenderer::JsSetLineCap(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info[0]->IsString()) {
        std::string capStr = "";
        JSViewAbstract::ParseJsString(info[0], capStr);
        static const LinearMapNode<LineCapStyle> lineCapTable[] = {
            { "butt", LineCapStyle::BUTT },
            { "round", LineCapStyle::ROUND },
            { "square", LineCapStyle::SQUARE },
        };
        auto lineCap = ConvertStrToEnum(capStr.c_str(), lineCapTable, ArraySize(lineCapTable), LineCapStyle::BUTT);
        renderingContext2DModel_->SetLineCap(lineCap);
    }
}

void JSCanvasRenderer::JsSetLineJoin(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info[0]->IsString()) {
        std::string joinStr = "";
        JSViewAbstract::ParseJsString(info[0], joinStr);
        static const LinearMapNode<LineJoinStyle> lineJoinTable[3] = {
            { "bevel", LineJoinStyle::BEVEL },
            { "miter", LineJoinStyle::MITER },
            { "round", LineJoinStyle::ROUND },
        };
        auto lineJoin =
            ConvertStrToEnum(joinStr.c_str(), lineJoinTable, ArraySize(lineJoinTable), LineJoinStyle::MITER);
        renderingContext2DModel_->SetLineJoin(lineJoin);
    }
}

void JSCanvasRenderer::JsSetMiterLimit(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info[0]->IsNumber()) {
        double limit = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], limit);
        renderingContext2DModel_->SetMiterLimit(limit);
    }
}

void JSCanvasRenderer::JsSetLineWidth(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info[0]->IsNumber()) {
        double lineWidth = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], lineWidth);
        lineWidth = PipelineBase::Vp2PxWithCurrentDensity(lineWidth);
        renderingContext2DModel_->SetLineWidth(lineWidth);
    }
}

void JSCanvasRenderer::JsSetGlobalAlpha(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info[0]->IsNumber()) {
        double alpha = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], alpha);
        renderingContext2DModel_->SetGlobalAlpha(alpha);
    }
}

void JSCanvasRenderer::JsSetGlobalCompositeOperation(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info[0]->IsString()) {
        std::string compositeStr = "";
        JSViewAbstract::ParseJsString(info[0], compositeStr);

        static const LinearMapNode<CompositeOperation> compositeOperationTable[] = {
            { "copy", CompositeOperation::COPY },
            { "destination-atop", CompositeOperation::DESTINATION_ATOP },
            { "destination-in", CompositeOperation::DESTINATION_IN },
            { "destination-out", CompositeOperation::DESTINATION_OUT },
            { "destination-over", CompositeOperation::DESTINATION_OVER },
            { "lighter", CompositeOperation::LIGHTER },
            { "source-atop", CompositeOperation::SOURCE_ATOP },

            { "source-in", CompositeOperation::SOURCE_IN },
            { "source-out", CompositeOperation::SOURCE_OUT },
            { "source-over", CompositeOperation::SOURCE_OVER },
            { "xor", CompositeOperation::XOR },
        };
        auto type = ConvertStrToEnum(compositeStr.c_str(), compositeOperationTable, ArraySize(compositeOperationTable),
            CompositeOperation::SOURCE_OVER);
        renderingContext2DModel_->SetCompositeType(type);
    }
}

void JSCanvasRenderer::JsSetLineDashOffset(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info[0]->IsNumber()) {
        double lineDashOffset = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], lineDashOffset);
        lineDashOffset = PipelineBase::Vp2PxWithCurrentDensity(lineDashOffset);
        renderingContext2DModel_->SetLineDashOffset(lineDashOffset);
    }
}

void JSCanvasRenderer::JsSetShadowBlur(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info[0]->IsNumber()) {
        double blur = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], blur);
        renderingContext2DModel_->SetShadowBlur(blur);
    }
}

void JSCanvasRenderer::JsSetShadowColor(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info[0]->IsString()) {
        std::string colorStr = "";
        JSViewAbstract::ParseJsString(info[0], colorStr);
        auto color = Color::FromString(colorStr);
        renderingContext2DModel_->SetShadowColor(color);
    }
}

void JSCanvasRenderer::JsSetShadowOffsetX(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info[0]->IsNumber()) {
        double offsetX = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], offsetX);
        offsetX = PipelineBase::Vp2PxWithCurrentDensity(offsetX);
        renderingContext2DModel_->SetShadowOffsetX(offsetX);
    }
}

void JSCanvasRenderer::JsSetShadowOffsetY(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info[0]->IsNumber()) {
        double offsetY = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], offsetY);
        offsetY = PipelineBase::Vp2PxWithCurrentDensity(offsetY);
        renderingContext2DModel_->SetShadowOffsetY(offsetY);
    }
}

void JSCanvasRenderer::JsSetImageSmoothingEnabled(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    bool enabled = false;
    if (JSViewAbstract::ParseJsBool(info[0], enabled)) {
        renderingContext2DModel_->SetSmoothingEnabled(enabled);
    }
}

void JSCanvasRenderer::JsSetImageSmoothingQuality(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    std::string quality = "";
    if (JSViewAbstract::ParseJsString(info[0], quality)) {
        if (QUALITY_TYPE.find(quality) == QUALITY_TYPE.end()) {
            return;
        }
        renderingContext2DModel_->SetSmoothingQuality(quality);
    }
}

void JSCanvasRenderer::JsMoveTo(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber()) {
        double x = 0.0;
        double y = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], x);
        JSViewAbstract::ParseJsDouble(info[1], y);
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        renderingContext2DModel_->MoveTo(x, y);
    }
}

void JSCanvasRenderer::JsLineTo(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber()) {
        double x = 0.0;
        double y = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], x);
        JSViewAbstract::ParseJsDouble(info[1], y);
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        renderingContext2DModel_->LineTo(x, y);
    }
}

void JSCanvasRenderer::JsBezierCurveTo(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber() &&
        info[4]->IsNumber() && info[5]->IsNumber()) {
        BezierCurveParam param;
        JSViewAbstract::ParseJsDouble(info[0], param.cp1x);
        JSViewAbstract::ParseJsDouble(info[1], param.cp1y);
        JSViewAbstract::ParseJsDouble(info[2], param.cp2x);
        JSViewAbstract::ParseJsDouble(info[3], param.cp2y);
        JSViewAbstract::ParseJsDouble(info[4], param.x);
        JSViewAbstract::ParseJsDouble(info[5], param.y);
        param.cp1x = PipelineBase::Vp2PxWithCurrentDensity(param.cp1x);
        param.cp1y = PipelineBase::Vp2PxWithCurrentDensity(param.cp1y);
        param.cp2x = PipelineBase::Vp2PxWithCurrentDensity(param.cp2x);
        param.cp2y = PipelineBase::Vp2PxWithCurrentDensity(param.cp2y);
        param.x = PipelineBase::Vp2PxWithCurrentDensity(param.x);
        param.y = PipelineBase::Vp2PxWithCurrentDensity(param.y);
        renderingContext2DModel_->BezierCurveTo(param);
    }
}

void JSCanvasRenderer::JsQuadraticCurveTo(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber()) {
        QuadraticCurveParam param;
        JSViewAbstract::ParseJsDouble(info[0], param.cpx);
        JSViewAbstract::ParseJsDouble(info[1], param.cpy);
        JSViewAbstract::ParseJsDouble(info[2], param.x);
        JSViewAbstract::ParseJsDouble(info[3], param.y);
        param.cpx = PipelineBase::Vp2PxWithCurrentDensity(param.cpx);
        param.cpy = PipelineBase::Vp2PxWithCurrentDensity(param.cpy);
        param.x = PipelineBase::Vp2PxWithCurrentDensity(param.x);
        param.y = PipelineBase::Vp2PxWithCurrentDensity(param.y);
        renderingContext2DModel_->QuadraticCurveTo(param);
    }
}

void JSCanvasRenderer::JsArcTo(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber() &&
        info[4]->IsNumber()) {
        ArcToParam param;
        JSViewAbstract::ParseJsDouble(info[0], param.x1);
        JSViewAbstract::ParseJsDouble(info[1], param.y1);
        JSViewAbstract::ParseJsDouble(info[2], param.x2);
        JSViewAbstract::ParseJsDouble(info[3], param.y2);
        JSViewAbstract::ParseJsDouble(info[4], param.radius);
        param.x1 = PipelineBase::Vp2PxWithCurrentDensity(param.x1);
        param.y1 = PipelineBase::Vp2PxWithCurrentDensity(param.y1);
        param.x2 = PipelineBase::Vp2PxWithCurrentDensity(param.x2);
        param.y2 = PipelineBase::Vp2PxWithCurrentDensity(param.y2);
        param.radius = PipelineBase::Vp2PxWithCurrentDensity(param.radius);
        renderingContext2DModel_->ArcTo(param);
    }
}

void JSCanvasRenderer::JsArc(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber() &&
        info[4]->IsNumber()) {
        ArcParam param;
        JSViewAbstract::ParseJsDouble(info[0], param.x);
        JSViewAbstract::ParseJsDouble(info[1], param.y);
        JSViewAbstract::ParseJsDouble(info[2], param.radius);
        JSViewAbstract::ParseJsDouble(info[3], param.startAngle);
        JSViewAbstract::ParseJsDouble(info[4], param.endAngle);
        param.x = PipelineBase::Vp2PxWithCurrentDensity(param.x);
        param.y = PipelineBase::Vp2PxWithCurrentDensity(param.y);
        param.radius = PipelineBase::Vp2PxWithCurrentDensity(param.radius);

        if (info.Length() == 6) {
            JSViewAbstract::ParseJsBool(info[5], param.anticlockwise);
        }
        renderingContext2DModel_->Arc(param);
    }
}

void JSCanvasRenderer::JsEllipse(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber() &&
        info[4]->IsNumber() && info[5]->IsNumber() && info[6]->IsNumber()) {
        EllipseParam param;
        JSViewAbstract::ParseJsDouble(info[0], param.x);
        JSViewAbstract::ParseJsDouble(info[1], param.y);
        JSViewAbstract::ParseJsDouble(info[2], param.radiusX);
        JSViewAbstract::ParseJsDouble(info[3], param.radiusY);
        JSViewAbstract::ParseJsDouble(info[4], param.rotation);
        JSViewAbstract::ParseJsDouble(info[5], param.startAngle);
        JSViewAbstract::ParseJsDouble(info[6], param.endAngle);
        param.x = PipelineBase::Vp2PxWithCurrentDensity(param.x);
        param.y = PipelineBase::Vp2PxWithCurrentDensity(param.y);
        param.radiusX = PipelineBase::Vp2PxWithCurrentDensity(param.radiusX);
        param.radiusY = PipelineBase::Vp2PxWithCurrentDensity(param.radiusY);

        if (info.Length() == 8) {
            JSViewAbstract::ParseJsBool(info[7], param.anticlockwise);
        }
        renderingContext2DModel_->Ellipse(param);
    }
}

void JSCanvasRenderer::JsFill(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    std::string ruleStr = "";
    if (info.Length() == 1 && info[0]->IsString()) {
        // fill(rule) uses fillRule specified by the application developers
        JSViewAbstract::ParseJsString(info[0], ruleStr);
    } else if (info.Length() == 2) {
        // fill(path, rule) uses fillRule specified by the application developers
        JSViewAbstract::ParseJsString(info[1], ruleStr);
    }
    auto fillRule = CanvasFillRule::NONZERO;
    if (ruleStr == "nonzero") {
        fillRule = CanvasFillRule::NONZERO;
    } else if (ruleStr == "evenodd") {
        fillRule = CanvasFillRule::EVENODD;
    }
    if (info.Length() == 0 || (info.Length() == 1 && info[0]->IsString())) {
        renderingContext2DModel_->SetFillRuleForPath(fillRule);
    } else if (info.Length() == 2 || (info.Length() == 1 && info[0]->IsObject())) {
        JSPath2D* jsCanvasPath = JSRef<JSObject>::Cast(info[0])->Unwrap<JSPath2D>();
        if (jsCanvasPath == nullptr) {
            return;
        }
        auto path = jsCanvasPath->GetCanvasPath2d();

        renderingContext2DModel_->SetFillRuleForPath2D(fillRule, path);
    }
}

void JSCanvasRenderer::JsStroke(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    // stroke always uses non-zero fillRule
    auto fillRule = CanvasFillRule::NONZERO;
    if (info.Length() == 1) {
        JSPath2D* jsCanvasPath = JSRef<JSObject>::Cast(info[0])->Unwrap<JSPath2D>();
        if (jsCanvasPath == nullptr) {
            return;
        }
        auto path = jsCanvasPath->GetCanvasPath2d();
        renderingContext2DModel_->SetStrokeRuleForPath2D(fillRule, path);
        return;
    }

    renderingContext2DModel_->SetStrokeRuleForPath(fillRule);
}

void JSCanvasRenderer::JsClip(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    std::string ruleStr = "";
    if (info.Length() == 1 && info[0]->IsString()) {
        // clip(rule) uses fillRule specified by the application developers
        JSViewAbstract::ParseJsString(info[0], ruleStr);
    } else if (info.Length() == 2) {
        // clip(path, rule) uses fillRule specified by the application developers
        JSViewAbstract::ParseJsString(info[1], ruleStr);
    }
    auto fillRule = CanvasFillRule::NONZERO;
    if (ruleStr == "nonzero") {
        fillRule = CanvasFillRule::NONZERO;
    } else if (ruleStr == "evenodd") {
        fillRule = CanvasFillRule::EVENODD;
    }
    if (info.Length() == 0 || (info.Length() == 1 && info[0]->IsString())) {
        renderingContext2DModel_->SetClipRuleForPath(fillRule);
    } else if (info.Length() == 2 || (info.Length() == 1 && info[0]->IsObject())) {
        JSPath2D* jsCanvasPath = JSRef<JSObject>::Cast(info[0])->Unwrap<JSPath2D>();
        if (jsCanvasPath == nullptr) {
            return;
        }
        auto path = jsCanvasPath->GetCanvasPath2d();
        renderingContext2DModel_->SetClipRuleForPath2D(fillRule, path);
    }
}

void JSCanvasRenderer::JsRect(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    Rect rect = GetJsRectParam(info);
    renderingContext2DModel_->AddRect(rect);
}

void JSCanvasRenderer::JsBeginPath(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() != 0) {
        return;
    }
    renderingContext2DModel_->BeginPath();
}

void JSCanvasRenderer::JsClosePath(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() != 0) {
        return;
    }
    renderingContext2DModel_->ClosePath();
}

void JSCanvasRenderer::JsRestore(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() != 0) {
        return;
    }
    renderingContext2DModel_->Restore();
}

void JSCanvasRenderer::JsSave(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() != 0) {
        return;
    }
    renderingContext2DModel_->CanvasRendererSave();
}

void JSCanvasRenderer::JsRotate(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() != 1) {
        return;
    }
    double angle = 0.0;
    JSViewAbstract::ParseJsDouble(info[0], angle);
    renderingContext2DModel_->CanvasRendererRotate(angle);
}

void JSCanvasRenderer::JsScale(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber()) {
        double x = 0.0;
        double y = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], x);
        JSViewAbstract::ParseJsDouble(info[1], y);
        renderingContext2DModel_->CanvasRendererScale(x, y);
    }
}

void JSCanvasRenderer::JsGetTransform(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    JSRef<JSObject> obj = JSClass<JSMatrix2d>::NewInstance();
    obj->SetProperty("__type", "Matrix2D");
    if (Container::IsCurrentUseNewPipeline()) {
        TransformParam param = renderingContext2DModel_->GetTransform();
        auto matrix = Referenced::Claim(obj->Unwrap<JSMatrix2d>());
        CHECK_NULL_VOID(matrix);
        matrix->SetTransform(param);
    }
    info.SetReturnValue(obj);
}

void JSCanvasRenderer::JsSetTransform(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() == 6) {
        if (!(info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber() &&
                info[4]->IsNumber() && info[5]->IsNumber())) {
            return;
        }
        TransformParam param;
        JSViewAbstract::ParseJsDouble(info[0], param.scaleX);
        JSViewAbstract::ParseJsDouble(info[1], param.skewY);
        JSViewAbstract::ParseJsDouble(info[2], param.skewX);
        JSViewAbstract::ParseJsDouble(info[3], param.scaleY);
        JSViewAbstract::ParseJsDouble(info[4], param.translateX);
        JSViewAbstract::ParseJsDouble(info[5], param.translateY);
        param.translateX = PipelineBase::Vp2PxWithCurrentDensity(param.translateX);
        param.translateY = PipelineBase::Vp2PxWithCurrentDensity(param.translateY);

        renderingContext2DModel_->SetTransform(param, true);
        return;
    } else if (info.Length() == 1) {
        if (!info[0]->IsObject()) {
            return;
        }

        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            auto* jsMatrix2d = JSRef<JSObject>::Cast(info[0])->Unwrap<JSMatrix2d>();
            CHECK_NULL_VOID(jsMatrix2d);
            TransformParam param = jsMatrix2d->GetTransform();
            renderingContext2DModel_->SetTransform(param, false);
            return;
        }

        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        TransformParam param = JSMatrix2d::GetTransformInfo(jsObj);
        renderingContext2DModel_->SetTransform(param, false);
    }
}

void JSCanvasRenderer::JsResetTransform(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() != 0) {
        return;
    }
    renderingContext2DModel_->ResetTransform();
}

void JSCanvasRenderer::JsTransform(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 6) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber() &&
        info[4]->IsNumber() && info[5]->IsNumber()) {
        TransformParam param;
        JSViewAbstract::ParseJsDouble(info[0], param.scaleX);
        JSViewAbstract::ParseJsDouble(info[1], param.skewX);
        JSViewAbstract::ParseJsDouble(info[2], param.skewY);
        JSViewAbstract::ParseJsDouble(info[3], param.scaleY);
        JSViewAbstract::ParseJsDouble(info[4], param.translateX);
        JSViewAbstract::ParseJsDouble(info[5], param.translateY);
        param.translateX = PipelineBase::Vp2PxWithCurrentDensity(param.translateX);
        param.translateY = PipelineBase::Vp2PxWithCurrentDensity(param.translateY);
        renderingContext2DModel_->Transform(param);
    }
}

void JSCanvasRenderer::JsTranslate(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 2) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber()) {
        double x = 0.0;
        double y = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], x);
        JSViewAbstract::ParseJsDouble(info[1], y);
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        renderingContext2DModel_->Translate(x, y);
    }
}

void JSCanvasRenderer::JsSetLineDash(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    std::vector<double> lineDash;
    ParseJsDoubleArray(info[0], lineDash);
    if (lineDash.size() % 2 != 0) {
        lineDash.insert(lineDash.end(), lineDash.begin(), lineDash.end());
    }
    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        for (auto i = 0U; i < lineDash.size(); i++) {
            lineDash[i] = PipelineBase::Vp2PxWithCurrentDensity(lineDash[i]);
        }
    }
    renderingContext2DModel_->SetLineDash(lineDash);
}

Pattern JSCanvasRenderer::GetPattern(unsigned int id)
{
    if (id < 0 || id >= pattern_.size()) {
        return Pattern();
    }
    return *(pattern_[id].get());
}

std::weak_ptr<Ace::Pattern> JSCanvasRenderer::GetPatternNG(int32_t id)
{
    if (id < 0) {
        return std::shared_ptr<Pattern>();
    }
    return pattern_[id];
}

std::shared_ptr<Pattern> JSCanvasRenderer::GetPatternPtr(int32_t id)
{
    if (id < 0 || id >= static_cast<int32_t>(pattern_.size())) {
        return std::shared_ptr<Pattern>();
    }
    return pattern_[id];
}

void JSCanvasRenderer::SetTransform(unsigned int id, const TransformParam& transform)
{
    if (id >= 0 && id <= patternCount_) {
        pattern_[id]->SetScaleX(transform.scaleX);
        pattern_[id]->SetScaleY(transform.scaleY);
        pattern_[id]->SetSkewX(transform.skewX);
        pattern_[id]->SetSkewY(transform.skewY);
        pattern_[id]->SetTranslateX(transform.translateX);
        pattern_[id]->SetTranslateY(transform.translateY);
    }
}

void JSCanvasRenderer::JsSetTextAlign(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }
    std::string value = "";
    if (info[0]->IsString()) {
        JSViewAbstract::ParseJsString(info[0], value);
        auto align = ConvertStrToTextAlign(value);
        paintState_.SetTextAlign(align);
        renderingContext2DModel_->SetTextAlign(align);
    }
}

void JSCanvasRenderer::JsSetTextBaseline(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 1) {
        return;
    }

    std::string textBaseline;
    if (info[0]->IsString()) {
        JSViewAbstract::ParseJsString(info[0], textBaseline);
        auto baseline =
            ConvertStrToEnum(textBaseline.c_str(), BASELINE_TABLE, ArraySize(BASELINE_TABLE), TextBaseline::ALPHABETIC);
        style_.SetTextBaseline(baseline);
        renderingContext2DModel_->SetTextBaseline(baseline);
    }
}

void JSCanvasRenderer::JsMeasureText(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    std::string text = "";
    paintState_.SetTextStyle(style_);
    double width = 0.0;
    double height = 0.0;
    TextMetrics textMetrics;
    if (info[0]->IsString()) {
        JSViewAbstract::ParseJsString(info[0], text);
        width = renderingContext2DModel_->GetMeasureTextWidth(paintState_, text);
        height = renderingContext2DModel_->GetMeasureTextHeight(paintState_, text);
        textMetrics = renderingContext2DModel_->GetMeasureTextMetrics(paintState_, text);

        auto retObj = JSRef<JSObject>::New();
        retObj->SetProperty("width", PipelineBase::Px2VpWithCurrentDensity(width));
        retObj->SetProperty("height", PipelineBase::Px2VpWithCurrentDensity(height));
        retObj->SetProperty(
            "actualBoundingBoxLeft", PipelineBase::Px2VpWithCurrentDensity(textMetrics.actualBoundingBoxLeft));
        retObj->SetProperty(
            "actualBoundingBoxRight", PipelineBase::Px2VpWithCurrentDensity(textMetrics.actualBoundingBoxRight));
        retObj->SetProperty(
            "actualBoundingBoxAscent", PipelineBase::Px2VpWithCurrentDensity(textMetrics.actualBoundingBoxAscent));
        retObj->SetProperty(
            "actualBoundingBoxDescent", PipelineBase::Px2VpWithCurrentDensity(textMetrics.actualBoundingBoxDescent));
        retObj->SetProperty("hangingBaseline", PipelineBase::Px2VpWithCurrentDensity(textMetrics.hangingBaseline));
        retObj->SetProperty(
            "alphabeticBaseline", PipelineBase::Px2VpWithCurrentDensity(textMetrics.alphabeticBaseline));
        retObj->SetProperty(
            "ideographicBaseline", PipelineBase::Px2VpWithCurrentDensity(textMetrics.ideographicBaseline));
        retObj->SetProperty("emHeightAscent", PipelineBase::Px2VpWithCurrentDensity(textMetrics.emHeightAscent));
        retObj->SetProperty("emHeightDescent", PipelineBase::Px2VpWithCurrentDensity(textMetrics.emHeightDescent));
        retObj->SetProperty(
            "fontBoundingBoxAscent", PipelineBase::Px2VpWithCurrentDensity(textMetrics.fontBoundingBoxAscent));
        retObj->SetProperty(
            "fontBoundingBoxDescent", PipelineBase::Px2VpWithCurrentDensity(textMetrics.fontBoundingBoxDescent));
        info.SetReturnValue(retObj);
    }
}

void JSCanvasRenderer::JsFillRect(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 4) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber()) {
        double x = 0.0;
        double y = 0.0;
        double width = 0.0;
        double height = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], x);
        JSViewAbstract::ParseJsDouble(info[1], y);
        JSViewAbstract::ParseJsDouble(info[2], width);
        JSViewAbstract::ParseJsDouble(info[3], height);
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        width = PipelineBase::Vp2PxWithCurrentDensity(width);
        height = PipelineBase::Vp2PxWithCurrentDensity(height);

        Rect rect = Rect(x, y, width, height);
        renderingContext2DModel_->FillRect(rect);
    }
}

void JSCanvasRenderer::JsStrokeRect(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 4) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber()) {
        double x = 0.0;
        double y = 0.0;
        double width = 0.0;
        double height = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], x);
        JSViewAbstract::ParseJsDouble(info[1], y);
        JSViewAbstract::ParseJsDouble(info[2], width);
        JSViewAbstract::ParseJsDouble(info[3], height);
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        width = PipelineBase::Vp2PxWithCurrentDensity(width);
        height = PipelineBase::Vp2PxWithCurrentDensity(height);

        Rect rect = Rect(x, y, width, height);
        renderingContext2DModel_->StrokeRect(rect);
    }
}

void JSCanvasRenderer::JsClearRect(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (info.Length() < 4) {
        return;
    }

    if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber()) {
        double x = 0.0;
        double y = 0.0;
        double width = 0.0;
        double height = 0.0;
        JSViewAbstract::ParseJsDouble(info[0], x);
        JSViewAbstract::ParseJsDouble(info[1], y);
        JSViewAbstract::ParseJsDouble(info[2], width);
        JSViewAbstract::ParseJsDouble(info[3], height);
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        width = PipelineBase::Vp2PxWithCurrentDensity(width);
        height = PipelineBase::Vp2PxWithCurrentDensity(height);
        renderingContext2DModel_->ClearRect(Rect(x, y, width, height));
    }
}

void JSCanvasRenderer::JsSaveLayer(const JSCallbackInfo& info)
{
    renderingContext2DModel_->SaveLayer();
}

void JSCanvasRenderer::JsRestoreLayer(const JSCallbackInfo& info)
{
    renderingContext2DModel_->RestoreLayer();
}

void JSCanvasRenderer::JsReset(const JSCallbackInfo& info)
{
    paintState_ = PaintState();
    style_ = TextStyle();
    anti_ = false;
    isInitializeShadow_ = false;
    isOffscreenInitializeShadow_ = false;
    renderingContext2DModel_->Reset();
}

Dimension JSCanvasRenderer::GetDimensionValue(const std::string& str)
{
    Dimension dimension = StringToDimension(str);
    if ((dimension.Unit() == DimensionUnit::NONE) || (dimension.Unit() == DimensionUnit::PX)) {
        return Dimension(dimension.Value());
    }
    if (dimension.Unit() == DimensionUnit::VP) {
        return Dimension(dimension.Value() * SystemProperties::GetResolution());
    }
    return Dimension(0.0);
}
} // namespace OHOS::Ace::Framework
