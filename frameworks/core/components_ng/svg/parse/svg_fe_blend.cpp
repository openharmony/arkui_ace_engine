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

#include "core/components_ng/svg/parse/svg_fe_blend.h"

#include "base/utils/utils.h"

namespace OHOS::Ace::NG {

RefPtr<SvgNode> SvgFeBlend::Create()
{
    return AceType::MakeRefPtr<SvgFeBlend>();
}

SvgFeBlend::SvgFeBlend() : SvgFe()
{
    declaration_ = AceType::MakeRefPtr<SvgFeBlendDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

RSBlendMode SvgFeBlend::GetBlendMode(FeBlendMode mode) const
{
    switch (mode) {
        case FeBlendMode::NORMAL:
            return RSBlendMode::SRC_OVER;
        case FeBlendMode::MULTIPLY:
            return RSBlendMode::MULTIPLY;
        case FeBlendMode::SCREEN:
            return RSBlendMode::SCREEN;
        case FeBlendMode::DARKEN:
            return RSBlendMode::DARKEN;
        case FeBlendMode::LIGHTEN:
            return RSBlendMode::LIGHTEN;
        default:
            return RSBlendMode::SRC_OVER;
    };
}

void SvgFeBlend::OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter, const ColorInterpolationType& srcColor,
    ColorInterpolationType& currentColor,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash) const
{
    auto declaration = AceType::DynamicCast<SvgFeBlendDeclaration>(declaration_);
    CHECK_NULL_VOID(declaration);
    auto blendMode = declaration->GetBlendMode();

    auto backImageFilter = MakeImageFilter(declaration->GetIn2(), imageFilter, resultHash);
    auto foreImageFilter = MakeImageFilter(declaration->GetIn(), imageFilter, resultHash);
    ConverImageFilterColor(foreImageFilter, srcColor, currentColor);
    ConverImageFilterColor(backImageFilter, srcColor, currentColor);

    imageFilter =
        RSRecordingImageFilter::CreateBlendImageFilter(GetBlendMode(blendMode), backImageFilter, foreImageFilter);
    ConverImageFilterColor(imageFilter, srcColor, currentColor);
    RegisterResult(declaration->GetResult(), imageFilter, resultHash);
}

} // namespace OHOS::Ace::NG
