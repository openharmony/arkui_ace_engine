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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_V8_FUNCTION_V8_FOREACH_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_V8_FUNCTION_V8_FOREACH_FUNCTION_H

#include <map>

#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class V8ForEachFunction : public V8Function {
    DECLARE_ACE_TYPE(V8ForEachFunction, V8Function)

private:
    v8::Persistent<v8::Function> jsIdentityMapperFunc_;
    v8::Persistent<v8::Function> jsViewMapperFunc_;

public:
    V8ForEachFunction(v8::Local<v8::Object> jsArray, v8::Local<v8::Function> jsIdentityMapperFunc,
        v8::Local<v8::Function> jsViewMapperFunc)
        : V8Function(v8::Local<v8::Value>(), v8::Local<v8::Function>())
    {
        isolate_ = v8::Isolate::GetCurrent();
        auto context = isolate_->GetCurrentContext();
        V8Function::jsThis_.Reset(isolate_, jsArray);
        v8::Local<v8::Value> mapfunc =
            jsArray->Get(context, v8::String::NewFromUtf8(isolate_, "map").ToLocalChecked()).ToLocalChecked();
        V8Function::jsFunction_.Reset(isolate_, v8::Local<v8::Function>::Cast(mapfunc)); // intrinsic property of array
        if (!jsIdentityMapperFunc.IsEmpty()) {
            jsIdentityMapperFunc_.Reset(isolate_, jsIdentityMapperFunc);
        }
        jsViewMapperFunc_.Reset(isolate_, jsViewMapperFunc);
    }

    ~V8ForEachFunction()
    {
        LOGD("Destroy: V8ForEachFunction");
        jsIdentityMapperFunc_.Reset();
        jsViewMapperFunc_.Reset();
    }

    // This exexutes the IdentifierFunction on all items  in a array
    // returns the vector of keys/ids in the same order.
    std::vector<std::string> executeIdentityMapper();

    // This exexutes the BuilderFunction on a specific index
    // returns the native JsView for the item in index.
    void executeBuilderForIndex(int32_t index);

}; // V8ForEachFunction

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_V8_FUNCTION_V8_FOREACH_FUNCTION_H
