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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_NODE_RENDER_NODE_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_NODE_RENDER_NODE_PAINT_METHOD_H

#include <cstdint>
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/pattern/render_node/render_node_modifier.h"
#include "core/components_ng/pattern/render_node/render_node_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {
class RenderNodePaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(RenderNodePaintMethod, NodePaintMethod)
public:
    explicit RenderNodePaintMethod(const RefPtr<RenderNodeModifier>& renderNodeModifier)
        : renderNodeModifier_(renderNodeModifier)
    {}

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(renderNodeModifier_, nullptr);
        return renderNodeModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        auto paintProperty = DynamicCast<RenderNodePaintProperty>(paintWrapper->GetPaintProperty());
        CHECK_NULL_VOID(paintProperty);
        renderNodeFlag_ = paintProperty->GetRenderNodeFlag().value_or(renderNodeFlag_);
        renderNodeModifier_->SetRenderNodeFlag(renderNodeFlag_);
    }

private:
    RefPtr<RenderNodeModifier> renderNodeModifier_;
    int32_t renderNodeFlag_ = 0;
};
} // namespace OHOS::Ace::NG

#endif
