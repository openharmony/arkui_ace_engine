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

RefPtr<FrameNode> TextFieldManagerNG::FindScrollableOfFocusedTextField(const RefPtr<FrameNode>& textField)
{
    CHECK_NULL_RETURN(textField, {});
    auto parent = textField->GetAncestorNodeOfFrame();
    while (parent) {
        auto pattern = parent->GetPattern<ScrollablePattern>();
        if (pattern) {
            return parent;
        }
        parent = parent->GetAncestorNodeOfFrame();
    }
    return {};
}

void TextFieldManagerNG::ScrollToSafeAreaHelper(const SafeAreaInsets::Inset& bottomInset)
{
    auto textField = DynamicCast<TextFieldPattern>(onFocusTextField_.Upgrade());
    CHECK_NULL_VOID(textField);
    auto textFieldNode = textField->GetHost();
    CHECK_NULL_VOID(textFieldNode);

    auto scrollableNode = FindScrollableOfFocusedTextField(textFieldNode);
    CHECK_NULL_VOID_NOLOG(scrollableNode);
    auto scrollPattern = scrollableNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollPattern);

    auto scrollableRect = scrollableNode->GetTransformRectRelativeToWindow();
    CHECK_NULL_VOID_NOLOG(scrollableRect.Top() < bottomInset.start);

    auto caretRect = textField->GetCaretRect() + textFieldNode->GetOffsetRelativeToWindow();
    // caret above scroll's content region
    auto diffTop = (caretRect.Top() - caretRect.Height() * 2) - scrollableRect.Top();
    if (diffTop < 0) {
        scrollPattern->ScrollTo(scrollPattern->GetTotalOffset() + diffTop);
        return;
    }

    // caret below safeArea
    auto diffBot = bottomInset.start - (caretRect.Bottom() + caretRect.Height() * 2);
    CHECK_NULL_VOID_NOLOG(diffBot < 0);
    scrollPattern->ScrollTo(scrollPattern->GetTotalOffset() - diffBot);
}

void TextFieldManagerNG::ScrollTextFieldToSafeArea()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto keyboardInset = pipeline->GetSafeAreaManager()->GetKeyboardInset();
    // only scroll when keyboard shows
    CHECK_NULL_VOID_NOLOG(keyboardInset.IsValid());
    auto bottomInset = pipeline->GetSafeArea().bottom_.Combine(keyboardInset);
    CHECK_NULL_VOID_NOLOG(bottomInset.IsValid());
    ScrollToSafeAreaHelper(bottomInset);
}
} // namespace OHOS::Ace::NG
