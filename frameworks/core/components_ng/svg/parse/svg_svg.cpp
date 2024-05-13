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

#include "base/geometry/size.h"
#include "include/pathops/SkPathOps.h"

#include "base/utils/utils.h"
#include "frameworks/core/components/declaration/svg/svg_declaration.h"

namespace OHOS::Ace::NG {
namespace {
const char DOM_SVG_SRC_VIEW_BOX[] = "viewBox";
}

SvgSvg::SvgSvg() : SvgGroup() {}

RefPtr<SvgNode> SvgSvg::Create()
{
    return AceType::MakeRefPtr<SvgSvg>();
}

#ifndef USE_ROSEN_DRAWING
SkPath SvgSvg::AsPath(const Size& viewPort) const
{
    SkPath path;
    for (const auto& child : children_) {
        const SkPath childPath = child->AsPath(viewPort);
        Op(path, childPath, kUnion_SkPathOp, &path);
    }
    return path;
}
#else
RSRecordingPath SvgSvg::AsPath(const Size& viewPort) const
{
    RSRecordingPath path;
    for (const auto& child : children_) {
        RSRecordingPath childPath = child->AsPath(viewPort);
        path.Op(path, childPath, RSPathOp::UNION);
    }
    return path;
}
#endif

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
        { DOM_SVG_MIRROR,
            [](const std::string& val, SvgAttributes& attr) {
                attr.autoMirror = val == "true";
            } },
        { DOM_SVG_HEIGHT,
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
        { DOM_SVG_VIEW_BOX,
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
        { DOM_SVG_WIDTH,
            [](const std::string& val, SvgAttributes& attr) {
                attr.width = SvgAttributesParser::ParseDimension(val);
            } },
        { DOM_SVG_X,
            [](const std::string& val, SvgAttributes& attr) {
                attr.x = SvgAttributesParser::ParseDimension(val);
            } },
        { DOM_SVG_Y,
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
