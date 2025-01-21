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

#include "core/components_ng/svg/parse/svg_fe_blend.h"
#include "core/components_ng/svg/parse/svg_fe_flood.h"
#include "frameworks/core/components_ng/render/adapter/image_painter_utils.h"
#include "frameworks/core/components_ng/svg/parse/svg_animation.h"
#include "frameworks/core/components_ng/svg/parse/svg_constants.h"
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
#include "frameworks/core/components_ng/svg/parse/svg_image.h"
#include "frameworks/core/components_ng/svg/parse/svg_line.h"
#include "frameworks/core/components_ng/svg/parse/svg_linear_gradient.h"
#include "frameworks/core/components_ng/svg/parse/svg_mask.h"
#include "frameworks/core/components_ng/svg/parse/svg_path.h"
#include "frameworks/core/components_ng/svg/parse/svg_pattern.h"
#include "frameworks/core/components_ng/svg/parse/svg_polygon.h"
#include "frameworks/core/components_ng/svg/parse/svg_radial_gradient.h"
#include "frameworks/core/components_ng/svg/parse/svg_rect.h"
#include "frameworks/core/components_ng/svg/parse/svg_stop.h"
#include "frameworks/core/components_ng/svg/parse/svg_svg.h"
#include "frameworks/core/components_ng/svg/parse/svg_use.h"
#include "frameworks/core/components_ng/svg/svg_fit_convertor.h"
#include "frameworks/core/components_ng/svg/svg_ulils.h"
#include "core/common/container.h"

namespace OHOS::Ace::NG {
namespace {

const char DOM_SVG_STYLE[] = "style";
const char DOM_SVG_CLASS[] = "class";
constexpr int32_t ONE_BYTE_TO_HEX_LEN = 2;
} // namespace

static const LinearMapNode<RefPtr<SvgNode> (*)()> TAG_FACTORIES[] = {
    { "animate", []() -> RefPtr<SvgNode> { return SvgAnimation::Create(); } },
    { "animateMotion", []() -> RefPtr<SvgNode> { return SvgAnimation::CreateAnimateMotion(); } },
    { "animateTransform", []() -> RefPtr<SvgNode> { return SvgAnimation::CreateAnimateTransform(); } },
    { "circle", []() -> RefPtr<SvgNode> { return SvgCircle::Create(); } },
    { "clipPath", []() -> RefPtr<SvgNode> { return SvgClipPath::Create(); } },
    { "defs", []() -> RefPtr<SvgNode> { return SvgDefs::Create(); } },
    { "ellipse", []() -> RefPtr<SvgNode> { return SvgEllipse::Create(); } },
    { "feBlend", []() -> RefPtr<SvgNode> { return SvgFeBlend::Create(); } },
    { "feColorMatrix", []() -> RefPtr<SvgNode> { return SvgFeColorMatrix::Create(); } },
    { "feComposite", []() -> RefPtr<SvgNode> { return SvgFeComposite::Create(); } },
    { "feFlood", []() -> RefPtr<SvgNode> { return SvgFeFlood::Create(); } },
    { "feGaussianBlur", []() -> RefPtr<SvgNode> { return SvgFeGaussianBlur::Create(); } },
    { "feOffset", []() -> RefPtr<SvgNode> { return SvgFeOffset::Create(); } },
    { "filter", []() -> RefPtr<SvgNode> { return SvgFilter::Create(); } },
    { "g", []() -> RefPtr<SvgNode> { return SvgG::Create(); } },
    { "image", []() -> RefPtr<SvgNode> { return SvgImage::Create(); } },
    { "line", []() -> RefPtr<SvgNode> { return SvgLine::Create(); } },
    { "linearGradient", []() -> RefPtr<SvgNode> {
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
             return SvgGradient::CreateLinearGradient();
        } else {
            return SvgLinearGradient::Create();
        }
        } },
    { "mask", []() -> RefPtr<SvgNode> { return SvgMask::Create(); } },
    { "path", []() -> RefPtr<SvgNode> { return SvgPath::Create(); } },
    { "pattern", []() -> RefPtr<SvgNode> { return SvgPattern::Create(); } },
    { "polygon", []() -> RefPtr<SvgNode> { return SvgPolygon::CreatePolygon(); } },
    { "polyline", []() -> RefPtr<SvgNode> { return SvgPolygon::CreatePolyline(); } },
    { "radialGradient", []() -> RefPtr<SvgNode> {
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
            return SvgGradient::CreateRadialGradient();
        } else {
            return SvgRadialGradient::Create();
        }
        } },
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

RefPtr<SvgDom> SvgDom::CreateSvgDom(SkStream& svgStream, const ImageSourceInfo& src)
{
    RefPtr<SvgDom> svgDom = AceType::MakeRefPtr<SvgDom>();
    svgDom->fillColor_ = src.GetFillColor();
    svgDom->path_ = src.GetSrc();
    bool ret = svgDom->ParseSvg(svgStream);
    if (ret) {
        return svgDom;
    }
    TAG_LOGW(AceLogTag::ACE_IMAGE, "CreateSvgDom Failed(Reason:Svg parse error).");
    return nullptr;
}

bool SvgDom::ParseSvg(SkStream& svgStream)
{
    SkDOM xmlDom;
    CHECK_NULL_RETURN(svgContext_, false);
    if (!xmlDom.build(svgStream)) {
        LOGE("Failed to parse xml file.");
        return false;
    }
    root_ = TranslateSvgNode(xmlDom, xmlDom.getRootNode(), nullptr);
    CHECK_NULL_RETURN(root_, false);
    auto svg = AceType::DynamicCast<SvgSvg>(root_);
    CHECK_NULL_RETURN(svg, false);
    svgSize_ = svg->GetSize();
    viewBox_ = svg->GetViewBox();
    svgContext_->SetRootViewBox(viewBox_);
    return true;
}

RefPtr<SvgNode> SvgDom::TranslateSvgNode(const SkDOM& dom, const SkDOM::Node* xmlNode, const RefPtr<SvgNode>& parent)
{
    auto root = CreateSvgNodeFromDom(dom, xmlNode, parent);
    CHECK_NULL_RETURN(root, nullptr);
    std::stack<SvgTranslateProcessInfo> translateTaskSt;
    translateTaskSt.emplace(root, dom.getFirstChild(xmlNode, nullptr));
    while (!translateTaskSt.empty()) {
        auto& [currentNode, curXmlNode] = translateTaskSt.top();
        if (!curXmlNode) {
            translateTaskSt.pop();
        } else {
            const auto& childNode = CreateSvgNodeFromDom(dom, curXmlNode, currentNode);
            if (childNode) {
                translateTaskSt.emplace(childNode, dom.getFirstChild(curXmlNode, nullptr));
                currentNode->AppendChild(childNode);
            }
            curXmlNode = dom.getNextSibling(curXmlNode);
        }
    }
    return root;
}

RefPtr<SvgNode> SvgDom::CreateSvgNodeFromDom(
    const SkDOM& dom, const SkDOM::Node* xmlNode, const RefPtr<SvgNode>& parent)
{
    const char* element = dom.getName(xmlNode);
    if (dom.getType(xmlNode) == SkDOM::kText_Type) {
        CHECK_NULL_RETURN(parent, nullptr);
        if (AceType::InstanceOf<SvgStyle>(parent)) {
            SvgStyle::ParseCssStyle(element, attrCallback_);
        }
    }

    auto elementIter = BinarySearchFindIndex(TAG_FACTORIES, ArraySize(TAG_FACTORIES), element);
    if (elementIter == -1) {
        return nullptr;
    }
    RefPtr<SvgNode> node = TAG_FACTORIES[elementIter].value();
    CHECK_NULL_RETURN(node, nullptr);
    if (AceType::InstanceOf<SvgAnimation>(node)) {
        isStatic_.store(false);
    }
    node->SetContext(svgContext_);
    node->SetImagePath(path_);
    ParseAttrs(dom, xmlNode, node);
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
    svgNode->SetAttr(DOM_SVG_ID, value);
    svgContext_->Push(value, svgNode);
}

void SvgDom::ParseFillAttr(const WeakPtr<SvgNode>& weakSvgNode, const std::string& value)
{
    auto svgNode = weakSvgNode.Upgrade();
    CHECK_NULL_VOID(svgNode);
    if (fillColor_) {
        std::string newValue;
        std::stringstream stream;
        auto fillColor = fillColor_.value();
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
            stream << std::hex << fillColor.GetValue();
            newValue = stream.str();
        } else {
            //convert color to #rgba format.
            newValue = IntToHexString(fillColor.GetRed()) + IntToHexString(fillColor.GetGreen()) +
                       IntToHexString(fillColor.GetBlue()) + IntToHexString(fillColor.GetAlpha());
        }
        svgNode->SetAttr(SVG_FILL, "#" + newValue);
    } else {
        svgNode->SetAttr(SVG_FILL, value);
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
        { SVG_FILL, [](const std::string& val, const WeakPtr<SvgNode>& svgNode,
                            SvgDom& svgDom) { svgDom.ParseFillAttr(svgNode, val); } },
        { DOM_SVG_ID, [](const std::string& val, const WeakPtr<SvgNode>& svgNode,
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
    CHECK_NULL_VOID(svgContext_);
    svgContext_->SetFuncNormalizeToPx(funcNormalizeToPx);
}

void SvgDom::SetAnimationCallback(FuncAnimateFlush&& funcAnimateFlush, const WeakPtr<CanvasImage>& imagePtr)
{
    CHECK_NULL_VOID(svgContext_);
    svgContext_->SetFuncAnimateFlush(std::move(funcAnimateFlush), imagePtr);
}

void SvgDom::ControlAnimation(bool play)
{
    CHECK_NULL_VOID(svgContext_);
    svgContext_->ControlAnimators(play);
}

bool SvgDom::IsStatic()
{
    return isStatic_;
}

void SvgDom::SetAnimationOnFinishCallback(const std::function<void()>& onFinishCallback)
{
    CHECK_NULL_VOID(svgContext_);
    svgContext_->SetOnAnimationFinished(onFinishCallback);
}

std::string SvgDom::GetDumpInfo()
{
    if (svgContext_) {
        return svgContext_->GetDumpInfo().ToString();
    }
    return "";
}

void SvgDom::InitStyles()
{
    CHECK_NULL_VOID(root_);
    if (!isStyleInited_) {
        isStyleInited_ = true;
        root_->InitStyle(SvgBaseAttribute());
    }
}

void SvgDom::DrawImage(
    RSCanvas& canvas, const ImageFit& imageFit, const Size& layout)
{
    if (!root_ || !svgContext_) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Svg DrawImage. root:%{public}d svgContext_:%{public}d",
            !!root_, !!svgContext_);
        return;
    }
    root_->SetIsRootNode(true);
    InitStyles();
    canvas.Save();
    // viewBox scale and imageFit scale
    FitImage(canvas, imageFit, layout);
    FitViewPort(layout);
    svgContext_->CreateDumpInfo(SvgDumpInfo(svgContext_->GetContentSize(),
        svgContext_->GetCurrentTimeString()));
    // draw svg tree
    if (GreatNotEqual(smoothEdge_, 0.0f)) {
        root_->SetSmoothEdge(smoothEdge_);
    }
    root_->SetColorFilter(colorFilter_);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        root_->Draw(canvas, svgContext_->GetViewPort(), fillColor_);
    } else {
        SvgLengthScaleRule lengthRule(Rect(0, 0, svgContext_->GetViewPort().Width(),
            svgContext_->GetViewPort().Height()), SvgLengthScaleUnit::USER_SPACE_ON_USE);
        svgContext_->SetFillColor(fillColor_);
        root_->Draw(canvas, lengthRule);
    }
    canvas.Restore();
}

void SvgDom::FitImage(RSCanvas& canvas, const ImageFit& imageFit, const Size& layout)
{
    // scale svg to layout_ with ImageFit applied
    if (!layout.IsEmpty()) {
        layout_ = layout;
    }
    RSRect clipRect(0.0f, 0.0f, layout_.Width(), layout_.Height());
    if (radius_) {
        ImagePainterUtils::ClipRRect(canvas, clipRect, *radius_);
    } else {
        canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
    }
    if (!layout_.IsEmpty()) {
        Size svgContentSize;
        SvgUtils::CalculateSvgConentSize(svgContentSize, layout_, svgSize_, viewBox_);
        SvgFitConvertor::ApplyFit(imageFit, canvas, layout_, svgContentSize);
        if (svgContext_) {
            svgContext_->SetContentSize(svgContentSize);
        }
    }
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

void SvgDom::SetSmoothEdge(float value)
{
    smoothEdge_ = value;
}

void SvgDom::SetColorFilter(const std::optional<ImageColorFilter>& colorFilter)
{
    colorFilter_ = colorFilter;
}

std::string SvgDom::IntToHexString(const int number)
{
    std::stringstream stringStream;
    stringStream << std::setw(ONE_BYTE_TO_HEX_LEN) << std::setfill('0') << std::hex << number;
    return stringStream.str();
}
} // namespace OHOS::Ace::NG
