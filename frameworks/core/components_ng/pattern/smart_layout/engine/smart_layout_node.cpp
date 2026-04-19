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

#include "smart_layout_node.h"
#include "smart_layout_log.h"
#include "smart_layout_constraints.h"

namespace OHOS::Ace::NG {

// Maximum layout size bound (16K resolution, sufficient for all practical screen sizes)
constexpr double MAX_LAYOUT_SIZE = 16384.0;

std::shared_ptr<SmartLayoutNode> SmartLayoutNode::CreateRootNode(const std::string& name)
{
    auto engine = std::make_shared<localsmt::Engine>();
    return std::make_shared<SmartLayoutNode>(engine, name);
}

SmartLayoutNode::SmartLayoutNode(std::shared_ptr<localsmt::Engine> engine, const std::string& name)
    : engine_(engine),
      name_(name),
      position_{
          // Set bounds: offsetX/offsetY >= 0 (eliminates 2 non-negativity constraints per child)
          {engine_->Var((name_ + ".x").c_str(), 0.0, MAX_LAYOUT_SIZE), 0.0},
          {engine_->Var((name_ + ".y").c_str(), 0.0, MAX_LAYOUT_SIZE), 0.0}
      },
      size_{
          // Set bounds: width/height >= 0 (eliminates 2 non-negativity constraints per node)
          {engine_->Var((name_ + ".w").c_str(), 0.0, MAX_LAYOUT_SIZE), 0.0},
          {engine_->Var((name_ + ".h").c_str(), 0.0, MAX_LAYOUT_SIZE), 0.0}
      },
      scaleInfo_{
          {engine_->Var((name_ + ".mainAxisSpaceScale").c_str(), 1.0), 1.0},
          {engine_->Var((name_ + ".crossAxisSpaceScale").c_str(), 1.0), 1.0},
          {engine_->Var((name_ + ".sizeScale").c_str(), 1.0), 1.0}
      }
{
}

std::shared_ptr<SmartLayoutNode> SmartLayoutNode::CreateChildNode(
    const ChildLayoutInfo& info, const EdgesSpaces& spaces)
{
    std::string childName = CHILD_NODE_PREFIX + std::to_string(info.id);
    auto node = std::make_shared<SmartLayoutNode>(engine_, childName);
    node->id_ = info.id;

    // Set size (Blank node: height is 0 for Column, width is 0 for Row)
    if (info.isBlank) {
        if (context_.layoutType == SmartLayoutType::COLUMN) {
            node->SetFixedSize(info.width, 0);
        } else {
            node->SetFixedSize(0, info.height);
        }
    } else {
        node->SetFixedSize(info.width, info.height);
    }

    // Set initial position from child layout info
    node->SetInitialPosition(info.offsetX, info.offsetY);

    // Set spaces
    node->SetSpace(spaces);

    return node;
}

bool SmartLayoutNode::SolveLayout()
{
    if (!engine_) {
        return false;
    }
    bool result = engine_->Solve();
    if (result) {
        SyncData();
    } else {
        SMT_LOGE("localsmt failed to find a solution for the given constraints");
    }
    return result;
}

void SmartLayoutNode::SetFixedSize(double width, double height)
{
    size_.width.value = width;
    size_.height.value = height;
}

void SmartLayoutNode::SetInitialPosition(double offsetX, double offsetY)
{
    position_.offsetX.value = offsetX;
    position_.offsetY.value = offsetY;
}

void SmartLayoutNode::SetFixedSizeConstraints(double width, double height)
{
    size_.width.value = width;
    size_.height.value = height;
    if (engine_) {
        engine_->Add(size_.width.expr == width);
        engine_->Add(size_.height.expr == height);
    }
}

void SmartLayoutNode::SetChildren(const std::vector<std::shared_ptr<SmartLayoutNode>>& children)
{
    children_ = children;
    for (auto& child : children_) {
        child->parent_ = this;
    }
}

void SmartLayoutNode::CreateChildrenFromInfos(const std::vector<ChildLayoutInfo>& childInfos)
{
    if (childInfos.empty()) {
        return;
    }

    std::vector<std::shared_ptr<SmartLayoutNode>> childNodes;
    for (size_t i = 0; i < childInfos.size(); ++i) {
        const ChildLayoutInfo* prevInfo = (i > 0) ? &childInfos[i - 1] : nullptr;
        const ChildLayoutInfo* nextInfo = (i < childInfos.size() - 1) ? &childInfos[i + 1] : nullptr;

        auto spaces = CalculateChildSpaces(childInfos[i], prevInfo, nextInfo,
            context_.layoutType, context_.size);
        auto node = CreateChildNode(childInfos[i], spaces);
        childNodes.push_back(node);
    }

    if (!childNodes.empty()) {
        SetChildren(childNodes);
    }
}

EdgesSpaces SmartLayoutNode::CalculateChildSpaces(const ChildLayoutInfo& info,
    const ChildLayoutInfo* prevInfo, const ChildLayoutInfo* nextInfo,
    SmartLayoutType layoutType, const SmartLayoutSize& parentSize)
{
    EdgesSpaces spaces;
    const bool isColumn = (layoutType == SmartLayoutType::COLUMN);

    if (prevInfo == nullptr) {
        if (isColumn) {
            spaces.top = info.offsetY;
            spaces.left = info.offsetX;
        } else {
            spaces.left = info.offsetX;
        }
    } else if (nextInfo != nullptr) {
        if (isColumn) {
            spaces.top = CalculateChildSpacing(*prevInfo, info, layoutType);
            spaces.left = info.offsetX;
        } else {
            spaces.left = CalculateChildSpacing(*prevInfo, info, layoutType);
        }
    }

    if (nextInfo != nullptr) {
        if (isColumn) {
            spaces.bottom = CalculateChildSpacing(info, *nextInfo, layoutType);
            spaces.left = info.offsetX;
        } else {
            spaces.right = CalculateChildSpacing(info, *nextInfo, layoutType);
        }
    }

    if (nextInfo == nullptr) {
        if (isColumn) {
            spaces.bottom = parentSize.Height() - (info.offsetY + info.height);
            spaces.left = info.offsetX;
        } else {
            spaces.right = parentSize.Width() - (info.offsetX + info.width);
        }
    }

    if (info.isBlank) {
        if (isColumn) {
            spaces.bottom += info.height;
            spaces.left = info.offsetX;
        } else {
            spaces.right += info.width;
        }
    }

    return spaces;
}

double SmartLayoutNode::CalculateChildSpacing(const ChildLayoutInfo& child1,
    const ChildLayoutInfo& child2, SmartLayoutType layoutType)
{
    if (layoutType == SmartLayoutType::COLUMN) {
        return child2.offsetY - (child1.offsetY + child1.height);
    } else {
        return child2.offsetX - (child1.offsetX + child1.width);
    }
}

void SmartLayoutNode::SyncData()
{
    if (!engine_) {
        return;
    }
    position_.offsetX.value = engine_->GetVariable(name_ + ".x");
    position_.offsetY.value = engine_->GetVariable(name_ + ".y");
    size_.width.value = engine_->GetVariable(name_ + ".w");
    size_.height.value = engine_->GetVariable(name_ + ".h");
    if (!children_.empty()) {
        scaleInfo_.mainAxisSpaceScale.value = engine_->GetVariable(name_ + ".mainAxisSpaceScale");
        scaleInfo_.crossAxisSpaceScale.value = engine_->GetVariable(name_ + ".crossAxisSpaceScale");
        scaleInfo_.sizeScale.value = engine_->GetVariable(name_ + ".sizeScale");
    }
}

SmartLayoutRect SmartLayoutNode::GetChildrenBoundingBox() const
{
    if (children_.empty()) {
        return SmartLayoutRect();
    }

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxRight = std::numeric_limits<double>::lowest();
    double maxBottom = std::numeric_limits<double>::lowest();

    for (const auto& child : children_) {
        double childX = child->GetPosition().offsetX.value;
        double childY = child->GetPosition().offsetY.value;
        double childW = child->GetSize().width.value;
        double childH = child->GetSize().height.value;

        minX = std::min(minX, childX);
        minY = std::min(minY, childY);
        maxRight = std::max(maxRight, childX + childW);
        maxBottom = std::max(maxBottom, childY + childH);
    }

    return SmartLayoutRect(minX, minY, maxRight - minX, maxBottom - minY);
}

void SmartLayoutNode::ApplyColumnConstraints()
{
    SmartLayoutConstraints constraintsBuilder;
    constraintsBuilder.AddColumnConstraints(*this);
}

void SmartLayoutNode::ApplyRowConstraints()
{
    SmartLayoutConstraints constraintsBuilder;
    constraintsBuilder.AddRowConstraints(*this);
}

} // namespace OHOS::Ace::NG