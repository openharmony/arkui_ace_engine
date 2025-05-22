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

#include "frameworks/core/components/svg/parse/svg_g.h"

#ifndef USE_ROSEN_DRAWING
#include "include/pathops/SkPathOps.h"
#endif

#include "frameworks/core/components/svg/render_svg_g.h"

namespace OHOS::Ace {

SvgG::SvgG() : SvgNode()
{
    component_ = AceType::MakeRefPtr<SvgGComponent>();
}

RefPtr<SvgNode> SvgG::Create()
{
    return AceType::MakeRefPtr<SvgG>();
}

void SvgG::SetAttr(const std::string& name, const std::string& value)
{
    component_->GetDeclaration()->SetSpecializedAttr(std::make_pair(name, value));
}

void SvgG::AppendChild(const RefPtr<SvgNode>& child)
{
    children_.emplace_back(child);
    component_->AppendChild(child->GetComponent());
}

bool SvgG::ProcessIteratively(const LayoutParam& layoutParam, std::stack<SvgCreateRenderInfo>& createRenderTaskSt,
    SvgCreateRenderInfo& svgCreateRenderInfo)
{
    auto svgNode = svgCreateRenderInfo.svgNode_;
    auto childIdx = svgCreateRenderInfo.childIndex_;
    if (childIdx == static_cast<int32_t>(svgNode->GetChildren().size())) {
        AfterChildrenProcessed(layoutParam, svgCreateRenderInfo);
        auto childRenderNode = svgCreateRenderInfo.renderNode_;
        auto parentRenderNode = svgCreateRenderInfo.parentRenderNode_;
        if (parentRenderNode && childRenderNode) {
            parentRenderNode->AddChild(childRenderNode, static_cast<int32_t>(parentRenderNode->GetChildren().size()));
            svgNode->Update(childRenderNode);
        }
        return true;
    }
    ++svgCreateRenderInfo.childIndex_;
    auto childNode = svgNode->GetChildren()[childIdx];
    // If the child node does not use recursion for CreateRender
    if (!childNode->IsCreateRenderRecursive()) {
        auto childRender =
            childNode->CreateRender(layoutParam, component_->GetDeclaration(), svgCreateRenderInfo.useBox_);
        auto renderNode = svgCreateRenderInfo.renderNode_;
        if (childRender && renderNode) {
            renderNode->AddChild(childRender, renderNode->GetChildren().size());
        }
    } else {
        createRenderTaskSt.emplace(
            childNode, component_->GetDeclaration(), svgCreateRenderInfo.useBox_, svgCreateRenderInfo.renderNode_);
    }
    return false;
}

bool SvgG::BeforeChildrenProcessed(SvgCreateRenderInfo& svgCreateRenderInfo)
{
    component_->Inherit(svgCreateRenderInfo.svgBaseDeclaration_);
    auto& declaration = component_->GetDeclaration();
    auto href = declaration->GetFillState().GetHref();
    if (!href.empty()) {
        auto gradient = GetGradient(href);
        if (gradient) {
            declaration->SetGradient(gradient.value());
        }
    }
    auto renderNode = AceType::DynamicCast<RenderSvgG>(component_->CreateRenderNode());
    if (!renderNode) {
        LOGE("create renderNode failed");
        return false;
    }
    renderNode->Attach(context_);
    renderNode->Update(component_);
    svgCreateRenderInfo.renderNode_ = renderNode;
    return true;
}

void SvgG::AfterChildrenProcessed(const LayoutParam& layoutParam, SvgCreateRenderInfo& svgCreateRenderInfo)
{
    auto renderNode = svgCreateRenderInfo.renderNode_;
    if (!renderNode) {
        return;
    }
    renderNode->Layout(layoutParam);
    auto& declaration = component_->GetDeclaration();
    if (!svgCreateRenderInfo.useBox_ || declaration->GetClipPathHref().empty()) {
        LOGW("g tag skip box create");
        return;
    }

    auto boxComponent = CreateBoxComponent(layoutParam, declaration->GetClipPathHref());
    auto renderBox = boxComponent->CreateRenderNode();
    renderBox->Attach(context_);
    renderBox->Update(boxComponent);
    renderBox->AddChild(renderNode);

    svgCreateRenderInfo.renderNode_ = renderBox;
}

RefPtr<RenderNode> SvgG::CreateRender(
    const LayoutParam& layoutParam, const RefPtr<SvgBaseDeclaration>& parent, bool useBox)
{
    component_->Inherit(parent);
    auto& declaration = component_->GetDeclaration();
    auto href = declaration->GetFillState().GetHref();
    if (!href.empty()) {
        auto gradient = GetGradient(href);
        if (gradient) {
            declaration->SetGradient(gradient.value());
        }
    }
    auto renderNode = AceType::DynamicCast<RenderSvgG>(component_->CreateRenderNode());
    if (!renderNode) {
        LOGE("create renderNode failed");
        return nullptr;
    }
    renderNode->Attach(context_);
    renderNode->Update(component_);
    for (auto child : children_) {
        auto childRender = child->CreateRender(layoutParam, declaration, useBox);
        if (childRender) {
            renderNode->AddChild(childRender, renderNode->GetChildren().size());
        }
    }
    renderNode->Layout(layoutParam);
    if (!useBox || declaration->GetClipPathHref().empty()) {
        LOGW("g tag skip box create");
        return renderNode;
    }

    auto boxComponent = CreateBoxComponent(layoutParam, declaration->GetClipPathHref());
    auto renderBox = boxComponent->CreateRenderNode();
    renderBox->Attach(context_);
    renderBox->Update(boxComponent);
    renderBox->AddChild(renderNode);
    return renderBox;
}

#ifndef USE_ROSEN_DRAWING
SkPath SvgG::AsPath(const Size& viewPort) const
{
    SkPath path;
    for (auto child : children_) {
        const SkPath childPath = child->AsPath(viewPort);
        Op(path, childPath, kUnion_SkPathOp, &path);
    }
    return path;
}
#else
RSPath SvgG::AsPath(const Size& viewPort) const
{
    RSPath path;
    for (auto child : children_) {
        RSPath childPath = child->AsPath(viewPort);
        path.Op(path, childPath, RSPathOp::UNION);
    }
    return path;
}
#endif

} // namespace OHOS::Ace
