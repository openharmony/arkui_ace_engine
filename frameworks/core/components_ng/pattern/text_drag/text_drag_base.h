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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_DRAG_TEXT_DRAG_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_DRAG_TEXT_DRAG_BASE_H

#include "base/memory/ace_type.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paragraph.h"

constexpr uint32_t DRAGGED_TEXT_OPACITY = 0x66;

namespace OHOS::Ace::NG {
using ParagraphT = std::variant<std::shared_ptr<RSParagraph>, RefPtr<Paragraph>>;

// inherited by TextPattern and TextFieldPattern
// Text Drag polymorphism
class TextDragBase : public virtual AceType {
    DECLARE_ACE_TYPE(TextDragBase, AceType);

public:
    TextDragBase() = default;
    ~TextDragBase() override = default;

    virtual bool IsTextArea() const = 0;

    virtual const RectF& GetTextRect() = 0;
    virtual const RectF& GetTextContentRect() const = 0;
    virtual float GetLineHeight() const = 0;

    virtual std::vector<RSTypographyProperties::TextBox> GetTextBoxes() = 0;
    virtual OffsetF GetParentGlobalOffset() const = 0;
    virtual bool BetweenSelectedPosition(const Offset& globalOffset) = 0;

    virtual RefPtr<FrameNode> MoveDragNode() = 0;

    virtual ParagraphT GetDragParagraph() const = 0;

    virtual void CloseSelectOverlay() = 0;
    virtual void CreateHandles() = 0;
    virtual bool CloseKeyboard(bool forceClose) = 0;

    ACE_DISALLOW_COPY_AND_MOVE(TextDragBase);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_DRAG_TEXT_DRAG_BASE_H
