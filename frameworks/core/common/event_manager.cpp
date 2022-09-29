/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "base/geometry/ng/point_t.h"
#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/event/key_event.h"
#include "core/gestures/gesture_referee.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

void EventManager::TouchTest(const TouchEvent& touchPoint, const RefPtr<RenderNode>& renderNode,
    const TouchRestrict& touchRestrict, const Offset& offset, float viewScale, bool needAppend)
{
    ContainerScope scope(instanceId_);

    ACE_FUNCTION_TRACE();
    if (!renderNode) {
        LOGW("renderNode is null.");
        return;
    }
    // first clean.
    referee_->CleanGestureScope(touchPoint.id);
    // collect
    TouchTestResult hitTestResult;
    const Point point { touchPoint.x, touchPoint.y, touchPoint.sourceType };
    // For root node, the parent local point is the same as global point.
    renderNode->TouchTest(point, point, touchRestrict, hitTestResult);
    if (needAppend) {
#ifdef OHOS_STANDARD_SYSTEM
        for (auto entry = hitTestResult.begin(); entry != hitTestResult.end(); ++entry) {
            if ((*entry)) {
                (*entry)->SetSubPipelineGlobalOffset(offset, viewScale);
            }
        }
#endif
        TouchTestResult prevHitTestResult = touchTestResults_[touchPoint.id];
        hitTestResult.splice(hitTestResult.end(), prevHitTestResult);
    }
    touchTestResults_[touchPoint.id] = std::move(hitTestResult);
}

void EventManager::TouchTest(const TouchEvent& touchPoint, const RefPtr<NG::FrameNode>& frameNode,
    const TouchRestrict& touchRestrict, bool needAppend)
{
    ContainerScope scope(instanceId_);

    ACE_FUNCTION_TRACE();
    if (!frameNode) {
        LOGW("renderNode is null.");
        return;
    }
    // first clean.
    refereeNG_->CleanGestureScope(touchPoint.id);
    // collect
    TouchTestResult hitTestResult;
    const NG::PointF point { touchPoint.x, touchPoint.y };
    // For root node, the parent local point is the same as global point.
    frameNode->TouchTest(point, point, touchRestrict, hitTestResult);
    if (needAppend) {
        TouchTestResult prevHitTestResult = touchTestResults_[touchPoint.id];
        hitTestResult.splice(hitTestResult.end(), prevHitTestResult);
    }
    touchTestResults_[touchPoint.id] = std::move(hitTestResult);
}

void EventManager::HandleGlobalEvent(const TouchEvent& touchPoint, const RefPtr<TextOverlayManager>& textOverlayManager)
{
    if (touchPoint.type != TouchType::DOWN) {
        return;
    }
    const Point point { touchPoint.x, touchPoint.y, touchPoint.sourceType };
    if (!textOverlayManager) {
        return;
    }
    auto textOverlayBase = textOverlayManager->GetTextOverlayBase();
    if (!textOverlayBase) {
        return;
    }
    auto targetNode = textOverlayManager->GetTargetNode();
    if (!targetNode) {
        return;
    }
    for (auto& rect : textOverlayManager->GetTextOverlayRect()) {
        if (rect.IsInRegion(point)) {
            inSelectedRect_ = true;
        }
    }
    for (auto& rect : textOverlayBase->GetSelectedRect()) {
        if (rect.IsInRegion(point)) {
            inSelectedRect_ = true;
        }
    }
    if (!inSelectedRect_) {
        textOverlayManager->PopTextOverlay();
        textOverlayBase->ChangeSelection(0, 0);
        textOverlayBase->MarkIsOverlayShowed(false);
        targetNode->MarkNeedRender();
    }
    inSelectedRect_ = false;
}

void EventManager::HandleOutOfRectCallback(const Point& point, std::vector<RectCallback>& rectCallbackList)
{
    for (auto iter = rectCallbackList.begin(); iter != rectCallbackList.end();) {
        auto rectCallback = *iter;
        auto rectGetCallback = rectCallback.rectGetCallback;
        if (!rectGetCallback) {
            ++iter;
            continue;
        }
        std::vector<Rect> rectList;
        rectGetCallback(rectList);
        if (std::any_of(rectList.begin(), rectList.end(),
            [point](const Rect& rect) { return rect.IsInRegion(point); })) {
            ++iter;
            continue;
        }
        for (const auto& rect : rectList) {
            LOGI("Point(%{public}f, %{public}f) out of Rect-[%{public}f, %{public}f, %{public}f, %{public}f]",
                point.GetX(), point.GetY(), rect.Left(), rect.Right(), rect.Top(), rect.Bottom());
        }
        if (point.GetSourceType() == SourceType::TOUCH) {
            if (!rectCallback.touchCallback) {
                ++iter;
                continue;
            }
            rectCallback.touchCallback();
        } else if (point.GetSourceType() == SourceType::MOUSE) {
            if (!rectCallback.mouseCallback) {
                ++iter;
                continue;
            }
            rectCallback.mouseCallback();
        }
        iter = rectCallbackList.erase(iter);
    }
}

void EventManager::TouchTest(
    const AxisEvent& event, const RefPtr<RenderNode>& renderNode, const TouchRestrict& touchRestrict)
{
    ContainerScope scope(instanceId_);

    ACE_FUNCTION_TRACE();
    if (!renderNode) {
        LOGW("renderNode is null.");
        return;
    }
    // collect
    const Point point { event.x, event.y, event.sourceType };
    // For root node, the parent local point is the same as global point.
    renderNode->TouchTest(point, point, touchRestrict, axisTouchTestResult_);
}

void EventManager::FlushTouchEventsBegin(const std::list<TouchEvent>& touchEvents)
{
    for (auto iter = touchEvents.begin(); iter != touchEvents.end(); ++iter) {
        const auto result = touchTestResults_.find((*iter).id);
        if (result != touchTestResults_.end()) {
            for (auto entry = result->second.rbegin(); entry != result->second.rend(); ++entry) {
                (*entry)->OnFlushTouchEventsBegin();
            }
        }
    }
}

void EventManager::FlushTouchEventsEnd(const std::list<TouchEvent>& touchEvents)
{
    for (auto iter = touchEvents.begin(); iter != touchEvents.end(); ++iter) {
        const auto result = touchTestResults_.find((*iter).id);
        if (result != touchTestResults_.end()) {
            for (auto entry = result->second.rbegin(); entry != result->second.rend(); ++entry) {
                (*entry)->OnFlushTouchEventsEnd();
            }
        }
    }
}

bool EventManager::DispatchTouchEvent(const TouchEvent& point)
{
    ContainerScope scope(instanceId_);

    ACE_FUNCTION_TRACE();
    const auto iter = touchTestResults_.find(point.id);
    if (iter != touchTestResults_.end()) {
        bool dispatchSuccess = true;
        for (auto entry = iter->second.rbegin(); entry != iter->second.rend(); ++entry) {
            if (!(*entry)->DispatchMultiContainerEvent(point)) {
                dispatchSuccess = false;
                break;
            }
        }
        // If one gesture recognizer has already been won, other gesture recognizers will still be affected by
        // the event, each recognizer needs to filter the extra events by itself.
        if (dispatchSuccess) {
            for (const auto& entry : iter->second) {
                if (!entry->HandleMultiContainerEvent(point)) {
                    break;
                }
            }
        }

        if (point.type == TouchType::UP || point.type == TouchType::CANCEL) {
            referee_->CleanGestureScope(point.id);
            refereeNG_->CleanGestureScope(point.id);
            touchTestResults_.erase(point.id);
        }

        return true;
    }
    LOGI("the %{public}d touch test result does not exist!", point.id);
    return false;
}

bool EventManager::DispatchTouchEvent(const AxisEvent& event)
{
    ContainerScope scope(instanceId_);

    ACE_FUNCTION_TRACE();
    for (const auto& entry : axisTouchTestResult_) {
        if (!entry->HandleEvent(event)) {
            break;
        }
    }
    if (event.action == AxisAction::END || event.action == AxisAction::NONE) {
        axisTouchTestResult_.clear();
    }
    return true;
}

bool EventManager::DispatchTabIndexEvent(
    const KeyEvent& event, const RefPtr<FocusNode>& focusNode, const RefPtr<FocusGroup>& curPage)
{
    CHECK_NULL_RETURN(focusNode, false);
    CHECK_NULL_RETURN(curPage, false);
    LOGD("The key code is %{public}d, the key action is %{public}d, the repeat time is %{public}d.", event.code,
        event.action, event.repeatTime);
    if (focusNode->HandleFocusByTabIndex(event, curPage)) {
        LOGI("Tab index focus system handled this event");
        return true;
    }
    return false;
}

bool EventManager::DispatchKeyEvent(const KeyEvent& event, const RefPtr<FocusNode>& focusNode)
{
    CHECK_NULL_RETURN(focusNode, false);
    LOGD("The key code is %{public}d, the key action is %{public}d, the repeat time is %{public}d.", event.code,
        event.action, event.repeatTime);
    if (focusNode->HandleKeyEvent(event)) {
        LOGI("Default focus system handled this event");
        return true;
    }
    LOGI("Use platform to handle this event");
    return false;
}

bool EventManager::DispatchTabIndexEventNG(
    const KeyEvent& event, const RefPtr<NG::FrameNode>& focusNode, const RefPtr<NG::FrameNode>& curPage)
{
    CHECK_NULL_RETURN(focusNode, false);
    CHECK_NULL_RETURN(curPage, false);
    LOGD("The key code is %{public}d, the key action is %{public}d, the repeat time is %{public}d.", event.code,
        event.action, event.repeatTime);
    auto focusNodeHub = focusNode->GetFocusHub();
    CHECK_NULL_RETURN(focusNodeHub, false);
    auto curPageFocusHub = curPage->GetFocusHub();
    CHECK_NULL_RETURN(curPageFocusHub, false);
    if (focusNodeHub->HandleFocusByTabIndex(event, curPageFocusHub)) {
        LOGI("Tab index focus system handled this event");
        return true;
    }
    return false;
}

bool EventManager::DispatchKeyEventNG(const KeyEvent& event, const RefPtr<NG::FrameNode>& focusNode)
{
    CHECK_NULL_RETURN(focusNode, false);
    LOGD("The key code is %{public}d, the key action is %{public}d, the repeat time is %{public}d.", event.code,
        event.action, event.repeatTime);
    auto focusNodeHub = focusNode->GetFocusHub();
    CHECK_NULL_RETURN(focusNodeHub, false);
    if (focusNodeHub->HandleKeyEvent(event)) {
        LOGI("Default focus system handled this event");
        return true;
    }
    LOGI("Use platform to handle this event");
    return false;
}

void EventManager::MouseTest(const MouseEvent& event, const RefPtr<RenderNode>& renderNode)
{
    if (!renderNode) {
        LOGW("renderNode is null.");
        return;
    }
    const Point point { event.x, event.y };
    MouseHoverTestList hitTestResult;
    WeakPtr<RenderNode> hoverNode = nullptr;
    renderNode->MouseDetect(point, point, hitTestResult, hoverNode);
    if (hitTestResult.empty()) {
        LOGD("mouse hover test result is empty");
    }
    if (event.action == MouseAction::WINDOW_LEAVE) {
        mouseHoverTestResultsPre_ = std::move(mouseHoverTestResults_);
        mouseHoverTestResults_.clear();
    } else if (event.action == MouseAction::WINDOW_ENTER) {
        mouseHoverTestResultsPre_.clear();
        mouseHoverTestResults_ = std::move(hitTestResult);
    } else {
        mouseHoverTestResultsPre_ = std::move(mouseHoverTestResults_);
        mouseHoverTestResults_ = std::move(hitTestResult);
    }
    mouseHoverNodePre_ = mouseHoverNode_;
    mouseHoverNode_ = hoverNode;
    LOGI("MouseDetect hit test last/new result size = %{public}zu/%{public}zu", mouseHoverTestResultsPre_.size(),
        mouseHoverTestResults_.size());
}

bool EventManager::DispatchMouseEvent(const MouseEvent& event)
{
    if (event.action == MouseAction::PRESS || event.action == MouseAction::RELEASE ||
        event.action == MouseAction::MOVE) {
        LOGD("RenderBox::HandleMouseEvent, button is %{public}d, action is %{public}d", event.button, event.action);
        for (const auto& wp : mouseHoverTestResults_) {
            auto hoverNode = wp.Upgrade();
            if (hoverNode) {
                if (hoverNode->HandleMouseEvent(event)) {
                    LOGI("Do HandleMouseEvent. Dispatch node: %{public}s", AceType::TypeName(hoverNode));
                    break;
                }
            }
        }
        return true;
    }
    return false;
}

void EventManager::DispatchMouseHoverAnimation(const MouseEvent& event)
{
    auto hoverNodeCur = mouseHoverNode_.Upgrade();
    auto hoverNodePre = mouseHoverNodePre_.Upgrade();
    if (event.action == MouseAction::PRESS) {
        if (hoverNodeCur) {
            hoverNodeCur->AnimateMouseHoverExit();
        }
    } else if (event.action == MouseAction::RELEASE) {
        if (hoverNodeCur) {
            hoverNodeCur->AnimateMouseHoverEnter();
        }
    } else if (event.button == MouseButton::NONE_BUTTON && event.action == MouseAction::MOVE) {
        if (hoverNodeCur != hoverNodePre) {
            if (hoverNodeCur) {
                hoverNodeCur->AnimateMouseHoverEnter();
            }
            if (hoverNodePre) {
                hoverNodePre->AnimateMouseHoverExit();
            }
        }
    } else if (event.action == MouseAction::WINDOW_ENTER) {
        if (hoverNodeCur) {
            hoverNodeCur->AnimateMouseHoverEnter();
        }
    } else if (event.action == MouseAction::WINDOW_LEAVE) {
        if (hoverNodeCur) {
            hoverNodeCur->AnimateMouseHoverExit();
        }
    }
}

bool EventManager::DispatchMouseHoverEvent(const MouseEvent& event)
{
    for (const auto& wp : mouseHoverTestResultsPre_) {
        // get all previous hover nodes while it's not in current hover nodes. Those nodes exit hover
        auto it = std::find(mouseHoverTestResults_.begin(), mouseHoverTestResults_.end(), wp);
        if (it == mouseHoverTestResults_.end()) {
            auto hoverNode = wp.Upgrade();
            if (hoverNode) {
                hoverNode->HandleMouseHoverEvent(MouseState::NONE);
            }
        }
    }
    for (const auto& wp : mouseHoverTestResults_) {
        // get all current hover nodes while it's not in previous hover nodes. Those nodes are new hover
        auto it = std::find(mouseHoverTestResultsPre_.begin(), mouseHoverTestResultsPre_.end(), wp);
        if (it == mouseHoverTestResultsPre_.end()) {
            auto hoverNode = wp.Upgrade();
            if (hoverNode) {
                hoverNode->HandleMouseHoverEvent(MouseState::HOVER);
            }
        }
    }
    return true;
}

void EventManager::MouseTest(const MouseEvent& event, const RefPtr<NG::FrameNode>& frameNode)
{
    if (!frameNode) {
        LOGW("renderNode is null.");
        return;
    }
    const NG::PointF point { event.x, event.y };
    MouseTestResult mouseTestResult;
    MouseTestResult hoverTestResult;
    RefPtr<NG::FrameNode> hoverNode = nullptr;
    frameNode->MouseTest(point, point, mouseTestResult, hoverTestResult, hoverNode);
    if (mouseTestResult.empty()) {
        LOGD("mouse hover test result is empty");
    }
    if (event.action == MouseAction::WINDOW_LEAVE) {
        lastHoverTestResults_ = std::move(currHoverTestResults_);
        currHoverTestResults_.clear();
    } else if (event.action == MouseAction::WINDOW_ENTER) {
        lastHoverTestResults_.clear();
        currHoverTestResults_ = std::move(hoverTestResult);
    } else {
        lastHoverTestResults_ = std::move(currHoverTestResults_);
        currHoverTestResults_ = std::move(hoverTestResult);
    }
    currMouseTestResults_ = std::move(mouseTestResult);
    lastHoverNode_ = currHoverNode_;
    currHoverNode_ = WeakClaim(AceType::RawPtr(hoverNode));
    LOGI("MouseTest hit test last/new result size = %{public}zu/%{public}zu.",
        lastHoverTestResults_.size(), currHoverTestResults_.size());
}

bool EventManager::DispatchMouseEventNG(const MouseEvent& event)
{
    if (event.action == MouseAction::PRESS || event.action == MouseAction::RELEASE ||
        event.action == MouseAction::MOVE) {
        LOGD("RenderBox::HandleMouseEvent, button is %{public}d, action is %{public}d", event.button, event.action);
        for (const auto& mouseTarget : currMouseTestResults_) {
            if (mouseTarget) {
                if (mouseTarget->HandleMouseEvent(event)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void EventManager::DispatchMouseHoverAnimationNG(const MouseEvent& event)
{
    auto hoverNodeCur = currHoverNode_.Upgrade();
    auto hoverNodePre = lastHoverNode_.Upgrade();
    if (event.action == MouseAction::PRESS) {
        if (hoverNodeCur) {
            hoverNodeCur->AnimateHoverEffect(false);
        }
    } else if (event.action == MouseAction::RELEASE) {
        if (hoverNodeCur) {
            hoverNodeCur->AnimateHoverEffect(true);
        }
    } else if (event.button == MouseButton::NONE_BUTTON && event.action == MouseAction::MOVE) {
        if (hoverNodeCur != hoverNodePre) {
            if (hoverNodeCur) {
                hoverNodeCur->AnimateHoverEffect(true);
            }
            if (hoverNodePre) {
                hoverNodePre->AnimateHoverEffect(false);
            }
        }
    } else if (event.action == MouseAction::WINDOW_ENTER) {
        if (hoverNodeCur) {
            hoverNodeCur->AnimateHoverEffect(true);
        }
    } else if (event.action == MouseAction::WINDOW_LEAVE) {
        if (hoverNodeCur) {
            hoverNodeCur->AnimateHoverEffect(false);
        }
    }
}

bool EventManager::DispatchMouseHoverEventNG(const MouseEvent& event)
{
    for (const auto& hoverResult : lastHoverTestResults_) {
        // get all previous hover nodes while it's not in current hover nodes. Those nodes exit hover
        auto it = std::find(currHoverTestResults_.begin(), currHoverTestResults_.end(), hoverResult);
        if (it == currHoverTestResults_.end()) {
            hoverResult->HandleHoverEvent(false);
        }
    }
    for (const auto& hoverResult : currHoverTestResults_) {
        // get all current hover nodes while it's not in previous hover nodes. Those nodes are new hover
        auto it = std::find(lastHoverTestResults_.begin(), lastHoverTestResults_.end(), hoverResult);
        if (it == lastHoverTestResults_.end()) {
            hoverResult->HandleHoverEvent(true);
        }
    }
    return true;
}

void EventManager::AxisTest(const AxisEvent& event, const RefPtr<RenderNode>& renderNode)
{
    if (!renderNode) {
        LOGW("renderNode is null.");
        return;
    }
    const Point point { event.x, event.y };
    WeakPtr<RenderNode> axisNode = nullptr;
    renderNode->AxisDetect(point, point, axisNode, event.GetDirection());
    axisNode_ = axisNode;
    LOGI("Current axis node is %{public}s", AceType::TypeName(axisNode_.Upgrade()));
}

bool EventManager::DispatchAxisEvent(const AxisEvent& event)
{
    auto responseNode = axisNode_.Upgrade();
    if (responseNode) {
        responseNode->HandleAxisEvent(event);
    }
    return true;
}

void EventManager::AxisTest(const AxisEvent& event, const RefPtr<NG::FrameNode>& frameNode)
{
    if (!frameNode) {
        LOGW("renderNode is null.");
        return;
    }
    const NG::PointF point { event.x, event.y };
    frameNode->AxisTest(point, point, axisTestResults_);
}

bool EventManager::DispatchAxisEventNG(const AxisEvent& event)
{
    if (event.horizontalAxis == 0 && event.verticalAxis == 0 && event.pinchAxisScale == 0) {
        return false;
    }
    LOGD("DispatchAxisEventNG, action is %{public}d, axis is %{public}f / %{public}f / %{public}f", event.action,
        event.horizontalAxis, event.verticalAxis, event.pinchAxisScale);
    for (const auto& axisTarget : axisTestResults_) {
        if (axisTarget && axisTarget->HandleAxisEvent(event)) {
            return true;
        }
    }
    return true;
}

bool EventManager::DispatchRotationEvent(
    const RotationEvent& event, const RefPtr<RenderNode>& renderNode, const RefPtr<RenderNode>& requestFocusNode)
{
    if (!renderNode) {
        LOGW("renderNode is null.");
        return false;
    }

    if (requestFocusNode && renderNode->RotationMatchTest(requestFocusNode)) {
        LOGD("RotationMatchTest: dispatch rotation to request node.");
        return requestFocusNode->RotationTestForward(event);
    } else {
        LOGD("RotationMatchTest: dispatch rotation to stack render node.");
        return renderNode->RotationTest(event);
    }
}

void EventManager::ClearResults()
{
    touchTestResults_.clear();
    mouseTestResults_.clear();
}

EventManager::EventManager()
{
    LOGD("EventManger Constructor.");
    referee_ = AceType::MakeRefPtr<GestureReferee>();
    refereeNG_ = AceType::MakeRefPtr<NG::GestureReferee>();
}

} // namespace OHOS::Ace
