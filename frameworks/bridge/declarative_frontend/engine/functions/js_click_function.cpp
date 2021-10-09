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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"

#include "base/log/log.h"
#include "core/gestures/click_recognizer.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"

namespace OHOS::Ace::Framework {

void JsClickFunction::Execute()
{
    JsFunction::ExecuteJS();

    // This is required to request for new frame, which eventually will call
    // FlushBuild, FlushLayout and FlushRender on the dirty elements
#ifdef USE_V8_ENGINE
    V8DeclarativeEngineInstance::TriggerPageUpdate();
#elif USE_QUICKJS_ENGINE
    QJSDeclarativeEngineInstance::TriggerPageUpdate(QJSContext::Current());
#elif USE_ARK_ENGINE
    JsiDeclarativeEngineInstance::TriggerPageUpdate(JsiDeclarativeEngineInstance::GetJsRuntime());
#endif
}

void JsClickFunction::Execute(const ClickInfo& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    obj->SetProperty<double>("screenX", globalOffset.GetX());
    obj->SetProperty<double>("screenY", globalOffset.GetY());
    obj->SetProperty<double>("x", localOffset.GetX());
    obj->SetProperty<double>("y", localOffset.GetY());
    obj->SetProperty<double>("timestamp", static_cast<double>(info.GetTimeStamp().time_since_epoch().count()));

    LOGD("globalOffset.GetX() = %lf, globalOffset.GetY() = %lf, localOffset.GetX() = %lf, localOffset.GetY() = %lf",
        globalOffset.GetX(), globalOffset.GetY(), localOffset.GetX(), localOffset.GetY());

    JSRef<JSVal> param = obj;
    JsFunction::ExecuteJS(1, &param);
}

void JsClickFunction::Execute(const GestureEvent& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    obj->SetProperty<double>("screenX", globalOffset.GetX());
    obj->SetProperty<double>("screenY", globalOffset.GetY());
    obj->SetProperty<double>("x", localOffset.GetX());
    obj->SetProperty<double>("y", localOffset.GetY());
    obj->SetProperty<double>("timestamp", static_cast<double>(info.GetTimeStamp().time_since_epoch().count()));

    LOGD("globalOffset.GetX() = %lf, globalOffset.GetY() = %lf, localOffset.GetX() = %lf, localOffset.GetY() = %lf",
        globalOffset.GetX(), globalOffset.GetY(), localOffset.GetX(), localOffset.GetY());

    JSRef<JSVal> param = obj;
    JsFunction::ExecuteJS(1, &param);
}

} // namespace OHOS::Ace::Framework
