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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_SVG_PAINT_STATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_SVG_PAINT_STATE_H

#include "base/memory/ace_type.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "frameworks/core/components/common/properties/color.h"
#include "frameworks/core/components/common/properties/decoration.h"
#include "frameworks/core/components/common/properties/paint_state.h"
#include "frameworks/core/components/common/properties/text_style.h"

namespace OHOS::Ace {

const char ATTR_NAME_FILL[] = "fill";
const char ATTR_NAME_STROKE[] = "stroke";
const char ATTR_NAME_STROKE_WIDTH[] = "stroke-width";
const char ATTR_NAME_MITER_LIMIT[] = "stroke-miterlimit";
const char ATTR_NAME_STROKE_DASHOFFSET[] = "stroke-dashoffset";
const char ATTR_NAME_FONT_SIZE[] = "font-size";
const char ATTR_NAME_FILL_OPACITY[] = "fill-opacity";
const char ATTR_NAME_STROKE_OPACITY[] = "stroke-opacity";
const char ATTR_NAME_LETTER_SPACING[] = "letter-spacing";
const char ANIMATOR_TYPE_MOTION[] = "motion";

class FillState {
public:
    const Color& GetColor() const
    {
        return color_;
    }

    /**
     * set fill color
     * @param color
     * @param isSelf if false the color value inherited from the parent node, otherwise the value is setted by self
     */
    void SetColor(const Color& color, bool isSelf = true)
    {
        color_ = color;
        hasColor_ = isSelf;
    }

    const Gradient& GetGradient() const
    {
        return gradient_;
    }

    void SetGradient(const Gradient& gradient)
    {
        gradient_ = gradient;
    }

    void SetOpacity(double opacity, bool isSelf = true)
    {
        opacity_ = opacity;
        hasOpacity_ = isSelf;
    }

    double GetOpacity() const
    {
        return opacity_;
    }

    void Inherit(const FillState& parent)
    {
        if (!hasColor_) {
            color_ = parent.GetColor();
        }
        if (!hasOpacity_) {
            opacity_ = parent.GetOpacity();
        }
    }

    bool HasColor() const
    {
        return hasColor_;
    }

    bool HasOpacity() const
    {
        return hasOpacity_;
    }

protected:
    Color color_ = Color::BLACK;
    double opacity_ = 1.0;
    Gradient gradient_;
    bool hasColor_ = false;
    bool hasOpacity_ = false;
};

class StrokeState {
public:
    const Color& GetColor() const
    {
        return color_;
    }

    void SetColor(const Color& color, bool isSelf = true)
    {
        color_ = color;
        hasColor_ = isSelf;
    }

    void SetOpacity(double opacity, bool isSelf = true)
    {
        opacity_ = opacity;
        hasOpacity_ = isSelf;
    }

    double GetOpacity() const
    {
        return opacity_;
    }

    LineCapStyle GetLineCap() const
    {
        return lineCap_;
    }

    void SetLineCap(LineCapStyle lineCap, bool isSelf = true)
    {
        lineCap_ = lineCap;
        hasLineCap_ = isSelf;
    }

    LineJoinStyle GetLineJoin() const
    {
        return lineJoin_;
    }

    void SetLineJoin(LineJoinStyle lineJoin, bool isSelf = true)
    {
        lineJoin_ = lineJoin;
        hasLineJoin_ = isSelf;
    }

    const Dimension& GetLineWidth() const
    {
        return lineWidth_;
    }

    void SetLineWidth(Dimension lineWidth, bool isSelf = true)
    {
        lineWidth_ = lineWidth;
        hasLineWidth_ = isSelf;
    }

    double GetMiterLimit() const
    {
        return miterLimit_;
    }

    void SetMiterLimit(double miterLimit, bool isSelf = true)
    {
        miterLimit_ = miterLimit;
        hasMiterLimit_ = isSelf;
    }

    const LineDashParam& GetLineDash() const
    {
        return lineDash_;
    }

    void SetLineDash(const LineDashParam& lineDash, bool isSelf = true)
    {
        lineDash_ = lineDash;
        hasLineDash_ = isSelf;
    }

    void SetLineDashOffset(double offset, bool isSelf = true)
    {
        lineDash_.dashOffset = offset;
        hasDashOffset_ = isSelf;
    }

    void SetLineDash(const std::vector<double>& segments, bool isSelf = true)
    {
        lineDash_.lineDash = segments;
        hasLineDash_ = isSelf;
    }

    bool HasStroke() const
    {
        // The text outline is drawn only when stroke is set
        return color_ != Color::TRANSPARENT;
    }

    void Inherit(const StrokeState& strokeState)
    {
        if (!hasColor_) {
            color_ = strokeState.GetColor();
        }
        if (!hasOpacity_) {
            opacity_ = strokeState.GetOpacity();
        }
        if (!hasLineCap_) {
            lineCap_ = strokeState.GetLineCap();
        }
        if (!hasLineJoin_) {
            lineJoin_ = strokeState.GetLineJoin();
        }
        if (!hasLineWidth_) {
            lineWidth_ = strokeState.GetLineWidth();
        }
        if (!hasMiterLimit_) {
            miterLimit_ = strokeState.GetMiterLimit();
        }
        if (!hasLineDash_) {
            lineDash_.lineDash = strokeState.GetLineDash().lineDash;
        }
        if (!hasDashOffset_) {
            lineDash_.dashOffset = strokeState.GetLineDash().dashOffset;
        }
    }

    bool HasColor() const
    {
        return hasColor_;
    }

    bool HasOpacity() const
    {
        return hasOpacity_;
    }

    bool HasLineWidth() const
    {
        return hasLineWidth_;
    }

    bool HasMiterLimit() const
    {
        return hasMiterLimit_;
    }

    bool HasDashOffset() const
    {
        return hasDashOffset_;
    }

private:
    Color color_ = Color::TRANSPARENT;
    double opacity_ = 1.0;
    LineCapStyle lineCap_ = LineCapStyle::BUTT;
    LineJoinStyle lineJoin_ = LineJoinStyle::MITER;
    Dimension lineWidth_ = Dimension(1.0);
    double miterLimit_ = 4.0;
    LineDashParam lineDash_;
    bool hasColor_ = false;
    bool hasOpacity_ = false;
    bool hasLineCap_ = false;
    bool hasLineJoin_ = false;
    bool hasLineWidth_ = false;
    bool hasMiterLimit_ = false;
    bool hasLineDash_ = false;
    bool hasDashOffset_ = false;
};

class SvgTextStyle {
public:
    void SetFontFamilies(const std::vector<std::string>& fontFamilies, bool isSelf = true)
    {
        hasFontFamilies_ = isSelf;
        textStyle_.SetFontFamilies(fontFamilies);
    }

    const std::vector<std::string>& GetFontFamilies() const
    {
        return textStyle_.GetFontFamilies();
    }

    void SetFontSize(const Dimension& fontSize, bool isSelf = true)
    {
        textStyle_.SetFontSize(fontSize);
        hasFontSize_ = isSelf;
    }

    const Dimension& GetFontSize() const
    {
        return textStyle_.GetFontSize();
    }

    void SetFontStyle(FontStyle fontStyle, bool isSelf = true)
    {
        textStyle_.SetFontStyle(fontStyle);
        hasFontStyle_ = isSelf;
    }

    FontStyle GetFontStyle() const
    {
        return textStyle_.GetFontStyle();
    }

    void SetFontWeight(FontWeight fontWeight, bool isSelf = true)
    {
        textStyle_.SetFontWeight(fontWeight);
        hasFontWeight_ = isSelf;
    }

    FontWeight GetFontWeight() const
    {
        return textStyle_.GetFontWeight();
    }

    void SetLetterSpacing(double letterSpacing, bool isSelf = true)
    {
        textStyle_.SetLetterSpacing(letterSpacing);
        hasLetterSpacing_ = isSelf;
    }

    double GetLetterSpacing() const
    {
        return textStyle_.GetLetterSpacing();
    }

    void SetTextDecoration(TextDecoration textDecoration, bool isSelf = true)
    {
        textStyle_.SetTextDecoration(textDecoration);
        hasTextDecoration_ = isSelf;
    }

    TextDecoration GetTextDecoration() const
    {
        return textStyle_.GetTextDecoration();
    }

    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }

    void Inherit(const SvgTextStyle& parent)
    {
        if (!hasFontFamilies_) {
            textStyle_.SetFontFamilies(parent.GetFontFamilies());
        }
        if (!hasFontSize_) {
            textStyle_.SetFontSize(parent.GetFontSize());
        }
        if (!hasFontStyle_) {
            textStyle_.SetFontStyle(parent.GetFontStyle());
        }
        if (!hasFontWeight_) {
            textStyle_.SetFontWeight(parent.GetFontWeight());
        }
        if (!hasLetterSpacing_) {
            textStyle_.SetLetterSpacing(parent.GetLetterSpacing());
        }
        if (!hasTextDecoration_) {
            textStyle_.SetTextDecoration(parent.GetTextDecoration());
        }
    }

    bool HasLetterSpacing() const
    {
        return hasLetterSpacing_;
    }

    bool HasFontSize() const
    {
        return hasFontSize_;
    }

private:
    TextStyle textStyle_;
    bool hasFontFamilies_ = false;
    bool hasFontSize_ = false;
    bool hasFontStyle_ = false;
    bool hasFontWeight_ = false;
    bool hasLetterSpacing_ = false;
    bool hasTextDecoration_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_SVG_PAINT_STATE_H
