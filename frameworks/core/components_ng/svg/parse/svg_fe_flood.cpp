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

#include "core/components_ng/svg/parse/svg_fe_flood.h"

#include "2d_graphics/include/effect/shader_effect.h"

#include "base/utils/utils.h"
#include "core/components/declaration/svg/svg_fe_flood_declaration.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {

RefPtr<SvgNode> SvgFeFlood::Create()
{
    return AceType::MakeRefPtr<SvgFeFlood>();
}

SvgFeFlood::SvgFeFlood() : SvgFe()
{
    declaration_ = AceType::MakeRefPtr<SvgFeFloodDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

void SvgFeFlood::OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter, const ColorInterpolationType& srcColor,
    ColorInterpolationType& currentColor,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash) const
{
    auto declaration = AceType::DynamicCast<SvgFeFloodDeclaration>(declaration_);
    CHECK_NULL_VOID(declaration);
    imageFilter = MakeImageFilter(declaration->GetIn(), imageFilter, resultHash);

    auto floodColor = declaration->GetFloodColor();
    auto floodOpacity = declaration->GetFloodOpacity();

    floodColor = floodColor.ChangeOpacity(floodOpacity);
    auto shaderFilter = RSRecordingShaderEffect::CreateColorShader(floodColor.GetValue());
    CHECK_NULL_VOID(shaderFilter);
    imageFilter = RSRecordingImageFilter::CreateShaderImageFilter(shaderFilter);

    ConverImageFilterColor(imageFilter, srcColor, currentColor);
    RegisterResult(declaration->GetResult(), imageFilter, resultHash);
}

} // namespace OHOS::Ace::NG
