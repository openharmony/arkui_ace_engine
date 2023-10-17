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

#include "core/components_ng/pattern/divider/divider_pattern.h"

namespace OHOS::Ace::NG {
bool DividerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto dividerLayoutAlgorithm = DynamicCast<DividerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(dividerLayoutAlgorithm, false);
    constrainStrokeWidth_ = dividerLayoutAlgorithm->GetConstrainStrokeWidth();
    dividerLength_ = dividerLayoutAlgorithm->GetDividerLength();
    vertical_ = dividerLayoutAlgorithm->GetVertical();
    strokeWidthLimitation_ = dividerLayoutAlgorithm->GetStrokeWidthLimitation();
    return true;
}
} // namespace OHOS::Ace::NG
