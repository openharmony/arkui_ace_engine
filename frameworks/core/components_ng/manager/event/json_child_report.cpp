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

#include "core/components_ng/manager/event/json_child_report.h"

#include "interfaces/inner_api/ace_kit/include/ui/base/geometry/point.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/log/event_report.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/manager/event/json_report.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/event/touch_event.h"

namespace OHOS::Ace::NG {
std::shared_ptr<InspectorJsonValue> TapJsonReport::GetJsonData() const
{
    auto touchValue = InspectorJsonUtil::CreateArray();
    touchValue->Put(GetPoint().GetX());
    touchValue->Put(GetPoint().GetY());
    auto value = InspectorJsonUtil::Create();
    value->Put("GestureType", "Tap");
    value->Put("id", GetId());
    value->Put("point", touchValue);
    value->Put("count", count_);
    value->Put("fingers", GetFingerList().size());
    return value;
}

std::shared_ptr<InspectorJsonValue> LongPressJsonReport::GetJsonData() const
{
    int32_t convertToMs = 1000000;
    int64_t duration = duration_ / convertToMs;
    auto touchValue = InspectorJsonUtil::CreateArray();
    touchValue->Put(GetPoint().GetX());
    touchValue->Put(GetPoint().GetY());
    auto value = InspectorJsonUtil::Create();
    value->Put("GestureType", "LongPress");
    value->Put("id", GetId());
    value->Put("action", "end");
    value->Put("point", touchValue);
    value->Put("actualDuration", duration);
    return value;
}

std::shared_ptr<InspectorJsonValue> PanJsonReport::GetJsonData() const
{
    auto touchValue = InspectorJsonUtil::CreateArray();
    touchValue->Put(GetPoint().GetX());
    touchValue->Put(GetPoint().GetY());
    auto value = InspectorJsonUtil::Create();
    switch (GetCallBackType()) {
        case GestureCallbackType::START:
            value->Put("GestureType", "Pan");
            value->Put("id", GetId());
            value->Put("action", "start");
            value->Put("point", touchValue);
            value->Put("direction", direction_);
            break;
        case GestureCallbackType::END:
            value->Put("GestureType", "Pan");
            value->Put("id", GetId());
            value->Put("action", "end");
            value->Put("point", touchValue);
            value->Put("direction", direction_);
            break;
        case GestureCallbackType::CANCEL:
            value->Put("GestureType", "Pan");
            value->Put("action", "cancel");
            break;
        default:
            break;
    }
    return value;
}

std::shared_ptr<InspectorJsonValue> PinchJsonReport::GetJsonData() const
{
    auto value = InspectorJsonUtil::Create();
    auto touchValue = InspectorJsonUtil::CreateArray();
    for (auto& fingerList : GetFingerList()) {
        auto point = fingerList.globalLocation_;
        auto touchValueChild = InspectorJsonUtil::CreateArray();
        touchValueChild->Put(point.GetX());
        touchValueChild->Put(point.GetY());
        touchValue->Put(touchValueChild);
    }
    switch (GetCallBackType()) {
        case GestureCallbackType::START:
            value->Put("GestureType", "Pinch");
            value->Put("id", GetId());
            value->Put("action", "start");
            value->Put("point", touchValue);
            value->Put("fingers", GetFingerList().size());
            break;
        case GestureCallbackType::END:
            value->Put("GestureType", "Pinch");
            value->Put("id", GetId());
            value->Put("action", "end");
            value->Put("point", touchValue);
            value->Put("fingers", GetFingerList().size());
            value->Put("scale", scale_);
            break;
        case GestureCallbackType::CANCEL:
            value->Put("GestureType", "Pinch");
            value->Put("action", "cancel");
            break;
        default:
            break;
    }
    return value;
}

std::shared_ptr<InspectorJsonValue> RotationJsonReport::GetJsonData() const
{
    auto touchValue = InspectorJsonUtil::CreateArray();
    for (auto& fingerList : GetFingerList()) {
        auto point = fingerList.globalLocation_;
        auto touchValueChild = InspectorJsonUtil::CreateArray();
        touchValueChild->Put(point.GetX());
        touchValueChild->Put(point.GetY());
        touchValue->Put(touchValueChild);
    }
    auto value = InspectorJsonUtil::Create();
    switch (GetCallBackType()) {
        case GestureCallbackType::START:
            value->Put("GestureType", "Rotation");
            value->Put("id", GetId());
            value->Put("action", "start");
            value->Put("point", touchValue);
            value->Put("fingers", GetFingerList().size());
            break;
        case GestureCallbackType::END:
            value->Put("GestureType", "Rotation");
            value->Put("id", GetId());
            value->Put("action", "end");
            value->Put("point", touchValue);
            value->Put("fingers", GetFingerList().size());
            value->Put("angle", angle_);
            break;
        case GestureCallbackType::CANCEL:
            value->Put("GestureType", "Rotation");
            value->Put("action", "cancel");
            break;
        default:
            break;
    }
    return value;
}

std::shared_ptr<InspectorJsonValue> SwipeJsonReport::GetJsonData() const
{
    double speed = Dimension(speed_, DimensionUnit::PX).ConvertToVp();
    double resultSpeed = Dimension(actualSpeed_, DimensionUnit::PX).ConvertToVp();
    auto upValue = InspectorJsonUtil::CreateArray();
    for (auto& fingerList : GetFingerList()) {
        auto point = fingerList.globalLocation_;
        auto upTouchValueChild = InspectorJsonUtil::CreateArray();
        upTouchValueChild->Put(point.GetX());
        upTouchValueChild->Put(point.GetY());
        upValue->Put(upTouchValueChild);
    }
    auto downValue = InspectorJsonUtil::CreateArray();
    for (auto& downEvent : touchEvents_) {
        auto point = downEvent.second;
        auto downTouchValueChild = InspectorJsonUtil::CreateArray();
        downTouchValueChild->Put(point.x);
        downTouchValueChild->Put(point.y);
        downValue->Put(downTouchValueChild);
    }
    auto value = InspectorJsonUtil::Create();
    value->Put("GestureType", "Swipe");
    value->Put("id", GetId());
    value->Put("upPoint", upValue);
    if (downValue->ToString() == "[]") {
        value->Put("downPoint", upValue);
    } else {
        value->Put("downPoint", downValue);
    }
    value->Put("direction", direction_);
    value->Put("speed", speed);
    value->Put("actualSpeed", resultSpeed);
    return value;
}

std::shared_ptr<InspectorJsonValue> ClickJsonReport::GetJsonData() const
{
    auto touchValue = InspectorJsonUtil::CreateArray();
    touchValue->Put(GetPoint().GetX());
    touchValue->Put(GetPoint().GetY());
    auto value = InspectorJsonUtil::Create();
    value->Put("GestureType", "Click");
    value->Put("id", GetId());
    value->Put("point", touchValue);
    value->Put("count", count_);
    value->Put("fingers", GetFingerList().size());
    return value;
}

std::shared_ptr<InspectorJsonValue> DragJsonReport::GetJsonData() const
{
    auto value = InspectorJsonUtil::Create();
    if (pharse_ == DragReporterPharse::DRAG_START) {
        auto touchValue = InspectorJsonUtil::CreateArray();
        touchValue->Put(startPoint_.GetX());
        touchValue->Put(startPoint_.GetY());
        value->Put("GestureType", "DragStart");
        value->Put("id", startId_);
        value->Put("point", touchValue);
        value->Put("hostName", hostName_.c_str());
        value->Put("actualDuration", actualDuration_);
    } else {
        auto touchValue = InspectorJsonUtil::CreateArray();
        touchValue->Put(endPoint_.GetX());
        touchValue->Put(endPoint_.GetY());
        value->Put("GestureType", "DrageEnd");
        value->Put("point", touchValue);
        if (dropResult_ == DropResult::DROP_SUCCESS) {
            value->Put("dropResult", "success");
            value->Put("id", dropId_);
        } else {
            value->Put("dropResult", "fail");
        }
        value->Put("hostName", hostName_.c_str());
    }
    return value;
}
} // namespace OHOS::Ace::NG
