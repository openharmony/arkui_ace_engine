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

#include "frameworks/core/components_ng/svg/parse/svg_node.h"

#include "include/core/SkClipOp.h"
#include "include/core/SkString.h"
#include "include/utils/SkParsePath.h"

#include "frameworks/core/components/common/painter/flutter_svg_painter.h"
#include "frameworks/core/components/transform/render_transform.h"
#include "frameworks/core/components_ng/svg/parse/svg_gradient.h"

namespace OHOS::Ace::NG {
namespace {

constexpr size_t SVG_ATTR_ID_FLAG_NUMS = 6;

}

uint8_t OpacityDoubleToUint8(double opacity)
{
    return static_cast<uint8_t>(std::round(opacity * UINT8_MAX));
}

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

void SvgNode::SetAttr(const std::string& name, const std::string& value)
{
    if (declaration_ == nullptr) {
        return;
    }
    if (!declaration_->SetSpecializedAttr(std::make_pair(name, value))) {
        declaration_->SetAttr({ std::make_pair(name, value) });
    }
}

void SvgNode::InitStyle(const RefPtr<SvgBaseDeclaration>& parent)
{
    if (declaration_ == nullptr) {
        return;
    }
    Inherit(parent);
    if (hrefFill_) {
        auto href = declaration_->GetFillState().GetHref();
        if (!href.empty()) {
            auto gradient = GetGradient(href);
            if (gradient) {
                declaration_->SetGradient(gradient.value());
            }
        }
    }
    if (hrefRender_) {
        hrefClipPath_ = declaration_->GetClipPathHref();
        opacity_ = OpacityDoubleToUint8(declaration_->GetOpacity());
        transform_ = declaration_->GetTransform();
        hrefMaskId_ = ParseIdFromUrl(declaration_->GetMaskId());
        hrefFilterId_ = ParseIdFromUrl(declaration_->GetFilterId());
    }
    if (childStyleTraversed_) {
        for (auto& node : children_) {
            if (node && node->styleTraversed_) {
                node->InitStyle(declaration_);
            }
        }
    }
}

void SvgNode::Draw(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    if (!OnCanvas(canvas)) {
        return;
    }
    canvas.Save();
    if (!hrefClipPath_.empty()) {
        OnClipPath(canvas, viewPort);
    }
    if (!transform_.empty()) {
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
    canvas.Restore();
}

void SvgNode::OnDrawTraversed(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    for (auto& node : children_) {
        if (node && node->drawTraversed_) {
            node->Draw(canvas, viewPort, color);
        }
    }
}

bool SvgNode::OnCanvas(RSCanvas& canvas)
{
    // drawing.h api 不完善，直接取用SkCanvas，后续要重写
    auto rsCanvas = canvas.GetImpl<RSSkCanvas>();
    if (rsCanvas == nullptr) {
        return false;
    }
    auto skCanvas_ = rsCanvas->ExportSkCanvas();
    return skCanvas_ == nullptr ? false : true;
}

void SvgNode::OnClipPath(RSCanvas& canvas, const Size& viewPort)
{
    auto svgContext = svgContext_.Upgrade();
    if (!svgContext) {
        LOGE("OnClipPath failed, svgContext is null");
        return;
    }
    auto refSvgNode = svgContext->GetSvgNodeById(hrefClipPath_);
    if (!refSvgNode) {
        LOGE("OnClipPath failed, refSvgNode is null");
        return;
    }
    auto clipPath = refSvgNode->AsPath(viewPort);
    if (clipPath.isEmpty()) {
        LOGW("OnClipPath abandon, clipPath is empty");
        return;
    }
    skCanvas_->clipPath(clipPath, SkClipOp::kIntersect);
    return;
}

void SvgNode::OnFilter(RSCanvas& canvas, const Size& viewPort)
{
    return;
}

void SvgNode::OnMask(RSCanvas& canvas, const Size& viewPort)
{
    auto svgContext = svgContext_.Upgrade();
    if (!svgContext) {
        LOGE("OnMask failed, svgContext is null");
        return;
    }
    auto refMask = svgContext->GetSvgNodeById(hrefMaskId_);
    if (!refMask) {
        LOGE("OnMask failed, refMask is null");
        return;
    }
    refMask->Draw(canvas, viewPort, std::nullopt);
    return;
}

void SvgNode::OnTransform(RSCanvas& canvas, const Size& viewPort)
{
    auto transformInfo = SvgTransform::CreateTransformInfo(transform_);
    if (transformInfo.hasRotateCenter) {
        transformInfo.matrix4 =
            RenderTransform::GetTransformByOffset(transformInfo.matrix4, transformInfo.rotateCenter);
        // maybe should process attr transformOrigin
    }
    skCanvas_->concat(FlutterSvgPainter::ToSkMatrix(transformInfo.matrix4));
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

std::optional<Gradient> SvgNode::GetGradient(const std::string& href)
{
    auto svgContext = svgContext_.Upgrade();
    if (!svgContext) {
        LOGE("Gradient failed, svgContext is null");
        return std::nullopt;
    }
    if (href.empty()) {
        return std::nullopt;
    }
    auto refSvgNode = svgContext->GetSvgNodeById(href);
    if (!refSvgNode) {
        LOGE("refSvgNode is null");
        return std::nullopt;
    }
    auto svgGradient = DynamicCast<SvgGradient>(refSvgNode);
    if (svgGradient) {
        return std::make_optional(svgGradient->GetGradient());
    }
    return std::nullopt;
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

} // namespace OHOS::Ace::NG
