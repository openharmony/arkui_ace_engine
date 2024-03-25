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

#include "base/utils/utils.h"
#include "frameworks/core/components/declaration/svg/svg_declaration.h"

namespace OHOS::Ace::NG {

SvgUse::SvgUse() : SvgGraphic()
{
    declaration_ = AceType::MakeRefPtr<SvgDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

RefPtr<SvgNode> SvgUse::Create()
{
    return AceType::MakeRefPtr<SvgUse>();
}

#ifndef USE_ROSEN_DRAWING
SkPath SvgUse::AsPath(const Size& viewPort) const
#else
RSRecordingPath SvgUse::AsPath(const Size& viewPort) const
#endif
{
    auto svgContext = svgContext_.Upgrade();
#ifndef USE_ROSEN_DRAWING
    CHECK_NULL_RETURN(svgContext, SkPath());
#else
    CHECK_NULL_RETURN(svgContext, RSRecordingPath());
#endif
    if (declaration_->GetHref().empty()) {
        LOGE("href is empty");
        return {};
    }
    auto refSvgNode = svgContext->GetSvgNodeById(declaration_->GetHref());
#ifndef USE_ROSEN_DRAWING
    CHECK_NULL_RETURN(refSvgNode, SkPath());
#else
    CHECK_NULL_RETURN(refSvgNode, RSRecordingPath());
#endif

    AttributeScope scope(refSvgNode);
    refSvgNode->Inherit(declaration_);
    return refSvgNode->AsPath(viewPort);
}

SvgUse::AttributeScope::AttributeScope(const RefPtr<SvgNode>& node) : node_(node)
{
    auto declaration = node->GetDeclaration();
    CHECK_NULL_VOID(declaration);
    attributes_ = static_cast<SvgBaseAttribute&>(declaration->GetAttribute(AttributeTag::SPECIALIZED_ATTR));
}

SvgUse::AttributeScope::~AttributeScope()
{
    auto node = node_.Upgrade();
    CHECK_NULL_VOID(node);
    auto declaration = node->GetDeclaration();
    CHECK_NULL_VOID(declaration);
    declaration->ReplaceAttributes(attributes_);
}
} // namespace OHOS::Ace::NG
