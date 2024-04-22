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

void SvgUse::OnInitStyle()
{
    auto declaration = AceType::DynamicCast<SvgDeclaration>(declaration_);
    CHECK_NULL_VOID(declaration);
    useOffsetX_ = declaration->GetX().Value();
    useOffsetY_ = declaration->GetY().Value();
}

RefPtr<SvgNode> SvgUse::Create()
{
    return AceType::MakeRefPtr<SvgUse>();
}

RSRecordingPath SvgUse::AsPath(const Size& viewPort) const
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_RETURN(svgContext, RSRecordingPath());
    if (declaration_->GetHref().empty()) {
        LOGE("href is empty");
        return {};
    }
    auto refSvgNode = svgContext->GetSvgNodeById(declaration_->GetHref());
    CHECK_NULL_RETURN(refSvgNode, RSRecordingPath());

    AttributeScope scope(refSvgNode);
    refSvgNode->Inherit(declaration_);
    return refSvgNode->AsPath(viewPort);
}

void SvgUse::OnDraw(RSCanvas& canvas, const Size& layout, const std::optional<Color>& color)
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_VOID(svgContext);
    if (declaration_->GetHref().empty()) {
        return;
    }
    auto refSvgNode = svgContext->GetSvgNodeById(declaration_->GetHref());
    CHECK_NULL_VOID(refSvgNode);

    auto declaration = AceType::DynamicCast<SvgDeclaration>(declaration_);
    if (declaration->GetX().Value() != 0 || declaration->GetY().Value() != 0) {
        canvas.Translate(declaration->GetX().Value(), declaration->GetY().Value());
    }
    AttributeScope scope(refSvgNode);
    refSvgNode->Inherit(declaration);

    refSvgNode->Draw(canvas, layout, color);
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
