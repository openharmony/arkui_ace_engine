/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

namespace OHOS::Ace {

std::unique_ptr<SliderModel> SliderModel::instance_ = nullptr;

SliderModel* SliderModel::GetInstance()
{
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
    JSClass<JSSlider>::StaticMethod("onChange", &JSSlider::OnChange);
    JSClass<JSSlider>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSlider>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSlider>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSlider>::Inherit<JSViewAbstract>();
    JSClass<JSSlider>::Bind(globalObj);
}

double GetStep(double step, double max, double min)
{
    if (LessOrEqual(step, 0.0) || step > max - min) {
        step = max - min;
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

void JSSlider::Create(const JSCallbackInfo& info)
{
    double value = 0; // value:Current progress value. The default value is 0.
    double min = 0;   // min:Set the minimum value. The default value is 0.
    double max = 100; // max:Set the maximum value. The default value is 100.
    double step = 1;  // step:Sets the sliding jump value of the slider. The default value is 1.
    bool reverse = false;

    if (!info[0]->IsObject()) {
        LOGE("slider create error, info is non-valid");
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

    if (!getValue->IsNull() && getValue->IsNumber()) {
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

    value = GetValue(value, max, min);

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
}

void JSSlider::SetThickness(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
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
        return;
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
        return;
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
        return;
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

    if (!info[0]->IsBoolean()) {
        LOGE("arg is not bool.");
        return;
    }
    SliderModel::GetInstance()->SetShowSteps(info[0]->ToBoolean());
}

void JSSlider::SetShowTips(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsBoolean()) {
        LOGE("arg is not bool.");
        return;
    }
    SliderModel::GetInstance()->SetShowTips(info[0]->ToBoolean());
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

} // namespace OHOS::Ace::Framework
