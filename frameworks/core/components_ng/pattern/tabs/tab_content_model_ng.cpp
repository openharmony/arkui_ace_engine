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
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_node.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

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
    auto frameNode = TabContentNode::GetOrCreateTabContentNode(V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId,
        [shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender))]() {
            return AceType::MakeRefPtr<TabContentPattern>(shallowBuilder);
        });
    stack->Push(frameNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    SetTabBar(tabTheme->GetDefaultTabBarName(), "", nullptr, true); // Set default tab bar.
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Text, tabTheme->GetDefaultTabBarName());
}

void TabContentModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto frameNode = TabContentNode::GetOrCreateTabContentNode(
        V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabContentPattern>(nullptr); });
    stack->Push(frameNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    SetTabBar(tabTheme->GetDefaultTabBarName(), "", nullptr, true); // Set default tab bar.
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Text, tabTheme->GetDefaultTabBarName());
}

void TabContentModelNG::Pop()
{
    auto tabContent = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    LOGD("position %{public}d", position);
    CHECK_NULL_VOID(tabContent);
    auto tabContentId = tabContent->GetId();

    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContent);
    CHECK_NULL_VOID(tabContentNode);

    if (update && !tabContentNode->HasTabBarItemId()) {
        LOGD("Update only, return");
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
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto linearLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(linearLayoutProperty);
    linearLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    linearLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    linearLayoutProperty->UpdateSpace(tabTheme->GetBottomTabBarSpace());
    auto columnRenderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(columnRenderContext);
    columnRenderContext->UpdateClipEdge(true);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabBarNode);
    CHECK_NULL_VOID(tabBarFrameNode);
    auto tabBarPattern = tabBarFrameNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->SetTabBarStyle(tabBarParam.GetTabBarStyle());
    auto selectedMode = tabContentPattern->GetSelectedMode();
    auto indicatorStyle = tabContentPattern->GetIndicatorStyle();
    auto boardStyle = tabContentPattern->GetBoardStyle();

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto myIndex = swiperNode->GetChildFlatIndex(tabContentId).second;
    
    tabBarPattern->SetTabBarStyle(tabBarParam.GetTabBarStyle(), myIndex);
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
    tabBarPattern->SetSelectedMode(selectedMode, myIndex);
    tabBarPattern->SetIndicatorStyle(indicatorStyle, myIndex);
    tabBarPattern->UpdateSubTabBoard();

    // Create tab bar with builder.
    if (tabBarParam.HasBuilder()) {
        ScopedViewStackProcessor builderViewStackProcessor;
        tabBarParam.ExecuteBuilder();
        auto builderNode = ViewStackProcessor::GetInstance()->Finish();
        if (static_cast<int32_t>(columnNode->GetChildren().size()) != 0) {
            columnNode->Clean();
        }
        builderNode->MountToParent(columnNode);
        auto oldColumnNode = tabsNode->GetBuilderByContentId(tabContentId, columnNode);
        if (!oldColumnNode)  {
            columnNode->MountToParent(tabBarNode, myIndex);
        } else {
            tabBarNode->ReplaceChild(oldColumnNode, columnNode);
        }
        tabBarPattern->AddTabBarItemType(tabContentId, true);
        tabBarFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        return;
    }
    if (tabBarParam.GetText().empty()) {
        LOGW("Text is empty.");
    } else {
        LOGD("Text %{public}s", tabBarParam.GetText().c_str());
    }

    // Create text node and image node.
    RefPtr<FrameNode> textNode;
    RefPtr<FrameNode> imageNode;
    auto layoutProperty = columnNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (tabBarStyle == TabBarStyle::SUBTABBATSTYLE) {
        auto horizontalPadding = tabTheme->GetSubTabHorizontalPadding();
        layoutProperty->UpdatePadding({ CalcLength(horizontalPadding), CalcLength(horizontalPadding),
            CalcLength(tabTheme->GetSubTabTopPadding()), CalcLength(tabTheme->GetSubTabBottomPadding()) });
    } else if (tabBarStyle == TabBarStyle::BOTTOMTABBATSTYLE) {
        layoutProperty->UpdatePadding({ CalcLength(tabTheme->GetBottomTabHorizontalPadding()),
            CalcLength(tabTheme->GetBottomTabHorizontalPadding()), {}, {} });
    } else {
        auto deviceType = SystemProperties::GetDeviceType();
        auto tabBarItemPadding = deviceType == DeviceType::PHONE ? tabTheme->GetSubTabHorizontalPadding()
                                                                 : tabTheme->GetSubtabLandscapeHorizontalPadding();
        layoutProperty->UpdatePadding({ CalcLength(tabBarItemPadding), CalcLength(tabBarItemPadding),
            CalcLength(tabBarItemPadding), CalcLength(tabBarItemPadding) });
    }

    if (static_cast<int32_t>(columnNode->GetChildren().size()) == 0) {
        ImageSourceInfo imageSourceInfo(tabBarParam.GetIcon());
        imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_VOID(textNode);
        CHECK_NULL_VOID(imageNode);
        columnNode->MountToParent(tabBarNode, position);
        imageNode->MountToParent(columnNode);
        textNode->MountToParent(columnNode);
    } else {
        imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
        textNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().back());
    }
    CHECK_NULL_VOID(textNode);
    CHECK_NULL_VOID(imageNode);

    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    int32_t indicator = swiperPattern->GetCurrentIndex();
    int32_t totalCount = swiperPattern->TotalCount();
    if (indicator > totalCount - 1 || indicator < 0) {
        indicator = 0;
    }

    // Update property of text.
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (myIndex == indicator) {
        textLayoutProperty->UpdateTextColor(tabTheme->GetActiveIndicatorColor());
    } else {
        textLayoutProperty->UpdateTextColor(tabTheme->GetSubTabTextOffColor());
    }
    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    textRenderContext->UpdateClipEdge(true);
    textLayoutProperty->UpdateContent(tabBarParam.GetText());
    textLayoutProperty->UpdateFontSize(tabTheme->GetSubTabTextDefaultFontSize());
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);

    // Update property of image.
    auto imageProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageProperty);
    if (!tabBarParam.GetIcon().empty() || tabBarStyle == TabBarStyle::BOTTOMTABBATSTYLE) {
        textLayoutProperty->UpdateFontSize(tabTheme->GetBottomTabTextSize());
        imageProperty->UpdateUserDefinedIdealSize(CalcSize(
            NG::CalcLength(tabTheme->GetBottomTabImageSize()), NG::CalcLength(tabTheme->GetBottomTabImageSize())));
    } else {
        imageProperty->UpdateUserDefinedIdealSize(CalcSize());
    }
    if (tabBarStyle == TabBarStyle::BOTTOMTABBATSTYLE) {
        textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    }
    auto labelStyle = tabContentPattern->GetLabelStyle();
    UpdateLabelStyle(labelStyle, textLayoutProperty);
    ImageSourceInfo imageSourceInfo(tabBarParam.GetIcon());
    if (imageSourceInfo.IsSvg()) {
        if (myIndex == indicator) {
            imageSourceInfo.SetFillColor(tabTheme->GetBottomTabIconOn());
        } else {
            imageSourceInfo.SetFillColor(tabTheme->GetBottomTabIconOff());
        }
    }
    
    imageProperty->UpdateImageSourceInfo(imageSourceInfo);
    columnNode->MarkModifyDone();
    textNode->MarkModifyDone();
    textNode->MarkDirtyNode();
    imageNode->MarkModifyDone();
    tabBarPattern->AddTabBarItemType(tabContentId, false);
    tabBarFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TabContentModelNG::RemoveTabBarItem(const RefPtr<TabContentNode>& tabContentNode)
{
    CHECK_NULL_VOID(tabContentNode);
    if (!tabContentNode->HasTabBarItemId()) {
        return;
    }

    auto tabBarItemId = tabContentNode->GetTabBarItemId();
    LOGD("Tab ID: %{public}d, Bar item ID: %{public}d", tabContentNode->GetId(), tabBarItemId);
    auto tabBarItemNode = ElementRegister::GetInstance()->GetUINodeById(tabBarItemId);
    CHECK_NULL_VOID(tabBarItemNode);
    auto tabBarNode = tabBarItemNode->GetParent();
    tabBarNode->RemoveChild(tabBarItemNode);
    CHECK_NULL_VOID(tabBarNode);
    tabContentNode->ResetTabBarItemId();
}

void TabContentModelNG::SetTabBar(const std::optional<std::string>& text, const std::optional<std::string>& icon,
    TabBarBuilderFunc&& builder, bool /*useContentOnly*/)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Icon, icon.value_or(""));
    ACE_UPDATE_LAYOUT_PROPERTY(TabContentLayoutProperty, Text, text.value_or(""));
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    CHECK_NULL_VOID(frameNodePattern);
    frameNodePattern->SetTabBar(text.value_or(""), icon.value_or(""), std::move(builder));
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
} // namespace OHOS::Ace::NG
