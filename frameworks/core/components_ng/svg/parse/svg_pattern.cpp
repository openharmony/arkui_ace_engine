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
#include "core/components_ng/render/drawing.h"
#include "frameworks/core/components_ng/svg/svg_utils.h"

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
    RSRect tileRect(0, 0, measuredWidth, measuredHeight);
    auto pictureRecorder = std::make_unique<RSPictureRecorder>();
    auto patternCanvas = pictureRecorder->BeginRecording(measuredWidth, measuredHeight);
    auto patternContentRule = BuildContentScaleRule(svgCoordinateSystemContext, patternAttr_.patternContentUnits);
    auto containerSize = svgCoordinateSystemContext.GetContainerRect().GetSize();
    TransformForCurrentOBB(*patternCanvas, patternContentRule, containerSize, Offset(0.0, 0.0));
    for (auto& child : children_) {
        auto node = DynamicCast<SvgNode>(child);
        if (node) {
            node->Draw(*patternCanvas, patternContentRule);
        }
    }
    RSMatrix patternMatrix;
    RSMatrix localMatrix;
    localMatrix.Translate(measureX, measureY);
    patternMatrix.PreConcat(localMatrix);
    auto picture = pictureRecorder->FinishRecordingAsPicture();
    auto shader = RSShaderEffect::CreatePictureShader(*picture, RSTileMode::REPEAT, RSTileMode::REPEAT,
        RSFilterMode::LINEAR, patternMatrix, tileRect);
    brush.SetShaderEffect(shader);
    canvas.Restore();
}

static void ParsePatternContentUnits(const std::string& val, SvgPatternAttribute& attr)
{
    auto featureEnable = SvgUtils::IsFeatureEnable(SVG_FEATURE_SUPPORT_TWO, attr.usrConfigVersion);
    if (!featureEnable) {
        attr.patternContentUnits = (val == "userSpaceOnUse") ? SvgLengthScaleUnit::USER_SPACE_ON_USE :
            SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
        return;
    }
    attr.patternContentUnits = (val == "objectBoundingBox") ? SvgLengthScaleUnit::OBJECT_BOUNDING_BOX :
        SvgLengthScaleUnit::USER_SPACE_ON_USE;
}

bool SvgPattern::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgPatternAttribute&)> attrs[] = {
        { SVG_HEIGHT,
            [](const std::string& val, SvgPatternAttribute& attr) {
                attr.height = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_PATTERN_CONTENT_UNITS, ParsePatternContentUnits},
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
        patternAttr_.usrConfigVersion = GetUsrConfigVersion();
        attrs[attrIter].value(value, patternAttr_);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
