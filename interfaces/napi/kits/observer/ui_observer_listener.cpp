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
    std::string navigationId, std::string navDestinationName, NG::NavDestinationState navState)
{
    if (!env_ || !callback_) {
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
