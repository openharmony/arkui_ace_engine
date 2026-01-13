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

#include "core/common/dynamic_module_helper.h"

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

const ArkUIRefreshModifierCompatible* RenderRefreshTarget::GetRefreshModifier()
{
    static const ArkUIRefreshModifierCompatible* modifier = nullptr;
    if (!modifier) {
        auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("refresh");
        CHECK_NULL_RETURN(loader, nullptr);
        modifier = reinterpret_cast<const ArkUIRefreshModifierCompatible*>(loader->GetCustomModifier());
    }
    return modifier;
}

bool RenderRefreshTarget::HandleRefreshEffect(double delta, int32_t source, double currentOffset)
{
    auto refresh = refreshParent_.Upgrade();
    if (!refresh) {
        return false;
    }
    refresh->SetHasScrollableChild(true);
    if ((LessOrEqual(currentOffset, 0.0) && source == SCROLL_FROM_UPDATE) || inLinkRefresh_) {
        auto* modifier = RenderRefreshTarget::GetRefreshModifier();
        CHECK_NULL_RETURN(modifier, false);
        modifier->updateScrollableOffset(refresh, delta);
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
                auto* modifier = RenderRefreshTarget::GetRefreshModifier();
                CHECK_NULL_VOID(modifier);
                modifier->handleDragEnd(refresh);
                refreshBase->inLinkRefresh_ = false;
            }
        }
    });
    scrollable->SetDragCancelCallback([weakRefreshBase = AceType::WeakClaim(this)]() {
        auto refreshBase = weakRefreshBase.Upgrade();
        if (refreshBase) {
            auto refresh = refreshBase->refreshParent_.Upgrade();
            if (refresh && refreshBase->inLinkRefresh_) {
                auto* modifier = RenderRefreshTarget::GetRefreshModifier();
                CHECK_NULL_VOID(modifier);
                modifier->handleDragCancel(refresh);
                refreshBase->inLinkRefresh_ = false;
            }
        }
    });
}

} // namespace OHOS::Ace
