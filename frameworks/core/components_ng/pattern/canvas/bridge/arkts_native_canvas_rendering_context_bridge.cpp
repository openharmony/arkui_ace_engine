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
#include "frameworks/core/components_ng/pattern/canvas/bridge/arkts_native_canvas_rendering_context_bridge.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include <cmath>
#include <unordered_set>
#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/common/dynamic_module_helper.h"
#include "core/interfaces/native/node/canvas_rendering_context_2d_modifier.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

#include "bridge/declarative_frontend/jsview/canvas/js_canvas_gradient.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_path.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_pattern.h"

namespace OHOS::Ace::NG {
namespace {

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm)) {
        return true;
    }
    if (firstArg->IsObject(vm)) {
        auto object = firstArg->ToObject(vm);
        auto nativeNodeValue = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "__canvasNativeNode__"));
        if (nativeNodeValue->IsNativePointer(vm)) {
            nativeNode = reinterpret_cast<ArkUINodeHandle>(nativeNodeValue->ToNativePointer(vm)->Value());
            return true;
        }
    }
    return false;
}

RefPtr<NG::CanvasPattern> GetCanvasPattern(ArkUINodeHandle nativeNode)
{
    auto* frameNode = nativeNode ? reinterpret_cast<FrameNode*>(nativeNode)
                                 : ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    return AceType::DynamicCast<NG::CanvasPattern>(pattern);
}

const ArkUICanvasRenderingContext2DModifier* GetModifier()
{
    static const ArkUICanvasRenderingContext2DModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Canvas");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUICanvasRenderingContext2DModifier*>(
            module->GetCustomModifier("CanvasRenderingContext2D"));
    }
    return cachedModifier;
}

double GetDensity()
{
    return PipelineBase::GetCurrentDensity();
}

// Validate a numeric argument: returns false if the arg is missing, NaN, or Infinity.
// Mirrors the old JSCanvasRenderer's GetDoubleArg(..., isJudgeSpecialValue_) behavior
// which was enabled for API >= 18.
bool GetValidDoubleArg(ArkUIRuntimeCallInfo* runtimeCallInfo, size_t index, double& value)
{
    auto arg = runtimeCallInfo->GetCallArgRef(index);
    if (arg->IsUndefined() || arg->IsNull()) {
        return false;
    }
    value = arg->ToNumber(runtimeCallInfo->GetVM())->Value();
    if (std::isnan(value) || std::isinf(value)) {
        return false;
    }
    return true;
}

// Read the C++ binding pointer from internal field 0 of a Panda ObjectRef.
template<typename T>
T* UnwrapNativePointer(EcmaVM* vm, const Local<panda::ObjectRef>& obj)
{
    if (obj->GetNativePointerFieldCount(vm) < 1) {
        return nullptr;
    }
    return static_cast<T*>(obj->GetNativePointerField(vm, 0));
}

constexpr uint32_t GRADIENT_TYPE = 0;
constexpr uint32_t PATTERN_TYPE = 1;

bool UpdateFontWeightFromProp(const std::string& fontProp, RefPtr<NG::CanvasPattern>& pattern)
{
    static const std::unordered_set<std::string> weightKeywords = {
        "normal", "bold", "lighter", "bolder",
        "100", "200", "300", "400", "500", "600", "700", "800", "900"
    };
    if (weightKeywords.find(fontProp) != weightKeywords.end()) {
        pattern->UpdateFontWeight(Framework::ConvertStrToFontWeight(fontProp));
        return true;
    }
    return false;
}

bool UpdateFontStyleFromProp(const std::string& fontProp, RefPtr<NG::CanvasPattern>& pattern)
{
    if (fontProp == "italic" || fontProp == "oblique") {
        pattern->UpdateFontStyle(Framework::ConvertStrToFontStyle(fontProp));
        return true;
    }
    return false;
}

bool UpdateFontFamilyFromProp(const std::string& fontProp, RefPtr<NG::CanvasPattern>& pattern)
{
    if (fontProp == "sans-serif" || fontProp == "serif" || fontProp == "monospace" ||
        fontProp.find('\"') != std::string::npos || fontProp.find('\'') != std::string::npos) {
        auto families = Framework::ConvertStrToFontFamilies(fontProp);
        pattern->UpdateFontFamilies(families);
        return true;
    }
    return false;
}

bool UpdateFontSizeFromProp(const std::string& fontProp, RefPtr<NG::CanvasPattern>& pattern)
{
    if (fontProp.find("px") != std::string::npos || fontProp.find("vp") != std::string::npos) {
        Dimension size;
        if (fontProp.find("vp") != std::string::npos) {
            size = StringUtils::StringToDimension(fontProp);
        } else {
            size = Dimension(StringUtils::StringToDouble(fontProp));
        }
        pattern->UpdateFontSize(size);
        return true;
    }
    return false;
}

void ApplyFillStyleObject(EcmaVM* vm, const Local<panda::ObjectRef>& obj, ArkUINodeHandle nativeNode)
{
    auto typeVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "__type"));
    if (!typeVal->IsNumber()) {
        return;
    }
    auto canvasPattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_VOID(canvasPattern);
    auto type = typeVal->ToNumber(vm)->Value();
    if (type == GRADIENT_TYPE) {
        auto* jsGradient = UnwrapNativePointer<Framework::JSCanvasGradient>(vm, obj);
        if (jsGradient != nullptr) {
            canvasPattern->SetFillGradient(jsGradient->GetGradient());
        }
    } else if (type == PATTERN_TYPE) {
        auto* jsPattern = UnwrapNativePointer<Framework::JSCanvasPattern>(vm, obj);
        if (jsPattern != nullptr) {
            canvasPattern->UpdateFillPattern(jsPattern->GetPattern());
        }
    }
}

void ApplyStrokeStyleObject(EcmaVM* vm, const Local<panda::ObjectRef>& obj, ArkUINodeHandle nativeNode)
{
    auto typeVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "__type"));
    if (!typeVal->IsNumber()) {
        return;
    }
    auto canvasPattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_VOID(canvasPattern);
    auto type = typeVal->ToNumber(vm)->Value();
    if (type == GRADIENT_TYPE) {
        auto* jsGradient = UnwrapNativePointer<Framework::JSCanvasGradient>(vm, obj);
        if (jsGradient != nullptr) {
            canvasPattern->SetStrokeGradient(jsGradient->GetGradient());
        }
    } else if (type == PATTERN_TYPE) {
        auto* jsPattern = UnwrapNativePointer<Framework::JSCanvasPattern>(vm, obj);
        if (jsPattern != nullptr) {
            canvasPattern->UpdateStrokePattern(jsPattern->GetPattern());
        }
    }
}

void CopyPixelsToImageData(const uint8_t* buffer, int32_t bufferLength, int32_t imgWidth,
    Ace::ImageData& imageData)
{
    imageData.data = std::vector<uint32_t>();
    constexpr int32_t redIdx = 0;
    constexpr int32_t greenIdx = 1;
    constexpr int32_t blueIdx = 2;
    constexpr int32_t alphaIdx = 3;
    for (int32_t i = std::max(imageData.dirtyY, 0); i < imageData.dirtyY + imageData.dirtyHeight; ++i) {
        for (int32_t j = std::max(imageData.dirtyX, 0); j < imageData.dirtyX + imageData.dirtyWidth; ++j) {
            uint32_t idx = static_cast<uint32_t>(4 * (j + imgWidth * i));
            if (bufferLength > static_cast<int32_t>(idx + alphaIdx)) {
                uint8_t red = buffer[idx + redIdx];
                uint8_t green = buffer[idx + greenIdx];
                uint8_t blue = buffer[idx + blueIdx];
                uint8_t alpha = buffer[idx + alphaIdx];
                imageData.data.emplace_back(Color::FromARGB(alpha, red, green, blue).GetValue());
            }
        }
    }
}
} // namespace

namespace {
constexpr size_t NUM_0 = 0;
constexpr size_t NUM_1 = 1;
constexpr size_t NUM_2 = 2;
constexpr size_t NUM_3 = 3;
constexpr size_t NUM_4 = 4;
constexpr size_t NUM_5 = 5;
constexpr size_t NUM_6 = 6;
constexpr size_t NUM_7 = 7;
constexpr size_t NUM_8 = 8;

void ParsePutImageDataCoords(ArkUIRuntimeCallInfo* runtimeCallInfo,
    Ace::ImageData& imageData, int32_t imgWidth, int32_t imgHeight)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    double density = GetDensity();
    auto parseCoord = [&runtimeCallInfo, &vm, &density](size_t idx, int32_t& out) {
        auto arg = runtimeCallInfo->GetCallArgRef(idx);
        if (arg->IsNumber()) {
            double v = arg->ToNumber(vm)->Value();
            if (!std::isnan(v) && !std::isinf(v)) {
                out = static_cast<int32_t>(v * density);
            }
        }
    };
    parseCoord(NUM_2, imageData.x);
    parseCoord(NUM_3, imageData.y);
    parseCoord(NUM_4, imageData.dirtyX);
    parseCoord(NUM_5, imageData.dirtyY);
    parseCoord(NUM_6, imageData.dirtyWidth);
    parseCoord(NUM_7, imageData.dirtyHeight);
    // Clamp dirty region
    imageData.dirtyWidth = imageData.dirtyX < 0 ? std::min(imageData.dirtyX + imageData.dirtyWidth, imgWidth)
                                                : std::min(imgWidth - imageData.dirtyX, imageData.dirtyWidth);
    imageData.dirtyHeight = imageData.dirtyY < 0 ? std::min(imageData.dirtyY + imageData.dirtyHeight, imgHeight)
                                                 : std::min(imgHeight - imageData.dirtyY, imageData.dirtyHeight);
}
} // namespace

namespace {
using Canvas2DFunc = ArkUINativeModuleValue (*)(ArkUIRuntimeCallInfo*);
struct Canvas2DEntry { const char* name; Canvas2DFunc func; };
const Canvas2DEntry CANVAS2D_ENTRIES[] = {
    { "beginPath", CanvasRenderingContext2DBridge::BeginPath },
    { "closePath", CanvasRenderingContext2DBridge::ClosePath },
    { "moveTo", CanvasRenderingContext2DBridge::MoveTo },
    { "lineTo", CanvasRenderingContext2DBridge::LineTo },
    { "bezierCurveTo", CanvasRenderingContext2DBridge::BezierCurveTo },
    { "quadraticCurveTo", CanvasRenderingContext2DBridge::QuadraticCurveTo },
    { "arc", CanvasRenderingContext2DBridge::Arc },
    { "arcTo", CanvasRenderingContext2DBridge::ArcTo },
    { "ellipse", CanvasRenderingContext2DBridge::Ellipse },
    { "rect", CanvasRenderingContext2DBridge::Rect },
    { "roundRect", CanvasRenderingContext2DBridge::RoundRect },
    { "fill", CanvasRenderingContext2DBridge::Fill },
    { "stroke", CanvasRenderingContext2DBridge::Stroke },
    { "clip", CanvasRenderingContext2DBridge::Clip },
    { "fillRect", CanvasRenderingContext2DBridge::FillRect },
    { "strokeRect", CanvasRenderingContext2DBridge::StrokeRect },
    { "clearRect", CanvasRenderingContext2DBridge::ClearRect },
    { "fillStyle", CanvasRenderingContext2DBridge::FillStyle },
    { "strokeStyle", CanvasRenderingContext2DBridge::StrokeStyle },
    { "lineWidth", CanvasRenderingContext2DBridge::LineWidth },
    { "lineCap", CanvasRenderingContext2DBridge::LineCap },
    { "lineJoin", CanvasRenderingContext2DBridge::LineJoin },
    { "miterLimit", CanvasRenderingContext2DBridge::MiterLimit },
    { "font", CanvasRenderingContext2DBridge::Font },
    { "textAlign", CanvasRenderingContext2DBridge::TextAlign },
    { "textBaseline", CanvasRenderingContext2DBridge::TextBaseline },
    { "globalAlpha", CanvasRenderingContext2DBridge::GlobalAlpha },
    { "globalCompositeOperation", CanvasRenderingContext2DBridge::GlobalCompositeOperation },
    { "shadowBlur", CanvasRenderingContext2DBridge::ShadowBlur },
    { "shadowColor", CanvasRenderingContext2DBridge::ShadowColor },
    { "shadowOffsetX", CanvasRenderingContext2DBridge::ShadowOffsetX },
    { "shadowOffsetY", CanvasRenderingContext2DBridge::ShadowOffsetY },
    { "filter", CanvasRenderingContext2DBridge::Filter },
    { "direction", CanvasRenderingContext2DBridge::Direction },
    { "imageSmoothingEnabled", CanvasRenderingContext2DBridge::ImageSmoothingEnabled },
    { "imageSmoothingQuality", CanvasRenderingContext2DBridge::ImageSmoothingQuality },
    { "letterSpacing", CanvasRenderingContext2DBridge::LetterSpacing },
    { "lineDashOffset", CanvasRenderingContext2DBridge::LineDashOffset },
    { "antiAlias", CanvasRenderingContext2DBridge::AntiAlias },
    { "save", CanvasRenderingContext2DBridge::Save },
    { "restore", CanvasRenderingContext2DBridge::Restore },
    { "scale", CanvasRenderingContext2DBridge::Scale },
    { "rotate", CanvasRenderingContext2DBridge::Rotate },
    { "translate", CanvasRenderingContext2DBridge::Translate },
    { "transform", CanvasRenderingContext2DBridge::Transform },
    { "setTransform", CanvasRenderingContext2DBridge::SetTransform },
    { "resetTransform", CanvasRenderingContext2DBridge::ResetTransform },
    { "reset", CanvasRenderingContext2DBridge::Reset },
    { "fillText", CanvasRenderingContext2DBridge::FillText },
    { "strokeText", CanvasRenderingContext2DBridge::StrokeText },
    { "setLineDash", CanvasRenderingContext2DBridge::SetLineDash },
    { "saveLayer", CanvasRenderingContext2DBridge::SaveLayer },
    { "restoreLayer", CanvasRenderingContext2DBridge::RestoreLayer },
    // drawImage / transferFromImageBitmap are excluded —
    // they need JSRenderImage methods which are in libarkts_frontend.z.so,
    // not linked into libarkui_canvas.z.so. JS parsing & runtime bridge
    // calls happen in js_canvas_renderer.cpp / js_rendering_context.cpp.
    // startImageAnalyzer: excluded — requires NAPI promise/callback infra.
    { "putImageData", CanvasRenderingContext2DBridge::PutImageData },
    { "stopImageAnalyzer", CanvasRenderingContext2DBridge::StopImageAnalyzer },
};
} // namespace

void CanvasRenderingContext2DBridge::RegisterCanvasRenderingContext2DAttributes(
    Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto ctx2d = panda::ObjectRef::New(vm);
    for (auto& e : CANVAS2D_ENTRIES) {
        ctx2d->Set(vm, panda::StringRef::NewFromUtf8(vm, e.name),
            panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), e.func));
    }
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "CanvasRenderingContext2D"), ctx2d);
}

// ── Path methods ──

ArkUINativeModuleValue CanvasRenderingContext2DBridge::BeginPath(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* modifier = GetModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    modifier->setCanvasBeginPath(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::ClosePath(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* modifier = GetModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    modifier->setCanvasClosePath(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::MoveTo(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* modifier = GetModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    double xVal = 0.0;
    double yVal = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, xVal) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, yVal)) {
        return panda::JSValueRef::Undefined(vm);
    }
    float x = static_cast<float>(xVal * density);
    float y = static_cast<float>(yVal * density);
    modifier->setCanvasMoveTo(nativeNode, x, y);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::LineTo(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* modifier = GetModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    double xVal = 0.0;
    double yVal = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, xVal) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, yVal)) {
        return panda::JSValueRef::Undefined(vm);
    }
    float x = static_cast<float>(xVal * density);
    float y = static_cast<float>(yVal * density);
    modifier->setCanvasLineTo(nativeNode, x, y);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::BezierCurveTo(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    BezierCurveParam param;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, param.cp1x) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_2, param.cp1y) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, param.cp2x) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_4, param.cp2y) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_5, param.x) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_6, param.y)) {
        return panda::JSValueRef::Undefined(vm);
    }
    param.cp1x *= density;
    param.cp1y *= density;
    param.cp2x *= density;
    param.cp2y *= density;
    param.x *= density;
    param.y *= density;
    pattern->BezierCurveTo(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::QuadraticCurveTo(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    QuadraticCurveParam param;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, param.cpx) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_2, param.cpy) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, param.x) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_4, param.y)) {
        return panda::JSValueRef::Undefined(vm);
    }
    param.cpx *= density;
    param.cpy *= density;
    param.x *= density;
    param.y *= density;
    pattern->QuadraticCurveTo(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Arc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* modifier = GetModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    ArkUICanvasArcOptions options;
    double xVal = 0.0;
    double yVal = 0.0;
    double radiusVal = 0.0;
    double startAngleVal = 0.0;
    double endAngleVal = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, xVal) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_2, yVal) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, radiusVal) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_4, startAngleVal) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_5, endAngleVal)) {
        return panda::JSValueRef::Undefined(vm);
    }
    options.x = static_cast<float>(xVal * density);
    options.y = static_cast<float>(yVal * density);
    options.radius = static_cast<float>(radiusVal * density);
    options.startAngle = static_cast<float>(startAngleVal);
    options.endAngle = static_cast<float>(endAngleVal);
    auto lastArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    options.counterclockwise = lastArg->IsBoolean() && lastArg->ToBoolean(vm)->Value();
    modifier->setCanvasArc(nativeNode, &options);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::ArcTo(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    ArcToParam param;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, param.x1) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_2, param.y1) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, param.x2) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_4, param.y2) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_5, param.radius)) {
        return panda::JSValueRef::Undefined(vm);
    }
    param.x1 *= density;
    param.y1 *= density;
    param.x2 *= density;
    param.y2 *= density;
    param.radius *= density;
    pattern->ArcTo(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Ellipse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    EllipseParam param;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, param.x) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_2, param.y) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, param.radiusX) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_4, param.radiusY) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_5, param.rotation) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_6, param.startAngle) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_7, param.endAngle)) {
        return panda::JSValueRef::Undefined(vm);
    }
    param.x *= density;
    param.y *= density;
    param.radiusX *= density;
    param.radiusY *= density;
    auto lastArg = runtimeCallInfo->GetCallArgRef(NUM_8);
    param.anticlockwise = lastArg->IsBoolean() && lastArg->ToBoolean(vm)->Value();
    pattern->Ellipse(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Rect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    double x = 0.0;
    double y = 0.0;
    double w = 0.0;
    double h = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, w) || !GetValidDoubleArg(runtimeCallInfo, NUM_4, h)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->AddRect(OHOS::Ace::Rect(x * density, y * density, w * density, h * density));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::RoundRect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    double x = 0.0;
    double y = 0.0;
    double w = 0.0;
    double h = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, w) || !GetValidDoubleArg(runtimeCallInfo, NUM_4, h)) {
        return panda::JSValueRef::Undefined(vm);
    }
    // Radius: single number or array of up to 4 values
    std::vector<double> radii;
    auto radiusArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    if (radiusArg->IsArray(vm)) {
        Local<panda::ArrayRef> arr(radiusArg);
        size_t arrLen = ArkTSUtils::GetArrayLength(vm, arr);
    constexpr size_t ROUND_RECT_CORNER_COUNT = 4;
        for (size_t i = 0; i < arrLen && i < ROUND_RECT_CORNER_COUNT; ++i) {
            double r = arr->Get(vm, i)->ToNumber(vm)->Value();
            if (std::isnan(r) || std::isinf(r)) {
                return panda::JSValueRef::Undefined(vm);
            }
            radii.push_back(r * density);
        }
    } else if (radiusArg->IsNumber()) {
        double r = radiusArg->ToNumber(vm)->Value();
        if (std::isnan(r) || std::isinf(r)) {
            return panda::JSValueRef::Undefined(vm);
        }
        radii = { r * density, r * density, r * density, r * density };
    }
    if (radii.empty()) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->AddRoundRect(OHOS::Ace::Rect(x * density, y * density, w * density, h * density), radii);
    return panda::JSValueRef::Undefined(vm);
}

// ── Fill / Stroke / Clip ──

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Fill(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    // Check if arg is a Path2D object (native pointer)
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto* jsPath = arg->IsObject(vm) ? UnwrapNativePointer<Framework::JSCanvasPath>(vm, arg->ToObject(vm)) : nullptr;
    if (jsPath != nullptr) {
        auto pattern = GetCanvasPattern(nativeNode);
        CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
        auto path = jsPath->GetCanvasPath2d();
        CanvasFillRule fillRule = CanvasFillRule::NONZERO;
        auto ruleArg = runtimeCallInfo->GetCallArgRef(NUM_2);
        if (!ruleArg->IsUndefined() && !ruleArg->IsNull()) {
            std::string ruleStr = ruleArg->ToString(vm)->ToString(vm);
            if (ruleStr == "evenodd") {
                fillRule = CanvasFillRule::EVENODD;
            }
        }
        pattern->UpdateFillRuleForPath2D(fillRule);
        pattern->Fill(path);
        return panda::JSValueRef::Undefined(vm);
    }
    // fill(fillRule?: CanvasFillRule) string overload
    auto* modifier = GetModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> fillRuleArg = arg;
    std::string rule("nonzero");
    if (!fillRuleArg->IsUndefined() && !fillRuleArg->IsNull()) {
        rule = fillRuleArg->ToString(vm)->ToString(vm);
    }
    modifier->setCanvasFill(nativeNode, rule.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Stroke(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    // Check if arg is a Path2D object
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto* jsPath = arg->IsObject(vm) ? UnwrapNativePointer<Framework::JSCanvasPath>(vm, arg->ToObject(vm)) : nullptr;
    if (jsPath != nullptr) {
        auto pattern = GetCanvasPattern(nativeNode);
        CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
        pattern->Stroke(jsPath->GetCanvasPath2d());
        return panda::JSValueRef::Undefined(vm);
    }
    // stroke() no-arg overload
    auto* modifier = GetModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    modifier->setCanvasStroke(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Clip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    // Check if arg is a Path2D object
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto* jsPath = arg->IsObject(vm) ? UnwrapNativePointer<Framework::JSCanvasPath>(vm, arg->ToObject(vm)) : nullptr;
    if (jsPath != nullptr) {
        auto path = jsPath->GetCanvasPath2d();
        CanvasFillRule fillRule = CanvasFillRule::NONZERO;
        auto ruleArg = runtimeCallInfo->GetCallArgRef(NUM_2);
        if (!ruleArg->IsUndefined() && !ruleArg->IsNull()) {
            std::string ruleStr = ruleArg->ToString(vm)->ToString(vm);
            if (ruleStr == "evenodd") {
                fillRule = CanvasFillRule::EVENODD;
            }
        }
        pattern->UpdateFillRuleForPath2D(fillRule);
        pattern->Clip(path);
        return panda::JSValueRef::Undefined(vm);
    }
    // clip() / clip(fillRule) no-arg overload
    pattern->Clip();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::FillRect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* modifier = GetModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    double xVal = 0.0;
    double yVal = 0.0;
    double wVal = 0.0;
    double hVal = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, xVal) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, yVal) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, wVal) || !GetValidDoubleArg(runtimeCallInfo, NUM_4, hVal)) {
        return panda::JSValueRef::Undefined(vm);
    }
    float x = static_cast<float>(xVal * density);
    float y = static_cast<float>(yVal * density);
    float w = static_cast<float>(wVal * density);
    float h = static_cast<float>(hVal * density);
    modifier->setCanvasFillRect(nativeNode, x, y, w, h);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::StrokeRect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    double x = 0.0;
    double y = 0.0;
    double w = 0.0;
    double h = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, w) || !GetValidDoubleArg(runtimeCallInfo, NUM_4, h)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->StrokeRect(OHOS::Ace::Rect(x * density, y * density, w * density, h * density));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::ClearRect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    double x = 0.0;
    double y = 0.0;
    double w = 0.0;
    double h = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, w) || !GetValidDoubleArg(runtimeCallInfo, NUM_4, h)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->ClearRect(OHOS::Ace::Rect(x * density, y * density, w * density, h * density));
    return panda::JSValueRef::Undefined(vm);
}

// ── Properties ──

ArkUINativeModuleValue CanvasRenderingContext2DBridge::FillStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    // Try string color or uint32 color first (ParseJsColorAlpha handles both).
    Color color;
    if (ArkTSUtils::ParseJsColorAlpha(vm, valueArg, color)) {
        auto* modifier = GetModifier();
        CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
        modifier->setCanvasFillColor(nativeNode, color.GetValue());
        return panda::JSValueRef::Undefined(vm);
    }
    if (valueArg->IsObject(vm)) {
        ApplyFillStyleObject(vm, valueArg->ToObject(vm), nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::StrokeStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    // Try string color or uint32 color first (ParseJsColorAlpha handles both).
    Color color;
    if (ArkTSUtils::ParseJsColorAlpha(vm, valueArg, color)) {
        auto* modifier = GetModifier();
        CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
        modifier->setCanvasStrokeStyle(nativeNode, color.GetValue());
        return panda::JSValueRef::Undefined(vm);
    }
    if (valueArg->IsObject(vm)) {
        ApplyStrokeStyleObject(vm, valueArg->ToObject(vm), nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::LineWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* modifier = GetModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    double widthVal = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, widthVal)) {
        return panda::JSValueRef::Undefined(vm);
    }
    double density = GetDensity();
    modifier->setCanvasLineWidth(nativeNode, static_cast<float>(widthVal * density));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::LineCap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    std::string value;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), value, resObj);
    LineCapStyle style = LineCapStyle::BUTT;
    if (value == "round") style = LineCapStyle::ROUND;
    else if (value == "square") style = LineCapStyle::SQUARE;
    pattern->UpdateLineCap(style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::LineJoin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    std::string value;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), value, resObj);
    LineJoinStyle style = LineJoinStyle::MITER;
    if (value == "round") style = LineJoinStyle::ROUND;
    else if (value == "bevel") style = LineJoinStyle::BEVEL;
    pattern->UpdateLineJoin(style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::MiterLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double limit = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, limit)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (NearEqual(limit, 0.0)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->UpdateMiterLimit(limit);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Font(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    std::string fontStr;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), fontStr, resObj);
    if (fontStr.empty()) {
        return panda::JSValueRef::Undefined(vm);
    }
    // Parse CSS-like font string, e.g. "normal bold 12px sans-serif"
    std::vector<std::string> fontProps;
    StringUtils::StringSplitter(fontStr, ' ', fontProps);
    bool updateFontWeight = false;
    bool updateFontStyle = false;
    for (const auto& fontProp : fontProps) {
        if (UpdateFontWeightFromProp(fontProp, pattern)) {
            updateFontWeight = true;
        } else if (UpdateFontStyleFromProp(fontProp, pattern)) {
            updateFontStyle = true;
        } else if (UpdateFontFamilyFromProp(fontProp, pattern)) {
            continue;
        } else if (UpdateFontSizeFromProp(fontProp, pattern)) {
            continue;
        }
    }
    if (!updateFontStyle) {
        pattern->UpdateFontStyle(FontStyle::NORMAL);
    }
    if (!updateFontWeight) {
        pattern->UpdateFontWeight(FontWeight::NORMAL);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::TextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    std::string value;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), value, resObj);
    OHOS::Ace::TextAlign align = OHOS::Ace::TextAlign::START;
    if (value == "left") align = OHOS::Ace::TextAlign::LEFT;
    else if (value == "right") align = OHOS::Ace::TextAlign::RIGHT;
    else if (value == "center") align = OHOS::Ace::TextAlign::CENTER;
    else if (value == "end") align = OHOS::Ace::TextAlign::END;
    pattern->UpdateTextAlign(align);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::TextBaseline(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    std::string value;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), value, resObj);
    OHOS::Ace::TextBaseline baseline = OHOS::Ace::TextBaseline::ALPHABETIC;
    if (value == "top") baseline = OHOS::Ace::TextBaseline::TOP;
    else if (value == "middle") baseline = OHOS::Ace::TextBaseline::MIDDLE;
    else if (value == "bottom") baseline = OHOS::Ace::TextBaseline::BOTTOM;
    else if (value == "hanging") baseline = OHOS::Ace::TextBaseline::HANGING;
    else if (value == "ideographic") baseline = OHOS::Ace::TextBaseline::IDEOGRAPHIC;
    pattern->UpdateTextBaseline(baseline);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::GlobalAlpha(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* modifier = GetModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    double alphaVal = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, alphaVal)) {
        return panda::JSValueRef::Undefined(vm);
    }
    modifier->setCanvasGlobalAlpha(nativeNode, static_cast<float>(alphaVal));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::GlobalCompositeOperation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    std::string value;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), value, resObj);
    CompositeOperation op = CompositeOperation::SOURCE_OVER;
    if (value == "source-over") op = CompositeOperation::SOURCE_OVER;
    else if (value == "source-atop") op = CompositeOperation::SOURCE_ATOP;
    else if (value == "source-in") op = CompositeOperation::SOURCE_IN;
    else if (value == "source-out") op = CompositeOperation::SOURCE_OUT;
    else if (value == "destination-over") op = CompositeOperation::DESTINATION_OVER;
    else if (value == "destination-atop") op = CompositeOperation::DESTINATION_ATOP;
    else if (value == "destination-in") op = CompositeOperation::DESTINATION_IN;
    else if (value == "destination-out") op = CompositeOperation::DESTINATION_OUT;
    else if (value == "lighter") op = CompositeOperation::LIGHTER;
    else if (value == "copy") op = CompositeOperation::COPY;
    else if (value == "xor") op = CompositeOperation::XOR;
    pattern->UpdateCompositeOperation(op);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::ShadowBlur(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double blur = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, blur)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->UpdateShadowBlur(blur);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::ShadowColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Color color;
    if (ArkTSUtils::ParseJsColorAlpha(vm, valueArg, color)) {
        pattern->UpdateShadowColor(color);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::ShadowOffsetX(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double offsetX = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, offsetX)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->UpdateShadowOffsetX(offsetX * GetDensity());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::ShadowOffsetY(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double offsetY = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, offsetY)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->UpdateShadowOffsetY(offsetY * GetDensity());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Filter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    std::string filterStr;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), filterStr, resObj);
    pattern->SetFilterParam(filterStr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Direction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    std::string value;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), value, resObj);
    TextDirection dir = TextDirection::LTR;
    if (value == "rtl") dir = TextDirection::RTL;
    pattern->SetTextDirection(dir);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::ImageSmoothingEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    bool enabled = runtimeCallInfo->GetCallArgRef(NUM_1)->ToBoolean(vm)->Value();
    pattern->UpdateSmoothingEnabled(enabled);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::ImageSmoothingQuality(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    std::string value;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), value, resObj);
    if (value != "low" && value != "medium" && value != "high") {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->UpdateSmoothingQuality(value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::LetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    std::string value;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), value, resObj);
    pattern->UpdateLetterSpacing(StringUtils::StringToDimension(value));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::LineDashOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double dash = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, dash)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->UpdateLineDashOffset(dash * GetDensity());
    pattern->UpdateLineDashOffset(dash);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::AntiAlias(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* modifier = GetModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    bool enabled = runtimeCallInfo->GetCallArgRef(NUM_1)->ToBoolean(vm)->Value();
    modifier->setCanvasAntiAlias(nativeNode, enabled);
    return panda::JSValueRef::Undefined(vm);
}

// ── Transform ──

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Save(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    pattern->Save();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Restore(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    pattern->Restore();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Scale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double x = 0.0;
    double y = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->Scale(x, y);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Rotate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double angle = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, angle)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->Rotate(angle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Translate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = GetDensity();
    double x = 0.0;
    double y = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->Translate(x * density, y * density);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Transform(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    TransformParam param;
    double density = GetDensity();
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, param.scaleX) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_2, param.skewX) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, param.skewY) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_4, param.scaleY) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_5, param.translateX) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_6, param.translateY)) {
        return panda::JSValueRef::Undefined(vm);
    }
    param.translateX *= density;
    param.translateY *= density;
    pattern->Transform(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::SetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    // setTransform() with 0 args → reset (Canvas spec).
    // Matrix2D object overload (>= API 10) requires frontend types;
    // delegated to JSCanvasRenderer in the declarative frontend path.
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    constexpr size_t MIN_ARGS_FOR_TRANSFORM = 2;
    if (runtimeCallInfo->GetArgsNumber() < MIN_ARGS_FOR_TRANSFORM) {
        pattern->ResetTransform();
        return panda::JSValueRef::Undefined(vm);
    }
    // setTransform(a, b, c, d, e, f): Canvas matrix [a b c d e f] maps to
    // scaleX=a, skewY=b, skewX=c, scaleY=d, translateX=e, translateY=f
    // (b=skewY, c=skewX — the same order as the old JSCanvasRenderer::JsSetTransform)
    TransformParam param;
    double density = GetDensity();
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, param.scaleX) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_2, param.skewY) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, param.skewX) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_4, param.scaleY) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_5, param.translateX) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_6, param.translateY)) {
        return panda::JSValueRef::Undefined(vm);
    }
    param.translateX *= density;
    param.translateY *= density;
    pattern->SetTransform(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::ResetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    pattern->ResetTransform();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::Reset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    pattern->Reset();
    return panda::JSValueRef::Undefined(vm);
}

// ── Text ──

ArkUINativeModuleValue CanvasRenderingContext2DBridge::FillText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto* modifier = GetModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    std::string text;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), text, resObj);
    double density = GetDensity();
    double xVal = 0.0;
    double yVal = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_2, xVal) || !GetValidDoubleArg(runtimeCallInfo, NUM_3, yVal)) {
        return panda::JSValueRef::Undefined(vm);
    }
    float x = static_cast<float>(xVal * density);
    float y = static_cast<float>(yVal * density);
    float maxWidth = 0.0f;
    auto maxWidthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (maxWidthArg->IsNumber()) {
        double mw = maxWidthArg->ToNumber(vm)->Value();
        if (!std::isnan(mw) && !std::isinf(mw)) {
            maxWidth = static_cast<float>(mw * density);
        }
    }
    modifier->setCanvasFillText(nativeNode, text.c_str(), x, y, maxWidth);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::StrokeText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    std::string text;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), text, resObj);
    double density = GetDensity();
    double x = 0.0;
    double y = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_2, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_3, y)) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::optional<double> maxWidth;
    auto maxWidthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (maxWidthArg->IsNumber()) {
        double mw = maxWidthArg->ToNumber(vm)->Value();
        if (!std::isnan(mw) && !std::isinf(mw)) {
            maxWidth = mw * density;
        }
    }
    pattern->StrokeText(text, x * density, y * density, maxWidth);
    return panda::JSValueRef::Undefined(vm);
}

// ── Line dash ──

ArkUINativeModuleValue CanvasRenderingContext2DBridge::SetLineDash(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    // Parse JS array of numbers into std::vector<double>
    Local<JSValueRef> dashArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    std::vector<double> segments;
    if (dashArg->IsArray(vm)) {
        Local<panda::ArrayRef> arr(dashArg);
        size_t len = ArkTSUtils::GetArrayLength(vm, arr);
        for (size_t i = 0; i < len; ++i) {
            auto elem = arr->Get(vm, i);
            double v = elem->ToNumber(vm)->Value();
            if (std::isnan(v) || std::isinf(v)) {
                continue;
            }
            segments.push_back(v);
        }
    }
    // Apply density scaling only for API >= 10 (matches old JSCanvasRenderer::JsSetLineDash)
    if (!Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        double density = GetDensity();
        for (auto& seg : segments) {
            seg *= density;
        }
    }
    // Duplicate if odd length (Canvas spec behavior)
    constexpr size_t DASH_SEGMENT_PAIR = 2;
    if (segments.size() % DASH_SEGMENT_PAIR != 0) {
        segments.insert(segments.end(), segments.begin(), segments.end());
    }
    pattern->UpdateLineDash(segments);
    return panda::JSValueRef::Undefined(vm);
}

// ── Layers ──

ArkUINativeModuleValue CanvasRenderingContext2DBridge::SaveLayer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    pattern->SaveLayer();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::RestoreLayer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    pattern->RestoreLayer();
    return panda::JSValueRef::Undefined(vm);
}

// ── Image ──

ArkUINativeModuleValue CanvasRenderingContext2DBridge::DrawImage(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    // Not registered — JSRenderImage unwrapping requires symbols from
    // libarkts_frontend.z.so which is not linked into libarkui_canvas.z.so.
    // JS parsing and runtime bridge calls happen in js_canvas_renderer.cpp.
    return panda::JSValueRef::Undefined(runtimeCallInfo->GetVM());
}

// ── Image data ──

ArkUINativeModuleValue CanvasRenderingContext2DBridge::PutImageData(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    // Arg0: ImageData { width, height, data: Uint8ClampedArray }
    Local<JSValueRef> imgArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!imgArg->IsObject(vm)) return panda::JSValueRef::Undefined(vm);
    auto jsImageData = imgArg->ToObject(vm);
    auto jsImgWidth = jsImageData->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
    auto jsImgHeight = jsImageData->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
    auto jsImgData = jsImageData->Get(vm, panda::StringRef::NewFromUtf8(vm, "data"));
    if (!jsImgWidth->IsNumber() || !jsImgHeight->IsNumber() || !jsImgData->IsUint8ClampedArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t imgWidth = jsImgWidth->ToNumber(vm)->Value();
    int32_t imgHeight = jsImgHeight->ToNumber(vm)->Value();
    Ace::ImageData imageData = { .dirtyWidth = imgWidth, .dirtyHeight = imgHeight };
    // Parse optional x, y (arg indices 2-3) and dirtyX/Y/Width/Height (indices 4-7)
    ParsePutImageDataCoords(runtimeCallInfo, imageData, imgWidth, imgHeight);
    // Read pixels from Uint8ClampedArray
    panda::Local<panda::Uint8ClampedArrayRef> colorArray = jsImgData->ToObject(vm);
    panda::Local<panda::ArrayBufferRef> arrayBuffer = colorArray->GetArrayBuffer(vm);
    auto* buffer = static_cast<uint8_t*>(arrayBuffer->GetBuffer(vm));
    CHECK_NULL_RETURN(buffer, panda::JSValueRef::Undefined(vm));
    int32_t bufferLength = arrayBuffer->ByteLength(vm);
    CopyPixelsToImageData(buffer, arrayBuffer->ByteLength(vm), imgWidth, imageData);
    pattern->PutImageData(imageData);
    return panda::JSValueRef::Undefined(vm);
}

// ── Transfer ──

ArkUINativeModuleValue CanvasRenderingContext2DBridge::TransferFromImageBitmap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    // Not registered — JSRenderImage unwrapping requires symbols from
    // libarkts_frontend.z.so. Runtime bridge call happens in js_rendering_context.cpp.
    return panda::JSValueRef::Undefined(runtimeCallInfo->GetVM());
}

// ── Analyzer ──

ArkUINativeModuleValue CanvasRenderingContext2DBridge::StartImageAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    // Stub — startImageAnalyzer config parsing is complex
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasRenderingContext2DBridge::StopImageAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pattern = GetCanvasPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    pattern->StopImageAnalyzer();
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
