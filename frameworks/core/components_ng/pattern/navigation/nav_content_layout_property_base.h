/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAV_CONTENT_LAYOUT_PROPERTY_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAV_CONTENT_LAYOUT_PROPERTY_BASE_H

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {


class ACE_EXPORT NavContentLayoutPropertyBase : public LinearLayoutProperty {
    DECLARE_ACE_TYPE(NavContentLayoutPropertyBase, LinearLayoutProperty);

public:
    explicit NavContentLayoutPropertyBase(bool isVertical) : LinearLayoutProperty(isVertical) {};
    ~NavContentLayoutPropertyBase() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto copy = MakeRefPtr<NavContentLayoutPropertyBase>(IsVertical());
        copy->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        return copy;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
    }
    
    void ExpandConstraintWithSafeArea() override
    {
        auto host = GetHost();
        if (!host || !host->GetIgnoreLayoutProcess()) {
            return;
        }
        RefPtr<FrameNode> parent = host->GetAncestorNodeOfFrame(false);
        CHECK_NULL_VOID(parent);
        IgnoreLayoutSafeAreaOpts options = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
            .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL };
        if (!IsIgnoreOptsValid()) {
            return;
        }
        options = *GetIgnoreLayoutSafeAreaOpts();
        ExpandEdges sae = parent->GetAccumulatedSafeAreaExpand(true, options);
        OptionalSizeF expandedSize;
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto parentConstraint = geometryNode->GetParentLayoutConstraint();
        if (parentConstraint) {
            expandedSize = parentConstraint->selfIdealSize;
        }
        layoutConstraint_->selfIdealSize.SetWidth(
            expandedSize.Width().value_or(0.0f) + sae.left.value_or(0.0f) + sae.right.value_or(0.0f));
        layoutConstraint_->selfIdealSize.SetHeight(
            expandedSize.Height().value_or(0.0f) + sae.top.value_or(0.0f) + sae.bottom.value_or(0.0f));
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAV_CONTENT_LAYOUT_PROPERTY_BASE_H
