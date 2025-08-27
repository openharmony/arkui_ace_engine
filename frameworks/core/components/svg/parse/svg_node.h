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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_PARSE_SVG_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_PARSE_SVG_NODE_H

#include <utility>
#include <vector>
#include "core/components_ng/render/drawing.h"

#include "base/memory/ace_type.h"
#include "core/components/declaration/svg/svg_base_declaration.h"
#include "core/pipeline/base/render_node.h"
#include "frameworks/core/components/box/box_component.h"
#include "frameworks/core/components/svg/parse/svg_context.h"

namespace OHOS::Ace {

enum class SvgLengthType {
    HORIZONTAL,
    VERTICAL,
    OTHER,
};

class SvgContext;
class SvgNode;

struct SvgCreateRenderInfo {
    SvgCreateRenderInfo() = default;
    SvgCreateRenderInfo(RefPtr<SvgNode> svgNode, RefPtr<SvgBaseDeclaration> svgBaseDeclaration, bool useBox,
        RefPtr<RenderNode> parentRenderNode = nullptr)
        : svgNode_(svgNode), svgBaseDeclaration_(svgBaseDeclaration), useBox_(useBox),
          parentRenderNode_(parentRenderNode)
    {}
    RefPtr<SvgNode> svgNode_ = nullptr; // The SVG node currently being processed
    RefPtr<SvgBaseDeclaration> svgBaseDeclaration_ =
        nullptr;             // Pointer to the declaration used for inheriting rendering attributes
    int32_t childIndex_ = 0; // Index of the next child node to traverse for the current node
    bool useBox_ = true;
    RefPtr<RenderNode> renderNode_ = nullptr;
    RefPtr<RenderNode> parentRenderNode_ = nullptr;
};

class SvgNode : public AceType {
    DECLARE_ACE_TYPE(SvgNode, AceType);

public:
    SvgNode() = default;
    ~SvgNode() override = default;

    virtual void AppendChild(const RefPtr<SvgNode>& svgNode) {}
    virtual void SetAttr(const std::string& name, const std::string& value) {}
    virtual void Update(RefPtr<RenderNode>& node) {}
    virtual void Inherit(const RefPtr<SvgBaseDeclaration>& parent) {}
    // Return true if CreateRender is implemented recursively; otherwise false.
    virtual bool IsCreateRenderRecursive() const
    {
        return false;
    }

    virtual bool BeforeChildrenProcessed(SvgCreateRenderInfo& svgCreateRenderInfo)
    {
        return true;
    }
    virtual void AfterChildrenProcessed(const LayoutParam& layoutParam, SvgCreateRenderInfo& svgCreateRenderInfo) {}
    virtual bool ProcessIteratively(const LayoutParam& layoutParam, std::stack<SvgCreateRenderInfo>& createRenderTaskSt,
        SvgCreateRenderInfo& svgCreateRenderInfo)
    {
        return false;
    }
    virtual RefPtr<RenderNode> CreateRender(
        const LayoutParam& layoutParam, const RefPtr<SvgBaseDeclaration>& parent, bool useBox = true)
    {
        return nullptr;
    }

    virtual RSPath AsPath(const Size& viewPort) const
    {
        return RSPath();
    }

    virtual RefPtr<Component> GetComponent() const
    {
        return nullptr;
    }

    void SetNodeId(const std::string& value)
    {
        nodeId_ = value;
    }

    void SetContext(const WeakPtr<PipelineContext>& context, const WeakPtr<SvgContext>& svgContext)
    {
        context_ = context;
        svgContext_ = svgContext;
    }

    void SetText(const std::string& text)
    {
        text_ = text;
    }

    const std::vector<RefPtr<SvgNode>>& GetChildren()
    {
        return children_;
    }

protected:
    double ConvertDimensionToPx(const Dimension& value, const Size& viewPort, SvgLengthType type) const;
    std::optional<Gradient> GetGradient(const std::string& href);
    RefPtr<BoxComponent> CreateBoxComponent(const LayoutParam& layoutParam, const std::string& clipPathHref);

    WeakPtr<PipelineContext> context_;
    WeakPtr<SvgContext> svgContext_;
    std::vector<RefPtr<SvgNode>> children_;
    std::string nodeId_;
    std::string text_;

private:
    std::string AsClipPathCommands(const Size& viewPort, const std::string& href) const;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_PARSE_SVG_NODE_H