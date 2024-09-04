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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_THIRD_ACCESSIBILITY_HOVER_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_THIRD_ACCESSIBILITY_HOVER_NG_H

#include <vector>

#include "accessibility_config.h"
#include "accessibility_element_operator.h"
#include "accessibility_event_info.h"
#include "accessibility_state_event.h"
#include "base/geometry/ng/point_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/type_definition.h"
#include "core/accessibility/accessibility_manager.h"
#include "core/accessibility/accessibility_utils.h"
#include "core/event/ace_events.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"

namespace OHOS::Ace {
struct MouseEvent;
struct TouchEvent;

namespace Framework {
class FrameNode;
class JsAccessibilityManager;
struct ActionParam;

using namespace OHOS::Accessibility;

struct AccessibilityHoverForThirdState {
    SourceType source = SourceType::NONE;
    std::vector<int64_t> nodesHovering;
    TimeStamp time;
    bool idle = true;
};

using AccessibilityHoverTestPathForThird = std::vector<int64_t>;

class AccessibilityHoverManagerForThirdNG : public AceType {
    DECLARE_ACE_TYPE(AccessibilityHoverManagerForThirdNG, AceType);

public:
    void HandleAccessibilityHoverForThird(
        int64_t hostElementId,
        const NG::PointF& point,
        SourceType sourceType,
        NG::AccessibilityHoverEventType eventType,
        TimeStamp time,
        RefPtr<NG::FrameNode> &hostNode,
        RefPtr<NG::PipelineContext> &context);

    void SendAccessibilityEventForThird(
        int64_t elementId,
        AccessibilityEventType eventType,
        WindowsContentChangeTypes windowsContentChangeType,
        RefPtr<NG::FrameNode> &hostNode,
        RefPtr<NG::PipelineContext> &context);
    void GetElementInfoForThird(int64_t elementId, AccessibilityElementInfo &info);
    void SendThirdAccessibilityAsyncEvent(
        const AccessibilityEvent& accessibilityEvent,
        const RefPtr<NG::FrameNode>& hostNode);

    void SetHandlerForThird(const WeakPtr<JsAccessibilityManager>& jsAccessibilityManager)
    {
        jsAccessibilityManager_ = jsAccessibilityManager;
    }

    const WeakPtr<JsAccessibilityManager>& GetHandlerForThird() const
    {
        return jsAccessibilityManager_;
    }

    void SetTreeIdForTest(int32_t treeId)
    {
        xcomponentTreeId_ = treeId;
    }

    int32_t GetTreeIdForTest()
    {
        return xcomponentTreeId_;
    }

    bool ActThirdAccessibilityFocus(
        int64_t elementId,
        const AccessibilityElementInfo& nodeInfo,
        const RefPtr<NG::FrameNode>& hostNode,
        const RefPtr<NG::PipelineContext>& context,
        bool isNeedClear);

private:
    void ResetHoverForThirdState();
    AccessibilityHoverTestPathForThird HoverPathForThird(
        const int64_t hostElementId,
        const NG::PointF& point,
        AccessibilityElementInfo& rootInfo);
    bool HoverPathForThirdRecursive(
        const int64_t hostElementId,
        const NG::PointF& hoverPoint,
        const AccessibilityElementInfo& nodeInfo,
        AccessibilityHoverTestPathForThird& path);
    std::pair<bool, bool> GetSearchStrategyForThird(
        const AccessibilityElementInfo& nodeInfo);
    bool IsAccessibilityFocusable(const AccessibilityElementInfo& nodeInfo);
    bool HasAccessibilityTextOrDescription(const AccessibilityElementInfo& nodeInfo);
    void UpdateSearchStrategyByHitTestModeStr(
        std::string &hitTestMode,
        bool& shouldSearchSelf,
        bool& shouldSearchChildren);

    AccessibilityHoverForThirdState hoverForThirdState_;
    WeakPtr<JsAccessibilityManager> jsAccessibilityManager_;
    int32_t xcomponentTreeId_ = 0;
};
} // namespace NG
} // namespace OHOS::Ace

#endif
