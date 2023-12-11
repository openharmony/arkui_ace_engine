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

#include "core/components_ng/pattern/rich_editor/rich_editor_overlay_modifier.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RichEditorOverlayModifier::RichEditorOverlayModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern,
    const WeakPtr<ScrollBarOverlayModifier>& scrollbarOverlayModifier, WeakPtr<ScrollEdgeEffect>&& edgeEffect)
    : TextOverlayModifier(), pattern_(pattern), edgeEffect_(edgeEffect),
      scrollBarOverlayModifier_(scrollbarOverlayModifier)
{
    caretVisible_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(caretVisible_);
    caretOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    AttachProperty(caretOffset_);
    caretHeight_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    AttachProperty(caretHeight_);
    caretWidth_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    AttachProperty(caretWidth_);
    caretColor_ = AceType::MakeRefPtr<PropertyInt>(0);
    AttachProperty(caretColor_);
    scrollOffset_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    AttachProperty(scrollOffset_);
    frameSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    AttachProperty(frameSize_);
    scrollBarOpacityType_ = AceType::MakeRefPtr<PropertyInt>(-1);
    AttachProperty(scrollBarOpacityType_);
    textHeight_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    AttachProperty(textHeight_);
}

void RichEditorOverlayModifier::SetCaretOffsetAndHeight(const OffsetF& cursorOffset, float height)
{
    caretOffset_->Set(cursorOffset);
    if (height > 0.0f) {
        caretHeight_->Set(height);
    }
}

void RichEditorOverlayModifier::SetCaretColor(uint32_t caretColor)
{
    CHECK_NULL_VOID(caretColor_);
    caretColor_->Set(static_cast<int32_t>(caretColor));
}

void RichEditorOverlayModifier::SetCaretWidth(float width)
{
    if (width <= 0.0f) {
        return;
    }
    caretWidth_->Set(width);
}

float RichEditorOverlayModifier::GetCaretWidth() const
{
    return caretWidth_->Get();
}

void RichEditorOverlayModifier::SetCaretVisible(bool value)
{
    caretVisible_->Set(value);
}

void RichEditorOverlayModifier::SetScrollOffset(float value)
{
    scrollOffset_->Set(value);
}

void RichEditorOverlayModifier::SetScrollBarOpacityType(int32_t value)
{
    scrollBarOpacityType_->Set(value);
}

void RichEditorOverlayModifier::SetTextHeight(float value)
{
    textHeight_->Set(value);
}

void RichEditorOverlayModifier::SetFrameSize(const SizeF& value)
{
    frameSize_->Set(value);
}

float RichEditorOverlayModifier::GetCaretHeight() const
{
    return caretHeight_->Get();
}

OffsetF RichEditorOverlayModifier::GetCaretOffset() const
{
    return caretOffset_->Get();
}

void RichEditorOverlayModifier::PaintCaret(DrawingContext& drawingContext) const
{
    if (!caretVisible_->Get()) {
        return;
    }
    auto offset = caretOffset_->Get();
    drawingContext.canvas.Save();
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(caretColor_->Get());
    drawingContext.canvas.AttachBrush(brush);

    if (NearEqual(offset.GetX(), contentRect_.value().Right())) {
        drawingContext.canvas.DrawRect(RSRect(
            offset.GetX() - caretWidth_->Get(), offset.GetY(), offset.GetX(), offset.GetY() + caretHeight_->Get()));
    } else {
        drawingContext.canvas.DrawRect(RSRect(
            offset.GetX(), offset.GetY(), offset.GetX() + caretWidth_->Get(), offset.GetY() + caretHeight_->Get()));
    }

    drawingContext.canvas.DetachBrush();
    drawingContext.canvas.Restore();
}

void RichEditorOverlayModifier::PaintScrollBar(DrawingContext& context)
{
    auto scrollBarOverlayModifier = scrollBarOverlayModifier_.Upgrade();
    CHECK_NULL_VOID(scrollBarOverlayModifier);
    scrollBarOverlayModifier->onDraw(context);
}

void RichEditorOverlayModifier::PaintEdgeEffect(const SizeF& frameSize, RSCanvas& canvas)
{
    auto edgeEffect = edgeEffect_.Upgrade();
    CHECK_NULL_VOID(edgeEffect);
    edgeEffect->Paint(canvas, frameSize, { 0.0f, 0.0f });
}

void RichEditorOverlayModifier::onDraw(DrawingContext& drawingContext)
{
    if (!showSelect_->Get()) {
        PaintScrollBar(drawingContext);
        PaintEdgeEffect(frameSize_->Get(), drawingContext.canvas);
        return;
    }
    drawingContext.canvas.Save();
    if (contentRect_.has_value()) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto richEditorTheme = pipeline->GetTheme<RichEditorTheme>();
        auto defaultCaretHeight = richEditorTheme->GetDefaultCaretHeight().ConvertToPx();
        if (contentRect_->Height() < defaultCaretHeight) {
            contentRect_->SetHeight(defaultCaretHeight);
        }
        drawingContext.canvas.ClipRect(ToRSRect(contentRect_.value()), RSClipOp::INTERSECT);
    }
    PaintCaret(drawingContext);
    TextOverlayModifier::onDraw(drawingContext);
    drawingContext.canvas.Restore();
    PaintScrollBar(drawingContext);
    PaintEdgeEffect(frameSize_->Get(), drawingContext.canvas);
}

void RichEditorOverlayModifier::UpdateScrollBar(PaintWrapper* paintWrapper)
{
    auto richEditorPattern = AceType::DynamicCast<RichEditorPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(richEditorPattern);
    auto scrollBar = richEditorPattern->GetScrollControllerBar();
    if (!scrollBar || !scrollBar->NeedPaint()) {
        return;
    }
    auto scrollBarOverlayModifier = scrollBarOverlayModifier_.Upgrade();
    CHECK_NULL_VOID(scrollBarOverlayModifier);
    if (scrollBar->GetPositionModeUpdate()) {
        scrollBarOverlayModifier->SetPositionMode(scrollBar->GetPositionMode());
    }
    SetScrollBarOpacityType(static_cast<int32_t>(scrollBar->GetOpacityAnimationType()));
    scrollBarOverlayModifier->StartBarAnimation(scrollBar->GetHoverAnimationType(),
        scrollBar->GetOpacityAnimationType(), scrollBar->GetNeedAdaptAnimation(), scrollBar->GetActiveRect());
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBarOverlayModifier->SetBarColor(scrollBar->GetForegroundColor());
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
}
} // namespace OHOS::Ace::NG
