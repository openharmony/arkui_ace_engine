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
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/manager/environment/environment_types.h"
#include "core/components_ng/syntax/with_env_model.h"

namespace OHOS::Ace::Framework {

constexpr int NUM_SECOND = 2;
constexpr int32_t FRONTEND_DIRECTION_LTR = 0;
constexpr int32_t FRONTEND_DIRECTION_RTL = 1;
constexpr int32_t FRONTEND_DIRECTION_AUTO = 2;

bool ParseDirectionValue(const JSRef<JSVal>& value, TextDirection& direction)
{
    if (value->IsNumber()) {
        auto index = value->ToNumber<int32_t>();
        switch (index) {
            case FRONTEND_DIRECTION_LTR:
                direction = TextDirection::LTR;
                return true;
            case FRONTEND_DIRECTION_RTL:
                direction = TextDirection::RTL;
                return true;
            case FRONTEND_DIRECTION_AUTO:
                direction = TextDirection::AUTO;
                return true;
            default:
                return false;
        }
    }
    if (!value->IsString()) {
        return false;
    }
    auto directionValue = value->ToString();
    if (directionValue == "Ltr") {
        direction = TextDirection::LTR;
        return true;
    }
    if (directionValue == "Rtl") {
        direction = TextDirection::RTL;
        return true;
    }
    if (directionValue == "Auto") {
        direction = TextDirection::AUTO;
        return true;
    }
    return false;
}

void JSWithEnv::Create(const JSCallbackInfo& info)
{
    WithEnvModel::GetInstance()->Create();
}

void JSWithEnv::Pop()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSWithEnv][pop]", &JSWithEnv::Pop);
    }

    ViewStackModel::GetInstance()->PopContainer();
}

void JSWithEnv::SetEnvProperty(const JSCallbackInfo& info)
{
    if (info.Length() < NUM_SECOND) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "JSWithEnv::SetEnvProperty invalid args");
        return;
    }
    std::string key;
    if (info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        auto keyIdVal = obj->GetProperty("keyId");
        if (keyIdVal->IsString()) {
            key = keyIdVal->ToString();
        }
    }
    if (key.empty()) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "JSWithEnv::SetEnvProperty invalid key");
        return;
    }

    if (info[1]->IsUndefined()) {
        if (key == NG::ENV_KEY_DIRECTION || key == NG::ENV_KEY_FONT_SCALE) {
            WithEnvModel::GetInstance()->RemoveSystemEnvProperty(key);
            return;
        }
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "JSWithEnv::SetEnvProperty: value type does not exist.");
        return;
    } else if (key == NG::ENV_KEY_DIRECTION) {
        TextDirection direction = TextDirection::AUTO;
        if (!ParseDirectionValue(info[1], direction)) {
            TAG_LOGW(AceLogTag::ACE_LAYOUT, "JSWithEnv::SetEnvProperty invalid direction value");
            return;
        }
        WithEnvModel::GetInstance()->SetSystemEnvProperty(key, direction);
    } else if (key == NG::ENV_KEY_FONT_SCALE) {
        if (!info[1]->IsNumber()) {
            TAG_LOGW(AceLogTag::ACE_LAYOUT, "JSWithEnv::SetEnvProperty invalid fontScale value");
            return;
        }
        auto value = info[1]->ToNumber<double>();
        WithEnvModel::GetInstance()->SetSystemEnvProperty(key, value);
    } else {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "JSWithEnv::SetEnvProperty: value type does not exist.");
    }
}

void JSWithEnv::SetCustomEnvProperty(const JSCallbackInfo& info)
{
    if (info.Length() < NUM_SECOND || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "JSWithEnv::SetCustomEnvProperty invalid args");
        return;
    }
    std::string key;
    auto obj = JSRef<JSObject>::Cast(info[0]);
    auto keyIdVal = obj->GetProperty("_internal_id");
    if (keyIdVal->IsNumber()) {
        key = std::to_string(keyIdVal->ToNumber<int32_t>());
    }
    if (key.empty()) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "JSWithEnv::SetCustomEnvProperty invalid key");
        return;
    }
    if (info[1]->IsUndefined()) {
        WithEnvModel::GetInstance()->RemoveCustomEnvProperty(key);
        return;
    }
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
