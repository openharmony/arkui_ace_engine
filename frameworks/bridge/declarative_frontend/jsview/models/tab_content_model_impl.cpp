/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/tab_content_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr char DEFAULT_TAB_BAR_NAME[] = "TabBar";

} // namespace

void TabContentModelImpl::Create()
{
    std::list<RefPtr<Component>> components;
    auto tabContentItemComponent = AceType::MakeRefPtr<V2::TabContentItemComponent>(components);
    tabContentItemComponent->SetCrossAxisSize(CrossAxisSize::MAX);
    ViewStackProcessor::GetInstance()->ClaimElementId(tabContentItemComponent);

    RefPtr<V2::TabsComponent> tabsComponent = nullptr;
    tabsComponent = AceType::DynamicCast<V2::TabsComponent>(ViewStackProcessor::GetInstance()->GetTopTabs());
    CHECK_NULL_VOID(tabsComponent);
    // GetTabsComponent used only by JSTabContent::SetTabBar
    // To Find TabBarComponent eventually
    tabContentItemComponent->SetTabsComponent(AceType::WeakClaim(AceType::RawPtr(tabsComponent)));

    auto tabBar = tabsComponent->GetTabBarChild();
    tabBar->AppendChild(CreateTabBarLabelComponent(tabContentItemComponent, std::string(DEFAULT_TAB_BAR_NAME)));

    ViewStackProcessor::GetInstance()->Push(tabContentItemComponent);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    CHECK_NULL_VOID(box);
    box->SetBoxClipFlag(true);
}

void TabContentModelImpl::Create(std::function<void()>&& deepRenderFunc)
{
    std::list<RefPtr<Component>> components;
    auto tabContentItemComponent = AceType::MakeRefPtr<V2::TabContentItemComponent>(components);
    tabContentItemComponent->SetCrossAxisSize(CrossAxisSize::MAX);
    ViewStackProcessor::GetInstance()->ClaimElementId(tabContentItemComponent);

    RefPtr<V2::TabsComponent> tabsComponent = nullptr;
    ViewStackProcessor::GetInstance()->Push(tabContentItemComponent);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    if (box) {
        box->SetBoxClipFlag(true);
    }

    auto jsWrapperFunc = [builder = std::move(deepRenderFunc)]() -> RefPtr<Component> {
        CHECK_NULL_RETURN(builder, nullptr);
        builder();
        return ViewStackProcessor::GetInstance()->Finish();
    };
    tabContentItemComponent->SetBuilder(std::move(jsWrapperFunc));
}

void TabContentModelImpl::Pop()
{
    JSContainerBase::Pop();
}

void TabContentModelImpl::SetTabBar(const std::optional<std::string>& text, const std::optional<std::string>& icon,
    const std::optional<TabBarSymbol>& tabBarSymbol, std::function<void()>&& builder, bool useContentOnly)
{
    auto tabContentItemComponent =
        AceType::DynamicCast<V2::TabContentItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(tabContentItemComponent);

    auto weakTabs = tabContentItemComponent->GetTabsComponent();
    // Full update: tabs and tabBar always exist
    // Partial update: tabs and tabBar exist for initial render and nullptr for rerender
    auto tabs = weakTabs.Upgrade();
    auto tabBar = tabs ? tabs->GetTabBarChild() : nullptr;

    if (!Container::IsCurrentUsePartialUpdate()) {
        CHECK_NULL_VOID(tabs);
        CHECK_NULL_VOID(tabBar);
    }

    RefPtr<Component> tabBarChild = nullptr;
    if (useContentOnly) {
        auto textVal = text.value_or(DEFAULT_TAB_BAR_NAME);
        if (!Container::IsCurrentUsePartialUpdate()) {
            tabBarChild = CreateTabBarLabelComponent(tabContentItemComponent, textVal);
        } else {
            tabContentItemComponent->SetBarText(textVal);
        }
    } else {
        // For Partial Update ProcessTabBarXXX methods
        // do not create any components for the tab bar items
        // and return nullptr.
        // Tab bar items created and added later by
        // TabContentItemElementProxy class.
        if (builder) {
            tabBarChild = ProcessTabBarBuilderFunction(tabContentItemComponent, std::move(builder));
            // Update tabBar always for full update and for initial render only for partial update
            if (tabBar) {
                tabBar->ResetIndicator();
                tabBar->SetAlignment(Alignment::TOP_LEFT);
            }
        } else if (text.has_value() && icon.has_value()) {
            tabBarChild = ProcessTabBarTextIconPair(tabContentItemComponent, text, icon);
        } else if (text.has_value() && !icon.has_value()) {
            tabBarChild = ProcessTabBarLabel(tabContentItemComponent, text);
        }
    }

    if (!Container::IsCurrentUsePartialUpdate()) {
        auto defaultTabChild = tabBar->GetChildren().back();
        tabBar->RemoveChildDirectly(defaultTabChild);
        tabBar->AppendChild(tabBarChild);
        return;
    }

    // Partial Update only
    if (tabContentItemComponent->GetBarElementId() == ElementRegister::UndefinedElementId) {
        const auto id = ElementRegister::GetInstance()->MakeUniqueId();
        tabContentItemComponent->SetBarElementId(id);
    }
}

RefPtr<Component> TabContentModelImpl::ProcessTabBarBuilderFunction(
    RefPtr<V2::TabContentItemComponent>& tabContent, std::function<void()>&& builderFunc)
{
    CHECK_NULL_RETURN(builderFunc, nullptr);
    tabContent->SetBarText("custom");
    if (Container::IsCurrentUsePartialUpdate()) {
        auto jsWrapperFunc = [builder = std::move(builderFunc)]() -> RefPtr<Component> {
            builder();
            return ViewStackProcessor::GetInstance()->Finish();
        };
        tabContent->SetBarBuilder(jsWrapperFunc);
        return nullptr;
    }

    ScopedViewStackProcessor builderViewStackProcessor;
    builderFunc();
    RefPtr<Component> builderGeneratedRootComponent = ViewStackProcessor::GetInstance()->Finish();
    return builderGeneratedRootComponent;
}

RefPtr<Component> TabContentModelImpl::CreateTabBarLabelComponent(
    RefPtr<V2::TabContentItemComponent>& tabContent, const std::string& labelStr)
{
    tabContent->SetBarText(labelStr);
    return TabBarItemComponent::BuildWithTextIcon(labelStr, std::string());
}

RefPtr<Component> TabContentModelImpl::ProcessTabBarLabel(
    RefPtr<V2::TabContentItemComponent>& tabContent, const std::optional<std::string>& textVal)
{
    std::string textStr = textVal.value_or(DEFAULT_TAB_BAR_NAME);
    tabContent->SetBarText(textStr);

    if (!Container::IsCurrentUsePartialUpdate()) {
        return CreateTabBarLabelComponent(tabContent, textStr);
    }
    return nullptr;
}

RefPtr<Component> TabContentModelImpl::ProcessTabBarTextIconPair(RefPtr<V2::TabContentItemComponent>& tabContent,
    const std::optional<std::string>& textVal, const std::optional<std::string>& iconVal)
{
    if (!iconVal.has_value()) {
        return ProcessTabBarLabel(tabContent, textVal);
    }

    auto textStr = textVal.value_or(DEFAULT_TAB_BAR_NAME);
    tabContent->SetBarText(textStr);
    tabContent->SetBarIcon(iconVal.value());

    if (!Container::IsCurrentUsePartialUpdate()) {
        return TabBarItemComponent::BuildWithTextIcon(textStr, iconVal.value());
    }
    return nullptr;
}

} // namespace OHOS::Ace::Framework
