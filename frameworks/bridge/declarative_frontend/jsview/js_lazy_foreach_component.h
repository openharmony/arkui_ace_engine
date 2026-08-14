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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAZY_FOREACH_COMPONENT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAZY_FOREACH_COMPONENT_H

#include <functional>
#include <set>
#include <string>

#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/jsview/js_lazy_foreach_actuator.h"
#include "bridge/declarative_frontend/jsview/js_view.h"
#include "core/components_v2/foreach/lazy_foreach_component.h"

namespace OHOS::Ace::Framework {

class DefaultDataChangeListener : public V2::DataChangeListener {
    DECLARE_ACE_TYPE(DefaultDataChangeListener, DataChangeListener);
public:
    explicit DefaultDataChangeListener(JSView* parentView) : parentView_(parentView) {}
    ~DefaultDataChangeListener() override = default;

    void OnDataReloaded() override
    {
        if (parentView_ != nullptr) {
            parentView_->MarkNeedUpdate();
        }
    }
    void OnDataAdded(size_t index) override
    {
        if (parentView_ != nullptr) {
            parentView_->MarkNeedUpdate();
        }
    }
    void OnDataBulkAdded(size_t index, size_t count) override
    {
        if (parentView_ != nullptr) {
            parentView_->MarkNeedUpdate();
        }
    }
    void OnDataDeleted(size_t index) override
    {
        if (parentView_ != nullptr) {
            parentView_->MarkNeedUpdate();
        }
    }
    void OnDataBulkDeleted(size_t index, size_t count) override
    {
        if (parentView_ != nullptr) {
            parentView_->MarkNeedUpdate();
        }
    }
    void OnDataChanged(size_t index) override
    {
        if (parentView_ != nullptr) {
            parentView_->MarkNeedUpdate();
        }
    }
    void OnDataMoved(size_t from, size_t to) override
    {
        if (parentView_ != nullptr) {
            parentView_->MarkNeedUpdate();
        }
    }
    void OnDatasetChange(const std::list<V2::Operation>& DataOperations) override
    {
        if (parentView_ != nullptr) {
            parentView_->MarkNeedUpdate();
        }
    }

private:
    JSView* parentView_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(DefaultDataChangeListener);
};

class JSLazyForEachComponent : public V2::LazyForEachComponent, public JSLazyForEachActuator {
    DECLARE_ACE_TYPE(JSLazyForEachComponent, V2::LazyForEachComponent, JSLazyForEachActuator);

public:
    explicit JSLazyForEachComponent(const std::string& id) : V2::LazyForEachComponent(id) {}
    ~JSLazyForEachComponent() override = default;

    size_t OnGetTotalCount() override
    {
        return static_cast<size_t>(GetTotalIndexCount());
    }

    void ExpandChildrenOnInitial()
    {
        auto totalIndex = GetTotalIndexCount();
        auto* stack = ViewStackProcessor::GetInstance();
        JSRef<JSVal> params[2];
        for (auto index = 0; index < totalIndex; index++) {
            params[0] = CallJSFunction(getDataFunc_, dataSourceObj_, index);
            params[1] = JSRef<JSVal>::Make(ToJSValue(index));
            std::string key = keyGenFunc_(params[0], index);
            auto multiComposed = AceType::MakeRefPtr<MultiComposedComponent>(key, "LazyForEach");
            stack->Push(multiComposed);
            stack->PushKey(key);
            itemGenFunc_->Call(JSRef<JSObject>(), 2, params);
            stack->PopContainer();
            stack->PopKey();
        }
    }

    RefPtr<Component> OnGetChildByIndex(size_t index) override
    {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, nullptr);
        if (getDataFunc_.IsEmpty()) {
            return nullptr;
        }

        JSRef<JSVal> params[2];
        params[0] = CallJSFunction(getDataFunc_, dataSourceObj_, index);
        params[1] = JSRef<JSVal>::Make(ToJSValue(index));
        std::string key = keyGenFunc_(params[0], index);

        ScopedViewStackProcessor scopedViewStackProcessor;
        auto* viewStack = ViewStackProcessor::GetInstance();
        auto multiComposed = AceType::MakeRefPtr<MultiComposedComponent>(key, "LazyForEach");
        viewStack->Push(multiComposed);
        if (parentView_) {
            parentView_->MarkLazyForEachProcess(key);
        }
        viewStack->PushKey(key);
        itemGenFunc_->Call(JSRef<JSObject>(), 2, params);
        viewStack->PopContainer();
        viewStack->PopKey();
        if (parentView_) {
            parentView_->ResetLazyForEachProcess();
        }
        auto component = viewStack->Finish();
        ACE_DCHECK(multiComposed == component);

        while (multiComposed) {
            const auto& children = multiComposed->GetChildren();
            if (children.empty()) {
                return AceType::MakeRefPtr<ComposedComponent>(key, "LazyForEachItem");
            }

            component = children.front();
            multiComposed = AceType::DynamicCast<MultiComposedComponent>(component);
        }

        return AceType::MakeRefPtr<ComposedComponent>(key, "LazyForEachItem", component);
    }

    void ReleaseChildGroupByComposedId(const std::string& composedId) override
    {
        JSLazyForEachActuator::ReleaseChildGroupByComposedId(composedId);
    }

    void RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) override
    {
        JSLazyForEachActuator::RegisterListener(listener);
    }

    void UnregisterDataChangeListener(V2::DataChangeListener* listener) override
    {
        JSLazyForEachActuator::UnregisterListener(listener);
    }

private:
    std::list<RefPtr<Component>>& ExpandChildren() override
    {
        // Register data change listener while expanding the lazy foreach component
        if (!Expanded()) {
            defaultListener_ = Referenced::MakeRefPtr<DefaultDataChangeListener>(parentView_);
            RegisterDataChangeListener(defaultListener_);
        }
        return LazyForEachComponent::ExpandChildren();
    }

    ACE_DISALLOW_COPY_AND_MOVE(JSLazyForEachComponent);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAZY_FOREACH_COMPONENT_H
