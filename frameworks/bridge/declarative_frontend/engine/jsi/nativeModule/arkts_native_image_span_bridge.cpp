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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_span_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

#include "base/image/pixel_map.h"
#include "bridge/declarative_frontend/jsview/js_image.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/text/image_span_view.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int SIZE_OF_FOUR = 4;
const std::vector<float> DEFAULT_COLOR_FILTER_MATRIX = {
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
};
} // namespace

ArkUINativeModuleValue ImageSpanBridge::SetVerticalAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> verticalAlign = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    int32_t value = static_cast<int32_t>(VerticalAlign::BOTTOM);
    if (verticalAlign->IsNumber()) {
        value = verticalAlign->Int32Value(vm);
        auto align = static_cast<VerticalAlign>(value);
        if (align < VerticalAlign::TOP || align > VerticalAlign::NONE) {
            align = VerticalAlign::BOTTOM;
        }
        value = static_cast<int32_t>(align);
    }
    GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanVerticalAlign(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::ResetVerticalAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanVerticalAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::SetObjectFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> objectFit = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    int32_t value = static_cast<int32_t>(ImageFit::COVER);
    if (objectFit->IsNumber()) {
        value = objectFit->Int32Value(vm);
        auto fit = static_cast<ImageFit>(value);
        if (fit < ImageFit::FILL || fit > ImageFit::SCALE_DOWN) {
            fit = ImageFit::COVER;
        }
        value = static_cast<int32_t>(fit);
    }
    GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanObjectFit(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::ResetObjectFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanObjectFit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::SetTextBackgroundStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Color color;
    std::vector<ArkUI_Float32> radiusArray;
    std::vector<ArkUI_Int32> valueUnits;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::shared_ptr<TextBackgroundStyle> style = std::make_shared<TextBackgroundStyle>();
    RefPtr<ResourceObject> colorResObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj)) {
        color = Color::TRANSPARENT;
    }
    ArkTSUtils::ParseOuterBorderRadius(runtimeCallInfo, vm, radiusArray, valueUnits, NUM_2, style);
    ArkTSUtils::SetTextBackgroundStyle(style, color, colorResObj, radiusArray.data(), valueUnits.data());
    GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanTextBackgroundStyle(
        nativeNode, color.GetValue(), radiusArray.data(), valueUnits.data(), static_cast<int32_t>(radiusArray.size()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::ResetTextBackgroundStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanTextBackgroundStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::SetBaselineOffset(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension result;
    if (secondArg->IsObject(vm) && ArkTSUtils::ParseJsLengthMetrics(vm, secondArg, result) &&
        result.Unit() != DimensionUnit::PERCENT && !std::isnan(result.Value())) {
        GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanBaselineOffset(
            nativeNode, result.Value(), static_cast<int8_t>(result.Unit()));
    } else {
        GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanBaselineOffset(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::ResetBaselineOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanBaselineOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::SetAlt(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    RefPtr<PixelMap> pixmap = nullptr;
#if defined (PIXEL_MAP_SUPPORTED)
    pixmap = Framework::CreatePixelMapFromNapiValue(info[1]);
#endif
    if (pixmap) {
        ImageSpanView::SetAlt(reinterpret_cast<FrameNode*>(nativeNode), pixmap);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::ResetAlt(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::SetOnComplete(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanOnComplete(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(LoadImageSuccessEvent&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](LoadImageSuccessEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "width", "height", "componentWidth", "componentHeight", "loadingStatus", "contentWidth",
            "contentHeight", "contentOffsetX", "contentOffsetY" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, event.GetWidth()),
            panda::NumberRef::New(vm, event.GetHeight()), panda::NumberRef::New(vm, event.GetComponentWidth()),
            panda::NumberRef::New(vm, event.GetComponentHeight()), panda::NumberRef::New(vm, event.GetLoadingStatus()),
            panda::NumberRef::New(vm, event.GetContentWidth()), panda::NumberRef::New(vm, event.GetContentHeight()),
            panda::NumberRef::New(vm, event.GetContentOffsetX()),
            panda::NumberRef::New(vm, event.GetContentOffsetY()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanOnComplete(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::ResetOnComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanOnComplete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::SetOnError(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanOnError(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(LoadImageFailEvent&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](LoadImageFailEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "componentWidth", "componentHeight", "message" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, event.GetComponentWidth()),
            panda::NumberRef::New(vm, event.GetComponentHeight()),
            panda::StringRef::NewFromUtf8(vm, event.GetErrorMessage().c_str()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanOnError(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::ResetOnError(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanOnError(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetSpanColorFilterObject(const EcmaVM* vm, const Local<JSValueRef>& jsObjArg, ArkUINodeHandle nativeNode)
{
    Framework::JSColorFilter* colorFilter;
    if (!jsObjArg->IsUndefined() && !jsObjArg->IsNull()) {
        colorFilter = static_cast<Framework::JSColorFilter*>(jsObjArg->ToObject(vm)->GetNativePointerField(vm, 0));
    } else {
        GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanColorFilter(
            nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return;
    }
    if (colorFilter && colorFilter->GetColorFilterMatrix().size() == COLOR_FILTER_MATRIX_SIZE) {
        GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanColorFilter(
            nativeNode, &(*colorFilter->GetColorFilterMatrix().begin()), COLOR_FILTER_MATRIX_SIZE);
        return;
    }
    GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanColorFilter(
        nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
}

ArkUINativeModuleValue ImageSpanBridge::SetColorFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> jsObjArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!jsObjArg->IsArray(vm) && !jsObjArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanColorFilter(
            nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return panda::JSValueRef::Undefined(vm);
    }
    if (jsObjArg->IsObject(vm) && !jsObjArg->IsArray(vm)) {
        auto drawingColorFilter = Ace::Framework::CreateDrawingColorFilter(info[1]);
        if (drawingColorFilter) {
            ImageModelNG::SetDrawingColorFilter(reinterpret_cast<FrameNode*>(nativeNode), drawingColorFilter);
            return panda::JSValueRef::Undefined(vm);
        }
        SetSpanColorFilterObject(vm, jsObjArg, nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto array = panda::CopyableGlobal<panda::ArrayRef>(vm, jsObjArg);
    if (array.IsEmpty() || array->IsUndefined() || array->IsNull() || array->Length(vm) != COLOR_FILTER_MATRIX_SIZE) {
        GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanColorFilter(
            nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<float> colorFilter;
    for (size_t i = 0; i < array->Length(vm); i++) {
        auto value = array->GetValueAt(vm, jsObjArg, i);
        if (value->IsNumber()) {
            colorFilter.emplace_back(value->ToNumber(vm)->Value());
        } else {
            GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanColorFilter(
                nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanColorFilter(
        nativeNode, &(*colorFilter.begin()), COLOR_FILTER_MATRIX_SIZE);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::ResetColorFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanColorFilter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::SetBorderRadius(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (topLeftArgs->IsUndefined() && topRightArgs->IsUndefined() && bottomLeftArgs->IsUndefined() &&
        bottomRightArgs->IsUndefined()) {
        GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension topLeft;
    CalcDimension topRight;
    CalcDimension bottomLeft;
    CalcDimension bottomRight;

    bool isLengthMetrics = false;
    isLengthMetrics |= ArkTSUtils::ParseJsLengthMetrics(vm, topLeftArgs, topLeft);
    isLengthMetrics |= ArkTSUtils::ParseJsLengthMetrics(vm, topRightArgs, topRight);
    isLengthMetrics |= ArkTSUtils::ParseJsLengthMetrics(vm, bottomLeftArgs, bottomLeft);
    isLengthMetrics |= ArkTSUtils::ParseJsLengthMetrics(vm, bottomRightArgs, bottomRight);
    if (!isLengthMetrics) {
        ArkTSUtils::ParseAllBorder(vm, topLeftArgs, topLeft);
        ArkTSUtils::ParseAllBorder(vm, topRightArgs, topRight);
        ArkTSUtils::ParseAllBorder(vm, bottomLeftArgs, bottomLeft);
        ArkTSUtils::ParseAllBorder(vm, bottomRightArgs, bottomRight);
    }
    auto directionChanged = false;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
        auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
        directionChanged = isRightToLeft && isLengthMetrics;
    }
    uint32_t size = SIZE_OF_FOUR;
    ArkUI_Float32 values[size];
    int units[size];
    values[NUM_0] = directionChanged ? topRight.Value() : topLeft.Value();
    units[NUM_0] = directionChanged ? static_cast<int>(topRight.Unit()) : static_cast<int>(topLeft.Unit());
    values[NUM_1] = directionChanged ? topLeft.Value() : topRight.Value();
    units[NUM_1] = directionChanged ? static_cast<int>(topLeft.Unit()) : static_cast<int>(topRight.Unit());
    values[NUM_2] = directionChanged ? bottomRight.Value() : bottomLeft.Value();
    units[NUM_2] = directionChanged ? static_cast<int>(bottomRight.Unit()) : static_cast<int>(bottomLeft.Unit());
    values[NUM_3] = directionChanged ? bottomLeft.Value() : bottomRight.Value();
    units[NUM_3] = directionChanged ? static_cast<int>(bottomLeft.Unit()) : static_cast<int>(bottomRight.Unit());

    GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanBorderRadius(nativeNode, values, units, SIZE_OF_FOUR);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::ResetBorderRadius(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

bool CheckIsCard()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto context = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(context, false);
    return context->IsFormRender() && !container->IsDynamicRender();
}

ArkUINativeModuleValue ImageSpanBridge::SetImageSpanSrc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    int32_t resId = 0;
    if (info.Length() > 1 && info[1]->IsObject()) {
        Framework::JSRef<Framework::JSObject> jsObj = Framework::JSRef<Framework::JSObject>::Cast(info[1]);
        Framework::JSRef<Framework::JSVal> tmp = jsObj->GetProperty("id");
        if (!tmp->IsNull() && tmp->IsNumber()) {
            resId = tmp->ToNumber<int32_t>();
        }
    }
    bool isCard = CheckIsCard();
    std::string src;
    bool srcValid = ArkTSUtils::ParseJsMedia(vm, secondArg, src);
    if (isCard && secondArg->IsString(vm)) {
        SrcType srcType = ImageSourceInfo::ResolveURIType(src);
        bool notSupport = (srcType == SrcType::NETWORK || srcType == SrcType::FILE || srcType == SrcType::DATA_ABILITY);
        if (notSupport) {
            src.clear();
        }
    }
    std::string bundleName;
    std::string moduleName;
    ArkTSUtils::GetJsMediaBundleInfo(vm, secondArg, bundleName, moduleName);
    RefPtr<PixelMap> pixmap = nullptr;
    if (!srcValid) {
#if defined(PIXEL_MAP_SUPPORTED)
        pixmap = Framework::CreatePixelMapFromNapiValue(info[1]);
#endif
    }
    if (pixmap) {
        ImageSpanView::SetPixelMap(reinterpret_cast<FrameNode*>(nativeNode), pixmap);
    } else {
        nodeModifiers->getImageSpanModifier()->setImageSpanSrc(
            nativeNode, src.c_str(), bundleName.c_str(), moduleName.c_str(), (resId == -1));
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
