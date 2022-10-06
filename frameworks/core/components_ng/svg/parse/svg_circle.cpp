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

#include "frameworks/core/components_ng/svg/parse/svg_circle.h"

#include "frameworks/core/components/declaration/svg/svg_circle_declaration.h"

namespace OHOS::Ace::NG {

SvgCircle::SvgCircle() : SvgGraphic()
{
    declaration_ = AceType::MakeRefPtr<SvgCircleDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

RefPtr<SvgNode> SvgCircle::Create()
{
    return AceType::MakeRefPtr<SvgCircle>();
}

SkPath SvgCircle::AsPath(const Size& viewPort) const
{
    SkPath path;
    auto declaration = AceType::DynamicCast<SvgCircleDeclaration>(declaration_);
    if (declaration == nullptr) {
        return path;
    }
    path.addCircle(ConvertDimensionToPx(declaration->GetCx(), viewPort, SvgLengthType::HORIZONTAL),
        ConvertDimensionToPx(declaration->GetCy(), viewPort, SvgLengthType::VERTICAL),
        ConvertDimensionToPx(declaration->GetR(), viewPort, SvgLengthType::OTHER));
    return path;
}

} // namespace OHOS::Ace::NG
