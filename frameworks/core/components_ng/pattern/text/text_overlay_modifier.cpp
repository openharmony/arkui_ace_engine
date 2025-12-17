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

#include "core/components_ng/pattern/text/text_overlay_modifier.h"

#include "ui/base/utils/utils.h"

#include "core/common/container.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
TextOverlayModifier::TextOverlayModifier(const WeakPtr<Pattern>& pattern) : pattern_(pattern)
{
    paintOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    AttachProperty(paintOffset_);
    cursorColor_ = AceType::MakeRefPtr<PropertyInt>(0);
    AttachProperty(cursorColor_);
    selectedColor_ = AceType::MakeRefPtr<PropertyInt>(0);
    selectedUrlColor_ = AceType::MakeRefPtr<PropertyInt>(0);
    AttachProperty(selectedColor_);
    changeSelectedRects_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(changeSelectedRects_);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        isClip_ = MakeRefPtr<PropertyBool>(true);
    } else {
        isClip_ = MakeRefPtr<PropertyBool>(false);
    }
    AttachProperty(isClip_);
    showSelect_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(showSelect_);
    highlightOpacityAnimation_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(1.0);
    AttachProperty(highlightOpacityAnimation_);
}

void TextOverlayModifier::onDraw(DrawingContext& drawingContext)
{
    onDrawHighlight(drawingContext);
    if (!showSelect_->Get()) {
        return;
    }
    drawingContext.canvas.Save();
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(selectedColor_->Get());
    drawingContext.canvas.AttachBrush(brush);

    if (contentRect_.has_value() && isClip_ && isClip_->Get()) {
        drawingContext.canvas.ClipRect(ToRSRect(contentRect_.value()), RSClipOp::INTERSECT);
    }

    auto paintOffset = paintOffset_->Get();
    for (const auto& selectedRect : selectedRects_) {
        auto rect = selectedRect;
        if (contentRect_.has_value() && !isSingleLineMode_) {
            if (rect.Right() > contentRect_.value().Right()) {
                rect.SetWidth(std::max(contentRect_.value().Right() - rect.Left(), 0.0f));
            }
        }
        drawingContext.canvas.DrawRect(RSRect(paintOffset.GetX() + rect.Left(), paintOffset.GetY() + rect.Top(),
            paintOffset.GetX() + rect.Right(), paintOffset.GetY() + rect.Bottom()));
    }
    drawingContext.canvas.DetachBrush();
    CHECK_NULL_VOID(selectedUrlColor_);
    brush.SetColor(selectedUrlColor_->Get());
    drawingContext.canvas.AttachBrush(brush);
    for (const auto& selectedRect : selectedUrlRects_) {
        auto rect = selectedRect;
        if (contentRect_.has_value()) {
            if (rect.Right() > contentRect_.value().Right()) {
                rect.SetWidth(std::max(contentRect_.value().Right() - rect.Left(), 0.0f));
            }
        }
        drawingContext.canvas.DrawRect(RSRect(paintOffset.GetX() + rect.Left(), paintOffset.GetY() + rect.Top(),
            paintOffset.GetX() + rect.Right(), paintOffset.GetY() + rect.Bottom()));
    }
    drawingContext.canvas.DetachBrush();
    drawingContext.canvas.Restore();
}

void TextOverlayModifier::onDrawHighlight(DrawingContext& drawingContext)
{
    auto textPattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textPattern);
    const auto& selection = textPattern->GetTextSelector();
    CHECK_NULL_VOID(selection.highlightStart.has_value() && selection.highlightEnd.has_value());
    CHECK_NULL_VOID(selection.highlightStart.value() != selection.highlightEnd.value());
    auto pManager = textPattern->GetParagraphManager();
    CHECK_NULL_VOID(pManager);

    auto paragraphsRects = pManager->GetTextBoxesForSelect(
        selection.highlightStart.has_value(), selection.highlightStart.value());
    CHECK_NULL_VOID(!paragraphsRects.empty());

    auto pipeline = textPattern->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    CHECK_NULL_VOID(paintOffset_);
    CHECK_NULL_VOID(highlightOpacityAnimation_);
    auto& canvas = drawingContext.canvas;
    canvas.Save();
    RSBrush brush;
    brush.SetAntiAlias(true);
    auto colorValue =
        Color(textOverlayTheme->GetHighlightColor()).BlendOpacity(highlightOpacityAnimation_->Get()).GetValue();
    brush.SetColor(colorValue);
    auto paintOffset = paintOffset_->Get();
    canvas.AttachBrush(brush);
    for (const auto& selectedRect : paragraphsRects) {
        auto rects = selectedRect.first;
        for (const auto& rect : rects) {
            auto rectValue = rect;
            if (contentRect_.has_value() && rectValue.Right() > contentRect_.value().Right()) {
                rectValue.SetWidth(std::max(contentRect_.value().Right() - rect.Left(), 0.0f));
            }
            canvas.DrawRect(RSRect(paintOffset.GetX() + rectValue.Left(), paintOffset.GetY() + rectValue.Top(),
                paintOffset.GetX() + rectValue.Right(), paintOffset.GetY() + rectValue.Bottom()));
        }
    }

    canvas.DetachBrush();
    canvas.Restore();
}

void TextOverlayModifier::SetSelectedForegroundColorAndRects(
    const std::vector<RectF>& selectedUrlRects, uint32_t selectedUrlColor)
{
    selectedUrlRects_ = selectedUrlRects;
    selectedUrlColor_->Set(static_cast<int32_t>(selectedUrlColor));
}

void TextOverlayModifier::ClearSelectedForegroundColorAndRects()
{
    selectedUrlRects_.clear();
}

void TextOverlayModifier::SetPrintOffset(const OffsetF& paintOffset)
{
    CHECK_NULL_VOID(paintOffset_);
    paintOffset_->Set(paintOffset);
}

void TextOverlayModifier::SetCursorColor(uint32_t cursorColor)
{
    CHECK_NULL_VOID(cursorColor_);
    cursorColor_->Set(static_cast<int32_t>(cursorColor));
}

void TextOverlayModifier::SetSelectedColor(uint32_t selectedColor)
{
    CHECK_NULL_VOID(selectedColor_);
    selectedColor_->Set(static_cast<int32_t>(selectedColor));
}

void TextOverlayModifier::SetSelectedRects(const std::vector<RectF>& selectedRects)
{
    changeSelectedRects_->Set(!changeSelectedRects_->Get());
    selectedRects_ = selectedRects;
}

bool TextOverlayModifier::IsSelectedRectsChanged(const std::vector<RectF>& selectedRects)
{
    bool result = false;
    if (selectedRects.size() == selectedRects_.size()) {
        for (unsigned int ii = 0; ii < selectedRects.size(); ii++) {
            if (selectedRects[ii] != selectedRects_[ii]) {
                result = true;
                break;
            }
        }
    } else {
        result = true;
    }
    return result;
}
void TextOverlayModifier::SetShowSelect(bool value)
{
    showSelect_->Set(value);
}

void TextOverlayModifier::SetSingleLine(bool value)
{
    isSingleLineMode_ = value;
}

std::vector<RectF> TextOverlayModifier::GetSelectedRects() const
{
    return selectedRects_;
}
} // namespace OHOS::Ace::NG