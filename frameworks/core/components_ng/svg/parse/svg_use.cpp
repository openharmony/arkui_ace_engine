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

#include "frameworks/core/components_ng/svg/parse/svg_use.h"

#include "frameworks/core/components/declaration/svg/svg_declaration.h"

namespace OHOS::Ace::NG {

SvgUse::SvgUse() : SvgGroup()
{
    declaration_ = AceType::MakeRefPtr<SvgDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

RefPtr<SvgNode> SvgUse::Create()
{
    return AceType::MakeRefPtr<SvgUse>();
}

SkPath SvgUse::AsPath(const Size& viewPort) const
{
    auto svgContext = svgContext_.Upgrade();
    if (!svgContext) {
        LOGE("asPath failed, svgContext is null");
        return SkPath();
    }
    if (declaration_->GetHref().empty()) {
        LOGE("href is empty");
        return SkPath();
    }
    auto refSvgNode = svgContext->GetSvgNodeById(declaration_->GetHref());
    if (!refSvgNode) {
        LOGE("refSvgNode is null");
        return SkPath();
    }
    refSvgNode->Inherit(declaration_);
    return refSvgNode->AsPath(viewPort);
}

} // namespace OHOS::Ace::NG
