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

#include "frameworks/core/components_ng/svg/parse/svg_mask.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#ifndef NEW_SKIA
#include "frameworks/core/components/common/painter/flutter_svg_painter.h"
#else
#include "frameworks/core/components/common/painter/rosen_svg_painter.h"
#endif
#include "frameworks/core/components/declaration/svg/svg_mask_declaration.h"

namespace OHOS::Ace::NG {

SvgMask::SvgMask() : SvgQuote()
{
    declaration_ = AceType::MakeRefPtr<SvgMaskDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

RefPtr<SvgNode> SvgMask::Create()
{
    return AceType::MakeRefPtr<SvgMask>();
}

void SvgMask::OnDrawTraversedBefore(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    auto nodeBounds = isDefaultMaskUnits_ ? AsBounds(viewPort) : GetRootViewBox();
#ifndef USE_ROSEN_DRAWING
    maskBounds_ = SkRect::MakeXYWH(SkDoubleToScalar(nodeBounds.Left() + ParseUnitsAttr(x_, nodeBounds.Width())),
        SkDoubleToScalar(nodeBounds.Top() + ParseUnitsAttr(y_, nodeBounds.Height())),
        SkDoubleToScalar(ParseUnitsAttr(width_, nodeBounds.Width())),
        SkDoubleToScalar(ParseUnitsAttr(height_, nodeBounds.Height())));
    // create mask layer
    skCanvas_->saveLayer(maskBounds_, nullptr);
    // ready to render mask content
    canvasLayerCount_ = skCanvas_->getSaveCount();
#ifndef NEW_SKIA
    FlutterSvgPainter::SetMask(skCanvas_);
#else
    RosenSvgPainter::SetMask(skCanvas_);
#endif
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
    canvasLayerCount_ = rsCanvas_->GetSaveCount();
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
    auto declaration = Ace::AceType::DynamicCast<SvgMaskDeclaration>(declaration_);
    CHECK_NULL_VOID(declaration);
    isDefaultMaskUnits_ = (declaration->GetMaskUnits() == "objectBoundingBox");
    isDefaultMaskContentUnits_ = (declaration->GetMaskContentUnits() == "userSpaceOnUse");
    x_ = declaration->GetX();
    y_ = declaration->GetY();
    height_ = declaration->GetHeight();
    width_ = declaration->GetWidth();
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
} // namespace OHOS::Ace::NG
