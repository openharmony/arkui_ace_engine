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

#include "frameworks/core/components_ng/svg/parse/svg_fe_gaussian_blur.h"

#include "include/effects/SkImageFilters.h"

#include "base/utils/utils.h"
#include "frameworks/core/components/declaration/svg/svg_fe_gaussianblur_declaration.h"

namespace OHOS::Ace::NG {
namespace {
std::vector<double> ParseVecDouble(const std::string& value)
{
    if (value.empty()) {
        return {};
    }
    std::vector<double> parsedValues;
    StringUtils::StringSplitter(value, ' ', parsedValues);
    if (parsedValues.empty()) {
        StringUtils::StringSplitter(value, ',', parsedValues);
    }
    return parsedValues;
}
};

RefPtr<SvgNode> SvgFeGaussianBlur::Create()
{
    return AceType::MakeRefPtr<SvgFeGaussianBlur>();
}

SvgFeGaussianBlur::SvgFeGaussianBlur() : SvgFe() {}

void SvgFeGaussianBlur::OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter,
    const SvgColorInterpolationType& srcColor, SvgColorInterpolationType& currentColor,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash) const
{
    imageFilter = MakeImageFilter(feAttr_.in, imageFilter, resultHash);
    imageFilter = RSRecordingImageFilter::CreateBlurImageFilter(
        gaussianBlurAttr_.stdDeviationX, gaussianBlurAttr_.stdDeviationY, RSTileMode::DECAL, imageFilter);
    ConverImageFilterColor(imageFilter, srcColor, currentColor);
    RegisterResult(feAttr_.result, imageFilter, resultHash);
}

bool SvgFeGaussianBlur::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgFeGaussianBlurAttribute&)> attrs[] = {
        { DOM_SVG_FE_EDGE_MODE, [](const std::string& val, SvgFeGaussianBlurAttribute& attr) { 
            static const LinearMapNode<SvgFeEdgeMode> EDGE_MODE_TABLE[] = {
                { "duplicate", SvgFeEdgeMode::EDGE_DUPLICATE },
                { "none", SvgFeEdgeMode::EDGE_NONE },
                { "wrap", SvgFeEdgeMode::EDGE_WRAP },
            };
            int64_t inIndex = BinarySearchFindIndex(EDGE_MODE_TABLE, ArraySize(EDGE_MODE_TABLE), val.c_str());
            if (inIndex != -1) {
                attr.edgeMode = EDGE_MODE_TABLE[inIndex].value;
            }
        } },
        { DOM_SVG_FE_STD_DEVIATION, [](const std::string& val, SvgFeGaussianBlurAttribute& attr) {
            auto vectorRes = ParseVecDouble(val);
            if (vectorRes.empty() || vectorRes.size() > 2) {
                return;
            }
            attr.stdDeviationX = vectorRes[0];
            attr.stdDeviationY = vectorRes.size() > 1 ? vectorRes[1] : vectorRes[0];
        } },
    };
    std::string key = name;
    StringUtils::TransformStrCase(key, StringUtils::TEXT_CASE_LOWERCASE);
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), key.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, gaussianBlurAttr_);
        return true;
    }
    return SvgFe::ParseAndSetSpecializedAttr(name, value);
}

} // namespace OHOS::Ace::NG
