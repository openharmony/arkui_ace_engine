/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/slider/slider_model_static.h"

#include "core/components/slider/slider_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void SliderModelStatic::SetThickness(FrameNode* frameNode, const std::optional<Dimension>& thickness)
{
    CHECK_NULL_VOID(frameNode);
    auto value = Dimension();
    if (thickness.has_value()) {
        value = thickness.value();
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, Thickness, frameNode);
    }

    if (value.IsNonPositive()) {
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
void SliderModelStatic::SetStepSize(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, StepSize, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, StepSize, frameNode);
    }
}

void SliderModelStatic::SetBlockType(FrameNode* frameNode, const std::optional<SliderModel::BlockStyleType>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockType, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockType, frameNode);
    }
}

void SliderModelStatic::SetBlockSize(FrameNode* frameNode,
    const std::optional<Dimension>& widthParam, const std::optional<Dimension>& heightParam)
{
    CHECK_NULL_VOID(frameNode);
    if (!widthParam.has_value() || !heightParam.has_value()) {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(SliderLayoutProperty, BlockSize, PROPERTY_UPDATE_MEASURE, frameNode);
        return;
    }
    Dimension width = widthParam.value();
    Dimension height = heightParam.value();

    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    SizeT<Dimension> blockSize;
    auto theme = pipeline->GetTheme<SliderTheme>();
    if (theme != nullptr) {
        auto mode = layoutProperty->GetSliderModeValue(SliderModel::SliderMode::OUTSET);
        auto themeBlockSize =
            mode == SliderModel::SliderMode::OUTSET ? theme->GetOutsetBlockSize() : theme->GetInsetBlockSize();
        blockSize = layoutProperty->GetBlockSizeValue(SizeT<Dimension>(themeBlockSize, themeBlockSize));
    }

    if (LessOrEqual(width.Value(), 0.0) || LessOrEqual(height.Value(), 0.0)) {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(SliderLayoutProperty, BlockSize, PROPERTY_UPDATE_MEASURE, frameNode);
    } else {
        blockSize.SetWidth(width);
        blockSize.SetHeight(height);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, BlockSize, blockSize, frameNode);
    }
}

void SliderModelStatic::SetTrackBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, TrackBorderRadius, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            SliderPaintProperty, TrackBorderRadius, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void SliderModelStatic::SetStepColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, StepColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(SliderPaintProperty, StepColor, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void SliderModelStatic::SetBlockBorderColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockBorderColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            SliderPaintProperty, BlockBorderColor, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void SliderModelStatic::SetBlockBorderWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockBorderWidth, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockBorderWidth, frameNode);
    }
}

void SliderModelStatic::SetBlockColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, BlockColor, frameNode);
    }
}

void SliderModelStatic::SetTrackBackgroundColor(FrameNode* frameNode,
    const std::optional<Gradient>& value, bool isResourceColor)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, TrackBackgroundColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, TrackBackgroundColor, frameNode);
    }
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, TrackBackgroundIsResourceColor, isResourceColor, frameNode);
}

void SliderModelStatic::SetSelectColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, SelectColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, SelectColor, frameNode);
    }
}

void SliderModelStatic::SetSelectColor(FrameNode* frameNode,
    const std::optional<Gradient>& value, bool isResourceColor)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, SelectGradientColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, SelectGradientColor, frameNode);
    }
    ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, SelectIsResourceColor, isResourceColor, frameNode);
}

void SliderModelStatic::SetSliderInteractionMode(
    FrameNode* frameNode, const std::optional<SliderModel::SliderInteraction>& mode)
{
    CHECK_NULL_VOID(frameNode);
    if (mode.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, SliderInteractionMode, mode.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            SliderPaintProperty, SliderInteractionMode, PROPERTY_UPDATE_RENDER, frameNode);
    }
}
void SliderModelStatic::SetMinResponsiveDistance(FrameNode* frameNode, const std::optional<float>& distance)
{
    CHECK_NULL_VOID(frameNode);
    
    float value = 0.0f;
    if (distance.has_value()) {
        value = distance.value();
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
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, MinResponsiveDistance, frameNode);
    }
}

#ifdef SUPPORT_DIGITAL_CROWN
void SliderModelStatic::SetDigitalCrownSensitivity(
    FrameNode* frameNode, const std::optional<CrownSensitivity>& valueOpt)
{
    CHECK_NULL_VOID(frameNode);
    if (valueOpt) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, DigitalCrownSensitivity, valueOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            SliderPaintProperty, DigitalCrownSensitivity, PROPERTY_UPDATE_RENDER, frameNode);
    }
}
#endif

void SliderModelStatic::SetSliderValue(FrameNode* frameNode, const std::optional<float>& value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    CHECK_NULL_VOID(pattern);
    if (value.has_value()) {
        pattern->UpdateValue(value.value());
    } else {
        pattern->UpdateValue(0.0f);
    }
}

void SliderModelStatic::SetMinLabel(FrameNode* frameNode, const std::optional<float>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, Min, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, Min, frameNode);
    }
}

void SliderModelStatic::SetMaxLabel(FrameNode* frameNode, const std::optional<float>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, Max, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, Max, frameNode);
    }
}

void SliderModelStatic::SetSliderMode(FrameNode* frameNode, const std::optional<SliderModel::SliderMode>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, SliderMode, value.value(), frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, SliderMode, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, SliderMode, frameNode);
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, SliderMode, frameNode);
    }
}

void SliderModelStatic::SetDirection(FrameNode* frameNode, const std::optional<Axis>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, Direction, value.value(), frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, Direction, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, Direction, frameNode);
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, Direction, frameNode);
    }
}

void SliderModelStatic::SetReverse(FrameNode* frameNode, const std::optional<bool>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, Reverse, value.value(), frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, Reverse, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SliderLayoutProperty, Reverse, frameNode);
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, Reverse, frameNode);
    }
}

void SliderModelStatic::SetStep(FrameNode* frameNode, const std::optional<float>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, Step, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(SliderPaintProperty, Step, frameNode);
    }
}

void SliderModelStatic::SetValidSlideRange(FrameNode* frameNode,
    const std::optional<float>& fromParam, const std::optional<float>& toParam)
{
    CHECK_NULL_VOID(frameNode);
    if (!fromParam.has_value() || !toParam.has_value()) {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            SliderPaintProperty, ValidSlideRange, PROPERTY_UPDATE_RENDER, frameNode);
        return;
    }

    float from = fromParam.value();
    float to = toParam.value();
    if (std::isnan(from) || std::isnan(to)) {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            SliderPaintProperty, ValidSlideRange, PROPERTY_UPDATE_RENDER, frameNode);
        return;
    }

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
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            SliderPaintProperty, ValidSlideRange, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void SliderModelStatic::SetSelectedBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SliderPaintProperty, SelectedBorderRadius, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
            SliderPaintProperty, SelectedBorderRadius, PROPERTY_UPDATE_RENDER, frameNode);
    }
}

void SliderModelStatic::SetOnChangeEvent(FrameNode* frameNode, SliderOnValueChangeEvent&& onChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}
} // namespace OHOS::Ace::NG
