/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_EVENT_HUB_H

#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {
class SelectOverlayEventHub : public EventHub {
    DECLARE_ACE_TYPE(SelectOverlayEventHub, EventHub);

public:
    SelectOverlayEventHub() = default;
    ~SelectOverlayEventHub() override = default;

    void SetMenuAppearCallback(std::function<void()>&& onAppear)
    {
        onAppear_ = std::move(onAppear);
    }

    void FireAppearEvent()
    {
        if (onAppear_) {
            onAppear_();
        }
    }

    void SetMenuDisappearCallback(std::function<void()>&& onDisappear)
    {
        onDisappear_ = std::move(onDisappear);
    }

    void FireDisappearEvent()
    {
        if (onDisappear_) {
            onDisappear_();
        }
    }

    void SetMenuShowCallback(std::function<void()>&& onMenuShow)
    {
        onMenuShowCallback_ = std::move(onMenuShow);
    }

    void SetMenuHideCallback(std::function<void()>&& onMenuHide)
    {
        onMenuHideCallback_ = std::move(onMenuHide);
    }

    void FireMenuVisibilityChangeEvent(bool isMenuShow)
    {
        if (lastMenuIsShow_.has_value() && lastMenuIsShow_.value() == isMenuShow) {
            return;
        }
        if (isMenuShow && onMenuShowCallback_) {
            onMenuShowCallback_();
        } else if (!isMenuShow && onMenuHideCallback_) {
            onMenuHideCallback_();
        }
        lastMenuIsShow_ = isMenuShow;
    }
private:
    std::optional<bool> lastMenuIsShow_;
    std::function<void()> onAppear_;
    std::function<void()> onDisappear_;
    std::function<void()> onMenuShowCallback_;
    std::function<void()> onMenuHideCallback_;
    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayEventHub);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_EVENT_HUB_H
