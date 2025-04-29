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

#include "frameworks/core/components_ng/svg/parse/svg_fe_composite.h"

#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {
namespace {
bool ConvertStrToSvgFeInType(const std::string& val, SvgFeInType& type)
{
    static const LinearMapNode<SvgFeInType> IN_TABLE[] = {
        { "BackgroundAlpha", SvgFeInType::BACKGROUND_ALPHA },
        { "BackgroundImage", SvgFeInType::BACKGROUND_IMAGE },
        { "FillPaint", SvgFeInType::FILL_PAINT },
        { "SourceAlpha", SvgFeInType::SOURCE_ALPHA },
        { "SourceGraphic", SvgFeInType::SOURCE_GRAPHIC },
        { "StrokePaint", SvgFeInType::STROKE_PAINT },
    };
    int64_t inIndex = BinarySearchFindIndex(IN_TABLE, ArraySize(IN_TABLE), val.c_str());
    if (inIndex != -1) {
        type = IN_TABLE[inIndex].value;
        return true;
    }
    return false;
}

bool ConvertStrToSvgFeOperatorType(const std::string& val, SvgFeOperatorType& type)
{
    static const LinearMapNode<SvgFeOperatorType> FE_OPERATOR_TABLE[] = {
        { "arithmetic", SvgFeOperatorType::FE_ARITHMETIC },
        { "atop", SvgFeOperatorType::FE_ATOP },
        { "in", SvgFeOperatorType::FE_IN },
        { "lighter", SvgFeOperatorType::FE_LIGHTER },
        { "out", SvgFeOperatorType::FE_OUT },
        { "over", SvgFeOperatorType::FE_OVER },
        { "xor", SvgFeOperatorType::FE_XOR },
    };
    int64_t inIndex = BinarySearchFindIndex(FE_OPERATOR_TABLE, ArraySize(FE_OPERATOR_TABLE), val.c_str());
    if (inIndex != -1) {
        type = FE_OPERATOR_TABLE[inIndex].value;
        return true;
    }
    return false;
}
}

RefPtr<SvgNode> SvgFeComposite::Create()
{
    return AceType::MakeRefPtr<SvgFeComposite>();
}

SvgFeComposite::SvgFeComposite() : SvgFe() {}

RSBlendMode SvgFeComposite::BlendModeForOperator(SvgFeOperatorType op) const
{
    switch (op) {
        case SvgFeOperatorType::FE_ATOP:
            return RSBlendMode::SRC_ATOP;
        case SvgFeOperatorType::FE_IN:
            return RSBlendMode::SRC_IN;
        case SvgFeOperatorType::FE_LIGHTER:
            return RSBlendMode::LIGHTEN;
        case SvgFeOperatorType::FE_OUT:
            return RSBlendMode::SRC_OUT;
        case SvgFeOperatorType::FE_OVER:
            return RSBlendMode::SRC_OVER;
        case SvgFeOperatorType::FE_XOR:
            return RSBlendMode::XOR;
        case SvgFeOperatorType::FE_ARITHMETIC:
            return RSBlendMode::SRC_OVER;
        default:
            return RSBlendMode::SRC_IN;
    };
}

void SvgFeComposite::OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter,
    const SvgColorInterpolationType& srcColor, SvgColorInterpolationType& currentColor,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash, bool cropRect) const
{
    auto mode = feCompositeAttr_.operatorType;
    auto foreImageFilter = MakeImageFilter(feAttr_.in, imageFilter, resultHash);
    auto backImageFilter = MakeImageFilter(feCompositeAttr_.in2, imageFilter, resultHash);
    RSRect filterRect(effectFilterArea_.Left(), effectFilterArea_.Top(),
                      effectFilterArea_.Right(), effectFilterArea_.Bottom());
    ConverImageFilterColor(foreImageFilter, srcColor, currentColor);
    ConverImageFilterColor(backImageFilter, srcColor, currentColor);
    if (mode != SvgFeOperatorType::FE_ARITHMETIC) {
        if (cropRect) {
            imageFilter = RSRecordingImageFilter::CreateBlendImageFilter(BlendModeForOperator(mode),
                backImageFilter, foreImageFilter, filterRect);
        } else {
            imageFilter = RSRecordingImageFilter::CreateBlendImageFilter(BlendModeForOperator(mode),
                backImageFilter, foreImageFilter);
        }
        ConverImageFilterColor(imageFilter, srcColor, currentColor);
        return;
    }
    std::vector<RSScalar> coefficients = { feCompositeAttr_.k1, feCompositeAttr_.k2, feCompositeAttr_.k3,
        feCompositeAttr_.k4 };
    if (cropRect) {
        imageFilter = RSRecordingImageFilter::CreateArithmeticImageFilter(coefficients, true, backImageFilter,
            foreImageFilter, filterRect);
    } else {
        imageFilter = RSRecordingImageFilter::CreateArithmeticImageFilter(coefficients, true, backImageFilter,
            foreImageFilter);
    }
    ConverImageFilterColor(imageFilter, srcColor, currentColor);
    RegisterResult(feAttr_.result, imageFilter, resultHash);
}

bool SvgFeComposite::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgFeCompositeAttribute&)> attrs[] = {
        { SVG_FE_IN2,
            [](const std::string& val, SvgFeCompositeAttribute& attribute) {
                SvgFeInType type = SvgFeInType::PRIMITIVE;
                bool res = ConvertStrToSvgFeInType(val, type);
                if (res) {
                    attribute.in2.in = type;
                } else {
                    attribute.in2.id = val;
                }
            } },
        { SVG_FE_K1,
            [](const std::string& val, SvgFeCompositeAttribute& attr) {
                attr.k1 = SvgAttributesParser::ParseDouble(val);
            } },
        { SVG_FE_K2,
            [](const std::string& val, SvgFeCompositeAttribute& attr) {
                attr.k2 = SvgAttributesParser::ParseDouble(val);
            } },
        { SVG_FE_K3,
            [](const std::string& val, SvgFeCompositeAttribute& attr) {
                attr.k3 = SvgAttributesParser::ParseDouble(val);
            } },
        { SVG_FE_K4,
            [](const std::string& val, SvgFeCompositeAttribute& attr) {
                attr.k4 = SvgAttributesParser::ParseDouble(val);
            } },
        { SVG_FE_OPERATOR_TYPE,
            [](const std::string& val, SvgFeCompositeAttribute& attr) {
                SvgFeOperatorType type = SvgFeOperatorType::FE_OVER;
                bool res = ConvertStrToSvgFeOperatorType(val, type);
                if (res) {
                    attr.operatorType = type;
                }
            } },
    };
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), name.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, feCompositeAttr_);
        return true;
    }
    return SvgFe::ParseAndSetSpecializedAttr(name, value);
}

} // namespace OHOS::Ace::NG
