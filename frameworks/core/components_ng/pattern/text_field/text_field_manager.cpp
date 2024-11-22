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
#include "core/common/ime/text_input_type.h"
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
        focusFieldIsInline = false;
        optionalPosition_ = std::nullopt;
        usingCustomKeyboardAvoid_ = false;
        isScrollableChild_ = false;
    }
}

bool TextFieldManagerNG::OnBackPressed()
{
    auto pattern = onFocusTextField_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textBasePattern = AceType::DynamicCast<TextBase>(pattern);
    CHECK_NULL_RETURN(textBasePattern, false);
    return textBasePattern->OnBackPressed();
}

void TextFieldManagerNG::SetClickPosition(const Offset& position)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto rootHeight = pipeline->GetRootHeight();
    if (GreatOrEqual(position.GetY(), rootHeight)) {
        auto pattern = onFocusTextField_.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto parent = host->GetAncestorNodeOfFrame();
        while (parent) {
            if (parent->GetTag() == "Panel" || parent->GetTag() == "SheetPage") {
                return;
            }
            parent = parent->GetAncestorNodeOfFrame();
        }
    }
    if (LessOrEqual(position.GetY(), 0.0f)) {
        return;
    }
    auto rootWidth = pipeline->GetRootWidth();
    if (GreatOrEqual(position.GetX(), rootWidth) || LessNotEqual(position.GetX(), 0.0f)) {
        return;
    }
    position_ = position;
    optionalPosition_ = position;
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

RectF TextFieldManagerNG::GetFocusedNodeCaretRect()
{
    auto node = onFocusTextField_.Upgrade();
    CHECK_NULL_RETURN(node, RectF());
    auto frameNode = node->GetHost();
    CHECK_NULL_RETURN(frameNode, RectF());
    auto textBase = DynamicCast<TextBase>(node);
    CHECK_NULL_RETURN(textBase, RectF());
    auto caretRect = textBase->GetCaretRect() + frameNode->GetTransformRectRelativeToWindow();
    return caretRect;
}

void TextFieldManagerNG::TriggerCustomKeyboardAvoid()
{
    CHECK_NULL_VOID(UsingCustomKeyboardAvoid());
    auto pattern = onFocusTextField_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto curPattern = DynamicCast<TextFieldPattern>(pattern);
    CHECK_NULL_VOID(curPattern);
    if (!curPattern->GetIsCustomKeyboardAttached()) {
        return;
    }
    auto caretHeight = curPattern->GetCaretRect().Height();
    auto safeHeight = caretHeight + curPattern->GetCaretRect().GetY();
    if (curPattern->GetCaretRect().GetY() > caretHeight) {
        safeHeight = caretHeight;
    }
    auto keyboardOverLay = curPattern->GetKeyboardOverLay();
    CHECK_NULL_VOID(keyboardOverLay);
    auto host = curPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto nodeId = host->GetId();
    keyboardOverLay->AvoidCustomKeyboard(nodeId, safeHeight);
}

void TextFieldManagerNG::TriggerAvoidOnCaretChange()
{
    auto pattern = onFocusTextField_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    if (!pipeline->UsingCaretAvoidMode() || NearEqual(safeAreaManager->GetKeyboardInset().Length(), 0)) {
        return;
    }
    if (UsingCustomKeyboardAvoid()) {
        ScrollTextFieldToSafeArea();
        TriggerCustomKeyboardAvoid();
    } else {
        ScrollTextFieldToSafeArea();
        auto keyboardInset = safeAreaManager->GetKeyboardInset();
        lastKeyboardOffset_ = safeAreaManager->GetKeyboardOffsetDirectly();
        Rect keyboardRect;
        keyboardRect.SetRect(0, 0, 0, keyboardInset.Length());
        pipeline->OnVirtualKeyboardAreaChange(keyboardRect,
            GetFocusedNodeCaretRect().Top(), GetHeight());
    }
    auto currentKeyboardOffset = safeAreaManager->GetKeyboardOffsetDirectly();
    if (currentKeyboardOffset != lastKeyboardOffset_) {
        AvoidKeyboardInSheet(host);
    }
}

void TextFieldManagerNG::GetOnFocusTextFieldInfo(const WeakPtr<Pattern>& onFocusTextField)
{
    auto node = onFocusTextField.Upgrade();
    CHECK_NULL_VOID(node);
    auto frameNode = node->GetHost();
    CHECK_NULL_VOID(frameNode);
    auto scrollableNode = FindScrollableOfFocusedTextField(frameNode);
    CHECK_NULL_VOID(scrollableNode);
    auto scrollPattern = scrollableNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollPattern);
    isScrollableChild_ = scrollPattern->IsScrollToSafeAreaHelper();
    TAG_LOGI(ACE_KEYBOARD, "isScrollableChild_: %{public}d", isScrollableChild_);
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
    CHECK_NULL_RETURN(scrollPattern->GetAxis() != Axis::HORIZONTAL, false);

    auto scrollableRect = scrollableNode->GetTransformRectRelativeToWindow();
    if (isShowKeyboard) {
        CHECK_NULL_RETURN(scrollableRect.Top() < bottomInset.start, false);
    }

    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, false);
    if (pipeline->UsingCaretAvoidMode()) {
        scrollableRect.SetTop(scrollableRect.Top() - safeAreaManager->GetKeyboardOffset());
    }

    auto caretRect = textBase->GetCaretRect() + frameNode->GetPositionToWindowWithTransform();
    auto diffTop = caretRect.Top() - scrollableRect.Top();
    // caret height larger scroll's content region
    if (isShowKeyboard && diffTop <= 0 && LessNotEqual(bottomInset.start,
        (caretRect.Bottom() + RESERVE_BOTTOM_HEIGHT.ConvertToPx()))) {
        return false;
    }

    // caret above scroll's content region
    if (diffTop < 0) {
        TAG_LOGI(ACE_KEYBOARD, "scrollRect:%{public}s caretRect:%{public}s totalOffset()=%{public}f diffTop=%{public}f",
            scrollableRect.ToString().c_str(), caretRect.ToString().c_str(), scrollPattern->GetTotalOffset(), diffTop);
        scrollPattern->ScrollTo(scrollPattern->GetTotalOffset() + diffTop);
        return true;
    }

    // caret inner scroll's content region
    if (isShowKeyboard && LessNotEqual((caretRect.Bottom() + RESERVE_BOTTOM_HEIGHT.ConvertToPx()), bottomInset.start)) {
        return false;
    }

    // caret below safeArea
    float diffBot = 0.0f;

    auto scrollBottom = isShowKeyboard && GreatOrEqual(scrollableRect.Bottom(), bottomInset.start) ?
        bottomInset.start : scrollableRect.Bottom();
    diffBot = scrollBottom - caretRect.Bottom() - RESERVE_BOTTOM_HEIGHT.ConvertToPx();
    CHECK_NULL_RETURN(diffBot < 0, false);
    TAG_LOGI(ACE_KEYBOARD, "scrollRect:%{public}s caretRect:%{public}s totalOffset()=%{public}f diffBot=%{public}f",
        scrollableRect.ToString().c_str(), caretRect.ToString().c_str(), scrollPattern->GetTotalOffset(), diffBot);
    scrollPattern->ScrollTo(scrollPattern->GetTotalOffset() - diffBot);
    return true;
}

bool TextFieldManagerNG::ScrollTextFieldToSafeArea()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto keyboardInset = pipeline->GetSafeAreaManager()->GetKeyboardInset();
    bool isShowKeyboard = keyboardInset.IsValid();
    if (isShowKeyboard) {
        auto bottomInset = pipeline->GetSafeArea().bottom_.Combine(keyboardInset);
        CHECK_NULL_RETURN(bottomInset.IsValid(), false);
        return ScrollToSafeAreaHelper(bottomInset, isShowKeyboard);
    } else if (pipeline->GetSafeAreaManager()->KeyboardSafeAreaEnabled()) {
        // hide keyboard only scroll when keyboard avoid mode is resize
        return ScrollToSafeAreaHelper({0, 0}, isShowKeyboard);
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

void TextFieldManagerNG::AvoidKeyBoardInNavigation()
{
    auto node = onFocusTextField_.Upgrade();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    auto avoidKeyboardOffset =  manager ? manager->GetKeyboardOffset() : 0.0f;
    if (!node) {
        auto navNode = weakNavNode_.Upgrade();
        CHECK_NULL_VOID(navNode);
        SetNavContentAvoidKeyboardOffset(navNode, avoidKeyboardOffset);
        return;
    }
    auto frameNode = node->GetHost();
    CHECK_NULL_VOID(frameNode);
    auto preNavNode = weakNavNode_.Upgrade();
    if (preNavNode) {
        SetNavContentAvoidKeyboardOffset(preNavNode, 0.0f);
    }
    auto navNode = FindNavNode(frameNode);
    CHECK_NULL_VOID(navNode);
    weakNavNode_ = navNode;
    SetNavContentAvoidKeyboardOffset(navNode, avoidKeyboardOffset);
}

void TextFieldManagerNG::AvoidKeyboardInSheet(const RefPtr<FrameNode>& textField)
{
    CHECK_NULL_VOID(textField);
    auto parent = textField->GetAncestorNodeOfFrame();
    bool findSheet = false;
    while (parent) {
        if (parent->GetHostTag() == V2::SHEET_PAGE_TAG) {
            findSheet = true;
            break;
        }
        parent = parent->GetAncestorNodeOfFrame();
    }
    CHECK_NULL_VOID(parent);
    auto sheetNodePattern = parent->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetNodePattern);
    TAG_LOGI(ACE_KEYBOARD, "Force AvoidKeyboard in sheet");
    sheetNodePattern->AvoidSafeArea(true);
}

RefPtr<FrameNode> TextFieldManagerNG::FindNavNode(const RefPtr<FrameNode>& textField)
{
    CHECK_NULL_RETURN(textField, nullptr);
    auto parent = textField->GetAncestorNodeOfFrame();
    RefPtr<FrameNode> ret = nullptr;
    while (parent) {
        // when the sheet showed in navdestination, sheet replaced navdestination to do avoid keyboard.
        if (parent->GetHostTag() == V2::SHEET_WRAPPER_TAG) {
            auto sheetNode = parent->GetChildAtIndex(0);
            CHECK_NULL_RETURN(sheetNode, nullptr);
            return AceType::DynamicCast<FrameNode>(sheetNode);
        }
        if (parent->GetHostTag() == V2::NAVDESTINATION_VIEW_ETS_TAG ||
            parent->GetHostTag() == V2::NAVBAR_ETS_TAG) {
                ret = parent;
                break;
            }
        parent = parent->GetAncestorNodeOfFrame();
    }
    CHECK_NULL_RETURN(ret, nullptr);
    
    // return navdestination or navBar if the closest ancestor navigation can expandKeyboard
    // if can't, recursively find the ancestor navigation can expandKeyboard.
    auto navigationNode = ret->GetAncestorNodeOfFrame();
    while (navigationNode) {
        if (navigationNode->GetHostTag() == V2::NAVIGATION_VIEW_ETS_TAG) {
            break;
        }
        navigationNode = navigationNode->GetAncestorNodeOfFrame();
    }
    CHECK_NULL_RETURN(navigationNode, nullptr);
    auto layoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto& opts = layoutProperty->GetSafeAreaExpandOpts();
    
    // if the extended keyboard area is set for the navigation, top navdestination or navbar need to avoid keyboard,
    // otherwise don't aovid, following parent navigation.
    bool isExpandKeyboard = opts && (opts->type & SAFE_AREA_TYPE_KEYBOARD) && (opts->edges & SAFE_AREA_EDGE_BOTTOM);
    if (isExpandKeyboard) {
        return ret;
    }
    auto mayAvoidNavContentNode = FindNavNode(navigationNode);
    if (mayAvoidNavContentNode) {
        return mayAvoidNavContentNode;
    }
    SetNavContentAvoidKeyboardOffset(ret, 0.0f);
    return nullptr;
}

void TextFieldManagerNG::SetNavContentAvoidKeyboardOffset(RefPtr<FrameNode> navNode, float avoidKeyboardOffset)
{
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(navNode);
    if (navDestinationNode) {
        TAG_LOGI(ACE_KEYBOARD, "navNode id:%{public}d, avoidKeyboardOffset:%{public}f", navNode->GetId(),
            avoidKeyboardOffset);
        auto pattern = navDestinationNode->GetPattern<NavDestinationPattern>();
        if (pattern) {
            avoidKeyboardOffset = pattern->NeedIgnoreKeyboard() ? 0.0f : avoidKeyboardOffset;
            pattern->SetAvoidKeyboardOffset(avoidKeyboardOffset);
        }
    }
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navNode);
    if (navBarNode) {
        auto pattern = navBarNode->GetPattern<NavBarPattern>();
        if (pattern) {
            pattern->SetAvoidKeyboardOffset(avoidKeyboardOffset);
        }
    }
    navNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void TextFieldManagerNG::AddTextFieldInfo(const TextFieldInfo& textFieldInfo)
{
    if (textFieldInfo.nodeId == -1 || textFieldInfo.autoFillContainerNodeId == -1) {
        return;
    }

    auto containerNodeIter = textFieldInfoMap_.find(textFieldInfo.autoFillContainerNodeId);
    if (containerNodeIter != textFieldInfoMap_.end()) {
        auto& innerTextFieldMap = containerNodeIter->second;
        innerTextFieldMap[textFieldInfo.nodeId] = textFieldInfo;
    } else {
        std::unordered_map<int32_t, TextFieldInfo> innerTextFieldInfoMap;
        innerTextFieldInfoMap[textFieldInfo.nodeId] = textFieldInfo;
        textFieldInfoMap_[textFieldInfo.autoFillContainerNodeId] = innerTextFieldInfoMap;
    }
}

void TextFieldManagerNG::RemoveTextFieldInfo(const int32_t& autoFillContainerNodeId, const int32_t& nodeId)
{
    auto containerNodeIter = textFieldInfoMap_.find(autoFillContainerNodeId);
    if (containerNodeIter != textFieldInfoMap_.end()) {
        auto& innerTextFieldInfoMap = containerNodeIter->second;
        auto textFieldNodeIter = innerTextFieldInfoMap.find(nodeId);
        if (textFieldNodeIter != innerTextFieldInfoMap.end()) {
            innerTextFieldInfoMap.erase(textFieldNodeIter);
        }
    }
}

void TextFieldManagerNG::UpdateTextFieldInfo(const TextFieldInfo& textFieldInfo)
{
    if (textFieldInfo.nodeId == -1 || textFieldInfo.autoFillContainerNodeId == -1) {
        return;
    }
    auto containerNodeIter = textFieldInfoMap_.find(textFieldInfo.autoFillContainerNodeId);
    if (containerNodeIter != textFieldInfoMap_.end()) {
        auto& innerTextFieldInfoMap = containerNodeIter->second;
        auto textFieldNodeIter = innerTextFieldInfoMap.find(textFieldInfo.nodeId);
        if (textFieldNodeIter != innerTextFieldInfoMap.end()) {
            innerTextFieldInfoMap.erase(textFieldNodeIter);
        }
        innerTextFieldInfoMap[textFieldInfo.nodeId] = textFieldInfo;
    } else {
        AddTextFieldInfo(textFieldInfo);
    }
}

bool TextFieldManagerNG::HasAutoFillPasswordNodeInContainer(
    const int32_t& autoFillContainerNodeId, const int32_t& nodeId)
{
    auto containerNodeIter = textFieldInfoMap_.find(autoFillContainerNodeId);
    if (containerNodeIter == textFieldInfoMap_.end()) {
        return false;
    }

    auto& innerTextFieldInfoMap = containerNodeIter->second;
    auto textFieldNodeIter = innerTextFieldInfoMap.find(nodeId);
    if (textFieldNodeIter == innerTextFieldInfoMap.end()) {
        return false;
    }

    for (const auto& textField : innerTextFieldInfoMap) {
        auto textFieldId = textField.first;
        auto textFieldInfo = textField.second;
        if (textFieldId == nodeId) {
            continue;
        }

        auto isPasswordType = IsAutoFillPasswordType(textFieldInfo);
        if (isPasswordType && textFieldInfo.enableAutoFill) {
            return true;
        }
    }

    return false;
}

bool TextFieldManagerNG::IsAutoFillPasswordType(const TextFieldInfo& textFieldInfo)
{
    return textFieldInfo.inputType == TextInputType::VISIBLE_PASSWORD ||
           textFieldInfo.inputType == TextInputType::NEW_PASSWORD ||
           textFieldInfo.inputType == TextInputType::NUMBER_PASSWORD ||
           textFieldInfo.contentType == TextContentType::VISIBLE_PASSWORD ||
           textFieldInfo.contentType == TextContentType::NEW_PASSWORD;
}

TextFieldManagerNG::~TextFieldManagerNG()
{
    textFieldInfoMap_.clear();
}
} // namespace OHOS::Ace::NG
