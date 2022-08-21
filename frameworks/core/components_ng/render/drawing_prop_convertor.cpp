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

#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace {

RSColor ToRSColor(const Color& color)
{
    return RSColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}

RSRect ToRSRect(const NG::RectF& rect)
{
    return RSRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
}

RSPoint ToRSPonit(const NG::PointF& point)
{
    return RSPoint(point.GetX(), point.GetY());
}

RSPen::CapStyle ToRSCapStyle(const LineCap& lineCap)
{
    RSPen::CapStyle capStyle;
    switch (lineCap) {
        case LineCap::SQUARE:
            capStyle = RSPen::CapStyle::SQUARE_CAP;
            break;
        case LineCap::ROUND:
            capStyle = RSPen::CapStyle::ROUND_CAP;
            break;
        default:
            capStyle = RSPen::CapStyle::FLAT_CAP;
            break;
    }
    return capStyle;
}

rosen::TextDirection ToRSTextDirection(const TextDirection& txtDir)
{
    rosen::TextDirection rsTxtDir = rosen::TextDirection::LTR;
    if (txtDir == TextDirection::LTR) {
        rsTxtDir = rosen::TextDirection::LTR;
    } else if (txtDir == TextDirection::RTL) {
        rsTxtDir = rosen::TextDirection::RTL;
    }
    return rsTxtDir;
}

rosen::TextAlign ToRSTextAlign(const TextAlign& align)
{
    // should keep enum same with rosen.
    return static_cast<rosen::TextAlign>(align);
}

rosen::WordBreakType ToRSWordBreakType(const WordBreak& wordBreak)
{
    // should keep enum same with rosen.
    return static_cast<rosen::WordBreakType>(wordBreak);
}

rosen::TextStyle ToRSTextStyle(const RefPtr<PipelineBase>& context, const TextStyle& textStyle)
{
    rosen::TextStyle rsTextStyle;
    rsTextStyle.color_ = ToRSColor(textStyle.GetTextColor());
    // TODO: convert decoration,fontFamily and other styles.

    // TODO: convert missing fontWeight and textBaseline
    rsTextStyle.fontWeight_ = static_cast<rosen::FontWeight>(textStyle.GetFontWeight());
    rsTextStyle.fontStyle_ = static_cast<rosen::FontStyle>(textStyle.GetFontStyle());
    rsTextStyle.textBaseline_ = static_cast<rosen::TextBaseline>(textStyle.GetTextBaseline());
    if (context) {
        rsTextStyle.fontSize_ = context->NormalizeToPx(textStyle.GetFontSize());
        if (textStyle.IsAllowScale() || textStyle.GetFontSize().Unit() == DimensionUnit::FP) {
            rsTextStyle.fontSize_ = context->NormalizeToPx(textStyle.GetFontSize() * context->GetFontScale());
        }
    } else {
        rsTextStyle.fontSize_ = textStyle.GetFontSize().Value();
    }
    if (context) {
        rsTextStyle.letterSpacing_ = context->NormalizeToPx(textStyle.GetLetterSpacing());
    }
    if (textStyle.GetWordSpacing().Unit() == DimensionUnit::PERCENT) {
        rsTextStyle.wordSpacing_ = textStyle.GetWordSpacing().Value() * rsTextStyle.fontSize_;
    } else {
        if (context) {
            rsTextStyle.wordSpacing_ = context->NormalizeToPx(textStyle.GetWordSpacing());
        } else {
            rsTextStyle.wordSpacing_ = textStyle.GetWordSpacing().Value();
        }
    }

    if (textStyle.GetLineHeight().Unit() == DimensionUnit::PERCENT) {
        rsTextStyle.hasHeightOverride_ = true;
        rsTextStyle.height_ = textStyle.GetLineHeight().Value();
    } else {
        double fontSize = rsTextStyle.fontSize_;
        double lineHeight = textStyle.GetLineHeight().Value();
        if (context) {
            lineHeight = context->NormalizeToPx(textStyle.GetLineHeight());
        }
        rsTextStyle.hasHeightOverride_ = textStyle.HasHeightOverride();
        if (!NearEqual(lineHeight, fontSize) && (lineHeight > 0.0) && (!NearZero(fontSize))) {
            rsTextStyle.height_ = lineHeight / fontSize;
        } else {
            LOGD("use default text style height value.");
            rsTextStyle.height_ = 1;
            static const int32_t BEGIN_VERSION = 6;
            auto isBeginVersion = context && context->GetMinPlatformVersion() >= BEGIN_VERSION;
            if (NearZero(lineHeight) || (!isBeginVersion && NearEqual(lineHeight, fontSize))) {
                rsTextStyle.hasHeightOverride_ = false;
            }
        }
    }
    return rsTextStyle;
}

} // namespace OHOS::Ace
