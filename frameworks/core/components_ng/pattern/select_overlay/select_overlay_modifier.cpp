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

#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/drawing.h"

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

constexpr float ROTATION_ANGLE = 45.0f;

std::vector<int32_t> circle_x { -1, 0, 1, 0 };
std::vector<int32_t> circle_Y { 0, -1, 0, 1 };
} // namespace

SelectOverlayModifier::SelectOverlayModifier(const OffsetF& menuOptionOffset)
{
    hasExtensitonMenu_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(hasExtensitonMenu_);

    pointRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    AttachProperty(pointRadius_);

    headPointRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    AttachProperty(headPointRadius_);

    menuOptionOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    AttachProperty(menuOptionOffset_);

    rotationAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(ROTATION_ANGLE);
    AttachProperty(rotationAngle_);

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
        if (i > 0) {
            lineEndOffset_.emplace_back(lineEndOffset);
            AttachProperty(lineEndOffset_[i - 1]);
        }
        AttachProperty(circleOffset_[i]);
    }
}

void SelectOverlayModifier::SetOtherPointRadius(const Dimension& radius)
{
    if (pointRadius_) {
        AnimationOption option = AnimationOption();
        option.SetDuration(ICON_MICRO_ANIMATION_DURATION2);
        option.SetCurve(Curves::FRICTION);
        AnimationUtils::Animate(
            option, [weakPointRadius = AceType::WeakClaim(AceType::RawPtr(pointRadius_)), radius]() {
                auto pointRadius = weakPointRadius.Upgrade();
                pointRadius->Set(radius.ConvertToPx());
            });
    }
}

void SelectOverlayModifier::SetHeadPointRadius(const Dimension& radius)
{
    if (headPointRadius_) {
        AnimationOption option = AnimationOption();
        option.SetDuration(ICON_MICRO_ANIMATION_DURATION2);
        option.SetCurve(Curves::FRICTION);
        AnimationUtils::Animate(
            option, [weakHeadPointRadius = AceType::WeakClaim(AceType::RawPtr(headPointRadius_)), radius]() {
                auto headPointRadius = weakHeadPointRadius.Upgrade();
                headPointRadius->Set(radius.ConvertToPx());
            });
    }
}

void SelectOverlayModifier::SetLineEndOffset(bool isMore)
{
    for (int32_t i = 0; i < ROUND_NUMBER; i++) {
        CHECK_NULL_VOID(circleOffset_[i]);
        if (i < ROUND_NUMBER - 1) {
            CHECK_NULL_VOID(lineEndOffset_[i]);
        }
    }
    CHECK_NULL_VOID(rotationAngle_);
    AnimationOption option = AnimationOption();
    option.SetDuration(ICON_MICRO_ANIMATION_DURATION1);
    option.SetCurve(Curves::FRICTION);
    if (isMore) {
        AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this),
                                            weakRotationAngle = AceType::WeakClaim(AceType::RawPtr(rotationAngle_))]() {
            auto overlayModifier = weak.Upgrade();
            auto rotationAngle = weakRotationAngle.Upgrade();
            overlayModifier->circleOffset_[0]->Set(
                OffsetF(MORE_ANIMATION_LINEEND_X.ConvertToPx(), MORE_ANIMATION_TOP_CIRCLE_Y.ConvertToPx()));
            overlayModifier->circleOffset_[1]->Set(
                OffsetF(-MORE_ANIMATION_OTHER_CIRCLE_X.ConvertToPx(), -MORE_ANIMATION_OTHER_CIRCLE_Y.ConvertToPx()));
            overlayModifier->circleOffset_[2]->Set(OffsetF(MORE_ANIMATION_END_CIRCLE_X.ConvertToPx(), 0));
            overlayModifier->circleOffset_[3]->Set(
                OffsetF(-MORE_ANIMATION_OTHER_CIRCLE_X.ConvertToPx(), MORE_ANIMATION_OTHER_CIRCLE_Y.ConvertToPx()));
            overlayModifier->lineEndOffset_[0]->Set(
                OffsetF(MORE_ANIMATION_LINEEND_X.ConvertToPx(), -MORE_ANIMATION_LINEEND_Y.ConvertToPx()));
            overlayModifier->lineEndOffset_[1]->Set(
                OffsetF(MORE_ANIMATION_LINEEND_X.ConvertToPx(), Dimension(0, DimensionUnit::VP).ConvertToPx()));
            overlayModifier->lineEndOffset_[2]->Set(
                OffsetF(MORE_ANIMATION_LINEEND_X.ConvertToPx(), MORE_ANIMATION_LINEEND_Y.ConvertToPx()));
            rotationAngle->Set(0);
        });
    } else {
        for (int32_t i = 0; i < ROUND_NUMBER; i++) {
            auto coordinate =
                OffsetF(COORDINATE_X.ConvertToPx() * circle_x[i], COORDINATE_Y.ConvertToPx() * circle_Y[i]);
            AnimationUtils::Animate(
                option, [weak = AceType::WeakClaim(this),
                            weakRotationAngle = AceType::WeakClaim(AceType::RawPtr(rotationAngle_)), i, coordinate]() {
                    auto overlayModifier = weak.Upgrade();
                    auto rotationAngle = weakRotationAngle.Upgrade();
                    overlayModifier->circleOffset_[i]->Set(coordinate);
                    rotationAngle->Set(ROTATION_ANGLE);
                    if (i > 0) {
                        overlayModifier->lineEndOffset_[i - 1]->Set(coordinate);
                    };
                });
        }
    }
}

void SelectOverlayModifier::onDraw(DrawingContext& drawingContext)
{
    CHECK_NULL_VOID(hasExtensitonMenu_);
    CHECK_NULL_VOID_NOLOG(hasExtensitonMenu_->Get());
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
    auto pipeline = PipelineContext::GetCurrentContext();
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

    for (int32_t i = 0; i < ROUND_NUMBER - 2; i++) {
        RSPen pen;
        pen.SetAntiAlias(true);
        pen.SetColor(iconColor_.GetValue());
        pen.SetWidth(pointRadius_->Get() * 2);
        pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
        canvas.AttachPen(pen);
        auto coordinate = menuOptionOffset_->Get() + circleOffset_[i + 1]->Get();
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
    pen.SetColor(iconColor_.GetValue());
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
    for (int32_t i = 0; i < ROUND_NUMBER; i++) {
        canvas.Save();
        canvas.Rotate(rotationAngle_->Get(), menuOptionOffset_->Get().GetX(), menuOptionOffset_->Get().GetY());
        auto coordinate = menuOptionOffset_->Get() + circleOffset_[i]->Get();
        canvas.Translate(coordinate.GetX(), coordinate.GetY());
        RSBrush brush;
        brush.SetAntiAlias(true);
        brush.SetColor(iconColor_.GetValue());
        canvas.AttachBrush(brush);
        // The radius UX effect of the top circle is different from other circles.
        if (i == 0) {
            canvas.DrawCircle({ 0.0, 0.0 }, headPointRadius_->Get());
        } else {
            canvas.DrawCircle({ 0.0, 0.0 }, pointRadius_->Get());
        }
        canvas.DetachBrush();
        canvas.Restore();
    }
}
} // namespace OHOS::Ace::NG
