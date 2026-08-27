/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tabs_side_bar_tab_list_pattern.h"

#include <algorithm>

#include "base/utils/utils.h"
#include "base/utils/utf_helper.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/interfaces/native/node/node_button_modifier.h"

namespace OHOS::Ace::NG {
namespace {
const Dimension DEFAULT_TAB_BAR_ITEM_HEIGHT = 56.0_vp;
const Dimension SIDEBAR_TAB_ICON_TEXT_GAP = 16.0_vp;
const Dimension SIDEBAR_TAB_LEFT_RIGHT_PADDING = 8.0_vp;
}

void TabsSideBarTabListPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
}

void TabsSideBarTabListPattern::SetCurrentIndex(int32_t index)
{
    if (currentIndex_ == index) {
        return;
    }
    int32_t prevIndex = currentIndex_;
    currentIndex_ = index;

    // Cancel old selected item highlight
    UpdateTabItemStyle(prevIndex, false);
    // Set new selected item highlight
    UpdateTabItemStyle(index, true);

    // Notify Swiper to switch page
    if (swiperController_) {
        swiperController_->SwipeTo(index);
    }

    UpdateTabItemTextAndIconColor(index);
}

void TabsSideBarTabListPattern::UpdateTabItemTextAndIconColor(int32_t selectedIndex)
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto scrollNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0));
    CHECK_NULL_VOID(scrollNode);
    auto columnNode = AceType::DynamicCast<FrameNode>(scrollNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(columnNode);
    int32_t childCount = columnNode->GetTotalChildCount();
    auto tabsNode = AceType::DynamicCast<TabsNode>(tabsNode_.Upgrade());
    CHECK_NULL_VOID(tabsNode);
    auto tabTheme = tabsNode->GetTheme<TabTheme>(true);
    CHECK_NULL_VOID(tabTheme);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    for (int32_t index = 0; index < childCount; index++) {
        auto tabItemNode = DynamicCast<FrameNode>(columnNode->GetChildAtIndex(index));
        CHECK_NULL_CONTINUE(tabItemNode);
        auto tabContentNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildByIndex(index));
        CHECK_NULL_CONTINUE(tabContentNode);
        auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
        CHECK_NULL_CONTINUE(tabContentPattern);
        const auto& tabBarParam = tabContentPattern->GetTabBarParam();

        if (tabBarParam.HasContent() || tabBarParam.HasBuilder()) {
            continue;
        }
        
        bool isSelected = (index == selectedIndex);
        Color textColor = isSelected ? tabTheme->GetSideBarSelectedTextColor() :
            tabTheme->GetSideBarUnselectedTextColor();
        Color iconColor = isSelected ? tabTheme->GetSideBarSelectedIconColor() :
            tabTheme->GetSideBarUnselectedIconColor();
        auto rowNode = AceType::DynamicCast<FrameNode>(tabItemNode->GetChildren().front());
        CHECK_NULL_CONTINUE(rowNode);
        UpdateTextColorAndIconColor(rowNode, textColor, iconColor, isSelected);
    }
}

void TabsSideBarTabListPattern::UpdateTextColorAndIconColor(const RefPtr<FrameNode>& rowNode,
    Color textColor, Color iconColor, bool isSelected)
{
    auto iconNode = AceType::DynamicCast<FrameNode>(rowNode->GetChildren().front());
    CHECK_NULL_VOID(iconNode);
    auto textNode = AceType::DynamicCast<FrameNode>(rowNode->GetChildren().back());
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto imagePaintProperty = iconNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imagePaintProperty);

    auto tabsNode = AceType::DynamicCast<TabsNode>(tabsNode_.Upgrade());
    CHECK_NULL_VOID(tabsNode);
    auto tabLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    if (isSelected) {
        if (tabLayoutProperty && tabLayoutProperty->GetSidebarSelectedTextColor().has_value()) {
            textColor = tabLayoutProperty->GetSidebarSelectedTextColor().value();
        }
        if (tabLayoutProperty && tabLayoutProperty->GetSidebarSelectedIconColor().has_value()) {
            iconColor = tabLayoutProperty->GetSidebarSelectedIconColor().value();
        }
    } else {
        if (tabLayoutProperty && tabLayoutProperty->GetSidebarUnselectedTextColor().has_value()) {
            textColor = tabLayoutProperty->GetSidebarUnselectedTextColor().value();
        }
        if (tabLayoutProperty && tabLayoutProperty->GetSidebarUnselectedIconColor().has_value()) {
            iconColor = tabLayoutProperty->GetSidebarUnselectedIconColor().value();
        }
    }

    textLayoutProperty->UpdateTextColor(textColor);
    imagePaintProperty->UpdateSvgFillColor(iconColor);
    textNode->MarkModifyDone();
    textNode->MarkDirtyNode();
    iconNode->MarkModifyDone();
    iconNode->MarkDirtyNode();
}

void TabsSideBarTabListPattern::InitCurrentIndex(int32_t index)
{
    // Initialize current index without triggering Swiper animation
    // Used when SideBar is first created or after mode switch
    if (currentIndex_ == index) {
        return;
    }
    int32_t prevIndex = currentIndex_;
    currentIndex_ = index;
    UpdateTabItemStyle(prevIndex, false);
    UpdateTabItemStyle(index, true);
}

void TabsSideBarTabListPattern::UpdateTabItemStyle(int32_t index, bool selected)
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto tabTheme = host->GetTheme<TabTheme>(true);
    CHECK_NULL_VOID(tabTheme);
    auto scrollNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0));
    CHECK_NULL_VOID(scrollNode);
    auto columnNode = AceType::DynamicCast<FrameNode>(scrollNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(columnNode);
    if (index < 0 || index >= static_cast<int32_t>(columnNode->GetChildren().size())) {
        return;
    }
    auto itemNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildAtIndex(index));
    CHECK_NULL_VOID(itemNode);
    auto renderContext = itemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto color = selected ? tabTheme->GetSideBarListItemActivedColor() : Color::TRANSPARENT;
    if (selected) {
        auto tabsNode = AceType::DynamicCast<TabsNode>(tabsNode_.Upgrade());
        if (tabsNode) {
            auto tabLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
            if (tabLayoutProperty && tabLayoutProperty->GetSidebarSelectedBoardColor().has_value()) {
                color = tabLayoutProperty->GetSidebarSelectedBoardColor().value();
            }
        }
    }
    renderContext->UpdateBackgroundColor(color);
    itemNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TabsSideBarTabListPattern::ApplySearchFilter(
    std::function<bool(int32_t, const std::string& text)> searchFilter, const std::u16string& searchText)
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(tabsNode_.Upgrade());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto tabContentNum = swiperNode->TotalChildCount();
    if (host->GetChildren().empty()) {
        return;
    }
    auto scrollNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(scrollNode);
    if (scrollNode->GetChildren().empty()) {
        return;
    }
    auto columnNode = AceType::DynamicCast<FrameNode>(scrollNode->GetChildren().front());
    CHECK_NULL_VOID(columnNode);
    auto children = columnNode->GetChildren();
    int32_t tabIndex = 0;
    // Pre-compute searchText lowercase and UTF-8 conversion outside loop
    auto toLowerU16 = [](std::u16string str) {
        for (auto& ch : str) {
            if (ch >= u'A' && ch <= u'Z') {
                ch += (u'a' - u'A');
            }
        }
        return str;
    };
    auto searchTextLower = toLowerU16(searchText);
    auto searchText8 = UtfUtils::Str16ToStr8(searchText);
    for (auto it = children.begin(); it != children.end(); ++it, ++tabIndex) {
        auto itemNode = AceType::DynamicCast<FrameNode>(*it);
        CHECK_NULL_CONTINUE(itemNode);
        auto property = itemNode->GetLayoutProperty();
        CHECK_NULL_CONTINUE(property);
        bool isVisible = true;
        do {
            if (searchText.empty()) {
                break;
            }
            if (searchFilter) {
                isVisible = searchFilter(tabIndex, searchText8);
                break;
            }
            // Default: fuzzy match by tab text (Unicode-aware case-insensitive)
            if (tabIndex >= tabContentNum) {
                break;
            }
            auto tabContentNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildByIndex(tabIndex));
            CHECK_NULL_BREAK(tabContentNode);
            auto pattern = tabContentNode->GetPattern<TabContentPattern>();
            CHECK_NULL_BREAK(pattern);
            auto tabTextLower = toLowerU16(UtfUtils::Str8ToStr16(pattern->GetTabBarParam().GetText()));
            isVisible = tabTextLower.find(searchTextLower) != std::u16string::npos;
        } while (false);
        property->UpdateVisibility(isVisible ? VisibleType::VISIBLE : VisibleType::GONE);
    }
    host->MarkNeedSyncRenderTree();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TabsSideBarTabListPattern::AddOrUpdateTabItemWithContent(
    const TabBarParam& tabBarParam, const RefPtr<FrameNode>& tabItemNode, int32_t tabContentId, int32_t myIndex)
{
    CHECK_NULL_VOID(tabItemNode);
    auto tabItemContainerNode = GetTabItemContainerNode();
    CHECK_NULL_VOID(tabItemContainerNode);
    ScopedViewStackProcessor builderViewStackProcessor;
    auto builderNode = tabBarParam.GetContent().Upgrade();
    CHECK_NULL_VOID(builderNode);
    if (!tabItemNode->GetChildren().empty()) {
        tabItemNode->Clean();
    }
    if (builderNode) {
        builderNode->MountToParent(tabItemNode);
    }
    auto oldTabItemNode = GetBuilderByContentId(tabContentId, tabItemNode);
    if (!oldTabItemNode) {
        auto index =
            std::clamp(myIndex, 0, static_cast<int32_t>(tabItemContainerNode->GetChildren().size()));
        tabItemNode->MountToParent(tabItemContainerNode, index);
    } else if (oldTabItemNode != tabItemNode) {
        tabItemContainerNode->ReplaceChild(oldTabItemNode, tabItemNode);
    }
    auto tabBarItemPadding = Dimension(0);
    auto layoutProperty = tabItemNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdatePadding({ CalcLength(tabBarItemPadding), CalcLength(tabBarItemPadding),
        CalcLength(tabBarItemPadding), CalcLength(tabBarItemPadding), {}, {} });
    tabItemNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    tabItemContainerNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TabsSideBarTabListPattern::AddOrUpdateTabItemWithBuilder(
    const TabBarParam& tabBarParam, const RefPtr<FrameNode>& tabItemNode, int32_t tabContentId, int32_t myIndex)
{
    CHECK_NULL_VOID(tabItemNode);
    auto tabItemContainerNode = GetTabItemContainerNode();
    CHECK_NULL_VOID(tabItemContainerNode);
    ScopedViewStackProcessor builderViewStackProcessor;
    tabBarParam.ExecuteBuilder();
    auto builderNode = ViewStackProcessor::GetInstance()->Finish();
    if (!tabItemNode->GetChildren().empty()) {
        tabItemNode->Clean();
    }
    if (builderNode) {
        builderNode->MountToParent(tabItemNode);
    }
    auto oldTabItemNode = GetBuilderByContentId(tabContentId, tabItemNode);
    if (!oldTabItemNode) {
        auto index = std::clamp(myIndex, 0, static_cast<int32_t>(tabItemContainerNode->GetChildren().size()));
        tabItemNode->MountToParent(tabItemContainerNode, index);
    } else if (oldTabItemNode != tabItemNode) {
        tabItemContainerNode->ReplaceChild(oldTabItemNode, tabItemNode);
    }
    tabItemNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    tabItemContainerNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TabsSideBarTabListPattern::CreateOrUpdateTabItemTextAndIcon(
    const TabBarParam& tabBarParam, const RefPtr<FrameNode>& tabItemNode,
    const RefPtr<TabContentPattern>& tabContentPattern, int32_t position,
    RefPtr<FrameNode>& iconNode, RefPtr<FrameNode>& textNode)
{
    CHECK_NULL_VOID(tabItemNode);
    CHECK_NULL_VOID(tabContentPattern);
    auto tabItemContainerNode = GetTabItemContainerNode();
    CHECK_NULL_VOID(tabItemContainerNode);
    RefPtr<FrameNode> rowNode = nullptr;
    if (tabItemNode->GetChildren().size() != 1 || !tabItemNode->GetChildren().front() ||
        tabItemNode->GetChildren().front()->GetTag() != V2::ROW_ETS_TAG) {
        tabItemNode->Clean();
        rowNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto linearLayoutProperty = rowNode->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_VOID(linearLayoutProperty);
        linearLayoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
        linearLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
        linearLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
        linearLayoutProperty->SetIsVertical(false);
        // Row fills TabItem width & height so icon+text content area covers the full item
        linearLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        rowNode->MountToParent(tabItemNode);
    } else {
        rowNode = AceType::DynamicCast<FrameNode>(tabItemNode->GetChildren().front());
    }
    CHECK_NULL_VOID(rowNode);
    auto tabBarStyle = tabContentPattern->GetTabBarStyle();
    bool isFrameNode = tabBarStyle == TabBarStyle::SUBTABBATSTYLE && tabContentPattern->HasSubTabBarStyleNode();
    if (rowNode->GetChildren().empty()) {
        if (tabBarParam.GetSymbol().has_value()) {
            iconNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        } else {
            iconNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
        }
        if (isFrameNode) {
            textNode = tabContentPattern->FireCustomStyleNode();
        } else {
            textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        }
        CHECK_NULL_VOID(textNode);
        CHECK_NULL_VOID(iconNode);
        // Text uses layoutWeight(1) to fill remaining Row width after icon+margin,
        // so it won't overflow Row and ellipsis works when text is too long.
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        if (textLayoutProperty) {
            textLayoutProperty->UpdateLayoutWeight(1);
        }
        // Set margin-right on icon to create gap between icon and text
        auto iconLayoutProperty = iconNode->GetLayoutProperty();
        if (iconLayoutProperty) {
            MarginProperty margin;
            margin.right = CalcLength(SIDEBAR_TAB_ICON_TEXT_GAP);
            iconLayoutProperty->UpdateMargin(margin);
        }
        iconNode->MountToParent(rowNode);
        textNode->MountToParent(rowNode);
        // Row mounts to ColumnNode (not directly to tabListNode)
        auto index = std::clamp(position, 0, static_cast<int32_t>(tabItemContainerNode->GetChildren().size()));
        tabItemNode->MountToParent(tabItemContainerNode, index);
        return;
    }
    if (isFrameNode) {
        auto builderNode = tabContentPattern->FireCustomStyleNode();
        rowNode->ReplaceChild(AceType::DynamicCast<FrameNode>(rowNode->GetChildren().back()), builderNode);
    }
    auto oldIcon = AceType::DynamicCast<FrameNode>(rowNode->GetChildren().front());
    CHECK_NULL_VOID(oldIcon);
    if (tabBarParam.GetSymbol().has_value() && oldIcon->GetTag() != V2::SYMBOL_ETS_TAG) {
        auto icon = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        rowNode->ReplaceChild(oldIcon, icon);
    } else if (!tabBarParam.GetIcon().empty() && oldIcon->GetTag() != V2::IMAGE_ETS_TAG) {
        auto icon = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
        rowNode->ReplaceChild(oldIcon, icon);
    }
    iconNode = AceType::DynamicCast<FrameNode>(rowNode->GetChildren().front());
    textNode = AceType::DynamicCast<FrameNode>(rowNode->GetChildren().back());
    // Set margin-right on icon for icon-text gap
    if (iconNode) {
        auto iconLayoutProperty = iconNode->GetLayoutProperty();
        if (iconLayoutProperty) {
            MarginProperty margin;
            margin.right = CalcLength(SIDEBAR_TAB_ICON_TEXT_GAP);
            iconLayoutProperty->UpdateMargin(margin);
        }
    }
    rowNode->MarkModifyDone();
}

void TabsSideBarTabListPattern::UpdateTabBarItemTextProperties(
    const TabBarParam& tabBarParam, const RefPtr<FrameNode>& textNode,
    const RefPtr<SwiperPattern>& swiperPattern, const RefPtr<TabContentPattern>& tabContentPattern,
    int32_t myIndex, int32_t indicator)
{
    CHECK_NULL_VOID(textNode);
    CHECK_NULL_VOID(tabContentPattern);
    CHECK_NULL_VOID(swiperPattern);
    auto tabsNode = AceType::DynamicCast<TabsNode>(tabsNode_.Upgrade());
    CHECK_NULL_VOID(tabsNode);
    auto tabTheme = tabsNode->GetTheme<TabTheme>(true);
    CHECK_NULL_VOID(tabTheme);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    TabContentModelNG::InitTabText(textLayoutProperty);
    auto tabBarStyle = tabContentPattern->GetTabBarStyle();
    bool isFrameNode = tabBarStyle == TabBarStyle::SUBTABBATSTYLE && tabContentPattern->HasSubTabBarStyleNode();
    auto labelStyle = tabContentPattern->GetLabelStyle();

    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    textRenderContext->UpdateClipEdge(true);
    if (!isFrameNode) {
        textLayoutProperty->UpdateContent(tabBarParam.GetText());
        textLayoutProperty->UpdateFontSize(tabTheme->GetSubTabTextDefaultFontSize());
        textLayoutProperty->UpdateTextAlign(TextAlign::START); // Left-aligned (Row layout)
        textLayoutProperty->UpdateMaxLines(1);
        textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    }
    if (!tabBarParam.GetIcon().empty()) {
        textLayoutProperty->UpdateFontSize(tabTheme->GetBottomTabTextSize());
    }
    if (!isFrameNode) {
        TabContentModelNG::UpdateLabelStyle(labelStyle, textLayoutProperty);
    }

    bool isSelected = (myIndex == indicator);
    Color textColor = isSelected ? tabTheme->GetSideBarSelectedTextColor() :
        tabTheme->GetSideBarUnselectedTextColor();
    auto tabLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    if (isSelected) {
        if (tabLayoutProperty && tabLayoutProperty->GetSidebarSelectedTextColor().has_value()) {
            textColor = tabLayoutProperty->GetSidebarSelectedTextColor().value();
        }
    } else {
        if (tabLayoutProperty && tabLayoutProperty->GetSidebarUnselectedTextColor().has_value()) {
            textColor = tabLayoutProperty->GetSidebarUnselectedTextColor().value();
        }
    }
    textLayoutProperty->UpdateTextColor(textColor);
}

void TabsSideBarTabListPattern::UpdateTabBarItemIconProperties(
    const TabBarParam& tabBarParam, const RefPtr<FrameNode>& iconNode,
    const RefPtr<TabContentPattern>& tabContentPattern, int32_t myIndex, int32_t indicator)
{
    CHECK_NULL_VOID(iconNode);
    CHECK_NULL_VOID(tabContentPattern);
    auto tabsNode = AceType::DynamicCast<TabsNode>(tabsNode_.Upgrade());
    CHECK_NULL_VOID(tabsNode);
    auto tabTheme = tabsNode->GetTheme<TabTheme>(true);
    CHECK_NULL_VOID(tabTheme);
    if (tabBarParam.GetSymbol().has_value()) {
        auto symbolProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolProperty);
        TabContentModelNG::UpdateDefaultSymbol(tabTheme, symbolProperty);
        auto modifierOnApply = tabBarParam.GetSymbol().value().onApply;
        if (modifierOnApply != nullptr) {
            modifierOnApply(AceType::WeakClaim(AceType::RawPtr(iconNode)), "normal");
            TabContentModelNG::UpdateDefaultSymbol(tabTheme, symbolProperty);
        }
        if (modifierOnApply != nullptr && tabBarParam.GetSymbol().value().selectedFlag && myIndex == indicator) {
            modifierOnApply(AceType::WeakClaim(AceType::RawPtr(iconNode)), "selected");
            TabContentModelNG::UpdateSymbolEffect(symbolProperty, false);
        }
        return;
    }
    auto imageProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageProperty);
    if (!tabBarParam.GetIcon().empty()) {
        imageProperty->UpdateUserDefinedIdealSize(CalcSize(
            CalcLength(tabTheme->GetBottomTabImageSize()), CalcLength(tabTheme->GetBottomTabImageSize())));
    } else {
        imageProperty->UpdateUserDefinedIdealSize(CalcSize());
    }
    ImageSourceInfo imageSourceInfo(tabBarParam.GetIcon());
    imageProperty->UpdateImageSourceInfo(imageSourceInfo);

    auto tabLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    auto imagePaintProperty = iconNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imagePaintProperty);
    bool isSelected = (myIndex == indicator);
    Color iconColor = isSelected ? tabTheme->GetSideBarSelectedIconColor() :
        tabTheme->GetSideBarUnselectedIconColor();
    if (isSelected) {
        if (tabLayoutProperty && tabLayoutProperty->GetSidebarSelectedIconColor().has_value()) {
            iconColor = tabLayoutProperty->GetSidebarSelectedIconColor().value();
        }
    } else {
        if (tabLayoutProperty && tabLayoutProperty->GetSidebarUnselectedIconColor().has_value()) {
            iconColor = tabLayoutProperty->GetSidebarUnselectedIconColor().value();
        }
    }
    imagePaintProperty->UpdateSvgFillColor(iconColor);
}

void TabsSideBarTabListPattern::AddOrUpdateTabItemWithIconAndText(
    const TabBarParam& tabBarParam, const RefPtr<FrameNode>& tabItemNode, const RefPtr<FrameNode>& swiperNode,
    const RefPtr<TabContentPattern>& tabContentPattern, int32_t position, int32_t myIndex)
{
    CHECK_NULL_VOID(tabItemNode);
    CHECK_NULL_VOID(swiperNode);
    CHECK_NULL_VOID(tabContentPattern);
    auto tabsNode = AceType::DynamicCast<TabsNode>(tabsNode_.Upgrade());
    CHECK_NULL_VOID(tabsNode);
    auto tabItemNodeProperty = tabItemNode->GetLayoutProperty();
    CHECK_NULL_VOID(tabItemNodeProperty);
    tabItemNodeProperty->MarkUserDefinedHeightConfigured();
    std::optional<CalcLength> width = std::nullopt;
    auto&& layoutConstraint = tabItemNodeProperty->GetCalcLayoutConstraint();
    if (layoutConstraint && layoutConstraint->selfIdealSize) {
        width = layoutConstraint->selfIdealSize->Width();
    }
    std::optional<CalcLength> height = CalcLength(DEFAULT_TAB_BAR_ITEM_HEIGHT);
    tabItemNodeProperty->UpdateUserDefinedIdealSize(CalcSize(width, height));

    auto tabLayoutProperty = AceType::DynamicCast<TabsLayoutProperty>(tabsNode->GetLayoutProperty());
    CHECK_NULL_VOID(tabLayoutProperty);
    RefPtr<FrameNode> iconNode;
    RefPtr<FrameNode> textNode;
    CreateOrUpdateTabItemTextAndIcon(tabBarParam, tabItemNode, tabContentPattern, position, iconNode, textNode);
    CHECK_NULL_VOID(textNode);
    CHECK_NULL_VOID(iconNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    int32_t indicator = 0;
    if (tabLayoutProperty->GetIndexSetByUser().has_value()) {
        indicator = tabLayoutProperty->GetIndexSetByUser().value();
    } else if (swiperLayoutProperty->GetIndex().has_value()) {
        indicator = swiperLayoutProperty->GetIndex().value();
    }
    int32_t totalCount = swiperPattern->TotalCount();
    if (indicator > totalCount - 1 || indicator < 0) {
        indicator = 0;
    }
    // Update text properties
    UpdateTabBarItemTextProperties(tabBarParam, textNode, swiperPattern, tabContentPattern, myIndex, indicator);
    // Update property of image/symbol.
    UpdateTabBarItemIconProperties(tabBarParam, iconNode, tabContentPattern, myIndex, indicator);

    tabItemNode->MarkModifyDone();
    textNode->MarkModifyDone();
    textNode->MarkDirtyNode();
    iconNode->MarkModifyDone();
}

RefPtr<FrameNode> TabsSideBarTabListPattern::GetOrCreateTabItemNode(int32_t id)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(tabsNode_.Upgrade());
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabTheme = tabsNode->GetTheme<TabTheme>(true);
    CHECK_NULL_RETURN(tabTheme, nullptr);
    auto* buttonModifier = NodeModifier::GetButtonCustomModifier();
    CHECK_NULL_RETURN(buttonModifier, nullptr);
    auto tabItemNode = FrameNode::GetOrCreateFrameNode("TabsSideBarTabItem", id,
        []() -> RefPtr<Pattern> {
            RefPtr<Pattern> buttonPattern = nullptr;
            auto* buttonModifier = NodeModifier::GetButtonCustomModifier();
            CHECK_NULL_RETURN(buttonModifier, buttonPattern);
            return AceType::Claim(reinterpret_cast<Pattern*>(buttonModifier->createButtonPattern()));
        });
    CHECK_NULL_RETURN(tabItemNode, nullptr);
    auto nodeHandle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(tabItemNode));
    buttonModifier->updateBackgroundColorFlagByUserToLayoutProp(nodeHandle, true);
    buttonModifier->setBlendColor(
        nodeHandle, tabTheme->GetSideBarListItemPressedColor(), tabTheme->GetSideBarListItemHoverColor());
    buttonModifier->setFocusBorderColor(nodeHandle, tabTheme->GetSideBarListItemFocusColor());
    buttonModifier->setFocusBorderWidth(nodeHandle, tabTheme->GetSideBarListItemFocusWidth());
    buttonModifier->updateTypeToLayoutProp(nodeHandle, ButtonType::NORMAL);
    auto radius = tabTheme->GetSideBarListItemCornerRadius();
    buttonModifier->setButtonBorderRadius(nodeHandle, radius, radius, radius, radius);
    auto property = tabItemNode->GetLayoutProperty();
    CHECK_NULL_RETURN(property, nullptr);
    PaddingProperty padding;
    padding.left = CalcLength(SIDEBAR_TAB_LEFT_RIGHT_PADDING);
    padding.right = CalcLength(SIDEBAR_TAB_LEFT_RIGHT_PADDING);
    property->UpdatePadding(padding);
    property->UpdateUserDefinedIdealSize(CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), std::nullopt));
    return tabItemNode;
}

void TabsSideBarTabListPattern::AddOrUpdateTabListItem(
    const RefPtr<FrameNode>& tabContent, int32_t position, bool update)
{
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContent);
    CHECK_NULL_VOID(tabContentNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(tabsNode_.Upgrade());
    CHECK_NULL_VOID(tabsNode);
    auto tabsProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsProperty);
    auto tabContentId = tabContentNode->GetId();
    // Get tabBarParam
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(tabContentPattern);
    const auto& tabBarParam = tabContentPattern->GetTabBarParam();

    // Get ColumnNode (mounting target for Row tab items)
    auto tabItemContainerNode = GetTabItemContainerNode();
    CHECK_NULL_VOID(tabItemContainerNode);
    // Use independent sideBarTabBarItemId (avoid ID collision with bottom TabBar)
    int32_t sideBarTabBarItemId = tabContentNode->GetSideBarTabBarItemId();
    auto tabItemNode = GetOrCreateTabItemNode(sideBarTabBarItemId);
    CHECK_NULL_VOID(tabItemNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto myIndex = swiperNode->GetChildFlatIndex(tabContentId).second;
    if (tabBarParam.HasContent()) {
        // Create tab bar with content.
        AddOrUpdateTabItemWithContent(tabBarParam, tabItemNode, tabContentId, myIndex);
    } else if (tabBarParam.HasBuilder()) {
        // Create tab bar with builder.
        AddOrUpdateTabItemWithBuilder(tabBarParam, tabItemNode, tabContentId, myIndex);
    } else {
        // Create icon and text child nodes
        AddOrUpdateTabItemWithIconAndText(tabBarParam, tabItemNode, swiperNode, tabContentPattern, position, myIndex);
    }

    // Bind click event: only on first creation to avoid duplicate handlers on update.
    // Capture tabContentId instead of index to handle Tab insertion/deletion/reordering dynamically.
    if (!update) {
        auto clickEvent = [weakTabsNode = WeakPtr(tabsNode), weakPattern = WeakClaim(this),
                          capturedTabContentId = tabContentId](const GestureEvent& info) {
            auto tabsNode = weakTabsNode.Upgrade();
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(tabsNode);
            CHECK_NULL_VOID(pattern);
            auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
            CHECK_NULL_VOID(swiperNode);
            auto currentIndex = swiperNode->GetChildFlatIndex(capturedTabContentId).second;
            pattern->SetCurrentIndex(currentIndex);
        };
        auto gestureHub = tabItemNode->GetOrCreateGestureEventHub();
        if (gestureHub) {
            gestureHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(std::move(clickEvent)));
        }
    }

    // Set initial selected/unselected background color inline (same as bottom TabBar)
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    int32_t indicator = 0;
    if (tabsProperty->GetIndexSetByUser().has_value()) {
        indicator = tabsProperty->GetIndexSetByUser().value();
    } else if (swiperLayoutProperty->GetIndex().has_value()) {
        indicator = swiperLayoutProperty->GetIndex().value();
    }
    int32_t totalCount = swiperPattern->TotalCount();
    if (indicator > totalCount - 1 || indicator < 0) {
        indicator = 0;
    }
    auto tabTheme = tabsNode->GetTheme<TabTheme>(true);
    auto itemRenderContext = tabItemNode->GetRenderContext();
    if (tabTheme && itemRenderContext) {
        auto color = (myIndex == indicator)
            ? tabTheme->GetSideBarListItemActivedColor()
            : Color::TRANSPARENT;
        if (myIndex == indicator) {
            auto tabLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
            if (tabLayoutProperty && tabLayoutProperty->GetSidebarSelectedBoardColor().has_value()) {
                color = tabLayoutProperty->GetSidebarSelectedBoardColor().value();
            }
        }
        itemRenderContext->UpdateBackgroundColor(color);
    }
    if (currentIndex_ == -1) {
        currentIndex_ = indicator;
    }

    tabItemContainerNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}
} // namespace OHOS::Ace::NG
