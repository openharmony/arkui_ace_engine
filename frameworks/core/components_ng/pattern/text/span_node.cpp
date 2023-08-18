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
    LOGD("fail to find Text or Parent Span");
}

int32_t SpanItem::UpdateParagraph(
    const RefPtr<Paragraph>& builder, double /* width */, double /* height */, VerticalAlign /* verticalAlign */)
{
    CHECK_NULL_RETURN(builder, -1);
    std::optional<TextStyle> textStyle;
    if (fontStyle || textLineStyle) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, -1);
        TextStyle themeTextStyle =
            CreateTextStyleUsingTheme(fontStyle, textLineStyle, pipelineContext->GetTheme<TextTheme>());
        if (NearZero(themeTextStyle.GetFontSize().Value())) {
            return -1;
        }
        textStyle = themeTextStyle;
        builder->PushStyle(themeTextStyle);
    }
    UpdateTextStyle(builder, textStyle);
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

void SpanItem::UpdateTextStyle(const RefPtr<Paragraph>& builder, const std::optional<TextStyle>& textStyle)
{
    auto textCase = fontStyle ? fontStyle->GetTextCase().value_or(TextCase::NORMAL) : TextCase::NORMAL;
    auto updateTextAction = [builder, textCase](const std::string& content, const std::optional<TextStyle>& textStyle) {
        if (content.empty()) {
            return;
        }
        auto displayText = content;
        StringUtils::TransformStrCase(displayText, static_cast<int32_t>(textCase));
        if (textStyle.has_value()) {
            builder->PushStyle(textStyle.value());
        }
        builder->AddText(StringUtils::Str8ToStr16(displayText));
        if (textStyle.has_value()) {
            builder->PopStyle();
        }
    };
#ifdef ENABLE_DRAG_FRAMEWORK
    if (!IsDragging()) {
#endif // ENABLE_DRAG_FRAMEWORK
        updateTextAction(content, textStyle);
#ifdef ENABLE_DRAG_FRAMEWORK
    } else {
        if (content.empty()) {
            return;
        }
        auto displayContent = StringUtils::Str8ToStr16(content);
        auto contentLength = static_cast<int32_t>(displayContent.length());
        auto beforeSelectedText = displayContent.substr(0, selectedStart);
        updateTextAction(StringUtils::Str16ToStr8(beforeSelectedText), textStyle);

        if (selectedStart < contentLength) {
            auto pipelineContext = PipelineContext::GetCurrentContext();
            TextStyle normalStyle =
                !pipelineContext ? TextStyle()
                                 : CreateTextStyleUsingTheme(nullptr, nullptr, pipelineContext->GetTheme<TextTheme>());
            TextStyle selectedTextStyle = textStyle.value_or(normalStyle);
            Color color = selectedTextStyle.GetTextColor().ChangeAlpha(DRAGGED_TEXT_OPACITY);
            selectedTextStyle.SetTextColor(color);
            auto selectedText = displayContent.substr(selectedStart, selectedEnd - selectedStart);
            updateTextAction(StringUtils::Str16ToStr8(selectedText), selectedTextStyle);
        }

        if (selectedEnd < contentLength) {
            auto afterSelectedText = displayContent.substr(selectedEnd);
            updateTextAction(StringUtils::Str16ToStr8(afterSelectedText), textStyle);
        }
    }
#endif // ENABLE_DRAG_FRAMEWORK
}

#ifdef ENABLE_DRAG_FRAMEWORK
void SpanItem::StartDrag(int32_t start, int32_t end)
{
    selectedStart = std::max(0, start);
    int contentLen = content.size();
    selectedEnd = std::min(contentLen, end);
}

void SpanItem::EndDrag()
{
    selectedStart = -1;
    selectedEnd = -1;
}

bool SpanItem::IsDragging()
{
    return selectedStart >= 0 && selectedEnd >= 0;
}
#endif // ENABLE_DRAG_FRAMEWORK

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
    // ImageSpan should ignore decoration styles
    textStyle.SetTextDecoration(TextDecoration::NONE);
    builder->PushStyle(textStyle);
    LOGD("ImageSpan fontsize = %{public}f", textStyle.GetFontSize().Value());
    int32_t index = builder->AddPlaceholder(run);
    builder->PopStyle();
    return index;
}
} // namespace OHOS::Ace::NG
