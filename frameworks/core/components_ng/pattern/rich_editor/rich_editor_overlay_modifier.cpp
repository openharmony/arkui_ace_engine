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

#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RichEditorOverlayModifier::RichEditorOverlayModifier() : TextOverlayModifier()
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

void RichEditorOverlayModifier::SetCaretVisible(bool value)
{
    caretVisible_->Set(value);
}

float RichEditorOverlayModifier::GetCareHeight() const
{
    return caretHeight_->Get();
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

    drawingContext.canvas.DrawRect(
        RSRect(offset.GetX(), offset.GetY(), offset.GetX() + caretWidth_->Get(), offset.GetY() + caretHeight_->Get()));

    drawingContext.canvas.DetachBrush();
    drawingContext.canvas.Restore();
}

void RichEditorOverlayModifier::onDraw(DrawingContext& drawingContext)
{
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
}
} // namespace OHOS::Ace::NG
