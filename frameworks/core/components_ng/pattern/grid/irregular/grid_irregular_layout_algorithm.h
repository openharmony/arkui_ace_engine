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

/**
 * @brief GridIrregularLayout class supports irregular grid items that take multiple rows and multiple columns.
 */
namespace OHOS::Ace::NG {
class GridIrregularLayout : public GridLayoutBaseAlgorithm {
    DECLARE_ACE_TYPE(GridIrregularLayout, GridLayoutBaseAlgorithm);

public:
    explicit GridIrregularLayout(GridLayoutInfo gridLayoutInfo) : GridLayoutBaseAlgorithm(std::move(gridLayoutInfo)) {};

    ~GridIrregularLayout() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    /**
     * @brief Measures the size of Grid based on the given GridLayoutProperty.
     * @param props The GridLayoutProperty object containing the layout properties.
     * @return The main-axis length of Grid contentRect.
     */
    float MeasureSelf(const RefPtr<GridLayoutProperty>& props);

    /**
     * @brief Initializes member variables based on the given GridLayoutProperty.
     * @param props The GridLayoutProperty object containing the layout properties.
     */
    void Init(const RefPtr<GridLayoutProperty>& props);

    /**
     * @brief Fills the content with GridItems up to the target length.
     * @param targetLen The target main-axis length to fill.
     */
    void FillWithItems(float targetLen);

    /**
     * @brief Performs the layout of the children based on the main offset.
     * @param mainOffset The main offset of the layout.
     */
    void LayoutChildren(float mainOffset);

    /**
     * @brief Update variables in GridLayoutInfo at the end of Layout.
     */
    void UpdateLayoutInfo();

    /**
     * @brief Removes children that are out of bounds.
     */
    void RemoveOutOfBoundChildren();

    /**
     * @brief Calculates the cross positions based on the padding.
     * @param padding The padding property of the layout.
     * @return A vector containing the cross positions.
     */
    std::vector<float> CalculateCrossPositions(const PaddingPropertyF& padding);

    /**
     * @brief Checks if Grid has scrolled to the end of its content.
     * @return True if Grid has reached the end, false otherwise.
     */
    inline bool ReachedEnd() const;

    LayoutWrapper* wrapper_ = nullptr;

    std::vector<float> crossLens_; /**< The column widths of the GridItems. */
    float crossGap_ = 0.0f;        /**< The cross-axis gap between GridItems. */
    float mainGap_ = 0.0f;         /**< The main-axis gap between GridItems. */

    float firstRowPos_ = 0.0f; /**< The position of the first row in the layout. */

    ACE_DISALLOW_COPY_AND_MOVE(GridIrregularLayout);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_LAYOUT_H
