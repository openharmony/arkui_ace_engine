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

#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_foreach_function.h"

#include "frameworks/bridge/declarative_frontend/engine/v8/v8_declarative_engine.h"
#include "frameworks/bridge/declarative_frontend/engine/v8/v8_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"

namespace OHOS::Ace::Framework {

std::vector<std::string> V8ForEachFunction::executeIdentityMapper()
{
    ACE_DCHECK(isolate_);
    v8::Isolate::Scope isolateScope(isolate_);
    v8::HandleScope handleScope(isolate_);
    auto context = ctx_.Get(isolate_);
    v8::Context::Scope contextScope(context);

    std::vector<std::string> result;

    v8::Local<v8::Object> jsKeys;
    if (!jsIdentityMapperFunc_.IsEmpty()) {
        v8::Local<v8::Value> argv[] = { jsIdentityMapperFunc_.Get(isolate_) };
        jsKeys = V8Function::executeJS(1, argv)->ToObject(context).ToLocalChecked();

        if (jsKeys.IsEmpty()) {
            return result;
        }
    }

    v8::Local<v8::Array> jsKeysArr;
    if (!jsKeys.IsEmpty()) {
        jsKeysArr = v8::Local<v8::Array>::Cast(jsKeys);
    } else {
        jsKeysArr = v8::Local<v8::Array>::Cast(jsThis_.Get(isolate_));
    }
    int length = jsKeysArr->Length();

    for (int i = 0; i < length; i++) {
        if (!jsKeys.IsEmpty()) {
            v8::Local<v8::Value> jsKey = jsKeysArr->Get(context, i).ToLocalChecked();

            if (!jsKey->IsString() && !jsKey->IsNumber()) {
                LOGE("ForEach Item with invalid identifier.........");
                continue;
            }

            V8Utils::ScopedString key(jsKey);
            LOGD("ForEach item with identifier: %s", key.get());
            result.emplace_back(key.get());
        } else {
            result.emplace_back(std::to_string(i));
        }
    }

    return result;
}

void V8ForEachFunction::executeBuilderForIndex(int32_t index)
{
    LOGD("executeBuilderForIndex: start");
    ACE_DCHECK(isolate_);
    v8::Isolate::Scope isolateScope(isolate_);
    v8::HandleScope handleScope(isolate_);
    auto context = ctx_.Get(isolate_);
    v8::Context::Scope contextScope(context);
    v8::TryCatch tryCatch(isolate_);

    // indexed item
    v8::Local<v8::Object> jsArray = v8::Local<v8::Object>::Cast(jsThis_.Get(isolate_));
    v8::Local<v8::Value> jsItem = jsArray->Get(context, index).ToLocalChecked();

    v8::Local<v8::Value> jsView;
    bool success = jsViewMapperFunc_.Get(isolate_)->Call(context, jsThis_.Get(isolate_), 1, &jsItem).ToLocal(&jsView);

    if (!success) {
        V8Utils::JsStdDumpErrorAce(isolate_, &tryCatch);
    }
}

} // namespace OHOS::Ace::Framework
