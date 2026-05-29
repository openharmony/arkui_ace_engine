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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_LAZY_DYNAMIC_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_LAZY_DYNAMIC_LAYOUT_ALGORITHM_H

#include <vector>
#include "core/components_ng/pattern/stack/stack_layout_algorithm.h"
#include "core/components_ng/layout/layout_algorithm.h"

namespace OHOS::Ace::NG {
class LazyCustomLayoutAlgorithmParam;

class ACE_EXPORT LazyDynamicLayoutAlgorithm : public StackLayoutAlgorithm {
    DECLARE_ACE_TYPE(LazyDynamicLayoutAlgorithm, StackLayoutAlgorithm);

public:
    LazyDynamicLayoutAlgorithm() {}
    explicit LazyDynamicLayoutAlgorithm(const RefPtr<LazyCustomLayoutAlgorithmParam>& param);
    ~LazyDynamicLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    const std::vector<int32_t>& GetVisibleIndexes() const
    {
        return visibleIndexes_;
    }

private:
    void RecycleOutOfThreshold(LayoutWrapper* layoutWrapper);
    void ProcessAdjustOffset(LayoutWrapper* layoutWrapper, float adjustOffset,  float prevMainSize);

    RefPtr<LazyCustomLayoutAlgorithmParam> customParams_;
    float prevMainSize_ = 0;
    Axis axis_ = Axis::VERTICAL;
    std::vector<int32_t> visibleIndexes_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_LAZY_DYNAMIC_LAYOUT_ALGORITHM_H