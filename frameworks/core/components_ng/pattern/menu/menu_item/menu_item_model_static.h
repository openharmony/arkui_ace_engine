/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MODEL_STATIC_H

#include "core/components_ng/pattern/menu/menu_item/menu_item_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MenuItemModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetSelected(FrameNode* frameNode,  const std::optional<bool>& isSelected = false);
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
    static void AddChild(FrameNode* frameNode, const RefPtr<NG::UINode>& customNode);
    static void AddRowChild(FrameNode* frameNode, const MenuItemProperties& menuItemProps);
    static void UpdateMenuProperty(FrameNode* frameNode, const MenuItemProperties& menuItemProps);
    static void SetSelectedChangeEvent(FrameNode* frameNode, std::function<void(bool)>&& selectedChangeEvent);
private:
    static void DoMountRow(const RefPtr<NG::FrameNode>& menuItem);
    static void UpdateRadius(const RefPtr<NG::FrameNode>& menuItem);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MODEL_STATIC_H
