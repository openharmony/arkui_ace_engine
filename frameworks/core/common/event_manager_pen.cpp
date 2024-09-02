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

#include "core/common/event_manager.h"

#include "base/log/dump_log.h"
#include "base/thread/frame_trace_adapter.h"
#include "core/common/container.h"
#include "core/common/xcollie/xcollieInterface.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"

namespace OHOS::Ace {

void EventManager::PenHoverTest(
    const TouchEvent& event, const RefPtr<NG::FrameNode>& frameNode, TouchRestrict& touchRestrict)
{
    CHECK_NULL_VOID(frameNode);
    const NG::PointF point { event.x, event.y };
    TouchTestResult testResult;
    ResponseLinkResult responseLinkResult;
    frameNode->TouchTest(
        point, point, point, touchRestrict, testResult, event.id, responseLinkResult);
    SetResponseLinkRecognizers(testResult, responseLinkResult);
    UpdatePenHoverNode(event, testResult);
}

void EventManager::UpdatePenHoverNode(const TouchEvent& event, const TouchTestResult& testResult)
{
    HoverTestResult penHoverTestResult;
    for (const auto& result : testResult) {
        auto penHoverResult = AceType::DynamicCast<HoverEventTarget>(result);
        if (penHoverResult && penHoverResult->IsPenHoverTarget()) {
            penHoverTestResult.emplace_back(penHoverResult);
        }
    }

    if (event.type == TouchType::PROXIMITY_IN) {
        TAG_LOGI(AceLogTag::ACE_INPUTTRACKING, "pen proximity in hover event.");
        lastPenHoverResults_.clear();
        curPenHoverResults_ = std::move(penHoverTestResult);
    } else if (event.type == TouchType::PROXIMITY_OUT) {
        TAG_LOGI(AceLogTag::ACE_INPUTTRACKING, "pen proximity out hover event.");
        lastPenHoverResults_ = std::move(curPenHoverResults_);
        curPenHoverResults_.clear();
    } else {
        lastPenHoverResults_ = std::move(curPenHoverResults_);
        curPenHoverResults_ = std::move(penHoverTestResult);
    }
}

void EventManager::DispatchPenHoverEventNG(const TouchEvent& event)
{
    auto lastHoverEndNode = lastPenHoverResults_.begin();
    auto currHoverEndNode = curPenHoverResults_.begin();
    RefPtr<HoverEventTarget> lastHoverEndNodeTarget;
    uint32_t iterCountLast = 0;
    uint32_t iterCountCurr = 0;
    for (const auto& hoverResult : lastPenHoverResults_) {
        // get valid part of previous hover nodes while it's not in current hover nodes. Those nodes exit hover
        // there may have some nodes in curPenHoverResults_ but intercepted
        iterCountLast++;
        if (lastHoverEndNode != curPenHoverResults_.end()) {
            lastHoverEndNode++;
        }
        if (std::find(curPenHoverResults_.begin(), curPenHoverResults_.end(), hoverResult) ==
            curPenHoverResults_.end()) {
            hoverResult->HandlePenHoverEvent(false, event);
        }
        if ((iterCountLast >= lastPenHoverDispatchLength_) && (lastPenHoverDispatchLength_ != 0)) {
            lastHoverEndNodeTarget = hoverResult;
            break;
        }
    }
    lastPenHoverDispatchLength_ = 0;
    for (const auto& hoverResult : curPenHoverResults_) {
        // get valid part of current hover nodes while it's not in previous hover nodes. Those nodes are new hover
        // the valid part stops at first interception
        iterCountCurr++;
        if (currHoverEndNode != curPenHoverResults_.end()) {
            currHoverEndNode++;
        }
        if (std::find(lastPenHoverResults_.begin(), lastHoverEndNode, hoverResult) == lastHoverEndNode) {
            if (!hoverResult->HandlePenHoverEvent(true, event)) {
                lastPenHoverDispatchLength_ = iterCountCurr;
                break;
            }
        }
        if (hoverResult == lastHoverEndNodeTarget) {
            lastPenHoverDispatchLength_ = iterCountCurr;
            break;
        }
    }
    for (auto hoverResultIt = lastPenHoverResults_.begin(); hoverResultIt != lastHoverEndNode; ++hoverResultIt) {
        // there may have previous hover nodes in the invalid part of current hover nodes. Those nodes exit hover also
        if (std::find(currHoverEndNode, curPenHoverResults_.end(), *hoverResultIt) != curPenHoverResults_.end()) {
            (*hoverResultIt)->HandlePenHoverEvent(false, event);
        }
    }
}
} // namespace OHOS::Ace
