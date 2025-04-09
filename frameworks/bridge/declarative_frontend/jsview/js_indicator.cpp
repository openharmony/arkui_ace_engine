/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_indicator.h"

#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_ng.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t DEFAULT_INDICATOR_COUNT = 2;
} // namespace
std::unique_ptr<IndicatorModel> IndicatorModel::instance_ = nullptr;
std::mutex IndicatorModel::mutex_;

IndicatorModel* IndicatorModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_.reset(new NG::IndicatorModelNG());
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
namespace {
JSRef<JSVal> SwiperChangeEventToJSValue(const SwiperChangeEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.GetIndex()));
}

} // namespace

void JSIndicator::Create(const JSCallbackInfo& info)
{
    auto indicatorController = IndicatorModel::GetInstance()->Create();
    if (info[0]->IsObject()) {
        auto* jsController = JSRef<JSObject>::Cast(info[0])->Unwrap<JSIndicatorController>();
        if (jsController) {
            jsController->SetInstanceId(Container::CurrentId());
            auto indicatorNode = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            jsController->SetController(indicatorController, indicatorNode);
        }
    }
}

void JSIndicator::JSBind(BindingTarget globalObj)
{
    JSClass<JSIndicator>::Declare("IndicatorComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSIndicator>::StaticMethod("create", &JSIndicator::Create, opt);
    JSClass<JSIndicator>::StaticMethod("count", &JSIndicator::SetCount, opt);
    JSClass<JSIndicator>::StaticMethod("loop", &JSIndicator::SetLoop, opt);
    JSClass<JSIndicator>::StaticMethod("vertical", &JSIndicator::SetVertical, opt);
    JSClass<JSIndicator>::StaticMethod("style", &JSIndicator::SetStyle, opt);
    JSClass<JSIndicator>::StaticMethod("initialIndex", &JSIndicator::SetInitialIndex, opt);
    JSClass<JSIndicator>::StaticMethod("onChange", &JSIndicator::SetOnChange);
    JSClass<JSIndicator>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSIndicator::SetCount(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        IndicatorModel::GetInstance()->SetCount(DEFAULT_INDICATOR_COUNT);
        return;
    }

    auto count = std::max(DEFAULT_INDICATOR_COUNT, info[0]->ToNumber<int32_t>());
    IndicatorModel::GetInstance()->SetCount(count);
}

void JSIndicator::SetLoop(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        IndicatorModel::GetInstance()->SetLoop(true);
        return;
    }

    IndicatorModel::GetInstance()->SetLoop(info[0]->ToBoolean());
}

void JSIndicator::SetVertical(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        IndicatorModel::GetInstance()->SetDirection(Axis::HORIZONTAL);
        return;
    }

    IndicatorModel::GetInstance()->SetDirection(info[0]->ToBoolean() ? Axis::VERTICAL : Axis::HORIZONTAL);
}

void JSIndicator::GetFontContent(const JSRef<JSVal>& font, bool isSelected, SwiperDigitalParameters& digitalParameters)
{
    JSRef<JSVal> size;
    JSRef<JSVal> weight;
    if (font->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(font);
        size = obj->GetProperty("size");
        weight = obj->GetProperty("weight");
    }

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    // set font size, unit FP
    CalcDimension fontSize;
    if (!size->IsUndefined() && !size->IsNull() && ParseJsDimensionFpNG(size, fontSize)) {
        if (LessOrEqual(fontSize.Value(), 0.0) || LessOrEqual(size->ToNumber<double>(), 0.0) ||
            fontSize.Unit() == DimensionUnit::PERCENT) {
            fontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
        }
    } else {
        fontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
    }
    if (isSelected) {
        digitalParameters.selectedFontSize = fontSize;
    } else {
        digitalParameters.fontSize = fontSize;
    }
    
    if (!weight->IsNull()) {
        std::string weightValue;
        if (weight->IsNumber()) {
            weightValue = std::to_string(weight->ToNumber<int32_t>());
        } else {
            ParseJsString(weight, weightValue);
        }
        if (isSelected) {
            digitalParameters.selectedFontWeight = ConvertStrToFontWeight(weightValue);
        } else {
            digitalParameters.fontWeight = ConvertStrToFontWeight(weightValue);
        }
    } else {
        if (isSelected) {
            digitalParameters.selectedFontWeight = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        } else {
            digitalParameters.fontWeight = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        }
    }
}

std::optional<Dimension> JSIndicator::ParseIndicatorDimension(const JSRef<JSVal>& value)
{
    std::optional<Dimension> indicatorDimension;
    if (value->IsUndefined()) {
        return indicatorDimension;
    }
    CalcDimension dimPosition;
    auto parseOk = ParseJsDimensionVpNG(value, dimPosition);
    indicatorDimension = parseOk && dimPosition.ConvertToPx() >= 0.0f ? dimPosition : 0.0_vp;
    return indicatorDimension;
}

SwiperParameters JSIndicator::GetDotIndicatorInfo(const JSRef<JSObject>& obj)
{
    JSRef<JSVal> leftValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT_VALUE));
    JSRef<JSVal> topValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP_VALUE));
    JSRef<JSVal> rightValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT_VALUE));
    JSRef<JSVal> bottomValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM_VALUE));
    JSRef<JSVal> startValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::START_VALUE));
    JSRef<JSVal> endValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::END_VALUE));
    JSRef<JSVal> itemWidthValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::ITEM_WIDTH_VALUE));
    JSRef<JSVal> itemHeightValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::ITEM_HEIGHT_VALUE));
    JSRef<JSVal> selectedItemWidthValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::SELECTED_ITEM_WIDTH_VALUE));
    JSRef<JSVal> selectedItemHeightValue =
        obj->GetProperty(static_cast<int32_t>(ArkUIIndex::SELECTED_ITEM_HEIGHT_VALUE));
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperParameters());
    SwiperParameters swiperParameters;
    swiperParameters.dimLeft = ParseIndicatorDimension(leftValue);
    swiperParameters.dimTop = ParseIndicatorDimension(topValue);
    swiperParameters.dimRight = ParseIndicatorDimension(rightValue);
    swiperParameters.dimBottom = ParseIndicatorDimension(bottomValue);
    CalcDimension dimStart;
    CalcDimension dimEnd;
    std::optional<Dimension> indicatorDimension;
    swiperParameters.dimStart = ParseLengthMetricsToDimension(startValue, dimStart) ? dimStart : indicatorDimension;
    swiperParameters.dimEnd = ParseLengthMetricsToDimension(endValue, dimEnd) ? dimEnd : indicatorDimension;

    CalcDimension dimPosition;
    bool parseItemWOk =
        ParseJsDimensionVpNG(itemWidthValue, dimPosition) && (dimPosition.Unit() != DimensionUnit::PERCENT);
    auto defaultSize = swiperIndicatorTheme->GetSize();
    swiperParameters.itemWidth = parseItemWOk && dimPosition > 0.0_vp ? dimPosition : defaultSize;
    bool parseItemHOk =
        ParseJsDimensionVpNG(itemHeightValue, dimPosition) && (dimPosition.Unit() != DimensionUnit::PERCENT);
    swiperParameters.itemHeight = parseItemHOk && dimPosition > 0.0_vp ? dimPosition : defaultSize;
    bool parseSelectedItemWOk =
        ParseJsDimensionVpNG(selectedItemWidthValue, dimPosition) && (dimPosition.Unit() != DimensionUnit::PERCENT);
    swiperParameters.selectedItemWidth = parseSelectedItemWOk && dimPosition > 0.0_vp ? dimPosition : defaultSize;
    bool parseSelectedItemHOk =
        ParseJsDimensionVpNG(selectedItemHeightValue, dimPosition) && (dimPosition.Unit() != DimensionUnit::PERCENT);
    swiperParameters.selectedItemHeight = parseSelectedItemHOk && dimPosition > 0.0_vp ? dimPosition : defaultSize;
    IndicatorModel::GetInstance()->SetIsIndicatorCustomSize(
        parseSelectedItemWOk || parseSelectedItemHOk || parseItemWOk || parseItemHOk);
    SetDotIndicatorInfo(obj, swiperParameters, swiperIndicatorTheme);
    return swiperParameters;
}
void JSIndicator::SetDotIndicatorInfo(const JSRef<JSObject>& obj, SwiperParameters& swiperParameters,
    const RefPtr<SwiperIndicatorTheme>& swiperIndicatorTheme)
{
    JSRef<JSVal> maskValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::MASK_VALUE));
    JSRef<JSVal> colorValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::COLOR_VALUE));
    JSRef<JSVal> selectedColorValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::SELECTED_COLOR_VALUE));
    JSRef<JSVal> maxDisplayCountVal = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::MAX_DISPLAY_COUNT_VALUE));
    JSRef<JSVal> spaceValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::SPACE_VALUE));
    if (maskValue->IsBoolean()) {
        auto mask = maskValue->ToBoolean();
        swiperParameters.maskValue = mask;
    }
    Color colorVal;
    auto parseOk = ParseJsColor(colorValue, colorVal);
    swiperParameters.colorVal = parseOk ? colorVal : swiperIndicatorTheme->GetColor();
    parseOk = ParseJsColor(selectedColorValue, colorVal);
    swiperParameters.selectedColorVal = parseOk ? colorVal : swiperIndicatorTheme->GetSelectedColor();
    auto defalutSpace = swiperIndicatorTheme->GetIndicatorDotItemSpace();
    CalcDimension dimSpace;
    auto parseSpaceOk = ParseLengthMetricsToDimension(spaceValue, dimSpace) &&
        (dimSpace.Unit() != DimensionUnit::PERCENT);
    swiperParameters.dimSpace =  (parseSpaceOk && !(dimSpace < 0.0_vp)) ? dimSpace : defalutSpace;
    if (maxDisplayCountVal->IsUndefined()) {
        return;
    }
    uint32_t result = 0;
    auto setMaxDisplayCountVal = ParseJsInteger(maxDisplayCountVal, result);
    swiperParameters.maxDisplayCountVal = setMaxDisplayCountVal && result > 0 ? result : 0;
}

SwiperDigitalParameters JSIndicator::GetDigitIndicatorInfo(const JSRef<JSObject>& obj)
{
    JSRef<JSVal> dotLeftValue = obj->GetProperty("leftValue");
    JSRef<JSVal> dotTopValue = obj->GetProperty("topValue");
    JSRef<JSVal> dotRightValue = obj->GetProperty("rightValue");
    JSRef<JSVal> dotBottomValue = obj->GetProperty("bottomValue");
    JSRef<JSVal> fontColorValue = obj->GetProperty("fontColorValue");
    JSRef<JSVal> selectedFontColorValue = obj->GetProperty("selectedFontColorValue");
    JSRef<JSVal> digitFontValue = obj->GetProperty("digitFontValue");
    JSRef<JSVal> selectedDigitFontValue = obj->GetProperty("selectedDigitFontValue");
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperDigitalParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperDigitalParameters());
    SwiperDigitalParameters digitalParameters;
    digitalParameters.dimLeft = ParseIndicatorDimension(dotLeftValue);
    digitalParameters.dimTop = ParseIndicatorDimension(dotTopValue);
    digitalParameters.dimRight = ParseIndicatorDimension(dotRightValue);
    digitalParameters.dimBottom = ParseIndicatorDimension(dotBottomValue);
    Color fontColor;
    auto parseOk = JSViewAbstract::ParseJsColor(fontColorValue, fontColor);
    digitalParameters.fontColor =
        parseOk ? fontColor : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    parseOk = JSViewAbstract::ParseJsColor(selectedFontColorValue, fontColor);
    digitalParameters.selectedFontColor =
        parseOk ? fontColor : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    if (!digitFontValue->IsNull() && digitFontValue->IsObject()) {
        GetFontContent(digitFontValue, false, digitalParameters);
    }
    if (!selectedDigitFontValue->IsNull() && selectedDigitFontValue->IsObject()) {
        GetFontContent(selectedDigitFontValue, true, digitalParameters);
    }
    return digitalParameters;
}

void JSIndicator::SetStyle(const JSCallbackInfo& info)
{
    if (info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);

        JSRef<JSVal> typeParam = obj->GetProperty("type");
        if (typeParam->IsString()) {
            auto type = typeParam->ToString();
            if (type == "DigitIndicator") {
                SwiperDigitalParameters digitalParameters = GetDigitIndicatorInfo(obj);
                IndicatorModel::GetInstance()->SetDigitIndicatorStyle(digitalParameters);
                IndicatorModel::GetInstance()->SetIndicatorType(SwiperIndicatorType::DIGIT);
            } else {
                SwiperParameters swiperParameters = GetDotIndicatorInfo(obj);
                IndicatorModel::GetInstance()->SetDotIndicatorStyle(swiperParameters);
                IndicatorModel::GetInstance()->SetIndicatorType(SwiperIndicatorType::DOT);
            }
        } else {
            SwiperParameters swiperParameters = GetDotIndicatorInfo(obj);
            IndicatorModel::GetInstance()->SetDotIndicatorStyle(swiperParameters);
            IndicatorModel::GetInstance()->SetIndicatorType(SwiperIndicatorType::DOT);
        }
    } else {
        SwiperParameters swiperParameters = GetDotIndicatorInfo(JSRef<JSObject>::New());
        IndicatorModel::GetInstance()->SetDotIndicatorStyle(swiperParameters);
        IndicatorModel::GetInstance()->SetIndicatorType(SwiperIndicatorType::DOT);
    }
}

void JSIndicator::SetOnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto changeHandler = AceType::MakeRefPtr<JsEventFunction<SwiperChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), SwiperChangeEventToJSValue);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [executionContext = info.GetExecutionContext(), func = std::move(changeHandler), node = targetNode](
                        const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            return;
        }
        PipelineContext::SetCallBackNode(node);
        func->Execute(*swiperInfo);
    };

    IndicatorModel::GetInstance()->SetOnChange(std::move(onChange));
}

void JSIndicator::SetInitialIndex(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        IndicatorModel::GetInstance()->SetInitialIndex(0);
        return;
    }

    auto index = std::max(0, info[0]->ToNumber<int32_t>());
    IndicatorModel::GetInstance()->SetInitialIndex(index);
}

void JSIndicatorController::JSBind(BindingTarget globalObj)
{
    JSClass<JSIndicatorController>::Declare("IndicatorComponentController");
    JSClass<JSIndicatorController>::CustomMethod("showNext", &JSIndicatorController::ShowNext);
    JSClass<JSIndicatorController>::CustomMethod("showPrevious", &JSIndicatorController::ShowPrevious);
    JSClass<JSIndicatorController>::CustomMethod("changeIndex", &JSIndicatorController::ChangeIndex);

    JSClass<JSIndicatorController>::Bind(
        globalObj, JSIndicatorController::Constructor, JSIndicatorController::Destructor);
}

void JSIndicatorController::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSIndicatorController>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSIndicatorController::Destructor(JSIndicatorController* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

void JSIndicatorController::ChangeIndex(const JSCallbackInfo& args)
{
    auto controller = controller_.Upgrade();
    CHECK_NULL_VOID(controller);
    ContainerScope scope(instanceId_);
    if (!args[0]->IsNumber()) {
        return;
    }
    bool useAnimation = false;
    if (args.Length() > 1 && args[1]->IsBoolean()) {
        useAnimation = args[1]->ToBoolean();
    }
    auto index = args[0]->ToNumber<int32_t>();
    controller->ChangeIndex(index, useAnimation);
}

} // namespace OHOS::Ace::Framework
