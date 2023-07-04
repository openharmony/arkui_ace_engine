/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"

#include "core/components_ng/pattern/loading_progress/loading_progress_layout_algorithm.h"

namespace OHOS::Ace::NG {

bool LoadingProgressPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);

    auto lodingprogressLayoutAlgorithm =
        DynamicCast<LoadingProgressLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(lodingprogressLayoutAlgorithm, false);
    return true;
}

void LoadingProgressPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    RegisterVisibleAreaChange();
}

void LoadingProgressPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto paintProperty = GetPaintProperty<LoadingProgressPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    enableLoading_ = paintProperty->GetEnableLoadingValue(true);
    enableLoading_ ? StartAnimation() : StopAnimation();
}

void LoadingProgressPattern::OnVisibleChange(bool isVisible)
{
    isVisible_ = isVisible;
    LOGD("Loading OnVisibleChange: isVisible = %d", isVisible_);
    isVisible_ ? StartAnimation() : StopAnimation();
}

void LoadingProgressPattern::StartAnimation()
{
    CHECK_NULL_VOID(loadingProgressModifier_);
    LOGD("Loading StartAnimation: isVisibleArea_ = %d, isVisible_ = %d, isShow_ = %d, enableLoading_ = %d",
        isVisibleArea_, isVisible_, isShow_, enableLoading_);
    if (isVisibleArea_ && isVisible_ && isShow_ && enableLoading_) {
        loadingProgressModifier_->SetVisible(true);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void LoadingProgressPattern::StopAnimation()
{
    CHECK_NULL_VOID(loadingProgressModifier_);
    LOGD("Loading StopAnimation");
    loadingProgressModifier_->SetVisible(false);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void LoadingProgressPattern::RegisterVisibleAreaChange()
{
    if (hasVisibleChangeRegistered_) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        LOGD("Loading VisibleAreaChange CallBack: visible = %d", visible);
        if (visible) {
            pattern->isVisibleArea_ = true;
            pattern->StartAnimation();
        } else {
            pattern->isVisibleArea_ = false;
            pattern->StopAnimation();
        }
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    pipeline->RemoveVisibleAreaChangeNode(host->GetId());
    pipeline->AddVisibleAreaChangeNode(host, 0.0f, callback);

    pipeline->AddWindowStateChangedCallback(host->GetId());
    hasVisibleChangeRegistered_ = true;
}

void LoadingProgressPattern::OnWindowHide()
{
    isShow_ = false;
    LOGD("Loading OnWindowHide");
    StopAnimation();
}

void LoadingProgressPattern::OnWindowShow()
{
    isShow_ = true;
    LOGD("Loading OnWindowShow");
    StartAnimation();
}
} // namespace OHOS::Ace::NG
