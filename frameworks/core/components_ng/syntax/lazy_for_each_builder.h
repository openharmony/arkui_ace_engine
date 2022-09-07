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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H

#include <cstdint>
#include <map>
#include <string>
#include <utility>

#include "base/log/ace_trace.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_v2/foreach/lazy_foreach_component.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LazyForEachBuilder : public virtual AceType, public V2::DataChangeListener {
    DECLARE_ACE_TYPE(NG::LazyForEachBuilder, AceType)
public:
    LazyForEachBuilder() = default;
    ~LazyForEachBuilder() override = default;

    int32_t GetTotalCount()
    {
        return OnGetTotalCount();
    }

    RefPtr<UINode> GetChildByIndex(int32_t index)
    {
        auto iter = cachedItems_.find(index);
        if (iter != cachedItems_.end()) {
            return iter->second.second;
        }
        {
            ACE_SCOPED_TRACE("Builder:BuildLazyItem");
            auto itemInfo = OnGetChildByIndex(index);
            CHECK_NULL_RETURN(itemInfo.second, nullptr);
            cachedItems_.try_emplace(index, itemInfo);
            return itemInfo.second;
        }
    }

    const std::map<int32_t, std::pair<std::string, RefPtr<UINode>>>& GetCacheItems() const
    {
        return cachedItems_;
    }

    std::map<int32_t, std::pair<std::string, RefPtr<UINode>>>& ModifyCacheItems()
    {
        return cachedItems_;
    }

    void ExpandChildrenOnInitial()
    {
        OnExpandChildrenOnInitial();
    }

    void OnDataReloaded() override {}
    void OnDataAdded(size_t index) override {}
    void OnDataDeleted(size_t index) override {}
    void OnDataChanged(size_t index) override {}
    void OnDataMoved(size_t from, size_t to) override {}

    virtual void ReleaseChildGroupById(const std::string& id) = 0;
    virtual void RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) = 0;
    virtual void UnregisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) = 0;

protected:
    virtual int32_t OnGetTotalCount() = 0;
    virtual std::pair<std::string, RefPtr<UINode>> OnGetChildByIndex(int32_t index) = 0;
    virtual void OnExpandChildrenOnInitial() = 0;

private:
    // [index : [key, UINode]]
    std::map<int32_t, std::pair<std::string, RefPtr<UINode>>> cachedItems_;

    ACE_DISALLOW_COPY_AND_MOVE(LazyForEachBuilder);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_LAZY_FOR_EACH_BUILDER_H
