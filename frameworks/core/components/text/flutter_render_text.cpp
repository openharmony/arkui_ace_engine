/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/text/flutter_render_text.h"

#include <cmath>

#include "flutter/lib/ui/text/font_collection.h"
#include "flutter/lib/ui/ui_dart_state.h"
#include "flutter/third_party/icu/source/common/unicode/uchar.h"
#include "flutter/third_party/txt/src/txt/paragraph_txt.h"

#include "base/geometry/dimension.h"
#include "base/i18n/localization.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/common/font_manager.h"
#include "core/components/calendar/flutter_render_calendar.h"
#include "core/components/font/constants_converter.h"
#include "core/components/font/flutter_font_collection.h"
#include "core/components/text_span/flutter_render_text_span.h"
#include "core/pipeline/base/flutter_render_context.h"
#include "core/pipeline/base/scoped_canvas_state.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {
namespace {

const std::u16string ELLIPSIS = u"\u2026";
constexpr Dimension ADAPT_UNIT = 1.0_fp;
const uint32_t ELLIPSIS_DEFAULT_MAX_LINES = 1;

} // namespace

double FlutterRenderText::GetBaselineDistance(TextBaseline textBaseline)
{
    if (textBaseline == TextBaseline::IDEOGRAPHIC) {
        return paragraph_->GetIdeographicBaseline();
    }
    return paragraph_->GetAlphabeticBaseline();
}

RefPtr<RenderNode> RenderText::Create()
{
    return AceType::MakeRefPtr<FlutterRenderText>();
}

void FlutterRenderText::Paint(RenderContext& context, const Offset& offset)
{
    if (!NeedPaint()) {
        return;
    }

    if (needMeasure_) {
        LOGW("Text can not paint before measure.");
        return;
    }
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas || !paragraph_) {
        LOGE("Paint canvas or paragraph is null");
        return;
    }
    if (textStyle_.GetTextOverflow() == TextOverflow::CLIP) {
        const auto& clipRect = Rect(offset, GetLayoutSize());
        canvas->clipRect(clipRect.Left(), clipRect.Top(), clipRect.Right(), clipRect.Bottom(), SkClipOp::kIntersect);
    }
    auto textRealWidth = paragraph_->GetMaxWidth();
    switch (textStyle_.GetTextAlign()) {
        case TextAlign::LEFT:
        case TextAlign::START:
            paragraph_->Paint(canvas->canvas(), offset.GetX(), offset.GetY());
            break;
        case TextAlign::RIGHT:
        case TextAlign::END:
            paragraph_->Paint(
                canvas->canvas(), offset.GetX() - (textRealWidth - GetLayoutSize().Width()), offset.GetY());
            break;
        case TextAlign::CENTER:
            paragraph_->Paint(canvas->canvas(), offset.GetX() - ((textRealWidth - GetLayoutSize().Width()) / 2.0),
                offset.GetY());
            break;
        case TextAlign::JUSTIFY:
            paragraph_->Paint(canvas->canvas(), offset.GetX(), offset.GetY());
            break;
        default:
            paragraph_->Paint(canvas->canvas(), offset.GetX(), offset.GetY());
    }
}

bool FlutterRenderText::NeedPaint()
{
    // If font is custom font, paint text until font is ready.
    auto pipelineContext = context_.Upgrade();
    if (pipelineContext && pipelineContext->GetFontManager()) {
        auto fontNames = pipelineContext->GetFontManager()->GetFontNames();
        for (const auto& familyName : textStyle_.GetFontFamilies()) {
            if (std::find(std::begin(fontNames), std::end(fontNames), familyName) != std::end(fontNames) &&
                !isCallbackCalled_) {
                return false;
            }
        }
        for (const auto& child : GetChildren()) {
            auto span = AceType::DynamicCast<RenderTextSpan>(child);
            if (!span) {
                continue;
            }
            for (const auto& familyName : span->GetSpanStyle().GetFontFamilies()) {
                if (std::find(std::begin(fontNames), std::end(fontNames), familyName) != std::end(fontNames) &&
                    !span->IsCallbackCalled()) {
                    return false;
                }
            }
        }
    }
    return true;
}

Size FlutterRenderText::Measure()
{
    if (CheckMeasureFlag()) {
        return GetSize();
    }
    lastLayoutMaxWidth_ = GetLayoutParam().GetMaxSize().Width();
    lastLayoutMinWidth_ = GetLayoutParam().GetMinSize().Width();
    if (!textStyle_.GetAdaptTextSize()) {
        if (!UpdateParagraph()) {
            LOGE("fail to initialize text paragraph");
            return Size();
        }
        paragraph_->Layout(lastLayoutMaxWidth_);
    } else {
        if (!AdaptTextSize(lastLayoutMaxWidth_)) {
            LOGE("fail to initialize text paragraph in adapt text size step");
            return Size();
        }
    }
    needMeasure_ = false;
    // If you need to lay out the text according to the maximum layout width given by the parent, use it.
    if (isMaxWidthLayout_) {
        paragraphNewWidth_ = GetLayoutParam().GetMaxSize().Width();
        return GetSize();
    }
    // The reason for the second layout is because the TextAlign property needs the width of the layout,
    // and the width of the second layout is used as the width of the TextAlign layout.
    if (!NearEqual(lastLayoutMinWidth_, lastLayoutMaxWidth_)) {
        paragraphNewWidth_ = std::clamp(paragraph_->GetMaxIntrinsicWidth(), lastLayoutMinWidth_, lastLayoutMaxWidth_);
        if (!NearEqual(paragraphNewWidth_, paragraph_->GetMaxWidth())) {
            paragraph_->Layout(std::ceil(paragraphNewWidth_));
        }
    }
    return GetSize();
}

bool FlutterRenderText::CheckMeasureFlag()
{
    if (isCallbackCalled_) {
        needMeasure_ = true;
    }
    for (const auto& child : GetChildren()) {
        auto span = AceType::DynamicCast<RenderTextSpan>(child);
        if (span && (span->IsCallbackCalled() || span->NeedLayout())) {
            paragraph_.reset();
            needMeasure_ = true;
            break;
        }
    }

    double paragraphMaxWidth = GetLayoutParam().GetMaxSize().Width();
    double paragraphMinWidth = GetLayoutParam().GetMinSize().Width();

    if (!needMeasure_) {
        bool constrainsAffect = true;
        auto layoutWidth = GetSize().Width();
        if (NearEqual(paragraphMaxWidth, lastLayoutMaxWidth_) && NearEqual(paragraphMinWidth, lastLayoutMinWidth_)) {
            // Constrains not changed.
            constrainsAffect = false;
        } else if (GreatOrEqual(layoutWidth, paragraphMinWidth) && LessOrEqual(layoutWidth, paragraphMaxWidth) &&
                   (lastLayoutMaxWidth_ - layoutWidth > 1.0)) {
            // Constrains changed but has no effect. For example, text width is 100 when constrains [0, 200].
            // When constrains changed to [100, 300], there's no need to do layout.
            // An exception is that given [0, 100], resulting in layout 100. We assume the actual layout size is more
            // than 100 due to soft-wrap.
            if (!textStyle_.GetAdaptTextSize()) {
                constrainsAffect = false;
            }
        }
        if (!constrainsAffect) {
            LOGD("Text content and constrains not affect, no need measure.");
            return true;
        }
    }
    return false;
}

bool FlutterRenderText::AdaptTextSize(double paragraphMaxWidth)
{
    const auto& preferTextSizeGroups = textStyle_.GetPreferTextSizeGroups();
    if (!preferTextSizeGroups.empty()) {
        return AdaptPreferTextSizeGroup(paragraphMaxWidth);
    }
    const auto& preferFontSizes = textStyle_.GetPreferFontSizes();
    if (!preferFontSizes.empty()) {
        return AdaptPreferTextSize(paragraphMaxWidth);
    }
    return AdaptMinTextSize(paragraphMaxWidth);
}

bool FlutterRenderText::AdaptMinTextSize(double paragraphMaxWidth)
{
    double maxFontSize = NormalizeToPx(textStyle_.GetAdaptMaxFontSize());
    double minFontSize = NormalizeToPx(textStyle_.GetAdaptMinFontSize());
    if (LessNotEqual(maxFontSize, minFontSize) || LessOrEqual(textStyle_.GetAdaptMinFontSize().Value(), 0.0)) {
        if (!UpdateParagraph()) {
            LOGE("fail to initialize text paragraph when adapt min text size.");
            return false;
        }
        paragraph_->Layout(lastLayoutMaxWidth_);
        return true;
    }
    Dimension step = ADAPT_UNIT;
    if (GreatNotEqual(textStyle_.GetAdaptFontSizeStep().Value(), 0.0)) {
        step = textStyle_.GetAdaptFontSizeStep();
    }
    double stepSize = NormalizeToPx(step);
    while (GreatOrEqual(maxFontSize, minFontSize)) {
        textStyle_.SetFontSize(Dimension(maxFontSize));
        if (!UpdateParagraphAndLayout(paragraphMaxWidth)) {
            return false;
        }
        if (!DidExceedMaxLines()) {
            break;
        }
        maxFontSize -= stepSize;
    }
    return true;
}

bool FlutterRenderText::AdaptPreferTextSize(double paragraphMaxWidth)
{
    // Use preferFontSizes to adapt lines.
    const auto& preferFontSizes = textStyle_.GetPreferFontSizes();
    for (const auto& fontSize : preferFontSizes) {
        textStyle_.SetFontSize(fontSize);
        if (!UpdateParagraphAndLayout(paragraphMaxWidth)) {
            return false;
        }
        if (!DidExceedMaxLines()) {
            break;
        }
    }
    return true;
}

bool FlutterRenderText::AdaptPreferTextSizeGroup(double paragraphMaxWidth)
{
    // Use preferTextSizeGroup.
    const auto& preferTextSizeGroups = textStyle_.GetPreferTextSizeGroups();
    for (const auto& preferTextSizeGroup : preferTextSizeGroups) {
        textStyle_.SetFontSize(preferTextSizeGroup.fontSize);
        textStyle_.SetMaxLines(preferTextSizeGroup.maxLines);
        textStyle_.SetTextOverflow(preferTextSizeGroup.textOverflow);
        if (!UpdateParagraphAndLayout(paragraphMaxWidth)) {
            return false;
        }
        if ((preferTextSizeGroup.textOverflow == TextOverflow::NONE) || (!DidExceedMaxLines())) {
            break;
        }
    }
    return true;
}

bool FlutterRenderText::UpdateParagraphAndLayout(double paragraphMaxWidth)
{
    if (!UpdateParagraph()) {
        return false;
    }
    if (paragraph_) {
        paragraph_->Layout(paragraphMaxWidth);
    }
    return true;
}

uint32_t FlutterRenderText::GetTextLines()
{
    uint32_t textLines = 0;
    auto paragraphTxt = static_cast<txt::ParagraphTxt*>(paragraph_.get());
    if (paragraphTxt != nullptr) {
        textLines = paragraphTxt->GetLineCount();
    }
    return textLines;
}

Size FlutterRenderText::GetSize()
{
    double height = paragraph_ ? paragraph_->GetHeight() : 0.0;
    return Size(isMaxWidthLayout_ ? paragraphNewWidth_ : std::ceil(paragraphNewWidth_),
        std::min(height, GetLayoutParam().GetMaxSize().Height()));
}

bool FlutterRenderText::UpdateParagraph()
{
    using namespace Constants;

    txt::ParagraphStyle style;

    const auto& textAlign = textStyle_.GetTextAlign();
    if (textAlign == TextAlign::START || textAlign == TextAlign::END) {
        std::string data = textData_;
        if (!GetChildren().empty()) {
            for (const auto& child : GetChildren()) {
                auto span = DynamicCast<RenderTextSpan>(child);
                if (span && !span->GetSpanData().empty()) {
                    data = span->GetSpanData();
                    break;
                }
            }
        }
        auto showingTextForWString = StringUtils::ToWstring(data);
        for (const auto& charOfShowingText : showingTextForWString) {
            if (u_charDirection(charOfShowingText) == UCharDirection::U_LEFT_TO_RIGHT) {
                textDirection_ = TextDirection::LTR;
                break;
            } else if (u_charDirection(charOfShowingText) == UCharDirection::U_RIGHT_TO_LEFT) {
                textDirection_ = TextDirection::RTL;
                break;
            } else if (u_charDirection(charOfShowingText) == UCharDirection::U_RIGHT_TO_LEFT_ARABIC) {
                textDirection_ = TextDirection::RTL;
                break;
            }
        }
    }
    style.text_direction = ConvertTxtTextDirection(textDirection_);
    style.text_align = ConvertTxtTextAlign(textAlign);
    style.max_lines = textStyle_.GetMaxLines();
    style.locale = Localization::GetInstance()->GetFontLocale();
    if (textStyle_.GetTextOverflow() == TextOverflow::ELLIPSIS) {
        if (textStyle_.GetMaxLines() == UINT32_MAX) {
            style.max_lines = ELLIPSIS_DEFAULT_MAX_LINES;
        }
        style.ellipsis = ELLIPSIS;
    }
    style.word_break_type = static_cast<minikin::WordBreakType>(textStyle_.GetWordBreak());

    std::unique_ptr<txt::ParagraphBuilder> builder;
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("UpdateParagraph: fontCollection is null");
        return false;
    }
    builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);

    txt::TextStyle txtStyle;
    ConvertTxtStyle(textStyle_, context_, txtStyle);
    builder->PushStyle(txtStyle);
    const auto& children = GetChildren();
    if (!children.empty()) {
        for (const auto& child : children) {
            auto textSpan = AceType::DynamicCast<FlutterRenderTextSpan>(child);
            if (textSpan) {
                textSpan->UpdateTextContent(*builder);
            }
        }
    } else {
        builder->AddText(StringUtils::Str8ToStr16(textData_));
    }
    paragraph_ = builder->Build();
    return true;
}

double FlutterRenderText::GetTextWidth()
{
    if (paragraph_) {
        return paragraph_->GetMaxIntrinsicWidth();
    }
    return 0;
}

bool FlutterRenderText::DidExceedMaxLines()
{
    auto* paragraphTxt = static_cast<txt::ParagraphTxt*>(paragraph_.get());
    if (paragraphTxt != nullptr) {
        return paragraphTxt->DidExceedMaxLines();
    }
    return false;
}

bool FlutterRenderText::MaybeRelease()
{
    auto context = GetContext().Upgrade();
    if (context && context->GetRenderFactory()->GetRenderTextFactory()->Recycle(this)) {
        ClearRenderObject();
        return false;
    }
    return true;
}

void FlutterRenderText::ClearRenderObject()
{
    RenderText::ClearRenderObject();
    LOGI("FlutterRenderText ClearRenderObject");
    paragraph_ = nullptr;
    paragraphNewWidth_ = 0.0;
    lastLayoutMaxWidth_ = 0.0;
    lastLayoutMinWidth_ = 0.0;
}

} // namespace OHOS::Ace
