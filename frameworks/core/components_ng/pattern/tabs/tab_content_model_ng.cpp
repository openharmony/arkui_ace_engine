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
#include <string>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/resource/resource_parse_utils.h"
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
constexpr uint16_t PIXEL_ROUND = static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_START) |
                                static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_TOP) |
                                static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END) |
                                static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM);
constexpr uint32_t DEFAULT_RENDERING_STRATEGY = 2;
const auto MASK_COUNT = 2;
const std::string KEY_PADDING = "tabContent.tabBarPadding";
const std::string KEY_PADDING_LEFT = "tabContent.tabBarPadding.left";
const std::string KEY_PADDING_RIGHT = "tabContent.tabBarPadding.right";
const std::string KEY_PADDING_TOP = "tabContent.tabBarPadding.top";
const std::string KEY_PADDING_BOTTOM = "tabContent.tabBarPadding.bottom";
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
    if (SystemProperties::ConfigChangePerform()) {
        auto tabsLayoutProperty = frameNode->GetLayoutProperty<TabContentLayoutProperty>();
        CHECK_NULL_VOID(tabsLayoutProperty);
        tabsLayoutProperty->ResetIndicatorColorSetByUser();
        tabsLayoutProperty->ResetLabelUnselectedColorSetByUser();
        tabsLayoutProperty->ResetLabelSelectedColorSetByUser();
        tabsLayoutProperty->ResetIconUnselectedColorSetByUser();
        tabsLayoutProperty->ResetIconSelectedColorSetByUser();
    }
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
    pattern->SetTabBarWithContent(nullptr);
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
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_VOID(tabBarRenderContext);
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
    if (tabTheme->GetIsChangeFocusTextStyle()) {
        columnRenderContext->UpdateClipEdge(false);
    } else {
        columnRenderContext->UpdateClipEdge(tabBarRenderContext->GetClipEdgeValue(true));
    }
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->SetTabBarStyle(tabBarParam.GetTabBarStyle());
    tabBarPattern->AddTabBarItemClickAndTouchEvent(columnNode);
    tabBarPattern->AddTabBarItemCallBack(columnNode);
    auto selectedMode = tabContentPattern->GetSelectedMode();
    auto indicatorStyle = tabContentPattern->GetIndicatorStyle();
    auto boardStyle = tabContentPattern->GetBoardStyle();
    auto bottomTabBarStyle = tabContentPattern->GetBottomTabBarStyle();
    auto padding = tabContentPattern->GetPadding();
    auto tabLayoutProperty = AceType::DynamicCast<TabsLayoutProperty>(tabsNode->GetLayoutProperty());
    CHECK_NULL_VOID(tabLayoutProperty);
    auto tabBarLayoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(tabBarNode->GetLayoutProperty());
    CHECK_NULL_VOID(tabBarLayoutProperty);
    auto tabsDirection = tabLayoutProperty->GetNonAutoLayoutDirection();
    auto tabBarDirection = tabBarLayoutProperty->GetLayoutDirection();
    auto isRTL = tabBarDirection == TextDirection::RTL ||
             (tabBarDirection == TextDirection::AUTO && tabsDirection == TextDirection::RTL);
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

    if (tabBarParam.GetTabBarStyle() == TabBarStyle::NOSTYLE && !tabBarParam.HasBuilder() &&
        !tabBarParam.HasContent() && tabBarParam.GetIcon().empty() && tabBarParam.GetText().empty()) {
        if (!columnNode->GetChildren().empty()) {
            columnNode->Clean();
        }
    }

    auto columnFocusHub = columnNode->GetFocusHub();
    if (columnFocusHub) {
        columnFocusHub->SetFocusDependence(FocusDependence::SELF);
    }

    // Create tab bar with content.
    if (tabBarParam.HasContent()) {
        ScopedViewStackProcessor builderViewStackProcessor;
        auto builderNode = tabBarParam.GetContent().Upgrade();
        CHECK_NULL_VOID(builderNode);
        if (!columnNode->GetChildren().empty()) {
            columnNode->Clean();
        }
        if (builderNode) {
            builderNode->MountToParent(columnNode);
        }
        tabBarPattern->SetIsExecuteBuilder(false);
        auto oldColumnNode = tabsNode->GetBuilderByContentId(tabContentId, columnNode);
        if (oldColumnNode != columnNode) {
            if (!oldColumnNode) {
                auto index =
                    std::clamp(myIndex, 0, static_cast<int32_t>(tabBarNode->GetChildren().size()) - MASK_COUNT);
                columnNode->MountToParent(tabBarNode, index);
            } else if (oldColumnNode != columnNode) {
                tabBarNode->ReplaceChild(oldColumnNode, columnNode);
            }
        }
        auto tabBarItemPadding = Dimension(0);
        auto layoutProperty = columnNode->GetLayoutProperty();
        layoutProperty->UpdatePadding({ CalcLength(tabBarItemPadding), CalcLength(tabBarItemPadding),
            CalcLength(tabBarItemPadding), CalcLength(tabBarItemPadding), {}, {} });
        columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        tabBarPattern->AddTabBarItemType(columnNode->GetId(), TabBarParamType::COMPONENT_CONTENT);
        tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        return;
    }

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
            auto index = std::clamp(myIndex, 0, static_cast<int32_t>(tabBarNode->GetChildren().size()) - MASK_COUNT);
            columnNode->MountToParent(tabBarNode, index);
        } else if (oldColumnNode != columnNode) {
            tabBarNode->ReplaceChild(oldColumnNode, columnNode);
        }
        columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        tabBarPattern->AddTabBarItemType(columnNode->GetId(), TabBarParamType::CUSTOM_BUILDER);
        tabBarPattern->SetIsExecuteBuilder(true);
        tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
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
        auto subTabItemHorizontalPadding_ = tabTheme->GetSubTabItemHorizontalPadding();
        layoutProperty->UpdatePadding({ CalcLength(subTabItemHorizontalPadding_),
            CalcLength(subTabItemHorizontalPadding_), CalcLength(tabBarItemPadding),
            CalcLength(tabBarItemPadding), {}, {} });
    }

    bool isFrameNode = tabBarStyle == TabBarStyle::SUBTABBATSTYLE && tabContentPattern->HasSubTabBarStyleNode();
    if (isFrameNode) {
        tabBarPattern->AddTabBarItemType(columnNode->GetId(), TabBarParamType::SUB_COMPONENT_CONTENT);
    } else {
        tabBarPattern->AddTabBarItemType(columnNode->GetId(), TabBarParamType::NORMAL);
    }
    if (static_cast<int32_t>(columnNode->GetChildren().size()) == 0) {
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
            textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<TextPattern>(); });
        }
        CHECK_NULL_VOID(textNode);
        CHECK_NULL_VOID(iconNode);
        auto index = std::clamp(position, 0, static_cast<int32_t>(tabBarNode->GetChildren().size()) - MASK_COUNT);
        columnNode->MountToParent(tabBarNode, index);
        iconNode->MountToParent(columnNode);
        textNode->MountToParent(columnNode);
    } else {
        if (isFrameNode) {
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
    tabBarPattern->UpdateSubTabBoard(indicator);
    // Update property of text.
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
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
    tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
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

template<typename T>
bool ParseType(const RefPtr<ResourceObject>& resObj, const std::string& name, T& result)
{
    if constexpr (std::is_same_v<T, Color>) {
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
            CHECK_NULL_RETURN(frameNode, false);
            auto pipelineContext = frameNode->GetContext();
            CHECK_NULL_RETURN(pipelineContext, false);
            auto tabTheme = pipelineContext->GetTheme<TabTheme>();
            CHECK_NULL_RETURN(tabTheme, false);
            result = tabTheme->GetActiveIndicatorColor();
            return false;
        }
        return true;
    } else if constexpr (std::is_same_v<T, std::optional<Color>>) {
        if (name == "selectedColor" || name == "unselectedColor") {
            Color color;
            if (ResourceParseUtils::ParseResColor(resObj, color)) {
                result = color;
            }
            return true;
        }
    } else if constexpr (std::is_same_v<T, std::optional<Dimension>>) {
        if (name == "fontSize") {
            CalcDimension fontSize;
            if (ResourceParseUtils::ParseResDimensionFp(resObj, fontSize) && NonNegative(fontSize.Value()) &&
                fontSize.Unit() != DimensionUnit::PERCENT) {
                result = fontSize;
            }
            return true;
        }
    } else if constexpr (std::is_same_v<T, CalcDimension>) {
        if (name == "height" || name == "borderRadius" || name == "width" || name == "marginTop") {
            return ResourceParseUtils::ParseResDimensionVp(resObj, result);
        } else if (name == "minFontSize" || name == "maxFontSize") {
            return ResourceParseUtils::ParseResDimensionFp(resObj, result);
        } else {
            return ResourceParseUtils::ParseResDimensionNG(resObj, result, DimensionUnit::PX);
        }
    } else if constexpr (std::is_same_v<T, Dimension>) {
        return ResourceParseUtils::ParseResDimensionFpNG(resObj, result);
    } else if constexpr (std::is_same_v<T, std::vector<std::string>>) {
        return ResourceParseUtils::ParseResFontFamilies(resObj, result);
    } else if constexpr (std::is_same_v<T, std::string>) {
        return ResourceParseUtils::ParseResString(resObj, result);
    }
    return false;
}

#define REGISTER_RESOURCE_UPDATE_ATTR_FUNC(caseType, attrType, name, resObj, resultType)                          \
    case caseType:                                                                                                \
        do {                                                                                                      \
            auto pattern = frameNode->GetPattern<TabContentPattern>();                                            \
            CHECK_NULL_VOID(pattern);                                                                             \
            const std::string key = "tabContent." #attrType #name;                                                \
            pattern->RemoveResObj(key);                                                                           \
            CHECK_NULL_VOID(resObj);                                                                              \
            auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& theResObj) { \
                auto frameNode = weak.Upgrade();                                                                  \
                CHECK_NULL_VOID(frameNode);                                                                       \
                auto pattern = frameNode->GetPattern<TabContentPattern>();                                        \
                CHECK_NULL_VOID(pattern);                                                                         \
                resultType result;                                                                                \
                ParseType(theResObj, #name, result);                                                              \
                auto attrs = pattern->Get##attrType();                                                            \
                attrs.name = result;                                                                              \
                pattern->Set##attrType(attrs);                                                                    \
            };                                                                                                    \
            pattern->AddResObj(key, resObj, std::move(updateFunc));                                               \
        } while (false);                                                                                          \
        break

#define REGISTER_RESOURCE_UPDATE_ATTR_FONT_SIZE_FUNC(caseType, attrType, name, resObj, resultType)                \
    case caseType:                                                                                                \
        do {                                                                                                      \
            auto pattern = frameNode->GetPattern<TabContentPattern>();                                            \
            CHECK_NULL_VOID(pattern);                                                                             \
            const std::string key = "tabContent." #attrType #name;                                                \
            pattern->RemoveResObj(key);                                                                           \
            CHECK_NULL_VOID(resObj);                                                                              \
            auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& theResObj) { \
                auto frameNode = weak.Upgrade();                                                                  \
                CHECK_NULL_VOID(frameNode);                                                                       \
                auto pattern = frameNode->GetPattern<TabContentPattern>();                                        \
                CHECK_NULL_VOID(pattern);                                                                         \
                resultType result;                                                                                \
                if (ParseType(theResObj, #name, result)) {                                                        \
                    auto attrs = pattern->Get##attrType();                                                        \
                    attrs.name = result;                                                                          \
                    pattern->Set##attrType(attrs);                                                                \
                }                                                                                                 \
            };                                                                                                    \
            pattern->AddResObj(key, resObj, std::move(updateFunc));                                               \
        } while (false);                                                                                          \
        break

void TabContentModelNG::CreateWithResourceObj(TabContentJsType jsType, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    switch (jsType) {
        REGISTER_RESOURCE_UPDATE_ATTR_FONT_SIZE_FUNC(
            TabContentJsType::FONT_SIZE, LabelStyle, fontSize, resObj, std::optional<Dimension>);
        REGISTER_RESOURCE_UPDATE_ATTR_FUNC(
            TabContentJsType::FONT_FAMILY, LabelStyle, fontFamily, resObj, std::vector<std::string>);
        REGISTER_RESOURCE_UPDATE_ATTR_FONT_SIZE_FUNC(
            TabContentJsType::MIN_FONT_SIZE, LabelStyle, minFontSize, resObj, CalcDimension);
        REGISTER_RESOURCE_UPDATE_ATTR_FONT_SIZE_FUNC(
            TabContentJsType::MAX_FONT_SIZE, LabelStyle, maxFontSize, resObj, CalcDimension);
        REGISTER_RESOURCE_UPDATE_ATTR_FUNC(
            TabContentJsType::LABEL_SELECT_COLOR, LabelStyle, selectedColor, resObj, std::optional<Color>);
        REGISTER_RESOURCE_UPDATE_ATTR_FUNC(
            TabContentJsType::LABEL_UNSELECT_COLOR, LabelStyle, unselectedColor, resObj, std::optional<Color>);
        REGISTER_RESOURCE_UPDATE_ATTR_FUNC(
            TabContentJsType::ICON_SELECT_COLOR, IconStyle, selectedColor, resObj, std::optional<Color>);
        REGISTER_RESOURCE_UPDATE_ATTR_FUNC(
            TabContentJsType::ICON_UNSELECT_COLOR, IconStyle, unselectedColor, resObj, std::optional<Color>);
        default:
            CreateMoreWithResourceObj(jsType, frameNode, resObj);
            break;
    }
}

void TabContentModelNG::CreateMoreWithResourceObj(TabContentJsType jsType, FrameNode* frameNode,
    const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    switch (jsType) {
        case TabContentJsType::INDICATOR_COLOR:
            CreateIndicatorColorWithResourceObj(frameNode, resObj);
            break;
        case TabContentJsType::INDICATOR_HEIGHT:
            CreateIndicatorHeightWithResourceObj(frameNode, resObj);
            break;
        case TabContentJsType::INDICATOR_WIDTH:
            CreateIndicatorWidthWithResourceObj(frameNode, resObj);
            break;
        case TabContentJsType::INDICATOR_RADIUS:
            CreateIndicatorBorderRadiusWithResourceObj(frameNode, resObj);
            break;
        case TabContentJsType::INDICATOR_MARGIN_TOP:
            CreateIndicatorMarginTopWithResourceObj(frameNode, resObj);
            break;
        case TabContentJsType::BORDER_RADIUS:
            CreateBoardStyleBorderRadiusWithResourceObj(frameNode, resObj);
            break;
        case TabContentJsType::PADDING:
            CreatePaddingWithResourceObj(frameNode, resObj);
            break;
        case TabContentJsType::TEXT_CONTENT:
            CreateTextContentWithResourceObj(frameNode, resObj);
            break;
        case TabContentJsType::TAB_BAR_OPTIONS_ICON: {
            CreateIconWithResourceObjWithKey(frameNode, "tabContent.tabBarOptions", resObj);
            break;
        }
        case TabContentJsType::BOTTOM_TAB_BAR_STYLE_ICON: {
            CreateIconWithResourceObjWithKey(frameNode, "tabContent.bottomTabBarStyle", resObj);
            break;
        }
        default:
            break;
    }
}

bool TabContentModelNG::CreateIconWithResourceObjWithKey(FrameNode* frameNode, const std::string key,
    const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->RemoveResObj(key);
    CHECK_NULL_RETURN(resObj, true);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        std::string result;
        ResourceParseUtils::ParseResMedia(resObj, result);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabContentLayoutProperty, Icon, result, frameNode);
        pattern->UpdateTabBarParamIcon(result);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
    return true;
}

void TabContentModelNG::CreatePaddingHorWithResourceObj(const RefPtr<ResourceObject>& resObjLeft,
    const RefPtr<ResourceObject>& resObjRight, bool isSubTabStyle, bool useLocalizedPadding)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreatePaddingLeftWithResourceObj(frameNode, resObjLeft, isSubTabStyle, useLocalizedPadding);
    CreatePaddingRightWithResourceObj(frameNode, resObjRight, isSubTabStyle, useLocalizedPadding);
}

void TabContentModelNG::CreatePaddingVerWithResourceObj(const RefPtr<ResourceObject>& resObjTop,
    const RefPtr<ResourceObject>& resObjBottom, bool isSubTabStyle, bool useLocalizedPadding)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreatePaddingTopWithResourceObj(frameNode, resObjTop, isSubTabStyle, useLocalizedPadding);
    CreatePaddingBottomWithResourceObj(frameNode, resObjBottom, isSubTabStyle, useLocalizedPadding);
}

bool TabContentModelNG::CreatePaddingWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    const std::string key = "tabContent.tabBarPadding";
    pattern->RemoveResObj(key);
    pattern->RemoveResObj(KEY_PADDING_LEFT);
    pattern->RemoveResObj(KEY_PADDING_RIGHT);
    pattern->RemoveResObj(KEY_PADDING_TOP);
    pattern->RemoveResObj(KEY_PADDING_BOTTOM);
    CHECK_NULL_RETURN(resObj, true);

    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        CalcDimension result;
        if (ResourceParseUtils::ParseResDimensionVp(resObj, result) && NonNegative(result.Value()) &&
            result.Unit() != DimensionUnit::PERCENT) {
            NG::PaddingProperty padding;
            padding.left = NG::CalcLength(result);
            padding.right = NG::CalcLength(result);
            padding.top = NG::CalcLength(result);
            padding.bottom = NG::CalcLength(result);
            pattern->SetPadding(padding);
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
    return true;
}

bool TabContentModelNG::CreateTextContentWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    const std::string key = "tabContent.tabBarParamText";
    pattern->RemoveResObj(key);
    CHECK_NULL_RETURN(resObj, true);

    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        std::string result;
        ResourceParseUtils::ParseResString(resObj, result);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TabContentLayoutProperty, Text, result, frameNode);
        pattern->UpdateTabBarParamText(result);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
    return true;
}

bool TabContentModelNG::CreatePaddingLeftWithResourceObj(FrameNode* frameNode,
    const RefPtr<ResourceObject>& resObjLeft, bool isSubTabStyle, bool useLocalizedPadding)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->RemoveResObj(KEY_PADDING);
    pattern->RemoveResObj(KEY_PADDING_LEFT);
    CHECK_NULL_RETURN(resObjLeft, true);

    auto&& updateFunc = [weakNode = AceType::WeakClaim(frameNode), isSubTabStyle](
        const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        CalcDimension left;
        auto padding = pattern->GetPadding();
        if (ResourceParseUtils::ParseResDimensionVp(resObj, left) && NonNegative(left.Value()) &&
            left.Unit() != DimensionUnit::PERCENT) {
            padding.left = NG::CalcLength(left);
        } else {
            auto pipelineContext = frameNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto tabTheme = pipelineContext->GetTheme<TabTheme>();
            CHECK_NULL_VOID(tabTheme);
            padding.left = (isSubTabStyle) ? NG::CalcLength(tabTheme->GetSubTabHorizontalPadding()) :
                NG::CalcLength(tabTheme->GetBottomTabHorizontalPadding());
        }
        pattern->SetPadding(padding);
    };
    pattern->AddResObj(KEY_PADDING_LEFT, resObjLeft, std::move(updateFunc));
    return true;
}

bool TabContentModelNG::CreatePaddingRightWithResourceObj(FrameNode* frameNode,
    const RefPtr<ResourceObject>& resObjRight, bool isSubTabStyle, bool useLocalizedPadding)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->RemoveResObj(KEY_PADDING);
    pattern->RemoveResObj(KEY_PADDING_RIGHT);
    CHECK_NULL_RETURN(resObjRight, true);

    auto&& updateFunc = [weakNode = AceType::WeakClaim(frameNode), isSubTabStyle](
        const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        CalcDimension right;
        auto padding = pattern->GetPadding();
        if (ResourceParseUtils::ParseResDimensionVp(resObj, right) && NonNegative(right.Value()) &&
            right.Unit() != DimensionUnit::PERCENT) {
            padding.right = NG::CalcLength(right);
        } else {
            auto pipelineContext = frameNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto tabTheme = pipelineContext->GetTheme<TabTheme>();
            CHECK_NULL_VOID(tabTheme);
            padding.right = (isSubTabStyle) ? NG::CalcLength(tabTheme->GetSubTabHorizontalPadding()) :
                NG::CalcLength(tabTheme->GetBottomTabHorizontalPadding());
        }
        pattern->SetPadding(padding);
    };
    pattern->AddResObj(KEY_PADDING_RIGHT, resObjRight, std::move(updateFunc));
    return true;
}

bool TabContentModelNG::CreatePaddingTopWithResourceObj(FrameNode* frameNode,
    const RefPtr<ResourceObject>& resObjTop, bool isSubTabStyle, bool useLocalizedPadding)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->RemoveResObj(KEY_PADDING);
    pattern->RemoveResObj(KEY_PADDING_TOP);
    CHECK_NULL_RETURN(resObjTop, true);

    auto&& updateFunc = [weakNode = AceType::WeakClaim(frameNode), isSubTabStyle](
        const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        CalcDimension top;
        auto padding = pattern->GetPadding();
        if (ResourceParseUtils::ParseResDimensionVp(resObj, top) && NonNegative(top.Value()) &&
            top.Unit() != DimensionUnit::PERCENT) {
            padding.top = NG::CalcLength(top);
        } else {
            auto pipelineContext = frameNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto tabTheme = pipelineContext->GetTheme<TabTheme>();
            CHECK_NULL_VOID(tabTheme);
            padding.top = (isSubTabStyle) ? NG::CalcLength(tabTheme->GetSubTabTopPadding()) : NG::CalcLength(0.0_vp);
        }
        pattern->SetPadding(padding);
    };
    pattern->AddResObj(KEY_PADDING_TOP, resObjTop, std::move(updateFunc));
    return true;
}

bool TabContentModelNG::CreatePaddingBottomWithResourceObj(FrameNode* frameNode,
    const RefPtr<ResourceObject>& resObjBottom, bool isSubTabStyle, bool useLocalizedPadding)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->RemoveResObj(KEY_PADDING);
    pattern->RemoveResObj(KEY_PADDING_BOTTOM);
    CHECK_NULL_RETURN(resObjBottom, true);

    auto&& updateFunc = [weakNode = AceType::WeakClaim(frameNode), isSubTabStyle](
        const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        CalcDimension bottom;
        auto padding = pattern->GetPadding();
        if (ResourceParseUtils::ParseResDimensionVp(resObj, bottom) && NonNegative(bottom.Value()) &&
            bottom.Unit() != DimensionUnit::PERCENT) {
            padding.bottom = NG::CalcLength(bottom);
        } else {
            auto pipelineContext = frameNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto tabTheme = pipelineContext->GetTheme<TabTheme>();
            CHECK_NULL_VOID(tabTheme);
            padding.bottom = (isSubTabStyle) ? NG::CalcLength(tabTheme->GetSubTabBottomPadding()) :
                NG::CalcLength(0.0_vp);
        }
        pattern->SetPadding(padding);
    };
    pattern->AddResObj(KEY_PADDING_BOTTOM, resObjBottom, std::move(updateFunc));
    return true;
}

bool TabContentModelNG::CreateBoardStyleBorderRadiusWithResourceObj(FrameNode* frameNode,
    const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    const std::string key = "tabContent.BoardStyle.borderRadius";
    pattern->RemoveResObj(key);
    CHECK_NULL_RETURN(resObj, true);

    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        CalcDimension result;
        auto attrs = pattern->GetBoardStyle();
        if (!ParseType(resObj, "borderRadius", result) || result.Value() < 0.0f ||
            result.Unit() == DimensionUnit::PERCENT) {
            auto pipelineContext = frameNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto tabTheme = pipelineContext->GetTheme<TabTheme>();
            CHECK_NULL_VOID(tabTheme);
            attrs.borderRadius = tabTheme->GetFocusIndicatorRadius();
        } else {
            attrs.borderRadius = result;
        }
        pattern->SetBoardStyle(attrs);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
    return true;
}

bool TabContentModelNG::CreateIndicatorColorWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    const std::string key = "tabContent.IndicatorStyle.color";
    pattern->RemoveResObj(key);
    CHECK_NULL_RETURN(resObj, true);

    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        Color result;
        auto attrs = pattern->GetIndicatorStyle();
        if (!ParseType(resObj, "color", result)) {
            auto pipelineContext = frameNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto tabTheme = pipelineContext->GetTheme<TabTheme>();
            CHECK_NULL_VOID(tabTheme);
            attrs.color = tabTheme->GetActiveIndicatorColor();
        } else {
            attrs.color = result;
        }
        pattern->SetIndicatorStyle(attrs);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
    return true;
}

bool TabContentModelNG::CreateIndicatorHeightWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    const std::string key = "tabContent.IndicatorStyle.height";
    pattern->RemoveResObj(key);
    CHECK_NULL_RETURN(resObj, true);

    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        CalcDimension result;
        auto attrs = pattern->GetIndicatorStyle();
        if (!ParseType(resObj, "height", result) || result.Value() < 0.0f ||
            result.Unit() == DimensionUnit::PERCENT) {
            auto pipelineContext = frameNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto tabTheme = pipelineContext->GetTheme<TabTheme>();
            CHECK_NULL_VOID(tabTheme);
            attrs.height = tabTheme->GetActiveIndicatorWidth();
        } else {
            attrs.height = result;
        }
        pattern->SetIndicatorStyle(attrs);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
    return true;
}

bool TabContentModelNG::CreateIndicatorWidthWithResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    const std::string key = "tabContent.IndicatorStyle.width";
    pattern->RemoveResObj(key);
    CHECK_NULL_RETURN(resObj, true);

    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        CalcDimension result;
        auto attrs = pattern->GetIndicatorStyle();
        if (!ParseType(resObj, "width", result) || result.Value() < 0.0f || result.Unit() == DimensionUnit::PERCENT) {
            attrs.width = 0.0_vp;
        } else {
            attrs.width = result;
        }
        pattern->SetIndicatorStyle(attrs);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
    return true;
}

bool TabContentModelNG::CreateIndicatorBorderRadiusWithResourceObj(FrameNode* frameNode,
    const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    const std::string key = "tabContent.IndicatorStyle.borderRadius";
    pattern->RemoveResObj(key);
    CHECK_NULL_RETURN(resObj, true);

    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        CalcDimension result;
        auto attrs = pattern->GetIndicatorStyle();
        if (!ParseType(resObj, "borderRadius", result) || result.Value() < 0.0f ||
            result.Unit() == DimensionUnit::PERCENT) {
            attrs.borderRadius = 0.0_vp;
        } else {
            attrs.borderRadius = result;
        }
        pattern->SetIndicatorStyle(attrs);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
    return true;
}

bool TabContentModelNG::CreateIndicatorMarginTopWithResourceObj(FrameNode* frameNode,
    const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    const std::string key = "tabContent.IndicatorStyle.marginTop";
    pattern->RemoveResObj(key);
    CHECK_NULL_RETURN(resObj, true);

    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TabContentPattern>();
        CHECK_NULL_VOID(pattern);
        CalcDimension result;
        auto attrs = pattern->GetIndicatorStyle();
        if (!ParseType(resObj, "marginTop", result) || result.Value() < 0.0f ||
            result.Unit() == DimensionUnit::PERCENT) {
            auto pipelineContext = frameNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto tabTheme = pipelineContext->GetTheme<TabTheme>();
            CHECK_NULL_VOID(tabTheme);
            attrs.marginTop = tabTheme->GetSubTabIndicatorGap();
        } else {
            attrs.marginTop = result;
        }
        pattern->SetIndicatorStyle(attrs);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
    return true;
}

void TabContentModelNG::SetTabBar(const std::optional<std::string>& text, const std::optional<std::string>& icon,
    const std::optional<TabBarSymbol>& tabBarSymbol, TabBarBuilderFunc&& builder, bool /*useContentOnly*/)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Icon, icon.value_or(""));
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Text, text.value_or(""));
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetTabBar(text.value_or(""), icon.value_or(""), tabBarSymbol, std::move(builder));
    frameNodePattern->SetTabBarWithContent(nullptr);
}

void TabContentModelNG::SetTabBarWithContent(const RefPtr<NG::UINode>& content)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetTabBarWithContent(content);
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

void TabContentModelNG::SetIndicatorColorByUser(bool isByUser)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, IndicatorColorSetByUser, isByUser);
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

void TabContentModelNG::SetLabelUnselectedColorByUser(bool isByUser)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, LabelUnselectedColorSetByUser, isByUser);
}

void TabContentModelNG::SetLabelSelectedColorByUser(bool isByUser)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, LabelSelectedColorSetByUser, isByUser);
}

void TabContentModelNG::SetIconStyle(const IconStyle& iconStyle)
{
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetIconStyle(iconStyle);
}

void TabContentModelNG::SetIconUnselectedColorByUser(bool isByUser)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, IconUnselectedColorSetByUser, isByUser);
}

void TabContentModelNG::SetIconSelectedColorByUser(bool isByUser)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, IconSelectedColorSetByUser, isByUser);
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
        if (labelStyle.textOverflow.value() == TextOverflow::MARQUEE) {
            textLayoutProperty->UpdateTextMarqueeStartPolicy(MarqueeStartPolicy::DEFAULT);
        }
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
    frameNodePattern->SetTabBarWithContent(nullptr);
}

void TabContentModelNG::SetTabBarLabel(FrameNode* node, const std::string& label)
{
    CHECK_NULL_VOID(node);
    auto frameNodePattern = node->GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetTabBar(label, "", std::nullopt, nullptr);
    frameNodePattern->SetTabBarWithContent(nullptr);
}

void TabContentModelNG::SetOnWillShow(FrameNode* tabContentNode, std::function<void()>&& onWillShow)
{
    CHECK_NULL_VOID(tabContentNode);
    auto tabContentEventHub = tabContentNode->GetEventHub<TabContentEventHub>();
    CHECK_NULL_VOID(tabContentEventHub);
    tabContentEventHub->SetOnWillShow(onWillShow);
}
void TabContentModelNG::SetOnWillHide(FrameNode* tabContentNode, std::function<void()>&& onWillHide)
{
    CHECK_NULL_VOID(tabContentNode);
    auto tabContentEventHub = tabContentNode->GetEventHub<TabContentEventHub>();
    CHECK_NULL_VOID(tabContentEventHub);
    tabContentEventHub->SetOnWillHide(onWillHide);
}
} // namespace OHOS::Ace::NG
