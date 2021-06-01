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

#include "core/components/tab_bar/tab_bar_element.h"

#include "base/utils/system_properties.h"
#include "core/components/tab_bar/render_tab_bar.h"
#include "core/components/text/text_component.h"

namespace OHOS::Ace {

RefPtr<RenderNode> TabBarElement::CreateRenderNode()
{
    RefPtr<RenderNode> node = ComponentGroupElement::CreateRenderNode();

    RefPtr<RenderTabBar> tabBar = AceType::DynamicCast<RenderTabBar>(node);
    if (tabBar) {
        tabBar->RegisterCallback([weakTabBarElement = AceType::WeakClaim(this)](int32_t index) {
            auto tabBar = weakTabBarElement.Upgrade();
            if (tabBar) {
                tabBar->UpdateElement(index);
            }
        });
    }
    return node;
}

void TabBarElement::UpdateElement(int32_t index)
{
    if (controller_) {
        int32_t preIndex = controller_->GetIndex();
        controller_->SetIndex(index);
        int32_t curIndex = controller_->GetIndex();
        if (preIndex != curIndex) {
            LOGD("TabBar change from %{public}d to %{public}d", preIndex, curIndex);
            controller_->ChangeDispatch(curIndex);
        }
        UpdateIndex(curIndex);
    }
}

void TabBarElement::Update()
{
    ComponentGroupElement::Update();

    if (component_) {
        RefPtr<TabBarComponent> tabBar = AceType::DynamicCast<TabBarComponent>(component_);
        if (!tabBar) {
            LOGE("TabBarElement::Update: get TabBarComponent failed!");
            return;
        }
        controller_ = tabBar->GetController();
        if (controller_) {
            controller_->SetBarElement(AceType::Claim(this));
        }

        indicatorStyle_ = tabBar->GetIndicator();
        focusIndicatorStyle_ = tabBar->GetFocusIndicator();

        tabs_.clear();
        tabBar->BuildItems(tabs_);
        auto domChangeEvent = AceAsyncEvent<void(uint32_t)>::Create(tabBar->GetDomChangeEventId(), GetContext());
        if (domChangeEvent) {
            int32_t index = controller_ ? controller_->GetIndex() : 0;
            domChangeEvent(index);
        }
        vertical_ = tabBar->IsVertical();
    }
}

bool TabBarElement::RequestNextFocus(bool vertical, bool reverse, const Rect& rect)
{
    if (vertical_ == vertical) {
        if (GoToNextFocus(reverse)) {
            int32_t index = std::distance(focusNodes_.begin(), itLastFocusNode_);
            UpdateElement(index);
            return true;
        }
    }
    return false;
}

void TabBarElement::UpdateIndex(int32_t index)
{
    RefPtr<RenderTabBar> tabBar = AceType::DynamicCast<RenderTabBar>(renderNode_);
    if (tabBar) {
        tabBar->SetIndex(index);
    }
}

void TabBarElement::PerformBuild()
{
    if (tabs_.empty()) {
        LOGD("tabs is empty");
        ComponentGroupElement::PerformBuild();
        return;
    }

    LOGD("TabBarElement::PerformBuild");
    int32_t index = 0;
    for (auto& box : tabs_) {
        UpdateChild(GetChild(index), box);
        index++;
    }

    GetRenderNode()->MarkNeedLayout();
}

RefPtr<Element> TabBarElement::GetChild(int32_t index)
{
    if (index >= 0 && decltype(children_)::size_type(index) < children_.size()) {
        auto pos = children_.begin();
        std::advance(pos, index);
        return (*pos);
    }
    return nullptr;
}

void TabBarElement::OnFocus()
{
    LOGD("TabBar element OnFocus");
    RefPtr<RenderTabBar> tabBar = AceType::DynamicCast<RenderTabBar>(renderNode_);
    if (tabBar) {
        tabBar->HandleFocusEvent(true);
        if (focusIndicatorStyle_) {
            tabBar->UpdateIndicatorStyle(focusIndicatorStyle_);
        }
    }
    if (controller_) {
        int32_t index = controller_->GetIndex();
        int32_t size = focusNodes_.size();
        if (size > 0) {
            size--;
        }
        index = std::clamp(index, 0, size);
        itLastFocusNode_ = focusNodes_.begin();
        std::advance(itLastFocusNode_, index);
    }

    return FocusGroup::OnFocus();
}

void TabBarElement::OnBlur()
{
    LOGD("TabBar element Onblur");
    RefPtr<RenderTabBar> tabBar = AceType::DynamicCast<RenderTabBar>(renderNode_);
    if (tabBar) {
        tabBar->HandleFocusEvent(false);
        if (indicatorStyle_) {
            tabBar->UpdateIndicatorStyle(indicatorStyle_);
        }
    }
    return FocusGroup::OnBlur();
}

} // namespace OHOS::Ace