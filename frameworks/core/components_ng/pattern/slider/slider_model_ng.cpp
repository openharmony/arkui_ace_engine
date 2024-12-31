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
const float DEFAULT_STEP = 1.0f;
const float DEFAULT_MIN_VALUE = 0.0f;
const float DEFAULT_MAX_VALUE = 100.0f;
constexpr uint32_t BLOCK_COLOR = 0xffffffff;
constexpr uint32_t TRACK_COLOR = 0x19182431;
constexpr uint32_t SELECTED_COLOR = 0xff007dff;

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
    auto sliderEventHub = frameNode->GetEventHub<SliderEventHub>();
    CHECK_NULL_VOID(sliderEventHub);
    sliderEventHub->SetValue(value);
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
void SliderModelNG::SetTrackBackgroundColor(const Gradient& value, bool isResourceColor)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, TrackBackgroundColor, value);
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, TrackBackgroundIsResourceColor, isResourceColor);
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
void SliderModelNG::SetMinResponsiveDistance(float value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto minResponse = 0.0f;
    auto minValue = layoutProperty->GetMinValue(0.0f);
    auto maxValue = layoutProperty->GetMaxValue(100.0f);
    auto diff = maxValue - minValue;
    if (LessOrEqual(value, diff) && GreatNotEqual(value, minResponse)) {
        minResponse = value;
    }
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, MinResponsiveDistance, minResponse);
}

void SliderModelNG::SetValidSlideRange(float from, float to)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SliderModelNG::SetValidSlideRange(frameNode, from, to);
}

void SliderModelNG::SetShowSteps(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, ShowSteps, value);
}
void SliderModelNG::SetSliderInteractionMode(SliderInteraction mode)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, SliderInteractionMode, mode);
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
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SliderTheme>();
        CHECK_NULL_VOID(theme);
        auto sliderMode = layoutProperty->GetSliderModeValue(SliderModel::SliderMode::OUTSET);
        Dimension themeTrackThickness;
        if (sliderMode == SliderModel::SliderMode::OUTSET) {
            themeTrackThickness = theme->GetOutsetTrackThickness();
        } else if (sliderMode == SliderModel::SliderMode::INSET) {
            themeTrackThickness = theme->GetInsetTrackThickness();
        } else {
            themeTrackThickness = theme->GetNoneTrackThickness();
        }
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
void SliderModelNG::SetSelectedBorderRadius(const Dimension& value)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, SelectedBorderRadius, value);
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
#ifdef SUPPORT_DIGITAL_CROWN
void SliderModelNG::SetDigitalCrownSensitivity(CrownSensitivity sensitivity)
{
    ACE_UPDATE_PAINT_PROPERTY(SliderPaintProperty, DigitalCrownSensitivity, sensitivity);
}
#endif
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

void SliderModelNG::ResetSelectedBorderRadius()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, SelectedBorderRadius, PROPERTY_UPDATE_RENDER);
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

void SliderModelNG::ResetSliderInteractionMode()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, SliderInteractionMode, PROPERTY_UPDATE_RENDER);
}

void SliderModelNG::ResetMinResponsiveDistance()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, MinResponsiveDistance, PROPERTY_UPDATE_RENDER);
}

void SliderModelNG::ResetValidSlideRange()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, ValidSlideRange, PROPERTY_UPDATE_RENDER);
}

#ifdef SUPPORT_DIGITAL_CROWN
void SliderModelNG::ResetDigitalCrownSensitivity()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, DigitalCrownSensitivity, PROPERTY_UPDATE_RENDER);
}

void SliderModelNG::ResetDigitalCrownSensitivity(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        SliderPaintProperty, DigitalCrownSensitivity, PROPERTY_UPDATE_RENDER, frameNode);
}
#endif

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
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SliderTheme>();
        CHECK_NULL_VOID(theme);
        auto sliderMode = layoutProperty->GetSliderModeValue(SliderModel::SliderMode::OUTSET);
        Dimension themeTrackThickness;
        if (sliderMode == SliderModel::SliderMode::OUTSET) {
            themeTrackThickness = theme->GetOutsetTrackThickness();
        } else if (sliderMode == SliderModel::SliderMode::INSET) {
            themeTrackThickness = theme->GetInsetTrackThickness();
        } else {
            themeTrackThickness = theme->GetNoneTrackThickness();
        }
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
    auto pipeline = frameNode->GetContext();
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
void SliderModelNG::SetTrackBackgroundColor(FrameNode* frameNode, const Gradient& value, bool isResourceColor)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, TrackBackgroundColor, value, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, TrackBackgroundIsResourceColor, isResourceColor, frameNode);
}
void SliderModelNG::SetSelectColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, SelectColor, value, frameNode);
}
void SliderModelNG::SetShowSteps(FrameNode* frameNode, bool value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, ShowSteps, value, frameNode);
}
void SliderModelNG::SetSliderInteractionMode(FrameNode* frameNode, SliderInteraction mode)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, SliderInteractionMode, mode, frameNode);
}
void SliderModelNG::SetMinResponsiveDistance(FrameNode* frameNode, float value)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto minResponse = 0.0f;
    auto minValue = layoutProperty->GetMinValue(0.0f);
    auto maxValue = layoutProperty->GetMaxValue(100.0f);
    auto diff = maxValue - minValue;
    if (LessOrEqual(value, diff) && GreatOrEqual(value, minResponse)) {
        minResponse = value;
    }
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, MinResponsiveDistance, minResponse, frameNode);
}

#ifdef SUPPORT_DIGITAL_CROWN
void SliderModelNG::SetDigitalCrownSensitivity(FrameNode* frameNode, CrownSensitivity sensitivity)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, DigitalCrownSensitivity, sensitivity, frameNode);
}
#endif

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

void SliderModelNG::ResetValidSlideRange(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, ValidSlideRange, PROPERTY_UPDATE_RENDER, frameNode);
}

RefPtr<FrameNode> SliderModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SLIDER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SliderPattern>(); });

    SetMinLabel(AceType::RawPtr(frameNode), DEFAULT_MIN_VALUE);
    SetMaxLabel(AceType::RawPtr(frameNode), DEFAULT_MAX_VALUE);
    SetStep(AceType::RawPtr(frameNode), DEFAULT_STEP);
    SetSliderValue(AceType::RawPtr(frameNode), DEFAULT_MIN_VALUE);

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

void SliderModelNG::SetValidSlideRange(FrameNode* frameNode, float from, float to)
{
    if (std::isnan(from) || std::isnan(to)) {
        return SliderModelNG::ResetValidSlideRange(frameNode);
    }
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto minValue = paintProperty->GetMinValue(0.0f);
    auto maxValue = paintProperty->GetMaxValue(100.0f);
    auto step = paintProperty->GetStepValue(1.0f);
    float fromValue = minValue;
    float toValue = maxValue;
    if (std::isfinite(from)) {
        fromValue = from;
    }
    if (std::isfinite(to)) {
        toValue = to;
    }
    if (GreatOrEqual(fromValue, minValue) && LessOrEqual(toValue, maxValue) && LessOrEqual(fromValue, toValue) &&
        GreatNotEqual(step, 0.0f)) {
        auto toValueCorrection = NearEqual(toValue - step * std::floor(toValue / step), 0) ? 0 : 1;
        fromValue = LessOrEqual(fromValue, minValue) ? minValue : std::floor(fromValue / step) * step;
        toValue = GreatOrEqual(toValue, maxValue) ?
                  maxValue : (std::floor(toValue / step) + toValueCorrection) * step;
        auto sliderValue = std::clamp(paintProperty->GetValueValue(fromValue), fromValue, toValue);
        RefPtr<SliderModel::SliderValidRange> rangeValue =
            AceType::MakeRefPtr<SliderModel::SliderValidRange>(fromValue, toValue);
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, Value, sliderValue, frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, ValidSlideRange, rangeValue, frameNode);
    } else {
        SliderModelNG::ResetValidSlideRange(frameNode);
    }
}

Color SliderModelNG::GetBlockColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, BlockColor, value, frameNode, Color(BLOCK_COLOR));
    return value;
}

Gradient SliderModelNG::GetTrackBackgroundColor(FrameNode* frameNode)
{
    Gradient value;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, TrackBackgroundColor, value, frameNode,
        SliderModelNG::CreateSolidGradient(Color(TRACK_COLOR)));
    return value;
}

Color SliderModelNG::GetSelectColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, SelectColor, value, frameNode, Color(SELECTED_COLOR));
    return value;
}

bool SliderModelNG::GetShowSteps(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, ShowSteps, value, frameNode, false);
    return value;
}

SliderModel::BlockStyleType SliderModelNG::GetBlockType(FrameNode* frameNode)
{
    SliderModel::BlockStyleType value = SliderModel::BlockStyleType::DEFAULT;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, BlockType, value, frameNode, SliderModel::BlockStyleType::DEFAULT);
    return value;
}

float SliderModelNG::GetSliderValue(FrameNode* frameNode)
{
    float value = DEFAULT_MIN_VALUE;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, Value, value, frameNode, DEFAULT_MIN_VALUE);
    return value;
}

float SliderModelNG::GetMinLabel(FrameNode* frameNode)
{
    float value = DEFAULT_MIN_VALUE;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, Min, value, frameNode, DEFAULT_MIN_VALUE);
    return value;
}
float SliderModelNG::GetMaxLabel(FrameNode* frameNode)
{
    float value = DEFAULT_MAX_VALUE;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, Max, value, frameNode, DEFAULT_MAX_VALUE);
    return value;
}

SliderModel::SliderMode SliderModelNG::GetSliderMode(FrameNode* frameNode)
{
    SliderModel::SliderMode value = SliderModel::SliderMode::OUTSET;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, SliderMode, value, frameNode, SliderModel::SliderMode::OUTSET);
    return value;
}
OHOS::Ace::Axis SliderModelNG::GetDirection(FrameNode* frameNode)
{
    OHOS::Ace::Axis value = OHOS::Ace::Axis::HORIZONTAL;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, Direction, value, frameNode, OHOS::Ace::Axis::HORIZONTAL);
    return value;
}
bool SliderModelNG::GetReverse(FrameNode* frameNode)
{
    bool value = false;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, Reverse, value, frameNode, false);
    return value;
}
float SliderModelNG::GetStep(FrameNode* frameNode)
{
    float value = DEFAULT_STEP;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, Step, value, frameNode, DEFAULT_STEP);
    return value;
}

std::string SliderModelNG::GetBlockImageValue(FrameNode* frameNode)
{
    std::string value = "";
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, BlockImage, value, frameNode, value);
    return value;
}

RefPtr<BasicShape> SliderModelNG::GetBlockShape(FrameNode* frameNode)
{
    RefPtr<BasicShape> value = AceType::MakeRefPtr<BasicShape>();
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(SliderPaintProperty, BlockShape, value, frameNode, value);
    return value;
}

RefPtr<SliderModel::SliderValidRange> SliderModelNG::GetValidSlideRange(FrameNode* frameNode)
{
    RefPtr<SliderModel::SliderValidRange> value = AceType::MakeRefPtr<SliderModel::SliderValidRange>();
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(SliderPaintProperty, ValidSlideRange, value, frameNode, value);
    return value;
}

#ifdef SUPPORT_DIGITAL_CROWN
CrownSensitivity SliderModelNG::GetDigitalCrownSensitivity(FrameNode* frameNode)
{
    CrownSensitivity sensitivity = CrownSensitivity::MEDIUM;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderPaintProperty, DigitalCrownSensitivity, sensitivity, frameNode, sensitivity);
    return sensitivity;
}
#endif

Gradient SliderModelNG::CreateSolidGradient(Color value)
{
    Gradient gradient;
    GradientColor gradientColorBegin;
    gradientColorBegin.SetLinearColor(LinearColor(value));
    gradientColorBegin.SetDimension(Dimension(0.0f));
    gradient.AddColor(gradientColorBegin);
    OHOS::Ace::NG::GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor(value));
    gradientColorEnd.SetDimension(Dimension(1.0f));
    gradient.AddColor(gradientColorEnd);
    return gradient;
}

void SliderModelNG::SetBuilderFunc(FrameNode* frameNode, SliderMakeCallback&& makeFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetBuilderFunc(std::move(makeFunc));
}

void SliderModelNG::SetChangeValue(FrameNode* frameNode, double value, int32_t mode)
{
    auto pattern = frameNode->GetPattern<SliderPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSliderValue(value, mode);
}

Dimension SliderModelNG::GetThickness(FrameNode* frameNode)
{
    Dimension defaultTrackThickness = Dimension(0.0f);
    CHECK_NULL_RETURN(frameNode, defaultTrackThickness);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, defaultTrackThickness);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, defaultTrackThickness);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_RETURN(theme, defaultTrackThickness);
    auto sliderMode = layoutProperty->GetSliderModeValue(SliderModel::SliderMode::OUTSET);
    if (sliderMode == SliderModel::SliderMode::OUTSET) {
        defaultTrackThickness = theme->GetOutsetTrackThickness();
    } else if (sliderMode == SliderModel::SliderMode::INSET) {
        defaultTrackThickness = theme->GetInsetTrackThickness();
    } else {
        defaultTrackThickness = theme->GetNoneTrackThickness();
    }

    Dimension trackThickness = Dimension(0.0f);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        SliderLayoutProperty, Thickness, trackThickness, frameNode, defaultTrackThickness);
    return trackThickness;
}

void SliderModelNG::SetSelectedBorderRadius(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, SelectedBorderRadius, value, frameNode);
}

void SliderModelNG::ResetSelectedBorderRadius(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        SliderPaintProperty, SelectedBorderRadius, PROPERTY_UPDATE_RENDER, frameNode);
}

void SliderModelNG::ResetSliderInteractionMode(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        SliderPaintProperty, SliderInteractionMode, PROPERTY_UPDATE_RENDER, frameNode);
}

void SliderModelNG::ResetMinResponsiveDistance(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        SliderPaintProperty, MinResponsiveDistance, PROPERTY_UPDATE_RENDER, frameNode);
}
} // namespace OHOS::Ace::NG
