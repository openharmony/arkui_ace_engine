/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_HUB_H

#include <functional>

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_proxy.h"

namespace OHOS::Ace::NG {
class SecurityUIExtensionProxy;
class UIExtensionHub : public EventHub {
    DECLARE_ACE_TYPE(UIExtensionHub, EventHub)

public:
    void SetOnReceiveCallback(
        const std::function<void(const AAFwk::WantParams&)>&& callback)
    {
        onReceiveCallback_ = std::move(callback);
    }

    void FireOnReceiveCallback(const AAFwk::WantParams& params)
    {
        if (onReceiveCallback_) {
            auto onReceiveCallback = onReceiveCallback_;
            onReceiveCallback_(params);
        }
    }

    void SetOnTerminatedCallback(
        const std::function<void(int32_t, const RefPtr<WantWrap>& wantWrap)>&& callback)
    {
        onTerminatedCallback_ = std::move(callback);
    }

    void FireOnTerminatedCallback(int32_t code, const RefPtr<WantWrap>& wantWrap)
    {
        if (onTerminatedCallback_) {
            auto onTerminatedCallback = onTerminatedCallback_;
            onTerminatedCallback_(code, wantWrap);
        }
    }

    void SetOnRemoteReadyCallback(
        const std::function<void(const RefPtr<SecurityUIExtensionProxy>&)>&& callback)
    {
        onRemoteReadyCallback_ = std::move(callback);
    }

    void FireOnRemoteReadyCallback(const RefPtr<SecurityUIExtensionProxy>& proxy) const
    {
        if (onRemoteReadyCallback_) {
            auto onRemoteReadyCallback = onRemoteReadyCallback_;
            onRemoteReadyCallback(proxy);
        }
    }

private:
    std::function<void(const RefPtr<SecurityUIExtensionProxy>&)> onRemoteReadyCallback_;
    std::function<void(int32_t, const RefPtr<WantWrap>&)> onTerminatedCallback_;
    std::function<void(const AAFwk::WantParams&)> onReceiveCallback_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_HUB_H