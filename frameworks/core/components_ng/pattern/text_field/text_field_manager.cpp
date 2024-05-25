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
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
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

void TextFieldManagerNG::ClearOnFocusTextField(int32_t id)
{
    if (onFocusTextFieldId == id) {
        onFocusTextField_ = nullptr;
    }
}

void TextFieldManagerNG::SetClickPosition(const Offset& position)
{
    auto pipeline =  PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto rootHeight = pipeline->GetRootHeight();
    if (GreatOrEqual(position.GetY(), rootHeight) || LessOrEqual(position.GetY(), 0.0f)) {
        return;
    }
    auto rootWidth = pipeline->GetRootWidth();
    if (GreatOrEqual(position.GetX(), rootWidth) || LessOrEqual(position.GetX(), 0.0f)) {
        return;
    }
    position_ = position;
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

bool TextFieldManagerNG::ScrollToSafeAreaHelper(
    const SafeAreaInsets::Inset& bottomInset, bool isShowKeyboard)
{
    auto node = onFocusTextField_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto frameNode = node->GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    auto textBase = DynamicCast<TextBase>(node);
    CHECK_NULL_RETURN(textBase, false);
    textBase->OnVirtualKeyboardAreaChanged();

    auto scrollableNode = FindScrollableOfFocusedTextField(frameNode);
    CHECK_NULL_RETURN(scrollableNode, false);
    auto scrollPattern = scrollableNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(scrollPattern && scrollPattern->IsScrollToSafeAreaHelper(), false);
    if (scrollPattern->GetAxis() == Axis::HORIZONTAL) {
        return false;
    }

    auto scrollableRect = scrollableNode->GetTransformRectRelativeToWindow();
    if (isShowKeyboard) {
        CHECK_NULL_RETURN(scrollableRect.Top() < bottomInset.start, false);
    }

    auto caretRect = textBase->GetCaretRect() + frameNode->GetOffsetRelativeToWindow();
    auto diffTop = caretRect.Top() - scrollableRect.Top();
    // caret height larger scroll's content region
    if (isShowKeyboard) {
        if (diffTop <= 0 &&
            LessNotEqual(bottomInset.start, (caretRect.Bottom() + RESERVE_BOTTOM_HEIGHT.ConvertToPx()))) {
            return false;
        }
    }

    // caret above scroll's content region
    if (diffTop < 0) {
        scrollPattern->ScrollTo(scrollPattern->GetTotalOffset() + diffTop);
        return true;
    }

    // caret inner scroll's content region
    if (isShowKeyboard) {
        if (LessNotEqual((caretRect.Bottom() + RESERVE_BOTTOM_HEIGHT.ConvertToPx()), bottomInset.start)) {
            return false;
        }
    }

    // caret below safeArea
    float diffBot = 0.0f;
    if (isShowKeyboard) {
        if (LessNotEqual(scrollableRect.Bottom(), bottomInset.start)) {
            diffBot = scrollableRect.Bottom() - caretRect.Bottom() - RESERVE_BOTTOM_HEIGHT.ConvertToPx();
        } else {
            diffBot = bottomInset.start - caretRect.Bottom() - RESERVE_BOTTOM_HEIGHT.ConvertToPx();
        }
    } else {
        diffBot = scrollableRect.Bottom() - caretRect.Bottom() - RESERVE_BOTTOM_HEIGHT.ConvertToPx();
    }
    CHECK_NULL_RETURN(diffBot < 0, false);
    scrollPattern->ScrollTo(scrollPattern->GetTotalOffset() - diffBot);
    return true;
}

bool TextFieldManagerNG::ScrollTextFieldToSafeArea()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto keyboardInset = pipeline->GetSafeAreaManager()->GetKeyboardInset();
    bool isShowKeyboard = keyboardInset.IsValid();
    NotifyKeyboardChangedCallback(isShowKeyboard);
    if (isShowKeyboard) {
        auto bottomInset = pipeline->GetSafeArea().bottom_.Combine(keyboardInset);
        CHECK_NULL_RETURN(bottomInset.IsValid(), false);
        return ScrollToSafeAreaHelper(bottomInset, isShowKeyboard);
    } else if (pipeline->GetSafeAreaManager()->KeyboardSafeAreaEnabled()) {
        // hide keyboard only scroll when keyboard avoid mode is resize
        return ScrollToSafeAreaHelper({ 0, 0 }, isShowKeyboard);
    }
    return false;
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

void TextFieldManagerNG::ProcessNavKeyboard()
{
    if (imeShow_ || uiExtensionImeShow_) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Nav notNeedSoftKeyboard.");
        FocusHub::NavCloseKeyboard();
    }
}

void TextFieldManagerNG::AvoidKeyboard()
{
    if (!ScrollTextFieldToSafeArea()) {
        NavContentToSafeAreaHelper();
    }
}

void TextFieldManagerNG::NavContentToSafeAreaHelper()
{
    auto node = onFocusTextField_.Upgrade();
    if (!node) {
        auto navNode = weakNavNode_.Upgrade();
        if (!navNode) {
            // if navNode is nullptr means TextField's parent
            // dont't have navBar or navDestination
            return;
        }
        SetNavContentKeyboardOffset(navNode);
        return;
    }
    auto frameNode = node->GetHost();
    CHECK_NULL_VOID(frameNode);
    auto navNode = FindNavNode(frameNode);
    if (!navNode) {
        return;
    }
    weakNavNode_ = navNode;
    SetNavContentKeyboardOffset(navNode);
}

RefPtr<FrameNode> TextFieldManagerNG::FindNavNode(const RefPtr<FrameNode>& textField)
{
    CHECK_NULL_RETURN(textField, nullptr);
    auto parent = textField->GetAncestorNodeOfFrame();
    RefPtr<FrameNode> ret = nullptr;
    while (parent) {
        if (parent->GetHostTag() == V2::NAVDESTINATION_VIEW_ETS_TAG ||
            parent->GetHostTag() == V2::NAVBAR_ETS_TAG) {
                ret = parent;
                break;
            }
        parent = parent->GetAncestorNodeOfFrame();
    }
    return ret;
}

void TextFieldManagerNG::SetNavContentKeyboardOffset(RefPtr<FrameNode> navNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    auto keyboardOffset =  manager ? manager->GetKeyboardOffset() : 0.0f;
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(navNode);
    if (navDestinationNode) {
        auto pattern = navDestinationNode->GetPattern<NavDestinationPattern>();
        if (pattern) {
            pattern->SetKeyboardOffset(keyboardOffset);
        }
    }
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navNode);
    if (navBarNode) {
        auto pattern = navBarNode->GetPattern<NavBarPattern>();
        if (pattern) {
            pattern->SetKeyboardOffset(keyboardOffset);
        }
    }
    navNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void TextFieldManagerNG::NotifyKeyboardChangedCallback(bool isShowKeyboard)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto safeAreaManager = context->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto keyboardOffset = safeAreaManager->GetKeyboardOffset();
    auto isChanged = !NearEqual(lastKeyboardOffset_, keyboardOffset);
    for (const auto& pair : keyboardChangeCallbackMap_) {
        if (pair.second) {
            pair.second(isChanged, isShowKeyboard);
        }
    }
    lastKeyboardOffset_ = keyboardOffset;
}
} // namespace OHOS::Ace::NG
