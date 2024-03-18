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
void UIObserverListener::OnNavigationStateChange(const NG::NavDestinationInfo& info)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle navDestination state change failed, runtime or callback function invalid!");
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value argv[] = { CreateNavDestinationInfoObj(info) };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
}

void UIObserverListener::OnScrollEventStateChange(
    const std::string& id, NG::ScrollEventType eventType, float offset)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle scrollEvent state change failed, runtime or callback function invalid!");
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value scrollId = nullptr;
    napi_value scrollEventType = nullptr;
    napi_value scrollOffset = nullptr;
    napi_create_string_utf8(env_, id.c_str(), id.length(), &scrollId);
    napi_create_int32(env_, static_cast<int32_t>(eventType), &scrollEventType);
    napi_create_double(env_, offset, &scrollOffset);
    napi_set_named_property(env_, objValue, "id", scrollId);
    napi_set_named_property(env_, objValue, "eventType", scrollEventType);
    napi_set_named_property(env_, objValue, "offset", scrollOffset);
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

void UIObserverListener::OnDensityChange(double density)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle density change failed, runtime or callback function invalid!");
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value napiDensity = nullptr;
    napi_create_double(env_, density, &napiDensity);
    napi_set_named_property(env_, objValue, "density", napiDensity);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
}

void UIObserverListener::OnDrawOrLayout()
{
    if (!env_ || !callback_) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
}

napi_value UIObserverListener::CreateNavDestinationInfoObj(const NG::NavDestinationInfo& info)
{
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value napiNavId = nullptr;
    napi_value napiName = nullptr;
    napi_value napiState = nullptr;
    napi_value napiIdx = nullptr;
    napi_value napiNavDesId = nullptr;
    napi_create_string_utf8(env_, info.navigationId.c_str(), info.navigationId.length(), &napiNavId);
    napi_create_string_utf8(env_, info.name.c_str(), info.name.length(), &napiName);
    napi_create_int32(env_, static_cast<int32_t>(info.state), &napiState);
    napi_create_int32(env_, info.index, &napiIdx);
    napi_create_string_utf8(env_, info.navDestinationId.c_str(), info.navDestinationId.length(), &napiNavDesId);
    napi_set_named_property(env_, objValue, "navigationId", napiNavId);
    napi_set_named_property(env_, objValue, "name", napiName);
    napi_set_named_property(env_, objValue, "state", napiState);
    napi_set_named_property(env_, objValue, "index", napiIdx);
    napi_set_named_property(env_, objValue, "param", info.param);
    napi_set_named_property(env_, objValue, "navDestinationId", napiNavDesId);
    return objValue;
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
