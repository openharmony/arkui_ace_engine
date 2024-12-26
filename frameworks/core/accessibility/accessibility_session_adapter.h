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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_SESSION_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_SESSION_ADAPTER_H

#include "base/memory/ace_type.h"

#include "base/geometry/ng/point_t.h"
#include "base/utils/type_definition.h"

namespace OHOS::Ace {
enum class SourceType;
namespace NG {
enum class AccessibilityHoverEventType;
class FrameNode;

class AccessibilitySessionAdapter : public AceType {
    DECLARE_ACE_TYPE(AccessibilitySessionAdapter, AceType);

public:
    AccessibilitySessionAdapter() = default;
    ~AccessibilitySessionAdapter() override = default;

    virtual void TransferHoverEvent(const PointF& point, SourceType source,
        AccessibilityHoverEventType eventType, TimeStamp time) { }

    virtual bool IgnoreHostNode() const { return false; };

    virtual bool IgnoreTransformMouseEvent() const { return false; };

    /*
    * Get session adapter of node if node type is in ${SESSION_ADAPTER_MAP}
    * {param} node: not-null
    */
    static RefPtr<AccessibilitySessionAdapter> GetSessionAdapter(const RefPtr<FrameNode>& node);
};
} // namespace NG
} // namespace OHOS::Ace

#endif
