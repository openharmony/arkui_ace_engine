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

#define ACE_UPDATE_SPAN_PROPERTY(name, value, flag)                                                              \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode()); \
        CHECK_NULL_VOID(spanNode);                                                                               \
        spanNode->Update##name(value);                                                                           \
        spanNode->AddPropertyInfo(flag);                                                                         \
    } while (false)

namespace OHOS::Ace::NG {

void SpanModelNG::Create(const std::string& content)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(nodeId);
    stack->Push(spanNode);

    ACE_UPDATE_SPAN_PROPERTY(Content, content, PropertyInfo::NONE);
}

void SpanModelNG::SetFont(const Font& value)
{
    if (value.fontSize.has_value()) {
        SetFontSize(value.fontSize.value());
    }
    if (value.fontWeight.has_value()) {
        SetFontWeight(value.fontWeight.value());
    }
    if (!value.fontFamilies.empty()) {
        SetFontFamily(value.fontFamilies);
    }
    if (value.fontStyle.has_value()) {
        SetItalicFontStyle(value.fontStyle.value());
    }
}

void SpanModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontSize, value, PropertyInfo::FONTSIZE);
}

void SpanModelNG::SetTextColor(const Color& value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextColor, value, PropertyInfo::FONTCOLOR);
}

void SpanModelNG::SetItalicFontStyle(Ace::FontStyle value)
{
    ACE_UPDATE_SPAN_PROPERTY(ItalicFontStyle, value, PropertyInfo::FONTSTYLE);
}

void SpanModelNG::SetFontWeight(Ace::FontWeight value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontWeight, value, PropertyInfo::FONTWEIGHT);
}

void SpanModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontFamily, value, PropertyInfo::FONTFAMILY);
}

void SpanModelNG::SetTextDecoration(Ace::TextDecoration value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecoration, value, PropertyInfo::TEXTDECORATION);
}

void SpanModelNG::SetTextDecorationStyle(Ace::TextDecorationStyle value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecorationStyle, value, PropertyInfo::NONE);
}

void SpanModelNG::SetTextDecorationColor(const Color& value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecorationColor, value, PropertyInfo::NONE);
}

void SpanModelNG::SetTextCase(Ace::TextCase value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextCase, value, PropertyInfo::TEXTCASE);
}

void SpanModelNG::SetLetterSpacing(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(LetterSpacing, value, PropertyInfo::LETTERSPACE);
}

void SpanModelNG::SetLineHeight(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(LineHeight, value, PropertyInfo::LINEHEIGHT);
}

void SpanModelNG::SetOnClick(std::function<void(const BaseEventInfo* info)>&& click)
{
    auto clickFunc = [func = std::move(click)](GestureEvent& info) { func(&info); };
    ACE_UPDATE_SPAN_PROPERTY(OnClickEvent, std::move(clickFunc), PropertyInfo::NONE);
}

} // namespace OHOS::Ace::NG
