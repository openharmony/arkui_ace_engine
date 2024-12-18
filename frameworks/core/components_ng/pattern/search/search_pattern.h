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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_PATTERN_H

#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "base/mousestyle/mouse_style.h"
#include "core/components/text_field/text_field_controller.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_layout_algorithm.h"
#include "core/components_ng/pattern/search/search_layout_property.h"
#include "core/components_ng/pattern/search/search_node.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class SearchPattern : public Pattern {
    DECLARE_ACE_TYPE(SearchPattern, Pattern);

public:
    SearchPattern() = default;
    ~SearchPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }
    // search pattern needs softkeyboard, override function.
    bool NeedSoftKeyboard() const override
    {
        return true;
    }

    bool NeedToRequestKeyboardOnFocus() const override
    {
        auto textField = textField_.Upgrade();
        CHECK_NULL_RETURN(textField, false);
        auto pattern = textField->GetPattern();
        CHECK_NULL_RETURN(pattern, false);
        auto curPattern = DynamicCast<TextFieldPattern>(pattern);
        return curPattern->NeedToRequestKeyboardOnFocus();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<SearchLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SearchLayoutAlgorithm>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SearchEventHub>();
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& /*config*/) override;

    const RefPtr<TextFieldController>& GetSearchController()
    {
        return searchController_;
    }

    void SetSearchController(const RefPtr<TextFieldController>& searchController)
    {
        searchController_ = searchController;
    }

    const OffsetF& GetTextFieldOffset() const
    {
        return textFieldOffset_;
    }

    FocusPattern GetFocusPattern() const override;

    bool HandleInputChildOnFocus() const;

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    static std::string ConvertCopyOptionsToString(CopyOptions copyOptions)
    {
        std::string result;
        switch (copyOptions) {
            case CopyOptions::None:
                result = "CopyOptions.None";
                break;
            case CopyOptions::InApp:
                result = "CopyOptions.InApp";
                break;
            case CopyOptions::Local:
                result = "CopyOptions.Local";
                break;
            case CopyOptions::Distributed:
                result = "CopyOptions.Distributed";
                break;
            default:
                break;
        }
        return result;
    }

    enum class FocusChoice { SEARCH = 0, CANCEL_BUTTON, SEARCH_BUTTON };

    void UpdateChangeEvent(const std::u16string& value, int16_t style = -1);

    void SetCancelButtonNode(const RefPtr<FrameNode>& cancelButtonNode)
    {
        cancelButtonNode_ = AceType::WeakClaim(AceType::RawPtr(cancelButtonNode));
    }

    void SetButtonNode(const RefPtr<FrameNode>& buttonNode)
    {
        buttonNode_ = AceType::WeakClaim(AceType::RawPtr(buttonNode));
    }

    void SetTextFieldNode(const RefPtr<FrameNode>& textField)
    {
        textField_ = AceType::WeakClaim(AceType::RawPtr(textField));
    }

    void SetSearchIconNode(const RefPtr<FrameNode>& searchIcon)
    {
        searchIcon_ = AceType::WeakClaim(AceType::RawPtr(searchIcon));
    }

    void SetCancelIconNode(const RefPtr<FrameNode>& cancelIcon)
    {
        cancelIcon_ = AceType::WeakClaim(AceType::RawPtr(cancelIcon));
    }

    void SetSearchNode(const RefPtr<SearchNode>& searchNode)
    {
        searchNode_ = AceType::WeakClaim(AceType::RawPtr(searchNode));
    }

    RefPtr<FrameNode> GetSearchIconNode() const
    {
        return searchIcon_.Upgrade();
    }

    RefPtr<FrameNode> GetCancelIconNode() const
    {
        return cancelIcon_.Upgrade();
    }

    RefPtr<SearchNode> GetSearchNode() const
    {
        return searchNode_.Upgrade();
    }

    bool GetIsSearchButtonEnabled() const
    {
        return isSearchButtonEnabled_;
    }

    const SizeF GetButtonSize() const
    {
        return buttonSize_;
    }

    void ResetDragOption() override;
    void OnColorConfigurationUpdate() override;

    void SetSearchIconSize(const Dimension& value);
    void SetSearchIconColor(const Color& color);
    void SetSearchSrcPath(const std::string& src, const std::string& bundleName, const std::string& moduleName);
    void SetSearchSymbolIcon();
    void SetSearchImageIcon(IconOptions& iconOptions);
    void SetCancelSymbolIcon();
    void SetCancelImageIcon(IconOptions& iconOptions);
    void SetRightIconSrcPath(const std::string& src);
    void SetCancelButtonStyle(const CancelButtonStyle& cancelButtonStyle);
    void SetCancelIconSize(const Dimension& value);
    void SetCancelIconColor(const Color& color);
    void InitIconColorSize();
    void InitSearchIconColorSize();
    void InitCancelIconColorSize();
    void CreateSearchIcon(const std::string& src, bool forceUpdate = false);
    void CreateCancelIcon();
    const Dimension ConvertImageIconSizeValue(const Dimension& fontSizeValue);
    void UpdateDisable(const std::u16string& textValue);

private:
    void OnModifyDone() override;
    void OnAfterModifyDone() override;
    void SetAccessibilityAction();
    void SetAccessibilityClearAction();
    void SetSearchFieldAccessibilityAction();
    void SetSearchButtonAccessibilityAction();
    void InitButtonAndImageClickEvent();
    void InitCancelButtonClickEvent();
    void InitTextFieldClickEvent();
    void InitSearchController();
    void OnClickButtonAndImage();
    void OnClickCancelButton();
    void OnClickTextField();
    void HandleCaretPosition(int32_t caretPosition);
    void HandleTextContentRect(Rect& rect);
    int32_t HandleGetCaretIndex();
    NG::OffsetF HandleGetCaretPosition();
    int32_t HandleTextContentLines();
    void StopEditing();
    // Init key event
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    void PaintFocusState(bool recoverFlag = false);
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void RequestKeyboard();
    // Init touch and hover event
    void InitTextFieldValueChangeEvent();
    void InitTextFieldDragEvent();
    void RemoveDragFrameNodeFromManager();
    void InitButtonTouchEvent(RefPtr<TouchEventImpl>& touchEvent, int32_t childId);
    void InitButtonMouseEvent(RefPtr<InputEvent>& inputEvent, int32_t childId);
    void HandleBackgroundColor();
    void HandleEnabled();
    void HandleTouchableAndHitTestMode();
    void InitButtonMouseAndTouchEvent();
    void SetMouseStyle(MouseFormat format);
    void OnButtonTouchDown(int32_t childId);
    void OnButtonTouchUp(int32_t childId);
    void HandleButtonMouseEvent(bool isHover, int32_t childId);
    void ClearButtonStyle(int32_t childId);

    void ToJsonValueForTextField(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void ToJsonValueForSearchIcon(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void ToJsonValueForCancelButton(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void ToJsonValueForSearchButtonOption(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void ToJsonValueForCursor(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void ToJsonValueForCancelButtonStyle(
        std::unique_ptr<JsonValue>& cancelButtonJson, const CancelButtonStyle& cancelButtonStyle) const;
    std::string SymbolColorToString(std::vector<Color>& colors) const;

    void AnimateTouchAndHover(RefPtr<RenderContext>& renderContext, float startOpacity, float endOpacity,
        int32_t duration, const RefPtr<Curve>& curve);
    void InitFocusEvent(const RefPtr<FocusHub>& focusHub);
    void HandleFocusEvent(bool forwardFocusMovement, bool backwardFocusMovement);
    void HandleBlurEvent();
    void InitClickEvent();
    void HandleClickEvent(GestureEvent& info);
    void UpdateIconChangeEvent();
    bool IsEventEnabled(const std::u16string& textValue, int16_t style);

    void UpdateSearchSymbolIconColor();
    void UpdateCancelSymbolIconColor();

    void CreateOrUpdateSymbol(int32_t index, bool isCreateNode, bool isFromModifier);
    void CreateOrUpdateImage(int32_t index, bool isCreateNode);
    void UpdateImageIconProperties(RefPtr<FrameNode>& frameNode, int32_t index);
    void UpdateImageIconNode(int32_t index);
    void UpdateSymbolIconNode(int32_t index);
    void UpdateSymbolIconProperties(RefPtr<FrameNode>& frameNode, int32_t index);

    void CreateOrUpdateSymbol(int32_t index, bool isCreateNode);
    void CreateOrUpdateImage(int32_t index, const std::string& src, bool isCreateNode, const std::string& bundleName,
        const std::string& moduleName);
    void HandleImageLayoutProperty(RefPtr<FrameNode>& frameNode, int32_t index, const std::string& src,
        const std::string& bundleName, const std::string& moduleName);
    bool IsSymbolIcon(int32_t index);
    void UpdateIconNode(
        int32_t index, const std::string& src, const std::string& bundleName, const std::string& moduleName);
    void UpdateIconSrc(int32_t index, const std::string& src);
    void UpdateIconColor(int32_t index, const Color& color);
    void UpdateIconSize(int32_t index, const Dimension& value);
    void UpdateDivider();
    void UpdateCancelButton();
    void UpdateDividerColorMode();
    void UpdateCancelButtonColorMode();
    void UpdateCancelButtonStatus(const std::u16string& value, int16_t style = -1);

    bool IsSearchAttached();

    uint32_t GetMaxLength() const;
    std::string SearchTypeToString() const;
    std::string searchButton_;
    SizeF searchSize_;
    OffsetF searchOffset_;
    SizeF buttonSize_;
    OffsetF buttonOffset_;
    SizeF cancelButtonSize_;
    OffsetF cancelButtonOffset_;
    SizeF textFieldSize_;
    OffsetF textFieldOffset_;
    RefPtr<ClickEvent> imageClickListener_;
    RefPtr<ClickEvent> buttonClickListener_;
    RefPtr<ClickEvent> cancelButtonClickListener_;
    RefPtr<ClickEvent> textFieldClickListener_;
    RefPtr<TextFieldController> searchController_;
    FocusChoice focusChoice_ = FocusChoice::SEARCH;

    RefPtr<TouchEventImpl> searchButtonTouchListener_;
    RefPtr<TouchEventImpl> cancelButtonTouchListener_;
    RefPtr<InputEvent> searchButtonMouseEvent_;
    RefPtr<InputEvent> cancelButtonMouseEvent_;
    RefPtr<InputEvent> textFieldHoverEvent_ = nullptr;
    RefPtr<ClickEvent> clickListener_;

    bool isCancelButtonHover_ = false;
    bool isSearchButtonHover_ = false;
    bool isSearchButtonEnabled_ = false;

    WeakPtr<FrameNode> cancelButtonNode_;
    WeakPtr<FrameNode> buttonNode_;
    WeakPtr<FrameNode> textField_;
    WeakPtr<FrameNode> searchIcon_;
    WeakPtr<FrameNode> cancelIcon_;
    WeakPtr<SearchNode> searchNode_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_PATTERN_H
