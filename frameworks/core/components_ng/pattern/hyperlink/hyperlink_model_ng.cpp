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

#include "core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_pattern.h"

namespace OHOS::Ace::NG {
void HyperlinkModelNG::Create(const std::string& address, const std::string& content)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto hyperlinkNode = FrameNode::GetOrCreateFrameNode(
        V2::HYPERLINK_ETS_TAG, nodeId, [address]() { return AceType::MakeRefPtr<HyperlinkPattern>(address); });

    stack->Push(hyperlinkNode);
    SetTextStyle(hyperlinkNode, content);
}

void HyperlinkModelNG::SetColor(const Color& value)
{
    LOGI("Hyperlink setColor.");
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextColor, value);
}

void HyperlinkModelNG::SetTextStyle(const RefPtr<FrameNode>& hyperlinkNode, const std::string& content)
{
    CHECK_NULL_VOID(hyperlinkNode);
    auto textLayoutProperty = hyperlinkNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto textStyle = PipelineBase::GetCurrentContext()->GetTheme<TextTheme>()->GetTextStyle();
    textLayoutProperty->UpdateContent(content);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
    textLayoutProperty->UpdateTextDecoration(TextDecoration::UNDERLINE);
    hyperlinkNode->MarkModifyDone();
    hyperlinkNode->MarkDirtyNode();
}
} // namespace OHOS::Ace::NG
