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

namespace OHOS::Ace::Framework {

class ACE_EXPORT JsFunctionBase : public virtual AceType {
    DECLARE_ACE_TYPE(JsFunctionBase, AceType);

public:
    JsFunctionBase(const JSRef<JSObject>& jsObject)
        : jsThis_(jsObject) {}

    void Execute()
    {
        ExecuteJS();
    }

    void Execute(const std::vector<std::string>& keys, const std::string& param);

    JSRef<JSVal> ExecuteJS()
    {
        return ExecuteJS(0, nullptr);
    }

    JSRef<JSVal> ExecuteJS(int argc, JSRef<JSVal> argv[]);

protected:
    JSRef<JSVal> This()
    {
        return jsThis_.Lock();
    }
    virtual JSRef<JSFunc> GetFunction() = 0;

private:
    JSWeak<JSVal> jsThis_;
};

template<template<typename> class Ref = JSRef>
class ACE_EXPORT JsFunctionT : public JsFunctionBase {
    DECLARE_ACE_TYPE(JsFunctionT, JsFunctionBase);

public:
    explicit JsFunctionT(const JSRef<JSFunc>& jsFunction)
        : JsFunctionT({}, jsFunction) {}
    JsFunctionT(const JSRef<JSObject>& jsObject, const JSRef<JSFunc>& jsFunction)
        : JsFunctionBase(jsObject), jsFunction_(jsFunction) {}
    ~JsFunctionT() override = default;

protected:
    JSRef<JSFunc> GetFunction() override;
    Ref<JSFunc> jsFunction_;
};

using JsFunction = JsFunctionT<JSRef>;
using JsWeakFunction = JsFunctionT<JSWeak>;

template<>
inline JSRef<JSFunc> JsWeakFunction::GetFunction()
{
    return jsFunction_.Lock();
}

template<>
inline JSRef<JSFunc> JsFunction::GetFunction()
{
    return jsFunction_;
}

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_FUNCTION_H
