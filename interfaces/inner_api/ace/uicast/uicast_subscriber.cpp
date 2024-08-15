/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "arkui_log.h"

namespace OHOS::Ace {
const std::string COMMON_EVENT_UICAST_START = "uicast.start";
const std::string COMMON_EVENT_UICAST_STOP = "uicast.stop";
const std::string COMMON_EVENT_UICAST_CAST_SESSION_KEY = "uicast.castSessionIdKey";

constexpr char UICAST_PROXY_START_FUNC[] = "OHOS_ACE_UICastProxyStart";
constexpr char UICAST_PROXY_UPDATE_CONTEXT_FUNC[] = "OHOS_ACE_UICastProxyUpdateContext";

using UICastProxyStartFunc = void (*)(int, UIContent*);
using UICastProxyUpdateContextFunc = void (*)(UIContent*);

#if (defined(__aarch64__) || defined(__x86_64__))
const char* DISTRIBUTED_UI_PROXY_SO_PATH = "/system/lib64/libace_uicast_proxy.z.so";
#else
const char* DISTRIBUTED_UI_PROXY_SO_PATH = "/system/lib/libace_uicast_proxy.z.so";
#endif

void UICastEventSubscribeProxy::SubscribeStartEvent(UIContent* context)
{
    if (context == nullptr) {
        LOGE("context is null");
        return;
    }

    if (uicastEventReceiver_ == nullptr) {
        if (access(DISTRIBUTED_UI_PROXY_SO_PATH, 0) == -1) {
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
        subscribeInfo.SetPermission("ohos.permission.CAPTURE_SCREEN");
        subscribeInfo.SetThreadMode(EventFwk::CommonEventSubscribeInfo::ThreadMode::HANDLER);

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

void UICastEventSubscriber::OnReceiveEvent(const CommonEventData& data)
{
    auto want = data.GetWant();
    std::string action = want.GetAction();
    if (action == COMMON_EVENT_UICAST_START) {
        int castSessionId = want.GetIntParam(COMMON_EVENT_UICAST_CAST_SESSION_KEY, -1);
        LOGI("castSessionId: %{public}d", castSessionId);
        UICastProxyStart(castSessionId, context_);
    } else if (action == COMMON_EVENT_UICAST_STOP) {
        LOGI("COMMON_EVENT_UICAST_STOP");
        UICastProxyStop();
    }
}
} // namespace OHOS::Ace
