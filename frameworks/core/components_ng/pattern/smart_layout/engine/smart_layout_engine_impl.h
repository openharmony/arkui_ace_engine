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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_ENGINE_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_ENGINE_IMPL_H

#include "smart_layout_engine_interface.h"
#include "smart_layout_node.h"

namespace OHOS::Ace::NG {

/**
 * @brief Implementation of ISmartLayoutNode
 *
 * Adapter pattern, holds SmartLayoutNode instance and forwards interface calls to actual implementation.
 */
class SmartLayoutNodeImpl : public ISmartLayoutNode {
public:
    explicit SmartLayoutNodeImpl(std::shared_ptr<SmartLayoutNode> node);
    ~SmartLayoutNodeImpl() override = default;

    void SetLayoutType(SmartLayoutType type) override { node_->SetLayoutType(type); }
    SmartLayoutType GetLayoutType() const override { return node_->GetLayoutType(); }

    void SetFixedSizeConstraints(double width, double height) override
    {
        node_->SetFixedSizeConstraints(width, height);
    }
    bool SolveLayout() override { return node_->SolveLayout(); }
    void SyncData() override { node_->SyncData(); }

    void CreateChildrenFromInfos(const std::vector<ChildLayoutInfo>& infos) override
    {
        node_->CreateChildrenFromInfos(infos);
    }
    const std::vector<std::shared_ptr<ISmartLayoutNode>>& GetChildren() const override;

    void ApplyColumnConstraints() override { node_->ApplyColumnConstraints(); }
    void ApplyRowConstraints() override { node_->ApplyRowConstraints(); }

    const NodePosition& GetPosition() const override { return node_->GetPosition(); }
    const std::string& GetName() const override { return node_->GetName(); }
    const NodeSize& GetSize() const override { return node_->GetSize(); }
    const ScaleInfo& GetScaleInfo() const override { return node_->GetScaleInfo(); }
    int64_t GetNodeId() const override { return node_->GetNodeId(); }
    SmartLayoutRect GetChildrenBoundingBox() const override
    {
        return node_->GetChildrenBoundingBox();
    }
    LayoutContext& GetContext() override { return node_->GetContext(); }

private:
    std::shared_ptr<SmartLayoutNode> node_;
    mutable std::vector<std::shared_ptr<ISmartLayoutNode>> childrenCache_;
};

/**
 * @brief Implementation of ISmartLayoutEngine
 *
 * Provides CreateRootNode method to create layout nodes.
 */
class SmartLayoutEngineImpl : public ISmartLayoutEngine {
public:
    SmartLayoutEngineImpl() = default;
    ~SmartLayoutEngineImpl() override = default;

    std::shared_ptr<ISmartLayoutNode> CreateRootNode(const std::string& name = "root") override;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_ENGINE_IMPL_H