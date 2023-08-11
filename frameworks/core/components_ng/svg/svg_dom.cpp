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

#include "frameworks/core/components_ng/svg/svg_dom.h"

#include "include/core/SkClipOp.h"

#include "base/utils/utils.h"
#include "core/components_ng/svg/svg_context.h"
#include "frameworks/core/components_ng/render/adapter/image_painter_utils.h"
#include "frameworks/core/components_ng/render/drawing.h"
#include "frameworks/core/components_ng/svg/parse/svg_animation.h"
#include "frameworks/core/components_ng/svg/parse/svg_circle.h"
#include "frameworks/core/components_ng/svg/parse/svg_clip_path.h"
#include "frameworks/core/components_ng/svg/parse/svg_defs.h"
#include "frameworks/core/components_ng/svg/parse/svg_ellipse.h"
#include "frameworks/core/components_ng/svg/parse/svg_fe_color_matrix.h"
#include "frameworks/core/components_ng/svg/parse/svg_fe_composite.h"
#include "frameworks/core/components_ng/svg/parse/svg_fe_gaussian_blur.h"
#include "frameworks/core/components_ng/svg/parse/svg_fe_offset.h"
#include "frameworks/core/components_ng/svg/parse/svg_filter.h"
#include "frameworks/core/components_ng/svg/parse/svg_g.h"
#include "frameworks/core/components_ng/svg/parse/svg_gradient.h"
#include "frameworks/core/components_ng/svg/parse/svg_line.h"
#include "frameworks/core/components_ng/svg/parse/svg_mask.h"
#include "frameworks/core/components_ng/svg/parse/svg_path.h"
#include "frameworks/core/components_ng/svg/parse/svg_pattern.h"
#include "frameworks/core/components_ng/svg/parse/svg_polygon.h"
#include "frameworks/core/components_ng/svg/parse/svg_rect.h"
#include "frameworks/core/components_ng/svg/parse/svg_stop.h"
#include "frameworks/core/components_ng/svg/parse/svg_svg.h"
#include "frameworks/core/components_ng/svg/parse/svg_use.h"

namespace OHOS::Ace::NG {
namespace {

const char DOM_SVG_STYLE[] = "style";
const char DOM_SVG_CLASS[] = "class";

} // namespace

static const LinearMapNode<RefPtr<SvgNode> (*)()> TAG_FACTORIES[] = {
    { "animate", []() -> RefPtr<SvgNode> { return SvgAnimation::Create(); } },
    { "animateMotion", []() -> RefPtr<SvgNode> { return SvgAnimation::CreateAnimateMotion(); } },
    { "animateTransform", []() -> RefPtr<SvgNode> { return SvgAnimation::CreateAnimateTransform(); } },
    { "circle", []() -> RefPtr<SvgNode> { return SvgCircle::Create(); } },
    { "clipPath", []() -> RefPtr<SvgNode> { return SvgClipPath::Create(); } },
    { "defs", []() -> RefPtr<SvgNode> { return SvgDefs::Create(); } },
    { "ellipse", []() -> RefPtr<SvgNode> { return SvgEllipse::Create(); } },
    { "feColorMatrix", []() -> RefPtr<SvgNode> { return SvgFeColorMatrix::Create(); } },
    { "feComposite", []() -> RefPtr<SvgNode> { return SvgFeComposite::Create(); } },
    { "feGaussianBlur", []() -> RefPtr<SvgNode> { return SvgFeGaussianBlur::Create(); } },
    { "feOffset", []() -> RefPtr<SvgNode> { return SvgFeOffset::Create(); } },
    { "filter", []() -> RefPtr<SvgNode> { return SvgFilter::Create(); } },
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

SvgDom::SvgDom()
{
    svgContext_ = AceType::MakeRefPtr<SvgContext>();
    attrCallback_ = [weakSvgDom = AceType::WeakClaim(this)](
                        const std::string& styleName, const std::pair<std::string, std::string>& attrPair) {
        auto svgDom = weakSvgDom.Upgrade();
        CHECK_NULL_VOID(svgDom);
        if (svgDom->svgContext_) {
            svgDom->svgContext_->PushStyle(styleName, attrPair);
        }
    };
}

SvgDom::~SvgDom() {}

RefPtr<SvgDom> SvgDom::CreateSvgDom(SkStream& svgStream, const std::optional<Color>& color)
{
    RefPtr<SvgDom> svgDom = AceType::MakeRefPtr<SvgDom>();
    if (color) {
        svgDom->fillColor_ = color;
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
    CHECK_NULL_RETURN_NOLOG(svgContext_, false);
    if (!xmlDom.build(svgStream)) {
        LOGE("Failed to parse xml file.");
        return false;
    }
    root_ = TranslateSvgNode(xmlDom, xmlDom.getRootNode(), nullptr);
    CHECK_NULL_RETURN_NOLOG(root_, false);
    auto svg = AceType::DynamicCast<SvgSvg>(root_);
    CHECK_NULL_RETURN_NOLOG(svg, false);
    svgSize_ = svg->GetSize();
    viewBox_ = svg->GetViewBox();
    svgContext_->SetRootViewBox(viewBox_);
    root_->InitStyle(nullptr);
    return true;
}

RefPtr<SvgNode> SvgDom::TranslateSvgNode(const SkDOM& dom, const SkDOM::Node* xmlNode, const RefPtr<SvgNode>& parent)
{
    const char* element = dom.getName(xmlNode);
    if (dom.getType(xmlNode) == SkDOM::kText_Type) {
        CHECK_NULL_RETURN_NOLOG(parent, nullptr);
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
    CHECK_NULL_RETURN_NOLOG(node, nullptr);
    node->SetContext(svgContext_);
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
    const char* name = nullptr;
    const char* value = nullptr;
    SkDOM::AttrIter attrIter(xmlDom, xmlNode);
    while ((name = attrIter.next(&value))) {
        SetAttrValue(name, value, svgNode);
    }
}

void SvgDom::ParseIdAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value)
{
    auto svgNode = weakSvgNode.Upgrade();
    CHECK_NULL_VOID(svgNode);
    svgNode->SetNodeId(value);
    svgNode->SetAttr(DOM_ID, value);
    svgContext_->Push(value, svgNode);
}

void SvgDom::ParseFillAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value)
{
    auto svgNode = weakSvgNode.Upgrade();
    CHECK_NULL_VOID(svgNode);
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
    CHECK_NULL_VOID(svgNode);
    std::vector<std::string> styleNameVector;
    StringUtils::SplitStr(value, " ", styleNameVector);
    for (const auto& styleName : styleNameVector) {
        auto attrMap = svgContext_->GetAttrMap(styleName);
        if (attrMap.empty()) {
            continue;
        }
        for (const auto& attr : attrMap) {
            svgNode->SetAttr(attr.first, attr.second);
        }
    }
}

void SvgDom::ParseStyleAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value)
{
    auto svgNode = weakSvgNode.Upgrade();
    CHECK_NULL_VOID(svgNode);
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
        { DOM_SVG_CLASS, [](const std::string& val, const WeakPtr<SvgNode>& svgNode,
                             SvgDom& svgDom) { svgDom.ParseClassAttr(svgNode, val); } },
        { DOM_SVG_FILL, [](const std::string& val, const WeakPtr<SvgNode>& svgNode,
                            SvgDom& svgDom) { svgDom.ParseFillAttr(svgNode, val); } },
        { DOM_ID, [](const std::string& val, const WeakPtr<SvgNode>& svgNode,
                      SvgDom& svgDom) { svgDom.ParseIdAttr(svgNode, val); } },
        { DOM_SVG_STYLE, [](const std::string& val, const WeakPtr<SvgNode>& svgNode,
                             SvgDom& svgDom) { svgDom.ParseStyleAttr(svgNode, val); } },
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

void SvgDom::SetFuncNormalizeToPx(FuncNormalizeToPx&& funcNormalizeToPx)
{
    CHECK_NULL_VOID_NOLOG(svgContext_);
    svgContext_->SetFuncNormalizeToPx(funcNormalizeToPx);
}

void SvgDom::SetAnimationCallback(FuncAnimateFlush&& funcAnimateFlush, const WeakPtr<CanvasImage>& imagePtr)
{
    CHECK_NULL_VOID_NOLOG(svgContext_);
    svgContext_->SetFuncAnimateFlush(std::move(funcAnimateFlush), imagePtr);
}

void SvgDom::ControlAnimation(bool play)
{
    CHECK_NULL_VOID_NOLOG(svgContext_);
    svgContext_->ControlAnimators(play);
}

bool SvgDom::IsStatic()
{
    return svgContext_->GetAnimatorCount() == 0;
}

void SvgDom::DrawImage(
    RSCanvas& canvas, const ImageFit& imageFit, const Size& layout, const std::optional<Color>&)
{
    CHECK_NULL_VOID_NOLOG(root_);
    canvas.Save();
    // viewBox scale and imageFit scale
    FitImage(canvas, imageFit, layout);
    FitViewPort(layout);
    // draw svg tree
    root_->Draw(canvas, layout, fillColor_);
    canvas.Restore();
}

void SvgDom::FitImage(RSCanvas& canvas, const ImageFit& imageFit, const Size& layout)
{
    // scale svg to layout_ with ImageFit applied
    double scaleX = 1.0;
    double scaleY = 1.0;

    float scaleViewBox = 1.0;
    float tx = 0.0;
    float ty = 0.0;
    constexpr float half = 0.5f;

    if (!layout.IsEmpty()) {
        layout_ = layout;
    }
    if (!layout_.IsEmpty() && (svgSize_.IsValid() && !svgSize_.IsInfinite())) {
        ApplyImageFit(imageFit, scaleX, scaleY);
    }
    /*
     * 1. viewBox_, svgSize_, and layout_ are on 3 different scales.
     * 2. Elements are painted in viewBox_ scale but displayed in layout_ scale.
     * 3. To center align svg content, we first align viewBox_ to svgSize_, then we align svgSize_ to layout_.
     * 4. Canvas is initially in layout_ scale, so transformation (tx, ty) needs to be in that scale, too.
     */
    if (viewBox_.IsValid()) {
        if (svgSize_.IsValid() && !svgSize_.IsInfinite()) {
            // center align viewBox_ to svg, need to map viewBox_ to the scale of svgSize_
            scaleViewBox = std::min(svgSize_.Width() / viewBox_.Width(), svgSize_.Height() / viewBox_.Height());
            tx = svgSize_.Width() * half - (viewBox_.Width() * half + viewBox_.Left()) * scaleViewBox;
            ty = svgSize_.Height() * half - (viewBox_.Height() * half + viewBox_.Top()) * scaleViewBox;
            // map transformation to layout_ scale
            tx *= scaleX;
            ty *= scaleY;

            // center align svg to layout container
            tx += (layout_.Width() - svgSize_.Width() * scaleX) * half;
            ty += (layout_.Height() - svgSize_.Height() * scaleY) * half;
        } else if (!layout_.IsEmpty()) {
            // no svgSize_, center align viewBox to layout container
            scaleViewBox = std::min(layout_.Width() / viewBox_.Width(), layout_.Height() / viewBox_.Height());
            tx = layout_.Width() * half - (viewBox_.Width() * half + viewBox_.Left()) * scaleViewBox;
            ty = layout_.Height() * half - (viewBox_.Height() * half + viewBox_.Top()) * scaleViewBox;
        } else {
            LOGW("FitImage containerSize and svgSize is null");
        }
    }
    RSRect clipRect(0.0f, 0.0f, layout_.Width(), layout_.Height());
    if (radius_) {
        ImagePainterUtils::ClipRRect(canvas, clipRect, *radius_);
    } else {
        canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
    }

    canvas.Translate(tx, ty);

    if (NearZero(scaleX) || NearZero(scaleViewBox) || NearZero(scaleY)) {
        return;
    }
    canvas.Scale(scaleX * scaleViewBox, scaleY * scaleViewBox);
}

void SvgDom::FitViewPort(const Size& layout)
{
    // 设置svg内置视口，用于路径遍历
    auto viewPort = (svgSize_.IsValid() && !svgSize_.IsInfinite()) ? svgSize_ : layout;
    if (svgContext_) {
        svgContext_->SetViewPort(viewPort);
    }
}

SizeF SvgDom::GetContainerSize() const
{
    return { static_cast<float>(svgSize_.Width()), static_cast<float>(svgSize_.Height()) };
}

void SvgDom::SetFillColor(const std::optional<Color>& color)
{
    fillColor_ = color;
}
} // namespace OHOS::Ace::NG
