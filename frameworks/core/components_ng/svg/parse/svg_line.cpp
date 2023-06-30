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

#include "frameworks/core/components_ng/svg/parse/svg_line.h"

#include "base/utils/utils.h"
#include "frameworks/core/components/declaration/svg/svg_line_declaration.h"

namespace OHOS::Ace::NG {

SvgLine::SvgLine() : SvgGraphic()
{
    declaration_ = AceType::MakeRefPtr<SvgLineDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
    InitGraphicFlag();
}

RefPtr<SvgNode> SvgLine::Create()
{
    return AceType::MakeRefPtr<SvgLine>();
}

#ifndef USE_ROSEN_DRAWING
SkPath SvgLine::AsPath(const Size& viewPort) const
{
    SkPath path;
    auto declaration = AceType::DynamicCast<SvgLineDeclaration>(declaration_);
    CHECK_NULL_RETURN_NOLOG(declaration, path);
    path.moveTo(ConvertDimensionToPx(declaration->GetX1(), viewPort, SvgLengthType::HORIZONTAL),
        ConvertDimensionToPx(declaration->GetY1(), viewPort, SvgLengthType::VERTICAL));
    path.lineTo(ConvertDimensionToPx(declaration->GetX2(), viewPort, SvgLengthType::HORIZONTAL),
        ConvertDimensionToPx(declaration->GetY2(), viewPort, SvgLengthType::VERTICAL));
    return path;
}
#else
RSRecordingPath SvgLine::AsPath(const Size& viewPort) const
{
    RSRecordingPath path;
    auto declaration = AceType::DynamicCast<SvgLineDeclaration>(declaration_);
    CHECK_NULL_RETURN_NOLOG(declaration, path);
    path.MoveTo(ConvertDimensionToPx(declaration->GetX1(), viewPort, SvgLengthType::HORIZONTAL),
        ConvertDimensionToPx(declaration->GetY1(), viewPort, SvgLengthType::VERTICAL));
    path.LineTo(ConvertDimensionToPx(declaration->GetX2(), viewPort, SvgLengthType::HORIZONTAL),
        ConvertDimensionToPx(declaration->GetY2(), viewPort, SvgLengthType::VERTICAL));
    return path;
}
#endif

} // namespace OHOS::Ace::NG
