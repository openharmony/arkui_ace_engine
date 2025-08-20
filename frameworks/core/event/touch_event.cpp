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

#include "core/event/touch_event.h"

#include "base/input_manager/input_manager.h"
#include "core/common/ace_application_info.h"
#include "core/event/mouse_event.h"
#include "core/event/key_event.h"

namespace OHOS::Ace {
void TouchPoint::CovertId()
{
    if (sourceTool == SourceTool::PEN) {
        originalId = TOUCH_TOOL_BASE_ID + static_cast<int32_t>(sourceTool);
        id = id + originalId;
    }
}

int32_t TouchPoint::GetOriginalReCovertId() const
{
    if (!AceApplicationInfo::GetInstance().GetTouchPadIdChanged()) {
        return originalId;
    }
    if (sourceTool == SourceTool::PEN) {
        return originalId - TOUCH_TOOL_BASE_ID - static_cast<int32_t>(sourceTool);
    } else if (sourceTool == SourceTool::MOUSE) {
        return originalId - MOUSE_BASE_ID - static_cast<int32_t>(MouseButton::LEFT_BUTTON);
    } else {
        return originalId;
    }
}

TouchEvent& TouchEvent::SetId(int32_t id)
{
    this->id = id;
    return *this;
}

TouchEvent& TouchEvent::SetX(float x)
{
    this->x = x;
    return *this;
}

TouchEvent& TouchEvent::SetY(float y)
{
    this->y = y;
    return *this;
}

TouchEvent& TouchEvent::SetScreenX(float screenX)
{
    this->screenX = screenX;
    return *this;
}

TouchEvent& TouchEvent::SetScreenY(float screenY)
{
    this->screenY = screenY;
    return *this;
}

TouchEvent& TouchEvent::SetGlobalDisplayX(double globalDisplayX)
{
    this->globalDisplayX = globalDisplayX;
    return *this;
}

TouchEvent& TouchEvent::SetGlobalDisplayY(double globalDisplayY)
{
    this->globalDisplayY = globalDisplayY;
    return *this;
}

TouchEvent& TouchEvent::SetTime(TimeStamp time)
{
    this->time = time;
    return *this;
}

TimeStamp TouchEvent::GetTimeStamp() const
{
    return this->time;
}

TouchEvent& TouchEvent::SetType(TouchType type)
{
    this->type = type;
    return *this;
}

TouchEvent& TouchEvent::SetPullType(TouchType pullType)
{
    this->pullType = pullType;
    return *this;
}

TouchEvent& TouchEvent::SetSize(double size)
{
    this->size = size;
    return *this;
}

TouchEvent& TouchEvent::SetForce(float force)
{
    this->force = force;
    return *this;
}

TouchEvent& TouchEvent::SetTiltX(std::optional<float> tiltX)
{
    this->tiltX = tiltX;
    return *this;
}

TouchEvent& TouchEvent::SetTiltY(std::optional<float> tiltY)
{
    this->tiltY = tiltY;
    return *this;
}

TouchEvent& TouchEvent::SetRollAngle(std::optional<float> rollAngle)
{
    this->rollAngle = rollAngle;
    return *this;
}

TouchEvent& TouchEvent::SetDeviceId(int64_t deviceId)
{
    this->deviceId = deviceId;
    return *this;
}

TouchEvent& TouchEvent::SetTargetDisplayId(int32_t targetDisplayId)
{
    this->targetDisplayId = targetDisplayId;
    return *this;
}

TouchEvent& TouchEvent::SetSourceType(SourceType sourceType)
{
    this->sourceType = sourceType;
    return *this;
}

TouchEvent& TouchEvent::SetSourceTool(SourceTool sourceTool)
{
    this->sourceTool = sourceTool;
    return *this;
}

TouchEvent& TouchEvent::SetTouchEventId(int32_t touchEventId)
{
    this->touchEventId = touchEventId;
    return *this;
}

TouchEvent& TouchEvent::SetIsInterpolated(bool isInterpolated)
{
    this->isInterpolated = isInterpolated;
    return *this;
}

TouchEvent& TouchEvent::SetPointers(std::vector<TouchPoint> pointers)
{
    this->pointers = std::move(pointers);
    return *this;
}

TouchEvent& TouchEvent::SetPointerEvent(std::shared_ptr<const MMI::PointerEvent> pointerEvent)
{
    this->pointerEvent = std::move(pointerEvent);
    return *this;
}

std::shared_ptr<MMI::PointerEvent> TouchEvent::GetTouchEventPointerEvent() const
{
    return InputManager::CreatePointerEvent(pointerEvent);
}

TouchEvent& TouchEvent::SetOriginalId(int32_t originalId)
{
    this->originalId = originalId;
    return *this;
}

TouchEvent& TouchEvent::SetIsInjected(bool isInjected)
{
    this->isInjected = isInjected;
    return *this;
}

TouchEvent& TouchEvent::SetInputXDeltaSlope(float inputXDeltaSlope)
{
    this->inputXDeltaSlope = inputXDeltaSlope;
    return *this;
}

TouchEvent& TouchEvent::SetInputYDeltaSlope(float inputYDeltaSlope)
{
    this->inputYDeltaSlope = inputYDeltaSlope;
    return *this;
}

TouchEvent& TouchEvent::SetPressedKeyCodes(const std::vector<KeyCode>& pressedKeyCodes)
{
    this->pressedKeyCodes_ = pressedKeyCodes;
    return *this;
}

TouchEvent& TouchEvent::SetIsPassThroughMode(bool isPassThroughMode)
{
    this->isPassThroughMode = isPassThroughMode;
    return *this;
}

TouchEvent& TouchEvent::SetPressedTime(TimeStamp pressedTime)
{
    this->pressedTime = pressedTime;
    return *this;
}

TouchEvent& TouchEvent::SetWidth(int32_t width)
{
    this->width = width;
    return *this;
}

TouchEvent& TouchEvent::SetHeight(int32_t height)
{
    this->height = height;
    return *this;
}

TouchEvent& TouchEvent::SetOperatingHand(int32_t operatingHand)
{
    this->operatingHand = operatingHand;
    return *this;
}

TouchEvent TouchEvent::CloneWith(float scale) const
{
    return CloneWith(scale, 0.0f, 0.0f, std::nullopt);
}

TouchEvent TouchEvent::CloneWith(float scale, float offsetX, float offsetY, std::optional<int32_t> pointId) const
{
    TouchEvent event;
    event.id = pointId.has_value() ? pointId.value() : id;
    event.x = (x - offsetX) / scale;
    event.y = (y - offsetY) / scale;
    event.screenX = (screenX - offsetX) / scale;
    event.screenY = (screenY - offsetY) / scale;
    event.globalDisplayX = (globalDisplayX - offsetX) / scale;
    event.globalDisplayY = (globalDisplayY - offsetY) / scale;
    event.type = type;
    event.pullType = pullType;
    event.time = time;
    event.size = size;
    event.force = force;
    event.tiltX = tiltX;
    event.tiltY = tiltY;
    event.rollAngle = rollAngle;
    event.deviceId = deviceId;
    event.targetDisplayId = targetDisplayId;
    event.sourceType = sourceType;
    event.sourceTool = sourceTool;
    event.touchEventId = touchEventId;
    event.isInterpolated = isInterpolated;
    event.pointers = std::move(pointers);
    event.pointerEvent = std::move(pointerEvent);
    event.originalId = originalId;
    event.pressedKeyCodes_ = pressedKeyCodes_;
    event.isInjected = isInjected;
    event.isPrivacyMode = isPrivacyMode;
    event.inputXDeltaSlope = inputXDeltaSlope;
    event.inputYDeltaSlope = inputYDeltaSlope;
    event.eventType = UIInputEventType::TOUCH;
    event.isPassThroughMode = isPassThroughMode;
    event.width = width;
    event.height = height;
    event.pressedTime = pressedTime;
    event.passThrough = passThrough;
    event.operatingHand = operatingHand;
    event.convertInfo = convertInfo;
    if (passThrough) {
        event.postEventNodeId = postEventNodeId;
    }
    return event;
}

void TouchEvent::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("id", id);
    json->Put("x", x);
    json->Put("y", y);
    json->Put("sx", screenX);
    json->Put("sy", screenY);
    json->Put("ty", static_cast<int32_t>(type));
    int64_t timeValue = std::chrono::duration_cast<std::chrono::nanoseconds>(time.time_since_epoch()).count();
    json->Put("ti", timeValue);
    json->Put("si", size);
    json->Put("f", force);
    int32_t hasTiltX = tiltX.has_value() ? 1 : 0;
    json->Put("hx", hasTiltX);
    if (hasTiltX) {
        json->Put("tx", tiltX.value());
    }
    int32_t hasTiltY = tiltY.has_value() ? 1 : 0;
    json->Put("hy", hasTiltY);
    if (tiltY.has_value()) {
        json->Put("ty", tiltY.value());
    }
    int32_t hasRollAngle = rollAngle.has_value() ? 1 : 0;
    json->Put("ha", hasRollAngle);
    if (rollAngle.has_value()) {
        json->Put("ta", rollAngle.value());
    }
    json->Put("d", deviceId);
    json->Put("sty", static_cast<int32_t>(sourceType));
    json->Put("sto", static_cast<int32_t>(sourceTool));
}

void TouchEvent::FromJson(const std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(json);
    id = json->GetInt("id");
    x = json->GetDouble("x");
    y = json->GetDouble("y");
    screenX = json->GetDouble("sx");
    screenY = json->GetDouble("sy");
    type = static_cast<TouchType>(json->GetInt("ty"));
    int64_t timeValue = json->GetInt64("ti");
    time = TimeStamp(std::chrono::nanoseconds(timeValue));
    size = json->GetDouble("si");
    force = json->GetDouble("f");
    int32_t hasTiltX = json->GetInt("hx");
    int32_t hasTiltY = json->GetInt("hy");
    if (hasTiltX) {
        tiltX = json->GetDouble("tx");
    }
    if (hasTiltY) {
        tiltY = json->GetDouble("ty");
    }
    int32_t hasRollAngle = json->GetInt("ha");
    if (hasRollAngle) {
        rollAngle = json->GetDouble("ta");
    }
    deviceId = json->GetInt64("d");
    sourceType = static_cast<SourceType>(json->GetInt("sty"));
    sourceTool = static_cast<SourceTool>(json->GetInt("sto"));
}

Offset TouchEvent::GetOffset() const
{
    return Offset(x, y);
}

Offset TouchEvent::GetScreenOffset() const
{
    return Offset(screenX, screenY);
}

Offset TouchEvent::GetGlobalDisplayOffset() const
{
    return Offset(globalDisplayX, globalDisplayY);
}

void TouchEvent::CovertId()
{
    if ((sourceType == SourceType::TOUCH) && (sourceTool == SourceTool::PEN)) {
        id = id + TOUCH_TOOL_BASE_ID + static_cast<int32_t>(sourceTool);
        originalId = TOUCH_TOOL_BASE_ID + static_cast<int32_t>(sourceTool);
    }
}

int32_t TouchEvent::GetOriginalReCovertId() const
{
    if (!AceApplicationInfo::GetInstance().GetTouchPadIdChanged()) {
        return originalId;
    }
    if ((sourceType == SourceType::TOUCH) && (sourceTool == SourceTool::PEN)) {
        return originalId - TOUCH_TOOL_BASE_ID - static_cast<int32_t>(sourceTool);
    } else if (sourceType == SourceType::MOUSE) {
        return originalId - MOUSE_BASE_ID - static_cast<int32_t>(MouseButton::LEFT_BUTTON);
    } else {
        return originalId;
    }
}

TouchEvent TouchEvent::CreateScalePoint(float scale) const
{
    if (NearZero(scale)) {
        return CloneWith(1);
    }
    auto temp = pointers;
    std::for_each(temp.begin(), temp.end(), [scale](auto&& point) {
        point.x = point.x / scale;
        point.y = point.y / scale;
        point.screenX = point.screenX / scale;
        point.screenY = point.screenY / scale;
        point.globalDisplayX = point.globalDisplayX / scale;
        point.globalDisplayY = point.globalDisplayY / scale;
    });
    return CloneWith(scale);
}

TouchEvent TouchEvent::UpdateScalePoint(float scale, float offsetX, float offsetY, int32_t pointId) const
{
    auto temp = pointers;
    if (NearZero(scale)) {
        std::for_each(temp.begin(), temp.end(), [offsetX, offsetY](auto&& point) {
            point.x = point.x - offsetX;
            point.y = point.y - offsetY;
            point.screenX = point.screenX - offsetX;
            point.screenY = point.screenY - offsetY;
            point.globalDisplayX = point.globalDisplayX - offsetX;
            point.globalDisplayY = point.globalDisplayY - offsetY;
        });
        return CloneWith(1, offsetX, offsetY, pointId);
    }

    std::for_each(temp.begin(), temp.end(), [scale, offsetX, offsetY](auto&& point) {
        point.x = (point.x - offsetX) / scale;
        point.y = (point.y - offsetY) / scale;
        point.screenX = (point.screenX - offsetX) / scale;
        point.screenY = (point.screenY - offsetY) / scale;
        point.globalDisplayX = (point.globalDisplayX - offsetX) / scale;
        point.globalDisplayY = (point.globalDisplayY - offsetY) / scale;
    });
    return CloneWith(scale, offsetX, offsetY, pointId);
}

TouchEvent TouchEvent::UpdatePointers() const
{
    TouchPoint point { .id = id,
        .x = x,
        .y = y,
        .screenX = screenX,
        .screenY = screenY,
        .globalDisplayX = globalDisplayX,
        .globalDisplayY = globalDisplayY,
        .downTime = time,
        .size = size,
        .force = force,
        .isPressed = (type == TouchType::DOWN),
        .operatingHand = operatingHand };
    TouchEvent event;
    event.SetId(id)
        .SetX(x)
        .SetY(y)
        .SetScreenX(screenX)
        .SetScreenY(screenY)
        .SetGlobalDisplayX(globalDisplayX)
        .SetGlobalDisplayY(globalDisplayY)
        .SetType(type)
        .SetTime(time)
        .SetSize(size)
        .SetForce(force)
        .SetDeviceId(deviceId)
        .SetTargetDisplayId(targetDisplayId)
        .SetSourceType(sourceType)
        .SetIsInterpolated(isInterpolated)
        .SetPointerEvent(pointerEvent)
        .SetOriginalId(originalId)
        .SetIsPassThroughMode(isPassThroughMode)
        .SetOperatingHand(operatingHand);
    event.pointers.emplace_back(std::move(point));
    return event;
}

bool TouchEvent::IsPenHoverEvent() const
{
    return sourceTool == SourceTool::PEN && (type == TouchType::PROXIMITY_IN || type == TouchType::PROXIMITY_OUT ||
                                                (type == TouchType::MOVE && NearZero(force)));
}

int32_t TouchEvent::GetTargetDisplayId() const
{
    return targetDisplayId;
}

int32_t TouchEvent::GetEventIdentity() const
{
    if (passThrough) {
        return id;
    }
    return originalId;
}

void TouchCallBackInfo::SetScreenX(float screenX)
{
    screenX_ = screenX;
}

float TouchCallBackInfo::GetScreenX() const
{
    return screenX_;
}

void TouchCallBackInfo::SetScreenY(float screenY)
{
    screenY_ = screenY;
}

float TouchCallBackInfo::GetScreenY() const
{
    return screenY_;
}

void TouchCallBackInfo::SetGlobalDisplayX(double globalDisplayX)
{
    globalDisplayX_ = globalDisplayX;
}

double TouchCallBackInfo::GetGlobalDisplayX() const
{
    return globalDisplayX_;
}

void TouchCallBackInfo::SetGlobalDisplayY(double globalDisplayY)
{
    globalDisplayY_ = globalDisplayY;
}

double TouchCallBackInfo::GetGlobalDisplayY() const
{
    return globalDisplayY_;
}

void TouchCallBackInfo::SetLocalX(float localX)
{
    localX_ = localX;
}

float TouchCallBackInfo::GetLocalX() const
{
    return localX_;
}

void TouchCallBackInfo::SetLocalY(float localY)
{
    localY_ = localY;
}

float TouchCallBackInfo::GetLocalY() const
{
    return localY_;
}

void TouchCallBackInfo::SetTouchType(TouchType type)
{
    touchType_ = type;
}

TouchType TouchCallBackInfo::GetTouchType() const
{
    return touchType_;
}

void TouchCallBackInfo::SetTimeStamp(const TimeStamp& time)
{
    time_ = time;
}

TimeStamp TouchCallBackInfo::GetTimeStamp() const
{
    return time_;
}

TouchLocationInfo& TouchLocationInfo::SetGlobalLocation(const Offset& globalLocation)
{
    globalLocation_ = globalLocation;
    return *this;
}

TouchLocationInfo& TouchLocationInfo::SetLocalLocation(const Offset& localLocation)
{
    localLocation_ = localLocation;
    return *this;
}

TouchLocationInfo& TouchLocationInfo::SetScreenLocation(const Offset& screenLocation)
{
    screenLocation_ = screenLocation;
    return *this;
}

TouchLocationInfo& TouchLocationInfo::SetGlobalDisplayLocation(const Offset& globalDisplayLocation)
{
    globalDisplayLocation_ = globalDisplayLocation;
    return *this;
}

void TouchLocationInfo::SetSize(double size)
{
    size_ = size;
}

double TouchLocationInfo::GetSize() const
{
    return size_;
}

void TouchLocationInfo::SetTouchDeviceId(int64_t deviceId)
{
    touchDeviceId_ = deviceId;
}

int64_t TouchLocationInfo::GetTouchDeviceId() const
{
    return touchDeviceId_;
}

void TouchLocationInfo::SetTouchType(TouchType type)
{
    touchType_ = type;
}

void TouchLocationInfo::SetPressedTime(TimeStamp pressedTime)
{
    pressedTime_ = pressedTime;
}

TimeStamp TouchLocationInfo::GetPressedTime() const
{
    return pressedTime_;
}

void TouchLocationInfo::SetWidth(int32_t width)
{
    width_ = width;
}

int32_t TouchLocationInfo::GetWidth() const
{
    return width_;
}

void TouchLocationInfo::SetHeight(int32_t height)
{
    height_ = height;
}

int32_t TouchLocationInfo::GetHeight() const
{
    return height_;
}

void StateRecord::Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const
{
    std::stringstream oss;
    oss << "procedure: " << procedure;
    if (!state.empty()) {
        oss << ", "
            << "state: " << state << ", "
            << "disposal: " << disposal << ", "
            << "extraInfo: " << extraInfo;
    }
    oss << ", "
        << "timestamp: " << ConvertTimestampToStr(timestamp);
    dumpList.emplace_back(std::make_pair(depth, oss.str()));
}

void StateRecord::Dump(std::unique_ptr<JsonValue>& json) const
{
    json->Put("procedure", procedure.c_str());
    if (!state.empty()) {
        json->Put("state", state.c_str());
        json->Put("disposal", disposal.c_str());
        json->Put("extraInfo", extraInfo.c_str());
    }
    json->Put("timestamp", ConvertTimestampToStr(timestamp).c_str());
}

void GestureSnapshot::AddProcedure(const std::string& procedure, const std::string& extraInfo,
    const std::string& state, const std::string& disposal, int64_t timestamp)
{
    if (timestamp == 0) {
        timestamp = GetCurrentTimestamp();
    }
    stateHistory.emplace_back(StateRecord(procedure, extraInfo, state, disposal, timestamp));
}

bool GestureSnapshot::CheckNeedAddMove(const std::string& state, const std::string& disposal)
{
    return stateHistory.empty() || stateHistory.back().state != state || stateHistory.back().disposal != disposal;
}

void GestureSnapshot::Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const
{
    std::stringstream oss;
    oss << "frameNodeId: " << nodeId << ", "
        << "type: " << type << ", "
        << "depth: " << this->depth << ", " << std::hex << "id: 0x" << id << ", "
        << "parentId: 0x" << parentId;
    if (!customInfo.empty()) {
        oss << ", "
            << "customInfo: " << customInfo;
    }
    dumpList.emplace_back(std::make_pair(depth + this->depth, oss.str()));
    dumpList.emplace_back(std::make_pair(depth + 1 + this->depth, "stateHistory:"));
    for (const auto& state : stateHistory) {
        state.Dump(dumpList, depth + 1 + 1 + this->depth);
    }
}

std::string GestureSnapshot::TransTouchType(TouchType type)
{
    switch (type) {
        case TouchType::DOWN:
            return "TouchDown";
        case TouchType::MOVE:
            return "TouchMove";
        case TouchType::UP:
            return "TouchUp";
        case TouchType::CANCEL:
            return "TouchCancel";
        default:
            return std::string("Type:").append(std::to_string(static_cast<int32_t>(type)));
    }
}

std::string GestureSnapshot::TransAxisType(AxisAction action)
{
    switch (action) {
        case AxisAction::BEGIN:
            return "AxisBegin";
        case AxisAction::UPDATE:
            return "AxisUpdate";
        case AxisAction::END:
            return "AxisEnd";
        case AxisAction::CANCEL:
            return "AxisCancel";
        default:
            return std::string("Type:").append(std::to_string(static_cast<int32_t>(action)));
    }
}

std::tuple<std::string, std::string> GestureSnapshot::GetIds() const
{
    std::stringstream oss;
    oss << "0x" << std::hex << id;
    std::string idStr = oss.str();
    oss.str("");
    oss << "0x" << std::hex << parentId;
    std::string parentIdStr = oss.str();
    return std::make_tuple(idStr, parentIdStr);
}

void GestureSnapshot::Dump(std::unique_ptr<JsonValue>& json) const
{
    json->Put("frameNodeId", nodeId);
    json->Put("type", type.c_str());
    auto result = GetIds();
    json->Put("id", std::get<0>(result).c_str());
    json->Put("parentId", std::get<1>(result).c_str());
    json->Put("depth", this->depth);
    if (!customInfo.empty()) {
        json->Put("customInfo", customInfo.c_str());
    }
    std::unique_ptr<JsonValue> children = JsonUtil::CreateArray(true);
    for (const auto& state : stateHistory) {
        std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
        state.Dump(child);
        children->Put(child);
    }
    json->Put("stateHistory", children);
}

void TouchEventTarget::SetTouchRestrict(const TouchRestrict& touchRestrict)
{
    touchRestrict_ = touchRestrict;
}

void TouchEventTarget::SetGetEventTargetImpl(const GetEventTargetImpl& getEventTargetImpl)
{
    getEventTargetImpl_ = getEventTargetImpl;
}

std::optional<EventTarget> TouchEventTarget::GetEventTarget() const
{
    if (getEventTargetImpl_) {
        return getEventTargetImpl_();
    }
    return std::nullopt;
}

void TouchEventTarget::SetCoordinateOffset(const Offset& coordinateOffset)
{
    coordinateOffset_ = coordinateOffset;
}

const Offset& TouchEventTarget::GetCoordinateOffset() const
{
    return coordinateOffset_;
}

void TouchEventTarget::SetSubPipelineGlobalOffset(const Offset& subPipelineGlobalOffset, float viewScale)
{
    subPipelineGlobalOffset_ = subPipelineGlobalOffset;
    viewScale_ = viewScale;
}

bool TouchEventTarget::DispatchMultiContainerEvent(const TouchEvent& point)
{
#ifdef OHOS_STANDARD_SYSTEM
    if (!subPipelineGlobalOffset_.IsZero()) {
        auto multiContainerPoint = point.UpdateScalePoint(
            viewScale_, subPipelineGlobalOffset_.GetX(), subPipelineGlobalOffset_.GetY(), point.id);
        return DispatchEvent(multiContainerPoint);
    }
#endif
    return DispatchEvent(point);
}

bool TouchEventTarget::HandleMultiContainerEvent(const TouchEvent& point)
{
#ifdef OHOS_STANDARD_SYSTEM
    if (!subPipelineGlobalOffset_.IsZero()) {
        auto multiContainerPoint = point.UpdateScalePoint(
            viewScale_, subPipelineGlobalOffset_.GetX(), subPipelineGlobalOffset_.GetY(), point.id);
        return HandleEvent(multiContainerPoint);
    }
#endif
    return HandleEvent(point);
}

std::string TouchEventTarget::GetNodeName() const
{
    return nodeName_;
}

void TouchEventTarget::SetNodeId(int id)
{
    if (nodeId_ != -1) {
        return;
    }
    nodeId_ = id;
}

int32_t TouchEventTarget::GetNodeId() const
{
    return nodeId_;
}

void TouchEventTarget::AttachFrameNode(const WeakPtr<NG::FrameNode>& node)
{
    if (!(node_.Invalid())) {
        return;
    }
    node_ = node;
}

WeakPtr<NG::FrameNode> TouchEventTarget::GetAttachedNode() const
{
    return node_;
}

RefPtr<GestureSnapshot> TouchEventTarget::Dump() const
{
    RefPtr<GestureSnapshot> info = AceType::MakeRefPtr<GestureSnapshot>();
    info->type = GetTypeName();
    info->id = reinterpret_cast<uintptr_t>(this);
    return info;
}

void TouchEventTarget::SetTargetComponent(const RefPtr<NG::TargetComponent>& targetComponent)
{
    if (!targetComponent_) {
        targetComponent_ = targetComponent;
    }
}

RefPtr<NG::TargetComponent> TouchEventTarget::GetTargetComponent()
{
    return targetComponent_;
}

void TouchEventTarget::SetIsPostEventResult(bool isPostEventResult)
{
    isPostEventResult_ = isPostEventResult;
}

bool TouchEventTarget::IsPostEventResult() const
{
    return isPostEventResult_;
}

void TouchEventInfo::AddTouchLocationInfo(TouchLocationInfo&& info)
{
    touches_.emplace_back(info);
}

void TouchEventInfo::AddChangedTouchLocationInfo(TouchLocationInfo&& info)
{
    changedTouches_.emplace_back(info);
}

void TouchEventInfo::AddHistoryLocationInfo(TouchLocationInfo&& info)
{
    history_.emplace_back(std::move(info));
}

const std::list<TouchLocationInfo>& TouchEventInfo::GetHistory() const
{
    return history_;
}

void TouchEventInfo::AddHistoryPointerEvent(const std::shared_ptr<MMI::PointerEvent>& info)
{
    historyPointerEvent_.emplace_back(info);
}

const std::list<std::shared_ptr<MMI::PointerEvent>>& TouchEventInfo::GetHistoryPointerEvent() const
{
    return historyPointerEvent_;
}

void TouchEventInfo::SetPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    pointerEvent_ = pointerEvent;
}

const std::shared_ptr<MMI::PointerEvent>& TouchEventInfo::GetPointerEvent() const
{
    return pointerEvent_;
}

void TouchEventInfo::SetTouchEventsEnd(bool isTouchEventsEnd)
{
    isTouchEventsEnd_ = isTouchEventsEnd;
}

bool TouchEventInfo::GetTouchEventsEnd() const
{
    return isTouchEventsEnd_;
}

TouchEvent TouchEventInfo::ConvertToTouchEvent() const
{
    TouchEvent touchEvent;
    if (!changedTouches_.empty()) {
        touchEvent.x = static_cast<float>(changedTouches_.front().GetGlobalLocation().GetX());
        touchEvent.y = static_cast<float>(changedTouches_.front().GetGlobalLocation().GetY());
        touchEvent.screenX = static_cast<float>(changedTouches_.front().GetScreenLocation().GetX());
        touchEvent.screenY = static_cast<float>(changedTouches_.front().GetScreenLocation().GetY());
        touchEvent.localX = static_cast<float>(changedTouches_.front().GetLocalLocation().GetX());
        touchEvent.localY = static_cast<float>(changedTouches_.front().GetLocalLocation().GetY());
        touchEvent.globalDisplayX = static_cast<double>(changedTouches_.front().GetGlobalDisplayLocation().GetX());
        touchEvent.globalDisplayY = static_cast<double>(changedTouches_.front().GetGlobalDisplayLocation().GetY());
        touchEvent.id = changedTouches_.front().GetFingerId();
        touchEvent.force = changedTouches_.front().GetForce();
        touchEvent.type = changedTouches_.front().GetTouchType();
        touchEvent.tiltX = changedTouches_.front().GetTiltX();
        touchEvent.tiltY = changedTouches_.front().GetTiltY();
        touchEvent.rollAngle = changedTouches_.front().GetRollAngle();
        touchEvent.width = changedTouches_.front().GetWidth();
        touchEvent.height = changedTouches_.front().GetHeight();
        touchEvent.pressedTime = changedTouches_.front().GetPressedTime();
        const auto& targetLocalOffset = changedTouches_.front().GetTarget().area.GetOffset();
        const auto& targetOrigin = changedTouches_.front().GetTarget().origin;
        // width height x y globalx globaly
        touchEvent.targetPositionX = targetLocalOffset.GetX().ConvertToPx();
        touchEvent.targetPositionY = targetLocalOffset.GetY().ConvertToPx();
        touchEvent.targetGlobalPositionX = targetOrigin.GetX().ConvertToPx() + targetLocalOffset.GetX().ConvertToPx();
        touchEvent.targetGlobalPositionY = targetOrigin.GetY().ConvertToPx() + targetLocalOffset.GetY().ConvertToPx();
        touchEvent.widthArea = changedTouches_.front().GetTarget().area.GetWidth().ConvertToPx();
        touchEvent.heightArea = changedTouches_.front().GetTarget().area.GetHeight().ConvertToPx();
        // deviceid
        touchEvent.deviceId = changedTouches_.front().GetDeviceId();
        // modifierkeystates
        touchEvent.modifierKeyState = CalculateModifierKeyState(changedTouches_.front().GetPressedKeyCodes());
    }
    touchEvent.time = timeStamp_;
    return touchEvent;
}

const std::string& NativeEmbeadTouchInfo::GetEmbedId() const
{
    return embedId_;
}

const TouchEventInfo& NativeEmbeadTouchInfo::GetTouchEventInfo() const
{
    return touchEvent_;
}
const RefPtr<GestureEventResult>& NativeEmbeadTouchInfo::GetResult() const
{
    return result_;
}

} // namespace OHOS::Ace
