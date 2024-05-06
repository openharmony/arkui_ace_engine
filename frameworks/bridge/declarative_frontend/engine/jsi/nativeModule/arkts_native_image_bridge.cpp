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
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_image.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {
constexpr int32_t INDEX_0 = 0;      // Arg Index
constexpr int32_t INDEX_1 = 1;      // Arg Index
constexpr int32_t INDEX_2 = 2;      // Arg Index
constexpr int32_t INDEX_3 = 3;      // Arg Index
constexpr int32_t INDEX_4 = 4;      // Arg Index
constexpr int32_t SIZE_OF_FOUR = 4; // Border Radius array size
const std::vector<float> DEFAULT_COLOR_FILTER_MATRIX = {
    1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0
};

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

void PushDimensionsToVector(std::vector<ArkUIStringAndFloat>& results,
    const std::vector<std::optional<CalcDimension>>& optDimensions)
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

ArkUINativeModuleValue ImageBridge::SetImageShowSrc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::NativePointerRef::New(vm, nullptr));
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, panda::NativePointerRef::New(vm, nullptr));
    bool isCard = context->IsFormRender() && !container->IsDynamicRender();
    std::string src;
    int32_t resId = 0;
    if (info[0]->IsObject()) {
        Framework::JSRef<Framework::JSObject> jsObj = Framework::JSRef<Framework::JSObject>::Cast(info[0]);
        Framework::JSRef<Framework::JSVal> tmp = jsObj->GetProperty("id");
        if (!tmp->IsNull() && tmp->IsNumber()) {
            resId = tmp->ToNumber<int32_t>();
        }
    }
    bool srcValid = ArkTSUtils::ParseJsMedia(vm, secondArg, src);
    if (isCard && secondArg->IsString()) {
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
#if defined (PIXEL_MAP_SUPPORTED)
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
        GetArkUINodeModifiers()->getImageModifier()->resetAlt(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (ImageSourceInfo::ResolveURIType(src) == SrcType::NETWORK) {
        GetArkUINodeModifiers()->getImageModifier()->resetAlt(nativeNode);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetAlt(nativeNode);
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
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getImageModifier()->resetImageInterpolation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetColorFilterObject(const EcmaVM* vm, const Local<JSValueRef>& jsObjArg, ArkUINodeHandle nativeNode)
{
    Framework::JSColorFilter* colorFilter;
    if (!jsObjArg->IsUndefined() && !jsObjArg->IsNull()) {
        colorFilter = static_cast<Framework::JSColorFilter*>(jsObjArg->ToObject(vm)->GetNativePointerField(0));
    } else {
        GetArkUINodeModifiers()->getImageModifier()->setColorFilter(
            nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return;
    }
    if (colorFilter && colorFilter->GetColorFilterMatrix().size() == COLOR_FILTER_MATRIX_SIZE) {
        GetArkUINodeModifiers()->getImageModifier()->setColorFilter(
            nativeNode, &(*colorFilter->GetColorFilterMatrix().begin()), COLOR_FILTER_MATRIX_SIZE);
    } else {
        GetArkUINodeModifiers()->getImageModifier()->setColorFilter(
            nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return;
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
    if (!jsObjArg->IsArray(vm) && !jsObjArg->IsObject()) {
        GetArkUINodeModifiers()->getImageModifier()->setColorFilter(
            nativeNode, &(*DEFAULT_COLOR_FILTER_MATRIX.begin()), COLOR_FILTER_MATRIX_SIZE);
        return panda::JSValueRef::Undefined(vm);
    }
    if (jsObjArg->IsObject() && !jsObjArg->IsArray(vm)) {
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

ArkUINativeModuleValue ImageBridge::SetBorderRadius(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
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

    ArkTSUtils::ParseAllBorder(vm, topLeftArgs, topLeft);
    ArkTSUtils::ParseAllBorder(vm, topRightArgs, topRight);
    ArkTSUtils::ParseAllBorder(vm, bottomLeftArgs, bottomLeft);
    ArkTSUtils::ParseAllBorder(vm, bottomRightArgs, bottomRight);

    uint32_t size = SIZE_OF_FOUR;
    ArkUI_Float32 values[size];
    int units[size];

    values[INDEX_0] = topLeft.Value();
    units[INDEX_0] = static_cast<int>(topLeft.Unit());
    values[INDEX_1] = topRight.Value();
    units[INDEX_1] = static_cast<int>(topRight.Unit());
    values[INDEX_2] = bottomLeft.Value();
    units[INDEX_2] = static_cast<int>(bottomLeft.Unit());
    values[INDEX_3] = bottomRight.Value();
    units[INDEX_3] = static_cast<int>(bottomRight.Unit());

    GetArkUINodeModifiers()->getImageModifier()->setImageBorderRadius(nativeNode, values, units, SIZE_OF_FOUR);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageBridge::ResetBorderRadius(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
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
    GetArkUINodeModifiers()->getImageModifier()->setImageBorder(nativeNode);
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
} // namespace OHOS::Ace::NG