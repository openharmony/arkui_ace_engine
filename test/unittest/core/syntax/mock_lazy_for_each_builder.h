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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_SYNTAX_MOCK_LAZY_FOR_EACH_BUILDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_SYNTAX_MOCK_LAZY_FOR_EACH_BUILDER_H

#include "base/memory/ace_type.h"
#define private public
#include "mock_lazy_for_each_actuator.h"

#include "core/components_ng/syntax/lazy_for_each_builder.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::Framework {
class MockLazyForEachBuilder : public NG::LazyForEachBuilder, public MockLazyForEachActuator {
    DECLARE_ACE_TYPE(MockLazyForEachBuilder, NG::LazyForEachBuilder, MockLazyForEachActuator);

public:
    explicit MockLazyForEachBuilder(bool deleteExpiringItemImmediately = false)
        : deleteExpiringItemImmediately_(deleteExpiringItemImmediately) {}
    void ReleaseChildGroupById(const std::string& id) override {}
    void RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) override {}
    void UnregisterDataChangeListener(V2::DataChangeListener* listener) override {}

protected:
    int32_t OnGetTotalCount() override
    {
        return static_cast<int32_t>(cachedItems_.size());
    }
    bool DeleteExpiringItemImmediately() override
    {
        return deleteExpiringItemImmediately_;
    }
    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& cachedItems) override
    {
        return { std::to_string(index),
            AceType::MakeRefPtr<NG::FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<NG::Pattern>()) };
    }
    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndexNew(int32_t index,
        std::map<int32_t, NG::LazyForEachChild>& cachedItems,
        std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override
    {
        return { std::to_string(index),
            AceType::MakeRefPtr<NG::FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<NG::Pattern>()) };
    }
    void OnExpandChildrenOnInitialInNG() override {}
    void NotifyDataChanged(size_t index, const RefPtr<NG::UINode>& lazyForEachNode, bool isRebuild = true) override {};
    void NotifyDataDeleted(const RefPtr<NG::UINode>& lazyForEachNode, size_t index, bool removeIds) override {};
    void NotifyDataAdded(size_t index) override {};
    void KeepRemovedItemInCache(NG::LazyForEachChild node,
        std::unordered_map<std::string, NG::LazyForEachCacheChild>& cachedItems) override {};
private:
    bool deleteExpiringItemImmediately_;
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_SYNTAX_MOCK_LAZY_FOR_EACH_BUILDER_H
