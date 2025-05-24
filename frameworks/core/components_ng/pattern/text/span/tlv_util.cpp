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

#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/text/span/tlv_util.h"


namespace OHOS::Ace {
void TLVUtil::WriteString(std::vector<uint8_t>& buff, const std::string& value)
{
    WriteUint8(buff, TLV_STRING_TAG);
    WriteInt32(buff, value.length());
    for (char ch: value) {
        WriteUint8(buff, static_cast<uint8_t>(ch));
    }
}

std::string TLVUtil::ReadString(std::vector<uint8_t>& buff, int32_t& cursor)
{
    if (ReadUint8(buff, cursor) != TLV_STRING_TAG) {
        return "";
    }
    int32_t strLen = ReadInt32(buff, cursor);
    if (strLen == TLV_END || strLen <= 0) {
        return "";
    }
    std::stringstream ss;
    for (auto i = 0; i < strLen; ++i) {
        uint8_t chVal = ReadUint8(buff, cursor);
        if (chVal == TLV_END) {
            return "";
        }
        ss << static_cast<char>(chVal);
    }
    return ss.str();
}

void TLVUtil::WriteU16String(std::vector<uint8_t>& buff, const std::u16string& value)
{
    WriteString(buff, UtfUtils::Str16DebugToStr8(value));
}

std::u16string TLVUtil::ReadU16String(std::vector<uint8_t>& buff, int32_t& cursor)
{
    return UtfUtils::Str8DebugToStr16(ReadString(buff, cursor));
}

void TLVUtil::WriteDouble(std::vector<uint8_t>& buff, double value)
{
    WriteUint8(buff, TLV_DOUBLE_TAG);
    std::vector<uint8_t> bytes(sizeof(double));
    auto valuePtr = reinterpret_cast<uint8_t*>(&value);
    std::copy(valuePtr, valuePtr + sizeof(double), bytes.begin());
    buff.insert(buff.end(), bytes.begin(), bytes.end());
}

double TLVUtil::ReadDouble(std::vector<uint8_t>& buff, int32_t& cursor)
{
    if (ReadUint8(buff, cursor) != TLV_DOUBLE_TAG) {
        return 0.0;
    }
    auto start = buff.begin() + cursor;
    auto end = start + sizeof(double);
    double value;
    std::copy(start, end, reinterpret_cast<uint8_t*>(&value));
    cursor += sizeof(double);
    return value;
}

void TLVUtil::WriteFloat(std::vector<uint8_t>& buff, float value)
{
    WriteUint8(buff, TLV_FLOAT_TAG);
    std::vector<uint8_t> bytes(sizeof(float));
    auto valuePtr = reinterpret_cast<uint8_t*>(&value);
    std::copy(valuePtr, valuePtr + sizeof(float), bytes.begin());
    buff.insert(buff.end(), bytes.begin(), bytes.end());
}

float TLVUtil::ReadFloat(std::vector<uint8_t>& buff, int32_t& cursor)
{
    if (ReadUint8(buff, cursor) != TLV_FLOAT_TAG) {
        return 0.0;
    }
    auto start = buff.begin() + cursor;
    auto end = start + sizeof(float);
    float value;
    std::copy(start, end, reinterpret_cast<uint8_t*>(&value));
    cursor += sizeof(float);
    return value;
}

void TLVUtil::WriteColor(std::vector<uint8_t>& buff, Color& value)
{
    WriteUint8(buff, TLV_COLOR_TAG);
    WriteUint8(buff, value.GetAlpha());
    WriteUint8(buff, value.GetRed());
    WriteUint8(buff, value.GetGreen());
    WriteUint8(buff, value.GetBlue());
}

Color TLVUtil::ReadColor(std::vector<uint8_t>& buff, int32_t& cursor)
{
    if (ReadUint8(buff, cursor) != TLV_COLOR_TAG) {
        return Color();
    }
    auto alpha = ReadUint8(buff, cursor);
    auto red = ReadUint8(buff, cursor);
    auto green = ReadUint8(buff, cursor);
    auto blue = ReadUint8(buff, cursor);
    return Color::FromARGB(alpha, red, green, blue);
}

void TLVUtil::WriteDimension(std::vector<uint8_t>& buff, const Dimension& value)
{
    WriteUint8(buff, TLV_DIMENSION_TAG);
    WriteDouble(buff, value.Value());
    WriteInt32(buff, static_cast<int32_t>(value.Unit()));
}

Dimension TLVUtil::ReadDimension(std::vector<uint8_t>& buff, int32_t& cursor)
{
    if (ReadUint8(buff, cursor) != TLV_DIMENSION_TAG) {
        return Dimension();
    }
    auto val = ReadDouble(buff, cursor);
    auto unit = static_cast<DimensionUnit>(ReadInt32(buff, cursor));
    return Dimension(val, unit);
}

void TLVUtil::WriteFontFamily(std::vector<uint8_t>& buff, std::vector<std::string>& value)
{
    WriteUint8(buff, TLV_FONTFAMILIES_TAG);
    WriteInt32(buff, value.size());
    for (auto& fontFamily: value) {
        WriteString(buff, fontFamily);
    }
}

std::vector<std::string> TLVUtil::ReadFontFamily(std::vector<uint8_t>& buff, int32_t& cursor)
{
    std::vector<std::string> fontFamilies;
    if (ReadUint8(buff, cursor) != TLV_FONTFAMILIES_TAG) {
        return fontFamilies;
    }
    int32_t fontFamilySize = ReadInt32(buff, cursor);
    for (auto i = 0; i < fontFamilySize; i++) {
        auto fontFamily = ReadString(buff, cursor);
        fontFamilies.emplace_back(fontFamily);
    }
    return fontFamilies;
}

void TLVUtil::WriteTextShadow(std::vector<uint8_t>& buff, Shadow& value)
{
    WriteUint8(buff, TLV_TEXTSHADOW_TAG);
    WriteDouble(buff, value.GetBlurRadius());
    auto color = value.GetColor();
    WriteColor(buff, color);
    WriteInt32(buff, static_cast<int32_t>(value.GetShadowType()));
    Offset offset = value.GetOffset();
    WriteDouble(buff, offset.GetX());
    WriteDouble(buff, offset.GetY());
}

Shadow TLVUtil::ReadTextShadow(std::vector<uint8_t>& buff, int32_t& cursor)
{
    Shadow shadow;
    if (ReadUint8(buff, cursor) != TLV_TEXTSHADOW_TAG) {
        return shadow;
    }
    double blurRadius = ReadDouble(buff, cursor);
    Color color = ReadColor(buff, cursor);
    ShadowType type = static_cast<ShadowType>(ReadInt32(buff, cursor));
    double offsetX = ReadDouble(buff, cursor);
    double offsetY = ReadDouble(buff, cursor);
    shadow.SetBlurRadius(blurRadius);
    shadow.SetColor(color);
    shadow.SetShadowType(type);
    shadow.SetOffset({offsetX, offsetY});
    shadow.SetIsFilled(false);
    return shadow;
}

void TLVUtil::WriteTextShadows(std::vector<uint8_t>& buff, std::vector<Shadow>& value)
{
    WriteUint8(buff, TLV_TEXTSHADOWS_TAG);
    WriteInt32(buff, value.size());
    for (auto& shadow: value) {
        WriteTextShadow(buff, shadow);
    }
}

std::vector<Shadow> TLVUtil::ReadTextShadows(std::vector<uint8_t>& buff, int32_t& cursor)
{
    std::vector<Shadow> shadows;
    if (ReadUint8(buff, cursor) != TLV_TEXTSHADOWS_TAG) {
        return shadows;
    }
    int32_t shadowSize = ReadInt32(buff, cursor);
    for (auto i = 0; i < shadowSize; i ++) {
        shadows.emplace_back(ReadTextShadow(buff, cursor));
    }
    return shadows;
}

void TLVUtil::WriteTextDecorations(std::vector<uint8_t>& buff, const std::vector<TextDecoration>& values)
{
    WriteUint8(buff, TLV_SPAN_FONT_STYLE_TEXTDECORATION);
    WriteInt32(buff, values.size());
    for (TextDecoration value: values) {
        WriteInt32(buff, static_cast<int32_t>(value));
    }
}

std::vector<TextDecoration> TLVUtil::ReadTextDecorations(std::vector<uint8_t>& buff, int32_t& cursor)
{
    std::vector<TextDecoration> textDecorations;
    int32_t size = ReadInt32(buff, cursor);
    std::cout << "ReadTextDecorations size:" << size << std::endl;
    for (auto i = 0; i < size; i ++) {
        int32_t value = ReadInt32(buff, cursor);
        textDecorations.emplace_back(static_cast<TextDecoration>(value));
    }
    return textDecorations;
}


void TLVUtil::WriteFontFeature(std::vector<uint8_t>& buff, std::list<std::pair<std::string, int32_t>>& value)
{
    WriteUint8(buff, TLV_FONTFEATURE_TAG);
    WriteInt32(buff, value.size());
    for (auto& fontFeature : value) {
        WriteString(buff, fontFeature.first);
        WriteInt32(buff, fontFeature.second);
    }
}

std::list<std::pair<std::string, int32_t>> TLVUtil::ReadFontFeature(std::vector<uint8_t>& buff, int32_t& cursor)
{
    std::list<std::pair<std::string, int32_t>> fontFeatureList;
    if (ReadUint8(buff, cursor) != TLV_FONTFEATURE_TAG) {
        return fontFeatureList;
    }
    int32_t len = ReadInt32(buff, cursor);
    for (auto i = 0; i < len; i++) {
        std::string first = ReadString(buff, cursor);
        int32_t second = ReadInt32(buff, cursor);
        fontFeatureList.push_back({first, second});
    }
    return fontFeatureList;
}

void TLVUtil::WriteBorderRadiusProperty(std::vector<uint8_t>& buff, NG::BorderRadiusProperty& value)
{
    WriteUint8(buff, TLV_BORDERRADIUS_TAG);

    WriteDimension(buff, value.radiusTopLeft.value_or(ILLEGAL_DIMENSION_VALUE));
    WriteDimension(buff, value.radiusTopRight.value_or(ILLEGAL_DIMENSION_VALUE));
    WriteDimension(buff, value.radiusBottomLeft.value_or(ILLEGAL_DIMENSION_VALUE));
    WriteDimension(buff, value.radiusBottomRight.value_or(ILLEGAL_DIMENSION_VALUE));
}

NG::BorderRadiusProperty TLVUtil::ReadBorderRadiusProperty(std::vector<uint8_t>& buff, int32_t& cursor)
{
    NG::BorderRadiusProperty br;
    if (ReadUint8(buff, cursor) != TLV_BORDERRADIUS_TAG) {
        return br;
    }

    Dimension radiusTopLeft = ReadDimension(buff, cursor);
    if (radiusTopLeft.IsNonNegative()) {
        br.radiusTopLeft = radiusTopLeft;
    }
    Dimension radiusTopRight = ReadDimension(buff, cursor);
    if (radiusTopRight.IsNonNegative()) {
        br.radiusTopRight = radiusTopRight;
    }
    Dimension radiusBottomLeft = ReadDimension(buff, cursor);
    if (radiusBottomLeft.IsNonNegative()) {
        br.radiusBottomLeft = radiusBottomLeft;
    }
    Dimension radiusBottomRight = ReadDimension(buff, cursor);
    if (radiusBottomRight.IsNonNegative()) {
        br.radiusBottomRight = radiusBottomRight;
    }
    return br;
}

void TLVUtil::WritePixelMap(std::vector<uint8_t>& buff, RefPtr<Ace::PixelMap>& pixelMap)
{
    WriteUint8(buff, TLV_PIXEL_MAP_TAG);
    std::vector<uint8_t> tmpPixel;
    if (pixelMap) {
        pixelMap->EncodeTlv(tmpPixel);
        WriteInt32(buff, static_cast<int32_t>(tmpPixel.size()));
        buff.insert(buff.end(), tmpPixel.begin(), tmpPixel.end());
    } else {
        WriteInt32(buff, 0);
    }
}

RefPtr<Ace::PixelMap> TLVUtil::ReadPixelMap(std::vector<uint8_t>& buff, int32_t& cursor)
{
    if (ReadUint8(buff, cursor) != TLV_PIXEL_MAP_TAG) {
        return nullptr;
    }
    auto pixelMapLength = ReadInt32(buff, cursor);
    if (pixelMapLength == 0) {
        return nullptr;
    }
    std::vector<uint8_t> pixelMapSubVec(buff.begin() + cursor, buff.begin() + cursor + pixelMapLength);
    RefPtr<Ace::PixelMap> p = Ace::PixelMap::DecodeTlv(pixelMapSubVec);
    cursor += pixelMapLength;
    return p;
}

void TLVUtil::WriteCalcDimension(std::vector<uint8_t>& buff, CalcDimension& value)
{
    WriteUint8(buff, TLV_CALCDIMENSION_TAG);
    WriteDimension(buff, value);
}

CalcDimension TLVUtil::ReadCalcDimension(std::vector<uint8_t>& buff, int32_t& cursor)
{
    CalcDimension i;
    if (ReadUint8(buff, cursor) != TLV_CALCDIMENSION_TAG) {
        return i;
    }
    Dimension dim = ReadDimension(buff, cursor);
    return CalcDimension(dim);
}

void TLVUtil::WriteCalcLength(std::vector<uint8_t>& buff, NG::CalcLength& value)
{
    WriteUint8(buff, TLV_CALCLENGTH_TAG);
    WriteString(buff, value.CalcValue());
    WriteDimension(buff, value.GetDimension());
}

NG::CalcLength TLVUtil::ReadCalcLength(std::vector<uint8_t>& buff, int32_t& cursor)
{
    NG::CalcLength calcL;
    if (ReadUint8(buff, cursor) != TLV_CALCLENGTH_TAG) {
        return calcL;
    }
    std::string calcValue = ReadString(buff, cursor);
    Dimension dim = ReadDimension(buff, cursor);
    calcL = NG::CalcLength(dim);
    calcL.SetCalcValue(calcValue);
    return calcL;
}

void TLVUtil::WriteImageSpanSize(std::vector<uint8_t>& buff, ImageSpanSize& value)
{
    WriteUint8(buff, TLV_IMAGESPANSIZE_TAG);
    if (value.width.has_value()) {
        WriteUint8(buff, TLV_IMAGESPANSIZE_WIDTH_TAG);
        WriteCalcDimension(buff, value.width.value());
    }
    if (value.height.has_value()) {
        WriteUint8(buff, TLV_IMAGESPANSIZE_HEIGHT_TAG);
        WriteCalcDimension(buff, value.height.value());
    }
    WriteUint8(buff, TLV_IMAGESPANSIZE_END_TAG);
}

ImageSpanSize TLVUtil::ReadImageSpanSize(std::vector<uint8_t>& buff, int32_t& cursor)
{
    ImageSpanSize imageSpanSize;
    if (ReadUint8(buff, cursor) != TLV_IMAGESPANSIZE_TAG) {
        return imageSpanSize;
    }
    for (uint8_t tag = TLVUtil::ReadUint8(buff, cursor);
        tag != TLV_IMAGESPANSIZE_END_TAG; tag = TLVUtil::ReadUint8(buff, cursor)) {
        switch (tag) {
            case TLV_IMAGESPANSIZE_WIDTH_TAG: {
                imageSpanSize.width = ReadCalcDimension(buff, cursor);
                break;
            }
            case TLV_IMAGESPANSIZE_HEIGHT_TAG: {
                imageSpanSize.height = ReadCalcDimension(buff, cursor);
                break;
            }
            default:
                break;
        }
    }
    return imageSpanSize;
}

void TLVUtil::WritePaddingProperty(std::vector<uint8_t>& buff, NG::PaddingProperty& value)
{
    WriteUint8(buff, TLV_PADDINGPROPERTY_TAG);
    if (value.left.has_value()) {
        WriteUint8(buff, TLV_PADDINGPROPERTY_LEFT_TAG);
        WriteCalcLength(buff, value.left.value());
    }
    if (value.right.has_value()) {
        WriteUint8(buff, TLV_PADDINGPROPERTY_RIGHT_TAG);
        WriteCalcLength(buff, value.right.value());
    }
    if (value.top.has_value()) {
        WriteUint8(buff, TLV_PADDINGPROPERTY_TOP_TAG);
        WriteCalcLength(buff, value.top.value());
    }
    if (value.bottom.has_value()) {
        WriteUint8(buff, TLV_PADDINGPROPERTY_BOTTOM_TAG);
        WriteCalcLength(buff, value.bottom.value());
    }
    WriteUint8(buff, TLV_PADDINGPROPERTY_END_TAG);
}

NG::PaddingProperty TLVUtil::ReadPaddingProperty(std::vector<uint8_t>& buff, int32_t& cursor)
{
    NG::PaddingProperty pad;
    if (ReadUint8(buff, cursor) != TLV_PADDINGPROPERTY_TAG) {
        return pad;
    }
    for (uint8_t tag = TLVUtil::ReadUint8(buff, cursor);
        tag != TLV_PADDINGPROPERTY_END_TAG; tag = TLVUtil::ReadUint8(buff, cursor)) {
        switch (tag) {
            case TLV_PADDINGPROPERTY_LEFT_TAG: {
                pad.left = ReadCalcLength(buff, cursor);
                break;
            }
            case TLV_PADDINGPROPERTY_TOP_TAG: {
                pad.top = ReadCalcLength(buff, cursor);
                break;
            }
            case TLV_PADDINGPROPERTY_BOTTOM_TAG: {
                pad.bottom = ReadCalcLength(buff, cursor);
                break;
            }
            case TLV_PADDINGPROPERTY_RIGHT_TAG: {
                pad.right = ReadCalcLength(buff, cursor);
                break;
            }
            default:
                break;
        }
    }
    return pad;
}

void TLVUtil::WriteImageSpanAttribute(std::vector<uint8_t>& buff, ImageSpanAttribute& value)
{
    WriteUint8(buff, TLV_IMAGESPANATTRIBUTE_TAG);
    if (value.size.has_value()) {
        WriteUint8(buff, TLV_IMAGESPANATTRIBUTE_SIZE_TAG);
        WriteImageSpanSize(buff, value.size.value());
    }
    if (value.verticalAlign.has_value()) {
        WriteUint8(buff, TLV_IMAGESPANATTRIBUTE_VERTICALALIGN_TAG);
        WriteVerticalAlign(buff, value.verticalAlign.value());
    }
    if (value.objectFit.has_value()) {
        WriteUint8(buff, TLV_IMAGESPANATTRIBUTE_OBJECTFIT_TAG);
        WriteImageFit(buff, value.objectFit.value());
    }
    if (value.marginProp.has_value()) {
        WriteUint8(buff, TLV_IMAGESPANATTRIBUTE_MARGINPROP_TAG);
        WritePaddingProperty(buff, value.marginProp.value());
    }
    if (value.borderRadius.has_value()) {
        WriteUint8(buff, TLV_IMAGESPANATTRIBUTE_BORDERRADIUS_TAG);
        WriteBorderRadiusProperty(buff, value.borderRadius.value());
    }
    if (value.paddingProp.has_value()) {
        WriteUint8(buff, TLV_IMAGESPANATTRIBUTE_PADDINGPROP_TAG);
        WritePaddingProperty(buff, value.paddingProp.value());
    }
    WriteUint8(buff, TLV_IMAGESPANATTRIBUTE_END_TAG);
}

ImageSpanAttribute TLVUtil::ReadImageSpanAttribute(std::vector<uint8_t>& buff, int32_t& cursor)
{
    ImageSpanAttribute l;
    if (ReadUint8(buff, cursor) != TLV_IMAGESPANATTRIBUTE_TAG) {
        return l;
    }
    for (uint8_t tag = TLVUtil::ReadUint8(buff, cursor);
        tag != TLV_IMAGESPANATTRIBUTE_END_TAG; tag = TLVUtil::ReadUint8(buff, cursor)) {
        switch (tag) {
            case TLV_IMAGESPANATTRIBUTE_SIZE_TAG: {
                l.size = ReadImageSpanSize(buff, cursor);
                break;
            }
            case TLV_IMAGESPANATTRIBUTE_VERTICALALIGN_TAG: {
                l.verticalAlign = ReadVerticalAlign(buff, cursor);
                break;
            }
            case TLV_IMAGESPANATTRIBUTE_OBJECTFIT_TAG: {
                l.objectFit = ReadImageFit(buff, cursor);
                break;
            }
            case TLV_IMAGESPANATTRIBUTE_MARGINPROP_TAG: {
                l.marginProp = ReadPaddingProperty(buff, cursor);
                break;
            }
            case TLV_IMAGESPANATTRIBUTE_BORDERRADIUS_TAG: {
                l.borderRadius = ReadBorderRadiusProperty(buff, cursor);
                break;
            }
            case TLV_IMAGESPANATTRIBUTE_PADDINGPROP_TAG: {
                l.paddingProp = ReadPaddingProperty(buff, cursor);
                break;
            }
            default:
                break;
        }
    }
    return l;
}

void TLVUtil::WriteLeadingMargin(std::vector<uint8_t>& buff, NG::LeadingMargin& value)
{
    WriteUint8(buff, TLV_LEADINGMARGIN_TAG);
    WriteDimension(buff, value.size.Width());
    WriteDimension(buff, value.size.Height());
    if (value.pixmap) {
        WriteUint8(buff, TLV_LEADINGMARGIN_HASPIXEL_TAG);
        WritePixelMap(buff, value.pixmap);
    } else {
        WriteUint8(buff, TLV_LEADINGMARGIN_NOPIXEL_TAG);
    }
}

NG::LeadingMargin TLVUtil::ReadLeadingMargin(std::vector<uint8_t>& buff, int32_t& cursor)
{
    NG::LeadingMargin l;
    if (ReadUint8(buff, cursor) != TLV_LEADINGMARGIN_TAG) {
        return l;
    }
    auto width = ReadDimension(buff, cursor);
    auto height = ReadDimension(buff, cursor);
    l.size = NG::LeadingMarginSize(width, height);
    auto tag = ReadUint8(buff, cursor);
    if (tag == TLV_LEADINGMARGIN_HASPIXEL_TAG) {
        l.pixmap = ReadPixelMap(buff, cursor);
    }
    return l;
}
} // namespace OHOS::Ace