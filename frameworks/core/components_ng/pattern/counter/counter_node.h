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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_NODE_H

#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/counter/counter_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT CounterNode : public GroupNode {
    DECLARE_ACE_TYPE(CounterNode, GroupNode);

public:
    CounterNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : GroupNode(tag, nodeId, pattern, isRoot)
    {}
    ~CounterNode() override = default;

    static RefPtr<CounterNode> GetOrCreateCounterNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    void AddChildToGroup(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT) override;
    
    void DeleteChildFromGroup(int32_t slot = DEFAULT_NODE_SLOT) override;

private:
    ACE_DISALLOW_COPY_AND_MOVE(CounterNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_NODE_H