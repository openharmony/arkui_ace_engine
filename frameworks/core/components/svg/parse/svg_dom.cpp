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

#include "frameworks/core/components/svg/parse/svg_dom.h"

#include "frameworks/core/components/svg/parse/svg_animation.h"
#include "frameworks/core/components/svg/parse/svg_circle.h"
#include "frameworks/core/components/svg/parse/svg_clip_path.h"
#include "frameworks/core/components/svg/parse/svg_defs.h"
#include "frameworks/core/components/svg/parse/svg_ellipse.h"
#include "frameworks/core/components/svg/parse/svg_g.h"
#include "frameworks/core/components/svg/parse/svg_gradient.h"
#include "frameworks/core/components/svg/parse/svg_line.h"
#include "frameworks/core/components/svg/parse/svg_mask.h"
#include "frameworks/core/components/svg/parse/svg_path.h"
#include "frameworks/core/components/svg/parse/svg_pattern.h"
#include "frameworks/core/components/svg/parse/svg_polygon.h"
#include "frameworks/core/components/svg/parse/svg_rect.h"
#include "frameworks/core/components/svg/parse/svg_stop.h"
#include "frameworks/core/components/svg/parse/svg_svg.h"
#include "frameworks/core/components/svg/parse/svg_use.h"
#include "frameworks/core/components/svg/render_svg_base.h"
#include "frameworks/core/components/transform/transform_component.h"

#include <queue>

namespace OHOS::Ace {

namespace {

const char DOM_SVG_STYLE[] = "style";
const char DOM_SVG_CLASS[] = "class";

} // namespace

static const LinearMapNode<RefPtr<SvgNode> (*)()> TAG_FACTORIES[] = {
    { "animate", []() -> RefPtr<SvgNode> { return SvgAnimation::CreateAnimate(); } },
    { "animateMotion", []() -> RefPtr<SvgNode> { return SvgAnimation::CreateAnimateMotion(); } },
    { "animateTransform", []() -> RefPtr<SvgNode> { return SvgAnimation::CreateAnimateTransform(); } },
    { "circle", []() -> RefPtr<SvgNode> { return SvgCircle::Create(); } },
    { "clipPath", []() -> RefPtr<SvgNode> { return SvgClipPath::Create(); } },
    { "defs", []() -> RefPtr<SvgNode> { return SvgDefs::Create(); } },
    { "ellipse", []() -> RefPtr<SvgNode> { return SvgEllipse::Create(); } },
    { "g", []() -> RefPtr<SvgNode> { return SvgG::Create(); } },
    { "line", []() -> RefPtr<SvgNode> { return SvgLine::Create(); } },
    { "linearGradient", []() -> RefPtr<SvgNode> { return SvgGradient::CreateLinearGradient(); } },
    { "mask", []() -> RefPtr<SvgNode> { return SvgMask::Create(); } },
    { "path", []() -> RefPtr<SvgNode> { return SvgPath::Create(); } },
    { "pattern", []() -> RefPtr<SvgNode> { return SvgPattern::Create(); } },
    { "polygon", []() -> RefPtr<SvgNode> { return SvgPolygon::CreatePolygon(); } },
    { "polyline", []() -> RefPtr<SvgNode> { return SvgPolygon::CreatePolyline(); } },
    { "radialGradient", []() -> RefPtr<SvgNode> { return SvgGradient::CreateRadialGradient(); } },
    { "rect", []() -> RefPtr<SvgNode> { return SvgRect::Create(); } },
    { "stop", []() -> RefPtr<SvgNode> { return SvgStop::Create(); } },
    { "style", []() -> RefPtr<SvgNode> { return SvgStyle::Create(); } },
    { "svg", []() -> RefPtr<SvgNode> { return SvgSvg::Create(); } },
    { "use", []() -> RefPtr<SvgNode> { return SvgUse::Create(); } },
};

SvgDom::SvgDom(const WeakPtr<PipelineContext>& context) : context_(context)
{
    attrCallback_ = [weakSvgDom = AceType::WeakClaim(this)](const std::string& styleName,
                    const std::pair<std::string, std::string>& attrPair) {
        auto svgDom = weakSvgDom.Upgrade();
        if (!svgDom) {
            LOGE("svg dom is null");
            return;
        }
        if (svgDom->svgContext_) {
            svgDom->svgContext_->PushStyle(styleName, attrPair);
        }
    };
}

SvgDom::~SvgDom()
{
    if (animatorGroup_) {
        animatorGroup_->Stop();
    }
    root_ = nullptr;
    renderNode_ = nullptr;
}

RefPtr<SvgDom> SvgDom::CreateSvgDom(SkStream& svgStream, const WeakPtr<PipelineContext>& context,
    const std::optional<Color>& svgThemeColor)
{
    RefPtr<SvgDom> svgDom = AceType::MakeRefPtr<SvgDom>(context);
    if (svgThemeColor) {
        svgDom->fillColor_ = svgThemeColor;
    }
    bool ret = svgDom->ParseSvg(svgStream);
    if (ret) {
        return svgDom;
    }
    return nullptr;
}

bool SvgDom::ParseSvg(SkStream& svgStream)
{
    SkDOM xmlDom;
    if (!xmlDom.build(svgStream)) {
        return false;
    }
    if (svgContext_ == nullptr) {
        svgContext_ = AceType::MakeRefPtr<SvgContext>();
    }
    root_ = TranslateSvgNode(xmlDom, xmlDom.getRootNode(), nullptr);
    if (root_ == nullptr) {
        return false;
    }
    auto svg = AceType::DynamicCast<SvgSvg>(root_);
    if (svg == nullptr) {
        return false;
    }
    svg->MarkIsRoot(true);
    svgSize_ = svg->GetSize();
    return true;
}

RefPtr<SvgNode> SvgDom::TranslateSvgNode(const SkDOM& dom, const SkDOM::Node* xmlNode,
    const RefPtr<SvgNode>& parent)
{
    const char* element = dom.getName(xmlNode);
    if (dom.getType(xmlNode) == SkDOM::kText_Type) {
        if (parent == nullptr) {
            return nullptr;
        }
        if (AceType::InstanceOf<SvgStyle>(parent)) {
            SvgStyle::ParseCssStyle(element, attrCallback_);
        } else {
            parent->SetText(element);
        }
    }

    auto elementIter = BinarySearchFindIndex(TAG_FACTORIES, ArraySize(TAG_FACTORIES), element);
    if (elementIter == -1) {
        return nullptr;
    }
    RefPtr<SvgNode> node = TAG_FACTORIES[elementIter].value();
    if (!node) {
        return nullptr;
    }
    node->SetContext(context_, svgContext_);
    ParseAttrs(dom, xmlNode, node);
    for (auto* child = dom.getFirstChild(xmlNode, nullptr); child; child = dom.getNextSibling(child)) {
        const auto& childNode = TranslateSvgNode(dom, child, node);
        if (childNode) {
            node->AppendChild(childNode);
        }
    }
    return node;
}

void SvgDom::ParseAttrs(const SkDOM& xmlDom, const SkDOM::Node* xmlNode, const RefPtr<SvgNode>& svgNode)
{
    const char *name = nullptr;
    const char *value = nullptr;
    SkDOM::AttrIter attrIter(xmlDom, xmlNode);
    while ((name = attrIter.next(&value))) {
        SetAttrValue(name, value, svgNode);
    }
}

void SvgDom::ParseIdAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value)
{
    auto svgNode = weakSvgNode.Upgrade();
    if (!svgNode) {
        LOGE("ParseIdAttr failed, svgNode is null");
    }
    svgNode->SetNodeId(value);
    svgNode->SetAttr(DOM_ID, value);
    svgContext_->Push(value, svgNode);
}

void SvgDom::ParseFillAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value)
{
    auto svgNode = weakSvgNode.Upgrade();
    if (!svgNode) {
        LOGE("ParseFillAttr failed, svgNode is null");
    }
    if (fillColor_) {
        std::stringstream stream;
        stream << std::hex << fillColor_.value().GetValue();
        std::string newValue(stream.str());
        svgNode->SetAttr(DOM_SVG_FILL, "#" + newValue);
    } else {
        svgNode->SetAttr(DOM_SVG_FILL, value);
    }
}

void SvgDom::ParseClassAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value)
{
    auto svgNode = weakSvgNode.Upgrade();
    if (!svgNode) {
        LOGE("ParseClassAttr failed, svgNode is null");
    }
    std::vector<std::string> styleNameVector;
    StringUtils::SplitStr(value, " ", styleNameVector);
    for (const auto& styleName : styleNameVector) {
        auto attrMap = svgContext_->GetAttrMap(styleName);
        if (attrMap.empty()) {
            continue;
        }
        for (const auto& attr: attrMap) {
            svgNode->SetAttr(attr.first, attr.second);
        }
    }
}

void SvgDom::ParseStyleAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value)
{
    auto svgNode = weakSvgNode.Upgrade();
    if (!svgNode) {
        LOGE("ParseStyleAttr failed, svgNode is null");
    }
    std::vector<std::string> attrPairVector;
    StringUtils::SplitStr(value, ";", attrPairVector);
    for (const auto& attrPair : attrPairVector) {
        std::vector<std::string> attrVector;
        StringUtils::SplitStr(attrPair, ":", attrVector);
        if (attrVector.size() == 2) {
            svgNode->SetAttr(attrVector[0], attrVector[1]);
        }
    }
}

void SvgDom::SetAttrValue(const std::string& name, const std::string& value, const RefPtr<SvgNode>& svgNode)
{
    static const LinearMapNode<void (*)(const std::string&, const WeakPtr<SvgNode>&, SvgDom&)> attrs[] = {
        { DOM_SVG_CLASS,
            [](const std::string& val, const WeakPtr<SvgNode>& svgNode, SvgDom& svgDom) {
                svgDom.ParseClassAttr(svgNode, val);
            } },
        { DOM_SVG_FILL,
            [](const std::string& val, const WeakPtr<SvgNode>& svgNode, SvgDom& svgDom) {
                svgDom.ParseFillAttr(svgNode, val);
            } },
        { DOM_ID,
            [](const std::string& val, const WeakPtr<SvgNode>& svgNode, SvgDom& svgDom) {
                svgDom.ParseIdAttr(svgNode, val);
            } },
        { DOM_SVG_STYLE,
            [](const std::string& val, const WeakPtr<SvgNode>& svgNode, SvgDom& svgDom) {
                svgDom.ParseStyleAttr(svgNode, val);
            } },
    };
    if (value.empty()) {
        return;
    }
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), name.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, svgNode, *this);
        return;
    }
    svgNode->SetAttr(name, value);
}

void SvgDom::CreateRenderNode()
{
    if (root_ == nullptr) {
        return;
    }
    auto svg = AceType::DynamicCast<SvgSvg>(root_);
    if (svg == nullptr) {
        return;
    }
    Size size;
    if (svgSize_.IsValid() && !svgSize_.IsInfinite()) {
        size = svgSize_;
    } else {
        size = containerSize_;
    }
    auto renderSvg = svg->CreateRender(LayoutParam(size, Size(0.0, 0.0)), nullptr);
    if (renderSvg) {
        InitAnimatorGroup(renderSvg);
        auto transformComponent = AceType::MakeRefPtr<TransformComponent>();
        auto renderTransform = transformComponent->CreateRenderNode();
        renderTransform->Attach(context_);
        renderTransform->Update(transformComponent);
        renderTransform->AddChild(renderSvg);
        renderTransform->Layout(LayoutParam(containerSize_, Size(0.0, 0.0)));

        auto boxComponent = AceType::MakeRefPtr<BoxComponent>();
        boxComponent->SetWidth(containerSize_.Width());
        boxComponent->SetHeight(containerSize_.Height());
        renderNode_ = boxComponent->CreateRenderNode();
        renderNode_->Attach(context_);
        renderNode_->Update(boxComponent);
        renderNode_->AddChild(renderTransform);
        renderNode_->Layout(LayoutParam(containerSize_, Size(0.0, 0.0)));
    }
}

void SvgDom::InitAnimatorGroup(const RefPtr<RenderNode>& node)
{
    animatorGroup_ = AceType::MakeRefPtr<AnimatorGroup>();
    if (!animatorGroup_) {
        return;
    }
    AddToAnimatorGroup(node, animatorGroup_);
    auto finishEvent = AceAsyncEvent<void()>::Create(finishEvent_, context_);
    if (finishEvent) {
        animatorGroup_->AddStopListener(
            [asyncEvent = finishEvent] { asyncEvent(); });
    }
    animatorGroup_->Play();
}

void SvgDom::AddToAnimatorGroup(const RefPtr<RenderNode>& node, RefPtr<AnimatorGroup>& animatorGroup)
{
    if (!animatorGroup) {
        return;
    }

    std::queue<RefPtr<RenderNode>> queue;
    queue.push(node);
    while (!queue.empty()) {
        auto renderNode = queue.front();
        queue.pop();
        auto svgBase = AceType::DynamicCast<RenderSvgBase>(renderNode);
        if (svgBase) {
            auto animators = svgBase->GetAnimators();
            for (auto& p : animators) {
                animatorGroup->AddAnimator(p.second);
            }
        }
        if (renderNode) {
            auto children = renderNode->GetChildren();
            for (auto& child : children) {
                queue.push(child);
            }
        }
    }
}

} // namespace OHOS::Ace
