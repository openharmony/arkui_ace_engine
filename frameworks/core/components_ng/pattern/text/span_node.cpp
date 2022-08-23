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

#include "core/components_ng/pattern/text/span_node.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<SpanNode> SpanNode::GetOrCreateSpanNode(int32_t nodeId)
{
    auto spanNode = ElementRegister::GetInstance()->GetSpecificItemById<SpanNode>(nodeId);
    if (spanNode) {
        return spanNode;
    }
    spanNode = MakeRefPtr<SpanNode>(nodeId);
    ElementRegister::GetInstance()->AddUINode(spanNode);
    return spanNode;
}

void SpanNode::MountToParagraph()
{
    auto parent = GetParent();
    while (parent) {
        auto spanNode = DynamicCast<SpanNode>(parent);
        if (spanNode) {
            spanNode->AddChildSpanItem(Claim(this));
            return;
        }
        auto textNode = DynamicCast<FrameNode>(parent);
        if (textNode) {
            auto textPattern = textNode->GetPattern<TextPattern>();
            if (textPattern) {
                textPattern->AddChildSpanItem(Claim(this));
                return;
            }
        }
        parent = parent->GetParent();
    }
    LOGE("fail to find Text or Parent Span");
}

void SpanItem::UpdateParagraph(RSParagraphBuilder* builder)
{
    CHECK_NULL_VOID(builder);
    if (fontStyle) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto themeManager = pipelineContext->GetThemeManager();
        TextStyle textStyle =
            CreateTextStyleUsingTheme(fontStyle, nullptr, themeManager ? themeManager->GetTheme<TextTheme>() : nullptr);
        builder->PushStyle(ToRSTextStyle(PipelineContext::GetCurrentContext(), textStyle));
    }
    auto displayText = content;
    auto textCase = fontStyle ? fontStyle->GetTextCase().value_or(TextCase::NORMAL) : TextCase::NORMAL;
    StringUtils::TransformStrCase(displayText, static_cast<int32_t>(textCase));
    builder->AddText(StringUtils::Str8ToStr16(displayText));
    for (const auto& child : children) {
        if (child) {
            child->UpdateParagraph(builder);
        }
    }
    if (fontStyle) {
        builder->Pop();
    }
}
} // namespace OHOS::Ace::NG