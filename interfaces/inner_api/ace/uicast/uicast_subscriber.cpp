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

#include "interfaces/inner_api/ace/uicast/uicast_subscriber.h"

#include <dlfcn.h>
#include <string>
#include <unistd.h>

namespace OHOS::Ace {
constexpr char UICAST_PROXY_START_FUNC[] = "OHOS_ACE_UICastProxyStart";
constexpr char UICAST_PROXY_UPDATE_CONTEXT_FUNC[] = "OHOS_ACE_UICastProxyUpdateContext";

using UICastProxyStartFunc = void (*)(int, UIContent*);
using UICastProxyUpdateContextFunc = void (*)(UIContent*);

// 创建订阅
void UICastEventSubscribeProxy::SubscribeStartEvent(UIContent* context)
{
    if (context == nullptr) {
        LOGE("context is null");
        return;
    }

    if (uicastEventReceiver_ == nullptr) {
        if (access("/system/lib64/libace_uicast_proxy.z.so", 0) == -1) {
            LOGI("SubscribeStartEvent libace_uicast_proxy so no exist!");
            return;
        }

        LOGI("SubscribeStartEvent");
        // create subscribe info
        MatchingSkills matchingSkills;

        // add common events
        matchingSkills.AddEvent(COMMON_EVENT_UICAST_START);
        matchingSkills.AddEvent(COMMON_EVENT_UICAST_STOP);
        CommonEventSubscribeInfo subscribeInfo(matchingSkills);
        subscribeInfo.SetPermission("ohos.permission.COMMONEVENT_STICKY");

        // init Receiver
        uicastEventReceiver_ = std::make_shared<UICastEventSubscriber>(subscribeInfo, context);
        eventReceiver_ = std::shared_ptr<CommonEventSubscriber>(uicastEventReceiver_);

        // create subscription
        CommonEventManager::SubscribeCommonEvent(eventReceiver_);
    } else {
        LOGI("Already SubscribeStartEvent");
        uicastEventReceiver_->UICastProxyUpdateContext(context);
    }
}

// 删除订阅
void UICastEventSubscribeProxy::UnSubscribeStartEvent(void)
{
    LOGE("UnSubscribeStartEvent");
    if (eventReceiver_ != nullptr) {
        CommonEventManager::UnSubscribeCommonEvent(eventReceiver_);
        eventReceiver_ = nullptr;
        uicastEventReceiver_ = nullptr;
    }
}

void UICastEventSubscriber::UICastProxyStart(int castSessionId, UIContent* context)
{
    if (handle_ == nullptr) {
        handle_ = dlopen("libace_uicast_proxy.z.so", RTLD_LAZY);
        if (handle_ == nullptr) {
            LOGE("dlopen failed: %{public}s", dlerror());
            return;
        }
        LOGI("UICastProxyStart dlopen ok, castSessionId: %{public}d", castSessionId);
    }

    auto entry = reinterpret_cast<UICastProxyStartFunc>(dlsym(handle_, UICAST_PROXY_START_FUNC));
    if (entry == nullptr) {
        LOGE("find func failed: %{public}s", dlerror());
        dlclose(handle_);
        handle_ = nullptr;
        return;
    }

    entry(castSessionId, context);
    return;
}

void UICastEventSubscriber::UICastProxyStop()
{
    if (handle_ != nullptr) {
        LOGI("UICastProxyStop");
        dlclose(handle_);
        handle_ = nullptr;
    }
    return;
}

void UICastEventSubscriber::UICastProxyUpdateContext(UIContent* context)
{
    if (handle_ == nullptr) {
        LOGE("handle_ is null");
        return;
    }
    auto entry = reinterpret_cast<UICastProxyUpdateContextFunc>(dlsym(handle_, UICAST_PROXY_UPDATE_CONTEXT_FUNC));
    if (entry == nullptr) {
        LOGE("find func failed: %{public}s", dlerror());
        return;
    }

    entry(context);
    return;
}
} // namespace OHOS::Ace
