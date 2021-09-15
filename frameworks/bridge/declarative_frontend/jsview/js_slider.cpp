/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/slider/render_slider.h"
#include "core/components/slider/slider_component.h"
#include "core/components/slider/slider_element.h"
#include "core/components/slider/slider_theme.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"

namespace OHOS::Ace::Framework {

void JSSlider::JSBind(BindingTarget globalObj)
{
    JSClass<JSSlider>::Declare("Slider");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSlider>::StaticMethod("create", &JSSlider::Create, opt);
    JSClass<JSSlider>::StaticMethod("blockColor", &JSSlider::SetBlockColor);
    JSClass<JSSlider>::StaticMethod("trackColor", &JSSlider::SetTrackColor);
    JSClass<JSSlider>::StaticMethod("selectedColor", &JSSlider::SetSelectedColor);
    JSClass<JSSlider>::StaticMethod("minLabel", &JSSlider::SetMinLabel);
    JSClass<JSSlider>::StaticMethod("maxLabel", &JSSlider::SetMaxLabel);
    JSClass<JSSlider>::StaticMethod("showSteps", &JSSlider::SetShowSteps);
    JSClass<JSSlider>::StaticMethod("showTips", &JSSlider::SetShowTips);
    JSClass<JSSlider>::StaticMethod("onChange", &JSSlider::OnChange);
    JSClass<JSSlider>::Inherit<JSViewAbstract>();
    JSClass<JSSlider>::Bind(globalObj);
}

void JSSlider::Create(const JSCallbackInfo& info)
{
    double value = 0;   // value:Current progress value. The default value is 0.
    double min = 0;     // min:Set the minimum value. The default value is 0.
    double max = 100;   // max:Set the maximum value. The default value is 100.
    double step = 1;    // step:Sets the sliding jump value of the slider. The default value is 1.

    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("slider create error, info is non-vaild");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto getvalue = paramObject->GetProperty("value");
    auto getmin = paramObject->GetProperty("min");
    auto getmax = paramObject->GetProperty("max");
    auto getstep = paramObject->GetProperty("step");
    auto getstyle = paramObject->GetProperty("style");

    if (getvalue->IsNumber()) {
        value = getvalue->ToNumber<double>();
    }

    if (getmin->IsNumber()) {
        min = getmin->ToNumber<double>();
    }

    if (getmax->IsNumber()) {
        max = getmax->ToNumber<double>();
    }

    if (getstep->IsNumber()) {
        step = getstep->ToNumber<double>();
    }

    RefPtr<Component> sliderComponent = AceType::MakeRefPtr<OHOS::Ace::SliderComponent>(value, step, min, max);

    ViewStackProcessor::GetInstance()->Push(sliderComponent);
    JSInteractableView::SetFocusNode(true);

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    if (!slider) {
        LOGE("Slider Component is null");
        return;
    }

    auto sliderMode = static_cast<SliderMode>(getstyle->ToNumber<int32_t>());
    if (sliderMode == SliderMode::INSET) {
        slider->SetSliderMode(SliderMode::INSET);
    } else {
        slider->SetSliderMode(SliderMode::OUTSET);
    }

    auto theme = GetTheme<SliderTheme>();
    if (!theme) {
        LOGE("Slider Theme is null");
        return;
    }
    slider->SetThemeStyle(theme);
}

void JSSlider::SetBlockColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsString()) {
        LOGE("arg is not a string");
        return;
    }

    Color color = Color::FromString(info[0]->ToString());

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    if (!slider) {
        LOGE("Slider Component is null");
        return;
    }
    auto block = slider->GetBlock();
    if (!block) {
        LOGE("backColor Component is null");
        return;
    }

    block->SetBlockColor(color);
}

void JSSlider::SetTrackColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsString()) {
        LOGE("arg is not a string");
        return;
    }

    Color color = Color::FromString(info[0]->ToString());

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    if (!slider) {
        LOGE("Slider Component is null");
        return;
    }
    auto track = slider->GetTrack();
    if (!track) {
        LOGE("track Component is null");
        return;
    }
    track->SetBackgroundColor(color);
}

void JSSlider::SetSelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsString()) {
        LOGE("arg is not a string");
        return;
    }

    Color color = Color::FromString(info[0]->ToString());

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    if (!slider) {
        LOGE("Slider Component is null");
        return;
    }
    auto track = slider->GetTrack();
    if (!track) {
        LOGE("track Component is null");
        return;
    }

    track->SetSelectColor(color);
}

void JSSlider::SetMinLabel(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not number.");
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto Slider = AceType::DynamicCast<SliderComponent>(component);
    if (!Slider) {
        LOGE("Slider Component is null");
        return;
    }
    Slider->SetMinValue(info[0]->ToNumber<double>());
}

void JSSlider::SetMaxLabel(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not number.");
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto Slider = AceType::DynamicCast<SliderComponent>(component);
    if (!Slider) {
        LOGE("Slider Component is null");
        return;
    }
    Slider->SetMaxValue(info[0]->ToNumber<double>());
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

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto Slider = AceType::DynamicCast<SliderComponent>(component);
    if (!Slider) {
        LOGE("Slider Component is null");
        return;
    }
    Slider->SetShowSteps(info[0]->ToBoolean());
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

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto Slider = AceType::DynamicCast<SliderComponent>(component);
    if (!Slider) {
        LOGE("Slider Component is null");
        return;
    }
    Slider->SetShowTips(info[0]->ToBoolean());
}

void JSSlider::OnChange(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&SliderComponent::SetOnChange, info)) {
        LOGW("Failed to bind event");
    }
    info.ReturnSelf();
}

} // namespace OHOS::Ace::Framework
