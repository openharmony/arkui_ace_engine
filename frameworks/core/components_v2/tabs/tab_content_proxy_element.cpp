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

#include "core/components_v2/tabs/tab_content_proxy_element.h"

#include "core/components_v2/tabs/tabs_helper.h"

namespace OHOS::Ace::V2 {

void TabContentProxyElement::Update()
{
    if (!component_) {
        return;
    }
    RefPtr<TabContentComponent> tabContent = AceType::DynamicCast<TabContentComponent>(component_);
    if (!tabContent) {
        LOGE("Get tabContent failed");
        return;
    }
    contents_ = tabContent->GetChildren();
    auto controller = tabContent->GetController();
    if (controller && (controller_ != controller)) {
        // Get index from old controller before replace.
        if (controller_) {
            if (!controller->IsIndexDefined()) {
                controller->SetIndexWithoutChangeContent(controller_->GetIndex());
            }
            controller->SetTotalCount(controller_->GetTotalCount());
        }
        controller_ = controller;
    }
    if (!controller_) {
        LOGE("Get controller failed");
        return;
    }
    controller_->SetContentElement(AceType::Claim(this));
    RenderElement::Update();

    SetElementId(component_->GetElementId());
}

RefPtr<FocusNode> TabContentProxyElement::GetChildFocusNode(const RefPtr<Element>& node)
{
    auto focusNode = AceType::DynamicCast<FocusNode>(node);
    if (focusNode) {
        return focusNode;
    }
    for (const auto& child : node->GetChildren()) {
        auto resNode = GetChildFocusNode(child);
        if (resNode) {
            return resNode;
        }
    }
    return nullptr;
}

void TabContentProxyElement::PerformBuild()
{
    if (component_) {
        auto tabsContentComponent = AceType::DynamicCast<TabContentComponent>(component_);
        if (!tabsContentComponent) {
            return;
        }
        ElementProxyHost::UpdateChildren(tabsContentComponent->GetChildren());
    }
    auto tabContent = AceType::DynamicCast<RenderTabContent>(renderNode_);
    if (!tabContent || !controller_) {
        LOGW("tabContent or controller is null.");
        return;
    }
    auto totalCount = static_cast<int32_t>(TotalCount());
    if (newIndex_ < 0 && newBarIndex_ < 0) {
        // verify controller index first build and flush index for render.
        auto maxIndex = totalCount - 1;
        if (controller_->GetIndex() >= totalCount) {
            controller_->SetIndexWithoutChangeContent(maxIndex < 0 ? 0 : maxIndex);
        }
        if (controller_->GetInitialIndex() >= totalCount) {
            controller_->SetInitialIndex(maxIndex < 0 ? 0 : maxIndex);
        }
        if (controller_->GetPendingIndex() >= totalCount) {
            controller_->SetPendingIndex(maxIndex < 0 ? 0 : maxIndex);
        }
        controller_->SetTotalCount(totalCount < 1 ? 0 : totalCount);
        tabContent->FlushIndex();
    }
    int32_t target = newIndex_ >= 0 ? newIndex_ : controller_->GetIndex();
    auto element = GetElementByIndex(target);
    if (!element) {
        LOGE("GetElementByIndex failed index=[%{public}d]", target);
        return;
    }
    auto renderNode = element->GetRenderNode();
    if (!renderNode) {
        LOGE("GetRenderNode failed");
        return;
    }
    tabContent->AddChildContent(target, renderNode);
    focusIndexMap_.emplace(target);
    focusChildMap_[target] = GetChildFocusNode(element);
    renderNode_->MarkNeedLayout();

    // process for new content requested by drag
    if (target == newIndex_) {
        tabContent->UpdateDragPosition(newIndex_);
        newIndex_ = -1;
    }
    // process for new content requested by tab bar
    if (target == newBarIndex_) {
        // That actually brings tab into view with animation
        tabContent->ChangeScroll(newBarIndex_, fromController_);
        UpdateLastFocusNode();
        newBarIndex_ = -1;
    }
    lastIndex_ = target;
    fromController_ = false;
}

// In ChangeByBar function the controller has already set index.
void TabContentProxyElement::ChangeByBar(int32_t index, bool isFromController)
{
    newBarIndex_ = index;
    fromController_ = isFromController;
    PerformBuild();
}

void TabContentProxyElement::PrepareContent(int32_t index)
{
    newIndex_ = index;
    PerformBuild();
}

RefPtr<Element> TabContentProxyElement::OnUpdateElement(
    const RefPtr<Element>& element, const RefPtr<Component>& component)
{
    bool usePartialUpdate  = Container::IsCurrentUsePartialUpdate();

    if (element && !component) {
        auto tabContent = AceType::DynamicCast<RenderTabContent>(renderNode_);
        if (!tabContent) {
            LOGE("tabContent is null.");
        } else {
            auto renderNode = element->GetRenderNode();
            if (!renderNode) {
                LOGW("delete render child is null.");
            } else {
                if (!usePartialUpdate) {
                    tabContent->RemoveChildContent(renderNode);
                } else {
                    tabContent->RemoveChildContentUpdateMap(renderNode);
                }
            }
        }
    }
    return UpdateChild(element, component);
}

RefPtr<Component> TabContentProxyElement::OnMakeEmptyComponent()
{
    LOGI("tab content does not support lazyForEach yet");
    return nullptr;
}

void TabContentProxyElement::OnDataSourceUpdated(size_t startIndex)
{
    LOGI("tab content does not support lazyForEach yet");
    ElementProxyHost::OnDataSourceUpdated(startIndex);
}

void TabContentProxyElement::UpdateIndex()
{
    if (!Container::IsCurrentUsePartialUpdate()) {
        return;
    }

    // We arrive here with new set of children (some can be dropped or added),
    // and focus index for TabBar already adjusted to point to correct render node.
    // Focused render node might move to new position after call to
    // ElementProxyHost::UpdateIndex();
    // So we have to move focus to new index (by same render node will be focused)

    auto renderNode = TabsHelper::GetTabBarFocusedElement(AceType::Claim(this));
    ElementProxyHost::UpdateIndex();
    auto idx2 = TabsHelper::GetTabBarElementIndex(AceType::Claim(this), renderNode);

    // idx2 can already be corrected value, so update focus in any case
    idx2 = idx2 < 0 ? 0 : idx2;
    TabsHelper::SetIndex(Referenced::Claim<Element>(this), idx2);
}

} // namespace OHOS::Ace::V2