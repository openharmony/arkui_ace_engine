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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_MODEL_NG_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_content_model.h"
#include "core/components_ng/pattern/tabs/tab_content_node.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {

using TabBarBuilderFunc = std::function<void()>;

class ACE_EXPORT TabContentModelNG : public OHOS::Ace::TabContentModel {
public:
    void Create(std::function<void()>&& deepRenderFunc) override;
    void Create() override;
    void Pop() override;
    void CreateWithResourceObj(TabContentJsType jsType, const RefPtr<ResourceObject>& resObj) override;
    void CreatePaddingHorWithResourceObj(const RefPtr<ResourceObject>& resObjLeft,
        const RefPtr<ResourceObject>& resObjRight, bool isSubTabStyle, bool useLocalizedPadding) override;
    void CreatePaddingVerWithResourceObj(const RefPtr<ResourceObject>& resObjTop,
        const RefPtr<ResourceObject>& resObjBottom, bool isSubTabStyle, bool useLocalizedPadding) override;
    void SetTabBar(const std::optional<std::string> &text, const std::optional<std::string> &icon,
        const std::optional<TabBarSymbol> &tabBarSymbol, TabBarBuilderFunc &&builder, bool useContentOnly) override;
    void SetTabBarWithContent(const RefPtr<NG::UINode>& content) override;
    void SetTabBarStyle(TabBarStyle tabBarStyle) override;
    void SetIndicator(const IndicatorStyle& indicator) override;
    void SetIndicatorColorByUser(bool isByUser) override;
    void SetBoard(const BoardStyle& board) override;
    void SetSelectedMode(SelectedMode selectedMode) override;
    void SetLabelStyle(const LabelStyle& labelStyle) override;
    void SetLabelUnselectedColorByUser(bool isByUser) override;
    void SetLabelSelectedColorByUser(bool isByUser) override;
    void SetIconStyle(const IconStyle& iconStyle) override;
    void SetIconUnselectedColorByUser(bool isByUser) override;
    void SetIconSelectedColorByUser(bool isByUser) override;
    void SetPadding(const NG::PaddingProperty& padding) override;
    void SetUseLocalizedPadding(bool useLocalizedPadding) override;
    void SetLayoutMode(LayoutMode layoutMode) override;
    void SetVerticalAlign(FlexAlign verticalAlign) override;
    void SetSymmetricExtensible(bool isExtensible) override;
    void SetId(const std::string& id) override;
    static void AddTabBarItem(
        const RefPtr<UINode>& tabContent, int32_t position = DEFAULT_NODE_SLOT, bool update = false);
    static void RemoveTabBarItem(const RefPtr<TabContentNode>& tabContentNode);
    static RefPtr<TabsNode> FindTabsNode(const RefPtr<UINode>& tabContent);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetTabBarBuilder(FrameNode* node, TabBarBuilderFunc&& builder);
    static void SetTabBarLabel(FrameNode* node, const std::string& label);
    void SetOnWillShow(std::function<void()>&& onWillShow) override;
    void SetOnWillHide(std::function<void()>&& onWillHide) override;
    void SetCustomStyleNode(const RefPtr<NG::FrameNode>& customStyleNode) override;
    static void SetCustomTabBar(FrameNode* node, FrameNode* tabBar);
    static void UpdateDefaultSymbol(RefPtr<TabTheme>& tabTheme, RefPtr<TextLayoutProperty> symbolProperty);
    static void UpdateSymbolEffect(RefPtr<TextLayoutProperty> symbolProperty, bool isActive);
    static void SetOnWillShow(FrameNode* node,  std::function<void()>&& onWillShow);
    static void SetOnWillHide(FrameNode* node, std::function<void()>&& onWillHide);
    static bool CreateIconWithResourceObjWithKey(FrameNode* frameNode, const std::string key,
        const RefPtr<ResourceObject>& resObj);
    static bool CreatePaddingWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static bool CreateTextContentWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static bool CreatePaddingLeftWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObjLeft,
        bool isSubTabStyle = false, bool useLocalizedPadding = false);
    static bool CreatePaddingRightWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObjRight,
        bool isSubTabStyle = false, bool useLocalizedPadding = false);
    static bool CreatePaddingTopWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObjTop,
        bool isSubTabStyle = false, bool useLocalizedPadding = false);
    static bool CreatePaddingBottomWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObjBottom,
        bool isSubTabStyle = false, bool useLocalizedPadding = false);
    static bool CreateBoardStyleBorderRadiusWithResourceObj(FrameNode* frameNode,
        const RefPtr<ResourceObject>& resObj);
    static bool CreateIndicatorColorWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static bool CreateIndicatorHeightWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static bool CreateIndicatorWidthWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static bool CreateIndicatorBorderRadiusWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static bool CreateIndicatorMarginTopWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);

private:
    static void UpdateLabelStyle(const LabelStyle& labelStyle, RefPtr<TextLayoutProperty> textLayoutProperty);
    static void CreateMoreWithResourceObj(TabContentJsType jsType, FrameNode* frameNode,
        const RefPtr<ResourceObject>& resObj);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_MODEL_NG_H
