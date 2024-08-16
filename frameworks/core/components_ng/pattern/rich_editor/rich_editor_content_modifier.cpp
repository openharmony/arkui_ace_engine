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

#include "core/components_ng/pattern/rich_editor/rich_editor_content_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/render/drawing.h"
#include "base/log/ace_trace.h"

namespace OHOS::Ace::NG {
RichEditorContentModifier::RichEditorContentModifier(const std::optional<TextStyle>& textStyle,
    const ParagraphManager* pManager, const WeakPtr<OHOS::Ace::NG::Pattern>& pattern)
    : TextContentModifier(textStyle, pattern), pManager_(pManager), pattern_(pattern)
{
    auto richEditorPattern = AceType::DynamicCast<RichEditorPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(richEditorPattern);
    richTextRectX_ = AceType::MakeRefPtr<PropertyFloat>(richEditorPattern->GetTextRect().GetX());
    AttachProperty(richTextRectX_);
    richTextRectY_ = AceType::MakeRefPtr<PropertyFloat>(richEditorPattern->GetTextRect().GetY());
    AttachProperty(richTextRectY_);
    clipOffset_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF());
    AttachProperty(clipOffset_);
    clipSize_ = AceType::MakeRefPtr<AnimatablePropertySizeF>(SizeF());
    AttachProperty(clipSize_);
}

void RichEditorContentModifier::onDraw(DrawingContext& drawingContext)
{
    ACE_SCOPED_TRACE("RichEditorContentOnDraw");
    CHECK_NULL_VOID(pManager_);
    auto richEditorPattern = AceType::DynamicCast<RichEditorPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(richEditorPattern);
    auto& canvas = drawingContext.canvas;
    canvas.Save();
    auto contentRect = richEditorPattern->GetTextContentRect();
    RSRect clipInnerRect = RSRect(contentRect.GetX(), contentRect.GetY(), contentRect.GetX() + contentRect.Width(),
        contentRect.GetY() + contentRect.Height());
    canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    auto&& paragraphs = pManager_->GetParagraphs();
    auto offset = richEditorPattern->GetTextRect().GetOffset();
    for (auto&& info : paragraphs) {
        info.paragraph->Paint(drawingContext.canvas, offset.GetX(), offset.GetY());
        offset.AddY(info.paragraph->GetHeight());
    }
    canvas.Restore();

    auto clipOffset = clipOffset_->Get();
    auto size = clipSize_->Get();
    auto clipRect = RSRect(
        clipOffset.GetX(), clipOffset.GetY(), clipOffset.GetX() + size.Width(), clipOffset.GetY() + size.Height());
    drawingContext.canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
    PaintCustomSpan(drawingContext);
}

void RichEditorContentModifier::PaintCustomSpan(DrawingContext& drawingContext)
{
    CHECK_NULL_VOID(pManager_);
    auto richEditorPattern = AceType::DynamicCast<RichEditorPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(richEditorPattern);
    auto offset = richEditorPattern->GetTextRect().GetOffset();
    const auto& rectsForPlaceholders = richEditorPattern->GetRectsForPlaceholders();
    auto customSpanPlaceholderInfo = richEditorPattern->GetCustomSpanPlaceholderInfo();
    for (auto& customSpanPlaceholder : customSpanPlaceholderInfo) {
        if (!customSpanPlaceholder.onDraw || pManager_->GetParagraphs().empty()) {
            continue;
        }
        auto index = customSpanPlaceholder.customSpanIndex;
        const auto& rect = rectsForPlaceholders.at(index);
        auto lineMetrics = pManager_->GetLineMetricsByRectF(rect, customSpanPlaceholder.paragraphIndex);
        CustomSpanOptions customSpanOptions;
        customSpanOptions.x = static_cast<double>(rect.Left()) + offset.GetX();
        customSpanOptions.lineTop = lineMetrics.y + offset.GetY();
        customSpanOptions.lineBottom = customSpanOptions.lineTop + lineMetrics.height;
        customSpanOptions.baseline = customSpanOptions.lineTop + lineMetrics.ascender;
        customSpanPlaceholder.onDraw(drawingContext, customSpanOptions);
    }
}
} // namespace OHOS::Ace::NG
