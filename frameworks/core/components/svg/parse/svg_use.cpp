/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/core/components/svg/parse/svg_use.h"

#include "frameworks/core/components/svg/render_svg_use.h"

namespace OHOS::Ace {

SvgUse::SvgUse() : SvgNode()
{
    component_ = AceType::MakeRefPtr<SvgUseComponent>();
}

RefPtr<SvgNode> SvgUse::Create()
{
    return AceType::MakeRefPtr<SvgUse>();
}

void SvgUse::SetAttr(const std::string& name, const std::string& value)
{
    component_->GetDeclaration()->SetSpecializedAttr(std::make_pair(name, value));
}

void SvgUse::AppendChild(const RefPtr<SvgNode>& child)
{
    children_.emplace_back(child);
    component_->AppendChild(child->GetComponent());
}

RefPtr<RenderNode> SvgUse::CreateRender(
    const LayoutParam& layoutParam, const RefPtr<SvgBaseDeclaration>& parent, bool useBox)
{
    auto svgContext = svgContext_.Upgrade();
    if (!svgContext) {
        LOGE("create user render failed, svgContext is null");
        return nullptr;
    }
    auto& declaration = component_->GetDeclaration();
    if (declaration->GetHref().empty()) {
        LOGE("href is empty");
        return nullptr;
    }
    if (isCreateRenderRunning_) {
        LOGW("Render creation already in progress, skipping current operation to avoid infinite loop.");
        return nullptr;
    }
    isCreateRenderRunning_ = true;
    auto refSvgNode = svgContext->GetSvgNodeById(declaration->GetHref());
    if (!refSvgNode) {
        LOGE("refSvgNode is null");
        return nullptr;
    }
    component_->Inherit(parent);
    auto href = declaration->GetFillState().GetHref();
    if (!href.empty()) {
        auto gradient = GetGradient(href);
        if (gradient) {
            declaration->SetGradient(gradient.value());
        }
    }
    auto refRenderNode = refSvgNode->CreateRender(layoutParam, declaration, useBox);
    if (!refRenderNode) {
        return nullptr;
    }
    auto renderNode = AceType::DynamicCast<RenderSvgUse>(component_->CreateRenderNode());
    if (!renderNode) {
        LOGE("create renderNode failed");
        return nullptr;
    }
    renderNode->Attach(context_);
    renderNode->Update(component_);
    renderNode->AddChild(refRenderNode, 0);
    renderNode->Layout(layoutParam);
    isCreateRenderRunning_ = false;
    if (!useBox || declaration->GetClipPathHref().empty()) {
        LOGW("use of svg tag skip box create");
        return renderNode;
    }

    auto boxComponent = CreateBoxComponent(layoutParam, declaration->GetClipPathHref());
    auto renderBox = boxComponent->CreateRenderNode();
    renderBox->Attach(context_);
    renderBox->Update(boxComponent);
    renderBox->AddChild(renderNode);
    return renderBox;
}

RSPath SvgUse::AsPath(const Size& viewPort) const
{
    auto svgContext = svgContext_.Upgrade();
    if (!svgContext) {
        LOGE("asPath failed, svgContext is null");
        return RSPath();
    }
    auto& declaration = component_->GetDeclaration();
    if (declaration->GetHref().empty()) {
        LOGE("href is empty");
        return RSPath();
    }
    auto refSvgNode = svgContext->GetSvgNodeById(declaration->GetHref());
    if (!refSvgNode) {
        LOGE("refSvgNode is null");
        return RSPath();
    }
    refSvgNode->Inherit(declaration);
    return refSvgNode->AsPath(viewPort);
}

} // namespace OHOS::Ace
