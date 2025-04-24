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

#include "frameworks/core/components/svg/parse/svg_mask.h"

#include "frameworks/core/components/svg/render_svg_mask.h"

namespace OHOS::Ace {

SvgMask::SvgMask() : SvgNode()
{
    component_ = AceType::MakeRefPtr<SvgMaskComponent>();
}

RefPtr<SvgNode> SvgMask::Create()
{
    return AceType::MakeRefPtr<SvgMask>();
}

void SvgMask::SetAttr(const std::string& name, const std::string& value)
{
    if (!component_->GetDeclaration()->SetSpecializedAttr(std::make_pair(name, value))) {
        component_->GetDeclaration()->SetAttr({ std::make_pair(name, value) });
    }
}

void SvgMask::AppendChild(const RefPtr<SvgNode>& child)
{
    children_.emplace_back(child);
    component_->AppendChild(child->GetComponent());
}

void SvgMask::Update(RefPtr<RenderNode>& node)
{
    if (node) {
        node->Update(component_);
    }
}

bool SvgMask::ProcessIteratively(const LayoutParam& layoutParam, std::stack<SvgCreateRenderInfo>& createRenderTaskSt,
    SvgCreateRenderInfo& svgCreateRenderInfo)
{
    auto svgNode = svgCreateRenderInfo.svgNode_;
    auto childIdx = svgCreateRenderInfo.childIndex_;
    if (childIdx == static_cast<int32_t>(svgNode->GetChildren().size())) {
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
            childNode->Update(childRender);
        }
    } else {
        createRenderTaskSt.emplace(
            childNode, component_->GetDeclaration(), svgCreateRenderInfo.useBox_, svgCreateRenderInfo.renderNode_);
    }
    return false;
}

bool SvgMask::BeforeChildrenProcessed(SvgCreateRenderInfo& svgCreateRenderInfo)
{
    auto svgContext = svgContext_.Upgrade();
    if (svgContext == nullptr) {
        LOGW("svgContext is null.");
        return false;
    }
    auto ifMaskIsUsed = svgContext->IfIdInMaskReferSet(nodeId_);
    if (!ifMaskIsUsed) {
        return false;
    }
    auto renderNode = AceType::DynamicCast<RenderSvgMask>(component_->CreateRenderNode());
    if (renderNode == nullptr) {
        return false;
    }
    component_->Inherit(svgCreateRenderInfo.svgBaseDeclaration_);
    renderNode->SetSvgRoot(svgContext->GetSvgRoot());
    renderNode->Attach(context_);
    svgCreateRenderInfo.renderNode_ = renderNode;
    return true;
}

RefPtr<RenderNode> SvgMask::CreateRender(
    const LayoutParam& layoutParam, const RefPtr<SvgBaseDeclaration>& parent, bool useBox)
{
    auto svgContext = svgContext_.Upgrade();
    if (svgContext == nullptr) {
        LOGW("svgContext is null.");
        return nullptr;
    }
    auto ifMaskIsUsed = svgContext->IfIdInMaskReferSet(nodeId_);
    if (!ifMaskIsUsed) {
        return nullptr;
    }
    auto renderNode = AceType::DynamicCast<RenderSvgMask>(component_->CreateRenderNode());
    if (renderNode == nullptr) {
        return nullptr;
    }
    component_->Inherit(parent);
    renderNode->SetSvgRoot(svgContext->GetSvgRoot());
    renderNode->Attach(context_);

    for (auto child : children_) {
        auto childRender = child->CreateRender(layoutParam, component_->GetDeclaration(), useBox);
        if (childRender) {
            renderNode->AddChild(childRender, renderNode->GetChildren().size());
            child->Update(childRender);
        }
    }
    return renderNode;
}

} // namespace OHOS::Ace
