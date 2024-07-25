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

#ifndef FOUNDATION_ACE_INTERFACES_OBSERVER_LISTENER_H
#define FOUNDATION_ACE_INTERFACES_OBSERVER_LISTENER_H

#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"

#include "core/components_ng/base/observer_handler.h"

namespace OHOS::Ace::Napi {
class UIObserverListener {
public:
    UIObserverListener(napi_env env, napi_value callback) : env_(env)
    {
        napi_create_reference(env_, callback, 1, &callback_);
    }
    ~UIObserverListener()
    {
        if (callback_) {
            napi_delete_reference(env_, callback_);
        }
    }
    void OnNavigationStateChange(const NG::NavDestinationInfo& info);
    void OnScrollEventStateChange(
        const std::string& id, int32_t uniqueId, NG::ScrollEventType eventType, float offset);
    void OnRouterPageStateChange(const NG::RouterPageInfoNG& pageInfo);
    void OnDensityChange(double density);
    void OnWillClick(const GestureEvent& gestureEventInfo, const ClickInfo& clickInfo,
        const RefPtr<NG::FrameNode> frameNode);
    void OnDidClick(const GestureEvent& gestureEventInfo, const ClickInfo& clickInfo,
        const RefPtr<NG::FrameNode> frameNode);
    void OnTabContentStateChange(const NG::TabContentInfo& tabContentInfo);
    void OnNavDestinationSwitch(const NG::NavDestinationSwitchInfo& switchInfo);
    bool NapiEqual(napi_value cb);
    void OnDrawOrLayout();

private:
    napi_value CreateNavDestinationSwitchInfoObj(const NG::NavDestinationSwitchInfo& switchInfo);
    napi_value CreateNavDestinationInfoObj(const NG::NavDestinationInfo& info);
    napi_value GetNapiCallback();
    static napi_valuetype GetValueType(napi_env env, napi_value value);
    static napi_value GetNamedProperty(napi_env env, napi_value object, const std::string& propertyName);
    void AddBaseEventInfo(napi_value objValueClickEvent, const ClickInfo& clickInfo);
    void AddGestureEventInfoOne(napi_value objValueClickEvent, const GestureEvent& gestureEventInfo);
    void AddGestureEventInfoTwo(napi_value objValueClickEvent, const GestureEvent& gestureEventInfo);
    void AddGestureEventInfoThree(napi_value objValueClickEvent, const GestureEvent& gestureEventInfo);
    void AddFingerListInfo(napi_value objValueClickEvent, const GestureEvent& gestureEventInfo);
    void AddClickEventInfoOne(napi_value objValueClickEvent, const ClickInfo& clickInfo);
    void AddClickEventInfoTwo(napi_value objValueClickEvent, const ClickInfo& clickInfo);
    void AddTargetObject(napi_value objValueClickEvent, const ClickInfo& clickInfo);
    napi_env env_ = nullptr;
    napi_ref callback_ = nullptr;
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACES_OBSERVER_LISTENER_H
