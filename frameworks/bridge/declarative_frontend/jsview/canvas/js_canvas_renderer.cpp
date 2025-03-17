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

#include "bridge/declarative_frontend/jsview/canvas/js_canvas_renderer.h"

#include <cstdint>
#include <memory>

#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_pattern.h"
#include "bridge/declarative_frontend/jsview/canvas/js_offscreen_rendering_context.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components/common/properties/paint_state.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline/pipeline_context.h"

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#include "pixel_map_napi.h"
#endif

namespace OHOS::Ace {
constexpr uint32_t PIXEL_SIZE = 4;
constexpr int32_t ALPHA_INDEX = 3;
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
std::unordered_map<int32_t, std::shared_ptr<Pattern>> JSCanvasRenderer::pattern_;
unsigned int JSCanvasRenderer::patternCount_ = 0;
namespace {

const std::set<std::string> FONT_WEIGHTS = { "normal", "bold", "lighter", "bolder", "100", "200", "300", "400", "500",
    "600", "700", "800", "900" };
const std::set<std::string> FONT_STYLES = { "italic", "oblique", "normal" };
const std::set<std::string> FONT_FAMILIES = { "sans-serif", "serif", "monospace" };
const std::set<std::string> QUALITY_TYPE = { "low", "medium", "high" }; // Default value is low.
constexpr double DEFAULT_QUALITY = 0.92;
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr double DIFF = 1e-10;
constexpr uint32_t RGB_SUB_SIZE = 3;
constexpr uint32_t RGBA_SUB_SIZE = 4;
constexpr double MIN_RGB_VALUE = 0.0;
constexpr double MAX_RGB_VALUE = 255.0;
constexpr double MIN_RGBA_OPACITY = 0.0;
constexpr double MAX_RGBA_OPACITY = 1.0;
template<typename T>
inline T ConvertStrToEnum(const char* key, const LinearMapNode<T>* map, size_t length, T defaultValue)
{
    int64_t index = BinarySearchFindIndex(map, length, key);
    return index != -1 ? map[index].value : defaultValue;
}

inline bool ParseJsDoubleArray(const JSRef<JSVal>& jsValue, std::vector<double>& result)
{
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

static bool MatchColorWithRGBA(const std::string& colorStr, Color& color)
{
    if (colorStr.rfind("rgb(", 0) != 0 && colorStr.rfind("rgba(", 0) != 0) {
        return false;
    }
    auto startPos = colorStr.find_first_of('(');
    auto endPos = colorStr.find_last_of(')');
    if (startPos == std::string::npos || endPos == std::string::npos || endPos != (colorStr.length() - 1)) {
        return false;
    }
    auto valueStr = colorStr.substr(startPos + 1, endPos - startPos - 1);
    std::vector<std::string> valueProps;
    StringUtils::StringSplitter(valueStr.c_str(), ',', valueProps);
    auto size = valueProps.size();
    auto count = std::count(valueStr.begin(), valueStr.end(), ',');
    if ((size != RGB_SUB_SIZE && size != RGBA_SUB_SIZE) || static_cast<int32_t>(size) != (count + 1)) {
        return false;
    }
    std::vector<uint8_t> colorInt;
    double opacity = 1.0;
    for (uint32_t i = 0; i < size; i++) {
        StringUtils::TrimStrLeadingAndTrailing(valueProps[i]);
        char* pEnd = nullptr;
        errno = 0;
        double val = std::strtod(valueProps[i].c_str(), &pEnd);
        if (pEnd == valueProps[i].c_str() || *pEnd != '\0' || errno == ERANGE) {
            return false;
        }
        if (i < RGB_SUB_SIZE) {
            val = std::clamp(val, MIN_RGB_VALUE, MAX_RGB_VALUE);
            colorInt.push_back(static_cast<uint8_t>(std::round(val)));
        } else {
            opacity = std::clamp(val, MIN_RGBA_OPACITY, MAX_RGBA_OPACITY);
        }
    }
    color = Color::FromRGBO(colorInt[0], colorInt[1], colorInt[2], opacity); // 0: red, 1: green, 2: blue.
    return true;
}

static bool ProcessColorFromString(std::string colorStr, Color& color)
{
    if (colorStr.empty()) {
        return false;
    }

    StringUtils::TrimStrLeadingAndTrailing(colorStr);
    std::transform(colorStr.begin(), colorStr.end(), colorStr.begin(), ::tolower);
    return (Color::MatchColorWithMagic(colorStr, COLOR_ALPHA_MASK, color) || MatchColorWithRGBA(colorStr, color) ||
            Color::MatchColorWithMagicMini(colorStr, COLOR_ALPHA_MASK, color) ||
            Color::MatchColorSpecialString(colorStr, color));
}

} // namespace

JSCanvasRenderer::JSCanvasRenderer()
{
    SetInstanceId(Container::CurrentIdSafely());
    density_ = PipelineBase::GetCurrentDensity();
    apiVersion_ = Container::GetCurrentApiTargetVersion();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        isJudgeSpecialValue_ = true;
    }
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    if (pipeline) {
        densityCallbackId_ = pipeline->RegisterDensityChangedCallback([self = WeakClaim(this)](double density) {
            auto canvasRender = self.Upgrade();
            CHECK_NULL_VOID(canvasRender);
            canvasRender->density_ = density;
            canvasRender->SetDensity();
        });
    }
}

JSCanvasRenderer::~JSCanvasRenderer()
{
    ContainerScope scope(instanceId_);
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    if (pipeline) {
        pipeline->UnregisterDensityChangedCallback(densityCallbackId_);
    }
}

// A helper fucntion to create GradientObj
JSRef<JSObject> JSCanvasRenderer::createGradientObj(const std::shared_ptr<Gradient>& gradient)
{
    JSRef<JSObject> pasteObj = JSClass<JSCanvasGradient>::NewInstance();
    pasteObj->SetProperty("__type", "gradient");
    auto pasteData = Referenced::Claim(pasteObj->Unwrap<JSCanvasGradient>());
    if (pasteData) {
        pasteData->SetGradient(gradient);
    } else {
        TAG_LOGE(AceLogTag::ACE_CANVAS, "Failed to construct 'Gradient'.");
    }
    return pasteObj;
}

// createLinearGradient(x0: number, y0: number, x1: number, y1: number): CanvasGradient
void JSCanvasRenderer::JsCreateLinearGradient(const JSCallbackInfo& info)
{
    double x0 = 0.0;
    double y0 = 0.0;
    double x1 = 0.0;
    double y1 = 0.0;
    if (info.GetDoubleArg(0, x0) && info.GetDoubleArg(1, y0) && info.GetDoubleArg(2, x1) && info.GetDoubleArg(3, y1)) {
        double density = GetDensity();
        auto gradient = std::make_shared<Gradient>();
        gradient->SetType(GradientType::LINEAR);
        gradient->SetBeginOffset(Offset(x0 * density, y0 * density));
        gradient->SetEndOffset(Offset(x1 * density, y1 * density));
        JSRef<JSObject> pasteObj = createGradientObj(gradient);
        info.SetReturnValue(pasteObj);
    }
}

// createRadialGradient(x0: number, y0: number, r0: number, x1: number, y1: number, r1: number): CanvasGradient
void JSCanvasRenderer::JsCreateRadialGradient(const JSCallbackInfo& info)
{
    double startX = 0.0;
    double startY = 0.0;
    double startRadial = 0.0;
    double endX = 0.0;
    double endY = 0.0;
    double endRadial = 0.0;
    if (info.GetDoubleArg(0, startX) && info.GetDoubleArg(1, startY) && info.GetDoubleArg(2, startRadial) &&
        info.GetDoubleArg(3, endX) && info.GetDoubleArg(4, endY) && info.GetDoubleArg(5, endRadial)) {
        double density = GetDensity();
        auto gradient = std::make_shared<Gradient>();
        gradient->SetType(GradientType::RADIAL);
        gradient->SetBeginOffset(Offset(startX * density, startY * density));
        gradient->SetEndOffset(Offset(endX * density, endY * density));
        gradient->SetInnerRadius(startRadial * density);
        gradient->SetOuterRadius(endRadial * density);
        JSRef<JSObject> pasteObj = createGradientObj(gradient);
        info.SetReturnValue(pasteObj);
    }
}

// createConicGradient(startAngle: number, x: number, y: number): CanvasGradient
void JSCanvasRenderer::JsCreateConicGradient(const JSCallbackInfo& info)
{
    if (info.Length() != 3) {
        return;
    }
    // in radian
    double startAngle = 0.0;
    double x = 0.0;
    double y = 0.0;
    info.GetDoubleArg(0, startAngle);
    info.GetDoubleArg(1, x);
    info.GetDoubleArg(2, y);
    double density = GetDensity();
    auto gradient = std::make_shared<Gradient>();
    gradient->SetType(GradientType::CONIC);
    gradient->GetConicGradient().startAngle = AnimatableDimension(Dimension(fmod(startAngle, (2 * M_PI))));
    gradient->GetConicGradient().centerX = AnimatableDimension(Dimension(x * density));
    gradient->GetConicGradient().centerY = AnimatableDimension(Dimension(y * density));
    JSRef<JSObject> pasteObj = createGradientObj(gradient);
    info.SetReturnValue(pasteObj);
}

// fillText(text: string, x: number, y: number, maxWidth?: number): void
void JSCanvasRenderer::JsFillText(const JSCallbackInfo& info)
{
    FillTextInfo textInfo;
    if (info.GetStringArg(0, textInfo.text) && info.GetDoubleArg(1, textInfo.x) && info.GetDoubleArg(2, textInfo.y)) {
        double density = GetDensity();
        textInfo.x *= density;
        textInfo.y *= density;
        if (info.Length() >= 4) {
            double maxWidth = 0.0;
            if (info.GetDoubleArg(3, maxWidth)) { // Parse the 3rd parameter.
                maxWidth *= density;
            } else if (info[3]->IsUndefined()) { // Is the 3rd parameter undefined.
                maxWidth = FLT_MAX;
            }
            if (maxWidth < 0) {
                return;
            }
            textInfo.maxWidth = maxWidth;
        }
        renderingContext2DModel_->SetFillText(paintState_, textInfo);
    }
}

// strokeText(text: string, x: number, y: number, maxWidth?:number): void
void JSCanvasRenderer::JsStrokeText(const JSCallbackInfo& info)
{
    FillTextInfo textInfo;
    double density = GetDensity();
    if (info.GetStringArg(0, textInfo.text) && info.GetDoubleArg(1, textInfo.x) && info.GetDoubleArg(2, textInfo.y)) {
        textInfo.x *= density;
        textInfo.y *= density;
        if (info.Length() >= 4) {
            double maxWidth = 0.0;
            if (info.GetDoubleArg(3, maxWidth)) { // Parse the 3rd parameter.
                maxWidth *= density;
            } else if (info[3]->IsUndefined()) { // Is the 3rd parameter undefined.
                maxWidth = FLT_MAX;
            }
            if (maxWidth < 0) {
                return;
            }
            textInfo.maxWidth = maxWidth;
        }
        renderingContext2DModel_->SetStrokeText(paintState_, textInfo);
    }
}

void JSCanvasRenderer::SetAntiAlias()
{
    renderingContext2DModel_->SetAntiAlias(anti_);
}

void JSCanvasRenderer::SetDensity()
{
    double density = GetDensity(true);
    renderingContext2DModel_->SetDensity(density);
}

// font: string
void JSCanvasRenderer::JsSetFont(const JSCallbackInfo& info)
{
    std::string fontStr;
    if (!info.GetStringArg(0, fontStr)) {
        return;
    }
    std::vector<std::string> fontProps;
    StringUtils::StringSplitter(fontStr.c_str(), ' ', fontProps);
    bool updateFontweight = false;
    bool updateFontStyle = false;
    for (const auto& fontProp : fontProps) {
        if (FONT_WEIGHTS.find(fontProp) != FONT_WEIGHTS.end()) {
            updateFontweight = true;
            auto weight = ConvertStrToFontWeight(fontProp);
            paintState_.SetFontWeight(weight);
            renderingContext2DModel_->SetFontWeight(weight);
        } else if (FONT_STYLES.find(fontProp) != FONT_STYLES.end()) {
            updateFontStyle = true;
            auto fontStyle = ConvertStrToFontStyle(fontProp);
            paintState_.SetFontStyle(fontStyle);
            renderingContext2DModel_->SetFontStyle(fontStyle);
        } else if (FONT_FAMILIES.find(fontProp) != FONT_FAMILIES.end() || IsCustomFont(fontProp)) {
            auto families = ConvertStrToFontFamilies(fontProp);
            paintState_.SetFontFamilies(families);
            renderingContext2DModel_->SetFontFamilies(families);
        } else if (fontProp.find("px") != std::string::npos || fontProp.find("vp") != std::string::npos) {
            Dimension size;
            if (fontProp.find("vp") != std::string::npos) {
                size = GetDimensionValue(fontProp);
            } else {
                std::string fontSize = fontProp.substr(0, fontProp.size() - 2);
                size = Dimension(StringToDouble(fontProp));
            }
            paintState_.SetFontSize(size);
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

// getLineDash(): number[]
void JSCanvasRenderer::JsGetLineDash(const JSCallbackInfo& info)
{
    std::vector<double> lineDash = renderingContext2DModel_->GetLineDash();
    JSRef<JSArray> lineDashObj = JSRef<JSArray>::New();
    double density = GetDensity();
    for (auto i = 0U; i < lineDash.size(); i++) {
        lineDashObj->SetValueAt(i, JSRef<JSVal>::Make(ToJSValue(lineDash[i] / density)));
    }
    info.SetReturnValue(lineDashObj);
}

// fillStyle: string | number | CanvasGradient | CanvasPattern
void JSCanvasRenderer::JsSetFillStyle(const JSCallbackInfo& info)
{
    Color color;
    std::string colorStr;
    if (info.GetStringArg(0, colorStr) && Color::ParseColorString(colorStr, color)) {
        renderingContext2DModel_->SetFillColor(color, true);
        return;
    }

    uint32_t colorNum;
    if (info.GetUint32Arg(0, colorNum)) {
        renderingContext2DModel_->SetFillColor(Color(ColorAlphaAdapt(colorNum)), false);
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
        auto* jSCanvasGradient = info.UnwrapArg<JSCanvasGradient>(0);
        CHECK_NULL_VOID(jSCanvasGradient);
        auto gradient = jSCanvasGradient->GetGradient();
        CHECK_NULL_VOID(gradient);
        renderingContext2DModel_->SetFillGradient(gradient);
    } else if (type == "pattern") {
        auto* jSCanvasPattern = info.UnwrapArg<JSCanvasPattern>(0);
        CHECK_NULL_VOID(jSCanvasPattern);
        int32_t id = jSCanvasPattern->GetId();
        renderingContext2DModel_->SetFillPattern(GetPatternPtr(id));
    }
}

// strokeStyle: string | number | CanvasGradient | CanvasPattern
void JSCanvasRenderer::JsSetStrokeStyle(const JSCallbackInfo& info)
{
    Color color;
    std::string colorStr;
    if (info.GetStringArg(0, colorStr) && Color::ParseColorString(colorStr, color)) {
        renderingContext2DModel_->SetStrokeColor(color, true);
        return;
    }

    uint32_t colorNum;
    if (info.GetUint32Arg(0, colorNum)) {
        renderingContext2DModel_->SetStrokeColor(Color(ColorAlphaAdapt(colorNum)), false);
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
        auto* jSCanvasGradient = info.UnwrapArg<JSCanvasGradient>(0);
        CHECK_NULL_VOID(jSCanvasGradient);
        auto gradient = jSCanvasGradient->GetGradient();
        CHECK_NULL_VOID(gradient);
        renderingContext2DModel_->SetStrokeGradient(gradient);
    } else if (type == "pattern") {
        auto* jSCanvasPattern = info.UnwrapArg<JSCanvasPattern>(0);
        CHECK_NULL_VOID(jSCanvasPattern);
        int32_t id = jSCanvasPattern->GetId();
        renderingContext2DModel_->SetStrokePattern(GetPatternPtr(id));
    }
}

RefPtr<CanvasPath2D> JSCanvasRenderer::JsMakePath2D(const JSCallbackInfo& info)
{
    if (info.Length() >= 1) {
        if (info[0]->IsString()) {
            std::string capStr = "";
            JSViewAbstract::ParseJsString(info[0], capStr);
            return AceType::MakeRefPtr<CanvasPath2D>(capStr);
        }

        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && info[0]->IsObject()) {
            auto* jsPath2d = info.UnwrapArg<JSPath2D>(0);
            CHECK_NULL_RETURN(jsPath2d, AceType::MakeRefPtr<CanvasPath2D>());
            auto canvasPath2D = jsPath2d->GetCanvasPath2d();
            return AceType::MakeRefPtr<CanvasPath2D>(canvasPath2D);
        }
    }
    // Example: ctx.createPath2D()
    return AceType::MakeRefPtr<CanvasPath2D>();
}

JSRenderImage* JSCanvasRenderer::UnwrapNapiImage(const JSRef<JSObject> jsObject)
{
    ContainerScope scope(instanceId_);
#if !defined(PREVIEW)
    auto engine = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
#else
    auto engine = EngineHelper::GetCurrentEngineSafely();
#endif
    CHECK_NULL_RETURN(engine, nullptr);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, nullptr);
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    panda::Local<JsiValue> value = jsObject.Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    napi_value napiValue = nativeEngine->ValueToNapiValue(valueWrapper);
    napi_value isImageBitmap = nullptr;
    if (napi_get_named_property(env, napiValue, "isImageBitmap", &isImageBitmap) != napi_ok) {
        return nullptr;
    }
    int32_t isImageBitmapValue = 0;
    napi_get_value_int32(env, isImageBitmap, &isImageBitmapValue);
    if (!isImageBitmapValue) {
        return nullptr;
    }
    void* native = nullptr;
    napi_unwrap(env, napiValue, &native);
    JSRenderImage* jsImage = reinterpret_cast<JSRenderImage*>(native);
    return jsImage;
}

void JSCanvasRenderer::DrawSvgImage(const JSCallbackInfo& info, JSRenderImage* jsImage)
{
    CanvasImage image;
    ExtractInfoToImage(image, info, true);
    image.instanceId = jsImage->GetInstanceId();

    ImageInfo imageInfo;
    imageInfo.image = image;
    imageInfo.svgDom = jsImage->GetSvgDom();
    CHECK_NULL_VOID(imageInfo.svgDom);
    imageInfo.imageFit = jsImage->GetImageFit();
    renderingContext2DModel_->DrawSvgImage(imageInfo);
}

void JSCanvasRenderer::DrawImage(const JSCallbackInfo& info, JSRenderImage* jsImage)
{
    CanvasImage image;
    ExtractInfoToImage(image, info, true);
    image.instanceId = jsImage->GetInstanceId();
    ImageInfo imageInfo;

#if !defined(PREVIEW)
    imageInfo.pixelMap = jsImage->GetPixelMap();
    CHECK_NULL_VOID(imageInfo.pixelMap);
    imageInfo.image = image;
    renderingContext2DModel_->DrawPixelMap(imageInfo);
#else
    image.src = jsImage->GetSrc();
    image.imageData = jsImage->GetImageData();
    imageInfo.image = image;
    imageInfo.imgWidth = jsImage->GetWidth();
    imageInfo.imgHeight = jsImage->GetHeight();
    renderingContext2DModel_->DrawImage(imageInfo);
#endif
}

void JSCanvasRenderer::DrawPixelMap(const JSCallbackInfo& info)
{
#if !defined(PREVIEW)
    CanvasImage image;
    ExtractInfoToImage(image, info, false);

    ImageInfo imageInfo;
    imageInfo.image = image;
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    CHECK_NULL_VOID(runtime);
    imageInfo.pixelMap = CreatePixelMapFromNapiValue(info[0], runtime->GetNativeEngine());
    CHECK_NULL_VOID(imageInfo.pixelMap);
    renderingContext2DModel_->DrawPixelMap(imageInfo);
#endif
}

// drawImage(image: ImageBitmap | PixelMap, dx: number, dy: number): void
// drawImage(image: ImageBitmap | PixelMap, dx: number, dy: number, dw: number, dh: number): void
// drawImage(image: ImageBitmap | PixelMap, sx: number, sy: number, sw: number, sh: number, dx: number,
//           dy: number, dw: number, dh: number):void
void JSCanvasRenderer::JsDrawImage(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (!info[0]->IsObject()) {
        return;
    }
    auto* jsImage = UnwrapNapiImage(info[0]);
    if (jsImage) {
        if (jsImage->IsSvg()) {
            DrawSvgImage(info, jsImage);
        } else {
            DrawImage(info, jsImage);
        }
    } else {
        DrawPixelMap(info);
    }
}

void JSCanvasRenderer::ExtractInfoToImage(CanvasImage& image, const JSCallbackInfo& info, bool isImage)
{
    double density = GetDensity();
    switch (info.Length()) {
        case 3:
            image.flag = 0;
            info.GetDoubleArg(1, image.dx);
            info.GetDoubleArg(2, image.dy);
            image.dx *= density;
            image.dy *= density;
            break;
        // 5 parameters: drawImage(image, dx, dy, dWidth, dHeight)
        case 5:
            image.flag = 1;
            info.GetDoubleArg(1, image.dx);
            info.GetDoubleArg(2, image.dy);
            info.GetDoubleArg(3, image.dWidth);
            info.GetDoubleArg(4, image.dHeight);
            image.dx *= density;
            image.dy *= density;
            image.dWidth *= density;
            image.dHeight *= density;
            break;
        // 9 parameters: drawImage(image, sx, sy, sWidth, sHeight, dx, dy, dWidth, dHeight)
        case 9:
            image.flag = 2;
            info.GetDoubleArg(1, image.sx);
            info.GetDoubleArg(2, image.sy);
            info.GetDoubleArg(3, image.sWidth);
            info.GetDoubleArg(4, image.sHeight);
            info.GetDoubleArg(5, image.dx);
            info.GetDoubleArg(6, image.dy);
            info.GetDoubleArg(7, image.dWidth);
            info.GetDoubleArg(8, image.dHeight);
            // In higher versions, sx, sy, sWidth, sHeight are parsed in VP units
            // In lower versions, sx, sy, sWidth, sHeight are parsed in PX units
            if (isImage || Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
                image.sx *= density;
                image.sy *= density;
                image.sWidth *= density;
                image.sHeight *= density;
            }
            image.dx *= density;
            image.dy *= density;
            image.dWidth *= density;
            image.dHeight *= density;
            break;
        default:
            break;
    }
}

// createPattern(image: ImageBitmap, repetition: string | null): CanvasPattern | null
void JSCanvasRenderer::JsCreatePattern(const JSCallbackInfo& info)
{
    auto arg0 = info[0];
    if (arg0->IsObject()) {
        auto* jsImage = UnwrapNapiImage(info[0]);
        CHECK_NULL_VOID(jsImage);
        std::string repeat;
        info.GetStringArg(1, repeat);
        auto pattern = std::make_shared<Pattern>();
        pattern->SetImgSrc(jsImage->GetSrc());
        pattern->SetImageWidth(jsImage->GetWidth());
        pattern->SetImageHeight(jsImage->GetHeight());
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
        canvasPattern->SetUnit(GetUnit());
        patternCount_++;
        info.SetReturnValue(obj);
    }
}

// createImageData(sw: number, sh: number): ImageData
// createImageData(imageData: ImageData): ImageData
void JSCanvasRenderer::JsCreateImageData(const JSCallbackInfo& info)
{
    double density = GetDensity();
    double fWidth = 0.0;
    double fHeight = 0.0;
    auto retObj = JSRef<JSObject>::New();
    info.SetReturnValue(retObj);
    if (info.Length() == 2) {
        info.GetDoubleArg(0, fWidth);
        info.GetDoubleArg(1, fHeight);
        fWidth *= density;
        fHeight *= density;
    } else if (info.Length() == 1 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> widthValue = obj->GetProperty("width");
        JSRef<JSVal> heightValue = obj->GetProperty("height");
        JSViewAbstract::ParseJsDouble(widthValue, fWidth);
        JSViewAbstract::ParseJsDouble(heightValue, fHeight);
    }
    uint32_t finalWidth = static_cast<uint32_t>(std::abs(fWidth + DIFF));
    uint32_t finalHeight = static_cast<uint32_t>(std::abs(fHeight + DIFF));
    JSRef<JSArrayBuffer> arrayBuffer = JSRef<JSArrayBuffer>::New(finalWidth * finalHeight * PIXEL_SIZE);
    // return the black image
    auto* buffer = static_cast<uint32_t*>(arrayBuffer->GetBuffer());
    // Height or Width is ZERO or Overflow.
    if (!buffer || (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight))) {
        JSRef<JSArrayBuffer> zeroArrayBuffer = JSRef<JSArrayBuffer>::New(0);
        auto zeroColorArray =
            JSRef<JSUint8ClampedArray>::New(zeroArrayBuffer->GetLocalHandle(), 0, zeroArrayBuffer->ByteLength());
        retObj->SetProperty("width", 0);
        retObj->SetProperty("height", 0);
        retObj->SetPropertyObject("data", zeroColorArray);
        return;
    }
    for (uint32_t idx = 0; idx < finalWidth * finalHeight; ++idx) {
        buffer[idx] = 0xffffffff;
    }

    JSRef<JSUint8ClampedArray> colorArray =
        JSRef<JSUint8ClampedArray>::New(arrayBuffer->GetLocalHandle(), 0, arrayBuffer->ByteLength());
    retObj->SetProperty("width", finalWidth);
    retObj->SetProperty("height", finalHeight);
    retObj->SetPropertyObject("data", colorArray);
}

// putImageData(imageData: ImageData, dx: number | string, dy: number | string): void
// putImageData(imageData: ImageData, dx: number | string, dy: number | string, dirtyX: number | string,
//              dirtyY: number | string, dirtyWidth: number | string, dirtyHeight: number | string): void
void JSCanvasRenderer::JsPutImageData(const JSCallbackInfo& info)
{
    auto arg0 = info[0]; // store the variable to avoid it being constructed multiple time.
    if (!arg0->IsObject()) {
        return;
    }
    // Parse the first parameter with type ImageData
    JSRef<JSObject> jsImageData = JSRef<JSObject>::Cast(arg0);
    JSRef<JSVal> jsImgWidth = jsImageData->GetProperty("width");
    JSRef<JSVal> jsImgHeight = jsImageData->GetProperty("height");
    JSRef<JSVal> jsImgData = jsImageData->GetProperty("data");
    if ((!jsImgWidth->IsNumber()) || (!jsImgHeight->IsNumber()) || (!jsImgData->IsUint8ClampedArray())) {
        return;
    }
    int32_t imgWidth = jsImgWidth->ToNumber<int32_t>();
    int32_t imgHeight = jsImgHeight->ToNumber<int32_t>();

    // Parse other parameters
    ImageData imageData = { .dirtyWidth = imgWidth, .dirtyHeight = imgHeight };
    ParseImageData(info, imageData);
    imageData.dirtyWidth = imageData.dirtyX < 0 ? std::min(imageData.dirtyX + imageData.dirtyWidth, imgWidth)
                                                : std::min(imgWidth - imageData.dirtyX, imageData.dirtyWidth);
    imageData.dirtyHeight = imageData.dirtyY < 0 ? std::min(imageData.dirtyY + imageData.dirtyHeight, imgHeight)
                                                 : std::min(imgHeight - imageData.dirtyY, imageData.dirtyHeight);

    // copy the data from the image data.
    JSRef<JSUint8ClampedArray> colorArray = JSRef<JSUint8ClampedArray>::Cast(jsImgData);
    auto arrayBuffer = colorArray->GetArrayBuffer();
    auto* buffer = static_cast<uint8_t*>(arrayBuffer->GetBuffer());
    CHECK_NULL_VOID(buffer);
    int32_t bufferLength = arrayBuffer->ByteLength();
    imageData.data = std::vector<uint32_t>();
    for (int32_t i = std::max(imageData.dirtyY, 0); i < imageData.dirtyY + imageData.dirtyHeight; ++i) {
        for (int32_t j = std::max(imageData.dirtyX, 0); j < imageData.dirtyX + imageData.dirtyWidth; ++j) {
            uint32_t idx = static_cast<uint32_t>(4 * (j + imgWidth * i));
            if (bufferLength > static_cast<int32_t>(idx + ALPHA_INDEX)) {
                uint8_t alpha = buffer[idx + 3]; // idx + 3: The 4th byte format: alpha
                uint8_t red = buffer[idx]; // idx: the 1st byte format: red
                uint8_t green = buffer[idx + 1]; // idx + 1: The 2nd byte format: green
                uint8_t blue = buffer[idx + 2]; // idx + 2: The 3rd byte format: blue
                imageData.data.emplace_back(Color::FromARGB(alpha, red, green, blue).GetValue());
            }
        }
    }

    renderingContext2DModel_->PutImageData(imageData);
}

void JSCanvasRenderer::ParseImageData(const JSCallbackInfo& info, ImageData& imageData)
{
    double density = GetDensity();
    std::string argStr;
    if (info.GetStringArg(1, argStr)) {
        imageData.x = static_cast<int32_t>(GetDimensionValue(argStr).Value());
    } else if (info.GetInt32Arg(1, imageData.x)) {
        imageData.x = static_cast<int32_t>(imageData.x * density);
    }

    if (info.GetStringArg(2, argStr)) {
        imageData.y = static_cast<int32_t>(GetDimensionValue(argStr).Value());
    } else if (info.GetInt32Arg(2, imageData.y)) {
        imageData.y = static_cast<int32_t>(imageData.y * density);
    }
    if (info.Length() != 7) {
        return;
    }
    if (info.GetStringArg(3, argStr)) {
        imageData.dirtyX = static_cast<int32_t>(GetDimensionValue(argStr).Value());
    } else if (info.GetInt32Arg(3, imageData.dirtyX)) {
        imageData.dirtyX = static_cast<int32_t>(imageData.dirtyX * density);
    }

    if (info.GetStringArg(4, argStr)) {
        imageData.dirtyY = static_cast<int32_t>(GetDimensionValue(argStr).Value());
    } else if (info.GetInt32Arg(4, imageData.dirtyY)) {
        imageData.dirtyY = static_cast<int32_t>(imageData.dirtyY * density);
    }

    if (info.GetStringArg(5, argStr)) {
        imageData.dirtyWidth = static_cast<int32_t>(GetDimensionValue(argStr).Value());
    } else if (info.GetInt32Arg(5, imageData.dirtyWidth)) {
        imageData.dirtyWidth = static_cast<int32_t>(imageData.dirtyWidth * density);
    }

    if (info.GetStringArg(6, argStr)) {
        imageData.dirtyHeight = static_cast<int32_t>(GetDimensionValue(argStr).Value());
    } else if (info.GetInt32Arg(6, imageData.dirtyHeight)) {
        imageData.dirtyHeight = static_cast<int32_t>(imageData.dirtyHeight * density);
    }
}

// Abandoned
void JSCanvasRenderer::JsCloseImageBitmap(const std::string& src)
{
    renderingContext2DModel_->CloseImageBitmap(src);
}

// getImageData(sx: number, sy: number, sw: number, sh: number): ImageData
void JSCanvasRenderer::JsGetImageData(const JSCallbackInfo& info)
{
    double density = GetDensity();
    ImageSize imageSize;
    auto retObj = JSRef<JSObject>::New();
    info.SetReturnValue(retObj);
    info.GetDoubleArg(0, imageSize.left);
    info.GetDoubleArg(1, imageSize.top);
    info.GetDoubleArg(2, imageSize.width);
    info.GetDoubleArg(3, imageSize.height);
    imageSize.left *= density;
    imageSize.top *= density;
    imageSize.width = imageSize.width * density + DIFF;
    imageSize.height = imageSize.height * density + DIFF;

    uint32_t finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    uint32_t finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    int32_t length = finalHeight * finalWidth * 4;
    JSRef<JSArrayBuffer> arrayBuffer = JSRef<JSArrayBuffer>::New(length);
    auto* buffer = static_cast<uint8_t*>(arrayBuffer->GetBuffer());
    // Height or Width is ZERO or Overflow.
    if (!buffer || (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight))) {
        JSRef<JSArrayBuffer> zeroArrayBuffer = JSRef<JSArrayBuffer>::New(0);
        auto zeroColorArray =
            JSRef<JSUint8ClampedArray>::New(zeroArrayBuffer->GetLocalHandle(), 0, zeroArrayBuffer->ByteLength());
        retObj->SetProperty("width", 0);
        retObj->SetProperty("height", 0);
        retObj->SetPropertyObject("data", zeroColorArray);
        return;
    }
    renderingContext2DModel_->GetImageDataModel(imageSize, buffer);
    auto colorArray = JSRef<JSUint8ClampedArray>::New(arrayBuffer->GetLocalHandle(), 0, arrayBuffer->ByteLength());
    retObj->SetProperty("width", finalWidth);
    retObj->SetProperty("height", finalHeight);
    retObj->SetPropertyObject("data", colorArray);
}

// getPixelMap(sx: number, sy: number, sw: number, sh: number): PixelMap
void JSCanvasRenderer::JsGetPixelMap(const JSCallbackInfo& info)
{
#ifdef PIXEL_MAP_SUPPORTED
    double density = GetDensity();
    ImageSize imageSize;
    info.GetDoubleArg(0, imageSize.left);
    info.GetDoubleArg(1, imageSize.top);
    info.GetDoubleArg(2, imageSize.width);
    info.GetDoubleArg(3, imageSize.height);
    imageSize.left *= density;
    imageSize.top *= density;
    imageSize.width = imageSize.width * density + DIFF;
    imageSize.height = imageSize.height * density + DIFF;
    auto height = static_cast<uint32_t>(std::abs(imageSize.height));
    auto width = static_cast<uint32_t>(std::abs(imageSize.width));
    if (height > 0 && width > (UINT32_MAX / height)) {
        return;
    }
    auto pixelmap = renderingContext2DModel_->GetPixelMap(imageSize);
    CHECK_NULL_VOID(pixelmap);

    // pixelmap to NapiValue
    ContainerScope scope(instanceId_);
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    CHECK_NULL_VOID(runtime);
    NativeEngine* nativeEngine = runtime->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    auto pixelmapSharedPtr = pixelmap->GetPixelMapSharedPtr();
    napi_value napiValue = OHOS::Media::PixelMapNapi::CreatePixelMap(env, pixelmapSharedPtr);
    auto jsValue = JsConverter::ConvertNapiValueToJsVal(napiValue);
    info.SetReturnValue(jsValue);
#else
    TAG_LOGI(
        AceLogTag::ACE_CANVAS, "[Engine Log] The function 'getPixelMap' is not supported on the current platform.");
#endif
}

// setPixelMap(value?: PixelMap): void
void JSCanvasRenderer::JsSetPixelMap(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
#if !defined(PREVIEW)
    if (info[0]->IsObject()) {
        ImageInfo imageInfo;
        auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
        CHECK_NULL_VOID(runtime);
        imageInfo.pixelMap = CreatePixelMapFromNapiValue(info[0], runtime->GetNativeEngine());
        CHECK_NULL_VOID(imageInfo.pixelMap);
        renderingContext2DModel_->DrawPixelMap(imageInfo);
    }
#else
    TAG_LOGI(
        AceLogTag::ACE_CANVAS, "[Engine Log] The function 'setPixelMap' is not supported on the current platform.");
#endif
}

// Abandoned
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
    bitmapMeshInfo.offscreenPattern = OffscreenPattern;
    bitmapMeshInfo.mesh = mesh;
    bitmapMeshInfo.column = column;
    bitmapMeshInfo.row = row;
    renderingContext2DModel_->DrawBitmapMesh(bitmapMeshInfo);
}

// filter: string
void JSCanvasRenderer::JsSetFilter(const JSCallbackInfo& info)
{
    std::string filterStr = "none";
    if (info.GetStringArg(0, filterStr) && !filterStr.empty()) {
        renderingContext2DModel_->SetFilterParam(filterStr);
    }
}

// direction: CanvasDirection
void JSCanvasRenderer::JsSetDirection(const JSCallbackInfo& info)
{
    std::string directionStr;
    if (info.GetStringArg(0, directionStr)) {
        auto direction = ConvertStrToTextDirection(directionStr);
        renderingContext2DModel_->SetTextDirection(direction);
    }
}

// getJsonData(path: string): string
void JSCanvasRenderer::JsGetJsonData(const JSCallbackInfo& info)
{
    std::string path;
    if (info.GetStringArg(0, path)) {
        std::string jsonData = renderingContext2DModel_->GetJsonData(path);
        auto returnValue = JSVal(ToJSValue(jsonData));
        auto returnPtr = JSRef<JSVal>::Make(returnValue);
        info.SetReturnValue(returnPtr);
    }
}

// toDataURL(type?: string, quality?: number): string
void JSCanvasRenderer::JsToDataUrl(const JSCallbackInfo& info)
{
    std::string dataUrl;
    double quality = DEFAULT_QUALITY;
    info.GetStringArg(0, dataUrl);
    info.GetDoubleArg(1, quality);
    std::string result = renderingContext2DModel_->ToDataURL(dataUrl, quality);

    auto returnValue = JSVal(ToJSValue(result));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

// lineCap: CanvasLineCap
void JSCanvasRenderer::JsSetLineCap(const JSCallbackInfo& info)
{
    static const LinearMapNode<LineCapStyle> lineCapTable[] = {
        { "butt", LineCapStyle::BUTT },
        { "round", LineCapStyle::ROUND },
        { "square", LineCapStyle::SQUARE },
    };
    std::string capStr;
    if (info.GetStringArg(0, capStr)) {
        auto lineCap = ConvertStrToEnum(capStr.c_str(), lineCapTable, ArraySize(lineCapTable), LineCapStyle::BUTT);
        renderingContext2DModel_->SetLineCap(lineCap);
    }
}

// lineJoin: CanvasLineJoin
void JSCanvasRenderer::JsSetLineJoin(const JSCallbackInfo& info)
{
    static const LinearMapNode<LineJoinStyle> lineJoinTable[3] = {
        { "bevel", LineJoinStyle::BEVEL },
        { "miter", LineJoinStyle::MITER },
        { "round", LineJoinStyle::ROUND },
    };
    std::string joinStr;
    if (info.GetStringArg(0, joinStr)) {
        auto lineJoin =
            ConvertStrToEnum(joinStr.c_str(), lineJoinTable, ArraySize(lineJoinTable), LineJoinStyle::MITER);
        renderingContext2DModel_->SetLineJoin(lineJoin);
    }
}

// miterLimit: number
void JSCanvasRenderer::JsSetMiterLimit(const JSCallbackInfo& info)
{
    double limit = 0.0;
    if (info.GetDoubleArg(0, limit)) {
        if (limit == 0 && apiVersion_ >= static_cast<int32_t>(PlatformVersion::VERSION_TWENTY)) {
            return;
        }
        renderingContext2DModel_->SetMiterLimit(limit);
    }
}

// lineWidth: number
void JSCanvasRenderer::JsSetLineWidth(const JSCallbackInfo& info)
{
    double lineWidth = 0.0;
    if (info.GetDoubleArg(0, lineWidth)) {
        renderingContext2DModel_->SetLineWidth(lineWidth * GetDensity());
    }
}

// globalAlpha: number
void JSCanvasRenderer::JsSetGlobalAlpha(const JSCallbackInfo& info)
{
    double alpha = 0.0;
    if (info.GetDoubleArg(0, alpha, isJudgeSpecialValue_)) { // Indexd0: the 1st arg.
        renderingContext2DModel_->SetGlobalAlpha(alpha);
    }
}

// globalCompositeOperation: string
void JSCanvasRenderer::JsSetGlobalCompositeOperation(const JSCallbackInfo& info)
{
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
    std::string compositeStr;
    if (info.GetStringArg(0, compositeStr)) {
        auto type = ConvertStrToEnum(compositeStr.c_str(), compositeOperationTable, ArraySize(compositeOperationTable),
            CompositeOperation::SOURCE_OVER);
        renderingContext2DModel_->SetCompositeType(type);
    }
}

// lineDashOffset: number
void JSCanvasRenderer::JsSetLineDashOffset(const JSCallbackInfo& info)
{
    double lineDashOffset = 0.0;
    if (info.GetDoubleArg(0, lineDashOffset, isJudgeSpecialValue_)) { // Indexd0: the 1st arg.
        renderingContext2DModel_->SetLineDashOffset(lineDashOffset * GetDensity());
    }
}

// shadowBlur: number
void JSCanvasRenderer::JsSetShadowBlur(const JSCallbackInfo& info)
{
    double blur = 0.0;
    if (info.GetDoubleArg(0, blur)) {
        renderingContext2DModel_->SetShadowBlur(blur);
    }
}

// shadowColor: string
void JSCanvasRenderer::JsSetShadowColor(const JSCallbackInfo& info)
{
    std::string colorStr;
    Color color;
    if (!info.GetStringArg(0, colorStr)) {
        return;
    }
    if (apiVersion_ >= static_cast<int32_t>(PlatformVersion::VERSION_TWENTY)) {
        if (!ProcessColorFromString(colorStr, color)) {
            return;
        }
    } else {
        color = Color::FromString(colorStr);
    }
    renderingContext2DModel_->SetShadowColor(color);
}

// shadowOffsetX: number
void JSCanvasRenderer::JsSetShadowOffsetX(const JSCallbackInfo& info)
{
    double offsetX = 0.0;
    if (info.GetDoubleArg(0, offsetX)) {
        renderingContext2DModel_->SetShadowOffsetX(offsetX * GetDensity());
    }
}

// shadowOffsetY: number
void JSCanvasRenderer::JsSetShadowOffsetY(const JSCallbackInfo& info)
{
    double offsetY = 0.0;
    if (info.GetDoubleArg(0, offsetY)) {
        renderingContext2DModel_->SetShadowOffsetY(offsetY * GetDensity());
    }
}

// imageSmoothingEnabled: boolean
void JSCanvasRenderer::JsSetImageSmoothingEnabled(const JSCallbackInfo& info)
{
    bool enabled = false;
    if (info.GetBooleanArg(0, enabled)) {
        renderingContext2DModel_->SetSmoothingEnabled(enabled);
    }
}

// imageSmoothingQuality: ImageSmoothingQuality
void JSCanvasRenderer::JsSetImageSmoothingQuality(const JSCallbackInfo& info)
{
    std::string quality;
    if (info.GetStringArg(0, quality) && (QUALITY_TYPE.find(quality) != QUALITY_TYPE.end())) {
        renderingContext2DModel_->SetSmoothingQuality(quality);
    }
}

// moveTo(x: number, y: number): void
void JSCanvasRenderer::JsMoveTo(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    if (info.GetDoubleArg(0, x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, y, isJudgeSpecialValue_)) { // Index1: the 2nd arg.
        double density = GetDensity();
        renderingContext2DModel_->MoveTo(x * density, y * density);
    }
}

// lineTo(x: number, y: number): void
void JSCanvasRenderer::JsLineTo(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    if (info.GetDoubleArg(0, x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, y, isJudgeSpecialValue_)) { // Index1: the 2nd arg.
        double density = GetDensity();
        renderingContext2DModel_->LineTo(x * density, y * density);
    }
}

// bezierCurveTo(cp1x: number, cp1y: number, cp2x: number, cp2y: number, x: number, y: number): void
void JSCanvasRenderer::JsBezierCurveTo(const JSCallbackInfo& info)
{
    BezierCurveParam param;
    if (info.GetDoubleArg(0, param.cp1x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, param.cp1y, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, param.cp2x, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, param.cp2y, isJudgeSpecialValue_) && // Index3: the 4th arg.
        info.GetDoubleArg(4, param.x, isJudgeSpecialValue_) && // Index4: the 5th arg.
        info.GetDoubleArg(5, param.y, isJudgeSpecialValue_)) { // Index5: the 6th arg.
        double density = GetDensity();
        param.cp1x *= density;
        param.cp1y *= density;
        param.cp2x *= density;
        param.cp2y *= density;
        param.x *= density;
        param.y *= density;
        renderingContext2DModel_->BezierCurveTo(param);
    }
}

// quadraticCurveTo(cpx: number, cpy: number, x: number, y: number): void
void JSCanvasRenderer::JsQuadraticCurveTo(const JSCallbackInfo& info)
{
    QuadraticCurveParam param;
    if (info.GetDoubleArg(0, param.cpx, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, param.cpy, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, param.x, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, param.y, isJudgeSpecialValue_)) { // Index3: the 4th arg.
        double density = GetDensity();
        param.cpx *= density;
        param.cpy *= density;
        param.x *= density;
        param.y *= density;
        renderingContext2DModel_->QuadraticCurveTo(param);
    }
}

// arcTo(x1: number, y1: number, x2: number, y2: number, radius: number): void
void JSCanvasRenderer::JsArcTo(const JSCallbackInfo& info)
{
    ArcToParam param;
    if (info.GetDoubleArg(0, param.x1, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, param.y1, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, param.x2, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, param.y2, isJudgeSpecialValue_) && // Index3: the 4th arg.
        info.GetDoubleArg(4, param.radius, isJudgeSpecialValue_)) { // Index4: the 5th arg.
        double density = GetDensity();
        param.x1 *= density;
        param.y1 *= density;
        param.x2 *= density;
        param.y2 *= density;
        param.radius *= density;
        renderingContext2DModel_->ArcTo(param);
    }
}

// arc(x: number, y: number, radius: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void
void JSCanvasRenderer::JsArc(const JSCallbackInfo& info)
{
    ArcParam param;
    if (info.GetDoubleArg(0, param.x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, param.y, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, param.radius, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, param.startAngle, isJudgeSpecialValue_) && // Index3: the 4th arg.
        info.GetDoubleArg(4, param.endAngle, isJudgeSpecialValue_)) { // Index4: the 5th arg.
        info.GetBooleanArg(5, param.anticlockwise); // Non mandatory parameter with default value 'false'
        double density = GetDensity();
        param.x *= density;
        param.y *= density;
        param.radius *= density;
        renderingContext2DModel_->Arc(param);
    }
}

// ellipse(x: number, y: number, radiusX: number, radiusY: number, rotation: number, startAngle: number,
//         endAngle: number, counterclockwise?: boolean): void
void JSCanvasRenderer::JsEllipse(const JSCallbackInfo& info)
{
    EllipseParam param;
    if (info.GetDoubleArg(0, param.x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, param.y, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, param.radiusX, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, param.radiusY, isJudgeSpecialValue_) && // Index3: the 4th arg.
        info.GetDoubleArg(4, param.rotation, isJudgeSpecialValue_) && // Index4: the 5th arg.
        info.GetDoubleArg(5, param.startAngle, isJudgeSpecialValue_) && // Index5: the 6th arg.
        info.GetDoubleArg(6, param.endAngle, isJudgeSpecialValue_)) { // Index6: the 7th arg.
        info.GetBooleanArg(7, param.anticlockwise); // Non mandatory parameter with default value 'false'
        double density = GetDensity();
        param.x *= density;
        param.y *= density;
        param.radiusX *= density;
        param.radiusY *= density;
        renderingContext2DModel_->Ellipse(param);
    }
}

// fill(fillRule?: CanvasFillRule): void
// fill(path: Path2D, fillRule?: CanvasFillRule): void
void JSCanvasRenderer::JsFill(const JSCallbackInfo& info)
{
    std::string ruleStr;
    auto fillRule = CanvasFillRule::NONZERO;

    // fill(fillRule?: CanvasFillRule): void
    if (info.Length() == 0 || info.GetStringArg(0, ruleStr)) {
        fillRule = ruleStr == "evenodd" ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
        renderingContext2DModel_->SetFillRuleForPath(fillRule);
        return;
    }

    // fill(path: Path2D, fillRule?: CanvasFillRule): void
    JSPath2D* jsCanvasPath = info.UnwrapArg<JSPath2D>(0);
    CHECK_NULL_VOID(jsCanvasPath);
    auto path = jsCanvasPath->GetCanvasPath2d();
    if (info.GetStringArg(1, ruleStr) && ruleStr == "evenodd") {
        fillRule = CanvasFillRule::EVENODD;
    }
    renderingContext2DModel_->SetFillRuleForPath2D(fillRule, path);
}

// stroke(path?: Path2D): void
void JSCanvasRenderer::JsStroke(const JSCallbackInfo& info)
{
    auto* jsCanvasPath = info.UnwrapArg<JSPath2D>(0);
    if (jsCanvasPath) {
        auto path = jsCanvasPath->GetCanvasPath2d();
        renderingContext2DModel_->SetStrokeRuleForPath2D(CanvasFillRule::NONZERO, path);
        return;
    }
    renderingContext2DModel_->SetStrokeRuleForPath(CanvasFillRule::NONZERO);
}

// clip(fillRule?: CanvasFillRule): void
// clip(path: Path2D, fillRule?: CanvasFillRule): void
void JSCanvasRenderer::JsClip(const JSCallbackInfo& info)
{
    std::string ruleStr;
    auto fillRule = CanvasFillRule::NONZERO;

    // clip(fillRule?: CanvasFillRule): void
    if (info.Length() == 0 || info.GetStringArg(0, ruleStr)) {
        fillRule = ruleStr == "evenodd" ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
        renderingContext2DModel_->SetClipRuleForPath(fillRule);
        return;
    }

    // clip(path: Path2D, fillRule?: CanvasFillRule): void
    JSPath2D* jsCanvasPath = info.UnwrapArg<JSPath2D>(0);
    CHECK_NULL_VOID(jsCanvasPath);
    auto path = jsCanvasPath->GetCanvasPath2d();
    if (info.GetStringArg(1, ruleStr) && ruleStr == "evenodd") {
        fillRule = CanvasFillRule::EVENODD;
    }
    renderingContext2DModel_->SetClipRuleForPath2D(fillRule, path);
}

// rect(x: number, y: number, w: number, h: number): void
void JSCanvasRenderer::JsRect(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    if (info.GetDoubleArg(0, x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, y, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, width, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, height, isJudgeSpecialValue_)) { // Index3: the 4th arg.
        renderingContext2DModel_->AddRect(Rect(x, y, width, height) * GetDensity());
    }
}

// beginPath(): void
void JSCanvasRenderer::JsBeginPath(const JSCallbackInfo& info)
{
    renderingContext2DModel_->BeginPath();
}

// closePath(): void
void JSCanvasRenderer::JsClosePath(const JSCallbackInfo& info)
{
    renderingContext2DModel_->ClosePath();
}

// restore(): void
void JSCanvasRenderer::JsRestore(const JSCallbackInfo& info)
{
    if (!savePaintState_.empty()) {
        paintState_ = savePaintState_.back();
        savePaintState_.pop_back();
    }
    renderingContext2DModel_->Restore();
}

// save(): void
void JSCanvasRenderer::JsSave(const JSCallbackInfo& info)
{
    savePaintState_.push_back(paintState_);
    renderingContext2DModel_->CanvasRendererSave();
}

// rotate(angle: number): void
void JSCanvasRenderer::JsRotate(const JSCallbackInfo& info)
{
    double angle = 0.0;
    if (info.GetDoubleArg(0, angle, isJudgeSpecialValue_)) { // Indexd0: the 1st arg.
        renderingContext2DModel_->CanvasRendererRotate(angle);
    }
}

// scale(x: number, y: number): void
void JSCanvasRenderer::JsScale(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    if (info.GetDoubleArg(0, x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, y, isJudgeSpecialValue_)) { // Index1: the 2nd arg.
        renderingContext2DModel_->CanvasRendererScale(x, y);
    }
}

// getTransform(): Matrix2D
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

// setTransform(a: number, b: number, c: number, d: number, e: number, f: number): void
// setTransform(transform?: Matrix2D): void
void JSCanvasRenderer::JsSetTransform(const JSCallbackInfo& info)
{
    if (info.GetSize() == 0) {
        renderingContext2DModel_->ResetTransform();
    }
    double density = GetDensity();
    TransformParam param;
    // setTransform(a: number, b: number, c: number, d: number, e: number, f: number): void
    if (info.GetDoubleArg(0, param.scaleX, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, param.skewY, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, param.skewX, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, param.scaleY, isJudgeSpecialValue_) && // Index3: the 4th arg.
        info.GetDoubleArg(4, param.translateX, isJudgeSpecialValue_) && // Index4: the 5th arg.
        info.GetDoubleArg(5, param.translateY, isJudgeSpecialValue_)) { // Index5: the 6th arg.
        param.translateX *= density;
        param.translateY *= density;
        renderingContext2DModel_->SetTransform(param, true);
        return;
    }

    // >= API10: setTransform(transform?: Matrix2D): void
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        auto* jsMatrix2d = info.UnwrapArg<JSMatrix2d>(0);
        CHECK_NULL_VOID(jsMatrix2d);
        param = jsMatrix2d->GetTransform();
        renderingContext2DModel_->SetTransform(param, false);
        return;
    }

    // old version: setTransform(transform?: Matrix2D): void
    if (info[0]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        TransformParam param = JSMatrix2d::GetTransformInfo(jsObj);
        param.translateX *= density;
        param.translateY *= density;
        renderingContext2DModel_->SetTransform(param, false);
    }
}

// resetTransform(): void
void JSCanvasRenderer::JsResetTransform(const JSCallbackInfo& info)
{
    renderingContext2DModel_->ResetTransform();
}

// transform(a: number, b: number, c: number, d: number, e: number, f: number): void
void JSCanvasRenderer::JsTransform(const JSCallbackInfo& info)
{
    TransformParam param;
    if (info.GetDoubleArg(0, param.scaleX, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, param.skewX, isJudgeSpecialValue_) && // Index1: the 2nd arg.
        info.GetDoubleArg(2, param.skewY, isJudgeSpecialValue_) && // Index2: the 3rd arg.
        info.GetDoubleArg(3, param.scaleY, isJudgeSpecialValue_) && // Index3: the 4th arg.
        info.GetDoubleArg(4, param.translateX, isJudgeSpecialValue_) && // Index4: the 5th arg.
        info.GetDoubleArg(5, param.translateY, isJudgeSpecialValue_)) { // Index5: the 6th arg.
        double density = GetDensity();
        param.translateX *= density;
        param.translateY *= density;
        renderingContext2DModel_->Transform(param);
    }
}

// translate(x: number, y: number): void
void JSCanvasRenderer::JsTranslate(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    if (info.GetDoubleArg(0, x, isJudgeSpecialValue_) && // Indexd0: the 1st arg.
        info.GetDoubleArg(1, y, isJudgeSpecialValue_)) { // Index1: the 2nd arg.
        double density = GetDensity();
        renderingContext2DModel_->Translate(x * density, y * density);
    }
}

// setLineDash(segments: number[]): void
void JSCanvasRenderer::JsSetLineDash(const JSCallbackInfo& info)
{
    std::vector<double> lineDash;
    info.GetDoubleArrayArg(0, lineDash);
    if (lineDash.size() % 2 != 0) {
        lineDash.insert(lineDash.end(), lineDash.begin(), lineDash.end());
    }
    double density = GetDensity();
    if (!Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        for (auto i = 0U; i < lineDash.size(); i++) {
            lineDash[i] *= density;
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
    if (id < 0 || id >= static_cast<int32_t>(pattern_.size())) {
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
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
            renderingContext2DModel_->SetTransform(pattern_[id], transform);
        } else {
            pattern_[id]->SetScaleX(transform.scaleX);
            pattern_[id]->SetScaleY(transform.scaleY);
            pattern_[id]->SetSkewX(transform.skewX);
            pattern_[id]->SetSkewY(transform.skewY);
            pattern_[id]->SetTranslateX(transform.translateX);
            pattern_[id]->SetTranslateY(transform.translateY);
        }
    }
}

// textAlign: CanvasTextAlign
void JSCanvasRenderer::JsSetTextAlign(const JSCallbackInfo& info)
{
    std::string value;
    if (info.GetStringArg(0, value)) {
        auto align = ConvertStrToTextAlign(value);
        paintState_.SetTextAlign(align);
        renderingContext2DModel_->SetTextAlign(align);
    }
}

// textBaseline: CanvasTextBaseline
void JSCanvasRenderer::JsSetTextBaseline(const JSCallbackInfo& info)
{
    std::string textBaseline;
    if (info.GetStringArg(0, textBaseline)) {
        auto baseline =
            ConvertStrToEnum(textBaseline.c_str(), BASELINE_TABLE, ArraySize(BASELINE_TABLE), TextBaseline::ALPHABETIC);
        paintState_.SetTextBaseline(baseline);
        renderingContext2DModel_->SetTextBaseline(baseline);
    }
}

// measureText(text: string): TextMetrics
void JSCanvasRenderer::JsMeasureText(const JSCallbackInfo& info)
{
    std::string text;
    double density = GetDensity();
    bool isGetStr = info.GetStringArg(0, text);
    if (!isGetStr && apiVersion_ >= static_cast<int32_t>(PlatformVersion::VERSION_TWENTY)) {
        if (info[0]->IsUndefined()) {
            text = "undefined";
            isGetStr = true;
        } else if (info[0]->IsNull()) {
            text = "null";
            isGetStr = true;
        }
    }
    if (Positive(density) && isGetStr) {
        TextMetrics textMetrics = renderingContext2DModel_->GetMeasureTextMetrics(paintState_, text);
        auto vm = info.GetVm();
        CHECK_NULL_VOID(vm);
        static const char* keysOfMeasureText[] = { "width", "height", "actualBoundingBoxLeft", "actualBoundingBoxRight",
            "actualBoundingBoxAscent", "actualBoundingBoxDescent", "hangingBaseline", "alphabeticBaseline",
            "ideographicBaseline", "emHeightAscent", "emHeightDescent", "fontBoundingBoxAscent",
            "fontBoundingBoxDescent" };
        Local<JSValueRef> valuesOfMeasureText[] = { panda::NumberRef::New(vm, (textMetrics.width / density)),
            panda::NumberRef::New(vm, (textMetrics.height / density)),
            panda::NumberRef::New(vm, (textMetrics.actualBoundingBoxLeft / density)),
            panda::NumberRef::New(vm, (textMetrics.actualBoundingBoxRight / density)),
            panda::NumberRef::New(vm, (textMetrics.actualBoundingBoxAscent / density)),
            panda::NumberRef::New(vm, (textMetrics.actualBoundingBoxDescent / density)),
            panda::NumberRef::New(vm, (textMetrics.hangingBaseline / density)),
            panda::NumberRef::New(vm, (textMetrics.alphabeticBaseline / density)),
            panda::NumberRef::New(vm, (textMetrics.ideographicBaseline / density)),
            panda::NumberRef::New(vm, (textMetrics.emHeightAscent / density)),
            panda::NumberRef::New(vm, (textMetrics.emHeightDescent / density)),
            panda::NumberRef::New(vm, (textMetrics.fontBoundingBoxAscent / density)),
            panda::NumberRef::New(vm, (textMetrics.fontBoundingBoxDescent / density)) };
        auto obj = panda::ObjectRef::NewWithNamedProperties(
            vm, ArraySize(keysOfMeasureText), keysOfMeasureText, valuesOfMeasureText);
        info.SetReturnValue(JsiRef<JsiObject>(JsiObject(obj)));
    }
}

// fillRect(x: number, y: number, w: number, h: number): void
void JSCanvasRenderer::JsFillRect(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    if (info.GetDoubleArg(0, x) && info.GetDoubleArg(1, y) && info.GetDoubleArg(2, width) &&
        info.GetDoubleArg(3, height)) {
        renderingContext2DModel_->FillRect(Rect(x, y, width, height) * GetDensity());
    }
}

// strokeRect(x: number, y: number, w: number, h: number): void
void JSCanvasRenderer::JsStrokeRect(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    if (info.GetDoubleArg(0, x) && info.GetDoubleArg(1, y) && info.GetDoubleArg(2, width) &&
        info.GetDoubleArg(3, height)) {
        renderingContext2DModel_->StrokeRect(Rect(x, y, width, height) * GetDensity());
    }
}

// clearRect(x: number, y: number, w: number, h: number): void
void JSCanvasRenderer::JsClearRect(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    if (info.GetDoubleArg(0, x) && info.GetDoubleArg(1, y) && info.GetDoubleArg(2, width) &&
        info.GetDoubleArg(3, height)) {
        renderingContext2DModel_->ClearRect(Rect(x, y, width, height) * GetDensity());
    }
}

// saveLayer(): void
void JSCanvasRenderer::JsSaveLayer(const JSCallbackInfo& info)
{
    renderingContext2DModel_->SaveLayer();
}

// restoreLayer(): void
void JSCanvasRenderer::JsRestoreLayer(const JSCallbackInfo& info)
{
    renderingContext2DModel_->RestoreLayer();
}

// reset(): void
void JSCanvasRenderer::JsReset(const JSCallbackInfo& info)
{
    ResetPaintState();
    renderingContext2DModel_->Reset();
}

void JSCanvasRenderer::ResetPaintState()
{
    paintState_ = PaintState();
    std::vector<PaintState>().swap(savePaintState_);
    isInitializeShadow_ = false;
    isOffscreenInitializeShadow_ = false;
}

Dimension JSCanvasRenderer::GetDimensionValue(const std::string& str)
{
    Dimension dimension = StringToDimension(str);
    if ((dimension.Unit() == DimensionUnit::NONE) || (dimension.Unit() == DimensionUnit::PX)) {
        return Dimension(dimension.Value());
    }
    if (dimension.Unit() == DimensionUnit::VP) {
        return Dimension(dimension.Value() * GetDensity(true));
    }
    return Dimension(0.0);
}

bool JSCanvasRenderer::IsCustomFont(const std::string& fontName)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto fontManager = pipeline->GetFontManager();
    CHECK_NULL_RETURN(fontManager, false);
    auto fontNames = fontManager->GetFontNames();
    return std::find(fontNames.begin(), fontNames.end(), fontName) != fontNames.end();
}

bool JSCanvasRenderer::IsValidLetterSpacing(const std::string& letterSpacing)
{
    std::regex pattern(R"(^[+-]?(\d+(\.\d+)?|\.\d+)((vp|px)$)?$)", std::regex::icase);
    return std::regex_match(letterSpacing, pattern);
}

// letterSpacing: string | LengthMetrics
void JSCanvasRenderer::JsSetLetterSpacing(const JSCallbackInfo& info)
{
    CalcDimension letterSpacingCal = Dimension(0.0);
    std::string letterSpacingStr;
    if (info.GetStringArg(0, letterSpacingStr) && IsValidLetterSpacing(letterSpacingStr)) {
        if (letterSpacingStr.find("vp") != std::string::npos || letterSpacingStr.find("px") != std::string::npos) {
            letterSpacingCal = GetDimensionValue(letterSpacingStr);
        } else {
            letterSpacingCal = Dimension(StringToDouble(letterSpacingStr) * GetDensity());
        }
    } else if (info[0]->IsObject() && JSViewAbstract::ParseLengthMetricsToDimension(info[0], letterSpacingCal)) {
        if (letterSpacingCal.Unit() != DimensionUnit::PX && letterSpacingCal.Unit() != DimensionUnit::VP) {
            letterSpacingCal.Reset();
        }
    }
    paintState_.SetLetterSpacing(letterSpacingCal);
    renderingContext2DModel_->SetLetterSpacing(letterSpacingCal);
}
} // namespace OHOS::Ace::Framework
