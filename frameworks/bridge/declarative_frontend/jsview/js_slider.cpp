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

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/slider_model_impl.h"
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
    JSClass<JSSlider>::StaticMethod("showSteps", &JSSlider::SetShowSteps);
    JSClass<JSSlider>::StaticMethod("showTips", &JSSlider::SetShowTips);
    JSClass<JSSlider>::StaticMethod("blockBorderColor", &JSSlider::SetBlockBorderColor);
    JSClass<JSSlider>::StaticMethod("blockBorderWidth", &JSSlider::SetBlockBorderWidth);
    JSClass<JSSlider>::StaticMethod("stepColor", &JSSlider::SetStepColor);
    JSClass<JSSlider>::StaticMethod("trackBorderRadius", &JSSlider::SetTrackBorderRadius);
    JSClass<JSSlider>::StaticMethod("blockSize", &JSSlider::SetBlockSize);
    JSClass<JSSlider>::StaticMethod("blockStyle", &JSSlider::SetBlockStyle);
    JSClass<JSSlider>::StaticMethod("stepSize", &JSSlider::SetStepSize);
    JSClass<JSSlider>::StaticMethod("onChange", &JSSlider::OnChange);
    JSClass<JSSlider>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSlider>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSlider>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSlider>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
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
        LOGE("slider create error, info is non-valid");
        SliderModel::GetInstance()->Create(
            static_cast<float>(value), static_cast<float>(step), static_cast<float>(min), static_cast<float>(max));
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

    if (!getValue->IsNull() && getValue->IsNumber()) {
        value = getValue->ToNumber<double>();
    } else if (!getValue->IsNull() && getValue->IsObject()) {
        JSRef<JSObject> valueObj = JSRef<JSObject>::Cast(getValue);
        changeEventVal = valueObj->GetProperty("changeEvent");
        auto valueProperty = valueObj->GetProperty("value");
        value = valueProperty->ToNumber<double>();
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
}

void JSSlider::SetThickness(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
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
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
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
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    Color colorVal;
    if (!ParseJsColor(info[0], colorVal)) {
        auto theme = GetTheme<SliderTheme>();
        CHECK_NULL_VOID(theme);
        colorVal = theme->GetTrackBgColor();
    }
    SliderModel::GetInstance()->SetTrackBackgroundColor(colorVal);
}

void JSSlider::SetSelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    Color colorVal;
    if (!ParseJsColor(info[0], colorVal)) {
        auto theme = GetTheme<SliderTheme>();
        CHECK_NULL_VOID(theme);
        colorVal = theme->GetTrackSelectedColor();
    }
    SliderModel::GetInstance()->SetSelectColor(colorVal);
}

void JSSlider::SetMinLabel(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsString()) {
        LOGE("arg is not string.");
        return;
    }
    SliderModel::GetInstance()->SetMinLabel(info[0]->ToNumber<float>());
}

void JSSlider::SetMaxLabel(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsString()) {
        LOGE("arg is not string.");
        return;
    }
    SliderModel::GetInstance()->SetMaxLabel(info[0]->ToNumber<float>());
}

void JSSlider::SetShowSteps(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    bool showSteps = false;
    if (info[0]->IsBoolean()) {
        showSteps = info[0]->ToBoolean();
    }
    SliderModel::GetInstance()->SetShowSteps(showSteps);
}

void JSSlider::SetShowTips(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
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
        LOGW("The arg is wrong, it is supposed to have at least 1 arguments");
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
        LOGW("The arg is wrong, it is supposed to have at least 1 arguments");
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
        LOGW("The arg is wrong, it is supposed to have at least 1 arguments");
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
        LOGW("The arg is wrong, it is supposed to have at least 1 arguments");
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

void JSSlider::SetBlockSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have at least 1 arguments");
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
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGW("arg is not object.");
        ResetBlockStyle();
        return;
    }
    auto jsObj = JSRef<JSObject>::Cast(info[0]);
    auto getType = jsObj->GetProperty("type");
    if (getType->IsNull() || !getType->IsNumber()) {
        LOGW("block type is not number.");
        ResetBlockStyle();
        return;
    }
    auto type = static_cast<SliderModel::BlockStyleType>(getType->ToNumber<int32_t>());
    if (type == SliderModel::BlockStyleType::IMAGE) {
        std::string src;
        if (!ParseJsMedia(jsObj->GetProperty("image"), src)) {
            ResetBlockStyle();
            return;
        }
        SliderModel::GetInstance()->SetBlockImage(src);
    } else if (type == SliderModel::BlockStyleType::SHAPE) {
        auto shape = jsObj->GetProperty("shape");
        if (!shape->IsObject()) {
            LOGW("shape param is not an object.");
            ResetBlockStyle();
            return;
        }
        JSShapeAbstract* shapeAbstract = JSRef<JSObject>::Cast(shape)->Unwrap<JSShapeAbstract>();
        if (shapeAbstract == nullptr) {
            LOGW("clipShape is null");
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
        LOGW("The arg is wrong, it is supposed to have at least 1 arguments");
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

void JSSlider::OnChange(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("Must contain at least 1 argument");
        return;
    }
    if (!info[0]->IsFunction()) {
        LOGW("Argument is not a function object");
        return;
    }
    SliderModel::GetInstance()->SetOnChange(
        JsEventCallback<void(float, int32_t)>(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0])));
    info.ReturnSelf();
}

void JSSlider::ResetBlockStyle()
{
    SliderModel::GetInstance()->ResetBlockType();
    SliderModel::GetInstance()->ResetBlockImage();
    SliderModel::GetInstance()->ResetBlockShape();
}
} // namespace OHOS::Ace::Framework
