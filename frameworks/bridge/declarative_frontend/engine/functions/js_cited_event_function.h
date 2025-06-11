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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_CITED_EVENT_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_CITED_EVENT_FUNCTION_H

#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"

namespace OHOS::Ace::Framework {

template<class T, int32_t ARGC = 0>
class ACE_EXPORT JsCitedEventFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsCitedEventFunction, JsFunction);

public:
    using ParseFunc = std::function<JSRef<JSVal>(T&)>;
    JsCitedEventFunction() = delete;
    JsCitedEventFunction(const JSRef<JSFunc>& jsFunction, ParseFunc parser)
        : JsFunction(JSRef<JSObject>(), jsFunction), parser_(parser) {}
    ~JsCitedEventFunction() override = default;

    void Execute(T& eventInfo)
    {
        JSRef<JSVal> param;
        if (parser_) {
            param = parser_(eventInfo);
        }
        JsFunction::ExecuteJS(ARGC, &param);
    }

    void Execute(const std::string& val, T& eventInfo)
    {
        JSRef<JSVal> jsVal = JSRef<JSVal>::Make(ToJSValue(val));
        JSRef<JSVal> itemInfo;
        if (parser_) {
            itemInfo = parser_(eventInfo);
        }
        JSRef<JSVal> params[] = { jsVal, itemInfo };
        JsFunction::ExecuteJS(ARGC, params);
    }

    void Execute(const std::u16string& val, T& eventInfo)
    {
        JSRef<JSVal> jsVal = JSRef<JSVal>::Make(ToJSValue(val));
        JSRef<JSVal> itemInfo;
        if (parser_) {
            itemInfo = parser_(eventInfo);
        }
        JSRef<JSVal> params[] = { jsVal, itemInfo };
        JsFunction::ExecuteJS(ARGC, params);
    }

private:
    ParseFunc parser_;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_CITED_EVENT_FUNCTION_H
