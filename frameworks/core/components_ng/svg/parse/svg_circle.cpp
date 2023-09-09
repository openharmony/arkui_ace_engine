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

#include "base/utils/utils.h"
#include "core/components_ng/svg/parse/svg_animation.h"
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

#ifndef USE_ROSEN_DRAWING
SkPath SvgCircle::AsPath(const Size& viewPort) const
{
    SkPath path;
    auto declaration = AceType::DynamicCast<SvgCircleDeclaration>(declaration_);
    CHECK_NULL_RETURN(declaration, path);
    path.addCircle(ConvertDimensionToPx(declaration->GetCx(), viewPort, SvgLengthType::HORIZONTAL),
        ConvertDimensionToPx(declaration->GetCy(), viewPort, SvgLengthType::VERTICAL),
        ConvertDimensionToPx(declaration->GetR(), viewPort, SvgLengthType::OTHER));
    return path;
}
#else
RSRecordingPath SvgCircle::AsPath(const Size& viewPort) const
{
    RSRecordingPath path;
    auto declaration = AceType::DynamicCast<SvgCircleDeclaration>(declaration_);
    CHECK_NULL_RETURN(declaration, path);
    path.AddCircle(ConvertDimensionToPx(declaration->GetCx(), viewPort, SvgLengthType::HORIZONTAL),
        ConvertDimensionToPx(declaration->GetCy(), viewPort, SvgLengthType::VERTICAL),
        ConvertDimensionToPx(declaration->GetR(), viewPort, SvgLengthType::OTHER));
    return path;
}
#endif

void SvgCircle::PrepareAnimation(const RefPtr<SvgAnimation>& animate)
{
    auto declaration = AceType::DynamicCast<SvgCircleDeclaration>(declaration_);
    CHECK_NULL_VOID(declaration);
    auto attr = animate->GetAttributeName();
    if (attr == DOM_SVG_CX) {
        AnimateOnAttribute(animate, declaration->GetCx());
    } else if (attr == DOM_SVG_CY) {
        AnimateOnAttribute(animate, declaration->GetCy());
    } else if (attr == DOM_SVG_R) {
        AnimateOnAttribute(animate, declaration->GetR());
    } else {
        SvgNode::PrepareAnimation(animate);
    }
}
} // namespace OHOS::Ace::NG
