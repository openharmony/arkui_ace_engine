/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/svg/parse/svg_gradient.h"

#include "frameworks/core/components_ng/svg/parse/svg_constants.h"
#include "frameworks/core/components_ng/svg/parse/svg_stop.h"

namespace OHOS::Ace::NG {
namespace {
const char DOM_SVG_SRC_GRADIENT_TRANSFORM[] = "gradientTransform";
const char DOM_SVG_SRC_SPREAD_METHOD[] = "spreadMethod"; 
}

SvgGradient::SvgGradient(GradientType gradientType)
{
    gradientAttr_.gradient.SetType(gradientType);
    InitNoneFlag();
}

RefPtr<SvgNode> SvgGradient::CreateLinearGradient()
{
    return AceType::MakeRefPtr<SvgGradient>(GradientType::LINEAR);
}

RefPtr<SvgNode> SvgGradient::CreateRadialGradient()
{
    return AceType::MakeRefPtr<SvgGradient>(GradientType::RADIAL);
}

void SvgGradient::SetAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgGradientAttribute&)> GRADIENT_ATTRS[] = {
        { SVG_CX,
            [](const std::string& val, SvgGradientAttribute& attr) {
                attr.gradient.GetRadialGradient().radialCenterX = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_CY,
            [](const std::string& val, SvgGradientAttribute& attr) {
                attr.gradient.GetRadialGradient().radialCenterY = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_FX,
            [](const std::string& val, SvgGradientAttribute& attr) {
                attr.gradient.GetRadialGradient().fRadialCenterX = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_FY,
            [](const std::string& val, SvgGradientAttribute& attr) {
                attr.gradient.GetRadialGradient().fRadialCenterY = SvgAttributesParser::ParseDimension(val);
            } },
        { DOM_SVG_SRC_GRADIENT_TRANSFORM, SetGradientTransform }, { SVG_GRADIENT_TRANSFORM, SetGradientTransform },
        { SVG_R,
            [](const std::string& val, SvgGradientAttribute& attr) {
                auto r = SvgAttributesParser::ParseDimension(val);
                attr.gradient.GetRadialGradient().radialHorizontalSize = r;
                attr.gradient.GetRadialGradient().radialVerticalSize = r;
            } },
        { DOM_SVG_SRC_SPREAD_METHOD, SetSpreadMethod }, { SVG_SPREAD_METHOD, SetSpreadMethod },
        { SVG_X1,
            [](const std::string& val, SvgGradientAttribute& attr) {
                attr.gradient.GetLinearGradient().x1 = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_X2,
            [](const std::string& val, SvgGradientAttribute& attr) {
                attr.gradient.GetLinearGradient().x2 = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_Y1,
            [](const std::string& val, SvgGradientAttribute& attr) {
                attr.gradient.GetLinearGradient().y1 = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_Y2,
            [](const std::string& val, SvgGradientAttribute& attr) {
                attr.gradient.GetLinearGradient().y2 = SvgAttributesParser::ParseDimension(val);
            } },
    };
    auto attrIter = BinarySearchFindIndex(GRADIENT_ATTRS, ArraySize(GRADIENT_ATTRS), name.c_str());
    if (attrIter != -1) {
        GRADIENT_ATTRS[attrIter].value(value, gradientAttr_);
    }
}

void SvgGradient::SetGradientTransform(const std::string& val, SvgGradientAttribute& attr)
{
    attr.gradient.SetGradientTransform(val);
}

void SvgGradient::SetSpreadMethod(const std::string& val, SvgGradientAttribute& attr)
{
    if (val == "pad") {
        attr.gradient.SetSpreadMethod(GradientSpreadMethodNG::PAD);
    }
    if (val == "reflect") {
        attr.gradient.SetSpreadMethod(GradientSpreadMethodNG::REFLECT);
    }
    if (val == "repeat") {
        attr.gradient.SetSpreadMethod(GradientSpreadMethodNG::REPEAT);
    }
}

void SvgGradient::OnAppendChild(const RefPtr<SvgNode>& child)
{
    auto svgStop = AceType::DynamicCast<SvgStop>(child);
    CHECK_NULL_VOID(svgStop);
    gradientAttr_.gradient.AddColor(svgStop->GetGradientColor());
}

const Gradient& SvgGradient::GetGradient() const
{
    return gradientAttr_.gradient;
}

} // namespace OHOS::Ace::NG
