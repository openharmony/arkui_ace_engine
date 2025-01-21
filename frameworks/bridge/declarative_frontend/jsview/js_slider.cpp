/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_slider.h"

#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/slider_model_impl.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_slider_theme.h"
#include "core/components/slider/render_slider.h"
#include "core/components/slider/slider_element.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"

namespace OHOS::Ace {
namespace {
constexpr int SLIDER_SHOW_TIPS_MAX_PARAMS = 2;
} // namespace

std::unique_ptr<SliderModel> SliderModel::instance_ = nullptr;
std::mutex SliderModel::mutex_;

SliderModel* SliderModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::SliderModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::SliderModelNG());
            } else {
                instance_.reset(new Framework::SliderModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSSlider::JSBind(BindingTarget globalObj)
{
    JSClass<JSSlider>::Declare("Slider");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSlider>::StaticMethod("create", &JSSlider::Create, opt);
    JSClass<JSSlider>::StaticMethod("blockColor", &JSSlider::SetBlockColor);
    JSClass<JSSlider>::StaticMethod("trackColor", &JSSlider::SetTrackColor);
    JSClass<JSSlider>::StaticMethod("trackThickness", &JSSlider::SetThickness);
    JSClass<JSSlider>::StaticMethod("selectedColor", &JSSlider::SetSelectedColor);
    JSClass<JSSlider>::StaticMethod("minLabel", &JSSlider::SetMinLabel);
    JSClass<JSSlider>::StaticMethod("maxLabel", &JSSlider::SetMaxLabel);
    JSClass<JSSlider>::StaticMethod("minResponsiveDistance", &JSSlider::SetMinResponsiveDistance);
    JSClass<JSSlider>::StaticMethod("showSteps", &JSSlider::SetShowSteps);
    JSClass<JSSlider>::StaticMethod("showTips", &JSSlider::SetShowTips);
    JSClass<JSSlider>::StaticMethod("blockBorderColor", &JSSlider::SetBlockBorderColor);
    JSClass<JSSlider>::StaticMethod("blockBorderWidth", &JSSlider::SetBlockBorderWidth);
    JSClass<JSSlider>::StaticMethod("stepColor", &JSSlider::SetStepColor);
    JSClass<JSSlider>::StaticMethod("trackBorderRadius", &JSSlider::SetTrackBorderRadius);
    JSClass<JSSlider>::StaticMethod("selectedBorderRadius", &JSSlider::SetSelectedBorderRadius);
    JSClass<JSSlider>::StaticMethod("blockSize", &JSSlider::SetBlockSize);
    JSClass<JSSlider>::StaticMethod("blockStyle", &JSSlider::SetBlockStyle);
    JSClass<JSSlider>::StaticMethod("stepSize", &JSSlider::SetStepSize);
    JSClass<JSSlider>::StaticMethod("sliderInteractionMode", &JSSlider::SetSliderInteractionMode);
    JSClass<JSSlider>::StaticMethod("slideRange", &JSSlider::SetValidSlideRange);
    JSClass<JSSlider>::StaticMethod("digitalCrownSensitivity", &JSSlider::SetDigitalCrownSensitivity);
    JSClass<JSSlider>::StaticMethod("onChange", &JSSlider::OnChange);
    JSClass<JSSlider>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSSlider>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSlider>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSlider>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSSlider>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSlider>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSlider>::StaticMethod("enableHapticFeedback", &JSSlider::SetEnableHapticFeedback);
    JSClass<JSSlider>::InheritAndBind<JSViewAbstract>(globalObj);
}

double GetStep(double step, double max, double min)
{
    if (LessOrEqual(step, 0.0) || step > max - min) {
        step = 1;
    }
    return step;
}

double GetValue(double value, double max, double min)
{
    if (value < min) {
        value = min;
    }

    if (value > max) {
        value = max;
    }
    return value;
}

void ParseSliderValueObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    JsEventCallback<void(float)> onChangeEvent(info.GetExecutionContext(), JSRef<JSFunc>::Cast(changeEventVal));
    SliderModel::GetInstance()->SetOnChangeEvent(std::move(onChangeEvent));
}

void JSSlider::Create(const JSCallbackInfo& info)
{
    static const double valueMin = -1000000.0f;
    double value = valueMin; // value:Current progress value. The default value is min.
    double min = 0;   // min:Set the minimum value. The default value is 0.
    double max = 100; // max:Set the maximum value. The default value is 100.
    double step = 1;  // step:Sets the sliding jump value of the slider. The default value is 1.
    bool reverse = false;

    if (!info[0]->IsObject()) {
        SliderModel::GetInstance()->Create(
            static_cast<float>(value), static_cast<float>(step), static_cast<float>(min), static_cast<float>(max));
        JSSliderTheme::ApplyTheme();
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto getValue = paramObject->GetProperty("value");
    auto getMin = paramObject->GetProperty("min");
    auto getMax = paramObject->GetProperty("max");
    auto getStep = paramObject->GetProperty("step");
    auto getStyle = paramObject->GetProperty("style");
    auto direction = paramObject->GetProperty("direction");
    auto isReverse = paramObject->GetProperty("reverse");
    JSRef<JSVal> changeEventVal;

    if (!getValue->IsNull() && getValue->IsObject()) {
        JSRef<JSObject> valueObj = JSRef<JSObject>::Cast(getValue);
        changeEventVal = valueObj->GetProperty("changeEvent");
        auto valueProperty = valueObj->GetProperty("value");
        value = valueProperty->ToNumber<double>();
    } else if (paramObject->HasProperty("$value")) {
        changeEventVal = paramObject->GetProperty("$value");
        value = getValue->ToNumber<double>();
    } else if (!getValue->IsNull() && getValue->IsNumber()) {
        value = getValue->ToNumber<double>();
    }

    if (!getMin->IsNull() && getMin->IsNumber()) {
        min = getMin->ToNumber<double>();
    }

    if (!getMax->IsNull() && getMax->IsNumber()) {
        max = getMax->ToNumber<double>();
    }

    if (!getStep->IsNull() && getStep->IsNumber()) {
        step = getStep->ToNumber<double>();
    }

    if (!isReverse->IsNull() && isReverse->IsBoolean()) {
        reverse = isReverse->ToBoolean();
    }

    if (GreatOrEqual(min, max)) {
        min = 0;
        max = 100;
    }

    step = GetStep(step, max, min);

    if (!Container::IsCurrentUseNewPipeline()) {
        value = GetValue(value, max, min);
    }

    auto sliderStyle = SliderStyle::OUTSET;
    auto sliderMode = SliderModel::SliderMode::OUTSET;
    if (!getStyle->IsNull() && getStyle->IsNumber()) {
        sliderStyle = static_cast<SliderStyle>(getStyle->ToNumber<int32_t>());
    }
    if (sliderStyle == SliderStyle::INSET) {
        sliderMode = SliderModel::SliderMode::INSET;
    } else if (sliderStyle == SliderStyle::CAPSULE) {
        sliderMode = SliderModel::SliderMode::CAPSULE;
    } else if (sliderStyle == SliderStyle::NONE) {
        sliderMode = SliderModel::SliderMode::NONE;
    } else {
        sliderMode = SliderModel::SliderMode::OUTSET;
    }

    auto sliderDirection = Axis::HORIZONTAL;
    if (!direction->IsNull() && direction->IsNumber()) {
        sliderDirection = static_cast<Axis>(direction->ToNumber<int32_t>());
    }
    if (sliderDirection != Axis::VERTICAL) {
        sliderDirection = Axis::HORIZONTAL;
    }

    SliderModel::GetInstance()->Create(
        static_cast<float>(value), static_cast<float>(step), static_cast<float>(min), static_cast<float>(max));
    SliderModel::GetInstance()->SetSliderMode(sliderMode);
    SliderModel::GetInstance()->SetDirection(sliderDirection);
    SliderModel::GetInstance()->SetReverse(reverse);
    if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction()) {
        ParseSliderValueObject(info, changeEventVal);
    }
    JSSliderTheme::ApplyTheme();
}

void JSSlider::SetThickness(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        value = CalcDimension(0.0);
    }
    SliderModel::GetInstance()->SetThickness(value);
}

void JSSlider::SetBlockColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color colorVal;
    if (!ParseJsColor(info[0], colorVal)) {
        auto theme = GetTheme<SliderTheme>();
        CHECK_NULL_VOID(theme);
        colorVal = theme->GetBlockColor();
    }
    SliderModel::GetInstance()->SetBlockColor(colorVal);
}

void JSSlider::SetTrackColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    NG::Gradient gradient;
    bool isResourceColor = false;
    if (!ConvertGradientColor(info[0], gradient)) {
        Color colorVal;
        if (info[0]->IsNull() || info[0]->IsUndefined() || !ParseJsColor(info[0], colorVal)) {
            auto theme = GetTheme<SliderTheme>();
            CHECK_NULL_VOID(theme);
            colorVal = theme->GetTrackBgColor();
        }
        isResourceColor = true;
        gradient = NG::SliderModelNG::CreateSolidGradient(colorVal);
        // Set track color to Framework::SliderModelImpl. Need to backward compatibility with old pipeline.
        SliderModel::GetInstance()->SetTrackBackgroundColor(colorVal);
    }
    // Set track gradient color to NG::SliderModelNG
    SliderModel::GetInstance()->SetTrackBackgroundColor(gradient, isResourceColor);
}

bool JSSlider::ConvertGradientColor(const JsiRef<JsiValue>& param, NG::Gradient& gradient)
{
    if (param->IsNull() || param->IsUndefined() || !param->IsObject()) {
        return false;
    }

    JSLinearGradient* jsLinearGradient = JSRef<JSObject>::Cast(param)->Unwrap<JSLinearGradient>();
    if (!jsLinearGradient || jsLinearGradient->GetGradient().empty()) {
        return false;
    }

    size_t size = jsLinearGradient->GetGradient().size();
    if (size == 1) {
        // If there is only one color, then this color is used for both the begin and end side.
        NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(jsLinearGradient->GetGradient().front().first));
        gradientColor.SetDimension(jsLinearGradient->GetGradient().front().second);
        gradient.AddColor(gradientColor);
        gradient.AddColor(gradientColor);
        return true;
    }

    for (size_t colorIndex = 0; colorIndex < size; colorIndex++) {
        NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(jsLinearGradient->GetGradient().at(colorIndex).first));
        gradientColor.SetDimension(jsLinearGradient->GetGradient().at(colorIndex).second);
        gradient.AddColor(gradientColor);
    }
    return true;
}

void JSSlider::SetSelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    NG::Gradient gradient;
    bool isResourceColor = false;
    if (!ConvertGradientColor(info[0], gradient)) {
        Color colorVal;
        if (!ParseJsColor(info[0], colorVal)) {
            auto theme = GetTheme<SliderTheme>();
            CHECK_NULL_VOID(theme);
            colorVal = theme->GetTrackSelectedColor();
        }
        isResourceColor = true;
        gradient = NG::SliderModelNG::CreateSolidGradient(colorVal);
        SliderModel::GetInstance()->SetSelectColor(colorVal);
    }
    SliderModel::GetInstance()->SetSelectColor(gradient, isResourceColor);
}

void JSSlider::SetMinLabel(const JSCallbackInfo& info)
{
    if (!info[0]->IsString() && !info[0]->IsNumber()) {
        return;
    }
    SliderModel::GetInstance()->SetMinLabel(info[0]->ToNumber<float>());
}

void JSSlider::SetMaxLabel(const JSCallbackInfo& info)
{
    if (!info[0]->IsString() && !info[0]->IsNumber()) {
        return;
    }
    SliderModel::GetInstance()->SetMaxLabel(info[0]->ToNumber<float>());
}

void JSSlider::SetValidSlideRange(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        SliderModel::GetInstance()->ResetValidSlideRange();
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto getValueRangeFrom = paramObject->GetProperty("from");
    auto getValueRangeTo = paramObject->GetProperty("to");
    float rangeFromValue = std::numeric_limits<float>::quiet_NaN();
    float rangeToValue = std::numeric_limits<float>::quiet_NaN();
    if (getValueRangeFrom->IsEmpty()) {
        rangeFromValue = std::numeric_limits<float>::infinity();
    } else if (getValueRangeFrom->IsNumber()) {
        rangeFromValue = getValueRangeFrom->ToNumber<double>();
    }
    if (getValueRangeTo->IsEmpty()) {
        rangeToValue = std::numeric_limits<float>::infinity();
    } else if (getValueRangeTo->IsNumber()) {
        rangeToValue = getValueRangeTo->ToNumber<double>();
    }

    if (std::isnan(rangeFromValue) || std::isnan(rangeToValue) ||
        (std::isinf(rangeFromValue) && std::isinf(rangeToValue))) {
        SliderModel::GetInstance()->ResetValidSlideRange();
        return;
    }
    SliderModel::GetInstance()->SetValidSlideRange(rangeFromValue, rangeToValue);
}

void JSSlider::SetMinResponsiveDistance(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        SliderModel::GetInstance()->ResetMinResponsiveDistance();
        return;
    }
    float value = 0.0f;
    if (info[0]->IsString() || info[0]->IsNumber()) {
        value = info[0]->ToNumber<float>();
        value = std::isfinite(value) ? value : 0.0f;
        SliderModel::GetInstance()->SetMinResponsiveDistance(value);
    } else {
        SliderModel::GetInstance()->ResetMinResponsiveDistance();
    }
}

void JSSlider::SetShowSteps(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    bool showSteps = false;
    if (info[0]->IsBoolean()) {
        showSteps = info[0]->ToBoolean();
    }
    SliderModel::GetInstance()->SetShowSteps(showSteps);
}

void JSSlider::SetSliderInteractionMode(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        SliderModel::GetInstance()->ResetSliderInteractionMode();
        return;
    }

    if (!info[0]->IsNull() && info[0]->IsNumber()) {
        int32_t num = info[0]->ToNumber<int32_t>();
        int32_t lowRange = static_cast<int32_t>(SliderModel::SliderInteraction::SLIDE_AND_CLICK);
        int32_t upRange = static_cast<int32_t>(SliderModel::SliderInteraction::SLIDE_AND_CLICK_UP);
        if (lowRange <= num && num <= upRange) {
            auto mode = static_cast<SliderModel::SliderInteraction>(num);
            SliderModel::GetInstance()->SetSliderInteractionMode(mode);
        } else {
            SliderModel::GetInstance()->ResetSliderInteractionMode();
        }
    } else {
        SliderModel::GetInstance()->ResetSliderInteractionMode();
    }
}

void JSSlider::SetShowTips(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    bool showTips = false;
    if (info[0]->IsBoolean()) {
        showTips = info[0]->ToBoolean();
    }

    std::optional<std::string> content;
    if (info.Length() == SLIDER_SHOW_TIPS_MAX_PARAMS) {
        std::string str;
        if (ParseJsString(info[1], str)) {
            content = str;
        }
    }

    SliderModel::GetInstance()->SetShowTips(showTips, content);
}

void JSSlider::SetBlockBorderColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    Color colorVal;
    if (!ParseJsColor(info[0], colorVal)) {
        SliderModel::GetInstance()->ResetBlockBorderColor();
        return;
    }
    SliderModel::GetInstance()->SetBlockBorderColor(colorVal);
}

void JSSlider::SetBlockBorderWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    CalcDimension blockBorderWidth;
    if (!ParseJsDimensionVp(info[0], blockBorderWidth)) {
        SliderModel::GetInstance()->ResetBlockBorderWidth();
        return;
    }
    if (LessNotEqual(blockBorderWidth.Value(), 0.0)) {
        SliderModel::GetInstance()->ResetBlockBorderWidth();
        return;
    }
    SliderModel::GetInstance()->SetBlockBorderWidth(blockBorderWidth);
}

void JSSlider::SetStepColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    Color colorVal;
    if (!ParseJsColor(info[0], colorVal)) {
        SliderModel::GetInstance()->ResetStepColor();
        return;
    }
    SliderModel::GetInstance()->SetStepColor(colorVal);
}

void JSSlider::SetTrackBorderRadius(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    CalcDimension trackBorderRadius;
    if (!ParseJsDimensionVpNG(info[0], trackBorderRadius, true)) {
        SliderModel::GetInstance()->ResetTrackBorderRadius();
        return;
    }
    if (LessNotEqual(trackBorderRadius.Value(), 0.0)) {
        SliderModel::GetInstance()->ResetTrackBorderRadius();
        return;
    }
    SliderModel::GetInstance()->SetTrackBorderRadius(trackBorderRadius);
}

void JSSlider::SetSelectedBorderRadius(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    CalcDimension selectedBorderRadius;
    if (!ParseJsDimensionVpNG(info[0], selectedBorderRadius, false)) {
        SliderModel::GetInstance()->ResetSelectedBorderRadius();
        return;
    }
    if (LessNotEqual(selectedBorderRadius.Value(), 0.0)) {
        SliderModel::GetInstance()->ResetSelectedBorderRadius();
        return;
    }
    SliderModel::GetInstance()->SetSelectedBorderRadius(selectedBorderRadius);
}

void JSSlider::SetBlockSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsObject()) {
        SliderModel::GetInstance()->ResetBlockSize();
        return;
    }
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);

    CalcDimension width;
    JSRef<JSVal> jsWidth = sizeObj->GetProperty("width");
    if (!ParseJsDimensionVp(jsWidth, width)) {
        width.SetValue(0.0);
    }
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }

    CalcDimension height;
    JSRef<JSVal> jsHeight = sizeObj->GetProperty("height");
    if (!ParseJsDimensionVp(jsHeight, height)) {
        height.SetValue(0.0);
    }
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }

    SliderModel::GetInstance()->SetBlockSize(width, height);
}

void JSSlider::SetBlockStyle(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        ResetBlockStyle();
        return;
    }
    auto jsObj = JSRef<JSObject>::Cast(info[0]);
    auto getType = jsObj->GetProperty("type");
    if (getType->IsNull() || !getType->IsNumber()) {
        ResetBlockStyle();
        return;
    }
    auto type = static_cast<SliderModel::BlockStyleType>(getType->ToNumber<int32_t>());
    if (type == SliderModel::BlockStyleType::IMAGE) {
        std::string src;
        auto image = jsObj->GetProperty("image");
        if (!ParseJsMedia(image, src)) {
            ResetBlockStyle();
            return;
        }
        std::string bundleName;
        std::string moduleName;
        GetJsMediaBundleInfo(image, bundleName, moduleName);
        SliderModel::GetInstance()->SetBlockImage(src, bundleName, moduleName);
    } else if (type == SliderModel::BlockStyleType::SHAPE) {
        auto shape = jsObj->GetProperty("shape");
        if (!shape->IsObject()) {
            ResetBlockStyle();
            return;
        }
        JSShapeAbstract* shapeAbstract = JSRef<JSObject>::Cast(shape)->Unwrap<JSShapeAbstract>();
        if (shapeAbstract == nullptr) {
            ResetBlockStyle();
            return;
        }
        SliderModel::GetInstance()->SetBlockShape(shapeAbstract->GetBasicShape());
    }
    SliderModel::GetInstance()->SetBlockType(type);
}

void JSSlider::SetStepSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    CalcDimension stepSize;
    if (!ParseJsDimensionVp(info[0], stepSize)) {
        SliderModel::GetInstance()->ResetStepSize();
        return;
    }
    if (LessNotEqual(stepSize.Value(), 0.0)) {
        auto theme = GetTheme<SliderTheme>();
        CHECK_NULL_VOID(theme);
        stepSize = theme->GetMarkerSize();
    }
    SliderModel::GetInstance()->SetStepSize(stepSize);
}

void JSSlider::SetDigitalCrownSensitivity(const JSCallbackInfo& info)
{
#ifdef SUPPORT_DIGITAL_CROWN
    if (info.Length() < 1 || info[0]->IsNull() || !info[0]->IsNumber()) {
        SliderModel::GetInstance()->ResetDigitalCrownSensitivity();
        return;
    }

    auto sensitivity = info[0]->ToNumber<int32_t>();
    if (sensitivity < 0 || sensitivity > static_cast<int32_t>(CrownSensitivity::HIGH)) {
        SliderModel::GetInstance()->ResetDigitalCrownSensitivity();
    } else {
        SliderModel::GetInstance()->SetDigitalCrownSensitivity(static_cast<CrownSensitivity>(sensitivity));
    }
#endif
}

void JSSlider::OnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    SliderModel::GetInstance()->SetOnChange(
        JsEventCallback<void(float, int32_t)>(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0])));
    info.ReturnSelf();
}

void JSSlider::SetEnableHapticFeedback(const JSCallbackInfo& info)
{
    bool isEnableHapticFeedback = true;
    if (info[0]->IsBoolean()) {
        isEnableHapticFeedback = info[0]->ToBoolean();
    }
    SliderModel::GetInstance()->SetEnableHapticFeedback(isEnableHapticFeedback);
}

void JSSlider::ResetBlockStyle()
{
    SliderModel::GetInstance()->ResetBlockType();
    SliderModel::GetInstance()->ResetBlockImage();
    SliderModel::GetInstance()->ResetBlockShape();
}
} // namespace OHOS::Ace::Framework
