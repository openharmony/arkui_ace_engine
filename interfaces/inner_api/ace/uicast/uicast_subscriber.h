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

#ifndef UICAST_SUBSCRIBER_H
#define UICAST_SUBSCRIBER_H

#include <string>

#include "common_event_manager.h"
#include "common_event_subscriber.h"
#include "hilog/log.h"
#include "interfaces/inner_api/ace/ui_content.h"
#include "singleton.h"

namespace OHOS::Ace {
using OHOS::EventFwk::CommonEventData;
using OHOS::EventFwk::CommonEventManager;
using OHOS::EventFwk::CommonEventSubscribeInfo;
using OHOS::EventFwk::CommonEventSubscriber;
using OHOS::EventFwk::MatchingSkills;

const std::string COMMON_EVENT_UICAST_START = "uicast.start";
const std::string COMMON_EVENT_UICAST_STOP = "uicast.stop";
const std::string COMMON_EVENT_UICAST_CAST_SESSION_KEY = "uicast.castSessionIdKey";

constexpr OHOS::HiviewDFX::HiLogLabel LOG_LABEL = { LOG_CORE, 0xD003900, "ACE_UI_CONTENT" };

#define HIVIEW_PRINTF(func, fmt, ...) func(LOG_LABEL, "<%{public}d>" fmt, __LINE__, ##__VA_ARGS__)

#define WLOGD(fmt, ...) HIVIEW_PRINTF(HiviewDFX::HiLog::Debug, fmt, ##__VA_ARGS__)
#define WLOGI(fmt, ...) HIVIEW_PRINTF(HiviewDFX::HiLog::Info, fmt, ##__VA_ARGS__)
#define WLOGW(fmt, ...) HIVIEW_PRINTF(HiviewDFX::HiLog::Warn, fmt, ##__VA_ARGS__)
#define WLOGE(fmt, ...) HIVIEW_PRINTF(HiviewDFX::HiLog::Error, fmt, ##__VA_ARGS__)

#define LOGD(fmt, ...) WLOGD("%{public}s: " fmt, __func__, ##__VA_ARGS__)
#define LOGI(fmt, ...) WLOGI("%{public}s: " fmt, __func__, ##__VA_ARGS__)
#define LOGW(fmt, ...) WLOGW("%{public}s: " fmt, __func__, ##__VA_ARGS__)
#define LOGE(fmt, ...) WLOGE("%{public}s: " fmt, __func__, ##__VA_ARGS__)

// 订阅者
class UICastEventSubscriber : public CommonEventSubscriber {
public:
    explicit UICastEventSubscriber(const CommonEventSubscribeInfo& info, UIContent* context)
        : CommonEventSubscriber(info), context_(context)
    {}

    ~UICastEventSubscriber() {}

    void UICastProxyStart(int castSessionId, UIContent* context);
    void UICastProxyStop();
    void UICastProxyUpdateContext(UIContent* context);

    void OnReceiveEvent(const CommonEventData& data) override
    {
        LOGI("In");
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

private:
    UIContent* context_;
    void* handle_ { nullptr };
};

class UICastEventSubscribeProxy : public DelayedSingleton<UICastEventSubscribeProxy> {
public:
    ~UICastEventSubscribeProxy()
    {
        UnSubscribeStartEvent();
    }
    void SubscribeStartEvent(UIContent* context);
    void UnSubscribeStartEvent(void);

private:
    std::shared_ptr<CommonEventSubscriber> eventReceiver_ { nullptr };
    std::shared_ptr<UICastEventSubscriber> uicastEventReceiver_ { nullptr };
};
} // namespace OHOS::Ace

#endif
