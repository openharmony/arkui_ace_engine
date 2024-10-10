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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_EVENT_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_EVENT_MANAGER_H

#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/event_dump.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/response_ctrl.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/event/axis_event.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/rotation_event.h"
#include "core/event/touch_event.h"
#include "core/focus/focus_node.h"
#include "core/gestures/gesture_referee.h"

namespace OHOS::Ace {
namespace NG {
class FrameNode;
class SelectOverlayManager;
class ResponseCtrl;
} // namespace NG
class RenderNode;
class Element;
class TextOverlayManager;
using MouseHoverTestList = std::list<WeakPtr<RenderNode>>;
using OutOfRectGetRectCallback = std::function<void(std::vector<Rect>&)>;
using OutOfRectTouchCallback = std::function<void(void)>;
using OutOfRectMouseCallback = std::function<void(void)>;

struct RectCallback final {
    RectCallback(OutOfRectGetRectCallback rectGetCallback, OutOfRectTouchCallback touchCallback,
        OutOfRectMouseCallback mouseCallback)
        : rectGetCallback(std::move(rectGetCallback)), touchCallback(std::move(touchCallback)),
          mouseCallback(std::move(mouseCallback))
    {}
    ~RectCallback() = default;
    OutOfRectGetRectCallback rectGetCallback;
    OutOfRectTouchCallback touchCallback;
    OutOfRectMouseCallback mouseCallback;
};

struct MarkProcessedEventInfo {
    int32_t eventId = -1;
    int64_t lastLogTimeStamp = 0;
};

class EventManager : public virtual AceType {
    DECLARE_ACE_TYPE(EventManager, AceType);

public:
    EventManager();
    ~EventManager() override = default;
    // After the touch down event is triggered, the touch test is performed to collect the corresponding
    // touch event target list.
    void TouchTest(const TouchEvent& touchPoint, const RefPtr<RenderNode>& renderNode,
        TouchRestrict& touchRestrict, const Offset& offset = Offset(),
        float viewScale = 1.0f, bool needAppend = false);

    void TouchTest(const TouchEvent& touchPoint, const RefPtr<NG::FrameNode>& frameNode,
        TouchRestrict& touchRestrict, const Offset& offset = Offset(),
        float viewScale = 1.0f, bool needAppend = false);

    bool PostEventTouchTest(const TouchEvent& touchPoint, const RefPtr<NG::UINode>& uiNode,
        TouchRestrict& touchRestrict);

    void TouchTest(const AxisEvent& event, const RefPtr<RenderNode>& renderNode, TouchRestrict& touchRestrict);

    void TouchTest(const AxisEvent& event, const RefPtr<NG::FrameNode>& frameNode, TouchRestrict& touchRestrict);

    bool HasDifferentDirectionGesture();

    bool DispatchTouchEvent(const TouchEvent& point, bool sendOnTouch = true);
    bool DispatchTouchEvent(const AxisEvent& event, bool sendOnTouch = true);
    bool PostEventDispatchTouchEvent(const TouchEvent& point);
    void FlushTouchEventsBegin(const std::list<TouchEvent>& touchEvents);
    void FlushTouchEventsEnd(const std::list<TouchEvent>& touchEvents);
    void PostEventFlushTouchEventEnd(const TouchEvent& touchEvent);

    // Distribute the key event to the corresponding root node. If the root node is not processed, return false and the
    // platform will handle it.
    bool DispatchKeyEvent(const KeyEvent& event, const RefPtr<FocusNode>& focusNode);
    bool DispatchTabIndexEvent(
        const KeyEvent& event, const RefPtr<FocusNode>& focusNode, const RefPtr<FocusGroup>& mainNode);

    // Distribute the key event to the corresponding root node. If the root node is not processed, return false and the
    // platform will handle it.
    bool DispatchKeyEventNG(const KeyEvent& event, const RefPtr<NG::FrameNode>& focusNode);
    bool DispatchTabIndexEventNG(const KeyEvent& event, const RefPtr<NG::FrameNode>& mainView);

    // Distribute the rotation event to the corresponding render tree or requested render node. If the render is not
    // processed, return false and the platform will handle it.
    static bool DispatchRotationEvent(
        const RotationEvent& event, const RefPtr<RenderNode>& renderNode, const RefPtr<RenderNode>& requestFocusNode);

    // If current focus node is Web, will skip some events processing.
    static bool IsSkipEventNode(const RefPtr<NG::FrameNode>& focusNode);

    // mouse event target list.
    void MouseTest(const MouseEvent& touchPoint, const RefPtr<RenderNode>& renderNode);
    bool DispatchMouseEvent(const MouseEvent& event);
    void DispatchMouseHoverAnimation(const MouseEvent& event);
    bool DispatchMouseHoverEvent(const MouseEvent& event);

    void LogPrintMouseTest();
    void MouseTest(const MouseEvent& event, const RefPtr<NG::FrameNode>& frameNode, TouchRestrict& touchRestrict);
    void AccessibilityHoverTest(
        const TouchEvent& event, const RefPtr<NG::FrameNode>& frameNode, TouchRestrict& touchRestrict);
    void UpdateAccessibilityHoverNode(const TouchEvent& event, const TouchTestResult& testResult);
    void PenHoverTest(const TouchEvent& event, const RefPtr<NG::FrameNode>& frameNode, TouchRestrict& touchRestrict);
    void UpdatePenHoverNode(const TouchEvent& event, const TouchTestResult& testResult);
    void UpdateHoverNode(const MouseEvent& event, const TouchTestResult& testResult);
    bool DispatchMouseEventNG(const MouseEvent& event);
    void DispatchMouseHoverAnimationNG(const MouseEvent& event);
    bool DispatchMouseHoverEventNG(const MouseEvent& event);
    void DispatchHoverEffectEvent(const MouseEvent& event);
    void DispatchAccessibilityHoverEventNG(const TouchEvent& event);
    void DispatchPenHoverEventNG(const TouchEvent& event);

    void AxisTest(const AxisEvent& event, const RefPtr<RenderNode>& renderNode);
    bool DispatchAxisEvent(const AxisEvent& event);

    void AxisTest(const AxisEvent& event, const RefPtr<NG::FrameNode>& frameNode);
    bool DispatchAxisEventNG(const AxisEvent& event);

    void ClearResults();
    void SetInstanceId(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }
    int32_t GetInstanceId()
    {
        return instanceId_;
    }
    void HandleGlobalEvent(const TouchEvent& touchPoint, const RefPtr<TextOverlayManager>& textOverlayManager);
    void HandleGlobalEventNG(const TouchEvent& touchPoint, const RefPtr<NG::SelectOverlayManager>& selectOverlayManager,
        const NG::OffsetF& rootOffset);

    void CollectTabIndexNodes(const RefPtr<FocusNode>& rootNode);

    void AdjustTabIndexNodes();

    bool HandleFocusByTabIndex(
        const KeyEvent& event, const RefPtr<FocusNode>& focusNode, const RefPtr<FocusGroup>& curPage);

    void HandleOutOfRectCallback(const Point& point, std::vector<RectCallback>& rectCallbackList);

    RefPtr<GestureReferee> GetGestureReferee()
    {
        return referee_;
    }

    RefPtr<NG::GestureReferee> GetGestureRefereeNG(const RefPtr<NG::NGGestureRecognizer>& recognizer)
    {
        if (recognizer->IsPostEventResult()) {
            return postEventRefereeNG_;
        }
        return refereeNG_;
    }

    bool DispatchKeyboardShortcut(const KeyEvent& event);

    void AddKeyboardShortcutNode(const WeakPtr<NG::FrameNode>& node);

    void DelKeyboardShortcutNode(int32_t nodeId);

    void AddKeyboardShortcutKeys(uint8_t keys, std::vector<KeyCode>& leftKeyCode, std::vector<KeyCode>& rightKeyCode,
        std::vector<uint8_t>& permutation);

    bool IsKeyInPressed(KeyCode tarCode) const
    {
        return std::any_of(pressedKeyCodes_.begin(), pressedKeyCodes_.end(),
            [tarCode](const KeyCode& code) { return code == tarCode; });
    }
    void SetPressedKeyCodes(const std::vector<KeyCode>& pressedKeyCodes)
    {
        pressedKeyCodes_ = pressedKeyCodes;
    }

    bool IsSameKeyboardShortcutNode(const std::string& value, uint8_t keys);

    bool IsSystemKeyboardShortcut(const KeyEvent& event);

    uint8_t GetKeyboardShortcutKeys(const std::vector<ModifierKey>& keys);

    void DoMouseActionRelease();

    void SetIsDragging(bool isDragging)
    {
        isDragging_ = isDragging;
    }

    bool IsDragging() const
    {
        return isDragging_;
    }

    void SetLastMoveBeforeUp(bool isLastMoveBeforeUp)
    {
        isLastMoveBeforeUp_ = isLastMoveBeforeUp;
    }

    bool IsLastMoveBeforeUp() const
    {
        return isLastMoveBeforeUp_;
    }

    NG::EventTreeRecord& GetEventTreeRecord(NG::EventTreeType treeType)
    {
        switch (treeType) {
            case NG::EventTreeType::TOUCH :
                return eventTree_;
            case NG::EventTreeType::POST_EVENT :
                return postEventTree_;
        }
    }

    void DumpEvent(NG::EventTreeType type, bool hasJson = false);

    void AddGestureSnapshot(
        int32_t finger, int32_t depth, const RefPtr<TouchEventTarget>& target, NG::EventTreeType type);

    RefPtr<NG::ResponseCtrl> GetResponseCtrl()
    {
        return responseCtrl_;
    }

    void CheckDownEvent(const TouchEvent& touchEvent);
    void CheckUpEvent(const TouchEvent& touchEvent);
    std::unordered_map<size_t, TouchTestResult> touchTestResults_;
    std::unordered_map<size_t, TouchTestResult> postEventTouchTestResults_;

    void SetInnerFlag(bool value)
    {
        innerEventWin_ = value;
    }

    bool GetInnerFlag() const
    {
        return innerEventWin_;
    }

    void SetIsKeyConsumed(bool value)
    {
        // Once consumed, isKeyConsumed_ keeps true
        if (!isKeyConsumed_ && value) {
            isKeyConsumed_ = true;
        }
    }

    int64_t GetLastTouchEventEndTimestamp()
    {
        return lastTouchEventEndTimestamp_;
    }

    void RecordHitEmptyMessage(
        const TouchEvent& touchPoint, const std::string& resultInfo, const RefPtr<NG::FrameNode>& frameNode);

    void CheckAndLogLastReceivedTouchEventInfo(int32_t eventId, TouchType type);

    void CheckAndLogLastConsumedTouchEventInfo(int32_t eventId, TouchType type);

    void CheckAndLogLastReceivedMouseEventInfo(int32_t eventId, MouseAction action);

    void CheckAndLogLastConsumedMouseEventInfo(int32_t eventId, MouseAction action);

    void CheckAndLogLastReceivedAxisEventInfo(int32_t eventId, AxisAction action);

    void CheckAndLogLastConsumedAxisEventInfo(int32_t eventId, AxisAction action);

    void CheckAndLogLastReceivedEventInfo(int32_t eventId, bool logImmediately = false);

    void CheckAndLogLastConsumedEventInfo(int32_t eventId, bool logImmediately = false);

    void ClearTouchTestTargetForPenStylus(TouchEvent& touchEvent);

    TouchEvent ConvertAxisEventToTouchEvent(const AxisEvent& axisEvent);

#if defined(SUPPORT_TOUCH_TARGET_TEST)
    bool TouchTargetHitTest(const TouchEvent& touchPoint, const RefPtr<NG::FrameNode>& frameNode,
        TouchRestrict& touchRestrict, const Offset& offset = Offset(), float viewScale = 1.0f,
        bool needAppend = false, const std::string& target = "");
#endif
private:
    void SetHittedFrameNode(const std::list<RefPtr<NG::NGGestureRecognizer>>& touchTestResults);
    void CleanGestureEventHub();
    void GetTouchTestIds(const TouchEvent& touchPoint, std::vector<std::string>& touchTestIds,
        bool& isMousePressAtSelectedNode, int32_t selectedNodeId);
    void CheckMouseTestResults(bool& isMousePressAtSelectedNode, int32_t selectedNodeId);
    void CleanRefereeBeforeTouchTest(TouchEvent touchPoint, bool needAppend);
    void LogTouchTestResultInfo(const TouchEvent& touchPoint, const RefPtr<NG::FrameNode>& frameNode,
        TouchRestrict& touchRestrict, const Offset& offset = Offset(),
        float viewScale = 1.0f, bool needAppend = false);
    void LogTouchTestResultRecognizers(const TouchTestResult& result, int32_t touchEventId);
    void CheckRefereeStateAndReTouchTest(const TouchEvent& touchPoint, const RefPtr<NG::FrameNode>& frameNode,
        TouchRestrict& touchRestrict, const Offset& offset = Offset(),
        float viewScale = 1.0f, bool needAppend = false);
    bool DispatchMultiContainerEvent(const TouchEvent& point);
    void DispatchTouchEventAndCheck(const TouchEvent& event, bool sendOnTouch = true);
    void DispatchTouchEventInOldPipeline(const TouchEvent& point, bool dispatchSuccess);
    void DispatchTouchEventToTouchTestResult(TouchEvent touchEvent, TouchTestResult touchTestResult,
        bool sendOnTouch);
    void CleanRecognizersForDragBegin(TouchEvent& touchEvent);
    void SetResponseLinkRecognizers(const TouchTestResult& result, const ResponseLinkResult& responseLinkRecognizers);
    void FalsifyCancelEventAndDispatch(const TouchEvent& touchPoint, bool sendOnTouch = true);
    void FalsifyCancelEventAndDispatch(const AxisEvent& axisEvent, bool sendOnTouch = true);
    void FalsifyHoverCancelEventAndDispatch(const TouchEvent& touchPoint);
    void UpdateDragInfo(TouchEvent& point);
    void UpdateInfoWhenFinishDispatch(const TouchEvent& point, bool sendOnTouch);
    bool innerEventWin_ = false;
    std::unordered_map<size_t, TouchTestResult> mouseTestResults_;
    MouseTestResult currMouseTestResults_;
    MouseTestResult pressMouseTestResults_;
    HoverTestResult currHoverTestResults_;
    HoverTestResult lastHoverTestResults_;
    HoverTestResult curAccessibilityHoverResults_;
    HoverTestResult lastAccessibilityHoverResults_;
    HoverTestResult curPenHoverResults_;
    HoverTestResult lastPenHoverResults_;
    AxisTestResult axisTestResults_;
    WeakPtr<NG::FrameNode> lastHoverNode_;
    WeakPtr<NG::FrameNode> currHoverNode_;
    std::unordered_map<size_t, TouchTestResult> axisTouchTestResults_;
    MouseHoverTestList mouseHoverTestResults_;
    MouseHoverTestList mouseHoverTestResultsPre_;
    WeakPtr<RenderNode> mouseHoverNodePre_;
    WeakPtr<RenderNode> mouseHoverNode_;
    WeakPtr<RenderNode> axisNode_;
    int32_t instanceId_ = 0;
    uint32_t lastHoverDispatchLength_ = 0;
    uint32_t lastAccessibilityHoverDispatchLength_ = 0;
    uint32_t lastPenHoverDispatchLength_ = 0;
    bool inSelectedRect_ = false;
    bool isDragging_ = false;
    bool isLastMoveBeforeUp_ = false;
    bool isKeyConsumed_ = false;
    RefPtr<GestureReferee> referee_;
    RefPtr<NG::GestureReferee> refereeNG_;
    RefPtr<NG::GestureReferee> postEventRefereeNG_;
    std::list<WeakPtr<NG::FrameNode>> keyboardShortcutNode_;
    std::vector<KeyCode> pressedKeyCodes_;
    NG::EventTreeRecord eventTree_;
    NG::EventTreeRecord postEventTree_;
    RefPtr<NG::ResponseCtrl> responseCtrl_;
    TimeStamp lastEventTime_;
    int64_t lastTouchEventEndTimestamp_ = 0;
    std::unordered_map<int32_t, int32_t> downFingerIds_;
    std::set<WeakPtr<NG::FrameNode>> hittedFrameNode_;
    MarkProcessedEventInfo lastReceivedEvent_;
    MarkProcessedEventInfo lastConsumedEvent_;
    int32_t lastDownFingerNumber_ = 0;
    SourceTool lastSourceTool_ = SourceTool::UNKNOWN;
    // used to pseudo cancel event.
    TouchEvent lastTouchEvent_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_EVENT_MANAGER_H
