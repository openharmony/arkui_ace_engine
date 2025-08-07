/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_COMPONENT_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_COMPONENT_MANAGER_H

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT DynamicComponentManager {
public:
    DynamicComponentManager() {}
    ~DynamicComponentManager() {};
    static void TriggerOnAreaChangeCallback(
        FrameNode* frameNode, uint64_t nanoTimestamp, int32_t areaChangeMinDepth = -1);
    static void HandleDynamicRenderOnAreaChange(FrameNode* frameNode, const RectF& currFrameRect,
        const OffsetF& currParentOffset, const OffsetF& currHostParentOffset);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_COMPONENT_MANAGER_H
