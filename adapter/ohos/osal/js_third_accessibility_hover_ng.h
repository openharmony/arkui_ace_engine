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
class JsAccessibilityManager;
struct ActionParam;
class JsThirdProviderInteractionOperation;

using namespace OHOS::Accessibility;

struct AccessibilityHoverForThirdState {
    SourceType source = SourceType::NONE;
    std::vector<int64_t> nodesHovering;
    TimeStamp time;
    bool idle = true;
    bool thirdOperationIdle = true;
};

struct AccessibilityHoverForThirdConfig {
    int64_t hostElementId = -1;
    NG::PointF point;
    SourceType sourceType = SourceType::NONE;
    NG::AccessibilityHoverEventType eventType = NG::AccessibilityHoverEventType::ENTER;
    TimeStamp time = std::chrono::high_resolution_clock::now();
    RefPtr<NG::PipelineContext> context;
};

using AccessibilityHoverTestPathForThird = std::vector<int64_t>;

class AccessibilityHoverManagerForThirdNG : public AceType {
    DECLARE_ACE_TYPE(AccessibilityHoverManagerForThirdNG, AceType);

public:
    void HandleAccessibilityHoverForThird(
        const AccessibilityHoverForThirdConfig& config);
    bool GetElementInfoForThird(
        int64_t elementId,
        AccessibilityElementInfo& info,
        int64_t hostElementId);

    bool ActThirdAccessibilityFocus(
        int64_t elementId,
        const AccessibilityElementInfo& nodeInfo,
        const RefPtr<NG::FrameNode>& hostNode,
        const RefPtr<NG::PipelineContext>& context,
        bool isNeedClear);
    void RegisterJsThirdProviderInteractionOperation(
        int64_t hostElementId,
        const std::shared_ptr<JsThirdProviderInteractionOperation>& jsThirdProviderOperator);
    void DeregisterJsThirdProviderInteractionOperation(int64_t hostElementId);
    std::weak_ptr<JsThirdProviderInteractionOperation> &GetJsThirdProviderInteractionOperation(
        int64_t hostElementId)
    {
        return jsThirdProviderOperator_[hostElementId];
    }

    bool OnDumpChildInfoForThirdRecursive(
        int64_t hostElementId,
        const std::vector<std::string>& params,
        std::vector<std::string>& info,
        const WeakPtr<JsAccessibilityManager>& jsAccessibilityManager);
    bool ClearThirdAccessibilityFocus(const RefPtr<NG::FrameNode>& hostNode);

private:
    void HandleAccessibilityHoverForThirdInner(
        const AccessibilityHoverForThirdConfig& config);
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
        std::string& hitTestMode,
        bool& shouldSearchSelf,
        bool& shouldSearchChildren);
    void DumpPropertyForThird(
        int64_t elementId,
        const WeakPtr<JsAccessibilityManager>& jsAccessibilityManager,
        const std::shared_ptr<JsThirdProviderInteractionOperation>& jsThirdProviderOperator);

    AccessibilityHoverForThirdState hoverForThirdState_;
    std::unordered_map<int64_t, std::weak_ptr<JsThirdProviderInteractionOperation>>
        jsThirdProviderOperator_;
};
} // namespace NG
} // namespace OHOS::Ace

#endif
