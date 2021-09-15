/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/navigation_bar/navigation_container_component.h"

#include "core/components/box/box_component.h"
#include "core/components/flex/flex_component.h"
#include "core/components/flex/flex_item_component.h"
#include "core/components/navigation_bar/navigation_bar_component.h"
#include "core/components/navigation_bar/navigation_container_element.h"
#include "core/components/navigation_bar/render_navigation_container.h"
#include "core/components/padding/padding_component.h"
#include "core/components/stage/stage_component.h"

namespace OHOS::Ace {

namespace {

static uint32_t g_navigationTabControllerId = 0;
#ifndef WEARABLE_PRODUCT
constexpr int32_t BOTTOM_TAB_ICON_SIZE = 24;
constexpr int32_t BOTTOM_TAB_ICON_AND_TEXT_PADDING = 2;
#endif
constexpr double SECTION_INDEX_PART_WEIGHT = 1.0;
constexpr double SECTION_CONTENT_PART_WEIGHT = 2.0;

} // namespace

void NavigationDeclaration::Append(const RefPtr<NavigationDeclaration>& other)
{
    if (!other->title_.empty()) {
        title_ = other->title_;
    }
    if (!other->subTitle_.empty()) {
        subTitle_ = other->subTitle_;
    }
    if (other->hideBar_ != HIDE::UNDEFINED) {
        hideBar_ = other->hideBar_;
    }
    if (other->hideBackButton_ != HIDE::UNDEFINED) {
        hideBackButton_ = other->hideBackButton_;
    }
    if (!other->toolbarItems_.empty()) {
        toolbarItems_ = other->toolbarItems_;
    }
    if (other->hideToolbar_ != HIDE::UNDEFINED) {
        hideToolbar_ = other->hideToolbar_;
    }
}

RefPtr<RenderNode> NavigationContainerComponent::CreateRenderNode()
{
#ifndef WEARABLE_PRODUCT
    return RenderNavigationContainer::Create();
#else
    return RenderFlex::Create();
#endif
}

RefPtr<Element> NavigationContainerComponent::CreateElement()
{
#ifndef WEARABLE_PRODUCT
    return AceType::MakeRefPtr<NavigationContainerElement>();
#else
    return AceType::MakeRefPtr<FlexElement>();
#endif
}

uint32_t NavigationContainerComponent::GetGlobalTabControllerId()
{
    return ++g_navigationTabControllerId;
}

RefPtr<Component> NavigationContainerComponent::BuildNavigationBar() const
{
    if (declaration_ && declaration_->HasNavigationBar() && !declaration_->GetTitle().empty()) {
        auto navigationBar = AceType::MakeRefPtr<NavigationBarComponent>(std::string(""), "NavigationBar");
        auto navigationBarData = navigationBar->GetData();
        navigationBarData->theme = AceType::MakeRefPtr<ThemeManager>()->GetTheme<NavigationBarTheme>();
        navigationBarData->title = declaration_->GetTitle();
        if (!declaration_->GetSubTitle().empty()) {
            navigationBarData->subTitle = declaration_->GetSubTitle();
        }
        navigationBarData->backEnabled = declaration_->HasBackButton();
        return navigationBar;
    }
    return nullptr;
}

RefPtr<Component> NavigationContainerComponent::BuildTabBar()
{
#ifndef WEARABLE_PRODUCT
    std::list<RefPtr<Component>> tabBarItems;
    for (const auto& item : declaration_->GetToolBarItems()) {
        if (!item.icon.empty()) {
            auto itemContainer = AceType::MakeRefPtr<ColumnComponent>(
                FlexAlign::CENTER, FlexAlign::CENTER, std::list<RefPtr<OHOS::Ace::Component>>());
            auto iconBox = AceType::MakeRefPtr<BoxComponent>();
            iconBox->SetChild(AceType::MakeRefPtr<ImageComponent>(item.icon));
            iconBox->SetHeight(BOTTOM_TAB_ICON_SIZE, DimensionUnit::VP);
            iconBox->SetWidth(BOTTOM_TAB_ICON_SIZE, DimensionUnit::VP);
            itemContainer->AppendChild(iconBox);
            auto padding = AceType::MakeRefPtr<PaddingComponent>();
            padding->SetPaddingTop(Dimension(BOTTOM_TAB_ICON_AND_TEXT_PADDING, DimensionUnit::VP));
            itemContainer->AppendChild(padding);
            itemContainer->AppendChild(AceType::MakeRefPtr<TextComponent>(item.value));
            tabBarItems.push_back(itemContainer);
        } else {
            tabBarItems.push_back(AceType::MakeRefPtr<TextComponent>(item.value));
        }
    }
    tabController_ = TabController::GetController(GetGlobalTabControllerId());
    auto tabBar = AceType::MakeRefPtr<TabBarComponent>(tabBarItems, tabController_);
    auto theme = AceType::MakeRefPtr<ThemeManager>()->GetTheme<TabTheme>();
    tabBar->InitBottomTabStyle(theme);

    RefPtr<BoxComponent> tabBarBox = AceType::MakeRefPtr<BoxComponent>();
    tabBarBox->SetChild(tabBar);
    tabBarBox->SetDeliverMinToChild(false);
    tabBarBox->SetHeight(theme->GetDefaultHeight().Value(), theme->GetDefaultHeight().Unit());
    return tabBarBox;
#else
    return nullptr;
#endif
}

bool NavigationContainerComponent::NeedSection() const
{
    bool isSupportDeviceType = SystemProperties::GetDeviceType() == DeviceType::TABLET;
    bool isWideScreen = SystemProperties::GetDevcieOrientation() == DeviceOrientation::LANDSCAPE;
    return isSupportDeviceType && isWideScreen;
}

void NavigationContainerComponent::Build()
{
    if (!declaration_) {
        return;
    }

    auto content = GetChildren();
    ClearChildren();

    auto originalContent = AceType::MakeRefPtr<ColumnComponent>(FlexAlign::FLEX_START, FlexAlign::FLEX_START, content);
    RefPtr<ColumnComponent> fixPart;
    auto navigationBar = BuildNavigationBar();
    if (navigationBar) {
        fixPart = AceType::MakeRefPtr<ColumnComponent>(
            FlexAlign::FLEX_START, FlexAlign::FLEX_START, std::list<RefPtr<OHOS::Ace::Component>>());
        fixPart->AppendChild(navigationBar);
        if (declaration_ && declaration_->HasToolBar()) {
            fixPart->AppendChild(AceType::MakeRefPtr<FlexItemComponent>(1.0, 1.0, 0.0, originalContent));
            fixPart->AppendChild(BuildTabBar());
        } else {
            fixPart->AppendChild(AceType::MakeRefPtr<FlexItemComponent>(0.0, 1.0, 0.0, originalContent));
        }
    } else {
        fixPart = originalContent;
    }

    if (NeedSection()) {
        auto rootContainer = AceType::MakeRefPtr<RowComponent>(
            FlexAlign::FLEX_START, FlexAlign::FLEX_START, std::list<RefPtr<OHOS::Ace::Component>>());
        fixPart->SetFlexWeight(SECTION_INDEX_PART_WEIGHT);
        rootContainer->AppendChild(fixPart);

        auto sectionPart = AceType::MakeRefPtr<StageComponent>(std::list<RefPtr<Component>>(), true);
        sectionPart->SetFlexWeight(SECTION_CONTENT_PART_WEIGHT);
        rootContainer->AppendChild(sectionPart);

        AppendChild(rootContainer);
    } else {
        AppendChild(fixPart);
    }
}

} // namespace OHOS::Ace
