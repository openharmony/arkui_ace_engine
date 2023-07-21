/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_field/text_field_manager.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
const RefPtr<KeyEventHandler>& TextFieldManagerNG::GetKeyEventHandler()
{
    if (!keyEventHandler_) {
        keyEventHandler_ = AceType::MakeRefPtr<KeyEventHandler>();
    }
    return keyEventHandler_;
}

void TextFieldManagerNG::ClearOnFocusTextField()
{
    onFocusTextField_ = nullptr;
    CHECK_NULL_VOID(keyEventHandler_);
    keyEventHandler_->ClearClient();
}

bool TextFieldManagerNG::OnBackPressed()
{
    auto pattern = onFocusTextField_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textfieldPattern = AceType::DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_RETURN(textfieldPattern, false);
    return textfieldPattern->OnBackPressed();
}

std::pair<RefPtr<FrameNode>, OffsetF> TextFieldManagerNG::FindScrollableOfFocusedTextField(
    const RefPtr<FrameNode>& textField)
{
    CHECK_NULL_RETURN(textField, {});
    auto parent = textField->GetAncestorNodeOfFrame();
    auto offset = textField->GetGeometryNode()->GetFrameOffset();
    while (parent) {
        auto pattern = parent->GetPattern<ScrollablePattern>();
        if (pattern) {
            return { parent, offset };
        }
        offset += parent->GetGeometryNode()->GetFrameOffset();
        parent = parent->GetAncestorNodeOfFrame();
    }
    return {};
}

void TextFieldManagerNG::ScrollTextFieldToSafeArea(const SafeAreaInsets::Inset& bottomInset)
{
    auto textPattern = onFocusTextField_.Upgrade();
    CHECK_NULL_VOID(textPattern);
    auto textField = textPattern->GetHost();
    CHECK_NULL_VOID(textField);

    auto [scrollable, textFieldOffsetToScrollable] = FindScrollableOfFocusedTextField(textField);
    CHECK_NULL_VOID_NOLOG(scrollable);

    // global offset
    RectF scrollableRect = scrollable->GetGeometryNode()->GetFrameRect();
    scrollableRect.SetOffset(scrollable->GetPaintRectOffset());
    CHECK_NULL_VOID_NOLOG(scrollableRect.Top() < bottomInset.start);

    // global offset
    auto textFieldRect = textField->GetGeometryNode()->GetFrameRect();
    textFieldRect.SetOffset(textFieldOffsetToScrollable + scrollableRect.GetOffset());

    // offset relative to textRect
    auto caretRect = DynamicCast<TextFieldPattern>(textPattern)->GetCaretRect();
    auto diff = bottomInset.start - (textFieldRect.GetY() + caretRect.Bottom() + textFieldRect.Height() / 2);

    CHECK_NULL_VOID_NOLOG(diff < 0);
    auto scrollPattern = scrollable->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->ScrollTo(scrollPattern->GetTotalOffset() - diff);
}
} // namespace OHOS::Ace::NG
