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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/smart_layout/engine/smart_layout_types.h"
#include "core/components_ng/pattern/smart_layout/engine/smart_layout_engine_interface.h"

namespace OHOS::Ace::NG {

/**
 * @brief Smart layout algorithm using SMT solver for constraint-based layout
 *
 * This algorithm uses the localsmt solver to compute optimal positions and sizes
 * for child elements based on constraints and alignment settings.
 * The engine is owned by the root node and shared with child nodes.
 */
class ACE_EXPORT SmartLayoutAlgorithm {
public:
    SmartLayoutAlgorithm() = default;
    ~SmartLayoutAlgorithm() = default;

    /**
     * @brief Perform smart layout (auto-detect layout direction from container type)
     * @param layoutWrapper Layout wrapper containing children to layout
     * @return true if smart layout executed, solved and applied successfully
     */
    bool PerformSmartLayout(LayoutWrapper* layoutWrapper);

private:
    /**
     * @brief Get layout type from layout wrapper's host tag
     * @param layoutWrapper Layout wrapper
     * @return SmartLayoutType::COLUMN for Column, SmartLayoutType::ROW for Row (default)
     */
    SmartLayoutType GetLayoutTypeFromWrapper(LayoutWrapper* layoutWrapper);

    /**
     * @brief Execute layout with specified type
     * @param layoutWrapper Layout wrapper
     * @param layoutType Column or Row layout type
     * @return true if layout solved and results applied successfully
     */
    bool ExecuteLayout(LayoutWrapper* layoutWrapper, SmartLayoutType layoutType);

    /**
     * @brief Initialize layout context with parent info
     * @param layoutWrapper Layout wrapper
     * @return true if initialization successful
     */
    bool InitializeLayoutContext(LayoutWrapper* layoutWrapper);

    /**
     * @brief Process and build child layout nodes
     * @param layoutWrapper Layout wrapper
     */
    void ProcessLayoutChildren(LayoutWrapper* layoutWrapper);

    /**
     * @brief Apply solved layout results to children
     * @param layoutWrapper Layout wrapper
     * @return true if results were applied to at least one child node
     */
    bool ApplyLayoutResults(LayoutWrapper* layoutWrapper);

    /**
     * @brief Collect child layout info from layout wrapper
     * @param layoutWrapper Layout wrapper
     * @return Vector of child layout info
     */
    std::vector<ChildLayoutInfo> CollectChildInfo(LayoutWrapper* layoutWrapper);

private:
    std::shared_ptr<ISmartLayoutNode> rootNode_ = nullptr;

    // Helper function declarations
    /**
     * @brief Build node ID mapping for fast lookup
     * @param children List of child nodes
     * @return Map with node ID as key
     */
    std::unordered_map<int64_t, std::shared_ptr<ISmartLayoutNode>> BuildNodeIdMap(
        const std::vector<std::shared_ptr<ISmartLayoutNode>>& children);

    /**
     * @brief Calculate offset with margin
     * @param layoutNode Layout node
     * @param geoNode Geometry node (for getting margin)
     * @param boundingBoxOffsetX Pre-calculated bounding box X offset
     * @param boundingBoxOffsetY Pre-calculated bounding box Y offset
     * @return Calculated offset
     */
    OffsetF CalculateOffsetWithMargin(
        const ISmartLayoutNode& layoutNode,
        const RefPtr<GeometryNode> geoNode,
        double boundingBoxOffsetX,
        double boundingBoxOffsetY);

    /**
     * @brief Apply layout result to a single child
     * @param childWrapper Child element LayoutWrapper
     * @param nodeMap Node mapping table
     * @param sizeScale Size scale factor
     * @param boundingBoxOffsetX Pre-calculated bounding box X offset
     * @param boundingBoxOffsetY Pre-calculated bounding box Y offset
     */
    void ApplyChildLayout(
        const RefPtr<LayoutWrapper>& childWrapper,
        const std::unordered_map<int64_t, std::shared_ptr<ISmartLayoutNode>>& nodeMap,
        double sizeScale,
        double boundingBoxOffsetX,
        double boundingBoxOffsetY);

    /**
     * @brief Pre-calculate bounding box offsets for all children
     * @return Pair of (offsetX, offsetY) for bounding box centering
     */
    std::pair<double, double> CalculateBoundingBoxOffsets();
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_ALGORITHM_H