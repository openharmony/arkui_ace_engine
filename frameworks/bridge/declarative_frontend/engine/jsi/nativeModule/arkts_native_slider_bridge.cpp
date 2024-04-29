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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
const char* SLIDER_NODEPTR_OF_UINODE = "nodePtr_";
panda::Local<panda::JSValueRef> JsSliderChangeCallback(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto vm = runtimeCallInfo->GetVM();
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (argc != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto valueArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto modeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!valueArg->IsNumber() || !modeArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    double value = valueArg->ToNumber(vm)->Value();
    int32_t mode = modeArg->ToNumber(vm)->Value();
    auto ref = runtimeCallInfo->GetThisRef();
    auto obj = ref->ToObject(vm);
    if (obj->GetNativePointerFieldCount() < NUM_1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = static_cast<FrameNode*>(obj->GetNativePointerField(0));
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    SliderModelNG::SetChangeValue(frameNode, value, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetShowTips(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> showTipArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> contentArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    bool showTips = false;
    if (showTipArg->IsBoolean()) {
        showTips = showTipArg->ToBoolean(vm)->Value();
    }
    
    std::string content;
    if (ArkTSUtils::ParseJsString(vm, contentArg, content)) {
        GetArkUINodeModifiers()->getSliderModifier()->setShowTips(nativeNode, showTips, content.c_str());
    } else {
        GetArkUINodeModifiers()->getSliderModifier()->setShowTips(nativeNode, showTips, nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetShowTips(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetShowTips(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetSliderStepSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension stepSize;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, stepSize, false)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetSliderStepSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    } else {
        if (LessNotEqual(stepSize.Value(), 0.0)) {
            GetArkUINodeModifiers()->getSliderModifier()->resetSliderStepSize(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }

        GetArkUINodeModifiers()->getSliderModifier()->setSliderStepSize(
            nativeNode, stepSize.Value(), static_cast<int>(stepSize.Unit()));
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetSliderStepSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetSliderStepSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetBlockSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    CalcDimension blockWidth;
    CalcDimension blockHeight;
    bool hasBlockWidth = ArkTSUtils::ParseJsDimensionVp(vm, secondArg, blockWidth);
    bool hasBlockHeight = ArkTSUtils::ParseJsDimensionVp(vm, thirdArg, blockHeight);
    if (!hasBlockWidth && !hasBlockHeight) {
        GetArkUINodeModifiers()->getSliderModifier()->resetBlockSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getSliderModifier()->setBlockSize(nativeNode,
        blockWidth.Value(), static_cast<int>(blockWidth.Unit()),
        blockHeight.Value(), static_cast<int>(blockHeight.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetBlockSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetBlockSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetTrackBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    CalcDimension trackBorderRadius;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, trackBorderRadius, true)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetTrackBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (LessNotEqual(trackBorderRadius.Value(), 0.0)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetTrackBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getSliderModifier()->setTrackBorderRadius(nativeNode,
        trackBorderRadius.Value(), static_cast<int>(trackBorderRadius.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetTrackBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetTrackBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetStepColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetStepColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSliderModifier()->setStepColor(nativeNode, color.GetValue());
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetStepColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetStepColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetBlockBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetBlockBorderColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSliderModifier()->setBlockBorderColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetBlockBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetBlockBorderColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetBlockBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    CalcDimension blockBorderWidth;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, blockBorderWidth)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetBlockBorderWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (LessNotEqual(blockBorderWidth.Value(), 0.0)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetBlockBorderWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getSliderModifier()->setBlockBorderWidth(nativeNode,
        blockBorderWidth.Value(), static_cast<int>(blockBorderWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetBlockBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetBlockBorderWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetBlockColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetBlockColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSliderModifier()->setBlockColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetBlockColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetBlockColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetTrackBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetTrackBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSliderModifier()->setTrackBackgroundColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetTrackBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetTrackBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetSelectColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetSelectColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSliderModifier()->setSelectColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetSelectColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetSelectColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetShowSteps(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool flag = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getSliderModifier()->setShowSteps(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetShowSteps(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetShowSteps(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetThickness(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    CalcDimension thickness;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, thickness, true)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetThickness(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getSliderModifier()->setThickness(nativeNode,
        thickness.Value(), static_cast<int>(thickness.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetThickness(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetThickness(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetBlockStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
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
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    SliderModelNG::ResetBlockType(frameNode);
    SliderModelNG::ResetBlockImage(frameNode);
    SliderModelNG::ResetBlockShape(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject()) {
        SliderModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    auto containerId = Container::CurrentId();
    SliderModelNG::SetBuilderFunc(frameNode,
        [vm, frameNode, obj = std::move(obj), containerId](
            SliderConfiguration config) -> RefPtr<FrameNode> {
            ContainerScope scope(containerId);
            auto context = ArkTSUtils::GetContext(vm);
            const char* keyOfSlider[] = { "value", "min", "max", "step", "enabled", "triggerChange" };
            Local<JSValueRef> valuesOfSlider[] = { panda::NumberRef::New(vm, config.value_),
                panda::NumberRef::New(vm, config.min_), panda::NumberRef::New(vm, config.max_),
                panda::NumberRef::New(vm, config.step_), panda::BooleanRef::New(vm, config.enabled_),
                panda::FunctionRef::New(vm, JsSliderChangeCallback) };
            auto slider = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keyOfSlider),
                keyOfSlider, valuesOfSlider);
            slider->SetNativePointerFieldCount(vm, 1);
            slider->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_2] = { context, slider };
            LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto jsObject = obj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, NUM_2);
            JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(), true, nullptr);
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr =
                resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, SLIDER_NODEPTR_OF_UINODE));
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
