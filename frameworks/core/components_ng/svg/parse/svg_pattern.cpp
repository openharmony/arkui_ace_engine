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

#include "base/geometry/rect.h"
#include "core/components_ng/pattern/pattern.h"
#include "frameworks/core/components/declaration/svg/svg_pattern_declaration.h"

namespace OHOS::Ace::NG {

SvgPattern::SvgPattern() : SvgQuote() {}

RefPtr<SvgNode> SvgPattern::Create()
{
    return AceType::MakeRefPtr<SvgPattern>();
}

void SvgPattern::OnDrawTraversedBefore(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    auto patternUnits = patternAttr_.patternUnits;

    auto scaleX = viewPort.Width() / patternAttr_.width.ConvertToPx();
    auto scaleY = viewPort.Height() / patternAttr_.height.ConvertToPx();
    canvas.Save();
    canvas.Scale(scaleX, scaleY);
}

void SvgPattern::OnDrawTraversedAfter(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    canvas.Restore();
}

bool SvgPattern::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgPatternAttribute&)> attrs[] = {
        { DOM_SVG_HEIGHT,
            [](const std::string& val, SvgPatternAttribute& attr) {
                attr.height = SvgAttributesParser::ParseDimension(val);
            } },
        { DOM_SVG_PATTERN_CONTENT_UNITS,
            [](const std::string& val, SvgPatternAttribute& attr) {
                attr.patternContentUnits = val;
            } },
        { DOM_SVG_PATTERN_UNITS,
            [](const std::string& val, SvgPatternAttribute& attr) {
                attr.patternUnits = val;
            } },
        { DOM_SVG_VIEW_BOX,
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
        { DOM_SVG_WIDTH,
            [](const std::string& val, SvgPatternAttribute& attr) {
                attr.width = SvgAttributesParser::ParseDimension(val);
            } },
        { DOM_SVG_X,
            [](const std::string& val, SvgPatternAttribute& attr) {
                attr.x = SvgAttributesParser::ParseDimension(val);
            } },
        { DOM_SVG_Y,
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
