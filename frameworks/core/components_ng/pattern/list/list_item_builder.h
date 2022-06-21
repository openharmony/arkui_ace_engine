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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_BUILDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_BUILDER_H

#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/syntax/foreach/for_each_builder.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ListItemBuilder : public virtual Referenced {
public:
    ListItemBuilder() = default;
    ~ListItemBuilder() override = default;

    void Clean()
    {
        uiNodes_.clear();
    }

    void AddUiNodeId(const RefPtr<UiNodeId>& child)
    {
        uiNodes_.emplace_back(child);
    }

    int32_t GetTotalCount()
    {
        auto totalCount = 0;
        for (const auto& item : uiNodes_) {
            if (AceType::InstanceOf<FrameNode>(item)) {
                totalCount++;
                continue;
            }
            if (AceType::InstanceOf<ForEachBuilder>(item)) {
                totalCount = totalCount + AceType::DynamicCast<ForEachBuilder>(item)->GetTotalCount();
            }
        }
        return totalCount;
    }

    RefPtr<FrameNode> GetChildByIndex(int32_t index)
    {
        auto currentIndex = 0;
        for (const auto& item : uiNodes_) {
            if (AceType::InstanceOf<FrameNode>(item)) {
                if (currentIndex == index) {
                    return AceType::DynamicCast<FrameNode>(item);
                }
                currentIndex++;
                continue;
            }
            if (AceType::InstanceOf<ForEachBuilder>(item)) {
                auto builder = AceType::DynamicCast<ForEachBuilder>(item);
                auto totalCount = builder->GetTotalCount();
                if ((index >= currentIndex) && (index < currentIndex + totalCount)) {
                    return builder->GetChildByIndex(index - currentIndex);
                }
                currentIndex = currentIndex + totalCount;
            }
        }
        return nullptr;
    }

private:
    std::list<RefPtr<UiNodeId>> uiNodes_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_BUILDER_H
