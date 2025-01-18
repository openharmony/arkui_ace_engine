/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/svg/parse/svg_node.h"

#include "include/core/SkClipOp.h"

#include "core/components/common/painter/rosen_svg_painter.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/base/svg_length_scale_rule.h"
#include "core/components_ng/svg/parse/svg_animation.h"
#include "core/components_ng/svg/parse/svg_attributes_parser.h"
#include "core/components_ng/svg/parse/svg_constants.h"
#include "core/components_ng/svg/parse/svg_filter.h"
#include "core/components_ng/svg/parse/svg_mask.h"
#include "core/components_ng/svg/parse/svg_clip_path.h"
#include "core/components_ng/svg/parse/svg_gradient.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

constexpr size_t SVG_ATTR_ID_FLAG_NUMS = 6;
const char VALUE_NONE[] = "none";
const char ATTR_NAME_OPACITY[] = "opacity";
const char DOM_SVG_SRC_FILL_OPACITY[] = "fill-opacity";
const char DOM_SVG_SRC_FILL_RULE[] = "fill-rule";
const char DOM_SVG_SRC_STROKE_DASHARRAY[] = "stroke-dasharray";
const char DOM_SVG_SRC_STROKE_DASHOFFSET[] = "stroke-dashoffset";
const char DOM_SVG_SRC_STROKE_LINECAP[] = "stroke-linecap";
const char DOM_SVG_SRC_STROKE_LINEJOIN[] = "stroke-linejoin";
const char DOM_SVG_SRC_STROKE_MITERLIMIT[] = "stroke-miterlimit";
const char DOM_SVG_SRC_STROKE_OPACITY[] = "stroke-opacity";
const char DOM_SVG_SRC_STROKE_WIDTH[] = "stroke-width";
const char DOM_SVG_SRC_CLIP_PATH[] = "clip-path";
const char DOM_SVG_SRC_CLIP_RULE[] = "clip-rule";
const char DOM_SVG_SRC_TRANSFORM_ORIGIN[] = "transform-origin";

std::string ParseIdFromUrl(const std::string& url)
{
    if (url.size() > SVG_ATTR_ID_FLAG_NUMS) {
        std::string::size_type start = url.find("url(#");
        if (start != std::string::npos) {
            start += std::strlen("url(#");
            std::string::size_type end = url.find_first_of(')', start);
            if (end != std::string::npos) {
                return url.substr(start, end - start);
            }
        }
    }
    return "";
}

const std::unordered_map<std::string, std::function<Color(SvgBaseAttribute&)>> COLOR_GETTERS = {
    { ATTR_NAME_FILL,
        [](SvgBaseAttribute& attr) -> Color { return attr.fillState.GetColor(); } },
    { ATTR_NAME_STROKE,
        [](SvgBaseAttribute& attr) -> Color { return attr.strokeState.GetColor(); } },
};

const std::unordered_map<std::string, std::function<Dimension(SvgBaseAttribute&)>> DIMENSION_GETTERS = {
    { ATTR_NAME_STROKE_WIDTH,
        [](SvgBaseAttribute& attr) -> Dimension {
            return attr.strokeState.GetLineWidth();
        } },
};

const std::unordered_map<std::string, std::function<double(SvgBaseAttribute&)>> DOUBLE_GETTERS = {
    { ATTR_NAME_FILL_OPACITY,
        [](SvgBaseAttribute& attr) -> double {
            return attr.fillState.GetOpacity().GetValue();
        } },
    { ATTR_NAME_STROKE_OPACITY,
        [](SvgBaseAttribute& attr) -> double {
            return attr.strokeState.GetOpacity().GetValue();
        } },
    { ATTR_NAME_MITER_LIMIT,
        [](SvgBaseAttribute& attr) -> double {
            return attr.strokeState.GetMiterLimit();
        } },
    { ATTR_NAME_STROKE_DASH_OFFSET,
        [](SvgBaseAttribute& attr) -> double {
            return attr.strokeState.GetLineDash().dashOffset;
        } },
    { ATTR_NAME_OPACITY,
        [](SvgBaseAttribute& attr) -> double {
            return attr.opacity * (1.0 / UINT8_MAX);
        } },
};

std::string GetNodeIdFromUrl(const std::string& url)
{
    return std::regex_replace(url, std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"), "$1");
}

void SetCompatibleFill(const std::string& value, SvgBaseAttribute& attrs)
{
    if (value.find("url(") == 0) {
        attrs.fillState.SetHref(GetNodeIdFromUrl(value));
        return;
    }
    attrs.fillState.SetColor((value == VALUE_NONE ? Color::TRANSPARENT : SvgAttributesParser::GetColor(value)));
}

void SetCompatibleStroke(const std::string& value, SvgBaseAttribute& attrs)
{
    if (value.find("url(") == 0) {
        attrs.strokeState.SetHref(GetNodeIdFromUrl(value));
        return;
    }
    attrs.strokeState.SetColor((value == VALUE_NONE ? Color::TRANSPARENT : SvgAttributesParser::GetColor(value)));
}
} // namespace

uint8_t OpacityDoubleToUint8(double opacity)
{
    return static_cast<uint8_t>(std::round(opacity * UINT8_MAX));
}

void SvgNode::SetAttr(const std::string& name, const std::string& value)
{
    if (ParseAndSetSpecializedAttr(name, value)) {
        return;
    }
    static const LinearMapNode<void (*)(const std::string&, SvgBaseAttribute&)> SVG_BASE_ATTRS[] = {
        { DOM_SVG_SRC_CLIP_PATH,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                auto value = StringUtils::TrimStr(val);
                if (value.find("url(") == 0) {
                    auto src = std::regex_replace(value,
                        std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"), "$1");
                    attrs.clipState.SetHref(src);
                }
            } },
        { DOM_SVG_SRC_CLIP_RULE,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.clipState.SetClipRule(val == "evenodd" ? SvgRuleType::SVG_RULE_EVENODD :
                    SvgRuleType::SVG_RULE_NONEZERO);
            } },
        { DOM_CLIP_PATH,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                auto value = StringUtils::TrimStr(val);
                if (value.find("url(") == 0) {
                    auto src = std::regex_replace(value,
                        std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"), "$1");
                    attrs.clipState.SetHref(src);
                }
            } },
        { SVG_CLIP_PATH_UNITS,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.clipState.SetClipPathUnits((val == "objectBoundingBox") ?
                    SvgLengthScaleUnit::OBJECT_BOUNDING_BOX : SvgLengthScaleUnit::USER_SPACE_ON_USE);
            } },
        { SVG_CLIP_RULE,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.clipState.SetClipRule(val == "evenodd" ? SvgRuleType::SVG_RULE_EVENODD :
                    SvgRuleType::SVG_RULE_NONEZERO);
            } },
        { SVG_FILL,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                auto value = StringUtils::TrimStr(val);
                if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
                    SetCompatibleFill(value, attrs);
                    return;
                }
                Color color;
                if (val == VALUE_NONE || SvgAttributesParser::ParseColor(value, color)) {
                    attrs.fillState.SetColor((val == VALUE_NONE ? Color::TRANSPARENT : color));
                    attrs.fillState.SetIsFillNone(val == VALUE_NONE);
                    return;
                }
                if (value.find("url(") == 0) {
                    auto src = std::regex_replace(value,
                        std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"), "$1");
                    attrs.fillState.SetHref(src);
                }
            } },
        { DOM_SVG_SRC_FILL_OPACITY,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.fillState.SetOpacity(std::clamp(StringUtils::StringToDouble(val), 0.0, 1.0));
            } },
        { DOM_SVG_SRC_FILL_RULE,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.fillState.SetFillRule(val);
            } },
        { SVG_FILL_OPACITY,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.fillState.SetOpacity(std::clamp(StringUtils::StringToDouble(val), 0.0, 1.0));
            } },
        { SVG_FILL_RULE,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.fillState.SetFillRule(val);
            } },
        { SVG_FILTER,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.filterId = val;
            } },
        { SVG_FONT_SIZE,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                Dimension fontSize = StringUtils::StringToDimension(val);
                if (GreatOrEqual(fontSize.Value(), 0.0)) {
                    attrs.textStyle.SetFontSize(fontSize);
                }
            } },
        { SVG_HREF,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                auto value = StringUtils::TrimStr(val);
                if (value.substr(0, 1) == "#") {
                    attrs.href = value.substr(1);
                }
            } },
        { SVG_MASK,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.maskId = val;
            } },
        { SVG_OPACITY,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.hasOpacity = true;
                attrs.opacity = std::clamp(StringUtils::StringToDouble(val), 0.0, 1.0);
            } },
        { SVG_PATTERN_TRANSFORM,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.transform = val;
            } },
        { SVG_STROKE,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                auto value = StringUtils::TrimStr(val);
                if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
                    SetCompatibleStroke(value, attrs);
                    return;
                }
                Color color;
                if (val == VALUE_NONE || SvgAttributesParser::ParseColor(value, color)) {
                    attrs.strokeState.SetColor((val == VALUE_NONE ? Color::TRANSPARENT : color));
                    return;
                }
                if (value.find("url(") == 0) {
                    auto src = std::regex_replace(value,
                        std::regex(R"(^url\(\s*['"]?\s*#([^()]+?)\s*['"]?\s*\)$)"), "$1");
                    attrs.strokeState.SetHref(src);
                }
            } },
        { DOM_SVG_SRC_STROKE_DASHARRAY,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                if (val.empty()) {
                    return;
                }
                std::vector<double> lineDashVector;
                std::string handledStr = StringUtils::ReplaceChar(val, ',', ' ');
                StringUtils::StringSplitter(handledStr, ' ', lineDashVector);
                attrs.strokeState.SetLineDash(lineDashVector);
            } },
        { DOM_SVG_SRC_STROKE_DASHOFFSET,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.strokeState.SetLineDashOffset(StringUtils::StringToDouble(val));
            } },
        { DOM_SVG_SRC_STROKE_LINECAP,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.strokeState.SetLineCap(SvgAttributesParser::GetLineCapStyle(val));
            } },
        { DOM_SVG_SRC_STROKE_LINEJOIN,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.strokeState.SetLineJoin(SvgAttributesParser::GetLineJoinStyle(val));
            } },
        { DOM_SVG_SRC_STROKE_MITERLIMIT,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                double miterLimit = StringUtils::StringToDouble(val);
                if (GreatOrEqual(miterLimit, 1.0)) {
                    attrs.strokeState.SetMiterLimit(miterLimit);
                }
            } },
        { DOM_SVG_SRC_STROKE_OPACITY,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.strokeState.SetOpacity(std::clamp(StringUtils::StringToDouble(val), 0.0, 1.0));
            } },
        { DOM_SVG_SRC_STROKE_WIDTH,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                Dimension lineWidth = StringUtils::StringToDimension(val);
                if (GreatOrEqual(lineWidth.Value(), 0.0)) {
                    attrs.strokeState.SetLineWidth(lineWidth);
                }
            } },
        { SVG_STROKE_DASHARRAY,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                if (val.empty()) {
                    return;
                }
                std::vector<double> lineDashVector;
                StringUtils::StringSplitter(val, ' ', lineDashVector);
                attrs.strokeState.SetLineDash(lineDashVector);
            } },
        { SVG_STROKE_DASHOFFSET,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.strokeState.SetLineDashOffset(StringUtils::StringToDouble(val));
            } },
        { SVG_STROKE_LINECAP,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.strokeState.SetLineCap(SvgAttributesParser::GetLineCapStyle(val));
            } },
        { SVG_STROKE_LINEJOIN,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.strokeState.SetLineJoin(SvgAttributesParser::GetLineJoinStyle(val));
            } },
        { SVG_STROKE_MITERLIMIT,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                double miterLimit = StringUtils::StringToDouble(val);
                if (GreatOrEqual(miterLimit, 1.0)) {
                    attrs.strokeState.SetMiterLimit(miterLimit);
                }
            } },
        { SVG_STROKE_OPACITY,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.strokeState.SetOpacity(std::clamp(StringUtils::StringToDouble(val), 0.0, 1.0));
            } },
        { SVG_STROKE_WIDTH,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                Dimension lineWidth = StringUtils::StringToDimension(val);
                if (GreatOrEqual(lineWidth.Value(), 0.0)) {
                    attrs.strokeState.SetLineWidth(lineWidth);
                }
            } },
        { SVG_TRANSFORM,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.transform = val;
            } },
        { DOM_SVG_SRC_TRANSFORM_ORIGIN,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                attrs.transformOrigin = val;
            } },
        { SVG_XLINK_HREF,
            [](const std::string& val, SvgBaseAttribute& attrs) {
                auto value = StringUtils::TrimStr(val);
                if (value.substr(0, 1) == "#") {
                    attrs.href = value.substr(1);
                }
            } }
    };
    auto attrIter = BinarySearchFindIndex(SVG_BASE_ATTRS, ArraySize(SVG_BASE_ATTRS), name.c_str());
    if (attrIter != -1) {
        SVG_BASE_ATTRS[attrIter].value(value, attributes_);
    }
}

RSPath SvgNode::AsRSPath(const Size& viewPort) const
{
    return {};
}

void SvgNode::InitStyle(const SvgBaseAttribute& attr)
{
    InheritAttr(attr);
    if (hrefFill_) {
        auto href = attributes_.fillState.GetHref();
        if (!href.empty()) {
            auto gradient = GetGradient(href);
            if (gradient) {
                attributes_.fillState.SetGradient(gradient.value());
            }
        }
        href = attributes_.strokeState.GetHref();
        if (!href.empty()) {
            auto gradient = GetGradient(href);
            if (gradient) {
                attributes_.strokeState.SetGradient(gradient.value());
            }
        }
    }
    if (hrefRender_) {
        hrefClipPath_ = attributes_.clipState.GetHref();
        opacity_ = OpacityDoubleToUint8(attributes_.opacity);
        transform_ = attributes_.transform;
        hrefMaskId_ = ParseIdFromUrl(attributes_.maskId);
        hrefFilterId_ = ParseIdFromUrl(attributes_.filterId);
    }
    OnInitStyle();
    if (passStyle_) {
        for (auto& node : children_) {
            CHECK_NULL_VOID(node);
            // pass down style only if child inheritStyle_ is true
            node->InitStyle((node->inheritStyle_) ? attributes_ : SvgBaseAttribute());
        }
    }
    for (auto& child : children_) {
        auto svgAnimate = DynamicCast<SvgAnimation>(child);
        if (svgAnimate) {
            svgAnimate->UpdateAttr();
            PrepareAnimation(svgAnimate);
        }
    }
}

void SvgNode::Draw(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    if (!OnCanvas(canvas)) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Svg Draw failed(Reason: Canvas is null).");
        return;
    }
    // mask and filter create extra layers, need to record initial layer count
    auto count = rsCanvas_->GetSaveCount();
    rsCanvas_->Save();
    if (!hrefClipPath_.empty()) {
        OnClipPath(canvas, viewPort);
    } else if (isRootNode_) {
        AdjustContentAreaByViewBox(canvas, viewPort);
    }
    if (!transform_.empty() || !animateTransform_.empty()) {
        OnTransform(canvas, viewPort);
    }
    if (!hrefMaskId_.empty()) {
        OnMask(canvas, viewPort);
    }
    if (!hrefFilterId_.empty()) {
        OnFilter(canvas, viewPort);
    }

    OnDraw(canvas, viewPort, color);
    OnDrawTraversed(canvas, viewPort, color);
    rsCanvas_->RestoreToCount(count);
}

void SvgNode::Draw(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule)
{
    // mask and filter create extra layers, need to record initial layer count
    auto count = canvas.GetSaveCount();
    canvas.Save();
    auto rsBounds = AsPath(lengthRule).GetBounds();
    Rect boundingRect(rsBounds.GetLeft(), rsBounds.GetTop(), rsBounds.GetWidth(), rsBounds.GetHeight());
    SvgCoordinateSystemContext svgCoordinateSystemContext(boundingRect, GetSvgContainerRect());
    TAG_LOGD(AceLogTag::ACE_IMAGE, "l:%{public}lf, t:%{public}lf, r:%{public}lf, b:%{public}lf, units:%{public}d",
        rsBounds.GetLeft(), rsBounds.GetTop(), rsBounds.GetRight(), rsBounds.GetBottom(),
        (int)lengthRule.GetLengthScaleUnit());
    if (!hrefClipPath_.empty()) {
        OnClipPath(canvas, svgCoordinateSystemContext);
    } else if (isRootNode_) {
        auto svgContext = svgContext_.Upgrade();
        if (svgContext) {
            AdjustContentAreaByViewBox(canvas, svgContext->GetViewPort());
        }
    }
    if (!transform_.empty() || !animateTransform_.empty()) {
        OnTransform(canvas);
    }
    if (!hrefMaskId_.empty()) {
        OnMask(canvas, svgCoordinateSystemContext);
    }
    if (!hrefFilterId_.empty()) {
        OnFilter(canvas, svgCoordinateSystemContext);
    }

    OnDraw(canvas, lengthRule);
    OnDrawTraversed(canvas, lengthRule);
    canvas.RestoreToCount(count);
}

void SvgNode::OnDrawTraversed(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    auto smoothEdge = GetSmoothEdge();
    auto colorFilter = GetColorFilter();
    for (auto& node : children_) {
        if (node && node->drawTraversed_) {
            if (GreatNotEqual(smoothEdge, 0.0f)) {
                node->SetSmoothEdge(smoothEdge);
            }
            node->SetColorFilter(colorFilter);
            node->Draw(canvas, viewPort, color);
        }
    }
}

void SvgNode::OnDrawTraversed(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule)
{
    auto smoothEdge = GetSmoothEdge();
    auto colorFilter = GetColorFilter();
    for (auto& node : children_) {
        if (node && node->drawTraversed_) {
            if (GreatNotEqual(smoothEdge, 0.0f)) {
                node->SetSmoothEdge(smoothEdge);
            }
            node->SetColorFilter(colorFilter);
            node->Draw(canvas, lengthRule);
        }
    }
}

bool SvgNode::OnCanvas(RSCanvas& canvas)
{
    rsCanvas_ = &canvas;
    return true;
}

void SvgNode::OnClipPath(RSCanvas& canvas, const Size& viewPort)
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_VOID(svgContext);
    auto refSvgNode = svgContext->GetSvgNodeById(hrefClipPath_);
    CHECK_NULL_VOID(refSvgNode);
    auto clipPath = refSvgNode->AsPath(viewPort);
    if (!clipPath.IsValid()) {
        LOGW("OnClipPath abandon, clipPath is empty");
        return;
    }
    rsCanvas_->ClipPath(clipPath, RSClipOp::INTERSECT, true);
}

void SvgNode::OnClipPath(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_VOID(svgContext);
    auto refSvgNode = svgContext->GetSvgNodeById(hrefClipPath_);
    CHECK_NULL_VOID(refSvgNode);
    if (!AceType::InstanceOf<SvgClipPath>(refSvgNode)) {
        return;
    }
    refSvgNode->OnClipEffect(canvas, svgCoordinateSystemContext);
}

void SvgNode::OnFilter(RSCanvas& canvas, const Size& viewPort)
{
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_VOID(svgContext);
    auto refFilter = svgContext->GetSvgNodeById(hrefFilterId_);
    CHECK_NULL_VOID(refFilter);
    auto effectPath = AsPath(viewPort);
    auto bounds = effectPath.GetBounds();
    refFilter->SetEffectFilterArea({
        useOffsetX_ + bounds.GetLeft(), useOffsetY_ + bounds.GetTop(),
        bounds.GetWidth(), bounds.GetHeight()
    });
    refFilter->Draw(canvas, viewPort, std::nullopt);
    return;
}

void SvgNode::OnFilter(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_VOID(svgContext);
    auto refFilter = svgContext->GetSvgNodeById(hrefFilterId_);
    CHECK_NULL_VOID(refFilter);
    if (!AceType::InstanceOf<SvgFilter>(refFilter)) {
        return;
    }
    refFilter->OnFilterEffect(canvas, svgCoordinateSystemContext);
}

void SvgNode::OnMask(RSCanvas& canvas, const Size& viewPort)
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_VOID(svgContext);
    auto refMask = svgContext->GetSvgNodeById(hrefMaskId_);
    CHECK_NULL_VOID(refMask);
    refMask->Draw(canvas, viewPort, std::nullopt);
    return;
}

void SvgNode::OnMask(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_VOID(svgContext);
    auto refMask = svgContext->GetSvgNodeById(hrefMaskId_);
    CHECK_NULL_VOID(refMask);
    if (!AceType::InstanceOf<SvgMask>(refMask)) {
        return;
    }
    refMask->OnMaskEffect(canvas, svgCoordinateSystemContext);
}

void SvgNode::OnTransform(RSCanvas& canvas, const Size& viewPort)
{
    auto matrix = (animateTransform_.empty()) ? SvgTransform::CreateMatrix4(transform_)
                                              : SvgTransform::CreateMatrixFromMap(animateTransform_);
    rsCanvas_->ConcatMatrix(RosenSvgPainter::ToDrawingMatrix(matrix));
}

void SvgNode::OnTransform(RSCanvas& canvas)
{
    auto matrix = (animateTransform_.empty()) ? SvgTransform::CreateMatrix4(transform_)
                                              : SvgTransform::CreateMatrixFromMap(animateTransform_);
    canvas.ConcatMatrix(RosenSvgPainter::ToDrawingMatrix(matrix));
}

float SvgNode::GetMeasuredLength(Dimension origin, const SvgLengthScaleRule& boxMeasureRule, SvgLengthType lengthType)
{
    switch (lengthType) {
        case SvgLengthType::HORIZONTAL: {
            auto x = (boxMeasureRule.GetLengthScaleUnit() == SvgLengthScaleUnit::USER_SPACE_ON_USE) ?
                     ConvertDimensionToPx(origin, GetSvgContainerRect().Width()) :
                     origin.Value() * boxMeasureRule.GetBaseRect().Width();
            return x;
        }
        case SvgLengthType::VERTICAL: {
            auto y = (boxMeasureRule.GetLengthScaleUnit() == SvgLengthScaleUnit::USER_SPACE_ON_USE) ?
                     ConvertDimensionToPx(origin, GetSvgContainerRect().Height()) :
                     origin.Value() * boxMeasureRule.GetBaseRect().Height();
            return y;
        }
        /*using the original definition, radius*/
        case SvgLengthType::OTHER: {
            auto width = boxMeasureRule.GetBaseRect().Width();
            auto height = boxMeasureRule.GetBaseRect().Height();
            auto baseLength = std::sqrt(width * width + height * height) / std::sqrt(2.0f);
            return boxMeasureRule.GetLengthScaleUnit() == SvgLengthScaleUnit::USER_SPACE_ON_USE ?
                ConvertDimensionToPx(origin, baseLength) : origin.Value() * baseLength;
        }
    }
    return 0.0f;
}

float SvgNode::GetMeasuredPosition(Dimension origin, const SvgLengthScaleRule& boxMeasureRule,
    SvgLengthType lengthType)
{
    switch (lengthType) {
        case SvgLengthType::HORIZONTAL: {
            auto x = (boxMeasureRule.GetLengthScaleUnit() == SvgLengthScaleUnit::USER_SPACE_ON_USE) ?
                     ConvertDimensionToPx(origin, GetSvgContainerRect().Width()) :
                     origin.Value() * boxMeasureRule.GetBaseRect().Width() + boxMeasureRule.GetBaseRect().Left();
            return x;
        }
        case SvgLengthType::VERTICAL: {
            auto y = (boxMeasureRule.GetLengthScaleUnit() == SvgLengthScaleUnit::USER_SPACE_ON_USE) ?
                     ConvertDimensionToPx(origin, GetSvgContainerRect().Height()) :
                     origin.Value() * boxMeasureRule.GetBaseRect().Height() + boxMeasureRule.GetBaseRect().Top();
            return y;
        }
        default:
            return 0.0f;
    }
}

double SvgNode::ConvertDimensionToPx(const Dimension& value, const Size& viewPort, SvgLengthType type) const
{
    switch (value.Unit()) {
        case DimensionUnit::PERCENT: {
            if (type == SvgLengthType::HORIZONTAL) {
                return value.Value() * viewPort.Width();
            }
            if (type == SvgLengthType::VERTICAL) {
                return value.Value() * viewPort.Height();
            }
            if (type == SvgLengthType::OTHER) {
                return value.Value() * sqrt(viewPort.Width() * viewPort.Height());
            }
            return 0.0;
        }
        case DimensionUnit::PX:
            return value.Value();
        default:
            auto svgContext = svgContext_.Upgrade();
            if (svgContext) {
                return svgContext->NormalizeToPx(value);
            }
            return 0.0;
    }
}

double SvgNode::ConvertDimensionToPx(const Dimension& value, double baseValue) const
{
    if (value.Unit() == DimensionUnit::PERCENT) {
        return value.Value() * baseValue;
    }
    if (value.Unit() == DimensionUnit::PX) {
        return value.Value();
    }
    auto svgContext = svgContext_.Upgrade();
    if (svgContext) {
        return svgContext->NormalizeToPx(value);
    }
    return 0.0;
}

std::optional<Ace::Gradient> SvgNode::GetGradient(const std::string& href)
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_RETURN(svgContext, std::nullopt);
    if (href.empty()) {
        return std::nullopt;
    }
    auto refSvgNode = svgContext->GetSvgNodeById(href);
    CHECK_NULL_RETURN(refSvgNode, std::nullopt);
    auto svgGradient = DynamicCast<SvgGradient>(refSvgNode);
    if (svgGradient) {
        return std::make_optional(svgGradient->GetGradient());
    }
    return std::nullopt;
}

Rect SvgNode::GetSvgContainerRect() const
{
    auto svgContext = svgContext_.Upgrade();
    if (!svgContext) {
        LOGE("Gradient failed, svgContext is null");
        static Rect empty;
        return empty;
    }
    return Rect(0, 0, svgContext->GetViewPort().Width(), svgContext->GetViewPort().Height());
}

const Rect& SvgNode::GetRootViewBox() const
{
    auto svgContext = svgContext_.Upgrade();
    if (!svgContext) {
        LOGE("Gradient failed, svgContext is null");
        static Rect empty;
        return empty;
    }
    return svgContext->GetRootViewBox();
}

void SvgNode::PrepareAnimation(const RefPtr<SvgAnimation>& animate)
{
    auto attrName = animate->GetAttributeName();
    if (COLOR_GETTERS.find(attrName) != COLOR_GETTERS.end()) {
        Color originalValue = COLOR_GETTERS.find(attrName)->second(attributes_);
        AnimateOnAttribute(animate, originalValue);
    } else if (DIMENSION_GETTERS.find(attrName) != DIMENSION_GETTERS.end()) {
        Dimension originalValue = DIMENSION_GETTERS.find(attrName)->second(attributes_);
        AnimateOnAttribute(animate, originalValue);
    } else if (DOUBLE_GETTERS.find(attrName) != DOUBLE_GETTERS.end()) {
        double originalValue = DOUBLE_GETTERS.find(attrName)->second(attributes_);
        AnimateOnAttribute(animate, originalValue);
    } else if (attrName.find(TRANSFORM) != std::string::npos) {
        AnimateTransform(animate, 0.0f);
    } else {
        LOGW("animation attrName not valid: %s", attrName.c_str());
    }
}

// create animation callback
template<typename T>
void SvgNode::AnimateOnAttribute(const RefPtr<SvgAnimation>& animate, const T& originalValue)
{
    std::function<void(T)> callback;
    callback = [weak = WeakClaim(this), attrName = animate->GetAttributeName()](T value) {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->UpdateAttr(attrName, value);
        auto context = self->svgContext_.Upgrade();
        CHECK_NULL_VOID(context);
        context->AnimateFlush();
    };
    animate->CreatePropertyAnimation(originalValue, std::move(callback));
}

// update attribute for svgNode and its children
void SvgNode::UpdateAttrHelper(const std::string& name, const std::string& val)
{
    SetAttr(name, val);
    if (!passStyle_) {
        return;
    }
    for (auto&& child : children_) {
        if (child->inheritStyle_) {
            child->UpdateAttrHelper(name, val);
        }
    }
}

template<typename T>
void SvgNode::UpdateAttr(const std::string& /* name */, const T& /* val */)
{
    LOGW("data type not supported");
}

template<>
void SvgNode::UpdateAttr(const std::string& name, const Color& val)
{
    UpdateAttrHelper(name, val.ColorToString());
}

template<>
void SvgNode::UpdateAttr(const std::string& name, const Dimension& val)
{
    UpdateAttrHelper(name, val.ToString());
}

template<>
void SvgNode::UpdateAttr(const std::string& name, const double& val)
{
    UpdateAttrHelper(name, std::to_string(val));
}

void SvgNode::AnimateTransform(const RefPtr<SvgAnimation>& animate, double originalValue)
{
    if (!animate->GetValues().empty()) {
        AnimateFrameTransform(animate, originalValue);
    } else {
        AnimateFromToTransform(animate, originalValue);
    }
}

void SvgNode::AnimateFrameTransform(const RefPtr<SvgAnimation>& animate, double originalValue)
{
    std::vector<std::vector<float>> frames;
    std::string type;
    if (!animate->GetFrames(frames, type)) {
        LOGE("invalid animate keys info of type %{public}s", type.c_str());
        return;
    }
    if (frames.size() <= 1) {
        LOGE("invalid frames numbers %{public}s", type.c_str());
        return;
    }

    // change Values to frame indices to create an index-based animation
    // property values of each frame are stored in [frames]
    std::vector<std::string> indices;
    uint32_t size = animate->GetValues().size();
    for (uint32_t i = 0; i < size; i++) {
        indices.emplace_back(std::to_string(i));
    }
    animate->SetValues(indices);

    std::function<void(double)> callback = [weak = WeakClaim(this), type, frames](double value) {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        // use index and rate to locate frame and progress
        auto index = static_cast<uint32_t>(value);
        double rate = value - index;
        if (index >= frames.size() - 1) {
            index = frames.size() - 2;
            rate = 1.0;
        }
        if (!SvgTransform::SetProperty(type, frames[index], frames[index + 1], rate, self->animateTransform_)) {
            LOGE("set property failed: property %{public}s not in map", type.c_str());
            return;
        }
        auto context = self->svgContext_.Upgrade();
        CHECK_NULL_VOID(context);
        context->AnimateFlush();
    };
    animate->CreatePropertyAnimation(originalValue, std::move(callback));
}

void SvgNode::AnimateFromToTransform(const RefPtr<SvgAnimation>& animate, double originalValue)
{
    std::vector<float> fromVec;
    std::vector<float> toVec;
    std::string type;
    if (!animate->GetValuesRange(fromVec, toVec, type)) {
        LOGE("invalid animate info of type %{public}s", type.c_str());
        return;
    }

    std::function<void(double)> callback = [weak = WeakClaim(this), type, fromVec, toVec](double value) {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        if (!SvgTransform::SetProperty(type, fromVec, toVec, value, self->animateTransform_)) {
            LOGE("set property failed: property %{public}s not in map", type.c_str());
            return;
        }
        auto context = self->svgContext_.Upgrade();
        CHECK_NULL_VOID(context);
        context->AnimateFlush();
    };
    animate->CreatePropertyAnimation(originalValue, std::move(callback));
}

} // namespace OHOS::Ace::NG