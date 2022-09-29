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

#include "core/components_ng/pattern/text/span_view.h"

#include "base/geometry/dimension.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/span_node.h"

#define ACE_UPDATE_SPAN_PROPERTY(name, value)                                                                    \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode()); \
        CHECK_NULL_VOID(spanNode);                                                                               \
        spanNode->Update##name(value);                                                                           \
    } while (false)

namespace OHOS::Ace::NG {
void SpanView::Create(const std::string& content)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(nodeId);
    stack->Push(spanNode);

    ACE_UPDATE_SPAN_PROPERTY(Content, content);
}

void SpanView::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontSize, value);
}

void SpanView::SetTextColor(const Color& value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextColor, value);
}

void SpanView::SetItalicFontStyle(const Ace::FontStyle& value)
{
    ACE_UPDATE_SPAN_PROPERTY(ItalicFontStyle, value);
}

void SpanView::SetFontWeight(const Ace::FontWeight& value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontWeight, value);
}

void SpanView::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_SPAN_PROPERTY(FontFamily, value);
}

void SpanView::SetTextDecoration(const Ace::TextDecoration& value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecoration, value);
}

void SpanView::SetTextDecorationColor(const Color& value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextDecorationColor, value);
}

void SpanView::SetTextCase(const Ace::TextCase& value)
{
    ACE_UPDATE_SPAN_PROPERTY(TextCase, value);
}

void SpanView::SetOnClick(GestureEventFunc&& onClick)
{
    ACE_UPDATE_SPAN_PROPERTY(OnClickEvent, std::move(onClick));
}
} // namespace OHOS::Ace::NG
