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

#include "core/components_ng/pattern/slider/slider_model_ng.h"

#include "core/components/slider/slider_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void SliderModelNG::Create(float value, float step, float min, float max)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SLIDER_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SLIDER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SliderPattern>(); });
    stack->Push(frameNode);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Step, step);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Min, min);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Max, max);
    SetSliderValue(value);
}
void SliderModelNG::SetSliderValue(float value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateValue(value);
}
void SliderModelNG::SetSliderMode(const SliderMode& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SliderLayoutProperty, SliderMode, value);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, SliderMode, value);
}
void SliderModelNG::SetDirection(Axis value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SliderLayoutProperty, Direction, value);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Direction, value);
}
void SliderModelNG::SetReverse(bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SliderLayoutProperty, Reverse, value);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Reverse, value);
}
void SliderModelNG::SetBlockColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, BlockColor, value);
}
void SliderModelNG::SetTrackBackgroundColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, TrackBackgroundColor, value);
}
void SliderModelNG::SetSelectColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, SelectColor, value);
}
void SliderModelNG::SetMinLabel(float value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Min, value);
}
void SliderModelNG::SetMaxLabel(float value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, Max, value);
}
void SliderModelNG::SetShowSteps(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, ShowSteps, value);
}
void SliderModelNG::SetShowTips(bool value, const std::optional<std::string>& content)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, ShowTips, value);
    if (content.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, CustomContent, content.value());
    } else {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, CustomContent, PROPERTY_UPDATE_RENDER);
    }
}
void SliderModelNG::SetThickness(const Dimension& value)
{
    if (value.IsNonPositive()) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SliderTheme>();
        CHECK_NULL_VOID(theme);
        auto sliderMode = layoutProperty->GetSliderModeValue(SliderModel::SliderMode::OUTSET);
        auto themeTrackThickness = sliderMode == SliderModel::SliderMode::OUTSET ? theme->GetOutsetTrackThickness()
                                                                                 : theme->GetInsetTrackThickness();
        ACE_UPDATE_LAYOUT_PROPERTY(SliderLayoutProperty, Thickness, themeTrackThickness);
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(SliderLayoutProperty, Thickness, value);
    }
}
void SliderModelNG::SetBlockBorderColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, BlockBorderColor, value);
}
void SliderModelNG::SetBlockBorderWidth(const Dimension& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, BlockBorderWidth, value);
}
void SliderModelNG::SetStepColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, StepColor, value);
}
void SliderModelNG::SetTrackBorderRadius(const Dimension& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, TrackBorderRadius, value);
}
void SliderModelNG::SetBlockSize(const Dimension& width, const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    SizeT<Dimension> blockSize;
    auto theme = pipeline->GetTheme<SliderTheme>();
    if (theme != nullptr) {
        auto mode = layoutProperty->GetSliderModeValue(SliderMode::OUTSET);
        auto themeBlockSize = mode == SliderMode::OUTSET ? theme->GetOutsetBlockSize() : theme->GetInsetBlockSize();
        blockSize = layoutProperty->GetBlockSizeValue(SizeT<Dimension>(themeBlockSize, themeBlockSize));
    }

    if (LessOrEqual(width.Value(), 0.0) || LessOrEqual(height.Value(), 0.0)) {
        ResetBlockSize();
    } else {
        blockSize.SetWidth(width);
        blockSize.SetHeight(height);
        ACE_UPDATE_LAYOUT_PROPERTY(SliderLayoutProperty, BlockSize, blockSize);
    }
}
void SliderModelNG::SetBlockType(BlockStyleType value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, BlockType, value);
}
void SliderModelNG::SetBlockImage(
    const std::string& value, const std::string& bundleName, const std::string& moduleName)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, BlockImage, value);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, BlockImageBundleName, bundleName);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, BlockImageModuleName, moduleName);
}
void SliderModelNG::SetBlockShape(const RefPtr<BasicShape>& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, BlockShape, value);
}
void SliderModelNG::SetStepSize(const Dimension& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, StepSize, value);
}
void SliderModelNG::SetOnChange(SliderOnChangeEvent&& eventOnChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(eventOnChange));
}

void SliderModelNG::SetOnChangeEvent(SliderOnValueChangeEvent&& onChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}

void SliderModelNG::ResetBlockBorderColor()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, BlockBorderColor, PROPERTY_UPDATE_RENDER);
}

void SliderModelNG::ResetBlockBorderWidth()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, BlockBorderWidth, PROPERTY_UPDATE_RENDER);
}

void SliderModelNG::ResetStepColor()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, StepColor, PROPERTY_UPDATE_RENDER);
}

void SliderModelNG::ResetTrackBorderRadius()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, TrackBorderRadius, PROPERTY_UPDATE_RENDER);
}

void SliderModelNG::ResetBlockSize()
{
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(SliderLayoutProperty, BlockSize, PROPERTY_UPDATE_MEASURE);
}

void SliderModelNG::ResetBlockType()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, BlockType, PROPERTY_UPDATE_RENDER);
}

void SliderModelNG::ResetBlockImage()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, BlockImage, PROPERTY_UPDATE_RENDER);
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, BlockImageBundleName, PROPERTY_UPDATE_RENDER);
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, BlockImageModuleName, PROPERTY_UPDATE_RENDER);
}

void SliderModelNG::ResetBlockShape()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, BlockShape, PROPERTY_UPDATE_RENDER);
}

void SliderModelNG::ResetStepSize()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, StepSize, PROPERTY_UPDATE_RENDER);
}

void SliderModelNG::SetShowTips(FrameNode* frameNode, bool value, const std::optional<std::string>& content)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, ShowTips, value, frameNode);
    if (content.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, CustomContent, content.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, CustomContent, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void SliderModelNG::SetThickness(FrameNode* frameNode, const Dimension& value)
{
    if (value.IsNonPositive()) {
        CHECK_NULL_VOID(frameNode);
        auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SliderTheme>();
        CHECK_NULL_VOID(theme);
        auto sliderMode = layoutProperty->GetSliderModeValue(SliderModel::SliderMode::OUTSET);
        auto themeTrackThickness = sliderMode == SliderModel::SliderMode::OUTSET ? theme->GetOutsetTrackThickness()
                                                                                 : theme->GetInsetTrackThickness();
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, Thickness, themeTrackThickness, frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, Thickness, value, frameNode);
    }
}
void SliderModelNG::SetStepSize(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, StepSize, value, frameNode);
}
void SliderModelNG::SetBlockType(FrameNode* frameNode, BlockStyleType value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockType, value, frameNode);
}
void SliderModelNG::SetBlockShape(FrameNode* frameNode, const RefPtr<BasicShape>& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockShape, value, frameNode);
}
void SliderModelNG::SetBlockSize(FrameNode* frameNode, const Dimension& width, const Dimension& height)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    SizeT<Dimension> blockSize;
    auto theme = pipeline->GetTheme<SliderTheme>();
    if (theme != nullptr) {
        auto mode = layoutProperty->GetSliderModeValue(SliderMode::OUTSET);
        auto themeBlockSize = mode == SliderMode::OUTSET ? theme->GetOutsetBlockSize() : theme->GetInsetBlockSize();
        blockSize = layoutProperty->GetBlockSizeValue(SizeT<Dimension>(themeBlockSize, themeBlockSize));
    }

    if (LessOrEqual(width.Value(), 0.0) || LessOrEqual(height.Value(), 0.0)) {
        ResetBlockSize(frameNode);
    } else {
        blockSize.SetWidth(width);
        blockSize.SetHeight(height);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, BlockSize, blockSize, frameNode);
    }
}
void SliderModelNG::SetTrackBorderRadius(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, TrackBorderRadius, value, frameNode);
}
void SliderModelNG::SetStepColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, StepColor, value, frameNode);
}
void SliderModelNG::SetBlockBorderColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockBorderColor, value, frameNode);
}
void SliderModelNG::SetBlockBorderWidth(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockBorderWidth, value, frameNode);
}
void SliderModelNG::SetBlockColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockColor, value, frameNode);
}
void SliderModelNG::SetTrackBackgroundColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, TrackBackgroundColor, value, frameNode);
}
void SliderModelNG::SetSelectColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, SelectColor, value, frameNode);
}
void SliderModelNG::SetShowSteps(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, ShowSteps, value, frameNode);
}
void SliderModelNG::SetBlockImage(
    FrameNode* frameNode, const std::string& value, const std::string& bundleName, const std::string& moduleName)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockImage, value, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockImageBundleName, bundleName, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockImageModuleName, moduleName, frameNode);
}

void SliderModelNG::ResetStepSize(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, StepSize, PROPERTY_UPDATE_RENDER, frameNode);
}

void SliderModelNG::ResetBlockType(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockType, frameNode);
}

void SliderModelNG::ResetBlockShape(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, BlockShape, PROPERTY_UPDATE_RENDER, frameNode);
}

void SliderModelNG::ResetBlockSize(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(SliderLayoutProperty, BlockSize, PROPERTY_UPDATE_MEASURE, frameNode);
}

void SliderModelNG::ResetTrackBorderRadius(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, TrackBorderRadius, PROPERTY_UPDATE_RENDER, frameNode);
}

void SliderModelNG::ResetStepColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, StepColor, PROPERTY_UPDATE_RENDER, frameNode);
}

void SliderModelNG::ResetBlockBorderColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, BlockBorderColor, PROPERTY_UPDATE_RENDER, frameNode);
}

void SliderModelNG::ResetBlockBorderWidth(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, BlockBorderWidth, PROPERTY_UPDATE_RENDER, frameNode);
}

void SliderModelNG::ResetBlockColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, BlockColor, PROPERTY_UPDATE_RENDER, frameNode);
}

void SliderModelNG::ResetBlockImage(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        SliderPaintProperty, BlockImage, PROPERTY_UPDATE_RENDER, frameNode);
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        SliderPaintProperty, BlockImageBundleName, PROPERTY_UPDATE_RENDER, frameNode);
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        SliderPaintProperty, BlockImageModuleName, PROPERTY_UPDATE_RENDER, frameNode);
}

RefPtr<FrameNode> SliderModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SLIDER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SliderPattern>(); });
    return frameNode;
}

void SliderModelNG::SetOnChange(FrameNode* frameNode, SliderOnChangeEvent&& eventOnChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(eventOnChange));
}

void SliderModelNG::SetSliderValue(FrameNode* frameNode, float value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateValue(value);
}

void SliderModelNG::SetMinLabel(FrameNode* frameNode, float value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, Min, value, frameNode);
}
void SliderModelNG::SetMaxLabel(FrameNode* frameNode, float value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, Max, value, frameNode);
}

void SliderModelNG::SetSliderMode(FrameNode* frameNode, const SliderMode& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, SliderMode, value, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, SliderMode, value, frameNode);
}
void SliderModelNG::SetDirection(FrameNode* frameNode, Axis value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, Direction, value, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, Direction, value, frameNode);
}
void SliderModelNG::SetReverse(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, Reverse, value, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, Reverse, value, frameNode);
}
void SliderModelNG::SetStep(FrameNode* frameNode, float value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, Step, value, frameNode);
}

} // namespace OHOS::Ace::NG
