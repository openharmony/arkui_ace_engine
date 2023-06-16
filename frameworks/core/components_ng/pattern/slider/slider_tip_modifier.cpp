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
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/slider/slider_theme.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension BEZIER_HORIZON_OFFSET_FIRST = 1.3_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_SECOND = 3.2_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_THIRD = 6.6_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_FOURTH = 16.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_FIRST = 0.1_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_SECOND = 3.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_THIRD = 8.0_vp;
constexpr Dimension ARROW_HEIGHT = 8.0_vp;
constexpr Dimension ARROW_WIDTH = 32.0_vp;
constexpr float HALF = 0.5f;

constexpr float BUBBLE_SIZE_MIN_SCALE = 0.6f;
constexpr float BUBBLE_SIZE_MAX_SCALE = 1.0f;
constexpr float BUBBLE_OPACITY_MIN_SCALE = 0.0f;
constexpr float BUBBLE_OPACITY_MAX_SCALE = 1.0f;
constexpr int32_t BUBBLE_DISPLAY_SIZE_CHANGE_TIMER = 250;
constexpr int32_t BUBBLE_DISPLAY_OPACITY_CHANGE_TIMER = 150;
constexpr int32_t BUBBLE_DISAPPEAR_SIZE_CHANGE_TIMER = 250;
constexpr int32_t BUBBLE_DISAPPEAR_OPACITY_CHANGE_TIMER = 250;
constexpr Dimension BUBBLE_TEXT_OFFSET = 8.0_vp;
} // namespace

SliderTipModifier::SliderTipModifier(std::function<OffsetF()> getBubbleVertexFunc)
    : tipFlag_(AceType::MakeRefPtr<PropertyBool>(false)),
      contentOffset_(AceType::MakeRefPtr<PropertyOffsetF>(OffsetF())),
      contentSize_(AceType::MakeRefPtr<PropertySizeF>(SizeF())),
      sizeScale_(AceType::MakeRefPtr<AnimatablePropertyFloat>(BUBBLE_SIZE_MIN_SCALE)),
      opacityScale_(AceType::MakeRefPtr<AnimatablePropertyFloat>(BUBBLE_OPACITY_MIN_SCALE)),
      content_(AceType::MakeRefPtr<PropertyString>("")), bubbleVertex_(AceType::MakeRefPtr<PropertyOffsetF>(OffsetF())),
      getBubbleVertexFunc_(std::move(getBubbleVertexFunc))
{
    AttachProperty(tipFlag_);
    AttachProperty(contentOffset_);
    AttachProperty(sizeScale_);
    AttachProperty(opacityScale_);
    AttachProperty(content_);
    AttachProperty(bubbleVertex_);
}

SliderTipModifier::~SliderTipModifier()
{}

void SliderTipModifier::PaintTip(DrawingContext& context)
{
    auto sizeScale = sizeScale_->Get();
    auto vertex = GetBubbleVertex();
    context.canvas.Save();
    context.canvas.Translate(vertex.GetX(), vertex.GetY());
    context.canvas.Scale(sizeScale, sizeScale);
    context.canvas.Translate(vertex.GetX() * -1.0, vertex.GetY() * -1.0);
    PaintBubble(context);
    CHECK_NULL_VOID(paragraph_);
    paragraph_->Paint(context.canvas, textOffset_.GetX(), textOffset_.GetY());
    context.canvas.Restore();
}

void SliderTipModifier::PaintBezier(
    bool isLeft, Axis axis, RSPath& path, const OffsetF& arrowCenter, const OffsetF& arrowEdge)
{
    if (isLeft) {
        path.MoveTo(arrowCenter.GetX(), arrowCenter.GetY());
        if (axis == Axis::HORIZONTAL) {
            path.QuadTo(arrowCenter.GetX() - static_cast<float>(BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() - static_cast<float>(BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()));
        } else {
            path.QuadTo(arrowCenter.GetX() + static_cast<float>(BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx()));
        }
        path.LineTo(arrowEdge.GetX(), arrowEdge.GetY());
    } else {
        path.MoveTo(arrowEdge.GetX(), arrowEdge.GetY());
        if (axis == Axis::HORIZONTAL) {
            path.LineTo(arrowCenter.GetX() + static_cast<float>(BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() + static_cast<float>(BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetX() + static_cast<float>(BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() + static_cast<float>(BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx()), arrowCenter.GetX(),
                arrowCenter.GetY());
        } else {
            path.LineTo(arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() + static_cast<float>(BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx()), arrowCenter.GetX(),
                arrowCenter.GetY());
        }
    }
}

void SliderTipModifier::PaintBubble(DrawingContext& context)
{
    auto opacityScale = opacityScale_->Get();
    auto offset = bubbleOffset_;
    auto bubbleSize = bubbleSize_;
    auto arrowHeight = static_cast<float>(ARROW_HEIGHT.ConvertToPx());
    RSPath path;
    OffsetF arrowCenter;
    OffsetF clockwiseFirstPoint;
    OffsetF clockwiseSecondPoint;
    float circularRadius = 0.0f;
    OffsetF clockwiseThirdPoint;
    OffsetF clockwiseFourthPoint;
    if (axis_ == Axis::HORIZONTAL) {
        arrowCenter = { offset.GetX() + bubbleSize.Width() * HALF, offset.GetY() + bubbleSize.Height() };
        float bottomLineLength = bubbleSize.Width() - (bubbleSize.Height() - arrowHeight);
        clockwiseFirstPoint = { arrowCenter.GetX() - bottomLineLength * HALF, arrowCenter.GetY() - arrowHeight };
        clockwiseSecondPoint = { clockwiseFirstPoint.GetX(), offset.GetY() };
        circularRadius = (clockwiseFirstPoint.GetY() - clockwiseSecondPoint.GetY()) * HALF;
        clockwiseThirdPoint = { clockwiseSecondPoint.GetX() + bottomLineLength, clockwiseSecondPoint.GetY() };
        clockwiseFourthPoint = { clockwiseThirdPoint.GetX(), offset.GetY() + circularRadius * 2 };
    } else {
        arrowCenter = { offset.GetX() + bubbleSize.Width(), offset.GetY() + bubbleSize.Height() * HALF };
        float bottomLineLength = bubbleSize.Height() - (bubbleSize.Width() - arrowHeight);
        clockwiseFirstPoint = { arrowCenter.GetX() - arrowHeight, arrowCenter.GetY() + bottomLineLength * HALF };
        clockwiseSecondPoint = { offset.GetX(), clockwiseFirstPoint.GetY() };
        circularRadius = (clockwiseFirstPoint.GetX() - clockwiseSecondPoint.GetX()) * HALF;
        clockwiseThirdPoint = { clockwiseSecondPoint.GetX(), clockwiseSecondPoint.GetY() - bottomLineLength };
        clockwiseFourthPoint = { offset.GetX() + circularRadius * 2, clockwiseThirdPoint.GetY() };
    }
    path.MoveTo(arrowCenter.GetX(), arrowCenter.GetY());
    PaintBezier(true, axis_, path, arrowCenter, clockwiseFirstPoint);
    path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION, clockwiseSecondPoint.GetX(),
        clockwiseSecondPoint.GetY());
    path.LineTo(clockwiseThirdPoint.GetX(), clockwiseThirdPoint.GetY());
    path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION, clockwiseFourthPoint.GetX(),
        clockwiseFourthPoint.GetY());
    PaintBezier(false, axis_, path, arrowCenter, clockwiseFourthPoint);
    RSPen pen;
    pen.SetColor(ToRSColor(tipColor_.ChangeAlpha(std::round(tipColor_.GetAlpha() * opacityScale))));
    pen.SetAntiAlias(true);
    RSBrush brush;
    brush.SetColor(ToRSColor(tipColor_.ChangeAlpha(std::round(tipColor_.GetAlpha() * opacityScale))));
    auto& canvas = context.canvas;
    canvas.AttachPen(pen);
    canvas.AttachBrush(brush);
#ifdef NEW_SKIA
    canvas.ClipPath(path, RSClipOp::INTERSECT, true);
    canvas.DrawPath(path);
#else
    canvas.DrawPath(path);
    canvas.ClipPath(path, RSClipOp::INTERSECT, true);
#endif
}

void SliderTipModifier::onDraw(DrawingContext& context)
{
    if (tipFlag_->Get() || GreatNotEqual(sizeScale_->Get(), BUBBLE_SIZE_MIN_SCALE)) {
        BuildParagraph();
        UpdateBubbleSize();
        PaintTip(context);
    }
}

void SliderTipModifier::SetBubbleDisplayAnimation()
{
    auto weak = AceType::WeakClaim(this);
    AnimationOption option = AnimationOption();
    option.SetDuration(BUBBLE_DISPLAY_SIZE_CHANGE_TIMER);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(option, [weak]() {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->sizeScale_->Set(BUBBLE_SIZE_MAX_SCALE);
    });

    option.SetDuration(BUBBLE_DISPLAY_OPACITY_CHANGE_TIMER);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [weak]() {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->opacityScale_->Set(BUBBLE_OPACITY_MAX_SCALE);
    });
}

void SliderTipModifier::SetBubbleDisappearAnimation()
{
    auto weak = AceType::WeakClaim(this);
    AnimationOption option = AnimationOption();
    option.SetDuration(BUBBLE_DISAPPEAR_SIZE_CHANGE_TIMER);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(option, [weak]() {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->sizeScale_->Set(BUBBLE_SIZE_MIN_SCALE);
    });

    option.SetDuration(BUBBLE_DISAPPEAR_OPACITY_CHANGE_TIMER);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [weak]() {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->opacityScale_->Set(BUBBLE_OPACITY_MIN_SCALE);
    });
}

void SliderTipModifier::SetTipFlag(bool flag)
{
    CHECK_NULL_VOID(tipFlag_);
    if (tipFlag_->Get() == flag) {
        return;
    }
    if (flag) {
        SetBubbleDisplayAnimation();
    } else {
        SetBubbleDisappearAnimation();
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
    fontStyle->UpdateFontSize(textFontSize_);
    TextStyle textStyle = CreateTextStyleUsingTheme(fontStyle, nullptr, pipeline->GetTheme<TextTheme>());
    auto content = content_->Get();
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
    auto bubbleMaxWidth = static_cast<float>(gridColumnType->GetMaxWidth());
    auto maxWidth = bubbleMaxWidth - BUBBLE_TEXT_OFFSET.ConvertToPx() * 2;
    paragraph_->Layout(maxWidth);
}

bool SliderTipModifier::CreateParagraph(const TextStyle& textStyle, std::string content)
{
    ParagraphStyle paraStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    paragraph_ = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_RETURN(paragraph_, false);
    paragraph_->PushStyle(textStyle);
    StringUtils::TransformStrCase(content, static_cast<int32_t>(textStyle.GetTextCase()));
    paragraph_->AddText(StringUtils::Str8ToStr16(content));
    paragraph_->Build();
    return true;
}

OffsetF SliderTipModifier::GetBubbleVertex()
{
    CHECK_NULL_RETURN(getBubbleVertexFunc_, bubbleVertex_->Get());
    return getBubbleVertexFunc_();
}

void SliderTipModifier::UpdateBubbleSize()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);

    SizeF textSize = { 0, 0 };
    if (paragraph_) {
        textSize = SizeF(paragraph_->GetTextWidth(), paragraph_->GetHeight());
    }
    OffsetF textOffsetInBubble = { 0, 0 };
    auto padding = static_cast<float>(theme->GetTipTextPadding().ConvertToPx());
    float bubbleSizeHeight = textSize.Height() + padding + padding;
    float bubbleSizeWidth = textSize.Width() + padding + padding;
    if (axis_ == Axis::HORIZONTAL) {
        bubbleSizeWidth = std::max(static_cast<float>(ARROW_WIDTH.ConvertToPx()) + bubbleSizeHeight, bubbleSizeWidth);
        bubbleSize_ = SizeF(bubbleSizeWidth, bubbleSizeHeight + static_cast<float>(ARROW_HEIGHT.ConvertToPx()));
        textOffsetInBubble.SetX((bubbleSize_.Width() - textSize.Width()) * HALF);
        textOffsetInBubble.SetY(padding);
        auto vertex = GetBubbleVertex();
        bubbleOffset_.SetX(vertex.GetX() - bubbleSize_.Width() * HALF);
        bubbleOffset_.SetY(vertex.GetY() - bubbleSize_.Height());
    } else {
        bubbleSizeHeight = std::max(static_cast<float>(ARROW_WIDTH.ConvertToPx()) + bubbleSizeWidth, bubbleSizeHeight);
        bubbleSize_ = SizeF(bubbleSizeWidth + static_cast<float>(ARROW_HEIGHT.ConvertToPx()), bubbleSizeHeight);
        textOffsetInBubble.SetX(padding);
        textOffsetInBubble.SetY((bubbleSize_.Height() - textSize.Height()) * HALF);
        auto vertex = GetBubbleVertex();
        bubbleOffset_.SetX(vertex.GetX() - bubbleSize_.Width());
        bubbleOffset_.SetY(vertex.GetY() - bubbleSize_.Height() * HALF);
    }
    textOffset_ = bubbleOffset_ + textOffsetInBubble;
}

void SliderTipModifier::UpdateOverlayRect(const SizeF& frameSize)
{
    auto contentSize = contentSize_->Get();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto distance = static_cast<float>(theme->GetBubbleToCircleCenterDistance().ConvertToPx());
    auto hotShadowWidth = sliderMode_ == SliderModel::SliderMode::OUTSET
                              ? theme->GetOutsetHotBlockShadowWidth().ConvertToPx()
                              : theme->GetInsetHotBlockShadowWidth().ConvertToPx();
    auto circleSize = SizeF(blockSize_.Width() + hotShadowWidth / HALF, blockSize_.Height() + hotShadowWidth / HALF);
    RectF rect;
    if (axis_ == Axis::HORIZONTAL) {
        auto maxWidth = std::max(circleSize.Height(), frameSize.Height());
        rect.SetOffset(OffsetF(-bubbleSize_.Width(), -bubbleSize_.Height() - distance));
        rect.SetSize(
            SizeF(contentSize.Width() + bubbleSize_.Width() / HALF, maxWidth + bubbleSize_.Height() + distance));
    } else {
        auto maxWidth = std::max(circleSize.Width(), frameSize.Width());
        rect.SetOffset(OffsetF(-bubbleSize_.Width() - distance, -bubbleSize_.Height()));
        rect.SetSize(
            SizeF(maxWidth + bubbleSize_.Width() + distance, contentSize.Height() + bubbleSize_.Height() / HALF));
    }

    SetBoundsRect(rect);
}
} // namespace OHOS::Ace::NG
