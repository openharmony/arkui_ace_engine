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

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;

void ParseOuterBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<ArkUI_Float32>& values,
    std::vector<ArkUI_Int32>& units, int32_t argsIndex)
{
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(argsIndex);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_1);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_2);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_3);

    std::optional<CalcDimension> topLeftOptional;
    std::optional<CalcDimension> topRightOptional;
    std::optional<CalcDimension> bottomLeftOptional;
    std::optional<CalcDimension> bottomRightOptional;

    ArkTSUtils::ParseOuterBorder(vm, topLeftArgs, topLeftOptional);
    ArkTSUtils::ParseOuterBorder(vm, topRightArgs, topRightOptional);
    ArkTSUtils::ParseOuterBorder(vm, bottomLeftArgs, bottomLeftOptional);
    ArkTSUtils::ParseOuterBorder(vm, bottomRightArgs, bottomRightOptional);

    ArkTSUtils::PushOuterBorderDimensionVector(topLeftOptional, values, units);
    ArkTSUtils::PushOuterBorderDimensionVector(topRightOptional, values, units);
    ArkTSUtils::PushOuterBorderDimensionVector(bottomLeftOptional, values, units);
    ArkTSUtils::PushOuterBorderDimensionVector(bottomRightOptional, values, units);
}
} // namespace

ArkUINativeModuleValue ImageSpanBridge::SetVerticalAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> verticalAlign = runtimeCallInfo->GetCallArgRef(1);
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
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color);
    ParseOuterBorderRadius(runtimeCallInfo, vm, radiusArray, valueUnits, NUM_2); // Border Radius args start index
    GetArkUINodeModifiers()->getImageSpanModifier()->setImageSpanTextBackgroundStyle(
        nativeNode, color.GetValue(), radiusArray.data(), valueUnits.data(), static_cast<int32_t>(radiusArray.size()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageSpanBridge::ResetTextBackgroundStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
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
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension result;
    if (secondArg->IsObject() && ArkTSUtils::ParseJsLengthMetrics(vm, secondArg, result) &&
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
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageSpanModifier()->resetImageSpanBaselineOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
