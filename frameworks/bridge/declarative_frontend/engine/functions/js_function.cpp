/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
#include "base/log/ace_performance_monitor.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent.h"

namespace OHOS::Ace::Framework {

JsFunction::JsFunction(const JSRef<JSFunc>& jsFunction)
{
    jsFunction_ = jsFunction;
}

JsFunction::JsFunction(const JSRef<JSObject>& jsObject, const JSRef<JSFunc>& jsFunction)
{
    jsThis_ = jsObject;
    jsFunction_ = jsFunction;
}

JsWeakFunction::JsWeakFunction(const JSRef<JSFunc>& jsFunction)
{
    jsWeakFunction_ = jsFunction;
}

JsWeakFunction::JsWeakFunction(const JSRef<JSObject>& jsObject, const JSRef<JSFunc>& jsFunction)
{
    jsThis_ = jsObject;
    jsWeakFunction_ = jsFunction;
}

JsFunction::~JsFunction() {}

void JsFunctionBase::Execute(const JSRef<JSObject>& jsParamsObject)
{
    JSRef<JSVal> paramObj = JSRef<JSVal>::Cast(jsParamsObject);
    ExecuteJS(1, &paramObj);
}

void JsFunctionBase::Execute(const std::vector<std::string>& keys, const std::string& param)
{
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(param);
    if (!argsPtr) {
        return;
    }
    JSRef<JSObject> eventInfo = JSRef<JSObject>::New();
    for (auto iter = keys.begin(); iter != keys.end(); iter++) {
        const std::string key = *iter;
        const auto value = argsPtr->GetValue(key);
        if (!value) {
            LOGD("key[%{public}s] not exist.", key.c_str());
            continue;
        }
        ExecuteInternal(value, key, eventInfo);
    }

    JSRef<JSVal> paramObj = JSRef<JSVal>::Cast(eventInfo);
    ExecuteJS(1, &paramObj);
}

void JsFunctionBase::ExecuteInternal(const std::unique_ptr<JsonValue>& value, const std::string& key,
    const JSRef<JSObject>& eventInfo)
{
    if (value->IsString()) {
        eventInfo->SetProperty<std::string>(key.c_str(), value->GetString().c_str());
    } else if (value->IsNumber()) {
        eventInfo->SetProperty<double>(key.c_str(), value->GetDouble());
    } else if (value->IsBool()) {
        eventInfo->SetProperty<bool>(key.c_str(), value->GetBool());
    } else if (value->IsObject()) {
        eventInfo->SetPropertyJsonObject(key.c_str(), value->ToString().c_str());
    } else if (value->IsArray()) {
        JSRef<JSArray> valueArray = JSRef<JSArray>::New();
        for (auto index = 0; index < value->GetArraySize(); index++) {
            auto item = value->GetArrayItem(index);
            if (item && item->IsString()) {
                valueArray->SetValueAt(index, JSRef<JSVal>::Make(ToJSValue(item->GetString())));
            }
            if (item && item->IsNumber()) {
                valueArray->SetValueAt(index, JSRef<JSVal>::Make(ToJSValue(item->GetInt())));
            }
        }
        eventInfo->SetPropertyObject(key.c_str(), valueArray);
    }
}

void JsFunctionBase::ExecuteNew(const std::vector<std::string>& keys, const std::string& param)
{
    JSRef<JSVal> jsVal;
    if (keys.size() > 1) {
        auto result = XComponentClient::GetInstance().GetJSVal(keys[1], jsVal);
        RefPtr<JSXComponentController> controller =
            XComponentClient::GetInstance().GetControllerFromJSXComponentControllersMap(keys[1]);
        if (result && controller) {
            controller->SetXComponentContext(jsVal);
        }
    }
    ExecuteJS(1, &jsVal);
}

JSRef<JSVal> JsWeakFunction::ExecuteJS(int argc, JSRef<JSVal> argv[])
{
    JS_CALLBACK_DURATION();
    JAVASCRIPT_EXECUTION_SCOPE_STATIC
    ACE_FUNCTION_TRACE();
    JSRef<JSVal> jsObject = jsThis_.Lock();
    auto jsFunction = jsWeakFunction_.Lock();
    if (jsFunction.IsEmpty()) {
        LOGW("js function is null.");
        return {};
    }
    JSRef<JSVal> result = jsFunction->Call(jsObject, argc, argv);
    return result;
}

JSRef<JSVal> JsFunction::ExecuteJS(int argc, JSRef<JSVal> argv[])
{
    JS_CALLBACK_DURATION();
    JAVASCRIPT_EXECUTION_SCOPE_STATIC
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
    const auto& localOffset = info.GetTarget().area.GetOffset();
    const auto& origin = info.GetTarget().origin;
    offset->SetProperty<double>("x", localOffset.GetX().ConvertToVp());
    offset->SetProperty<double>("y", localOffset.GetY().ConvertToVp());
    globalOffset->SetProperty<double>("x", (origin.GetX().ConvertToVp() + localOffset.GetX().ConvertToVp()));
    globalOffset->SetProperty<double>("y", (origin.GetY().ConvertToVp() + localOffset.GetY().ConvertToVp()));
    area->SetPropertyObject("position", offset);
    area->SetPropertyObject("globalPosition", globalOffset);
    area->SetProperty<double>("width", info.GetTarget().area.GetWidth().ConvertToVp());
    area->SetProperty<double>("height", info.GetTarget().area.GetHeight().ConvertToVp());
    target->SetPropertyObject("area", area);
    return target;
}

} // namespace OHOS::Ace::Framework
