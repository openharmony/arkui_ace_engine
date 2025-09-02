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

#include "core/components_ng/pattern/rich_editor/rich_editor_paint_method.h"

#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_overlay_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_content_pattern.h"

namespace OHOS::Ace::NG {
RichEditorPaintMethod::RichEditorPaintMethod(const WeakPtr<Pattern>& pattern, const ParagraphManager* pManager,
    float baselineOffset, const RefPtr<TextContentModifier>& contentMod, const RefPtr<TextOverlayModifier>& overlayMod)
    : TextPaintMethod(pattern, baselineOffset, contentMod, overlayMod), pManager_(pManager)
{}

void RichEditorPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto richEditorPattern = DynamicCast<RichEditorPattern>(GetPattern().Upgrade());
    if (richEditorPattern) {
        auto overlayMod = DynamicCast<RichEditorOverlayModifier>(GetOverlayModifier(paintWrapper));
        CHECK_NULL_VOID(overlayMod);
        overlayMod->SetPrintOffset(richEditorPattern->GetTextRect().GetOffset());
        overlayMod->SetTextHeight(richEditorPattern->GetTextRect().Height());
        overlayMod->SetScrollOffset(richEditorPattern->GetScrollOffset());
        overlayMod->ChangeOverlay();
        if (!richEditorPattern->HasFocus()) {
            overlayMod->UpdateScrollBar(paintWrapper);
        } else {
            auto geometryNode = paintWrapper->GetGeometryNode();
            CHECK_NULL_VOID(geometryNode);
            auto frameSize = geometryNode->GetFrameSize();
            overlayMod->SetFrameSize(frameSize);
            overlayMod->UpdateScrollBar(paintWrapper);
            overlayMod->SetIsClip(false);
        }
        return;
    }
    UpdateContentOverlayModifier(paintWrapper);
}
void RichEditorPaintMethod::UpdateContentOverlayModifier(PaintWrapper* paintWrapper)
{
    auto contentPattern = DynamicCast<RichEditorContentPattern>(GetPattern().Upgrade());
    CHECK_NULL_VOID(contentPattern);
    auto richEditorPattern = contentPattern->GetParentPattern();
    CHECK_NULL_VOID(richEditorPattern);
    TextPaintMethod::UpdateOverlayModifier(paintWrapper);
    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(GetOverlayModifier(paintWrapper));
    CHECK_NULL_VOID(overlayMod);
    overlayMod->SetPrintOffset(richEditorPattern->GetTextRect().GetOffset());
    overlayMod->SetTextHeight(richEditorPattern->GetTextRect().Height());
    overlayMod->SetScrollOffset(richEditorPattern->GetScrollOffset());
    SetPreviewTextDecoration(paintWrapper);
    if (!richEditorPattern->HasFocus()) {
        overlayMod->UpdateScrollBar(paintWrapper);
        overlayMod->SetCaretVisible(false);
        overlayMod->SetFloatingCaretVisible(false);
        const auto& selection = richEditorPattern->GetTextSelector();
        std::vector<RectF> selectedRects;
        if (richEditorPattern->GetTextContentLength() > 0 && selection.GetTextStart() != selection.GetTextEnd()) {
            auto contentRect = richEditorPattern->GetTextContentRect();
            auto rects = pManager_->GetRichEditorBoxesForSelect(selection.GetTextStart(), selection.GetTextEnd());
            selectedRects = CalculateSelectedRect(rects, contentRect.Width());
        }
        overlayMod->SetSelectedRects(selectedRects);
        return;
    }
    overlayMod->SetShowSelect(richEditorPattern->GetShowSelect());
    overlayMod->SetSelectedColor(richEditorPattern->GetSelectedBackgroundColor().GetValue());
    SetCaretState(paintWrapper);
    std::vector<RectF> selectedRects;
    const auto& selection = richEditorPattern->GetTextSelector();
    auto contentRect = richEditorPattern->GetTextContentRect();
    if (richEditorPattern->GetTextContentLength() > 0 && selection.GetTextStart() != selection.GetTextEnd()) {
        auto rects = pManager_->GetRichEditorBoxesForSelect(selection.GetTextStart(), selection.GetTextEnd());
        selectedRects = CalculateSelectedRect(rects, contentRect.Width());
    }
    overlayMod->SetContentRect(contentRect);
    overlayMod->SetSelectedRects(selectedRects);
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    overlayMod->SetFrameSize(frameSize);
    overlayMod->UpdateScrollBar(paintWrapper);
    overlayMod->SetIsClip(false);
}

void RichEditorPaintMethod::SetCaretState(PaintWrapper* paintWrapper)
{
    auto contentPattern = DynamicCast<RichEditorContentPattern>(GetPattern().Upgrade());
    CHECK_NULL_VOID(contentPattern);
    auto richEditorPattern = contentPattern->GetParentPattern();
    CHECK_NULL_VOID(richEditorPattern);
    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(GetOverlayModifier(paintWrapper));
    CHECK_NULL_VOID(overlayMod);
    auto caretVisible = richEditorPattern->GetCaretVisible();
    const auto& floatingCaretState = richEditorPattern->GetFloatingCaretState();
    overlayMod->SetCaretVisible(caretVisible);
    overlayMod->SetOriginCaretVisible(floatingCaretState.isOriginCaretVisible);
    overlayMod->SetFloatingCaretVisible(floatingCaretState.isFloatingCaretVisible);
    overlayMod->SetOriginCaretColor(floatingCaretState.originCaretColor.GetValue());
    overlayMod->SetCaretColor(richEditorPattern->GetCaretColor().GetValue());
    overlayMod->SetCaretWidth(richEditorPattern->GetCaretWidth());
    SetCaretOffsetAndHeight(paintWrapper);
}

std::vector<RectF> RichEditorPaintMethod::CalculateSelectedRect(
    const std::vector<std::pair<std::vector<RectF>, ParagraphStyle>>& selectedRects, float contentWidth)
{
    const float blankWidth = TextBase::GetSelectedBlankLineWidth();
    std::vector<RectF> result;
    float lastLineBottom = -1.0f;
    for (const auto& info : selectedRects) {
        auto rects = info.first;
        TextBase::CalculateSelectedRectEx(rects, lastLineBottom);
        auto textAlign = TextBase::CheckTextAlignByDirection(info.second.align, info.second.direction);
        for (auto& rect : rects) {
            TextBase::UpdateSelectedBlankLineRect(rect, blankWidth, textAlign, contentWidth);
        }
        result.insert(result.end(), rects.begin(), rects.end());
        if (!result.empty()) {
            lastLineBottom = result.back().Bottom();
        }
    }
    return result;
}

void RichEditorPaintMethod::SetPreviewTextDecoration(PaintWrapper* paintWrapper)
{
    auto contentPattern = DynamicCast<RichEditorContentPattern>(GetPattern().Upgrade());
    CHECK_NULL_VOID(contentPattern);
    auto richEditorPattern = contentPattern->GetParentPattern();
    CHECK_NULL_VOID(richEditorPattern);
    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(GetOverlayModifier(paintWrapper));
    CHECK_NULL_VOID(overlayMod);
    overlayMod->SetPreviewTextDecorationColor(richEditorPattern->GetPreviewTextDecorationColor());
    overlayMod->SetPreviewTextUnderlineWidth(richEditorPattern->GetPreviewTextUnderlineWidth());
    overlayMod->SetShowPreviewTextDecoration(richEditorPattern->IsPreviewTextInputting());
    overlayMod->SetPreviewTextStyle(richEditorPattern->GetPreviewTextStyle());
}

void RichEditorPaintMethod::SetCaretOffsetAndHeight(PaintWrapper* paintWrapper)
{
    auto contentPattern = DynamicCast<RichEditorContentPattern>(GetPattern().Upgrade());
    CHECK_NULL_VOID(contentPattern);
    auto richEditorPattern = contentPattern->GetParentPattern();
    CHECK_NULL_VOID(richEditorPattern);
    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(GetOverlayModifier(paintWrapper));
    CHECK_NULL_VOID(overlayMod);
    auto [caretOffset, caretHeight] = richEditorPattern->CalculateCaretOffsetAndHeight();
    auto lastOffset = overlayMod->GetCaretOffset();
    auto lastCaretY = lastOffset.GetY() + overlayMod->GetCaretHeight() - richEditorPattern->GetLastTextRect().GetY();
    auto curCaretY = caretOffset.GetY() + caretHeight - richEditorPattern->GetTextRect().GetY();
    overlayMod->SetCaretOffsetAndHeight(caretOffset, caretHeight);
    const auto& floatingCaretState = richEditorPattern->GetFloatingCaretState();
    if (floatingCaretState.touchMoveOffset && !overlayMod->GetFloatCaretLanding()) {
        overlayMod->SetFloatingCaretOffset(OffsetF(floatingCaretState.touchMoveOffset->GetX(), caretOffset.GetY()));
    }
    if (richEditorPattern->IsTriggerAvoidOnCaretAvoidMode() || !NearEqual(lastCaretY, curCaretY) ||
        !NearEqual(lastOffset.GetX(), caretOffset.GetX())) {
        richEditorPattern->NotifyCaretChange();
        richEditorPattern->ResetTriggerAvoidFlagOnCaretChange();
    }
    richEditorPattern->ChangeLastRichTextRect();
}

void RichEditorPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    auto contentMod = DynamicCast<RichEditorContentModifier>(GetContentModifier(paintWrapper));
    CHECK_NULL_VOID(contentMod);
    TextPaintMethod::UpdateContentModifier(paintWrapper);
    auto contentPattern = DynamicCast<RichEditorContentPattern>(GetPattern().Upgrade());
    CHECK_NULL_VOID(contentPattern);
    auto richEditorPattern = contentPattern->GetParentPattern();
    CHECK_NULL_VOID(richEditorPattern);
    auto richtTextOffset = contentPattern->GetTextRect().GetOffset();
    contentMod->SetRichTextRectX(richtTextOffset.GetX());
    contentMod->SetRichTextRectY(richtTextOffset.GetY());

    const auto& geometryNode = paintWrapper->GetGeometryNode();
    auto frameSize = geometryNode->GetPaddingSize();
    OffsetF paddingOffset = geometryNode->GetPaddingOffset() - geometryNode->GetFrameOffset();
    contentMod->SetClipOffset(paddingOffset);
    contentMod->SetClipSize(frameSize);
    contentMod->ContentChange();
}
} // namespace OHOS::Ace::NG
