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

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension RESERVE_BOTTOM_HEIGHT = 24.0_vp;
} // namespace

void TextFieldManagerNG::ClearOnFocusTextField()
{
    onFocusTextField_ = nullptr;
}

bool TextFieldManagerNG::OnBackPressed()
{
    auto pattern = onFocusTextField_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textBasePattern = AceType::DynamicCast<TextBase>(pattern);
    CHECK_NULL_RETURN(textBasePattern, false);
    return textBasePattern->OnBackPressed();
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
    auto node = onFocusTextField_.Upgrade();
    CHECK_NULL_VOID(node);
    auto frameNode = node->GetHost();
    CHECK_NULL_VOID(frameNode);
    auto textBase = DynamicCast<TextBase>(node);
    CHECK_NULL_VOID(textBase);

    auto scrollableNode = FindScrollableOfFocusedTextField(frameNode);
    CHECK_NULL_VOID(scrollableNode);
    auto scrollPattern = scrollableNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollPattern);
    if (scrollPattern->GetAxis() == Axis::HORIZONTAL) {
        return;
    }

    auto scrollableRect = scrollableNode->GetTransformRectRelativeToWindow();
    CHECK_NULL_VOID(scrollableRect.Top() < bottomInset.start);

    auto caretRect = textBase->GetCaretRect() + frameNode->GetOffsetRelativeToWindow();
    auto diffTop = caretRect.Top() - scrollableRect.Top();
    // caret height larger scroll's content region
    if (diffTop <= 0 && LessNotEqual(bottomInset.start, caretRect.Bottom())) {
        return;
    }

    // caret above scroll's content region
    if (diffTop < 0) {
        scrollPattern->ScrollTo(scrollPattern->GetTotalOffset() + diffTop);
        return;
    }

    // caret inner scroll's content region
    if(LessNotEqual(caretRect.Bottom(), bottomInset.start)) {
        return;
    }

    // caret below safeArea
    auto diffBot = bottomInset.start - caretRect.Bottom();
    CHECK_NULL_VOID(diffBot < 0);
    scrollPattern->ScrollTo(scrollPattern->GetTotalOffset() - diffBot);
}

void TextFieldManagerNG::ScrollTextFieldToSafeArea()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto keyboardInset = pipeline->GetSafeAreaManager()->GetKeyboardInset();
    // only scroll when keyboard shows
    CHECK_NULL_VOID(keyboardInset.IsValid());
    auto bottomInset = pipeline->GetSafeArea().bottom_.Combine(keyboardInset);
    CHECK_NULL_VOID(bottomInset.IsValid());
    ScrollToSafeAreaHelper(bottomInset);
}

void TextFieldManagerNG::SetHeight(float height)
{
    height_ = height + RESERVE_BOTTOM_HEIGHT.ConvertToPx();
}

void TextFieldManagerNG::UpdateScrollableParentViewPort(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto scrollableNode = FindScrollableOfFocusedTextField(node);
    CHECK_NULL_VOID(scrollableNode);
    auto scrollPattern = scrollableNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollPattern);
    if (scrollPattern->GetAxis() == Axis::HORIZONTAL) {
        return;
    }
    auto scrollableRect = scrollableNode->GetTransformRectRelativeToWindow();
    scrollableNode->SetViewPort(scrollableRect);
}
} // namespace OHOS::Ace::NG
