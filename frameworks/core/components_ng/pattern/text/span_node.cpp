/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paragraph.h"
#include "core/pipeline/pipeline_context.h"
#include "core/common/font_manager.h"

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

std::string SpanItem::GetFont() const
{
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("style", GetFontStyleInJson(fontStyle->GetItalicFontStyle()).c_str());
    jsonValue->Put("size", GetFontSizeInJson(fontStyle->GetFontSize()).c_str());
    jsonValue->Put("weight", GetFontWeightInJson(fontStyle->GetFontWeight()).c_str());
    jsonValue->Put("family", GetFontFamilyInJson(fontStyle->GetFontFamily()).c_str());
    return jsonValue->ToString();
}

void SpanItem::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("content", content.c_str());
    if (fontStyle) {
        json->Put("font", GetFont().c_str());
        json->Put("fontSize", GetFontSizeInJson(fontStyle->GetFontSize()).c_str());
        json->Put(
            "decoration", GetDeclaration(fontStyle->GetTextDecorationColor(), fontStyle->GetTextDecoration()).c_str());
        json->Put("letterSpacing", fontStyle->GetLetterSpacing().value_or(Dimension()).ToString().c_str());
        json->Put(
            "textCase", V2::ConvertWrapTextCaseToStirng(fontStyle->GetTextCase().value_or(TextCase::NORMAL)).c_str());
        json->Put("fontColor", fontStyle->GetForegroundColor()
            .value_or(fontStyle->GetTextColor().value_or(Color::BLACK)).ColorToString().c_str());
        json->Put("fontStyle", GetFontStyleInJson(fontStyle->GetItalicFontStyle()).c_str());
        json->Put("fontWeight", GetFontWeightInJson(fontStyle->GetFontWeight()).c_str());
        json->Put("fontFamily", GetFontFamilyInJson(fontStyle->GetFontFamily()).c_str());
    }
    if (textLineStyle) {
        json->Put("lineHeight", textLineStyle->GetLineHeight().value_or(Dimension()).ToString().c_str());
    }
}

SpanNode::~SpanNode()
{
    auto context = PipelineContext::GetCurrentContext();
    if (context) {
        context->RemoveFontNodeNG(AceType::WeakClaim(this));
        auto fontManager = context->GetFontManager();
        if (fontManager) {
            fontManager->UnRegisterCallbackNG(AceType::WeakClaim(this));
            fontManager->RemoveVariationNodeNG(AceType::WeakClaim(this));
        }
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
    LOGI("fail to find Text or Parent Span");
}

int32_t SpanItem::UpdateParagraph(
    const RefPtr<Paragraph>& builder, double /* width */, double /* height */, VerticalAlign /* verticalAlign */)
{
    CHECK_NULL_RETURN(builder, -1);
    if (fontStyle || textLineStyle) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, -1);
        TextStyle textStyle =
            CreateTextStyleUsingTheme(fontStyle, textLineStyle, pipelineContext->GetTheme<TextTheme>());
        if (NearZero(textStyle.GetFontSize().Value())) {
            return -1;
        }
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
    if (fontStyle || textLineStyle) {
        builder->PopStyle();
    }
    return -1;
}

int32_t ImageSpanItem::UpdateParagraph(
    const RefPtr<Paragraph>& builder, double width, double height, VerticalAlign verticalAlign)
{
    LOGD("ImageSpanItem::UpdateParagraph imageWidth = %{public}f, imageHeight = %{public}f verticalAlign = "
         "%{public}d",
        width, height, verticalAlign);
    CHECK_NULL_RETURN(builder, -1);
    PlaceholderRun run;
    run.width = width;
    run.height = height;
    switch (verticalAlign) {
        case VerticalAlign::TOP:
            run.alignment = PlaceholderAlignment::TOP;
            break;
        case VerticalAlign::CENTER:
            run.alignment = PlaceholderAlignment::MIDDLE;
            break;
        case VerticalAlign::BOTTOM:
        case VerticalAlign::NONE:
            run.alignment = PlaceholderAlignment::BOTTOM;
            break;
        case VerticalAlign::BASELINE:
            run.alignment = PlaceholderAlignment::ABOVEBASELINE;
            break;
        default:
            run.alignment = PlaceholderAlignment::BOTTOM;
    }
    builder->PushStyle(textStyle);
    LOGD("ImageSpan fontsize = %{public}f", textStyle.GetFontSize().Value());
    int32_t index = builder->AddPlaceholder(run);
    builder->PopStyle();
    return index;
}
} // namespace OHOS::Ace::NG
