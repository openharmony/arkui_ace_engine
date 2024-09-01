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

#include "bridge/declarative_frontend/jsview/models/tabs_model_impl.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_v2/tabs/tabs_component.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr Dimension DEFAULT_TAB_BAR_HEIGHT = 56.0_vp;

} // namespace

void TabsModelImpl::Create(BarPosition barPosition, int32_t /*index*/, const RefPtr<TabController>& tabController,
    const RefPtr<SwiperController>& /*swiperController*/)
{
    std::list<RefPtr<Component>> children;
    auto tabsComponent = AceType::MakeRefPtr<V2::TabsComponent>(children, barPosition, tabController);
    auto tabBar = tabsComponent->GetTabBarChild();
    if (tabBar) {
        tabBar->InitStyle(GetTheme());
        auto box = AceType::DynamicCast<BoxComponent>(tabBar->GetParent().Upgrade());
        if (box) {
            box->SetHeight(DEFAULT_TAB_BAR_HEIGHT);
        }
    }
    ViewStackProcessor::GetInstance()->PushTabs(tabsComponent);
    ViewStackProcessor::GetInstance()->Push(tabsComponent);
}

void TabsModelImpl::Pop()
{
    ViewStackProcessor::GetInstance()->PopTabs();
    JSContainerBase::Pop();
}

void TabsModelImpl::SetIndex(int32_t index)
{
    auto component = AceType::DynamicCast<V2::TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto controller = component->GetTabsController();
    CHECK_NULL_VOID(controller);
    controller->SetPendingIndex(index);
}

void TabsModelImpl::SetTabBarPosition(BarPosition tabBarPosition)
{
    auto component = AceType::DynamicCast<V2::TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto tabBar = component->GetTabBarChild();
    CHECK_NULL_VOID(tabBar);
    tabBar->SetBarPosition(tabBarPosition);
}

void TabsModelImpl::SetTabBarMode(TabBarMode tabBarMode)
{
    auto component = AceType::DynamicCast<V2::TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto tabBar = component->GetTabBarChild();
    CHECK_NULL_VOID(tabBar);
    tabBar->SetMode(tabBarMode);
}

void TabsModelImpl::SetTabBarWidth(const Dimension& tabBarWidth)
{
    auto component = AceType::DynamicCast<V2::TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto tabBar = component->GetTabBarChild();
    CHECK_NULL_VOID(tabBar);
    auto box = AceType::DynamicCast<BoxComponent>(tabBar->GetParent().Upgrade());
    CHECK_NULL_VOID(box);
    box->SetWidth(tabBarWidth);
}

void TabsModelImpl::SetTabBarHeight(const Dimension& tabBarHeight)
{
    auto component = AceType::DynamicCast<V2::TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto tabBar = component->GetTabBarChild();
    CHECK_NULL_VOID(tabBar);
    auto box = AceType::DynamicCast<BoxComponent>(tabBar->GetParent().Upgrade());
    CHECK_NULL_VOID(box);
    box->SetHeight(tabBarHeight);
}

void TabsModelImpl::SetIsVertical(bool isVertical)
{
    auto tabsComponent = AceType::DynamicCast<V2::TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(tabsComponent);
    if (isVertical) {
        tabsComponent->SetDirection(FlexDirection::ROW);
    } else {
        tabsComponent->SetDirection(FlexDirection::COLUMN);
    }
    auto tabBar = tabsComponent->GetTabBarChild();
    if (tabBar) {
        tabBar->SetVertical(isVertical);
    }
    auto tabContent = tabsComponent->GetTabContentChild();
    if (tabContent) {
        tabContent->SetVertical(isVertical);
    }
}

void TabsModelImpl::SetScrollable(bool scrollable)
{
    auto component = AceType::DynamicCast<V2::TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto tabContent = component->GetTabContentChild();
    CHECK_NULL_VOID(tabContent);
    tabContent->SetScrollable(scrollable);
}

void TabsModelImpl::SetAnimationDuration(float duration)
{
    auto component = AceType::DynamicCast<V2::TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto tabContent = component->GetTabContentChild();
    CHECK_NULL_VOID(tabContent);
    tabContent->SetScrollDuration(duration);
}

void TabsModelImpl::SetOnChange(std::function<void(const BaseEventInfo*)>&& onChange)
{
    auto component = AceType::DynamicCast<V2::TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(component);
    auto tabContent = component->GetTabContentChild();
    CHECK_NULL_VOID(tabContent);
    tabContent->SetChangeEventId(EventMarker(std::move(onChange)));
}

RefPtr<TabTheme> TabsModelImpl::GetTheme() const
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetTheme<TabTheme>();
}

} // namespace OHOS::Ace::Framework
