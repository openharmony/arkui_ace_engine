/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/common/event_manager.h"

#include <algorithm>
#include <chrono>

#include "core/event/focus_axis_event.h"

namespace OHOS::Ace {
namespace {
template<typename EventT>
uint64_t GetEventNs(const EventT& event)
{
    return static_cast<uint64_t>(event.time.time_since_epoch().count());
}

template<typename EventT>
EventT InterpolateEvent(const EventT& prev, const EventT& next, uint64_t nanoTimeStamp)
{
    auto prevTs = GetEventNs(prev);
    auto nextTs = GetEventNs(next);
    if (nextTs <= prevTs) {
        return prev;
    }
    double ratio = static_cast<double>(nanoTimeStamp - prevTs) / static_cast<double>(nextTs - prevTs);
    ratio = std::clamp(ratio, 0.0, 1.0);
    EventT result = prev;
    result.x = prev.x + static_cast<decltype(result.x)>((next.x - prev.x) * ratio);
    result.y = prev.y + static_cast<decltype(result.y)>((next.y - prev.y) * ratio);
    result.time = TimeStamp(std::chrono::nanoseconds(nanoTimeStamp));
    return result;
}

template<typename EventT>
EventT GetInterpolatedEvent(
    const std::vector<EventT>& history, const std::vector<EventT>& current, uint64_t nanoTimeStamp)
{
    std::vector<EventT> all;
    all.reserve(history.size() + current.size());
    all.insert(all.end(), history.begin(), history.end());
    all.insert(all.end(), current.begin(), current.end());
    if (all.empty()) {
        return {};
    }
    std::sort(all.begin(), all.end(), [](const EventT& a, const EventT& b) { return GetEventNs(a) < GetEventNs(b); });
    if (nanoTimeStamp <= GetEventNs(all.front())) {
        return all.front();
    }
    if (nanoTimeStamp >= GetEventNs(all.back())) {
        return all.back();
    }
    for (size_t i = 1; i < all.size(); ++i) {
        auto prevTs = GetEventNs(all[i - 1]);
        auto nextTs = GetEventNs(all[i]);
        if (prevTs <= nanoTimeStamp && nanoTimeStamp <= nextTs) {
            return InterpolateEvent(all[i - 1], all[i], nanoTimeStamp);
        }
    }
    return all.back();
}
} // namespace

class CoastingAxisEventGenerator : public AceType {
    DECLARE_ACE_TYPE(CoastingAxisEventGenerator, AceType);
public:
    CoastingAxisEventGenerator() = default;
    ~CoastingAxisEventGenerator() override = default;
};

EventManager::EventManager()
{
    mouseStyleManager_ = AceType::MakeRefPtr<MouseStyleManager>();
}

bool EventManager::DispatchTouchEvent(const TouchEvent& point, bool sendOnTouch)
{
    (void)point;
    (void)sendOnTouch;
    return false;
}

void EventManager::TouchTest(const TouchEvent& touchPoint, const RefPtr<NG::FrameNode>& frameNode,
    TouchRestrict& touchRestrict, const Offset& offset, float viewScale, bool needAppend)
{
    (void)touchPoint;
    (void)frameNode;
    (void)touchRestrict;
    (void)offset;
    (void)viewScale;
    (void)needAppend;
}

void EventManager::TouchTest(const AxisEvent& event, const RefPtr<NG::FrameNode>& frameNode, TouchRestrict& touchRestrict)
{
    (void)event;
    (void)frameNode;
    (void)touchRestrict;
}

bool EventManager::HasDifferentDirectionGesture()
{
    return false;
}

bool EventManager::OnNonPointerEvent(const NonPointerEvent& event)
{
    if (event.eventType == UIInputEventType::KEY) {
        return OnKeyEvent(static_cast<const KeyEvent&>(event));
    }
    if (event.eventType == UIInputEventType::FOCUS_AXIS) {
        return OnFocusAxisEvent(static_cast<const NG::FocusAxisEvent&>(event));
    }
    if (event.eventType == UIInputEventType::CROWN) {
        return OnCrownEvent(static_cast<const CrownEvent&>(event));
    }
    return false;
}

bool EventManager::DispatchTouchEvent(const AxisEvent& event, bool sendOnTouch)
{
    (void)event;
    (void)sendOnTouch;
    return false;
}

void EventManager::FlushTouchEventsBegin(const std::list<TouchEvent>& touchEvents)
{
    (void)touchEvents;
}

void EventManager::FlushTouchEventsEnd(const std::list<TouchEvent>& touchEvents)
{
    (void)touchEvents;
}

void EventManager::MouseTest(const MouseEvent& event, const RefPtr<NG::FrameNode>& frameNode, TouchRestrict& touchRestrict)
{
    (void)event;
    (void)frameNode;
    (void)touchRestrict;
}

void EventManager::AccessibilityHoverTest(
    const TouchEvent& event, const RefPtr<NG::FrameNode>& frameNode, TouchRestrict& touchRestrict)
{
    (void)event;
    (void)frameNode;
    (void)touchRestrict;
}

void EventManager::PenHoverTest(const TouchEvent& event, const RefPtr<NG::FrameNode>& frameNode, TouchRestrict& touchRestrict)
{
    (void)event;
    (void)frameNode;
    (void)touchRestrict;
}

void EventManager::UpdatePenHoverNode(const TouchEvent& event, const TouchTestResult& testResult)
{
    (void)event;
    (void)testResult;
}

bool EventManager::DispatchMouseEventNG(const MouseEvent& event)
{
    (void)event;
    return false;
}

void EventManager::DispatchMouseHoverAnimationNG(const MouseEvent& event, bool isMockEvent)
{
    (void)event;
    (void)isMockEvent;
}

bool EventManager::DispatchMouseHoverEventNG(const MouseEvent& event)
{
    (void)event;
    return false;
}

void EventManager::DispatchAccessibilityHoverEventNG(const TouchEvent& event)
{
    (void)event;
}

void EventManager::DispatchPenHoverEventNG(const TouchEvent& event)
{
    (void)event;
}

void EventManager::DispatchPenHoverMoveEventNG(const TouchEvent& event)
{
    (void)event;
}

void EventManager::AxisTest(const AxisEvent& event, const RefPtr<NG::FrameNode>& frameNode)
{
    (void)event;
    (void)frameNode;
}

bool EventManager::DispatchAxisEventNG(const AxisEvent& event)
{
    (void)event;
    return false;
}

void EventManager::ClearResults()
{
    touchTestResults_.clear();
    postEventTouchTestResults_.clear();
    mouseTestResults_.clear();
    axisTouchTestResults_.clear();
}

void EventManager::HandleGlobalEventNG(const TouchEvent& touchPoint, const RefPtr<NG::SelectOverlayManager>& selectOverlayManager,
    const NG::OffsetF& rootOffset)
{
    (void)touchPoint;
    (void)selectOverlayManager;
    (void)rootOffset;
}

bool EventManager::TryResampleTouchEvent(std::vector<TouchEvent>& history,
    const std::vector<TouchEvent>& current, uint64_t nanoTimeStamp, TouchEvent& resample)
{
    (void)history;
    (void)nanoTimeStamp;
    if (current.empty()) {
        return false;
    }
    resample = current.back();
    return true;
}

bool EventManager::GetResampleTouchEvent(const std::vector<TouchEvent>& history,
    const std::vector<TouchEvent>& current, uint64_t nanoTimeStamp, TouchEvent& newTouchEvent)
{
    if (history.empty() && current.empty()) {
        return false;
    }
    newTouchEvent = GetInterpolatedEvent(history, current, nanoTimeStamp);
    return true;
}

TouchEvent EventManager::GetLatestPoint(const std::vector<TouchEvent>& current, uint64_t nanoTimeStamp)
{
    if (current.empty()) {
        return {};
    }
    auto result = current.front();
    for (const auto& point : current) {
        if (GetEventNs(point) <= nanoTimeStamp) {
            result = point;
            continue;
        }
        break;
    }
    return result;
}

DragPointerEvent EventManager::GetResamplePointerEvent(const std::vector<DragPointerEvent>& history,
    const std::vector<DragPointerEvent>& current, uint64_t nanoTimeStamp)
{
    return GetInterpolatedEvent(history, current, nanoTimeStamp);
}

MouseEvent EventManager::GetResampleMouseEvent(
    const std::vector<MouseEvent>& history, const std::vector<MouseEvent>& current, uint64_t nanoTimeStamp)
{
    return GetInterpolatedEvent(history, current, nanoTimeStamp);
}

void EventManager::DumpEvent(NG::EventTreeType type, bool hasJson)
{
    (void)type;
    (void)hasJson;
}

void EventManager::DumpEventWithCount(const std::vector<std::string>& params, NG::EventTreeType type, bool hasJson)
{
    (void)params;
    (void)type;
    (void)hasJson;
}

void EventManager::DumpTouchInfo(const std::vector<std::string>& params, bool hasJson)
{
    (void)params;
    (void)hasJson;
}

void EventManager::CheckDownEvent(const TouchEvent& touchEvent)
{
    (void)touchEvent;
}

void EventManager::ClearTouchTestTargetForPenStylus(TouchEvent& touchEvent)
{
    (void)touchEvent;
}

void EventManager::CleanHoverStatusForDragBegin()
{
    mouseTestResults_.clear();
}

void EventManager::UnregisterTouchDelegate(int32_t touchId)
{
    (void)touchId;
}

void EventManager::UnregisterTouchDelegate(TouchDelegateHdl handler)
{
    (void)handler;
}

void EventManager::DelegateTouchEvent(const TouchEvent& point)
{
    (void)point;
}

void EventManager::CheckAndLogLastReceivedTouchEventInfo(int32_t eventId, TouchType type)
{
    (void)eventId;
    (void)type;
}

void EventManager::CheckAndLogLastConsumedTouchEventInfo(int32_t eventId, TouchType type)
{
    (void)eventId;
    (void)type;
}

void EventManager::CheckAndLogLastReceivedMouseEventInfo(int32_t eventId, MouseAction action)
{
    (void)eventId;
    (void)action;
}

void EventManager::CheckAndLogLastConsumedMouseEventInfo(int32_t eventId, MouseAction action)
{
    (void)eventId;
    (void)action;
}

void EventManager::CheckAndLogLastReceivedAxisEventInfo(int32_t eventId, AxisAction action)
{
    (void)eventId;
    (void)action;
}

void EventManager::CheckAndLogLastConsumedAxisEventInfo(int32_t eventId, AxisAction action)
{
    (void)eventId;
    (void)action;
}

bool EventManager::HandleAxisEventWithDifferentDeviceId(const AxisEvent& event, const RefPtr<NG::FrameNode>& frameNode)
{
    (void)frameNode;
    switch (event.action) {
        case AxisAction::BEGIN: {
            auto iter = deviceIdChecker_.find(event.id);
            if (iter == deviceIdChecker_.end()) {
                deviceIdChecker_[event.id] = event.deviceId;
                return false;
            }
            if (iter->second != event.deviceId) {
                iter->second = event.deviceId;
            }
            return false;
        }
        case AxisAction::UPDATE: {
            auto iter = deviceIdChecker_.find(event.id);
            if (iter == deviceIdChecker_.end()) {
                return true;
            }
            return iter->second != event.deviceId;
        }
        case AxisAction::END:
        case AxisAction::CANCEL: {
            auto iter = deviceIdChecker_.find(event.id);
            if (iter == deviceIdChecker_.end()) {
                return true;
            }
            if (iter->second != event.deviceId) {
                return true;
            }
            deviceIdChecker_.erase(iter);
            return false;
        }
        default:
            return false;
    }
}

void EventManager::NotifyAxisEvent(const AxisEvent& event, const RefPtr<NG::FrameNode>& node) const
{
    (void)event;
    if (node) {
        const_cast<EventManager*>(this)->passThroughResult_ = false;
    }
}

void EventManager::NotifyCoastingAxisEventStop() const {}

std::string EventManager::GetLastHitTestNodeInfosForTouch(bool isTopMost)
{
    (void)isTopMost;
    return {};
}

void EventManager::LogHitTestInfoRecord(const TouchEvent& touchPoint)
{
    (void)touchPoint;
}

void EventManager::ClearHitTestInfoRecord(const TouchEvent& touchPoint)
{
    (void)touchPoint;
}
} // namespace OHOS::Ace
