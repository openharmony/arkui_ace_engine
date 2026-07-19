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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_NODE_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_NODE_HELPER_H

#include <cstdint>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/node/divider_modifier.h"

namespace OHOS::Ace::NG {

inline RefPtr<FrameNode> CreateDividerFrameNode(int32_t nodeId)
{
    auto nodeModifiers = NG::NodeModifier::GetDividerModifier();
    CHECK_NULL_RETURN(nodeModifiers && nodeModifiers->createFrameNode, nullptr);
    auto arkUINodeHandle = nodeModifiers->createFrameNode(nodeId);
    CHECK_NULL_RETURN(arkUINodeHandle, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(arkUINodeHandle);
    CHECK_NULL_RETURN(frameNode, nullptr);
    return Referenced::Claim<FrameNode>(frameNode);
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_NODE_HELPER_H
