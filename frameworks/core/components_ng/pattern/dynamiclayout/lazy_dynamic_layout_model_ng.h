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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_LAZY_DYNAMIC_LAYOUT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_LAZY_DYNAMIC_LAYOUT_MODEL_NG_H

#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"

namespace OHOS::Ace::NG {
class FrameNode;

class ACE_EXPORT LazyDynamicLayoutModelNG {
public:
    void Create(const RefPtr<LazyCustomLayoutAlgorithmParam>& customParams);
    
    static void SetOnVisibleIndexesChange(FrameNode* frameNode, OnVisibleIndexesChangeEvent&& onVisibleIndexesChange);
    
    static void SetAdjustedOffset(FrameNode* frameNode, float adjustedOffset);

    static void SetInActiveChildren(FrameNode* frameNode, const std::vector<int32_t>& inActiveChildren);

private:
    static void UpdatePropertyFromCustomParam(
        const RefPtr<FrameNode>& frameNode, const RefPtr<LazyCustomLayoutAlgorithmParam>& customParams);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_LAZY_DYNAMIC_LAYOUT_MODEL_NG_H