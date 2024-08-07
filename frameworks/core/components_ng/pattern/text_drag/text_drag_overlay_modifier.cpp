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
#include "core/components/text/text_theme.h"

namespace OHOS::Ace::NG {
constexpr float DEFAULT_LIGHT_HEIGHT = 600.0f;
constexpr uint32_t DEFAULT_AMBIENT_COLOR = 0X0A000000;
constexpr float DEFAULT_SHADOW_COLOR = 0x33000000;
constexpr float DEFAULT_LIGHT_RADIUS = 800.0f;
constexpr float DEFAULT_ELEVATION = 120.0f;

TextDragOverlayModifier::TextDragOverlayModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern) : pattern_(pattern)
{
    backgroundOffset_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(TEXT_DRAG_OFFSET.ConvertToPx());
    selectedBackgroundOpacity_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    shadowOpacity_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    AttachProperty(backgroundOffset_);
    AttachProperty(selectedBackgroundOpacity_);
    AttachProperty(shadowOpacity_);
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
    canvas.ClipPath(*pattern->GetClipPath(), RSClipOp::INTERSECT, true);
    auto paragraph = pattern->GetParagraph().Upgrade();
    if (paragraph) {
        paragraph->Paint(canvas, pattern->GetTextRect().GetX(), pattern->GetTextRect().GetY());
    }

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
