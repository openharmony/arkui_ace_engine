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
#include "base/log/dump_log.h"
#include "base/memory/ace_type.h"
#include "base/thread/frame_trace_adapter.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/recognizers/recognizer_group.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/event/ace_events.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_referee.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {
constexpr uint8_t KEYS_MAX_VALUE = 3;
constexpr int32_t DUMP_START_NUMBER = 4;
constexpr int64_t EVENT_CLEAR_DURATION = 1000;
constexpr int64_t TRANSLATE_NS_TO_MS = 1000000;
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

struct TouchTestResultInfo {
    int32_t nodeId = 0;
    std::string tag;
    std::string inspectorId;
    std::string frameRect;
    int32_t depth = 0;
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
    TAG_LOGI(AceLogTag::ACE_INPUTTRACKING,
        "TouchEvent do TouchTest in EventManager: "
        "eventInfo: id:%{public}d, pointX=%{public}f pointY=%{public}f "
        "touchPoint referee state:%{public}d, needAppend:%{public}d",
        touchPoint.id, touchPoint.x, touchPoint.y, (int)(refereeNG_->QueryAllDone(touchPoint.id)), (int)needAppend);
    ContainerScope scope(instanceId_);

    ACE_FUNCTION_TRACE();
    CHECK_NULL_VOID(frameNode);
    // collect
    TouchTestResult hitTestResult;
    const NG::PointF point { touchPoint.x, touchPoint.y };
    refereeNG_->CheckSourceTypeChange(touchPoint.sourceType);
    if (refereeNG_->QueryAllDone(touchPoint.id)) {
        refereeNG_->CleanGestureScope(touchPoint.id);
        if (touchTestResults_.empty() && refereeNG_->QueryAllDone()) {
            innerEventWin_ = false;
            responseCtrl_->Reset();
            refereeNG_->CleanAll();
        }
    }
    if (downFingerIds_.empty() && refereeNG_->QueryAllDone()) {
        refereeNG_->ForceCleanGestureReferee();
        CleanGestureEventHub();
    }
    if (frameNode->HaveSecurityComponent()) {
        std::vector<NG::RectF> rect;
        frameNode->CheckSecurityComponentStatus(rect);
    }
    if (!needAppend && touchTestResults_.empty()) {
        NG::NGGestureRecognizer::ResetGlobalTransCfg();
    }
    // For root node, the parent local point is the same as global point.
    frameNode->TouchTest(point, point, point, touchRestrict, hitTestResult, touchPoint.id);
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
    std::list<RefPtr<NG::NGGestureRecognizer>> hitTestRecognizers;
    for (const auto& item : hitTestResult) {
        auto recognizer = AceType::DynamicCast<NG::NGGestureRecognizer>(item);
        if (recognizer) {
            hitTestRecognizers.emplace_back(recognizer);
        }
    }
    SetHittedFrameNode(hitTestRecognizers);
    touchTestResults_[touchPoint.id] = std::move(hitTestResult);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    std::map<int32_t, TouchTestResultInfo> touchTestResultInfo;
    for (const auto& item : touchTestResults_[touchPoint.id]) {
        auto node = item->GetAttachedNode().Upgrade();
        if (!node) {
            continue;
        }
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(node);
        if (!frameNode) {
            continue;
        }
        touchTestResultInfo[frameNode->GetId()] = { frameNode->GetId(), frameNode->GetTag(),
            frameNode->GetInspectorIdValue(""), frameNode->GetGeometryNode()->GetFrameRect().ToString(),
            frameNode->GetDepth() };
    }
    std::string resultInfo = std::string("fingerId: ").append(std::to_string(touchPoint.id));
    for (const auto& item : touchTestResultInfo) {
        resultInfo.append(" id: ")
            .append(std::to_string(item.first))
            .append(", tag: ")
            .append(item.second.tag)
            .append(", inspectorId: ")
            .append(item.second.inspectorId)
            .append(", frameRect: ")
            .append(item.second.frameRect)
            .append(", depth: ")
            .append(std::to_string(item.second.depth))
            .append(".");
    }
    TAG_LOGI(AceLogTag::ACE_INPUTTRACKING, "Touch test hitted node info: %{public}s", resultInfo.c_str());
    if (touchTestResultInfo.empty()) {
        TAG_LOGW(AceLogTag::ACE_INPUTTRACKING, "Touch test result is empty.");
        std::list<std::pair<int32_t, std::string>> dumpList;
        eventTree_.Dump(dumpList, 0, DUMP_START_NUMBER);
        for (auto& item : dumpList) {
            TAG_LOGI(AceLogTag::ACE_INPUTTRACKING, "EventTreeDumpInfo: %{public}s", item.second.c_str());
        }
    }
}

bool EventManager::PostEventTouchTest(
    const TouchEvent& touchPoint, const RefPtr<NG::UINode>& uiNode, const TouchRestrict& touchRestrict)
{
    ContainerScope scope(instanceId_);
    ACE_FUNCTION_TRACE();
    CHECK_NULL_RETURN(uiNode, false);
    // collect
    TouchTestResult hitTestResult;
    const NG::PointF point { touchPoint.x, touchPoint.y };
    postEventRefereeNG_->CheckSourceTypeChange(touchPoint.sourceType);
    if (postEventRefereeNG_->QueryAllDone(touchPoint.id)) {
        postEventRefereeNG_->CleanGestureScope(touchPoint.id);
        if (postEventTouchTestResults_.empty() && postEventRefereeNG_->QueryAllDone()) {
            postEventRefereeNG_->CleanAll();
        }
    }
    // For root node, the parent local point is the same as global point.
    uiNode->TouchTest(point, point, point, touchRestrict, hitTestResult, touchPoint.id);
    for (const auto& item : hitTestResult) {
        item->SetIsPostEventResult(true);
        auto group = AceType::DynamicCast<NG::RecognizerGroup>(item);
        if (group) {
            group->SetIsPostEventResultRecursively(true);
        }
    }
    auto result = !hitTestResult.empty();
    postEventTouchTestResults_[touchPoint.id] = std::move(hitTestResult);
    return result;
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
    if (axisTouchTestResults_.empty() && refereeNG_->QueryAllDone()) {
        responseCtrl_->Reset();
    }
    // collect
    const NG::PointF point { event.x, event.y };
    if (frameNode->HaveSecurityComponent()) {
        std::vector<NG::RectF> rect;
        frameNode->CheckSecurityComponentStatus(rect);
    }
    // For root node, the parent local point is the same as global point.
    TouchTestResult hitTestResult;
    frameNode->TouchTest(point, point, point, touchRestrict, hitTestResult, event.id);
    axisTouchTestResults_[event.id] = std::move(hitTestResult);
}

bool EventManager::HasDifferentDirectionGesture()
{
    uint8_t verticalFlag = 0;
    uint8_t horizontalFlag = 0;
    for (const auto& axisResult : axisTouchTestResults_) {
        auto axisRecognizerList = axisResult.second;
        for (const auto& axisRecognizer : axisRecognizerList) {
            if (!axisRecognizer) {
                continue;
            }
            auto axisDirection = axisRecognizer->GetAxisDirection();
            if (axisDirection == Axis::FREE) {
                return true;
            }
            if (axisDirection == Axis::VERTICAL) {
                verticalFlag = 0x1;
            } else if (axisDirection == Axis::HORIZONTAL) {
                horizontalFlag = 0x2;
            }
            if ((verticalFlag | horizontalFlag) == 0x3) {
                return true;
            }
        }
    }
    return (verticalFlag | horizontalFlag) == 0x3;
}

void EventManager::HandleGlobalEvent(const TouchEvent& touchPoint, const RefPtr<TextOverlayManager>& textOverlayManager)
{
    if (touchPoint.type != TouchType::DOWN) {
        return;
    }
    auto coordinateOffset = textOverlayManager->GetCoordinateOffset();
    const Point point { touchPoint.x - coordinateOffset.GetX(), touchPoint.y - coordinateOffset.GetY(),
        touchPoint.sourceType };
    CHECK_NULL_VOID(textOverlayManager);
    auto textOverlayBase = textOverlayManager->GetTextOverlayBase();
    CHECK_NULL_VOID(textOverlayBase);
    auto targetNode = textOverlayManager->GetTargetNode();
    CHECK_NULL_VOID(targetNode);
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
    CHECK_NULL_VOID(selectOverlayManager);
    auto isMousePressAtSelectedNode = false;
    if (touchPoint.type == TouchType::DOWN &&
        (touchTestResults_.find(touchPoint.id) != touchTestResults_.end() || !currMouseTestResults_.empty())) {
        int32_t selectedNodeId = -1;
        if (touchPoint.sourceType == SourceType::MOUSE) {
            selectOverlayManager->GetSelectedNodeIdByMouse(selectedNodeId);
        }
        if (!touchTestResults_.empty()) {
            std::vector<std::string> touchTestIds;
            GetTouchTestIds(touchPoint, touchTestIds, isMousePressAtSelectedNode, selectedNodeId);
            selectOverlayManager->SetOnTouchTestResults(touchTestIds);
        } else {
            // When right-click on another component, close the current component selection.
            CheckMouseTestResults(isMousePressAtSelectedNode, selectedNodeId);
        }
    }
    selectOverlayManager->HandleGlobalEvent(touchPoint, rootOffset, isMousePressAtSelectedNode);
}

void EventManager::CheckMouseTestResults(bool& isMousePressAtSelectedNode, int32_t selectedNodeId)
{
    for (const auto& result : currMouseTestResults_) {
        TAG_LOGD(AceLogTag::ACE_INPUTTRACKING,
            "HandleGlobalEventNG selectedNodeId: %{public}d mouseTestResult id is: %{public}d", selectedNodeId,
            result->GetNodeId());
        if (result->GetNodeId() == selectedNodeId) {
            isMousePressAtSelectedNode = true;
        }
    }
}

void EventManager::GetTouchTestIds(const TouchEvent& touchPoint, std::vector<std::string>& touchTestIds,
    bool& isMousePressAtSelectedNode, int32_t selectedNodeId)
{
    const auto& resultList = touchTestResults_[touchPoint.id];
    for (const auto& result : resultList) {
        auto eventTarget = result->GetEventTarget();
        if (eventTarget.has_value()) {
            touchTestIds.emplace_back(eventTarget.value().id);
            if (eventTarget.value().id == std::to_string(selectedNodeId)) {
                TAG_LOGD(AceLogTag::ACE_INPUTTRACKING,
                    "HandleGlobalEventNG selectedNodeId: %{public}d eventTarget id is: %{public}s", selectedNodeId,
                    eventTarget.value().id.c_str());
                isMousePressAtSelectedNode = true;
            }
        }
    }
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

void EventManager::PostEventFlushTouchEventEnd(const TouchEvent& touchEvent)
{
    const auto result = postEventTouchTestResults_.find(touchEvent.id);
    if (result != postEventTouchTestResults_.end()) {
        for (auto entry = result->second.rbegin(); entry != result->second.rend(); ++entry) {
            (*entry)->OnFlushTouchEventsEnd();
        }
    }
}

void EventManager::CheckTouchEvent(TouchEvent touchEvent)
{
    auto touchEventFindResult = downFingerIds_.find(touchEvent.id);
    if (touchEvent.type == TouchType::DOWN) {
        if (touchEventFindResult == downFingerIds_.end()) {
            downFingerIds_.insert(touchEvent.id);
        } else {
            TAG_LOGW(AceLogTag::ACE_INPUTTRACKING, "EventManager receive DOWN event twice,"
                " touchEvent id is %{public}d", touchEvent.id);
        }
    } else if (touchEvent.type == TouchType::UP) {
        if (touchEventFindResult == downFingerIds_.end()) {
            TAG_LOGW(AceLogTag::ACE_INPUTTRACKING, "EventManager receive UP event without receive DOWN event,"
                " touchEvent id is %{public}d", touchEvent.id);
        } else {
            downFingerIds_.erase(touchEvent.id);
        }
    }
}

bool EventManager::DispatchTouchEvent(const TouchEvent& event)
{
    if (event.type != TouchType::MOVE) {
        TAG_LOGI(AceLogTag::ACE_INPUTTRACKING,
            "TouchEvent Dispatch in EventManager: "
            "eventInfo: id:%{public}d, pointX=%{public}f pointY=%{public}f "
            "type=%{public}d",
            event.id, event.x, event.y, (int)event.type);
    }
    CheckTouchEvent(event);
    ContainerScope scope(instanceId_);
    TouchEvent point = event;
    if (point.type == TouchType::PULL_MOVE || point.pullType == TouchType::PULL_MOVE) {
        isDragging_ = false;
        point.type = TouchType::CANCEL;
    }
    if (point.type == TouchType::PULL_UP || point.type == TouchType::UP) {
        isDragging_ = false;
        point.type = TouchType::UP;
    }
    ACE_SCOPED_TRACE(
        "DispatchTouchEvent id:%d, pointX=%f pointY=%f type=%d", point.id, point.x, point.y, (int)point.type);
    const auto iter = touchTestResults_.find(point.id);
    if (iter == touchTestResults_.end()) {
        return false;
    }

    if (point.type == TouchType::DOWN) {
        int64_t currentEventTime = static_cast<int64_t>(point.time.time_since_epoch().count());
        int64_t lastEventTime = static_cast<int64_t>(lastEventTime_.time_since_epoch().count());
        int64_t duration = static_cast<int64_t>((currentEventTime - lastEventTime) / TRANSLATE_NS_TO_MS);
        if (duration >= EVENT_CLEAR_DURATION && !refereeNG_->CheckGestureRefereeState()) {
            TAG_LOGW(AceLogTag::ACE_INPUTTRACKING, "GestureReferee check state fail, force clean gestureReferee.");
            std::list<std::pair<int32_t, std::string>> dumpList;
            eventTree_.Dump(dumpList, 0);
            for (auto& item : dumpList) {
                TAG_LOGI(AceLogTag::ACE_INPUTTRACKING, "EventTreeDumpInfo: %{public}s", item.second.c_str());
            }
            refereeNG_->ForceCleanGestureReferee();
        }
        // first collect gesture into gesture referee.
        if (Container::IsCurrentUseNewPipeline()) {
            refereeNG_->AddGestureToScope(point.id, iter->second);
        }
        // add gesture snapshot to dump
        for (const auto& target : iter->second) {
            AddGestureSnapshot(point.id, 0, target);
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
                    eventTree_.AddGestureProcedure(reinterpret_cast<uintptr_t>(AceType::RawPtr(recognizer)), point,
                        NG::TransRefereeState(recognizer->GetRefereeState()),
                        NG::TransGestureDisposal(recognizer->GetGestureDisposal()));
                }
                if (!recognizer && !isStopTouchEvent) {
                    isStopTouchEvent = !entry->HandleMultiContainerEvent(point);
                    eventTree_.AddGestureProcedure(reinterpret_cast<uintptr_t>(AceType::RawPtr(entry)),
                        std::string("Handle").append(GestureSnapshot::TransTouchType(point.type)), "", "");
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
        if (touchTestResults_.empty()) {
            refereeNG_->CleanRedundanceScope();
        }
    }

    lastEventTime_ = point.time;
    return true;
}

bool EventManager::PostEventDispatchTouchEvent(const TouchEvent& event)
{
    ContainerScope scope(instanceId_);
    TouchEvent point = event;
    const auto iter = postEventTouchTestResults_.find(point.id);
    if (iter == postEventTouchTestResults_.end()) {
        return false;
    }
    ACE_SCOPED_TRACE(
        "PostEventDispatchTouchEvent id:%d, pointX=%f pointY=%f type=%d", point.id, point.x, point.y, (int)point.type);

    if (point.type == TouchType::DOWN) {
        // first collect gesture into gesture referee.
        postEventRefereeNG_->AddGestureToScope(point.id, iter->second);
        // add gesture snapshot to dump
        for (const auto& target : iter->second) {
            AddGestureSnapshot(point.id, 0, target);
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
        bool isStopTouchEvent = false;
        for (const auto& entry : iter->second) {
            auto recognizer = AceType::DynamicCast<NG::NGGestureRecognizer>(entry);
            if (recognizer) {
                entry->HandleMultiContainerEvent(point);
                eventTree_.AddGestureProcedure(reinterpret_cast<uintptr_t>(AceType::RawPtr(recognizer)), point,
                    NG::TransRefereeState(recognizer->GetRefereeState()),
                    NG::TransGestureDisposal(recognizer->GetGestureDisposal()));
            }
            if (!recognizer && !isStopTouchEvent) {
                isStopTouchEvent = !entry->HandleMultiContainerEvent(point);
                eventTree_.AddGestureProcedure(reinterpret_cast<uintptr_t>(AceType::RawPtr(entry)),
                    std::string("Handle").append(GestureSnapshot::TransTouchType(point.type)), "", "");
            }
        }
    }

    if (point.type == TouchType::UP || point.type == TouchType::CANCEL) {
        postEventRefereeNG_->CleanGestureScope(point.id);
        postEventTouchTestResults_.erase(point.id);
        if (postEventTouchTestResults_.empty()) {
            postEventRefereeNG_->CleanRedundanceScope();
        }
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
    lastEventTime_ = event.time;
    return true;
}

bool EventManager::DispatchTabIndexEvent(
    const KeyEvent& event, const RefPtr<FocusNode>& focusNode, const RefPtr<FocusGroup>& mainNode)
{
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
    if (focusNode->HandleKeyEvent(event)) {
        LOGI("Default focus system handled this event");
        return true;
    }
    return false;
}

bool EventManager::DispatchTabIndexEventNG(const KeyEvent& event, const RefPtr<NG::FrameNode>& mainView)
{
    CHECK_NULL_RETURN(mainView, false);
    TAG_LOGD(AceLogTag::ACE_FOCUS,
        "Dispatch tab index event: code:%{public}d/action:%{public}d on node: %{public}s/%{public}d.", event.code,
        event.action, mainView->GetTag().c_str(), mainView->GetId());
    auto mainViewFocusHub = mainView->GetFocusHub();
    CHECK_NULL_RETURN(mainViewFocusHub, false);
    if (mainViewFocusHub->HandleFocusByTabIndex(event)) {
        TAG_LOGD(AceLogTag::ACE_FOCUS, "Tab index handled the key event: code:%{public}d/action:%{public}d", event.code,
            event.action);
        return true;
    }
    return false;
}

bool EventManager::DispatchKeyEventNG(const KeyEvent& event, const RefPtr<NG::FrameNode>& focusNode)
{
    CHECK_NULL_RETURN(focusNode, false);
    TAG_LOGD(AceLogTag::ACE_FOCUS,
        "Dispatch key event: code:%{public}d/action:%{public}d on node: %{public}s/%{public}d.", event.code,
        event.action, focusNode->GetTag().c_str(), focusNode->GetId());
    auto focusNodeHub = focusNode->GetFocusHub();
    CHECK_NULL_RETURN(focusNodeHub, false);
    if (focusNodeHub->HandleKeyEvent(event)) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Focus system handled the key event: code:%{public}d/action:%{public}d",
            event.code, event.action);
        return true;
    }
    TAG_LOGD(AceLogTag::ACE_FOCUS, "Focus system do not handled the key event: code:%{public}d/action:%{public}d",
        event.code, event.action);
    return false;
}

void EventManager::MouseTest(const MouseEvent& event, const RefPtr<RenderNode>& renderNode)
{
    CHECK_NULL_VOID(renderNode);
    const Point point { event.x, event.y };
    MouseHoverTestList hitTestResult;
    WeakPtr<RenderNode> hoverNode = nullptr;
    renderNode->MouseDetect(point, point, hitTestResult, hoverNode);

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
    if (!SystemProperties::GetDebugEnabled()) {
        return;
    }
    if (currMouseTestResults_.empty()) {
        TAG_LOGI(AceLogTag::ACE_MOUSE, "Mouse test onMouse result is empty.");
    } else {
        for (const auto& result : currMouseTestResults_) {
            TAG_LOGI(AceLogTag::ACE_MOUSE, "Mouse test onMouse result: %{public}s/%{public}d.",
                result->GetNodeName().c_str(), result->GetNodeId());
        }
    }
    if (lastHoverTestResults_.empty()) {
        TAG_LOGI(AceLogTag::ACE_MOUSE, "Mouse test onHover last result is empty.");
    } else {
        for (const auto& result : lastHoverTestResults_) {
            TAG_LOGI(AceLogTag::ACE_MOUSE, "Mouse test onHover last result: %{public}s/%{public}d.",
                result->GetNodeName().c_str(), result->GetNodeId());
        }
    }
    if (currHoverTestResults_.empty()) {
        TAG_LOGI(AceLogTag::ACE_MOUSE, "Mouse test onHover current result is empty.");
    } else {
        for (const auto& result : currHoverTestResults_) {
            TAG_LOGI(AceLogTag::ACE_MOUSE, "Mouse test onHover current result: %{public}s/%{public}d.",
                result->GetNodeName().c_str(), result->GetNodeId());
        }
    }
    auto lastNode = lastHoverNode_.Upgrade();
    auto currNode = currHoverNode_.Upgrade();
    TAG_LOGI(AceLogTag::ACE_MOUSE,
        "Mouse test last/current hoverEffect node: %{public}s/%{public}d / %{public}s/%{public}d",
        lastNode ? lastNode->GetTag().c_str() : "NULL", lastNode ? lastNode->GetId() : -1,
        currNode ? currNode->GetTag().c_str() : "NULL", currNode ? currNode->GetId() : -1);
}

void EventManager::MouseTest(
    const MouseEvent& event, const RefPtr<NG::FrameNode>& frameNode, const TouchRestrict& touchRestrict)
{
    TAG_LOGD(AceLogTag::ACE_MOUSE,
        "Mouse test start. Event is (%{public}f,%{public}f), button: %{public}d, action: %{public}d", event.x, event.y,
        event.button, event.action);
    CHECK_NULL_VOID(frameNode);
    const NG::PointF point { event.x, event.y };
    TouchTestResult testResult;
    if (frameNode->HaveSecurityComponent()) {
        std::vector<NG::RectF> rect;
        frameNode->CheckSecurityComponentStatus(rect);
    }
    frameNode->TouchTest(point, point, point, touchRestrict, testResult, event.GetId());

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
        TAG_LOGI(AceLogTag::ACE_MOUSE, "Exit hover by leave-window event.");
        lastHoverTestResults_ = std::move(currHoverTestResults_);
        currHoverTestResults_.clear();
    } else if (event.action == MouseAction::WINDOW_ENTER) {
        TAG_LOGI(AceLogTag::ACE_MOUSE, "Enter hover by enter-window event.");
        lastHoverTestResults_.clear();
        currHoverTestResults_ = std::move(hoverTestResult);
    } else {
        lastHoverTestResults_ = std::move(currHoverTestResults_);
        currHoverTestResults_ = std::move(hoverTestResult);
    }
    lastHoverNode_ = currHoverNode_;
    currHoverNode_ = hoverNode;
    LogPrintMouseTest();
}

bool EventManager::DispatchMouseEventNG(const MouseEvent& event)
{
    if (event.action == MouseAction::PRESS || event.action == MouseAction::RELEASE ||
        event.action == MouseAction::MOVE || event.action == MouseAction::WINDOW_ENTER ||
        event.action == MouseAction::WINDOW_LEAVE) {
        MouseTestResult handledResults;
        handledResults.clear();
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, false);
        if (event.button == MouseButton::LEFT_BUTTON) {
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
        return requestFocusNode->RotationTestForward(event);
    } else {
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
        // FunctionKey
        if (event.IsFunctionKey() || event.IsEscapeKey()) {
            if (event.ConvertInputCodeToString() != keyboardShortcut.value) {
                continue;
            }
        } else if (event.ConvertInputCodeToString().find(keyboardShortcut.value) == std::string::npos) {
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
    postEventTouchTestResults_.clear();
    mouseTestResults_.clear();
    axisTouchTestResults_.clear();
    keyboardShortcutNode_.clear();
}

EventManager::EventManager()
{
    refereeNG_ = AceType::MakeRefPtr<NG::GestureReferee>();
    postEventRefereeNG_ = AceType::MakeRefPtr<NG::GestureReferee>();
    referee_ = AceType::MakeRefPtr<GestureReferee>();
    responseCtrl_ = AceType::MakeRefPtr<NG::ResponseCtrl>();

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

void EventManager::DumpEvent() const
{
    std::list<std::pair<int32_t, std::string>> dumpList;
    eventTree_.Dump(dumpList, 0);
    for (auto& item : dumpList) {
        DumpLog::GetInstance().Print(item.first, item.second);
    }
}

void EventManager::AddGestureSnapshot(int32_t finger, int32_t depth, const RefPtr<TouchEventTarget>& target)
{
    if (!target) {
        return;
    }
    RefPtr<GestureSnapshot> info = target->Dump();
    auto frameNode = target->GetAttachedNode().Upgrade();
    if (frameNode) {
        info->nodeId = frameNode->GetId();
    }
    info->depth = depth;
    eventTree_.AddGestureSnapshot(finger, std::move(info));

    // add child gesture if target is group
    auto group = AceType::DynamicCast<NG::RecognizerGroup>(target);
    if (group) {
        for (const auto& child : group->GetGroupRecognizer()) {
            AddGestureSnapshot(finger, depth + 1, child);
        }
    }
}

void EventManager::SetHittedFrameNode(const std::list<RefPtr<NG::NGGestureRecognizer>>& touchTestResults)
{
    if (touchTestResults.empty()) {
        return;
    }
    for (const auto& item : touchTestResults) {
        auto node = item->GetAttachedNode().Upgrade();
        if (node) {
            hittedFrameNode_.emplace(node);
        }
        auto group = AceType::DynamicCast<NG::RecognizerGroup>(item);
        if (group) {
            auto groupRecognizers = group->GetGroupRecognizer();
            SetHittedFrameNode(groupRecognizers);
        }
    }
}

void EventManager::CleanGestureEventHub()
{
    for (const auto& item : hittedFrameNode_) {
        auto frameNode = item.Upgrade();
        if (frameNode) {
            auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
            if (gestureEventHub) {
                gestureEventHub->CleanExternalRecognizers();
            }
        }
    }
    hittedFrameNode_.clear();
}

} // namespace OHOS::Ace
