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

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_layout_algorithm.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_pattern.h"

namespace OHOS::Ace::NG {
std::optional<SizeF> CustomPaintLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    std::optional<SizeF> canvasSize = contentConstraint.maxSize;
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, canvasSize);
    auto pattern = host->GetPattern<CustomPaintPattern>();
    CHECK_NULL_RETURN(pattern, canvasSize);
    if (contentConstraint.selfIdealSize.IsValid()) {
        canvasSize = contentConstraint.selfIdealSize.ConvertToSizeT();
        pattern->SetCanvasSize(canvasSize);
        return canvasSize;
    }
    pattern->SetCanvasSize(canvasSize);
    return canvasSize;
}

void CustomPaintLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::Layout(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto contentRect = layoutWrapper->GetGeometryNode()->GetContentRect();
    if (contentRect.IsValid()) {
        renderContext->SetOverrideContentRect(contentRect);
    } else {
        contentRect.SetSize({ 0.0f, 0.0f });
        renderContext->SetOverrideContentRect(contentRect);
    }
}
} // namespace OHOS::Ace::NG
