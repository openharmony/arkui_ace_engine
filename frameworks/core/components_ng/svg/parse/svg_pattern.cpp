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

#include "frameworks/core/components_ng/svg/parse/svg_pattern.h"

#include "core/common/container.h"
#include "core/components_ng/svg/base/svg_length_scale_rule.h"
#include "frameworks/core/components_ng/svg/parse/svg_constants.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {

SvgPattern::SvgPattern() : SvgQuote() {}

RefPtr<SvgNode> SvgPattern::Create()
{
    return AceType::MakeRefPtr<SvgPattern>();
}

void SvgPattern::OnDrawTraversedBefore(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        auto scaleX = viewPort.Width() / patternAttr_.width.ConvertToPx();
        auto scaleY = viewPort.Height() / patternAttr_.height.ConvertToPx();
        canvas.Save();
        canvas.Scale(scaleX, scaleY);
        return;
    }
    canvas.Save();
    auto actualWdith = boundingBoxRect_.Width() * patternAttr_.width.Value();
    auto actualHeight = boundingBoxRect_.Height() * patternAttr_.height.Value();
    auto actualX = boundingBoxRect_.Width() * patternAttr_.x.Value();
    auto actualY = boundingBoxRect_.Height() * patternAttr_.y.Value();
    RSRect clipRect(actualX, actualY, actualX + actualWdith, actualY + actualHeight);
    canvas.ClipRect(clipRect, RSClipOp::INTERSECT, true);
    
    if (patternAttr_.patternContentUnits != SvgLengthScaleUnit::USER_SPACE_ON_USE) {
        auto scaleX = static_cast<float>(boundingBoxRect_.Width() / patternAttr_.width.Value());
        auto scaleY = static_cast<float>(boundingBoxRect_.Height() / patternAttr_.height.Value());
        canvas.Scale(scaleX, scaleY);
    }
}

void SvgPattern::OnDrawTraversedAfter(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    canvas.Restore();
}

void SvgPattern::OnPatternEffect(RSCanvas& canvas, RSBrush& brush,
    const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    canvas.Save();
    auto patternRule = svgCoordinateSystemContext.BuildScaleRule(patternAttr_.patternUnits);
    auto measureX = GetRegionPosition(patternAttr_.x, patternRule, SvgLengthType::HORIZONTAL);
    auto measureY = GetRegionPosition(patternAttr_.y, patternRule, SvgLengthType::VERTICAL);
    auto measuredWidth = GetRegionLength(patternAttr_.width, patternRule, SvgLengthType::HORIZONTAL);
    auto measuredHeight = GetRegionLength(patternAttr_.height, patternRule, SvgLengthType::VERTICAL);
    auto surface = RSSurface::MakeRasterN32Premul(measuredWidth, measuredHeight);
    if (surface == nullptr) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "SvgPattern::OnPatternEffect surface is null");
        return;
    }
    auto patternCanvas = surface->GetCanvas();
    if (patternCanvas == nullptr) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "SvgPattern::OnPatternEffect patternCanvas is null");
        return;
    }
    // Create New coordinate system
    Rect patternContentRect(0, 0, svgCoordinateSystemContext.GetContainerRect().Width(),
        svgCoordinateSystemContext.GetContainerRect().Height());
    SvgCoordinateSystemContext patternContentCoordinateSystemContext(patternContentRect,
        svgCoordinateSystemContext.GetViewPort());
    auto patternContentRule = TransformForCurrentOBB(*patternCanvas, svgCoordinateSystemContext,
        patternAttr_.patternContentUnits, 0.0f, 0.0f);
    TAG_LOGD(AceLogTag::ACE_IMAGE, "OnPatternEffect l:%{public}lf, t:%{public}lf, r:%{public}lf, b:%{public}lf ",
        patternContentRect.Left(), patternContentRect.Top(), patternContentRect.Right(), patternContentRect.Bottom());
    for (auto& child : children_) {
        auto node = DynamicCast<SvgNode>(child);
        if (node) {
            node->Draw(*patternCanvas, patternContentRule);
        }
    }
    auto image = surface->GetImageSnapshot();
    if (!image) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "SvgPattern::OnPatternEffect image is nullptr");
        return ;
    }
    RSMatrix matrix;
    matrix.SetMatrix(1, 0,  measureX, 0, 1,  measureY, 0, 0, 1);
    auto shader = RSShaderEffect::CreateImageShader(*image, RSTileMode::REPEAT, RSTileMode::REPEAT,
        RSSamplingOptions(RSFilterMode::LINEAR), matrix);
    if (!shader) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "SvgPattern::OnPatternEffect shader is nullptr");
        return ;
    }
    brush.SetShaderEffect(shader);
    canvas.Restore();
}

bool SvgPattern::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgPatternAttribute&)> attrs[] = {
        { SVG_HEIGHT,
            [](const std::string& val, SvgPatternAttribute& attr) {
                attr.height = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_PATTERN_CONTENT_UNITS,
            [](const std::string& val, SvgPatternAttribute& attr) {
                attr.patternContentUnits = (val == "objectBoundingBox") ? SvgLengthScaleUnit::OBJECT_BOUNDING_BOX :
                    SvgLengthScaleUnit::USER_SPACE_ON_USE;
            } },
        { SVG_PATTERN_UNITS,
            [](const std::string& val, SvgPatternAttribute& attr) {
                attr.patternUnits = (val == "userSpaceOnUse") ? SvgLengthScaleUnit::USER_SPACE_ON_USE :
                    SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
            } },
        { SVG_VIEW_BOX,
            [](const std::string& val, SvgPatternAttribute& attr) {
                if (val.empty()) {
                    return;
                }
                std::vector<double> viewBox;
                StringUtils::StringSplitter(val, ' ', viewBox);
                if (viewBox.size() == 4) {
                    attr.viewBox = Rect(viewBox[0], viewBox[1], viewBox[2], viewBox[3]);
                }
            } },
        { SVG_WIDTH,
            [](const std::string& val, SvgPatternAttribute& attr) {
                attr.width = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_X,
            [](const std::string& val, SvgPatternAttribute& attr) {
                attr.x = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_Y,
            [](const std::string& val, SvgPatternAttribute& attr) {
                attr.y = SvgAttributesParser::ParseDimension(val);
            } },
    };

    std::string key = name;
    StringUtils::TransformStrCase(key, StringUtils::TEXT_CASE_LOWERCASE);
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), key.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, patternAttr_);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
