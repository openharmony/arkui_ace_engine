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

#include "ui/view/components/tabs/tabs.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/base/ace_type.h"
#include "ui/view_stack/view_stack_processor.h"

#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_controller.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components/tab_bar/tab_theme.h"

namespace OHOS::Ace::Kit {

struct TabsThemeInfo {
    Ace::Dimension bottomTabBarSpace;
    Ace::Dimension bottomTabTextSize;
};

Tabs::Tabs()
{
    int32_t nodeId = Ace::Kit::ViewStackProcessor::ClaimNodeId();
    auto aceNode = NG::TabsModelNG::CreateFrameNode(nodeId);
    node_ = AceType::MakeRefPtr<FrameNodeImpl>(aceNode);
}

Tabs::Tabs(RefPtr<FrameNode>& node)
{
    node_ = node;
}

Tabs::~Tabs() = default;

RefPtr<Tabs> Tabs::Create()
{
    return Referenced::MakeRefPtr<Tabs>();
}

RefPtr<Tabs> Tabs::Create(RefPtr<FrameNode>& node)
{
    return Referenced::MakeRefPtr<Tabs>(node);
}

RefPtr<NG::TabsNode> GetTabsNode(const RefPtr<FrameNode>& node)
{
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(node);
    CHECK_NULL_RETURN(frameNodeImpl, nullptr);
    auto aceFrameNode = frameNodeImpl->GetAceNode();
    CHECK_NULL_RETURN(aceFrameNode, nullptr);
    return AceType::DynamicCast<NG::TabsNode>(aceFrameNode);
}

void Tabs::UpdateDividerOpacity(const double opacity)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    auto divider = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetDivider());
    CHECK_NULL_VOID(divider);
    NG::ViewAbstract::SetOpacity(Referenced::RawPtr(divider), opacity);
}

void Tabs::UpdateTabBarBrightness(const BrightnessOption& brightnessOption)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    NG::ViewAbstract::SetBgDynamicBrightness(Referenced::RawPtr(tabBarNode), brightnessOption);
}

void Tabs::UpdateEffectNodeBrightness(const BrightnessOption& brightnessOption)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    auto effectNode = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetEffectNode());
    CHECK_NULL_VOID(effectNode);
    NG::ViewAbstract::SetBgDynamicBrightness(Referenced::RawPtr(effectNode), brightnessOption);
}

auto GetTabBarFrameRect(const RefPtr<FrameNode>& node)
{
    auto tabsNode = GetTabsNode(node);
    CHECK_NULL_RETURN(tabsNode, NG::RectF {});
    auto tabBarNode = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, NG::RectF {});
    auto geometryNode = tabBarNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, NG::RectF {});
    return geometryNode->GetFrameRect();
}

void Tabs::SetBarBackgroundBlurStyle(const BlurStyleOption& styleOption)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    NG::TabsModelNG::SetBarBackgroundBlurStyle(Referenced::RawPtr(tabsNode), styleOption);
}

void Tabs::SetBarBackgroundColor(const Color& backgroundColor)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    NG::TabsModelNG::SetBarBackgroundColor(Referenced::RawPtr(tabsNode), backgroundColor);
}

void Tabs::SetBarBackgroundEffect(const EffectOption& effectOption)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    NG::TabsModelNG::SetBarBackgroundEffect(Referenced::RawPtr(tabsNode), effectOption);
}

uint32_t Tabs::GetAnimationDuration()
{
    auto tabBarNode = GetTabBar();
    CHECK_NULL_RETURN(tabBarNode, 0);
    auto aceFrameNode = reinterpret_cast<NG::FrameNode*>(tabBarNode->GetHandle());
    CHECK_NULL_RETURN(aceFrameNode, 0);
    auto tabPattern = aceFrameNode->GetPattern<NG::TabBarPattern>();
    CHECK_NULL_RETURN(tabPattern, 0);
    auto animationDuration = tabPattern->GetAnimationDuration();
    if (animationDuration && animationDuration.value() >= 0) {
        return animationDuration.value();
    }

    bool bottomStyle = false;
    const int32_t itemSize = GetTabBarItemSize();
    for (int32_t index = 0; index < itemSize; index++) {
        if (tabPattern->GetTabBarStyle(index) == TabBarStyle::BOTTOMTABBATSTYLE) {
            bottomStyle = true;
            break;
        }
    }
    auto pipelineContext = tabPattern->GetContext();
    CHECK_NULL_RETURN(pipelineContext, 0);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_RETURN(tabTheme, 0);
    auto duration = static_cast<uint32_t>(tabTheme->GetTabContentAnimationDuration());
    if ((Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && bottomStyle)
        || Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        duration = 0;
    }
    return duration;
}

double Tabs::GetTabBarTop()
{
    const auto tabBarRect = GetTabBarFrameRect(node_);
    return tabBarRect.Top();
}

double Tabs::GetTabBarBottom()
{
    const auto tabBarRect = GetTabBarFrameRect(node_);
    return tabBarRect.Bottom();
}

std::size_t Tabs::GetTabBarItemSize()
{
    auto tabBarNode = GetTabBar();
    CHECK_NULL_RETURN(tabBarNode, 0);
    auto aceFrameNode = reinterpret_cast<NG::FrameNode*>(tabBarNode->GetHandle());
    CHECK_NULL_RETURN(aceFrameNode, 0);
    auto tabPattern = aceFrameNode->GetPattern<NG::TabBarPattern>();
    CHECK_NULL_RETURN(tabPattern, 0);
    return tabPattern->GetTabBarItemSize();
}

void Tabs::SetTabBarWidth(const Dimension& tabBarWidth)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    NG::TabsModelNG::SetTabBarWidth(Referenced::RawPtr(tabsNode), tabBarWidth);
}

Dimension Tabs::GetTabBarWidth() const
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_RETURN(tabsNode, {});
    auto tabsLayoutProperty = tabsNode->GetLayoutPropertyPtr<NG::TabsLayoutProperty>();
    CHECK_NULL_RETURN(tabsLayoutProperty, {});
    return tabsLayoutProperty->GetBarWidthValue({});
}

void Tabs::SetTabBarHeight(const Dimension& tabBarHeight)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    NG::TabsModelNG::SetTabBarHeight(Referenced::RawPtr(tabsNode), tabBarHeight);
}

Dimension Tabs::GetTabBarHeight() const
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_RETURN(tabsNode, {});
    auto tabsLayoutProperty = tabsNode->GetLayoutPropertyPtr<NG::TabsLayoutProperty>();
    CHECK_NULL_RETURN(tabsLayoutProperty, {});
    return tabsLayoutProperty->GetBarHeightValue({});
}

void Tabs::SetDivider(const TabsItemDivider& divider)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);

    Ace::TabsItemDivider aceDivider;
    aceDivider.strokeWidth = divider.strokeWidth;
    aceDivider.color = divider.color;
    aceDivider.startMargin = divider.startMargin;
    aceDivider.endMargin = divider.endMargin;
    aceDivider.isNull = divider.isNull;
    NG::TabsModelNG::SetDivider(Referenced::RawPtr(tabsNode), aceDivider);
}

void Tabs::SetEffectNodeOption(const TabsEffectNodeOption& option)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    NG::TabsModelNG::SetEffectNodeOption(Referenced::RawPtr(tabsNode), option);
}

void Tabs::SetTabBarMode(const TabBarMode& barMode)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    NG::TabsModelNG::SetTabBarMode(Referenced::RawPtr(tabsNode), barMode);
}

void Tabs::SetScrollableBarModeOptions(const ScrollableBarModeOptions& option)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    NG::TabsModelNG::SetScrollableBarModeOptions(Referenced::RawPtr(tabsNode), option);
}

RefPtr<NG::TabsControllerNG> GetTabsControllerNode(const RefPtr<FrameNode>& node)
{
    auto tabsNode = GetTabsNode(node);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<NG::SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, nullptr);
    auto swiperControllerNode = swiperPattern->GetSwiperController();
    CHECK_NULL_RETURN(swiperControllerNode, nullptr);
    return AceType::DynamicCast<NG::TabsControllerNG>(swiperControllerNode);
}

void Tabs::SetTabBarTranslate(const NG::TranslateOptions& options)
{
    auto tabsController = GetTabsControllerNode(node_);
    CHECK_NULL_VOID(tabsController);
    tabsController->SetTabBarTranslate(options);
}

void Tabs::SetTabBarOpacity(float opacity)
{
    auto tabsController = GetTabsControllerNode(node_);
    CHECK_NULL_VOID(tabsController);
    tabsController->SetTabBarOpacity(opacity);
}

void Tabs::SwipeTo(const int32_t index)
{
    auto tabsController = GetTabsControllerNode(node_);
    CHECK_NULL_VOID(tabsController);
    tabsController->SwipeTo(index);
}

RefPtr<FrameNode> Tabs::GetTabBar()
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    return AceType::MakeRefPtr<FrameNodeImpl>(Referenced::RawPtr(tabBarNode));
}

RefPtr<FrameNode> Tabs::GetEffectNode()
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto effectNode = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetEffectNode());
    CHECK_NULL_RETURN(effectNode, nullptr);
    return AceType::MakeRefPtr<FrameNodeImpl>(Referenced::RawPtr(effectNode));
}

void Tabs::SetOnChange(OnChangeEvent onChangeEvent)
{
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(node_);
    CHECK_NULL_VOID(frameNodeImpl);
    auto aceFrameNode = frameNodeImpl->GetAceNode();
    CHECK_NULL_VOID(aceFrameNode);
    auto tabPattern = aceFrameNode->GetPattern<NG::TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    auto onChange = [onChangeEvent](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            return;
        }
        onChangeEvent(tabsInfo->GetIndex());
    };
    tabPattern->SetOnChangeEvent(std::move(onChange));
}

void Tabs::SetOnTabBarClick(OnTabBarClickEvent onTabBarClickEvent)
{
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(node_);
    CHECK_NULL_VOID(frameNodeImpl);
    auto aceFrameNode = frameNodeImpl->GetAceNode();
    CHECK_NULL_VOID(aceFrameNode);
    auto tabPattern = aceFrameNode->GetPattern<NG::TabsPattern>();
    CHECK_NULL_VOID(tabPattern);
    auto onTabBarClick = [onTabBarClickEvent](const BaseEventInfo* info) {
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            return;
        }
        onTabBarClickEvent(tabsInfo->GetIndex());
    };
    tabPattern->SetOnTabBarClickEvent(std::move(onTabBarClick));
}

void Tabs::SetOnGestureSwipe(OnGestureSwipeEvent onGestureSwipe)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    NG::TabsModelNG::SetOnGestureSwipe(Referenced::RawPtr(tabsNode), std::move(onGestureSwipe));
}

void Tabs::SetOnAnimationStart(OnAnimationStartEvent onAnimationStart)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    NG::TabsModelNG::SetOnAnimationStart(Referenced::RawPtr(tabsNode), std::move(onAnimationStart));
}

void Tabs::SetOnTabBarItemsChange(OnTabBarItemsChangeEvent&& event)
{
    auto tabBarNode = GetTabBar();
    CHECK_NULL_VOID(tabBarNode);
    auto aceFrameNode = reinterpret_cast<NG::FrameNode*>(tabBarNode->GetHandle());
    CHECK_NULL_VOID(aceFrameNode);
    auto tabBarPattern = aceFrameNode->GetPattern<NG::TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->SetOnTabBarItemsChangeEvent(std::move(event));
}

void UpdateNormalTabBarItem(bool isFolded, RefPtr<NG::FrameNode>& tabBarChildFrameNode,
    RefPtr<NG::FrameNode>& tabBarNode, double translateX, const TabsThemeInfo& info)
{
    CHECK_NULL_VOID(tabBarChildFrameNode);
    NG::ViewAbstract::SetTranslate(tabBarChildFrameNode.GetRawPtr(), {
        isFolded ? Ace::Dimension(translateX) : Ace::Dimension{}, 0.0, 0.0 });
    auto tabBarPattern = tabBarNode->GetPattern<NG::TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    NG::TabBarParamType itemType = tabBarPattern->GetTabBarItemType(tabBarChildFrameNode->GetId());
    if (itemType == NG::TabBarParamType::NORMAL) {
        auto linearLayoutProperty = tabBarChildFrameNode->GetLayoutProperty<NG::LinearLayoutProperty>();
        CHECK_NULL_VOID(linearLayoutProperty);
        linearLayoutProperty->UpdateSpace(isFolded ? Ace::Dimension{} : info.bottomTabBarSpace);
        auto textNode = AceType::DynamicCast<NG::FrameNode>(tabBarChildFrameNode->GetChildren().back());
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<NG::TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        const auto style = tabBarPattern->GetBottomTabLabelStyle(tabBarChildFrameNode->GetId());
        if (style.minFontSize) {
            textLayoutProperty->UpdateAdaptMinFontSize(isFolded ? Ace::Dimension{0} : style.minFontSize.value());
        }
        if (style.maxFontSize) {
            textLayoutProperty->UpdateAdaptMaxFontSize(isFolded ? Ace::Dimension{0} : style.maxFontSize.value());
        }
        NG::TextModelNG::SetFontSize(textNode.GetRawPtr(), isFolded ? Ace::Dimension{} : info.bottomTabTextSize);
        NG::ViewAbstract::SetOpacity(textNode.GetRawPtr(), isFolded ? 0 : 1);
        textNode->MarkDirtyNode(NG::PROPERTY_UPDATE_LAYOUT);
    }
    NG::ViewAbstract::SetHitTestMode(tabBarChildFrameNode.GetRawPtr(),
        isFolded ? NG::HitTestMode::HTMNONE : NG::HitTestMode::HTMDEFAULT);
}

void Tabs::SetTabBarFolded(bool isFolded)
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_VOID(tabsNode);
    auto pipelineContext = tabsNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    const auto bottomTabBarSpace = tabTheme->GetBottomTabBarSpace();
    const auto bottomTabTextSize = tabTheme->GetBottomTabTextSize();
    auto tabBarNode = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    NG::ViewAbstract::SetHitTestMode(tabBarNode.GetRawPtr(),
        isFolded ? NG::HitTestMode::HTMNONE : NG::HitTestMode::HTMDEFAULT);
    auto tabBarChildren = tabBarNode->GetChildren();
    auto tabBarPattern = tabBarNode->GetPattern<NG::TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->SetShouldPlayMaskAnimation(!isFolded);
    const auto tabBarItemsSize = tabBarPattern->GetTabBarItemSize();
    CHECK_NULL_VOID(tabBarItemsSize);
    auto tabsPattern = tabsNode->GetPattern<NG::TabsPattern>();
    CHECK_NULL_VOID(tabsPattern);
 
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<NG::TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);
    auto activeTabIndex = tabsLayoutProperty->GetIndexValue(0);
    const double tabBarWidth = GetTabBarWidth().ConvertToPx();
    const double tabBarHeight = GetTabBarHeight().ConvertToPx();
    const auto padding = NG::ViewAbstract::GetPadding(tabBarNode.GetRawPtr());
    const double paddingLeft = padding.left ? padding.left->GetDimension().ConvertToPx() : 0.0;
    const double paddingRight = padding.right ? padding.right->GetDimension().ConvertToPx() : 0.0;
    const double tabBarItemWidth = (tabBarWidth - paddingLeft - paddingRight) / tabBarItemsSize;
    int32_t index = 0;
    for (const auto& tabBarChild : tabBarChildren) {
        if (index >= tabBarItemsSize) {
            break;
        }
        auto tabBarChildFrameNode = AceType::DynamicCast<NG::FrameNode>(tabBarChild);
        CHECK_NULL_VOID(tabBarChildFrameNode);
        const double x = (tabBarItemWidth - tabBarHeight) / 2 + paddingLeft + tabBarItemWidth * index; // 2 is average
        const bool isRTL = GetNonAutoLayoutDirection() == Ace::TextDirection::RTL;
        UpdateNormalTabBarItem(isFolded, tabBarChildFrameNode,
            tabBarNode, isRTL ? x : -x, {bottomTabBarSpace, bottomTabTextSize});
        if (isFolded) {
            NG::ViewAbstract::SetOpacity(tabBarChildFrameNode.GetRawPtr(), index != activeTabIndex ? 0 : 1);
        } else {
            NG::ViewAbstract::SetOpacity(tabBarChildFrameNode.GetRawPtr(), 1);
        }
        index++;
    }
}

RefPtr<FrameNode> Tabs::GetTabBarActiveItem()
{
    auto tabsNode = GetTabsNode(node_);
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    auto tabBarChildren = tabBarNode->GetChildren();
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<NG::TabsLayoutProperty>();
    CHECK_NULL_RETURN(tabsLayoutProperty, nullptr);
    auto activeTabIndex = tabsLayoutProperty->GetIndexValue(0);
    auto tabBarPattern = tabBarNode->GetPattern<NG::TabBarPattern>();
    CHECK_NULL_RETURN(tabBarPattern, nullptr);
    int32_t index = 0;
    for (const auto& tabBarChild : tabBarChildren) {
        if (index == activeTabIndex) {
            auto tabBarChildFrameNode = AceType::DynamicCast<NG::FrameNode>(tabBarChild);
            CHECK_NULL_RETURN(tabBarChildFrameNode, nullptr);
            return AceType::MakeRefPtr<FrameNodeImpl>(Referenced::RawPtr(tabBarChildFrameNode));
        }
        index++;
    }
    return nullptr;
}
} // namespace OHOS::Ace::Kit
