/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLL_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLL_CONTROLLER_H

#include "core/components/scroll/scroll_controller_base.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class ACE_EXPORT ScrollController : public ScrollControllerBase {
    DECLARE_ACE_TYPE(ScrollController, ScrollControllerBase);
public:
    ScrollController() = default;

    ~ScrollController() override = default;

    void SetScrollNode(const WeakPtr<RenderNode>& scroll)
    {
        scroll_ = scroll;
    }

    void SetObserver(const ScrollerObserver& observer) override
    {
        observer_ = observer;
    }

    ScrollerObserver GetObserver()
    {
        return observer_;
    }

protected:
    WeakPtr<RenderNode> scroll_;
    ScrollerObserver observer_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLL_CONTROLLER_H
