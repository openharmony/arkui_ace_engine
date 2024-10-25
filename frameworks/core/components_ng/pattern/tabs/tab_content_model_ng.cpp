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

#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include <optional>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_item_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_event_hub.h"
#include "core/components_ng/pattern/tabs/tab_content_node.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/symbol/constants.h"
#include "core/components_ng/pattern/symbol/symbol_effect_options.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint8_t PIXEL_ROUND = static_cast<uint8_t>(PixelRoundPolicy::FORCE_FLOOR_START) |
                                static_cast<uint8_t>(PixelRoundPolicy::FORCE_FLOOR_TOP) |
                                static_cast<uint8_t>(PixelRoundPolicy::FORCE_CEIL_END) |
                                static_cast<uint8_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM);
constexpr uint32_t DEFAULT_RENDERING_STRATEGY = 2;
}

void TabContentModelNG::Create(std::function<void()>&& deepRenderFunc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto deepRender = [nodeId, deepRenderFunc = std::move(deepRenderFunc)]() -> RefPtr<UINode> {
        CHECK_NULL_RETURN(deepRenderFunc, nullptr);
        ScopedViewStackProcessor scopedViewStackProcessor;
        deepRenderFunc();
        auto deepChild = ViewStackProcessor::GetInstance()->Finish();
        auto parent = FrameNode::GetFrameNode(V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId);
        if (deepChild && parent) {
            deepChild->MountToParent(parent);
        }
        return deepChild;
    };
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId);
    auto frameNode = TabContentNode::GetOrCreateTabContentNode(V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId,
        [shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender))]() {
            return AceType::MakeRefPtr<TabContentPattern>(shallowBuilder);
        });
    stack->Push(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    SetTabBar(tabTheme->GetDefaultTabBarName(), "", std::nullopt, nullptr, true); // Set default tab bar.
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Text, tabTheme->GetDefaultTabBarName());
}

void TabContentModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId);
    auto frameNode = TabContentNode::GetOrCreateTabContentNode(
        V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabContentPattern>(nullptr); });
    stack->Push(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    SetTabBar(tabTheme->GetDefaultTabBarName(), "", std::nullopt, nullptr, true); // Set default tab bar.
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Text, tabTheme->GetDefaultTabBarName());
}

RefPtr<FrameNode> TabContentModelNG::CreateFrameNode(int32_t nodeId)
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
    return frameNode;
}

void TabContentModelNG::Pop()
{
    auto tabContent = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    AddTabBarItem(tabContent, DEFAULT_NODE_SLOT, true);
    NG::ViewStackProcessor::GetInstance()->PopContainer();
}

RefPtr<TabsNode> TabContentModelNG::FindTabsNode(const RefPtr<UINode>& tabContent)
{
    CHECK_NULL_RETURN(tabContent, nullptr);
    RefPtr<UINode> parent = tabContent->GetParent();

    while (parent) {
        if (AceType::InstanceOf<TabsNode>(parent)) {
            return AceType::DynamicCast<TabsNode>(parent);
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

void TabContentModelNG::AddTabBarItem(const RefPtr<UINode>& tabContent, int32_t position, bool update)
{
    CHECK_NULL_VOID(tabContent);
    auto tabContentId = tabContent->GetId();

    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContent);
    CHECK_NULL_VOID(tabContentNode);

    if (update && !tabContentNode->HasTabBarItemId()) {
        return;
    }

    auto tabsNode = FindTabsNode(tabContent);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = tabsNode->GetTabBar();
    CHECK_NULL_VOID(tabBarNode);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(tabContentPattern);
    const auto& tabBarParam = tabContentPattern->GetTabBarParam();

    // Create column node to contain image and text or builder.
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, tabContentNode->GetTabBarItemId(),
        []() { return AceType::MakeRefPtr<TabBarItemPattern>(); });
    auto pipelineContext = tabsNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto linearLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(linearLayoutProperty);
    linearLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    linearLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    linearLayoutProperty->UpdateSpace(tabTheme->GetBottomTabBarSpace());
    linearLayoutProperty->UpdatePixelRound(PIXEL_ROUND);
    auto columnRenderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(columnRenderContext);
    columnRenderContext->UpdateClipEdge(true);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabBarNode);
    CHECK_NULL_VOID(tabBarFrameNode);
    auto tabBarPattern = tabBarFrameNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->SetTabBarStyle(tabBarParam.GetTabBarStyle());
    tabBarPattern->AddTabBarItemClickEvent(columnNode);
    auto selectedMode = tabContentPattern->GetSelectedMode();
    auto indicatorStyle = tabContentPattern->GetIndicatorStyle();
    auto boardStyle = tabContentPattern->GetBoardStyle();
    auto bottomTabBarStyle = tabContentPattern->GetBottomTabBarStyle();
    auto padding = tabContentPattern->GetPadding();
    auto tabLayoutProperty = AceType::DynamicCast<TabsLayoutProperty>(tabsNode->GetLayoutProperty());
    CHECK_NULL_VOID(tabLayoutProperty);
    auto isRTL = tabLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (isRTL && tabContentPattern->GetUseLocalizedPadding()) {
        PaddingProperty paddingRtl;
        paddingRtl.left = padding.right;
        paddingRtl.right = padding.left;
        paddingRtl.top = padding.top;
        paddingRtl.bottom = padding.bottom;
        padding = paddingRtl;
    }

    if (tabBarParam.GetTabBarStyle() == TabBarStyle::BOTTOMTABBATSTYLE) {
        if (bottomTabBarStyle.layoutMode == LayoutMode::HORIZONTAL) {
            linearLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
            linearLayoutProperty->UpdateSpace(tabTheme->GetHorizontalBottomTabBarSpace());
            linearLayoutProperty->UpdateCrossAxisAlign(bottomTabBarStyle.verticalAlign);
            linearLayoutProperty->SetIsVertical(false);
        } else {
            linearLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
            linearLayoutProperty->UpdateSpace(tabTheme->GetBottomTabBarSpace());
            linearLayoutProperty->UpdateMainAxisAlign(bottomTabBarStyle.verticalAlign);
            linearLayoutProperty->SetIsVertical(true);
        }
    }

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto myIndex = swiperNode->GetChildFlatIndex(tabContentId).second;

    auto newTabBar = tabBarPattern->IsNewTabBar(columnNode->GetId());
    tabBarPattern->SetTabBarStyle(tabBarParam.GetTabBarStyle(), myIndex, newTabBar);
    tabBarPattern->AddTabBarItemId(columnNode->GetId(), myIndex, newTabBar);
    tabBarPattern->SetBottomTabBarStyle(bottomTabBarStyle, myIndex, newTabBar);
    auto labelStyle = tabContentPattern->GetLabelStyle();
    tabBarPattern->SetLabelStyle(columnNode->GetId(), labelStyle);
    auto iconStyle = tabContentPattern->GetIconStyle();
    tabBarPattern->SetIconStyle(iconStyle, myIndex, newTabBar);
    auto symbol = tabContentPattern->GetSymbol();
    tabBarPattern->SetSymbol(symbol, myIndex, newTabBar);
    auto tabBarStyle = tabContentPattern->GetTabBarStyle();
    if (tabBarStyle == TabBarStyle::SUBTABBATSTYLE) {
        auto renderContext = columnNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        BorderRadiusProperty borderRadiusProperty;
        borderRadiusProperty.SetRadius(boardStyle.borderRadius);
        renderContext->UpdateBorderRadius(borderRadiusProperty);
    }
    if (tabBarStyle != TabBarStyle::SUBTABBATSTYLE) {
        indicatorStyle.marginTop = 0.0_vp;
    }
    tabBarPattern->SetSelectedMode(selectedMode, myIndex, newTabBar);
    tabBarPattern->SetIndicatorStyle(indicatorStyle, myIndex, newTabBar);

    // Create tab bar with builder.
    if (tabBarParam.HasBuilder()) {
        ScopedViewStackProcessor builderViewStackProcessor;
        tabBarParam.ExecuteBuilder();
        auto builderNode = ViewStackProcessor::GetInstance()->Finish();
        if (static_cast<int32_t>(columnNode->GetChildren().size()) != 0) {
            columnNode->Clean();
        }
        if (builderNode) {
            builderNode->MountToParent(columnNode);
        }
        auto oldColumnNode = tabsNode->GetBuilderByContentId(tabContentId, columnNode);
        if (!oldColumnNode) {
            columnNode->MountToParent(tabBarNode, myIndex);
        } else {
            tabBarNode->ReplaceChild(oldColumnNode, columnNode);
        }
        columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        tabBarPattern->AddTabBarItemType(columnNode->GetId(), true);
        tabBarPattern->SetIsExecuteBuilder(true);
        tabBarFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        return;
    }

    // Create text node and image node.
    RefPtr<FrameNode> textNode;
    RefPtr<FrameNode> iconNode;
    auto layoutProperty = columnNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (tabBarStyle == TabBarStyle::SUBTABBATSTYLE || tabBarStyle == TabBarStyle::BOTTOMTABBATSTYLE) {
        layoutProperty->UpdatePadding(padding);
        auto accessibilityProperty = columnNode->GetAccessibilityProperty<AccessibilityProperty>();
        accessibilityProperty->SetAccessibilityGroup(true);
        auto id = tabContentPattern->GetId();
        columnNode->UpdateInspectorId(id);
    } else {
        auto tabBarItemPadding = tabTheme->GetSubTabItemPadding();
        layoutProperty->UpdatePadding({ CalcLength(tabBarItemPadding), CalcLength(tabBarItemPadding),
            CalcLength(tabBarItemPadding), CalcLength(tabBarItemPadding) });
    }

    bool isFrameNode = false;
    if (static_cast<int32_t>(columnNode->GetChildren().size()) == 0) {
        if (tabBarParam.GetSymbol().has_value()) {
            iconNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        } else {
            iconNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
        }
        if (tabBarStyle == TabBarStyle::SUBTABBATSTYLE && tabContentPattern->HasSubTabBarStyleNode()) {
            isFrameNode = true;
            textNode = tabContentPattern->FireCustomStyleNode();
        } else {
            textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<TextPattern>(); });
        }
        CHECK_NULL_VOID(textNode);
        CHECK_NULL_VOID(iconNode);
        columnNode->MountToParent(tabBarNode, position);
        iconNode->MountToParent(columnNode);
        textNode->MountToParent(columnNode);
    } else {
        if (tabBarStyle == TabBarStyle::SUBTABBATSTYLE && tabContentPattern->HasSubTabBarStyleNode()) {
            isFrameNode = true;
            auto builderNode = tabContentPattern->FireCustomStyleNode();
            columnNode->ReplaceChild(AceType::DynamicCast<FrameNode>(columnNode->GetChildren().back()), builderNode);
        }
        auto oldIcon = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
        CHECK_NULL_VOID(oldIcon);
        if (tabBarParam.GetSymbol().has_value() && oldIcon->GetTag() != V2::SYMBOL_ETS_TAG) {
            auto icon = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
            columnNode->ReplaceChild(oldIcon, icon);
        } else if (!tabBarParam.GetIcon().empty() && oldIcon->GetTag() != V2::IMAGE_ETS_TAG) {
            auto icon = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
            columnNode->ReplaceChild(oldIcon, icon);
        }
        iconNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
        textNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().back());
    }
    CHECK_NULL_VOID(textNode);
    CHECK_NULL_VOID(iconNode);

    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    int32_t indicator = swiperLayoutProperty->GetIndexValue(0);
    int32_t totalCount = swiperPattern->TotalCount();
    if (indicator > totalCount - 1 || indicator < 0) {
        indicator = 0;
    }
    tabBarPattern->UpdateSubTabBoard(indicator);
    // Update property of text.
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    auto axis = tabBarLayoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    if ((!swiperPattern->IsUseCustomAnimation() || !swiperPattern->GetCustomAnimationToIndex().has_value()) &&
        !isFrameNode) {
        if (myIndex == indicator) {
            if (labelStyle.selectedColor.has_value()) {
                textLayoutProperty->UpdateTextColor(labelStyle.selectedColor.value());
            } else {
                selectedMode == SelectedMode::BOARD && axis == Axis::HORIZONTAL ?
                    textLayoutProperty->UpdateTextColor(tabTheme->GetSubTabBoardTextOnColor()) :
                    textLayoutProperty->UpdateTextColor(tabTheme->GetSubTabTextOnColor());
            }
        } else {
            if (labelStyle.unselectedColor.has_value()) {
                textLayoutProperty->UpdateTextColor(labelStyle.unselectedColor.value());
            } else {
                textLayoutProperty->UpdateTextColor(tabTheme->GetSubTabTextOffColor());
            }
        }
    }

    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    textRenderContext->UpdateClipEdge(true);
    if (!isFrameNode) {
        textLayoutProperty->UpdateContent(tabBarParam.GetText());
        textLayoutProperty->UpdateFontSize(tabTheme->GetSubTabTextDefaultFontSize());
        textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    }
    if (!isFrameNode) {
        textLayoutProperty->UpdateMaxLines(1);
        textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    }
    if (tabBarStyle == TabBarStyle::BOTTOMTABBATSTYLE) {
        textLayoutProperty->UpdateFlexShrink(1.0f);
    }

    if (!tabBarParam.GetIcon().empty() || tabBarStyle == TabBarStyle::BOTTOMTABBATSTYLE) {
        textLayoutProperty->UpdateFontSize(tabTheme->GetBottomTabTextSize());
    }
    if (tabBarStyle == TabBarStyle::BOTTOMTABBATSTYLE) {
        textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    } else if (tabBarStyle == TabBarStyle::SUBTABBATSTYLE && !isFrameNode) {
        textLayoutProperty->UpdateFontWeight(myIndex == indicator ? FontWeight::MEDIUM : FontWeight::NORMAL);
    }
    if (tabBarStyle == TabBarStyle::BOTTOMTABBATSTYLE && bottomTabBarStyle.layoutMode == LayoutMode::HORIZONTAL) {
        textLayoutProperty->UpdateTextAlign(TextAlign::LEFT);
        if (!labelStyle.fontSize.has_value() &&
            Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            textLayoutProperty->UpdateFontSize(tabTheme->GetBottomTabHorizontalTextSize());
        }
    }
    if (!isFrameNode) {
        UpdateLabelStyle(labelStyle, textLayoutProperty);
    }

    // Update property of image/symbol.
    if (tabBarParam.GetSymbol().has_value()) {
        auto symbolProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolProperty);
        UpdateDefaultSymbol(tabTheme, symbolProperty);
        auto modifierOnApply = tabBarParam.GetSymbol().value().onApply;
        if (myIndex == indicator) {
            tabBarPattern->SetImageColorOnIndex(indicator);
            symbolProperty->UpdateSymbolColorList({tabTheme->GetBottomTabSymbolOn()});
            if (modifierOnApply != nullptr) {
                modifierOnApply(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconNode)), "normal");
                UpdateDefaultSymbol(tabTheme, symbolProperty);
                symbolProperty->UpdateSymbolColorList({tabTheme->GetBottomTabSymbolOn()});
            }
            if (modifierOnApply != nullptr && tabBarParam.GetSymbol().value().selectedFlag) {
                modifierOnApply(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconNode)),
                    "selected");
                UpdateSymbolEffect(symbolProperty, false);
            }
        } else {
            symbolProperty->UpdateSymbolColorList({tabTheme->GetBottomTabSymbolOff()});
            if (modifierOnApply != nullptr) {
                modifierOnApply(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconNode)), "normal");
                UpdateSymbolEffect(symbolProperty, false);
            }
        }
    } else {
        auto imageProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageProperty);
        if (!tabBarParam.GetIcon().empty() || tabBarStyle == TabBarStyle::BOTTOMTABBATSTYLE) {
            imageProperty->UpdateUserDefinedIdealSize(CalcSize(
                NG::CalcLength(tabTheme->GetBottomTabImageSize()), NG::CalcLength(tabTheme->GetBottomTabImageSize())));
        } else {
            imageProperty->UpdateUserDefinedIdealSize(CalcSize());
        }
        ImageSourceInfo imageSourceInfo(tabBarParam.GetIcon());
        auto imagePaintProperty = iconNode->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(imagePaintProperty);
        if (imageSourceInfo.IsSvg() && myIndex == indicator) {
            tabBarPattern->SetImageColorOnIndex(indicator);
            if (iconStyle.selectedColor.has_value()) {
                imagePaintProperty->UpdateSvgFillColor(iconStyle.selectedColor.value());
            } else {
                imagePaintProperty->UpdateSvgFillColor(tabTheme->GetBottomTabIconOn());
            }
        }
        if (imageSourceInfo.IsSvg() && myIndex != indicator) {
            if (iconStyle.unselectedColor.has_value()) {
                imagePaintProperty->UpdateSvgFillColor(iconStyle.unselectedColor.value());
            } else {
                imagePaintProperty->UpdateSvgFillColor(tabTheme->GetBottomTabIconOff());
            }
        }
        imageProperty->UpdateImageSourceInfo(imageSourceInfo);
    }
    columnNode->MarkModifyDone();
    textNode->MarkModifyDone();
    textNode->MarkDirtyNode();
    iconNode->MarkModifyDone();
    tabBarPattern->AddTabBarItemType(columnNode->GetId(), false);
    tabBarFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TabContentModelNG::RemoveTabBarItem(const RefPtr<TabContentNode>& tabContentNode)
{
    CHECK_NULL_VOID(tabContentNode);
    if (!tabContentNode->HasTabBarItemId()) {
        return;
    }

    auto tabBarItemId = tabContentNode->GetTabBarItemId();
    auto tabBarItemNode = ElementRegister::GetInstance()->GetUINodeById(tabBarItemId);
    CHECK_NULL_VOID(tabBarItemNode);
    auto tabBarNode = tabBarItemNode->GetParent();
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabBarNode);
    CHECK_NULL_VOID(tabBarFrameNode);
    auto tabBarPattern = tabBarFrameNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->RemoveTabBarItemInfo(tabBarItemId);
    tabBarNode->RemoveChild(tabBarItemNode);
    tabContentNode->ResetTabBarItemId();

    auto tabsNode = FindTabsNode(tabContentNode);
    CHECK_NULL_VOID(tabsNode);
    tabsNode->RemoveBuilderByContentId(tabContentNode->GetId());
    tabBarFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TabContentModelNG::SetTabBar(const std::optional<std::string>& text, const std::optional<std::string>& icon,
    const std::optional<TabBarSymbol>& tabBarSymbol, TabBarBuilderFunc&& builder, bool /*useContentOnly*/)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Icon, icon.value_or(""));
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Text, text.value_or(""));
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetTabBar(text.value_or(""), icon.value_or(""), tabBarSymbol, std::move(builder));
}

void TabContentModelNG::SetTabBarStyle(TabBarStyle tabBarStyle)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetTabBarStyle(tabBarStyle);
}

void TabContentModelNG::SetIndicator(const IndicatorStyle& indicator)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetIndicatorStyle(indicator);
}

void TabContentModelNG::SetCustomTabBar(FrameNode* node, FrameNode* tabBar)
{
    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(tabBar);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetTabBarStyle(TabBarStyle::NOSTYLE);
    frameNodePattern->SetCustomTabBar(tabBar);
}

void TabContentModelNG::SetBoard(const BoardStyle& board)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetBoardStyle(board);
}

void TabContentModelNG::SetSelectedMode(SelectedMode selectedMode)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetSelectedMode(selectedMode);
}

void TabContentModelNG::SetLabelStyle(const LabelStyle& labelStyle)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetLabelStyle(labelStyle);
}

void TabContentModelNG::SetIconStyle(const IconStyle& iconStyle)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetIconStyle(iconStyle);
}

void TabContentModelNG::SetPadding(const PaddingProperty& padding)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetPadding(padding);
}

void TabContentModelNG::SetUseLocalizedPadding(bool useLocalizedPadding)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetUseLocalizedPadding(useLocalizedPadding);
}

void TabContentModelNG::SetLayoutMode(LayoutMode layoutMode)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetLayoutMode(layoutMode);
}

void TabContentModelNG::SetVerticalAlign(FlexAlign verticalAlign)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetVerticalAlign(verticalAlign);
}

void TabContentModelNG::SetSymmetricExtensible(bool isExtensible)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetSymmetricExtensible(isExtensible);
}

void TabContentModelNG::SetId(const std::string& id)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetId(id);
}

void TabContentModelNG::UpdateLabelStyle(const LabelStyle& labelStyle, RefPtr<TextLayoutProperty> textLayoutProperty)
{
    CHECK_NULL_VOID(textLayoutProperty);

    if (labelStyle.fontSize.has_value()) {
        textLayoutProperty->UpdateFontSize(labelStyle.fontSize.value());
    }
    if (labelStyle.fontWeight.has_value()) {
        textLayoutProperty->UpdateFontWeight(labelStyle.fontWeight.value());
    }
    if (labelStyle.fontStyle.has_value()) {
        textLayoutProperty->UpdateItalicFontStyle(labelStyle.fontStyle.value());
    }
    if (labelStyle.fontFamily.has_value()) {
        textLayoutProperty->UpdateFontFamily(labelStyle.fontFamily.value());
    }
    if (labelStyle.textOverflow.has_value()) {
        textLayoutProperty->UpdateTextOverflow(labelStyle.textOverflow.value());
    }
    if (labelStyle.maxLines.has_value()) {
        textLayoutProperty->UpdateMaxLines(labelStyle.maxLines.value());
    }
    if (labelStyle.minFontSize.has_value()) {
        textLayoutProperty->UpdateAdaptMinFontSize(labelStyle.minFontSize.value());
    }
    if (labelStyle.maxFontSize.has_value()) {
        textLayoutProperty->UpdateAdaptMaxFontSize(labelStyle.maxFontSize.value());
    }
    if (labelStyle.heightAdaptivePolicy.has_value()) {
        textLayoutProperty->UpdateHeightAdaptivePolicy(labelStyle.heightAdaptivePolicy.value());
    }
}

void TabContentModelNG::UpdateDefaultSymbol(RefPtr<TabTheme>& tabTheme, RefPtr<TextLayoutProperty> symbolProperty)
{
    symbolProperty->UpdateFontSize(tabTheme->GetBottomTabImageSize());
    symbolProperty->UpdateSymbolRenderingStrategy(DEFAULT_RENDERING_STRATEGY);
    UpdateSymbolEffect(symbolProperty, false);
}
void TabContentModelNG::UpdateSymbolEffect(RefPtr<TextLayoutProperty> symbolProperty, bool isActive)
{
    auto symbolEffectOptions = SymbolEffectOptions(SymbolEffectType::BOUNCE);
    symbolEffectOptions.SetIsTxtActive(isActive);
    symbolEffectOptions.SetIsTxtActiveSource(0);
    symbolProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
}

void TabContentModelNG::SetOnWillShow(std::function<void()>&& onWillShow)
{
    auto tabContentNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabContentNode);
    auto tabContentEventHub = tabContentNode->GetEventHub<TabContentEventHub>();
    CHECK_NULL_VOID(tabContentEventHub);
    tabContentEventHub->SetOnWillShow(onWillShow);
}

void TabContentModelNG::SetOnWillHide(std::function<void()>&& onWillHide)
{
    auto tabContentNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(tabContentNode);
    auto tabContentEventHub = tabContentNode->GetEventHub<TabContentEventHub>();
    CHECK_NULL_VOID(tabContentEventHub);
    tabContentEventHub->SetOnWillHide(onWillHide);
}

void TabContentModelNG::SetCustomStyleNode(const RefPtr<FrameNode>& customStyleNode)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCustomStyleNode(customStyleNode);
}

void TabContentModelNG::SetTabBarBuilder(FrameNode* node, TabBarBuilderFunc&& builder)
{
    CHECK_NULL_VOID(node);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetTabBar("", "", std::nullopt, std::move(builder));
}

void TabContentModelNG::SetTabBarLabel(FrameNode* node, const std::string& label)
{
    CHECK_NULL_VOID(node);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetTabBar(label, "", std::nullopt, nullptr);
}
} // namespace OHOS::Ace::NG
