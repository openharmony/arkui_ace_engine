/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

namespace OHOS::Ace::Framework {
namespace {
void ExecuteInternal(const std::unique_ptr<JsonValue>& value, const std::string& key,
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

JSRef<JSVal> JsFunctionBase::ExecuteJS(int argc, JSRef<JSVal> argv[])
{
    int32_t id = -1;
    if (SystemProperties::GetAcePerformanceMonitorEnabled()) {
        id = Container::CurrentId();
    }
    JS_CALLBACK_DURATION(id);
    JAVASCRIPT_EXECUTION_SCOPE_STATIC;
    ACE_FUNCTION_TRACE();
    auto jsFunction = GetFunction();
    if (jsFunction.IsEmpty()) {
        LOGW("js function is null.");
        return {};
    }
    return jsFunction->Call(This(), argc, argv);
}

} // namespace OHOS::Ace::Framework
