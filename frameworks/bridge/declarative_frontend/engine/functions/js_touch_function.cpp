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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_touch_function.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

#include "base/log/log.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"

namespace OHOS::Ace::Framework {

JSRef<JSObject> JsTouchFunction::CreateTouchInfo(const TouchLocationInfo& touchInfo, TouchEventInfo& info)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> touchInfoObj = objectTemplate->NewInstance();
    const OHOS::Ace::Offset& globalLocation = touchInfo.GetGlobalLocation();
    const OHOS::Ace::Offset& localLocation = touchInfo.GetLocalLocation();
    const OHOS::Ace::Offset& screenLocation = touchInfo.GetScreenLocation();
    touchInfoObj->SetProperty<int32_t>("type", static_cast<int32_t>(touchInfo.GetTouchType()));
    touchInfoObj->SetProperty<int32_t>("id", touchInfo.GetFingerId());
    touchInfoObj->SetProperty<double>("displayX", PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX()));
    touchInfoObj->SetProperty<double>("displayY", PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetY()));
    touchInfoObj->SetProperty<double>("windowX", PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX()));
    touchInfoObj->SetProperty<double>("windowY", PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY()));
    touchInfoObj->SetProperty<double>("screenX", PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX()));
    touchInfoObj->SetProperty<double>("screenY", PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY()));
    touchInfoObj->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX()));
    touchInfoObj->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY()));
    touchInfoObj->SetProperty<double>(
        "pressedTime", static_cast<double>(touchInfo.GetPressedTime().time_since_epoch().count()));
    touchInfoObj->SetProperty<double>("pressure", PipelineBase::Px2VpWithCurrentDensity(touchInfo.GetForce()));
    touchInfoObj->SetProperty<double>("width", PipelineBase::Px2VpWithCurrentDensity(touchInfo.GetWidth()));
    touchInfoObj->SetProperty<double>("height", PipelineBase::Px2VpWithCurrentDensity(touchInfo.GetHeight()));
    touchInfoObj->Wrap<TouchEventInfo>(&info);
    return touchInfoObj;
}

JSRef<JSObject> JsTouchFunction::CreateJSEventInfo(TouchEventInfo& info)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> eventObj = objectTemplate->NewInstance();
    JSRef<JSArray> touchArr = JSRef<JSArray>::New();
    JSRef<JSArray> changeTouchArr = JSRef<JSArray>::New();
    eventObj->SetProperty<double>("source", static_cast<int32_t>(info.GetSourceDevice()));
    eventObj->SetProperty<double>("timestamp", static_cast<double>(info.GetTimeStamp().time_since_epoch().count()));
    auto target = CreateEventTargetObject(info);
    eventObj->SetPropertyObject("target", target);
    eventObj->SetProperty<double>("pressure", info.GetForce());
    eventObj->SetProperty<double>("deviceId", info.GetDeviceId());
    eventObj->SetPropertyObject("preventDefault", JSRef<JSFunc>::New<FunctionCallback>(JsTouchPreventDefault));
    eventObj->SetProperty<double>("tiltX", info.GetTiltX().value_or(0.0f));
    eventObj->SetProperty<double>("tiltY", info.GetTiltY().value_or(0.0f));
    eventObj->SetProperty<double>("rollAngle", info.GetRollAngle().value_or(0.0f));
    eventObj->SetProperty<double>("sourceTool", static_cast<int32_t>(info.GetSourceTool()));
    eventObj->SetProperty<int32_t>("targetDisplayId", info.GetTargetDisplayId());

    const std::list<TouchLocationInfo>& touchList = info.GetTouches();
    uint32_t idx = 0;
    for (const TouchLocationInfo& location : touchList) {
        JSRef<JSObject> element = CreateTouchInfo(location, info);
        touchArr->SetValueAt(idx++, element);
    }
    eventObj->SetPropertyObject("touches", touchArr);

    idx = 0; // reset index counter
    const std::list<TouchLocationInfo>& changeTouch = info.GetChangedTouches();
    for (const TouchLocationInfo& change : changeTouch) {
        JSRef<JSObject> element = CreateTouchInfo(change, info);
        changeTouchArr->SetValueAt(idx++, element);
    }
    if (changeTouch.size() > 0) {
        eventObj->SetProperty<int32_t>("type", static_cast<int32_t>(changeTouch.front().GetTouchType()));
    }
    eventObj->SetPropertyObject("changedTouches", changeTouchArr);
    eventObj->SetProperty<double>("axisVertical", 0.0f);
    eventObj->SetProperty<double>("axisHorizontal", 0.0f);
    eventObj->SetPropertyObject(
        "stopPropagation", JSRef<JSFunc>::New<FunctionCallback>(JsStopPropagation));
    eventObj->SetPropertyObject(
        "getHistoricalPoints", JSRef<JSFunc>::New<FunctionCallback>(JsGetHistoricalPoints));
    eventObj->SetPropertyObject(
        "getModifierKeyState",
        JSRef<JSFunc>::New<FunctionCallback>(NG::ArkTSUtils::JsGetModifierKeyState));
    eventObj->SetPropertyObject("preventDefault", JSRef<JSFunc>::New<FunctionCallback>(JsPreventDefault));
    eventObj->Wrap<TouchEventInfo>(&info);
    return eventObj;
}

void JsTouchFunction::Execute(TouchEventInfo& info)
{
    JSRef<JSVal> param = JSRef<JSObject>::Cast(CreateJSEventInfo(info));
    JsFunction::ExecuteJS(1, &param);
}

} // namespace OHOS::Ace::Framework
