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

#include "core/components/tab_bar/tabs_component.h"

#include "core/components/tab_bar/tab_theme.h"
#include "core/components/tab_bar/tabs_element.h"
#include "core/components/theme/theme_manager.h"

namespace OHOS::Ace {
namespace {

static uint32_t g_tabControllerId = 0;

} // namespace

uint32_t TabsComponent::GetGlobalTabControllerId()
{
    return ++g_tabControllerId;
}

TabsComponent::TabsComponent(FlexDirection direction, FlexAlign mainAxisAlign, FlexAlign crossAxisAlign,
    std::list<RefPtr<Component>>& children, BarPosition barPosition) : FlexComponent(FlexDirection::COLUMN,
    FlexAlign::FLEX_START, FlexAlign::CENTER, children)
{
    controller_ = TabController::GetController(GetGlobalTabControllerId());
    tabBarIndicator_ = AceType::MakeRefPtr<TabBarIndicatorComponent>();
    tabBar_ = AceType::MakeRefPtr<TabBarComponent>(tabBarChildren_, controller_, tabBarIndicator_);
    tabContent_ = AceType::MakeRefPtr<TabContentComponent>(tabContentChildren_, controller_);
    flexItem_ = AceType::MakeRefPtr<FlexItemComponent>(0, 1, 0);
    flexItem_->SetChild(tabContent_);
    auto box = AceType::MakeRefPtr<BoxComponent>();
    box->SetChild(tabBar_);
    if (barPosition == BarPosition::END) {
        AppendChildDirectly(flexItem_);
        AppendChildDirectly(box);
    } else {
        AppendChildDirectly(box);
        AppendChildDirectly(flexItem_);
    }
}

RefPtr<Element> TabsComponent::CreateElement()
{
    return AceType::MakeRefPtr<TabsElement>();
}

void TabsComponent::AppendChild(const RefPtr<Component>& child)
{
    flexItem_->SetChild(child);
}

} // namespace OHOS::Ace
