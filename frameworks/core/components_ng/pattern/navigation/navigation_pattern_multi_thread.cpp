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

#include "frameworks/core/components_ng/pattern/navigation/navigation_pattern.h"

namespace OHOS::Ace::NG {
void NavigationPattern::OnAttachToFrameNodeMultiThread()
{
    // nothing, thread unsafe
}

void NavigationPattern::OnDetachFromFrameNodeMultiThread(FrameNode* frameNode)
{
    // nothing, thread unsafe
}

void NavigationPattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto id = host->GetId();
    context->AddWindowStateChangedCallback(id);
    context->AddWindowSizeChangeCallback(id);

    auto theme = NavigationGetTheme();
    if (theme && theme->GetNavBarUnfocusEffectEnable()) {
        context->AddWindowFocusChangedCallback(id);
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_ALL, .edges = SAFE_AREA_EDGE_ALL };
        host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    }
    auto manager = context->GetForceSplitManager();
    CHECK_NULL_VOID(manager);
    if (manager->IsForceSplitSupported(false)) {
        RegisterForceSplitListener(context, id);
    }

    InitPageNode(host);
    InitFoldState();
    RegisterAvoidInfoChangeListener(host);
}

void NavigationPattern::OnDetachFromMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isFullPageNavigation_ = false;
    UnregisterAvoidInfoChangeListener(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    TryRestoreSystemBarStyle(windowManager);
    backupStyle_.reset();
    currStyle_.reset();
    pageNode_ = nullptr;
    SetIsTargetForceSplitNav(false);

    auto id = host->GetId();
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->RemoveWindowSizeChangeCallback(id);
    auto manager = pipeline->GetForceSplitManager();
    CHECK_NULL_VOID(manager);
    if (manager->IsForceSplitSupported(false)) {
        UnregisterForceSplitListener(pipeline, id);
    }
}

void NavigationPattern::SetSystemBarStyleMultiThread(const RefPtr<SystemBarStyle>& style)
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
