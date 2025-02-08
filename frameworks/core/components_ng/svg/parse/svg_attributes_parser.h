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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_ATTRIBUTES_PARSER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_ATTRIBUTES_PARSER_H

#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components/common/properties/svg_paint_state.h"
#include "core/components_ng/svg/base/svg_length_scale_rule.h"

namespace OHOS::Ace::NG {
struct TransformInfo;

enum class SvgAlign {
    ALIGN_XMIN_YMIN,
    ALIGN_XMIN_YMID,
    ALIGN_XMIN_YMAX,
    ALIGN_XMID_YMIN,
    ALIGN_XMID_YMID,
    ALIGN_XMID_YMAX,
    ALIGN_XMAX_YMIN,
    ALIGN_XMAX_YMID,
    ALIGN_XMAX_YMAX,
    ALIGN_NONE,
};

enum class SvgMeetOrSlice {
    MEET,
    SLICE,
};

struct SvgPreserveAspectRatio {
    SvgAlign svgAlign = SvgAlign::ALIGN_XMID_YMID;
    SvgMeetOrSlice meetOrSlice = SvgMeetOrSlice::MEET;
};

class SvgAttributesParser {
public:
    static Color GetColor(const std::string& str);
    static bool ParseColor(std::string value, Color& color);
    static bool ParseRGBAMagicColor(const std::string& value, Color& color);
    static std::optional<Color> GetSpecialColor(const std::string& value);
    static LineCapStyle GetLineCapStyle(const std::string& val);
    static LineJoinStyle GetLineJoinStyle(const std::string& val);
    static Dimension ParseDimension(const std::string& value, bool useVp = false);
    static double ParseDouble(const std::string& value);
    static bool CheckColorAlpha(const std::string& colorStr, Color& result);
    static std::pair<Dimension, Dimension> GetTransformOrigin(const std::string& transformOrigin);
    static std::vector<NG::TransformInfo> GetTransformInfo(const std::string& transform);
    static SvgAlign ParseSvgAlign(const std::string& value);
    static SvgMeetOrSlice ParseSvgMeetOrSlice(const std::string& value);
    static void ComputeTranslate(const Size& viewBox, const Size& viewPort, const float scaleX, const float scaleY,
        const SvgAlign& svgAlign, float& translateX, float& translateY);
    static void ComputeScale(const Size& viewBox, const Size& viewPort,
        const SvgPreserveAspectRatio& preserveAspectRatio, float& scaleX, float& scaleY);
};
enum class SvgFeColorMatrixType {
    MATRIX,
    SATURATE,
    HUE_ROTATE,
    LUMINACE_TO_ALPHA,
};

enum class SvgColorInterpolationType {
    LINEAR_RGB,
    SRGB,
    AUTO
};

enum class SvgFeInType {
    SOURCE_GRAPHIC,
    SOURCE_ALPHA,
    BACKGROUND_IMAGE,
    BACKGROUND_ALPHA,
    FILL_PAINT,
    STROKE_PAINT,
    PRIMITIVE
};

enum class SvgFeEdgeMode {
    EDGE_DUPLICATE,
    EDGE_WRAP,
    EDGE_NONE
};

enum class SvgFeOperatorType {
    FE_ARITHMETIC,
    FE_ATOP,
    FE_IN,
    FE_LIGHTER,
    FE_OUT,
    FE_OVER,
    FE_XOR
};

enum class SvgFeBlendMode {
    NORMAL,
    MULTIPLY,
    SCREEN,
    DARKEN,
    LIGHTEN
};

struct SvgFeIn {
    SvgFeInType in = SvgFeInType::PRIMITIVE;
    std::string id;
};

struct SvgAttributes {
    Rect viewBox;
    Dimension x;
    Dimension y;
    Dimension width = -1.0_px;
    Dimension height = -1.0_px;
    bool autoMirror = false;
    SvgPreserveAspectRatio preserveAspectRatio;
};

struct TransformInfo {
    std::string funcType;
    std::vector<std::string> paramVec;
};

enum SvgRuleType {
    SVG_RULE_NONEZERO = 0,
    SVG_RULE_EVENODD
};

constexpr float HALF_FLOAT = 0.5f;
class SvgClipAttribute {
public:
    SvgClipAttribute() = default;
    ~SvgClipAttribute() = default;
    const SvgRuleType& GetClipRule() const
    {
        return clipRule_;
    }

    bool IsEvenodd() const
    {
        return clipRule_ == SvgRuleType::SVG_RULE_EVENODD;
    }

    void SetClipRule(const SvgRuleType& clipRule, bool isSelf = true)
    {
        clipRule_ = clipRule;
        hasClipRule_ = isSelf;
    }

    const std::string& GetHref() const
    {
        return href_;
    }

    void SetHref(const std::string& href, bool isSelf = true)
    {
        href_ = href;
        hasHref_ = isSelf;
    }

    SvgLengthScaleUnit GetClipPathUnits() const
    {
        return clipPathUnits_;
    }

    void SetClipPathUnits(SvgLengthScaleUnit clipPathUnits, bool isSelf = true)
    {
        clipPathUnits_ = clipPathUnits;
        hasClipPathUnits_ = isSelf;
    }

    void Inherit(const SvgClipAttribute& svgClipAttribute)
    {
        if (!hasHref_) {
            href_ = svgClipAttribute.GetHref();
        }
        if (!hasClipRule_) {
            clipRule_ = svgClipAttribute.GetClipRule();
        }
        if (!hasClipPathUnits_) {
            clipPathUnits_ = svgClipAttribute.GetClipPathUnits();
        }
    }
private:
    std::string href_;
    SvgRuleType clipRule_ = SvgRuleType::SVG_RULE_NONEZERO;
    SvgLengthScaleUnit clipPathUnits_ = SvgLengthScaleUnit::USER_SPACE_ON_USE;
    bool hasHref_ = false;
    bool hasClipRule_ = false;
    bool hasClipPathUnits_ = false;
};

struct SvgBaseAttribute {
    bool hasOpacity = false;
    double opacity = 1.0;
    FillState fillState;
    StrokeState strokeState;
    SvgTextStyle textStyle;
    std::string transform;
    std::vector<NG::TransformInfo> transformVec;
    std::pair<Dimension, Dimension> transformOrigin;
    std::string filterId;
    std::string maskId;
    std::string href;
    std::string id;
    SvgClipAttribute clipState;

    void InheritFromUse(const SvgBaseAttribute& parent)
    {
        if (!hasOpacity) {
            if (parent.hasOpacity) {
                fillState.SetOpacity(parent.opacity);
                opacity = parent.opacity;
            } else {
                opacity = 1.0; // default opacity is 1.0
            }
        }
        fillState.Inherit(parent.fillState);
        strokeState.Inherit(parent.strokeState);
        clipState.Inherit(parent.clipState);
    }

    void Inherit(const SvgBaseAttribute& parent)
    {
        if (!hasOpacity) {
            if (parent.hasOpacity) {
                opacity = parent.opacity;
                hasOpacity = true;
            } else {
                opacity = 1.0; // default opacity is 1.0
            }
        }
        fillState.Inherit(parent.fillState);
        strokeState.Inherit(parent.strokeState);
        clipState.Inherit(parent.clipState);
    }
};


struct SvgAnimateAttribute {
    std::string attributeName;
    int32_t begin = 0;
    int32_t dur = 0;
    int32_t end = 0;
    int32_t repeatCount = 1;
    std::string fillMode;
    std::string calcMode;
    std::vector<std::string> values;
    std::vector<double> keyTimes;
    std::vector<std::string> keySplines;
    std::string from;
    std::string to;
    std::vector<std::string> keyPoints;
    std::string path;
    std::string rotate;
    std::string transformType;
};

struct SvgStopAttribute {
    GradientColor gradientColor;
};

struct SvgRectAttribute {
    Dimension x;
    Dimension y;
    Dimension rx = -1.0_px;
    Dimension ry = -1.0_px;
    Dimension width;
    Dimension height;
};

struct SvgMaskAttribute {
    Dimension x = Dimension(-0.1, DimensionUnit::PERCENT); // x-axis default value
    Dimension y = Dimension(-0.1, DimensionUnit::PERCENT); // y-axis default value
    Dimension width = Dimension(1.2, DimensionUnit::PERCENT); // masking area width default value
    Dimension height = Dimension(1.2, DimensionUnit::PERCENT); // masking area height default value
    SvgLengthScaleUnit maskContentUnits = SvgLengthScaleUnit::USER_SPACE_ON_USE;
    SvgLengthScaleUnit maskUnits = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
};

struct SvgCircleAttribute {
    Dimension cx;
    Dimension cy;
    Dimension r;
};

struct SvgPolygonAttribute {
    std::string points;
};

struct SvgEllipseAttribute {
    Dimension cx;
    Dimension cy;
    Dimension rx = -1.0_px;
    Dimension ry = -1.0_px;
};

struct SvgLineAttribute {
    Dimension x1;
    Dimension y1;
    Dimension x2;
    Dimension y2;
};

struct SvgPatternAttribute {
    Dimension x; // x-axis default value
    Dimension y; // y-axis default value
    Dimension width; // pattern area width default value
    Dimension height; // pattern area height default value
    SvgLengthScaleUnit patternUnits = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    SvgLengthScaleUnit patternContentUnits = SvgLengthScaleUnit::USER_SPACE_ON_USE;
    std::string patternTransform;
    Rect viewBox;
};

struct SvgImageAttribute {
    Dimension x = Dimension(0, DimensionUnit::PX); // x-axis default value
    Dimension y = Dimension(0, DimensionUnit::PX); // y-axis default value
    Dimension width = Dimension(0.0, DimensionUnit::PX); // image width default value
    Dimension height = Dimension(0.0, DimensionUnit::PX); // image height default value
    std::string href = "";
};

struct SvgFilterAttribute {
    Dimension x = Dimension(-0.1, DimensionUnit::PERCENT); // x-axis default value
    Dimension y = Dimension(-0.1, DimensionUnit::PERCENT); // y-axis default value
    Dimension width = Dimension(1.2, DimensionUnit::PERCENT); // masking area width default value
    Dimension height = Dimension(1.2, DimensionUnit::PERCENT); // masking area height default value
    SvgLengthScaleUnit filterUnits = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    SvgLengthScaleUnit primitiveUnits = SvgLengthScaleUnit::USER_SPACE_ON_USE;
};

struct SvgFeCommonAttribute {
    Dimension x = Dimension(0.0, DimensionUnit::PERCENT);
    Dimension y = Dimension(0.0, DimensionUnit::PERCENT);
    Dimension height = Dimension(1.0, DimensionUnit::PERCENT);
    Dimension width = Dimension(1.0, DimensionUnit::PERCENT);
    std::string result;
    SvgFeIn in;
    SvgColorInterpolationType colorInterpolationType = SvgColorInterpolationType::SRGB;
    std::optional<bool> isWidthValid;
    std::optional<bool> isHeightValid;
};

struct SvgFeFloodAttribute {
    Color floodColor = Color::BLACK;
    double floodOpacity = 1.0;
};

struct SvgFeGaussianBlurAttribute {
    float stdDeviationX = 0.0f;
    float stdDeviationY = 0.0f;
    SvgFeEdgeMode edgeMode = SvgFeEdgeMode::EDGE_DUPLICATE;
};

struct SvgFeOffsetAttribute {
    Dimension dx;
    Dimension dy;
};

struct SvgFeCompositeAttribute {
    SvgFeIn in2;
    SvgFeOperatorType operatorType = SvgFeOperatorType::FE_OVER;
    float k1 = 0.0f;
    float k2 = 0.0f;
    float k3 = 0.0f;
    float k4 = 0.0f;
};

struct SvgFeBlendAttribute {
    SvgFeIn in2;
    SvgFeBlendMode blendMode = SvgFeBlendMode::NORMAL;
};

struct SvgFeColorMatrixAttribute {
    SvgFeColorMatrixType type = SvgFeColorMatrixType::MATRIX;
    std::string values;
};

enum class SvgSpreadMethod {
    PAD = 0,
    REPEAT,
    REFLECT,
};

struct SvgLinearGradientInfo {
    float x1;
    float x2;
    float y1;
    float y2;
    int32_t spreadMethod;
    std::string gradientTransform;
    std::vector<GradientColor> colors;
};

struct SvgLinearGradientAttribute {
    Dimension x1 = Dimension(0.0, DimensionUnit::PERCENT);
    Dimension y1 = Dimension(0.0, DimensionUnit::PERCENT);
    Dimension x2 = Dimension(1.0, DimensionUnit::PERCENT);
    Dimension y2 = Dimension(0.0, DimensionUnit::PERCENT);
    std::string gradientTransform;
    SvgLengthScaleUnit gradientUnits = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    SvgSpreadMethod spreadMethod = SvgSpreadMethod::PAD;
};

struct SvgRadialGradientInfo {
    float cx;
    float cy;
    float r;
    float fx;
    float fy;
    int32_t spreadMethod;
    std::string gradientTransform;
    std::vector<GradientColor> colors;
};
struct SvgRadialGradientAttribute {
    Dimension cx = Dimension(HALF_FLOAT, DimensionUnit::PERCENT);
    Dimension cy = Dimension(HALF_FLOAT, DimensionUnit::PERCENT);
    Dimension r = Dimension(HALF_FLOAT, DimensionUnit::PERCENT);
    std::optional<Dimension> fx;
    std::optional<Dimension> fy;
    std::string gradientTransform;
    SvgLengthScaleUnit gradientUnits = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    SvgSpreadMethod spreadMethod = SvgSpreadMethod::PAD;
};

struct SvgGradientAttribute {
    Gradient gradient = Gradient();
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_ATTRIBUTES_PARSER_H