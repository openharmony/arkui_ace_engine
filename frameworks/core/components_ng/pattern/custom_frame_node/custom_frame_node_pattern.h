/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_CUSTOM_FRAME_NODE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_CUSTOM_FRAME_NODE_PATTERN_H

#include <functional>

#include "core/components_ng/pattern/custom_frame_node/custom_frame_node_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/render_node/render_node_modifier.h"
#include "core/components_ng/pattern/render_node/render_node_paint_method.h"
#include "core/components_ng/pattern/stack/stack_layout_algorithm.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT CustomFrameNodePattern : public Pattern {
    DECLARE_ACE_TYPE(CustomFrameNodePattern, Pattern);

public:
    CustomFrameNodePattern() = default;
    ~CustomFrameNodePattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CustomFrameNodeLayoutAlgorithm>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        auto layoutProperty = MakeRefPtr<StackLayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
        return layoutProperty;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        auto renderNodePaintProperty = MakeRefPtr<RenderNodePaintProperty>();
        renderNodePaintProperty->UpdateRenderNodeFlag(0);
        return renderNodePaintProperty;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);

        if (!renderNodeModifier_) {
            renderNodeModifier_ = AceType::MakeRefPtr<RenderNodeModifier>(drawCallback_);
        }
        auto paintMethod = AceType::MakeRefPtr<RenderNodePaintMethod>(renderNodeModifier_);
        return paintMethod;
    }

    void SetDrawCallback(std::function<void(DrawingContext& context)>&& drawCallback)
    {
        drawCallback_ = drawCallback;
        renderNodeModifier_ = AceType::MakeRefPtr<RenderNodeModifier>(drawCallback_);
    }

    void Invalidate()
    {
        CHECK_NULL_VOID(renderNodeModifier_);
        renderNodeModifier_->Modify();
    }

private:
    std::function<void(DrawingContext& context)> drawCallback_;
    RefPtr<RenderNodeModifier> renderNodeModifier_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_CUSTOM_FRAME_NODE_PATTERN_H
