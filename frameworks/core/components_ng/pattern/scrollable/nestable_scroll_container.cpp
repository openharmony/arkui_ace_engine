/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"

#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
RefPtr<NestableScrollContainer> NestableScrollContainer::SearchParent()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    for (auto parent = host->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }
        auto pattern = frameNode->GetPattern<NestableScrollContainer>();
        if (!pattern) {
            continue;
        }
        if ((!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) ||
                !isSearchRefresh_) &&
            InstanceOf<RefreshPattern>(pattern)) {
            continue;
        }
        if (pattern->GetAxis() != GetAxis()) {
            continue;
        }
        return pattern;
    }
    return nullptr;
}

void NestableScrollContainer::UpdateNestedModeForChildren(const NestedScrollOptions& childNestedScroll)
{
    if (!childNestedScroll_) {
        childNestedScroll_ = std::make_unique<NestedScrollOptions>();
    }
    if (*childNestedScroll_ != childNestedScroll) {
        *childNestedScroll_ = childNestedScroll;
    }
}

void NestableScrollContainer::SetNestedScroll(const NestedScrollOptions& nestedScroll, bool isFixedNestedScrollMode)
{
    if (isFixedNestedScrollMode_ && !nestedScroll.NeedParent()) {
        return;
    }
    if (!isFixedNestedScrollMode && AceType::InstanceOf<ScrollablePattern>(this)) {
        if (nestedScroll.NeedParent()) {
            isSearchRefresh_ = false;
        } else {
            isSearchRefresh_ = true;
        }
    }
    SetIsFixedNestedScrollMode(isFixedNestedScrollMode);
    auto parent = parent_.Upgrade();
    if (parent && !nestedScroll.NeedParent() && nestedScroll_.NeedParent()) {
        isNestedInterrupt_ = true;
    }
    nestedScroll_ = nestedScroll;
}

void NestableScrollContainer::SetParentScrollable()
{
    parent_ = SearchParent();
    auto parent = parent_.Upgrade();
    CHECK_NULL_VOID(parent);
    if (!isFixedNestedScrollMode_) {
        auto && childNestedMode = parent->GetNestedModeForChildren();
        auto selfNestedScrollMode = nestedScroll_;
        if (childNestedMode) {
            SetNestedScroll(*childNestedMode, true);
        }
        if (AceType::InstanceOf<RefreshPattern>(parent)) {
            parent->SetNestedScroll(selfNestedScrollMode);
        }
    }
}

void NestableScrollContainer::OnScrollDragEndRecursive()
{
    auto parent = parent_.Upgrade();
    if (parent && nestedScroll_.NeedParent()) {
        parent->OnScrollDragEndRecursive();
    }
}
} // namespace OHOS::Ace::NG
