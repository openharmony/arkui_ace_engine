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

#include "core/components_v2/inspector/slider_composed_element.h"

#include <unordered_map>

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components/slider/slider_element.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const SliderComposedElement&)>> CREATE_JSON_MAP {
    { "value", [](const SliderComposedElement& inspector) { return inspector.GetValue(); } },
    { "max", [](const SliderComposedElement& inspector) { return inspector.GetMax(); } },
    { "min", [](const SliderComposedElement& inspector) { return inspector.GetMin(); } },
    { "step", [](const SliderComposedElement& inspector) { return inspector.GetStep(); } },
    { "style", [](const SliderComposedElement& inspector) { return inspector.GetStyle(); } },
    { "blockColor", [](const SliderComposedElement& inspector) { return inspector.GetBlockColor(); } },
    { "trackColor", [](const SliderComposedElement& inspector) { return inspector.GetTrackColor(); } },
    { "selectedColor", [](const SliderComposedElement& inspector) { return inspector.GetSelectedColor(); } },
    { "showSteps", [](const SliderComposedElement& inspector) { return inspector.GetShowSteps(); } },
    { "showTips", [](const SliderComposedElement& inspector) { return inspector.GetShowTips(); } }
};

} // namespace

void SliderComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(std::string("value: ").append(GetValue()));
    DumpLog::GetInstance().AddDesc(std::string("max: ").append(GetMax()));
    DumpLog::GetInstance().AddDesc(std::string("min: ").append(GetMin()));
    DumpLog::GetInstance().AddDesc(std::string("step: ").append(GetStep()));
    DumpLog::GetInstance().AddDesc(std::string("blockColor: ").append(GetBlockColor()));
    DumpLog::GetInstance().AddDesc(std::string("trackColor: ").append(GetTrackColor()));
    DumpLog::GetInstance().AddDesc(std::string("selectedColor: ").append(GetSelectedColor()));
    DumpLog::GetInstance().AddDesc(std::string("showSteps: ").append(GetShowSteps()));
    DumpLog::GetInstance().AddDesc(std::string("showTips: ").append(GetShowTips()));
}

std::unique_ptr<JsonValue> SliderComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string SliderComposedElement::GetValue() const
{
    auto renderSlider = GetRenderSlider();
    if (renderSlider) {
        return std::to_string(renderSlider->GetValue());
    }
    return "";
}

std::string SliderComposedElement::GetMax() const
{
    auto renderSlider = GetRenderSlider();
    if (renderSlider) {
        return std::to_string(renderSlider->GetMax());
    }
    return "";
}

std::string SliderComposedElement::GetMin() const
{
    auto renderSlider = GetRenderSlider();
    if (renderSlider) {
        return std::to_string(renderSlider->GetMin());
    }
    return "";
}

std::string SliderComposedElement::GetStep() const
{
    auto renderSlider = GetRenderSlider();
    if (renderSlider) {
        return std::to_string(renderSlider->GetStep());
    }
    return "";
}

std::string SliderComposedElement::GetStyle() const
{
    auto renderSlider = GetRenderSlider();
    if (renderSlider) {
        SliderMode mode = renderSlider->GetMode();
        if (mode == SliderMode::OUTSET) {
            return std::string("Outset");
        } else {
            return std::string("Inset");
        }
    }
    return "";
}

std::string SliderComposedElement::GetBlockColor() const
{
    auto renderSlider = GetRenderSlider();
    if (renderSlider) {
        auto slider = renderSlider->GetSliderComponent().Upgrade();
        if (slider) {
            auto block = slider->GetBlock();
            return block->GetBlockColor().ColorToString();
        }
        return "";
    }
    return "";
}

std::string SliderComposedElement::GetTrackColor() const
{
    auto renderSlider = GetRenderSlider();
    if (renderSlider) {
        auto slider = renderSlider->GetSliderComponent().Upgrade();
        if (slider) {
            auto Track = slider->GetTrack();
            return Track->GetBackgroundColor().ColorToString();
        }
        return "";
    }
    return "";
}

std::string SliderComposedElement::GetSelectedColor() const
{
    auto renderSlider = GetRenderSlider();
    if (renderSlider) {
        auto slider = renderSlider->GetSliderComponent().Upgrade();
        if (slider) {
            auto Track = slider->GetTrack();
            return Track->GetSelectColor().ColorToString();
        }
        return "";
    }
    return "";
}

std::string SliderComposedElement::GetShowSteps() const
{
    auto renderSlider = GetRenderSlider();
    if (renderSlider) {
        return ConvertBoolToString(renderSlider->GetShowSteps());
    }
    return "";
}

std::string SliderComposedElement::GetShowTips() const
{
    auto renderSlider = GetRenderSlider();
    if (renderSlider) {
        return ConvertBoolToString(renderSlider->GetShowTips());
    }
    return "";
}

RefPtr<RenderSlider> SliderComposedElement::GetRenderSlider() const
{
    auto node = GetInspectorNode(SliderElement::TypeId());
    if (node) {
        return AceType::DynamicCast<RenderSlider>(node);
    }
    return nullptr;
}

} // namespace OHOS::Ace::V2
