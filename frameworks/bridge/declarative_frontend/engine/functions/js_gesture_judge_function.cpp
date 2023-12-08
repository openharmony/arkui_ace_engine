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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_gesture_judge_function.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/gestures/base_gesture_event.h"

namespace OHOS::Ace::Framework {

GestureJudgeResult JsGestureJudgeFunction::Execute(
    const RefPtr<NG::GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info)
{
    JSRef<JSObject> gestureInfoObj = JSRef<JSObject>::New();
    CHECK_NULL_RETURN(gestureInfo, GestureJudgeResult::CONTINUE);
    CHECK_NULL_RETURN(info, GestureJudgeResult::CONTINUE);
    if (gestureInfo->GetTag().has_value()) {
        gestureInfoObj->SetProperty<std::string>("tag", gestureInfo->GetTag().value());
    }
    gestureInfoObj->SetProperty<int32_t>("type", static_cast<int32_t>(gestureInfo->GetType()));
    gestureInfoObj->SetProperty<bool>("isSystemGesture", gestureInfo->IsSystemGesture());

    JSRef<JSObject> obj = JSRef<JSObject>::New();
    SetUniqueAttributes(obj, gestureInfo->GetType(), info);
    obj->SetProperty<double>("timestamp", info->GetTimeStamp().time_since_epoch().count());
    obj->SetProperty<double>("source", static_cast<int32_t>(info->GetSourceDevice()));
    obj->SetProperty<double>("pressure", info->GetForce());
    if (info->GetTiltX().has_value()) {
        obj->SetProperty<double>("tiltX", info->GetTiltX().value());
    }
    if (info->GetTiltY().has_value()) {
        obj->SetProperty<double>("tiltY", info->GetTiltY().value());
    }
    obj->SetProperty<double>("sourceTool", static_cast<int32_t>(info->GetSourceTool()));

    JSRef<JSArray> fingerArr = JSRef<JSArray>::New();
    const std::list<FingerInfo>& fingerList = info->GetFingerList();
    std::list<FingerInfo> notTouchFingerList;
    int32_t maxFingerId = -1;
    for (const FingerInfo& fingerInfo : fingerList) {
        JSRef<JSObject> element = CreateFingerInfo(fingerInfo);
        if (fingerInfo.sourceType_ == SourceType::TOUCH && fingerInfo.sourceTool_ == SourceTool::FINGER) {
            fingerArr->SetValueAt(fingerInfo.fingerId_, element);
            if (fingerInfo.fingerId_ > maxFingerId) {
                maxFingerId = fingerInfo.fingerId_;
            }
        } else {
            notTouchFingerList.emplace_back(fingerInfo);
        }
    }
    auto idx = maxFingerId + 1;
    for (const FingerInfo& fingerInfo : notTouchFingerList) {
        JSRef<JSObject> element = CreateFingerInfo(fingerInfo);
        fingerArr->SetValueAt(idx++, element);
    }
    obj->SetPropertyObject("fingerList", fingerArr);
    auto target = CreateEventTargetObject(info);
    obj->SetPropertyObject("target", target);
    int32_t paramCount = 2;
    JSRef<JSVal> params[paramCount];
    params[0] = gestureInfoObj;
    params[1] = obj;
    auto jsValue = JsFunction::ExecuteJS(paramCount, params);
    auto returnValue = GestureJudgeResult::CONTINUE;
    if (jsValue->IsNumber()) {
        returnValue = static_cast<GestureJudgeResult>(jsValue->ToNumber<int32_t>());
    }
    return returnValue;
}

JSRef<JSObject> JsGestureJudgeFunction::CreateFingerInfo(const FingerInfo& fingerInfo)
{
    JSRef<JSObject> fingerInfoObj = JSRef<JSObject>::New();
    const OHOS::Ace::Offset& globalLocation = fingerInfo.globalLocation_;
    const OHOS::Ace::Offset& localLocation = fingerInfo.localLocation_;
    fingerInfoObj->SetProperty<int32_t>("id", fingerInfo.fingerId_);
    fingerInfoObj->SetProperty<double>("globalX", PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX()));
    fingerInfoObj->SetProperty<double>("globalY", PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY()));
    fingerInfoObj->SetProperty<double>("localX", PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX()));
    fingerInfoObj->SetProperty<double>("localY", PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY()));
    return fingerInfoObj;
}

JSRef<JSObject> JsGestureJudgeFunction::CreateEventTargetObject(const std::shared_ptr<BaseGestureEvent>& info)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    JSRef<JSObject> target = objectTemplate->NewInstance();
    JSRef<JSObject> area = objectTemplate->NewInstance();
    JSRef<JSObject> offset = objectTemplate->NewInstance();
    JSRef<JSObject> globalOffset = objectTemplate->NewInstance();
    const auto& localOffset = info->GetTarget().area.GetOffset();
    const auto& origin = info->GetTarget().origin;
    offset->SetProperty<double>("x", localOffset.GetX().ConvertToVp());
    offset->SetProperty<double>("y", localOffset.GetY().ConvertToVp());
    globalOffset->SetProperty<double>("x", (origin.GetX().ConvertToVp() + localOffset.GetX().ConvertToVp()));
    globalOffset->SetProperty<double>("y", (origin.GetY().ConvertToVp() + localOffset.GetY().ConvertToVp()));
    area->SetPropertyObject("position", offset);
    area->SetPropertyObject("globalPosition", globalOffset);
    area->SetProperty<double>("width", info->GetTarget().area.GetWidth().ConvertToVp());
    area->SetProperty<double>("height", info->GetTarget().area.GetHeight().ConvertToVp());
    target->SetPropertyObject("area", area);
    return target;
}

void JsGestureJudgeFunction::SetUniqueAttributes(
    JSRef<JSObject>& obj, GestureTypeName typeName, const std::shared_ptr<BaseGestureEvent>& info)
{
    switch (typeName) {
        case OHOS::Ace::GestureTypeName::LONG_PRESS_GESTURE: {
            auto longPressGestureEvent = TypeInfoHelper::DynamicCast<LongPressGestureEvent>(info.get());
            if (longPressGestureEvent) {
                obj->SetProperty<bool>("repeat", longPressGestureEvent->GetRepeat());
            }
            break;
        }
        case OHOS::Ace::GestureTypeName::PAN_GESTURE: {
            auto panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(info.get());
            if (panGestureEvent) {
                obj->SetProperty<double>(
                    "offsetX", PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetOffsetX()));
                obj->SetProperty<double>(
                    "offsetY", PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetOffsetY()));
                obj->SetProperty<double>(
                    "velocityX", PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetVelocity().GetVelocityX()));
                obj->SetProperty<double>(
                    "velocityY", PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetVelocity().GetVelocityY()));
                obj->SetProperty<double>("velocity",
                    PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetVelocity().GetVelocityValue()));
            }
            break;
        }
        case OHOS::Ace::GestureTypeName::PINCH_GESTURE: {
            auto pinchGestureEvent = TypeInfoHelper::DynamicCast<PinchGestureEvent>(info.get());
            if (pinchGestureEvent) {
                obj->SetProperty<double>("scale", pinchGestureEvent->GetScale());
                obj->SetProperty<double>(
                    "pinchCenterX", PipelineBase::Px2VpWithCurrentDensity(pinchGestureEvent->GetPinchCenter().GetX()));
                obj->SetProperty<double>(
                    "pinchCenterY", PipelineBase::Px2VpWithCurrentDensity(pinchGestureEvent->GetPinchCenter().GetY()));
            }
            break;
        }
        case OHOS::Ace::GestureTypeName::ROTATION_GESTURE: {
            auto rotationGestureEvent = TypeInfoHelper::DynamicCast<RotationGestureEvent>(info.get());
            if (rotationGestureEvent) {
                obj->SetProperty<double>("angle", rotationGestureEvent->GetAngle());
            }
            break;
        }
        case OHOS::Ace::GestureTypeName::SWIPE_GESTURE: {
            auto swipeGestureEvent = TypeInfoHelper::DynamicCast<SwipeGestureEvent>(info.get());
            if (swipeGestureEvent) {
                obj->SetProperty<double>("angle", swipeGestureEvent->GetAngle());
                obj->SetProperty<double>("speed", swipeGestureEvent->GetSpeed());
            }
            break;
        }
        default:
            break;
    }
}
} // namespace OHOS::Ace::Framework
