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
#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"

namespace OHOS::Ace::NG {
namespace {
Dimension SIDEBAR_WIDTH_NEGATIVE = -1.0_vp;
} // namespace

void SideBarContainerPattern::OnAttachToFrameNodeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
    auto layoutProperty = host->GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    userSetSidebarWidth_ = layoutProperty->GetSideBarWidth().value_or(SIDEBAR_WIDTH_NEGATIVE);
}

void SideBarContainerPattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowSizeChangeCallback(host->GetId());
    auto sideBarTheme = pipelineContext->GetTheme<SideBarTheme>();
    if (sideBarTheme && sideBarTheme->GetSideBarUnfocusEffectEnable()) {
        pipelineContext->AddWindowFocusChangedCallback(host->GetId());
    }
}

void SideBarContainerPattern::OnDetachFromFrameNodeMultiThread(FrameNode* frameNode)
{
    // nothing, thread unsafe
}

void SideBarContainerPattern::OnDetachFromMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowSizeChangeCallback(host->GetId());
    pipeline->RemoveWindowFocusChangedCallback(host->GetId());
}
} // namespace OHOS::Ace::NG
