/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/svg/parse/svg_mask.h"

#include "frameworks/core/components/common/painter/rosen_svg_painter.h"
#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {

SvgMask::SvgMask() : SvgQuote() {}

RefPtr<SvgNode> SvgMask::Create()
{
    return AceType::MakeRefPtr<SvgMask>();
}

SvgLengthScaleRule SvgMask::TransformForCurrentOBB(RSCanvas& canvas,
    const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    if (maskAttr_.maskContentUnits == SvgLengthScaleUnit::USER_SPACE_ON_USE) {
        return svgCoordinateSystemContext.BuildScaleRule(SvgLengthScaleUnit::USER_SPACE_ON_USE);
    }
    // create default rect to draw graphic
    Rect defaultRect(0, 0, 1, 1);
    SvgLengthScaleRule maskContentRule = SvgLengthScaleRule(defaultRect, SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);
    auto obb = svgCoordinateSystemContext.GetBoundingBoxRect();
    // scale the graphic content of the given element non-uniformly
    // such that the element's bounding box exactly matches the viewport rectangle.
    canvas.Translate(obb.Left(), obb.Top());
    canvas.Scale(obb.Width(), obb.Height());
    return maskContentRule;
}

void SvgMask::OnMaskEffect(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    auto maskRule = svgCoordinateSystemContext.BuildScaleRule(maskAttr_.maskUnits);
    auto measuredX = GetMeasuredPosition(maskAttr_.x, maskRule, SvgLengthType::HORIZONTAL);
    auto measuredY = GetMeasuredPosition(maskAttr_.y, maskRule, SvgLengthType::VERTICAL);
    auto measuredWidth = GetMeasuredLength(maskAttr_.width, maskRule, SvgLengthType::HORIZONTAL);
    auto measuredHeight = GetMeasuredLength(maskAttr_.height, maskRule, SvgLengthType::VERTICAL);
    Rect maskRect = {
        measuredX,
        measuredY,
        measuredWidth,
        measuredHeight
    };
    RSRect maskBounds(maskRect.Left(), maskRect.Top(), maskRect.Right(), maskRect.Bottom());
    // create mask layer
    RSSaveLayerOps slo(&maskBounds, nullptr);
    canvas.SaveLayer(slo);
    // ready to render mask content
    auto canvasLayerCount = static_cast<int32_t>(canvas.GetSaveCount());
    RosenSvgPainter::SetMask(&canvas);
    auto maskContentRule = TransformForCurrentOBB(canvas, svgCoordinateSystemContext);
    DrawChildren(canvas, maskContentRule);
    canvas.RestoreToCount(canvasLayerCount);
    // create content layer and render content
    RSBrush maskBrush;
    maskBrush.SetBlendMode(RSBlendMode::SRC_IN);
    RSSaveLayerOps slo2(&maskBounds, &maskBrush);
    canvas.SaveLayer(slo2);
    canvas.ClipRect(maskBounds, RSClipOp::INTERSECT, true);
}

void SvgMask::OnDrawTraversedBefore(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    auto nodeBounds = isDefaultMaskUnits_ ? AsBounds(viewPort) : GetRootViewBox();
    RSScalar left = static_cast<RSScalar>(nodeBounds.Left() + ParseUnitsAttr(x_, nodeBounds.Width()));
    RSScalar top = static_cast<RSScalar>(nodeBounds.Top() + ParseUnitsAttr(y_, nodeBounds.Height()));
    RSScalar width = static_cast<RSScalar>(ParseUnitsAttr(width_, nodeBounds.Width()));
    RSScalar height = static_cast<RSScalar>(ParseUnitsAttr(height_, nodeBounds.Height()));
    maskBounds_ = RSRect(left, top, width + left, height + top);
    // create mask layer
    RSSaveLayerOps slo(&maskBounds_, nullptr);
    rsCanvas_->SaveLayer(slo);
    // ready to render mask content
    canvasLayerCount_ = static_cast<int32_t>(rsCanvas_->GetSaveCount());
    RosenSvgPainter::SetMask(rsCanvas_);
}

void SvgMask::OnDrawTraversedAfter(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    rsCanvas_->RestoreToCount(canvasLayerCount_);
    // create content layer and render content
    RSBrush maskBrush;
    maskBrush.SetBlendMode(RSBlendMode::SRC_IN);
    RSSaveLayerOps slo(&maskBounds_, &maskBrush);
    rsCanvas_->SaveLayer(slo);
    rsCanvas_->ClipRect(maskBounds_, RSClipOp::INTERSECT, true);
}

void SvgMask::DrawChildren(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule)
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
void SvgMask::OnInitStyle()
{
    isDefaultMaskUnits_ = (maskAttr_.maskUnits == SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);
    isDefaultMaskContentUnits_ = (maskAttr_.maskContentUnits == SvgLengthScaleUnit::USER_SPACE_ON_USE);
    x_ = maskAttr_.x;
    y_ = maskAttr_.y;
    height_ = maskAttr_.height;
    width_ = maskAttr_.width;
}

double SvgMask::ParseUnitsAttr(const Dimension& attr, double value)
{
    if (isDefaultMaskUnits_) {
        // only support decimal or percent
        if (attr.Unit() == DimensionUnit::PERCENT) {
            return value * attr.Value();
        }
        return attr.Value() * value;
    }
    // percent and px
    if (attr.Unit() == DimensionUnit::PERCENT) {
        return value * attr.Value();
    }
    return attr.Value();
}

bool SvgMask::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgMaskAttribute&)> attrs[] = {
        { SVG_HEIGHT,
            [](const std::string& val, SvgMaskAttribute& attr) {
                attr.height = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_MASK_CONTENT_UNITS,
            [](const std::string& val, SvgMaskAttribute& attr) {
                attr.maskContentUnits = (val == "objectBoundingBox") ? SvgLengthScaleUnit::OBJECT_BOUNDING_BOX :
                    SvgLengthScaleUnit::USER_SPACE_ON_USE;
            } },
        { SVG_MASK_UNITS,
            [](const std::string& val, SvgMaskAttribute& attr) {
                attr.maskUnits = (val == "userSpaceOnUse") ? SvgLengthScaleUnit::USER_SPACE_ON_USE :
                    SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
            } },
        { SVG_WIDTH,
            [](const std::string& val, SvgMaskAttribute& attr) {
                attr.width = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_X,
            [](const std::string& val, SvgMaskAttribute& attr) {
                attr.x = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_Y,
            [](const std::string& val, SvgMaskAttribute& attr) {
                attr.y = SvgAttributesParser::ParseDimension(val);
            } },
    };
    std::string key = name;
    StringUtils::TransformStrCase(key, StringUtils::TEXT_CASE_LOWERCASE);
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), key.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, maskAttr_);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
