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

#include "core/components_ng/pattern/select_overlay/select_overlay_modifier.h"

#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension COORDINATE_X = 8.13_vp;
constexpr Dimension COORDINATE_Y = 8.13_vp;
constexpr Dimension MORE_ANIMATION_LINEEND_X = -8.9_vp;
constexpr Dimension MORE_ANIMATION_LINEEND_Y = 0.6_vp;
constexpr Dimension MORE_ANIMATION_OTHER_CIRCLE_X = 1.25_vp;
constexpr Dimension MORE_ANIMATION_OTHER_CIRCLE_Y = 8.25_vp;
constexpr Dimension MORE_ANIMATION_END_CIRCLE_X = 9.0_vp;
constexpr Dimension MORE_ANIMATION_TOP_CIRCLE_Y = -0.25_vp;
constexpr Dimension MASK_OFFSET_Y = 1.75_vp;
constexpr Dimension MASK_WIDTH = 24.0_vp;
constexpr Dimension MASK_HEIGHT = 10.25_vp;

constexpr int32_t ICON_MICRO_ANIMATION_DURATION1 = 300;
constexpr int32_t ICON_MICRO_ANIMATION_DURATION2 = 200;
constexpr int32_t ROUND_NUMBER = 4;
constexpr int32_t FIRST_INDEX = 0;
constexpr int32_t SECOND_INDEX = 1;
constexpr int32_t THIRD_INDEX = 2;
constexpr int32_t FOURTH_INDEX = 3;

constexpr float ROTATION_ANGLE = 45.0f;

std::vector<int32_t> circle_x { -1, 0, 1, 0 };
std::vector<int32_t> circle_Y { 0, -1, 0, 1 };
} // namespace

SelectOverlayModifier::SelectOverlayModifier(const OffsetF& menuOptionOffset, bool isReverse) : isReverse_(isReverse)
{
    pointRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    AttachProperty(pointRadius_);

    headPointRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    AttachProperty(headPointRadius_);

    menuOptionOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    AttachProperty(menuOptionOffset_);

    rotationAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(isReverse_ ? -ROTATION_ANGLE : ROTATION_ANGLE);
    AttachProperty(rotationAngle_);

    circlesAndBackArrowOpacity_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(1.0);
    AttachProperty(circlesAndBackArrowOpacity_);

    firstHandleIsShow_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(firstHandleIsShow_);

    secondHandleIsShow_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(secondHandleIsShow_);

    hasExtensionMenu_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(hasExtensionMenu_);

    SetDefaultCircleAndLineEndOffset();
}

void SelectOverlayModifier::SetDefaultCircleAndLineEndOffset()
{
    for (int32_t i = 0; i < ROUND_NUMBER; i++) {
        auto coordinate = OffsetF(COORDINATE_X.ConvertToPx() * circle_x[i], COORDINATE_Y.ConvertToPx() * circle_Y[i]);
        auto circleOffset = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(coordinate);
        auto lineEndCoordinate = coordinate;
        auto lineEndOffset = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(lineEndCoordinate);
        circleOffset_.emplace_back(circleOffset);
        if (i > FIRST_INDEX) {
            if (i == THIRD_INDEX && isReverse_ && !circleOffset_.empty()) {
                lineEndOffset->Set(circleOffset_.front()->Get());
            }
            lineEndOffset_.emplace_back(lineEndOffset);
            if (static_cast<int32_t>(lineEndOffset_.size()) > i - 1) {
                AttachProperty(lineEndOffset_[i - 1]);
            }
        }
        if (static_cast<int32_t>(circleOffset_.size()) > i) {
            AttachProperty(circleOffset_[i]);
        }
    }
}

void SelectOverlayModifier::SetOtherPointRadius(const Dimension& radius, bool noAnimation)
{
    if (pointRadius_) {
        AnimationOption option = AnimationOption();
        option.SetDuration(ICON_MICRO_ANIMATION_DURATION2);
        option.SetCurve(Curves::FRICTION);
        AnimationUtils::Animate(
            option, [weakPointRadius = AceType::WeakClaim(AceType::RawPtr(pointRadius_)), radius]() {
                auto pointRadius = weakPointRadius.Upgrade();
                CHECK_NULL_VOID(pointRadius);
                pointRadius->Set(radius.ConvertToPx());
            });
    }
}

void SelectOverlayModifier::SetHeadPointRadius(const Dimension& radius, bool noAnimation)
{
    if (headPointRadius_) {
        AnimationOption option = AnimationOption();
        option.SetDuration(ICON_MICRO_ANIMATION_DURATION2);
        option.SetCurve(Curves::FRICTION);
        AnimationUtils::Animate(
            option, [weakHeadPointRadius = AceType::WeakClaim(AceType::RawPtr(headPointRadius_)), radius]() {
                auto headPointRadius = weakHeadPointRadius.Upgrade();
                CHECK_NULL_VOID(headPointRadius);
                headPointRadius->Set(radius.ConvertToPx());
            });
    }
}

void SelectOverlayModifier::SetLineEndOffset(bool isMore, bool noAnimation)
{
    if (circleOffset_.size() < ROUND_NUMBER || lineEndOffset_.size() < ROUND_NUMBER - 1) {
        return;
    }
    for (int32_t i = 0; i < ROUND_NUMBER; i++) {
        CHECK_NULL_VOID(circleOffset_[i]);
        if (i < ROUND_NUMBER - 1) {
            CHECK_NULL_VOID(lineEndOffset_[i]);
        }
    }
    LineEndOffsetWithAnimation(isMore, noAnimation);
}

void SelectOverlayModifier::ChangeCircle()
{
    CHECK_NULL_VOID(rotationAngle_);
    if (circleOffset_.size() < ROUND_NUMBER || lineEndOffset_.size() < ROUND_NUMBER - 1) {
        return;
    }
    if (!isReverse_) {
        circleOffset_[FIRST_INDEX]->Set(
            OffsetF(MORE_ANIMATION_LINEEND_X.ConvertToPx(), MORE_ANIMATION_TOP_CIRCLE_Y.ConvertToPx()));
        circleOffset_[SECOND_INDEX]->Set(
            OffsetF(-MORE_ANIMATION_OTHER_CIRCLE_X.ConvertToPx(), -MORE_ANIMATION_OTHER_CIRCLE_Y.ConvertToPx()));
        circleOffset_[THIRD_INDEX]->Set(OffsetF(MORE_ANIMATION_END_CIRCLE_X.ConvertToPx(), 0));
        circleOffset_[FOURTH_INDEX]->Set(
            OffsetF(-MORE_ANIMATION_OTHER_CIRCLE_X.ConvertToPx(), MORE_ANIMATION_OTHER_CIRCLE_Y.ConvertToPx()));
        lineEndOffset_[FIRST_INDEX]->Set(
            OffsetF(MORE_ANIMATION_LINEEND_X.ConvertToPx(), -MORE_ANIMATION_LINEEND_Y.ConvertToPx()));
        lineEndOffset_[SECOND_INDEX]->Set(
            OffsetF(MORE_ANIMATION_LINEEND_X.ConvertToPx(), Dimension(0, DimensionUnit::VP).ConvertToPx()));
        lineEndOffset_[THIRD_INDEX]->Set(
            OffsetF(MORE_ANIMATION_LINEEND_X.ConvertToPx(), MORE_ANIMATION_LINEEND_Y.ConvertToPx()));
    } else {
        circleOffset_[FIRST_INDEX]->Set(
            OffsetF(-MORE_ANIMATION_END_CIRCLE_X.ConvertToPx(), Dimension(0, DimensionUnit::VP).ConvertToPx()));
        circleOffset_[SECOND_INDEX]->Set(
            OffsetF(MORE_ANIMATION_OTHER_CIRCLE_X.ConvertToPx(), -MORE_ANIMATION_OTHER_CIRCLE_Y.ConvertToPx()));
        circleOffset_[THIRD_INDEX]->Set(
            OffsetF(-MORE_ANIMATION_LINEEND_X.ConvertToPx(), MORE_ANIMATION_TOP_CIRCLE_Y.ConvertToPx()));
        circleOffset_[FOURTH_INDEX]->Set(
            OffsetF(MORE_ANIMATION_OTHER_CIRCLE_X.ConvertToPx(), MORE_ANIMATION_OTHER_CIRCLE_Y.ConvertToPx()));
        // Adjust the direction of back arrow when reverse layout.
        lineEndOffset_[FIRST_INDEX]->Set(
            OffsetF(-MORE_ANIMATION_LINEEND_X.ConvertToPx(), -MORE_ANIMATION_LINEEND_Y.ConvertToPx()));
        lineEndOffset_[SECOND_INDEX]->Set(
            OffsetF(-MORE_ANIMATION_LINEEND_X.ConvertToPx(), Dimension(0, DimensionUnit::VP).ConvertToPx()));
        lineEndOffset_[THIRD_INDEX]->Set(
            OffsetF(-MORE_ANIMATION_LINEEND_X.ConvertToPx(), MORE_ANIMATION_LINEEND_Y.ConvertToPx()));
    }
    rotationAngle_->Set(0);
}

void SelectOverlayModifier::LineEndOffsetWithAnimation(bool isMore, bool noAnimation)
{
    CHECK_NULL_VOID(rotationAngle_);
    if (isMore) {
        if (!noAnimation) {
            AnimationOption option = AnimationOption();
            option.SetDuration(ICON_MICRO_ANIMATION_DURATION1);
            option.SetCurve(Curves::FRICTION);
            AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this)]() {
                auto overlayModifier = weak.Upgrade();
                CHECK_NULL_VOID(overlayModifier);
                overlayModifier->ChangeCircle();
            });
        } else {
            ChangeCircle();
        }
    } else {
        BackArrowTransitionAnimation(noAnimation);
    }
}

void SelectOverlayModifier::BackArrowTransitionChange(const OffsetF& coordinate, int32_t i)
{
    if (static_cast<int32_t>(circleOffset_.size()) < i || static_cast<int32_t>(lineEndOffset_.size()) < i - 1) {
        return;
    }
    circleOffset_[i]->Set(coordinate);
    rotationAngle_->Set(isReverse_ ? -ROTATION_ANGLE : ROTATION_ANGLE);
    if (i > FIRST_INDEX) {
        if (i == THIRD_INDEX && isReverse_) {
            auto endCircleOffset = OffsetF(COORDINATE_X.ConvertToPx() * circle_x[FIRST_INDEX],
                COORDINATE_Y.ConvertToPx() * circle_Y[FIRST_INDEX]);
            lineEndOffset_[i - 1]->Set(endCircleOffset);
            circleOffset_[FIRST_INDEX]->Set(endCircleOffset);
            return;
        }
        lineEndOffset_[i - 1]->Set(coordinate);
    };
}

void SelectOverlayModifier::BackArrowTransitionAnimation(bool noAnimation)
{
    CHECK_NULL_VOID(rotationAngle_);
    if (!noAnimation) {
        AnimationOption option = AnimationOption();
        option.SetDuration(ICON_MICRO_ANIMATION_DURATION1);
        option.SetCurve(Curves::FRICTION);

        for (int32_t i = 0; i < ROUND_NUMBER; i++) {
            auto coordinate =
                OffsetF(COORDINATE_X.ConvertToPx() * circle_x[i], COORDINATE_Y.ConvertToPx() * circle_Y[i]);
            AnimationUtils::Animate(
                option, [weak = AceType::WeakClaim(this),
                            weakRotationAngle = AceType::WeakClaim(AceType::RawPtr(rotationAngle_)), i, coordinate]() {
                    auto overlayModifier = weak.Upgrade();
                    CHECK_NULL_VOID(overlayModifier);
                    overlayModifier->BackArrowTransitionChange(coordinate, i);
                });
        }
    } else {
        for (int32_t i = 0; i < ROUND_NUMBER; i++) {
            auto coordinate =
                OffsetF(COORDINATE_X.ConvertToPx() * circle_x[i], COORDINATE_Y.ConvertToPx() * circle_Y[i]);
            BackArrowTransitionChange(coordinate, i);
        }
    }
}

void SelectOverlayModifier::onDraw(DrawingContext& drawingContext)
{
    CHECK_NULL_VOID(hasExtensionMenu_);
    CHECK_NULL_VOID(hasExtensionMenu_->Get());
    for (int32_t i = 0; i < ROUND_NUMBER; i++) {
        CHECK_NULL_VOID(circleOffset_[i]);
        if (i < ROUND_NUMBER - 1) {
            CHECK_NULL_VOID(lineEndOffset_[i]);
        }
    }
    CHECK_NULL_VOID(rotationAngle_);
    CHECK_NULL_VOID(menuOptionOffset_);
    CHECK_NULL_VOID(pointRadius_);
    CHECK_NULL_VOID(headPointRadius_);
    CHECK_NULL_VOID(firstHandleIsShow_);
    CHECK_NULL_VOID(secondHandleIsShow_);

    if (!isNewAvoid_ && !firstHandleIsShow_->Get() && !secondHandleIsShow_->Get()) {
        return;
    }

    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    iconColor_ = textOverlayTheme->GetMoreOrBackIconColor();
    DrawbBackArrow(drawingContext);
    DrawbCircles(drawingContext);
}

void SelectOverlayModifier::DrawbBackArrow(DrawingContext& drawingContext)
{
    auto& canvas = drawingContext.canvas;
    // Draw a back arrow.
    canvas.Save();
    canvas.Rotate(rotationAngle_->Get(), menuOptionOffset_->Get().GetX(), menuOptionOffset_->Get().GetY());

    Color iconColor = iconColor_;
    iconColor = iconColor.BlendOpacity(circlesAndBackArrowOpacity_->Get());
    int32_t headPointIndex = isReverse_ ? THIRD_INDEX : FIRST_INDEX;
    if (circleOffset_.size() < ROUND_NUMBER || lineEndOffset_.size() < ROUND_NUMBER - 1) {
        return;
    }
    for (int32_t i = 0; i < ROUND_NUMBER - 2; i++) {
        RSPen pen;
        pen.SetAntiAlias(true);
        pen.SetColor(iconColor.GetValue());
        pen.SetWidth(pointRadius_->Get() * 2);
        pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
        canvas.AttachPen(pen);
        int32_t targetIndex = (i + 1 == headPointIndex ? FIRST_INDEX : i + 1);
        auto coordinate = menuOptionOffset_->Get() + circleOffset_[targetIndex]->Get();
        auto endOffset = menuOptionOffset_->Get() + lineEndOffset_[i]->Get();
        canvas.DrawLine({ coordinate.GetX(), coordinate.GetY() }, { endOffset.GetX(), endOffset.GetY() });
        canvas.DetachPen();
    }

    auto sideWidth = MASK_WIDTH.ConvertToPx();
    auto maskOffset = menuOptionOffset_->Get() + OffsetF(-sideWidth / 2.0, MASK_OFFSET_Y.ConvertToPx());
    RSRect clipInnerRect = RSRect(maskOffset.GetX(), maskOffset.GetY(), sideWidth + maskOffset.GetX(),
        maskOffset.GetY() + MASK_HEIGHT.ConvertToPx());
    canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(iconColor.GetValue());
    pen.SetWidth(pointRadius_->Get() * 2);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    canvas.AttachPen(pen);
    auto coordinate = menuOptionOffset_->Get() + circleOffset_[3]->Get();
    auto endOffset = menuOptionOffset_->Get() + lineEndOffset_[2]->Get();
    canvas.DrawLine({ coordinate.GetX(), coordinate.GetY() }, { endOffset.GetX(), endOffset.GetY() });
    canvas.DetachPen();
    canvas.Restore();
}

void SelectOverlayModifier::DrawbCircles(DrawingContext& drawingContext)
{
    auto& canvas = drawingContext.canvas;
    // Paint other circles.
    Color iconColor = iconColor_;
    iconColor = iconColor.BlendOpacity(circlesAndBackArrowOpacity_->Get());
    if (circleOffset_.size() < ROUND_NUMBER) {
        return;
    }
    for (int32_t i = 0; i < ROUND_NUMBER; i++) {
        canvas.Save();
        canvas.Rotate(rotationAngle_->Get(), menuOptionOffset_->Get().GetX(), menuOptionOffset_->Get().GetY());
        auto coordinate = menuOptionOffset_->Get() + circleOffset_[i]->Get();
        canvas.Translate(coordinate.GetX(), coordinate.GetY());
        RSBrush brush;
        brush.SetAntiAlias(true);
        brush.SetColor(iconColor.GetValue());
        canvas.AttachBrush(brush);
        // The radius UX effect of the top circle is different from other circles.
        // the top circle is the third index when reverse layout.
        if ((!isReverse_ && (i == FIRST_INDEX)) || (isReverse_ && (i == THIRD_INDEX))) {
            canvas.DrawCircle({ 0.0, 0.0 }, headPointRadius_->Get());
        } else {
            canvas.DrawCircle({ 0.0, 0.0 }, pointRadius_->Get());
        }
        canvas.DetachBrush();
        canvas.Restore();
    }
}
} // namespace OHOS::Ace::NG
