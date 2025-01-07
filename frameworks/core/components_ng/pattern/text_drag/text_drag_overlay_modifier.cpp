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

#include "core/components_ng/pattern/text_drag/text_drag_overlay_modifier.h"

#include <variant>

#include "base/geometry/rect.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_info.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/text/text_theme.h"

namespace OHOS::Ace::NG {
constexpr float DEFAULT_LIGHT_HEIGHT = 600.0f;
constexpr uint32_t DEFAULT_AMBIENT_COLOR = 0X0A000000;
constexpr float DEFAULT_SHADOW_COLOR = 0x33000000;
constexpr float DEFAULT_LIGHT_RADIUS = 800.0f;
constexpr float DEFAULT_ELEVATION = 120.0f;
constexpr int32_t HANDLE_RING_DEGREE = 360;
constexpr float CONSTANT_DOUBLE = 2.0f;

TextDragOverlayModifier::TextDragOverlayModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern) : pattern_(pattern)
{
    backgroundOffset_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(TEXT_DRAG_OFFSET.ConvertToPx());
    selectedBackgroundOpacity_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    shadowOpacity_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    handleOpacity_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    firstHandle_ = AceType::MakeRefPtr<PropertyRectF>(RectF(0, 0, 0, 0));
    secondHandle_ = AceType::MakeRefPtr<PropertyRectF>(RectF(0, 0, 0, 0));
    handleRadius_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    innerHandleRadius_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
    innerHandleColor_ = AceType::MakeRefPtr<PropertyColor>(Color::BLACK);
    handleColor_ = AceType::MakeRefPtr<PropertyColor>(Color::BLACK);
    selectedColor_ = AceType::MakeRefPtr<PropertyInt>(0);
    AttachProperty(backgroundOffset_);
    AttachProperty(selectedBackgroundOpacity_);
    AttachProperty(shadowOpacity_);
    AttachProperty(firstHandle_);
    AttachProperty(secondHandle_);
    AttachProperty(handleOpacity_);
    AttachProperty(handleRadius_);
    AttachProperty(innerHandleRadius_);
    AttachProperty(innerHandleColor_);
    AttachProperty(handleColor_);
    AttachProperty(selectedColor_);
}

void TextDragOverlayModifier::StartFloatingAnimate()
{
    isAnimating_ = true;
    type_ = DragAnimType::FLOATING;
    SetHandleOpacity(IsHandlesShow() ? 1.0 : 0.0);
    AnimationOption handleOption;
    handleOption.SetDuration(TEXT_FLOATING_ANIMATE_HANDLE_OPACITY_DURATION);
    handleOption.SetCurve(Curves::LINEAR);
    handleOption.SetDelay(0);
    handleOption.SetFillMode(FillMode::FORWARDS);
    auto handlePropertyCallback = [weakModifier = WeakClaim(this)]() {
        auto modifier = weakModifier.Upgrade();
        CHECK_NULL_VOID(modifier);
        modifier->SetHandleOpacity(0.0);
    };
    AnimationUtils::Animate(handleOption, handlePropertyCallback, nullptr);
    SetShadowOpacity(0.0);
    AnimationOption shadowOption;
    shadowOption.SetDuration(TEXT_ANIMATION_DURATION);
    shadowOption.SetCurve(Curves::SHARP);
    shadowOption.SetDelay(0);
    shadowOption.SetFillMode(FillMode::FORWARDS);
    auto shadowPropertyCallback = [weakModifier = WeakClaim(this)]() {
        auto modifier = weakModifier.Upgrade();
        CHECK_NULL_VOID(modifier);
        modifier->SetShadowOpacity(1.0);
    };
    AnimationUtils::Animate(shadowOption, shadowPropertyCallback, nullptr);
    StartFloatingSelBackgroundAnimate();
}

void TextDragOverlayModifier::StartFloatingSelBackgroundAnimate()
{
    SetBackgroundOffset(0);
    SetSelectedBackgroundOpacity(IsHandlesShow() ? 1.0 : 0.0);
    AnimationOption option;
    option.SetDuration(TEXT_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    option.SetDelay(0);
    auto finishFuc = [weakModifier = WeakClaim(this)]() {
        auto modifier = weakModifier.Upgrade();
        CHECK_NULL_VOID(modifier);
        modifier->SetAnimateFlag(false);
    };
    option.SetOnFinishEvent(finishFuc);
    option.SetFillMode(FillMode::FORWARDS);
    auto propertyCallback = [weakModifier = WeakClaim(this)]() {
        auto modifier = weakModifier.Upgrade();
        CHECK_NULL_VOID(modifier);
        modifier->SetBackgroundOffset(TEXT_DRAG_DEFAULT_OFFSET.ConvertToPx());
        modifier->SetSelectedBackgroundOpacity(0.0);
    };
    AnimationUtils::Animate(option, propertyCallback, option.GetOnFinishEvent());
}

void TextDragOverlayModifier::PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas& canvas)
{
    if (type_ == DragAnimType::DEFAULT) {
        return;
    }
    RSRecordingPath rsPath;
    rsPath.AddPath(path);
    rsPath.Offset(shadow.GetOffset().GetX(), shadow.GetOffset().GetY());
    Color color = shadow.GetColor();
    color = color.BlendOpacity(shadowOpacity_->Get());
    RSColor spotColor = ToRSColor(color);
    RSPoint3 planeParams = { 0.0, 0.0, shadow.GetElevation() };
    auto bounds = rsPath.GetBounds();
    RSPoint3 lightPos = { bounds.GetLeft() + bounds.GetWidth() / 2.0, bounds.GetTop() + bounds.GetHeight() / 2.0,
        DEFAULT_LIGHT_HEIGHT };
    RSColor ambientColor = ToRSColor(Color(DEFAULT_AMBIENT_COLOR));
    canvas.DrawShadowStyle(rsPath, planeParams, lightPos, DEFAULT_LIGHT_RADIUS, ambientColor, spotColor,
        RSShadowFlags::TRANSPARENT_OCCLUDER, true);
    canvas.Restore();
}

void TextDragOverlayModifier::PaintBackground(const RSPath& path, RSCanvas& canvas,
    RefPtr<TextDragPattern> textDragPattern)
{
    auto shadow = Shadow(DEFAULT_ELEVATION, {0.0, 0.0}, Color(DEFAULT_SHADOW_COLOR), ShadowStyle::OuterFloatingSM);
    PaintShadow(path, shadow, canvas);
    auto pattern = DynamicCast<TextDragPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    Color color = pattern->GetDragBackgroundColor();
    RSBrush brush;
    brush.SetColor(ToRSColor(color));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
    canvas.DetachBrush();
    if (type_ == DragAnimType::DEFAULT) {
        return;
    }
    canvas.Save();
    canvas.ClipPath(path, RSClipOp::INTERSECT, true);
    std::shared_ptr<RSPath> selPath = textDragPattern->GetSelBackgroundPath();
    RSBrush selBrush;
    Color selColor = Color::WHITE;
    if (type_ == DragAnimType::FLOATING) {
        selColor = selColor.BlendOpacity(selectedBackgroundOpacity_->Get());
    }
    selBrush.SetColor(ToRSColor(selColor));
    selBrush.SetAntiAlias(true);
    canvas.AttachBrush(selBrush);
    canvas.DrawPath(*selPath);
    canvas.DetachBrush();
    canvas.Restore();
}

void TextDragOverlayModifier::PaintHandle(RSCanvas& canvas, const RectF& handleRect, bool isFirstHandle,
    float startX, float startY)
{
    if (!isAnimating_ || type_ == DragAnimType::DEFAULT) {
        return;
    }
    if (NearZero(handleOpacity_->Get()) || NearZero(handleRect.Width())) {
        return;
    }
    auto rectTopX = (handleRect.Right() - handleRect.Left()) / CONSTANT_DOUBLE + startX;
    auto centerOffset = OffsetF(rectTopX, 0.0);
    OffsetF startPoint(0.0, 0.0);
    OffsetF endPoint(0.0, 0.0);
    float offset = backgroundOffset_->Get();
    auto outerHandleRadius = handleRadius_->Get();
    auto handleRectHeight = handleRect.Height();
    if (isFirstHandle) {
        centerOffset.SetX(centerOffset.GetX() - offset);
        centerOffset.SetY(startY - outerHandleRadius);
        startPoint.SetY(outerHandleRadius - 1.0);
        endPoint.SetY(outerHandleRadius + handleRectHeight);
    } else {
        centerOffset.SetX(centerOffset.GetX() + offset);
        centerOffset.SetY(startY + outerHandleRadius);
        startPoint.SetY(-outerHandleRadius + 1.0);
        endPoint.SetY(-outerHandleRadius - handleRectHeight);
    }
    canvas.Save();
    canvas.Translate(centerOffset.GetX(), centerOffset.GetY());
    PaintHandleRing(canvas);
    PaintHandleHold(canvas, handleRect, startPoint, endPoint);
    canvas.Restore();
}

void TextDragOverlayModifier::PaintHandleRing(RSCanvas& canvas)
{
    RSPen pen;
    pen.SetAntiAlias(true);
    Color handleColor = handleColor_->Get();
    auto handleOpacity = handleOpacity_->Get();
    handleColor = handleColor.BlendOpacity(handleOpacity);
    pen.SetColor(handleColor.GetValue());
    auto outerHandleRadius = handleRadius_->Get();
    auto innerHandleRadius = innerHandleRadius_->Get();
    pen.SetWidth(outerHandleRadius - innerHandleRadius);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    canvas.AttachPen(pen);
    auto radius = (innerHandleRadius + outerHandleRadius) / 2;
    RSPath ringPath;
    ringPath.AddArc({ -radius, -radius, radius, radius }, 0, HANDLE_RING_DEGREE);
    canvas.DrawPath(ringPath);
    canvas.DetachPen();
    Color innerHandleColor = innerHandleColor_->Get();
    innerHandleColor = innerHandleColor.BlendOpacity(handleOpacity);
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(innerHandleColor.GetValue());
    canvas.AttachBrush(brush);
    canvas.DrawCircle(RSPoint(0.0, 0.0), innerHandleRadius);
    canvas.DetachBrush();
}

void TextDragOverlayModifier::PaintHandleHold(RSCanvas& canvas, const RectF& handleRect,
    const OffsetF& startPoint, const OffsetF& endPoint)
{
    Color handleColor = handleColor_->Get();
    auto handleOpacity = handleOpacity_->Get();
    handleColor = handleColor.BlendOpacity(handleOpacity);
    RSPen linePen;
    linePen.SetAntiAlias(true);
    linePen.SetColor(handleColor.GetValue());
    linePen.SetWidth(handleRect.Width());
    linePen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    canvas.AttachPen(linePen);
    canvas.DrawLine(RSPoint(startPoint.GetX(), startPoint.GetY()), RSPoint(endPoint.GetX(), endPoint.GetY()));
    canvas.DetachPen();
}

void TextDragOverlayModifier::PaintSelBackground(RSCanvas& canvas, const RefPtr<TextDragPattern>& textDragPattern)
{
    if (type_ == DragAnimType::DEFAULT || NearZero(selectedBackgroundOpacity_->Get())) {
        return;
    }
    std::shared_ptr<RSPath> path = textDragPattern->GetSelBackgroundPath();
    float offset = isAnimating_ ? backgroundOffset_->Get() : 0.0;
    if (!NearZero(offset)) {
        path = textDragPattern->GenerateSelBackgroundPath(offset);
    }
    RSBrush selBrush;
    Color selColor = Color(selectedColor_->Get());
    selColor = selColor.BlendOpacity(selectedBackgroundOpacity_->Get());
    selBrush.SetColor(ToRSColor(selColor));
    selBrush.SetAntiAlias(true);
    canvas.AttachBrush(selBrush);
    canvas.DrawPath(*path);
    canvas.DetachBrush();
}

void TextDragOverlayModifier::onDraw(DrawingContext& context)
{
    auto pattern = DynamicCast<TextDragPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto& canvas = context.canvas;
    std::shared_ptr<RSPath> path;
    if (!isAnimating_) {
        path = pattern->GetBackgroundPath();
    } else {
        path = pattern->GenerateBackgroundPath(backgroundOffset_->Get(), 1 - selectedBackgroundOpacity_->Get());
    }
    PaintBackground(*path, canvas, pattern);
    canvas.Save();
    canvas.ClipPath(*pattern->GetClipPath(), RSClipOp::INTERSECT, true);
    auto paragraph = pattern->GetParagraph().Upgrade();
    if (paragraph) {
        paragraph->Paint(canvas, pattern->GetTextRect().GetX(), pattern->GetTextRect().GetY());
    }
    PaintImage(canvas);
    canvas.Restore();
    canvas.Save();
    canvas.ClipPath(*path, RSClipOp::INTERSECT, true);
    PaintSelBackground(canvas, pattern);
    canvas.Restore();
    if (isHandleAnimation_) {
        if (firstHandle_) {
            auto selectPosition = pattern->GetSelectPosition();
            auto rect = firstHandle_->Get();
            auto startY = rect.Top() - selectPosition.globalY_;
            PaintHandle(canvas, firstHandle_->Get(), true, rect.Left() - selectPosition.globalX_, startY);
        }
        if (secondHandle_) {
            auto selectPosition = pattern->GetSelectPosition();
            auto rect = secondHandle_->Get();
            auto startY = rect.Bottom() - selectPosition.globalY_;
            PaintHandle(canvas, secondHandle_->Get(), false, rect.Left() - selectPosition.globalX_, startY);
        }
    }
}

void TextDragOverlayModifier::PaintImage(RSCanvas& canvas)
{
    auto pattern = DynamicCast<TextDragPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    size_t index = 0;
    auto contentOffset = pattern->GetContentOffset();
    auto imageChildren = pattern->GetImageChildren();
    auto rectsForPlaceholders = pattern->GetRectsForPlaceholders();
    for (const auto& child : imageChildren) {
        auto rect = rectsForPlaceholders.at(index);
        auto offset = OffsetF(rect.Left(), rect.Top()) - contentOffset;
        auto imageChild = DynamicCast<ImagePattern>(child->GetPattern());
        if (imageChild) {
            RectF imageRect(offset.GetX(), offset.GetY(), rect.Width(), rect.Height());
            auto canvasImage = imageChild->GetCanvasImage();
            CHECK_NULL_VOID(canvasImage);
            auto pixelMapImage = DynamicCast<PixelMapImage>(canvasImage);
            CHECK_NULL_VOID(pixelMapImage);
            pixelMapImage->DrawRect(canvas, ToRSRect(imageRect));
        }
        ++index;
    }
}

void TextDragOverlayModifier::SetBackgroundOffset(float offset)
{
    backgroundOffset_->Set(offset);
}

void TextDragOverlayModifier::SetSelectedBackgroundOpacity(float offset)
{
    selectedBackgroundOpacity_->Set(offset);
}
} // namespace OHOS::Ace::NG
