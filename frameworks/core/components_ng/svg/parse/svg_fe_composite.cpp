/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "include/effects/SkImageFilters.h"

#include "base/utils/utils.h"
#include "core/components/common/properties/blend_mode.h"

namespace OHOS::Ace::NG {

RefPtr<SvgNode> SvgFeComposite::Create()
{
    return AceType::MakeRefPtr<SvgFeComposite>();
}

SvgFeComposite::SvgFeComposite() : SvgFe()
{
    declaration_ = AceType::MakeRefPtr<SvgFeCompositeDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

RSBlendMode SvgFeComposite::BlendModeForOperator(FeOperatorType op) const
{
    switch (op) {
        case FeOperatorType::FE_ATOP:
            return RSBlendMode::SRC_ATOP;
        case FeOperatorType::FE_IN:
            return RSBlendMode::SRC_IN;
        case FeOperatorType::FE_LIGHTER:
            return RSBlendMode::LIGHTEN;
        case FeOperatorType::FE_OUT:
            return RSBlendMode::SRC_OUT;
        case FeOperatorType::FE_OVER:
            return RSBlendMode::SRC_OVER;
        case FeOperatorType::FE_XOR:
            return RSBlendMode::XOR;
        case FeOperatorType::FE_ARITHMETIC:
            return RSBlendMode::SRC_OVER;
        default:
            return RSBlendMode::SRC_IN;
    };
}

void SvgFeComposite::OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter,
    const ColorInterpolationType& srcColor, ColorInterpolationType& currentColor,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash) const
{
    auto declaration = AceType::DynamicCast<SvgFeCompositeDeclaration>(declaration_);
    CHECK_NULL_VOID(declaration);
    auto mode = declaration->GetOperatorType();
    auto foreImageFilter = MakeImageFilter(declaration->GetIn(), imageFilter, resultHash);
    auto backImageFilter = MakeImageFilter(declaration->GetIn2(), imageFilter, resultHash);
    ConverImageFilterColor(foreImageFilter, srcColor, currentColor);
    ConverImageFilterColor(backImageFilter, srcColor, currentColor);
    if (mode != FeOperatorType::FE_ARITHMETIC) {
        imageFilter = RSRecordingImageFilter::CreateBlendImageFilter(
            BlendModeForOperator(mode), backImageFilter, foreImageFilter);
        ConverImageFilterColor(imageFilter, srcColor, currentColor);
        return;
    }
    std::vector<RSScalar> coefficients = { declaration->GetK1(), declaration->GetK2(), declaration->GetK3(),
        declaration->GetK4() };
    imageFilter =
        RSRecordingImageFilter::CreateArithmeticImageFilter(coefficients, true, backImageFilter, foreImageFilter);
    ConverImageFilterColor(imageFilter, srcColor, currentColor);
    RegisterResult(declaration->GetResult(), imageFilter, resultHash);
}

} // namespace OHOS::Ace::NG
