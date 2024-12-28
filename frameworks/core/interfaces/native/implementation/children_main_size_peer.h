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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CHILDREN_MAIN_SIZE_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CHILDREN_MAIN_SIZE_PEER_H

#include "base/utils/noncopyable.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/list/list_children_main_size.h"

namespace ohos = OHOS;

struct ChildrenMainSizePeer {
public:
    ChildrenMainSizePeer() = default;
    ~ChildrenMainSizePeer() = default;
    explicit ChildrenMainSizePeer(float defaultSize) : defaultSize_(defaultSize) {};

    const ohos::Ace::RefPtr<ohos::Ace::NG::ListChildrenMainSize>& GetHandler() const
    {
        return handler_;
    }

    void SetHandler(const ohos::Ace::RefPtr<ohos::Ace::NG::ListChildrenMainSize>& handler)
    {
        handler_ = handler;
        if (defaultSize_.has_value()) {
            if (handler_) {
                handler_->UpdateDefaultSize(defaultSize_.value());
            }
        }
    }

    std::optional<float> GetDefaultSize()
    {
        return defaultSize_;
    }

    void SetDefaultSize(float defaultSize)
    {
        defaultSize_ = defaultSize;
        handler_->UpdateDefaultSize(defaultSize);
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(ChildrenMainSizePeer);
    ohos::Ace::RefPtr<ohos::Ace::NG::ListChildrenMainSize> handler_;
    std::optional<float> defaultSize_;
};

#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CHILDREN_MAIN_SIZE_PEER_H
