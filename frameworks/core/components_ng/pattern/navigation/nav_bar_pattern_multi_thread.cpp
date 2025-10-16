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

#include "ui/base/ace_type.h"

#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"

namespace OHOS::Ace::NG {
void NavBarPattern::OnAttachToFrameNodeMultiThread()
{
    // nothing, thread unsafe
}

void NavBarPattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    NavDestinationPatternBase::InitOnTouchEvent(host);
    auto pipelineContext = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowSizeChangeCallback(host->GetId());

    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    if (theme && theme->GetNavBarUnfocusEffectEnable()) {
        pipelineContext->AddWindowFocusChangedCallback(host->GetId());
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
            .edges = SAFE_AREA_EDGE_ALL };
        host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    }
}

void NavBarPattern::OnDetachFromFrameNodeMultiThread(FrameNode* frameNode)
{
    // nothing, thread unsafe
}

void NavBarPattern::OnDetachFromMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowSizeChangeCallback(host->GetId());
    NavDestinationPatternBase::RemoveOnTouchEvent(AceType::RawPtr(host));
}
} // namespace OHOS::Ace::NG
