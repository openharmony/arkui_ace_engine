/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_CONTAINER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_CONTAINER_PATTERN_H

#include <cstddef>
#include <optional>

#include "base/geometry/ng/rect_t.h"
#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/shape_container_layout_algorithm.h"
#include "core/components_ng/pattern/shape/shape_container_modifier.h"
#include "core/components_ng/pattern/shape/shape_container_paint_property.h"
#include "core/components_ng/pattern/shape/shape_view_box.h"

namespace OHOS::Ace::NG {
class ShapeContainerPattern : public Pattern {
    DECLARE_ACE_TYPE(ShapeContainerPattern, Pattern);

public:
    ShapeContainerPattern() = default;
    ~ShapeContainerPattern() override = default;

    void UpdatePropertyImpl(const std::string& key, RefPtr<PropertyValueBase> value) override;

    bool IsEnableMatchParent() override
    {
        return true;
    }

    bool IsEnableChildrenMatchParent() override
    {
        return true;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<ShapeContainerLayoutAlgorithm>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<ShapeContainerPaintProperty>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    void OnModifyDone() override;

    bool IsAtomicNode() const override
    {
        return false;
    }

    void AddChildShapeNode(WeakPtr<FrameNode> childNode)
    {
        ChildNodes_.push_back(std::move(childNode));
    }

private:
    void ViewPortTransform();
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    bool isShapeContainerInit_ = false;
    std::vector<WeakPtr<FrameNode>> ChildNodes_;
    RefPtr<ShapeContainerModifier> shapeContainerModifier_;

    ACE_DISALLOW_COPY_AND_MOVE(ShapeContainerPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_CONTAINER_PATTERN_H
