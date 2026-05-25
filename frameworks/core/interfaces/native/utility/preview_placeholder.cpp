/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/utility/preview_placeholder.h"

#if defined(PREVIEW)
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/preview_mock/preview_mock_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#endif

namespace OHOS::Ace::NG {
#if defined(PREVIEW)
RefPtr<FrameNode> CreatePreviewPlaceholder(const std::string& tag, int32_t nodeId)
{
    constexpr Dimension DEFAULT_HEIGHT = Dimension(150.0, DimensionUnit::VP);
    constexpr Dimension DEFAULT_FONT_SIZE = Dimension(20.0, DimensionUnit::VP);
    const Color bgColor = Color::FromString("#808080");
    const std::string presentationText("Preview not available for this component.");
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        tag, nodeId, []() { return AceType::MakeRefPtr<PreviewMockPattern>(); });
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(presentationText);
    textLayoutProperty->UpdateFontSize(DEFAULT_FONT_SIZE);
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext) {
        renderContext->UpdateBackgroundColor(bgColor);
    }
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode), CalcLength(DEFAULT_HEIGHT));
    return frameNode;
}
#endif
} // namespace OHOS::Ace::NG
