/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
#include "base/thread/frame_trace_adapter.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/event/ace_events.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_referee.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {
constexpr uint8_t KEYS_MAX_VALUE = 3;
const std::string SHORT_CUT_VALUE_X = "X";
const std::string SHORT_CUT_VALUE_Y = "Y";
const std::string SHORT_CUT_VALUE_Z = "Z";
const std::string SHORT_CUT_VALUE_A = "A";
const std::string SHORT_CUT_VALUE_C = "C";
const std::string SHORT_CUT_VALUE_V = "V";
enum class CtrlKeysBit {
    CTRL = 1,
    SHIFT = 2,
    ALT = 4,
};

void EventManager::TouchTest(const TouchEvent& touchPoint, const RefPtr<RenderNode>& renderNode,
    const TouchRestrict& touchRestrict, const Offset& offset, float viewScale, bool needAppend)
{
    ContainerScope scope(instanceId_);

    ACE_FUNCTION_TRACE();
    CHECK_NULL_VOID(renderNode);
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
    const TouchRestrict& touchRestrict, const Offset& offset, float viewScale, bool needAppend)
{
    ContainerScope scope(instanceId_);

    ACE_FUNCTION_TRACE();
    CHECK_NULL_VOID(frameNode);
    // collect
    TouchTestResult hitTestResult;
    const NG::PointF point { touchPoint.x, touchPoint.y };
    if (refereeNG_->CheckSourceTypeChange(touchPoint.sourceType)) {
        refereeNG_->CleanAll(true);
    }
    if (refereeNG_->QueryAllDone(touchPoint.id)) {
        refereeNG_->CleanGestureScope(touchPoint.id);
    }
    if (frameNode->HaveSecurityComponent()) {
        std::vector<NG::RectF> rect;
        frameNode->CheckSecurityComponentStatus(rect);
    }
    if (!needAppend) {
        NG::NGGestureRecognizer::ResetGlobalTransCfg();
    }
    // For root node, the parent local point is the same as global point.
    frameNode->TouchTest(point, point, touchRestrict, hitTestResult, touchPoint.id);
    if (needAppend) {
#ifdef OHOS_STANDARD_SYSTEM
        for (const auto& entry : hitTestResult) {
            if (entry) {
                entry->SetSubPipelineGlobalOffset(offset, viewScale);
            }
        }
#endif
        TouchTestResult prevHitTestResult = touchTestResults_[touchPoint.id];
        hitTestResult.splice(hitTestResult.end(), prevHitTestResult);
    }
    touchTestResults_[touchPoint.id] = std::move(hitTestResult);
}

void EventManager::TouchTest(
    const AxisEvent& event, const RefPtr<NG::FrameNode>& frameNode, const TouchRestrict& touchRestrict)
{
    ContainerScope scope(instanceId_);

    if (refereeNG_->CheckSourceTypeChange(event.sourceType, true)) {
        refereeNG_->CleanAll(true);
    }
    ACE_FUNCTION_TRACE();
    CHECK_NULL_VOID(frameNode);
    // collect
    const NG::PointF point { event.x, event.y };
    if (frameNode->HaveSecurityComponent()) {
        std::vector<NG::RectF> rect;
        frameNode->CheckSecurityComponentStatus(rect);
    }
    // For root node, the parent local point is the same as global point.
    TouchTestResult hitTestResult;
    frameNode->TouchTest(point, point, touchRestrict, hitTestResult, event.id);
    axisTouchTestResults_[event.id] = std::move(hitTestResult);
}

void EventManager::HandleGlobalEvent(const TouchEvent& touchPoint, const RefPtr<TextOverlayManager>& textOverlayManager)
{
    if (touchPoint.type != TouchType::DOWN) {
        return;
    }
    auto coordinateOffset = textOverlayManager->GetCoordinateOffset();
    const Point point { touchPoint.x - coordinateOffset.GetX(), touchPoint.y - coordinateOffset.GetY(),
        touchPoint.sourceType };
    CHECK_NULL_VOID_NOLOG(textOverlayManager);
    auto textOverlayBase = textOverlayManager->GetTextOverlayBase();
    CHECK_NULL_VOID_NOLOG(textOverlayBase);
    auto targetNode = textOverlayManager->GetTargetNode();
    CHECK_NULL_VOID_NOLOG(targetNode);
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

void EventManager::HandleGlobalEventNG(const TouchEvent& touchPoint,
    const RefPtr<NG::SelectOverlayManager>& selectOverlayManager, const NG::OffsetF& rootOffset)
{
    CHECK_NULL_VOID_NOLOG(selectOverlayManager);
    if (touchPoint.type == TouchType::DOWN &&
        touchTestResults_.find(touchPoint.id) != touchTestResults_.end()) {
        std::vector<std::string> touchTestIds;
        const auto& resultList = touchTestResults_[touchPoint.id];
        for (const auto& result : resultList) {
            auto eventTarget = result->GetEventTarget();
            if (eventTarget.has_value()) {
                touchTestIds.emplace_back(eventTarget.value().id);
            }
        }
        selectOverlayManager->SetOnTouchTestResults(touchTestIds);
    }
    selectOverlayManager->HandleGlobalEvent(touchPoint, rootOffset);
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
        if (std::any_of(
                rectList.begin(), rectList.end(), [point](const Rect& rect) { return rect.IsInRegion(point); })) {
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
    CHECK_NULL_VOID(renderNode);
    // collect
    const Point point { event.x, event.y, event.sourceType };
    // For root node, the parent local point is the same as global point.
    TouchTestResult hitTestResult;
    renderNode->TouchTest(point, point, touchRestrict, hitTestResult);
    axisTouchTestResults_[event.id] = std::move(hitTestResult);
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

bool EventManager::DispatchTouchEvent(const TouchEvent& event)
{
    ContainerScope scope(instanceId_);
    TouchEvent point = event;
#ifdef ENABLE_DRAG_FRAMEWORK
    if (point.type == TouchType::PULL_MOVE) {
        point.type = TouchType::MOVE;
    }
    if (point.type == TouchType::PULL_UP) {
        point.type = TouchType::UP;
    }
#endif // ENABLE_DRAG_FRAMEWORK
    ACE_FUNCTION_TRACE();
    const auto iter = touchTestResults_.find(point.id);
    if (iter == touchTestResults_.end()) {
        LOGI("the %{public}d touch test result does not exist!", point.id);
        return false;
    }

    if (point.type == TouchType::DOWN) {
        // first collect gesture into gesture referee.
        if (Container::IsCurrentUseNewPipeline()) {
            refereeNG_->AddGestureToScope(point.id, iter->second);
        }
    }

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
        if (Container::IsCurrentUseNewPipeline()) {
            // Need update here: onTouch/Recognizer need update
            bool isStopTouchEvent = false;
            for (const auto& entry : iter->second) {
                auto recognizer = AceType::DynamicCast<NG::NGGestureRecognizer>(entry);
                if (recognizer) {
                    entry->HandleMultiContainerEvent(point);
                }
                if (!recognizer && !isStopTouchEvent) {
                    isStopTouchEvent = !entry->HandleMultiContainerEvent(point);
                }
            }
        } else {
            for (const auto& entry : iter->second) {
                if (!entry->HandleMultiContainerEvent(point)) {
                    break;
                }
            }
        }
    }

    if (point.type == TouchType::UP || point.type == TouchType::CANCEL) {
        FrameTraceAdapter* ft = FrameTraceAdapter::GetInstance();
        if (ft != nullptr) {
            ft->SetFrameTraceLimit();
        }
        refereeNG_->CleanGestureScope(point.id);
        referee_->CleanGestureScope(point.id);
        touchTestResults_.erase(point.id);
    }

    return true;
}

bool EventManager::DispatchTouchEvent(const AxisEvent& event)
{
    ContainerScope scope(instanceId_);

    const auto curResultIter = axisTouchTestResults_.find(event.id);
    if (curResultIter == axisTouchTestResults_.end()) {
        LOGI("the %{public}d axis test result does not exist!", event.id);
        return false;
    }
    if (event.action == AxisAction::BEGIN) {
        // first collect gesture into gesture referee.
        if (Container::IsCurrentUseNewPipeline()) {
            if (refereeNG_) {
                refereeNG_->AddGestureToScope(event.id, curResultIter->second);
            }
        }
    }

    ACE_FUNCTION_TRACE();
    for (const auto& entry : curResultIter->second) {
        if (!entry->HandleEvent(event)) {
            break;
        }
    }
    if (event.action == AxisAction::END || event.action == AxisAction::NONE || event.action == AxisAction::CANCEL) {
        if (Container::IsCurrentUseNewPipeline()) {
            if (refereeNG_) {
                refereeNG_->CleanGestureScope(event.id);
            }
        }
        axisTouchTestResults_.erase(event.id);
    }
    return true;
}

bool EventManager::DispatchTabIndexEvent(
    const KeyEvent& event, const RefPtr<FocusNode>& focusNode, const RefPtr<FocusGroup>& mainNode)
{
    LOGD("The key code is %{public}d, the key action is %{public}d, the repeat time is %{public}d.", event.code,
        event.action, event.repeatTime);
    CHECK_NULL_RETURN(focusNode, false);
    CHECK_NULL_RETURN(mainNode, false);
    if (focusNode->HandleFocusByTabIndex(event, mainNode)) {
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
    LOGD("Use platform to handle this event");
    return false;
}

bool EventManager::DispatchTabIndexEventNG(
    const KeyEvent& event, const RefPtr<NG::FrameNode>& focusNode, const RefPtr<NG::FrameNode>& mainNode)
{
    LOGD("The key code is %{public}d, the key action is %{public}d, the repeat time is %{public}d.", event.code,
        event.action, event.repeatTime);
    CHECK_NULL_RETURN(focusNode, false);
    CHECK_NULL_RETURN(mainNode, false);
    auto focusNodeHub = focusNode->GetFocusHub();
    CHECK_NULL_RETURN(focusNodeHub, false);
    auto mainNodeHub = mainNode->GetFocusHub();
    CHECK_NULL_RETURN(mainNodeHub, false);
    if (focusNodeHub->HandleFocusByTabIndex(event, mainNodeHub)) {
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
    LOGD("Use platform to handle this event");
    return false;
}

void EventManager::MouseTest(const MouseEvent& event, const RefPtr<RenderNode>& renderNode)
{
    CHECK_NULL_VOID(renderNode);
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

void EventManager::LogPrintMouseTest()
{
#ifdef ACE_DEBUG_LOG
    if (!SystemProperties::GetDebugEnabled()) {
        return;
    }
    if (currMouseTestResults_.empty()) {
        LOGD("Mouse test onMouse result is empty.");
    } else {
        for (const auto& result : currMouseTestResults_) {
            LOGD("Mouse test onMouse result: %{public}s/%{public}d.", result->GetNodeName().c_str(),
                result->GetNodeId());
        }
    }
    if (lastHoverTestResults_.empty()) {
        LOGD("Mouse test onHover last result is empty.");
    } else {
        for (const auto& result : lastHoverTestResults_) {
            LOGD("Mouse test onHover last result: %{public}s/%{public}d.", result->GetNodeName().c_str(),
                result->GetNodeId());
        }
    }
    if (currHoverTestResults_.empty()) {
        LOGD("Mouse test onHover current result is empty.");
    } else {
        for (const auto& result : currHoverTestResults_) {
            LOGD("Mouse test onHover current result: %{public}s/%{public}d.", result->GetNodeName().c_str(),
                result->GetNodeId());
        }
    }
    auto lastNode = lastHoverNode_.Upgrade();
    auto currNode = currHoverNode_.Upgrade();
    LOGD("Mouse test last/current hoverEffect node: %{public}s/%{public}d / %{public}s/%{public}d",
        lastNode ? lastNode->GetTag().c_str() : "NULL", lastNode ? lastNode->GetId() : -1,
        currNode ? currNode->GetTag().c_str() : "NULL", currNode ? currNode->GetId() : -1);
#endif
}

void EventManager::MouseTest(
    const MouseEvent& event, const RefPtr<NG::FrameNode>& frameNode, const TouchRestrict& touchRestrict)
{
    LOGD("Mouse test start. Mouse event is (%{public}f,%{public}f), button: %{public}d, action: %{public}d", event.x,
        event.y, event.button, event.action);
    CHECK_NULL_VOID(frameNode);
    const NG::PointF point { event.x, event.y };
    TouchTestResult testResult;
    if (frameNode->HaveSecurityComponent()) {
        std::vector<NG::RectF> rect;
        frameNode->CheckSecurityComponentStatus(rect);
    }
    frameNode->TouchTest(point, point, touchRestrict, testResult, event.GetId());
    if (testResult.empty()) {
        LOGD("mouse hover test result is empty");
    }
    currMouseTestResults_.clear();
    HoverTestResult hoverTestResult;
    WeakPtr<NG::FrameNode> hoverNode = nullptr;
    for (const auto& result : testResult) {
        auto mouseResult = AceType::DynamicCast<MouseEventTarget>(result);
        if (mouseResult) {
            currMouseTestResults_.emplace_back(mouseResult);
        }
        auto hoverResult = AceType::DynamicCast<HoverEventTarget>(result);
        if (hoverResult) {
            hoverTestResult.emplace_back(hoverResult);
        }
        if (!hoverNode.Upgrade()) {
            auto hoverEffectResult = AceType::DynamicCast<HoverEffectTarget>(result);
            if (hoverEffectResult) {
                hoverNode = hoverEffectResult->GetHoverNode();
            }
        }
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
    lastHoverNode_ = currHoverNode_;
    currHoverNode_ = hoverNode;
    LogPrintMouseTest();
    LOGD("Mouse test end.");
}

bool EventManager::DispatchMouseEventNG(const MouseEvent& event)
{
    LOGD("DispatchMouseEventNG: button is %{public}d, action is %{public}d.", event.button, event.action);
    if (event.action == MouseAction::PRESS || event.action == MouseAction::RELEASE ||
        event.action == MouseAction::MOVE || event.action == MouseAction::WINDOW_ENTER ||
        event.action == MouseAction::WINDOW_LEAVE) {
        MouseTestResult handledResults;
        handledResults.clear();
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, false);
        if ((event.button == MouseButton::LEFT_BUTTON && !container->IsScenceBoardWindow()) ||
            (event.button == MouseButton::LEFT_BUTTON && container->IsScenceBoardWindow() &&
            event.pullAction != MouseAction::PULL_UP && event.pullAction != MouseAction::PULL_MOVE)) {
            for (const auto& mouseTarget : pressMouseTestResults_) {
                if (mouseTarget) {
                    handledResults.emplace_back(mouseTarget);
                    if (mouseTarget->HandleMouseEvent(event)) {
                        break;
                    }
                }
            }
            if (event.action == MouseAction::PRESS) {
                pressMouseTestResults_ = currMouseTestResults_;
            } else if (event.action == MouseAction::RELEASE) {
                DoMouseActionRelease();
            }
        }
        if (event.pullAction == MouseAction::PULL_UP) {
            DoMouseActionRelease();
        }
        for (const auto& mouseTarget : currMouseTestResults_) {
            if (mouseTarget &&
                std::find(handledResults.begin(), handledResults.end(), mouseTarget) == handledResults.end()) {
                if (mouseTarget->HandleMouseEvent(event)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void EventManager::DoMouseActionRelease()
{
    pressMouseTestResults_.clear();
}

void EventManager::DispatchMouseHoverAnimationNG(const MouseEvent& event)
{
    LOGD("DispatchMouseHoverAnimationNG: button is %{public}d, action is %{public}d.", event.button, event.action);
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
    LOGD("DispatchMouseHoverEventNG: button is %{public}d, action is %{public}d.", event.button, event.action);
    auto lastHoverEndNode = lastHoverTestResults_.begin();
    auto currHoverEndNode = currHoverTestResults_.begin();
    RefPtr<HoverEventTarget> lastHoverEndNodeTarget;
    uint32_t iterCountLast = 0;
    uint32_t iterCountCurr = 0;
    for (const auto& hoverResult : lastHoverTestResults_) {
        // get valid part of previous hover nodes while it's not in current hover nodes. Those nodes exit hover
        // there may have some nodes in currHoverTestResults_ but intercepted
        iterCountLast++;
        if (lastHoverEndNode != currHoverTestResults_.end()) {
            lastHoverEndNode++;
        }
        if (std::find(currHoverTestResults_.begin(), currHoverTestResults_.end(), hoverResult) ==
            currHoverTestResults_.end()) {
            hoverResult->HandleHoverEvent(false, event);
        }
        if ((iterCountLast >= lastHoverDispatchLength_) && (lastHoverDispatchLength_ != 0)) {
            lastHoverEndNodeTarget = hoverResult;
            break;
        }
    }
    lastHoverDispatchLength_ = 0;
    for (const auto& hoverResult : currHoverTestResults_) {
        // get valid part of current hover nodes while it's not in previous hover nodes. Those nodes are new hover
        // the valid part stops at first interception
        iterCountCurr++;
        if (currHoverEndNode != currHoverTestResults_.end()) {
            currHoverEndNode++;
        }
        if (std::find(lastHoverTestResults_.begin(), lastHoverEndNode, hoverResult) == lastHoverEndNode) {
            if (!hoverResult->HandleHoverEvent(true, event)) {
                lastHoverDispatchLength_ = iterCountCurr;
                break;
            }
        }
        if (hoverResult == lastHoverEndNodeTarget) {
            lastHoverDispatchLength_ = iterCountCurr;
            break;
        }
    }
    for (auto hoverResultIt = lastHoverTestResults_.begin(); hoverResultIt != lastHoverEndNode; ++hoverResultIt) {
        // there may have previous hover nodes in the invalid part of current hover nodes. Those nodes exit hover also
        if (std::find(currHoverEndNode, currHoverTestResults_.end(), *hoverResultIt) != currHoverTestResults_.end()) {
            (*hoverResultIt)->HandleHoverEvent(false, event);
        }
    }
    return true;
}

void EventManager::AxisTest(const AxisEvent& event, const RefPtr<RenderNode>& renderNode)
{
    CHECK_NULL_VOID(renderNode);
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
    CHECK_NULL_VOID(frameNode);
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
    CHECK_NULL_RETURN(renderNode, false);
    if (requestFocusNode && renderNode->RotationMatchTest(requestFocusNode)) {
        LOGD("RotationMatchTest: dispatch rotation to request node.");
        return requestFocusNode->RotationTestForward(event);
    } else {
        LOGD("RotationMatchTest: dispatch rotation to stack render node.");
        return renderNode->RotationTest(event);
    }
}

void EventManager::AddKeyboardShortcutNode(const WeakPtr<NG::FrameNode>& node)
{
    auto frameNode = node.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto iter = keyboardShortcutNode_.begin();
    while (iter != keyboardShortcutNode_.end()) {
        auto keyboardShortcutNode = (*iter).Upgrade();
        if (!keyboardShortcutNode) {
            keyboardShortcutNode_.erase(iter++);
            continue;
        }
        if (keyboardShortcutNode->GetId() == frameNode->GetId()) {
            return;
        }
        ++iter;
    }
    keyboardShortcutNode_.emplace_back(node);
}

uint8_t EventManager::GetKeyboardShortcutKeys(const std::vector<ModifierKey>& keys)
{
    uint8_t keyValue = 0;
    uint8_t ctrlTimes = 0;
    uint8_t shiftTimes = 0;
    uint8_t altTimes = 0;
    if (keys.size() > KEYS_MAX_VALUE) {
        return 0;
    }
    for (const auto& key : keys) {
        switch (static_cast<uint8_t>(key)) {
            case static_cast<uint8_t>(ModifierKey::CTRL): {
                keyValue |= static_cast<uint8_t>(CtrlKeysBit::CTRL);
                ++ctrlTimes;
                break;
            }
            case static_cast<uint8_t>(ModifierKey::SHIFT): {
                keyValue |= static_cast<uint8_t>(CtrlKeysBit::SHIFT);
                ++shiftTimes;
                break;
            }
            case static_cast<uint8_t>(ModifierKey::ALT): {
                keyValue |= static_cast<uint8_t>(CtrlKeysBit::ALT);
                ++altTimes;
                break;
            }
            default:
                keyValue |= 0;
        }
    }
    if (ctrlTimes > 1 || shiftTimes > 1 || altTimes > 1) {
        return 0;
    }
    return keyValue;
}

bool EventManager::IsSystemKeyboardShortcut(const std::string& value, uint8_t keys)
{
    if (!(keys ^ static_cast<uint8_t>(CtrlKeysBit::CTRL)) && value == SHORT_CUT_VALUE_C) {
        return true;
    }
    if (!(keys ^ static_cast<uint8_t>(CtrlKeysBit::CTRL)) && value == SHORT_CUT_VALUE_A) {
        return true;
    }
    if (!(keys ^ static_cast<uint8_t>(CtrlKeysBit::CTRL)) && value == SHORT_CUT_VALUE_V) {
        return true;
    }
    if (!(keys ^ static_cast<uint8_t>(CtrlKeysBit::CTRL)) && value == SHORT_CUT_VALUE_X) {
        return true;
    }
    if (!(keys ^ static_cast<uint8_t>(CtrlKeysBit::CTRL)) && value == SHORT_CUT_VALUE_Y) {
        return true;
    }
    if (!(keys ^ static_cast<uint8_t>(CtrlKeysBit::CTRL)) && value == SHORT_CUT_VALUE_Z) {
        return true;
    }
    if (!(keys ^ (static_cast<uint8_t>(CtrlKeysBit::CTRL) + static_cast<uint8_t>(CtrlKeysBit::SHIFT))) &&
        value == SHORT_CUT_VALUE_Z) {
        return true;
    }
    return false;
}

bool EventManager::IsSameKeyboardShortcutNode(const std::string& value, uint8_t keys)
{
    if (IsSystemKeyboardShortcut(value, keys)) {
        return true;
    }
    for (auto& weakNode : keyboardShortcutNode_) {
        auto frameNode = weakNode.Upgrade();
        if (!frameNode) {
            continue;
        }
        auto eventHub = frameNode->GetEventHub<NG::EventHub>();
        if (!eventHub) {
            continue;
        }
        auto keyboardShortcuts = eventHub->GetKeyboardShortcut();
        for (auto& keyboardShortcut : keyboardShortcuts) {
            LOGI("IsSameKeyboardShortcutNode keys = %{public}d value = %{public}s", keyboardShortcut.keys,
                keyboardShortcut.value.c_str());
            if (keyboardShortcut.value.find(value) != std::string::npos && keyboardShortcut.keys == keys) {
                return true;
            }
        }
    }
    return false;
}

void AddKeyboardShortcutSingleKey(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    uint8_t index = 0;
    std::vector<KeyCode> keyCode1;
    std::vector<KeyCode> keyCode2;
    if (keys & static_cast<uint8_t>(CtrlKeysBit::CTRL)) {
        keyCode1.emplace_back(KeyCode::KEY_CTRL_LEFT);
        keyCode2.emplace_back(KeyCode::KEY_CTRL_RIGHT);
        permutation.emplace_back(++index);
    }
    if (keys & static_cast<uint8_t>(CtrlKeysBit::SHIFT)) {
        keyCode1.emplace_back(KeyCode::KEY_SHIFT_LEFT);
        keyCode2.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
        permutation.emplace_back(++index);
    }
    if (keys & static_cast<uint8_t>(CtrlKeysBit::ALT)) {
        keyCode1.emplace_back(KeyCode::KEY_ALT_LEFT);
        keyCode2.emplace_back(KeyCode::KEY_ALT_RIGHT);
        permutation.emplace_back(++index);
    }
    keyCodes.emplace_back(keyCode1);
    keyCodes.emplace_back(keyCode2);
}

void AddKeyboardShortcutDoubleKeysWithCtrlShift(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    uint8_t index = 0;
    std::vector<KeyCode> keyCode1;
    std::vector<KeyCode> keyCode2;
    std::vector<KeyCode> keyCode3;
    std::vector<KeyCode> keyCode4;

    keyCode1.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode3.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    keyCode4.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    permutation.emplace_back(++index);

    keyCode1.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    keyCode3.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode4.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    permutation.emplace_back(++index);

    keyCodes.emplace_back(keyCode1);
    keyCodes.emplace_back(keyCode2);
    keyCodes.emplace_back(keyCode3);
    keyCodes.emplace_back(keyCode4);
}

void AddKeyboardShortcutDoubleKeysWithCtrlAlt(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    uint8_t index = 0;
    std::vector<KeyCode> keyCode1;
    std::vector<KeyCode> keyCode2;
    std::vector<KeyCode> keyCode3;
    std::vector<KeyCode> keyCode4;

    keyCode1.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode3.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    keyCode4.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    permutation.emplace_back(++index);

    keyCode1.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_ALT_RIGHT);
    keyCode3.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode4.emplace_back(KeyCode::KEY_ALT_RIGHT);
    permutation.emplace_back(++index);

    keyCodes.emplace_back(keyCode1);
    keyCodes.emplace_back(keyCode2);
    keyCodes.emplace_back(keyCode3);
    keyCodes.emplace_back(keyCode4);
}

void AddKeyboardShortcutDoubleKeysWithShiftAlt(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    uint8_t index = 0;
    std::vector<KeyCode> keyCode1;
    std::vector<KeyCode> keyCode2;
    std::vector<KeyCode> keyCode3;
    std::vector<KeyCode> keyCode4;

    keyCode1.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode3.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    keyCode4.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    permutation.emplace_back(++index);

    keyCode1.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_ALT_RIGHT);
    keyCode3.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode4.emplace_back(KeyCode::KEY_ALT_RIGHT);
    permutation.emplace_back(++index);

    keyCodes.emplace_back(keyCode1);
    keyCodes.emplace_back(keyCode2);
    keyCodes.emplace_back(keyCode3);
    keyCodes.emplace_back(keyCode4);
}

void AddKeyboardShortcutDoubleKeys(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    if (keys == static_cast<uint8_t>(CtrlKeysBit::CTRL) + static_cast<uint8_t>(CtrlKeysBit::SHIFT)) {
        AddKeyboardShortcutDoubleKeysWithCtrlShift(keys, keyCodes, permutation);
    }
    if (keys == static_cast<uint8_t>(CtrlKeysBit::CTRL) + static_cast<uint8_t>(CtrlKeysBit::ALT)) {
        AddKeyboardShortcutDoubleKeysWithCtrlAlt(keys, keyCodes, permutation);
    }
    if (keys == static_cast<uint8_t>(CtrlKeysBit::SHIFT) + static_cast<uint8_t>(CtrlKeysBit::ALT)) {
        AddKeyboardShortcutDoubleKeysWithShiftAlt(keys, keyCodes, permutation);
    }
}

void AddKeyboardShortcutTripleKeys(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    uint8_t index = 0;
    std::vector<KeyCode> keyCode1;
    std::vector<KeyCode> keyCode2;
    std::vector<KeyCode> keyCode3;
    std::vector<KeyCode> keyCode4;
    std::vector<KeyCode> keyCode5;
    std::vector<KeyCode> keyCode6;
    std::vector<KeyCode> keyCode7;
    std::vector<KeyCode> keyCode8;

    keyCode1.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode3.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode4.emplace_back(KeyCode::KEY_CTRL_LEFT);
    keyCode5.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    keyCode6.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    keyCode7.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    keyCode8.emplace_back(KeyCode::KEY_CTRL_RIGHT);
    permutation.emplace_back(++index);

    keyCode1.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode3.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    keyCode4.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    keyCode5.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode6.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyCode7.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    keyCode8.emplace_back(KeyCode::KEY_SHIFT_RIGHT);
    permutation.emplace_back(++index);

    keyCode1.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode2.emplace_back(KeyCode::KEY_ALT_RIGHT);
    keyCode3.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode4.emplace_back(KeyCode::KEY_ALT_RIGHT);
    keyCode5.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode6.emplace_back(KeyCode::KEY_ALT_RIGHT);
    keyCode7.emplace_back(KeyCode::KEY_ALT_LEFT);
    keyCode8.emplace_back(KeyCode::KEY_ALT_RIGHT);
    permutation.emplace_back(++index);

    keyCodes.emplace_back(keyCode1);
    keyCodes.emplace_back(keyCode2);
    keyCodes.emplace_back(keyCode3);
    keyCodes.emplace_back(keyCode4);
    keyCodes.emplace_back(keyCode5);
    keyCodes.emplace_back(keyCode6);
    keyCodes.emplace_back(keyCode7);
    keyCodes.emplace_back(keyCode8);
}

void AddKeyboardShortcutKeys(
    uint8_t keys, std::vector<std::vector<KeyCode>>& keyCodes, std::vector<uint8_t>& permutation)
{
    // single FunctionKey
    if (keys == 0) {
        keyCodes.emplace_back(std::vector<KeyCode>());
    }
    // single key
    if (keys == static_cast<uint8_t>(CtrlKeysBit::CTRL) || keys == static_cast<uint8_t>(CtrlKeysBit::SHIFT) ||
        keys == static_cast<uint8_t>(CtrlKeysBit::ALT)) {
        LOGI("AddKeyboardShortcutKeys single key");
        AddKeyboardShortcutSingleKey(keys, keyCodes, permutation);
    }
    // double keys
    if (keys == static_cast<uint8_t>(CtrlKeysBit::CTRL) + static_cast<uint8_t>(CtrlKeysBit::SHIFT) ||
        keys == static_cast<uint8_t>(CtrlKeysBit::CTRL) + static_cast<uint8_t>(CtrlKeysBit::ALT) ||
        keys == static_cast<uint8_t>(CtrlKeysBit::SHIFT) + static_cast<uint8_t>(CtrlKeysBit::ALT)) {
        LOGI("AddKeyboardShortcutKeys double keys");
        AddKeyboardShortcutDoubleKeys(keys, keyCodes, permutation);
    }
    // triple keys
    if (keys == static_cast<uint8_t>(CtrlKeysBit::CTRL) + static_cast<uint8_t>(CtrlKeysBit::SHIFT) +
                    static_cast<uint8_t>(CtrlKeysBit::ALT)) {
        LOGI("AddKeyboardShortcutKeys triple keys");
        AddKeyboardShortcutTripleKeys(keys, keyCodes, permutation);
    }
}

void TriggerKeyboardShortcut(const KeyEvent& event, const std::vector<NG::KeyboardShortcut>& keyboardShortcuts,
    const WeakPtr<NG::FrameNode>& node, const RefPtr<NG::EventHub>& eventHub)
{
    CHECK_NULL_VOID(eventHub);
    for (auto& keyboardShortcut : keyboardShortcuts) {
        if (keyboardShortcut.value.empty()) {
            continue;
        }

        std::vector<std::vector<KeyCode>> keyCodes;
        std::vector<uint8_t> permutation;
        AddKeyboardShortcutKeys(keyboardShortcut.keys, keyCodes, permutation);
        if (event.ConvertInputCodeToString().find(keyboardShortcut.value) == std::string::npos) {
            continue;
        }
        // Handle left and right the keys problem.
        std::vector<uint8_t> perm;
        for (auto& keyCode : keyCodes) {
            perm.assign(permutation.begin(), permutation.end());
            // Handle the keys order problem.
            do {
                keyCode.emplace_back(event.code);
                if (!event.IsKey(keyCode)) {
                    keyCode.pop_back();
                    std::next_permutation(keyCode.begin(), keyCode.end());
                    continue;
                }

                if (keyboardShortcut.onKeyboardShortcutAction) {
                    keyboardShortcut.onKeyboardShortcutAction();
                    LOGI("TriggerKeyboardShortcut action done.");
                } else {
                    auto gestureEventHub = eventHub->GetGestureEventHub();
                    if (gestureEventHub && gestureEventHub->IsClickable()) {
                        gestureEventHub->KeyBoardShortCutClick(event, node);
                        LOGI("TriggerKeyboardShortcut click done.");
                    }
                }
                keyCode.pop_back();
                std::next_permutation(keyCode.begin(), keyCode.end());
            } while (std::next_permutation(perm.begin(), perm.end()));
            perm.clear();
        }
        keyCodes.clear();
        permutation.clear();
    }
}

void EventManager::DispatchKeyboardShortcut(const KeyEvent& event)
{
    LOGD("EventManager: The key code is %{public}d, the key action is %{public}d.", event.code, event.action);
    if (event.action != KeyAction::DOWN) {
        return;
    }
    for (auto& node : keyboardShortcutNode_) {
        auto frameNode = node.Upgrade();
        if (!frameNode || !(frameNode->IsActive())) {
            continue;
        }
        auto eventHub = frameNode->GetEventHub<NG::EventHub>();
        if (!eventHub || !(eventHub->IsEnabled())) {
            continue;
        }

        auto keyboardShortcuts = eventHub->GetKeyboardShortcut();
        TriggerKeyboardShortcut(event, keyboardShortcuts, node, eventHub);
    }
}

void EventManager::DelKeyboardShortcutNode(int32_t nodeId)
{
    auto iter = keyboardShortcutNode_.begin();
    while (iter != keyboardShortcutNode_.end()) {
        auto frameNode = (*iter).Upgrade();
        if (!frameNode) {
            keyboardShortcutNode_.erase(iter++);
            continue;
        }
        if (frameNode->GetId() == nodeId) {
            keyboardShortcutNode_.erase(iter);
            break;
        }
        ++iter;
    }
}

void EventManager::ClearResults()
{
    touchTestResults_.clear();
    mouseTestResults_.clear();
    axisTouchTestResults_.clear();
    keyboardShortcutNode_.clear();
}

EventManager::EventManager()
{
    LOGD("EventManger Constructor.");
    refereeNG_ = AceType::MakeRefPtr<NG::GestureReferee>();
    referee_ = AceType::MakeRefPtr<GestureReferee>();

    auto callback = [weak = WeakClaim(this)](size_t touchId) -> bool {
        auto eventManager = weak.Upgrade();
        CHECK_NULL_RETURN(eventManager, false);
        auto refereeNG = eventManager->refereeNG_;
        CHECK_NULL_RETURN(refereeNG, false);
        return refereeNG->HasGestureAccepted(touchId);
    };
    referee_->SetQueryStateFunc(std::move(callback));

    auto cleanReferee = [weak = WeakClaim(this)](size_t touchId) -> void {
        auto eventManager = weak.Upgrade();
        CHECK_NULL_VOID(eventManager);
        auto referee = eventManager->referee_;
        CHECK_NULL_VOID(referee);
        auto gestureScope = referee->GetGestureScope();
        const auto iter = gestureScope.find(touchId);
        if (iter == gestureScope.end()) {
            return;
        }

        auto highRecognizers = iter->second.GetHighRecognizers();
        auto lowRecognizers = iter->second.GetLowRecognizers();
        auto parallelRecognizers = iter->second.GetParallelRecognizers();

        for (const auto& weak : highRecognizers) {
            auto gesture = weak.Upgrade();
            if (gesture) {
                gesture->OnRejected(touchId);
            }
        }

        for (const auto& weak : lowRecognizers) {
            auto gesture = weak.Upgrade();
            if (gesture) {
                gesture->OnRejected(touchId);
            }
        }

        for (const auto& weak : parallelRecognizers) {
            auto gesture = weak.Upgrade();
            if (gesture) {
                gesture->OnRejected(touchId);
            }
        }
    };
    refereeNG_->SetQueryStateFunc(std::move(cleanReferee));
}

} // namespace OHOS::Ace
