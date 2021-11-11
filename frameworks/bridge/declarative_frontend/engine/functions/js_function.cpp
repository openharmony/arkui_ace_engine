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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"

#include "base/json/json_util.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"

namespace OHOS::Ace::Framework {

JsFunction::JsFunction(const JSRef<JSObject>& jsObject, const JSRef<JSFunc>& jsFunction)
{
    jsThis_ = jsObject;
    jsFunction_ = jsFunction;
}

JsFunction::~JsFunction()
{
    LOGD("Destroy: JsFunction");
}

void JsFunction::Execute()
{
    JsFunction::ExecuteJS();
}

void JsFunction::Execute(std::vector<std::string> keys, const std::string& param)
{
    LOGI("param : %{private}s", param.c_str());
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(param);
    if (!argsPtr) {
        LOGW("Parse param failed!");
        return;
    }
    JSRef<JSObject> eventInfo = JSRef<JSObject>::New();
    for (auto iter = keys.begin(); iter != keys.end(); iter++) {
        const std::string key = *iter;
        const auto value = argsPtr->GetValue(key);
        if (!value) {
            LOGI("key[%{public}s] is not exist.", key.c_str());
            continue;
        }

        if (value->IsString()) {
            eventInfo->SetProperty<std::string>(key.c_str(), value->GetString().c_str());
        } else if (value->IsNumber()) {
            eventInfo->SetProperty<double>(key.c_str(), value->GetDouble());
        } else if (value->IsBool()) {
            eventInfo->SetProperty<bool>(key.c_str(), value->GetBool());
        } else if (value->IsObject()) {
            eventInfo->SetPropertyJsonObject(key.c_str(), value->ToString().c_str());
        }
    }

    JSRef<JSVal> paramObj = JSRef<JSVal>::Cast(eventInfo);
    JsFunction::ExecuteJS(1, &paramObj);
}

JSRef<JSVal> JsFunction::ExecuteJS(int argc, JSRef<JSVal> argv[])
{
    ACE_FUNCTION_TRACE();

    JSRef<JSVal> jsObject = jsThis_.Lock();
    JSRef<JSVal> result = jsFunction_->Call(jsObject, argc, argv);
    return result;
}

JSRef<JSObject> CreateEventTargetObject(const BaseEventInfo& info)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    JSRef<JSObject> target = objectTemplate->NewInstance();
    JSRef<JSObject> area = objectTemplate->NewInstance();
    JSRef<JSObject> offset = objectTemplate->NewInstance();
    JSRef<JSObject> globalOffset = objectTemplate->NewInstance();
    offset->SetProperty<double>("dx", info.GetTarget().area.GetOffset().GetX().ConvertToVp());
    offset->SetProperty<double>("dy", info.GetTarget().area.GetOffset().GetY().ConvertToVp());
    globalOffset->SetProperty<double>("dx", info.GetTarget().area.GetGlobalOffset().GetX().ConvertToVp());
    globalOffset->SetProperty<double>("dy", info.GetTarget().area.GetGlobalOffset().GetY().ConvertToVp());
    area->SetPropertyObject("pos", offset);
    area->SetPropertyObject("globalPos", globalOffset);
    area->SetProperty<double>("width", info.GetTarget().area.GetWidth().ConvertToVp());
    area->SetProperty<double>("height", info.GetTarget().area.GetHeight().ConvertToVp());
    target->SetPropertyObject("area", area);
    return target;
}

} // namespace OHOS::Ace::Framework
