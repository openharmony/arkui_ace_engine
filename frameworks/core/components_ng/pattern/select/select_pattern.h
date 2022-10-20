/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/option/option_paint_method.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select/select_event_hub.h"
#include "core/components_ng/pattern/select/select_view.h"

namespace OHOS::Ace::NG {

class SelectPattern : public Pattern {
    DECLARE_ACE_TYPE(SelectPattern, Pattern);

public:
    SelectPattern() = default;
    ~SelectPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SelectEventHub>();
    }

    void BuildChild();

    void SetMenuNode(const RefPtr<FrameNode>& menu)
    {
        menu_ = menu;
    }

    void AddOptionNode(const RefPtr<FrameNode>& option)
    {
        CHECK_NULL_VOID(option);
        options_.push_back(option);
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

private:
    void OnModifyDone() override;

    // change background color when hovered
    void RegisterOnHover();
    // add click event to show menu
    void RegisterOnClick();
    // callback when an option is selected
    void CreateSelectedCallback();

    // update selected option props
    void UpdateSelectedProps(int32_t index);
    // update text to selected option's text
    void UpdateText(int32_t index);

    std::vector<RefPtr<FrameNode>> options_;
    RefPtr<FrameNode> menu_ = nullptr;
    RefPtr<FrameNode> text_ = nullptr;

    // index of selected option
    int32_t selected_ = -1;
    // props when selected
    struct SelectedFont {
        // text style when selected
        std::optional<Dimension> FontSize;
        std::optional<Ace::FontStyle> FontStyle;
        std::optional<FontWeight> FontWeight;
        std::optional<std::vector<std::string>> FontFamily;
        std::optional<Color> FontColor;
    };
    SelectedFont selectedFont_;
    std::optional<Color> selectedBgColor_;

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;
    // XTS inspector helper functions
    std::string InspectorGetOptions() const;
    std::string InspectorGetSelectedFont() const;

    ACE_DISALLOW_COPY_AND_MOVE(SelectPattern);
};

} // namespace OHOS::Ace::NG

#endif