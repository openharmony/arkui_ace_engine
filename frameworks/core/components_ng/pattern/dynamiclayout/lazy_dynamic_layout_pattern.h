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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_LAZY_DYNAMIC_LAYOUT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_LAZY_DYNAMIC_LAYOUT_PATTERN_H

#include <string>
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_pattern.h"

namespace OHOS::Ace::NG {

class LazyDynamicLayoutPattern : public LazyLayoutPattern {
    DECLARE_ACE_TYPE(LazyDynamicLayoutPattern, LazyLayoutPattern);

public:
    LazyDynamicLayoutPattern() = default;
    explicit LazyDynamicLayoutPattern(const RefPtr<LazyCustomLayoutAlgorithmParam>& param)
        : customParams_(param)
    {
        if (customParams_) {
            axis_ = customParams_->GetAxis();
        }
    }
    ~LazyDynamicLayoutPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    bool IsAtomicNode() const override;
    void OnAttachToMainTree() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    AdjustOffset GetAdjustOffset() const override
    {
        CHECK_NULL_RETURN(customParams_, {});
        return customParams_->GetAdjustOffset();
    }

    AdjustOffset GetAndResetAdjustOffset() override
    {
        CHECK_NULL_RETURN(customParams_, {});
        AdjustOffset ret = customParams_->GetAdjustOffset();
        customParams_->SetAdjustOffset({});
        return ret;
    }

    void UpdateCustomLayoutAlgorithmParam(const RefPtr<LazyCustomLayoutAlgorithmParam>& param);

    RefPtr<LazyCustomLayoutAlgorithmParam> GetCustomLayoutAlgorithmParam() const
    {
        return customParams_;
    }

private:
    void FireOnVisibleIndexesChange(const std::vector<int32_t>& indexes);

    RefPtr<LazyCustomLayoutAlgorithmParam> customParams_;
    AdjustOffset adjustOffset_;
    std::vector<int32_t> prevVisibleIndexes_;
    Axis axis_ = Axis::VERTICAL;
    ACE_DISALLOW_COPY_AND_MOVE(LazyDynamicLayoutPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_LAZY_DYNAMIC_LAYOUT_PATTERN_H