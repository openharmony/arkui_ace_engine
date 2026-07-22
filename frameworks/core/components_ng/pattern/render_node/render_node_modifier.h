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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RENDER_HODE_RENDER_NODE_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RENDER_HODE_RENDER_NODE_MODIFIER_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {
class RenderNodeModifier : public ContentModifier {
    DECLARE_ACE_TYPE(RenderNodeModifier, ContentModifier);

public:
    explicit RenderNodeModifier(const std::function<void(DrawingContext& context)>& drawCallback)
        : drawCallback_(drawCallback)
    {
        renderNodeFlag_ = AceType::MakeRefPtr<PropertyInt>(0);
        AttachProperty(renderNodeFlag_);
    };

    ~RenderNodeModifier() override = default;

    void onDraw(DrawingContext& context) override
    {
        if (drawCallback_) {
            drawCallback_(context);
        }
    }

    void SetRenderNodeFlag(int32_t renderNodeFlag)
    {
        renderNodeFlag_->Set(renderNodeFlag);
    }

    void Modify()
    {
        renderNodeFlag_->Set(renderNodeFlag_->Get() + 1);
    }

private:
    std::function<void(DrawingContext& context)> drawCallback_;
    RefPtr<PropertyInt> renderNodeFlag_;
};
} // namespace OHOS::Ace::NG

#endif
