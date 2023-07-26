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

#include "frameworks/core/components_ng/svg/parse/svg_path.h"

#include "include/utils/SkParsePath.h"

#include "base/utils/utils.h"
#include "frameworks/core/components/declaration/svg/svg_path_declaration.h"

namespace OHOS::Ace::NG {

SvgPath::SvgPath() : SvgGraphic()
{
    declaration_ = AceType::MakeRefPtr<SvgPathDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

RefPtr<SvgNode> SvgPath::Create()
{
    return AceType::MakeRefPtr<SvgPath>();
}

#ifndef USE_ROSEN_DRAWING
SkPath SvgPath::AsPath(const Size& /* viewPort */) const
{
    SkPath out;
    auto declaration = AceType::DynamicCast<SvgPathDeclaration>(declaration_);
    CHECK_NULL_RETURN(declaration, out);

    auto pathD = declaration->GetD();
    if (!pathD.empty()) {
        SkParsePath::FromSVGString(pathD.c_str(), &out);
        if (declaration->GetFillState().IsEvenodd()) {
#ifndef NEW_SKIA
            out.setFillType(SkPath::FillType::kEvenOdd_FillType);
#else
            out.setFillType(SkPathFillType::kEvenOdd);
#endif
        }
    }
    return out;
}
#else
RSRecordingPath SvgPath::AsPath(const Size& /* viewPort */) const
{
    RSRecordingPath out;
    auto declaration = AceType::DynamicCast<SvgPathDeclaration>(declaration_);
    CHECK_NULL_RETURN(declaration, out);

    auto pathD = declaration->GetD();
    if (!pathD.empty()) {
        out.BuildFromSVGString(pathD);
        if (declaration->GetClipState().IsEvenodd()) {
            out.SetFillStyle(RSPathFillType::EVENTODD);
        }
    }
    return out;
}
#endif

} // namespace OHOS::Ace::NG
