/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_LAYOUT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_LAYOUT_H

#include "base/utils/noncopyable.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_layout_base_algorithm.h"

namespace OHOS::Ace::NG {
class GridIrregularLayout : public GridLayoutBaseAlgorithm {
    DECLARE_ACE_TYPE(GridIrregularLayout, GridLayoutBaseAlgorithm);

public:
    explicit GridIrregularLayout(GridLayoutInfo gridLayoutInfo) : GridLayoutBaseAlgorithm(std::move(gridLayoutInfo)) {};
    ~GridIrregularLayout() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void Init(const RefPtr<GridLayoutProperty>& props);
    void LoadChild(LayoutWrapper* wrapper,int32_t index);

    LayoutWrapper* wrapper_ = nullptr;

    std::vector<float> crossLens_;
    float crossGap_ = 0.0f;
    float mainGap_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(GridIrregularLayout);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_LAYOUT_H
