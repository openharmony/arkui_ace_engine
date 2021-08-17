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

#include "core/components/grid_layout/grid_layout_element.h"

#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/components/grid_layout/grid_layout_component.h"
#include "core/components/grid_layout/grid_layout_item_component.h"
#include "core/components/grid_layout/render_grid_layout.h"
#include "core/components/grid_layout/render_grid_scroll_layout.h"
#include "core/components/proxy/render_item_proxy.h"
#include "core/pipeline/base/composed_element.h"

namespace OHOS::Ace {

void GridItemDataChangeListener::OnDataReloaded()
{
    auto grid = element_.Upgrade();
    if (grid) {
        grid->OnReload();
    }
}

void GridItemDataChangeListener::OnDataAdded(size_t index)
{
    auto grid = element_.Upgrade();
    if (grid) {
        grid->OnItemAdded(static_cast<int32_t>(index));
    }
}

void GridItemDataChangeListener::OnDataDeleted(size_t index)
{
    auto grid = element_.Upgrade();
    if (grid) {
        grid->OnItemDeleted(static_cast<int32_t>(index));
    }
}

void GridItemDataChangeListener::OnDataChanged(size_t index)
{
    auto grid = element_.Upgrade();
    if (grid) {
        grid->OnItemChanged(static_cast<int32_t>(index));
    }
}

void GridItemDataChangeListener::OnDataMoved(size_t from, size_t to)
{
    auto grid = element_.Upgrade();
    if (grid) {
        grid->OnItemMoved(static_cast<int32_t>(from), static_cast<int32_t>(to));
    }
}

RefPtr<RenderNode> GridLayoutElement::CreateRenderNode()
{
    return ComponentGroupElement::CreateRenderNode();
}

void GridLayoutElement::Update()
{
    RenderElement::Update();

    isUseLazyForEach_ = false;
    lazyForEachComponent_ = nullptr;
    lazyChildItems_.clear();
    auto gridLayoutComponent = AceType::DynamicCast<GridLayoutComponent>(component_);
    if (!gridLayoutComponent) {
        return;
    }
    auto lazyForEach = gridLayoutComponent->GetLazyForEachComponent();
    if (!lazyForEach) {
        return;
    }
    if (!listener) {
        listener = AceType::MakeRefPtr<GridItemDataChangeListener>(AceType::WeakClaim(this));
    }
    lazyForEach->RegiterDataChangeListener(listener);

    RefPtr<RenderGridScrollLayout> grid = AceType::DynamicCast<RenderGridScrollLayout>(renderNode_);
    if (!grid) {
        return;
    }

    isUseLazyForEach_ = true;
    lazyForEachComponent_ = lazyForEach;
    grid->ClearItems();
    grid->ClearLayout();
    grid->SetBuildChildByIndex([weak = WeakClaim(this)](int32_t index) {
        auto element = weak.Upgrade();
        if (!element) {
            return false;
        }
        return element->BuildChildByIndex(index);
    });

    grid->SetDeleteChildByIndex([weak = WeakClaim(this)](int32_t index) {
        auto element = weak.Upgrade();
        if (!element) {
            return;
        }
        element->DeleteChildByIndex(index);
    });
}

bool GridLayoutElement::BuildChildByIndex(int32_t index)
{
    if (index < 0) {
        return false;
    }

    if (static_cast<size_t>(index) >= lazyForEachComponent_->TotalCount()) {
        return false;
    }
    auto child = lazyForEachComponent_->GetChildByIndex(static_cast<size_t>(index));
    auto item = lazyChildItems_.find(index);
    if (item == lazyChildItems_.end()) {
        auto element = UpdateChild(nullptr, child);
        RefPtr<RenderGridScrollLayout> grid = AceType::DynamicCast<RenderGridScrollLayout>(renderNode_);
        if (!grid) {
            return false;
        }
        grid->AddChildByIndex(index, element->GetRenderNode());
        lazyChildItems_[index] = element;
    } else {
        UpdateChild(item->second, child);
    }
    return true;
}

void GridLayoutElement::DeleteChildByIndex(int32_t index)
{
    auto item = lazyChildItems_.find(index);
    if (item == lazyChildItems_.end()) {
        return;
    }
    UpdateChild(item->second, nullptr);
    lazyChildItems_.erase(item);
}

void GridLayoutElement::Prepare(const WeakPtr<Element>& parent)
{
    ComponentGroupElement::Prepare(parent);
}

bool GridLayoutElement::RequestNextFocus(bool vertical, bool reverse, const Rect& rect)
{
    RefPtr<RenderGridLayout> grid = AceType::DynamicCast<RenderGridLayout>(renderNode_);
    if (!grid) {
        LOGE("Render grid is null.");
        return false;
    }
    LOGI("RequestNextFocus vertical:%{public}d reverse:%{public}d.", vertical, reverse);
    bool ret = false;
    while (!ret) {
        int32_t focusIndex = grid->RequestNextFocus(vertical, reverse);
        int32_t size = GetChildrenList().size();
        if (focusIndex < 0 || focusIndex >= size) {
            return false;
        }
        auto iter = GetChildrenList().begin();
        std::advance(iter, focusIndex);
        auto focusNode = *iter;
        if (!focusNode) {
            LOGE("Target focus node is null.");
            return false;
        }
        // If current Node can not obtain focus, move to next.
        ret = focusNode->RequestFocusImmediately();
    }
    return ret;
}

void GridLayoutElement::ApplyRenderChild(const RefPtr<RenderElement>& renderChild)
{
    if (!renderChild) {
        LOGE("Element child is null");
        return;
    }

    if (!renderNode_) {
        LOGE("RenderElement don't have a render node");
        return;
    }

    if (isUseLazyForEach_) {
        return;
    }

    auto proxy = RenderItemProxy::Create();
    proxy->AddChild(renderChild->GetRenderNode());
    proxy->Attach(context_);
    renderNode_->AddChild(proxy);
}

void GridLayoutElement::OnReload()
{
    LOGD("GridLayoutElement::OnReload");
    RefPtr<RenderGridScrollLayout> render = AceType::DynamicCast<RenderGridScrollLayout>(renderNode_);
    if (!render) {
        return;
    }
    for (const auto& item : lazyChildItems_) {
        Element::RemoveChild(item.second);
        render->RemoveChildByIndex(item.first);
    }
    lazyChildItems_.clear();
    render->OnReload();
}
void GridLayoutElement::OnItemAdded(int32_t index)
{
    LOGD("GridLayoutElement::OnItemAdded");
    decltype(lazyChildItems_) items(std::move(lazyChildItems_));
    for (const auto& item : items) {
        if (item.first >= index) {
            lazyChildItems_.emplace(std::make_pair(item.first + 1, item.second));
        } else {
            lazyChildItems_.emplace(std::make_pair(item.first, item.second));
        }
    }
    RefPtr<RenderGridScrollLayout> render = AceType::DynamicCast<RenderGridScrollLayout>(renderNode_);
    if (!render) {
        return;
    }
    render->OnItemAdded(index);
}

void GridLayoutElement::OnItemDeleted(int32_t index)
{
    LOGD("GridLayoutElement::OnItemDeleted");
    decltype(lazyChildItems_) items(std::move(lazyChildItems_));
    for (const auto& item : items) {
        if (item.first == index) {
            UpdateChild(item.second, nullptr);
        } else if (item.first > index) {
            lazyChildItems_.emplace(std::make_pair(item.first - 1, item.second));
        } else {
            lazyChildItems_.emplace(std::make_pair(item.first, item.second));
        }
    }
    RefPtr<RenderGridScrollLayout> render = AceType::DynamicCast<RenderGridScrollLayout>(renderNode_);
    if (!render) {
        return;
    }
    render->OnItemDeleted(index);
}

void GridLayoutElement::OnItemChanged(int32_t index)
{
    LOGD("GridLayoutElement::OnItemChanged");
    RefPtr<RenderGridScrollLayout> render = AceType::DynamicCast<RenderGridScrollLayout>(renderNode_);
    if (!render) {
        return;
    }
    render->OnItemChanged((index));
}
void GridLayoutElement::OnItemMoved(int32_t from, int32_t to)
{
    LOGD("GridLayoutElement::OnItemMoved");
    DeleteChildByIndex(from);
    DeleteChildByIndex(to);
    RefPtr<RenderGridScrollLayout> render = AceType::DynamicCast<RenderGridScrollLayout>(renderNode_);
    if (!render) {
        return;
    }
    render->OnItemMoved(from, to);
}

} // namespace OHOS::Ace
