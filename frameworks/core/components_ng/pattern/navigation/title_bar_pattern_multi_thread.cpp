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

#include "ui/base/utils/utils.h"

#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"

namespace OHOS::Ace::NG {

void TitleBarPattern::OnAttachToFrameNodeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    host->GetRenderContext()->UpdateClipEdge(true);

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
            .edges = SAFE_AREA_EDGE_TOP };
        host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    }
}

void TitleBarPattern::OnDetachFromFrameNodeMultiThread(FrameNode* frameNode)
{
    // nothing, thread unsafe
}

void TitleBarPattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);

    auto halfFoldHoverCallbackId = pipelineContext->RegisterHalfFoldHoverChangedCallback(
        [weakHost = WeakPtr<FrameNode>(host)](bool isHalfFoldHover) {
            auto host = weakHost.Upgrade();
            CHECK_NULL_VOID(host);
            NavigationTitleUtil::FoldStatusChangedAnimation(host);
        });
    UpdateHalfFoldHoverChangedCallbackId(halfFoldHoverCallbackId);
}

void TitleBarPattern::OnDetachFromMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    if (HasHalfFoldHoverChangedCallbackId()) {
        pipeline->UnRegisterHalfFoldHoverChangedCallback(halfFoldHoverChangedCallbackId_.value());
    }
}

void TitleBarPattern::UpdateBackgroundStyleMultiThread(RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this)]() -> void {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        pattern->UpdateBackgroundStyle(host);
    });
}
} // namespace OHOS::Ace::NG
