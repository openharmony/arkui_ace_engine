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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_CONSTRAINTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_CONSTRAINTS_H

#include "smart_layout_context.h"
#include "smart_layout_node.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {

/**
 * @brief Statistics for child nodes (calculated in single pass)
 */
struct ChildStatistics {
    double sumOfAllChildHeight = 0.0;
    double sumOfAllChildWidth = 0.0;
    double maxChildWidth = 0.0;
    double maxChildHeight = 0.0;
    size_t childCount = 0;
};

/**
 * @brief Constraint builder for smart layout algorithm
 *
 * This class handles the creation and addition of constraints to the SMT solver
 * for different layout scenarios (column, row, default).
 */
class ACE_EXPORT SmartLayoutConstraints {
public:
    SmartLayoutConstraints() = default;
    ~SmartLayoutConstraints() = default;

    /**
     * @brief Add constraints for column layout
     * @param parent Parent node to add constraints for
     */
    void AddColumnConstraints(SmartLayoutNode& parent);

    /**
     * @brief Add constraints for row layout
     * @param parent Parent node to add constraints for
     */
    void AddRowConstraints(SmartLayoutNode& parent);

    /**
     * @brief Add default constraints (non-negative sizes, boundary constraints)
     * @param parent Parent node
     */
    void AddDefaultConstraints(SmartLayoutNode& parent);

    /**
     * @brief Calculate all child statistics in a single pass
     * @param parent Parent node containing children
     * @return ChildStatistics with all aggregated values
     */
    static ChildStatistics CalculateChildStatistics(const SmartLayoutNode& parent);

    /**
     * @brief Get sum of all child heights (deprecated, use CalculateChildStatistics)
     * @param parent Parent node containing children
     * @return Sum of child heights
     */
    static double GetSumOfAllChildHeight(const SmartLayoutNode& parent);

    /**
     * @brief Get sum of all child widths
     * @param parent Parent node containing children
     * @return Sum of child widths
     */
    static double GetSumOfAllChildWidth(const SmartLayoutNode& parent);

    /**
     * @brief Get maximum width of all child nodes
     * @param parent Parent node containing children
     * @return Maximum child width
     */
    static double GetMaxWidthOfAllChild(const SmartLayoutNode& parent);

    /**
     * @brief Get maximum height of all child nodes
     * @param parent Parent node containing children
     * @return Maximum child height
     */
    static double GetMaxHeightOfAllChild(const SmartLayoutNode& parent);

private:
    /**
     * @brief Calculate and add size scale constraint
     * @param parent Parent node
     * @param sumOfAllChildHeight Sum of all child heights
     * @param maxChildWidth Maximum child width
     */
    void AddSizeScaleConstraint(SmartLayoutNode& parent, double sumOfAllChildHeight, double maxChildWidth);

    /**
     * @brief Calculate and add size scale constraint for row layout
     * @param parent Parent node
     * @param sumOfAllChildWidth Sum of all child widths
     * @param maxChildHeight Maximum child height
     */
    void AddRowSizeScaleConstraint(SmartLayoutNode& parent, double sumOfAllChildWidth, double maxChildHeight);

    /**
     * @brief Add child size constraints
     * @param parent Parent node
     * @param child Child node
     */
    void AddChildSizeConstraints(SmartLayoutNode& parent, SmartLayoutNode& child);

    /**
     * @brief Add cross-axis alignment constraint
     * @param parent Parent node
     * @param child Child node
     * @param isRow true for row layout, false for column layout
     */
    void AddCrossAxisAlignmentConstraint(SmartLayoutNode& parent, SmartLayoutNode& child, bool isRow = false);

    /**
     * @brief Add child main-axis position constraint
     * @param parent Parent node
     * @param child Child node
     * @param prev Previous child node (nullptr for first child)
     * @param index Child index
     * @param isRow true for row layout, false for column layout
     */
    void AddChildMainAxisPosition(SmartLayoutNode& parent, SmartLayoutNode& child,
        SmartLayoutNode* prev, size_t index, bool isRow = false);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_CONSTRAINTS_H