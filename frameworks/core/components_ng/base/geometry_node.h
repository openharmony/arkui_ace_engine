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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_GEOMETRY_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_GEOMETRY_NODE_H

#include <list>
#include <memory>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/property/geometry_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/magic_layout_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/position_property.h"

namespace OHOS::Ace::NG {
// GeometryNode acts as a physical property of the size and position of the component
class ACE_EXPORT GeometryNode : public Referenced {
public:
    GeometryNode() = default;

    ~GeometryNode() override = default;

    void Reset();

    bool CheckUnchanged(const GeometryNode& geometryNode)
    {
        return (frame_ == geometryNode.frame_) && (bound_ == geometryNode.bound_) &&
               (content_ == geometryNode.content_) && (parentGlobalOffset_ == geometryNode.parentGlobalOffset_) &&
               (parentLayoutConstraint_ == geometryNode.parentLayoutConstraint_);
    }

    RefPtr<GeometryNode> Clone() const;

    void SetFrameSize(const SizeF& size)
    {
        frame_.rect_.SetSize(size);
    }

    SizeF GetFrameSize() const
    {
        return frame_.rect_.GetSize();
    }

    OffsetF GetFrameOffset() const
    {
        return frame_.rect_.GetOffset();
    }

    const RectF& GetFrameRect() const
    {
        return frame_.rect_;
    }

    void SetFrameOffset(const OffsetF& translate)
    {
        frame_.rect_.SetOffset(translate);
    }

    void SetContentSize(const SizeF& size)
    {
        if (!content_) {
            content_ = std::make_unique<GeometryProperty>();
        }
        content_->rect_.SetSize(size);
    }

    void SetContentOffset(const OffsetF& translate)
    {
        if (!content_) {
            content_ = std::make_unique<GeometryProperty>();
        }
        content_->rect_.SetOffset(translate);
    }

    SizeF GetContentSize() const
    {
        return content_ ? content_->rect_.GetSize() : SizeF();
    }

    OffsetF GetContentOffset() const
    {
        return content_ ? content_->rect_.GetOffset() : OffsetF();
    }

    const std::unique_ptr<GeometryProperty>& GetContent() const
    {
        return content_;
    }

    const GeometryProperty& GetFrame() const
    {
        return frame_;
    }

    const std::unique_ptr<GeometryProperty>& GetBound() const
    {
        return bound_;
    }

    const OffsetF& GetParentGlobalOffset() const
    {
        return parentGlobalOffset_;
    }

    void SetParentGlobalOffset(const OffsetF& parentGlobalOffset)
    {
        parentGlobalOffset_ = parentGlobalOffset;
    }

    void SetParentLayoutConstraint(const LayoutConstraintF& layoutConstraint)
    {
        parentLayoutConstraint_ = layoutConstraint;
    }

    const std::optional<LayoutConstraintF>& GetParentLayoutConstraint() const
    {
        return parentLayoutConstraint_;
    }

    void SetBaselineDistance(float baselineDistance)
    {
        baselineDistance_ = baselineDistance;
    }

    float GetBaselineDistance()
    {
        return baselineDistance_.value_or(frame_.rect_.GetY());
    }

private:
    // the layoutConstraint of prev measure task.
    std::optional<LayoutConstraintF> parentLayoutConstraint_;

    std::optional<float> baselineDistance_;

    // the frame size in parent local coordinate.
    GeometryProperty frame_;
    // the size of border rect in current node local coordinate.
    std::unique_ptr<GeometryProperty> bound_;
    // the size of content rect in current node local coordinate.
    std::unique_ptr<GeometryProperty> content_;

    OffsetF parentGlobalOffset_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_GEOMETRY_NODE_H
