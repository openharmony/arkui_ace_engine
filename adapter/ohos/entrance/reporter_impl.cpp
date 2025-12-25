/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "reporter_impl.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/utils/system_properties.h"
#include "core/components_ng/manager/event/json_child_report.h"
#include "frameworks/base/utils/time_util.h"
#include "frameworks/core/common/layout_inspector.h"
#include "frameworks/core/components_ng/manager/event/json_report.h"
#include "frameworks/core/event/axis_event.h"
#include "frameworks/core/event/key_event.h"
#include "frameworks/core/event/mouse_event.h"
#include "frameworks/core/event/touch_event.h"
namespace OHOS::Ace::NG {
Reporter& Reporter::GetInstance()
{
    static ReporterImpl singleInstance;
    return singleInstance;
}

void ReporterImpl::HandleUISessionReporting(const JsonReport& report) const
{
    auto value = report.GetJsonData();
    CHECK_NULL_VOID(value);
    if (value->IsNull()) {
        return;
    }
    TAG_LOGD(
        AceLogTag::ACE_GESTURE, "UISession JsonString " SEC_PLD("%{public}s"), SEC_PARAM(value->ToString().c_str()));
    UiSessionManager::GetInstance()->ReportComponentChangeEvent(report.GetId(), "event", value);
}

static const std::unordered_map<TouchType, std::string> TOUCH_TYPE_CONVERT_MAP {
    { TouchType::DOWN, "Down" },
    { TouchType::UP, "Up" },
    { TouchType::MOVE, "Move" },
    { TouchType::CANCEL, "Cancel" },
};

static const std::unordered_map<AxisAction, std::string> AXIS_ACTION_CONVERT_MAP { { AxisAction::BEGIN, "Begin" },
    { AxisAction::UPDATE, "Update" }, { AxisAction::END, "End" }, { AxisAction::CANCEL, "Cancel" },
    { AxisAction::NONE, "None" } };

static const std::unordered_map<MouseAction, std::string> MOUSE_ACTION_CONVERT_MAP { { MouseAction::PRESS, "Press" },
    { MouseAction::RELEASE, "Release" }, { MouseAction::MOVE, "Move" }, { MouseAction::WINDOW_ENTER, "WindowEnter" },
    { MouseAction::WINDOW_LEAVE, "WindowLeave" }, { MouseAction::CANCEL, "Cancel" } };

static const std::unordered_map<MouseButton, std::string> MOUSE_BUTTON_CONVERT_MAP {
    { MouseButton::LEFT_BUTTON, "Left" }, { MouseButton::RIGHT_BUTTON, "Right" },
    { MouseButton::MIDDLE_BUTTON, "Middle" }, { MouseButton::BACK_BUTTON, "Back" },
    { MouseButton::FORWARD_BUTTON, "Forward" }, { MouseButton::NONE_BUTTON, "None" }
};

void ReporterImpl::HandleInspectorReporting(const JsonReport& report) const
{
    auto value = report.GetJsonData();
    CHECK_NULL_VOID(value);
    if (value->IsNull()) {
        return;
    }
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "Inspector JsonString %{public}s", value->ToString().c_str());
    }
    LayoutInspector::SendMessage(value->ToString());
}

void ReporterImpl::HandleInputEventInspectorReporting(const TouchEvent& event) const
{
    if (!LayoutInspector::GetInteractionEventStatus()) {
        return;
    }
    if (event.sourceType != SourceType::TOUCH) {
        return;
    }
    auto actionIter = TOUCH_TYPE_CONVERT_MAP.find(event.type);
    if (actionIter == TOUCH_TYPE_CONVERT_MAP.end()) {
        return;
    }
    NG::TouchJsonReport touchReport;
    touchReport.SetAction(actionIter->second);
    touchReport.SetEventType("TouchScreen");
    touchReport.SetTime(event.time);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    uint32_t windowId = container->GetWindowId();
    touchReport.SetWindowID(windowId);
    Point touchPoint(event.x, event.y);
    touchReport.SetPoint(touchPoint);
    HandleInspectorReporting(touchReport);
}

void ReporterImpl::HandleInputEventInspectorReporting(const MouseEvent& event) const
{
    if (!LayoutInspector::GetInteractionEventStatus()) {
        return;
    }
    if (event.sourceType != SourceType::MOUSE || (event.convertInfo.first != event.convertInfo.second)) {
        return;
    }
    auto iter = MOUSE_ACTION_CONVERT_MAP.find(event.action);
    if (iter == MOUSE_ACTION_CONVERT_MAP.end()) {
        return;
    }
    auto buttonIter = MOUSE_BUTTON_CONVERT_MAP.find(event.button);
    if (buttonIter == MOUSE_BUTTON_CONVERT_MAP.end()) {
        return;
    }
    NG::MouseJsonReport mouseReport;
    mouseReport.SetAction(iter->second);
    mouseReport.SetMouseButton(buttonIter->second);
    mouseReport.SetEventType("Mouse");
    mouseReport.SetTime(event.time);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    uint32_t windowId = container->GetWindowId();
    mouseReport.SetWindowID(windowId);
    Point mousePoint(event.x, event.y);
    mouseReport.SetPoint(mousePoint);
    HandleInspectorReporting(mouseReport);
}

void ReporterImpl::HandleInputEventInspectorReporting(const AxisEvent& event) const
{
    if (!LayoutInspector::GetInteractionEventStatus()) {
        return;
    }
    if (event.sourceType != SourceType::MOUSE) {
        return;
    }
    auto iter = AXIS_ACTION_CONVERT_MAP.find(event.action);
    if (iter == AXIS_ACTION_CONVERT_MAP.end()) {
        return;
    }
    NG::AxisJsonReport axisReport;
    axisReport.SetAction(iter->second);
    axisReport.SetEventType("Axis");
    axisReport.SetTime(event.time);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    uint32_t windowId = container->GetWindowId();
    axisReport.SetWindowID(windowId);
    Point axisPoint(event.x, event.y);
    axisReport.SetPoint(axisPoint);
    AxisValue axisValues = { event.horizontalAxis, event.verticalAxis, event.pinchAxisScale, event.rotateAxisAngle };
    axisReport.SetAxisValues(axisValues);
    HandleInspectorReporting(axisReport);
}

void ReporterImpl::HandleInputEventInspectorReporting(const KeyEvent& event) const
{
    if (!LayoutInspector::GetInteractionEventStatus()) {
        return;
    }
    NG::KeyJsonReport keyReport;
    keyReport.SetEventType("Key");
    switch (event.action) {
        case KeyAction::DOWN:
            keyReport.SetAction("Down");
            break;
        case KeyAction::UP:
            keyReport.SetAction("Up");
            break;
        default: {
            return;
        }
    }
    keyReport.SetTime(event.timeStamp);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    uint32_t windowId = container->GetWindowId();
    keyReport.SetWindowID(windowId);
    keyReport.SetKeyCode(static_cast<int32_t>(event.code));
    HandleInspectorReporting(keyReport);
}

void ReporterImpl::HandleWindowFocusInspectorReporting(bool isFocus) const
{
    if (!LayoutInspector::GetInteractionEventStatus()) {
        return;
    }
    NG::FocusJsonReport focusReport;
    focusReport.SetEventType("WindowFocus");
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    uint32_t windowId = container->GetWindowId();
    if (isFocus) {
        focusReport.SetAction("Focus");
    } else {
        focusReport.SetAction("Blur");
    }
    focusReport.SetWindowID(windowId);
    TimeStamp currentDetectorTimeStamp = std::chrono::high_resolution_clock::now();
    focusReport.SetTime(currentDetectorTimeStamp);
    focusReport.SetIsFocus(isFocus);
    HandleInspectorReporting(focusReport);
}
} // namespace OHOS::Ace::NG