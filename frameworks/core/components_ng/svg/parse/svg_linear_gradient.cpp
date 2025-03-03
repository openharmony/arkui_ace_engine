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

#include "core/components_ng/svg/parse/svg_linear_gradient.h"

#include "core/common/container.h"
#include "frameworks/core/components_ng/svg/parse/svg_constants.h"
#include "frameworks/core/components_ng/svg/parse/svg_stop.h"

namespace OHOS::Ace::NG {
RefPtr<SvgNode> SvgLinearGradient::Create()
{
    return AceType::MakeRefPtr<SvgLinearGradient>();
}

void SvgLinearGradient::SetAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgLinearGradientAttribute&)> LINEAR_GRADIENT_ATTRS[] = {
        { SVG_GRADIENT_TRANSFORM, [](const std::string& val, SvgLinearGradientAttribute& attr) {
                attr.gradientTransform = val;
            }  },
        { SVG_GRADIENT_UNITS, [](const std::string& val, SvgLinearGradientAttribute& attr) {
                attr.gradientUnits = (val == "userSpaceOnUse") ? SvgLengthScaleUnit::USER_SPACE_ON_USE :
                    SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
            }  },
        { SVG_SPREAD_METHOD, [](const std::string& val, SvgLinearGradientAttribute& attr) {
                attr.spreadMethod = SvgGradient::ParseSpreadMethod(val);
            }  },
        { SVG_X1,
            [](const std::string& val, SvgLinearGradientAttribute& attr) {
                attr.x1 = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_X2,
            [](const std::string& val, SvgLinearGradientAttribute& attr) {
                attr.x2 = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_Y1,
            [](const std::string& val, SvgLinearGradientAttribute& attr) {
                attr.y1 = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_Y2,
            [](const std::string& val, SvgLinearGradientAttribute& attr) {
                attr.y2 = SvgAttributesParser::ParseDimension(val);
            } },
    };
    std::string key = name;
    StringUtils::TransformStrCase(key, StringUtils::TEXT_CASE_LOWERCASE);
    auto attrIter = BinarySearchFindIndex(LINEAR_GRADIENT_ATTRS, ArraySize(LINEAR_GRADIENT_ATTRS), key.c_str());
    if (attrIter != -1) {
        LINEAR_GRADIENT_ATTRS[attrIter].value(value, linearGradientAttr_);
    }
}

SvgLinearGradientInfo SvgLinearGradient::GetLinearGradientInfo(
    const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    Rect defaultRect(0, 0, 1, 1);
    SvgLengthScaleRule gradientRule =
        linearGradientAttr_.gradientUnits == SvgLengthScaleUnit::OBJECT_BOUNDING_BOX ?
        SvgLengthScaleRule(defaultRect, SvgLengthScaleUnit::OBJECT_BOUNDING_BOX) :
        svgCoordinateSystemContext.BuildScaleRule(SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto measuredX1 = GetMeasuredPosition(linearGradientAttr_.x1, gradientRule, SvgLengthType::HORIZONTAL);
    auto measuredY1 = GetMeasuredPosition(linearGradientAttr_.y1, gradientRule, SvgLengthType::VERTICAL);
    auto measuredX2 = GetMeasuredPosition(linearGradientAttr_.x2, gradientRule, SvgLengthType::HORIZONTAL);
    auto measuredY2 = GetMeasuredPosition(linearGradientAttr_.y2, gradientRule, SvgLengthType::VERTICAL);
    return {
        .x1 = measuredX1, .x2 = measuredX2, .y1 = measuredY1, .y2 = measuredY2,
        .spreadMethod = static_cast<int32_t>(linearGradientAttr_.spreadMethod),
        .gradientTransform = linearGradientAttr_.gradientTransform, .colors = GetStopColors()
    };
}

SvgLengthScaleUnit SvgLinearGradient::GradientUnits()
{
    return linearGradientAttr_.gradientUnits;
}
} // namespace OHOS::Ace::NG
