/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/slider/slider_view.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void SliderView::Create(float value, float step, float min, float max)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SLIDER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SliderPattern>(); });
    stack->Push(frameNode);
    LoadTheme(frameNode);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Value, value);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Step, step);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Min, min);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Max, max);
}
void SliderView::SetSliderMode(const SliderMode& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SliderLayoutProperty, SliderMode, value);
}
void SliderView::SetDirection(Axis value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SliderLayoutProperty, Direction, value);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Direction, value);
}
void SliderView::SetReverse(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Reverse, value);
}
void SliderView::SetBlockColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, BlockColor, value);
}
void SliderView::SetTrackBackgroundColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, TrackBackgroundColor, value);
}
void SliderView::SetSelectColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, SelectColor, value);
}
void SliderView::SetMinLabel(float value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Min, value);
}
void SliderView::SetMaxLabel(float value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Max, value);
}
void SliderView::SetShowSteps(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, ShowSteps, value);
}
void SliderView::SetShowTips(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, ShowTips, value);
}
void SliderView::SetThickness(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SliderLayoutProperty, Thickness, value);
}
void SliderView::SetOnChange(SliderOnChangeEvent&& eventOnChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(eventOnChange));
}

// TODO: When used, it is obtained from the theme, and cannot be saved in the object set by the developer.
void SliderView::LoadTheme(const RefPtr<FrameNode>& frameNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto castSliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    if (castSliderLayoutProperty) {
        castSliderLayoutProperty->UpdateOutsetBlockSize(theme->GetOutsetBlockSize());
        castSliderLayoutProperty->UpdateOutsetBlockHotSize(theme->GetOutsetBlockHotSize());
        castSliderLayoutProperty->UpdateOutsetTrackThickness(theme->GetOutsetTrackThickness());
        castSliderLayoutProperty->UpdateInsetBlockSize(theme->GetInsetBlockSize());
        castSliderLayoutProperty->UpdateInsetBlockHotSize(theme->GetInsetBlockHotSize());
        castSliderLayoutProperty->UpdateInsetTrackThickness(theme->GetInsetTrackThickness());
    }
    auto castSliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    if (castSliderPaintProperty) {
        castSliderPaintProperty->UpdateBlockColor(theme->GetBlockColor());
        castSliderPaintProperty->UpdateBlockHoverColor(theme->GetBlockHoverColor());
        castSliderPaintProperty->UpdateTipColor(theme->GetTipColor());
        castSliderPaintProperty->UpdateTipTextColor(theme->GetTipTextColor());
        castSliderPaintProperty->UpdateMarkerColor(theme->GetMarkerColor());
        castSliderPaintProperty->UpdateTrackBackgroundColor(theme->GetTrackBgColor());
        castSliderPaintProperty->UpdateSelectColor(theme->GetTrackSelectedColor());
        castSliderPaintProperty->UpdateMarkerSize(theme->GetMarkerSize());
    }
}

} // namespace OHOS::Ace::NG