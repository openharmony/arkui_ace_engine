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

#include "core/components_ng/pattern/text/span_model_ng.h"

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

#define ACE_UPDATE_SPAN_PROPERTY(name, value)                                                                    \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode()); \
        CHECK_NULL_VOID(spanNode);                                                                               \
        spanNode->Update##name(value);                                                                           \
    } while (false)

namespace OHOS::Ace::NG {
namespace {
FontWeight ConvertFontWeight(FontWeight fontWeight)
{
    FontWeight convertValue = fontWeight;
    switch (fontWeight) {
        case FontWeight::LIGHTER:
            convertValue = FontWeight::W100;
            break;
        case FontWeight::NORMAL:
        case FontWeight::REGULAR:
            convertValue = FontWeight::W400;
            break;
        case FontWeight::MEDIUM:
            convertValue = FontWeight::W500;
            break;
        case FontWeight::BOLD:
            convertValue = FontWeight::W700;
            break;
        case FontWeight::BOLDER:
            convertValue = FontWeight::W900;
            break;
        default:
            convertValue = fontWeight;
            break;
    }
    return convertValue;
}
} // namespace

void SpanModelNG::Create(const std::string& content)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(nodeId);
    stack->Push(spanNode);

    ACE_UPDATE_SPAN_PROPERTY(Content, content);
}

void SpanModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontSize, value);
}

void SpanModelNG::SetTextColor(const Color& value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextColor, value);
}

void SpanModelNG::SetItalicFontStyle(Ace::FontStyle value)
{
    ACE_UPDATE_SPAN_PROPERTY(ItalicFontStyle, value);
}

void SpanModelNG::SetFontWeight(Ace::FontWeight value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontWeight, ConvertFontWeight(value));
}

void SpanModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontFamily, value);
}

void SpanModelNG::SetTextDecoration(Ace::TextDecoration value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecoration, value);
}

void SpanModelNG::SetTextDecorationColor(const Color& value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecorationColor, value);
}

void SpanModelNG::SetTextCase(Ace::TextCase value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextCase, value);
}

void SpanModelNG::SetLetterSpacing(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(LetterSpacing, value);
}

void SpanModelNG::SetOnClick(std::function<void(const BaseEventInfo* info)>&& click)
{
    LOGE("no support OnClick");
}

} // namespace OHOS::Ace::NG
