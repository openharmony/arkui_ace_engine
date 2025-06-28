/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/button/rosen_render_button.h"

#include "core/components/box/render_box.h"
#include "core/pipeline/base/rosen_render_context.h"
#ifdef OHOS_PLATFORM
#include "core/components/common/painter/rosen_svg_painter.h"
#endif
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace {
namespace {

constexpr double HALF = 0.5;

// Definition for arc button of watch which intersected by circle and ellipse.
constexpr Dimension CIRCLE_DIAMETER = 233.0_vp;
constexpr Dimension OVAL_WIDTH = 260.0_vp;
constexpr Dimension OVAL_HEIGHT = 98.0_vp;
constexpr Dimension OFFSET_X = (OVAL_WIDTH - ARC_BUTTON_WIDTH) / 2.0;
constexpr Dimension OFFSET_Y = CIRCLE_DIAMETER - ARC_BUTTON_HEIGHT;
constexpr double CIRCLE_START_ANGLE = 0.759;
const double CIRCLE_SWEEP_ANGLE = ACE_PI - CIRCLE_START_ANGLE * 2;
constexpr double OVAL_START_ANGLE = 4.0;
const double OVAL_SWEEP_ANGLE = ACE_PI * 3 - OVAL_START_ANGLE * 2;
const double RADIAN_TO_DEGREE = 180.0 / ACE_PI;

// Definition for download button in watch
constexpr Dimension CIRCLE_PROGRESS_THICKNESS = 2.0_vp;
constexpr Dimension WATCH_DOWNLOAD_SIZE_DELTA = 8.0_vp;
const double PROGRESS_START_ANGLE = 1.5 * ACE_PI;

// Definition for animation
constexpr uint8_t DEFAULT_OPACITY = 255;

constexpr Dimension FOCUS_PADDING = 2.0_vp;
constexpr Dimension FOCUS_BORDER_WIDTH = 2.0_vp;
constexpr uint32_t FOCUS_BORDER_COLOR = 0xFF0A59F7;
constexpr uint32_t FOCUS_POPUP_BORDER_COLOR = 0xFFFFFFFF;

} // namespace

void RosenRenderButton::PerformLayout()
{
    RenderButton::PerformLayout();

    UpdateLayer();
}

void RosenRenderButton::UpdateLayer()
{
    float translateX = GetLayoutSize().Width() / 2 * (INIT_SCALE - scale_);
    // The bottom of the component must be close to the bottom of the circle when the type is arc.
    // The center point deviates 2 times downward.
    if (!buttonComponent_) {
        return;
    }
    float translateY = (buttonComponent_->GetType() == ButtonType::ARC)
                        ? GetLayoutSize().Height() * (INIT_SCALE - scale_) * 2
                        : GetLayoutSize().Height() / 2 * (1.0 - scale_);
    Matrix4 translateMatrix = Matrix4::CreateTranslate(translateX, translateY, 0.0);
    Matrix4 scaleMatrix = Matrix4::CreateScale(scale_, scale_, 1.0);
    Matrix4 transformMatrix = translateMatrix * scaleMatrix;

    transformLayer_ = transformMatrix;
    opacityLayer_ = DEFAULT_OPACITY * opacity_;
}

void RosenRenderButton::PaintLayer(RSCanvas* canvas)
{
#ifdef OHOS_PLATFORM
    auto recordingCanvas = static_cast<RSRecordingCanvas*>(canvas);
    recordingCanvas->ConcatMatrix(RosenSvgPainter::ToDrawingMatrix(transformLayer_));
#endif
}

void RosenRenderButton::Paint(RenderContext& context, const Offset& offset)
{
    if (!buttonComponent_) {
        return;
    }
    if (isHover_) {
        UpdateLayer();
        isHover_ = false;
    }
    PaintButtonAnimation();
    auto canvas = static_cast<RosenRenderContext&>(context).GetCanvas();
    if (canvas == nullptr) {
        LOGE("Paint canvas is null");
        return;
    }
    PaintLayer(canvas);
    if (buttonComponent_->GetType() == ButtonType::ICON) {
        RenderNode::Paint(context, offset);
        return;
    }
    DrawButton(canvas, offset);
    auto pipeline = context_.Upgrade();
    if (pipeline == nullptr) {
        return;
    }
    if (isFocus_ && (isTablet_ || isPhone_) && pipeline && pipeline->GetIsTabKeyPressed()) {
        // Need to use PipelineContext::ShowFocusAnimation
        if (buttonComponent_->IsPopupButton()) {
            PaintPopupFocus(context);
        } else {
            PaintFocus(context, offset);
        }
        SyncFocusGeometryProperties();
    }
    RenderNode::Paint(context, offset);
}

void RosenRenderButton::PaintButtonAnimation()
{
    if (!animationRunning_) {
        return;
    }
    UpdateLayer();
    if (isLastFrame_) {
        animationRunning_ = false;
        isOpacityAnimation_ = false;
        isLastFrame_ = false;
        isTouchAnimation_ = false;
    }
}

Size RosenRenderButton::Measure()
{
    // Layout size need includes border width, the border width is half outside of button,
    // total width and height needs to add border width defined by user.
    if (!buttonComponent_) {
        return Size();
    }
    widthDelta_ = NormalizeToPx(buttonComponent_->GetBorderEdge().GetWidth());
    double delta = widthDelta_ / 2;
    offsetDelta_ = Offset(delta, delta);
    if (buttonComponent_->GetType() == ButtonType::ARC) {
        return buttonSize_ + Size(widthDelta_, widthDelta_);
    }
    if (NeedLayoutExtendToParant()) {
        buttonSize_ = GetLayoutParam().GetMaxSize();
    }
    MeasureButtonSize();
    if (buttonComponent_->GetType() == ButtonType::NORMAL) {
        if (buttonComponent_->GetDeclarativeFlag()) {
            ResetBoxRadius();
        }
        if (!buttonComponent_->GetRadiusState() && buttonComponent_->IsInputButton()) {
            rrectRadius_ = buttonSize_.Height() / 2.0;
        }
    }
    return buttonSize_ + Size(widthDelta_, widthDelta_);
}

void RosenRenderButton::MeasureButtonSize()
{
    if (buttonComponent_->GetType() == ButtonType::ICON) {
        return;
    }
    if (NearEqual(GetLayoutParam().GetMaxSize().Width(), Size::INFINITE_SIZE) || (!widthDefined_)) {
        buttonSize_.SetWidth(0.0);
    }
    if (buttonComponent_->GetType() == ButtonType::CAPSULE) {
        MeasureCapsule();
        return;
    }
    if (buttonComponent_->GetType() == ButtonType::CIRCLE) {
        MeasureCircle();
        return;
    }
    if (isWatch_ && (buttonComponent_->GetType() == ButtonType::DOWNLOAD)) {
        if (buttonComponent_->GetRadiusState() || widthDefined_ || heightDefined_) {
            MeasureCircle();
            progressDiameter_ = rrectRadius_ * 2 - NormalizeToPx(WATCH_DOWNLOAD_SIZE_DELTA);
        } else {
            buttonSize_ = Size(progressDiameter_ + NormalizeToPx(WATCH_DOWNLOAD_SIZE_DELTA),
                progressDiameter_ + NormalizeToPx(WATCH_DOWNLOAD_SIZE_DELTA));
        }
    }
}

void RosenRenderButton::MeasureCapsule()
{
    if (GreatNotEqual(rrectRadius_, buttonSize_.Height() / 2.0)) {
        return;
    }
    rrectRadius_ = buttonSize_.Height() / 2.0;
    ResetBoxRadius();
}

void RosenRenderButton::MeasureCircle()
{
    if (!buttonComponent_->GetRadiusState()) {
        if (widthDefined_ || heightDefined_) {
            double minSize = std::min(GetLayoutParam().GetMaxSize().Width(), GetLayoutParam().GetMaxSize().Height());
            if (buttonComponent_->GetDeclarativeFlag()) {
                minSize = widthDefined_ ? std::min(buttonSize_.Width(), buttonSize_.Height()) : buttonSize_.Height();
            }
            rrectRadius_ = (minSize - widthDelta_) / 2.0;
        }
    } else {
        auto constrainedSize =
            GetLayoutParam().Constrain(Size(rrectRadius_ * 2.0 + widthDelta_, rrectRadius_ * 2.0 + widthDelta_));
        rrectRadius_ = (std::min(constrainedSize.Width(), constrainedSize.Height()) - widthDelta_) / 2.0;
    }
    buttonSize_.SetWidth(rrectRadius_ * 2.0);
    buttonSize_.SetHeight(rrectRadius_ * 2.0);
    ResetBoxRadius();
}

void RosenRenderButton::ResetBoxRadius()
{
    if (!buttonComponent_->GetRadiusState() && buttonComponent_->GetDeclarativeFlag()) {
        return;
    }
    auto parent = GetParent().Upgrade();
    if (!parent) {
        return;
    }
    auto box = AceType::DynamicCast<RenderBox>(parent);
    if (box) {
        auto backDecoration = box->GetBackDecoration();
        if (backDecoration) {
            auto border = backDecoration->GetBorder();
            backDecoration->SetBorderRadius(Radius(rrectRadius_ + NormalizeToPx(border.Top().GetWidth())));
        }
    }
}

void RosenRenderButton::DrawShape(RSCanvas* canvas, const Offset& offset, bool isStroke)
{
    RSRoundRect rRect;

    if (isStroke) {
        RSPen pen;
        uint32_t focusColorValue = buttonComponent_->GetFocusColor().GetValue();
        uint32_t borderColorValue = buttonComponent_->GetBorderEdge().GetColor().GetValue();
        pen.SetColor(needFocusColor_ ? focusColorValue : borderColorValue);
        pen.SetWidth(NormalizeToPx(borderEdge_.GetWidth()));
        pen.SetAntiAlias(true);

        if (buttonComponent_->GetType() == ButtonType::CUSTOM) {
            ConvertToVector(buttonComponent_->GetRectRadii(), radii_);
            rRect = RSRoundRect(RSRect(0, 0, static_cast<RSScalar>(buttonSize_.Width()),
                static_cast<RSScalar>(buttonSize_.Height())), radii_);
        } else {
            rRect = RSRoundRect(RSRect(0, 0, static_cast<RSScalar>(buttonSize_.Width()),
                static_cast<RSScalar>(buttonSize_.Height())),
                rrectRadius_, rrectRadius_);
        }
        rRect.Offset(offset.GetX(), offset.GetY());

        canvas->AttachPen(pen);
        canvas->DrawRoundRect(rRect);
        canvas->DetachPen();
    } else {
        RSBrush brush;
        brush.SetColor(GetStateColor());
        brush.SetAntiAlias(true);

        if (buttonComponent_->GetType() == ButtonType::CUSTOM) {
            ConvertToVector(buttonComponent_->GetRectRadii(), radii_);
            rRect = RSRoundRect(RSRect(0, 0, static_cast<RSScalar>(buttonSize_.Width()),
                static_cast<RSScalar>(buttonSize_.Height())), radii_);
        } else {
            rRect = RSRoundRect(RSRect(0, 0, static_cast<RSScalar>(buttonSize_.Width()),
                static_cast<RSScalar>(buttonSize_.Height())),
                rrectRadius_, rrectRadius_);
        }
        rRect.Offset(offset.GetX(), offset.GetY());

        canvas->AttachBrush(brush);
        canvas->DrawRoundRect(rRect);
        canvas->DetachBrush();
    }
}

void RosenRenderButton::DrawArc(RSCanvas* canvas, const Offset& offset)
{
    double offsetDelta = NormalizeToPx((OVAL_WIDTH - CIRCLE_DIAMETER)) / 2;
    RSRecordingPath arcPath;
    arcPath.AddArc(
        RSRect(0, NormalizeToPx(OFFSET_Y), NormalizeToPx(OVAL_WIDTH), NormalizeToPx(OVAL_HEIGHT + OFFSET_Y)),
        OVAL_START_ANGLE * RADIAN_TO_DEGREE, OVAL_SWEEP_ANGLE * RADIAN_TO_DEGREE);
    arcPath.AddArc(
        RSRect(offsetDelta, 0, NormalizeToPx(CIRCLE_DIAMETER) + offsetDelta, NormalizeToPx(CIRCLE_DIAMETER)),
        CIRCLE_START_ANGLE * RADIAN_TO_DEGREE, CIRCLE_SWEEP_ANGLE * RADIAN_TO_DEGREE);
    arcPath.Offset(offset.GetX() - NormalizeToPx(OFFSET_X), offset.GetY() - NormalizeToPx(OFFSET_Y));

    RSBrush brush;
    brush.SetColor(GetStateColor());
    brush.SetAntiAlias(true);
    canvas->AttachBrush(brush);
    canvas->DrawPath(arcPath);
    canvas->DetachBrush();
}

void RosenRenderButton::DrawLineProgress(RSCanvas* canvas, const Offset& offset)
{
    RSBrush brush;
    brush.SetColor(needFocusColor_ ? progressFocusColor_.GetValue() : progressColor_.GetValue());
    brush.SetAntiAlias(true);
    RSRoundRect rRect(
        RSRect(0, 0, buttonSize_.Width(), buttonSize_.Height()), rrectRadius_, rrectRadius_);
    rRect.Offset(offset.GetX(), offset.GetY());
    canvas->Save();
    canvas->ClipRoundRect(rRect, RSClipOp::INTERSECT, true);
    canvas->AttachBrush(brush);
    canvas->DrawRect({ offset.GetX(), offset.GetY(), progressWidth_, buttonSize_.Height() });
    canvas->DetachBrush();
    canvas->Restore();
}

void RosenRenderButton::DrawLineProgressAnimation(RSCanvas* canvas, const Offset& offset)
{
    double offsetX = offset.GetX();
    double offsetY = offset.GetY();
    double radius = buttonSize_.Height() / 2.0;
    RSRecordingPath path;
    path.AddArc(RSRect(offsetX, offsetY, buttonSize_.Height() + offsetX, buttonSize_.Height() + offsetY),
        90, 180);
    if (LessNotEqual(progressWidth_, radius)) {
        path.AddArc(RSRect(progressWidth_ + offsetX, offsetY,
            buttonSize_.Height() - progressWidth_ + offsetX, buttonSize_.Height() + offsetY),
            270, -180);
    } else if (GreatNotEqual(progressWidth_, buttonSize_.Width() - radius)) {
        path.AddRect(RSRect(radius + offsetX, offsetY, buttonSize_.Width() - radius + offsetX,
            buttonSize_.Height() + offsetY),
            RSPathDirection::CW_DIRECTION);
        path.AddArc(RSRect((buttonSize_.Width() - radius) * 2.0 - progressWidth_ + offsetX, offsetY,
            progressWidth_ + offsetX, buttonSize_.Height() + offsetY),
            270, 180);
    } else {
        path.AddRect(
            RSRect(radius + offsetX, offsetY, progressWidth_ + offsetX, buttonSize_.Height() + offsetY),
            RSPathDirection::CW_DIRECTION);
    }
    RSBrush brush;
    brush.SetColor(progressColor_.GetValue());
    brush.SetAntiAlias(true);
    canvas->AttachBrush(brush);
    canvas->DrawPath(path);
    canvas->DetachBrush();
}

void RosenRenderButton::DrawCircleProgress(RSCanvas* canvas, const Offset& offset)
{
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(progressColor_.GetValue());
    pen.SetWidth(NormalizeToPx(CIRCLE_PROGRESS_THICKNESS));
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    canvas->AttachPen(pen);
    canvas->DrawArc(RSRect(offset.GetX(), offset.GetY(),
        progressDiameter_ + offset.GetX(), progressDiameter_ + offset.GetY()),
        PROGRESS_START_ANGLE * RADIAN_TO_DEGREE, 360 * progressPercent_);
    canvas->DetachPen();
}

void RosenRenderButton::DrawDownloadButton(RSCanvas* canvas, const Offset& offset)
{
    if (isWatch_) {
        RSBrush brush;
        brush.SetAntiAlias(true);
        canvas->Save();
        brush.SetColor(GetStateColor());
        canvas->AttachBrush(brush);
        canvas->DrawCircle(
            RSPoint(offset.GetX() + buttonSize_.Width() / 2, offset.GetY() + buttonSize_.Height() / 2),
            (progressDiameter_ + NormalizeToPx(WATCH_DOWNLOAD_SIZE_DELTA)) / 2);
        canvas->DetachBrush();
        canvas->Restore();
        if (progressDisplay_) {
            DrawCircleProgress(canvas, offset + Offset((buttonSize_.Width() - progressDiameter_) / 2,
                (buttonSize_.Height() - progressDiameter_) / 2));
        }
        return;
    }

    DrawShape(canvas, offset);
    if (isPhone_) {
        DrawShape(canvas, offset, true);
        if (progressDisplay_) {
            if (GreatOrEqual(rrectRadius_, buttonSize_.Height() / 2.0)) {
                DrawLineProgressAnimation(canvas, offset);
            } else {
                DrawLineProgress(canvas, offset);
            }
        }
        return;
    }
    if (progressDisplay_) {
        DrawShape(canvas, offset, true);
        DrawLineProgress(canvas, offset);
    }
}

void RosenRenderButton::DrawButton(RSCanvas* canvas, const Offset& inOffset)
{
    Offset offset = inOffset + offsetDelta_;
    if (buttonComponent_->GetType() == ButtonType::ARC) {
        DrawArc(canvas, offset);
        return;
    }
    if (buttonComponent_->GetType() == ButtonType::DOWNLOAD) {
        DrawDownloadButton(canvas, offset);
        return;
    }

    // Paint button with border
    if (NormalizeToPx(buttonComponent_->GetBorderEdge().GetWidth()) > 0.0) {
        DrawShape(canvas, offset);
        DrawShape(canvas, offset, true);
        return;
    }
    DrawShape(canvas, offset);
}

uint32_t RosenRenderButton::GetStateColor()
{
    if (!buttonComponent_) {
        return Color().GetValue();
    }
    if (!buttonComponent_->GetStateEffect()) {
        return buttonComponent_->GetBackgroundColor().GetValue();
    }
    if (needHoverColor_) {
        return buttonComponent_->GetHoverColor().GetValue();
    }
    if (buttonComponent_->GetDisabledState()) {
        return buttonComponent_->GetDisabledColor().GetValue();
    }
    if (needFocusColor_) {
        return buttonComponent_->GetFocusColor().GetValue();
    }
    Color backgroundColor = buttonComponent_->GetBackgroundColor();
    if (NeedClickedColor(backgroundColor)) {
        return isClicked_ ? clickedColor_.GetValue() : backgroundColor.GetValue();
    }
    if (!isMoveEventValid_) {
        maskingOpacity_ = 0.0;
    }
    uint32_t animationColor;
    if (isWatch_) {
        animationColor = backgroundColor.BlendColor(Color::WHITE.ChangeOpacity(maskingOpacity_)).GetValue();
    } else {
        animationColor = backgroundColor.BlendColor(Color::BLACK.ChangeOpacity(maskingOpacity_)).GetValue();
    }
    return animationColor;
}

bool RosenRenderButton::NeedClickedColor(const Color& backgroundColor)
{
    if (setClickColor_) {
        return true;
    }
    if (clickedColor_ != defaultClickedColor_) {
        return true;
    } else {
        if (backgroundColor == Color::TRANSPARENT) {
            return true;
        }
    }
    return false;
}

bool RosenRenderButton::HasEffectiveTransform() const
{
    return scale_ != INIT_SCALE;
}

void RosenRenderButton::ConvertToVector(const std::array<Radius, 4>& radii, std::vector<RSPoint>& pRadii)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    double dipScale = context->GetDipScale();
    for (int32_t i = 0; i < 4; ++i) {
        pRadii[i].SetX(static_cast<float>(std::max(radii[i].GetX().ConvertToPx(dipScale), 0.0)));
        pRadii[i].SetY(static_cast<float>(std::max(radii[i].GetY().ConvertToPx(dipScale), 0.0)));
    }
}

void RosenRenderButton::PaintFocus(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("paint canvas is null");
        return;
    }
    Size canvasSize = GetLayoutSize();
    double focusBorderHeight = canvasSize.Height() + NormalizeToPx(FOCUS_PADDING * 2 + FOCUS_BORDER_WIDTH);
    double focusBorderWidth = canvasSize.Width() + NormalizeToPx(FOCUS_PADDING * 2 + FOCUS_BORDER_WIDTH);
    double focusRadius = focusBorderHeight * HALF;
    if (!buttonComponent_) {
        return;
    }
    if (buttonComponent_->GetType() == ButtonType::NORMAL) {
        focusRadius = rrectRadius_ + NormalizeToPx(FOCUS_PADDING);
    }
    RSPen pen;
    pen.SetColor(FOCUS_BORDER_COLOR);
    pen.SetWidth(NormalizeToPx(FOCUS_BORDER_WIDTH));
    pen.SetAntiAlias(true);
    RSRoundRect rRect(RSRect(0, 0, focusBorderWidth, focusBorderHeight), focusRadius, focusRadius);
    rRect.Offset(-NormalizeToPx(FOCUS_PADDING + FOCUS_BORDER_WIDTH * HALF),
        -NormalizeToPx(FOCUS_PADDING + FOCUS_BORDER_WIDTH * HALF));
    canvas->AttachPen(pen);
    canvas->DrawRoundRect(rRect);
    canvas->DetachPen();
}

void RosenRenderButton::PaintPopupFocus(RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("paint canvas is null");
        return;
    }
    Size canvasSize = GetLayoutSize();
    double focusBorderHeight = canvasSize.Height() - NormalizeToPx(FOCUS_BORDER_WIDTH) / HALF;
    double focusBorderWidth = canvasSize.Width() - NormalizeToPx(FOCUS_BORDER_WIDTH) / HALF;
    double focusRadius = focusBorderHeight * HALF;
    if (!buttonComponent_) {
        return;
    }

    RSPen pen;
    pen.SetColor(FOCUS_POPUP_BORDER_COLOR);
    pen.SetWidth(NormalizeToPx(FOCUS_BORDER_WIDTH));
    pen.SetAntiAlias(true);

    RSRoundRect rRect(RSRect(0, 0, focusBorderWidth, focusBorderHeight), focusRadius, focusRadius);
    rRect.Offset(NormalizeToPx(FOCUS_BORDER_WIDTH), NormalizeToPx(FOCUS_BORDER_WIDTH));

    canvas->AttachPen(pen);
    canvas->DrawRoundRect(rRect);
    canvas->DetachPen();
}

void RosenRenderButton::SyncFocusGeometryProperties()
{
    auto rsNode = GetRSNode();
    if (!rsNode) {
        return;
    }
    Size boundsSize = GetLayoutSize();
    double focusBorderHeight = boundsSize.Height() + NormalizeToPx(FOCUS_PADDING * 2 + FOCUS_BORDER_WIDTH);
    double focusBorderWidth = boundsSize.Width() + NormalizeToPx(FOCUS_PADDING * 2 + FOCUS_BORDER_WIDTH);
    Offset boundsOffset = GetPaintOffset() + Offset(-NormalizeToPx(FOCUS_PADDING + FOCUS_BORDER_WIDTH * HALF),
                                                    -NormalizeToPx(FOCUS_PADDING + FOCUS_BORDER_WIDTH * HALF));
    boundsOffset += Offset(-NormalizeToPx(FOCUS_PADDING), -NormalizeToPx(FOCUS_PADDING));
    focusBorderWidth += 2 * NormalizeToPx(FOCUS_PADDING);
    focusBorderHeight += 2 *NormalizeToPx(FOCUS_PADDING);
    rsNode->SetBounds(boundsOffset.GetX(), boundsOffset.GetY(), focusBorderWidth, focusBorderHeight);
    if (IsTailRenderNode()) {
        Offset frameOffset = GetPaintOffset();
        Size frameSize = GetLayoutSize();
        rsNode->SetFrame(frameOffset.GetX(), frameOffset.GetY(), frameSize.Width(), frameSize.Height());
    }
}

} // namespace OHOS::Ace
