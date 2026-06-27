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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_LAZY_DYNAMIC_LAYOUT_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_LAZY_DYNAMIC_LAYOUT_MODEL_STATIC_H

#include <functional>
#include <memory>
#include <vector>

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LazyDynamicLayoutModelStatic {
public:
    using VisibleIndexesChangeEvent = std::function<void(const std::vector<int32_t>&)>;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetParams(FrameNode* frameNode, const RefPtr<LazyCustomLayoutAlgorithmParam>& params);
    static void SetOnVisibleIndexesChange(FrameNode* frameNode, VisibleIndexesChangeEvent&& onVisibleIndexesChange);
    static void SetAdjustedOffset(FrameNode* frameNode, float adjustedOffset);
    static void SetInActiveChildren(FrameNode* frameNode, const std::vector<int32_t>& inActiveChildren);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_LAZY_DYNAMIC_LAYOUT_MODEL_STATIC_H