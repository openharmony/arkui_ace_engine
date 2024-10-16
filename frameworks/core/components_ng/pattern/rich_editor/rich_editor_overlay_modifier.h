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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_OVERLAY_MODIFIER_H

#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar_overlay_modifier.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/text/text_overlay_modifier.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace::NG {
class RichEditorOverlayModifier : public TextOverlayModifier {
    DECLARE_ACE_TYPE(RichEditorOverlayModifier, TextOverlayModifier)

public:
    RichEditorOverlayModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern,
        const WeakPtr<ScrollBarOverlayModifier>& scrollbarOverlayModifier, WeakPtr<ScrollEdgeEffect>&& edgeEffect);
    void SetCaretOffsetAndHeight(const OffsetF& cursorOffset, float height);
    void SetCaretColor(uint32_t caretColor);
    void SetCaretWidth(float width);
    void SetCaretVisible(bool value);
    void SetScrollOffset(float value);
    void SetScrollBarOpacityType(int32_t type);
    void SetTextHeight(float value);
    void SetFrameSize(const SizeF& value);
    void SetPreviewTextDecorationColor(const Color& value);
    void SetPreviewTextUnderlineWidth(float value);
    void SetShowPreviewTextDecoration(bool value);
    void SetPreviewTextStyle(const PreviewTextStyle& value);
    float GetCaretHeight() const;
    float GetCaretWidth() const;
    OffsetF GetCaretOffset() const;
    void onDraw(DrawingContext& drawingContext) override;
    void UpdateScrollBar(PaintWrapper* paintWrapper);
private:
    void PaintPreviewTextDecoration(DrawingContext& drawingContext) const;
    void PaintCaret(DrawingContext& drawingContext) const;
    void PaintScrollBar(DrawingContext& context);
    void PaintEdgeEffect(const SizeF& frameSize, RSCanvas& canvas);

    RefPtr<PropertyBool> caretVisible_;
    RefPtr<PropertyOffsetF> caretOffset_;
    RefPtr<PropertyFloat> caretHeight_;
    RefPtr<PropertyFloat> caretWidth_;
    RefPtr<PropertyInt> caretColor_;
    RefPtr<PropertyFloat> scrollOffset_;
    RefPtr<PropertyInt> scrollBarOpacityType_;
    RefPtr<PropertyFloat> textHeight_;
    WeakPtr<Pattern> pattern_;
    WeakPtr<ScrollEdgeEffect> edgeEffect_;
    WeakPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier_;
    RefPtr<PropertySizeF> frameSize_;
    RefPtr<PropertyColor> previewTextDecorationColor_;
    RefPtr<PropertyFloat> previewTextUnderlineWidth_;
    RefPtr<PropertyBool> showPreviewTextDecoration_;
    PreviewTextStyle previewTextStyle_;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorOverlayModifier);
};
} // namespace OHOS::Ace::NG
#endif
