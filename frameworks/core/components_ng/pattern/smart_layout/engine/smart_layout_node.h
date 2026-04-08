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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_NODE_H

#include <memory>
#include "localsmt/localsmt.h"
#include "smart_layout_context.h"
#include "smart_layout_types.h"
#include "smart_layout_constraints.h"

namespace OHOS::Ace::NG {

inline const std::string CHILD_NODE_PREFIX = "child_";
/**
 * @brief Node representation for smart layout algorithm
 *
 * This class represents a layout node with position, size, scale information,
 * and edge spaces. It integrates with the localsmt solver for constraint-based layout.
 * Each node contains its own LayoutContext for encapsulation.
 */
class ACE_EXPORT SmartLayoutNode {
public:
    /**
     * @brief Create a root node with a new Engine instance
     * @param name Unique name for this node (default: "root")
     * @return Shared pointer to the created root node
     */
    static std::shared_ptr<SmartLayoutNode> CreateRootNode(const std::string& name = "root");

    /**
     * @brief Construct a SmartLayoutNode with given engine and name
     * @param engine Shared pointer to the SMT engine
     * @param name Unique name for this node (used as variable prefix)
     */
    explicit SmartLayoutNode(std::shared_ptr<localsmt::Engine> engine, const std::string& name);

    ~SmartLayoutNode() = default;

    /**
     * @brief Create a child node sharing the same engine
     * @param info Child layout info
     * @param spaces Edge spaces for the child
     * @return Created child node
     */
    std::shared_ptr<SmartLayoutNode> CreateChildNode(
        const ChildLayoutInfo& info, const EdgesSpaces& spaces);

    /**
     * @brief Solve the constraint system
     * @return true if solution found, false otherwise
     */
    bool SolveLayout();

    /**
     * @brief Set fixed size values (without constraints)
     * @param width Width value
     * @param height Height value
     */
    void SetFixedSize(double width, double height);

    /**
     * @brief Set fixed size with constraints to the engine
     * @param width Width value
     * @param height Height value
     */
    void SetFixedSizeConstraints(double width, double height);

    /**
     * @brief Set children nodes for this node
     * @param children Vector of child nodes
     */
    void SetChildren(const std::vector<std::shared_ptr<SmartLayoutNode>>& children);

    /**
     * @brief Create all child nodes from child layout info vector
     * @param childInfos Vector of child layout info
     */
    void CreateChildrenFromInfos(const std::vector<ChildLayoutInfo>& childInfos);

    /**
     * @brief Calculate edge spaces for a child
     * @param info Current child info
     * @param prevInfo Previous child info (nullptr if first)
     * @param nextInfo Next child info (nullptr if last)
     * @param layoutType Column or Row layout type
     * @param parentSize Parent container size
     * @return Edge spaces for the child
     */
    EdgesSpaces CalculateChildSpaces(const ChildLayoutInfo& info,
                                      const ChildLayoutInfo* prevInfo,
                                      const ChildLayoutInfo* nextInfo,
                                      SmartLayoutType layoutType,
                                      const SmartLayoutSize& parentSize);

    /**
     * @brief Calculate spacing between two children along the layout axis
     * @param child1 First child info
     * @param child2 Second child info
     * @param layoutType Column or Row layout type
     * @return Spacing between children
     */
    double CalculateChildSpacing(const ChildLayoutInfo& child1,
                                  const ChildLayoutInfo& child2,
                                  SmartLayoutType layoutType);

    /**
     * @brief Synchronize data from the SMT engine
     */
    void SyncData();

    /**
     * @brief Apply column layout constraints using internal constraints builder
     */
    void ApplyColumnConstraints();

    /**
     * @brief Apply row layout constraints using internal constraints builder
     */
    void ApplyRowConstraints();

    // Getters for context
    LayoutContext& GetContext() { return context_; }
    const LayoutContext& GetContext() const { return context_; }

    // Getters
    const std::string& GetName() const { return name_; }
    int64_t GetNodeId() const { return id_; }
    const NodePosition& GetPosition() const { return position_; }
    const NodeSize& GetSize() const { return size_; }
    const ScaleInfo& GetScaleInfo() const { return scaleInfo_; }
    const EdgesSpaces& GetSpace() const { return space_; }
    SmartLayoutNode* GetParent() const { return parent_; }
    const std::vector<std::shared_ptr<SmartLayoutNode>>& GetChildren() const { return children_; }

    /**
     * @brief Get union bounding box of all children
     * Calculates the combined bounding box that encloses all child nodes.
     * @return SmartLayoutRect representing the union bounding box of all children
     */
    SmartLayoutRect GetChildrenBoundingBox() const;

    // Setters for space
    void SetSpace(const EdgesSpaces& space) { space_ = space; }
    EdgesSpaces& GetMutableSpace() { return space_; }

    // Set initial position from child layout info
    void SetInitialPosition(double offsetX, double offsetY);

    // Convenience methods for context access
    localsmt::Engine* GetEngine() { return engine_.get(); }
    std::shared_ptr<localsmt::Engine> GetSharedEngine() { return engine_; }
    SmartLayoutType GetLayoutType() const { return context_.layoutType; }
    void SetLayoutType(SmartLayoutType type) { context_.layoutType = type; }
    SmartLayoutAlign GetMainAxisAlign() const { return context_.mainAxisAlign; }
    void SetMainAxisAlign(SmartLayoutAlign align) { context_.mainAxisAlign = align; }
    SmartLayoutAlign GetCrossAxisAlign() const { return context_.crossAxisAlign; }
    void SetCrossAxisAlign(SmartLayoutAlign align) { context_.crossAxisAlign = align; }
    const SmartLayoutSize& GetLayoutSize() const { return context_.size; }
    void SetLayoutSize(const SmartLayoutSize& size) { context_.size = size; }
    void SetLayoutSize(double width, double height) { context_.size = SmartLayoutSize(width, height); }

private:
    std::shared_ptr<localsmt::Engine> engine_ = nullptr;
    std::string name_;
    int64_t id_ = 0;
    NodePosition position_ = {};
    NodeSize size_ = {};
    ScaleInfo scaleInfo_ = {};
    EdgesSpaces space_ = {};
    SmartLayoutNode* parent_ = nullptr;
    std::vector<std::shared_ptr<SmartLayoutNode>> children_;
    LayoutContext context_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_SMART_LAYOUT_NODE_H