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

#include <optional>

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paragraph.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
std::string GetDeclaration(const std::optional<Color>& color, const std::optional<TextDecoration>& textDecoration)
{
    auto jsonSpanDeclaration = JsonUtil::Create(true);
    jsonSpanDeclaration->Put(
        "type", V2::ConvertWrapTextDecorationToStirng(textDecoration.value_or(TextDecoration::NONE)).c_str());
    jsonSpanDeclaration->Put("color", (color.value_or(Color::BLACK).ColorToString()).c_str());
    return jsonSpanDeclaration->ToString();
}
} // namespace

void SpanItem::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("content", content.c_str());
    if (fontStyle) {
        json->Put("fontSize", fontStyle->GetFontSize().value_or(Dimension()).ToString().c_str());
        json->Put(
            "decoration", GetDeclaration(fontStyle->GetTextDecorationColor(), fontStyle->GetTextDecoration()).c_str());
        json->Put("letterSpacing", fontStyle->GetLetterSpacing().value_or(Dimension()).ToString().c_str());
        json->Put(
            "textCase", V2::ConvertWrapTextCaseToStirng(fontStyle->GetTextCase().value_or(TextCase::NORMAL)).c_str());
        json->Put("fontColor", fontStyle->GetForegroundColor()
            .value_or(fontStyle->GetTextColor().value_or(Color::BLACK)).ColorToString().c_str());
        json->Put("fontStyle",
            fontStyle->GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL
                                ? "FontStyle.Normal" : "FontStyle.Italic");
        json->Put("fontWeight",
            V2::ConvertWrapFontWeightToStirng(fontStyle->GetFontWeight().value_or(FontWeight::NORMAL)).c_str());
        std::vector<std::string> fontFamilyVector =
            fontStyle->GetFontFamily().value_or<std::vector<std::string>>({ "HarmonyOS Sans" });
        if (fontFamilyVector.empty()) {
            fontFamilyVector = std::vector<std::string>({ "HarmonyOS Sans" });
        }
        std::string fontFamily = fontFamilyVector.at(0);
        for (uint32_t i = 1; i < fontFamilyVector.size(); ++i) {
            fontFamily += ',' + fontFamilyVector.at(i);
        }
        json->Put("fontFamily", fontFamily.c_str());
    }
}

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

void SpanNode::RequestTextFlushDirty()
{
    auto parent = GetParent();
    while (parent) {
        auto textNode = DynamicCast<FrameNode>(parent);
        if (textNode) {
            textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto textPattern = textNode->GetPattern<TextPattern>();
            if (textPattern) {
                textPattern->OnModifyDone();
                return;
            }
        }
        parent = parent->GetParent();
    }
    LOGE("fail to find Text or Parent Span");
}

void SpanItem::UpdateParagraph(const RefPtr<Paragraph>& builder)
{
    CHECK_NULL_VOID(builder);
    if (fontStyle) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        TextStyle textStyle = CreateTextStyleUsingTheme(fontStyle, nullptr, pipelineContext->GetTheme<TextTheme>());
        builder->PushStyle(textStyle);
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
        builder->PopStyle();
    }
}
} // namespace OHOS::Ace::NG
