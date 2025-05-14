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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_MANAGER_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_MANAGER_NG_H

#include <vector>

#include "base/memory/ace_type.h"

#include "base/geometry/ng/point_t.h"
#include "base/utils/type_definition.h"
#include "core/event/ace_events.h"
#include "accessibility_constants.h"

namespace OHOS::Ace {
struct MouseEvent;
struct TouchEvent;
class TouchEventInfo;

namespace NG {
class FrameNode;
enum class AccessibilityHoverEventType;

struct AccessibilityHoverState {
    SourceType source = SourceType::NONE;
    std::vector<WeakPtr<FrameNode>> nodesHovering;
    TimeStamp time;
    bool idle = true;
    AccessibilityHoverEventType eventType = AccessibilityHoverEventType::MOVE;
};

class AccessibilityManagerNG final: public AceType {
    DECLARE_ACE_TYPE(AccessibilityManagerNG, AceType);

public:
    void HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, const MouseEvent& event);
    void HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, const TouchEvent& event);
    void HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, float pointX, float pointY,
        int32_t sourceType, int32_t eventType, int64_t timeMs);
    void HoverTestDebug(const RefPtr<FrameNode>& root, const PointF& point,
        std::string& summary, std::string& detail) const;

    /*
    * Convert coordinates of point relative to ancestor (x_ances, y_ances) to
    * coordinates of point relative to node (x_node, y_node)
    * { return } true if succeeded, and the new point is saved in ${pointNode}
    *            false if nullptr or ${ancestor} is not ancestor of ${node}
    */
    static bool ConvertPointFromAncestorToNode(
        const RefPtr<NG::FrameNode>& ancestor, const RefPtr<NG::FrameNode>& node,
        const PointF& pointAncestor, PointF& pointNode);

private:
    struct HandleHoverEventInnerParam {
        SourceType sourceType = SourceType::NONE;
        AccessibilityHoverEventType eventType = AccessibilityHoverEventType::MOVE;
        TimeStamp time;
    };

    /*
    * Compute components which are hovered in accessibility mode.
    * And send hover enter/exit events to accessibility framework;
    * param: {root} should be not-null.
    */
    void HandleAccessibilityHoverEventInner(
        const RefPtr<FrameNode>& root,
        const PointF& point,
        HandleHoverEventInnerParam param,
        const TouchEvent& event);

    void ResetHoverState();
    bool IgnoreCurrentHoveringNode(const RefPtr<FrameNode> &node);
    static bool NotifyHoverEventToNodeSession(
        const RefPtr<FrameNode>& node,
        const RefPtr<FrameNode>& rootNode, const PointF& pointRoot,
        SourceType sourceType, AccessibilityHoverEventType eventType, TimeStamp time);

    bool IsEventTypeChangeDirectHandleHover(AccessibilityHoverEventType eventType);
    bool IsHandlePipelineAccessibilityHoverEnter(const RefPtr<NG::FrameNode>& root);
    void HandlePipelineAccessibilityHoverEnter(
        const RefPtr<NG::FrameNode>& root,
        TouchEvent& event,
        int32_t eventType);

    bool HandleAccessibilityHoverTransparentCallback(bool transform,
        const RefPtr<FrameNode>& root,
        const int32_t& currentHoveringId,
        const int32_t& lastHoveringId,
        const TouchEvent& event);
    bool ExecuteChildNodeHoverTransparentCallback(const RefPtr<FrameNode>& root, const TouchEvent& event);

    AccessibilityHoverState hoverState_;
};
} // namespace NG
} // namespace OHOS::Ace

#endif
