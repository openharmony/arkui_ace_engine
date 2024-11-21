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

#include "core/components_ng/pattern/tabs/tab_content_node.h"

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int DEFAULT_MAXLINES = 1;
} // namespace

void TabContentNode::OnAttachToMainTree(bool recursive)
{
    FrameNode::OnAttachToMainTree(recursive);
    if (!UseOffscreenProcess()) {
        ProcessTabBarItem();
    }
    FrameNode::OnOffscreenProcess(recursive);
}

void TabContentNode::OnDetachFromMainTree(bool recursive, PipelineContext* context)
{
    FrameNode::OnDetachFromMainTree(recursive, context);
    auto tabs = TabContentModelNG::FindTabsNode(Referenced::Claim(this));
    CHECK_NULL_VOID(tabs);

    if (!tabs->IsOnMainTree()) {
        return;
    }

    TabContentModelNG::RemoveTabBarItem(Referenced::Claim(this));
}

void TabContentNode::OnOffscreenProcess(bool recursive)
{
    ProcessTabBarItem();
    FrameNode::OnOffscreenProcess(recursive);
}

void TabContentNode::ProcessTabBarItem()
{
    auto tabs = TabContentModelNG::FindTabsNode(Referenced::Claim(this));
    CHECK_NULL_VOID(tabs);
    auto swiper = tabs->GetTabs();
    CHECK_NULL_VOID(swiper);
    auto myIndex = swiper->GetChildFlatIndex(GetId()).second;
    bool update = false;
#ifdef UICAST_COMPONENT_SUPPORTED
    do {
        auto container = Container::Current();
        CHECK_NULL_BREAK(container);
        auto distributedUI = container->GetDistributedUI();
        CHECK_NULL_BREAK(distributedUI);
        if (distributedUI->IsSinkMode()) {
            update = true;
        }
    } while (false);
#endif
    TabContentModelNG::AddTabBarItem(Referenced::Claim(this), myIndex, update);
}

RefPtr<TabContentNode> TabContentNode::GetOrCreateTabContentNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto node = GetFrameNode(tag, nodeId);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(node);

    if (tabContentNode) {
        return tabContentNode;
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    tabContentNode = AceType::MakeRefPtr<TabContentNode>(tag, nodeId, pattern, false);
    tabContentNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(tabContentNode);
    return tabContentNode;
}

void TabContentNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    FrameNode::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto tabBar = JsonUtil::Create(true);
    auto tabContentPattern = GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(tabContentPattern);

    auto indicator = JsonUtil::Create(true);
    auto indicatorStyle = tabContentPattern->GetIndicatorStyle();
    indicator->Put("color", indicatorStyle.color.ColorToString().c_str());
    indicator->Put("height", indicatorStyle.height.ToString().c_str());
    indicator->Put("width", indicatorStyle.width.ToString().c_str());
    indicator->Put("borderRadius", indicatorStyle.borderRadius.ToString().c_str());
    indicator->Put("marginTop", indicatorStyle.marginTop.ToString().c_str());
    tabBar->Put("indicator", indicator);

    auto board = JsonUtil::Create(true);
    auto boardStyle = tabContentPattern->GetBoardStyle();
    board->Put("borderRadius", boardStyle.borderRadius.ToString().c_str());
    tabBar->Put("board", board);

    tabBar->Put("selectedMode", tabContentPattern->GetSelectedMode() == SelectedMode::INDICATOR ?
		"SelectedMode.INDICATOR" : "SelectedMode.BOARD");

    auto font = JsonUtil::Create(true);
    auto labelStyle = tabContentPattern->GetLabelStyle();
    font->Put("size", labelStyle.fontSize.value_or(Dimension(0)).ToString().c_str());
    font->Put("weight",
        V2::ConvertWrapFontWeightToStirng(labelStyle.fontWeight.value_or(FontWeight::NORMAL)).c_str());
    std::vector<std::string> emptyFontFamily = { "HarmonyOS Sans" };
    auto fontFamilyVector = labelStyle.fontFamily.value_or(emptyFontFamily);
    std::string fontFamily = fontFamilyVector.at(0);
    for (uint32_t i = 1; i < fontFamilyVector.size(); ++i) {
        fontFamily += ',' + fontFamilyVector.at(i);
    }
    font->Put("family", fontFamily.c_str());
    font->Put("style", labelStyle.fontStyle.value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL
                                ? "FontStyle.Normal"
                                : "FontStyle.Italic");

    auto label = JsonUtil::Create(true);
    label->Put("overflow",
        V2::ConvertWrapTextOverflowToString(labelStyle.textOverflow.value_or(TextOverflow::ELLIPSIS)).c_str());
    label->Put("maxLines", std::to_string(labelStyle.maxLines.value_or(DEFAULT_MAXLINES)).c_str());
    label->Put("minFontSize", labelStyle.minFontSize.value_or(Dimension(0)).ToString().c_str());
    label->Put("maxFontSize", labelStyle.maxFontSize.value_or(Dimension(0)).ToString().c_str());
    label->Put("heightAdaptivePolicy", V2::ConvertWrapTextHeightAdaptivePolicyToString(
        labelStyle.heightAdaptivePolicy.value_or(TextHeightAdaptivePolicy::MAX_LINES_FIRST)).c_str());
    label->Put("font", font);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    label->Put("unselectedColor", labelStyle.unselectedColor.value_or(
        tabTheme->GetSubTabTextOffColor()).ColorToString().c_str());
    auto selectColor = tabContentPattern->GetSelectedMode() == SelectedMode::BOARD &&
        GetTabBarAxis() == Axis::HORIZONTAL ? tabTheme->GetSubTabBoardTextOnColor() : tabTheme->GetSubTabTextOnColor();
    label->Put("selectedColor", labelStyle.selectedColor.value_or(selectColor).ColorToString().c_str());
    tabBar->Put("labelStyle", label);

    auto iconStyle = tabContentPattern->GetIconStyle();
    auto icon = JsonUtil::Create(true);
    icon->Put("unselectedColor", iconStyle.unselectedColor.value_or(
        tabTheme->GetBottomTabIconOff()).ColorToString().c_str());
    icon->Put("selectedColor", iconStyle.selectedColor.value_or(
        tabTheme->GetBottomTabIconOn()).ColorToString().c_str());
    tabBar->Put("iconStyle", icon);

    tabBar->Put("padding", tabContentPattern->GetPadding().ToJsonString().c_str());
    tabBar->Put(
        "verticalAlign", ConvertFlexAlignToString(tabContentPattern->GetBottomTabBarStyle().verticalAlign).c_str());
    tabBar->Put("layoutMode", ConvertLayoutModeToString(tabContentPattern->GetBottomTabBarStyle().layoutMode).c_str());
    tabBar->Put(
        "symmetricExtensible", tabContentPattern->GetBottomTabBarStyle().symmetricExtensible ? "true" : "false");
    tabBar->Put("id", tabContentPattern->GetId().c_str());

    json->PutExtAttr("tabBar", tabBar, filter);
}

Axis TabContentNode::GetTabBarAxis() const
{
    if (!tabBarItemId_.has_value()) {
        return Axis::HORIZONTAL;
    }
    auto columnNode = GetFrameNode(V2::COLUMN_ETS_TAG, tabBarItemId_.value());
    CHECK_NULL_RETURN(columnNode, Axis::HORIZONTAL);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(columnNode->GetParent());
    CHECK_NULL_RETURN(tabBarNode, Axis::HORIZONTAL);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarLayoutProperty, Axis::HORIZONTAL);
    return tabBarLayoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
}

std::string TabContentNode::ConvertFlexAlignToString(FlexAlign verticalAlign) const
{
    if (verticalAlign == FlexAlign::FLEX_START) {
        return "VerticalAlign.Top";
    } else if (verticalAlign == FlexAlign::FLEX_END) {
        return "VerticalAlign.Bottom";
    }
    return "VerticalAlign.Center";
}

std::string TabContentNode::ConvertLayoutModeToString(LayoutMode layoutMode) const
{
    if (layoutMode == LayoutMode::VERTICAL) {
        return "LayoutMode.VERTICAL";
    } else if (layoutMode == LayoutMode::HORIZONTAL) {
        return "LayoutMode.HORIZONTAL";
    }
    return "LayoutMode.AUTO";
}
} // namespace OHOS::Ace::NG
