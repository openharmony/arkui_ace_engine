/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"

namespace OHOS::Ace::Framework {

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
    JSRef<JSObject> gestureInfoObj = JSRef<JSObject>::New();
    gestureInfoObj->SetProperty<bool>("repeat", info.GetRepeat());
    gestureInfoObj->SetProperty<double>("offsetX", info.GetOffsetX());
    gestureInfoObj->SetProperty<double>("offsetY", info.GetOffsetY());
    gestureInfoObj->SetProperty<double>("scale", info.GetScale());
    gestureInfoObj->SetProperty<double>("angle", info.GetAngle());
    gestureInfoObj->SetProperty<double>("timestamp", info.GetTimeStamp().time_since_epoch().count());
    return gestureInfoObj;
}

} // namespace OHOS::Ace::Framework
