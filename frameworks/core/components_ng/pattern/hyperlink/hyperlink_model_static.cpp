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

#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_static.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_pattern.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> HyperlinkModelStatic::CreateFrameNode(int32_t nodeId)
{
    return FrameNode::GetOrCreateFrameNode(
        V2::HYPERLINK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<HyperlinkPattern>(); });
}

void HyperlinkModelStatic::SetColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value.has_value()) {
        HyperlinkModelNG::SetColor(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(HyperlinkLayoutProperty, TextColor, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(HyperlinkLayoutProperty, Color, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
    }
}

void HyperlinkModelStatic::SetTextStyle(
    FrameNode* frameNode, const std::string& address, const std::optional<std::string>& content)
{
    CHECK_NULL_VOID(frameNode);
    auto textLayoutProperty = frameNode->GetLayoutProperty<HyperlinkLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent((!content.has_value() || content.value().empty()) ? address : content.value());
    textLayoutProperty->UpdateAddress(address);

    auto context = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    auto textTheme = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    auto textStyle = textTheme->GetTextStyle();
    auto theme = PipelineContext::GetCurrentContextSafelyWithCheck()->GetTheme<HyperlinkTheme>();
    CHECK_NULL_VOID(theme);

    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateTextColor(theme->GetTextColor());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
    // textLayoutProperty->UpdateTextDecoration(theme->GetTextUnSelectedDecoration());
    textLayoutProperty->UpdateAdaptMinFontSize(10.0_vp);
    textLayoutProperty->UpdateAdaptMaxFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    frameNode->MarkModifyDone();
    frameNode->MarkDirtyNode();
}
} // namespace OHOS::Ace::NG
