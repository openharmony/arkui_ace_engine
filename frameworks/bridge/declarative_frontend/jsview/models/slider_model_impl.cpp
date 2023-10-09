/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/slider_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/slider/slider_component.h"
#include "core/components/slider/slider_theme.h"

namespace OHOS::Ace::Framework {

void SliderModelImpl::Create(float value, float step, float min, float max)
{
    auto sliderComponent = AceType::MakeRefPtr<OHOS::Ace::SliderComponent>(value, step, min, max);
    ViewStackProcessor::GetInstance()->ClaimElementId(sliderComponent);
    auto theme = JSViewAbstract::GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    sliderComponent->SetThemeStyle(theme);
    ViewStackProcessor::GetInstance()->Push(sliderComponent);
}
void SliderModelImpl::SetSliderMode(const SliderMode& value)
{
    Ace::SliderMode sliderMode = Ace::SliderMode::OUTSET;
    if (value == SliderMode::CAPSULE) {
        sliderMode = Ace::SliderMode::CAPSULE;
    } else if (value == SliderMode::INSET) {
        sliderMode = Ace::SliderMode::INSET;
    } else {
        sliderMode = Ace::SliderMode::OUTSET;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    CHECK_NULL_VOID(slider);
    slider->SetSliderMode(sliderMode);
}
void SliderModelImpl::SetDirection(Axis value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    CHECK_NULL_VOID(slider);
    slider->SetDirection(value);
}
void SliderModelImpl::SetReverse(bool value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    CHECK_NULL_VOID(slider);
    slider->SetReverse(value);
}
void SliderModelImpl::SetBlockColor(const Color& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    CHECK_NULL_VOID(slider);
    auto block = slider->GetBlock();
    CHECK_NULL_VOID(block);
    block->SetBlockColor(value);
}
void SliderModelImpl::SetTrackBackgroundColor(const Color& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    CHECK_NULL_VOID(slider);
    auto track = slider->GetTrack();
    CHECK_NULL_VOID(track);
    track->SetBackgroundColor(value);
}
void SliderModelImpl::SetSelectColor(const Color& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    CHECK_NULL_VOID(slider);
    auto track = slider->GetTrack();
    CHECK_NULL_VOID(track);
    track->SetSelectColor(value);
}
void SliderModelImpl::SetMinLabel(float value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    CHECK_NULL_VOID(slider);
    slider->SetMinValue(value);
}
void SliderModelImpl::SetMaxLabel(float value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    CHECK_NULL_VOID(slider);
    slider->SetMaxValue(value);
}
void SliderModelImpl::SetShowSteps(bool value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    CHECK_NULL_VOID(slider);
    slider->SetShowSteps(value);
}
void SliderModelImpl::SetShowTips(bool value, const std::optional<std::string>& content)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    CHECK_NULL_VOID(slider);
    slider->SetShowTips(value);
}
void SliderModelImpl::SetThickness(const Dimension& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    CHECK_NULL_VOID(slider);
    slider->SetThickness(value);
}
void SliderModelImpl::SetBlockBorderColor(const Color& value) {}
void SliderModelImpl::SetBlockBorderWidth(const Dimension& value) {}
void SliderModelImpl::SetStepColor(const Color& value) {}
void SliderModelImpl::SetTrackBorderRadius(const Dimension& value) {}
void SliderModelImpl::SetBlockSize(const Dimension& width, const Dimension& height) {}
void SliderModelImpl::SetBlockType(BlockStyleType value) {}
void SliderModelImpl::SetBlockImage(
    const std::string& value, const std::string& bundleName, const std::string& moduleName)
{}
void SliderModelImpl::SetBlockShape(const RefPtr<BasicShape>& value) {}
void SliderModelImpl::SetStepSize(const Dimension& value) {}
void SliderModelImpl::SetOnChange(std::function<void(float, int32_t)>&& eventOnChange)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto slider = AceType::DynamicCast<SliderComponent>(component);
    slider->SetOnChange(std::move(eventOnChange));
}

} // namespace OHOS::Ace::Framework