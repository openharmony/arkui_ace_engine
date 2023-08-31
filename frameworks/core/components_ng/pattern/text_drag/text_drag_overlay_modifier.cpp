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

namespace OHOS::Ace::NG {
constexpr int32_t TEXT_ANIMATION_DURATION = 300;
TextDragOverlayModifier::TextDragOverlayModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern) : pattern_(pattern)
{
    backgroundOffset_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(TEXT_DRAG_OFFSET.ConvertToPx());
    AttachProperty(backgroundOffset_);
}

void TextDragOverlayModifier::onDraw(DrawingContext& context)
{
    auto pattern = DynamicCast<TextDragPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto canvas = context.canvas;
    Color color(TEXT_DRAG_COLOR_BG);
    RSBrush brush;
    brush.SetColor(ToRSColor(color));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
#ifdef NEW_SKIA
    if (!isAnimating_) {
        canvas.DrawPath(*pattern->GetBackgroundPath());
    } else {
        canvas.DrawPath(*pattern->GenerateBackgroundPath(backgroundOffset_->Get()));
    }
#else
    if (!isAnimating_) {
        canvas.DrawPath(*pattern->GetBackgroundPath());
    } else {
        canvas.DrawPath(*pattern->GenerateBackgroundPath(backgroundOffset_->Get()));
    }
    canvas.ClipPath(*pattern->GetClipPath(), RSClipOp::INTERSECT, true);
#endif
    auto&& paragraph = pattern->GetParagraph();
    if (std::holds_alternative<RefPtr<Paragraph>>(paragraph)) {
        auto paragraphPtr = std::get<RefPtr<Paragraph>>(paragraph);
        paragraphPtr->Paint(canvas, pattern->GetTextRect().GetX(), pattern->GetTextRect().GetY());
    } else {
        auto rsParagraph = std::get<std::shared_ptr<RSParagraph>>(paragraph);
        rsParagraph->Paint(&canvas, pattern->GetTextRect().GetX(), pattern->GetTextRect().GetY());
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

void TextDragOverlayModifier::StartAnimate()
{
    isAnimating_ = true;
    backgroundOffset_->Set(0);
    AnimationOption option;
    option.SetDuration(TEXT_ANIMATION_DURATION);
    option.SetCurve(Curves::EASE_OUT);
    option.SetDelay(0);
    option.SetOnFinishEvent([this]() { isAnimating_ = false; });
    AnimationUtils::Animate(
        option, [this]() { SetBackgroundOffset(TEXT_DRAG_OFFSET.ConvertToPx()); }, option.GetOnFinishEvent());
}

void TextDragOverlayModifier::SetBackgroundOffset(float offset)
{
    backgroundOffset_->Set(offset);
}
} // namespace OHOS::Ace::NG
