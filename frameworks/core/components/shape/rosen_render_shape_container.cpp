/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/core/components/shape/rosen_render_shape_container.h"

#include "render_service_client/core/ui/rs_node.h"

#include "frameworks/core/components/transform/rosen_render_transform.h"

namespace OHOS::Ace {

void RosenRenderShapeContainer::PerformLayout()
{
    RenderShapeContainer::PerformLayout();

    auto node = GetRSNode();
    if (node == nullptr) {
        return;
    }
    node->SetClipToFrame(true);

    double viewBoxWidth = NormalizePercentToPx(viewBox_.Width(), false);
    double viewBoxHeight = NormalizePercentToPx(viewBox_.Height(), true);
    double viewBoxLeft = NormalizePercentToPx(viewBox_.Left(), false);
    double viewBoxTop = NormalizePercentToPx(viewBox_.Top(), true);
    if (!GetLayoutSize().IsInfinite() && GreatNotEqual(viewBoxWidth, 0.0) && GreatNotEqual(viewBoxHeight, 0.0)) {
        double scale = std::min(GetLayoutSize().Width() / viewBoxWidth, GetLayoutSize().Height() / viewBoxHeight);
        double tx = GetLayoutSize().Width() * 0.5 - (viewBoxWidth * 0.5 + viewBoxLeft) * scale;
        double ty = GetLayoutSize().Height() * 0.5 - (viewBoxHeight * 0.5 + viewBoxTop) * scale;
        for (const auto& child : GetChildren()) {
            auto rsNode = child->GetRSNode();
            if (!rsNode) {
                continue;
            }
            rsNode->SetPivot(0.0f, 0.0f);
            rsNode->SetScale(scale);
            rsNode->SetTranslate({tx, ty});
        }
    }
}

} // namespace OHOS::Ace
