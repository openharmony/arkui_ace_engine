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
#include "core/pipeline/pipeline_base.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

#include "bridge/declarative_frontend/jsview/canvas/js_canvas_gradient.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_pattern.h"

namespace OHOS::Ace::NG {

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
    double a1 = static_cast<double>(runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value()) * density;
    double a2 = static_cast<double>(runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value()) * density;
    p->MoveTo(a1, a2);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::LineTo(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    double a1 = static_cast<double>(runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value()) * density;
    double a2 = static_cast<double>(runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value()) * density;
    p->LineTo(a1, a2);
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
        auto obj = val->ToObject(vm);
        auto typeVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "__type"));
        if (typeVal->IsNumber()) {
            auto type = typeVal->ToNumber(vm)->Value();
            if (type == GRADIENT_TYPE) {
                auto* jsGradient = UnwrapNativePointer<Framework::JSCanvasGradient>(vm, obj);
                if (jsGradient != nullptr) {
                    p->SetFillGradient(*jsGradient->GetGradient());
                }
            } else if (type == PATTERN_TYPE) {
                auto* jsPattern = UnwrapNativePointer<Framework::JSCanvasPattern>(vm, obj);
                if (jsPattern != nullptr) {
                    p->SetFillPattern(jsPattern->GetPattern());
                }
            }
        }
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
        auto obj = val->ToObject(vm);
        auto typeVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "__type"));
        if (typeVal->IsNumber()) {
            auto type = typeVal->ToNumber(vm)->Value();
            if (type == GRADIENT_TYPE) {
                auto* jsGradient = UnwrapNativePointer<Framework::JSCanvasGradient>(vm, obj);
                if (jsGradient != nullptr) {
                    p->SetStrokeGradient(*jsGradient->GetGradient());
                }
            } else if (type == PATTERN_TYPE) {
                auto* jsPattern = UnwrapNativePointer<Framework::JSCanvasPattern>(vm, obj);
                if (jsPattern != nullptr) {
                    p->SetStrokePattern(jsPattern->GetPattern());
                }
            }
        }
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::LineWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double val = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value() *
        PipelineBase::GetCurrentDensity();
    p->SetLineWidth(val);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::GlobalAlpha(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double val = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value();
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
    param.x = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value() * density;
    param.y = runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value() * density;
    param.radius = runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value() * density;
    param.startAngle = runtimeCallInfo->GetCallArgRef(NUM_4)->ToNumber(vm)->Value();
    param.endAngle = runtimeCallInfo->GetCallArgRef(NUM_5)->ToNumber(vm)->Value();
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
    double x = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value() * density;
    double y = runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value() * density;
    double w = runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value() * density;
    double h = runtimeCallInfo->GetCallArgRef(NUM_4)->ToNumber(vm)->Value() * density;
    pattern->FillRect(OHOS::Ace::Rect(x, y, w, h));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::StrokeRect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto pattern = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    double x = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value() * density;
    double y = runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value() * density;
    double w = runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value() * density;
    double h = runtimeCallInfo->GetCallArgRef(NUM_4)->ToNumber(vm)->Value() * density;
    pattern->StrokeRect(OHOS::Ace::Rect(x, y, w, h));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::ClearRect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto pattern = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    double x = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value() * density;
    double y = runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value() * density;
    double w = runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value() * density;
    double h = runtimeCallInfo->GetCallArgRef(NUM_4)->ToNumber(vm)->Value() * density;
    pattern->ClearRect(OHOS::Ace::Rect(x, y, w, h));
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
    double x = runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value() * density;
    double y = runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value() * density;
    std::optional<double> maxWidth;
    auto maxWidthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (maxWidthArg->IsNumber()) {
        maxWidth = maxWidthArg->ToNumber(vm)->Value() * density;
    }
    pattern->FillText(text, x, y, maxWidth);
    return panda::JSValueRef::Undefined(vm);
}

// Stub implementations for complex methods
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Scale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->Scale(runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value(),
        runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value());
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Rotate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    p->Rotate(runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value());
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Translate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    p->Translate(runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value() * density,
        runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value() * density);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Rect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    p->AddRect(OHOS::Ace::Rect(runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value() * density,
        runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value() * density,
        runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value() * density,
        runtimeCallInfo->GetCallArgRef(NUM_4)->ToNumber(vm)->Value() * density));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Ellipse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    EllipseParam param;
    param.x = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value() * density;
    param.y = runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value() * density;
    param.radiusX = runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value() * density;
    param.radiusY = runtimeCallInfo->GetCallArgRef(NUM_4)->ToNumber(vm)->Value() * density;
    param.rotation = runtimeCallInfo->GetCallArgRef(NUM_5)->ToNumber(vm)->Value();
    param.startAngle = runtimeCallInfo->GetCallArgRef(NUM_6)->ToNumber(vm)->Value();
    param.endAngle = runtimeCallInfo->GetCallArgRef(NUM_7)->ToNumber(vm)->Value();
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
    param.cp1x = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value() * density;
    param.cp1y = runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value() * density;
    param.cp2x = runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value() * density;
    param.cp2y = runtimeCallInfo->GetCallArgRef(NUM_4)->ToNumber(vm)->Value() * density;
    param.x = runtimeCallInfo->GetCallArgRef(NUM_5)->ToNumber(vm)->Value() * density;
    param.y = runtimeCallInfo->GetCallArgRef(NUM_6)->ToNumber(vm)->Value() * density;
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
    param.cpx = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value() * density;
    param.cpy = runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value() * density;
    param.x = runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value() * density;
    param.y = runtimeCallInfo->GetCallArgRef(NUM_4)->ToNumber(vm)->Value() * density;
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
    param.x1 = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value() * density;
    param.y1 = runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value() * density;
    param.x2 = runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value() * density;
    param.y2 = runtimeCallInfo->GetCallArgRef(NUM_4)->ToNumber(vm)->Value() * density;
    param.radius = runtimeCallInfo->GetCallArgRef(NUM_5)->ToNumber(vm)->Value() * density;
    p->ArcTo(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::RoundRect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    double density = PipelineBase::GetCurrentDensity();
    double x = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value() * density;
    double y = runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value() * density;
    double w = runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value() * density;
    double h = runtimeCallInfo->GetCallArgRef(NUM_4)->ToNumber(vm)->Value() * density;
    // Radius: single number or array of up to 4 values
    std::vector<double> radii;
    auto radiusArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    if (radiusArg->IsArray(vm)) {
        Local<panda::ArrayRef> arr(radiusArg);
        size_t arrLen = ArkTSUtils::GetArrayLength(vm, arr);
        for (size_t i = 0; i < arrLen && i < 4; ++i) {
            radii.push_back(arr->Get(vm, i)->ToNumber(vm)->Value() * density);
        }
    } else if (radiusArg->IsNumber()) {
        double r = radiusArg->ToNumber(vm)->Value() * density;
        radii = { r, r, r, r };
    }
    if (radii.empty()) {
        return panda::JSValueRef::Undefined(vm);
    }
    p->AddRoundRect(OHOS::Ace::Rect(x, y, w, h), radii);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::Transform(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    TransformParam param;
    double density = PipelineBase::GetCurrentDensity();
    param.scaleX = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value();
    param.skewX = runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value();
    param.skewY = runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value();
    param.scaleY = runtimeCallInfo->GetCallArgRef(NUM_4)->ToNumber(vm)->Value();
    param.translateX = runtimeCallInfo->GetCallArgRef(NUM_5)->ToNumber(vm)->Value() * density;
    param.translateY = runtimeCallInfo->GetCallArgRef(NUM_6)->ToNumber(vm)->Value() * density;
    p->Transform(param);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue OffscreenCanvasRenderingContext2DBridge::SetTransform(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = nullptr;
    auto p = GetPatternForStub(runtimeCallInfo, vm);
    CHECK_NULL_RETURN(p, panda::JSValueRef::Undefined(vm));
    TransformParam param;
    double density = PipelineBase::GetCurrentDensity();
    param.scaleX = runtimeCallInfo->GetCallArgRef(NUM_1)->ToNumber(vm)->Value();
    param.skewX = runtimeCallInfo->GetCallArgRef(NUM_2)->ToNumber(vm)->Value();
    param.skewY = runtimeCallInfo->GetCallArgRef(NUM_3)->ToNumber(vm)->Value();
    param.scaleY = runtimeCallInfo->GetCallArgRef(NUM_4)->ToNumber(vm)->Value();
    param.translateX = runtimeCallInfo->GetCallArgRef(NUM_5)->ToNumber(vm)->Value() * density;
    param.translateY = runtimeCallInfo->GetCallArgRef(NUM_6)->ToNumber(vm)->Value() * density;
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
        double density = PipelineBase::GetCurrentDensity();
        Local<panda::ArrayRef> arr(dashArg);
        size_t len = ArkTSUtils::GetArrayLength(vm, arr);
        for (size_t i = 0; i < len; ++i) {
            segments.push_back(arr->Get(vm, i)->ToNumber(vm)->Value() * density);
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
            out = static_cast<int32_t>(arg->ToNumber(vm)->Value() * density);
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
    int32_t bufLen = arrayBuffer->ByteLength(vm);
    imageData.data = std::vector<uint32_t>();
    constexpr int32_t ALPHA_IDX = 3;
    for (int32_t i = std::max(imageData.dirtyY, 0); i < imageData.dirtyY + imageData.dirtyHeight; ++i) {
        for (int32_t j = std::max(imageData.dirtyX, 0); j < imageData.dirtyX + imageData.dirtyWidth; ++j) {
            uint32_t idx = static_cast<uint32_t>(4 * (j + imgWidth * i));
            if (bufLen > static_cast<int32_t>(idx + ALPHA_IDX)) {
                imageData.data.emplace_back(Color::FromARGB(
                    buffer[idx + ALPHA_IDX], buffer[idx], buffer[idx + 1], buffer[idx + 2]).GetValue());
            }
        }
    }
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
