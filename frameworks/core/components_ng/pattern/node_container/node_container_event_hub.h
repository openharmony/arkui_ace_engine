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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_EVENT_HUB_H

#include <utility>
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

class NodeContainerEventHub : public EventHub {
    DECLARE_ACE_TYPE(NodeContainerEventHub, EventHub);
public:
    void SetControllerAboutToAppear(std::function<void()>&& onAppearCallback)
    {
        onAppearCallback_ = std::move(onAppearCallback);
    }

    void SetControllerAboutToDisappear(std::function<void()>&& onDisAppearCallback)
    {
        onDisAppearCallback_ = std::move(onDisAppearCallback);
    }

    void SetControllerOnWillBind(std::function<void(int32_t)>&& onWillBindCallback)
    {
        onWillBindCallback_ = std::move(onWillBindCallback);
    }

    void SetControllerOnWillUnbind(std::function<void(int32_t)>&& onWillUnbindCallback)
    {
        onWillUnbindCallback_ = std::move(onWillUnbindCallback);
    }

    void SetControllerOnBind(std::function<void(int32_t)>&& onBindCallback)
    {
        onBindCallback_ = std::move(onBindCallback);
    }

    void SetControllerOnUnbind(std::function<void(int32_t)>&& onUnbindCallback)
    {
        onUnbindCallback_ = std::move(onUnbindCallback);
    }

    void SetControllerOnAttach(std::function<void()>&& onAttachCallback)
    {
        onAttachCallback_ = std::move(onAttachCallback);
    }

    void SetControllerOnDetach(std::function<void()>&& onDetachCallback)
    {
        onDetachCallback_ = std::move(onDetachCallback);
    }

    void FireOnAppear() override;

    void FireOnDisappear() override;

    void FireOnWillBind(int32_t containerId) override;

    void FireOnWillUnbind(int32_t containerId) override;

    void FireOnBind(int32_t containerId) override;

    void FireOnUnbind(int32_t containerId) override;

    void FireOnAttach() override;

    void FireOnDetach() override;

private:
    std::function<void()> onAppearCallback_;
    std::function<void()> onDisAppearCallback_;
    std::function<void(int32_t)> onWillBindCallback_;
    std::function<void(int32_t)> onWillUnbindCallback_;
    std::function<void(int32_t)> onBindCallback_;
    std::function<void(int32_t)> onUnbindCallback_;
    std::function<void()> onAttachCallback_;
    std::function<void()> onDetachCallback_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_EVENT_HUB_H
