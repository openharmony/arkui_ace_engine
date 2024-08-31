/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "js_accessibility_manager.h"
#include "core/accessibility/accessibility_manager_ng.h"

#include <algorithm>

#include "accessibility_constants.h"
#include "accessibility_event_info.h"
#include "accessibility_system_ability_client.h"

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/linear_map.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/dom/dom_type.h"
#include "frameworks/core/components_ng/pattern/web/web_pattern.h"
#include "nlohmann/json.hpp"

using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;
using namespace std;

namespace OHOS::Ace::Framework {

constexpr int32_t ACCESSIBILITY_FOCUS_WITHOUT_EVENT = -2100001;
AccessibilityElementInfo nodeInfo_[9];

void AccessibilityHoverManagerForThirdNG::GetElementInfoForThird(
    int64_t elementId,
    AccessibilityElementInfo &info)
{}

void AccessibilityHoverManagerForThirdNG::SendAccessibilityEventForThird(
    int64_t elementId,
    AccessibilityEventType eventType,
    WindowsContentChangeTypes windowsContentChangeType,
    RefPtr<NG::FrameNode> &hostNode,
    RefPtr<NG::PipelineContext> &context)
{
    auto accessibilityManager = context->GetAccessibilityManager();
    auto jsAccessibilityManager =
        AceType::DynamicCast<JsAccessibilityManager>(accessibilityManager);;
    CHECK_NULL_VOID(jsAccessibilityManager);

    AccessibilityEvent event;
    event.type = eventType;
    event.windowContentChangeTypes = windowsContentChangeType;
    event.nodeId = elementId;
    SendThirdAccessibilityAsyncEvent(event, hostNode);
}

void AccessibilityHoverManagerForThirdNG::UpdateSearchStrategyByHitTestModeStr(
    std::string &hitTestMode,
    bool& shouldSearchSelf,
    bool& shouldSearchChildren)
{
    if (hitTestMode == "HitTestMode.Block") {
        shouldSearchChildren = false;
    }  else if (hitTestMode == "HitTestMode.None") {
        shouldSearchSelf = false;
    }
}

bool AccessibilityHoverManagerForThirdNG::HasAccessibilityTextOrDescription(
    const AccessibilityElementInfo& nodeInfo)
{
    std::optional<std::string> accessibilityText = nodeInfo.GetAccessibilityText();
    std::optional<std::string> accessibilityDescription = nodeInfo.GetDescriptionInfo();
    return !accessibilityText.value_or("").empty() ||
        !accessibilityDescription.value_or("").empty();
}

bool AccessibilityHoverManagerForThirdNG::IsAccessibilityFocusable(
    const AccessibilityElementInfo& nodeInfo)
{
    return true;
}

std::pair<bool, bool> AccessibilityHoverManagerForThirdNG::GetSearchStrategyForThird(
    const AccessibilityElementInfo& nodeInfo)
{
    bool shouldSearchSelf = true;
    bool shouldSearchChildren = true;
    auto level = NG::AccessibilityProperty::Level::AUTO;
    do {
        level = nodeInfo.GetAccessibilityLevel();
        bool hasAccessibilityText = HasAccessibilityTextOrDescription(nodeInfo);
        if (level == NG::AccessibilityProperty::Level::YES_STR) {
            break;
        } else if (level == NG::AccessibilityProperty::Level::NO_HIDE_DESCENDANTS) {
            shouldSearchSelf = false;
            shouldSearchChildren = false;
            break;
        } else {
            if (level == NG::AccessibilityProperty::Level::NO_STR) {
                shouldSearchSelf = false;
            } else {
                // shouldSearchSelf is true here
                if (hasAccessibilityText) {
                    break;
                }
            }
        }
    
        auto hitTestMode = nodeInfo.GetHitTestBehavior();
        UpdateSearchStrategyByHitTestModeStr(
            hitTestMode, shouldSearchSelf, shouldSearchChildren);
    } while (0);

    if (IsAccessibilityFocusable(nodeInfo) == false) {
        shouldSearchSelf = false;
    }

    return std::make_pair(shouldSearchSelf, shouldSearchChildren);
}


bool AccessibilityHoverManagerForThirdNG::HoverPathForThirdRecursive(
    const int64_t hostElementId,
    const NG::PointF& hoverPoint,
    const AccessibilityElementInfo& nodeInfo,
    AccessibilityHoverTestPathForThird& path)
{
    bool hitTarget = false;
    auto [shouldSearchSelf, shouldSearchChildren]
        = GetSearchStrategyForThird(nodeInfo);
    auto rectInScreen = nodeInfo.GetRectInScreen();
    auto left = rectInScreen.GetLeftTopXScreenPostion();
    auto right = rectInScreen.GetLeftTopYScreenPostion();
    auto width = rectInScreen.GetRightBottomXScreenPostion() - rectInScreen.GetLeftTopXScreenPostion();
    auto height = rectInScreen.GetRightBottomYScreenPostion() - rectInScreen.GetLeftTopYScreenPostion();
    NG::RectF rect { left, right, width, height };
    bool hitSelf = rect.IsInnerRegion(hoverPoint);
    if (hitSelf && shouldSearchSelf) {
        hitTarget = true;
        path.push_back(nodeInfo.GetAccessibilityId());
    }

    if (shouldSearchChildren) {
        auto childrenIds = nodeInfo.GetChildIds();
        for (auto childId = childrenIds.rbegin(); childId != childrenIds.rend(); ++childId) {
            AccessibilityElementInfo childInfo;
            GetElementInfoForThird(*childId, childInfo);
            if (HoverPathForThirdRecursive(hostElementId, hoverPoint, childInfo, path)) {
                return true;
            }
        }
    }
    return hitTarget;
}

AccessibilityHoverTestPathForThird AccessibilityHoverManagerForThirdNG::HoverPathForThird(
    const int64_t hostElementId,
    const NG::PointF& point,
    AccessibilityElementInfo& rootInfo) 
{
    AccessibilityHoverTestPathForThird path;
    HoverPathForThirdRecursive(hostElementId, point, rootInfo, path);
    return path;
}

void AccessibilityHoverManagerForThirdNG::ResetHoverForThirdState()
{
    hoverForThirdState_.idle = true;
    hoverForThirdState_.nodesHovering.clear();
}

void AccessibilityHoverManagerForThirdNG::HandleAccessibilityHoverForThird(
    int64_t hostElementId,
    const NG::PointF& point,
    SourceType sourceType,
    NG::AccessibilityHoverEventType eventType,
    TimeStamp time,
    RefPtr<NG::FrameNode> &hostNode,
    RefPtr<NG::PipelineContext> &context)
{

    if (eventType == NG::AccessibilityHoverEventType::ENTER) {
        ResetHoverForThirdState();
    }

    std::vector<int64_t> currentNodesHovering;
    std::vector<int64_t> lastNodesHovering = hoverForThirdState_.nodesHovering;
    if (eventType != NG::AccessibilityHoverEventType::EXIT) {
        AccessibilityElementInfo rootInfo;
        GetElementInfoForThird(-1, rootInfo);
        AccessibilityHoverTestPathForThird path =
            HoverPathForThird(hostElementId,  point, rootInfo);
        for (const auto& node: path) {
            currentNodesHovering.push_back(node);
        }
    }

    static constexpr int64_t INVALID_NODE_ID = -1;
    int64_t lastHoveringId = INVALID_NODE_ID;
    if (!lastNodesHovering.empty()) {
        lastHoveringId = lastNodesHovering.back();
    }

    int64_t currentHoveringId = INVALID_NODE_ID;
    if (!currentNodesHovering.empty()) {
        currentHoveringId = currentNodesHovering.back();
    }

    if (lastHoveringId != INVALID_NODE_ID && lastHoveringId != currentHoveringId) {
        SendAccessibilityEventForThird(lastHoveringId, AccessibilityEventType::HOVER_EXIT_EVENT,
            WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID, hostNode, context);
    }

    if ((currentHoveringId != INVALID_NODE_ID) && (currentHoveringId != lastHoveringId)) {
        SendAccessibilityEventForThird(currentHoveringId, AccessibilityEventType::HOVER_ENTER_EVENT,
            WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID, hostNode, context);
    }

    hoverForThirdState_.nodesHovering = std::move(currentNodesHovering);
    hoverForThirdState_.time = time;
    hoverForThirdState_.source = sourceType;
    hoverForThirdState_.idle = eventType == NG::AccessibilityHoverEventType::EXIT;
}

void AccessibilityHoverManagerForThirdNG::SendThirdAccessibilityAsyncEvent(
    const AccessibilityEvent &accessibilityEvent, 
    const RefPtr<NG::FrameNode>& hostNode)
{}

bool AccessibilityHoverManagerForThirdNG::ActThirdAccessibilityFocus(
    int64_t elementId,
    const AccessibilityElementInfo& nodeInfo,
    const RefPtr<NG::FrameNode>& hostNode,
    const RefPtr<NG::PipelineContext>& context,
    bool isNeedClear)
{
    CHECK_NULL_RETURN(hostNode, false);
    RefPtr<NG::RenderContext> renderContext = nullptr;
    renderContext = hostNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    if (isNeedClear) {
        renderContext->UpdateAccessibilityFocus(false);
        return true;
    }

    auto [displayOffset, err] = hostNode->GetPaintRectGlobalOffsetWithTranslate();
    auto rectInScreen = nodeInfo.GetRectInScreen();
    auto left = rectInScreen.GetLeftTopXScreenPostion() - static_cast<int32_t>(displayOffset.GetX());
    auto right = rectInScreen.GetLeftTopYScreenPostion() - static_cast<int32_t>(displayOffset.GetY());
    auto width = rectInScreen.GetRightBottomXScreenPostion() - rectInScreen.GetLeftTopXScreenPostion();
    auto height = rectInScreen.GetRightBottomYScreenPostion() - rectInScreen.GetLeftTopYScreenPostion();
    NG::RectT<int32_t> rectInt { static_cast<int32_t>(left), static_cast<int32_t>(right),
        static_cast<int32_t>(width), static_cast<int32_t>(height) };
    
    renderContext->UpdateAccessibilityFocusRect(rectInt);
    renderContext->UpdateAccessibilityFocus(true, ACCESSIBILITY_FOCUS_WITHOUT_EVENT);
    return true;
}
} // namespace OHOS::Ace::Framework
