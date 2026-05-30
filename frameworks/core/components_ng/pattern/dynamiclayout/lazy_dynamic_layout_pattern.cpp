/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_pattern.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {
RefPtr<LayoutAlgorithm> LazyDynamicLayoutPattern::CreateLayoutAlgorithm()
{
    return AceType::MakeRefPtr<LazyDynamicLayoutAlgorithm>(customParams_);
}

bool LazyDynamicLayoutPattern::IsAtomicNode() const
{
    return false;
}

void LazyDynamicLayoutPattern::OnAttachToMainTree()
{
    Axis axis = Axis::VERTICAL;
    if (customParams_) {
        axis = customParams_->GetAxis();
    }
    LazyLayoutUtils::ValidateLazyLayoutParentWithAxis(GetHost(), "LazyDynamicLayout", axis);
}

bool LazyDynamicLayoutPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = AceType::DynamicCast<LazyDynamicLayoutAlgorithm>(
        layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);

    const auto& visibleIndexes = layoutAlgorithm->GetVisibleIndexes();
    if (visibleIndexes != prevVisibleIndexes_) {
        prevVisibleIndexes_ = visibleIndexes;
        FireOnVisibleIndexesChange(visibleIndexes);
    }

    return false;
}

void LazyDynamicLayoutPattern::FireOnVisibleIndexesChange(const std::vector<int32_t>& indexes)
{
    CHECK_NULL_VOID(customParams_);
    customParams_->FireOnVisibleIndexesChange(indexes);
}

void LazyDynamicLayoutPattern::UpdateCustomLayoutAlgorithmParam(const RefPtr<LazyCustomLayoutAlgorithmParam>& param)
{
    customParams_ = param;
    if (customParams_) {
        axis_ = customParams_->GetAxis();
    }
}
} // namespace OHOS::Ace::NG