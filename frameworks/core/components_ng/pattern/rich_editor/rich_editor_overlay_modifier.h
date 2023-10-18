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
#include "core/components_ng/pattern/text/text_overlay_modifier.h"

namespace OHOS::Ace::NG {
class RichEditorOverlayModifier : public TextOverlayModifier {
    DECLARE_ACE_TYPE(RichEditorOverlayModifier, TextOverlayModifier)

public:
    RichEditorOverlayModifier();
    void SetCaretOffsetAndHeight(const OffsetF& cursorOffset, float height);
    void SetCaretColor(uint32_t caretColor);
    void SetCaretWidth(float width);
    void SetCaretVisible(bool value);
    float GetCaretHeight() const;
    float GetCaretWidth() const;
    OffsetF GetCaretOffset() const;
    void onDraw(DrawingContext& drawingContext) override;

private:
    void PaintCaret(DrawingContext& drawingContext) const;

    RefPtr<PropertyBool> caretVisible_;
    RefPtr<PropertyOffsetF> caretOffset_;
    RefPtr<PropertyFloat> caretHeight_;
    RefPtr<PropertyFloat> caretWidth_;
    RefPtr<PropertyInt> caretColor_;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorOverlayModifier);
};
} // namespace OHOS::Ace::NG
#endif
