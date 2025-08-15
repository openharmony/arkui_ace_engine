/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/slider/slider_tip_modifier.h"

#include "base/geometry/ng/offset_t.h"
#include "base/i18n/localization.h"
#include "bridge/common/utils/utils.h"
#include "core/common/font_manager.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/slider/slider_theme.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension CIRCULAR_HORIZON_OFFSET = 13.86_vp;
constexpr Dimension ARROW_HORIZON_OFFSET = 1.5_vp;
constexpr Dimension ARROW_VERTICAL_OFFSET = 0.68_vp;
constexpr Dimension ARROW_RADIUS = 2.0_vp;
constexpr Dimension ARROW_HEIGHT = 8.0_vp;
constexpr Dimension ARROW_WIDTH = 16.0_vp;
constexpr float HALF = 0.5f;

constexpr float BUBBLE_SIZE_MIN_SCALE = 0.6f;
constexpr float BUBBLE_SIZE_MAX_SCALE = 1.0f;
constexpr float BUBBLE_OPACITY_MIN_SCALE = 0.0f;
constexpr float BUBBLE_OPACITY_MAX_SCALE = 1.0f;
constexpr int32_t BUBBLE_DISPLAY_SIZE_CHANGE_TIMER = 250;
constexpr int32_t BUBBLE_DISPLAY_OPACITY_CHANGE_TIMER = 150;
constexpr int32_t BUBBLE_DISAPPEAR_SIZE_CHANGE_TIMER = 250;
constexpr int32_t BUBBLE_DISAPPEAR_OPACITY_CHANGE_TIMER = 250;
constexpr Dimension BUBBLE_VERTICAL_WIDTH = 62.0_vp;
constexpr Dimension BUBBLE_VERTICAL_HEIGHT = 32.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_WIDTH = 48.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_HEIGHT = 40.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_WIDTH = 92.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_HEIGHT = 52.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH = 48.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT = 60.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_WIDTH = 96.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_HEIGHT = 56.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH = 48.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT = 64.0_vp;
constexpr Dimension TEXT_MAX = 36.0_vp;
constexpr Dimension TEXT_AGING_MAX = 72.0_vp;
constexpr int32_t MAX_LENGTH = 1;
constexpr float SUITABLEAGING_LEVEL_1_SCALE = 1.75f;
constexpr float SUITABLEAGING_LEVEL_2_SCALE = 2.0f;
constexpr Dimension SUITABLEAGING_LEVEL_1_TEXT_FONT_SIZE = 25.0_vp;
constexpr Dimension SUITABLEAGING_LEVEL_2_TEXT_FONT_SIZE = 28.0_vp;

} // namespace

SliderTipModifier::SliderTipModifier(std::function<std::pair<OffsetF, float>()> getBubbleVertexFunc,
    std::function<void()> onFinishEventTipSize)
    : tipFlag_(AceType::MakeRefPtr<PropertyBool>(false)),
      contentOffset_(AceType::MakeRefPtr<PropertyOffsetF>(OffsetF())),
      contentSize_(AceType::MakeRefPtr<PropertySizeF>(SizeF())),
      sizeScale_(AceType::MakeRefPtr<AnimatablePropertyFloat>(BUBBLE_SIZE_MIN_SCALE)),
      opacityScale_(AceType::MakeRefPtr<AnimatablePropertyFloat>(BUBBLE_OPACITY_MIN_SCALE)),
      content_(AceType::MakeRefPtr<PropertyString>("")), bubbleVertex_(AceType::MakeRefPtr<PropertyOffsetF>(OffsetF())),
      sliderGlobalOffset_(AceType::MakeRefPtr<PropertyOffsetF>(OffsetF())),
      getBubbleVertexFunc_(std::move(getBubbleVertexFunc)),
      onFinishEventTipSize_(std::move(onFinishEventTipSize))
{
    AttachProperty(tipFlag_);
    AttachProperty(contentOffset_);
    AttachProperty(sizeScale_);
    AttachProperty(opacityScale_);
    AttachProperty(content_);
    AttachProperty(bubbleVertex_);
    AttachProperty(sliderGlobalOffset_);
}

SliderTipModifier::~SliderTipModifier() {}

void SliderTipModifier::UpdateThemeParams(const RefPtr<SliderTheme>& theme)
{
    tipDelayTime_ = theme->GetTipDelayTime();
}

void SliderTipModifier::PaintTip(DrawingContext& context)
{
    PaintBubble(context);
    CHECK_NULL_VOID(paragraph_);
    PaintText(context);
    context.canvas.Restore();
}

void SliderTipModifier::PaintText(DrawingContext& context)
{
    auto arrowSizeWidth = static_cast<float>(ARROW_WIDTH.ConvertToPx());
    auto arrowSizeHeight = static_cast<float>(ARROW_HEIGHT.ConvertToPx());
    auto circularOffset = static_cast<float>(CIRCULAR_HORIZON_OFFSET.ConvertToPx());
    auto pipeLine = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeLine);
    auto fontScale = pipeLine->GetFontScale();
    SizeF textSize = { 0, 0 };
    if (paragraph_) {
        auto width = static_cast<float>(TEXT_MAX.ConvertToPx());
        if (GreatOrEqual(fontScale, SUITABLEAGING_LEVEL_1_SCALE) ||
            (GreatOrEqual(fontScale, SUITABLEAGING_LEVEL_2_SCALE))) {
            width = static_cast<float>(TEXT_AGING_MAX.ConvertToPx());
        }
        textSize = SizeF(std::min(paragraph_->GetLongestLine(), width), paragraph_->GetHeight());
    }
    if (axis_ == Axis::HORIZONTAL) {
        textOffset_.SetX(vertex_.GetX() - textSize.Width() * HALF);
        if (isMask_) {
            textOffset_.SetY(vertex_.GetY() + (bubbleSize_.Height() - textSize.Height() + arrowSizeHeight) * HALF);
        } else {
            textOffset_.SetY(vertex_.GetY() - (bubbleSize_.Height() + textSize.Height() + arrowSizeHeight) * HALF);
        }
    } else {
        textOffset_.SetY(vertex_.GetY() - textSize.Height() * HALF);
        if (isMask_) {
            textOffset_.SetX(
                vertex_.GetX() +
                (bubbleSize_.Width() - textSize.Width() + arrowSizeHeight + circularOffset - arrowSizeWidth) * HALF);
        } else {
            textOffset_.SetX(
                vertex_.GetX() -
                (bubbleSize_.Width() + textSize.Width() + arrowSizeHeight + circularOffset - arrowSizeWidth) * HALF);
        }
    }
    paragraph_->Paint(context.canvas, textOffset_.GetX(), textOffset_.GetY());
}

void SliderTipModifier::PaintHorizontalBubble(float vertexOffsetFromBlock, RSPath& path)
{
    float arrowRadius = static_cast<float>(ARROW_RADIUS.ConvertToPx());
    auto arrowSizeWidth = static_cast<float>(ARROW_WIDTH.ConvertToPx());
    auto arrowSizeHeight = static_cast<float>(ARROW_HEIGHT.ConvertToPx());
    auto arrowHorizonOffset = static_cast<float>(ARROW_HORIZON_OFFSET.ConvertToPx());
    auto arrowVerticalOffset = static_cast<float>(ARROW_VERTICAL_OFFSET.ConvertToPx());
    float circularRadius = (bubbleSize_.Height() - arrowSizeHeight) * HALF;
    if (sliderGlobalOffset_->Get().GetY() + vertex_.GetY() < bubbleSize_.Height()) {
        vertex_.AddY(vertexOffsetFromBlock / HALF);
        isMask_ = true;
        path.MoveTo(vertex_.GetX(), vertex_.GetY());
        path.ArcTo(arrowRadius, arrowRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX() + arrowHorizonOffset,
            vertex_.GetY() + arrowVerticalOffset);
        path.LineTo(vertex_.GetX() + arrowSizeWidth * HALF, vertex_.GetY() + arrowSizeHeight);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() + arrowSizeWidth * HALF, vertex_.GetY() + bubbleSize_.Height());
        path.LineTo(vertex_.GetX() - arrowSizeWidth * HALF, vertex_.GetY() + bubbleSize_.Height());
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() - arrowSizeWidth * HALF, vertex_.GetY() + arrowSizeHeight);
        path.LineTo(vertex_.GetX() - arrowHorizonOffset * HALF, vertex_.GetY() + arrowVerticalOffset);
    } else {
        isMask_ = false;
        path.MoveTo(vertex_.GetX(), vertex_.GetY());
        path.ArcTo(arrowRadius, arrowRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX() - arrowHorizonOffset,
            vertex_.GetY() - arrowVerticalOffset);
        path.LineTo(vertex_.GetX() - arrowSizeWidth * HALF, vertex_.GetY() - arrowSizeHeight);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() - arrowSizeWidth * HALF, vertex_.GetY() - bubbleSize_.Height());
        path.LineTo(vertex_.GetX() + arrowSizeWidth * HALF, vertex_.GetY() - bubbleSize_.Height());
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() + arrowSizeWidth * HALF, vertex_.GetY() - arrowSizeHeight);
        path.LineTo(vertex_.GetX() + arrowHorizonOffset * HALF, vertex_.GetY() - arrowVerticalOffset);
    }
    path.ArcTo(arrowRadius, arrowRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX(), vertex_.GetY());
}

void SliderTipModifier::PaintVerticalBubble(float vertexOffsetFromBlock, RSPath& path)
{
    auto arrowWidth = static_cast<float>(ARROW_WIDTH.ConvertToPx());
    auto arrowHeight = static_cast<float>(ARROW_HEIGHT.ConvertToPx());
    auto circularOffset = static_cast<float>(CIRCULAR_HORIZON_OFFSET.ConvertToPx());
    auto arrowHorizonOffset = static_cast<float>(ARROW_HORIZON_OFFSET.ConvertToPx());
    auto arrowVerticalOffset = static_cast<float>(ARROW_VERTICAL_OFFSET.ConvertToPx());
    float arrowRadius = static_cast<float>(ARROW_RADIUS.ConvertToPx());
    float circularRadius = bubbleSize_.Height() * HALF;
    if (sliderGlobalOffset_->Get().GetX() + vertex_.GetX() < bubbleSize_.Width() ||
        AceApplicationInfo::GetInstance().IsRightToLeft()) {
        vertex_.AddX(vertexOffsetFromBlock / HALF);
        isMask_ = true;
        path.MoveTo(vertex_.GetX(), vertex_.GetY());
        path.ArcTo(arrowRadius, arrowRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX() + arrowVerticalOffset,
            vertex_.GetY() - arrowHorizonOffset);
        path.LineTo(vertex_.GetX() + arrowHeight, vertex_.GetY() - arrowWidth * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() + arrowHeight + circularOffset, vertex_.GetY() - bubbleSize_.Height() * HALF);
        path.LineTo(vertex_.GetX() + bubbleSize_.Width() - bubbleSize_.Height() * HALF,
            vertex_.GetY() - bubbleSize_.Height() * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() + bubbleSize_.Width() - bubbleSize_.Height() * HALF,
            vertex_.GetY() + bubbleSize_.Height() * HALF);
        path.LineTo(vertex_.GetX() + arrowHeight + circularOffset, vertex_.GetY() + bubbleSize_.Height() * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX() + arrowHeight,
            vertex_.GetY() + arrowWidth * HALF);
        path.LineTo(vertex_.GetX() + arrowVerticalOffset, vertex_.GetY() + arrowHorizonOffset);
    } else {
        isMask_ = false;
        path.MoveTo(vertex_.GetX(), vertex_.GetY());
        path.ArcTo(arrowRadius, arrowRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX() - arrowVerticalOffset,
            vertex_.GetY() + arrowHorizonOffset);
        path.LineTo(vertex_.GetX() - arrowHeight, vertex_.GetY() + arrowWidth * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() - arrowHeight - circularOffset, vertex_.GetY() + bubbleSize_.Height() * HALF);
        path.LineTo(vertex_.GetX() - bubbleSize_.Width() + bubbleSize_.Height() * HALF,
            vertex_.GetY() + bubbleSize_.Height() * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() - bubbleSize_.Width() + bubbleSize_.Height() * HALF,
            vertex_.GetY() - bubbleSize_.Height() * HALF);
        path.LineTo(vertex_.GetX() - arrowHeight - circularOffset, vertex_.GetY() - bubbleSize_.Height() * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX() - arrowHeight,
            vertex_.GetY() - arrowWidth * HALF);
        path.LineTo(vertex_.GetX() - arrowVerticalOffset, vertex_.GetY() - arrowHorizonOffset);
    }
    path.ArcTo(arrowRadius, arrowRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX(), vertex_.GetY());
}

void SliderTipModifier::PaintHorizontalBubbleSuitableAging(float vertexOffsetFromBlock, RSPath& path)
{
    float arrowRadius = static_cast<float>(ARROW_RADIUS.ConvertToPx());
    auto arrowSizeWidth = static_cast<float>(ARROW_WIDTH.ConvertToPx());
    auto arrowSizeHeight = static_cast<float>(ARROW_HEIGHT.ConvertToPx());
    auto arrowHorizonOffset = static_cast<float>(ARROW_HORIZON_OFFSET.ConvertToPx());
    auto arrowVerticalOffset = static_cast<float>(ARROW_VERTICAL_OFFSET.ConvertToPx());
    float circularRadius = (bubbleSize_.Height() - arrowSizeHeight) * (1.0f / 3.0f);
    if (sliderGlobalOffset_->Get().GetY() + vertex_.GetY() < bubbleSize_.Height()) {
        vertex_.AddY(vertexOffsetFromBlock / HALF);
        isMask_ = true;
        path.MoveTo(vertex_.GetX(), vertex_.GetY());
        path.ArcTo(arrowRadius, arrowRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX() + arrowHorizonOffset,
            vertex_.GetY() + arrowVerticalOffset);
        path.LineTo(vertex_.GetX() + arrowSizeWidth * HALF, vertex_.GetY() + arrowSizeHeight);
        path.LineTo(vertex_.GetX() + bubbleSize_.Width() * HALF, vertex_.GetY() + arrowSizeHeight);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() + bubbleSize_.Width() * HALF + circularRadius,
            vertex_.GetY() + arrowSizeHeight + (bubbleSize_.Height() - arrowSizeHeight) * (1.0f / 3.0f));
        path.LineTo(vertex_.GetX() + bubbleSize_.Width() * HALF + circularRadius,
            vertex_.GetY() + arrowSizeHeight + (bubbleSize_.Height() - arrowSizeHeight) * (2.0f / 3.0f));
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() + bubbleSize_.Width() * HALF, vertex_.GetY() + bubbleSize_.Height());
        path.LineTo(vertex_.GetX() - bubbleSize_.Width() * HALF, vertex_.GetY() + bubbleSize_.Height());
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() - bubbleSize_.Width() * HALF - circularRadius,
            vertex_.GetY() + arrowSizeHeight + (bubbleSize_.Height() - arrowSizeHeight) * (2.0f / 3.0f));
        path.LineTo(vertex_.GetX() - bubbleSize_.Width() * HALF - circularRadius,
            vertex_.GetY() + arrowSizeHeight + (bubbleSize_.Height() - arrowSizeHeight) * (1.0f / 3.0f));
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() - bubbleSize_.Width() * HALF, vertex_.GetY() + arrowSizeHeight);
        path.LineTo(vertex_.GetX() - arrowSizeWidth * HALF, vertex_.GetY() + arrowSizeHeight);
        path.LineTo(vertex_.GetX() - arrowHorizonOffset * HALF, vertex_.GetY() + arrowVerticalOffset);
    } else {
        isMask_ = false;
        path.MoveTo(vertex_.GetX(), vertex_.GetY());
        path.ArcTo(arrowRadius, arrowRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX() - arrowHorizonOffset,
            vertex_.GetY() - arrowVerticalOffset);
        path.LineTo(vertex_.GetX() - arrowSizeWidth * HALF, vertex_.GetY() - arrowSizeHeight);
        path.LineTo(vertex_.GetX() - bubbleSize_.Width() * HALF, vertex_.GetY() - arrowSizeHeight);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() - bubbleSize_.Width() * HALF - circularRadius,
            vertex_.GetY() - arrowSizeHeight - (bubbleSize_.Height() - arrowSizeHeight) * (1.0f / 3.0f));
        path.LineTo(vertex_.GetX() - bubbleSize_.Width() * HALF - circularRadius,
            vertex_.GetY() - arrowSizeHeight - (bubbleSize_.Height() - arrowSizeHeight) * (2.0f / 3.0f));
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() - bubbleSize_.Width() * HALF, vertex_.GetY() - bubbleSize_.Height());
        path.LineTo(vertex_.GetX() + bubbleSize_.Width() * HALF, vertex_.GetY() - bubbleSize_.Height());
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() + bubbleSize_.Width() * HALF + circularRadius,
            vertex_.GetY() - arrowSizeHeight - (bubbleSize_.Height() - arrowSizeHeight) * (2.0f / 3.0f));
        path.LineTo(vertex_.GetX() + bubbleSize_.Width() * HALF + circularRadius,
            vertex_.GetY() - arrowSizeHeight - (bubbleSize_.Height() - arrowSizeHeight) * (1.0f / 3.0f));
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() + bubbleSize_.Width() * HALF, vertex_.GetY() - arrowSizeHeight);
        path.LineTo(vertex_.GetX() + arrowSizeWidth * HALF, vertex_.GetY() - arrowSizeHeight);
        path.LineTo(vertex_.GetX() + arrowHorizonOffset * HALF, vertex_.GetY() - arrowVerticalOffset);
    }
    path.ArcTo(arrowRadius, arrowRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX(), vertex_.GetY());
}

void SliderTipModifier::PaintVerticalBubbleSuitableAging(float vertexOffsetFromBlock, RSPath& path)
{
    auto arrowWidth = static_cast<float>(ARROW_WIDTH.ConvertToPx());
    auto arrowHeight = static_cast<float>(ARROW_HEIGHT.ConvertToPx());
    auto arrowHorizonOffset = static_cast<float>(ARROW_HORIZON_OFFSET.ConvertToPx());
    auto arrowVerticalOffset = static_cast<float>(ARROW_VERTICAL_OFFSET.ConvertToPx());
    float arrowRadius = static_cast<float>(ARROW_RADIUS.ConvertToPx());
    float circularRadius = bubbleSize_.Height() * (1.0f / 3.0f);
    if (sliderGlobalOffset_->Get().GetX() + vertex_.GetX() < bubbleSize_.Width() ||
        AceApplicationInfo::GetInstance().IsRightToLeft()) {
        vertex_.AddX(vertexOffsetFromBlock / HALF);
        isMask_ = true;
        path.MoveTo(vertex_.GetX(), vertex_.GetY());
        path.ArcTo(arrowRadius, arrowRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX() + arrowVerticalOffset,
            vertex_.GetY() - arrowHorizonOffset);
        path.LineTo(vertex_.GetX() + arrowHeight, vertex_.GetY() - arrowWidth * HALF);
        path.LineTo(vertex_.GetX() + arrowHeight, vertex_.GetY() - bubbleSize_.Height() * (1.0f / 3.0f) * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() + arrowHeight + circularRadius, vertex_.GetY() - bubbleSize_.Height() * HALF);
        path.LineTo(
            vertex_.GetX() + bubbleSize_.Width() - circularRadius, vertex_.GetY() - bubbleSize_.Height() * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() + bubbleSize_.Width(), vertex_.GetY() - bubbleSize_.Height() * (1.0f / 3.0f) * HALF);
        path.LineTo(vertex_.GetX() + bubbleSize_.Width(), vertex_.GetY() + bubbleSize_.Height() * (1.0f / 3.0f) * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() + bubbleSize_.Width() - circularRadius, vertex_.GetY() + bubbleSize_.Height() * HALF);
        path.LineTo(vertex_.GetX() + arrowHeight + circularRadius, vertex_.GetY() + bubbleSize_.Height() * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX() + arrowHeight,
            vertex_.GetY() + bubbleSize_.Height() * (1.0f / 3.0f) * HALF);
        path.LineTo(vertex_.GetX() + arrowHeight, vertex_.GetY() + arrowWidth * HALF);
        path.LineTo(vertex_.GetX() + arrowVerticalOffset, vertex_.GetY() + arrowHorizonOffset);
    } else {
        isMask_ = false;
        path.MoveTo(vertex_.GetX(), vertex_.GetY());
        path.ArcTo(arrowRadius, arrowRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX() - arrowVerticalOffset,
            vertex_.GetY() + arrowHorizonOffset);
        path.LineTo(vertex_.GetX() - arrowHeight, vertex_.GetY() + arrowWidth * HALF);
        path.LineTo(vertex_.GetX() - arrowHeight, vertex_.GetY() + bubbleSize_.Height() * (1.0f / 3.0f) * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() - arrowHeight - circularRadius, vertex_.GetY() + bubbleSize_.Height() * HALF);
        path.LineTo(
            vertex_.GetX() - bubbleSize_.Width() + circularRadius, vertex_.GetY() + bubbleSize_.Height() * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() - bubbleSize_.Width(), vertex_.GetY() + bubbleSize_.Height() * (1.0f / 3.0f) * HALF);
        path.LineTo(vertex_.GetX() - bubbleSize_.Width(), vertex_.GetY() - bubbleSize_.Height() * (1.0f / 3.0f) * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION,
            vertex_.GetX() - bubbleSize_.Width() + circularRadius, vertex_.GetY() - bubbleSize_.Height() * HALF);
        path.LineTo(vertex_.GetX() - arrowHeight - circularRadius, vertex_.GetY() - bubbleSize_.Height() * HALF);
        path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX() - arrowHeight,
            vertex_.GetY() - bubbleSize_.Height() * (1.0f / 3.0f) * HALF);
        path.LineTo(vertex_.GetX() - arrowHeight, vertex_.GetY() - arrowWidth * HALF);
        path.LineTo(vertex_.GetX() - arrowVerticalOffset, vertex_.GetY() - arrowHorizonOffset);
    }
    path.ArcTo(arrowRadius, arrowRadius, 0.0f, RSPathDirection::CW_DIRECTION, vertex_.GetX(), vertex_.GetY());
}

void SliderTipModifier::PaintBubble(DrawingContext& context)
{
    auto sizeScale = sizeScale_->Get();
    auto opacityScale = opacityScale_->Get();
    RSPath path;
    auto vertexPair = GetBubbleVertex();
    vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock = vertexPair.second;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto fontScale = pipeline->GetFontScale();
    if (axis_ == Axis::HORIZONTAL) {
        if (GreatOrEqual(fontScale, SUITABLEAGING_LEVEL_1_SCALE)) {
            PaintHorizontalBubbleSuitableAging(vertexOffsetFromBlock, path);
        } else {
            PaintHorizontalBubble(vertexOffsetFromBlock, path);
        }
    } else {
        if (GreatOrEqual(fontScale, SUITABLEAGING_LEVEL_1_SCALE)) {
            PaintVerticalBubbleSuitableAging(vertexOffsetFromBlock, path);
        } else {
            PaintVerticalBubble(vertexOffsetFromBlock, path);
        }
    }
    context.canvas.Save();
    context.canvas.Translate(vertex_.GetX(), vertex_.GetY());
    context.canvas.Scale(sizeScale, sizeScale);
    context.canvas.Translate(vertex_.GetX() * -1.0, vertex_.GetY() * -1.0);
    RSPen pen;
    pen.SetColor(ToRSColor(tipColor_.ChangeAlpha(std::round(tipColor_.GetAlpha() * opacityScale))));
    pen.SetAntiAlias(true);
    RSBrush brush;
    brush.SetColor(ToRSColor(tipColor_.ChangeAlpha(std::round(tipColor_.GetAlpha() * opacityScale))));
    auto& canvas = context.canvas;
    canvas.AttachPen(pen);
    canvas.AttachBrush(brush);
    canvas.ClipPath(path, RSClipOp::INTERSECT, true);
    canvas.DrawPath(path);
    canvas.DetachBrush();
    canvas.DetachPen();
}

void SliderTipModifier::onDraw(DrawingContext& context)
{
    if ((!tipFlag_->Get()) || (tipFlag_->Get() && GreatNotEqual(sizeScale_->Get(), BUBBLE_SIZE_MIN_SCALE))) {
        BuildParagraph();
        UpdateBubbleSize();
        PaintTip(context);
    }
}

void SliderTipModifier::SetBubbleDisplayAnimation(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto weak = AceType::WeakClaim(this);
    AnimationOption option = AnimationOption();
    option.SetDuration(BUBBLE_DISPLAY_SIZE_CHANGE_TIMER);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(option, [weak]() {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->sizeScale_->Set(BUBBLE_SIZE_MAX_SCALE);
    }, nullptr, nullptr, host->GetContextRefPtr());

    option.SetDuration(BUBBLE_DISPLAY_OPACITY_CHANGE_TIMER);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [weak]() {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->opacityScale_->Set(BUBBLE_OPACITY_MAX_SCALE);
    }, nullptr, nullptr, host->GetContextRefPtr());
}

void SliderTipModifier::SetBubbleDisappearAnimation(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto weak = AceType::WeakClaim(this);
    AnimationOption option = AnimationOption();
    option.SetDuration(BUBBLE_DISAPPEAR_SIZE_CHANGE_TIMER);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(option, [weak]() {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->sizeScale_->Set(BUBBLE_SIZE_MIN_SCALE);
    }, nullptr, nullptr, host->GetContextRefPtr());

    option.SetDuration(BUBBLE_DISAPPEAR_OPACITY_CHANGE_TIMER);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [weak]() {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->opacityScale_->Set(BUBBLE_OPACITY_MIN_SCALE);
    }, onFinishEventTipSize_, nullptr, host->GetContextRefPtr());
}

void SliderTipModifier::SetTipFlag(bool flag, const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(tipFlag_);
    if (tipFlag_->Get() == flag) {
        return;
    }
    taskId_++;
    if (flag) {
        SetBubbleDisplayAnimation(host);
    } else if (tipDelayTime_ > 0) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto taskExecutor = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostDelayedTask(
            [weak = WeakClaim(this), taskId = taskId_, weakHost = AceType::WeakClaim(AceType::RawPtr(host))]() {
                auto modifier = weak.Upgrade();
                CHECK_NULL_VOID(modifier);
                auto host = weakHost.Upgrade();
                CHECK_NULL_VOID(host);
                if (modifier->taskId_ != taskId) {
                    return;
                }
                modifier->SetBubbleDisappearAnimation(host);
                auto pipeline = host->GetContextRefPtr();
                CHECK_NULL_VOID(pipeline);
                pipeline->RequestFrame();
            },
            TaskExecutor::TaskType::UI, tipDelayTime_, "ArkUISliderSetBubbleDisappearAnimation");
    } else {
        SetBubbleDisappearAnimation(host);
    }
    tipFlag_->Set(flag);
}

void SliderTipModifier::BuildParagraph()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto fontStyle = std::make_unique<NG::FontStyle>();
    CHECK_NULL_VOID(fontStyle);
    fontStyle->UpdateTextColor(textColor_.ChangeAlpha(std::round(textColor_.GetAlpha() * opacityScale_->Get())));
    auto fontScale = pipeline->GetFontScale();
    if (GreatOrEqual(fontScale, SUITABLEAGING_LEVEL_1_SCALE) && LessNotEqual(fontScale, SUITABLEAGING_LEVEL_2_SCALE)) {
        textFontSize_ = SUITABLEAGING_LEVEL_1_TEXT_FONT_SIZE;
    } else if (GreatOrEqual(fontScale, SUITABLEAGING_LEVEL_2_SCALE)) {
        textFontSize_ = SUITABLEAGING_LEVEL_2_TEXT_FONT_SIZE;
    }
    fontStyle->UpdateFontSize(textFontSize_);
    auto theme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    TextStyle textStyle = CreateTextStyleUsingTheme(fontStyle, nullptr, theme);
    auto content = content_->Get();
    auto fontManager = pipeline->GetFontManager();
    if (fontManager && fontManager->IsUseAppCustomFont()) {
        textStyle.SetFontFamilies(Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont()));
    }
    CreateParagraphAndLayout(textStyle, content);
}

void SliderTipModifier::CreateParagraphAndLayout(const TextStyle& textStyle, const std::string& content)
{
    if (!CreateParagraph(textStyle, content)) {
        return;
    }
    CHECK_NULL_VOID(paragraph_);
    auto gridColumnType = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::BUBBLE_TYPE);
    CHECK_NULL_VOID(gridColumnType);
    auto parent = gridColumnType->GetParent();
    if (parent) {
        parent->BuildColumnWidth();
    }

    auto pipeLine = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeLine);
    auto fontScale = pipeLine->GetFontScale();
    auto width = static_cast<float>(TEXT_MAX.ConvertToPx());
    if (GreatOrEqual(fontScale, SUITABLEAGING_LEVEL_1_SCALE) ||
        (GreatOrEqual(fontScale, SUITABLEAGING_LEVEL_2_SCALE))) {
        width = static_cast<float>(TEXT_AGING_MAX.ConvertToPx());
    }
    paragraph_->Layout(width);
}

bool SliderTipModifier::CreateParagraph(const TextStyle& textStyle, std::string content)
{
    ParagraphStyle paraStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = MAX_LENGTH,
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = WordBreak::BREAK_ALL,
        .textOverflow = TextOverflow::ELLIPSIS };
    paragraph_ = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_RETURN(paragraph_, false);
    paragraph_->PushStyle(textStyle);
    StringUtils::TransformStrCase(content, static_cast<int32_t>(textStyle.GetTextCase()));
    paragraph_->AddText(StringUtils::Str8ToStr16(content));
    paragraph_->Build();
    return true;
}

std::pair<OffsetF, float> SliderTipModifier::GetBubbleVertex()
{
    if (!getBubbleVertexFunc_) {
        return std::pair<OffsetF, float>();
    }
    auto bubbleVertexInBlock = getBubbleVertexFunc_();
    bubbleVertexInBlock.first += contentOffset_->Get();
    return bubbleVertexInBlock;
}

void SliderTipModifier::UpdateBubbleSize()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);

    float bubbleSizeHeight = static_cast<float>(BUBBLE_HORIZONTAL_WIDTH.ConvertToPx());
    float bubbleSizeWidth = static_cast<float>(BUBBLE_HORIZONTAL_HEIGHT.ConvertToPx());
    if (axis_ != Axis::HORIZONTAL) {
        bubbleSizeHeight = static_cast<float>(BUBBLE_VERTICAL_WIDTH.ConvertToPx());
        bubbleSizeWidth = static_cast<float>(BUBBLE_VERTICAL_HEIGHT.ConvertToPx());
    }

    auto fontScale = pipeline->GetFontScale();
    if (GreatOrEqual(fontScale, SUITABLEAGING_LEVEL_1_SCALE) && LessNotEqual(fontScale, SUITABLEAGING_LEVEL_2_SCALE)) {
        bubbleSizeHeight = static_cast<float>(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx());
        bubbleSizeWidth = static_cast<float>(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx());
        if (axis_ != Axis::HORIZONTAL) {
            bubbleSizeHeight = static_cast<float>(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx());
            bubbleSizeWidth = static_cast<float>(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx());
        }
    } else if (GreatOrEqual(fontScale, SUITABLEAGING_LEVEL_2_SCALE)) {
        bubbleSizeHeight = static_cast<float>(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx());
        bubbleSizeWidth = static_cast<float>(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx());
        if (axis_ != Axis::HORIZONTAL) {
            bubbleSizeHeight = static_cast<float>(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx());
            bubbleSizeWidth = static_cast<float>(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx());
        }
    }
    bubbleSize_ = SizeF(bubbleSizeHeight, bubbleSizeWidth);
}

bool SliderTipModifier::UpdateOverlayRect(const SizeF& frameSize)
{
    auto contentSize = contentSize_->Get();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto vertexPair = GetBubbleVertex();
    auto vertex = vertexPair.first;
    auto distance = static_cast<float>(theme->GetBubbleToCircleCenterDistance().ConvertToPx());
    auto hotShadowWidth = sliderMode_ == SliderModel::SliderMode::OUTSET
                              ? theme->GetOutsetHotBlockShadowWidth().ConvertToPx()
                              : theme->GetInsetHotBlockShadowWidth().ConvertToPx();
    auto circleSize = SizeF(blockSize_.Width() + hotShadowWidth / HALF, blockSize_.Height() + hotShadowWidth / HALF);
    RectF rect;
    if (axis_ == Axis::HORIZONTAL) {
        auto maxWidth = std::max(circleSize.Height(), frameSize.Height());
        if (sliderGlobalOffset_->Get().GetY() + vertex.GetY() < bubbleSize_.Height()) {
            rect.SetOffset(OffsetF(-bubbleSize_.Width(), bubbleSize_.Height() + distance));
        } else {
            rect.SetOffset(OffsetF(-bubbleSize_.Width(), -bubbleSize_.Height() - distance));
        }
        rect.SetSize(
            SizeF(contentSize.Width() + bubbleSize_.Width() / HALF, maxWidth + bubbleSize_.Height() + distance));
    } else {
        float bubbleCenterX = rect.GetOffset().GetX() + bubbleSize_.Width() * HALF;
        float sliderOffsetX = sliderGlobalOffset_->Get().GetX() - bubbleCenterX;
        auto maxWidth = std::max(circleSize.Width(), frameSize.Width());
        if (sliderGlobalOffset_->Get().GetX() + vertex.GetX() < bubbleSize_.Width()) {
            rect.SetOffset(OffsetF(AceApplicationInfo::GetInstance().IsRightToLeft()
                ? (sliderOffsetX - bubbleSize_.Width() - distance)
                : (bubbleSize_.Width() + distance), -bubbleSize_.Height()));
        } else {
            rect.SetOffset(OffsetF(AceApplicationInfo::GetInstance().IsRightToLeft()
                ? (sliderOffsetX + bubbleSize_.Width() + distance)
                : (-bubbleSize_.Width() - distance), -bubbleSize_.Height()));
        }
        rect.SetSize(
            SizeF(maxWidth + bubbleSize_.Width() + distance, contentSize.Height() + bubbleSize_.Height() / HALF));
    }
    auto origin = GetBoundsRect();
    if (origin.IsValid() && rect.IsValid()) {
        rect = rect.CombineRectT(origin);
    }
    if (rect != origin) {
        SetBoundsRect(rect);
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG
