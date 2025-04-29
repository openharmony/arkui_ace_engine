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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_FUNCTION_H

#include <functional>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#if defined(XCOMPONENT_SUPPORTED)
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller.h"
#endif

namespace OHOS::Ace::Framework {

class ACE_EXPORT JsFunctionBase : public virtual AceType {
    DECLARE_ACE_TYPE(JsFunctionBase, AceType);

public:
    virtual void Execute()
    {
        ExecuteJS();
    }

    void Execute(const JSRef<JSObject>& jsParamsObject);
    void Execute(const std::vector<std::string>& keys, const std::string& param);
    void ExecuteNew(const std::vector<std::string>& keys, const std::string& param);

    virtual JSRef<JSVal> ExecuteJS(int argc)
    {
        return ExecuteJS(argc, nullptr);
    }
    virtual JSRef<JSVal> ExecuteJS(JSRef<JSVal>* argv)
    {
        return ExecuteJS(0, argv);
    }
    virtual JSRef<JSVal> ExecuteJS()
    {
        return ExecuteJS(0, nullptr);
    }
    // Empty realization in JsFunctionBase
    virtual JSRef<JSVal> ExecuteJS(int argc, JSRef<JSVal>* argv, bool isAnimation = false)
    {
        JSRef<JSObject> eventInfo = JSRef<JSObject>::New();
        return JSRef<JSVal>::Cast(eventInfo);
    }

protected:
    JSWeak<JSVal> jsThis_;

private:
    void ExecuteInternal(const std::unique_ptr<JsonValue>& value, const std::string& key,
    const JSRef<JSObject>& eventInfo);
};

class ACE_EXPORT JsFunction : public virtual JsFunctionBase {
    DECLARE_ACE_TYPE(JsFunction, JsFunctionBase);

public:
    explicit JsFunction(const JSRef<JSFunc>& jsFunction);
    JsFunction(const JSRef<JSObject>& jsObject, const JSRef<JSFunc>& jsFunction);
    ~JsFunction() override;

    JSRef<JSVal> ExecuteJS(int argc) override
    {
        return ExecuteJS(argc, nullptr);
    }
    JSRef<JSVal> ExecuteJS(JSRef<JSVal>* argv) override
    {
        return ExecuteJS(0, argv);
    }
    JSRef<JSVal> ExecuteJS() override
    {
        return ExecuteJS(0, nullptr);
    }
    JSRef<JSVal> ExecuteJS(int argc, JSRef<JSVal>* argv, bool isAnimation = false) override;

protected:
    JSRef<JSFunc> jsFunction_;
};

class ACE_EXPORT JsWeakFunction : public virtual JsFunctionBase {
    DECLARE_ACE_TYPE(JsWeakFunction, JsFunctionBase);

public:
    explicit JsWeakFunction(const JSRef<JSFunc>& jsFunction);
    JsWeakFunction(const JSRef<JSObject>& jsObject, const JSRef<JSFunc>& jsFunction);
    ~JsWeakFunction() override = default;

    JSRef<JSVal> ExecuteJS(int argc) override
    {
        return ExecuteJS(argc, nullptr);
    }
    JSRef<JSVal> ExecuteJS(JSRef<JSVal>* argv) override
    {
        return ExecuteJS(0, argv);
    }
    JSRef<JSVal> ExecuteJS() override
    {
        return ExecuteJS(0, nullptr);
    }
    JSRef<JSVal> ExecuteJS(int argc, JSRef<JSVal>* argv, bool isAnimation = false) override;

protected:
    JSWeak<JSFunc> jsWeakFunction_;
};

template<class T, int32_t ARGC = 0>
class ACE_EXPORT JsCitedEventFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsCitedEventFunction, JsFunction);

public:
    using ParseFunc = std::function<JSRef<JSVal>(T&)>;
    JsCitedEventFunction() = delete;
    JsCitedEventFunction(const JSRef<JSFunc>& jsFunction, ParseFunc parser)
        : JsFunction(JSRef<JSObject>(), jsFunction), parser_(parser)
    {}
    ~JsCitedEventFunction() override = default;

    void Execute() override
    {
        JsFunction::ExecuteJS();
    }

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

template<class T, int32_t ARGC = 0>
class ACE_EXPORT JsCommonEventFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsCommonEventFunction, JsFunction);

public:
    JsCommonEventFunction() = delete;
    JsCommonEventFunction(const JSRef<JSFunc>& jsFunction)
        : JsFunction(JSRef<JSObject>(), jsFunction)
    {}
    ~JsCommonEventFunction() override = default;

    void Execute() override
    {
        JsFunction::ExecuteJS();
    }

    void Execute(JSRef<JSVal>* argv)
    {
        JsFunction::ExecuteJS(ARGC, argv);
    }
};

template<class T, int32_t ARGC = 0>
class ACE_EXPORT JsEventFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsEventFunction, JsFunction);

public:
    using ParseFunc = std::function<JSRef<JSVal>(const T&)>;
    JsEventFunction() = delete;
    JsEventFunction(const JSRef<JSFunc>& jsFunction, ParseFunc parser)
        : JsFunction(JSRef<JSObject>(), jsFunction), parser_(parser)
    {}
    ~JsEventFunction() override = default;

    void Execute() override
    {
        JsFunction::ExecuteJS();
    }

    void Execute(const T& eventInfo)
    {
        JSRef<JSVal> param;
        if (parser_) {
            param = parser_(eventInfo);
        }
        JsFunction::ExecuteJS(ARGC, &param);
    }

    JSRef<JSVal> ExecuteWithValue(const T& eventInfo)
    {
        JSRef<JSVal> param;
        if (parser_) {
            param = parser_(eventInfo);
        }
        return JsFunction::ExecuteJS(ARGC, &param);
    }

private:
    ParseFunc parser_;
};

JSRef<JSObject> CreateEventTargetObject(const BaseEventInfo& info);

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_FUNCTION_H
