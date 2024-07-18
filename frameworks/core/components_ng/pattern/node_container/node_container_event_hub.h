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
    DECLARE_ACE_TYPE(NodeContainerEventHub, EventHub)
public:
    void SetControllerAboutToAppear(std::function<void()>&& onAppearCallback)
    {
        onAppearCallback_ = std::move(onAppearCallback);
    }

    void SetControllerAboutToDisappear(std::function<void()>&& onDisAppearCallback)
    {
        onDisAppearCallback_ = std::move(onDisAppearCallback);
    }

    void FireOnAppear() override;

    void FireOnDisappear() override;

private:
    std::function<void()> onAppearCallback_;
    std::function<void()> onDisAppearCallback_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_EVENT_HUB_H
