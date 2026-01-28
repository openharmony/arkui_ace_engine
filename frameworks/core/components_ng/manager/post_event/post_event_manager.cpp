/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/post_event/post_event_manager.h"

#include "core/common/stylus/stylus_detector_mgr.h"
#include "core/components_ng/event/error_reporter/general_interaction_error_reporter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t PASS_THROUGH_EVENT_ID = 100000;
}

bool PostEventManager::PostEvent(const RefPtr<NG::UINode>& uiNode, TouchEvent& touchEvent)
{
    if (!CheckPointValidity(touchEvent)) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW,
            "PostEvent event is invalid, possible reason is event timeStamp is the same as the previous event");
        return false;
    }
    CHECK_NULL_RETURN(uiNode, false);
    touchEvent.postEventNodeId = uiNode->GetId();
    auto result = false;
    switch (touchEvent.type) {
        case TouchType::DOWN:
            result = PostDownEvent(uiNode, touchEvent);
            break;
        case TouchType::MOVE:
            result = PostMoveEvent(uiNode, touchEvent);
            break;
        case TouchType::UP:
        case TouchType::CANCEL:
            result = PostUpEvent(uiNode, touchEvent);
            break;
        default:
            TAG_LOGE(AceLogTag::ACE_GESTURE, "dispatchEvent touchEvent type unkown");
            break;
    }
    return result;
}

bool PostEventManager::PostTouchEvent(const RefPtr<NG::UINode>& uiNode, TouchEvent&& touchEvent)
{
    CHECK_NULL_RETURN(uiNode, false);
    touchEvent.postEventNodeId = uiNode->GetId();
    touchEvent.id += PASS_THROUGH_EVENT_ID;
    auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(frameNode, false);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto eventManager = pipelineContext->GetEventManager();
    CHECK_NULL_RETURN(eventManager, false);
    touchEvent.passThrough = true;
    passThroughResult_ = false;
    if (!CheckTouchEvent(uiNode, touchEvent, eventManager->GetInstanceId())) {
        return false;
    }
    if (touchEvent.type != TouchType::MOVE) {
        postInputEventAction_.push_back({ uiNode, touchEvent });
    }
    // Check if there's a pending drag cancel operation
    if (!eventManager->IsDragCancelPending()) {
        // Normal touch event processing: dispatch the touch event through the pipeline context
        // for standard event handling and gesture recognition
        targetNode_ = frameNode;
        pipelineContext->OnTouchEvent(touchEvent, frameNode, false);
        targetNode_.Reset();
    } else {
        // Abnormal state handling: when drag cancel is pending, use specialized event validation
        // to check and clean up invalid touch events (e.g., UP/CANCEL without corresponding DOWN)
        eventManager->CheckUpEvent(touchEvent);
    }
    touchEvent.passThrough = false;
    if (touchEvent.type == TouchType::UP || touchEvent.type == TouchType::CANCEL) {
        ClearPostInputActions(uiNode, touchEvent.id);
    }
    return passThroughResult_;
}

bool PostEventManager::PostMouseEvent(const RefPtr<NG::UINode>& uiNode, MouseEvent&& mouseEvent)
{
    CHECK_NULL_RETURN(uiNode, false);
    mouseEvent.id += PASS_THROUGH_EVENT_ID;
    mouseEvent.postEventNodeId = uiNode->GetId();
    auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(frameNode, false);
    targetNode_ = frameNode;
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    mouseEvent.passThrough = true;
    passThroughResult_ = false;
    auto eventManager = pipelineContext->GetEventManager();
    CHECK_NULL_RETURN(eventManager, false);
    if (!CheckMouseEvent(uiNode, mouseEvent, eventManager->GetInstanceId())) {
        return false;
    }
    if (mouseEvent.action == MouseAction::PRESS || mouseEvent.action == MouseAction::RELEASE ||
        mouseEvent.action == MouseAction::CANCEL) {
        postMouseEventAction_.push_back({ uiNode, mouseEvent });
    }
    if (mouseEvent.action == MouseAction::CANCEL || mouseEvent.action == MouseAction::WINDOW_LEAVE) {
        postMouseEventWindowAction_.push_back({ uiNode, mouseEvent });
    }
    if (!eventManager->IsDragCancelPending()) {
        pipelineContext->OnMouseEvent(mouseEvent, frameNode);
    }
    mouseEvent.passThrough = false;
    targetNode_.Reset();
    if (mouseEvent.action == MouseAction::RELEASE || mouseEvent.action == MouseAction::CANCEL) {
        ClearPostInputActions(uiNode, mouseEvent.id, PostInputEventType::MOUSE);
    }
    if (mouseEvent.action == MouseAction::WINDOW_LEAVE || mouseEvent.action == MouseAction::CANCEL) {
        ClearMouseWindowAction(uiNode, mouseEvent.id);
    }
    return passThroughResult_;
}

bool PostEventManager::PostAxisEvent(const RefPtr<NG::UINode>& uiNode, AxisEvent&& axisEvent)
{
    CHECK_NULL_RETURN(uiNode, false);
    axisEvent.id += PASS_THROUGH_EVENT_ID;
    axisEvent.postEventNodeId = uiNode->GetId();
    auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(frameNode, false);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    axisEvent.passThrough = true;
    passThroughResult_ = false;
    auto eventManager = pipelineContext->GetEventManager();
    CHECK_NULL_RETURN(eventManager, false);
    if (!CheckAxisEvent(uiNode, axisEvent, eventManager->GetInstanceId())) {
        return false;
    }
    if (axisEvent.action != AxisAction::UPDATE) {
        postAxisEventAction_.push_back({ uiNode, axisEvent });
    }
    pipelineContext->OnAxisEvent(axisEvent, frameNode);
    axisEvent.passThrough = false;
    if (axisEvent.action == AxisAction::END || axisEvent.action == AxisAction::CANCEL) {
        ClearPostInputActions(uiNode, axisEvent.id, PostInputEventType::AXIS);
    }
    return passThroughResult_;
}

bool PostEventManager::CheckTouchEvent(
    const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent, const int32_t instanceId)
{
    CHECK_NULL_RETURN(targetNode, false);
    bool hasDown = false;
    bool hasUpOrCancel = false;
    for (const auto& item : postInputEventAction_) {
        if (item.targetNode != targetNode || item.touchEvent.id != touchEvent.id) {
            continue;
        }
        if (item.touchEvent.type == TouchType::DOWN) {
            hasDown = true;
        }
        if (item.touchEvent.type == TouchType::UP || item.touchEvent.type == TouchType::CANCEL) {
            hasUpOrCancel = true;
        }
    }
    switch (touchEvent.type) {
        case TouchType::DOWN:
            if (hasDown && !hasUpOrCancel) {
                TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW,
                    "CheckTouchEvent: duplicate DOWN event detected for id=%{public}d, dropping this event",
                    touchEvent.id);
                // todo, when get DOWN twice, falsifyCancel for touchEvent, return true.
                std::stringstream oss;
                oss << "id: " << touchEvent.id << ", TouchEvent receive DOWN event twice";
                GeneralInteractionErrorInfo errorInfo { GeneralInteractionErrorType::POST_EVENT_ERROR,
                    touchEvent.touchEventId, touchEvent.id, oss.str() };
                NG::GeneralInteractionErrorReporter::GetInstance().Submit(errorInfo, instanceId);
                return false;
            }
            if (hasUpOrCancel) {
                ClearPostInputActions(targetNode, touchEvent.id);
            }
            return true;
        case TouchType::UP:
        case TouchType::CANCEL:
            if (!hasDown) {
                std::stringstream oss;
                oss << "id: " << touchEvent.id << ", TouchEvent receive UP/CANCEL event without receive DOWN event";
                GeneralInteractionErrorInfo errorInfo { GeneralInteractionErrorType::POST_EVENT_ERROR,
                    touchEvent.touchEventId, touchEvent.id, oss.str() };
                NG::GeneralInteractionErrorReporter::GetInstance().Submit(errorInfo, instanceId);
            }
            return hasDown && !hasUpOrCancel;
        case TouchType::MOVE:
            return hasDown && !hasUpOrCancel;
        default:
            TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "CheckTouchEvent: unsupported touch type=%{public}d, id=%{public}d",
                static_cast<int>(touchEvent.type), touchEvent.id);
            return false;
    }
}

void PostEventManager::ClearPostInputActions(const RefPtr<NG::UINode>& targetNode, int32_t id, PostInputEventType type)
{
    switch (type) {
        case PostInputEventType::TOUCH:
            for (auto item = postInputEventAction_.begin(); item != postInputEventAction_.end();) {
                if (item->targetNode == targetNode && item->touchEvent.id == id) {
                    item = postInputEventAction_.erase(item);
                } else {
                    ++item;
                }
            }
            break;
        case PostInputEventType::MOUSE:
            for (auto item = postMouseEventAction_.begin(); item != postMouseEventAction_.end();) {
                if (item->targetNode == targetNode && item->mouseEvent.id == id) {
                    item = postMouseEventAction_.erase(item);
                } else {
                    ++item;
                }
            }
            break;
        case PostInputEventType::AXIS:
            for (auto item = postAxisEventAction_.begin(); item != postAxisEventAction_.end();) {
                if (item->targetNode == targetNode && item->axisEvent.id == id) {
                    item = postAxisEventAction_.erase(item);
                } else {
                    ++item;
                }
            }
            break;
        default:
            return;
    }
}

void PostEventManager::ClearMouseWindowAction(const RefPtr<NG::UINode>& targetNode, int32_t id)
{
    for (auto item = postMouseEventWindowAction_.begin(); item != postMouseEventWindowAction_.end();) {
        if (item->targetNode == targetNode && item->mouseEvent.id == id) {
            item = postMouseEventWindowAction_.erase(item);
        } else {
            ++item;
        }
    }
}

MouseEventState PostEventManager::CollectMouseEventState(const RefPtr<NG::UINode>& targetNode, int32_t id)
{
    MouseEventState state;
    for (const auto& item : postMouseEventAction_) {
        if (item.targetNode != targetNode || item.mouseEvent.id != id) {
            continue;
        }
        if (item.mouseEvent.action == MouseAction::PRESS) {
            state.hasPress = true;
        }
        if (item.mouseEvent.action == MouseAction::RELEASE || item.mouseEvent.action == MouseAction::CANCEL) {
            state.hasReleaseOrCancel = true;
        }
    }
    for (const auto& item : postMouseEventWindowAction_) {
        if (item.targetNode != targetNode || item.mouseEvent.id != id) {
            continue;
        }
        if (item.mouseEvent.action == MouseAction::WINDOW_ENTER) {
            state.hasWindowEnter = true;
        }
        if (item.mouseEvent.action == MouseAction::WINDOW_LEAVE || item.mouseEvent.action == MouseAction::CANCEL) {
            state.hasWindowLeaveOrCancel = true;
        }
    }
    return state;
}

bool PostEventManager::HandleMousePressEvent(
    const MouseEventState& state, const RefPtr<NG::UINode>& targetNode, int32_t id, const int32_t instanceId)
{
    if (state.hasPress && !state.hasReleaseOrCancel) {
        TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW,
            "CheckMouseEvent: duplicate PRESS event detected for id=%{public}d, dropping this event", id);
        // todo, when get PRESS twice, falsifyCancel for mouseEvent.
        std::stringstream oss;
        oss << "id: " << id << ", MouseEvent, receive PRESS event twice";
        GeneralInteractionErrorInfo errorInfo { GeneralInteractionErrorType::POST_EVENT_ERROR, -1,
            id, oss.str() };
        NG::GeneralInteractionErrorReporter::GetInstance().Submit(errorInfo, instanceId);
    }
    if (state.hasReleaseOrCancel) {
        ClearPostInputActions(targetNode, id, PostInputEventType::MOUSE);
    }
    return true;
}

bool PostEventManager::HandleMouseReleaseEvent(const MouseEventState& state, int32_t id)
{
    if (!state.hasPress) {
        TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW,
            "CheckMouseEvent: receive RELEASE/CANCEL event without receive PRESS event, id: %{public}d", id);
    }
    return state.hasPress && !state.hasReleaseOrCancel;
}

bool PostEventManager::HandleMouseWindowEnterEvent(
    const MouseEventState& state, const RefPtr<NG::UINode>& targetNode, int32_t id, const int32_t instanceId)
{
    if (state.hasWindowEnter && !state.hasWindowLeaveOrCancel) {
        TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW,
            "CheckMouseEvent: duplicate WindowEnter event detected for id=%{public}d, dropping this event", id);
        // todo, when get WINDOW_ENTER twice, falsifyCancel for mouseEvent.
        std::stringstream oss;
        oss << "id: " << id << ", MouseEvent, receive WindowEnter event twice";
        GeneralInteractionErrorInfo errorInfo { GeneralInteractionErrorType::POST_EVENT_ERROR, -1,
            id, oss.str() };
        NG::GeneralInteractionErrorReporter::GetInstance().Submit(errorInfo, instanceId);
    }
    if (state.hasReleaseOrCancel) {
        ClearMouseWindowAction(targetNode, id);
    }
    return true;
}

bool PostEventManager::HandleMouseWindowLeaveEvent(const MouseEventState& state, int32_t id)
{
    if (!state.hasWindowEnter) {
        TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW,
            "CheckMouseEvent: receive WindowLeave event without receive WindowEnter event, id: %{public}d", id);
    }
    return state.hasWindowEnter && !state.hasWindowLeaveOrCancel;
}

bool PostEventManager::PostDownEvent(const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent)
{
    CHECK_NULL_RETURN(targetNode, false);

    for (const auto& iter : postEventAction_) {
        if (iter.targetNode == targetNode && iter.touchEvent.type == TouchType::DOWN &&
            iter.touchEvent.id == touchEvent.id) {
            auto lastEventMap = lastEventMap_;
            auto lastItem = lastEventMap.find(touchEvent.id);
            if (lastItem != lastEventMap.end()) {
                auto event = lastItem->second.touchEvent;
                event.type = TouchType::CANCEL;
                PostUpEvent(lastItem->second.targetNode, event);
                break;
            }
            TAG_LOGW(
                AceLogTag::ACE_INPUTKEYFLOW, "PostEvent receive DOWN event twice, id is %{public}d", touchEvent.id);
            return false;
        }
    }
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto eventManager = pipelineContext->GetEventManager();
    CHECK_NULL_RETURN(eventManager, false);
    auto scalePoint = touchEvent.CreateScalePoint(pipelineContext->GetViewScale());
    eventManager->GetEventTreeRecord(EventTreeType::POST_EVENT).AddTouchPoint(scalePoint);
    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = touchEvent.sourceType;
    touchRestrict.touchEvent = touchEvent;
    touchRestrict.inputEventType = InputEventType::TOUCH_SCREEN;
    touchRestrict.touchTestType = EventTreeType::POST_EVENT;
    touchRestrict.sourceTool = touchEvent.sourceTool;
    auto result = eventManager->PostEventTouchTest(scalePoint, targetNode, touchRestrict);
    if (!result) {
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "PostDownEvent id: %{public}d touch test result is empty", touchEvent.id);
        return false;
    }
    if (StylusDetectorMgr::GetInstance()->IsNeedInterceptedTouchEvent(
        scalePoint, eventManager->postEventTouchTestResults_)) {
        eventManager->ClearTouchTestTargetForPenStylus(scalePoint);
        return true;
    }
    HandlePostEvent(targetNode, touchEvent);
    return true;
}

bool PostEventManager::PostMoveEvent(const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent)
{
    CHECK_NULL_RETURN(targetNode, false);

    if (!HaveReceiveDownEvent(targetNode, touchEvent.id) || HaveReceiveUpOrCancelEvent(targetNode, touchEvent.id)) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW,
            "PostMoveEvent id: %{public}d doesn't receive down event or has receive up or cancel event", touchEvent.id);
        return false;
    }

    HandlePostEvent(targetNode, touchEvent);
    return true;
}

bool PostEventManager::PostUpEvent(const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent)
{
    CHECK_NULL_RETURN(targetNode, false);

    if (!HaveReceiveDownEvent(targetNode, touchEvent.id) || HaveReceiveUpOrCancelEvent(targetNode, touchEvent.id)) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW,
            "PostUpEvent id: %{public}d doesn't receive down event or has receive up or cancel event", touchEvent.id);
        return false;
    }

    HandlePostEvent(targetNode, touchEvent);
    return true;
}

void PostEventManager::HandlePostEvent(const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent)
{
    // push dispatchAction and store
    PostEventAction postEventAction;
    postEventAction.targetNode = targetNode;
    postEventAction.touchEvent = touchEvent;
    lastEventMap_[touchEvent.id] = postEventAction;
    postEventAction_.push_back(postEventAction);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto eventManager = pipelineContext->GetEventManager();
    if (touchEvent.type != TouchType::DOWN && touchEvent.type != TouchType::MOVE) {
        eventManager->GetEventTreeRecord(EventTreeType::POST_EVENT).AddTouchPoint(touchEvent);
    }
    eventManager->PostEventFlushTouchEventEnd(touchEvent);
    eventManager->PostEventDispatchTouchEvent(touchEvent);
    // when receive UP event, clear DispatchAction which is same targetNode and same id
    CheckAndClearPostEventAction(targetNode, touchEvent.id);
}

void PostEventManager::CheckAndClearPostEventAction(const RefPtr<NG::UINode>& targetNode, int32_t id)
{
    bool receiveDown = false;
    bool receiveUp = false;
    for (const auto& iter : postEventAction_) {
        if (iter.targetNode == targetNode && iter.touchEvent.id == id) {
            if (iter.touchEvent.type == TouchType::DOWN) {
                receiveDown = true;
            } else if ((iter.touchEvent.type == TouchType::UP || iter.touchEvent.type == TouchType::CANCEL) &&
                       receiveDown) {
                receiveUp = true;
            }
        }
    }
    if (receiveUp) {
        for (auto iter = postEventAction_.begin(); iter != postEventAction_.end();) {
            if (iter->targetNode == targetNode && iter->touchEvent.id == id) {
                iter = postEventAction_.erase(iter);
            } else {
                ++iter;
            }
        }
        lastEventMap_.erase(id);
    }
}

bool PostEventManager::HaveReceiveDownEvent(const RefPtr<NG::UINode>& targetNode, int32_t id)
{
    return std::any_of(postEventAction_.begin(), postEventAction_.end(), [targetNode, id](const auto& actionItem) {
        return actionItem.targetNode == targetNode && actionItem.touchEvent.type == TouchType::DOWN &&
               actionItem.touchEvent.id == id;
    });
}

bool PostEventManager::HaveReceiveUpOrCancelEvent(const RefPtr<NG::UINode>& targetNode, int32_t id)
{
    return std::any_of(postEventAction_.begin(), postEventAction_.end(), [targetNode, id](const auto& actionItem) {
        return actionItem.targetNode == targetNode &&
               (actionItem.touchEvent.type == TouchType::UP || actionItem.touchEvent.type == TouchType::CANCEL) &&
               actionItem.touchEvent.id == id;
    });
}

bool PostEventManager::CheckPointValidity(const TouchEvent& touchEvent)
{
    return !std::any_of(postEventAction_.begin(), postEventAction_.end(), [touchEvent](const auto& actionItem) {
        return actionItem.touchEvent.id == touchEvent.id && actionItem.touchEvent.time == touchEvent.time;
    });
}

void PostEventManager::SetPassThroughResult(bool passThroughResult)
{
    passThroughResult_ = passThroughResult;
}

RefPtr<FrameNode> PostEventManager::GetPostTargetNode()
{
    return targetNode_.Upgrade();
}

bool PostEventManager::CheckMouseEvent(
    const RefPtr<NG::UINode>& targetNode, const MouseEvent& mouseEvent, const int32_t instanceId)
{
    CHECK_NULL_RETURN(targetNode, false);

    auto state = CollectMouseEventState(targetNode, mouseEvent.id);

    switch (mouseEvent.action) {
        case MouseAction::PRESS:
            return HandleMousePressEvent(state, targetNode, mouseEvent.id, instanceId);
        case MouseAction::MOVE:
            return true;
        case MouseAction::RELEASE:
        case MouseAction::CANCEL:
            return HandleMouseReleaseEvent(state, mouseEvent.id);
        case MouseAction::WINDOW_ENTER:
            return HandleMouseWindowEnterEvent(state, targetNode, mouseEvent.id, instanceId);
        case MouseAction::WINDOW_LEAVE:
            return HandleMouseWindowLeaveEvent(state, mouseEvent.id);
        default:
            TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW,
                "CheckMouseEvent: unsupported mouseEvent action=%{public}d, id=%{public}d",
                static_cast<int>(mouseEvent.action), mouseEvent.id);
            return false;
    }
}

bool PostEventManager::CheckAxisEvent(
    const RefPtr<NG::UINode>& targetNode, const AxisEvent& axisEvent, const int32_t instanceId)
{
    CHECK_NULL_RETURN(targetNode, false);
    bool hasBegin = false;
    bool hasEndOrCancel = false;

    for (const auto& item : postAxisEventAction_) {
        if (item.targetNode != targetNode || item.axisEvent.id != axisEvent.id) {
            continue;
        }
        if (item.axisEvent.action == AxisAction::BEGIN) {
            hasBegin = true;
        }
        if (item.axisEvent.action == AxisAction::END || item.axisEvent.action == AxisAction::CANCEL) {
            hasEndOrCancel = true;
        }
    }

    switch (axisEvent.action) {
        case AxisAction::BEGIN:
            if (hasBegin && !hasEndOrCancel) {
                TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW,
                    "CheckAxisEvent: duplicate BEGIN event detected for id=%{public}d, dropping this event",
                    axisEvent.id);
                // todo, when get BEGIN twice, falsifyCancel for axisEvent.
                std::stringstream oss;
                oss << "id: " << axisEvent.id << ", AxisEvent, receive BEGIN event twice";
                GeneralInteractionErrorInfo errorInfo { GeneralInteractionErrorType::POST_EVENT_ERROR, axisEvent.id, -1,
                    oss.str() };
                NG::GeneralInteractionErrorReporter::GetInstance().Submit(errorInfo, instanceId);
            }
            if (hasEndOrCancel) {
                ClearPostInputActions(targetNode, axisEvent.id, PostInputEventType::AXIS);
            }
            return true;
        case AxisAction::UPDATE:
            return hasBegin && !hasEndOrCancel;
        case AxisAction::END:
        case AxisAction::CANCEL:
            if (!hasBegin) {
                TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW,
                    "CheckAxisEvent: receive END/CANCEL event without receive BEGIN event, axisId: %{public}d",
                    axisEvent.id);
            }
            return hasBegin && !hasEndOrCancel;
        default:
            TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "CheckAxisEvent: unsupported axis action=%{public}d, id=%{public}d",
                static_cast<int>(axisEvent.action), axisEvent.id);
            return false;
    }
}
} // namespace OHOS::Ace::NG
