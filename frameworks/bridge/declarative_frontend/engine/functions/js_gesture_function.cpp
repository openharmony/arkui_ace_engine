/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_gesture_function.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_common_utils.h"

namespace OHOS::Ace::Framework {
using namespace OHOS::Ace::Framework::CommonUtils;
void JsGestureFunction::Execute()
{
    JsFunction::Execute();
}

void JsGestureFunction::Execute(const GestureEvent& info)
{
    JSRef<JSVal> param = JSRef<JSObject>::Cast(CreateGestureEvent(info));
    JsFunction::ExecuteJS(1, &param);
}

JSRef<JSObject> JsGestureFunction::CreateGestureEvent(const GestureEvent& info)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> gestureInfoObj = objectTemplate->NewInstance();
    gestureInfoObj->SetProperty<bool>("repeat", info.GetRepeat());
    gestureInfoObj->SetProperty<double>("offsetX", PipelineBase::Px2VpWithCurrentDensity(info.GetOffsetX()));
    gestureInfoObj->SetProperty<double>("offsetY", PipelineBase::Px2VpWithCurrentDensity(info.GetOffsetY()));
    gestureInfoObj->SetProperty<double>("scale", info.GetScale());
    gestureInfoObj->SetProperty<double>("angle", info.GetAngle());
    gestureInfoObj->SetProperty<double>("speed", info.GetSpeed());
    gestureInfoObj->SetProperty<double>("timestamp", info.GetTimeStamp().time_since_epoch().count());
    gestureInfoObj->SetProperty<double>(
        "pinchCenterX", PipelineBase::Px2VpWithCurrentDensity(info.GetPinchCenter().GetX()));
    gestureInfoObj->SetProperty<double>(
        "pinchCenterY", PipelineBase::Px2VpWithCurrentDensity(info.GetPinchCenter().GetY()));
    gestureInfoObj->SetProperty<double>("source", static_cast<int32_t>(info.GetSourceDevice()));
    gestureInfoObj->SetProperty<double>("pressure", info.GetForce());
    gestureInfoObj->SetProperty<double>("tiltX", info.GetTiltX().value_or(0.0f));
    gestureInfoObj->SetProperty<double>("tiltY", info.GetTiltY().value_or(0.0f));
    gestureInfoObj->SetProperty<double>("rollAngle", info.GetRollAngle().value_or(0.0f));
    gestureInfoObj->SetProperty<double>("sourceTool", static_cast<int32_t>(info.GetSourceTool()));

    gestureInfoObj->SetProperty<double>(
        "velocityX", PipelineBase::Px2VpWithCurrentDensity(info.GetVelocity().GetVelocityX()));
    gestureInfoObj->SetProperty<double>(
        "velocityY", PipelineBase::Px2VpWithCurrentDensity(info.GetVelocity().GetVelocityY()));
    gestureInfoObj->SetProperty<double>(
        "velocity", PipelineBase::Px2VpWithCurrentDensity(info.GetVelocity().GetVelocityValue()));
    gestureInfoObj->SetPropertyObject(
        "getModifierKeyState",
        JSRef<JSFunc>::New<FunctionCallback>(NG::ArkTSUtils::JsGetModifierKeyState));
    gestureInfoObj->SetPropertyObject("fingerList", CreateFingerListArray(info));
    gestureInfoObj->SetPropertyObject("fingerInfos", CreateFingerInfosArray(info));
    gestureInfoObj->SetProperty<double>("deviceId", info.GetDeviceId());

    auto target = CreateEventTargetObject(info);
    gestureInfoObj->SetPropertyObject("target", target);
    gestureInfoObj->SetProperty<float>("axisVertical", info.GetVerticalAxis());
    gestureInfoObj->SetProperty<float>("axisHorizontal", info.GetHorizontalAxis());
    gestureInfoObj->SetProperty<int32_t>("targetDisplayId", info.GetTargetDisplayId());
    if (info.GetGestureTypeName() == GestureTypeName::TAP_GESTURE) {
        if (!info.GetFingerList().empty()) {
            gestureInfoObj->SetPropertyObject("tapLocation", GetTapLocation(info.GetFingerList().back()));
        }
    }
    gestureInfoObj->Wrap<GestureEvent>(const_cast<GestureEvent*> (&info));
    return gestureInfoObj;
}

JSRef<JSArray> JsGestureFunction::CreateFingerListArray(const GestureEvent& info)
{
    JSRef<JSArray> fingerArr = JSRef<JSArray>::New();
    const std::list<FingerInfo>& fingerList = info.GetFingerList();
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
    return fingerArr;
}

JSRef<JSArray> JsGestureFunction::CreateFingerInfosArray(const GestureEvent& info)
{
    JSRef<JSArray> fingerArr = JSRef<JSArray>::New();
    const std::list<FingerInfo>& fingerList = info.GetFingerList();
    std::list<FingerInfo> notTouchFingerList;
    std::vector<JSRef<JSObject>> validFingers;
    for (const FingerInfo& fingerInfo : fingerList) {
        JSRef<JSObject> element = CreateFingerInfo(fingerInfo);
        if (fingerInfo.sourceType_ == SourceType::TOUCH && fingerInfo.sourceTool_ == SourceTool::FINGER) {
            validFingers.emplace_back(element);
        } else {
            notTouchFingerList.emplace_back(fingerInfo);
        }
    }
    for (size_t i = 0; i < validFingers.size(); ++i) {
        fingerArr->SetValueAt(i, validFingers[i]);
    }
    auto idx = validFingers.size();
    for (const FingerInfo& fingerInfo : notTouchFingerList) {
        JSRef<JSObject> element = CreateFingerInfo(fingerInfo);
        fingerArr->SetValueAt(idx++, element);
    }
    return fingerArr;
}

JSRef<JSObject> JsGestureFunction::CreateFingerInfo(const FingerInfo& fingerInfo)
{
    JSRef<JSObject> fingerInfoObj = JSRef<JSObject>::New();
    const OHOS::Ace::Offset& globalLocation = fingerInfo.globalLocation_;
    const OHOS::Ace::Offset& localLocation = fingerInfo.localLocation_;
    const OHOS::Ace::Offset& screenLocation  = fingerInfo.screenLocation_;
    const OHOS::Ace::Offset& globalDisplayLocation  = fingerInfo.globalDisplayLocation_;
    fingerInfoObj->SetProperty<int32_t>("id", fingerInfo.fingerId_);
    fingerInfoObj->SetProperty<int32_t>("hand", fingerInfo.operatingHand_);
    fingerInfoObj->SetProperty<double>("globalX", PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX()));
    fingerInfoObj->SetProperty<double>("globalY", PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY()));
    fingerInfoObj->SetProperty<double>("localX", PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX()));
    fingerInfoObj->SetProperty<double>("localY", PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY()));
    fingerInfoObj->SetProperty<double>("displayX", PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX()));
    fingerInfoObj->SetProperty<double>("displayY", PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetY()));
    fingerInfoObj->SetProperty<double>(
        "globalDisplayX", PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetX()));
    fingerInfoObj->SetProperty<double>(
        "globalDisplayY", PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetY()));
    return fingerInfoObj;
}

} // namespace OHOS::Ace::Framework
