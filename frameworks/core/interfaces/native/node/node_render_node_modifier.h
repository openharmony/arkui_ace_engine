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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_RENDER_NODE_MODIFIER_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_RENDER_NODE_MODIFIER_H

#include "core/components_ng/base/modifier.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG::NodeModifier {
    const ArkUINDKRenderNodeModifier* GetNDKRenderNodeModifier();

using DrawFunction = std::function<void(DrawingContext& context)>;
class RenderContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(RenderContentModifier, ContentModifier);
public:
    explicit RenderContentModifier(DrawFunction&& drawCallback) : drawCallback_(std::move(drawCallback))
    {
        renderFlag_ = AceType::MakeRefPtr<PropertyInt>(0);
        AttachProperty(renderFlag_);
    }

    ~RenderContentModifier() override = default;

    void onDraw(DrawingContext& context) override
    {
        if (drawCallback_) {
            drawCallback_(context);
        }
    }

    void setDrawFunction(DrawFunction&& drawCallback)
    {
        drawCallback_ = std::move(drawCallback);
    }

private:
    DrawFunction drawCallback_;
    RefPtr<PropertyInt> renderFlag_;
};

} // namespace OHOS::Ace::NG::NodeModifier

#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_RENDER_NODE_MODIFIER_H
