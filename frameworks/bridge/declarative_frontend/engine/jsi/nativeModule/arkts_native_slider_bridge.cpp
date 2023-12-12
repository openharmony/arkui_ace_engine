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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_slider_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
ArkUINativeModuleValue SliderBridge::SetShowTips(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> showTipArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> contentArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    bool showTips = false;
    if (showTipArg->IsBoolean()) {
        showTips = showTipArg->ToBoolean(vm)->Value();
    }
    
    std::string content;
    if (ArkTSUtils::ParseJsString(vm, contentArg, content)) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().SetShowTips(nativeNode, showTips, content.c_str());
    } else {
        GetArkUIInternalNodeAPI()->GetSliderModifier().SetShowTips(nativeNode, showTips, nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetShowTips(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().ResetShowTips(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetSliderStepSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    CalcDimension stepSize;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, stepSize, false)) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().ResetSliderStepSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    } else {
        if (LessNotEqual(stepSize.Value(), 0.0)) {
            GetArkUIInternalNodeAPI()->GetSliderModifier().ResetSliderStepSize(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }

        GetArkUIInternalNodeAPI()->GetSliderModifier().SetSliderStepSize(
            nativeNode, stepSize.Value(), static_cast<int>(stepSize.Unit()));
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetSliderStepSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().ResetSliderStepSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetBlockSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    CalcDimension blockWidth;
    CalcDimension blockHeight;
    bool hasBlockWidth = ArkTSUtils::ParseJsDimensionVp(vm, secondArg, blockWidth);
    bool hasBlockHeight = ArkTSUtils::ParseJsDimensionVp(vm, thirdArg, blockHeight);
    if (!hasBlockWidth && !hasBlockHeight) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().ResetBlockSize(nativeNode);
    }

    GetArkUIInternalNodeAPI()->GetSliderModifier().SetBlockSize(nativeNode,
        blockWidth.Value(), static_cast<int>(blockWidth.Unit()),
        blockHeight.Value(), static_cast<int>(blockHeight.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetBlockSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().ResetBlockSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetTrackBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    CalcDimension trackBorderRadius;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, trackBorderRadius, true)) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().ResetTrackBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (LessNotEqual(trackBorderRadius.Value(), 0.0)) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().ResetTrackBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUIInternalNodeAPI()->GetSliderModifier().SetTrackBorderRadius(nativeNode,
        trackBorderRadius.Value(), static_cast<int>(trackBorderRadius.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetTrackBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().ResetTrackBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetStepColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().ResetStepColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetSliderModifier().SetStepColor(nativeNode, color.GetValue());
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetStepColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().ResetStepColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetBlockBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().ResetBlockBorderColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetSliderModifier().SetBlockBorderColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetBlockBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().ResetBlockBorderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetBlockBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    CalcDimension blockBorderWidth;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, blockBorderWidth)) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().ResetBlockBorderWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (LessNotEqual(blockBorderWidth.Value(), 0.0)) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().ResetBlockBorderWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUIInternalNodeAPI()->GetSliderModifier().SetBlockBorderWidth(nativeNode,
        blockBorderWidth.Value(), static_cast<int>(blockBorderWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetBlockBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().ResetBlockBorderWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetBlockColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().ResetBlockColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetSliderModifier().SetBlockColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetBlockColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().ResetBlockColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetTrackBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().ResetTrackBackgroundColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetSliderModifier().SetTrackBackgroundColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetTrackBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().ResetTrackBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetSelectColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
        Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().ResetSelectColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetSliderModifier().SetSelectColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetSelectColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().ResetSelectColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetShowSteps(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool flag = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().SetShowSteps(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetShowSteps(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().ResetShowSteps(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetThickness(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    CalcDimension thickness;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, thickness, true)) {
        GetArkUIInternalNodeAPI()->GetSliderModifier().ResetThickness(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUIInternalNodeAPI()->GetSliderModifier().SetThickness(nativeNode,
        thickness.Value(), static_cast<int>(thickness.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetThickness(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSliderModifier().ResetThickness(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetBlockStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[1]->IsObject()) {
        SliderBridge::ResetBlockStyle(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    auto jsObj = Framework::JSRef<Framework::JSObject>::Cast(info[1]);
    auto getType = jsObj->GetProperty("type");
    if (getType->IsNull() || !getType->IsNumber()) {
        SliderBridge::ResetBlockStyle(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    auto type = static_cast<SliderModel::BlockStyleType>(getType->ToNumber<int32_t>());
    if (type == SliderModel::BlockStyleType::IMAGE) {
        std::string src;
        auto image = jsObj->GetProperty("image");
        if (!Framework::JSShapeAbstract::ParseJsMedia(image, src)) {
            SliderBridge::ResetBlockStyle(runtimeCallInfo);
            return panda::JSValueRef::Undefined(vm);
        }
        std::string bundleName;
        std::string moduleName;
        Framework::JSViewAbstract::GetJsMediaBundleInfo(image, bundleName, moduleName);
        SliderModelNG::SetBlockImage(frameNode, src, bundleName, moduleName);
    } else if (type == SliderModel::BlockStyleType::SHAPE) {
        auto shape = jsObj->GetProperty("shape");
        if (!shape->IsObject()) {
            SliderBridge::ResetBlockStyle(runtimeCallInfo);
            return panda::JSValueRef::Undefined(vm);
        }
        Framework::JSShapeAbstract* shapeAbstract =
            Framework::JSRef<Framework::JSObject>::Cast(shape)->Unwrap<Framework::JSShapeAbstract>();
        if (shapeAbstract == nullptr) {
            SliderBridge::ResetBlockStyle(runtimeCallInfo);
            return panda::JSValueRef::Undefined(vm);
        }
        SliderModelNG::SetBlockShape(frameNode, shapeAbstract->GetBasicShape());
    }
    SliderModelNG::SetBlockType(frameNode, type);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetBlockStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    SliderModelNG::ResetBlockType(frameNode);
    SliderModelNG::ResetBlockImage(frameNode);
    SliderModelNG::ResetBlockShape(frameNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
