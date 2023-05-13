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
#include "core/components_ng/pattern/preview_mock/preview_mock_model_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_pattern.h"
#include "core/components_ng/pattern/preview_mock/preview_mock_model.h"

namespace OHOS::Ace::NG {
void PreviewMockModelNG::Create(const std::string& content)
{
    constexpr double DEFAULT_OFFSET = 25;
    constexpr double DEFAULT_HEIGHT = 30;
    constexpr Dimension DEFAULT_FONT_SIZE = 30.0_px;
    const Color bgColor = Color::FromString("#808080");
    const std::string presentationText("This component is not supported on PC preview.");
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(content, nodeId, []() { return AceType::MakeRefPtr<CustomPaintPattern>(); });
    CHECK_NULL_VOID(frameNode);
    stack->Push(frameNode);
    auto pattern = frameNode->GetPattern<CustomPaintPattern>();
    pattern->SetAntiAlias(true);
    pattern->UpdateFontSize(DEFAULT_FONT_SIZE);
    std::optional<double> maxWidth;
    pattern->FillText(presentationText, 0, DEFAULT_OFFSET, maxWidth);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        renderContext->UpdateBackgroundColor(bgColor);
    }
}
} // namespace OHOS::Ace::NG
