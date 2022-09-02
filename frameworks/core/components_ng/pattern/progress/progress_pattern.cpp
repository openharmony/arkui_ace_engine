/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/progress/progress_pattern.h"

namespace OHOS::Ace::NG {
bool ProgressPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto progressLayoutAlgorithm = DynamicCast<ProgressLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(progressLayoutAlgorithm, false);
    value_=progressLayoutAlgorithm->GetValue();
    maxValue_=progressLayoutAlgorithm->GetMaxValue();
    color_ = progressLayoutAlgorithm->GetColor();
    progressType_ = progressLayoutAlgorithm->GetType();
    strokeWidth_ = progressLayoutAlgorithm->GetStrokeWidth();
    scaleCount_ = progressLayoutAlgorithm->GetScaleCount();
    scaleWidth_ = progressLayoutAlgorithm->GetScaleWidth();
    return true;
}

void ProgressPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}
} // namespace OHOS::Ace::NG