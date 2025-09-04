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

#include "frameworks/core/components_ng/svg/parse/svg_attributes_parser.h"
#include "core/common/container.h"
#include "frameworks/core/components_ng/svg/svg_utils.h"

namespace OHOS::Ace::NG {
namespace {
const char LINECAP_ROUND[] = "round";
const char LINECAP_SQUARE[] = "square";
const char LINEJOIN_BEVEL[] = "bevel";
const char LINEJOIN_ROUND[] = "round";
const std::regex COLOR_WITH_ALPHA(
    R"(rgba?\(([0-9]{1,3})\,([0-9]{1,3})\,([0-9]{1,3})\,(\d+\.?\d*)\))", std::regex::icase);
const std::regex COLOR_WITH_RGBA_MAGIC("#[0-9A-Fa-f]{7,8}");
const std::regex COLOR_FORMAT_FOUR_HEX("#[0-9A-Fa-f]{4}");
constexpr int32_t RADIX_HEX = 16;
constexpr int32_t THREE_BYTE_BITS = 24;
constexpr int32_t TWO_BYTE_BITS = 16;
constexpr int32_t TWELVE_BITS = 12;
constexpr int32_t ONE_BYTE_BITS = 8;
constexpr int32_t FOUR_BITS = 4;
constexpr uint32_t RGBA_SUB_MATCH_SIZE = 5;
constexpr int32_t HEX_COLOR_LEN_SEVEN = 7;
constexpr double MAX_ALPHA = 1.0;
constexpr Dimension TRANSFORM_ORIGIN_DEFAULT = 0.5_pct;
constexpr size_t TRANSFORM_ORIGIN_PARA_AMOUNT1 = 1;
constexpr size_t TRANSFORM_ORIGIN_PARA_AMOUNT2 = 2;
constexpr size_t TRANSFORM_ORIGIN_PARA_AMOUNT3 = 3;
const char TRANSFORM_MATRIX[] = "matrix";
const char TRANSFORM_ROTATE[] = "rotate";
const char TRANSFORM_SCALE[] = "scale";
const char TRANSFORM_SKEWX[] = "skewX";
const char TRANSFORM_SKEWY[] = "skewY";
const char TRANSFORM_TRANSLATE[] = "translate";
const char SVG_ALIGN_XMIN_YMIN[] = "xMinYMin";
const char SVG_ALIGN_XMIN_YMID[] = "xMinYMid";
const char SVG_ALIGN_XMIN_YMAX[] = "xMinYMax";
const char SVG_ALIGN_XMID_YMIN[] = "xMidYMin";
const char SVG_ALIGN_XMID_YMID[] = "xMidYMid";
const char SVG_ALIGN_XMID_YMAX[] = "xMidYMax";
const char SVG_ALIGN_XMAX_YMIN[] = "xMaxYMin";
const char SVG_ALIGN_XMAX_YMID[] = "xMaxYMid";
const char SVG_ALIGN_XMAX_YMAX[] = "xMaxYMax";
const char SVG_ALIGN_NONE[] = "none";
const char SVG_ALIGN_MEET[] = "meet";
const char SVG_ALIGN_SLICE[] = "slice";
constexpr float PERCENT_RANGE_MAX = 100.0;
}

LineCapStyle SvgAttributesParser::GetLineCapStyle(const std::string& val)
{
    if (val == LINECAP_ROUND) {
        return LineCapStyle::ROUND;
    } else if (val == LINECAP_SQUARE) {
        return LineCapStyle::SQUARE;
    } else {
        return LineCapStyle::BUTT;
    }
}

LineJoinStyle SvgAttributesParser::GetLineJoinStyle(const std::string& val)
{
    if (val == LINEJOIN_BEVEL) {
        return LineJoinStyle::BEVEL;
    } else if (val == LINEJOIN_ROUND) {
        return LineJoinStyle::ROUND;
    } else {
        return LineJoinStyle::MITER;
    }
}

std::optional<Color> SvgAttributesParser::GetSpecialColor(const std::string& value)
{
    static const LinearMapNode<Color> COLOR_TABLE[] = {
        { "aliceblue", Color(0xfff0f8ff) },
        { "antiquewhite", Color(0xfffaebd7) },
        { "aqua", Color(0xff00ffff) },
        { "aquamarine", Color(0xff7fffd4) },
        { "azure", Color(0xfff0ffff) },
        { "beige", Color(0xfff5f5dc) },
        { "bisque", Color(0xffffe4c4) },
        { "black", Color(0XFF000000) },
        { "blanchedalmond", Color(0xffffebcd) },
        { "blue", Color(0xff0000ff) },
        { "blueviolet", Color(0xff8a2be2) },
        { "brown", Color(0xffa52a2a) },
        { "burlywood", Color(0xffdeb887) },
        { "cadetblue", Color(0xff5f9ea0) },
        { "chartreuse", Color(0xff7fff00) },
        { "chocolate", Color(0xffd2691e) },
        { "coral", Color(0xffff7f50) },
        { "cornflowerblue", Color(0xff6495ed) },
        { "cornsilk", Color(0xfffff8dc) },
        { "crimson", Color(0xffdc143c) },
        { "cyan", Color(0xff00ffff) },
        { "darkblue", Color(0xff00008b) },
        { "darkcyan", Color(0xff008b8b) },
        { "darkgoldenrod", Color(0xffb8860b) },
        { "darkgray", Color(0xffa9a9a9) },
        { "darkgreen", Color(0xff006400) },
        { "darkgrey", Color(0xffa9a9a9) },
        { "darkkhaki", Color(0xffbdb76b) },
        { "darkmagenta", Color(0xff8b008b) },
        { "darkolivegreen", Color(0xff556b2f) },
        { "darkorange", Color(0xffff8c00) },
        { "darkorchid", Color(0xff9932cc) },
        { "darkred", Color(0xff8b0000) },
        { "darksalmon", Color(0xffe9967a) },
        { "darkseagreen", Color(0xff8fbc8f) },
        { "darkslateblue", Color(0xff483d8b) },
        { "darkslategray", Color(0xff2f4f4f) },
        { "darkslategrey", Color(0xff2f4f4f) },
        { "darkturquoise", Color(0xff00ced1) },
        { "darkviolet", Color(0xff9400D3) },
        { "deeppink", Color(0xffff1493) },
        { "deepskyblue", Color(0xff00bfff) },
        { "dimgray", Color(0xff696969) },
        { "dimgrey", Color(0xff696969) },
        { "dodgerblue", Color(0xff1e90ff) },
        { "firebrick", Color(0xffb22222) },
        { "floralwhite", Color(0xfffffaf0) },
        { "forestgreen", Color(0xff228b22) },
        { "fuchsia", Color(0xffff00ff) },
        { "gainsboro", Color(0xffdcdcdc) },
        { "ghostwhite", Color(0xfff8f8ff) },
        { "gold", Color(0xffffd700) },
        { "goldenrod", Color(0xffdaa520) },
        { "gray", Color(0xff808080) },
        { "green", Color(0xff008000) },
        { "greenyellow", Color(0xffadff2f) },
        { "grey", Color(0xff808080) },
        { "honeydew", Color(0xfff0fff0) },
        { "hotpink", Color(0xffff69b4) },
        { "indianred", Color(0xffcd5c5c) },
        { "indigo", Color(0xff4b0082) },
        { "ivory", Color(0xfffffff0) },
        { "khaki", Color(0xfff0e68c) },
        { "lavender", Color(0xffe6e6fa) },
        { "lavenderblush", Color(0xfffff0f5) },
        { "lawngreen", Color(0xff7cfc00) },
        { "lemonchiffon", Color(0xfffffacd) },
        { "lightblue", Color(0xffadd8e6) },
        { "lightcoral", Color(0xfff08080) },
        { "lightcyan", Color(0xffe0ffff) },
        { "lightgoldenrodyellow", Color(0xfffafad2) },
        { "lightgray", Color(0xffd3d3d3) },
        { "lightgreen", Color(0xff90ee90) },
        { "lightgrey", Color(0xffd3d3d3) },
        { "lightpink", Color(0xffffb6c1) },
        { "lightsalmon", Color(0xffffa07a) },
        { "lightseagreen", Color(0xff20b2aa) },
        { "lightskyblue", Color(0xff87cefa) },
        { "lightslategray", Color(0xff778899) },
        { "lightslategrey", Color(0xff778899) },
        { "lightsteelblue", Color(0xffb0c4de) },
        { "lightyellow", Color(0xffffffe0) },
        { "lime", Color(0xff00ff00) },
        { "limegreen", Color(0xff32cd32) },
        { "linen", Color(0xfffaf0e6) },
        { "magenta", Color(0xffff00ff) },
        { "maroon", Color(0xff800000) },
        { "mediumaquamarine", Color(0xff66cdaa) },
        { "mediumblue", Color(0xff0000cd) },
        { "mediumorchid", Color(0xffba55d3) },
        { "mediumpurple", Color(0xff9370db) },
        { "mediumseagreen", Color(0xff3cb371) },
        { "mediumslateblue", Color(0xff7b68ee) },
        { "mediumspringgreen", Color(0xff00fa9a) },
        { "mediumturquoise", Color(0xff48d1cc) },
        { "mediumvioletred", Color(0xffc71585) },
        { "midnightblue", Color(0xff191970) },
        { "mintcream", Color(0xfff5fffa) },
        { "mistyrose", Color(0xffffe4e1) },
        { "moccasin", Color(0xffffe4b5) },
        { "navajowhite", Color(0xffffdead) },
        { "navy", Color(0xff000080) },
        { "oldlace", Color(0xfffdf5e6) },
        { "olive", Color(0xff808000) },
        { "olivedrab", Color(0xff6b8e23) },
        { "orange", Color(0xffffa500) },
        { "orangered", Color(0xffff4500) },
        { "orchid", Color(0xffda70d6) },
        { "palegoldenrod", Color(0xffeee8aa) },
        { "palegreen", Color(0xff98fb98) },
        { "paleturquoise", Color(0xffafeeee) },
        { "palevioletred", Color(0xffdb7093) },
        { "papayawhip", Color(0xffffefd5) },
        { "peachpuff", Color(0xffffdab9) },
        { "peru", Color(0xffcd853f) },
        { "pink", Color(0xffffc0cb) },
        { "plum", Color(0xffdda0dd) },
        { "powderblue", Color(0xffb0e0e6) },
        { "purple", Color(0xff800080) },
        { "red", Color(0xffff0000) },
        { "rosybrown", Color(0xffbc8f8f) },
        { "royalblue", Color(0xff4169e1) },
        { "rebeccapurple", Color(0xff663399) },
        { "saddlebrown", Color(0xff8b4513) },
        { "salmon", Color(0xfffa8072) },
        { "sandybrown", Color(0xfff4a460) },
        { "seagreen", Color(0xff2e8b57) },
        { "seashell", Color(0xfffff5ee) },
        { "sienna", Color(0xffa0522d) },
        { "silver", Color(0xffc0c0c0) },
        { "skyblue", Color(0xff87ceeb) },
        { "slateblue", Color(0xff6a5acd) },
        { "slategray", Color(0xff708090) },
        { "slategrey", Color(0xff708090) },
        { "snow", Color(0xfffffafa) },
        { "springgreen", Color(0xff00ff7f) },
        { "steelblue", Color(0xff4682b4) },
        { "tan", Color(0xffd2b48c) },
        { "teal", Color(0xff008080) },
        { "thistle", Color(0xffd8bfd8) },
        { "tomato", Color(0xffff6347) },
        { "turquoise", Color(0xff40e0d0) },
        { "violet", Color(0xffee82ee) },
        { "wheat", Color(0xfff5deb3) },
        { "white", Color(0xffffffff) },
        { "whitesmoke", Color(0xfff5f5f5) },
        { "yellow", Color(0xffffff00) },
        { "yellowgreen", Color(0xff9acd32) },
    };
    int64_t colorIndex = BinarySearchFindIndex(COLOR_TABLE, ArraySize(COLOR_TABLE), value.c_str());
    if (colorIndex != -1) {
        return COLOR_TABLE[colorIndex].value;
    }
    return std::nullopt;
}

bool SvgAttributesParser::ParseRGBAMagicColor(const std::string& value, Color& color)
{
    std::smatch matches;
    // #RGBA--->RRGGBBAA
    if (std::regex_match(value, matches, COLOR_FORMAT_FOUR_HEX)) {
        auto colorStr = value.substr(1);
        color = GetColorFrom4HexString(colorStr);
        return true;
    }

    if (!std::regex_match(value, matches, COLOR_WITH_RGBA_MAGIC)) {
        return false;
    }
    std::string colorStr = value.substr(1);
    // #00ffaad--->default black
    if (colorStr.length() == HEX_COLOR_LEN_SEVEN) {
        color = Color::BLACK;
        return true;
    }
    // #00ffaadd
    color = GetColorFromHexString(colorStr);
    return true;
}

bool SvgAttributesParser::ParseColor(std::string value, Color& color, bool featureEnable)
{
    if (value == "currentColor") {
        color = Color::BLACK;
        return true;
    }
    auto colorOpt = GetSpecialColor(value);
    if (colorOpt.has_value()) {
        color = colorOpt.value();
        return true;
    }
    value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
    if (featureEnable && ParseRGBAMagicColor(value, color)) {
        return true;
    }
    if (Color::MatchColorHexString(value)) {
        color = Color::FromString(value);
        return true;
    }
    return false;
}

Color SvgAttributesParser::GetColor(const std::string& value)
{
    auto colorOpt = GetSpecialColor(value);
    if (colorOpt.has_value()) {
        return colorOpt.value();
    }
    return Color::FromString(value);
}

Dimension SvgAttributesParser::ParseDimension(const std::string& value, bool useVp)
{
    return StringUtils::StringToDimension(value, useVp);
}

void SvgAttributesParser::StringToDimensionWithUnitSvg(const std::string& value, Dimension& dimension)
{
    errno = 0;
    if (std::strcmp(value.c_str(), "auto") == 0) {
        return;
    }
    char* pEnd = nullptr;
    double result = std::strtod(value.c_str(), &pEnd);
    if ((pEnd == nullptr) || (pEnd == value.c_str()) || (errno == ERANGE)) {
        return;
    }
    if (std::strcmp(pEnd, "%") == 0) {
        // Parse percent, transfer from [0, 100] to [0, 1]
        dimension = Dimension(result / PERCENT_RANGE_MAX, DimensionUnit::PERCENT);
    } else if (std::strcmp(pEnd, "px") == 0) {
        dimension = Dimension(result, DimensionUnit::PX);
    } else if (std::strcmp(pEnd, "vp") == 0) {
        dimension = Dimension(result, DimensionUnit::VP);
    } else if (std::strcmp(pEnd, "fp") == 0) {
        dimension = Dimension(result, DimensionUnit::FP);
    } else if (std::strcmp(pEnd, "lpx") == 0) {
        dimension = Dimension(result, DimensionUnit::LPX);
    } else if (std::strcmp(pEnd, "\0") == 0) {
        dimension = Dimension(result, DimensionUnit::PX);
    } else {
        return;
    }
}

void SvgAttributesParser::ParseDimension(const std::string& value, Dimension& dimension, bool featureEnable,
    bool useVp)
{
    if (!featureEnable) {
        dimension = StringUtils::StringToDimension(value, useVp);
        return;
    }
    StringToDimensionWithUnitSvg(value, dimension);
}

double SvgAttributesParser::ParseDouble(const std::string& value)
{
    return StringUtils::StringToDouble(value);
}

bool SvgAttributesParser::CheckColorAlpha(const std::string& colorStr, Color& result)
{
    std::smatch matches;
    if (std::regex_match(colorStr, matches, COLOR_WITH_ALPHA)) {
        if (matches.size() == RGBA_SUB_MATCH_SIZE) {
            auto red = static_cast<uint8_t>(std::stoi(matches[1]));
            auto green = static_cast<uint8_t>(std::stoi(matches[2]));
            auto blue = static_cast<uint8_t>(std::stoi(matches[3]));
            auto alpha = static_cast<double>(std::stod(matches[4]));
            // Scale up from 0~1.0 to 255
            result = Color::FromARGB(static_cast<uint8_t>(std::min(MAX_ALPHA, alpha)) * 0xff, red, green, blue);
            return true;
        }
    }
    return false;
}

std::pair<Dimension, Dimension> SvgAttributesParser::GetTransformOrigin(const std::string& transformOrigin)
{
    if (transformOrigin.empty()) {
        return std::pair<Dimension, Dimension>(0, 0);
    }
    std::vector<std::string> valueVector;
    Dimension pivotX = Dimension(0.0);
    Dimension pivotY = Dimension(0.0);
    Dimension tempPivotX = Dimension(0.0);
    Dimension tempPivotY = Dimension(0.0);
    StringUtils::StringSplitter(transformOrigin, ' ', valueVector);
    if (valueVector.size() == TRANSFORM_ORIGIN_PARA_AMOUNT1) {
        if (StringUtils::StringToDimensionWithUnitNG(valueVector[0], tempPivotX)) {
            pivotX = tempPivotX;
            pivotY = TRANSFORM_ORIGIN_DEFAULT;
            TAG_LOGI(AceLogTag::ACE_IMAGE, "GetTransformOrigin value:%{public}s|%{public}s",
                pivotX.ToString().c_str(), pivotY.ToString().c_str());
        }
    } else if ((valueVector.size() == TRANSFORM_ORIGIN_PARA_AMOUNT2) ||
               (valueVector.size() == TRANSFORM_ORIGIN_PARA_AMOUNT3)) {
        if (StringUtils::StringToDimensionWithUnitNG(valueVector[0], tempPivotX) &&
            StringUtils::StringToDimensionWithUnitNG(valueVector[1], tempPivotY)) {
            pivotX = tempPivotX;
            pivotY = tempPivotY;
            TAG_LOGI(AceLogTag::ACE_IMAGE, "GetTransformOrigin value:%{public}s|%{public}s",
                pivotX.ToString().c_str(), pivotY.ToString().c_str());
        }
    }
    return std::pair<Dimension, Dimension>(pivotX, pivotY);
}

bool IsBalanced(const std::string& str)
{
    std::stack<char> bracketStack;
    for (char ch : str) {
        if (ch == '(') {
            bracketStack.push(ch);
        } else if (ch == ')') {
            if (bracketStack.empty()) {
                return false;
            } else if (bracketStack.top() != '(') {
                return false;
            } else {
                bracketStack.pop();
            }
        }
    }
    return bracketStack.empty();
}

bool IsLegalParam(const std::vector<std::string>& paramVec)
{
    double result = 0.0;
    for (auto param : paramVec) {
        if (param.empty() || (param.back() == '%')) {
            return false;
        }
        if (!StringUtils::StringToDouble(param, result)) {
            return false;
        }
    }
    return true;
}

bool IsValidFuncType(const std::string& funcType)
{
    if ((funcType == TRANSFORM_MATRIX) || (funcType == TRANSFORM_ROTATE) || (funcType == TRANSFORM_SCALE) ||
        (funcType == TRANSFORM_SKEWX) || (funcType == TRANSFORM_SKEWY) || (funcType == TRANSFORM_TRANSLATE)) {
        return true;
    }
    return false;
}

std::vector<NG::TransformInfo> SvgAttributesParser::GetTransformInfo(const std::string& transform)
{
    std::vector<NG::TransformInfo> transformVec;
    if (transform.empty() || !IsBalanced(transform)) {
        return std::vector<NG::TransformInfo>();
    }
    std::string transformStr = StringUtils::TrimStr(transform);
    if (transformStr.empty()) {
        return std::vector<NG::TransformInfo>();
    }
    std::vector<std::string> attrs;
    StringUtils::SplitStr(transformStr, ")", attrs);
    for (auto& attr : attrs) {
        attr = StringUtils::TrimStr(attr);
        if (attr.empty()) {
            continue;
        }

        std::string funcType = attr.substr(0, attr.find_first_of("("));
        if (funcType.empty()) {
            return std::vector<NG::TransformInfo>();
        }
        funcType = StringUtils::TrimStr(funcType);
        if (!IsValidFuncType(funcType)) {
            return std::vector<NG::TransformInfo>();
        }

        std::string parameters = attr.substr(attr.find_first_of("(") + 1);
        if (parameters.empty()) {
            return std::vector<NG::TransformInfo>();
        }
        parameters = StringUtils::TrimStr(parameters);

        std::vector<std::string> paramVec;
        std::string tag = (parameters.find(",") != std::string::npos) ? "," : " ";
        StringUtils::SplitStr(parameters, tag, paramVec);
        if (paramVec.empty() || !IsLegalParam(paramVec)) {
            return std::vector<NG::TransformInfo>();
        }
        NG::TransformInfo transformInfo {funcType, paramVec};
        transformVec.push_back(transformInfo);
    }
    return transformVec;
}

SvgAlign SvgAttributesParser::ParseSvgAlign(const std::string& value)
{
    static const LinearMapNode<SvgAlign> SVG_ALIGN_ARRAY[] = {
        { SVG_ALIGN_NONE, SvgAlign::ALIGN_NONE },
        { SVG_ALIGN_XMAX_YMAX, SvgAlign::ALIGN_XMAX_YMAX },
        { SVG_ALIGN_XMAX_YMID, SvgAlign::ALIGN_XMAX_YMID },
        { SVG_ALIGN_XMAX_YMIN, SvgAlign::ALIGN_XMAX_YMIN },
        { SVG_ALIGN_XMID_YMAX, SvgAlign::ALIGN_XMID_YMAX },
        { SVG_ALIGN_XMID_YMID, SvgAlign::ALIGN_XMID_YMID },
        { SVG_ALIGN_XMID_YMIN, SvgAlign::ALIGN_XMID_YMIN },
        { SVG_ALIGN_XMIN_YMAX, SvgAlign::ALIGN_XMIN_YMAX },
        { SVG_ALIGN_XMIN_YMID, SvgAlign::ALIGN_XMIN_YMID },
        { SVG_ALIGN_XMIN_YMIN, SvgAlign::ALIGN_XMIN_YMIN },
    };
    auto attrIter = BinarySearchFindIndex(SVG_ALIGN_ARRAY, ArraySize(SVG_ALIGN_ARRAY), value.c_str());
    if (attrIter != -1) {
        return SVG_ALIGN_ARRAY[attrIter].value;
    }
    return SvgAlign::ALIGN_XMID_YMID;
}

SvgMeetOrSlice SvgAttributesParser::ParseSvgMeetOrSlice(const std::string& value)
{
    static const LinearMapNode<SvgMeetOrSlice> SVG_MEETORSLICE_ARRAY[] = {
        { SVG_ALIGN_MEET, SvgMeetOrSlice::MEET },
        { SVG_ALIGN_SLICE, SvgMeetOrSlice::SLICE },
    };
    auto attrIter = BinarySearchFindIndex(SVG_MEETORSLICE_ARRAY, ArraySize(SVG_MEETORSLICE_ARRAY), value.c_str());
    if (attrIter != -1) {
        return SVG_MEETORSLICE_ARRAY[attrIter].value;
    }
    return SvgMeetOrSlice::MEET;
}

void SvgAttributesParser::ComputeTranslate(const Size& viewBox, const Size& viewPort, const float scaleX,
    const float scaleY, const SvgAlign& svgAlign, float& translateX, float& translateY)
{
    translateX = 0.0f;
    translateY = 0.0f;
    switch (svgAlign) {
        /*translate x y eq 0.0f*/
        case SvgAlign::ALIGN_XMIN_YMIN:
            break;
        /*translate x eq 0.0f*/
        case SvgAlign::ALIGN_XMIN_YMID:
            translateY = (viewPort.Height() - viewBox.Height() * scaleY) * HALF_FLOAT;
            break;
        /*translate x eq 0.0f*/
        case SvgAlign::ALIGN_XMIN_YMAX:
            translateY = viewPort.Height() - viewBox.Height() * scaleY;
            break;
        /*translate y eq 0.0f*/
        case SvgAlign::ALIGN_XMID_YMIN:
            translateX = (viewPort.Width() - viewBox.Width() * scaleX) * HALF_FLOAT;
            break;
        case SvgAlign::ALIGN_XMID_YMAX:
            translateX = (viewPort.Width() - viewBox.Width() * scaleX) * HALF_FLOAT;
            translateY = viewPort.Height() - viewBox.Height() * scaleY;
            break;
        /*translate y eq 0.0f*/
        case SvgAlign::ALIGN_XMAX_YMIN:
            translateX = viewPort.Width() - viewBox.Width() * scaleX;
            break;
        case SvgAlign::ALIGN_XMAX_YMID:
            translateX = viewPort.Width() - viewBox.Width() * scaleX;
            translateY = (viewPort.Height() - viewBox.Height() * scaleY) * HALF_FLOAT;
            break;
        case SvgAlign::ALIGN_XMAX_YMAX:
            translateX = viewPort.Width() - viewBox.Width() * scaleX;
            translateY = viewPort.Height() - viewBox.Height() * scaleY;
            break;
        case SvgAlign::ALIGN_XMID_YMID:
        default:
            translateX = (viewPort.Width() - viewBox.Width() * scaleX) * HALF_FLOAT;
            translateY = (viewPort.Height() - viewBox.Height() * scaleY) * HALF_FLOAT;
            break;
    }
}

void SvgAttributesParser::ComputeScale(const Size& viewBox, const Size& viewPort,
    const SvgPreserveAspectRatio& preserveAspectRatio, float& scaleX, float& scaleY)
{
    if (!viewBox.IsValid()) {
        return;
    }
    float ratioX = viewPort.Width() / viewBox.Width();
    float ratioY = viewPort.Height() / viewBox.Height();
    if (preserveAspectRatio.svgAlign == SvgAlign::ALIGN_NONE) {
        scaleX = ratioX;
        scaleY = ratioY;
        return;
    }
    switch (preserveAspectRatio.meetOrSlice) {
        case SvgMeetOrSlice::SLICE:
            scaleX = std::max(ratioX, ratioY);
            break;
        case SvgMeetOrSlice::MEET:
        default:
            scaleX = std::min(ratioX, ratioY);
            break;
    }
    scaleY = scaleX;
}

Color SvgAttributesParser::GetColorFromHexString(const std::string& value)
{
    auto colorInt32 = std::strtoul(value.c_str(), nullptr, RADIX_HEX);
    auto red = (colorInt32 >> THREE_BYTE_BITS) & 0xff;
    auto green = (colorInt32 >> TWO_BYTE_BITS) & 0xff;
    auto blue = (colorInt32 >> ONE_BYTE_BITS) & 0xff;
    auto alpha = colorInt32 & 0xff;
    return Color::FromARGB(alpha, red, green, blue);
}

Color SvgAttributesParser::GetColorFrom4HexString(const std::string& value)
{
    // value is rgba, convert to rrggbbaa color
    auto colorInt32 = std::strtoul(value.c_str(), nullptr, RADIX_HEX);
    auto red = (colorInt32 >> TWELVE_BITS) & 0xf;
    red += red << FOUR_BITS;
    auto green = (colorInt32 >> ONE_BYTE_BITS) & 0xf;
    green += green << FOUR_BITS;
    auto blue = (colorInt32 >> FOUR_BITS) & 0xf;
    blue += blue << FOUR_BITS;
    auto alpha = colorInt32 & 0xf;
    alpha += alpha << FOUR_BITS;
    return Color::FromARGB(alpha, red, green, blue);
}
} // namespace OHOS::Ace::NG
