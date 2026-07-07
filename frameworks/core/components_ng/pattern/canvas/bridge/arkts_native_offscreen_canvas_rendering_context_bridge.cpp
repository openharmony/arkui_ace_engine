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
#include "frameworks/core/components_ng/pattern/canvas/bridge/arkts_native_offscreen_canvas_rendering_context_bridge.h"

#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"
#include "core/common/container.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

#include "bridge/declarative_frontend/jsview/canvas/js_canvas_gradient.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_pattern.h"

#include <cmath>

namespace OHOS::Ace::NG {

namespace {

// Returns true and sets `value` only when the argument is a finite number
// (not NaN, not Infinity, not undefined/null).  Mirrors the old
// GetDoubleArg(..., isJudgeSpecialValue_=true) behaviour.
bool GetValidDoubleArg(ArkUIRuntimeCallInfo* info, size_t index, double& value)
{
    auto arg = info->GetCallArgRef(index);
    if (arg->IsUndefined() || arg->IsNull()) {
        return false;
    }
    double v = arg->ToNumber(info->GetVM())->Value();
    if (std::isnan(v) || std::isinf(v)) {
        return false;
    }
    value = v;
    return true;
}

constexpr size_t NUM_0 = 0;
constexpr size_t NUM_1 = 1;
constexpr size_t NUM_2 = 2;
constexpr size_t NUM_3 = 3;
constexpr size_t NUM_4 = 4;
constexpr size_t NUM_5 = 5;
constexpr size_t NUM_6 = 6;
constexpr size_t NUM_7 = 7;
constexpr size_t NUM_8 = 8;

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

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm)) {
        return true;
    }
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        nativeNode = nullptr;
        return true;
    }
    return false;
}

RefPtr<OffscreenCanvasPattern> GetOffscreenPattern(ArkUINodeHandle nativeNode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetPattern<OffscreenCanvasPattern>();
}
void ApplyOffscreenFillObject(EcmaVM* vm, const Local<panda::ObjectRef>& obj,
    const RefPtr<OffscreenCanvasPattern>& pattern)
{
    auto typeVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "__type"));
    if (!typeVal->IsNumber()) {
        return;
    }
    auto type = typeVal->ToNumber(vm)->Value();
    if (type == GRADIENT_TYPE) {
        auto* jsGradient = UnwrapNativePointer<Framework::JSCanvasGradient>(vm, obj);
        if (jsGradient != nullptr) {
            pattern->SetFillGradient(*jsGradient->GetGradient());
        }
    } else if (type == PATTERN_TYPE) {
        auto* jsPattern = UnwrapNativePointer<Framework::JSCanvasPattern>(vm, obj);
        if (jsPattern != nullptr) {
            pattern->SetFillPattern(jsPattern->GetPattern());
        }
    }
}

void ApplyOffscreenStrokeObject(EcmaVM* vm, const Local<panda::ObjectRef>& obj,
    const RefPtr<OffscreenCanvasPattern>& pattern)
{
    auto typeVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "__type"));
    if (!typeVal->IsNumber()) {
        return;
    }
    auto type = typeVal->ToNumber(vm)->Value();
    if (type == GRADIENT_TYPE) {
        auto* jsGradient = UnwrapNativePointer<Framework::JSCanvasGradient>(vm, obj);
        if (jsGradient != nullptr) {
            pattern->SetStrokeGradient(*jsGradient->GetGradient());
        }
    } else if (type == PATTERN_TYPE) {
        auto* jsPattern = UnwrapNativePointer<Framework::JSCanvasPattern>(vm, obj);
        if (jsPattern != nullptr) {
            pattern->SetStrokePattern(jsPattern->GetPattern());
        }
    }
}

void CopyPixelsToImageData(const uint8_t* buffer, int32_t bufLen, int32_t imgWidth,
    Ace::ImageData& imageData)
{
    imageData.data = std::vector<uint32_t>();
    constexpr int32_t RED_IDX = 0;
    constexpr int32_t GREEN_IDX = 1;
    constexpr int32_t BLUE_IDX = 2;
    constexpr int32_t ALPHA_IDX = 3;
    for (int32_t i = std::max(imageData.dirtyY, 0); i < imageData.dirtyY + imageData.dirtyHeight; ++i) {
        for (int32_t j = std::max(imageData.dirtyX, 0); j < imageData.dirtyX + imageData.dirtyWidth; ++j) {
            uint32_t idx = static_cast<uint32_t>(4 * (j + imgWidth * i));
            if (bufLen > static_cast<int32_t>(idx + ALPHA_IDX)) {
                imageData.data.emplace_back(Color::FromARGB(
                    buffer[idx + ALPHA_IDX], buffer[idx + RED_IDX],
                    buffer[idx + GREEN_IDX], buffer[idx + BLUE_IDX]).GetValue());
            }
        }
    }
}
} // namespace

namespace {
void RegisterOffscreenMethods(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto ctx2d = panda::ObjectRef::New(vm);
    auto reg = [&ctx2d, &vm](const char* name, ArkUINativeModuleValue (*func)(ArkUIRuntimeCallInfo*)) {
        ctx2d->Set(vm, panda::StringRef::NewFromUtf8(vm, name),
            panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), func));
    };
    reg("beginPath", OffscreenCanvasRenderingContext2DBridge::BeginPath);
    reg("closePath", OffscreenCanvasRenderingContext2DBridge::ClosePath);
    reg("moveTo", OffscreenCanvasRenderingContext2DBridge::MoveTo);
    reg("lineTo", OffscreenCanvasRenderingContext2DBridge::LineTo);
    reg("arc", OffscreenCanvasRenderingContext2DBridge::Arc);
    reg("fill", OffscreenCanvasRenderingContext2DBridge::Fill);
    reg("stroke", OffscreenCanvasRenderingContext2DBridge::Stroke);
    reg("fillStyle", OffscreenCanvasRenderingContext2DBridge::FillStyle);
    reg("strokeStyle", OffscreenCanvasRenderingContext2DBridge::StrokeStyle);
    reg("lineWidth", OffscreenCanvasRenderingContext2DBridge::LineWidth);
    reg("globalAlpha", OffscreenCanvasRenderingContext2DBridge::GlobalAlpha);
    reg("fillRect", OffscreenCanvasRenderingContext2DBridge::FillRect);
    reg("fillText", OffscreenCanvasRenderingContext2DBridge::FillText);
    reg("save", OffscreenCanvasRenderingContext2DBridge::Save);
    reg("restore", OffscreenCanvasRenderingContext2DBridge::Restore);
    reg("scale", OffscreenCanvasRenderingContext2DBridge::Scale);
    reg("rotate", OffscreenCanvasRenderingContext2DBridge::Rotate);
    reg("translate", OffscreenCanvasRenderingContext2DBridge::Translate);
    reg("reset", OffscreenCanvasRenderingContext2DBridge::Reset);
    reg("antiAlias", OffscreenCanvasRenderingContext2DBridge::AntiAlias);
    reg("strokeRect", OffscreenCanvasRenderingContext2DBridge::StrokeRect);
    reg("clearRect", OffscreenCanvasRenderingContext2DBridge::ClearRect);
    reg("clip", OffscreenCanvasRenderingContext2DBridge::Clip);
    reg("rect", OffscreenCanvasRenderingContext2DBridge::Rect);
    reg("ellipse", OffscreenCanvasRenderingContext2DBridge::Ellipse);
    reg("bezierCurveTo", OffscreenCanvasRenderingContext2DBridge::BezierCurveTo);
    reg("quadraticCurveTo", OffscreenCanvasRenderingContext2DBridge::QuadraticCurveTo);
    reg("arcTo", OffscreenCanvasRenderingContext2DBridge::ArcTo);
    reg("roundRect", OffscreenCanvasRenderingContext2DBridge::RoundRect);
    reg("transform", OffscreenCanvasRenderingContext2DBridge::Transform);
    reg("setTransform", OffscreenCanvasRenderingContext2DBridge::SetTransform);
    reg("resetTransform", OffscreenCanvasRenderingContext2DBridge::ResetTransform);
    reg("setLineDash", OffscreenCanvasRenderingContext2DBridge::SetLineDash);
    reg("saveLayer", OffscreenCanvasRenderingContext2DBridge::SaveLayer);
    reg("restoreLayer", OffscreenCanvasRenderingContext2DBridge::RestoreLayer);
    // drawImage / transferFromImageBitmap: need JSRenderImage methods from
    // libarkts_frontend.z.so. JS parsing happens in js_canvas_renderer.cpp.
    // startImageAnalyzer: requires NAPI async promise/callback infra.
    reg("putImageData", OffscreenCanvasRenderingContext2DBridge::PutImageData);
    reg("stopImageAnalyzer", OffscreenCanvasRenderingContext2DBridge::StopImageAnalyzer);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "OffscreenCanvasRenderingContext2D"), ctx2d);
}
} // namespace

void OffscreenCanvasRenderingContext2DBridge::RegisterOffscreenCanvasRenderingContext2DAttributes(
    Local<panda::ObjectRef> object, EcmaVM* vm)
{
    RegisterOffscreenMethods(object, vm);
}

RefPtr<OffscreenCanvasPattern> GetPatternForStub(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM*& vm)
{
    vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, nullptr);
    auto pattern = GetOffscreenPattern(nativeNode);
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern;
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::BeginPath(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->BeginPath();
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::ClosePath(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->ClosePath();
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::MoveTo(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    double x = 0.0, y = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y)) {
        return panda::JSValueRef::Undefined(vm);
    }
    p->MoveTo(x * density, y * density);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::LineTo(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    double x = 0.0, y = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y)) {
        return panda::JSValueRef::Undefined(vm);
    }
    p->LineTo(x * density, y * density);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Fill(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->Fill();
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Stroke(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->Stroke();
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Clip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->Clip();
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Save(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->Save();
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Restore(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->Restore();
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Reset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->Reset();
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::RestoreLayer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->RestoreLayer();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::FillStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> val = runtimeCallInfo->GetCallArgRef(NUM_1);
    // Try string color or uint32 color first (ParseJsColorAlpha handles both).
    Color color;
    if (ArkTSUtils::ParseJsColorAlpha(vm, val, color)) {
        p->SetFillColor(color);
        return panda::JSValueRef::Undefined(vm);
    }
    // Check for Gradient or Pattern object (__type marker).
    if (val->IsObject(vm)) {
        ApplyOffscreenFillObject(vm, val->ToObject(vm), p);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::StrokeStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> val = runtimeCallInfo->GetCallArgRef(NUM_1);
    // Try string color or uint32 color first (ParseJsColorAlpha handles both).
    Color color;
    if (ArkTSUtils::ParseJsColorAlpha(vm, val, color)) {
        p->SetStrokeColor(color);
        return panda::JSValueRef::Undefined(vm);
    }
    // Check for Gradient or Pattern object (__type marker).
    if (val->IsObject(vm)) {
        ApplyOffscreenStrokeObject(vm, val->ToObject(vm), p);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::LineWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double val = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, val)) {
        return panda::JSValueRef::Undefined(vm);
    }
    p->SetLineWidth(val * PipelineBase::GetCurrentDensity());
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::GlobalAlpha(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double val = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, val)) {
        return panda::JSValueRef::Undefined(vm);
    }
    p->SetAlpha(val);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::AntiAlias(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto pattern = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    bool enabled = runtimeCallInfo->GetCallArgRef(NUM_1)->ToBoolean(vm)->Value();
    pattern->SetAntiAlias(enabled);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Arc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto pattern = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    ArcParam param;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, param.x) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_2, param.y) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, param.radius) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_4, param.startAngle) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_5, param.endAngle)) {
        return panda::JSValueRef::Undefined(vm);
    }
    param.x *= density;
    param.y *= density;
    param.radius *= density;
    auto lastArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    param.anticlockwise = lastArg->IsBoolean() && lastArg->ToBoolean(vm)->Value();
    pattern->Arc(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::FillRect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto pattern = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    double x = 0.0, y = 0.0, w = 0.0, h = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, w) || !GetValidDoubleArg(runtimeCallInfo, NUM_4, h)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->FillRect(OHOS::Ace::Rect(x * density, y * density, w * density, h * density));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::StrokeRect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto pattern = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    double x = 0.0, y = 0.0, w = 0.0, h = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, w) || !GetValidDoubleArg(runtimeCallInfo, NUM_4, h)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->StrokeRect(OHOS::Ace::Rect(x * density, y * density, w * density, h * density));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::ClearRect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto pattern = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    double x = 0.0, y = 0.0, w = 0.0, h = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, w) || !GetValidDoubleArg(runtimeCallInfo, NUM_4, h)) {
        return panda::JSValueRef::Undefined(vm);
    }
    pattern->ClearRect(OHOS::Ace::Rect(x * density, y * density, w * density, h * density));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::FillText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto pattern = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    std::string text;
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseJsString(vm, runtimeCallInfo->GetCallArgRef(NUM_1), text, resObj);
    double density = PipelineBase::GetCurrentDensity();
    double x = 0.0, y = 0.0;
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
    pattern->FillText(text, x * density, y * density, maxWidth);
    return panda::JSValueRef::Undefined(vm);
}

// Stub implementations for complex methods
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Scale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double x = 0.0, y = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y)) {
        return panda::JSValueRef::Undefined(vm);
    }
    p->Scale(x, y);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Rotate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double angle = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, angle)) {
        return panda::JSValueRef::Undefined(vm);
    }
    p->Rotate(angle);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Translate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    double x = 0.0, y = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y)) {
        return panda::JSValueRef::Undefined(vm);
    }
    p->Translate(x * density, y * density);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Rect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    double x = 0.0, y = 0.0, w = 0.0, h = 0.0;
    if (!GetValidDoubleArg(runtimeCallInfo, NUM_1, x) || !GetValidDoubleArg(runtimeCallInfo, NUM_2, y) ||
        !GetValidDoubleArg(runtimeCallInfo, NUM_3, w) || !GetValidDoubleArg(runtimeCallInfo, NUM_4, h)) {
        return panda::JSValueRef::Undefined(vm);
    }
    p->AddRect(OHOS::Ace::Rect(x * density, y * density, w * density, h * density));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Ellipse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
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
    auto la = runtimeCallInfo->GetCallArgRef(NUM_8);
    param.anticlockwise = la->IsBoolean() && la->ToBoolean(vm)->Value();
    p->Ellipse(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::BezierCurveTo(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
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
    p->BezierCurveTo(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::QuadraticCurveTo(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
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
    p->QuadraticCurveTo(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::ArcTo(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
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
    p->ArcTo(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::RoundRect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    double x = 0.0, y = 0.0, w = 0.0, h = 0.0;
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
    p->AddRoundRect(OHOS::Ace::Rect(x * density, y * density, w * density, h * density), radii);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Transform(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    TransformParam param;
    double density = PipelineBase::GetCurrentDensity();
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
    p->Transform(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::SetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    // setTransform(a, b, c, d, e, f): Canvas matrix [a b c d e f] maps to
    // scaleX=a, skewY=b, skewX=c, scaleY=d, translateX=e, translateY=f
    // (b=skewY, c=skewX — the same order as the old JSCanvasRenderer::JsSetTransform)
    TransformParam param;
    double density = PipelineBase::GetCurrentDensity();
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
    p->SetTransform(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::ResetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->ResetTransform();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::SetLineDash(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> dashArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    std::vector<double> segments;
    if (dashArg->IsArray(vm)) {
        Local<panda::ArrayRef> arr(dashArg);
        size_t len = ArkTSUtils::GetArrayLength(vm, arr);
        for (size_t i = 0; i < len; ++i) {
            double v = arr->Get(vm, i)->ToNumber(vm)->Value();
            if (std::isnan(v) || std::isinf(v)) {
                continue;
            }
            segments.push_back(v);
        }
    }
    // Apply density scaling only for API >= 10 (matches old JSCanvasRenderer::JsSetLineDash)
    if (!Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        double density = PipelineBase::GetCurrentDensity();
        for (auto& seg : segments) {
            seg *= density;
        }
    }
    p->SetLineDash(segments);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::SaveLayer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->SaveLayer();
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::DrawImage(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    // Not registered — JSRenderImage unwrapping requires symbols from
    // libarkts_frontend.z.so which is not linked into libarkui_canvas.z.so.
    return panda::JSValueRef::Undefined(runtimeCallInfo->GetVM());
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::PutImageData(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto pattern = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> imgArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!imgArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto jsImageData = imgArg->ToObject(vm);
    auto jsWidth = jsImageData->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
    auto jsHeight = jsImageData->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
    auto jsData = jsImageData->Get(vm, panda::StringRef::NewFromUtf8(vm, "data"));
    if (!jsWidth->IsNumber() || !jsHeight->IsNumber() || !jsData->IsUint8ClampedArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t imgWidth = jsWidth->ToNumber(vm)->Value();
    int32_t imgHeight = jsHeight->ToNumber(vm)->Value();
    Ace::ImageData imageData = { .dirtyWidth = imgWidth, .dirtyHeight = imgHeight };
    double density = PipelineBase::GetCurrentDensity();
    auto parseCoord = [&](size_t idx, int32_t& out) {
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
    imageData.dirtyWidth = imageData.dirtyX < 0 ?
        std::min(imageData.dirtyX + imageData.dirtyWidth, imgWidth) :
        std::min(imgWidth - imageData.dirtyX, imageData.dirtyWidth);
    imageData.dirtyHeight = imageData.dirtyY < 0 ?
        std::min(imageData.dirtyY + imageData.dirtyHeight, imgHeight) :
        std::min(imgHeight - imageData.dirtyY, imageData.dirtyHeight);
    panda::Local<panda::Uint8ClampedArrayRef> colorArray = jsData->ToObject(vm);
    panda::Local<panda::ArrayBufferRef> arrayBuffer = colorArray->GetArrayBuffer(vm);
    auto* buffer = static_cast<uint8_t*>(arrayBuffer->GetBuffer(vm));
    CHECK_NULL_RETURN(buffer, panda::JSValueRef::Undefined(vm));
    CopyPixelsToImageData(buffer, arrayBuffer->ByteLength(vm), imgWidth, imageData);
    pattern->PutImageData(imageData);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::TransferFromImageBitmap(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    // OffscreenCanvasPattern has no TransferFromImageBitmap — not registered.
    return panda::JSValueRef::Undefined(runtimeCallInfo->GetVM());
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::StartImageAnalyzer(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{ return panda::JSValueRef::Undefined(runtimeCallInfo->GetVM()); }
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::StopImageAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{ return panda::JSValueRef::Undefined(runtimeCallInfo->GetVM()); }

} // namespace OHOS::Ace::NG
