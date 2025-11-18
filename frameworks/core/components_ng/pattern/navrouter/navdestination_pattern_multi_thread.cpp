/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"

namespace OHOS::Ace::NG {
void NavDestinationPattern::OnAttachToFrameNodeMultiThread()
{
    // nothing, thread unsafe
}

void NavDestinationPattern::OnDetachFromFrameNodeMultiThread(FrameNode* frameNode)
{
    // nothing, thread unsafe
}

void NavDestinationPattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    NavDestinationPatternBase::InitOnTouchEvent(host);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
            .edges = SAFE_AREA_EDGE_ALL };
        host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    }
    isRightToLeft_ = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto id = host->GetId();
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);

    pipeline->AddWindowStateChangedCallback(id);
    pipeline->AddWindowSizeChangeCallback(id);
    pipeline->GetMemoryManager()->AddRecyclePageNode(host);
}

void NavDestinationPattern::OnDetachFromMainTreeMultiThread()
{
    auto host = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(host);
    backupStyle_.reset();
    currStyle_.reset();
    if (!host->IsHomeDestination()) {
        return;
    }
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigationNode_.Upgrade());
    CHECK_NULL_VOID(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    navigationPattern->NotifyDestinationLifecycle(host, NavDestinationLifecycle::ON_WILL_DISAPPEAR);

    auto id = host->GetId();
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->RemoveWindowSizeChangeCallback(id);
    pipeline->GetMemoryManager()->RemoveRecyclePageNode(id);
    NavDestinationPatternBase::RemoveOnTouchEvent(AceType::RawPtr(host));
}

void NavDestinationPattern::SetSystemBarStyleMultiThread(const RefPtr<SystemBarStyle>& style)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto setTask = [weak = WeakClaim(this), style]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetSystemBarStyle(style);
    };
    host->PostAfterAttachMainTreeTask(std::move(setTask));
}
} // namespace OHOS::Ace::NG