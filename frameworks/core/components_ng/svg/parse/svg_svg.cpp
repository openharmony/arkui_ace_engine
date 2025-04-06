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

#include "core/common/container.h"
#include "frameworks/core/components_ng/svg/parse/svg_svg.h"

#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {
namespace {
const char DOM_SVG_SRC_VIEW_BOX[] = "viewBox";
constexpr float HALF = 0.5f;
constexpr int32_t INDEX_VIEWBOX_X = 0;
constexpr int32_t INDEX_VIEWBOX_Y = 1;
constexpr int32_t INDEX_VIEWBOX_WIDTH = 2;
constexpr int32_t INDEX_VIEWBOX_HEIGHT = 3;
constexpr int32_t VIEWBOX_PARAM_COUNT = 4;
constexpr int32_t PRESERVEASPECTRATIO_PARAM_COUNT_MAX = 2;
}

SvgSvg::SvgSvg() : SvgGroup() {}

RefPtr<SvgNode> SvgSvg::Create()
{
    return AceType::MakeRefPtr<SvgSvg>();
}

RSRecordingPath SvgSvg::AsPath(const SvgLengthScaleRule& lengthRule)
{
    RSRecordingPath path;
    for (const auto& child : children_) {
        CHECK_NULL_RETURN(child, path);
        RSRecordingPath childPath = child->AsPath(lengthRule);
        path.Op(path, childPath, RSPathOp::UNION);
    }
    return path;
}

RSRecordingPath SvgSvg::AsPath(const Size& viewPort) const
{
    RSRecordingPath path;
    for (const auto& child : children_) {
        RSRecordingPath childPath = child->AsPath(viewPort);
        path.Op(path, childPath, RSPathOp::UNION);
    }
    return path;
}

SvgPreserveAspectRatio SvgSvg::GetPreserveAspectRatio() const
{
    return svgAttr_.preserveAspectRatio;
}

void SvgSvg::AdjustContentAreaSvgSizeInvalid(RSCanvas& canvas, const Size& viewPort, const Size& svgSize,
    const Rect& viewBox)
{
    if (LessNotEqual(svgSize.Width(), 0.0) && LessNotEqual(svgSize.Height(), 0.0)) {
        RSRect clipRect(0.0f, 0.0f, viewPort.Width(), viewPort.Height());
        canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
        auto scale = std::min(viewPort.Width() / viewBox.Width(), viewPort.Height() / viewBox.Height());
        auto translateX = (viewPort.Width() - viewBox.Width() * scale) * HALF;
        auto translateY = (viewPort.Height() - viewBox.Height() * scale) * HALF;
        canvas.Translate(translateX, translateY);
        canvas.Scale(scale, scale);
        canvas.Translate(-1 * viewBox.Left(), -1 * viewBox.Top());
        return;
    }
    if (LessNotEqual(svgSize.Width(), 0.0)) {
        RSRect clipRect(0.0f, 0.0f, viewBox.Width() / viewBox.Height() * svgSize.Height(), svgSize.Height());
        canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
        auto scaleY = svgSize.Height() / viewBox.Height();
        canvas.Scale(scaleY, scaleY);
        canvas.Translate(-1 * viewBox.Left(), -1 * viewBox.Top());
        return;
    }
    if (LessNotEqual(svgSize.Height(), 0.0)) {
        RSRect clipRect(0.0f, 0.0f, svgSize.Width(), viewBox.Height() / viewBox.Width() * svgSize.Width());
        canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
        auto scaleX = svgSize.Width() / viewBox.Width();
        canvas.Scale(scaleX, scaleX);
        canvas.Translate(-1 * viewBox.Left(), -1 * viewBox.Top());
        return;
    }
}

void SvgSvg::AdjustContentAreaSvgSizeValid(RSCanvas& canvas, const Size& viewPort, const Size& svgSize,
    const Rect& viewBox)
{
    float scaleX = 0.0f;
    float scaleY = 0.0f;
    float translateX = 0.0f;
    float translateY = 0.0f;
    RSRect clipRect(0.0f, 0.0f, svgSize.Width(), svgSize.Height());
    canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        scaleX = std::min(svgSize.Width() / viewBox.Width(), svgSize.Height() / viewBox.Height());
        scaleY = scaleX;
        translateX = (svgSize.Width() - viewBox.Width() * scaleX) * HALF;
        translateY = (svgSize.Height() - viewBox.Height() * scaleY) * HALF;
    } else {
        auto preserveAspectRatio = GetPreserveAspectRatio();
        SvgAttributesParser::ComputeScale(viewBox.GetSize(), viewPort, preserveAspectRatio, scaleX, scaleY);
        SvgAttributesParser::ComputeTranslate(viewBox.GetSize(), viewPort, scaleX, scaleY,
            preserveAspectRatio.svgAlign, translateX, translateY);
        TAG_LOGD(AceLogTag::ACE_IMAGE, "Scale: X=%{public}f Y=%{public}f,translate: X=%{public}f Y=%{public}f",
            scaleX, scaleY, translateX, translateY);
    }
    canvas.Translate(translateX, translateY);
    canvas.Scale(scaleX, scaleY);
    canvas.Translate(-1 * viewBox.Left(), -1 * viewBox.Top());
}

void SvgSvg::AdjustContentAreaByViewBox(RSCanvas& canvas, const Size& viewPort)
{
    auto svgSize = GetSize();
    auto viewBox = GetViewBox();
    if (LessOrEqual(viewBox.Width(), 0.0) || LessOrEqual(viewBox.Height(), 0.0)) {
        RSRect clipRect(0.0f, 0.0f, LessNotEqual(svgSize.Width(), 0.0) ? viewPort.Width() : svgSize.Width(),
            LessNotEqual(svgSize.Height(), 0.0) ? viewPort.Height() : svgSize.Height());
        canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
        return;
    }
    if (svgSize.IsValid()) {
        AdjustContentAreaSvgSizeValid(canvas, viewPort, svgSize, viewBox);
    } else {
        AdjustContentAreaSvgSizeInvalid(canvas, viewPort, svgSize, viewBox);
    }
}

void SvgSvg::OnImageColorFilter(RSCanvas& canvas, const ImageColorFilter& imageColorFilter)
{
    auto rsColorFilterPtr = SvgColorFilterEffect::GetRsColorFilter(imageColorFilter);
    CHECK_NULL_VOID(rsColorFilterPtr);
    RSBrush brush;
    auto filter = brush.GetFilter();
    auto imageFilter = RSRecordingImageFilter::CreateColorFilterImageFilter(*rsColorFilterPtr, nullptr);
    filter.SetImageFilter(imageFilter);
    brush.SetFilter(filter);
    RSSaveLayerOps slo(nullptr, &brush);
    canvas.SaveLayer(slo);
}

void SvgSvg::OnDraw(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule)
{
    auto imageColorFilterOpt = GetColorFilter();
    if (isRootNode_ && imageColorFilterOpt.has_value()) {
        OnImageColorFilter(canvas, imageColorFilterOpt.value());
    }
    SvgNode::OnDraw(canvas, lengthRule);
}

Size SvgSvg::GetSize() const
{
    return Size(svgAttr_.width.Value(), svgAttr_.height.Value());
}

Rect SvgSvg::GetViewBox() const
{
    return svgAttr_.viewBox;
}

void ParsePreserveAspectRatio(const std::string& val, SvgAttributes& attr)
{
    if (val.empty()) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "ParsePreserveAspectRatio val empty");
        return;
    }
    std::vector<std::string> tmpValue;
    StringUtils::StringSplitter(val, ' ', tmpValue);
    if (tmpValue.empty() || tmpValue.size() > PRESERVEASPECTRATIO_PARAM_COUNT_MAX) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "ParsePreserveAspectRatio parameter count error");
        return;
    }
    attr.preserveAspectRatio.svgAlign = SvgAttributesParser::ParseSvgAlign(tmpValue[0]);
    if (tmpValue.size() > 1) {
        attr.preserveAspectRatio.meetOrSlice = SvgAttributesParser::ParseSvgMeetOrSlice(tmpValue[1]);
    }
    TAG_LOGD(AceLogTag::ACE_IMAGE, "ParsePreserveAspectRatio, svgAlign=%{public}d meetOrSlice=%{public}d",
        attr.preserveAspectRatio.svgAlign, attr.preserveAspectRatio.meetOrSlice);
}

void ParseViewBox(const std::string& val, SvgAttributes& attr)
{
    if (val.empty()) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "ParseViewBox val empty");
        return;
    }
    std::vector<double> viewBox;
    StringUtils::StringSplitter(val, ' ', viewBox);
    if (viewBox.size() != VIEWBOX_PARAM_COUNT) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "ParseViewBox parameter count != 4");
        return;
    }
    attr.viewBox = Rect(viewBox[INDEX_VIEWBOX_X], viewBox[INDEX_VIEWBOX_Y], viewBox[INDEX_VIEWBOX_WIDTH],
        viewBox[INDEX_VIEWBOX_HEIGHT]);
}

bool SvgSvg::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgAttributes&)> SVG_ATTR_ARRAY[] = {
        { SVG_MIRROR,
            [](const std::string& val, SvgAttributes& attr) {
                attr.autoMirror = val == "true";
            } },
        { SVG_HEIGHT,
            [](const std::string& val, SvgAttributes& attr) {
                attr.height = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_PRESERVE_ASPECT_RATIO, ParsePreserveAspectRatio},
        { DOM_SVG_SRC_VIEW_BOX, ParseViewBox},
        { SVG_VIEW_BOX, ParseViewBox},
        { SVG_WIDTH,
            [](const std::string& val, SvgAttributes& attr) {
                attr.width = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_X,
            [](const std::string& val, SvgAttributes& attr) {
                attr.x = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_Y,
            [](const std::string& val, SvgAttributes& attr) {
                attr.y = SvgAttributesParser::ParseDimension(val);
            } },
    };
    auto attrIter = BinarySearchFindIndex(SVG_ATTR_ARRAY, ArraySize(SVG_ATTR_ARRAY), name.c_str());
    if (attrIter != -1) {
        SVG_ATTR_ARRAY[attrIter].value(value, svgAttr_);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
