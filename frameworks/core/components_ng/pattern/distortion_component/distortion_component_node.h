/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DISTORTION_COMPONENT_DISTORTION_COMPONENT_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DISTORTION_COMPONENT_DISTORTION_COMPONENT_NODE_H

#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/distortion_component/distortion_component_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT DistortionComponentNode : public GroupNode {
    DECLARE_ACE_TYPE(DistortionComponentNode, GroupNode);

public:
    DistortionComponentNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : GroupNode(tag, nodeId, pattern) {}
    ~DistortionComponentNode() override = default;

    void AddChildToGroup(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT) override;

    static RefPtr<DistortionComponentNode> GetOrCreateDistortionComponentNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

private:
    ACE_DISALLOW_COPY_AND_MOVE(DistortionComponentNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DISTORTION_COMPONENT_DISTORTION_COMPONENT_NODE_H