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
#include "include/core/SkString.h"
#include "include/utils/SkParsePath.h"

#include "base/utils/utils.h"
#ifndef NEW_SKIA
#include "core/components/common/painter/flutter_svg_painter.h"
#else
#include "core/components/common/painter/rosen_svg_painter.h"
#endif
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_animation.h"
#include "core/components_ng/svg/parse/svg_gradient.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

constexpr size_t SVG_ATTR_ID_FLAG_NUMS = 6;
const char ATTR_NAME_OPACITY[] = "opacity";

const std::unordered_map<std::string, std::function<Color(RefPtr<SvgBaseDeclaration>&)>> COLOR_GETTERS = {
    { ATTR_NAME_FILL,
        [](RefPtr<SvgBaseDeclaration>& declaration) -> Color { return declaration->GetFillState().GetColor(); } },
    { ATTR_NAME_STROKE,
        [](RefPtr<SvgBaseDeclaration>& declaration) -> Color { return declaration->GetStrokeState().GetColor(); } },
};

const std::unordered_map<std::string, std::function<Dimension(RefPtr<SvgBaseDeclaration>&)>> DIMENSION_GETTERS = {
    { ATTR_NAME_STROKE_WIDTH,
        [](RefPtr<SvgBaseDeclaration>& declaration) -> Dimension {
            return declaration->GetStrokeState().GetLineWidth();
        } },
    { ATTR_NAME_FONT_SIZE,
        [](RefPtr<SvgBaseDeclaration>& declaration) -> Dimension {
            return declaration->GetSvgTextStyle().GetFontSize();
        } },
    { ATTR_NAME_LETTER_SPACING,
        [](RefPtr<SvgBaseDeclaration>& declaration) -> Dimension {
            return declaration->GetSvgTextStyle().GetLetterSpacing();
        } },
};

const std::unordered_map<std::string, std::function<double(RefPtr<SvgBaseDeclaration>&)>> DOUBLE_GETTERS = {
    { ATTR_NAME_FILL_OPACITY,
        [](RefPtr<SvgBaseDeclaration>& declaration) -> double {
            return declaration->GetFillState().GetOpacity().GetValue();
        } },
    { ATTR_NAME_STROKE_OPACITY,
        [](RefPtr<SvgBaseDeclaration>& declaration) -> double {
            return declaration->GetStrokeState().GetOpacity().GetValue();
        } },
    { ATTR_NAME_MITER_LIMIT,
        [](RefPtr<SvgBaseDeclaration>& declaration) -> double {
            return declaration->GetStrokeState().GetMiterLimit();
        } },
    { ATTR_NAME_STROKE_DASH_OFFSET,
        [](RefPtr<SvgBaseDeclaration>& declaration) -> double {
            return declaration->GetStrokeState().GetLineDash().dashOffset;
        } },
    { ATTR_NAME_OPACITY,
        [](RefPtr<SvgBaseDeclaration>& declaration) -> double {
            return declaration->GetOpacity() * (1.0 / UINT8_MAX);
        } },
};
} // namespace

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
    CHECK_NULL_VOID(declaration_);
    if (!declaration_->SetSpecializedAttr(std::make_pair(name, value))) {
        declaration_->SetAttr({ std::make_pair(name, value) });
    }
}

RSPath SvgNode::AsRSPath(const Size& viewPort) const
{
    return {};
}

void SvgNode::InitStyle(const RefPtr<SvgBaseDeclaration>& parent)
{
    CHECK_NULL_VOID(declaration_);
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
    OnInitStyle();
    // pass down style declaration to children
    if (passStyle_) {
        for (auto& node : children_) {
            CHECK_NULL_VOID(node);
            // pass down style only if child inheritStyle_ is true
            node->InitStyle((node->inheritStyle_) ? declaration_ : nullptr);
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
        return;
    }
    // mask and filter create extra layers, need to record initial layer count
#ifndef USE_ROSEN_DRAWING
    auto count = skCanvas_->getSaveCount();
    skCanvas_->save();
#else
    auto count = rsCanvas_->GetSaveCount();
    rsCanvas_->Save();
#endif
    if (!hrefClipPath_.empty()) {
        OnClipPath(canvas, viewPort);
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
#ifndef USE_ROSEN_DRAWING
    skCanvas_->restoreToCount(count);
#else
    rsCanvas_->RestoreToCount(count);
#endif
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
#ifndef USE_ROSEN_DRAWING
    // drawing.h api 不完善，直接取用SkCanvas，后续要重写
    auto rsCanvas = canvas.GetImpl<RSSkCanvas>();
    CHECK_NULL_RETURN(rsCanvas, false);
    skCanvas_ = rsCanvas->ExportSkCanvas();
    return skCanvas_ != nullptr;
#else
    rsCanvas_ = &canvas;
    return true;
#endif
}

void SvgNode::OnClipPath(RSCanvas& canvas, const Size& viewPort)
{
    auto svgContext = svgContext_.Upgrade();
    CHECK_NULL_VOID(svgContext);
    auto refSvgNode = svgContext->GetSvgNodeById(hrefClipPath_);
    CHECK_NULL_VOID(refSvgNode);
    auto clipPath = refSvgNode->AsPath(viewPort);
#ifndef USE_ROSEN_DRAWING
    if (clipPath.isEmpty()) {
        LOGW("OnClipPath abandon, clipPath is empty");
        return;
    }
    skCanvas_->clipPath(clipPath, SkClipOp::kIntersect);
#else
    if (!clipPath.IsValid()) {
        LOGW("OnClipPath abandon, clipPath is empty");
        return;
    }
    rsCanvas_->ClipPath(clipPath, RSClipOp::INTERSECT);
#endif
    return;
}

void SvgNode::OnFilter(RSCanvas& canvas, const Size& viewPort)
{
    return;
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

void SvgNode::OnTransform(RSCanvas& canvas, const Size& viewPort)
{
    auto matrix = (animateTransform_.empty()) ? SvgTransform::CreateMatrix4(transform_)
                                              : SvgTransform::CreateMatrixFromMap(animateTransform_);
#ifndef USE_ROSEN_DRAWING
#ifndef NEW_SKIA
    skCanvas_->concat(FlutterSvgPainter::ToSkMatrix(matrix));
#else
    skCanvas_->concat(RosenSvgPainter::ToSkMatrix(matrix));
#endif
#else
    rsCanvas_->ConcatMatrix(RosenSvgPainter::ToDrawingMatrix(matrix));
#endif
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
        Color originalValue = COLOR_GETTERS.find(attrName)->second(declaration_);
        AnimateOnAttribute(animate, originalValue);
    } else if (DIMENSION_GETTERS.find(attrName) != DIMENSION_GETTERS.end()) {
        Dimension originalValue = DIMENSION_GETTERS.find(attrName)->second(declaration_);
        AnimateOnAttribute(animate, originalValue);
    } else if (DOUBLE_GETTERS.find(attrName) != DOUBLE_GETTERS.end()) {
        double originalValue = DOUBLE_GETTERS.find(attrName)->second(declaration_);
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
