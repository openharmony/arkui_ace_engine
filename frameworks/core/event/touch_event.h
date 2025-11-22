/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TOUCH_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TOUCH_EVENT_H

#include <utility>

#include "ui/event/touch_event.h"
#include "core/components_ng/event/event_constants.h"
#include "core/components_ng/event/target_component.h"
#include "core/event/axis_event.h"

namespace OHOS::Ace {

enum class MouseAction : int32_t {
    NONE = 0,
    PRESS = 1,
    RELEASE = 2,
    MOVE = 3,
    WINDOW_ENTER = 4,
    WINDOW_LEAVE = 5,
    HOVER,
    HOVER_ENTER,
    HOVER_MOVE,
    HOVER_EXIT,
    PULL_DOWN,
    PULL_MOVE,
    PULL_UP,
    CANCEL
};

namespace Platform {
ACE_FORCE_EXPORT Offset GetTouchEventOriginOffset(const TouchEvent& event);
ACE_FORCE_EXPORT TimeStamp GetTouchEventOriginTimeStamp(const TouchEvent& event);
ACE_FORCE_EXPORT void UpdatePressedKeyCodes(std::vector<KeyCode>& pressedKeyCodes);
} // namespace Platform

struct TouchRestrict final {
    static constexpr uint32_t NONE = 0x00000000;
    static constexpr uint32_t CLICK = 0x00000001;
    static constexpr uint32_t LONG_PRESS = 0x00000010;
    static constexpr uint32_t SWIPE_LEFT = 0x00000100;
    static constexpr uint32_t SWIPE_RIGHT = 0x00000200;
    static constexpr uint32_t SWIPE_UP = 0x00000400;
    static constexpr uint32_t SWIPE_DOWN = 0x00000800;
    static constexpr uint32_t SWIPE = 0x00000F00;
    static constexpr uint32_t SWIPE_VERTICAL = 0x0000C00;   // Vertical
    static constexpr uint32_t SWIPE_HORIZONTAL = 0x0000300; // Horizontal
    static constexpr uint32_t TOUCH = 0xFFFFFFFF;
    uint32_t forbiddenType = NONE;

    void UpdateForbiddenType(uint32_t gestureType)
    {
        forbiddenType |= gestureType;
    }
    TouchEvent touchEvent = {};
    std::list<std::string> childTouchTestList = {};
    SourceType sourceType = SourceType::NONE;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    SourceType hitTestType = SourceType::TOUCH;
    MouseAction mouseAction = MouseAction::NONE;
    InputEventType inputEventType = InputEventType::TOUCH_SCREEN;
    // use to dump event tree
    NG::EventTreeType touchTestType = NG::EventTreeType::TOUCH;
    bool isCoastingAxisEvent = false;
};

class TouchCallBackInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(TouchCallBackInfo, BaseEventInfo);

public:
    explicit TouchCallBackInfo(TouchType type) : BaseEventInfo("onTouchEvent"), touchType_(type) {}
    ~TouchCallBackInfo() override = default;

    void SetScreenX(float screenX);
    float GetScreenX() const;
    void SetScreenY(float screenY);
    float GetScreenY() const;
    void SetGlobalDisplayX(double globalDisplayX);
    double GetGlobalDisplayX() const;
    void SetGlobalDisplayY(double globalDisplayY);
    double GetGlobalDisplayY() const;
    void SetLocalX(float localX);
    float GetLocalX() const;
    void SetLocalY(float localY);
    float GetLocalY() const;
    void SetTouchType(TouchType type);
    TouchType GetTouchType() const;
    void SetTimeStamp(const TimeStamp& time);
    TimeStamp GetTimeStamp() const;

private:
    double globalDisplayX_ = 0.0;
    double globalDisplayY_ = 0.0;
    float screenX_ = 0.0f;
    float screenY_ = 0.0f;
    float localX_ = 0.0f;
    float localY_ = 0.0f;
    TouchType touchType_ = TouchType::UNKNOWN;
    TimeStamp time_;
};

using GetEventTargetImpl = std::function<std::optional<EventTarget>()>;

struct StateRecord {
    std::string procedure;
    std::string extraInfo;
    std::string state;
    std::string disposal;
    int64_t timestamp = 0;

    StateRecord(const std::string& procedure, const std::string& extraInfo, const std::string& state,
        const std::string& disposal, int64_t timestamp) : procedure(procedure), extraInfo(extraInfo),
        state(state), disposal(disposal), timestamp(timestamp)
    {}
    void Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const;
    void Dump(std::unique_ptr<JsonValue>& json) const;
};

struct GestureSnapshot : public virtual AceType {
    DECLARE_ACE_TYPE(GestureSnapshot, AceType);

public:
    void AddProcedure(const std::string& procedure, const std::string& extraInfo,
        const std::string& state, const std::string& disposal, int64_t timestamp);
    bool CheckNeedAddMove(const std::string& state, const std::string& disposal);
    void Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const;
    static std::string TransTouchType(TouchType type);
    static std::string TransAxisType(AxisAction action);
    std::tuple<std::string, std::string> GetIds() const;
    void Dump(std::unique_ptr<JsonValue>& json) const;

    int32_t nodeId = -1;
    std::string type;
    uint64_t id = 0;
    uint64_t parentId = 0;
    int32_t depth = 0;
    std::string customInfo;
    std::list<StateRecord> stateHistory;
};

class ACE_FORCE_EXPORT TouchEventTarget : public virtual AceType {
    DECLARE_ACE_TYPE(TouchEventTarget, AceType);

public:
    TouchEventTarget() = default;
    TouchEventTarget(std::string nodeName, int32_t nodeId) : nodeName_(std::move(nodeName)), nodeId_(nodeId) {}
    ~TouchEventTarget() override = default;

    // if return false means need to stop event dispatch.
    virtual bool DispatchEvent(const TouchEvent& point) = 0;
    // if return false means need to stop event bubbling.
    virtual bool HandleEvent(const TouchEvent& point) = 0;
    virtual bool HandleEvent(const AxisEvent& event)
    {
        return true;
    }
    virtual void OnFlushTouchEventsBegin() {}
    virtual void OnFlushTouchEventsEnd() {}
    virtual Axis GetAxisDirection()
    {
        return direction_;
    }
    void SetTouchRestrict(const TouchRestrict& touchRestrict);
    void SetGetEventTargetImpl(const GetEventTargetImpl& getEventTargetImpl);
    std::optional<EventTarget> GetEventTarget() const;
    // Coordinate offset is used to calculate the local location of the touch point in the render node.
    void SetCoordinateOffset(const Offset& coordinateOffset);
    // Gets the coordinate offset to calculate the local location of the touch point by manually.
    const Offset& GetCoordinateOffset() const;
    void SetSubPipelineGlobalOffset(const Offset& subPipelineGlobalOffset, float viewScale);
    bool DispatchMultiContainerEvent(const TouchEvent& point);
    bool HandleMultiContainerEvent(const TouchEvent& point);
    std::string GetNodeName() const;
    void SetNodeId(int id);
    int32_t GetNodeId() const;
    virtual void AttachFrameNode(const WeakPtr<NG::FrameNode>& node);
    WeakPtr<NG::FrameNode> GetAttachedNode() const;
    virtual RefPtr<GestureSnapshot> Dump() const;
    void SetTargetComponent(const RefPtr<NG::TargetComponent>& targetComponent);
    RefPtr<NG::TargetComponent> GetTargetComponent();
    void SetIsPostEventResult(bool isPostEventResult);
    bool IsPostEventResult() const;

private:
    virtual bool ShouldResponse()
    {
        return true;
    };

protected:
    TouchRestrict touchRestrict_ { TouchRestrict::NONE };
    WeakPtr<NG::FrameNode> node_ = nullptr;
    Offset coordinateOffset_;
    Offset subPipelineGlobalOffset_;
    GetEventTargetImpl getEventTargetImpl_;
    std::string nodeName_ = "NULL";
    RefPtr<NG::TargetComponent> targetComponent_;
    std::optional<TimeStamp> firstInputTime_;
    float viewScale_ = 1.0f;
    int32_t nodeId_ = -1;
    Axis direction_ = Axis::NONE;
    bool isPostEventResult_ = false;
};

using TouchTestResult = std::list<RefPtr<TouchEventTarget>>;
using ResponseLinkResult = std::list<RefPtr<NG::NGGestureRecognizer>>;

class ACE_EXPORT GestureEventResult : public AceType {
    DECLARE_ACE_TYPE(GestureEventResult, AceType);

public:
    GestureEventResult() = default;
    ~GestureEventResult() = default;

    virtual void SetGestureEventResult(bool result) = 0;
    virtual void SetGestureEventResult(bool result, bool stopPropagation) = 0;
};

class NativeEmbeadTouchInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(NativeEmbeadTouchInfo, BaseEventInfo);

public:
    NativeEmbeadTouchInfo(
        const std::string& embedId, const TouchEventInfo& touchEventInfo, const RefPtr<GestureEventResult>& result)
        : BaseEventInfo("NativeEmbeadTouchInfo"), embedId_(embedId), touchEvent_(touchEventInfo), result_(result)
    {}
    ~NativeEmbeadTouchInfo() override = default;
    const std::string& GetEmbedId() const;
    const TouchEventInfo& GetTouchEventInfo() const;
    const RefPtr<GestureEventResult>& GetResult() const;

private:
    std::string embedId_;
    TouchEventInfo touchEvent_;
    RefPtr<GestureEventResult> result_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TOUCH_EVENT_H
