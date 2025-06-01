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

#include "core/components_ng/pattern/tabs/tab_content_model_static.h"

#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_node.h"

namespace OHOS::Ace::NG {
void TabContentModelStatic::SetIndicator(FrameNode* frameNode, const std::optional<IndicatorStyle>& indicatorOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto frameNodePattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    if (indicatorOpt) {
        frameNodePattern->SetIndicatorStyle(indicatorOpt.value());
    } else {
        IndicatorStyle indicator;
        auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        RefPtr<TabTheme> tabTheme = pipeline->GetTheme<TabTheme>();
        if (tabTheme) {
            indicator.color = tabTheme->GetActiveIndicatorColor();
            indicator.height = tabTheme->GetActiveIndicatorWidth();
            indicator.marginTop = tabTheme->GetSubTabIndicatorGap();
        }
        frameNodePattern->SetIndicatorStyle(indicator);
    }
}

void TabContentModelStatic::SetLabelStyle(FrameNode* frameNode, const std::optional<LabelStyle>& labelStyleOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto frameNodePattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetLabelStyle(labelStyleOpt.value_or(LabelStyle()));
}

void TabContentModelStatic::SetSelectedMode(FrameNode* node, const std::optional<SelectedMode>& selectedMode)
{
    CHECK_NULL_VOID(node);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetSelectedMode(selectedMode.value_or(SelectedMode::INDICATOR));
}

void TabContentModelStatic::SetBoard(FrameNode* node, const std::optional<BoardStyle>& board)
{
    CHECK_NULL_VOID(node);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetBoardStyle(board.value_or(BoardStyle()));
}

void TabContentModelStatic::SetPadding(FrameNode* node, const std::optional<PaddingProperty>& padding)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetPadding(padding.value_or(PaddingProperty()));
}

void TabContentModelStatic::SetUseLocalizedPadding(FrameNode* node, bool useLocalizedPadding)
{
    CHECK_NULL_VOID(node);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetUseLocalizedPadding(useLocalizedPadding);
}

void TabContentModelStatic::SetId(FrameNode* node, const std::optional<std::string>& id)
{
    CHECK_NULL_VOID(node);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetId(id.value_or(""));
}

void TabContentModelStatic::SetTabBarStyle(FrameNode* node, TabBarStyle tabBarStyle)
{
    CHECK_NULL_VOID(node);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetTabBarStyle(tabBarStyle);
}

void TabContentModelStatic::SetTabBar(FrameNode* node, const std::optional<std::string>& label,
    const std::optional<std::string>& icon, TabBarBuilderFunc&& builder)
{
    CHECK_NULL_VOID(node);
    if (icon) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabContentLayoutProperty, Icon, icon.value(), node);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TabContentLayoutProperty, Icon, node);
    }
    if (label) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabContentLayoutProperty, Text, label.value(), node);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TabContentLayoutProperty, Text, node);
    }
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetTabBar(label.value_or(""), icon.value_or(""), std::nullopt, std::move(builder));
    auto tabsNode = AceType::DynamicCast<TabsNode>(node->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TabContentModelStatic::SetLayoutMode(FrameNode* node, const std::optional<LayoutMode>& layoutMode)
{
    CHECK_NULL_VOID(node);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetLayoutMode(layoutMode.value_or(LayoutMode::VERTICAL));
}

void TabContentModelStatic::SetVerticalAlign(FrameNode* node, const std::optional<FlexAlign>& verticalAlign)
{
    CHECK_NULL_VOID(node);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetVerticalAlign(verticalAlign.value_or(FlexAlign::CENTER));
}

void TabContentModelStatic::SetSymmetricExtensible(FrameNode* node, const std::optional<bool>& isExtensible)
{
    CHECK_NULL_VOID(node);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetSymmetricExtensible(isExtensible.value_or(false));
}

void TabContentModelStatic::SetIconStyle(FrameNode* node, const  std::optional<IconStyle>& iconStyle)
{
    CHECK_NULL_VOID(node);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetIconStyle(iconStyle.value_or(IconStyle()));
}

void TabContentModelStatic::SetOnWillShow(FrameNode* node, std::function<void()>&& onWillShow)
{
    CHECK_NULL_VOID(node);
    auto tabContentEventHub = node->GetEventHub<TabContentEventHub>();
    CHECK_NULL_VOID(tabContentEventHub);
    tabContentEventHub->SetOnWillShow(onWillShow);
}

void TabContentModelStatic::SetOnWillHide(FrameNode* node, std::function<void()>&& onWillHide)
{
    CHECK_NULL_VOID(node);
    auto tabContentEventHub = node->GetEventHub<TabContentEventHub>();
    CHECK_NULL_VOID(tabContentEventHub);
    tabContentEventHub->SetOnWillHide(onWillHide);
}

RefPtr<FrameNode> TabContentModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = TabContentNode::GetOrCreateTabContentNode(
        V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabContentPattern>(nullptr); });
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_RETURN(tabTheme, nullptr);
    auto layout = frameNode->GetLayoutProperty<TabContentLayoutProperty>();
    CHECK_NULL_RETURN(layout, nullptr);
    auto text = tabTheme->GetDefaultTabBarName();
    layout->UpdateText(text);
    layout->UpdateIcon("");
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->SetTabBar(text, "", std::nullopt, nullptr);
    pattern->SetTabBarWithContent(nullptr);
    return frameNode;
}
} // namespace OHOS::Ace::NG
