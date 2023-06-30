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

#include "frameworks/core/components_ng/svg/parse/svg_svg.h"

#include "include/pathops/SkPathOps.h"

#include "base/utils/utils.h"
#include "frameworks/core/components/declaration/svg/svg_declaration.h"

namespace OHOS::Ace::NG {

SvgSvg::SvgSvg() : SvgGroup()
{
    declaration_ = AceType::MakeRefPtr<SvgDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

RefPtr<SvgNode> SvgSvg::Create()
{
    return AceType::MakeRefPtr<SvgSvg>();
}

#ifndef USE_ROSEN_DRAWING
SkPath SvgSvg::AsPath(const Size& viewPort) const
{
    SkPath path;
    for (const auto& child : children_) {
        const SkPath childPath = child->AsPath(viewPort);
        Op(path, childPath, kUnion_SkPathOp, &path);
    }
    return path;
}
#else
RSRecordingPath SvgSvg::AsPath(const Size& viewPort) const
{
    RSRecordingPath path;
    for (const auto& child : children_) {
        RSRecordingPath childPath = child->AsPath(viewPort);
        path.Op(path, childPath, RSPathOp::UNION);
    }
    return path;
}
#endif

Size SvgSvg::GetSize() const
{
    auto declaration = AceType::DynamicCast<SvgDeclaration>(declaration_);
    CHECK_NULL_RETURN_NOLOG(declaration, Size());

    return Size(declaration->GetWidth().Value(), declaration->GetHeight().Value());
}

const Rect& SvgSvg::GetViewBox() const
{
    auto declaration = AceType::DynamicCast<SvgDeclaration>(declaration_);
    CHECK_NULL_RETURN_NOLOG(declaration, Rect());
    return declaration->GetViewBox();
}

} // namespace OHOS::Ace::NG
