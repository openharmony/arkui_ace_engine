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

#include "frameworks/core/components/svg/parse/svg_svg.h"
#include "ui/base/referenced.h"
#include "core/components/svg/parse/svg_node.h"

#ifndef USE_ROSEN_DRAWING
#include "include/pathops/SkPathOps.h"
#endif

#include "frameworks/core/components/svg/render_svg.h"

namespace OHOS::Ace {

SvgSvg::SvgSvg() : SvgNode()
{
    component_ = AceType::MakeRefPtr<SvgComponent>();
}

RefPtr<SvgNode> SvgSvg::Create()
{
    return AceType::MakeRefPtr<SvgSvg>();
}

void SvgSvg::SetAttr(const std::string& name, const std::string& value)
{
    component_->GetDeclaration()->SetSpecializedAttr(std::make_pair(name, value));
}

void SvgSvg::AppendChild(const RefPtr<SvgNode>& child)
{
    children_.emplace_back(child);
    component_->AppendChild(child->GetComponent());
}

RefPtr<RenderNode> SvgSvg::InitializeRenderNode()
{
    auto renderNode = AceType::DynamicCast<RenderSvg>(component_->CreateRenderNode());
    if (!renderNode) {
        LOGE("create renderNode failed");
        return nullptr;
    }
    renderNode->Attach(context_);
    if (IsRoot()) {
        auto svgContext = svgContext_.Upgrade();
        if (svgContext) {
            svgContext->SetSvgRoot(renderNode);
        }
    }

    renderNode->Update(component_);
    return renderNode;
}

bool SvgSvg::ProcessIteratively(const LayoutParam& layoutParam, std::stack<SvgCreateRenderInfo>& createRenderTaskSt,
    SvgCreateRenderInfo& svgCreateRenderInfo)
{
    auto svgNode = svgCreateRenderInfo.svgNode_;
    auto childIdx = svgCreateRenderInfo.childIndex_;
    if (childIdx == static_cast<int32_t>(svgNode->GetChildren().size())) {
        AfterChildrenProcessed(layoutParam, svgCreateRenderInfo);
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
            childNode->Update(childRender);
        }
    } else {
        createRenderTaskSt.emplace(
            childNode, component_->GetDeclaration(), svgCreateRenderInfo.useBox_, svgCreateRenderInfo.renderNode_);
    }
    return false;
}

bool SvgSvg::BeforeChildrenProcessed(SvgCreateRenderInfo& svgCreateRenderInfo)
{
    auto parent = svgCreateRenderInfo.svgBaseDeclaration_;
    component_->Inherit(parent);
    auto& declaration = component_->GetDeclaration();
    auto href = declaration->GetFillState().GetHref();
    if (!href.empty()) {
        auto gradient = GetGradient(href);
        if (gradient) {
            declaration->SetGradient(gradient.value());
        }
    }
    svgCreateRenderInfo.renderNode_ = InitializeRenderNode();
    return true;
}

void SvgSvg::AfterChildrenProcessed(const LayoutParam& layoutParam, SvgCreateRenderInfo& svgCreateRenderInfo)
{
    auto renderNode = DynamicCast<RenderSvg>(svgCreateRenderInfo.renderNode_);
    if (!renderNode) {
        return;
    }
    renderNode->MarkIsFixSize(true);
    renderNode->Layout(layoutParam);
    if (!svgCreateRenderInfo.useBox_ || component_->GetDeclaration()->GetClipPathHref().empty()) {
        LOGW("svg of svg tag skip box create");
        return;
    }

    auto boxComponent = CreateBoxComponent(layoutParam, component_->GetDeclaration()->GetClipPathHref());
    boxComponent->SetWidth(layoutParam.GetMaxSize().Width());
    boxComponent->SetHeight(layoutParam.GetMaxSize().Height());
    boxComponent->SetOverflow(Overflow::FORCE_CLIP);
    auto renderBox = boxComponent->CreateRenderNode();
    renderBox->Attach(context_);
    renderBox->Update(boxComponent);
    renderBox->AddChild(renderNode);
    renderBox->Layout(layoutParam);
}

RefPtr<RenderNode> SvgSvg::CreateRenderHelp(
    const WeakPtr<SvgNode>& root, const LayoutParam& layoutParam, const RefPtr<SvgBaseDeclaration>& parent, bool useBox)
{
    auto svgRoot = root.Upgrade();
    if (!svgRoot) {
        return nullptr;
    }
    std::stack<SvgCreateRenderInfo> createRenderTaskSt;
    createRenderTaskSt.emplace(svgRoot, parent, useBox);
    RefPtr<RenderNode> result = nullptr;
    while (!createRenderTaskSt.empty()) {
        auto& currentSvgCreateRenderInfo = createRenderTaskSt.top();
        auto& svgNode = currentSvgCreateRenderInfo.svgNode_;
        if (currentSvgCreateRenderInfo.childIndex_ == 0 &&
            !svgNode->BeforeChildrenProcessed(currentSvgCreateRenderInfo)) {
            createRenderTaskSt.pop();
            continue;
        }

        if (svgNode->ProcessIteratively(layoutParam, createRenderTaskSt, currentSvgCreateRenderInfo)) {
            if (createRenderTaskSt.size() == 1) {
                // Set result if this is the root SVG node
                result = currentSvgCreateRenderInfo.renderNode_;
            }
            createRenderTaskSt.pop();
        }
    }
    return result;
}

RefPtr<RenderNode> SvgSvg::CreateRender(
    const LayoutParam& layoutParam, const RefPtr<SvgBaseDeclaration>& parent, bool useBox)
{
    return CreateRenderHelp(WeakClaim(this), layoutParam, parent, useBox);
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
RSPath SvgSvg::AsPath(const Size& viewPort) const
{
    RSPath path;
    for (const auto& child : children_) {
        RSPath childPath = child->AsPath(viewPort);
        path.Op(path, childPath, RSPathOp::UNION);
    }
    return path;
}
#endif

} // namespace OHOS::Ace
