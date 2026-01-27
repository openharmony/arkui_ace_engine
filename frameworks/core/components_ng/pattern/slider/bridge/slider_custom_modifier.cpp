/*
* Copyright (c) 2026 Huawei Device Co., Ltd.
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "frameworks/core/components_ng/pattern/slider/bridge/slider_custom_modifier.h"
#include "frameworks/core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"


namespace OHOS::Ace::NG {
RefPtr<FrameNode> GetFrameNode(RefPtr<FrameNode>& node)
{
    if (node) {
        return node;
    }
    auto* main = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return AceType::Claim(main);
}

RefPtr<FrameNode> CreateSliderFrameNode(int32_t nodeId)
{
    auto frameNode = SliderModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return frameNode;
}

void SliderPatternUpdateValue(RefPtr<FrameNode>& node, float value)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateValue(static_cast<float>(value));
}

void SliderLayoutPropertyUpdatePadding(RefPtr<FrameNode>& node, PaddingProperty value)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(sliderLayoutProperty);
    sliderLayoutProperty->UpdatePadding(value);
}

void SliderLayoutPropertyUpdateLayoutWeight(RefPtr<FrameNode>& node, float value)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(sliderLayoutProperty);
    sliderLayoutProperty->UpdateLayoutWeight(static_cast<float>(value));
}

void SliderEventHubSetOnChange(RefPtr<FrameNode>& node, void* callback)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onChange = reinterpret_cast<std::function<void(float, int32_t)>*>(callback);
    eventHub->SetOnChange(std::move(*onChange));
}

void SliderPaintPropertyUpdateMin(RefPtr<FrameNode>& node, float value)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    sliderPaintProperty->UpdateMin(static_cast<float>(value));
}

void SliderPaintPropertyUpdateMax(RefPtr<FrameNode>& node, float value)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    sliderPaintProperty->UpdateMax(static_cast<float>(value));
}

void SliderPaintPropertyUpdateSelectGradientColor(RefPtr<FrameNode>& node, uint32_t color)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    sliderPaintProperty->UpdateSelectGradientColor(SliderModelNG::CreateSolidGradient(Color(color)));
}

void SliderPaintPropertyUpdateSelectIsResourceColor(RefPtr<FrameNode>& node, bool value)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    sliderPaintProperty->UpdateSelectIsResourceColor(value);
}

void SliderPaintPropertyUpdateTrackBackgroundColor(RefPtr<FrameNode>& node, uint32_t color)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    sliderPaintProperty->UpdateTrackBackgroundColor(SliderModelNG::CreateSolidGradient(Color(color)));
}

void SliderPaintPropertyUpdateTrackBackgroundIsResourceColor(RefPtr<FrameNode>& node, bool value)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    sliderPaintProperty->UpdateTrackBackgroundIsResourceColor(value);
}

void SliderPaintPropertyUpdateValue(RefPtr<FrameNode>& node, float value)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    sliderPaintProperty->UpdateValue(static_cast<float>(value));
}

namespace CustomModifier {
const ArkUISliderCustomModifier* GetSliderCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISliderCustomModifier modifier = {
        .createSliderFrameNode = CreateSliderFrameNode,
        .sliderPatternUpdateValue = SliderPatternUpdateValue,
        .sliderLayoutPropertyUpdatePadding = SliderLayoutPropertyUpdatePadding,
        .sliderLayoutPropertyUpdateLayoutWeight = SliderLayoutPropertyUpdateLayoutWeight,
        .sliderEventHubSetOnChange = SliderEventHubSetOnChange,
        .sliderPaintPropertyUpdateMin = SliderPaintPropertyUpdateMin,
        .sliderPaintPropertyUpdateMax = SliderPaintPropertyUpdateMax,
        .sliderPaintPropertyUpdateSelectGradientColor = SliderPaintPropertyUpdateSelectGradientColor,
        .sliderPaintPropertyUpdateSelectIsResourceColor = SliderPaintPropertyUpdateSelectIsResourceColor,
        .sliderPaintPropertyUpdateTrackBackgroundColor = SliderPaintPropertyUpdateTrackBackgroundColor,
        .sliderPaintPropertyUpdateTrackBackgroundIsResourceColor = SliderPaintPropertyUpdateTrackBackgroundIsResourceColor,
        .sliderPaintPropertyUpdateValue = SliderPaintPropertyUpdateValue,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace CustomModifier
} // namespace OHOS::Ace::NG