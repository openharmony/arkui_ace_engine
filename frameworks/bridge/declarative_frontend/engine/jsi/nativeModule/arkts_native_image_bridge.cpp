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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_bridge.h"

#include "base/image/pixel_map.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_image.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/theme/theme_attributes.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {
constexpr int32_t INDEX_0 = 0;      // Arg Index
constexpr int32_t INDEX_1 = 1;      // Arg Index
constexpr int32_t INDEX_2 = 2;      // Arg Index
constexpr int32_t INDEX_3 = 3;      // Arg Index
constexpr int32_t INDEX_4 = 4;      // Arg Index
constexpr int32_t SIZE_OF_FOUR = 4; // Border Radius array size
constexpr int32_t BORDER_RADIUS_INDEX_1 = 2;
constexpr int32_t BORDER_RADIUS_INDEX_2 = 3;
constexpr int32_t BORDER_RADIUS_INDEX_3 = 4;
constexpr int32_t BORDER_RADIUS_INDEX_4 = 4;
constexpr int32_t BORDER_RADIUS_VALUE = 0;

void PushOuterBorderDimensionVector(const std::optional<CalcDimension>& valueDim, std::vector<ArkUI_Float32> &options)
{
    options.push_back(static_cast<ArkUI_Float32>(valueDim.has_value()));
    if (valueDim.has_value()) {
        options.push_back(static_cast<ArkUI_Float32>(valueDim.value().Value()));
        options.push_back(static_cast<ArkUI_Float32>(valueDim.value().Unit()));
    } else {
        options.push_back(BORDER_RADIUS_VALUE);
        options.push_back(BORDER_RADIUS_VALUE);
    }
}

void ParseOuterBorderRadius(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<ArkUI_Float32>& values)
{
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(BORDER_RADIUS_INDEX_1);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(BORDER_RADIUS_INDEX_2);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(BORDER_RADIUS_INDEX_3);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(BORDER_RADIUS_INDEX_4);

    std::optional<CalcDimension> topLeftOptional;
    std::optional<CalcDimension> topRightOptional;
    std::optional<CalcDimension> bottomLeftOptional;
    std::optional<CalcDimension> bottomRightOptional;

    ArkTSUtils::ParseOuterBorder(vm, topLeftArgs, topLeftOptional);
    ArkTSUtils::ParseOuterBorder(vm, topRightArgs, topRightOptional);
    ArkTSUtils::ParseOuterBorder(vm, bottomLeftArgs, bottomLeftOptional);
    ArkTSUtils::ParseOuterBorder(vm, bottomRightArgs, bottomRightOptional);

    PushOuterBorderDimensionVector(topLeftOptional, values);
    PushOuterBorderDimensionVector(topRightOptional, values);
    PushOuterBorderDimensionVector(bottomLeftOptional, values);
    PushOuterBorderDimensionVector(bottomRightOptional, values);
}

const std::vector<float> DEFAULT_COLOR_FILTER_MATRIX = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 };

void ParseResizableCalcDimensions(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t offset, uint32_t count,
    std::vector<std::optional<CalcDimension>>& results, const CalcDimension& defValue)
{
    auto end = offset + count;
    auto argsNumber = runtimeCallInfo->GetArgsNumber();
    if (end > argsNumber) {
        return;
    }
    CalcDimension defaultDimension(defValue);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    for (uint32_t index = offset; index < end; index++) {
        auto arg = runtimeCallInfo->GetCallArgRef(index);
        std::optional<CalcDimension> optCalcDimension;
        CalcDimension dimension(defValue);
        if (ArkTSUtils::ParseJsDimensionVp(vm, arg, dimension, false)) {
            optCalcDimension = dimension;
        } else {
            optCalcDimension = defaultDimension;
        }
        results.push_back(optCalcDimension);
    }
}

void PushDimensionsToVector(
    std::vector<ArkUIStringAndFloat>& results, const std::vector<std::optional<CalcDimension>>& optDimensions)
{
    for (uint32_t index = 0; index < optDimensions.size(); index++) {
        auto optDimension = optDimensions[index];
        auto hasValue = optDimension.has_value();
        DimensionUnit unit = DimensionUnit::PX;
        ArkUIStringAndFloat value = { 0.0, nullptr };
        if (hasValue) {
            unit = optDimension.value().Unit();
            if (unit == DimensionUnit::CALC) {
                value.valueStr = optDimension.value().CalcValue().c_str();
            } else {
                value.value = optDimension.value().Value();
            }
        }
        results.push_back(ArkUIStringAndFloat { static_cast<double>(hasValue), nullptr });
        results.push_back(value);
        results.push_back(ArkUIStringAndFloat { static_cast<double>(unit), nullptr });
    }
}

bool ImageBridge::CheckIsCard()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    return context->IsFormRender() && !container->IsDynamicRender();
}

ArkUINativeModuleValue ImageBridge::SetImageShowSrc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);

    bool isCard = CheckIsCard();
    std::string src;
    int32_t resId = 0;
    if (info[1]->IsNumber()) {
        GetArkUINodeModifiers()->getImageModifier()->resetImageContent(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (info[0]->IsObject()) {
        Framework::JSRef<Framework::JSObject> jsObj = Framework::JSRef<Framework::JSObject>::Cast(info[0]);
        Framework::JSRef<Framework::JSVal> tmp = jsObj->GetProperty("id");
        if (!tmp->IsNull() && tmp->IsNumber()) {
            resId = tmp->ToNumber<int32_t>();
        }
    }
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
    if (!srcValid && !isCard) {
#if defined(PIXEL_MAP_SUPPORTED)
        if (Framework::IsDrawable(info[1])) {
            pixmap = Framework::GetDrawablePixmap(info[1]);
        } else {
            pixmap = Framework::CreatePixelMapFromNapiValue(info[1]);
        }
#endif
    }
    if (pixmap) {
        ImageModelNG::SetInitialPixelMap(reinterpret_cast<FrameNode*>(nativeNode), pixmap);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->setImageShowSrc(
            nativeNode, src.c_str(), bundleName.c_str(), moduleName.c_str(), (resId == -1));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> optionArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (optionArg->IsNumber()) {
        int32_t option = optionArg->Int32Value(vm);
        GetArkUINodeModifiers()->getImageModifier()->setCopyOption(nativeNode, option);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetCopyOption(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetAutoResize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> autoResizeArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (autoResizeArg->IsBoolean()) {
        bool autoResize = autoResizeArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getImageModifier()->setAutoResize(nativeNode, autoResize);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetAutoResize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetAutoResize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetObjectRepeat(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int32_t imageRepeat = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getImageModifier()->setObjectRepeat(nativeNode, imageRepeat);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetObjectRepeat(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetObjectRepeat(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetObjectRepeat(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetEdgeAntialiasing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        float edgeAntialiasing = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getImageModifier()->setEdgeAntialiasing(nativeNode, edgeAntialiasing);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetEdgeAntialiasing(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetEdgeAntialiasing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetEdgeAntialiasing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetResizableLattice(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (info.Length() > 1 && info[1]->IsObject()) {
        auto drawingLattice = Ace::Framework::CreateDrawingLattice(info[1]);
        if (drawingLattice) {
            Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(INDEX_0);
            auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
            ImageModelNG::SetResizableLattice(reinterpret_cast<FrameNode*>(nativeNode), drawingLattice);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetResizable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::vector<ArkUIStringAndFloat> options;
    std::vector<std::optional<CalcDimension>> sliceDimensions;
    ParseResizableCalcDimensions(runtimeCallInfo, INDEX_1, INDEX_4, sliceDimensions, CalcDimension(0.0));
    PushDimensionsToVector(options, sliceDimensions);

    GetArkUINodeModifiers()->getImageModifier()->setResizable(nativeNode, options.data());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetResizable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetResizable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetDynamicRangeMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int32_t objectFitValue = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getImageModifier()->setDynamicRangeMode(nativeNode, objectFitValue);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetDynamicRangeMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetDynamicRangeMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetDynamicRangeMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetEnhancedImageQuality(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int32_t objectFitValue = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getImageModifier()->setEnhancedImageQuality(nativeNode, objectFitValue);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetEnhancedImageQuality(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetEnhancedImageQuality(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetEnhancedImageQuality(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetPrivacySensitive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t sensitive = false;
    if (secondArg->IsBoolean()) {
        sensitive = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getImageModifier()->setImagePrivacySensitive(nativeNode, sensitive);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetPrivacySensitive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetImagePrivacySensitive(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetRenderMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int32_t imageRenderMode = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getImageModifier()->setRenderMode(nativeNode, imageRenderMode);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetRenderMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetRenderMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetRenderMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetSyncLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool syncLoadValue = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getImageModifier()->setSyncLoad(nativeNode, syncLoadValue);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetSyncLoad(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetSyncLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetSyncLoad(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetObjectFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int32_t objectFitValue = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getImageModifier()->setObjectFit(nativeNode, objectFitValue);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetObjectFit(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetObjectFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetObjectFit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetFitOriginalSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool fitOriginalSize = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getImageModifier()->setFitOriginalSize(nativeNode, fitOriginalSize);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetFitOriginalSize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetFitOriginalSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetFitOriginalSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetSourceSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsNumber() && thirdArg->IsNumber() && secondArg->ToNumber(vm)->Value() >= 0 &&
        thirdArg->ToNumber(vm)->Value() >= 0) {
        double width = secondArg->ToNumber(vm)->Value();
        double height = thirdArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getImageModifier()->setSourceSize(nativeNode, width, height);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetSourceSize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetSourceSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetSourceSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetMatchTextDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getImageModifier()->setMatchTextDirection(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetMatchTextDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetMatchTextDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetMatchTextDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetFillColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        GetArkUINodeModifiers()->getImageModifier()->setFillColor(nativeNode, color.GetValue());
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetFillColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetFillColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetFillColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetAlt(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string src;
    if (!ArkTSUtils::ParseJsMedia(vm, secondArg, src)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (ImageSourceInfo::ResolveURIType(src) == SrcType::NETWORK) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::string bundleName;
    std::string moduleName;
    ArkTSUtils::GetJsMediaBundleInfo(vm, secondArg, bundleName, moduleName);
    GetArkUINodeModifiers()->getImageModifier()->setAlt(
        nativeNode, src.c_str(), bundleName.c_str(), moduleName.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetAlt(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetImageInterpolation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getImageModifier()->setImageInterpolation(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetImageInterpolation(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetImageInterpolation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto *nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetImageInterpolation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetColorFilterObject(const EcmaVM* vm, const Local<JSValueRef>& jsObjArg, ArkUINodeHandle nativeNode)
{
    Framework::JSColorFilter* colorFilter = nullptr;
    if (!jsObjArg->IsUndefined() && !jsObjArg->IsNull()) {
        colorFilter = static_cast<Framework::JSColorFilter*>(jsObjArg->ToObject(vm)->GetNativePointerField(vm, 0));
    } else {
        GetArkUINodeModifiers()->getImageModifier()->setColorFilter(
            nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return;
    }
    if (colorFilter && colorFilter->GetColorFilterMatrix().size() == COLOR_FILTER_MATRIX_SIZE) {
        GetArkUINodeModifiers()->getImageModifier()->setColorFilter(
            nativeNode, &(*colorFilter->GetColorFilterMatrix().begin()), COLOR_FILTER_MATRIX_SIZE);
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
            return;
        }
    }
    GetArkUINodeModifiers()->getImageModifier()->setColorFilter(
        nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
}

ArkUINativeModuleValue ImageBridge::SetColorFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> jsObjArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!jsObjArg->IsArray(vm) && !jsObjArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getImageModifier()->setColorFilter(
            nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return panda::JSValueRef::Undefined(vm);
    }
    if (jsObjArg->IsObject(vm) && !jsObjArg->IsArray(vm)) {
        auto drawingColorFilter = Ace::Framework::CreateDrawingColorFilter(info[1]);
        if (drawingColorFilter) {
            ImageModelNG::SetDrawingColorFilter(reinterpret_cast<FrameNode*>(nativeNode), drawingColorFilter);
            return panda::JSValueRef::Undefined(vm);
        }

        SetColorFilterObject(vm, jsObjArg, nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto array = panda::CopyableGlobal<panda::ArrayRef>(vm, jsObjArg);
    if (array->Length(vm) != COLOR_FILTER_MATRIX_SIZE) {
        GetArkUINodeModifiers()->getImageModifier()->setColorFilter(
            nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<float> colorFilter;
    for (size_t i = 0; i < array->Length(vm); i++) {
        auto value = array->GetValueAt(vm, jsObjArg, i);
        if (value->IsNumber()) {
            colorFilter.emplace_back(value->ToNumber(vm)->Value());
        } else {
            GetArkUINodeModifiers()->getImageModifier()->setColorFilter(
                nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    GetArkUINodeModifiers()->getImageModifier()->setColorFilter(
        nativeNode, &(*colorFilter.begin()), COLOR_FILTER_MATRIX_SIZE);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetColorFilter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetColorFilter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool value;
    if (secondArg->IsBoolean()) {
        value = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getImageModifier()->setImageDraggable(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->resetImageDraggable(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetImageDraggable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(INDEX_1);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(INDEX_2);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(INDEX_3);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(INDEX_4);
    if (topLeftArgs->IsUndefined() && topRightArgs->IsUndefined() && bottomLeftArgs->IsUndefined() &&
        bottomRightArgs->IsUndefined()) {
        GetArkUINodeModifiers()->getCommonModifier()->resetBorderRadius(nativeNode);
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
    auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto directionChanged = isRightToLeft && isLengthMetrics;
    uint32_t size = SIZE_OF_FOUR;
    ArkUI_Float32 values[size];
    int units[size];
    values[INDEX_0] = directionChanged ? topRight.Value() : topLeft.Value();
    units[INDEX_0] = directionChanged ? static_cast<int>(topRight.Unit()) : static_cast<int>(topLeft.Unit());
    values[INDEX_1] = directionChanged ? topLeft.Value() : topRight.Value();
    units[INDEX_1] = directionChanged ? static_cast<int>(topLeft.Unit()) : static_cast<int>(topRight.Unit());
    values[INDEX_2] = directionChanged ? bottomRight.Value() : bottomLeft.Value();
    units[INDEX_2] = directionChanged ? static_cast<int>(bottomRight.Unit()) : static_cast<int>(bottomLeft.Unit());
    values[INDEX_3] = directionChanged ? bottomLeft.Value() : bottomRight.Value();
    units[INDEX_3] = directionChanged ? static_cast<int>(bottomLeft.Unit()) : static_cast<int>(bottomRight.Unit());

    GetArkUINodeModifiers()->getImageModifier()->setImageBorderRadius(nativeNode, values, units, SIZE_OF_FOUR);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetImageBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetImageBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::SetBorder(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0:node info
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        GetArkUINodeModifiers()->getImageModifier()->setImageBorder(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<ArkUI_Float32> options;
    ParseOuterBorderRadius(runtimeCallInfo, vm, options); // Border Radius args start index
    GetArkUINodeModifiers()->getImageModifier()->setImageBorderWithValues(nativeNode, options.data(), options.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetImageBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0:node info
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetBorder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetImageOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0:node info
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (ImageModelNG::IsSrcSvgImage(frameNode)) {
        CommonBridge::SetOpacity(runtimeCallInfo);
    } else {
        Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1); // 1:value info
        double opacity;
        if (!ArkTSUtils::ParseJsDouble(vm, valueArg, opacity)) {
            GetArkUINodeModifiers()->getImageModifier()->resetImageOpacity(nativeNode);
        } else {
            GetArkUINodeModifiers()->getImageModifier()->setImageOpacity(nativeNode, opacity);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetImageOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0:node info
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetImageOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetImageTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0:node info
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (ImageModelNG::IsSrcSvgImage(frameNode)) {
        CommonBridge::SetTransition(runtimeCallInfo);
    } else {
        CommonBridge::SetTransitionPassThrough(runtimeCallInfo);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetImageTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0:node info
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    if (ImageModelNG::IsSrcSvgImage(frameNode)) {
        CommonBridge::ResetTransition(runtimeCallInfo);
    } else {
        CommonBridge::ResetTransitionPassThrough(runtimeCallInfo);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::EnableAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> enableValue = runtimeCallInfo->GetCallArgRef(1);

    if (enableValue->IsBoolean()) {
        bool enable = enableValue->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getImageModifier()->enableAnalyzer(nativeNode, enable);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::AnalyzerConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> configValue = runtimeCallInfo->GetCallArgRef(1);
    JSValueWrapper valueWrapper = configValue;
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, panda::NativePointerRef::New(vm, nullptr));
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    Framework::ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value nativeValue = nativeEngine->ValueToNapiValue(valueWrapper);
    GetArkUINodeModifiers()->getImageModifier()->analyzerConfig(nativeNode, nativeValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetOnComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getImageModifier()->setOnComplete(nativeNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(LoadImageSuccessEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                               LoadImageSuccessEvent& event) {
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
    GetArkUINodeModifiers()->getImageModifier()->setOnComplete(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetOnComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->setOnComplete(nativeNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetOnError(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(INDEX_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getImageModifier()->resetOnError(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(LoadImageFailEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                            LoadImageFailEvent& event) {
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
    GetArkUINodeModifiers()->getImageModifier()->setOnError(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetOnError(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetOnError(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::SetOnFinish(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getImageModifier()->resetImageOnFinish(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    GetArkUINodeModifiers()->getImageModifier()->setImageOnFinish(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetOnFinish(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetImageOnFinish(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG