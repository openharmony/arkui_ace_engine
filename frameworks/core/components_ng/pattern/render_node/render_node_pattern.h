/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RENDER_NODE_RENDER_NODE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RENDER_NODE_RENDER_NODE_PATTERN_H
#include <functional>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/render_node/render_node_layout_algorithm.h"
#include "core/components_ng/pattern/render_node/render_node_layout_property.h"
#include "core/components_ng/pattern/render_node/render_node_modifier.h"
#include "core/components_ng/pattern/render_node/render_node_paint_method.h"
#include "core/components_ng/pattern/render_node/render_node_paint_property.h"

namespace OHOS::Ace::NG {
using DrawCallback = std::function<void(DrawingContext)>;

class ACE_EXPORT RenderNodePattern : public Pattern {
    DECLARE_ACE_TYPE(RenderNodePattern, Pattern);

public:
    RenderNodePattern() = default;
    ~RenderNodePattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<RenderNodeLayoutAlgorithm>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<RenderNodeLayoutProperty>();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    void SetDrawCallback(std::function<void(DrawingContext& context)>&& drawCallback)
    {
        drawCallback_ = drawCallback;
        renderNodeModifier_ = AceType::MakeRefPtr<RenderNodeModifier>(drawCallback_);
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
        auto paintProperty = host->GetPaintProperty<RenderNodePaintProperty>();
        paintProperty->SetHost(host);
        auto context = host->GetRenderContext();
        if (context != nullptr) {
            context->SetNeedUseCmdlistDrawRegion(true);
        }

        if (!renderNodeModifier_) {
            renderNodeModifier_ = AceType::MakeRefPtr<RenderNodeModifier>(drawCallback_);
        }
        auto paintMethod = AceType::MakeRefPtr<RenderNodePaintMethod>(renderNodeModifier_);
        return paintMethod;
    }

    void Invalidate()
    {
        CHECK_NULL_VOID(renderNodeModifier_);
        renderNodeModifier_->Modify();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        Pattern::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        
        json->PutExtAttr("label", label_.c_str(), filter);
    }

    void SetLabel(const std::string& label)
    {
        label_ = label;
    }

private:
    void OnModifyDone() override;

    std::function<void(DrawingContext& context)> drawCallback_;
    RefPtr<RenderNodeModifier> renderNodeModifier_;
    std::string label_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RENDER_NODE_RENDER_NODE_PATTERN_H
