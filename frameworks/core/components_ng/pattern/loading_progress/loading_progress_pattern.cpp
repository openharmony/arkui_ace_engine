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
}

void LoadingProgressPattern::OnModifyDone()
{
    auto layoutProperty = GetLayoutProperty<LoadingProgressLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto visibilityProp = layoutProperty->GetVisibility().value_or(VisibleType::VISIBLE);
    CHECK_NULL_VOID(visibilityProp != visibilityProp_);
    visibilityProp_ = visibilityProp;
    CHECK_NULL_VOID(loadingProgressModifier_);
    loadingProgressModifier_->SetVisible(visibilityProp_ == VisibleType::VISIBLE);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}
} // namespace OHOS::Ace::NG
