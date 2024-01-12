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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_LAYOUT_ALGORITHM_H

#include "base/utils/noncopyable.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_layout_base_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"

/**
 * @brief GridIrregularLayout class supports irregular grid items that take multiple rows and multiple columns.
 */
namespace OHOS::Ace::NG {
class GridIrregularLayoutAlgorithm : public GridLayoutBaseAlgorithm {
    DECLARE_ACE_TYPE(GridIrregularLayoutAlgorithm, GridLayoutBaseAlgorithm);

public:
    explicit GridIrregularLayoutAlgorithm(GridLayoutInfo gridLayoutInfo)
        : GridLayoutBaseAlgorithm(std::move(gridLayoutInfo)) {};

    ~GridIrregularLayoutAlgorithm() override = default;

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

    void MeasureOnOffset(float mainSize);

    void MeasureOnJump(float mainSize);

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

    /**
     * @brief Transforms GridLayoutInfo::scrollAlign_ into other ScrollAlign values.
     */
    void TransformAutoScrollAlign();

    /**
     *
     * @param jumpIdx The GridItem index to jump to.
     * @return The line index of the item in GridMatrix.
     */
    int32_t FindJumpLineIdx(int32_t jumpIdx);

    /**
     * @brief Prepares GridLayoutInfo::lineHeightMap_ using GridIrregularFiller.
     *
     * If the algorithm identifies that mainSize can't be filled with the current scrollAlign_ and jumpLineIdx, these
     * params will be adjusted. For instance, jumping to the last line with ScrollAlign::START isn't possible.
     *
     * @param mainSize The main-axis length of the grid.
     * @param jumpLineIdx The line index to jump to, can be adjusted during the function call.
     */
    void PrepareLineHeight(float mainSize, int32_t& jumpLineIdx);

    LayoutWrapper* wrapper_ = nullptr;

    std::vector<float> crossLens_; /**< The column widths of the GridItems. */
    float crossGap_ = 0.0f;        /**< The cross-axis gap between GridItems. */
    float mainGap_ = 0.0f;         /**< The main-axis gap between GridItems. */

    ACE_DISALLOW_COPY_AND_MOVE(GridIrregularLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_LAYOUT_ALGORITHM_H
