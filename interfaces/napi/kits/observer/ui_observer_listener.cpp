/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "ui_observer_listener.h"

namespace OHOS::Ace::Napi {
void UIObserverListener::OnNavigationStateChange(
    const std::string& navigationId, const std::string& navDestinationName, NG::NavDestinationState navState)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle navDestination state change failed, runtime or callback function invalid!");
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value id = nullptr;
    napi_value name = nullptr;
    napi_value state = nullptr;
    napi_create_string_utf8(env_, navigationId.c_str(), navigationId.length(), &id);
    napi_create_string_utf8(env_, navDestinationName.c_str(), navDestinationName.length(), &name);
    napi_create_int32(env_, static_cast<int32_t>(navState), &state);
    napi_set_named_property(env_, objValue, "navigationId", id);
    napi_set_named_property(env_, objValue, "name", name);
    napi_set_named_property(env_, objValue, "state", state);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
}

void UIObserverListener::OnRouterPageStateChange(napi_value context, int32_t index,
    const std::string& name, const std::string& path, NG::RouterPageState state)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle router page state change failed, runtime or callback function invalid!");
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value napiCtx = context;
    napi_value napiIndex = nullptr;
    napi_value napiName = nullptr;
    napi_value napiPath = nullptr;
    napi_value napiState = nullptr;
    napi_create_int32(env_, index, &napiIndex);
    napi_create_string_utf8(env_, name.c_str(), name.length(), &napiName);
    napi_create_string_utf8(env_, path.c_str(), path.length(), &napiPath);
    napi_create_int32(env_, static_cast<int32_t>(state), &napiState);
    napi_set_named_property(env_, objValue, "context", napiCtx);
    napi_set_named_property(env_, objValue, "index", napiIndex);
    napi_set_named_property(env_, objValue, "name", napiName);
    napi_set_named_property(env_, objValue, "path", napiPath);
    napi_set_named_property(env_, objValue, "state", napiState);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
}

napi_value UIObserverListener::GetNapiCallback()
{
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    return callback;
}

bool UIObserverListener::NapiEqual(napi_value cb)
{
    bool isEquals = false;
    napi_strict_equals(env_, cb, GetNapiCallback(), &isEquals);
    return isEquals;
}
} // namespace OHOS::Ace::Napi
