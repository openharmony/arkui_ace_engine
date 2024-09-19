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

#include "frameworks/core/common/container.h"
#include "frameworks/core/components/common/painter/rosen_svg_painter.h"
#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {

SvgMask::SvgMask() : SvgQuote() {}

RefPtr<SvgNode> SvgMask::Create()
{
    return AceType::MakeRefPtr<SvgMask>();
}

void SvgMask::OnDrawTraversedBefore(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    RectF nodeBounds;
    if (isDefaultMaskUnits_ && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        if (boundingBoxRectOpt_.has_value()) {
            nodeBounds = boundingBoxRectOpt_.value();
        }
    } else {
        auto boundsRect = isDefaultMaskUnits_ ? AsBounds(viewPort) : GetRootViewBox();
        nodeBounds = { boundsRect.Left(), boundsRect.Top(), boundsRect.Width(), boundsRect.Height() };
    }
#ifndef USE_ROSEN_DRAWING
    maskBounds_ = SkRect::MakeXYWH(SkDoubleToScalar(nodeBounds.Left() + ParseUnitsAttr(x_, nodeBounds.Width())),
        SkDoubleToScalar(nodeBounds.Top() + ParseUnitsAttr(y_, nodeBounds.Height())),
        SkDoubleToScalar(ParseUnitsAttr(width_, nodeBounds.Width())),
        SkDoubleToScalar(ParseUnitsAttr(height_, nodeBounds.Height())));
    // create mask layer
    skCanvas_->saveLayer(maskBounds_, nullptr);
    // ready to render mask content
    canvasLayerCount_ = skCanvas_->getSaveCount();

    RosenSvgPainter::SetMask(skCanvas_);
#else
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
#endif
}

void SvgMask::OnDrawTraversedAfter(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->restoreToCount(canvasLayerCount_);
    // create content layer and render content
    SkPaint maskPaint;
    maskPaint.setBlendMode(SkBlendMode::kSrcIn);
    skCanvas_->saveLayer(maskBounds_, &maskPaint);
    skCanvas_->clipRect(maskBounds_, true);
#else
    rsCanvas_->RestoreToCount(canvasLayerCount_);
    // create content layer and render content
    RSBrush maskBrush;
    maskBrush.SetBlendMode(RSBlendMode::SRC_IN);
    RSSaveLayerOps slo(&maskBounds_, &maskBrush);
    rsCanvas_->SaveLayer(slo);
    rsCanvas_->ClipRect(maskBounds_, RSClipOp::INTERSECT, true);
#endif
}

void SvgMask::OnInitStyle()
{
    isDefaultMaskUnits_ = (maskAttr_.maskUnits == "objectBoundingBox");
    isDefaultMaskContentUnits_ = (maskAttr_.maskContentUnits == "userSpaceOnUse");
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
                attr.maskContentUnits = val;
            } },
        { SVG_MASK_UNITS,
            [](const std::string& val, SvgMaskAttribute& attr) {
                attr.maskUnits = val;
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
