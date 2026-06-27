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
#include "core/components_ng/pattern/scrollable/refresh_coordination.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_coordination_event.h"
#include "core/components_ng/pattern/refresh/bridge/refresh_dynamic_module.h"
#include "core/common/dynamic_module_helper.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG {
namespace {
const ArkUIRefreshModifier* GetRefreshModifier()
{
    static const ArkUIRefreshModifier* cachedModifier = nullptr;
    if (!cachedModifier) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Refresh");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIRefreshModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}
} // namespace

RefPtr<FrameNode> RefreshCoordination::FindRefreshNode() const
{
    auto scrollableNode = scrollableNode_.Upgrade();
    CHECK_NULL_RETURN(scrollableNode, nullptr);
    auto parent = scrollableNode->GetParent();
    while (parent) {
        if (InstanceOf<FrameNode>(parent)) {
            auto parentFrameNode = DynamicCast<FrameNode>(parent);
            if (InstanceOf<RefreshPattern>(parentFrameNode->GetPattern())) {
                return DynamicCast<FrameNode>(parent);
            }
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

bool RefreshCoordination::UpdateRefreshNode()
{
    auto refreshNode = FindRefreshNode();
    refreshNode_ = WeakClaim(RawPtr(refreshNode));
    coordinationEvent_ = nullptr;
    if (!refreshNode) {
        return false;
    }
    coordinationEvent_ = CreateCoordinationEvent();
    return !!coordinationEvent_;
}

bool RefreshCoordination::IsValid() const
{
    auto scrollableNode = scrollableNode_.Upgrade();
    auto refreshNode = refreshNode_.Upgrade();
    CHECK_NULL_RETURN(scrollableNode && refreshNode, false);
    CHECK_NULL_RETURN(refreshNode->GetPattern<RefreshPattern>(), false);
    for (auto parent = scrollableNode->GetParent(); parent; parent = parent->GetParent()) {
        if (parent == refreshNode) {
            return true;
        }
    }
    return false;
}

RefPtr<ScrollableCoordinationEvent> RefreshCoordination::CreateCoordinationEvent()
{
    if (coordinationEvent_) {
        return coordinationEvent_;
    }
    auto refreshNode = refreshNode_.Upgrade();
    CHECK_NULL_RETURN(refreshNode, nullptr);
    auto coordinationEvent = AceType::MakeRefPtr<ScrollableCoordinationEvent>();
    auto refreshModifier = GetRefreshModifier();
    CHECK_NULL_RETURN(refreshModifier, nullptr);
    refreshModifier->initCoordinationEvent(
        reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(refreshNode)), &coordinationEvent);
    return coordinationEvent;
}

void RefreshCoordination::OnScrollStart(bool isDrag, float mainVelocity) const
{
    CHECK_NULL_VOID(coordinationEvent_);
    auto onScrollStart = coordinationEvent_->GetOnScrollStartEvent();
    if (onScrollStart) {
        onScrollStart(isDrag, mainVelocity);
    }
}

bool RefreshCoordination::OnScroll(float offset, float mainVelocity) const
{
    CHECK_NULL_RETURN(coordinationEvent_, false);
    auto onScroll = coordinationEvent_->GetOnScroll();
    CHECK_NULL_RETURN(onScroll, false);
    return onScroll(offset, mainVelocity);
}

void RefreshCoordination::OnScrollEnd(float mainVelocity) const
{
    CHECK_NULL_VOID(coordinationEvent_);
    auto onScrollEnd = coordinationEvent_->GetOnScrollEndEvent();
    if (onScrollEnd) {
        onScrollEnd(mainVelocity);
    }
}

bool RefreshCoordination::IsRefreshInScroll() const
{
    auto refreshNode = refreshNode_.Upgrade();
    CHECK_NULL_RETURN(refreshNode, false);
    auto pattern = refreshNode->GetPattern<RefreshPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return GreatNotEqual(pattern->GetScrollOffsetValue(), 0.0);
}
} // namespace OHOS::Ace::NG
