/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HOVER_STACK_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HOVER_STACK_NODE_H

#include <cstdint>
#include <list>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/animation/page_transition_common.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/folder_stack/hover_stack_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
namespace OHOS::Ace::NG {
class ACE_EXPORT HoverStackNode : public GroupNode {
    DECLARE_ACE_TYPE(HoverStackNode, GroupNode)
public:
    HoverStackNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : GroupNode(tag, nodeId, pattern)
    {}
    ~HoverStackNode() override = default;
    static RefPtr<HoverStackNode> GetOrCreateHoverStackNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
};
} // namespace OHOS::Ace::NG
#endif