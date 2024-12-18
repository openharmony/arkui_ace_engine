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

#include "frameworks/core/components_ng/svg/parse/svg_svg.h"

#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {
namespace {
const char DOM_SVG_SRC_VIEW_BOX[] = "viewBox";
constexpr float HALF = 0.5f;
}

SvgSvg::SvgSvg() : SvgGroup() {}

RefPtr<SvgNode> SvgSvg::Create()
{
    return AceType::MakeRefPtr<SvgSvg>();
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
    RSRect clipRect(0.0f, 0.0f, svgSize.Width(), svgSize.Height());
    canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
    auto scale = std::min(svgSize.Width() / viewBox.Width(), svgSize.Height() / viewBox.Height());
    auto translateX = (svgSize.Width() - viewBox.Width() * scale) * HALF;
    auto translateY = (svgSize.Height() - viewBox.Height() * scale) * HALF;
    canvas.Translate(translateX, translateY);
    canvas.Scale(scale, scale);
    canvas.Translate(-1 * viewBox.Left(), -1 * viewBox.Top());
}

Size SvgSvg::GetSize() const
{
    return Size(svgAttr_.width.Value(), svgAttr_.height.Value());
}

Rect SvgSvg::GetViewBox() const
{
    return svgAttr_.viewBox;
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
        { DOM_SVG_SRC_VIEW_BOX,
            [](const std::string& val, SvgAttributes& attr) {
                if (val.empty()) {
                    return;
                }
                std::vector<double> viewBox;
                StringUtils::StringSplitter(val, ' ', viewBox);
                if (viewBox.size() == 4) {
                    attr.viewBox = Rect(viewBox[0], viewBox[1], viewBox[2], viewBox[3]);
                }
            } },
        { SVG_VIEW_BOX,
            [](const std::string& val, SvgAttributes& attr) {
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
