/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/slider/bridge/arkts_native_slider_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_color_metrics_linear_gradient.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "native_engine/impl/ark/ark_native_engine.h"
#include "napi/native_api.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int32_t NUM_3 = 3;
constexpr int32_t NUM_4 = 4;
constexpr int32_t NUM_5 = 5;
constexpr int32_t NUM_6 = 6;
constexpr int NUM_8 = 8;
constexpr int SLIDER_MIN = 0;
constexpr int SLIDER_MAX = 100;
constexpr int PARAM_ARR_LENGTH_1 = 1;
constexpr int PARAM_ARR_LENGTH_2 = 2;
const char* SLIDER_NODEPTR_OF_UINODE = "nodePtr_";
constexpr char ENTRIES_STRING[] = "entries";
constexpr char NEXT_STRING[] = "next";
constexpr char VALUE_STRING[] = "value";
constexpr char TEXT_STRING[] = "text";
constexpr char DONE_STRING[] = "done";
namespace {
struct SliderOptions {
    double value = 0;
    double min = 0;
    double max = 100;
    double step = 1;
    bool reverse = false;
    int32_t style = 0;
    int32_t direction = 1;
};

static void GetStep(SliderOptions& options)
{
    if (LessOrEqual(options.step, 0.0) || options.step > options.max - options.min) {
        options.step = 1;
    }
}

static void GetValue(SliderOptions& options)
{
    if (options.value < options.min) {
        options.value = options.min;
    }

    if (options.value > options.max) {
        options.value = options.max;
    }
}

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (firstArg->IsNativePointer(vm)) {
        nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        return true;
    }
    if (firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value()) {
        nativeNode = nullptr;
        return true;
    }

    return false;
}

bool IsJsView(const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    return firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
}

bool ConvertSliderGradientColor(const EcmaVM* vm, const Local<JSValueRef>& value, OHOS::Ace::NG::Gradient& gradient)
{
    if (!value->IsObject(vm)) {
        return false;
    }
    Framework::JSLinearGradient* jsLinearGradient =
        static_cast<Framework::JSLinearGradient*>(value->ToObject(vm)->GetNativePointerField(vm, 0));
    if (!jsLinearGradient) {
        return false;
    }

    size_t colorLength = jsLinearGradient->GetGradient().size();
    if (colorLength == 0) {
        return false;
    }
    for (size_t colorIndex = 0; colorIndex < colorLength; ++colorIndex) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(jsLinearGradient->GetGradient().at(colorIndex).first));
        gradientColor.SetDimension(jsLinearGradient->GetGradient().at(colorIndex).second);
        gradient.AddColor(gradientColor);
    }
    return true;
}

bool ConvertSliderMetricsGradientColor(
    const EcmaVM* vm, const Local<JSValueRef>& value, OHOS::Ace::NG::Gradient& gradient, bool isJsView = false)
{
    if (!value->IsObject(vm)) {
        return false;
    }
    Framework::JSColorMetricsLinearGradient* jsColorMetricsLinearGradient =
        static_cast<Framework::JSColorMetricsLinearGradient*>(value->ToObject(vm)->GetNativePointerField(vm, 0));
    if (!jsColorMetricsLinearGradient) {
        return false;
    }

    size_t colorLength = jsColorMetricsLinearGradient->GetColorMetricsGradient().size();
    if (colorLength == 0) {
        return false;
    }

    if (isJsView && colorLength == 1) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(
            LinearColor(jsColorMetricsLinearGradient->GetColorMetricsGradient().front().color));
        gradientColor.SetDimension(jsColorMetricsLinearGradient->GetColorMetricsGradient().front().offset);
        gradient.AddColor(gradientColor);
        gradient.AddColor(gradientColor);
        return true;
    }

    for (size_t colorIndex = 0; colorIndex < colorLength; ++colorIndex) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(
            LinearColor(jsColorMetricsLinearGradient->GetColorMetricsGradient().at(colorIndex).color));
        gradientColor.SetDimension(jsColorMetricsLinearGradient->GetColorMetricsGradient().at(colorIndex).offset);
        gradient.AddColor(gradientColor);
    }
    return true;
}

static void ParseStyleOptions(ArkUIRuntimeCallInfo* runtimeCallInfo, SliderOptions& options)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(5);     // 5: parameter index
    Local<JSValueRef> directionArg = runtimeCallInfo->GetCallArgRef(6); // 6: parameter index
    Local<JSValueRef> reverseArg = runtimeCallInfo->GetCallArgRef(7);   // 7: parameter index

    if (!reverseArg.IsNull() && !reverseArg->IsUndefined() && reverseArg->IsBoolean()) {
        options.reverse = reverseArg->ToBoolean(vm)->Value();
    }
    if (!styleArg.IsNull() && !styleArg->IsUndefined() && styleArg->IsNumber()) {
        auto tempStyle = styleArg->Int32Value(vm);
        if (tempStyle >= static_cast<int32_t>(SliderMode::OUTSET) &&
            tempStyle <= static_cast<int32_t>(SliderMode::CAPSULE)) {
            options.style = tempStyle;
        }
    }
    if (!directionArg.IsNull() && !directionArg->IsUndefined() && directionArg->IsNumber()) {
        auto tempDirection = directionArg->Int32Value(vm);
        if (tempDirection >= static_cast<int32_t>(Axis::VERTICAL) &&
            tempDirection <= static_cast<int32_t>(Axis::HORIZONTAL)) {
            options.direction = tempDirection;
        }
    }
}

static void ParseOptions(ArkUIRuntimeCallInfo* runtimeCallInfo, SliderOptions& options)
{
    static const double valueMin = -1000000.0f;
    options.value = valueMin;
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1); // 1: parameter index
    Local<JSValueRef> minArg = runtimeCallInfo->GetCallArgRef(2);   // 2: parameter index
    Local<JSValueRef> maxArg = runtimeCallInfo->GetCallArgRef(3);   // 3: parameter index
    Local<JSValueRef> stepArg = runtimeCallInfo->GetCallArgRef(4);  // 4: parameter index
    if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsNumber()) {
        options.value = valueArg->ToNumber(vm)->Value();
    }
    if (!minArg.IsNull() && !minArg->IsUndefined() && minArg->IsNumber()) {
        options.min = minArg->ToNumber(vm)->Value();
    }
    if (!maxArg.IsNull() && !maxArg->IsUndefined() && maxArg->IsNumber()) {
        options.max = maxArg->ToNumber(vm)->Value();
    }
    if (!stepArg.IsNull() && !stepArg->IsUndefined() && stepArg->IsNumber()) {
        options.step = stepArg->ToNumber(vm)->Value();
    }

    if (GreatOrEqual(options.min, options.max)) {
        options.min = SLIDER_MIN;
        options.max = SLIDER_MAX;
    }

    GetStep(options);
    GetValue(options);
    ParseStyleOptions(runtimeCallInfo, options);
}

static void ParsePrefixOrSuffixOptions(ArkUIRuntimeCallInfo* runtimeCallInfo,
    std::string& text, std::string& desc, std::string& level, bool& group)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> textArg = Local<JSValueRef>();
    Local<JSValueRef> descriptionArg = Local<JSValueRef>();
    Local<JSValueRef> levelArg = Local<JSValueRef>();
    Local<JSValueRef> groupArg = Local<JSValueRef>();
    if (runtimeCallInfo->GetArgsNumber() < NUM_6) {
        Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(NUM_2);
        textArg = optionsArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "accessibilityText"));
        descriptionArg =
            optionsArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "accessibilityDescription"));
        levelArg = optionsArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "accessibilityLevel"));
        groupArg = optionsArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "accessibilityGroup"));
    } else {
        textArg = runtimeCallInfo->GetCallArgRef(NUM_2);
        descriptionArg = runtimeCallInfo->GetCallArgRef(NUM_3);
        levelArg = runtimeCallInfo->GetCallArgRef(NUM_4);
        groupArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    }

    if (!textArg.IsNull() && !textArg->IsUndefined()) {
        ArkTSUtils::ParseJsString(vm, textArg, text);
    }

    if (!descriptionArg.IsNull() && !descriptionArg->IsUndefined()) {
        ArkTSUtils::ParseJsString(vm, descriptionArg, desc);
    }

    if (!levelArg.IsNull() && !levelArg->IsUndefined()) {
        ArkTSUtils::ParseJsString(vm, levelArg, level);
    }
    if (!groupArg.IsNull() && !groupArg->IsUndefined() && groupArg->IsBoolean()) {
        group = groupArg->ToBoolean(vm)->Value();
    }
}

RefPtr<NG::UINode> SetPrefixOrSuffixBuilderNode(EcmaVM* vm, const Local<panda::ObjectRef>& jsObject)
{
    CHECK_NULL_RETURN(vm, nullptr);
    auto builderNodeParam = ArkTSUtils::GetProperty(vm, jsObject, "builderNode_");
    if (builderNodeParam->IsObject(vm)) {
        auto builderNodeObject = builderNodeParam->ToObject(vm);
        auto nodePtr = ArkTSUtils::GetProperty(vm, builderNodeObject, "nodePtr_");
        if (!(nodePtr.IsEmpty() || nodePtr->IsNull() || nodePtr->IsUndefined())) {
            auto* node = nodePtr->ToNativePointer(vm)->Value();
            auto* myUINode = reinterpret_cast<NG::UINode*>(node);
            if (!myUINode) {
                return nullptr;
            }
            auto refPtrUINode = AceType::Claim(myUINode);
            return refPtrUINode;
        }
    }
    return nullptr;
}

void ParseSliderValueObject(const EcmaVM* vm, const Local<JSValueRef>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction(vm));
    panda::Local<panda::FunctionRef> func = changeEventVal->ToObject(vm);
    NG::FrameNode* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    std::function<void(float)> callback = [vm, weakNode = AceType::WeakClaim(frameNode),
                                              func = panda::CopyableGlobal(vm, func)](float value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        panda::Local<panda::NumberRef> numberParam = panda::NumberRef::New(vm, value);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { numberParam };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getSliderModifier()->setOnChangeEvent(reinterpret_cast<void*>(&callback));
}
} // namespace

void SliderBridge::RegisterSliderAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setShowTips", "resetShowTips", "setSliderStepSize",
        "resetSliderStepSize", "setBlockSize", "resetBlockSize", "setTrackBorderRadius", "resetTrackBorderRadius",
        "setStepColor", "resetStepColor", "setBlockBorderColor", "resetBlockBorderColor", "setBlockBorderWidth",
        "resetBlockBorderWidth", "setBlockColor", "resetBlockColor", "setTrackBackgroundColor",
        "resetTrackBackgroundColor", "setTrackColorMetrics", "resetTrackColorMetrics", "setSelectColor",
        "resetSelectColor", "setShowSteps", "resetShowSteps", "setThickness", "resetThickness", "setBlockStyle",
        "resetBlockStyle", "setValidSlideRange", "resetValidSlideRange", "setSelectedBorderRadius",
        "resetSelectedBorderRadius", "setInteractionMode", "resetInteractionMode", "setMinResponsiveDistance",
        "resetMinResponsiveDistance", "setContentModifierBuilder", "setSliderOptions", "setEnableHapticFeedback",
        "resetEnableHapticFeedback", "setOnChange", "resetOnChange", "setPrefix", "resetPrefix", "setSuffix",
        "resetSuffix", "setDigitalCrownSensitivity", "resetDigitalCrownSensitivity", "setMinLabel", "setMaxLabel" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::CreateSlider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetShowTips),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetShowTips),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetSliderStepSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetSliderStepSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetTrackBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetTrackBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetStepColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetStepColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockBorderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockBorderColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockBorderWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockBorderWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetTrackBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetTrackBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetTrackColorMetrics),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetTrackColorMetrics),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetSelectColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetSelectColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetShowSteps),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetShowSteps),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetThickness),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetThickness),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetValidSlideRange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetValidSlideRange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetSelectedBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetSelectedBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetInteractionMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetInteractionMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetMinResponsiveDistance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetMinResponsiveDistance),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetContentModifierBuilder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetSliderOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetPrefix),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetPrefix),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetSuffix),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetSuffix),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetDigitalCrownSensitivity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetDigitalCrownSensitivity),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetMinLabel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetMaxLabel),
    };

    auto slider = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "slider"), slider);
}

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
    if (obj->GetNativePointerFieldCount(vm) < NUM_1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = static_cast<FrameNode*>(obj->GetNativePointerField(vm, 0));
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    SliderModelNG::SetChangeValue(frameNode, value, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::CreateSlider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    static const double valueMin = -1000000.0f;
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    SliderOptions options;
    options.value = valueMin; // value:Current progress value. The default value is min.

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getSliderModifier()->createSlider(
            options.value, options.step, options.min, options.max);
        return panda::JSValueRef::Undefined(vm);
    }

    auto paramObj = firstArg->ToObject(vm);
    auto getValue = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
    auto getMin = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "min"));
    auto getMax = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "max"));
    auto getStep = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "step"));
    auto getStyle = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "style"));
    auto direction = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "direction"));
    auto isReverse = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "reverse"));
    Local<JSValueRef> changeEventVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "$value"));
    if (!getValue->IsNull() && getValue->IsObject(vm)) {
        Local<panda::ObjectRef> valueObj = getValue->ToObject(vm);
        auto valueProperty = valueObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        changeEventVal = valueObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));
        if (valueProperty->IsNumber()) {
            options.value = valueProperty->ToNumber(vm)->Value();
        }
    } else if (!changeEventVal->IsNull()) {
        if (getValue->IsNumber()) {
            options.value = getValue->ToNumber(vm)->Value();
        }
    } else if (!getValue->IsNull() && getValue->IsNumber()) {
        options.value = getValue->ToNumber(vm)->Value();
    }

    if (!getMin->IsNull() && getMin->IsNumber()) {
        options.min = getMin->ToNumber(vm)->Value();
    }

    if (!getMax->IsNull() && getMax->IsNumber()) {
        options.max = getMax->ToNumber(vm)->Value();
    }

    if (!getStep->IsNull() && getStep->IsNumber()) {
        options.step = getStep->ToNumber(vm)->Value();
    }

    if (!isReverse->IsNull() && isReverse->IsBoolean()) {
        options.reverse = isReverse->ToBoolean(vm)->Value();
    }

    if (GreatOrEqual(options.min, options.max)) {
        options.min = SLIDER_MIN;
        options.max = SLIDER_MAX;
    }

    GetStep(options);
    if (!getStyle->IsNull() && getStyle->IsNumber()) {
        options.style = static_cast<int32_t>(getStyle->ToNumber(vm)->Value());
    }

    if (!direction->IsNull() && direction->IsNumber()) {
        options.direction = static_cast<int32_t>(direction->ToNumber(vm)->Value());
    }
    if (options.direction != static_cast<int32_t>(Axis::VERTICAL)) {
        options.direction = static_cast<int32_t>(Axis::HORIZONTAL);
    }

    GetArkUINodeModifiers()->getSliderModifier()->createSlider(options.value, options.step, options.min, options.max);
    GetArkUINodeModifiers()->getSliderModifier()->setSliderStyle(nullptr, options.style);
    GetArkUINodeModifiers()->getSliderModifier()->setDirection(nullptr, options.direction);
    GetArkUINodeModifiers()->getSliderModifier()->setReverse(nullptr, options.reverse);
    if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction(vm)) {
        ParseSliderValueObject(vm, changeEventVal);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetShowTips(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> showTipArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> contentArg = runtimeCallInfo->GetCallArgRef(NUM_2);

    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool showTips = false;
    if (showTipArg->IsBoolean()) {
        showTips = showTipArg->ToBoolean(vm)->Value();
    }

    std::string content;
    RefPtr<ResourceObject> strResObj;
    if (ArkTSUtils::ParseJsString(vm, contentArg, content, strResObj)) {
        auto strRawPtr = AceType::RawPtr(strResObj);
        GetArkUINodeModifiers()->getSliderModifier()->setShowTipsPtr(nativeNode, showTips, content.c_str(), strRawPtr);
    } else {
        GetArkUINodeModifiers()->getSliderModifier()->setShowTipsPtr(nativeNode, showTips, nullptr, nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetShowTips(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSliderModifier()->resetShowTips(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetSliderStepSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension stepSize;
    if (IsJsView(firstArg, vm) && !ArkTSUtils::ParseJsDimensionVp(vm, secondArg, stepSize, false)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetSliderStepSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (!IsJsView(firstArg, vm) && !ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, stepSize, false)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetSliderStepSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (LessNotEqual(stepSize.Value(), 0.0)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetSliderStepSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSliderModifier()->setSliderStepSize(
        nativeNode, stepSize.Value(), static_cast<int>(stepSize.Unit()));

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
    Local<JSValueRef> secondArg = Local<JSValueRef>();
    Local<JSValueRef> thirdArg = Local<JSValueRef>();
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm)) {
        Local<JSValueRef> sizeOptionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
        if (!sizeOptionArg->IsNull() && !sizeOptionArg->IsUndefined() && sizeOptionArg->IsObject(vm)) {
            secondArg = sizeOptionArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
            thirdArg = sizeOptionArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
        } else {
            GetArkUINodeModifiers()->getSliderModifier()->resetBlockSize(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
        thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    }

    CalcDimension blockWidth;
    CalcDimension blockHeight;
    bool hasBlockWidth = ArkTSUtils::ParseJsDimensionVp(vm, secondArg, blockWidth);
    bool hasBlockHeight = ArkTSUtils::ParseJsDimensionVp(vm, thirdArg, blockHeight);
    if (!hasBlockWidth && !hasBlockHeight) {
        GetArkUINodeModifiers()->getSliderModifier()->resetBlockSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSliderModifier()->setBlockSize(nativeNode, blockWidth.Value(),
        static_cast<int>(blockWidth.Unit()), blockHeight.Value(), static_cast<int>(blockHeight.Unit()));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension trackBorderRadius;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, trackBorderRadius, true)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetTrackBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (LessNotEqual(trackBorderRadius.Value(), 0.0)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetTrackBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSliderModifier()->setTrackBorderRadius(
        nativeNode, trackBorderRadius.Value(), static_cast<int>(trackBorderRadius.Unit()));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto frameNode = IsJsView(firstArg, vm)
                         ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                         : nativeNode;
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetStepColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getSliderModifier()->setStepColorPtr(nativeNode, color.GetValue(), colorRawPtr);
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto frameNode = IsJsView(firstArg, vm)
                         ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                         : nativeNode;
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetBlockBorderColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getSliderModifier()->setBlockBorderColorPtr(nativeNode, color.GetValue(), colorRawPtr);
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension blockBorderWidth;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, blockBorderWidth)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetBlockBorderWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (LessNotEqual(blockBorderWidth.Value(), 0.0)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetBlockBorderWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSliderModifier()->setBlockBorderWidth(
        nativeNode, blockBorderWidth.Value(), static_cast<int>(blockBorderWidth.Unit()));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Gradient gradient;
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto frameNode = IsJsView(firstArg, vm)
                         ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                         : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
    if (ConvertSliderGradientColor(vm, secondArg, gradient)) {
        ArkUIGradientType gradientObj;
        auto colorLength = gradient.GetColors().size();
        std::vector<uint32_t> colorValues;
        std::vector<ArkUILengthType> offsetValues;
        if (colorLength <= 0) {
            GetArkUINodeModifiers()->getSliderModifier()->resetBlockColor(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        for (int32_t i = 0; i < static_cast<int32_t>(colorLength); i++) {
            colorValues.push_back(gradient.GetColors()[i].GetLinearColor().GetValue());
            offsetValues.push_back(
                ArkUILengthType { .number = static_cast<ArkUI_Float32>(gradient.GetColors()[i].GetDimension().Value()),
                    .unit = static_cast<int8_t>(gradient.GetColors()[i].GetDimension().Unit()) });
        }
        gradientObj.color = colorValues.data();
        gradientObj.offset = offsetValues.data();
        GetArkUINodeModifiers()->getSliderModifier()->setLinearBlockColor(nativeNode, &gradientObj, colorLength);
    } else if (ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getSliderModifier()->setBlockColorPtr(nativeNode, color.GetValue(), colorRawPtr);
    } else {
        GetArkUINodeModifiers()->getSliderModifier()->resetBlockColor(nativeNode);
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Gradient gradient;
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto frameNode = IsJsView(firstArg, vm)
                         ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                         : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
    if (ConvertSliderGradientColor(vm, secondArg, gradient)) {
        ArkUIGradientType gradientObj;
        auto colorLength = gradient.GetColors().size();
        std::vector<uint32_t> colorValues;
        std::vector<ArkUILengthType> offsetValues;
        GetArkUINodeModifiers()->getSliderModifier()->resetTrackBackgroundColor(nativeNode);
        if (colorLength <= 0) {
            return panda::JSValueRef::Undefined(vm);
        }
        for (int32_t i = 0; i < static_cast<int32_t>(colorLength); i++) {
            colorValues.push_back(gradient.GetColors()[i].GetLinearColor().GetValue());
            offsetValues.push_back(
                ArkUILengthType { .number = static_cast<ArkUI_Float32>(gradient.GetColors()[i].GetDimension().Value()),
                    .unit = static_cast<int8_t>(gradient.GetColors()[i].GetDimension().Unit()) });
        }

        gradientObj.color = &(*colorValues.begin());
        gradientObj.offset = &(*offsetValues.begin());
        GetArkUINodeModifiers()->getSliderModifier()->setLinearTrackBackgroundColor(
            nativeNode, &gradientObj, colorLength);
    } else if (ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getSliderModifier()->setTrackBackgroundColorPtr(
            nativeNode, color.GetValue(), colorRawPtr);
    } else {
        GetArkUINodeModifiers()->getSliderModifier()->resetTrackBackgroundColor(nativeNode);
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

ArkUINativeModuleValue SliderBridge::SetTrackColorMetrics(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Gradient gradient;
    RefPtr<ResourceObject> colorResObj;
    bool isJsView = IsJsView(firstArg, vm);
    auto frameNode = isJsView
                         ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                         : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
    if (ConvertSliderMetricsGradientColor(vm, secondArg, gradient, isJsView)) {
        ArkUIGradientType gradientObj;
        auto colorLength = gradient.GetColors().size();
        std::vector<uint32_t> colorValues;
        std::vector<ArkUILengthType> offsetValues;
        GetArkUINodeModifiers()->getSliderModifier()->resetTrackBackgroundColor(nativeNode);
        if (colorLength <= 0) {
            return panda::JSValueRef::Undefined(vm);
        }
        for (int32_t i = 0; i < static_cast<int32_t>(colorLength); i++) {
            colorValues.push_back(gradient.GetColors()[i].GetLinearColor().GetValue());
            offsetValues.push_back(
                ArkUILengthType { .number = static_cast<ArkUI_Float32>(gradient.GetColors()[i].GetDimension().Value()),
                    .unit = static_cast<int8_t>(gradient.GetColors()[i].GetDimension().Unit()) });
        }

        gradientObj.color = &(*colorValues.begin());
        gradientObj.offset = &(*offsetValues.begin());
        GetArkUINodeModifiers()->getSliderModifier()->setLinearTrackBackgroundColor(
            nativeNode, &gradientObj, colorLength);
    } else {
        GetArkUINodeModifiers()->getSliderModifier()->resetTrackBackgroundColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetTrackColorMetrics(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Gradient gradient;
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto frameNode = IsJsView(firstArg, vm)
                         ? reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode())
                         : nativeNode;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(frameNode);
    if (ConvertSliderGradientColor(vm, secondArg, gradient)) {
        ArkUIGradientType gradientObj;
        auto colorLength = gradient.GetColors().size();
        std::vector<uint32_t> colorValues;
        std::vector<ArkUILengthType> offsetValues;
        if (colorLength <= 0) {
            GetArkUINodeModifiers()->getSliderModifier()->resetSelectColor(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }

        for (int32_t i = 0; i < static_cast<int32_t>(colorLength); i++) {
            colorValues.push_back(gradient.GetColors()[i].GetLinearColor().GetValue());
            offsetValues.push_back(
                ArkUILengthType { .number = static_cast<ArkUI_Float32>(gradient.GetColors()[i].GetDimension().Value()),
                    .unit = static_cast<int8_t>(gradient.GetColors()[i].GetDimension().Unit()) });
        }

        gradientObj.color = &(*colorValues.begin());
        gradientObj.offset = &(*offsetValues.begin());
        GetArkUINodeModifiers()->getSliderModifier()->setLinearSelectColor(nativeNode, &gradientObj, colorLength);
    } else if (ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getSliderModifier()->setSelectColorPtr(nativeNode, color.GetValue(), colorRawPtr);
    } else {
        GetArkUINodeModifiers()->getSliderModifier()->resetSelectColor(nativeNode);
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool flag = secondArg->ToBoolean(vm)->Value();
    if ((runtimeCallInfo->GetArgsNumber() < NUM_3) || (!runtimeCallInfo->GetCallArgRef(NUM_2)->IsObject(vm))) {
        GetArkUINodeModifiers()->getSliderModifier()->setShowSteps(nativeNode, flag);
        return panda::JSValueRef::Undefined(vm);
    }
    StepOptions optionsMap {};
    Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto stepsMap = optionsArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "stepsAccessibility"));
    if (!stepsMap.IsNull() && !stepsMap->IsUndefined() && stepsMap->IsObject(vm)) {
        SliderBridge::ParseStepOptionsMap(vm, stepsMap, optionsMap);
    }
    if (optionsMap.size() > 0) {
        auto optionLength = NUM_0;
        auto options = new ArkUISliderShowStepOptions[optionsMap.size()];
        for (auto& option : optionsMap) {
            options[optionLength].step = option.first;
            options[optionLength].text = option.second.c_str();
            optionLength++;
        }
        GetArkUINodeModifiers()->getSliderModifier()->setShowStepsWithOptions(nativeNode, flag, options, optionLength);
        delete[] options;
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension thickness;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, thickness, true)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetThickness(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSliderModifier()->setThickness(
        nativeNode, thickness.Value(), static_cast<int>(thickness.Unit()));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = nativeNode ? reinterpret_cast<FrameNode*>(nativeNode)
                                 : reinterpret_cast<FrameNode*>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (!runtimeCallInfo->GetCallArgRef(NUM_1)->IsObject(vm)) {
        SliderBridge::ResetBlockStyle(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> styleOptionArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    auto getType = styleOptionArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (getType->IsNull() || !getType->IsNumber()) {
        SliderBridge::ResetBlockStyle(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    auto type = static_cast<SliderModel::BlockStyleType>(getType->ToNumber(vm)->Value());
    if (type == SliderModel::BlockStyleType::IMAGE) {
        std::string src;
        RefPtr<ResourceObject> mediaResObj;
        auto image = styleOptionArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "image"));
        if (!ArkTSUtils::ParseJsMedia(vm, image, src, mediaResObj)) {
            SliderBridge::ResetBlockStyle(runtimeCallInfo);
            return panda::JSValueRef::Undefined(vm);
        }
        std::string bundleName;
        std::string moduleName;
        ArkTSUtils::GetJsMediaBundleInfo(vm, image, bundleName, moduleName);
        SliderModelNG::SetBlockImage(frameNode, src, bundleName, moduleName);
        if (SystemProperties::ConfigChangePerform()) {
            SliderModelNG::CreateWithMediaResourceObj(frameNode, mediaResObj, bundleName, moduleName);
        }
    } else if (type == SliderModel::BlockStyleType::SHAPE) {
        auto shape = styleOptionArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "shape"));
        if (!shape->IsObject(vm)) {
            SliderBridge::ResetBlockStyle(runtimeCallInfo);
            return panda::JSValueRef::Undefined(vm);
        }
        auto BasicShape = ArkTSUtils::GetJSBasicShape(vm, shape);
        if (BasicShape == nullptr) {
            SliderBridge::ResetBlockStyle(runtimeCallInfo);
            return panda::JSValueRef::Undefined(vm);
        }
        SliderModelNG::SetBlockShape(frameNode, BasicShape);
    }
    SliderModelNG::SetBlockType(frameNode, type);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetBlockStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = nativeNode ? reinterpret_cast<FrameNode*>(nativeNode)
                                 : reinterpret_cast<FrameNode*>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    SliderModelNG::ResetBlockType(frameNode);
    SliderModelNG::ResetBlockImage(frameNode);
    SliderModelNG::ResetBlockShape(frameNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetValidSlideRange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!runtimeCallInfo->GetCallArgRef(NUM_1)->IsObject(vm)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetSliderValidSlideRange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    float from = std::numeric_limits<float>::infinity();
    float to = std::numeric_limits<float>::infinity();

    Local<JSValueRef> fromArg = Local<JSValueRef>();
    Local<JSValueRef> toArg = Local<JSValueRef>();
    Local<JSValueRef> rangeOptionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (rangeOptionArg->IsObject(vm)) {
        fromArg = rangeOptionArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "from"));
        toArg = rangeOptionArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, "to"));
    }

    if (!fromArg.IsNull() && !fromArg->IsUndefined() && fromArg->IsNumber()) {
        from = fromArg->ToNumber(vm)->Value();
    }
    if (!toArg.IsNull() && !toArg->IsUndefined() && toArg->IsNumber()) {
        to = toArg->ToNumber(vm)->Value();
    }
    if ((std::isinf(from) && std::isinf(to)) || std::isnan(from) || std::isnan(to)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetSliderValidSlideRange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto* frameNode = nativeNode ? reinterpret_cast<FrameNode*>(nativeNode)
                                 : reinterpret_cast<FrameNode*>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    SliderModelNG::SetValidSlideRange(frameNode, from, to);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetValidSlideRange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetSliderValidSlideRange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetSelectedBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension borderRadius;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, borderRadius, true)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetSelectedBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    if (LessNotEqual(borderRadius.Value(), 0.0)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetSelectedBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSliderModifier()->setSelectedBorderRadius(
        nativeNode, borderRadius.Value(), static_cast<int>(borderRadius.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetSelectedBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetSelectedBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetInteractionMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getSliderModifier()->resetInteractionMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t interactionMode = secondArg->Int32Value(vm);
    int32_t lowRange = static_cast<int32_t>(SliderModel::SliderInteraction::SLIDE_AND_CLICK);
    int32_t upRange = static_cast<int32_t>(SliderModel::SliderInteraction::SLIDE_AND_CLICK_UP);
    if (IsJsView(nodeArg, vm) && (interactionMode < lowRange || interactionMode > upRange)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetInteractionMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSliderModifier()->setInteractionMode(nativeNode, interactionMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetInteractionMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetInteractionMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetMinResponsiveDistance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getSliderModifier()->resetMinResponsiveDistance(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    float distance = secondArg->ToNumber(vm)->Value();
    GetArkUINodeModifiers()->getSliderModifier()->setMinResponsiveDistance(nativeNode, distance);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetMinResponsiveDistance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetMinResponsiveDistance(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = nativeNode ? reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value())
                                 : reinterpret_cast<FrameNode*>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (!secondArg->IsObject(vm)) {
        SliderModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    auto containerId = Container::CurrentId();
    SliderModelNG::SetBuilderFunc(
        frameNode, [vm, frameNode, obj = std::move(obj), containerId](SliderConfiguration config) -> RefPtr<FrameNode> {
            ContainerScope scope(containerId);
            auto context = ArkTSUtils::GetContext(vm);
            const char* keyOfSlider[] = { "value", "min", "max", "step", "enabled", "triggerChange" };
            Local<JSValueRef> valuesOfSlider[] = { panda::NumberRef::New(vm, config.value_),
                panda::NumberRef::New(vm, config.min_), panda::NumberRef::New(vm, config.max_),
                panda::NumberRef::New(vm, config.step_), panda::BooleanRef::New(vm, config.enabled_),
                panda::FunctionRef::New(vm, JsSliderChangeCallback) };
            auto slider =
                panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keyOfSlider), keyOfSlider, valuesOfSlider);
            slider->SetNativePointerFieldCount(vm, 1);
            slider->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_2] = { context, slider };
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto jsObject = obj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, NUM_2);
            panda::JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
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

ArkUINativeModuleValue SliderBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(nativeNodeArg, vm);

    auto frameNode =
        nativeNode ? reinterpret_cast<FrameNode*>(nativeNode) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));

    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getToggleModifier()->resetToggleOnChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(float, int32_t)> callback = [vm, node = AceType::WeakClaim(frameNode),
                                                       func = panda::CopyableGlobal(vm, func),
                                                       isJsView](float number, int32_t mode) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);

        panda::Local<panda::NumberRef> numberParam = panda::NumberRef::New(vm, number);
        panda::Local<panda::NumberRef> modeParam = panda::NumberRef::New(vm, mode);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = { numberParam, modeParam };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);

        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSliderModifier()->setOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetSliderOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    auto sliderModifier = GetArkUINodeModifiers()->getSliderModifier();
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_EQUAL_RETURN(runtimeCallInfo->GetArgsNumber() != NUM_8, true, panda::JSValueRef::Undefined(vm));
    SliderOptions options;
    ParseOptions(runtimeCallInfo, options);
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto pointer = nodeArg->ToNativePointer(vm);
    CHECK_EQUAL_RETURN(pointer.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(pointer->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    sliderModifier->setStep(nativeNode, options.step);
    sliderModifier->setMinLabel(nativeNode, options.min);
    sliderModifier->setMaxLabel(nativeNode, options.max);
    sliderModifier->setSliderValue(nativeNode, options.value);
    sliderModifier->setSliderStyle(nativeNode, options.style);
    sliderModifier->setDirection(nativeNode, options.direction);
    sliderModifier->setReverse(nativeNode, options.reverse);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableHapticFeedbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto sliderModifier = nodeModifiers->getSliderModifier();
    CHECK_NULL_RETURN(sliderModifier, panda::NativePointerRef::New(vm, nullptr));
    if (enableHapticFeedbackArg->IsBoolean()) {
        bool value = enableHapticFeedbackArg->ToBoolean(vm)->Value();
        sliderModifier->setEnableHapticFeedback(nativeNode, value);
    } else {
        sliderModifier->resetEnableHapticFeedback(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto sliderModifier = nodeModifiers->getSliderModifier();
    CHECK_NULL_RETURN(sliderModifier, panda::NativePointerRef::New(vm, nullptr));
    sliderModifier->resetEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetPrefix(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (IsJsView(nodeArg, vm)) {
        JsSetPrefix(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    if (runtimeCallInfo->GetArgsNumber() < NUM_3) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> prefixArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto prefixNode = nodePtr(prefixArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(prefixNode, panda::NativePointerRef::New(vm, nullptr));

    std::string text = "";
    std::string desc = "";
    std::string level = "";
    bool group = false;
    ParsePrefixOrSuffixOptions(runtimeCallInfo, text, desc, level, group);
    ArkUISliderCustomContentOptions options;
    options.accessibilityText = text.c_str();
    options.accessibilityDescription = desc.c_str();
    options.accessibilityLevel = level.c_str();
    options.accessibilityGroup = group;

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto sliderModifier = nodeModifiers->getSliderModifier();
    CHECK_NULL_RETURN(sliderModifier, panda::NativePointerRef::New(vm, nullptr));
    sliderModifier->setPrefix(nativeNode, prefixNode, static_cast<ArkUISliderCustomContentOptions*>(&options));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetPrefix(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));

    Local<JSValueRef> prefixArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto prefixNode = nodePtr(prefixArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(prefixNode, panda::NativePointerRef::New(vm, nullptr));

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));

    auto sliderModifier = nodeModifiers->getSliderModifier();
    CHECK_NULL_RETURN(sliderModifier, panda::NativePointerRef::New(vm, nullptr));
    sliderModifier->resetPrefix(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::JsSetPrefix(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (!secondArg->IsObject(vm)) {
        SliderBridge::ResetPrefix(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }

    RefPtr<NG::UINode> prefixNode = nullptr;
    if (!secondArg.IsNull() && !secondArg->IsUndefined()) {
        auto contentObject = secondArg->ToObject(vm);
        if (ArkTSUtils::HasProperty(vm, contentObject, "builderNode_")) {
            prefixNode = SetPrefixOrSuffixBuilderNode(vm, contentObject);
        }
    }

    std::string text = "";
    std::string desc = "";
    std::string level = "";
    bool group = false;

    if (!thirdArg.IsNull() && !thirdArg->IsUndefined() && thirdArg->IsObject(vm)) {
        ParsePrefixOrSuffixOptions(runtimeCallInfo, text, desc, level, group);
    }
    ArkUISliderCustomContentOptions options;
    options.accessibilityText = text.c_str();
    options.accessibilityDescription = desc.c_str();
    options.accessibilityLevel = level.c_str();
    options.accessibilityGroup = group;

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto sliderModifier = nodeModifiers->getSliderModifier();
    CHECK_NULL_RETURN(sliderModifier, panda::NativePointerRef::New(vm, nullptr));
    sliderModifier->setPrefix(nativeNode, reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(prefixNode)),
        static_cast<ArkUISliderCustomContentOptions*>(&options));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetSuffix(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (IsJsView(nodeArg, vm)) {
        JsSetSuffix(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    if (runtimeCallInfo->GetArgsNumber() < NUM_3) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> suffixArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto suffixNode = nodePtr(suffixArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(suffixNode, panda::NativePointerRef::New(vm, nullptr));

    std::string text = "";
    std::string desc = "";
    std::string level = "";
    bool group = false;
    ParsePrefixOrSuffixOptions(runtimeCallInfo, text, desc, level, group);
    ArkUISliderCustomContentOptions options;
    options.accessibilityText = text.c_str();
    options.accessibilityDescription = desc.c_str();
    options.accessibilityLevel = level.c_str();
    options.accessibilityGroup = group;

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto sliderModifier = nodeModifiers->getSliderModifier();
    CHECK_NULL_RETURN(sliderModifier, panda::NativePointerRef::New(vm, nullptr));
    sliderModifier->setSuffix(nativeNode, suffixNode, static_cast<ArkUISliderCustomContentOptions*>(&options));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetSuffix(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, panda::NativePointerRef::New(vm, nullptr));

    Local<JSValueRef> suffixArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto suffixNode = nodePtr(suffixArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(suffixNode, panda::NativePointerRef::New(vm, nullptr));

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));

    auto sliderModifier = nodeModifiers->getSliderModifier();
    CHECK_NULL_RETURN(sliderModifier, panda::NativePointerRef::New(vm, nullptr));
    sliderModifier->resetSuffix(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::JsSetSuffix(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (!secondArg->IsObject(vm)) {
        SliderBridge::ResetSuffix(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }

    RefPtr<NG::UINode> suffixNode = nullptr;
    if (!secondArg.IsNull() && !secondArg->IsUndefined()) {
        auto contentObject = secondArg->ToObject(vm);
        if (ArkTSUtils::HasProperty(vm, contentObject, "builderNode_")) {
            suffixNode = SetPrefixOrSuffixBuilderNode(vm, contentObject);
        }
    }

    std::string text = "";
    std::string desc = "";
    std::string level = "";
    bool group = false;

    if (!thirdArg.IsNull() && !thirdArg->IsUndefined() && thirdArg->IsObject(vm)) {
        ParsePrefixOrSuffixOptions(runtimeCallInfo, text, desc, level, group);
    }
    ArkUISliderCustomContentOptions options;
    options.accessibilityText = text.c_str();
    options.accessibilityDescription = desc.c_str();
    options.accessibilityLevel = level.c_str();
    options.accessibilityGroup = group;

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    auto sliderModifier = nodeModifiers->getSliderModifier();
    CHECK_NULL_RETURN(sliderModifier, panda::NativePointerRef::New(vm, nullptr));
    sliderModifier->setSuffix(nativeNode, reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(suffixNode)),
        static_cast<ArkUISliderCustomContentOptions*>(&options));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetDigitalCrownSensitivity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
#ifdef SUPPORT_DIGITAL_CROWN
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (!IsJsView(firstArg, vm)) {
        throw new Error('The method does not support attributeModifier.');
        return panda::JSValueRef::Undefined(vm);
    }

    if (firstArg.IsNull() || !firstArg->IsNumber()) {
        GetArkUINodeModifiers()->getSliderModifier()->resetDigitalCrownSensitivity(nullptr);
        return panda::JSValueRef::Undefined(vm);
    }

    auto sensitivity = firstArg->ToNumber(vm)->Value();
    if (sensitivity < 0 || sensitivity > static_cast<int32_t>(CrownSensitivity::HIGH)) {
        GetArkUINodeModifiers()->getSliderModifier()->resetDigitalCrownSensitivity(nullptr);
    } else {
        GetArkUINodeModifiers()->getSliderModifier()->setDigitalCrownSensitivity(
            nullptr, static_cast<CrownSensitivity>(sensitivity));
    }
#endif
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::ResetDigitalCrownSensitivity(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
#ifdef SUPPORT_DIGITAL_CROWN

    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSliderModifier()->resetDigitalCrownSensitivity(nativeNode);
#endif
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetMinLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsString(vm) && !secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto minLabel = secondArg->ToNumber(vm)->Value();

    GetArkUINodeModifiers()->getSliderModifier()->setMinLabel(nativeNode, minLabel);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SliderBridge::SetMaxLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsString(vm) && !secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto maxLabel = secondArg->ToNumber(vm)->Value();

    GetArkUINodeModifiers()->getSliderModifier()->setMaxLabel(nativeNode, maxLabel);
    return panda::JSValueRef::Undefined(vm);
}

napi_value SliderBridge::GetIteratorNext(const napi_env env, napi_value iterator, napi_value func, bool* done)
{
    napi_value next = nullptr;
    NAPI_CALL_BASE(env, napi_call_function(env, iterator, func, 0, nullptr, &next), nullptr);
    CHECK_NULL_RETURN(next, nullptr);
    napi_value doneValue = nullptr;
    NAPI_CALL_BASE(env, napi_get_named_property(env, next, DONE_STRING, &doneValue), nullptr);
    CHECK_NULL_RETURN(doneValue, nullptr);
    NAPI_CALL_BASE(env, napi_get_value_bool(env, doneValue, done), nullptr);
    return next;
}

int32_t SliderBridge::ParseStepOptionItemKey(const napi_env env, napi_value item)
{
    int32_t result = INT32_MIN;
    napi_value entry = nullptr;
    napi_value key = nullptr;
    napi_valuetype kType = napi_undefined;
    NAPI_CALL_BASE(env, napi_get_named_property(env, item, VALUE_STRING, &entry), result);
    CHECK_NULL_RETURN(entry, result);
    NAPI_CALL_BASE(env, napi_get_element(env, entry, NUM_0, &key), result);
    CHECK_NULL_RETURN(key, result);
    NAPI_CALL_BASE(env, napi_typeof(env, key, &kType), result);
    CHECK_NULL_RETURN(kType, result);
    if (napi_number == kType) {
        double step = NUM_0;
        NAPI_CALL_BASE(env, napi_get_value_double(env, key, &step), result);
        if ((step >= 0) && (NearZero(std::abs(step - std::floor(step)))) && (step <= INT32_MAX)) {
            result = static_cast<int32_t>(step);
        }
    }
    return result;
}

bool SliderBridge::ParseStepOptionItemValue(EcmaVM* vm, const napi_env env, napi_value item, std::string& stepText)
{
    bool result = false;
    CHECK_NULL_RETURN(vm, result);
    napi_value entry = nullptr;
    napi_value value = nullptr;
    napi_value textObject = nullptr;
    napi_valuetype vType = napi_undefined;
    NAPI_CALL_BASE(env, napi_get_named_property(env, item, VALUE_STRING, &entry), result);
    CHECK_NULL_RETURN(entry, result);
    NAPI_CALL_BASE(env, napi_get_element(env, entry, NUM_1, &value), result);
    CHECK_NULL_RETURN(value, result);
    NAPI_CALL_BASE(env, napi_typeof(env, value, &vType), result);
    CHECK_NULL_RETURN(vType, result);
    if (napi_object == vType) {
        NAPI_CALL_BASE(env, napi_get_named_property(env, value, TEXT_STRING, &textObject), result);
        CHECK_NULL_RETURN(textObject, result);
        panda::Local<panda::JSValueRef> localValue = NapiValueToLocalValue(textObject);
        result = ArkTSUtils::ParseJsString(vm, localValue, stepText);
    }
    return result;
}

napi_value SliderBridge::ParseStepOptionsMap(
    EcmaVM* vm, const panda::Local<panda::JSValueRef>& jsStepOptionsMap, StepOptions& stepOptionsMap)
{
    CHECK_NULL_RETURN(vm, nullptr);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, nullptr);
    auto env = reinterpret_cast<napi_env>(nativeEngine);

    panda::Local<panda::JSValueRef> localValue = jsStepOptionsMap;

    JSValueWrapper valueWrapper = localValue;
    napi_value nativeValue = nativeEngine->ValueToNapiValue(valueWrapper);

    napi_value entriesFunc = nullptr;
    napi_value iterator = nullptr;
    napi_value nextFunc = nullptr;
    bool done = false;

    NAPI_CALL_BASE(env, napi_get_named_property(env, nativeValue, ENTRIES_STRING, &entriesFunc), nullptr);
    CHECK_NULL_RETURN(entriesFunc, nullptr);

    NAPI_CALL_BASE(env, napi_call_function(env, nativeValue, entriesFunc, NUM_0, nullptr, &iterator), nullptr);
    CHECK_NULL_RETURN(iterator, nullptr);

    NAPI_CALL_BASE(env, napi_get_named_property(env, iterator, NEXT_STRING, &nextFunc), nullptr);
    CHECK_NULL_RETURN(nextFunc, nullptr);

    napi_value next = SliderBridge::GetIteratorNext(env, iterator, nextFunc, &done);
    while ((nullptr != next) && !done) {
        auto optionKey = SliderBridge::ParseStepOptionItemKey(env, next);
        std::string optionStr = "";
        auto praseResult = SliderBridge::ParseStepOptionItemValue(vm, env, next, optionStr);
        next = SliderBridge::GetIteratorNext(env, iterator, nextFunc, &done);
        if ((optionKey < 0) || (!praseResult)) {
            continue;
        }
        stepOptionsMap[static_cast<uint32_t>(optionKey)] = optionStr;
    }
    return next;
}
} // namespace OHOS::Ace::NG
