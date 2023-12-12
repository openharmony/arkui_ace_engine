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

#include "core/components/refresh/render_refresh_target.h"

namespace OHOS::Ace {

void RenderRefreshTarget::FindRefreshParent(const WeakPtr<RenderNode>& node)
{
    auto childNode = node.Upgrade();
    if (!childNode) {
        return;
    }
    auto parent = childNode->GetParent().Upgrade();
    while (parent) {
        auto refresh = AceType::DynamicCast<RenderRefresh>(parent);
        if (refresh) {
            refreshParent_ = AceType::WeakClaim(AceType::RawPtr(refresh));
            break;
        }
        parent = parent->GetParent().Upgrade();
    }
}

bool RenderRefreshTarget::HandleRefreshEffect(double delta, int32_t source, double currentOffset)
{
    auto refresh = refreshParent_.Upgrade();
    if (!refresh) {
        return false;
    }
    refresh->SetHasScrollableChild(true);
    if ((LessOrEqual(currentOffset, 0.0) && source == SCROLL_FROM_UPDATE) || inLinkRefresh_) {
        refresh->UpdateScrollableOffset(delta);
        inLinkRefresh_ = true;
    }
    if (refresh->GetStatus() != RefreshStatus::INACTIVE) {
        return true;
    }
    return false;
}

void RenderRefreshTarget::InitializeScrollable(const RefPtr<Scrollable>& scrollable)
{
    if (!scrollable) {
        return;
    }
    scrollable->SetDragEndCallback([weakRefreshBase = AceType::WeakClaim(this)]() {
        auto refreshBase = weakRefreshBase.Upgrade();
        if (refreshBase) {
            auto refresh = refreshBase->refreshParent_.Upgrade();
            if (refresh && refreshBase->inLinkRefresh_) {
                refresh->HandleDragEnd();
                refreshBase->inLinkRefresh_ = false;
            }
        }
    });
    scrollable->SetDragCancelCallback([weakRefreshBase = AceType::WeakClaim(this)]() {
        auto refreshBase = weakRefreshBase.Upgrade();
        if (refreshBase) {
            auto refresh = refreshBase->refreshParent_.Upgrade();
            if (refresh && refreshBase->inLinkRefresh_) {
                refresh->HandleDragCancel();
                refreshBase->inLinkRefresh_ = false;
            }
        }
    });
}

} // namespace OHOS::Ace
