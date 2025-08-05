/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components_v2/common/element_proxy.h"

#include "base/log/dump_log.h"
#include "core/components/grid_layout/grid_layout_item_component.h"
#include "core/components/ifelse/if_else_component.h"
#include "core/components_v2/foreach/lazy_foreach_component.h"
#include "core/components_v2/inspector/inspector_composed_component.h"
#include "core/components_v2/list/list_item_component.h"
#include "core/components_v2/tabs/tabs_helper.h"
#include "frameworks/core//components_part_upd/foreach/foreach_component.h"
#include "frameworks/core//components_part_upd/foreach/foreach_element.h"

namespace OHOS::Ace::V2 {
namespace {

const std::string PREFIX_STEP = "  ";
class RenderElementProxy : public ElementProxy {
public:
    explicit RenderElementProxy(const WeakPtr<ElementProxyHost>& host, bool forceRender = false)
        : ElementProxy(host), forceRender_(forceRender)
    {}
    ~RenderElementProxy() override
    {
        RemoveSelfFromElementRegistry();
        ReleaseElement(Container::IsCurrentUsePartialUpdate());
    }

    void Update(const RefPtr<Component>& component, size_t startIndex) override
    {
        if (Container::IsCurrentUsePartialUpdate()) {
            UpdateForPartialUpdate(component, startIndex);
            return;
        }
        auto composedComponent = AceType::DynamicCast<ComposedComponent>(component);
        auto inspectorComposedComponent = AceType::DynamicCast<InspectorComposedComponent>(component);
        SetComposedId(composedComponent ? composedComponent->GetId() : "");

        component_ = component;
        while (composedComponent && !composedComponent->HasElementFunction() && !inspectorComposedComponent) {
            component_ = composedComponent->GetChild();
            composedComponent = AceType::DynamicCast<ComposedComponent>(component_);
        }

        auto host = host_.Upgrade();
        if (!host) {
            return;
        }

        if (!component_ && forceRender_) {
            component_ = host->OnMakeEmptyComponent();
        }

        startIndex_ = startIndex;
        count_ = component_ ? 1 : 0;

        if (element_) {
            element_ = host->OnUpdateElement(element_, component_);
        }
    }

    void UpdateForPartialUpdate(const RefPtr<Component>& component, size_t startIndex)
    {
        auto composedComponent = AceType::DynamicCast<ComposedComponent>(component);
        auto inspectorComposedComponent = AceType::DynamicCast<InspectorComposedComponent>(component);
        SetComposedId(composedComponent ? composedComponent->GetId() : "");

        component_ = component;
        while (composedComponent && !composedComponent->HasElementFunction() && !inspectorComposedComponent) {
            component_ = composedComponent->GetChild();
            composedComponent = AceType::DynamicCast<ComposedComponent>(component_);
        }

        auto host = host_.Upgrade();
        if (!host) {
            return;
        }

        if (!component_ && forceRender_) {
            component_ = host->OnMakeEmptyComponent();
        }

        startIndex_ = startIndex;
        count_ = component_ ? 1 : 0;

        if (GetElementId() == ElementRegister::UndefinedElementId) {
            // first render case, add the ElementRegistry
            ACE_DCHECK(element_ == nullptr);

            SetElementId(component_->GetElementId());
            AddSelfToElementRegistry();
            realElmtId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }

        if (element_) {
            element_ = CreateElement();
        }
    }

    void LocalizedUpdate(
        const RefPtr<Component>& inwardWrappingComponent, const RefPtr<Component>& newListItemComponent) override
    {
        ACE_DCHECK(
            (component_ != nullptr) && (GetElementId() != ElementRegister::UndefinedElementId) && "Is re-render");

        if (element_) {
            // the Component (correctly) has elmtId of this ProxyElement
            // We are updating the 'real' Lst/GridElement, need to adjust the elmtId
            // in the Component.
            newListItemComponent->SetElementId(realElmtId_);

            // List/Grid Item do not use normal wrapping
            auto updateElement = element_;
            auto updateComponent = newListItemComponent;

            for (;;) {
                updateElement->SetNewComponent(updateComponent);
                updateElement->LocalizedUpdate(); // virtual
                updateElement->SetNewComponent(nullptr);

                updateElement = updateElement->GetFirstChild();
                auto singleChild = AceType::DynamicCast<SingleChild>(updateComponent);
                if ((updateElement == nullptr) || (singleChild == nullptr) || (singleChild->GetChild() == nullptr)) {
                    break;
                }
                updateComponent = singleChild->GetChild();
            }
        }
    }

    RefPtr<Element> CreateElement()
    {
        auto host = host_.Upgrade();
        if (!host) {
            return nullptr;
        }

        auto tabContentItemComponent = TabsHelper::TraverseComponentTo<TabContentItemComponent>(component_);
        if (tabContentItemComponent) {
            tabContentItemComponent->SetElementId(realElmtId_);
        } else {
            component_->SetElementId(realElmtId_);
        }
        auto element = host->OnUpdateElement(element_, component_);
        if (tabContentItemComponent) {
            tabContentItemComponent->SetElementId(GetElementId());
        } else {
            component_->SetElementId(GetElementId());
        }
        return element;
    }

    void UpdateIndex(size_t startIndex) override
    {
        startIndex_ = startIndex;
    }

    RefPtr<Component> GetComponentByIndex(size_t index) override
    {
        ACE_DCHECK(index == startIndex_);
        return component_;
    }

    RefPtr<Element> GetElementByIndex(size_t index) override
    {
        ACE_DCHECK(index == startIndex_);
        if (element_) {
            return element_;
        }
        if (!component_) {
            return nullptr;
        }
        auto host = host_.Upgrade();
        if (!host) {
            return nullptr;
        }
        if (Container::IsCurrentUsePartialUpdate()) {
            element_ = CreateElement();
            return element_;
        }
        element_ = host->OnUpdateElement(element_, component_);
        return element_;
    }

    void RefreshActiveComposeIds() override
    {
        auto host = host_.Upgrade();
        if (!host) {
            return;
        }
        host->AddActiveComposeId(composedId_);
    };

    void ReleaseElement(bool partialUpdates)
    {
        if (!element_) {
            return;
        }
        auto host = host_.Upgrade();
        if (!host) {
            return;
        }
        SetComposedId("");
        if (partialUpdates) {
            element_->UnregisterForPartialUpdates();
        }
        element_ = host->OnUpdateElement(element_, nullptr);
    }

    void ReleaseElementByIndex(size_t index) override
    {
        ACE_DCHECK(index == startIndex_);
        ReleaseElement(true);
    }

    void ReleaseElementById(const ComposeId& id) override {}

    void Dump(const std::string& prefix) const override
    {
        if (!DumpLog::GetInstance().GetDumpFile()) {
            return;
        }
        ElementProxy::Dump(prefix);
        if (element_) {
            DumpLog::GetInstance().AddDesc(prefix + std::string("[RenderElementProxy] element: ") +
                                           AceType::TypeName(AceType::RawPtr(element_)) +
                                           ", retakeId: " + std::to_string(element_->GetRetakeId()));
        } else {
            DumpLog::GetInstance().AddDesc(prefix + std::string("[RenderElementProxy] Null element."));
        }
    }

protected:
    // the proxy has elmtId, the real Element element_
    // needs to be always given a different but always same elmtId
    int32_t realElmtId_ = ElementRegister::UndefinedElementId;

    void SetComposedId(const ComposeId& composedId)
    {
        auto host = host_.Upgrade();
        if (!host) {
            return;
        }
        if (composedId_ != composedId) {
            // Add old id to host and remove it later
            host->AddComposeId(composedId_);
        }
        host->AddComposeId(composedId);
        composedId_ = composedId;
    }
    bool forceRender_ = false;
    RefPtr<Component> component_;
    RefPtr<Element> element_;
};

class TabContentItemElementProxy : public RenderElementProxy {
public:
    explicit TabContentItemElementProxy(const WeakPtr<ElementProxyHost>& host, bool forceRender = false)
        : RenderElementProxy(host, forceRender) {}

    ~TabContentItemElementProxy() override
    {
        auto tabContentItemComponent = TabsHelper::TraverseComponentTo<TabContentItemComponent>(component_);
        if (tabContentItemComponent) {
            TabsHelper::RemoveTabBarItemById(tabContentItemComponent->GetBarElementId());

            if (!host_.Upgrade()) {
                LOGE("Host_ is nullptr");
                return;
            }
            auto element = AceType::DynamicCast<TabContentProxyElement>(host_.Upgrade());
            if (!element) {
                LOGE("DTOR host is NOT TabContentProxyElement is nullptr");
                return;
            }
            TabsHelper::DecTabContentRenderCount(AceType::DynamicCast<TabContentProxyElement>(host_.Upgrade()));
        }
    }

    void Update(const RefPtr<Component>& component, size_t startIndex) override
    {
        if (GetElementId() == ElementRegister::UndefinedElementId) {
            // first render case, add the ElementRegistry
            ACE_DCHECK(element_ == nullptr);

            auto tabContentItemComponent = TabsHelper::TraverseComponentTo<TabContentItemComponent>(component);
            if (tabContentItemComponent) {
                SetElementId(tabContentItemComponent->GetElementId());
            }
            AddSelfToElementRegistry();
            realElmtId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }

        // Add Tab Bar Item
        auto tabContentProxyElement = AceType::DynamicCast<TabContentProxyElement>(host_.Upgrade());
        if (tabContentProxyElement && !element_) {
            auto tabContentItemComponent = TabsHelper::TraverseComponentTo<TabContentItemComponent>(component);
            TabsHelper::AddTabBarElement(tabContentProxyElement, tabContentItemComponent);
            TabsHelper::IncTabContentRenderCount(tabContentProxyElement);
        }

        RenderElementProxy::Update(component, startIndex);
    }

    void LocalizedUpdate(
        const RefPtr<Component>& inwardWrappingComponent, const RefPtr<Component>& newTabContentItemComponent) override
    {
        ACE_DCHECK(
            (component_ != nullptr) && (GetElementId() != ElementRegister::UndefinedElementId) && "Is re-render");

        // Update TabBar element
        auto tabContentProxyElement = AceType::DynamicCast<TabContentProxyElement>(host_.Upgrade());
        if (tabContentProxyElement) {
            auto tabContentItemComponent = TabsHelper::TraverseComponentTo<TabContentItemComponent>(
                inwardWrappingComponent);
            auto oldComponent = TabsHelper::TraverseComponentTo<TabContentItemComponent>(component_);
            tabContentItemComponent->SetBarElementId(oldComponent->GetBarElementId());
            TabsHelper::UpdateTabBarElement(tabContentProxyElement, element_, inwardWrappingComponent);
        }

        RenderElementProxy::LocalizedUpdate(inwardWrappingComponent, newTabContentItemComponent);
    }

    void UpdateIndex(size_t startIndex) override
    {
        startIndex_ = startIndex;
        TabsHelper::SetTabBarElementIndex(element_,
            TabsHelper::TraverseComponentTo<TabContentItemComponent>(component_), startIndex);
        RenderElementProxy::UpdateIndex(startIndex);
    }
};

class ItemElementProxy : public RenderElementProxy {
public:
    explicit ItemElementProxy(const WeakPtr<ElementProxyHost>& host)
        : RenderElementProxy(host), deepRenderignState_(DeepRenderingState::shallowTree)
    {}
    ~ItemElementProxy() override = default;

    RefPtr<Element> GetElementByIndex(size_t index) override
    {
        if (element_) {
            return element_;
        }
        if (!component_) {
            return nullptr;
        }

        if (deepRenderignState_ == DeepRenderingState::shallowTree) {
            // repalce ListItemcomponent with new one from deep render
            GetDeepRenderComponent();
        }
        element_ = CreateElement();
        return element_;
    }

    virtual void GetDeepRenderComponent() = 0;

protected:
    enum class DeepRenderingState { shallowTree, deepTree };

    DeepRenderingState deepRenderignState_ = DeepRenderingState::shallowTree;
};

class ListItemElementProxy : public ItemElementProxy {
public:
    explicit ListItemElementProxy(const WeakPtr<ElementProxyHost>& host) : ItemElementProxy(host) {}
    ~ListItemElementProxy() override
    {
        if (element_) {
            element_->UnregisterForPartialUpdates();
        }
    }

    void Update(const RefPtr<Component>& component, size_t startIndex) override
    {
        auto composedComponent = AceType::DynamicCast<ComposedComponent>(component);
        auto inspectorComposedComponent = AceType::DynamicCast<InspectorComposedComponent>(component);
        SetComposedId(composedComponent ? composedComponent->GetId() : "");

        component_ = component;
        while (composedComponent && !composedComponent->HasElementFunction() && !inspectorComposedComponent) {
            component_ = composedComponent->GetChild();
            composedComponent = AceType::DynamicCast<ComposedComponent>(component_);
        }

        auto host = host_.Upgrade();
        if (!host) {
            LOGE("no host");
            return;
        }
        startIndex_ = startIndex;
        count_ = component_ ? 1 : 0;

        if (GetElementId() == ElementRegister::UndefinedElementId) {
            // first render case, add the ElementRegistry
            ACE_DCHECK(element_ == nullptr);

            SetElementId(component_->GetElementId());
            AddSelfToElementRegistry();
            realElmtId_ = ElementRegister::GetInstance()->MakeUniqueId();

            auto listItemComponent = AceType::DynamicCast<V2::ListItemComponent>(component_);
            if (listItemComponent->GetIsLazyCreating()) {
                deepRenderignState_ = DeepRenderingState::shallowTree;
                // continue later when GetElementByIndex is called
                return;
            } else {
                deepRenderignState_ = DeepRenderingState::deepTree;
                element_ = CreateElement();
                return;
            }
        }

        if (element_) {
            element_ = CreateElement();
        }
    }

    void GetDeepRenderComponent() override
    {
        auto listItemComponent = AceType::DynamicCast<V2::ListItemComponent>(component_);
        auto newComponent = listItemComponent->ExecDeepRender();

        ACE_DCHECK(newComponent != nullptr);
        ACE_DCHECK(newComponent->GetElementId() == component_->GetElementId());
        deepRenderignState_ = DeepRenderingState::deepTree;
        component_ = newComponent;

        auto composedComponent = AceType::DynamicCast<ComposedComponent>(newComponent);
        while (composedComponent && !composedComponent->HasElementFunction()) {
            LOGW("ComposedComponent case, using child as component_");
            component_ = composedComponent->GetChild();
            composedComponent = AceType::DynamicCast<ComposedComponent>(component_);
        }

        ACE_DCHECK(GetElementId() == component_->GetElementId());
    }

    void ReleaseElementByIndex(size_t index) override
    {
        deepRenderignState_ = DeepRenderingState::shallowTree;

        RenderElementProxy::ReleaseElementByIndex(index);

        // release deeprender Component tree,
        // repalce component_ with a dummy
        auto listItem = AceType::DynamicCast<V2::ListItemComponent>(component_);
        auto placeholder = AceType::MakeRefPtr<V2::ListItemComponent>();
        listItem->MoveDeepRenderFunc(placeholder);
        placeholder->SetElementId(listItem->GetElementId());
        component_ = std::move(placeholder);
    }
};

class GridItemElementProxy : public ItemElementProxy {
public:
    explicit GridItemElementProxy(const WeakPtr<ElementProxyHost>& host) : ItemElementProxy(host) {}
    ~GridItemElementProxy() override
    {
        if (element_) {
            element_->UnregisterForPartialUpdates();
        }
    }

    void Update(const RefPtr<Component>& component, size_t startIndex) override
    {
        auto composedComponent = AceType::DynamicCast<ComposedComponent>(component);
        auto inspectorComposedComponent = AceType::DynamicCast<InspectorComposedComponent>(component);
        SetComposedId(composedComponent ? composedComponent->GetId() : "");

        component_ = component;
        while (composedComponent && !composedComponent->HasElementFunction() && !inspectorComposedComponent) {
            component_ = composedComponent->GetChild();
            composedComponent = AceType::DynamicCast<ComposedComponent>(component_);
        }

        auto host = host_.Upgrade();
        if (!host) {
            LOGE("no host");
            return;
        }
        startIndex_ = startIndex;
        count_ = component_ ? 1 : 0;

        if (GetElementId() == ElementRegister::UndefinedElementId) {
            // first render case, add the ElementRegistry
            ACE_DCHECK(element_ == nullptr);

            SetElementId(component_->GetElementId());
            AddSelfToElementRegistry();
            realElmtId_ = ElementRegister::GetInstance()->MakeUniqueId();
            auto gridItemComponent = AceType::DynamicCast<GridLayoutItemComponent>(component_);
            if (gridItemComponent->GetIsLazyCreating()) {
                deepRenderignState_ = DeepRenderingState::shallowTree;
                // continue later when GetElementByIndex is called
                return;
            } else {
                deepRenderignState_ = DeepRenderingState::deepTree;
                element_ = CreateElement();
                return;
            }
        }

        if (element_) {
            element_ = CreateElement();
        }
    }

    void GetDeepRenderComponent() override
    {
        auto gridItemComponent = AceType::DynamicCast<GridLayoutItemComponent>(component_);
        auto newComponent = gridItemComponent->ExecDeepRender();

        ACE_DCHECK(newComponent != nullptr);
        ACE_DCHECK(newComponent->GetElementId() == component_->GetElementId());

        deepRenderignState_ = DeepRenderingState::deepTree;
        component_ = newComponent;

        auto composedComponent = AceType::DynamicCast<ComposedComponent>(newComponent);
        while (composedComponent && !composedComponent->HasElementFunction()) {
            LOGW("ComposedComponent case, using child as component_");
            component_ = composedComponent->GetChild();
            composedComponent = AceType::DynamicCast<ComposedComponent>(component_);
        }

        ACE_DCHECK(GetElementId() == component_->GetElementId());
    }

    void ReleaseElementByIndex(size_t index) override
    {
        deepRenderignState_ = DeepRenderingState::shallowTree;

        RenderElementProxy::ReleaseElementByIndex(index);

        // release deeprender Component tree,
        // replace component_ with a dummy
        auto gridItem = AceType::DynamicCast<GridLayoutItemComponent>(component_);
        auto placeholder = AceType::MakeRefPtr<GridLayoutItemComponent>();
        gridItem->MoveDeepRenderFunc(placeholder);
        placeholder->SetElementId(gridItem->GetElementId());
        component_ = std::move(placeholder);
    }
};

class LazyForEachElementProxy : public virtual ElementProxy, public virtual DataChangeListener {
    DECLARE_ACE_TYPE(LazyForEachElementProxy, ElementProxy, DataChangeListener);
public:
    explicit LazyForEachElementProxy(const WeakPtr<ElementProxyHost>& host) : ElementProxy(host) {}
    ~LazyForEachElementProxy() override
    {
        for (auto&& item : children_) {
            auto viewId = item.second->GetId();
            if (lazyForEachComponent_) {
                lazyForEachComponent_->ReleaseChildGroupByComposedId(viewId);
            }
        }
        children_.clear();
    }

    void Update(const RefPtr<Component>& component, size_t startIndex) override
    {
        auto lazyForEachComponent = AceType::DynamicCast<LazyForEachComponent>(component);
        ACE_DCHECK(lazyForEachComponent);

        if (lazyForEachComponent_) {
            if (count_ != lazyForEachComponent->TotalCount()) {
                LOGW("Count of items MUST be the same while updating");
                count_ = lazyForEachComponent->TotalCount();
            }
            lazyForEachComponent_->UnregisterDataChangeListener(this);
        } else {
            count_ = lazyForEachComponent->TotalCount();
        }

        startIndex_ = startIndex;
        composedId_ = lazyForEachComponent->GetId();
        lazyForEachComponent->RegisterDataChangeListener(AceType::Claim(this));
        lazyForEachComponent_ = lazyForEachComponent;

        for (const auto& item : children_) {
            auto childComponent = lazyForEachComponent_->GetChildByIndex(item.first);
            item.second->Update(childComponent, startIndex_ + item.first);
        }
    }

    void LocalizedUpdate(
        const RefPtr<Component>& newComponent, const RefPtr<Component>& outmostWrappingComponent) override
    {
        Update(newComponent, startIndex_);
    }

    void UpdateIndex(size_t startIndex) override
    {
        if (startIndex_ == startIndex) {
            return;
        }
        startIndex_ = startIndex;

        for (const auto& item : children_) {
            item.second->UpdateIndex(startIndex_ + item.first);
        }
    }

    RefPtr<Component> GetComponentByIndex(size_t index) override
    {
        auto it = children_.find(index - startIndex_);
        if (it != children_.end()) {
            return it->second->GetComponentByIndex(index);
        }

        auto component = lazyForEachComponent_->GetChildByIndex(index - startIndex_);
        ACE_DCHECK(AceType::InstanceOf<ComposedComponent>(component));
        auto child = AceType::MakeRefPtr<RenderElementProxy>(host_.Upgrade(), true);
        child->Update(component, index);
        return child->GetComponentByIndex(index);
    }

    RefPtr<Element> GetElementByIndex(size_t index) override
    {
        auto it = children_.find(index - startIndex_);
        if (it != children_.end()) {
            return it->second->GetElementByIndex(index);
        }

        auto component = lazyForEachComponent_->GetChildByIndex(index - startIndex_);
        auto child = ElementProxy::Create(host_, component);
        children_.emplace(index - startIndex_, child);
        child->Update(component, index);
        return child->GetElementByIndex(index);
    }

    void ReleaseElementByIndex(size_t index) override
    {
        auto it = children_.find(index - startIndex_);
        if (it != children_.end()) {
            auto viewId = it->second->GetId();
            if (lazyForEachComponent_) {
                lazyForEachComponent_->ReleaseChildGroupByComposedId(viewId);
            }
            children_.erase(it);
        }
    }

    void ReleaseElementById(const ComposeId& composeId) override
    {
        if (lazyForEachComponent_) {
            lazyForEachComponent_->ReleaseChildGroupByComposedId(composeId);
        }
    }

    void RefreshActiveComposeIds() override
    {
        auto host = host_.Upgrade();
        if (!host) {
            return;
        }
        for (auto const& child : children_) {
            child.second->RefreshActiveComposeIds();
        }
    }

    void OnDataReloaded() override
    {
        LOGI("OnDataReloaded()");
        ACE_SCOPED_TRACE("OnDataReloaded");

        if (!lazyForEachComponent_) {
            LOGE("lazyForEachComponent_ is nullptr");
            return;
        }
        LazyForEachCache cache(lazyForEachComponent_);
        size_t oldCount = count_;
        count_ = cache.TotalCount();
        auto host = host_.Upgrade();
        if (count_ == 0) {
            children_.clear();
            if (host) {
                if (oldCount != count_) {
                    host->UpdateIndex();
                }
                host->OnDataSourceUpdated(startIndex_);
            }
            return;
        }

        std::list<std::pair<size_t, RefPtr<ElementProxy>>> items(children_.begin(), children_.end());
        children_.clear();
        std::list<RefPtr<ElementProxy>> deletedItems;
        auto checkRange = items.size() / 3;
        for (const auto& [index, child] : items) {
            size_t newIdx = cache[child->GetId()];
            if (newIdx != INVALID_INDEX) {
                children_.emplace(newIdx, child);
                child->Update(cache[newIdx], startIndex_ + newIdx);
                continue;
            }

            size_t idx = std::min(index, count_ - 1);
            size_t range = std::max(idx, count_ - 1 - idx);
            range = std::min(range, checkRange);
            bool recycle = false;
            for (size_t i = 0; i <= range; ++i) {
                if (idx >= i && !cache.IsInCache(idx - i)) {
                    auto component = cache[idx - i];
                    if (component->GetId() == child->GetId()) {
                        children_.emplace(idx - i, child);
                        child->Update(cache[idx - i], startIndex_ + idx - i);
                        recycle = true;
                        break;
                    }
                }

                if (idx + i < count_ && !cache.IsInCache(idx + i)) {
                    auto component = cache[idx + i];
                    if (component->GetId() == child->GetId()) {
                        children_.emplace(idx + i, child);
                        child->Update(cache[idx + i], startIndex_ + idx + i);
                        recycle = true;
                        break;
                    }
                }
            }
            if (!recycle) {
                deletedItems.emplace_back(child);
            }
        }

        if (lazyForEachComponent_) {
            for (auto&& item : deletedItems) {
                lazyForEachComponent_->ReleaseChildGroupByComposedId(item->GetId());
            }
        }

        if (host) {
            if (oldCount != count_) {
                host->UpdateIndex();
            }
            host->OnDataSourceUpdated(startIndex_);
        }
    }

    void OnDataAdded(size_t index) override
    {
        LOGI("OnDataAdded(%{public}zu)", index);

        if (index > count_) {
            LOGW("Invalid index");
            return;
        }

        if (index < count_) {
            std::list<std::pair<size_t, RefPtr<ElementProxy>>> items;
            auto it = children_.begin();
            while (it != children_.end()) {
                if (it->first < index) {
                    ++it;
                    continue;
                }
                items.emplace_back(it->first + 1, it->second);
                it = children_.erase(it);
            }

            for (const auto& item : items) {
                children_.emplace(item.first, item.second);
                item.second->UpdateIndex(startIndex_ + item.first);
            }
        }

        count_++;

        auto host = host_.Upgrade();
        if (host) {
            host->UpdateIndex();
            host->OnDataSourceUpdated(startIndex_ + index);
        }
    }

    void OnDataBulkAdded(size_t index, size_t count) override {};

    void OnDataDeleted(size_t index) override
    {
        LOGI("OnDataDeleted(%{public}zu)", index);

        if (index >= count_) {
            LOGW("Invalid index");
            return;
        }

        std::list<std::pair<size_t, RefPtr<ElementProxy>>> items;
        RefPtr<ElementProxy> deleteItem;
        auto it = children_.begin();
        while (it != children_.end()) {
            if (it->first < index) {
                ++it;
                continue;
            }
            if (it->first == index) {
                deleteItem = it->second;
            }

            if (it->first > index) {
                items.emplace_back(it->first - 1, it->second);
            }
            it = children_.erase(it);
        }

        if (lazyForEachComponent_ && deleteItem) {
            lazyForEachComponent_->ReleaseChildGroupByComposedId(deleteItem->GetId());
        }

        for (const auto& item : items) {
            children_.emplace(item.first, item.second);
            item.second->UpdateIndex(startIndex_ + item.first);
        }

        count_--;

        auto host = host_.Upgrade();
        if (host) {
            host->UpdateIndex();
            host->OnDataSourceUpdated(startIndex_ + index);
        }
    }

    void OnDataBulkDeleted(size_t index, size_t count) override {};

    void OnDatasetChange(const std::list<V2::Operation>& DataOperations) override {};

    void OnDataChanged(size_t index) override
    {
        LOGI("OnDataChanged(%{public}zu)", index);

        auto it = children_.find(index);
        if (it == children_.end()) {
            return;
        }

        auto component = lazyForEachComponent_->GetChildByIndex(index);
        it->second->Update(component, startIndex_ + index);

        auto host = host_.Upgrade();
        if (host) {
            host->OnDataSourceUpdated(startIndex_ + index);
        }
    }

    void OnDataMoved(size_t from, size_t to) override
    {
        LOGI("OnDataMoved(from:%{public}zu, to:%{public}zu)", from, to);

        if (from == to || from >= count_ || to >= count_) {
            LOGW("Invalid index");
            return;
        }

        RefPtr<ElementProxy> childFrom;
        auto itFrom = children_.find(from);
        if (itFrom != children_.end()) {
            childFrom = itFrom->second;
            children_.erase(itFrom);
        }

        std::list<std::pair<size_t, RefPtr<ElementProxy>>> items;

        if (from < to) {
            for (size_t idx = from + 1; idx <= to; ++idx) {
                auto it = children_.find(idx);
                if (it == children_.end()) {
                    continue;
                }
                items.emplace_back(idx - 1, it->second);
                children_.erase(it);
            }
        } else {
            for (size_t idx = from - 1; idx >= to; --idx) {
                auto it = children_.find(idx);
                if (it != children_.end()) {
                    items.emplace_back(idx + 1, it->second);
                    children_.erase(it);
                }
                if (idx == 0) {
                    break;
                }
            }
        }

        for (const auto& item : items) {
            children_.emplace(item.first, item.second);
            item.second->UpdateIndex(startIndex_ + item.first);
        }

        if (childFrom) {
            children_.emplace(to, childFrom);
            childFrom->UpdateIndex(startIndex_ + to);
        }

        auto host = host_.Upgrade();
        if (host) {
            host->OnDataSourceUpdated(startIndex_ + std::min(from, to));
        }
    }

    void Dump(const std::string& prefix) const override
    {
        if (!DumpLog::GetInstance().GetDumpFile()) {
            return;
        }
        ElementProxy::Dump(prefix);
        DumpLog::GetInstance().AddDesc(
            prefix + std::string("[LazyForEachElementProxy] childSize: ").append(std::to_string(children_.size())));
    }

private:
    class LazyForEachCache final {
    public:
        explicit LazyForEachCache(const RefPtr<LazyForEachComponent>& component) : lazyForEachComponent_(component)
        {
            if (component) {
                count_ = component->TotalCount();
            } else {
                count_ = 0;
            }
        }
        ~LazyForEachCache() = default;

        RefPtr<ComposedComponent> operator[](size_t index)
        {
            if (index >= count_) {
                return nullptr;
            }

            auto it = componentCache_.find(index);
            if (it != componentCache_.end()) {
                return it->second;
            }

            auto component = AceType::DynamicCast<ComposedComponent>(lazyForEachComponent_->GetChildByIndex(index));
            ACE_DCHECK(component);
            idCache_.emplace(component->GetId(), index);
            componentCache_.emplace(index, component);
            return component;
        }

        size_t operator[](const ComposeId& id) const
        {
            auto it = idCache_.find(id);
            return it == idCache_.end() ? INVALID_INDEX : it->second;
        }

        bool IsInCache(size_t index) const
        {
            return componentCache_.find(index) != componentCache_.end();
        }

        size_t TotalCount() const
        {
            return count_;
        }

    private:
        RefPtr<LazyForEachComponent> lazyForEachComponent_;
        size_t count_ = 0;
        std::unordered_map<ComposeId, size_t> idCache_;
        std::unordered_map<size_t, RefPtr<ComposedComponent>> componentCache_;
    };

    RefPtr<LazyForEachComponent> lazyForEachComponent_;
    std::map<size_t, RefPtr<ElementProxy>> children_;
};

class LinearElementProxy : public ElementProxy {
    DECLARE_ACE_TYPE(LinearElementProxy, ElementProxy);

public:
    explicit LinearElementProxy(const WeakPtr<ElementProxyHost>& host) : ElementProxy(host) {}
    ~LinearElementProxy() override = default;

    void UpdateIndex(size_t startIndex) override
    {
        count_ = 0;
        startIndex_ = startIndex;
        for (const auto& child : children_) {
            child->UpdateIndex(startIndex_ + count_);
            count_ += child->RenderCount();
        }
    }

    RefPtr<Component> GetComponentByIndex(size_t index) override
    {
        for (const auto& child : children_) {
            if (child->IndexInRange(index)) {
                return child->GetComponentByIndex(index);
            }
        }
        return nullptr;
    }

    RefPtr<Element> GetElementByIndex(size_t index) override
    {
        for (const auto& child : children_) {
            if (child->IndexInRange(index)) {
                return child->GetElementByIndex(index);
            }
        }
        return nullptr;
    }

    void ReleaseElementByIndex(size_t index) override
    {
        for (const auto& child : children_) {
            if (child->IndexInRange(index)) {
                child->ReleaseElementByIndex(index);
                break;
            }
        }
    }

    void ReleaseElementById(const ComposeId& composeId) override
    {
        for (const auto& child : children_) {
            if (!child) {
                continue;
            }
            child->ReleaseElementById(composeId);
        }
    }

    void RefreshActiveComposeIds() override
    {
        for (const auto& child : children_) {
            if (!child) {
                continue;
            }
            child->RefreshActiveComposeIds();
        }
    }

    void Dump(const std::string& prefix) const override
    {
        if (!DumpLog::GetInstance().GetDumpFile()) {
            return;
        }
        ElementProxy::Dump(prefix);
        DumpLog::GetInstance().AddDesc(
            prefix + std::string("[LinearElementProxy] childSize: ").append(std::to_string(children_.size())));
        for (const auto& child : children_) {
            child->Dump(prefix + PREFIX_STEP);
        }
    }

protected:
    std::list<RefPtr<ElementProxy>> children_;
};

class ForEachElementProxy : public LinearElementProxy {
    DECLARE_ACE_TYPE(ForEachElementProxy, LinearElementProxy);

public:
    explicit ForEachElementProxy(const WeakPtr<ElementProxyHost>& host) : LinearElementProxy(host) {}
    ~ForEachElementProxy() override = default;

    void Update(const RefPtr<Component>& component, size_t startIndex) override
    {
        if (Container::IsCurrentUsePartialUpdate()) {
            UpdateForPartialUpdate(component, startIndex);
            return;
        }

        auto forEachComponent = AceType::DynamicCast<ForEachComponent>(component);
        ACE_DCHECK(forEachComponent);

        const auto& components = forEachComponent->GetChildren();

        count_ = 0;
        startIndex_ = startIndex;
        composedId_ = forEachComponent->GetId();

        // Child of ForEachElement MUST be ComposedComponent or MultiComposedComponent
        auto itChildStart = children_.begin();
        auto itChildEnd = children_.end();
        auto itComponentStart = components.begin();
        auto itComponentEnd = components.end();

        // 1. Try to update children at start with new components by order
        while (itChildStart != itChildEnd && itComponentStart != itComponentEnd) {
            const auto& child = *itChildStart;
            const auto& childComponent = *itComponentStart;
            auto composedComponent = AceType::DynamicCast<BaseComposedComponent>(childComponent);
            ACE_DCHECK(composedComponent);
            if (child->GetId() != composedComponent->GetId()) {
                break;
            }

            child->Update(childComponent, startIndex_ + count_);
            count_ += child->RenderCount();
            ++itChildStart;
            ++itComponentStart;
        }

        // 2. Try to find children at end with new components by order
        while (itChildStart != itChildEnd && itComponentStart != itComponentEnd) {
            const auto& child = *(--itChildEnd);
            const auto& childComponent = *(--itComponentEnd);
            auto composedComponent = AceType::DynamicCast<BaseComposedComponent>(childComponent);
            ACE_DCHECK(composedComponent);
            if (child->GetId() != composedComponent->GetId()) {
                ++itChildEnd;
                ++itComponentEnd;
                break;
            }
        }

        // 3. Collect children at middle
        std::unordered_map<ComposeId, RefPtr<ElementProxy>> proxies;
        while (itChildStart != itChildEnd) {
            const auto& child = *itChildStart;
            proxies.emplace(child->GetId(), child);
            itChildStart = children_.erase(itChildStart);
        }

        // 4. Try to update children at middle with new components by order
        while (itComponentStart != itComponentEnd) {
            const auto& childComponent = *(itComponentStart++);
            auto composedComponent = AceType::DynamicCast<BaseComposedComponent>(childComponent);
            ACE_DCHECK(composedComponent);

            RefPtr<ElementProxy> child;
            auto it = proxies.find(composedComponent->GetId());
            if (it == proxies.end()) {
                child = ElementProxy::Create(host_, childComponent);
            } else {
                child = it->second;
                proxies.erase(it);
            }

            children_.insert(itChildEnd, child);
            child->Update(childComponent, startIndex_ + count_);
            count_ += child->RenderCount();
        }

        // 5. Remove these useless children
        proxies.clear();

        // 6. Try to update children at end with new components by order
        while (itChildEnd != children_.end() && itComponentEnd != components.end()) {
            const auto& child = *(itChildEnd++);
            const auto& childComponent = *(itComponentEnd++);
            child->Update(childComponent, startIndex_ + count_);
            count_ += child->RenderCount();
        }
    }

    // In baseline Update is used on first render and also on rerender
    // in partial update only used fro first render
    // Update simplify to only support the first render case.
    void UpdateForPartialUpdate(const RefPtr<Component>& component, size_t startIndex)
    {
        if (GetElementId() != ElementRegister::UndefinedElementId) {
            // run this function only on first render
            return;
        }

        auto forEachComponent = AceType::DynamicCast<OHOS::Ace::PartUpd::ForEachComponent>(component);
        ACE_DCHECK(forEachComponent);

        SetElementId(forEachComponent->GetElementId());
        AddSelfToElementRegistry();

        const auto& components = forEachComponent->GetChildren();

        count_ = 0;
        startIndex_ = startIndex;
        composedId_ = forEachComponent->GetId();

        // Child of ForEachElement MUST be ComposedComponent or MultiComposedComponent
        auto itChildStart = children_.begin();
        auto itChildEnd = children_.end();
        auto itComponentStart = components.begin();
        auto itComponentEnd = components.end();

        // 1. Try to update children at start with new components by order
        while (itChildStart != itChildEnd && itComponentStart != itComponentEnd) {
            const auto& child = *itChildStart;
            const auto& childComponent = *itComponentStart;
            auto composedComponent = AceType::DynamicCast<BaseComposedComponent>(childComponent);
            ACE_DCHECK(composedComponent);
            if (child->GetId() != composedComponent->GetId()) {
                break;
            }

            child->Update(childComponent, startIndex_ + count_);
            count_ += child->RenderCount();
            ++itChildStart;
            ++itComponentStart;
        }

        // 2. Try to find children at end with new components by order
        while (itChildStart != itChildEnd && itComponentStart != itComponentEnd) {
            const auto& child = *(--itChildEnd);
            const auto& childComponent = *(--itComponentEnd);
            auto composedComponent = AceType::DynamicCast<BaseComposedComponent>(childComponent);
            ACE_DCHECK(composedComponent);
            if (child->GetId() != composedComponent->GetId()) {
                ++itChildEnd;
                ++itComponentEnd;
                break;
            }
        }

        // 3. Collect children at middle
        std::unordered_map<ComposeId, RefPtr<ElementProxy>> proxies;
        while (itChildStart != itChildEnd) {
            const auto& child = *itChildStart;
            proxies.emplace(child->GetId(), child);
            itChildStart = children_.erase(itChildStart);
        }

        // 4. Try to update children at middle with new components by order
        while (itComponentStart != itComponentEnd) {
            const auto& childComponent = *(itComponentStart++);
            auto composedComponent = AceType::DynamicCast<BaseComposedComponent>(childComponent);
            ACE_DCHECK(composedComponent);

            RefPtr<ElementProxy> child;
            auto it = proxies.find(composedComponent->GetId());
            if (it == proxies.end()) {
                child = ElementProxy::Create(host_, childComponent);
            } else {
                child = it->second;
                proxies.erase(it);
            }

            children_.insert(itChildEnd, child);
            child->Update(childComponent, startIndex_ + count_);
            count_ += child->RenderCount();
        }

        // 5. Remove these useless children
        proxies.clear();

        // 6. Try to update children at end with new components by order
        while (itChildEnd != children_.end() && itComponentEnd != components.end()) {
            const auto& child = *(itChildEnd++);
            const auto& childComponent = *(itComponentEnd++);
            child->Update(childComponent, startIndex_ + count_);
            count_ += child->RenderCount();
        }

        SetIdArray(forEachComponent->GetIdArray());
#ifdef ACE_DEBUG
        const auto& newIds = forEachComponent->GetIdArray();

        std::string idS = "[";
        for (const auto& newId : newIds) {
            idS += newId + ", ";
        }
        idS += "]";
#endif
    }

    void SetIdArray(const std::list<std::string>& newIdArray)
    {
        idArray_ = newIdArray;
    }

    const std::list<std::string>& GetIdArray() const
    {
        return idArray_;
    }

    template<typename T>
    int indexOf(const std::list<T>& list, T value)
    {
        int index = 0;
        for (auto it = list.begin(); it != list.end(); ++it, ++index)
            if ((*it) == value) {
                return index;
            }
        return -1;
    }

    void Append(const RefPtr<ElementProxy>& existingProxyChild)
    {
        children_.emplace_back(existingProxyChild);
        existingProxyChild->UpdateIndex(startIndex_ + count_);
        count_ += existingProxyChild->RenderCount();
    }

    void AppendNewComponent(const RefPtr<Component>& newComponent)
    {
        auto proxyChild = ElementProxy::Create(host_, newComponent);
        children_.emplace_back(proxyChild);
        proxyChild->Update(newComponent, startIndex_ + count_);
        proxyChild->UpdateIndex(startIndex_ + count_);
        count_ += proxyChild->RenderCount();
    }

    void LocalizedUpdate(
        const RefPtr<Component>& newComponent, const RefPtr<Component>& outmostWrappingComponent) override
    {
        auto forEachComponent = AceType::DynamicCast<OHOS::Ace::PartUpd::ForEachComponent>(newComponent);
        ACE_DCHECK(forEachComponent);

        // old / previous render and new render array id's
        const auto& newIds = forEachComponent->GetIdArray();
        const auto& oldIds = GetIdArray();

        ACE_DCHECK((oldIds.size() == children_.size()) &&
                   "ForEachElementProxy::LocalizedUpdate:Number of IDs generated during previous render and number of "
                   "ForEach child ElementProxy objects must match");

        // will build children_ array from scratch
        // make a copy of the list
        std::list<RefPtr<ElementProxy>> oldChildren;
        std::swap(oldChildren, children_);

        // the ForEach Component only includes the newly added children!
        const auto& newChildComponents = forEachComponent->GetChildren();

#ifdef ACE_DEBUG
        std::string idS = "[";
        for (const auto& oldId : oldIds) {
            idS += oldId + ", ";
        }
        idS += "]";

        idS = "[";
        for (const auto& newId : newIds) {
            idS += newId + ", ";
        }
        idS += "]";
#endif

        size_t newChildIndex = 0;
        int32_t oldIndex = -1;
        count_ = 0;
        for (const auto& newId : newIds) {
            if ((oldIndex = indexOf(oldIds, newId)) == -1) {
                // found a newly added ID
                // insert component into 'slot'
                auto newCompsIter = newChildComponents.begin();
                std::advance(newCompsIter, newChildIndex);
                AppendNewComponent(*newCompsIter);
                newChildIndex++;
            } else {
                // the ID was used before, only need to update the child Element's slot
                auto oldElementIter = oldChildren.begin();
                std::advance(oldElementIter, oldIndex);
                Append(*oldElementIter);
            }
        }

        SetIdArray(forEachComponent->GetIdArray());

        // host is the parent List, Swiper or Grid element
        auto host = host_.Upgrade();
        if (host) {
            host->UpdateIndex();
            host->OnDataSourceUpdated(startIndex_);
        }
    }

private:
    std::list<std::string> idArray_;
};

class MultiComposedElementProxy : public LinearElementProxy {
public:
    explicit MultiComposedElementProxy(const WeakPtr<ElementProxyHost>& host) : LinearElementProxy(host) {}
    ~MultiComposedElementProxy() override = default;

    void Update(const RefPtr<Component>& component, size_t startIndex) override
    {
        auto multiComposedComponent = AceType::DynamicCast<MultiComposedComponent>(component);
        ACE_DCHECK(multiComposedComponent);

        const auto& components = multiComposedComponent->GetChildren();

        count_ = 0;
        startIndex_ = startIndex;
        composedId_ = multiComposedComponent->GetId();

        if (children_.empty()) {
            for (const auto& childComponent : components) {
                auto child = ElementProxy::Create(host_, childComponent);
                children_.emplace_back(child);
                child->Update(childComponent, startIndex_ + count_);
                count_ += child->RenderCount();
            }
        } else {
            ACE_DCHECK(children_.size() == components.size());
            auto it = components.begin();
            for (const auto& child : children_) {
                child->Update(*(it++), startIndex_ + count_);
                count_ += child->RenderCount();
            }
        }
    }

    void LocalizedUpdate(
        const RefPtr<Component>& newComponent, const RefPtr<Component>& outmostWrappingComponent) override
    {
        Update(newComponent, startIndex_);
    }
};

class IfElseElementProxy : public MultiComposedElementProxy {
public:
    explicit IfElseElementProxy(const WeakPtr<ElementProxyHost>& host) : MultiComposedElementProxy(host) {}
    ~IfElseElementProxy() override = default;

    void Update(const RefPtr<Component>& component, size_t startIndex) override
    {
        if (Container::IsCurrentUsePartialUpdate()) {
            UpdateForPartialUpdate(component, startIndex);
            return;
        }

        auto ifElseComponent = AceType::DynamicCast<IfElseComponent>(component);
        ACE_DCHECK(ifElseComponent);

        if (branchId_ >= 0 && ifElseComponent->GetBranchId() != branchId_) {
            // Clear old children while branch id mismatched
            children_.clear();
        }

        branchId_ = ifElseComponent->GetBranchId();
        MultiComposedElementProxy::Update(component, startIndex);
    }

    void UpdateInternal(const RefPtr<IfElseComponent>& ifElseComponent, size_t startIndex)
    {
        branchId_ = ifElseComponent->GetBranchId();
        MultiComposedElementProxy::Update(ifElseComponent, startIndex);
    }

    // this function is wrongly named Update, we do not change its name to remain compatible with baseline
    // the function is only called on first render
    // on re-render Localupdate is called
    void UpdateForPartialUpdate(const RefPtr<Component>& component, size_t startIndex)
    {
        ACE_DCHECK(
            (GetElementId() == ElementRegister::UndefinedElementId) && "Update must only be called on first render");

        auto ifElseComponent = AceType::DynamicCast<IfElseComponent>(component);
        ACE_DCHECK(ifElseComponent);

        SetElementId(ifElseComponent->GetElementId());
        AddSelfToElementRegistry();

        UpdateInternal(ifElseComponent, startIndex);
    }

    void LocalizedUpdate(
        const RefPtr<Component>& newComponent, const RefPtr<Component>& outmostWrappingComponent) override
    {
        ACE_DCHECK((GetElementId() != ElementRegister::UndefinedElementId) &&
                   "IfElseElementProxy::LocalizedUpdate must only be called on re-render");

        auto ifElseComponent = AceType::DynamicCast<IfElseComponent>(newComponent);

        ACE_DCHECK(ifElseComponent && "Must supply IfElseComponent");
        ACE_DCHECK(branchId_ >= 0 && "branchId_ must initial during frst render");

        if (ifElseComponent->GetBranchId() == branchId_) {
            return;
        }

        // Clear old children while branch id mismatched
        children_.clear();

        UpdateInternal(ifElseComponent, 0);

        // host is the parent List, Swiper or Gridelement
        auto host = host_.Upgrade();
        if (host) {
            host->UpdateIndex();
            host->OnDataSourceUpdated(startIndex_);
        }
    }

private:
    int32_t branchId_ = -1;
};

} // namespace

void ElementProxy::Dump(const std::string& prefix) const
{
    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpLog::GetInstance().AddDesc(prefix + "[ElementProxy] composeId: " + composedId_);
    }
}

RefPtr<ElementProxy> ElementProxy::Create(const WeakPtr<ElementProxyHost>& host, const RefPtr<Component>& component)
{
    if (AceType::InstanceOf<LazyForEachComponent>(component)) {
        return AceType::MakeRefPtr<LazyForEachElementProxy>(host);
    }
    if (!Container::IsCurrentUsePartialUpdate()) {
        if (AceType::InstanceOf<ForEachComponent>(component)) {
            return AceType::MakeRefPtr<ForEachElementProxy>(host);
        }
    } else {
        if (AceType::InstanceOf<OHOS::Ace::PartUpd::ForEachComponent>(component)) {
            return AceType::MakeRefPtr<ForEachElementProxy>(host);
        }
        if (AceType::InstanceOf<ListItemComponent>(component)) {
            return AceType::MakeRefPtr<ListItemElementProxy>(host);
        }
        if (AceType::InstanceOf<GridLayoutItemComponent>(component)) {
            return AceType::MakeRefPtr<GridItemElementProxy>(host);
        }
    }
    if (AceType::InstanceOf<IfElseComponent>(component)) {
        return AceType::MakeRefPtr<IfElseElementProxy>(host);
    }
    if (AceType::InstanceOf<MultiComposedComponent>(component)) {
        return AceType::MakeRefPtr<MultiComposedElementProxy>(host);
    }

    if (Container::IsCurrentUsePartialUpdate()) {
        auto tabContentItemComponent = TabsHelper::TraverseComponentTo<TabContentItemComponent>(component);
        if (tabContentItemComponent) {
            return AceType::MakeRefPtr<TabContentItemElementProxy>(host);
        }
    }

    return AceType::MakeRefPtr<RenderElementProxy>(host);
}

size_t ElementProxyHost::TotalCount() const
{
    return proxy_ ? proxy_->RenderCount() : 0;
}

void ElementProxyHost::UpdateChildren(const std::list<RefPtr<Component>>& components)
{
    auto component = AceType::MakeRefPtr<MultiComposedComponent>("", "", components);
    if (!proxy_) {
        proxy_ = ElementProxy::Create(AceType::WeakClaim(this), component);
    }
    proxy_->Update(component, 0);
}

void ElementProxyHost::UpdateIndex()
{
    if (proxy_) {
        proxy_->UpdateIndex(0);
    }
}

RefPtr<Component> ElementProxyHost::GetComponentByIndex(size_t index)
{
    return proxy_ && proxy_->IndexInRange(index) ? proxy_->GetComponentByIndex(index) : nullptr;
}

RefPtr<Element> ElementProxyHost::GetElementByIndex(size_t index)
{
    return proxy_ && proxy_->IndexInRange(index) ? proxy_->GetElementByIndex(index) : nullptr;
}

void ElementProxyHost::ReleaseElementByIndex(size_t index)
{
    if (proxy_ && proxy_->IndexInRange(index)) {
        proxy_->ReleaseElementByIndex(index);
    }
}

void ElementProxyHost::ReleaseElementById(const std::string& id)
{
    if (proxy_) {
        proxy_->ReleaseElementById(id);
    }
}

void ElementProxyHost::DumpProxy()
{
    if (proxy_) {
        proxy_->Dump(PREFIX_STEP);
    } else {
        if (DumpLog::GetInstance().GetDumpFile()) {
            DumpLog::GetInstance().AddDesc(std::string("No Proxy"));
        }
    }
}

size_t ElementProxyHost::GetReloadedCheckNum()
{
    return TotalCount();
}

void ElementProxyHost::AddComposeId(const ComposeId& id)
{
    composeIds_.emplace(id);
}

void ElementProxyHost::AddActiveComposeId(ComposeId& id)
{
    activeComposeIds_.emplace(id);
}

void ElementProxyHost::ReleaseRedundantComposeIds()
{
    if (!proxy_) {
        return;
    }
    activeComposeIds_.clear();
    proxy_->RefreshActiveComposeIds();

    std::set<ComposeId> idsToRemove;
    std::set_difference(composeIds_.begin(), composeIds_.end(), activeComposeIds_.begin(), activeComposeIds_.end(),
        std::inserter(idsToRemove, idsToRemove.begin()));
    for (auto const& id : idsToRemove) {
        ReleaseElementById(id);
    }
    composeIds_ = activeComposeIds_;
    activeComposeIds_.clear();
}

void ElementProxy::AddSelfToElementRegistry()
{
    ElementRegister::GetInstance()->AddElementProxy(AceType::WeakClaim(this));
}

void ElementProxy::RemoveSelfFromElementRegistry()
{
    ElementRegister::GetInstance()->RemoveItem(GetElementId());
}

std::list<std::string> ForEachElementLookup::GetIdArray(int32_t elmtId)
{
    auto elmt = ElementRegister::GetInstance()->GetElementById(elmtId);
    auto feElmt = elmt != nullptr ? AceType::DynamicCast<OHOS::Ace::PartUpd::ForEachElement>(elmt) : nullptr;
    if (feElmt != nullptr) {
        return feElmt->GetIdArray();
    }

    auto elmtProxy = ElementRegister::GetInstance()->GetElementProxyById(elmtId);
    auto feElmtProxy =
        elmtProxy != nullptr ? AceType::DynamicCast<OHOS::Ace::V2::ForEachElementProxy>(elmtProxy) : nullptr;
    if (feElmtProxy != nullptr) {
        return feElmtProxy->GetIdArray();
    }

    LOGW("Can not find ForEachElement or ForEachElementProxy with elmtId %{public}d. (ok on first render)", elmtId);
    return {};
}

} // namespace OHOS::Ace::V2
