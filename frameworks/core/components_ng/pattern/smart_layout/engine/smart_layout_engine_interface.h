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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_ENGINE_INTERFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_ENGINE_INTERFACE_H

#include <memory>
#include <string>
#include <vector>
#include "smart_layout_types.h"
#include "smart_layout_context.h"

namespace OHOS::Ace::NG {

/**
 * @brief Abstract interface for node operations
 *
 * Defines SmartLayoutNode operation interface for decoupling algorithm layer from engine implementation.
 * Implementation class is in libsmartlayout.z.so.
 */
class ISmartLayoutNode {
public:
    virtual ~ISmartLayoutNode() = default;

    virtual void SetLayoutType(SmartLayoutType type) = 0;
    virtual SmartLayoutType GetLayoutType() const = 0;

    virtual void SetFixedSizeConstraints(double width, double height) = 0;
    virtual bool SolveLayout() = 0;
    virtual void SyncData() = 0;

    virtual void CreateChildrenFromInfos(const std::vector<ChildLayoutInfo>& infos) = 0;
    virtual const std::vector<std::shared_ptr<ISmartLayoutNode>>& GetChildren() const = 0;

    virtual void ApplyColumnConstraints() = 0;
    virtual void ApplyRowConstraints() = 0;
    virtual void ApplyGeneralConstraints() = 0;
    virtual void SetBoundingBox(const SmartLayoutRect& box) = 0;
    virtual const SmartLayoutRect& GetBoundingBox() const = 0;

    virtual int64_t GetNodeId() const = 0;
    virtual const std::string& GetName() const = 0;
    virtual const NodePosition& GetPosition() const = 0;
    virtual const NodeSize& GetSize() const = 0;
    virtual const ScaleInfo& GetScaleInfo() const = 0;
    virtual SmartLayoutRect GetChildrenBoundingBox() const = 0;
    virtual void SetAvoidSafeArea(bool avoid) = 0;

    virtual LayoutContext& GetContext() = 0;
};

/**
 * @brief Abstract interface for SmartLayoutEngine entry point
 *
 * Defines engine creation entry for obtaining engine instance after dynamic loading.
 */
class ISmartLayoutEngine {
public:
    virtual ~ISmartLayoutEngine() = default;

    /**
     * @brief Create root node
     * @param name Node name
     * @return Node interface pointer
     */
    virtual std::shared_ptr<ISmartLayoutNode> CreateRootNode(const std::string& name = "root") = 0;
};

using SmartLayoutEngineCreateFunc = ISmartLayoutEngine* (*)();

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_ENGINE_INTERFACE_H