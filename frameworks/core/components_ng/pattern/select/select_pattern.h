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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_SELECT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_SELECT_PATTERN_H

#include <cstdint>
#include <optional>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/option/option_paint_method.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select/select_accessibility_property.h"
#include "core/components_ng/pattern/select/select_event_hub.h"
#include "core/components_ng/pattern/select/select_layout_algorithm.h"
#include "core/components_ng/pattern/select/select_model.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/select/select_model_ng.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class SelectPattern : public Pattern {
    DECLARE_ACE_TYPE(SelectPattern, Pattern);

public:
    SelectPattern() = default;
    ~SelectPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<SelectAccessibilityProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SelectLayoutAlgorithm>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SelectEventHub>();
    }

    void BuildChild();

    void SetMenuNode(const RefPtr<FrameNode>& menuWrapper)
    {
        menuWrapper_ = menuWrapper;
    }

    const RefPtr<FrameNode>& GetMenuWrapper() const
    {
        return menuWrapper_;
    }

    RefPtr<FrameNode> GetMenuNode() const
    {
        CHECK_NULL_RETURN(menuWrapper_, nullptr);
        return DynamicCast<FrameNode>(menuWrapper_->GetChildAtIndex(0));
    }

    void SetSelectSize(const SizeF& selectSize)
    {
        selectSize_ = selectSize;
    }
    SizeF GetSelectSize() const
    {
        return selectSize_;
    }

    void AddOptionNode(const RefPtr<FrameNode>& option);

    void ClearOptions()
    {
        options_.clear();
    }

    void InitSelected()
    {
        selected_ = -1;
    }

    int32_t GetSelected() const
    {
        return selected_;
    }

    void SetSelected(int32_t index);

    // set properties of text node
    void SetValue(const std::string& value);
    void SetFontSize(const Dimension& value);
    void SetItalicFontStyle(const Ace::FontStyle& value);
    void SetFontWeight(const FontWeight& value);
    void SetFontFamily(const std::vector<std::string>& value);
    void SetFontColor(const Color& color);

    // set props of option nodes
    void SetOptionBgColor(const Color& color);
    void SetOptionFontSize(const Dimension& value);
    void SetOptionItalicFontStyle(const Ace::FontStyle& value);
    void SetOptionFontWeight(const FontWeight& value);
    void SetOptionFontFamily(const std::vector<std::string>& value);
    void SetOptionFontColor(const Color& color);

    // set props of option node when selected
    void SetSelectedOptionBgColor(const Color& color);
    void SetSelectedOptionFontSize(const Dimension& value);
    void SetSelectedOptionItalicFontStyle(const Ace::FontStyle& value);
    void SetSelectedOptionFontWeight(const FontWeight& value);
    void SetSelectedOptionFontFamily(const std::vector<std::string>& value);
    void SetSelectedOptionFontColor(const Color& color);

    // set props of menu background
    void SetMenuBackgroundColor(const Color& color);
    void SetMenuBackgroundBlurStyle(const BlurStyleOption& blurStyle);

    // Get functions for unit tests
    const std::vector<RefPtr<FrameNode>>& GetOptions();

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true, FocusStyleType::INNER_BORDER };
    }

    // update selected option props
    void UpdateSelectedProps(int32_t index);

    void UpdateLastSelectedProps(int32_t index);

    // reset options props when selected index is -1
    void ResetOptionProps();

    void SetBgBlendColor(const Color& color)
    {
        bgBlendColor_ = color;
    }

    Color GetBgBlendColor() const
    {
        return bgBlendColor_;
    }

    void SetIsHover(bool isHover)
    {
        isHover_ = isHover;
    }

    bool IsHover() const
    {
        return isHover_;
    }

    void SetItemSelected(int index, const std::string& value);
    void PlayBgColorAnimation(bool isHoverChange = true);
    void SetSpace(const Dimension& value);
    void SetArrowPosition(const ArrowPosition value);
    void SetMenuAlign(const MenuAlign& menuAlign);

    std::string GetValue();
    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;
    void OnColorConfigurationUpdate() override;
    void OnLanguageConfigurationUpdate() override;
    void ShowSelectMenu();
    
    Dimension GetFontSize();
    void SetOptionWidth(const Dimension& value);
    void SetOptionHeight(const Dimension& value);
    void SetOptionWidthFitTrigger(bool isFitTrigger);
    void SetHasOptionWidth(bool hasOptionWidth);
    void SetControlSize(const ControlSize& controlSize);
    void SetDivider(const SelectDivider& divider);
    ControlSize GetControlSize();
    void SetLayoutDirection(TextDirection value);

private:
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    void OnAfterModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    bool HasRowNode() const
    {
        return rowId_.has_value();
    }

    bool HasTextNode() const
    {
        return textId_.has_value();
    }

    bool HasSpinnerNode() const
    {
        return spinnerId_.has_value();
    }

    int32_t GetRowId()
    {
        if (!rowId_.has_value()) {
            rowId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return rowId_.value();
    }

    int32_t GetTextId()
    {
        if (!textId_.has_value()) {
            textId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return textId_.value();
    }

    int32_t GetSpinnerId()
    {
        if (!spinnerId_.has_value()) {
            spinnerId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return spinnerId_.value();
    }

    // change background color when pressed
    void RegisterOnPress();
    // change background color when hovered
    void RegisterOnHover();
    // add click event to show menu
    void RegisterOnClick();

    void RegisterOnKeyEvent();
    bool OnKeyEvent(const KeyEvent& event);

    // callback when an option is selected
    void CreateSelectedCallback();
    // change text and spinner color if disabled
    void SetDisabledStyle();

    // update text to selected option's text
    void UpdateText(int32_t index);

    void InitTextProps(const RefPtr<TextLayoutProperty>& textProps, const RefPtr<SelectTheme>& theme);
    void InitSpinner(
        const RefPtr<FrameNode>& spinner, const RefPtr<IconTheme>& iconTheme, const RefPtr<SelectTheme>& selectTheme);
    void InitSpinner(const RefPtr<FrameNode>& spinner, const RefPtr<SelectTheme>& selectTheme);
    void ResetParams();
    void UpdateOptionsWidth(float selectWidth);

    std::vector<RefPtr<FrameNode>> options_;
    RefPtr<FrameNode> menuWrapper_ = nullptr;
    RefPtr<FrameNode> text_ = nullptr;
    RefPtr<FrameNode> spinner_ = nullptr;
    SizeF selectSize_;

    // index of selected option
    int32_t selected_ = -1;
    // props when selected
    struct OptionFont {
        // text style when selected
        std::optional<Dimension> FontSize;
        std::optional<Ace::FontStyle> FontStyle;
        std::optional<FontWeight> FontWeight;
        std::optional<std::vector<std::string>> FontFamily;
        std::optional<Color> FontColor;
    };
    OptionFont selectedFont_;
    std::optional<Color> selectedBgColor_;
    OptionFont optionFont_;
    std::optional<Color> optionBgColor_;

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    void ToJsonArrowAndText(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void ToJsonOptionAlign(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void ToJsonMenuBackgroundStyle(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void ToJsonDivider(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    // XTS inspector helper functions
    std::string InspectorGetOptions() const;
    std::string InspectorGetSelectedFont() const;

    std::optional<int32_t> rowId_;
    std::optional<int32_t> textId_;
    std::optional<int32_t> spinnerId_;

    Color bgBlendColor_ = Color::TRANSPARENT;
    bool isHover_ = false;
    bool isSelected_ = false;
    MenuAlign menuAlign_;
    std::string selectValue_;
    bool isFitTrigger_ = false;
    ControlSize controlSize_ = ControlSize::NORMAL;
    ACE_DISALLOW_COPY_AND_MOVE(SelectPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_SELECT_PATTERN_H
