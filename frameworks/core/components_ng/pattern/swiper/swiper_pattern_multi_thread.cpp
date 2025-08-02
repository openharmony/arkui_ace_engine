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

#include "core/components_ng/pattern/swiper/swiper_pattern.h"

#include "base/log/log_wrapper.h"
#include "core/components/common/layout/constants.h"
 
namespace OHOS::Ace::NG {

void SwiperPattern::OnAttachToFrameNodeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetClipToFrame(true);
    renderContext->SetClipToBounds(true);
}

void SwiperPattern::OnDetachFromFrameNodeMultiThread(FrameNode* node)
{
}

void SwiperPattern::OnAttachToMainTreeMultiThread()
{
    do {
        auto host = GetHost();
        CHECK_NULL_BREAK(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_BREAK(pipeline);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_BREAK(renderContext);
        auto indicatorTheme = pipeline->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_BREAK(indicatorTheme);
        renderContext->UpdateClipEdge(indicatorTheme->GetClipEdge());
        InitSurfaceChangedCallback();
    } while (false);
    if (!isInit_) {
        SetOnHiddenChangeForParent();
    }
}

void SwiperPattern::OnDetachFromMainTreeMultiThread()
{
    RemoveOnHiddenChange();
    auto node = GetHost();
    CHECK_NULL_VOID(node);
    auto pipeline = node->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (HasSurfaceChangedCallback()) {
        pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
    }
    pipeline->RemoveWindowStateChangedCallback(node->GetId());
}

void SwiperPattern::ChangeIndexMultiThread(int32_t index, bool useAnimation)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto changeTask = [weakPattern = WeakClaim(this), index, useAnimation]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ChangeIndex(index, useAnimation);
    };
    host->PostAfterAttachMainTreeTask(std::move(changeTask));
}

void SwiperPattern::ChangeIndexMultiThread(int32_t index, SwiperAnimationMode mode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto changeTask = [weakPattern = WeakClaim(this), index, mode]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ChangeIndex(index, mode);
    };
    host->PostAfterAttachMainTreeTask(std::move(changeTask));
}

void SwiperPattern::SetCachedCountMultiThread(int32_t cachedCount)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto setTask = [weakPattern = WeakClaim(this), cachedCount]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetCachedCount(cachedCount);
    };
    host->PostAfterAttachMainTreeTask(std::move(setTask));
}
} // namespace OHOS::Ace::NG
 