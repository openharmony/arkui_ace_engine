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

#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/jsview/js_canvas_pattern.h"
#include "bridge/declarative_frontend/jsview/js_offscreen_rendering_context.h"
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

inline bool ParseJsInt(const JSRef<JSVal>& jsValue, int32_t& result)
{
    if (jsValue->IsNumber()) {
        result = jsValue->ToNumber<int32_t>();
        return true;
    } else {
        return false;
    }
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

} // namespace

JSCanvasRenderer::JSCanvasRenderer()
{
    SetInstanceId(Container::CurrentIdSafely());
}

// A helper fucntion to create GradientObj
JSRef<JSObject> JSCanvasRenderer::createGradientObj(Gradient* gradient)
{
    JSRef<JSObject> pasteObj = JSClass<JSCanvasGradient>::NewInstance();
    pasteObj->SetProperty("__type", "gradient");
    auto pasteData = Referenced::Claim(pasteObj->Unwrap<JSCanvasGradient>());
    pasteData->SetGradient(gradient);
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
        ContainerScope scope(instanceId_);
        double density = GetDensity();
        Gradient* gradient = new Gradient();
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
        ContainerScope scope(instanceId_);
        double density = GetDensity();
        Gradient* gradient = new Gradient();
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
    ContainerScope scope(instanceId_);
    double density = GetDensity();
    Gradient* gradient = new Gradient();
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
        ContainerScope scope(instanceId_);
        double density = GetDensity();
        textInfo.x *= density;
        textInfo.y *= density;
        if (info.Length() >= 4) {
            double maxWidth = FLT_MAX;
            if (info.GetDoubleArg(3, maxWidth)) {
                maxWidth *= density;
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
    ContainerScope scope(instanceId_);
    double density = GetDensity();
    if (info.GetStringArg(0, textInfo.text) && info.GetDoubleArg(1, textInfo.x) && info.GetDoubleArg(2, textInfo.y)) {
        textInfo.x *= density;
        textInfo.y *= density;
        if (info.Length() >= 4) {
            double maxWidth = FLT_MAX;
            if (info.GetDoubleArg(3, maxWidth)) {
                maxWidth *= density;
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

// font: string
void JSCanvasRenderer::JsSetFont(const JSCallbackInfo& info)
{
    std::string fontStr;
    if (!info.GetStringArg(0, fontStr)) {
        return;
    }
    ContainerScope scope(instanceId_);
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

void JSCanvasRenderer::JsGetLineDash(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    std::vector<double> lineDash = renderingContext2DModel_->GetLineDash();
    JSRef<JSObject> lineDashObj = JSRef<JSObject>::New();
    double density = GetDensity();
    for (auto i = 0U; i < lineDash.size(); i++) {
        lineDash[i] *= density;
        lineDashObj->SetProperty<double>(std::to_string(i).c_str(), lineDash[i]);
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
        Gradient* gradient = jSCanvasGradient->GetGradient();
        CHECK_NULL_VOID(gradient);
        renderingContext2DModel_->SetFillGradient(*gradient);
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
        Gradient* gradient = jSCanvasGradient->GetGradient();
        CHECK_NULL_VOID(gradient);
        renderingContext2DModel_->SetStrokeGradient(*gradient);
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

// drawImage(image: ImageBitmap | PixelMap, dx: number, dy: number): void
// drawImage(image: ImageBitmap | PixelMap, dx: number, dy: number, dw: number, dh: number): void
// drawImage(image: ImageBitmap | PixelMap, sx: number, sy: number, sw: number, sh: number, dx: number,
//           dy: number, dw: number, dh: number):void
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
            if (isImage) {
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
    std::string repeat;
    auto arg0 = info[0];
    if (arg0->IsObject() && info.GetStringArg(1, repeat)) {
        JSRenderImage* jsImage = UnwrapNapiImage(info[0]);
        CHECK_NULL_VOID(jsImage);
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
    ContainerScope scope(instanceId_);
    double density = GetDensity();
    double fWidth = 0.0;
    double fHeight = 0.0;
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

// putImageData(imageData: ImageData, dx: number | string, dy: number | string): void
// putImageData(imageData: ImageData, dx: number | string, dy: number | string, dirtyX: number | string,
//              dirtyY: number | string, dirtyWidth: number | string, dirtyHeight: number | string): void
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
    double density = GetDensity();
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
        imageData.x *= density;
    }
    if (info[2]->IsString()) {
        std::string imageDataYStr = "";
        JSViewAbstract::ParseJsString(info[2], imageDataYStr);
        value = GetDimensionValue(imageDataYStr);
        imageData.y = value.Value();
    } else {
        ParseJsInt(info[2], imageData.y);
        imageData.y *= density;
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
    double density = GetDensity();
    Dimension value;
    if (info[3]->IsString()) {
        std::string imageDataDirtyXStr = "";
        JSViewAbstract::ParseJsString(info[3], imageDataDirtyXStr);
        value = GetDimensionValue(imageDataDirtyXStr);
        imageData.dirtyX = value.Value();
    } else {
        ParseJsInt(info[3], imageData.dirtyX);
        imageData.dirtyX *= density;
    }
    if (info[4]->IsString()) {
        std::string imageDataDirtyYStr = "";
        JSViewAbstract::ParseJsString(info[4], imageDataDirtyYStr);
        value = GetDimensionValue(imageDataDirtyYStr);
        imageData.dirtyY = value.Value();
    } else {
        ParseJsInt(info[4], imageData.dirtyY);
        imageData.dirtyY *= density;
    }
    if (info[5]->IsString()) {
        std::string imageDataDirtWidth = "";
        JSViewAbstract::ParseJsString(info[5], imageDataDirtWidth);
        value = GetDimensionValue(imageDataDirtWidth);
        imageData.dirtyWidth = value.Value();
    } else {
        ParseJsInt(info[5], imageData.dirtyWidth);
        imageData.dirtyWidth *= density;
    }
    if (info[6]->IsString()) {
        std::string imageDataDirtyHeight = "";
        JSViewAbstract::ParseJsString(info[6], imageDataDirtyHeight);
        value = GetDimensionValue(imageDataDirtyHeight);
        imageData.dirtyHeight = value.Value();
    } else {
        ParseJsInt(info[6], imageData.dirtyHeight);
        imageData.dirtyHeight *= density;
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
    ContainerScope scope(instanceId_);
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

    uint32_t finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    uint32_t finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    int32_t length = finalHeight * finalWidth * 4;
    JSRef<JSArrayBuffer> arrayBuffer = JSRef<JSArrayBuffer>::New(length);
    auto* buffer = static_cast<uint8_t*>(arrayBuffer->GetBuffer());
    renderingContext2DModel_->GetImageDataModel(imageSize, buffer);
    auto colorArray = JSRef<JSUint8ClampedArray>::New(arrayBuffer->GetLocalHandle(), 0, arrayBuffer->ByteLength());

    auto retObj = JSRef<JSObject>::New();
    retObj->SetProperty("width", finalWidth);
    retObj->SetProperty("height", finalHeight);
    retObj->SetPropertyObject("data", colorArray);
    info.SetReturnValue(retObj);
}

// getPixelMap(sx: number, sy: number, sw: number, sh: number): PixelMap
void JSCanvasRenderer::JsGetPixelMap(const JSCallbackInfo& info)
{
#ifdef PIXEL_MAP_SUPPORTED
    ContainerScope scope(instanceId_);
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
#if !defined(PREVIEW)
    if (info[0]->IsObject()) {
        ImageInfo imageInfo;
        imageInfo.pixelMap = CreatePixelMapFromNapiValue(info[0]);
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
    bitmapMeshInfo.pool = canvasPattern_;
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
    if (info.GetDoubleArg(0, alpha)) {
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
    if (info.GetDoubleArg(0, lineDashOffset)) {
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
    if (info.GetStringArg(0, colorStr)) {
        renderingContext2DModel_->SetShadowColor(Color::FromString(colorStr));
    }
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
        renderingContext2DModel_->SetShadowOffsetX(offsetY * GetDensity());
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
    if (info.GetDoubleArg(0, x) && info.GetDoubleArg(1, y)) {
        ContainerScope scope(instanceId_);
        double density = GetDensity();
        renderingContext2DModel_->MoveTo(x * density, y * density);
    }
}

// lineTo(x: number, y: number): void
void JSCanvasRenderer::JsLineTo(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    if (info.GetDoubleArg(0, x) && info.GetDoubleArg(1, y)) {
        ContainerScope scope(instanceId_);
        double density = GetDensity();
        renderingContext2DModel_->LineTo(x * density, y * density);
    }
}

// bezierCurveTo(cp1x: number, cp1y: number, cp2x: number, cp2y: number, x: number, y: number): void
void JSCanvasRenderer::JsBezierCurveTo(const JSCallbackInfo& info)
{
    BezierCurveParam param;
    if (info.GetDoubleArg(0, param.cp1x) && info.GetDoubleArg(1, param.cp1y) && info.GetDoubleArg(2, param.cp2x) &&
        info.GetDoubleArg(3, param.cp2y) && info.GetDoubleArg(4, param.x) && info.GetDoubleArg(5, param.y)) {
        ContainerScope scope(instanceId_);
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
    if (info.GetDoubleArg(0, param.cpx) && info.GetDoubleArg(1, param.cpy) && info.GetDoubleArg(2, param.x) &&
        info.GetDoubleArg(3, param.y)) {
        ContainerScope scope(instanceId_);
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
    if (info.GetDoubleArg(0, param.x1) && info.GetDoubleArg(1, param.y1) && info.GetDoubleArg(2, param.x2) &&
        info.GetDoubleArg(3, param.y2) && info.GetDoubleArg(4, param.radius)) {
        ContainerScope scope(instanceId_);
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
    if (info.GetDoubleArg(0, param.x) && info.GetDoubleArg(1, param.y) && info.GetDoubleArg(2, param.radius) &&
        info.GetDoubleArg(3, param.startAngle) && info.GetDoubleArg(4, param.endAngle)) {
        info.GetBooleanArg(5, param.anticlockwise); // Non mandatory parameter with default value 'false'
        ContainerScope scope(instanceId_);
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
    if (info.GetDoubleArg(0, param.x) && info.GetDoubleArg(1, param.y) && info.GetDoubleArg(2, param.radiusX) &&
        info.GetDoubleArg(3, param.radiusY) && info.GetDoubleArg(4, param.rotation) &&
        info.GetDoubleArg(5, param.startAngle) && info.GetDoubleArg(6, param.endAngle)) {
        info.GetBooleanArg(7, param.anticlockwise); // Non mandatory parameter with default value 'false'
        ContainerScope scope(instanceId_);
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
    if (info.GetDoubleArg(0, x) && info.GetDoubleArg(1, y) && info.GetDoubleArg(2, width) &&
        info.GetDoubleArg(3, height)) {
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
    renderingContext2DModel_->Restore();
}

// save(): void
void JSCanvasRenderer::JsSave(const JSCallbackInfo& info)
{
    renderingContext2DModel_->CanvasRendererSave();
}

// rotate(angle: number): void
void JSCanvasRenderer::JsRotate(const JSCallbackInfo& info)
{
    double angle = 0.0;
    info.GetDoubleArg(0, angle);
    renderingContext2DModel_->CanvasRendererRotate(angle);
}

// scale(x: number, y: number): void
void JSCanvasRenderer::JsScale(const JSCallbackInfo& info)
{
    double x = 0.0;
    double y = 0.0;
    if (info.GetDoubleArg(0, x) && info.GetDoubleArg(1, y)) {
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
    ContainerScope scope(instanceId_);
    double density = GetDensity();
    TransformParam param;
    // setTransform(a: number, b: number, c: number, d: number, e: number, f: number): void
    if (info.GetDoubleArg(0, param.scaleX) && info.GetDoubleArg(1, param.skewY) && info.GetDoubleArg(2, param.skewX) &&
        info.GetDoubleArg(3, param.scaleY) && info.GetDoubleArg(4, param.translateX) &&
        info.GetDoubleArg(5, param.translateY)) {
        param.translateX *= density;
        param.translateY *= density;
        renderingContext2DModel_->SetTransform(param, true);
        return;
    }

    // >= API10: setTransform(transform?: Matrix2D): void
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
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
    if (info.GetDoubleArg(0, param.scaleX) && info.GetDoubleArg(1, param.skewX) && info.GetDoubleArg(2, param.skewY) &&
        info.GetDoubleArg(3, param.scaleY) && info.GetDoubleArg(4, param.translateX) &&
        info.GetDoubleArg(5, param.translateY)) {
        ContainerScope scope(instanceId_);
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
    if (info.GetDoubleArg(0, x) && info.GetDoubleArg(1, y)) {
        ContainerScope scope(instanceId_);
        double density = GetDensity();
        renderingContext2DModel_->Translate(x * density, y * density);
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
    double density = GetDensity();
    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
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
        pattern_[id]->SetScaleX(transform.scaleX);
        pattern_[id]->SetScaleY(transform.scaleY);
        pattern_[id]->SetSkewX(transform.skewX);
        pattern_[id]->SetSkewY(transform.skewY);
        pattern_[id]->SetTranslateX(transform.translateX);
        pattern_[id]->SetTranslateY(transform.translateY);
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
        style_.SetTextBaseline(baseline);
        renderingContext2DModel_->SetTextBaseline(baseline);
    }
}

// measureText(text: string): TextMetrics
void JSCanvasRenderer::JsMeasureText(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    std::string text;
    paintState_.SetTextStyle(style_);
    double density = GetDensity();
    if (Positive(density) && info.GetStringArg(0, text)) {
        double width = renderingContext2DModel_->GetMeasureTextWidth(paintState_, text);
        double height = renderingContext2DModel_->GetMeasureTextHeight(paintState_, text);
        TextMetrics textMetrics = renderingContext2DModel_->GetMeasureTextMetrics(paintState_, text);
        auto retObj = JSRef<JSObject>::New();
        retObj->SetProperty("width", width / density);
        retObj->SetProperty("height", height / density);
        retObj->SetProperty("actualBoundingBoxLeft", textMetrics.actualBoundingBoxLeft / density);
        retObj->SetProperty("actualBoundingBoxRight", textMetrics.actualBoundingBoxRight / density);
        retObj->SetProperty("actualBoundingBoxAscent", textMetrics.actualBoundingBoxAscent / density);
        retObj->SetProperty("actualBoundingBoxDescent", textMetrics.actualBoundingBoxDescent / density);
        retObj->SetProperty("hangingBaseline", textMetrics.hangingBaseline / density);
        retObj->SetProperty("alphabeticBaseline", textMetrics.alphabeticBaseline / density);
        retObj->SetProperty("ideographicBaseline", textMetrics.ideographicBaseline / density);
        retObj->SetProperty("emHeightAscent", textMetrics.emHeightAscent / density);
        retObj->SetProperty("emHeightDescent", textMetrics.emHeightDescent / density);
        retObj->SetProperty("fontBoundingBoxAscent", textMetrics.fontBoundingBoxAscent / density);
        retObj->SetProperty("fontBoundingBoxDescent", textMetrics.fontBoundingBoxDescent / density);
        info.SetReturnValue(retObj);
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

// Abandoned
void JSCanvasRenderer::JsSaveLayer(const JSCallbackInfo& info)
{
    renderingContext2DModel_->SaveLayer();
}

// Abandoned
void JSCanvasRenderer::JsRestoreLayer(const JSCallbackInfo& info)
{
    renderingContext2DModel_->RestoreLayer();
}

// reset(): void
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
