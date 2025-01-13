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

#include "core/components_ng/svg/parse/svg_radial_gradient.h"

#include "core/common/container.h"
#include "frameworks/core/components_ng/svg/parse/svg_constants.h"
#include "frameworks/core/components_ng/svg/parse/svg_stop.h"

namespace OHOS::Ace::NG {
RefPtr<SvgNode> SvgRadialGradient::Create()
{
    return AceType::MakeRefPtr<SvgRadialGradient>();
}

void SvgRadialGradient::SetAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgRadialGradientAttribute&)> RADIAL_GRADIENT_ATTRS[] = {
        { SVG_CX,
            [](const std::string& val, SvgRadialGradientAttribute& attr) {
                attr.cx = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_CY,
            [](const std::string& val, SvgRadialGradientAttribute& attr) {
                attr.cy = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_FX,
            [](const std::string& val, SvgRadialGradientAttribute& attr) {
                attr.fx = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_FY,
            [](const std::string& val, SvgRadialGradientAttribute& attr) {
                attr.fy = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_GRADIENT_TRANSFORM, [](const std::string& val, SvgRadialGradientAttribute& attr) {
                attr.gradientTransform = val;
            }  },
        { SVG_GRADIENT_UNITS, [](const std::string& val, SvgRadialGradientAttribute& attr) {
                attr.gradientUnits = (val == "userSpaceOnUse") ? SvgLengthScaleUnit::USER_SPACE_ON_USE :
                    SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
            }  },
        { SVG_R,
            [](const std::string& val, SvgRadialGradientAttribute& attr) {
                attr.r = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_SPREAD_METHOD, [](const std::string& val, SvgRadialGradientAttribute& attr) {
                attr.spreadMethod = SvgGradient::ParseSpreadMethod(val);
            } },
    };
    std::string key = name;
    StringUtils::TransformStrCase(key, StringUtils::TEXT_CASE_LOWERCASE);
    auto attrIter = BinarySearchFindIndex(RADIAL_GRADIENT_ATTRS, ArraySize(RADIAL_GRADIENT_ATTRS), key.c_str());
    if (attrIter != -1) {
        RADIAL_GRADIENT_ATTRS[attrIter].value(value, radialGradientAttr_);
    }
}

SvgRadialGradientInfo SvgRadialGradient::GetRadialGradientInfo(
    const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    auto gradientRule = svgCoordinateSystemContext.BuildScaleRule(radialGradientAttr_.gradientUnits);
    auto cx = GetMeasuredPosition(radialGradientAttr_.cx, gradientRule, SvgLengthType::HORIZONTAL);
    auto cy = GetMeasuredPosition(radialGradientAttr_.cy, gradientRule, SvgLengthType::VERTICAL);
    auto r = GetMeasuredLength(radialGradientAttr_.r, gradientRule, SvgLengthType::OTHER);
    auto fx = GetMeasuredPosition(radialGradientAttr_.fx.value_or(radialGradientAttr_.cx), gradientRule,
        SvgLengthType::HORIZONTAL);
    auto fy = GetMeasuredPosition(radialGradientAttr_.fy.value_or(radialGradientAttr_.cy), gradientRule,
        SvgLengthType::VERTICAL);
    TAG_LOGD(AceLogTag::ACE_IMAGE, "cx:%{public}lf, cy:%{public}lf, r:%{public}lf, fx:%{public}lf, fy:%{public}lf",
        cx, cy, r, fx, fy);
    return { .cx = cx, .cy = cy, .r = r, .fx = fx, .fy = fy,
        .spreadMethod =static_cast<int32_t>(radialGradientAttr_.spreadMethod),
        .gradientTransform = radialGradientAttr_.gradientTransform, .colors = GetStopColors()};
}
} // namespace OHOS::Ace::NG
