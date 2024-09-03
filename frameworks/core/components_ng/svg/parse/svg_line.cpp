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

#include "frameworks/core/components_ng/svg/parse/svg_line.h"

#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {

SvgLine::SvgLine() : SvgGraphic()
{
    InitGraphicFlag();
}

RefPtr<SvgNode> SvgLine::Create()
{
    return AceType::MakeRefPtr<SvgLine>();
}

#ifndef USE_ROSEN_DRAWING
SkPath SvgLine::AsPath(const Size& viewPort) const
{
    SkPath path;
    path.moveTo(ConvertDimensionToPx(lineAttr_.x1, viewPort, SvgLengthType::HORIZONTAL),
        ConvertDimensionToPx(lineAttr_.y1, viewPort, SvgLengthType::VERTICAL));
    path.lineTo(ConvertDimensionToPx(lineAttr_.x2, viewPort, SvgLengthType::HORIZONTAL),
        ConvertDimensionToPx(lineAttr_.y2, viewPort, SvgLengthType::VERTICAL));
    return path;
}
#else
RSRecordingPath SvgLine::AsPath(const Size& viewPort) const
{
    RSRecordingPath path;
    path.MoveTo(ConvertDimensionToPx(lineAttr_.x1, viewPort, SvgLengthType::HORIZONTAL),
        ConvertDimensionToPx(lineAttr_.y1, viewPort, SvgLengthType::VERTICAL));
    path.LineTo(ConvertDimensionToPx(lineAttr_.x2, viewPort, SvgLengthType::HORIZONTAL),
        ConvertDimensionToPx(lineAttr_.y2, viewPort, SvgLengthType::VERTICAL));
    return path;
}
#endif

bool SvgLine::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgLineAttribute&)> attrs[] = {
        { SVG_X1,
            [](const std::string& val, SvgLineAttribute& attr) {
                attr.x1 = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_X2,
            [](const std::string& val, SvgLineAttribute& attr) {
                attr.x2 = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_Y1,
            [](const std::string& val, SvgLineAttribute& attr) {
                attr.y1 = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_Y2,
            [](const std::string& val, SvgLineAttribute& attr) {
                attr.y2 = SvgAttributesParser::ParseDimension(val);
            } },
    };
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), name.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, lineAttr_);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
