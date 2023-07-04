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

#include "frameworks/core/components_ng/svg/parse/svg_ellipse.h"

#include "base/utils/utils.h"
#include "frameworks/core/components/declaration/svg/svg_ellipse_declaration.h"

namespace OHOS::Ace::NG {

SvgEllipse::SvgEllipse() : SvgGraphic()
{
    declaration_ = AceType::MakeRefPtr<SvgEllipseDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

RefPtr<SvgNode> SvgEllipse::Create()
{
    return AceType::MakeRefPtr<SvgEllipse>();
}

#ifndef USE_ROSEN_DRAWING
SkPath SvgEllipse::AsPath(const Size& viewPort) const
{
    SkPath path;
#else
RSRecordingPath SvgEllipse::AsPath(const Size& viewPort) const
{
    RSRecordingPath path;
#endif
    auto declaration = AceType::DynamicCast<SvgEllipseDeclaration>(declaration_);
    CHECK_NULL_RETURN_NOLOG(declaration, path);
    double rx = 0.0;
    if (GreatOrEqual(declaration->GetRx().Value(), 0.0)) {
        rx = ConvertDimensionToPx(declaration->GetRx(), viewPort, SvgLengthType::HORIZONTAL);
    } else {
        if (GreatNotEqual(declaration->GetRy().Value(), 0.0)) {
            rx = ConvertDimensionToPx(declaration->GetRy(), viewPort, SvgLengthType::VERTICAL);
        }
    }
    double ry = 0.0;
    if (GreatOrEqual(declaration->GetRy().Value(), 0.0)) {
        ry = ConvertDimensionToPx(declaration->GetRy(), viewPort, SvgLengthType::VERTICAL);
    } else {
        if (GreatNotEqual(declaration->GetRx().Value(), 0.0)) {
            ry = ConvertDimensionToPx(declaration->GetRx(), viewPort, SvgLengthType::HORIZONTAL);
        }
    }
#ifndef USE_ROSEN_DRAWING
    SkRect rect = SkRect::MakeXYWH(ConvertDimensionToPx(declaration->GetCx(), viewPort, SvgLengthType::HORIZONTAL) - rx,
        ConvertDimensionToPx(declaration->GetCy(), viewPort, SvgLengthType::VERTICAL) - ry, rx + rx, ry + ry);
    path.addOval(rect);
#else
    RSScalar left = ConvertDimensionToPx(declaration->GetCx(), viewPort, SvgLengthType::HORIZONTAL) - rx;
    RSScalar top = ConvertDimensionToPx(declaration->GetCy(), viewPort, SvgLengthType::VERTICAL) - ry;
    RSRect rect = RSRect(left, top, rx + rx + left, ry + ry + top);
    path.AddOval(rect);
#endif
    return path;
}

} // namespace OHOS::Ace::NG
