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

#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_overlay_modifier.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/rect.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
void RichEditorDragOverlayModifier::onDraw(DrawingContext& context)
{
    auto pattern = DynamicCast<RichEditorDragPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto& canvas = context.canvas;
    Color color(TEXT_DRAG_COLOR_BG);
    RSBrush brush;
    brush.SetColor(ToRSColor(color));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    if (!isAnimating_) {
        canvas.DrawPath(*pattern->GetBackgroundPath());
    } else {
        canvas.DrawPath(*pattern->GenerateBackgroundPath(backgroundOffset_->Get()));
    }
    canvas.ClipPath(*pattern->GetClipPath(), RSClipOp::INTERSECT, true);
    auto hostPattern = hostPattern_.Upgrade();
    CHECK_NULL_VOID(hostPattern);

    auto richEditor = DynamicCast<RichEditorPattern>(hostPattern);
    if (richEditor) {
        OffsetF offset = { pattern->GetTextRect().GetX(), pattern->GetTextRect().GetY() };
        for (auto&& info : richEditor->GetParagraphs()) {
            info.paragraph->Paint(canvas, offset.GetX(), offset.GetY());
            offset.AddY(info.paragraph->GetHeight());
        }
    } else {
        auto&& paragraph = hostPattern->GetParagraph();
        paragraph->Paint(canvas, pattern->GetTextRect().GetX(), pattern->GetTextRect().GetY());
    }
    PaintImage(context);
}

void RichEditorDragOverlayModifier::PaintImage(DrawingContext& context)
{
    auto pattern = DynamicCast<RichEditorDragPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto canvas = context.canvas;
    size_t index = 0;
    auto imageChildren = pattern->GetImageChildren();
    auto rectsForPlaceholders = pattern->GetRectsForPlaceholders();
    for (const auto& child : imageChildren) {
        auto rect = rectsForPlaceholders.at(index);
        auto offset = OffsetF(rect.Left(), rect.Top()) + pattern->GetTextRect().GetOffset();
        auto imageChild = DynamicCast<ImagePattern>(child->GetPattern());
        if (imageChild) {
            auto pixelMap = child->GetRenderContext()->GetThumbnailPixelMap();
            CHECK_NULL_VOID(pixelMap);
            auto canvasImage = CanvasImage::Create(pixelMap);
            CHECK_NULL_VOID(canvasImage);
            auto layoutProperty = imageChild->GetLayoutProperty<ImageLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            const auto& marginProperty = layoutProperty->GetMarginProperty();
            float marginTop = 0.0f;
            float marginLeft = 0.0f;
            if (marginProperty) {
                marginLeft =
                    marginProperty->left.has_value() ? marginProperty->left->GetDimension().ConvertToPx() : 0.0f;
                marginTop = marginProperty->top.has_value() ? marginProperty->top->GetDimension().ConvertToPx() : 0.0f;
            }
            RectF imageRect(
                offset.GetX() + marginLeft, offset.GetY() + marginTop, pixelMap->GetWidth(), pixelMap->GetHeight());
            CHECK_NULL_VOID(canvasImage);
            auto pixelMapImage = DynamicCast<PixelMapImage>(canvasImage);
            CHECK_NULL_VOID(pixelMapImage);
            pixelMapImage->DrawRect(canvas, ToRSRect(imageRect));
        }
        ++index;
    }
    canvas.DetachBrush();
}
} // namespace OHOS::Ace::NG
