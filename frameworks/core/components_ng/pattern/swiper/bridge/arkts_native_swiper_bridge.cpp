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
#include "core/components_ng/pattern/swiper/bridge/arkts_native_swiper_bridge.h"

#include <string>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_utils_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "frameworks/bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/components_ng/pattern/swiper/swiper_change_event.h"
#include "bridge/declarative_frontend/jsview/js_indicator_controller.h"
#include "bridge/declarative_frontend/jsview/js_swiper_controller.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper_indicator/bridge/indicator_controller_modifier_api.h"
#include "core/interfaces/native/node/node_swiper_modifier.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "core/components_ng/pattern/swiper/swiper_theme_utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NUM_2 = 2;
constexpr int32_t NUM_3 = 3;
constexpr int32_t CALL_ARG_NODE_INDEX = 0;
constexpr int32_t CALL_ARG_VALUE_INDEX = 1;
constexpr int32_t CALL_ARG_TYPE_INDEX = 2;
constexpr int32_t DISPLAY_ARROW_VALUE = 1;
constexpr int32_t ARROW_IS_SHOW_BACKGROUND = 2;
constexpr int32_t ARROW_IS_SIDE_BAR_MIDDLE = 3;
constexpr int32_t ARROW_BACKGROUND_SIZE = 4;
constexpr int32_t ARROW_BACKGROUND_COLOR = 5;
constexpr int32_t ARROW_SIZE = 6;
constexpr int32_t ARROW_COLOR = 7;
constexpr int32_t DISPLAY_ARROW_IS_HOVER_SHOW_INDEX = 8;
constexpr int32_t INDICATOR_VALUE_INDEX = 2;
constexpr int32_t DIGIT_INDICATOR_FONT_COLOR = 2;
constexpr int32_t DIGIT_INDICATOR_SELECTED_FONT_COLOR = 3;
constexpr int32_t DIGIT_INDICATOR_DIGIT_FONT_SIZE = 4;
constexpr int32_t DIGIT_INDICATOR_DIGIT_FONT_WEIGHT = 5;
constexpr int32_t DIGIT_INDICATOR_SELECTED_DIGIT_FONT_SIZE = 6;
constexpr int32_t DIGIT_INDICATOR_SELECTED_DIGIT_FONT_WEIGHT = 7;
constexpr int32_t DIGIT_INDICATOR_LEFT = 8;
constexpr int32_t DIGIT_INDICATOR_TOP = 9;
constexpr int32_t DIGIT_INDICATOR_RIGHT = 10;
constexpr int32_t DIGIT_INDICATOR_BOTTOM = 11;
constexpr int32_t DIGIT_INDICATOR_IGNORE_SIZE = 12;
constexpr int32_t DIGIT_INDICATOR_SET_IGNORE_SIZE = 13;
constexpr int32_t DOT_INDICATOR_ITEM_WIDTH = 2;
constexpr int32_t DOT_INDICATOR_ITEM_HEIGHT = 3;
constexpr int32_t DOT_INDICATOR_SELECTED_ITEM_WIDTH = 4;
constexpr int32_t DOT_INDICATOR_SELECTED_ITEM_HEIGHT = 5;
constexpr int32_t DOT_INDICATOR_MASK = 6;
constexpr int32_t DOT_INDICATOR_COLOR = 7;
constexpr int32_t DOT_INDICATOR_SELECTED_COLOR = 8;
constexpr int32_t DOT_INDICATOR_LEFT = 9;
constexpr int32_t DOT_INDICATOR_TOP = 10;
constexpr int32_t DOT_INDICATOR_RIGHT = 11;
constexpr int32_t DOT_INDICATOR_BOTTOM = 12;
constexpr int32_t DOT_INDICATOR_MAX_DISPLAY_COUNT = 13;
constexpr int32_t DOT_INDICATOR_SPACE = 14;
constexpr int32_t DOT_INDICATOR_IGNORE_SIZE = 15;
constexpr int32_t DOT_INDICATOR_SET_IGNORE_SIZE = 16;
constexpr int32_t DOT_INDICATOR_INDICATOR_ICON = 17;
constexpr double DEFAULT_PERCENT_VALUE = 100.0;
constexpr int32_t DEFAULT_ANIMATION_MODE = 0;
constexpr int32_t DEFAULT_CACHED_COUNT = 1;
constexpr int32_t STOP_WHEN_TOUCHED = 2;
constexpr int32_t INDICATOR_RESOURCE_LEFT = 0;
constexpr int32_t INDICATOR_RESOURCE_TOP = 1;
constexpr int32_t INDICATOR_RESOURCE_RIGHT = 2;
constexpr int32_t INDICATOR_RESOURCE_BOTTOM = 3;
constexpr int32_t DOT_INDICATOR_RESOURCE_ITEM_WIDTH = 4;
constexpr int32_t DOT_INDICATOR_RESOURCE_ITEM_HEIGHT = 5;
constexpr int32_t DOT_INDICATOR_RESOURCE_SELECTED_ITEM_WIDTH = 6;
constexpr int32_t DOT_INDICATOR_RESOURCE_SELECTED_ITEM_HEIGHT = 7;
constexpr int32_t DOT_INDICATOR_RESOURCE_COLOR = 8;
constexpr int32_t DOT_INDICATOR_RESOURCE_SELECTED_COLOR = 9;
constexpr int32_t INDICATOR_RESOURCE_VECTOR_LENGTH = 10;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_COLOR = 4;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_SELECTED_COLOR = 5;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_SIZE = 6;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_SELECTED_FONT_SIZE = 7;
constexpr int32_t ARROW_RESOURCE_BACKGROUND_SIZE = 0;
constexpr int32_t ARROW_RESOURCE_BACKGROUND_COLOR = 1;
constexpr int32_t ARROW_RESOURCE_SIZE = 2;
constexpr int32_t ARROW_RESOURCE_COLOR = 3;
constexpr int32_t ARROW_RESOURCE_VECTOR_LENGTH = 4;
constexpr float ARROW_SIZE_COEFFICIENT = 0.75f;
constexpr char DOM_ANIMATION_TIMING_FUNCTION_CUSTOM[] = "customCallback";

enum class DotIndicatorThemeMode {
    APPLY,
    FORCE,
};

ArkUINativeModuleValue FinishSwiperContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto thisObj = runtimeCallInfo->GetThisRef();
    CHECK_NULL_RETURN(thisObj->IsObject(vm), panda::JSValueRef::Undefined(vm));
    auto object = thisObj->ToObject(vm);
    CHECK_NULL_RETURN(object->GetNativePointerFieldCount(vm) > 0, panda::JSValueRef::Undefined(vm));
    auto* strongRef = static_cast<NG::NativeStrongRef*>(object->GetNativePointerField(vm, 0));
    CHECK_NULL_RETURN(strongRef, panda::JSValueRef::Undefined(vm));
    auto* proxy = static_cast<SwiperContentTransitionProxy*>(strongRef->RawPtr());
    CHECK_NULL_RETURN(proxy, panda::JSValueRef::Undefined(vm));
    proxy->FinishTransition();
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::ObjectRef> CreateSwiperContentTransitionProxyObject(
    EcmaVM* vm, const RefPtr<SwiperContentTransitionProxy>& proxy)
{
    auto proxyObj = panda::ObjectRef::New(vm);
    CHECK_NULL_RETURN(proxy, proxyObj);
    proxyObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "selectedIndex"),
        panda::NumberRef::New(vm, proxy->GetSelectedIndex()));
    proxyObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "index"), panda::NumberRef::New(vm, proxy->GetIndex()));
    proxyObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "position"), panda::NumberRef::New(vm, proxy->GetPosition()));
    proxyObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "mainAxisLength"),
        panda::NumberRef::New(vm, proxy->GetMainAxisLength()));
    proxyObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "finishTransition"),
        panda::FunctionRef::New(vm, FinishSwiperContentTransition));
    proxyObj->SetNativePointerFieldCount(vm, 1);
    auto* strongRef = new NG::NativeStrongRef(proxy);
    proxyObj->SetNativePointerField(vm, 0, strongRef, &NG::DestructorInterceptor<NG::NativeStrongRef>);
    return proxyObj;
}

void SetSwiperIndexChangeEvent(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& callbackArg)
{
    if (callbackArg.IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        return;
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_VOID(frameNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback = [frameWeakNode = AceType::WeakClaim(frameNode),
        func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        auto vm = func.GetEcmaVM();
        ACE_SCORING_EVENT("Swiper.onChangeEvent");
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            return;
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, swiperInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnChangeEvent(
        nativeNode, reinterpret_cast<void*>(&callback));
}

std::string ParseDisplayCountObject(Local<JSValueRef> valueArg, EcmaVM* vm, std::string& type)
{
    if (!valueArg->IsObject(vm)) {
        return "";
    }
    auto obj = valueArg->ToObject(vm);
    auto minSizeParam = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "minSize"));
    if (!minSizeParam->IsUndefined()) {
        type = "minSize";
        return minSizeParam->ToString(vm)->ToString(vm);
    }
    type = "fillType";
    auto fillTypeParam = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "fillType"));
    int32_t fillTypeValue = 0;
    if (fillTypeParam->IsNumber()) {
        fillTypeValue = fillTypeParam->Int32Value(vm);
    }
    return std::to_string(fillTypeValue);
}

Local<JSValueRef> GetNamedProperty(EcmaVM* vm, const Local<JSValueRef>& objectArg, const char* name)
{
    CHECK_NULL_RETURN(
        !objectArg.IsNull() && !objectArg->IsUndefined() && objectArg->IsObject(vm), panda::JSValueRef::Undefined(vm));
    return objectArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, name));
}

void ParseCachedCountOptions(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& optionArg)
{
    auto isShown = GetNamedProperty(vm, optionArg, "isShown");
    if (!isShown.IsNull() && !isShown->IsUndefined() && isShown->IsBoolean()) {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIsShown(nativeNode, isShown->ToBoolean(vm)->Value());
    }
    auto independent = GetNamedProperty(vm, optionArg, "independent");
    if (!independent.IsNull() && !independent->IsUndefined() && independent->IsBoolean()) {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperCachedIndependent(
            nativeNode, independent->ToBoolean(vm)->Value());
    }
}

RefPtr<Curve> GetDefaultSwiperCurve()
{
    return AceType::MakeRefPtr<InterpolatingSpring>(-1, 1, 328, 34);
}

RefPtr<Curve> ParseJsViewCurveObject(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CHECK_NULL_RETURN(runtimeCallInfo, nullptr);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    CHECK_NULL_RETURN(valueArg->IsObject(vm), nullptr);
    std::function<float(float)> customCallBack = nullptr;
    auto object = valueArg->ToObject(vm);
    auto onCallBack = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "__curveCustomFunc"));
    if (!onCallBack.IsNull() && !onCallBack->IsUndefined() && onCallBack->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = onCallBack->ToObject(vm);
        customCallBack = [func = panda::CopyableGlobal(vm, func), id = Container::CurrentId()](float time) -> float {
            auto vm = func.GetEcmaVM();
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ContainerScope scope(id);
            panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, time) };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            auto resultValue = result->IsNumber() ? static_cast<float>(result->ToNumber(vm)->Value()) : 1.0f;
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            return resultValue;
        };
    }
    auto jsCurveString = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "__curveString"));
    if (jsCurveString->IsString(vm)) {
        auto aniTimFunc = jsCurveString->ToString(vm)->ToString(vm);
        if (aniTimFunc == DOM_ANIMATION_TIMING_FUNCTION_CUSTOM && customCallBack) {
            return Framework::CreateCurve(customCallBack);
        } else if (aniTimFunc != DOM_ANIMATION_TIMING_FUNCTION_CUSTOM) {
            return Framework::CreateCurve(aniTimFunc);
        }
    }
    return nullptr;
}

void GetFontContent(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& font, bool isSelected,
    SwiperDigitalParameters& digitalParameters)
{
    auto obj = font->ToObject(vm);
    auto size = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    CalcDimension fontSize;
    RefPtr<ResourceObject> resObj;
    if (!size->IsUndefined() && !size->IsNull() &&
        ArkTSUtils::ParseJsDimensionFp(vm, size, fontSize, resObj)) {
        if (LessOrEqual(fontSize.Value(), 0.0) ||
            LessOrEqual(size->ToNumber(vm)->Value(), 0.0) ||
            fontSize.Unit() == DimensionUnit::PERCENT) {
            fontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
        }
    } else {
        fontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
    }
    if (SystemProperties::ConfigChangePerform()) {
        if (isSelected) {
            digitalParameters.resourceSelectedFontSizeValueObject = resObj;
        } else {
            digitalParameters.resourceFontSizeValueObject = resObj;
        }
    }
    if (isSelected) {
        digitalParameters.selectedFontSize = fontSize;
    } else {
        digitalParameters.fontSize = fontSize;
    }
    auto weight = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "weight"));
    if (!weight->IsNull()) {
        std::string weightValue;
        if (weight->IsNumber()) {
            weightValue = std::to_string(weight->Int32Value(vm));
        } else {
            weightValue = weight->ToString(vm)->ToString(vm);
        }
        if (isSelected) {
            digitalParameters.selectedFontWeight = Framework::ConvertStrToFontWeight(weightValue);
        } else {
            digitalParameters.fontWeight = Framework::ConvertStrToFontWeight(weightValue);
        }
    } else {
        if (isSelected) {
            digitalParameters.selectedFontWeight = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        } else {
            digitalParameters.fontWeight = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        }
    }
}

std::optional<Dimension> ParseIndicatorDimension(
    EcmaVM* vm, const Local<JSValueRef>& value, RefPtr<ResourceObject>& resObj)
{
    std::optional<Dimension> indicatorDimension;
    if (value->IsUndefined()) {
        return indicatorDimension;
    }
    CalcDimension dimPosition;
    auto parseOk = ArkTSUtils::ParseJsDimensionVpNG(vm, value, dimPosition, resObj);
    indicatorDimension = parseOk && dimPosition.ConvertToPx() >= 0.0f ? dimPosition : 0.0_vp;
    return indicatorDimension;
}

std::optional<Dimension> ParseIndicatorBottom(EcmaVM* vm, const Local<JSValueRef>& bottomValue, bool hasIgnoreSize,
    RefPtr<ResourceObject>& resObj)
{
    std::optional<Dimension> bottom;
    if (bottomValue->IsUndefined()) {
        return bottom;
    }
    if (!hasIgnoreSize) {
        bottom = ParseIndicatorDimension(vm, bottomValue, resObj);
        return bottom;
    } else {
        CalcDimension dimBottom;
        bool parseOk = ArkTSUtils::ParseLengthMetricsToDimensionForTabs(vm, bottomValue, dimBottom, resObj);
        if (!parseOk) {
            bottom = ParseIndicatorDimension(vm, bottomValue, resObj);
            return bottom;
        }
        dimBottom = parseOk && dimBottom.ConvertToPx() >= 0.0f ? dimBottom : 0.0_vp;
        return dimBottom;
    }
}

void SetJsViewDotIndicatorInfo(EcmaVM* vm, const Local<ObjectRef>& obj, SwiperParameters& swiperParameters,
    ArkUINodeHandle nativeNode)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    auto maskValue = obj->Get(vm, "maskValue");
    auto colorValue = obj->Get(vm, "colorValue");
    auto selectedColorValue = obj->Get(vm, "selectedColorValue");
    auto maxDisplayCountVal = obj->Get(vm, "maxDisplayCountValue");
    if (!maskValue.IsNull() && maskValue->IsBoolean()) {
        swiperParameters.maskValue = maskValue->ToBoolean(vm)->Value();
    }
    Color colorVal;
    RefPtr<ResourceObject> resColorObj;
    RefPtr<ResourceObject> resSelectedColorObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    auto parseOk = ArkTSUtils::ParseJsColorAlpha(vm, colorValue, colorVal, resColorObj, nodeInfo);
    swiperParameters.colorVal = parseOk ? (swiperParameters.parametersByUser.insert("colorVal"), colorVal)
        : swiperIndicatorTheme->GetColor();
    parseOk = ArkTSUtils::ParseJsColorAlpha(vm, selectedColorValue, colorVal, resSelectedColorObj, nodeInfo);
    swiperParameters.selectedColorVal = parseOk
        ? (swiperParameters.parametersByUser.insert("selectedColorVal"), colorVal)
        : swiperIndicatorTheme->GetSelectedColor();
    if (SystemProperties::ConfigChangePerform()) {
        swiperParameters.resourceColorValueObject = resColorObj;
        swiperParameters.resourceSelectedColorValueObject = resSelectedColorObj;
    }
    if (maxDisplayCountVal.IsNull() || maxDisplayCountVal->IsUndefined()) {
        return;
    }
    uint32_t result = 0;
    auto setMaxDisplayCountVal = ArkTSUtils::ParseJsInteger(vm, maxDisplayCountVal, result);
    swiperParameters.maxDisplayCountVal = setMaxDisplayCountVal && result > 0 ? result : 0;
}

SwiperParameters GetDotIndicatorInfo(EcmaVM* vm, const Local<ObjectRef>& obj, ArkUINodeHandle nativeNode)
{
    auto leftValue = obj->Get(vm, "leftValue");
    auto topValue = obj->Get(vm, "topValue");
    auto rightValue = obj->Get(vm, "rightValue");
    auto bottomValue = obj->Get(vm, "bottomValue");
    auto startValue = obj->Get(vm, "startValue");
    auto endValue = obj->Get(vm, "endValue");
    auto itemWidthValue = obj->Get(vm, "itemWidthValue");
    auto itemHeightValue = obj->Get(vm, "itemHeightValue");
    auto selectedItemWidthValue = obj->Get(vm, "selectedItemWidthValue");
    auto selectedItemHeightValue = obj->Get(vm, "selectedItemHeightValue");
    auto spaceValue = obj->Get(vm, "spaceValue");
    auto ignoreSizeValue = obj->Get(vm, "ignoreSizeValue");
    auto setIgnoreSizeValue = obj->Get(vm, "setIgnoreSizeValue");

    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, SwiperParameters());
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperParameters());
    SwiperParameters swiperParameters;
    RefPtr<ResourceObject> resLeftObj;
    RefPtr<ResourceObject> resTopObj;
    RefPtr<ResourceObject> resRightObj;
    RefPtr<ResourceObject> resBottomObj;
    swiperParameters.dimLeft = ParseIndicatorDimension(vm, leftValue, resLeftObj);
    swiperParameters.dimTop = ParseIndicatorDimension(vm, topValue, resTopObj);
    swiperParameters.dimRight = ParseIndicatorDimension(vm, rightValue, resRightObj);
    auto hasIgnoreSizeValue = false;

    if (!setIgnoreSizeValue.IsNull() && setIgnoreSizeValue->IsBoolean()) {
        hasIgnoreSizeValue = setIgnoreSizeValue->ToBoolean(vm)->Value();
        swiperParameters.setIgnoreSizeValue = hasIgnoreSizeValue;
    }

    if (!ignoreSizeValue.IsNull() && ignoreSizeValue->IsBoolean()) {
        swiperParameters.ignoreSizeValue = ignoreSizeValue->ToBoolean(vm)->Value();
    }
    swiperParameters.dimBottom = ParseIndicatorBottom(vm, bottomValue, hasIgnoreSizeValue, resBottomObj);
    CalcDimension dimStart;
    CalcDimension dimEnd;
    CalcDimension dimSpace;

    std::optional<Dimension> indicatorDimension;
    swiperParameters.dimStart =
        !startValue.IsNull() && !startValue->IsUndefined() &&
            ArkTSUtils::ParseLengthMetricsToDimensionForTabs(vm, startValue, dimStart)
            ? dimStart
            : indicatorDimension;
    swiperParameters.dimEnd =
        !endValue.IsNull() && !endValue->IsUndefined() &&
            ArkTSUtils::ParseLengthMetricsToDimensionForTabs(vm, endValue, dimEnd)
            ? dimEnd
            : indicatorDimension;

    auto parseSpaceOk = !spaceValue.IsNull() && !spaceValue->IsUndefined() &&
                        ArkTSUtils::ParseLengthMetricsToDimensionForTabs(vm, spaceValue, dimSpace) &&
                        (dimSpace.Unit() != DimensionUnit::PERCENT);
    auto defaultSpace = swiperIndicatorTheme->GetIndicatorDotItemSpace();
    swiperParameters.dimSpace = (parseSpaceOk && !(dimSpace < 0.0_vp)) ? dimSpace : defaultSpace;
    bool ignoreSize = !ignoreSizeValue.IsNull() && ignoreSizeValue->IsBoolean()
                          ? ignoreSizeValue->ToBoolean(vm)->Value()
                          : false;
    swiperParameters.ignoreSizeValue = ignoreSize;

    CalcDimension dimPosition;
    RefPtr<ResourceObject> resItemWidthObj;
    RefPtr<ResourceObject> resItemHeightObj;
    RefPtr<ResourceObject> resSelectedItemWidthObj;
    RefPtr<ResourceObject> resSelectedItemHeightObj;
    bool parseItemWOk = !itemWidthValue.IsNull() && !itemWidthValue->IsUndefined() &&
                        ArkTSUtils::ParseJsDimensionVpNG(vm, itemWidthValue, dimPosition, resItemWidthObj) &&
                        (dimPosition.Unit() != DimensionUnit::PERCENT);
    auto defaultSize = swiperIndicatorTheme->GetSize();
    if (parseItemWOk && dimPosition > 0.0_vp) {
        swiperParameters.parametersByUser.insert("itemWidth");
        swiperParameters.itemWidth = dimPosition;
    } else {
        swiperParameters.itemWidth = defaultSize;
    }
    bool parseItemHOk = !itemHeightValue.IsNull() && !itemHeightValue->IsUndefined() &&
                        ArkTSUtils::ParseJsDimensionVpNG(vm, itemHeightValue, dimPosition, resItemHeightObj) &&
                        (dimPosition.Unit() != DimensionUnit::PERCENT);
    if (parseItemHOk && dimPosition > 0.0_vp) {
        swiperParameters.parametersByUser.insert("itemHeight");
        swiperParameters.itemHeight = dimPosition;
    } else {
        swiperParameters.itemHeight = defaultSize;
    }
    bool parseSelectedItemWOk =
        !selectedItemWidthValue.IsNull() && !selectedItemWidthValue->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionVpNG(vm, selectedItemWidthValue, dimPosition, resSelectedItemWidthObj) &&
        (dimPosition.Unit() != DimensionUnit::PERCENT);
    if (parseSelectedItemWOk && dimPosition > 0.0_vp) {
        swiperParameters.parametersByUser.insert("selectedItemWidth");
        swiperParameters.selectedItemWidth = dimPosition;
    } else {
        swiperParameters.selectedItemWidth = defaultSize;
    }
    bool parseSelectedItemHOk =
        !selectedItemHeightValue.IsNull() && !selectedItemHeightValue->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionVpNG(vm, selectedItemHeightValue, dimPosition, resSelectedItemHeightObj) &&
        (dimPosition.Unit() != DimensionUnit::PERCENT);
    if (parseSelectedItemHOk && dimPosition > 0.0_vp) {
        swiperParameters.parametersByUser.insert("selectedItemHeight");
        swiperParameters.selectedItemHeight = dimPosition;
    } else {
        swiperParameters.selectedItemHeight = defaultSize;
    }
    if (SystemProperties::ConfigChangePerform()) {
        swiperParameters.resourceDimLeftValueObject = resLeftObj;
        swiperParameters.resourceDimTopValueObject = resTopObj;
        swiperParameters.resourceDimRightValueObject = resRightObj;
        swiperParameters.resourceDimBottomValueObject = resBottomObj;
        swiperParameters.resourceItemWidthValueObject = resItemWidthObj;
        swiperParameters.resourceItemHeightValueObject = resItemHeightObj;
        swiperParameters.resourceSelectedItemWidthValueObject = resSelectedItemWidthObj;
        swiperParameters.resourceSelectedItemHeightValueObject = resSelectedItemHeightObj;
    }
    SwiperModelNG::SetIsIndicatorCustomSize(
        frameNode, parseSelectedItemWOk || parseSelectedItemHOk || parseItemWOk || parseItemHOk);
    SetJsViewDotIndicatorInfo(vm, obj, swiperParameters, nativeNode);
    return swiperParameters;
}

SwiperDigitalParameters GetDigitIndicatorInfo(EcmaVM* vm, const Local<ObjectRef>& obj, ArkUINodeHandle nativeNode)
{
    auto dotLeftValue = obj->Get(vm, "leftValue");
    auto dotTopValue = obj->Get(vm, "topValue");
    auto dotRightValue = obj->Get(vm, "rightValue");
    auto dotBottomValue = obj->Get(vm, "bottomValue");
    auto startValue = obj->Get(vm, "startValue");
    auto endValue = obj->Get(vm, "endValue");
    auto fontColorValue = obj->Get(vm, "fontColorValue");
    auto selectedFontColorValue = obj->Get(vm, "selectedFontColorValue");
    auto digitFontValue = obj->Get(vm, "digitFontValue");
    auto selectedDigitFontValue = obj->Get(vm, "selectedDigitFontValue");
    auto ignoreSizeValue = obj->Get(vm, "ignoreSizeValue");
    auto setIgnoreSizeValue = obj->Get(vm, "setIgnoreSizeValue");
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, SwiperDigitalParameters());
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperDigitalParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperDigitalParameters());
    SwiperDigitalParameters digitalParameters;
    RefPtr<ResourceObject> resLeftObj;
    RefPtr<ResourceObject> resTopObj;
    RefPtr<ResourceObject> resRightObj;
    RefPtr<ResourceObject> resBottomObj;
    digitalParameters.dimLeft = ParseIndicatorDimension(vm, dotLeftValue, resLeftObj);
    digitalParameters.dimTop = ParseIndicatorDimension(vm, dotTopValue, resTopObj);
    digitalParameters.dimRight = ParseIndicatorDimension(vm, dotRightValue, resRightObj);
    bool hasIgnoreSizeValue = !setIgnoreSizeValue.IsNull() && setIgnoreSizeValue->IsBoolean()
                                  ? setIgnoreSizeValue->ToBoolean(vm)->Value()
                                  : false;
    auto bottom = ParseIndicatorBottom(vm, dotBottomValue, hasIgnoreSizeValue, resBottomObj);
    digitalParameters.dimBottom = bottom;
    std::optional<Dimension> indicatorDimension;
    CalcDimension dimStart;
    CalcDimension dimEnd;
    digitalParameters.dimStart = ArkTSUtils::ParseLengthMetricsToDimensionForTabs(vm, startValue, dimStart)
                                     ? dimStart
                                     : indicatorDimension;
    digitalParameters.dimEnd = ArkTSUtils::ParseLengthMetricsToDimensionForTabs(vm, endValue, dimEnd)
                                   ? dimEnd
                                   : indicatorDimension;

    if (!ignoreSizeValue.IsNull() && ignoreSizeValue->IsBoolean()) {
        digitalParameters.ignoreSizeValue = ignoreSizeValue->ToBoolean(vm)->Value();
    } else {
        digitalParameters.ignoreSizeValue = false;
    }

    Color fontColor;
    RefPtr<ResourceObject> resFontColorObj;
    RefPtr<ResourceObject> resSelectedFontColorObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    auto parseOk = ArkTSUtils::ParseJsColorAlpha(vm, fontColorValue, fontColor, resFontColorObj, nodeInfo);
    digitalParameters.fontColor =
        parseOk ? (digitalParameters.parametersByUser.insert("fontColor"), fontColor)
        : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    parseOk = ArkTSUtils::ParseJsColorAlpha(vm, selectedFontColorValue, fontColor, resSelectedFontColorObj, nodeInfo);
    digitalParameters.selectedFontColor =
        parseOk ? (digitalParameters.parametersByUser.insert("selectedFontColor"), fontColor)
        : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    if (SystemProperties::ConfigChangePerform()) {
        digitalParameters.resourceDimLeftValueObject = resLeftObj;
        digitalParameters.resourceDimTopValueObject = resTopObj;
        digitalParameters.resourceDimRightValueObject = resRightObj;
        digitalParameters.resourceDimBottomValueObject = resBottomObj;
        digitalParameters.resourceFontColorValueObject = resFontColorObj;
        digitalParameters.resourceSelectedFontColorValueObject = resSelectedFontColorObj;
    }
    if (!digitFontValue.IsNull() && !digitFontValue->IsUndefined() && digitFontValue->IsObject(vm)) {
        GetFontContent(vm, nativeNode, digitFontValue, false, digitalParameters);
    }
    if (!selectedDigitFontValue.IsNull() && !selectedDigitFontValue->IsUndefined() &&
        selectedDigitFontValue->IsObject(vm)) {
        GetFontContent(vm, nativeNode, selectedDigitFontValue, true, digitalParameters);
    }
    return digitalParameters;
}

bool GetArrowInfo(
    const Local<ObjectRef>& obj, SwiperArrowParameters& swiperArrowParameters, EcmaVM* vm, ArkUINodeHandle nativeNode)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, false);
    auto isShowBackgroundValue = obj->Get(vm, "showBackground");
    auto isSidebarMiddleValue = obj->Get(vm, "isSidebarMiddle");
    auto backgroundSizeValue = obj->Get(vm, "backgroundSize");
    auto backgroundColorValue = obj->Get(vm, "backgroundColor");
    auto arrowSizeValue = obj->Get(vm, "arrowSize");
    auto arrowColorValue = obj->Get(vm, "arrowColor");
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto swiperIndicatorTheme = frameNode->GetTheme<SwiperIndicatorTheme>(true);
    CHECK_NULL_RETURN(swiperIndicatorTheme, false);
    swiperArrowParameters.isShowBackground =
        !isShowBackgroundValue.IsNull() && !isShowBackgroundValue->IsUndefined() && isShowBackgroundValue->IsBoolean()
            ? isShowBackgroundValue->ToBoolean(vm)->Value()
            : swiperIndicatorTheme->GetIsShowArrowBackground();
    swiperArrowParameters.isSidebarMiddle =
        !isSidebarMiddleValue.IsNull() && !isSidebarMiddleValue->IsUndefined() && isSidebarMiddleValue->IsBoolean()
            ? isSidebarMiddleValue->ToBoolean(vm)->Value()
            : swiperIndicatorTheme->GetIsSidebarMiddle();
    bool parseOk = false;
    CalcDimension dimension;
    Color color;
    RefPtr<ResourceObject> resBackgroundSizeObj;
    RefPtr<ResourceObject> resBackgroundColorObj;
    RefPtr<ResourceObject> resArrowSizeObj;
    RefPtr<ResourceObject> resArrowColorObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (swiperArrowParameters.isSidebarMiddle.value()) {
        parseOk = !backgroundSizeValue.IsNull() && !backgroundSizeValue->IsUndefined() &&
                  ArkTSUtils::ParseJsDimensionVp(vm, backgroundSizeValue, dimension, resBackgroundSizeObj);
        swiperArrowParameters.backgroundSize =
            parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                ? dimension
                : swiperIndicatorTheme->GetBigArrowBackgroundSize();
        parseOk = !backgroundColorValue.IsNull() && !backgroundColorValue->IsUndefined() &&
                  ArkTSUtils::ParseJsColorAlpha(vm, backgroundColorValue, color, resBackgroundColorObj, nodeInfo);
        swiperArrowParameters.backgroundColor =
            parseOk ? (swiperArrowParameters.parametersByUser.insert("backgroundColor"), color)
                    : swiperIndicatorTheme->GetBigArrowBackgroundColor();
        if (swiperArrowParameters.isShowBackground.value()) {
            swiperArrowParameters.arrowSize = swiperArrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
        } else {
            parseOk = !arrowSizeValue.IsNull() && !arrowSizeValue->IsUndefined() &&
                      ArkTSUtils::ParseJsDimensionVpNG(vm, arrowSizeValue, dimension, resArrowSizeObj);
            swiperArrowParameters.arrowSize =
                parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                    ? dimension
                    : swiperIndicatorTheme->GetBigArrowSize();
            swiperArrowParameters.backgroundSize = swiperArrowParameters.arrowSize;
        }
        parseOk = !arrowColorValue.IsNull() && !arrowColorValue->IsUndefined() &&
                  ArkTSUtils::ParseJsColorAlpha(vm, arrowColorValue, color, resArrowColorObj, nodeInfo);
        swiperArrowParameters.arrowColor = parseOk
                                               ? (swiperArrowParameters.parametersByUser.insert("arrowColor"), color)
                                               : swiperIndicatorTheme->GetBigArrowColor();
    } else {
        parseOk = !backgroundSizeValue.IsNull() && !backgroundSizeValue->IsUndefined() &&
                  ArkTSUtils::ParseJsDimensionVp(vm, backgroundSizeValue, dimension, resBackgroundSizeObj);
        swiperArrowParameters.backgroundSize =
            parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                ? dimension
                : swiperIndicatorTheme->GetSmallArrowBackgroundSize();
        parseOk = !backgroundColorValue.IsNull() && !backgroundColorValue->IsUndefined() &&
                  ArkTSUtils::ParseJsColorAlpha(vm, backgroundColorValue, color, resBackgroundColorObj, nodeInfo);
        swiperArrowParameters.backgroundColor =
            parseOk ? (swiperArrowParameters.parametersByUser.insert("backgroundColor"), color)
                    : swiperIndicatorTheme->GetSmallArrowBackgroundColor();
        if (swiperArrowParameters.isShowBackground.value()) {
            swiperArrowParameters.arrowSize = swiperArrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
        } else {
            parseOk = !arrowSizeValue.IsNull() && !arrowSizeValue->IsUndefined() &&
                      ArkTSUtils::ParseJsDimensionVpNG(vm, arrowSizeValue, dimension, resArrowSizeObj);
            swiperArrowParameters.arrowSize =
                parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                    ? dimension
                    : swiperIndicatorTheme->GetSmallArrowSize();
            swiperArrowParameters.backgroundSize = swiperArrowParameters.arrowSize;
        }
        parseOk = !arrowColorValue.IsNull() && !arrowColorValue->IsUndefined() &&
                  ArkTSUtils::ParseJsColorAlpha(vm, arrowColorValue, color, resArrowColorObj, nodeInfo);
        swiperArrowParameters.arrowColor = parseOk
                                               ? (swiperArrowParameters.parametersByUser.insert("arrowColor"), color)
                                               : swiperIndicatorTheme->GetSmallArrowColor();
    }
    if (SystemProperties::ConfigChangePerform()) {
        swiperArrowParameters.resourceBackgroundSizeValueObject = resBackgroundSizeObj;
        swiperArrowParameters.resourceBackgroundColorValueObject = resBackgroundColorObj;
        swiperArrowParameters.resourceArrowSizeValueObject = resArrowSizeObj;
        swiperArrowParameters.resourceArrowColorValueObject = resArrowColorObj;
    }
    return true;
}
} // namespace

bool ParseJsBoolForSwiper(const EcmaVM* vm, const Local<JSValueRef>& value, bool& result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsBoolForSwiper(vm, value, result, resourceObject);
}

bool ParseJsBoolForSwiper(
    const EcmaVM* vm, const Local<JSValueRef>& value, bool& result, RefPtr<ResourceObject>& resourceObject)
{
    if (!value->IsBoolean() && !value->IsObject(vm)) {
        return false;
    }
    if (value->IsBoolean()) {
        result = value->ToBoolean(vm)->Value();
        return true;
    }
    int32_t intResult = 0;
    auto parseResult = ArkTSUtils::ParseJsIntegerWithResource(vm, value, intResult, resourceObject);
    if (parseResult) {
        result = static_cast<bool>(intResult);
    }
    return parseResult;
}

bool ParseSymbolIndicatorIcon(EcmaVM* vm, const Local<JSValueRef>& iconValue, OHOS::Ace::IndicatorIconParam& iconParam)
{
    if (!iconValue->IsObject(vm)) {
        return false;
    }
    auto iconObject = iconValue->ToObject(vm);
    if (!iconObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "fontColor"))) {
        return false;
    }
    ArkTSUtils::SetSymbolOptionApply(vm, iconParam.symbolApply, iconValue);
    if (!iconParam.symbolApply) {
        return false;
    }
    iconParam.sourceType = OHOS::Ace::IndicatorIconParam::SourceType::SYMBOL;
    return true;
}

bool ParseMediaIndicatorIcon(EcmaVM* vm, const Local<JSValueRef>& iconValue, OHOS::Ace::IndicatorIconParam& iconParam)
{
    RefPtr<ResourceObject> resourceObject;
    std::string iconSrc;
    if (!ArkTSUtils::ParseJsMedia(vm, iconValue, iconSrc, resourceObject) || iconSrc.empty()) {
        return false;
    }
    iconParam.sourceType = OHOS::Ace::IndicatorIconParam::SourceType::MEDIA;
    iconParam.iconSrc = iconSrc;
    ArkTSUtils::GetJsMediaBundleInfo(vm, iconValue, iconParam.bundleName, iconParam.moduleName);
    return true;
}

void ParseIndicatorIconList(EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo,
    std::map<int32_t, OHOS::Ace::IndicatorIconParam>& indicatorIconMap)
{
    auto iconListArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_INDICATOR_ICON);
    if (iconListArg.IsEmpty() || iconListArg->IsNull() || iconListArg->IsUndefined() || !iconListArg->IsArray(vm)) {
        return;
    }
    auto iconListLength = ArkTSUtils::GetArrayLength(vm, iconListArg);
    for (size_t index = 0; index < iconListLength; ++index) {
        auto iconInfoValue = panda::ArrayRef::GetValueAt(vm, iconListArg, index);
        if (!iconInfoValue->IsObject(vm)) {
            continue;
        }
        Local<ObjectRef> iconInfoObject = iconInfoValue->ToObject(vm);
        auto itemIndexValue = iconInfoObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "index"));
        int32_t itemIndex = -1;
        if (!ArkTSUtils::ParseJsInteger(vm, itemIndexValue, itemIndex) || itemIndex < 0) {
            continue;
        }
        auto iconValue = iconInfoObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "icon"));
        OHOS::Ace::IndicatorIconParam iconParam;
        if (!ParseSymbolIndicatorIcon(vm, iconValue, iconParam) && !ParseMediaIndicatorIcon(vm, iconValue, iconParam)) {
            continue;
        }
        indicatorIconMap[itemIndex] = std::move(iconParam);
    }
}

void SwiperBridge::RegisterSwiperAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "setSwiperInitialize", "resetSwiperInitialize", "setSwiperNextMargin",
        "resetSwiperNextMargin", "setSwiperPrevMargin", "resetSwiperPrevMargin", "setSwiperDisplayCount",
        "resetSwiperDisplayCount", "setSwiperSwipeByGroup", "resetSwiperSwipeByGroup", "setSwiperDisplayArrow",
        "resetSwiperDisplayArrow", "setSwiperCurve", "resetSwiperCurve", "setSwiperOnChange", "resetSwiperOnChange",
        "setSwiperOnSelected", "resetSwiperOnSelected", "setSwiperDisableSwipe", "resetSwiperDisableSwipe",
        "setSwiperEffectMode", "resetSwiperEffectMode", "setSwiperCachedCount", "resetSwiperCachedCount",
        "setSwiperIsShown", "resetSwiperIsShown", "setSwiperCachedIndependent", "resetSwiperCachedIndependent",
        "setSwiperDisplayMode", "resetSwiperDisplayMode", "setSwiperItemSpace", "resetSwiperItemSpace",
        "setSwiperVertical", "resetSwiperVertical", "setSwiperLoop", "resetSwiperLoop", "setSwiperInterval",
        "resetSwiperInterval", "setSwiperAutoPlay", "resetSwiperAutoPlay", "setSwiperIndex", "resetSwiperIndex",
        "setSwiperIndicator", "resetSwiperIndicator", "setSwiperIndicatorStyle", "setSwiperDuration",
        "resetSwiperDuration", "setSwiperEnabled", "resetSwiperEnabled", "setNestedScroll", "resetNestedScroll",
        "setSwiperOnAnimationStart", "resetSwiperOnAnimationStart", "setSwiperOnAnimationEnd",
        "resetSwiperOnAnimationEnd", "setSwiperOnGestureSwipe", "resetSwiperOnGestureSwipe", "setSwiperOnUnselected",
        "resetSwiperOnUnselected", "setIndicatorInteractive", "resetIndicatorInteractive",
        "setSwiperCustomContentTransition", "resetSwiperCustomContentTransition", "setSwiperOnContentDidScroll",
        "resetSwiperOnContentDidScroll", "setSwiperPageFlipMode", "resetSwiperPageFlipMode",
        "setSwiperOnContentWillScroll", "resetSwiperOnContentWillScroll", "setSwiperMaintainVisibleContentPosition",
        "resetSwiperMaintainVisibleContentPosition", "setSwiperOnScrollStateChanged", "resetSwiperOnScrollStateChanged",
        "setSwiperWidth", "setSwiperHeight", "setSwiperSize", "setSwiperOnClick", "setSwiperRemoteMessage" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperInitialize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperInitialize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperNextMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperNextMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperPrevMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperPrevMargin),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperDisplayCount),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperDisplayCount),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperSwipeByGroup),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperSwipeByGroup),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperDisplayArrow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperDisplayArrow),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperCurve),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperCurve),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnSelected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnSelected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperDisableSwipe),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperDisableSwipe),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperEffectMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperEffectMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperCachedCount),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperCachedCount),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperIsShown),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperIsShown),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperCachedIndependent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperCachedIndependent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperDisplayMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperDisplayMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperItemSpace),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperItemSpace),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperVertical),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperVertical),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperLoop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperLoop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperInterval),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperInterval),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperAutoPlay),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperAutoPlay),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperIndex),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperIndex),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperIndicator),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperIndicator),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperIndicatorStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperDuration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperDuration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperEnabled),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperEnabled),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetNestedScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetNestedScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnAnimationStart),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnAnimationStart),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnAnimationEnd),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnAnimationEnd),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnGestureSwipe),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnGestureSwipe),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnUnselected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnUnselected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetIndicatorInteractive),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetIndicatorInteractive),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperCustomContentTransition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperCustomContentTransition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetOnContentDidScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetOnContentDidScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperPageFlipMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperPageFlipMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnContentWillScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnContentWillScroll),
        panda::FunctionRef::New(
            const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperMaintainVisibleContentPosition),
        panda::FunctionRef::New(
            const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperMaintainVisibleContentPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnScrollStateChanged),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnScrollStateChanged),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnClick),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperRemoteMessage),
    };
    auto swiper = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "swiper"), swiper);
}

void ApplyThemeInConstructor(EcmaVM* vm, ArkUINodeHandle nativeNode)
{
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        return;
    }
    auto themeColors = Framework::JSThemeUtils::GetThemeColors();
    if (!themeColors) {
        // no need to apply custom theme colors
        return;
    }
    Local<JSValueRef> emptyObject = panda::ObjectRef::New(vm);
    SwiperParameters swiperParameters = GetDotIndicatorInfo(vm, emptyObject, nativeNode);
    SwiperThemeUtils::ApplyThemeToDotIndicatorForce(vm, swiperParameters);
    GetArkUINodeModifiers()->getSwiperModifier()->setJsViewStyle(nativeNode, true, &swiperParameters);
    GetArkUINodeModifiers()->getSwiperModifier()->setJsShowIndicator(nativeNode, true);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto controllerPtr = GetArkUINodeModifiers()->getSwiperModifier()->create(false);
    auto controller = AceType::Claim(reinterpret_cast<OHOS::Ace::SwiperController*>(controllerPtr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> controllerArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (!controllerArg.IsNull() && !controllerArg->IsUndefined() && controllerArg->IsObject(vm)) {
        auto* jsController =
            static_cast<Framework::JSSwiperController*>(controllerArg->ToObject(vm)->GetNativePointerField(vm, 0));
        if (jsController) {
            jsController->SetInstanceId(Container::CurrentId());
            jsController->SetControllerHandle(controller);
        }
    }
    ApplyThemeInConstructor(vm, nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->getSwiperController(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperNextMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (isJsView) {
        auto argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
    }
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    Ace::CalcDimension nextMargin;
    RefPtr<ResourceObject> nextMarginResObj;
    if (valueArg->IsUndefined() || valueArg->IsNull() ||
        !ArkTSUtils::ParseJsDimension(vm, valueArg, nextMargin, DimensionUnit::VP, nextMarginResObj) ||
        LessNotEqual(nextMargin.Value(), 0.0)) {
        nextMargin.SetValue(0.0);
    }
    int32_t nextMarginUnit = static_cast<int32_t>(nextMargin.Unit());
    bool ignoreBlank = false;
    if (isJsView) {
        Local<JSValueRef> ignoreBlankArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_TYPE_INDEX);
        if (!ignoreBlankArg.IsNull() && !ignoreBlankArg->IsUndefined() && ignoreBlankArg->IsBoolean()) {
            ignoreBlank = ignoreBlankArg->ToBoolean(vm)->Value();
        }
    }
    if (SystemProperties::ConfigChangePerform()) {
        auto nextMarginRawPtr = AceType::RawPtr(nextMarginResObj);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperNextMarginRaw(
            nativeNode, nextMargin.Value(), nextMarginUnit, ignoreBlank, nextMarginRawPtr);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperNextMargin(
            nativeNode, nextMargin.Value(), nextMarginUnit, ignoreBlank);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperNextMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperNextMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperPrevMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (isJsView) {
        auto argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
    }
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    Ace::CalcDimension prevMargin;
    RefPtr<ResourceObject> preMarginResObj;
    if (valueArg->IsUndefined() || valueArg->IsNull() ||
        !ArkTSUtils::ParseJsDimension(vm, valueArg, prevMargin, DimensionUnit::VP, preMarginResObj) ||
        LessNotEqual(prevMargin.Value(), 0.0)) {
        prevMargin.SetValue(0.0);
    }
    int32_t prevMarginUnit = static_cast<int32_t>(prevMargin.Unit());
    bool ignoreBlank = false;
    if (isJsView) {
        Local<JSValueRef> ignoreBlankArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_TYPE_INDEX);
        if (!ignoreBlankArg.IsNull() && !ignoreBlankArg->IsUndefined() && ignoreBlankArg->IsBoolean()) {
            ignoreBlank = ignoreBlankArg->ToBoolean(vm)->Value();
        }
    }
    if (SystemProperties::ConfigChangePerform()) {
        auto preMarginRawPtr = AceType::RawPtr(preMarginResObj);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperPrevMarginRaw(
            nativeNode, prevMargin.Value(), prevMarginUnit, ignoreBlank, preMarginRawPtr);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperPrevMargin(
            nativeNode, prevMargin.Value(), prevMarginUnit, ignoreBlank);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperPrevMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperPrevMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (isJsView) {
        auto argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
        if (argc < NUM_2) {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperNestedScroll(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (isJsView) {
        if (valueArg.IsNull() || valueArg->IsUndefined() || !valueArg->IsNumber()) {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperNestedScroll(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        auto mode = static_cast<NestedScrollMode>(valueArg->Int32Value(vm));
        if (mode < NestedScrollMode::SELF_ONLY || mode > NestedScrollMode::SELF_FIRST) {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperNestedScroll(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        int32_t values[1] = { valueArg->Int32Value(vm) };
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperNestedScroll(nativeNode, &values);
        return panda::JSValueRef::Undefined(vm);
    }
    if (valueArg->IsNumber()) {
        int32_t index = valueArg->Int32Value(vm);
        int32_t values[1] = { 0 };
        values[0] = index;
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperNestedScroll(nativeNode, &values);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperNestedScroll(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetIndicatorInteractive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    bool isNotJsBoolean = valueArg.IsNull() || valueArg->IsUndefined() || !valueArg->IsBoolean();
    if (isJsView && isNotJsBoolean) {
        GetArkUINodeModifiers()->getSwiperModifier()->setIndicatorInteractive(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    bool interactive = valueArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getSwiperModifier()->setIndicatorInteractive(nativeNode, interactive);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetIndicatorInteractive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetIndicatorInteractive(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperDisplayCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    auto argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (isJsView && argc < CALL_ARG_TYPE_INDEX) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);

    if (isJsView) {
        if (valueArg.IsNull() || valueArg->IsUndefined()) {
            return panda::JSValueRef::Undefined(vm);
        }
        if (argc == NUM_3) {
            Local<JSValueRef> swipeByGroupArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_TYPE_INDEX);
            if (!swipeByGroupArg.IsNull() && !swipeByGroupArg->IsUndefined() && swipeByGroupArg->IsBoolean()) {
                GetArkUINodeModifiers()->getSwiperModifier()->setSwiperSwipeByGroup(
                    nativeNode, swipeByGroupArg->ToBoolean(vm)->Value());
            } else {
                GetArkUINodeModifiers()->getSwiperModifier()->setSwiperSwipeByGroup(nativeNode, false);
            }
        }

        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            if (valueArg->IsString(vm) && valueArg->ToString(vm)->ToString(vm) == "auto") {
                GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayCount(nativeNode, "auto", "string");
            } else if (valueArg->IsNumber() && valueArg->Int32Value(vm) > 0) {
                std::string displayCountValue = std::to_string(valueArg->Int32Value(vm));
                GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayCount(
                    nativeNode, displayCountValue.c_str(), "number");
            } else if (valueArg->IsObject(vm)) {
                std::string type;
                std::string displayCountValue = ParseDisplayCountObject(valueArg, vm, type);
                GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayCount(
                    nativeNode, displayCountValue.c_str(), type.c_str());
            } else {
                GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayCount(
                    nativeNode, "DEFAULT_DISPLAY_COUNT", "DEFAULT_DISPLAY_COUNT");
            }
            return panda::JSValueRef::Undefined(vm);
        }
        if (valueArg->IsString(vm) && valueArg->ToString(vm)->ToString(vm) == "auto") {
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayCount(nativeNode, "auto", "string");
        } else if (valueArg->IsNumber()) {
            std::string displayCountValue = std::to_string(valueArg->Int32Value(vm));
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayCount(
                nativeNode, displayCountValue.c_str(), "number");
        }
        return panda::JSValueRef::Undefined(vm);
    }

    if (valueArg->IsNumber() || valueArg->IsString(vm)) {
        Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_TYPE_INDEX);
        std::string displayCountValue;
        std::string type = typeArg->ToString(vm)->ToString(vm);
        if (type == "number" || type == "fillType") {
            displayCountValue = std::to_string(valueArg->Int32Value(vm));
        } else {
            displayCountValue = valueArg->ToString(vm)->ToString(vm);
        }
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayCount(
            nativeNode, displayCountValue.c_str(), type.c_str());
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisplayCount(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDisplayCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisplayCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperSwipeByGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    bool swipeByGroup = valueArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperSwipeByGroup(nativeNode, swipeByGroup);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperSwipeByGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperSwipeByGroup(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
std::string GetDimensionUnitString(DimensionUnit unit)
{
    switch (unit) {
        case DimensionUnit::VP:
            return "vp";
        case DimensionUnit::PX:
            return "px";
        case DimensionUnit::FP:
            return "fp";
        case DimensionUnit::CALC:
            return "calc";
        default:
            return "px";
    }
}

ArkUINativeModuleValue SwiperBridge::SetSwiperDisplayArrow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    Local<JSValueRef> displayArrowValue = runtimeCallInfo->GetCallArgRef(DISPLAY_ARROW_VALUE);
    if (isJsView) {
        if (displayArrowValue.IsNull() || displayArrowValue->IsUndefined()) {
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayArrowForJs(nativeNode, false);
            return panda::JSValueRef::Undefined(vm);
        }
        if (!displayArrowValue.IsNull() && !displayArrowValue->IsUndefined() && displayArrowValue->IsObject(vm)) {
            auto displayArrowValueObj = displayArrowValue->ToObject(vm);
            SwiperArrowParameters swiperArrowParameters;
            if (!GetArrowInfo(displayArrowValueObj, swiperArrowParameters, vm, nativeNode)) {
                GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayArrowForJs(nativeNode, false);
                return panda::JSValueRef::Undefined(vm);
            }
            SwiperThemeUtils::ApplyThemeToDisplayArrow(vm, nativeNode, swiperArrowParameters, displayArrowValueObj);
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndicatorStyleByArrowParameters(
                nativeNode, &swiperArrowParameters);
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayArrowForJs(nativeNode, true);
        } else if (!displayArrowValue.IsNull() && !displayArrowValue->IsUndefined() && displayArrowValue->IsBoolean()) {
            if (displayArrowValue->ToBoolean(vm)->Value()) {
                auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
                CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
                auto swiperIndicatorTheme = frameNode->GetTheme<SwiperIndicatorTheme>(true);
                CHECK_NULL_RETURN(swiperIndicatorTheme, panda::JSValueRef::Undefined(vm));
                SwiperArrowParameters swiperArrowParameters;
                swiperArrowParameters.isShowBackground = swiperIndicatorTheme->GetIsShowArrowBackground();
                swiperArrowParameters.isSidebarMiddle = swiperIndicatorTheme->GetIsSidebarMiddle();
                swiperArrowParameters.backgroundSize = swiperIndicatorTheme->GetSmallArrowBackgroundSize();
                swiperArrowParameters.backgroundColor = swiperIndicatorTheme->GetSmallArrowBackgroundColor();
                swiperArrowParameters.arrowSize = swiperIndicatorTheme->GetSmallArrowSize();
                swiperArrowParameters.arrowColor = swiperIndicatorTheme->GetSmallArrowColor();
                SwiperThemeUtils::ApplyThemeToDisplayArrowForce(swiperArrowParameters);
                GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndicatorStyleByArrowParameters(
                    nativeNode, &swiperArrowParameters);
                GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayArrowForJs(nativeNode, true);
            } else {
                GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayArrowForJs(nativeNode, false);
                return panda::JSValueRef::Undefined(vm);
            }
        } else {
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayArrowForJs(nativeNode, false);
            return panda::JSValueRef::Undefined(vm);
        }
        Local<JSValueRef> isHoverShowArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_TYPE_INDEX);
        if (!isHoverShowArg.IsNull() && !isHoverShowArg->IsUndefined() && isHoverShowArg->IsBoolean()) {
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperHoverShowForJs(
                nativeNode, isHoverShowArg->ToBoolean(vm)->Value());
        } else {
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperHoverShowForJs(nativeNode, false);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    Local<JSValueRef> showBackground = runtimeCallInfo->GetCallArgRef(ARROW_IS_SHOW_BACKGROUND);
    Local<JSValueRef> isSidebarMiddle = runtimeCallInfo->GetCallArgRef(ARROW_IS_SIDE_BAR_MIDDLE);
    Local<JSValueRef> backgroundSize = runtimeCallInfo->GetCallArgRef(ARROW_BACKGROUND_SIZE);
    Local<JSValueRef> backgroundColor = runtimeCallInfo->GetCallArgRef(ARROW_BACKGROUND_COLOR);
    Local<JSValueRef> arrowSize = runtimeCallInfo->GetCallArgRef(ARROW_SIZE);
    Local<JSValueRef> arrowColor = runtimeCallInfo->GetCallArgRef(ARROW_COLOR);
    Local<JSValueRef> isHoverShow = runtimeCallInfo->GetCallArgRef(DISPLAY_ARROW_IS_HOVER_SHOW_INDEX);
    std::string displayArrowValueStr = std::to_string(displayArrowValue->Int32Value(vm));
    std::string showBackgroundStr = "2";
    if (!showBackground->IsUndefined()) {
        showBackgroundStr = showBackground->ToBoolean(vm)->Value() ? "1" : "0";
    }
    std::string isSidebarMiddleStr = "2";
    if (!isSidebarMiddle->IsUndefined()) {
        isSidebarMiddleStr = isSidebarMiddle->ToBoolean(vm)->Value() ? "1" : "0";
    }
    CalcDimension lengthValue;
    Color color;
    std::vector<RefPtr<ResourceObject>> resObjs;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    resObjs.resize(ARROW_RESOURCE_VECTOR_LENGTH);
    std::string backgroundSizeStr = ArkTSUtils::ParseJsDimension(vm, backgroundSize, lengthValue, DimensionUnit::VP,
        resObjs.at(ARROW_RESOURCE_BACKGROUND_SIZE), false)
        ? std::to_string(lengthValue.Value()) + GetDimensionUnitString(lengthValue.Unit()) : "-";
    std::string backgroundColorStr = ArkTSUtils::ParseJsColorAlpha(vm, backgroundColor, color,
        resObjs.at(ARROW_RESOURCE_BACKGROUND_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string arrowSizeStr = ArkTSUtils::ParseJsDimensionNG(vm, arrowSize, lengthValue, DimensionUnit::VP,
        resObjs.at(ARROW_RESOURCE_SIZE), false)
        ? std::to_string(lengthValue.Value()) + GetDimensionUnitString(lengthValue.Unit()) : "-";
    std::string arrowColorStr = ArkTSUtils::ParseJsColorAlpha(vm, arrowColor, color,
        resObjs.at(ARROW_RESOURCE_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string isHoverShowStr = "2";
    if (!isHoverShow->IsUndefined()) {
        isHoverShowStr = isHoverShow->ToBoolean(vm)->Value() ? "1" : "0";
    }
    std::string displayArrowStr = displayArrowValueStr + "|" + showBackgroundStr + "|" + isSidebarMiddleStr + "|" +
                                  backgroundSizeStr + "|" + backgroundColorStr + "|" + arrowSizeStr + "|" +
                                  arrowColorStr + "|" + isHoverShowStr + "|1|1|1|1|1|";
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayArrowRaw(nativeNode, displayArrowStr.c_str(),
            static_cast<void*>(&resObjs));
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayArrow(nativeNode, displayArrowStr.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDisplayArrow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisplayArrow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperCurve(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    std::string curve;
    if (isJsView) {
        RefPtr<Curve> curveObj = GetDefaultSwiperCurve();
        if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsString(vm)) {
            auto parsedCurve = Framework::CreateCurve(valueArg->ToString(vm)->ToString(vm), false);
            if (parsedCurve) {
                curveObj = parsedCurve;
            }
        } else if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsObject(vm)) {
            auto parsedCurve = ParseJsViewCurveObject(runtimeCallInfo);
            if (parsedCurve) {
                curveObj = parsedCurve;
            }
        }
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperCurveByCurve(nativeNode, AceType::RawPtr(curveObj));
        return panda::JSValueRef::Undefined(vm);
    } else if (valueArg->IsString(vm)) {
        curve = valueArg->ToString(vm)->ToString(vm);
    }
    if (!curve.empty()) {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperCurve(nativeNode, curve.c_str());
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperCurve(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperCurve(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperCurve(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperDisableSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (isJsView && !valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsBoolean()) {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisableSwipe(
            nativeNode, static_cast<ArkUI_Bool>(valueArg->Uint32Value(vm)));
        return panda::JSValueRef::Undefined(vm);
    }
    if (valueArg->IsBoolean()) {
        bool disableswipe = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisableSwipe(nativeNode, disableswipe);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisableSwipe(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDisableSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisableSwipe(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperEffectMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsNumber()) {
        auto edgeEffect = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperEffectMode(nativeNode, edgeEffect);
    } else if (!isJsView) {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperEffectMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperEffectMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperEffectMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (isJsView) {
        auto argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
    }

    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (isJsView) {
        int32_t cachedCount = DEFAULT_CACHED_COUNT;
        if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsNumber()) {
            cachedCount = valueArg->Int32Value(vm);
            if (cachedCount < 0) {
                cachedCount = DEFAULT_CACHED_COUNT;
            }
        }
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperCachedCount(nativeNode, cachedCount);
        auto argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
        if (argc > CALL_ARG_TYPE_INDEX) {
            Local<JSValueRef> optionArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_TYPE_INDEX);
            if (!optionArg.IsNull() && !optionArg->IsUndefined() && optionArg->IsObject(vm)) {
                ParseCachedCountOptions(vm, nativeNode, optionArg);
                return panda::JSValueRef::Undefined(vm);
            }
            bool isShownValue = !optionArg.IsNull() && !optionArg->IsUndefined() && optionArg->IsBoolean() &&
                                optionArg->ToBoolean(vm)->Value();
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIsShown(nativeNode, isShownValue);
        }
    } else if (valueArg->IsNumber()) {
        int32_t cachedCount = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperCachedCount(nativeNode, cachedCount);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperCachedCount(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperCachedCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperIsShown(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    bool isShown = valueArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIsShown(nativeNode, isShown);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperIsShown(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperIsShown(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperCachedIndependent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    bool independent = valueArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperCachedIndependent(nativeNode, independent);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperCachedIndependent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperCachedIndependent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperDisplayMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsNumber()) {
        int32_t index = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayMode(nativeNode, index);
    } else if (!isJsView) {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisplayMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDisplayMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisplayMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperItemSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (isJsView) {
        auto argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
        if (argc < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
        }
    }
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    Ace::CalcDimension itemSpace;
    if (valueArg.IsNull() || valueArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, valueArg, itemSpace) ||
        LessNotEqual(itemSpace.Value(), 0.0)) {
        itemSpace.SetValue(0.0);
    }
    int32_t itemSpaceUnit = static_cast<int32_t>(itemSpace.Unit());
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperItemSpace(nativeNode, itemSpace.Value(), itemSpaceUnit);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperItemSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperItemSpace(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (isJsView && !valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsBoolean()) {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperVertical(
            nativeNode, static_cast<ArkUI_Bool>(valueArg->Uint32Value(vm)));
        return panda::JSValueRef::Undefined(vm);
    }
    if (valueArg->IsBoolean()) {
        bool isVertical = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperVertical(nativeNode, isVertical);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperVertical(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperVertical(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (isJsView) {
        auto argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
    }
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN) && isJsView) {
        bool loop = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperLoop(nativeNode, loop);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsBoolean()) {
        bool loop = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperLoop(nativeNode, loop);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperLoop(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperLoop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperInterval(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (isJsView) {
        auto argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
    }
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsNumber()) {
        int32_t interval = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperInterval(nativeNode, interval);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperInterval(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperInterval(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperInterval(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperAutoPlay(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    Local<JSValueRef> jsStopWhenTouchedArg = runtimeCallInfo->GetCallArgRef(STOP_WHEN_TOUCHED);
    if (isJsView) {
        bool autoPlay = false;
        if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsBoolean()) {
            autoPlay = valueArg->ToBoolean(vm)->Value();
        }
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperAutoPlay(nativeNode, autoPlay);
        bool neddStopWhenTouched = true;

        if (!jsStopWhenTouchedArg->IsNull() && !jsStopWhenTouchedArg->IsUndefined() &&
            jsStopWhenTouchedArg->IsObject(vm)) {
            auto jsStopWhenTouchedBoolArg = GetNamedProperty(vm, jsStopWhenTouchedArg, "stopWhenTouched");
            if (!jsStopWhenTouchedBoolArg->IsNull() && !jsStopWhenTouchedBoolArg->IsUndefined() &&
                jsStopWhenTouchedBoolArg->IsBoolean()) {
                neddStopWhenTouched = jsStopWhenTouchedBoolArg->ToBoolean(vm)->Value();
            }
        }
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperStopWhenTouched(nativeNode, neddStopWhenTouched);
        return panda::JSValueRef::Undefined(vm);
    }
    if (valueArg->IsBoolean()) {
        bool autoPlay = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperAutoPlay(nativeNode, autoPlay);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperAutoPlay(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    bool neddStopWhenTouched = true;
    if (!jsStopWhenTouchedArg->IsNull() && !jsStopWhenTouchedArg->IsUndefined() && jsStopWhenTouchedArg->IsBoolean()) {
        neddStopWhenTouched = jsStopWhenTouchedArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperStopWhenTouched(nativeNode, neddStopWhenTouched);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperAutoPlay(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperAutoPlay(nativeNode);
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperStopWhenTouched(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    auto argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (isJsView) {
        if (argc < NUM_2 || argc > NUM_3) {
            return panda::JSValueRef::Undefined(vm);
        }
        if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsObject(vm)) {
            SetSwiperIndexChangeEvent(vm, nativeNode, GetNamedProperty(vm, valueArg, "$value"));
            valueArg = GetNamedProperty(vm, valueArg, "value");
        }
        int32_t index = 0;
        if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsNumber()) {
            index = valueArg->Int32Value(vm);
        }
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            index = index < 0 ? 0 : index;
        }
        if (index < 0) {
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndexForJs(nativeNode, index);
        if (argc > 2) {
            SetSwiperIndexChangeEvent(vm, nativeNode, runtimeCallInfo->GetCallArgRef(CALL_ARG_TYPE_INDEX));
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (valueArg->IsNumber()) {
        int32_t index = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndex(nativeNode, index, DEFAULT_ANIMATION_MODE);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperIndex(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
std::string GetStringByValueRef(const EcmaVM* vm, const Local<JSValueRef>& jsValue, RefPtr<ResourceObject>& resObj)
{
    std::string result = "-";
    if (jsValue->IsUndefined()) {
        return result;
    }
    CalcDimension calc;
    result = ArkTSUtils::ParseJsDimension(vm, jsValue, calc, DimensionUnit::VP, resObj, true)
                 ? (calc.Unit() == DimensionUnit::PERCENT
                           ? (std::to_string(calc.Value() * DEFAULT_PERCENT_VALUE) + "%")
                           : (std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit())))
                 : "0.0_vp";
    return result;
}
std::string GetIntStringByValueRef(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    std::string result = "-";
    if (jsValue->IsUndefined()) {
        return result;
    }
    int32_t intValue;
    result = ArkTSUtils::ParseJsInteger(vm, jsValue, intValue) ? std::to_string(intValue) : "0";
    return result;
}

std::string ParseBottom(const EcmaVM* vm, const Local<JSValueRef>& jsValue, bool hasIgnoreSize,
    RefPtr<ResourceObject>& resObj)
{
    std::string bottom = "-";
    if (jsValue->IsUndefined()) {
        return bottom;
    }
    if (hasIgnoreSize) {
        CalcDimension bottomcCalc;
        bool parseOK =  ArkTSUtils::ParseJsLengthMetrics(vm, jsValue, bottomcCalc, resObj);
        if (!parseOK) {
            bottom = GetStringByValueRef(vm, jsValue, resObj);
            return bottom;
        } else {
            bottomcCalc = bottomcCalc > 0.0_vp ? bottomcCalc : 0.0_vp;
            bottom = bottomcCalc.ToString();
            return bottom;
        }
    } else {
        bottom = GetStringByValueRef(vm, jsValue, resObj);
        return bottom;
    }
}

std::optional<bool> ParseIgrnoreSize(const EcmaVM* vm, const Local<JSValueRef>& jsValue, bool hasIgrnoreSize)
{
    std::optional<bool> ignoreSize;
    if (!hasIgrnoreSize) {
        return ignoreSize;
    }
    ignoreSize = false;
    if (!jsValue->IsNull() && !jsValue->IsUndefined() && jsValue->IsBoolean()) {
        ignoreSize = jsValue->ToBoolean(vm)->Value();
    }
    return ignoreSize;
}

std::optional<Dimension> ParseJsViewIndicatorDimension(EcmaVM* vm, const Local<JSValueRef>& value,
    RefPtr<ResourceObject>& resObj)
{
    std::optional<Dimension> indicatorDimension;
    if (value.IsNull() || value->IsUndefined()) {
        return indicatorDimension;
    }
    CalcDimension dimPosition;
    auto parseOk = ArkTSUtils::ParseJsDimension(vm, value, dimPosition, DimensionUnit::VP, resObj);
    indicatorDimension = parseOk && dimPosition.ConvertToPx() >= 0.0f ? dimPosition : 0.0_vp;
    return indicatorDimension;
}

SwiperParameters ParseJsViewIndicatorStyle(
    EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& styleArg, bool& isCustomSize)
{
    SwiperParameters swiperParameters;
    if (styleArg.IsNull() || styleArg->IsUndefined() || !styleArg->IsObject(vm)) {
        return swiperParameters;
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, swiperParameters);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, swiperParameters);
    auto swiperIndicatorTheme = ArkTSUtils::GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, swiperParameters);

    RefPtr<ResourceObject> resLeftObj;
    RefPtr<ResourceObject> resTopObj;
    RefPtr<ResourceObject> resRightObj;
    RefPtr<ResourceObject> resBottomObj;
    swiperParameters.dimLeft = ParseJsViewIndicatorDimension(vm, GetNamedProperty(vm, styleArg, "left"), resLeftObj);
    swiperParameters.dimTop = ParseJsViewIndicatorDimension(vm, GetNamedProperty(vm, styleArg, "top"), resTopObj);
    swiperParameters.dimRight = ParseJsViewIndicatorDimension(vm, GetNamedProperty(vm, styleArg, "right"), resRightObj);
    swiperParameters.dimBottom =
        ParseJsViewIndicatorDimension(vm, GetNamedProperty(vm, styleArg, "bottom"), resBottomObj);

    CalcDimension dimPosition;
    RefPtr<ResourceObject> resItemSizeObj;
    auto sizeValue = GetNamedProperty(vm, styleArg, "size");
    auto parseOk = !sizeValue.IsNull() && !sizeValue->IsUndefined() &&
                   ArkTSUtils::ParseJsDimension(vm, sizeValue, dimPosition, DimensionUnit::VP, resItemSizeObj) &&
                   (dimPosition.Unit() != DimensionUnit::PERCENT);
    isCustomSize = parseOk && dimPosition > 0.0_vp;
    if (isCustomSize) {
        swiperParameters.parametersByUser.insert("itemWidth");
        swiperParameters.parametersByUser.insert("itemHeight");
        swiperParameters.parametersByUser.insert("selectedItemWidth");
        swiperParameters.parametersByUser.insert("selectedItemHeight");
        swiperParameters.itemWidth = dimPosition;
        swiperParameters.itemHeight = dimPosition;
        swiperParameters.selectedItemWidth = dimPosition;
        swiperParameters.selectedItemHeight = dimPosition;
    } else {
        swiperParameters.itemWidth = swiperIndicatorTheme->GetSize();
        swiperParameters.itemHeight = swiperIndicatorTheme->GetSize();
        swiperParameters.selectedItemWidth = swiperIndicatorTheme->GetSize();
        swiperParameters.selectedItemHeight = swiperIndicatorTheme->GetSize();
    }

    auto maskValue = GetNamedProperty(vm, styleArg, "mask");
    if (!maskValue.IsNull() && !maskValue->IsUndefined() && maskValue->IsBoolean()) {
        swiperParameters.maskValue = maskValue->ToBoolean(vm)->Value();
    }
    auto ignoreSizeValue = GetNamedProperty(vm, styleArg, "ignoreSize");
    swiperParameters.ignoreSizeValue =
        !ignoreSizeValue.IsNull() && !ignoreSizeValue->IsUndefined() && ignoreSizeValue->IsBoolean()
            ? ignoreSizeValue->ToBoolean(vm)->Value()
            : false;

    auto colorValue = GetNamedProperty(vm, styleArg, "color");
    auto selectedColorValue = GetNamedProperty(vm, styleArg, "selectedColor");
    Color colorVal;
    RefPtr<ResourceObject> resColorObj;
    RefPtr<ResourceObject> resSelectedColorObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    parseOk = !colorValue.IsNull() && !colorValue->IsUndefined() &&
              ArkTSUtils::ParseJsColorAlpha(vm, colorValue, colorVal, resColorObj, nodeInfo);
    swiperParameters.colorVal =
        parseOk ? (swiperParameters.parametersByUser.insert("colorVal"), colorVal) : swiperIndicatorTheme->GetColor();
    parseOk = !selectedColorValue.IsNull() && !selectedColorValue->IsUndefined() &&
              ArkTSUtils::ParseJsColorAlpha(vm, selectedColorValue, colorVal, resSelectedColorObj, nodeInfo);
    swiperParameters.selectedColorVal = parseOk
                                            ? (swiperParameters.parametersByUser.insert("selectedColorVal"), colorVal)
                                            : swiperIndicatorTheme->GetSelectedColor();

    if (SystemProperties::ConfigChangePerform()) {
        swiperParameters.resourceDimLeftValueObject = resLeftObj;
        swiperParameters.resourceDimTopValueObject = resTopObj;
        swiperParameters.resourceDimRightValueObject = resRightObj;
        swiperParameters.resourceDimBottomValueObject = resBottomObj;
        swiperParameters.resourceColorValueObject = resColorObj;
        swiperParameters.resourceSelectedColorValueObject = resSelectedColorObj;
        swiperParameters.resourceItemSizeValueObject = resItemSizeObj;
    }
    return swiperParameters;
}

std::string ParseSpace(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    std::string result = "-";
    if (jsValue->IsUndefined()) {
        return result;
    }
    CalcDimension calc;
    bool parseOK =  ArkTSUtils::ParseJsLengthMetrics(vm, jsValue, calc);
    calc = (parseOK && !(calc < 0.0_vp) && calc.Unit() != DimensionUnit::PERCENT) ?
        calc : 8.0_vp;
    return calc.ToString();
}

void GetSpaceAndBottom(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::string& bottom,
    std::string& spaceAndIgnoreSize, RefPtr<ResourceObject>& resObj)
{
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_BOTTOM);
    Local<JSValueRef> spaceArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_SPACE);
    Local<JSValueRef> ignoreSizeArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_IGNORE_SIZE);
    Local<JSValueRef> setIgnoreSizeArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_SET_IGNORE_SIZE);

    auto hasIgnoreSize = (setIgnoreSizeArg->IsBoolean() && setIgnoreSizeArg->ToBoolean(vm)->Value()) ? true : false;
    std::optional<bool> ignoreSize = ParseIgrnoreSize(vm, ignoreSizeArg, hasIgnoreSize);
    std::string ignoreSizeStr = "-";
    if (ignoreSize.has_value()) {
        ignoreSizeStr = ignoreSize.value()  ? "1" : "0";
    }

    std::string setIgnoreSizeStr = "-";
    if (!setIgnoreSizeArg->IsUndefined()) {
        setIgnoreSizeStr = setIgnoreSizeArg->ToBoolean(vm)->Value() ? "1" : "0";
    }

    bottom = ParseBottom(vm, bottomArg, hasIgnoreSize, resObj);
    std::string space = ParseSpace(vm, spaceArg);
    spaceAndIgnoreSize =  space + "|" + ignoreSizeStr + "|" + setIgnoreSizeStr;
}

std::string GetSwiperDotIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm,
    std::vector<RefPtr<ResourceObject>>& resObjs, ArkUINodeHandle nativeNode)
{
    Local<JSValueRef> itemWidthArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_ITEM_WIDTH);
    Local<JSValueRef> itemHeightArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_ITEM_HEIGHT);
    Local<JSValueRef> selectedItemWidthArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_SELECTED_ITEM_WIDTH);
    Local<JSValueRef> selectedItemHeightArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_SELECTED_ITEM_HEIGHT);
    Local<JSValueRef> maskArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_MASK);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_COLOR);
    Local<JSValueRef> selectedColorArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_SELECTED_COLOR);
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_LEFT);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_TOP);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_RIGHT);

    CalcDimension calc;
    std::string itemWidth = ArkTSUtils::ParseJsDimension(vm, itemWidthArg, calc, DimensionUnit::VP,
        resObjs.at(DOT_INDICATOR_RESOURCE_ITEM_WIDTH), false)
        ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string itemHeight = ArkTSUtils::ParseJsDimension(vm, itemHeightArg, calc, DimensionUnit::VP,
        resObjs.at(DOT_INDICATOR_RESOURCE_ITEM_HEIGHT), false)
        ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string selectedItemWidth =
        ArkTSUtils::ParseJsDimension(vm, selectedItemWidthArg, calc, DimensionUnit::VP,
            resObjs.at(DOT_INDICATOR_RESOURCE_SELECTED_ITEM_WIDTH), false)
            ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string selectedItemHeight =
        ArkTSUtils::ParseJsDimension(vm, selectedItemHeightArg, calc, DimensionUnit::VP,
            resObjs.at(DOT_INDICATOR_RESOURCE_SELECTED_ITEM_HEIGHT), false)
            ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string mask = "2";
    if (!maskArg->IsUndefined()) {
        mask = maskArg->ToBoolean(vm)->Value() ? "1" : "0";
    }
    Color color;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    std::string colorStr = ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color,
        resObjs.at(DOT_INDICATOR_RESOURCE_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string selectedColor = ArkTSUtils::ParseJsColorAlpha(vm, selectedColorArg, color,
        resObjs.at(DOT_INDICATOR_RESOURCE_SELECTED_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string left = GetStringByValueRef(vm, leftArg, resObjs.at(INDICATOR_RESOURCE_LEFT));
    std::string top = GetStringByValueRef(vm, topArg, resObjs.at(INDICATOR_RESOURCE_TOP));
    std::string right = GetStringByValueRef(vm, rightArg, resObjs.at(INDICATOR_RESOURCE_RIGHT));
    Local<JSValueRef> maxDisplayCountArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_MAX_DISPLAY_COUNT);
    auto maxDisplayCount = GetIntStringByValueRef(vm, maxDisplayCountArg);
    std::string bottom = "-";
    std::string spaceAndIgnoreSize = "-";
    GetSpaceAndBottom(runtimeCallInfo, vm, bottom, spaceAndIgnoreSize, resObjs.at(INDICATOR_RESOURCE_BOTTOM));
    std::string indicatorStr = itemWidth + "|" + itemHeight + "|" + selectedItemWidth + "|" +
                               selectedItemHeight + "|" + mask + "|" + colorStr + "|" + selectedColor + "|" + left +
                               "|" + top + "|" + right + "|" + bottom + "|" + maxDisplayCount + "|" +
                               spaceAndIgnoreSize;
    return indicatorStr;
}
std::string GetSwiperDigitIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm,
    std::vector<RefPtr<ResourceObject>>& resObjs, ArkUINodeHandle nativeNode)
{
    Local<JSValueRef> fontColorArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_FONT_COLOR);
    Local<JSValueRef> selectedFontColorArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_SELECTED_FONT_COLOR);
    Local<JSValueRef> digitFontSizeArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_DIGIT_FONT_SIZE);
    Local<JSValueRef> digitFontWeightArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_DIGIT_FONT_WEIGHT);
    Local<JSValueRef> selectedDigitFontSizeArg =
        runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_SELECTED_DIGIT_FONT_SIZE);
    Local<JSValueRef> selectedDigitFontWeightArg =
        runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_SELECTED_DIGIT_FONT_WEIGHT);
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_LEFT);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_TOP);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_RIGHT);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_BOTTOM);
    Local<JSValueRef> ignoreSizeArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_IGNORE_SIZE);
    Local<JSValueRef> setIgnoreSizeArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_SET_IGNORE_SIZE);
    Color color;
    CalcDimension calc;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    std::string fontColor = ArkTSUtils::ParseJsColorAlpha(vm, fontColorArg, color,
        resObjs.at(DIGIT_INDICATOR_RESOURCE_FONT_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string selectedFontColor = ArkTSUtils::ParseJsColorAlpha(vm, selectedFontColorArg, color,
        resObjs.at(DIGIT_INDICATOR_RESOURCE_FONT_SELECTED_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string digitFontSize = ArkTSUtils::ParseJsDimension(vm, digitFontSizeArg, calc, DimensionUnit::FP,
        resObjs.at(DIGIT_INDICATOR_RESOURCE_FONT_SIZE), false)
        ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string digitFontWeight = digitFontWeightArg->ToString(vm)->ToString(vm);
    std::string selectedDigitFontSize = ArkTSUtils::ParseJsDimension(vm, selectedDigitFontSizeArg, calc,
        DimensionUnit::FP, resObjs.at(DIGIT_INDICATOR_RESOURCE_SELECTED_FONT_SIZE), false)
        ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string selectedDigitFontWeight = selectedDigitFontWeightArg->ToString(vm)->ToString(vm);
    std::string left = GetStringByValueRef(vm, leftArg, resObjs.at(INDICATOR_RESOURCE_LEFT));
    std::string top = GetStringByValueRef(vm, topArg, resObjs.at(INDICATOR_RESOURCE_TOP));
    std::string right = GetStringByValueRef(vm, rightArg, resObjs.at(INDICATOR_RESOURCE_RIGHT));
    
    std::string setIgnoreSize = "-";
    if (!setIgnoreSizeArg->IsUndefined()) {
        setIgnoreSize = setIgnoreSizeArg->ToBoolean(vm)->Value() ? "1" : "0";
    }

    auto hasIgnoreSize = (setIgnoreSizeArg->IsBoolean() && setIgnoreSizeArg->ToBoolean(vm)->Value()) ? true : false;
    std::optional<bool> ignoreSize = ParseIgrnoreSize(vm, ignoreSizeArg, hasIgnoreSize);
    std::string ignoreSizeStr = "-";
    if (ignoreSize.has_value()) {
        ignoreSizeStr = ignoreSize.value()  ? "1" : "0";
    }
    std::string bottom = ParseBottom(vm, bottomArg, hasIgnoreSize, resObjs.at(INDICATOR_RESOURCE_BOTTOM));
    std::string indicatorStr = fontColor + "|" + selectedFontColor + "|" + digitFontSize + "|" + digitFontWeight +
                   "|" + selectedDigitFontSize + "|" + selectedDigitFontWeight + "|" + left + "|" + top + "|" + right +
                   "|" + bottom + "|" + ignoreSizeStr + "|" + setIgnoreSize;
    return indicatorStr;
}

bool SwiperBridge::SetIndicatorController(
    ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, int32_t valueIndex)
{
    CHECK_NULL_RETURN(runtimeCallInfo, false);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, false);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(valueIndex);
    if (valueArg.IsNull() || valueArg->IsUndefined() || !valueArg->IsObject(vm)) {
        return false;
    }

    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, false);
    auto* jsIndicatorController =
        static_cast<Framework::JSIndicatorController*>(valueArg->ToObject(vm)->GetNativePointerField(vm, 0));
    if (!jsIndicatorController) {
        return false;
    }

    jsIndicatorController->SetInstanceId(Container::CurrentId());
    auto targetNode = AceType::Claim(frameNode);
    auto resetFunc = jsIndicatorController->SetSwiperNodeBySwiper(targetNode);
    auto controllerBase = jsIndicatorController->GetControllerBase();
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndicatorController(
        nativeNode, static_cast<void*>(&controllerBase), resetFunc ? static_cast<void*>(&resetFunc) : nullptr);
    return true;
}

void ResetJsViewSwiperNode(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode)
{
    CHECK_NULL_VOID(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    auto currentControllerBase = AceType::Claim(reinterpret_cast<AceType*>(
        GetArkUINodeModifiers()->getSwiperModifier()->getSwiperIndicatorController(nativeNode)));
    RefPtr<AceType> newControllerBase;
    Framework::JSIndicatorController* jsController = nullptr;
    if (runtimeCallInfo->GetArgsNumber() > CALL_ARG_VALUE_INDEX) {
        auto valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
        if (valueArg->IsObject(vm)) {
            jsController =
                static_cast<Framework::JSIndicatorController*>(valueArg->ToObject(vm)->GetNativePointerField(vm, 0));
            if (jsController) {
                newControllerBase = jsController->GetControllerBase();
            }
        }
    }
    if (currentControllerBase && currentControllerBase != newControllerBase) {
        auto* modifier = GetIndicatorControllerModifier();
        if (modifier) {
            modifier->resetSwiperNode(currentControllerBase);
        }
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperIndicatorController(nativeNode);
    }
}

ArkUINativeModuleValue SwiperBridge::SetSwiperIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    std::string indicatorStr = "";
    std::vector<RefPtr<ResourceObject>> resObjs;
    resObjs.resize(INDICATOR_RESOURCE_VECTOR_LENGTH);
    std::map<int32_t, OHOS::Ace::IndicatorIconParam> indicatorIconMap;
    if (isJsView) {
        ResetJsViewSwiperNode(runtimeCallInfo, nativeNode);
        if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
        if (valueArg.IsEmpty() || valueArg->IsUndefined() || valueArg->IsNull()) {
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperShowIndicator(nativeNode, true);
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperBindIndicator(nativeNode, false);
        if (valueArg->IsObject(vm)) {
            auto obj = valueArg->ToObject(vm);
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndicatorIsBoolean(nativeNode, false);
            auto typeArg = GetNamedProperty(vm, valueArg, "type");
            if (!typeArg.IsNull() && !typeArg->IsUndefined() && typeArg->IsString(vm)) {
                if (typeArg->ToString(vm)->ToString(vm) == "DigitIndicator") {
                    SwiperDigitalParameters digitalParameters = GetDigitIndicatorInfo(vm, obj, nativeNode);
                    SwiperThemeUtils::ApplyThemeToDigitIndicator(vm, nativeNode, digitalParameters, obj);
                    GetArkUINodeModifiers()->getSwiperModifier()->setJsViewStyle(nativeNode, false, &digitalParameters);
                } else {
                    SwiperParameters swiperParameters = GetDotIndicatorInfo(vm, obj, nativeNode);
                    ParseIndicatorIconList(vm, runtimeCallInfo, swiperParameters.indicatorIconMap);
                    SwiperThemeUtils::ApplyThemeToDotIndicator(vm, nativeNode, swiperParameters, obj);
                    GetArkUINodeModifiers()->getSwiperModifier()->setJsViewStyle(nativeNode, true, &swiperParameters);
                }
            } else if (typeArg->IsUndefined()) {
                SetIndicatorController(runtimeCallInfo, nativeNode, CALL_ARG_VALUE_INDEX);
                GetArkUINodeModifiers()->getSwiperModifier()->setSwiperShowIndicator(nativeNode, true);
                return panda::JSValueRef::Undefined(vm);
            } else {
                SwiperParameters swiperParameters = GetDotIndicatorInfo(vm, panda::ObjectRef::New(vm), nativeNode);
                ParseIndicatorIconList(vm, runtimeCallInfo, swiperParameters.indicatorIconMap);
                SwiperThemeUtils::ApplyThemeToDotIndicatorForce(vm, swiperParameters);
                GetArkUINodeModifiers()->getSwiperModifier()->setJsViewStyle(nativeNode, true, &swiperParameters);
            }
        } else {
            Local<JSValueRef> emptyObject = panda::ObjectRef::New(vm);
            SwiperParameters swiperParameters = GetDotIndicatorInfo(vm, emptyObject, nativeNode);
            ParseIndicatorIconList(vm, runtimeCallInfo, swiperParameters.indicatorIconMap);
            SwiperThemeUtils::ApplyThemeToDotIndicatorForce(vm, swiperParameters);
            GetArkUINodeModifiers()->getSwiperModifier()->setJsViewStyle(nativeNode, true, &swiperParameters);
        }
        if (valueArg->IsBoolean()) {
            bool showIndicator = false;
            ParseJsBoolForSwiper(vm, valueArg, showIndicator);
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperShowIndicator(nativeNode, showIndicator);
        } else {
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperShowIndicator(nativeNode, true);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    std::string type = valueArg->ToString(vm)->ToString(vm);
    if (type == "boolean") {
        Local<JSValueRef> indicatorArg = runtimeCallInfo->GetCallArgRef(INDICATOR_VALUE_INDEX);
        std::string indicator = indicatorArg->ToBoolean(vm)->Value() ? "1" : "0";
        indicatorStr = type + "|" + indicator;
    } else if (type == "ArkDotIndicator") {
        indicatorStr = type + "|" + GetSwiperDotIndicator(runtimeCallInfo, vm, resObjs, nativeNode);
        ParseIndicatorIconList(vm, runtimeCallInfo, indicatorIconMap);
    } else if (type == "ArkDigitIndicator") {
        indicatorStr = type + "|" + GetSwiperDigitIndicator(runtimeCallInfo, vm, resObjs, nativeNode);
    } else if (type == "IndicatorComponentController") {
        Local<JSValueRef> indicatorControllerArg = runtimeCallInfo->GetCallArgRef(INDICATOR_VALUE_INDEX);
        Framework::JSIndicatorController* jsController =
            indicatorControllerArg->IsObject(vm)
                ? static_cast<Framework::JSIndicatorController*>(
                      indicatorControllerArg->ToObject(vm)->GetNativePointerField(vm, 0))
                : nullptr;
        if (jsController) {
            jsController->SetInstanceId(Container::CurrentId());
            auto targetNode = AceType::Claim(frameNode);
            jsController->SetSwiperNodeBySwiper(targetNode);
        }
        indicatorStr = "IndicatorComponentController|";
    } else {
        indicatorStr = "boolean|1";
    }
    if (!indicatorIconMap.empty()) {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndicatorWithIcon(
            nativeNode, indicatorStr.c_str(),
            SystemProperties::ConfigChangePerform() ? static_cast<void*>(&resObjs) : nullptr,
            static_cast<void*>(&indicatorIconMap));
    } else if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndicatorRaw(nativeNode, indicatorStr.c_str(),
            static_cast<void*>(&resObjs));
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndicator(nativeNode, indicatorStr.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperIndicator(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperIndicatorStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    SwiperParameters swiperParameters;
    if (!styleArg.IsNull() && !styleArg->IsUndefined() && styleArg->IsObject(vm)) {
        bool isCustomSize = false;
        swiperParameters = ParseJsViewIndicatorStyle(vm, nativeNode, styleArg, isCustomSize);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndicatorStyleByParameters(
            nativeNode, &swiperParameters, true, isCustomSize);
    }
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndicatorStyleByParameters(
        nativeNode, &swiperParameters, false, false);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (isJsView && runtimeCallInfo->GetArgsNumber() < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (isJsView) {
        if (valueArg.IsNull()) {
            return panda::JSValueRef::Undefined(vm);
        }
        if (!valueArg->IsUndefined() && valueArg->IsNumber()) {
            int32_t duration = valueArg->Int32Value(vm);
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDuration(nativeNode, duration);
        } else {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDuration(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (valueArg->IsNumber()) {
        int32_t duration = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDuration(nativeNode, duration);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDuration(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDuration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (isJsView && runtimeCallInfo->GetArgsNumber() < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (isJsView && !valueArg.IsNull() && !valueArg->IsUndefined() && !valueArg->IsBoolean()) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (valueArg->IsBoolean()) {
        bool enabled = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setEnabled(nativeNode, enabled);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperEnabled(nativeNode, enabled);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetEnabled(nativeNode);
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperEnabled(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetEnabled(nativeNode);
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperEnabled(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback = [isJsView, frameWeakNode = AceType::WeakClaim(frameNode),
        func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        auto vm = func.GetEcmaVM();
        ACE_SCORING_EVENT("Swiper.onChange");
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper onChange callback execute failed.");
            return;
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, swiperInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam }; // 1: Array length
        auto result = func->Call(vm, func.ToLocal(), params, 1); // 1: Array length
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnSelected(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback = [isJsView, frameWeakNode = AceType::WeakClaim(frameNode),
        func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        auto vm = func.GetEcmaVM();
        ACE_SCORING_EVENT("Swiper.onSelected");
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper onSelected callback execute failed.");
            return;
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, swiperInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam }; // 1: Array length
        auto result = func->Call(vm, func.ToLocal(), params, 1); // 1: Array length
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnSelected(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnAnimationStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnAnimationStart(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t, const AnimationCallbackInfo&)> callback =
        [isJsView, frameWeakNode = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func)](
        int32_t index, int32_t targetIndex, const AnimationCallbackInfo& extraInfo) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        panda::Local<panda::NumberRef> targetIndexParam = panda::NumberRef::New(vm, targetIndex);
        const char* keys[] = {"currentOffset", "targetOffset", "velocity"};
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, extraInfo.currentOffset.value_or(0.0f)),
            panda::NumberRef::New(vm, extraInfo.targetOffset.value_or(0.0f)),
            panda::NumberRef::New(vm, extraInfo.velocity.value_or(0.0f)) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[3] = { indexParam, targetIndexParam, eventObject }; // 3: Array length
        auto result = func->Call(vm, func.ToLocal(), params, 3); // 3: Array length
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnAnimationStart(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnAnimationStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnAnimationStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnAnimationEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnAnimationEnd(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, const AnimationCallbackInfo&)> callback =
        [isJsView, frameWeakNode = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func)](
        int32_t index, const AnimationCallbackInfo& extraInfo) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        const char* keys[] = {"currentOffset", "targetOffset", "velocity"};
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, extraInfo.currentOffset.value()),
            panda::NumberRef::New(vm, 0),
            panda::NumberRef::New(vm, 0) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[2] = { indexParam, eventObject }; // 2: Array length
        auto result = func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnAnimationEnd(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnAnimationEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnAnimationEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnGestureSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnGestureSwipe(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, const AnimationCallbackInfo&)> callback =
        [isJsView, frameWeakNode = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func)](
        int32_t index, const AnimationCallbackInfo& extraInfo) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        const char* keys[] = {"currentOffset", "targetOffset", "velocity"};
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, extraInfo.currentOffset.value()),
            panda::NumberRef::New(vm, 0),
            panda::NumberRef::New(vm, 0) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[2] = { indexParam, eventObject }; // 2: Array length
        auto result = func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnGestureSwipe(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnGestureSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnGestureSwipe(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnUnselected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnUnselected(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [isJsView, frameWeakNode = AceType::WeakClaim(frameNode),
        func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper OnUnselected callback execute failed.");
            return;
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, swiperInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam }; // 1: Array length
        auto result = func->Call(vm, func.ToLocal(), params, 1); // 1: Array length
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnUnselected(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnUnselected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnUnselected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperCustomContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }

    Local<JSValueRef> transitionArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (transitionArg->IsNull() || transitionArg->IsUndefined() || !transitionArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    SwiperContentAnimatedTransition transitionInfo;
    auto transitionObj = transitionArg->ToObject(vm);
    auto timeoutProperty = ArkTSUtils::GetProperty(vm, transitionObj, "timeout");
    if (!timeoutProperty->IsNull() && !timeoutProperty->IsUndefined() && timeoutProperty->IsNumber()) {
        auto timeout = timeoutProperty->Int32Value(vm);
        transitionInfo.timeout = timeout < 0 ? 0 : timeout;
    } else {
        transitionInfo.timeout = 0;
    }

    auto transition = ArkTSUtils::GetProperty(vm, transitionObj, "transition");
    if (!transition->IsNull() && !transition->IsUndefined() && transition->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> funcRef = transition->ToObject(vm);
        auto onTransition = [vm, frameWeakNode = AceType::WeakClaim(frameNode),
                                func = panda::CopyableGlobal(vm, funcRef),
                                isJsView](const RefPtr<SwiperContentTransitionProxy>& proxy) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(frameWeakNode);
            ACE_SCORING_EVENT("Swiper.customContentTransition");
            auto proxyObj = CreateSwiperContentTransitionProxyObject(vm, proxy);
            panda::Local<panda::JSValueRef> params[] = { proxyObj };
            auto result = func->Call(vm, func.ToLocal(), params, 1); // 1: Array length
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
        transitionInfo.transition = std::move(onTransition);
    }
    auto swiperModifier = GetArkUINodeModifiers()->getSwiperModifier();
    CHECK_NULL_RETURN(swiperModifier, panda::JSValueRef::Undefined(vm));
    swiperModifier->setSwiperCustomContentTransition(nativeNode, &transitionInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperCustomContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto swiperModifier = GetArkUINodeModifiers()->getSwiperModifier();
    CHECK_NULL_RETURN(swiperModifier, panda::JSValueRef::Undefined(vm));
    swiperModifier->resetSwiperCustomContentTransition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetOnContentDidScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnContentDidScroll(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t, float_t, float_t)> callback =
        [isJsView, frameWeakNode = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func)](
        int32_t selectedIndex, int32_t index, float position, float mainAxisLength) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        panda::Local<panda::NumberRef> selectedIndexParam = panda::NumberRef::New(vm, selectedIndex);
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        panda::Local<panda::NumberRef> positionParam = panda::NumberRef::New(vm, position);
        panda::Local<panda::NumberRef> mainAxisLengthParam = panda::NumberRef::New(vm, mainAxisLength);
        panda::Local<panda::JSValueRef> params[4] = { selectedIndexParam, indexParam, // 4: Array length
            positionParam, mainAxisLengthParam };
        auto result = func->Call(vm, func.ToLocal(), params, 4); // 4: Array length
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnContentDidScroll(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetOnContentDidScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnContentDidScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperPageFlipMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (isJsView) {
        int32_t value = 0;
        if (valueArg.IsNull() || valueArg->IsUndefined() || !valueArg->IsNumber()) {
            GetArkUINodeModifiers()->getSwiperModifier()->setSwiperPageFlipMode(nativeNode, value);
            return panda::JSValueRef::Undefined(vm);
        }
        ArkTSUtils::ParseJsInt32(vm, valueArg, value);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperPageFlipMode(nativeNode, value);
        return panda::JSValueRef::Undefined(vm);
    }
    if (valueArg->IsNumber()) {
        int32_t pageFlipMode = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperPageFlipMode(nativeNode, pageFlipMode);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperPageFlipMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperPageFlipMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperPageFlipMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnContentWillScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnContentWillScroll(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const SwiperContentWillScrollResult&)> callback =
        [isJsView, frameWeakNode = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func)](
        const SwiperContentWillScrollResult& result) -> bool {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        const char* keys[] = { "currentIndex", "comingIndex", "offset" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, result.currentIndex),
            panda::NumberRef::New(vm, result.comingIndex), panda::NumberRef::New(vm, result.offset) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return true;
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnContentWillScroll(
        nativeNode, reinterpret_cast<bool*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnContentWillScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnContentWillScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperMaintainVisibleContentPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsBoolean()) {
        bool value = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSwiperModifier()->setMaintainVisibleContentPosition(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetMaintainVisibleContentPosition(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperMaintainVisibleContentPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetMaintainVisibleContentPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnScrollStateChanged(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (!callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnScrollStateChanged(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback = [isJsView, frameWeakNode = AceType::WeakClaim(frameNode),
        func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        auto vm = func.GetEcmaVM();
        ACE_SCORING_EVENT("Swiper.onScrollStateChanged");
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        const auto* scrollStateInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!scrollStateInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "scrollStateInfo invalid, OnScrollStateChanged failed.");
            return;
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, scrollStateInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnScrollStateChanged(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnScrollStateChanged(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnScrollStateChanged(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto result = CommonBridge::SetWidth(runtimeCallInfo);
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperMainSizeWidth();
    return result;
}

ArkUINativeModuleValue SwiperBridge::SetSwiperHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto result = CommonBridge::SetHeight(runtimeCallInfo);
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperMainSizeHeight();
    return result;
}

ArkUINativeModuleValue SwiperBridge::SetSwiperSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    if (runtimeCallInfo->GetArgsNumber() < NUM_3) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto result = CommonBridge::SetSize(runtimeCallInfo);
    auto swiperModifier = GetArkUINodeModifiers()->getSwiperModifier();
    swiperModifier->setSwiperMainSizeWidth();
    swiperModifier->setSwiperMainSizeHeight();
    return result;
}

Local<panda::ObjectRef> CreateClickInfo(EcmaVM* vm, const ClickInfo& info)
{
    auto obj = panda::ObjectRef::New(vm);
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    Offset screenOffset = info.GetScreenLocation();
    Offset globalDisplayOffset = info.GetGlobalDisplayLocation();
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "globalDisplayX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalDisplayOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "globalDisplayY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalDisplayOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "displayX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "displayY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "windowX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "windowY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "screenX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "screenY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "x"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "y"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "timestamp"),
        panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "source"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceDevice())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "deviceId"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetDeviceId())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getModifierKeyState"),
        panda::FunctionRef::New(vm, NG::ArkTSUtils::JsGetModifierKeyState));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "target"), FrameNodeBridge::CreateEventTargetObject(vm, info));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "pressure"),
        panda::NumberRef::New(vm, info.GetForce()));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltX"),
        panda::NumberRef::New(vm, info.GetTiltX().value_or(0.0f)));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltY"),
        panda::NumberRef::New(vm, info.GetTiltY().value_or(0.0f)));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "rollAngle"),
        panda::NumberRef::New(vm, info.GetRollAngle().value_or(0.0f)));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sourceTool"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceTool())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "axisVertical"),
        panda::NumberRef::New(vm, 0.0));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "axisHorizontal"),
        panda::NumberRef::New(vm, 0.0));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "axisPinch"),
        panda::NumberRef::New(vm, 0.0));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "targetDisplayId"),
        panda::NumberRef::New(vm, info.GetTargetDisplayId()));
#ifdef USE_ARK_ENGINE
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getCurrentLocalPosition"),
        panda::FunctionRef::New(vm, Framework::JsGetCurrentLocalPosition));
#endif
    obj->SetNativePointerFieldCount(vm, 1);
    obj->SetNativePointerField(vm, 0, static_cast<void*>(const_cast<ClickInfo*>(&info)));
    return obj;
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (Container::IsCurrentUseNewPipeline()) {
        CommonBridge::SetOnClick(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (callbackArg.IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto obj = callbackArg->ToObject(vm);
    panda::Local<panda::FunctionRef> func = obj;
    std::function<void(const BaseEventInfo* info, const RefPtr<V2::InspectorFunctionImpl>& impl)> onClick =
        [isJsView, vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode)](
            const BaseEventInfo* info, const RefPtr<V2::InspectorFunctionImpl>& impl) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(node);
            const auto* clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
            if (!clickInfo) {
                TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper onClick callback execute failed.");
                return;
            }
            auto newInfo = *clickInfo;
            if (impl) {
                impl->UpdateEventInfo(newInfo);
            }

            auto obj = CreateClickInfo(vm, newInfo);
            panda::Local<panda::JSValueRef> params[1] = { obj };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    auto swiperModifier = GetArkUINodeModifiers()->getSwiperModifier();
    swiperModifier->setJsSwiperOnClick(nullptr, reinterpret_cast<void*>(&onClick));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperRemoteMessage(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    RemoteCallback remoteCallback;
    ArkTSUtils::JsRemoteMessage(vm, secondArg, remoteCallback);
    auto swiperModifier = GetArkUINodeModifiers()->getSwiperModifier();
    swiperModifier->setJsSwiperRemoteMessage(nullptr, reinterpret_cast<void*>(&remoteCallback));
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
