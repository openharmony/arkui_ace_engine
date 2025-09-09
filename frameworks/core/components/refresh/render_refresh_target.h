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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_REFRESH_RENDER_REFRESH_ADAPTER_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_REFRESH_RENDER_REFRESH_ADAPTER_BASE_H

#include "core/components/refresh/render_refresh.h"
#include "core/components/scroll/scrollable.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RenderRefreshTarget : public virtual AceType {
    DECLARE_ACE_TYPE(RenderRefreshTarget, AceType);

public:
    virtual bool HandleRefreshEffect(double delta, int32_t source, double currentOffset);
    virtual void FindRefreshParent(const WeakPtr<RenderNode>& node);
    virtual void InitializeScrollable(const RefPtr<Scrollable>& scrollable);
protected:
    WeakPtr<RenderRefresh> refreshParent_;
private:
    bool inLinkRefresh_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_REFRESH_RENDER_REFRESH_ADAPTER_BASE_H
