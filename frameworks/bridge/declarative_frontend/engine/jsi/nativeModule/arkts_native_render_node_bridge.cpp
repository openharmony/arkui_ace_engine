/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_render_node_bridge.h"

#include <cstdint>

#include "canvas_napi/js_canvas.h"
#include "jsnapi_expo.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/shape.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/pattern/render_node/render_node_properties.h"
#include "core/pipeline/pipeline_base.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const uint32_t DEFAULT_COLOR = 0xFF000000;

ArkUINativeModuleValue SetRectShape(ArkUIRuntimeCallInfo* runtimeCallInfo, bool isClip)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto leftValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 1, 0.0f);
    auto topValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 2, 0.0f);
    auto rightValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 3, 0.0f);
    auto bottomValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 4, 0.0f);
    if (isClip) {
        GetArkUINodeModifiers()->getRenderNodeModifier()->setRectClip(
            nativeNode, leftValue, topValue, rightValue - leftValue, bottomValue - topValue);
        return panda::JSValueRef::Undefined(vm);
    }
    auto fillColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 5, DEFAULT_COLOR);
    auto strokeColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 6, DEFAULT_COLOR);
    auto strokeWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 7, 0.0f);

    GetArkUINodeModifiers()->getRenderNodeModifier()->setRectMask(nativeNode, leftValue, topValue,
        rightValue - leftValue, bottomValue - topValue, fillColorValue, strokeColorValue, strokeWidthValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetCircleShape(ArkUIRuntimeCallInfo* runtimeCallInfo, bool isClip)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto centerXValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 1, 0.0f);
    auto centerYValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 2, 0.0f);
    auto radiusValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 3, 0.0f);
    if (isClip) {
        GetArkUINodeModifiers()->getRenderNodeModifier()->setCircleClip(
            nativeNode, centerXValue, centerYValue, radiusValue);
        return panda::JSValueRef::Undefined(vm);
    }
    auto fillColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 4, DEFAULT_COLOR);
    auto strokeColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 5, DEFAULT_COLOR);
    auto strokeWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 6, 0.0f);

    GetArkUINodeModifiers()->getRenderNodeModifier()->setCircleMask(
        nativeNode, centerXValue, centerYValue, radiusValue, fillColorValue, strokeColorValue, strokeWidthValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetRoundRectShape(ArkUIRuntimeCallInfo* runtimeCallInfo, bool isClip)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto topLeftXValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 1, 0.0f);
    auto topLeftYValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 2, 0.0f);

    auto topRightXValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 3, 0.0f);
    auto topRightYValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 4, 0.0f);

    auto bottomLeftXValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 5, 0.0f);
    auto bottomLeftYValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 6, 0.0f);

    auto bottomRightXValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 7, 0.0f);
    auto bottomRightYValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 8, 0.0f);

    auto leftValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 9, 0.0f);
    auto topValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 10, 0.0f);
    auto rightValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 11, 0.0f);
    auto bottomValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 12, 0.0f);

    ArkUI_Float32 roundRect[] = { topLeftXValue, topLeftYValue, topRightXValue, topRightYValue, bottomLeftXValue,
        bottomLeftYValue, bottomRightXValue, bottomRightYValue, leftValue, topValue, rightValue - leftValue,
        bottomValue - topValue };

    if (isClip) {
        GetArkUINodeModifiers()->getRenderNodeModifier()->setRoundRectClip(nativeNode, roundRect, sizeof(roundRect));
        return panda::JSValueRef::Undefined(vm);
    }

    auto fillColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 13, DEFAULT_COLOR);
    auto strokeColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 14, DEFAULT_COLOR);
    auto strokeWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 15, 0.0f);

    GetArkUINodeModifiers()->getRenderNodeModifier()->setRoundRectMask(
        nativeNode, roundRect, sizeof(roundRect), fillColorValue, strokeColorValue, strokeWidthValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetOvalShape(ArkUIRuntimeCallInfo* runtimeCallInfo, bool isClip)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto leftValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 1, 0.0f);
    auto topValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 2, 0.0f);
    auto rightValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 3, 0.0f);
    auto bottomValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 4, 0.0f);
    if (isClip) {
        GetArkUINodeModifiers()->getRenderNodeModifier()->setOvalClip(
            nativeNode, leftValue, topValue, rightValue - leftValue, bottomValue - topValue);
        return panda::JSValueRef::Undefined(vm);
    }
    auto fillColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 5, DEFAULT_COLOR);
    auto strokeColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 6, DEFAULT_COLOR);
    auto strokeWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 7, 0.0f);

    GetArkUINodeModifiers()->getRenderNodeModifier()->setOvalMask(nativeNode, leftValue, topValue,
        rightValue - leftValue, bottomValue - topValue, fillColorValue, strokeColorValue, strokeWidthValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SetCommandPathShape(ArkUIRuntimeCallInfo* runtimeCallInfo, bool isClip)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    Local<JSValueRef> path = runtimeCallInfo->GetCallArgRef(1);
    std::string pathValue;
    if (path->IsString(vm)) {
        pathValue = path->ToString(vm)->ToString(vm);
    }

    if (isClip) {
        GetArkUINodeModifiers()->getRenderNodeModifier()->setCommandPathClip(nativeNode, pathValue.c_str());
        return panda::JSValueRef::Undefined(vm);
    }
    auto fillColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 2, DEFAULT_COLOR);
    auto strokeColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 3, DEFAULT_COLOR);
    auto strokeWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 4, 0.0f);

    GetArkUINodeModifiers()->getRenderNodeModifier()->setCommandPathMask(
        nativeNode, pathValue.c_str(), fillColorValue, strokeColorValue, strokeWidthValue);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace

ArkUINativeModuleValue RenderNodeBridge::CreateRenderNode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode(
        V2::RENDER_NODE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NG::RenderNodePattern>(); });
    frameNode->SetIsArkTsRenderNode(true);
    RenderNodeBridge::SetOnDraw(frameNode, runtimeCallInfo);
    return NativeUtilsBridge::CreateStrongRef(vm, frameNode);
}

void RenderNodeBridge::FireDrawCallback(EcmaVM* vm, JsWeak<panda::CopyableGlobal<panda::ObjectRef>> object,
    NG::DrawingContext& context, Local<panda::StringRef> funcName)
{
    auto obj = object.Lock();
    CHECK_NULL_VOID(!obj.IsEmpty());
    CHECK_NULL_VOID(obj->IsObject(vm));
    auto funcObj = obj->Get(vm, funcName);
    CHECK_NULL_VOID(funcObj->IsFunction(vm));
    panda::Local<panda::FunctionRef> func = funcObj;
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    Framework::ScopeRAII scope(env);

    const char* keysOfSize[] = { "height", "width" };
    Local<JSValueRef> valuesOfSize[] = {
        panda::NumberRef::New(vm, static_cast<double>(PipelineBase::Px2VpWithCurrentDensity(context.height))),
        panda::NumberRef::New(vm, static_cast<double>(PipelineBase::Px2VpWithCurrentDensity(context.width)))
    };
    auto sizeObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfSize), keysOfSize, valuesOfSize);

    Local<JSValueRef> valuesOfSizeInPixel[] = {
        panda::NumberRef::New(vm, static_cast<double>(context.height)),
        panda::NumberRef::New(vm, static_cast<double>(context.width))
    };
    auto sizeInPixelObj =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfSize), keysOfSize, valuesOfSizeInPixel);

    auto jsCanvas = OHOS::Rosen::Drawing::JsCanvas::CreateJsCanvas(env, &context.canvas);
    OHOS::Rosen::Drawing::JsCanvas* unwrapCanvas = nullptr;
    napi_unwrap(env, jsCanvas, reinterpret_cast<void**>(&unwrapCanvas));
    if (unwrapCanvas) {
        unwrapCanvas->SaveCanvas();
        unwrapCanvas->ClipCanvas(context.width, context.height);
    }

    auto jsCanvasVal = NapiValueToLocalValue(jsCanvas);
    Local<JSValueRef> values[] = { sizeObj, sizeInPixelObj, jsCanvasVal };
    const char* keys[] = { "size", "sizeInPixel", "canvas" };
    auto contextObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    contextObj->SetNativePointerFieldCount(vm, 1);
    JSValueWrapper valueWrapper = contextObj;
    napi_value nativeValue = nativeEngine->ValueToNapiValue(valueWrapper);
    napi_wrap(
        env, nativeValue, &context.canvas, [](napi_env, void*, void*) {}, nullptr, nullptr);
    panda::Local<panda::JSValueRef> params[1] = { contextObj };
    func->Call(vm, obj.ToLocal(), params, 1);
    if (unwrapCanvas) {
        unwrapCanvas->RestoreCanvas();
        unwrapCanvas->ResetCanvas();
    }
}

void RenderNodeBridge::SetOnDraw(const RefPtr<FrameNode>& frameNode, ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_VOID(firstArg->IsObject(vm));
    auto obj = Local<panda::ObjectRef>(firstArg);
    auto funcName = panda::StringRef::NewFromUtf8(vm, "draw");
    auto funcObj = obj->Get(vm, funcName);
    CHECK_NULL_VOID(funcObj->IsFunction(vm));
    auto drawCallback = [vm, object = JsWeak(panda::CopyableGlobal(vm, obj))](NG::DrawingContext& context) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto funcName = panda::StringRef::NewFromUtf8(vm, "draw");
        RenderNodeBridge::FireDrawCallback(vm, object, context, funcName);
    };
    auto pattern = frameNode->GetPattern<NG::RenderNodePattern>();
    pattern->SetDrawCallback(std::move(drawCallback));
}

ArkUINativeModuleValue RenderNodeBridge::AddBuilderNode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto childNativeNode = nodePtr(secondArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRenderNodeModifier()->addBuilderNode(nativeNode, childNativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::AppendChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto childNativeNode = nodePtr(secondArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRenderNodeModifier()->appendChild(nativeNode, childNativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::InsertChildAfter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto child = nodePtr(secondArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    if (thirdArg.IsNull()) {
        GetArkUINodeModifiers()->getRenderNodeModifier()->insertChildAfter(nativeNode, child, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    auto sibling = nodePtr(thirdArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRenderNodeModifier()->insertChildAfter(nativeNode, child, sibling);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::RemoveBuilderNode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto childNativeNode = nodePtr(secondArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRenderNodeModifier()->removeBuilderNode(nativeNode, childNativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::RemoveChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto childNativeNode = nodePtr(secondArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRenderNodeModifier()->removeChild(nativeNode, childNativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::ClearBuilderNode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getRenderNodeModifier()->clearBuilderNode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::ClearChildren(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRenderNodeModifier()->clearChildren(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetClipToFrame(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    bool useClip = false;
    if (secondArg->IsBoolean()) {
        useClip = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getRenderNodeModifier()->setClipToFrame(nativeNode, useClip);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetRotation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(4);
    double rotationX = 0.0;
    double rotationY = 0.0;
    double rotationZ = 0.0;
    int32_t unit = 0;
    if (secondArg->IsNumber()) {
        rotationX = secondArg->ToNumber(vm)->Value();
    }
    if (thirdArg->IsNumber()) {
        rotationY = thirdArg->ToNumber(vm)->Value();
    }
    if (fourthArg->IsNumber()) {
        rotationZ = fourthArg->ToNumber(vm)->Value();
    }
    if (fifthArg->IsNumber()) {
        unit = fifthArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getRenderNodeModifier()->setRotation(nativeNode, rotationX, rotationY, rotationZ, unit);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetShadowColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> color = runtimeCallInfo->GetCallArgRef(1);
    uint32_t colorValue = 0;
    if (color->IsNumber()) {
        colorValue = color->Uint32Value(vm);
    }
    GetArkUINodeModifiers()->getRenderNodeModifier()->setShadowColor(nativeNode, colorValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetShadowOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(3);
    double offsetX = 0.0;
    double offsetY = 0.0;
    int32_t unit = 0;
    if (secondArg->IsNumber()) {
        offsetX = secondArg->ToNumber(vm)->Value();
    }
    if (thirdArg->IsNumber()) {
        offsetY = thirdArg->ToNumber(vm)->Value();
    }
    if (fourthArg->IsNumber()) {
        unit = fourthArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getRenderNodeModifier()->setShadowOffset(nativeNode, offsetX, offsetY, unit);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RenderNodeBridge::SetLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> label = runtimeCallInfo->GetCallArgRef(1);
    std::string labelValue;
    if (label->IsString(vm)) {
        labelValue = label->ToString(vm)->ToString(vm);
    } else {
        labelValue = "";
        LOGW("The label of the node should be a string!");
    }
    GetArkUINodeModifiers()->getRenderNodeModifier()->setLabel(nativeNode, labelValue.c_str());
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RenderNodeBridge::SetShadowAlpha(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> alpha = runtimeCallInfo->GetCallArgRef(1);
    float alphaValue = 1.0;
    if (alpha->IsNumber()) {
        alphaValue = alpha->ToNumber(vm)->Value();
    }
    GetArkUINodeModifiers()->getRenderNodeModifier()->setShadowAlpha(nativeNode, alphaValue);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RenderNodeBridge::SetShadowElevation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> elevation = runtimeCallInfo->GetCallArgRef(1);
    float elevationValue = 0;
    if (elevation->IsNumber()) {
        elevationValue = elevation->ToNumber(vm)->Value();
    }
    GetArkUINodeModifiers()->getRenderNodeModifier()->setShadowElevation(nativeNode, elevationValue);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RenderNodeBridge::SetShadowRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> radius = runtimeCallInfo->GetCallArgRef(1);
    float radiusValue = 0;
    if (radius->IsNumber()) {
        radiusValue = radius->ToNumber(vm)->Value();
    }

    GetArkUINodeModifiers()->getRenderNodeModifier()->setShadowRadius(nativeNode, radiusValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    Local<JSValueRef> scaleX = runtimeCallInfo->GetCallArgRef(1);
    float scaleXValue = 0;
    if (scaleX->IsNumber()) {
        scaleXValue = scaleX->ToNumber(vm)->Value();
    }

    Local<JSValueRef> scaleY = runtimeCallInfo->GetCallArgRef(2);
    float scaleYValue = 0;
    if (scaleY->IsNumber()) {
        scaleYValue = scaleY->ToNumber(vm)->Value();
    }

    GetArkUINodeModifiers()->getRenderNodeModifier()->setScale(nativeNode, scaleXValue, scaleYValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> color = runtimeCallInfo->GetCallArgRef(1);
    uint32_t colorValue = 0;
    if (color->IsNumber()) {
        colorValue = color->Uint32Value(vm);
    }

    GetArkUINodeModifiers()->getRenderNodeModifier()->setRenderNodeBackgroundColor(nativeNode, colorValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetPivot(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    Local<JSValueRef> pivotX = runtimeCallInfo->GetCallArgRef(1);
    float pivotXValue = 0;
    if (pivotX->IsNumber()) {
        pivotXValue = pivotX->ToNumber(vm)->Value();
    }

    Local<JSValueRef> pivotY = runtimeCallInfo->GetCallArgRef(2);
    float pivotYValue = 0;
    if (pivotY->IsNumber()) {
        pivotYValue = pivotY->ToNumber(vm)->Value();
    }

    GetArkUINodeModifiers()->getRenderNodeModifier()->setPivot(nativeNode, pivotXValue, pivotYValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetFrame(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    Local<JSValueRef> positionX = runtimeCallInfo->GetCallArgRef(1);
    float positionXValue = 0;
    if (positionX->IsNumber()) {
        positionXValue = positionX->ToNumber(vm)->Value();
    }

    Local<JSValueRef> positionY = runtimeCallInfo->GetCallArgRef(2);
    float positionYValue = 0;
    if (positionY->IsNumber()) {
        positionYValue = positionY->ToNumber(vm)->Value();
    }

    Local<JSValueRef> width = runtimeCallInfo->GetCallArgRef(3);
    float widthValue = 0;
    if (width->IsNumber()) {
        widthValue = width->ToNumber(vm)->Value();
    }

    Local<JSValueRef> height = runtimeCallInfo->GetCallArgRef(4);
    float heightValue = 0;
    if (height->IsNumber()) {
        heightValue = height->ToNumber(vm)->Value();
    }

    GetArkUINodeModifiers()->getRenderNodeModifier()->setFrame(
        nativeNode, positionXValue, positionYValue, widthValue, heightValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    Local<JSValueRef> width = runtimeCallInfo->GetCallArgRef(1);
    float widthValue = 0;
    if (width->IsNumber()) {
        widthValue = width->ToNumber(vm)->Value();
    }

    Local<JSValueRef> height = runtimeCallInfo->GetCallArgRef(2);
    float heightValue = 0;
    if (height->IsNumber()) {
        heightValue = height->ToNumber(vm)->Value();
    }

    Local<JSValueRef> unit = runtimeCallInfo->GetCallArgRef(3);
    int32_t unitValue = 0;
    if (unit->IsNumber()) {
        unitValue = unit->Int32Value(vm);
    }

    GetArkUINodeModifiers()->getRenderNodeModifier()->setSize(nativeNode, widthValue, heightValue, unitValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    Local<JSValueRef> xAxis = runtimeCallInfo->GetCallArgRef(1);
    float xAxisValue = 0;
    if (xAxis->IsNumber()) {
        xAxisValue = xAxis->ToNumber(vm)->Value();
    }

    Local<JSValueRef> yAxis = runtimeCallInfo->GetCallArgRef(2);
    float yAxisValue = 0;
    if (yAxis->IsNumber()) {
        yAxisValue = yAxis->ToNumber(vm)->Value();
    }

    Local<JSValueRef> unit = runtimeCallInfo->GetCallArgRef(3);
    int32_t unitValue = 0;
    if (unit->IsNumber()) {
        unitValue = unit->Int32Value(vm);
    }

    GetArkUINodeModifiers()->getRenderNodeModifier()->setPosition(nativeNode, xAxisValue, yAxisValue, unitValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> opacity = runtimeCallInfo->GetCallArgRef(1);
    float opacityValue = 0;
    if (opacity->IsNumber()) {
        opacityValue = opacity->ToNumber(vm)->Value();
    }

    GetArkUINodeModifiers()->getRenderNodeModifier()->setOpacity(nativeNode, opacityValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetTranslate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    Local<JSValueRef> translateX = runtimeCallInfo->GetCallArgRef(1);
    float translateXValue = 0;
    if (translateX->IsNumber()) {
        translateXValue = translateX->ToNumber(vm)->Value();
    }

    Local<JSValueRef> translateY = runtimeCallInfo->GetCallArgRef(2);
    float translateYValue = 0;
    if (translateY->IsNumber()) {
        translateYValue = translateY->ToNumber(vm)->Value();
    }

    GetArkUINodeModifiers()->getRenderNodeModifier()->setTranslate(nativeNode, translateXValue, translateYValue, 0);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetBorderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto leftStyle = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 1, 0);
    auto leftStyleValue = static_cast<BorderStyle>(leftStyle);

    auto topStyle = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 2, 0);
    auto topStyleValue = static_cast<BorderStyle>(topStyle);

    auto rightStyle = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 3, 0);
    auto rightStyleValue = static_cast<BorderStyle>(rightStyle);

    auto bottomStyle = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 4, 0);
    auto bottomStyleValue = static_cast<BorderStyle>(bottomStyle);

    GetArkUINodeModifiers()->getRenderNodeModifier()->setBorderStyle(nativeNode,
        static_cast<ArkUI_Int32>(leftStyleValue), static_cast<ArkUI_Int32>(topStyleValue),
        static_cast<ArkUI_Int32>(rightStyleValue), static_cast<ArkUI_Int32>(bottomStyleValue));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto leftWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 1, 0.0f);
    auto topWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 2, 0.0f);
    auto rightWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 3, 0.0f);
    auto bottomWidthValue = RenderNodeBridge::GetNumber<float>(vm, runtimeCallInfo, 4, 0.0f);
    auto unitValue = RenderNodeBridge::GetNumber<int32_t>(vm, runtimeCallInfo, 5, 0);

    GetArkUINodeModifiers()->getRenderNodeModifier()->setBorderWidth(
        nativeNode, leftWidthValue, topWidthValue, rightWidthValue, bottomWidthValue, unitValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto leftColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 1, DEFAULT_COLOR);
    auto topColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 2, DEFAULT_COLOR);
    auto rightColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 3, DEFAULT_COLOR);
    auto bottomColorValue = RenderNodeBridge::GetNumber<uint32_t>(vm, runtimeCallInfo, 4, DEFAULT_COLOR);

    GetArkUINodeModifiers()->getRenderNodeModifier()->setBorderColor(
        nativeNode, leftColorValue, topColorValue, rightColorValue, bottomColorValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto topLeftRadiusValue = RenderNodeBridge::GetNumber<double>(vm, runtimeCallInfo, 1, 0.0);
    auto topRightRadiusValue = RenderNodeBridge::GetNumber<double>(vm, runtimeCallInfo, 2, 0.0);
    auto bottomLeftRadiusValue = RenderNodeBridge::GetNumber<double>(vm, runtimeCallInfo, 3, 0.0);
    auto bottomRightRadiusValue = RenderNodeBridge::GetNumber<double>(vm, runtimeCallInfo, 4, 0.0);
    auto unitValue = RenderNodeBridge::GetNumber<int32_t>(vm, runtimeCallInfo, 5, 0);

    GetArkUINodeModifiers()->getRenderNodeModifier()->setBorderRadius(
        nativeNode, topLeftRadiusValue, topRightRadiusValue, bottomLeftRadiusValue, bottomRightRadiusValue, unitValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetRectMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetRectShape(runtimeCallInfo, false);
}

ArkUINativeModuleValue RenderNodeBridge::SetCircleMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetCircleShape(runtimeCallInfo, false);
}

ArkUINativeModuleValue RenderNodeBridge::SetRoundRectMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetRoundRectShape(runtimeCallInfo, false);
}

ArkUINativeModuleValue RenderNodeBridge::SetOvalMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetOvalShape(runtimeCallInfo, false);
}

ArkUINativeModuleValue RenderNodeBridge::SetCommandPathMask(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetCommandPathShape(runtimeCallInfo, false);
}

ArkUINativeModuleValue RenderNodeBridge::SetRectClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetRectShape(runtimeCallInfo, true);
}

ArkUINativeModuleValue RenderNodeBridge::SetCircleClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetCircleShape(runtimeCallInfo, true);
}

ArkUINativeModuleValue RenderNodeBridge::SetRoundRectClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetRoundRectShape(runtimeCallInfo, true);
}

ArkUINativeModuleValue RenderNodeBridge::SetOvalClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetOvalShape(runtimeCallInfo, true);
}

ArkUINativeModuleValue RenderNodeBridge::SetCommandPathClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetCommandPathShape(runtimeCallInfo, true);
}

ArkUINativeModuleValue RenderNodeBridge::Invalidate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRenderNodeModifier()->invalidate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::SetMarkNodeGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    Local<JSValueRef> isNodeGroup = runtimeCallInfo->GetCallArgRef(1);
    bool isNodeGroupValue = false;
    if (isNodeGroup->IsBoolean()) {
        isNodeGroupValue = isNodeGroup->ToBoolean(vm)->Value();
    }

    GetArkUINodeModifiers()->getRenderNodeModifier()->setMarkNodeGroup(nativeNode, isNodeGroupValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RenderNodeBridge::FireArkUIObjectLifecycleCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto defaultReturnValue = panda::JSValueRef::Undefined(vm);
    CHECK_NULL_RETURN(vm, defaultReturnValue);
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(3);
    CHECK_NULL_RETURN(!arg.IsNull() && arg->IsNativePointer(vm), defaultReturnValue);
    auto* nativeNode = nodePtr(arg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, defaultReturnValue);
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, defaultReturnValue);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, defaultReturnValue);
    void* data = static_cast<void*>(runtimeCallInfo);
    context->FireArkUIObjectLifecycleCallback(data);
    return defaultReturnValue;
}

ArkUINativeModuleValue RenderNodeBridge::GetNodeType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::StringRef::NewFromUtf8(vm, ""));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::StringRef::NewFromUtf8(vm, ""));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeType = GetArkUINodeModifiers()->getRenderNodeModifier()->getNodeType(nativeNode);
    return panda::StringRef::NewFromUtf8(vm, nodeType);
}
} // namespace OHOS::Ace::NG
