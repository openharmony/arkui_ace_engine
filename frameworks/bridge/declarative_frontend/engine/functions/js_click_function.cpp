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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"

namespace OHOS::Ace::Framework {

void JsClickFunction::Execute()
{
    JsFunction::ExecuteJS();

    // This is required to request for new frame, which eventually will call
    // FlushBuild, FlushLayout and FlushRender on the dirty elements
#ifdef USE_ARK_ENGINE
    JsiDeclarativeEngineInstance::TriggerPageUpdate(JsiDeclarativeEngineInstance::GetCurrentRuntime());
#endif
}

void JsClickFunction::Execute(const ClickInfo& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    Offset screenOffset = info.GetScreenLocation();
    obj->SetProperty<double>("displayX", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
    obj->SetProperty<double>("displayY", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));
    obj->SetProperty<double>("windowX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    obj->SetProperty<double>("windowY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    obj->SetProperty<double>("screenX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    obj->SetProperty<double>("screenY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    obj->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    obj->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
    obj->SetProperty<double>("timestamp", static_cast<double>(info.GetTimeStamp().time_since_epoch().count()));
    obj->SetProperty<double>("source", static_cast<int32_t>(info.GetSourceDevice()));
    obj->SetPropertyObject("getModifierKeyState",
        JSRef<JSFunc>::New<FunctionCallback>(NG::ArkTSUtils::JsGetModifierKeyState));
    obj->SetProperty<double>("deviceId", static_cast<int32_t>(info.GetDeviceId()));
    auto target = CreateEventTargetObject(info);
    obj->SetPropertyObject("target", target);
    obj->SetProperty<double>("pressure", info.GetForce());
    obj->SetProperty<double>("tiltX", info.GetTiltX().value_or(0.0f));
    obj->SetProperty<double>("tiltY", info.GetTiltY().value_or(0.0f));
    obj->SetProperty<double>("sourceTool", static_cast<int32_t>(info.GetSourceTool()));
    obj->SetProperty<double>("axisVertical", 0.0f);
    obj->SetProperty<double>("axisHorizontal", 0.0f);
    obj->SetProperty<int32_t>("targetDisplayId", info.GetTargetDisplayId());

    JSRef<JSVal> param = obj;
    JsFunction::ExecuteJS(1, &param);
}

void JsClickFunction::Execute(GestureEvent& info)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> obj = objectTemplate->NewInstance();
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    Offset screenOffset = info.GetScreenLocation();
    obj->SetProperty<double>("displayX", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
    obj->SetProperty<double>("displayY", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));
    obj->SetProperty<double>("windowX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    obj->SetProperty<double>("windowY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    obj->SetProperty<double>("screenX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    obj->SetProperty<double>("screenY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    obj->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    obj->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
    obj->SetProperty<double>("timestamp", static_cast<double>(info.GetTimeStamp().time_since_epoch().count()));
    obj->SetProperty<double>("source", static_cast<int32_t>(info.GetSourceDevice()));
    obj->SetProperty<double>("pressure", info.GetForce());
    obj->SetPropertyObject("preventDefault", JSRef<JSFunc>::New<FunctionCallback>(JsClickPreventDefault));
    obj->SetPropertyObject("getModifierKeyState",
        JSRef<JSFunc>::New<FunctionCallback>(NG::ArkTSUtils::JsGetModifierKeyState));
    obj->SetProperty<double>("deviceId", static_cast<int32_t>(info.GetDeviceId()));
    obj->SetProperty<double>("tiltX", info.GetTiltX().value_or(0.0f));
    obj->SetProperty<double>("tiltY", info.GetTiltY().value_or(0.0f));
    obj->SetProperty<double>("sourceTool", static_cast<int32_t>(info.GetSourceTool()));
    obj->SetProperty<double>("axisVertical", 0.0f);
    obj->SetProperty<double>("axisHorizontal", 0.0f);
    obj->SetProperty<int32_t>("targetDisplayId", info.GetTargetDisplayId());
    auto target = CreateEventTargetObject(info);
    obj->SetPropertyObject("target", target);
    obj->Wrap<GestureEvent>(&info);
    JSRef<JSVal> param = JSRef<JSObject>::Cast(obj);
    JsFunction::ExecuteJS(1, &param);
}

void JsClickFunction::Execute(MouseInfo& info)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> obj = objectTemplate->NewInstance();
    obj->SetProperty<int32_t>("button", static_cast<int32_t>(info.GetButton()));
    obj->SetProperty<int32_t>("action", static_cast<int32_t>(info.GetAction()));
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    Offset screenOffset = info.GetScreenLocation();
    obj->SetProperty<double>("displayX", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
    obj->SetProperty<double>("displayY", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));
    obj->SetProperty<double>("windowX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    obj->SetProperty<double>("windowY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    obj->SetProperty<double>("screenX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    obj->SetProperty<double>("screenY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    obj->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    obj->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
    obj->SetProperty<double>("timestamp", static_cast<double>(info.GetTimeStamp().time_since_epoch().count()));
    obj->SetPropertyObject(
        "stopPropagation", JSRef<JSFunc>::New<FunctionCallback>(JsStopPropagation));
    obj->SetPropertyObject("getModifierKeyState",
        JSRef<JSFunc>::New<FunctionCallback>(NG::ArkTSUtils::JsGetModifierKeyState));
    obj->SetProperty<double>("deviceId", static_cast<int32_t>(info.GetDeviceId()));
    obj->SetProperty<double>("source", static_cast<int32_t>(info.GetSourceDevice()));
    obj->SetProperty<double>("pressure", info.GetForce());
    obj->SetProperty<double>("tiltX", info.GetTiltX().value_or(0.0f));
    obj->SetProperty<double>("tiltY", info.GetTiltY().value_or(0.0f));
    obj->SetProperty<double>("sourceTool", static_cast<int32_t>(info.GetSourceTool()));
    obj->SetProperty<double>("axisVertical", 0.0f);
    obj->SetProperty<double>("axisHorizontal", 0.0f);
    auto target = CreateEventTargetObject(info);
    obj->SetPropertyObject("target", target);
    obj->SetProperty<int32_t>("targetDisplayId", info.GetTargetDisplayId());
    obj->SetProperty<int32_t>("rawDeltaX", PipelineBase::Px2VpWithCurrentDensity(info.GetRawDeltaX()));
    obj->SetProperty<int32_t>("rawDeltaY", PipelineBase::Px2VpWithCurrentDensity(info.GetRawDeltaY()));
    JSRef<JSArray> pressedButtonArr = JSRef<JSArray>::New();
    auto pressedButtons = info.GetPressedButtons();
    uint32_t idx = 0;
    for (const auto& button : pressedButtons) {
        auto jsButton = JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(button)));
        pressedButtonArr->SetValueAt(idx++, jsButton);
    }
    obj->SetPropertyObject("pressedButtons", pressedButtonArr);
    obj->Wrap<MouseInfo>(&info);

    JSRef<JSVal> param = JSRef<JSObject>::Cast(obj);
    JsFunction::ExecuteJS(1, &param);
}

void JsWeakClickFunction::Execute()
{
    JsWeakFunction::ExecuteJS();

    // This is required to request for new frame, which eventually will call
    // FlushBuild, FlushLayout and FlushRender on the dirty elements
#ifdef USE_ARK_ENGINE
    JsiDeclarativeEngineInstance::TriggerPageUpdate(JsiDeclarativeEngineInstance::GetCurrentRuntime());
#endif
}

void JsWeakClickFunction::Execute(const ClickInfo& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    Offset screenOffset = info.GetScreenLocation();
    obj->SetProperty<double>("displayX", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
    obj->SetProperty<double>("displayY", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));
    obj->SetProperty<double>("windowX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    obj->SetProperty<double>("windowY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    obj->SetProperty<double>("screenX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    obj->SetProperty<double>("screenY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    obj->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    obj->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
    obj->SetProperty<double>("timestamp", static_cast<double>(info.GetTimeStamp().time_since_epoch().count()));
    obj->SetProperty<double>("source", static_cast<int32_t>(info.GetSourceDevice()));
    obj->SetPropertyObject("getModifierKeyState",
        JSRef<JSFunc>::New<FunctionCallback>(NG::ArkTSUtils::JsGetModifierKeyState));
    obj->SetProperty<double>("deviceId", static_cast<int32_t>(info.GetDeviceId()));
    auto target = CreateEventTargetObject(info);
    obj->SetPropertyObject("target", target);
    obj->SetProperty<double>("pressure", info.GetForce());
    obj->SetProperty<double>("tiltX", info.GetTiltX().value_or(0.0f));
    obj->SetProperty<double>("tiltY", info.GetTiltY().value_or(0.0f));
    obj->SetProperty<double>("sourceTool", static_cast<int32_t>(info.GetSourceTool()));
    obj->SetProperty<double>("axisVertical", 0.0f);
    obj->SetProperty<double>("axisHorizontal", 0.0f);

    JSRef<JSVal> param = obj;
    JsWeakFunction::ExecuteJS(1, &param);
}

void JsWeakClickFunction::Execute(GestureEvent& info)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> obj = objectTemplate->NewInstance();
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    Offset screenOffset = info.GetScreenLocation();
    obj->SetProperty<double>("displayX", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
    obj->SetProperty<double>("displayY", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));
    obj->SetProperty<double>("windowX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    obj->SetProperty<double>("windowY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    obj->SetProperty<double>("screenX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    obj->SetProperty<double>("screenY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    obj->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    obj->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
    obj->SetProperty<double>("timestamp", static_cast<double>(info.GetTimeStamp().time_since_epoch().count()));
    obj->SetProperty<double>("source", static_cast<int32_t>(info.GetSourceDevice()));
    obj->SetProperty<double>("pressure", info.GetForce());
    obj->SetPropertyObject("preventDefault", JSRef<JSFunc>::New<FunctionCallback>(JsClickPreventDefault));
    obj->SetPropertyObject("getModifierKeyState",
        JSRef<JSFunc>::New<FunctionCallback>(NG::ArkTSUtils::JsGetModifierKeyState));
    obj->SetProperty<double>("deviceId", static_cast<int32_t>(info.GetDeviceId()));
    obj->SetProperty<double>("tiltX", info.GetTiltX().value_or(0.0f));
    obj->SetProperty<double>("tiltY", info.GetTiltY().value_or(0.0f));
    obj->SetProperty<double>("sourceTool", static_cast<int32_t>(info.GetSourceTool()));
    obj->SetProperty<double>("axisVertical", 0.0f);
    obj->SetProperty<double>("axisHorizontal", 0.0f);
    auto target = CreateEventTargetObject(info);
    obj->SetPropertyObject("target", target);
    obj->Wrap<GestureEvent>(&info);
    JSRef<JSVal> param = JSRef<JSObject>::Cast(obj);
    JsWeakFunction::ExecuteJS(1, &param);
}

void JsWeakClickFunction::Execute(MouseInfo& info)
{
    JSRef<JSObjTemplate> objTemp = JSRef<JSObjTemplate>::New();
    objTemp->SetInternalFieldCount(1);
    JSRef<JSObject> obj = objTemp->NewInstance();
    Offset localOffset = info.GetLocalLocation();
    Offset globalOffset = info.GetGlobalLocation();
    Offset screenOffset = info.GetScreenLocation();
    obj->SetProperty<int32_t>("button", static_cast<int32_t>(info.GetButton()));
    obj->SetProperty<int32_t>("action", static_cast<int32_t>(info.GetAction()));
    obj->SetProperty<double>("displayX", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
    obj->SetProperty<double>("displayY", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));
    obj->SetProperty<double>("windowX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    obj->SetProperty<double>("windowY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    obj->SetProperty<double>("screenX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    obj->SetProperty<double>("screenY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    obj->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    obj->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
    obj->SetProperty<double>("timestamp", static_cast<double>(info.GetTimeStamp().time_since_epoch().count()));
    obj->SetPropertyObject(
        "stopPropagation", JSRef<JSFunc>::New<FunctionCallback>(JsStopPropagation));
    obj->SetPropertyObject("getModifierKeyState",
        JSRef<JSFunc>::New<FunctionCallback>(NG::ArkTSUtils::JsGetModifierKeyState));
    obj->SetProperty<double>("deviceId", static_cast<int32_t>(info.GetDeviceId()));
    obj->SetProperty<double>("source", static_cast<int32_t>(info.GetSourceDevice()));
    obj->SetProperty<double>("pressure", info.GetForce());
    obj->SetProperty<double>("tiltX", info.GetTiltX().value_or(0.0f));
    obj->SetProperty<double>("tiltY", info.GetTiltY().value_or(0.0f));
    obj->SetProperty<double>("sourceTool", static_cast<int32_t>(info.GetSourceTool()));
    obj->SetProperty<double>("axisVertical", 0.0f);
    obj->SetProperty<double>("axisHorizontal", 0.0f);
    auto target = CreateEventTargetObject(info);
    obj->SetPropertyObject("target", target);
    obj->SetProperty<int32_t>("targetDisplayId", info.GetTargetDisplayId());
    obj->SetProperty<int32_t>("rawDeltaX", PipelineBase::Px2VpWithCurrentDensity(info.GetRawDeltaX()));
    obj->SetProperty<int32_t>("rawDeltaY", PipelineBase::Px2VpWithCurrentDensity(info.GetRawDeltaY()));
    JSRef<JSArray> pressedButtonArr = JSRef<JSArray>::New();
    auto pressedButtons = info.GetPressedButtons();
    uint32_t idx = 0;
    for (const auto& button : pressedButtons) {
        auto jsButton = JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(button)));
        pressedButtonArr->SetValueAt(idx++, jsButton);
    }
    obj->SetPropertyObject("pressedButtons", pressedButtonArr);
    obj->Wrap<MouseInfo>(&info);

    JSRef<JSVal> param = JSRef<JSObject>::Cast(obj);
    JsWeakFunction::ExecuteJS(1, &param);
}

} // namespace OHOS::Ace::Framework
