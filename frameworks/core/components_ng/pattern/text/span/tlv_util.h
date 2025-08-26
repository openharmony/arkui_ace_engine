/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_TLV_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_TLV_UTIL_H

#include <string>
#include <sstream>
#include <utility>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/image/pixel_map.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_ng/pattern/text/text_styles.h"

namespace OHOS::Ace {

constexpr Dimension ILLEGAL_DIMENSION_VALUE = Dimension(-100.0);

constexpr uint8_t TLV_VARINT_BITS = 7;
constexpr uint8_t TLV_VARINT_MASK = 0x7F;
constexpr uint8_t TLV_VARINT_MORE = 0x80;
constexpr uint8_t TLV_END = 0x00;
constexpr uint8_t TLV_SPAN_STRING_CONTENT = 0x01;
constexpr uint8_t TLV_SPAN_STRING_SPANS = 0x02;

constexpr uint8_t TLV_STRING_TAG = 0x20;
constexpr uint8_t TLV_DOUBLE_TAG = 0x21;
constexpr uint8_t TLV_COLOR_TAG = 0x22;
constexpr uint8_t TLV_TEXTSHADOW_TAG = 0x23;
constexpr uint8_t TLV_DIMENSION_TAG = 0x24;
constexpr uint8_t TLV_FONTFAMILIES_TAG = 0x25;

constexpr uint8_t TLV_TEXTSHADOWS_TAG = 0x26;
constexpr uint8_t TLV_BORDERRADIUS_TAG = 0x27;
constexpr uint8_t TLV_PIXEL_MAP_TAG = 0x28;
constexpr uint8_t TLV_FONTFEATURE_TAG = 0x29;
constexpr uint8_t TLV_CALCDIMENSION_TAG = 0x2A;
constexpr uint8_t TLV_CALCLENGTH_TAG = 0x2B;

constexpr uint8_t TLV_VERTICALALIGN_TAG = 0x2C;
constexpr uint8_t TLV_IMAGEFIT_TAG = 0x2D;
constexpr uint8_t TLV_FONTWEIGHT_TAG = 0x2E;
constexpr uint8_t TLV_ITALICSFONTSTYLE_TAG = 0x2F;
constexpr uint8_t TLV_TEXTDECORATION_TAG = 0x30;
constexpr uint8_t TLV_TEXTDECORATIONSTYLE_TAG = 0x31;
constexpr uint8_t TLV_TEXTCASE_TAG = 0x32;
constexpr uint8_t TLV_TEXTBASELINE_TAG = 0x33;
constexpr uint8_t TLV_TEXTOVERFLOW_TAG = 0x34;
constexpr uint8_t TLV_TEXTALIGN_TAG = 0x35;
constexpr uint8_t TLV_TEXTHEIGHTADAPTIVEPOLICY_TAG = 0x36;
constexpr uint8_t TLV_WORDBREAK_TAG = 0x37;
constexpr uint8_t TLV_LINEBREAKSTRATEGY_TAG = 0x38;
constexpr uint8_t TLV_ELLIPSISMODE_TAG = 0x39;

constexpr uint8_t TLV_IMAGESPANATTRIBUTE_TAG = 0x3A;
constexpr uint8_t TLV_IMAGESPANATTRIBUTE_SIZE_TAG = 0x3B;
constexpr uint8_t TLV_IMAGESPANATTRIBUTE_VERTICALALIGN_TAG = 0x3C;
constexpr uint8_t TLV_IMAGESPANATTRIBUTE_OBJECTFIT_TAG = 0x3D;
constexpr uint8_t TLV_IMAGESPANATTRIBUTE_MARGINPROP_TAG = 0x3E;
constexpr uint8_t TLV_IMAGESPANATTRIBUTE_BORDERRADIUS_TAG = 0x3F;
constexpr uint8_t TLV_IMAGESPANATTRIBUTE_PADDINGPROP_TAG = 0x40;
constexpr uint8_t TLV_IMAGESPANATTRIBUTE_END_TAG = 0x41;

constexpr uint8_t TLV_IMAGESPANSIZE_TAG = 0x42;
constexpr uint8_t TLV_IMAGESPANSIZE_WIDTH_TAG = 0x43;
constexpr uint8_t TLV_IMAGESPANSIZE_HEIGHT_TAG = 0x44;
constexpr uint8_t TLV_IMAGESPANSIZE_END_TAG = 0x45;

constexpr uint8_t TLV_PADDINGPROPERTY_TAG = 0x46;
constexpr uint8_t TLV_PADDINGPROPERTY_TOP_TAG = 0x47;
constexpr uint8_t TLV_PADDINGPROPERTY_BOTTOM_TAG = 0x48;
constexpr uint8_t TLV_PADDINGPROPERTY_LEFT_TAG = 0x49;
constexpr uint8_t TLV_PADDINGPROPERTY_RIGHT_TAG = 0x4A;
constexpr uint8_t TLV_PADDINGPROPERTY_END_TAG = 0x4B;

constexpr uint8_t TLV_LEADINGMARGIN_TAG = 0x4C;
constexpr uint8_t TLV_LEADINGMARGIN_HASPIXEL_TAG = 0x4D;
constexpr uint8_t TLV_LEADINGMARGIN_NOPIXEL_TAG = 0x4E;

constexpr uint8_t TLV_SPANITEM_TAG = 0x4F;
constexpr uint8_t TLV_IMAGESPANITEM_TAG = 0x50;
constexpr uint8_t TLV_SPANITEM_END_TAG = 0x51;
constexpr uint8_t TLV_IMAGESPANOPTION_OFFSET_TAG = 0x52;
constexpr uint8_t TLV_IMAGESPANOPTION_IMAGE_TAG = 0x53;
constexpr uint8_t TLV_IMAGESPANOPTION_BUNDLENAME_TAG = 0x54;
constexpr uint8_t TLV_IMAGESPANOPTION_MODULENAME_TAG = 0x55;
constexpr uint8_t TLV_IMAGESPANOPTION_IMAGEPIXELMAP_TAG = 0x56;
constexpr uint8_t TLV_IMAGESPANOPTION_IMAGEATTRIBUTE_TAG = 0x57;

constexpr uint8_t TLV_SPAN_FONT_STYLE_FONTSIZE = 0x58;
constexpr uint8_t TLV_SPAN_FONT_STYLE_TEXTCOLOR = 0x59;
constexpr uint8_t TLV_SPAN_FONT_STYLE_TEXTSHADOW = 0x5A;
constexpr uint8_t TLV_SPAN_FONT_STYLE_ITALICFONTSTYLE = 0x5B;
constexpr uint8_t TLV_SPAN_FONT_STYLE_FONTWEIGHT = 0x5C;
constexpr uint8_t TLV_SPAN_FONT_STYLE_FONTFAMILY = 0x5D;
constexpr uint8_t TLV_SPAN_FONT_STYLE_FONTFEATURE = 0x5E;
constexpr uint8_t TLV_SPAN_FONT_STYLE_TEXTDECORATION = 0x5F;
constexpr uint8_t TLV_SPAN_FONT_STYLE_TEXTDECORATIONCOLOR = 0x60;
constexpr uint8_t TLV_SPAN_FONT_STYLE_TEXTDECORATIONSTYLE = 0x61;
constexpr uint8_t TLV_SPAN_FONT_STYLE_TEXTCASE = 0x62;
constexpr uint8_t TLV_SPAN_FONT_STYLE_ADPATMINFONTSIZE = 0x63;
constexpr uint8_t TLV_SPAN_FONT_STYLE_ADPATMAXFONTSIZE = 0x64;
constexpr uint8_t TLV_SPAN_FONT_STYLE_LETTERSPACING = 0x65;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_LINEHEIGHT = 0x66;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_LINESPACING = 0x67;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_TEXTBASELINE = 0x68;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_BASELINEOFFSET = 0x69;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_TEXTOVERFLOW = 0x6A;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_TEXTALIGN = 0x6B;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_MAXLENGTH = 0x6C;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_MAXLINES = 0x6D;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_HEIGHTADAPTIVEPOLICY = 0x6E;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_TEXTINDENT = 0x6F;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_LEADINGMARGIN = 0x90;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_WORDBREAK = 0x91;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_LINEBREAKSTRATEGY = 0x92;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_ELLIPSISMODE = 0x93;

constexpr uint8_t TLV_SPAN_BACKGROUND_BACKGROUNDCOLOR = 0x94;
constexpr uint8_t TLV_SPAN_BACKGROUND_BACKGROUNDRADIUS = 0x95;
constexpr uint8_t TLV_SPAN_BACKGROUND_GROUPID = 0x96;

constexpr uint8_t TLV_CUSTOM_MARSHALL_BUFFER_START = 0x97;

constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_PARAGRAPH_SPACING = 0x98;

constexpr uint8_t TLV_SPAN_STRING_MODE_FLAG = 0x99;
constexpr uint8_t TLV_SPAN_FONT_STYLE_LineThicknessScale = 0x9A;
constexpr uint8_t TLV_FLOAT_TAG = 0x9B;
constexpr uint8_t TLV_SPAN_URL_CONTENT = 0X9C;
constexpr uint8_t TLV_SPAN_FONT_STYLE_SUPERSCRIPT = 0x9D;
constexpr uint8_t TLV_SPAN_FONT_STYLE_STROKEWIDTH = 0x9E;
constexpr uint8_t TLV_SPAN_FONT_STYLE_STROKECOLOR = 0x9F;
constexpr uint8_t TLV_SUPERSCRIPT_TAG = 0xA0;
constexpr uint8_t TLV_SPAN_TEXT_LINE_STYLE_TEXTVERTICALALIGN = 0xA1;
constexpr uint8_t TLV_TEXTVERTICALALIGN_TAG = 0xA2;


#define TLV_DEFINE_ENUM_TYPE(type, tag) \
public:                                                                     \
    static void Write##type(std::vector<uint8_t>& buff, type value)         \
    {                                                                       \
        WriteUint8(buff, tag);                                              \
        WriteInt32(buff, static_cast<int32_t>(value));                      \
    }                                                                       \
    static type Read##type(std::vector<uint8_t>& buff, int32_t& cursor)     \
    {                                                                       \
        if (ReadUint8(buff, cursor) != (tag)) {                             \
            return static_cast<type>(0);                                    \
        }                                                                   \
        auto val = ReadInt32(buff, cursor);                                 \
        return static_cast<type>(val);                                      \
    }

class TLVUtil {
public:
    static void WriteUint8(std::vector<uint8_t>& buff, uint8_t value)
    {
        buff.push_back(value);
    }

    static uint8_t ReadUint8(std::vector<uint8_t>& buff, int32_t& cursor)
    {
        if (static_cast<size_t>(cursor + 1) > buff.size()) {
            return TLV_END;
        }
        return buff[cursor++];
    }

    static void WriteInt32(std::vector<uint8_t>& buff, int32_t oriValue)
    {
        uint32_t value = static_cast<uint32_t>(oriValue);
        while (value > TLV_VARINT_MASK) {
            buff.push_back(TLV_VARINT_MORE | uint8_t(value & TLV_VARINT_MASK));
            value >>= TLV_VARINT_BITS;
        }
        buff.push_back(uint8_t(value));
    }

    static int32_t ReadInt32(std::vector<uint8_t>& buff, int32_t& cursor)
    {
        uint32_t value = 0;
        uint8_t shift = 0;
        uint32_t item = 0;
        do {
            if (static_cast<size_t>(cursor + 1) > buff.size()) {
                return static_cast<int32_t>(TLV_END);
            }
            item = uint32_t(buff[cursor++]);
            value |= (item & TLV_VARINT_MASK) << shift;
            shift += TLV_VARINT_BITS;
        } while ((item & TLV_VARINT_MORE) != 0);
        return static_cast<int32_t>(value);
    }

    TLV_DEFINE_ENUM_TYPE(FontStyle, TLV_ITALICSFONTSTYLE_TAG);
    TLV_DEFINE_ENUM_TYPE(FontWeight, TLV_FONTWEIGHT_TAG);
    TLV_DEFINE_ENUM_TYPE(SuperscriptStyle, TLV_SUPERSCRIPT_TAG);
    TLV_DEFINE_ENUM_TYPE(TextDecoration, TLV_TEXTDECORATION_TAG);
    TLV_DEFINE_ENUM_TYPE(TextDecorationStyle, TLV_TEXTDECORATIONSTYLE_TAG);
    TLV_DEFINE_ENUM_TYPE(TextCase, TLV_TEXTCASE_TAG);
    TLV_DEFINE_ENUM_TYPE(TextBaseline, TLV_TEXTBASELINE_TAG);
    TLV_DEFINE_ENUM_TYPE(TextOverflow, TLV_TEXTOVERFLOW_TAG);
    TLV_DEFINE_ENUM_TYPE(TextAlign, TLV_TEXTALIGN_TAG);
    TLV_DEFINE_ENUM_TYPE(TextHeightAdaptivePolicy, TLV_TEXTHEIGHTADAPTIVEPOLICY_TAG);
    TLV_DEFINE_ENUM_TYPE(WordBreak, TLV_WORDBREAK_TAG);
    TLV_DEFINE_ENUM_TYPE(EllipsisMode, TLV_ELLIPSISMODE_TAG);
    TLV_DEFINE_ENUM_TYPE(LineBreakStrategy, TLV_LINEBREAKSTRATEGY_TAG);
    TLV_DEFINE_ENUM_TYPE(VerticalAlign, TLV_VERTICALALIGN_TAG);
    TLV_DEFINE_ENUM_TYPE(ImageFit, TLV_IMAGEFIT_TAG);
    TLV_DEFINE_ENUM_TYPE(TextVerticalAlign, TLV_TEXTVERTICALALIGN_TAG);

    static void WriteString(std::vector<uint8_t>& buff, const std::string& value);
    static std::string ReadString(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteU16String(std::vector<uint8_t>& buff, const std::u16string& value);
    static std::u16string ReadU16String(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteDouble(std::vector<uint8_t>& buff, double value);
    static double ReadDouble(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteColor(std::vector<uint8_t>& buff, Color& value);
    static Color ReadColor(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteDimension(std::vector<uint8_t>& buff, const Dimension& value);
    static Dimension ReadDimension(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteFontFamily(std::vector<uint8_t>& buff, std::vector<std::string>& value);
    static std::vector<std::string> ReadFontFamily(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteTextShadow(std::vector<uint8_t>& buff, Shadow& value);
    static Shadow ReadTextShadow(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteTextShadows(std::vector<uint8_t>& buff, std::vector<Shadow>& value);
    static std::vector<Shadow> ReadTextShadows(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteFontFeature(std::vector<uint8_t>& buff, std::list<std::pair<std::string, int32_t>>& value);
    static std::list<std::pair<std::string, int32_t>> ReadFontFeature(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteBorderRadiusProperty(std::vector<uint8_t>& buff, NG::BorderRadiusProperty& value);
    static NG::BorderRadiusProperty ReadBorderRadiusProperty(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WritePixelMap(std::vector<uint8_t>& buff, RefPtr<Ace::PixelMap>& pixelMap);
    static RefPtr<Ace::PixelMap> ReadPixelMap(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteCalcDimension(std::vector<uint8_t>& buff, CalcDimension& value);
    static CalcDimension ReadCalcDimension(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteCalcLength(std::vector<uint8_t>& buff, NG::CalcLength& value);
    static NG::CalcLength ReadCalcLength(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteImageSpanSize(std::vector<uint8_t>& buff, ImageSpanSize& value);
    static ImageSpanSize ReadImageSpanSize(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WritePaddingProperty(std::vector<uint8_t>& buff, NG::PaddingProperty& value);
    static NG::PaddingProperty ReadPaddingProperty(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteImageSpanAttribute(std::vector<uint8_t>& buff, ImageSpanAttribute& value);
    static ImageSpanAttribute ReadImageSpanAttribute(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteLeadingMargin(std::vector<uint8_t>& buff, NG::LeadingMargin& value);
    static NG::LeadingMargin ReadLeadingMargin(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteTextDecorations(std::vector<uint8_t>& buff, const std::vector<TextDecoration>& values);
    static std::vector<TextDecoration> ReadTextDecorations(std::vector<uint8_t>& buff, int32_t& cursor);
    static void WriteFloat(std::vector<uint8_t>& buff, float value);
    static float ReadFloat(std::vector<uint8_t>& buff, int32_t& cursor);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_TLV_UTIL_H