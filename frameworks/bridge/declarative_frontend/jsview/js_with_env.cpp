/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_with_env.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/syntax/with_env_model.h"

namespace OHOS::Ace::Framework {

constexpr int NUM_SECOND = 2;

void JSWithEnv::Create(const JSCallbackInfo& info)
{
    WithEnvModel::GetInstance()->Create();
}

void JSWithEnv::Pop()
{
    ViewStackProcessor::GetInstance()->PopContainer();
}

void JSWithEnv::SetEnvProperty(const JSCallbackInfo& info)
{
    if (info.Length() < NUM_SECOND || !info[0]->IsString()) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "JSWithEnv::SetEnvProperty invalid args");
        return;
    }
    auto key = info[0]->ToString();

    if (info[1]->IsBoolean()) {
        auto value = info[1]->ToBoolean();
        WithEnvModel::GetInstance()->SetEnvProperty(key, value);
    } else if (info[1]->IsNumber()) {
        auto value = info[1]->ToNumber<double>();
        WithEnvModel::GetInstance()->SetEnvProperty(key, value);
    } else if (info[1]->IsString()) {
        auto value = info[1]->ToString();
        WithEnvModel::GetInstance()->SetEnvProperty(key, value);
    } else {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "JSWithEnv::SetEnvProperty: value type does not exist.");
    }
}

void JSWithEnv::SetCustomEnvProperty(const JSCallbackInfo& info)
{
    if (info.Length() < NUM_SECOND || !info[0]->IsString()) {
        TAG_LOGW(AceLogTag::ACE_FOREACH, "JSWithEnv::SetCustomEnvProperty invalid args");
        return;
    }
    auto key = info[0]->ToString();
    // customEnv<T>(key: string, value: T) — value is generic, handle by JS type
    WithEnvModel::GetInstance()->SetCustomEnvProperty(key, std::any(info[1]));
}
    
void JSWithEnv::JSBind(BindingTarget globalObj)
{
    JSClass<JSWithEnv>::Declare("WithEnv");
    JSClass<JSWithEnv>::StaticMethod("create", &JSWithEnv::Create);
    JSClass<JSWithEnv>::StaticMethod("pop", &JSWithEnv::Pop);
    JSClass<JSWithEnv>::StaticMethod("env", &JSWithEnv::SetEnvProperty);
    JSClass<JSWithEnv>::StaticMethod("customEnv", &JSWithEnv::SetCustomEnvProperty);
    JSClass<JSWithEnv>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
