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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_LAYOUT_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_LAYOUT_CONTROLLER_H

#include <map>

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"

namespace OHOS::Ace::NG {
class GridLayoutController : public virtual AceType {
    DECLARE_ACE_TYPE(GridLayoutController, AceType);

public:
    GridLayoutController() = default;
    ~GridLayoutController() override = default;

    void FillGridViewportAndMeasureChildren(float mainSize, float crossSize,
        const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper);
    void MeasureRecordedItems(float mainSize, float crossSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty,
        LayoutWrapper* layoutWrapper, float& mainLength);

    void FillBlankAtStart(float mainSize, float crossSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty,
        LayoutWrapper* layoutWrapper, float& mainLength);
    float FillNewLineForward(float crossSize, float mainSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty,
        LayoutWrapper* layoutWrapper);

    void FillBlankAtEnd(float mainSize, float crossSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty,
        LayoutWrapper* layoutWrapper, float& mainLength);
    float FillNewLineBackward(float crossSize, float mainSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty,
        LayoutWrapper* layoutWrapper);
    Axis GetAxis() const;

    bool UpdateScrollPosition(float offset, int32_t source);
    void StripItemsOutOfViewport();

    void ModifyCurrentOffsetWhenReachEnd(float mainSize);

    void SetMarkNeedRenderTask(std::function<void()>&& task)
    {
        markNeedRenderTask_ = std::move(task);
    }

private:
    void PrintGridMatrix() const;
    void PrintLineHeightMap() const;
    LayoutConstraintF MakeMeasureConstraintForGridItem(float mainSize, float crossSize, uint32_t itemFractionCount,
        const RefPtr<GridLayoutProperty>& gridLayoutProperty) const;

    bool isVertical_ = true;
    bool isConfiguredScrollable_ = true;
    float currentOffset_ = 0.0f;
    float prevOffset_ = 0.0f;

    int32_t currentIndex_ = 0;
    int32_t startIndex_ = 0;
    int32_t endIndex_ = -1;

    uint32_t crossCount_ = 0;
    uint32_t mainCount_ = 0;

    int32_t currentMainLineIndex_ = 0; // it equals to row index in vertical grid
    int32_t startMainLineIndex_ = 0;
    int32_t endMainLineIndex_ = 0;

    bool reachEnd_ = false;
    bool reachStart_ = false;

    // in vertical grid, this map is like: [rowIndex: [itemIndex: fragmentCount], [itemIndex: fragmentCount]]
    // for e.g, when a vertical grid has two [GridItem]s in first row, [gridMatrix_] is like [0: [0: 1fr], [1: 2fr]]
    std::map<int32_t, std::map<int32_t, uint32_t>> gridMatrix_;
    // in vertical grid, this map is like: [rowIndex: rowHeight]
    std::map<int32_t, float> lineHeightMap_;
    
    std::function<void()> markNeedRenderTask_;

    friend class GridLayoutAlgorithm;
    friend class GridPattern;
    ACE_DISALLOW_COPY_AND_MOVE(GridLayoutController);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_LAYOUT_CONTROLLER_H
