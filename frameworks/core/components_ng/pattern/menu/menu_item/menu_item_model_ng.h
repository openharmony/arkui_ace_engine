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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MODEL_NG_H

#include "core/components_ng/pattern/menu/menu_item/menu_item_model.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/property/menu_property.h"
#include "core/components/select/select_theme.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MenuItemModelNG : public OHOS::Ace::MenuItemModel {
public:
    void Create(const RefPtr<NG::UINode>& customNode) override;
    void Create(const MenuItemProperties& props) override;
    void SetSelected(bool isSelected = false) override;
    void SetSelectIcon(bool isShow = false) override;
    void SetSelectIconSrc(const std::string& src) override;
    void SetOnChange(std::function<void(bool)>&& onChange) override;
    void SetFontSize(const Dimension& fontSize) override;
    void SetFontWeight(FontWeight weight) override;
    void SetFontStyle(Ace::FontStyle style) override;
    void SetFontColor(const std::optional<Color>& color) override;
    void SetFontFamily(const std::vector<std::string> &families) override;
    void SetLabelFontSize(const Dimension& fontSize) override;
    void SetLabelFontWeight(FontWeight weight) override;
    void SetLabelFontStyle(Ace::FontStyle style) override;
    void SetLabelFontColor(const std::optional<Color>& color) override;
    void SetLabelFontFamily(const std::vector<std::string> &families) override;
    void SetSelectedChangeEvent(std::function<void(bool)>&& selectedChangeEvent) override;
    void SetSelectIconSymbol(std::function<void(WeakPtr<NG::FrameNode>)>&& symbolApply) override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetSelected(FrameNode* frameNode, bool isSelected = false);
    static void SetLabelFontColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetLabelFontSize(FrameNode* frameNode, const std::optional<Dimension>& fontSize);
    static void SetLabelFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& weight);
    static void SetLabelFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& families);
    static void SetLabelFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& style);
    static void SetFontColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& fontSize);
    static void SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& weight);
    static void SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& style);
    static void SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& families);
    static void SetSelectIcon(FrameNode* frameNode, bool isShow = false);
    static void SetSelectIconSrc(FrameNode* frameNode, const std::optional<std::string>& src);
    static void SetSelectIconSymbol(FrameNode* frameNode, std::function<void(WeakPtr<NG::FrameNode>)>&& symbolApply);
    static void SetOnChange(FrameNode* frameNode, std::function<void(bool)>&& onChange);
    static RefPtr<FrameNode> CreateMenuItem(OptionParam&& param, const MenuParam& menuParam);
    static void SetupMenuItemProperties(const RefPtr<FrameNode>& menuItem, const RefPtr<SelectTheme>& theme);
    static void AddChild(FrameNode* frameNode, const RefPtr<NG::UINode>& customNode);
    static void AddRowChild(FrameNode* frameNode, const MenuItemProperties& menuItemProps);
    static void UpdateMenuProperty(FrameNode* frameNode, const MenuItemProperties& menuItemProps);
    static void SetSelectedChangeEvent(FrameNode* frameNode, std::function<void(bool)>&& selectedChangeEvent);

private:
    void UpdateMenuProperty(const RefPtr<NG::FrameNode>& menuItem, const MenuItemProperties& menuItemProps);
    static void DoMountRow(const RefPtr<NG::FrameNode>& menuItem);
    static void UpdateRadius(const RefPtr<NG::FrameNode>& menuItem);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MODEL_NG_H
