/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_NODE_UTILS_ACCESSIBILITY_FRAME_NODE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_NODE_UTILS_ACCESSIBILITY_FRAME_NODE_UTILS_H

#include "base/memory/ace_type.h"
#include "core/accessibility/accessibility_utils.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class AccessibilityFrameNodeUtils {
public:
    static void UpdateAccessibilityVisibleToRoot(const RefPtr<UINode>& uiNode);
    static RefPtr<FrameNode> GetFramenodeByAccessibilityId(const RefPtr<FrameNode>& root, int64_t id);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_NODE_UTILS_ACCESSIBILITY_FRAME_NODE_UTILS_H
