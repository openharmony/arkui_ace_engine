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

#include "core/common/container.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> RefreshCoordination::FindRefreshNode() const
{
    CHECK_NULL_RETURN(scrollableNode_, nullptr);
    auto parent = scrollableNode_->GetParent();
    while (parent) {
        if (InstanceOf<FrameNode>(parent)) {
            auto parentFrameNode = DynamicCast<FrameNode>(parent);
            if (InstanceOf<NavigationPattern>(parentFrameNode->GetPattern())) {
                return nullptr;
            }
            if (InstanceOf<RefreshPattern>(parentFrameNode->GetPattern())) {
                return DynamicCast<FrameNode>(parent);
            }
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

RefPtr<ScrollableCoordinationEvent> RefreshCoordination::CreateCoordinationEvent()
{
    if (coordinationEvent_) {
        return coordinationEvent_;
    }
    CHECK_NULL_RETURN(refreshNode_, nullptr);
    auto refreshPattern = DynamicCast<RefreshPattern>(refreshNode_->GetPattern());
    CHECK_NULL_RETURN(refreshPattern, nullptr);
    auto coordinationEvent = AceType::MakeRefPtr<ScrollableCoordinationEvent>();
    refreshPattern->InitCoordinationEvent(coordinationEvent);
    return coordinationEvent;
}

void RefreshCoordination::OnScrollStart() const
{
    CHECK_NULL_VOID(coordinationEvent_);
    auto onScrollStart = coordinationEvent_->GetOnScrollStartEvent();
    if (onScrollStart) {
        onScrollStart();
    }
}

bool RefreshCoordination::OnScroll(float offset) const
{
    CHECK_NULL_RETURN(coordinationEvent_, false);
    auto onScroll = coordinationEvent_->GetOnScroll();
    CHECK_NULL_RETURN(onScroll, false);
    return onScroll(offset);
}

void RefreshCoordination::OnScrollEnd(float speed) const
{
    CHECK_NULL_VOID(coordinationEvent_);
    auto onScrollEnd = coordinationEvent_->GetOnScrollEndEvent();
    if (onScrollEnd) {
        onScrollEnd(speed);
    }
}

bool RefreshCoordination::IsRefreshInScroll() const
{
    CHECK_NULL_RETURN(refreshNode_, false);
    auto pattern = refreshNode_->GetPattern<RefreshPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return GreatNotEqual(pattern->GetScrollOffsetValue().GetY(), 0.0);
}
} // namespace OHOS::Ace::NG