/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/dom/dom_svg_base.h"

#include "frameworks/bridge/common/dom/dom_svg.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {
namespace {

const char LINECAP_ROUND[] = "round";
const char LINECAP_SQUARE[] = "square";
const char LINEJOIN_BEVEL[] = "bevel";
const char LINEJOIN_ROUND[] = "round";
const char VALUE_NONE[] = "none";

} // namespace

DOMSvgBase::DOMSvgBase(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName) {}

bool DOMSvgBase::SetPresentationAttr(const std::pair<std::string, std::string>& attr)
{
    static const std::unordered_map<std::string, void (*)(const std::string&, DOMSvgBase&)> presentationAttrs = {
        { DOM_SVG_OPACITY, [](const std::string& val, DOMSvgBase& node) {
            node.opacity_ = StringToDouble(val);
        } },
        { DOM_SVG_FILL, [](const std::string& val, DOMSvgBase& node) {
            if (val != VALUE_NONE) {
                node.fillState_.SetColor(Color::FromString(val));
                return;
            }
            node.fillState_.SetOpacity(0.0);
            node.fillState_.SetColor(Color::TRANSPARENT);
        } },
        { DOM_SVG_FILL_OPACITY, [](const std::string& val, DOMSvgBase& node) {
            if (node.fillState_.GetColor() == Color::TRANSPARENT) {
                node.fillState_.SetOpacity(0.0);
                return;
            }
            node.fillState_.SetOpacity(StringToDouble(val));
        } },
        { DOM_SVG_STROKE, [](const std::string& val, DOMSvgBase& node) {
            if (val != VALUE_NONE) {
                node.strokeState_.SetColor(Color::FromString(val));
                return;
            }
            node.strokeState_.SetOpacity(0.0);
            node.strokeState_.SetColor(Color::TRANSPARENT);
        } },
        { DOM_SVG_STROKE_DASHARRAY, [](const std::string& val, DOMSvgBase& node) {
            std::vector<double> tmp;
            StringUtils::StringSpliter(val, ' ', tmp);
            node.strokeState_.SetLineDash(tmp);
        } },
        { DOM_SVG_STROKE_DASHOFFSET, [](const std::string& val, DOMSvgBase& node) {
            node.strokeState_.SetLineDashOffset(StringToDouble(val));
        } },
        { DOM_SVG_STROKE_LINECAP, [](const std::string& val, DOMSvgBase& node) {
            if (val == LINECAP_ROUND) {
                node.strokeState_.SetLineCap(LineCapStyle::ROUND);
            } else if (val == LINECAP_SQUARE) {
                node.strokeState_.SetLineCap(LineCapStyle::SQUARE);
            } else {
                node.strokeState_.SetLineCap(LineCapStyle::BUTT);
            }
        } },
        { DOM_SVG_STROKE_LINEJOIN, [](const std::string& val, DOMSvgBase& node) {
            if (val == LINEJOIN_BEVEL) {
                node.strokeState_.SetLineJoin(LineJoinStyle::BEVEL);
            } else if (val == LINEJOIN_ROUND) {
                node.strokeState_.SetLineJoin(LineJoinStyle::ROUND);
            } else {
                node.strokeState_.SetLineJoin(LineJoinStyle::MITER);
            }
        } },
        { DOM_SVG_STROKE_MITERLIMIT, [](const std::string& val, DOMSvgBase& node) {
            node.strokeState_.SetMiterLimit(StringToDouble(val));
        } },
        { DOM_SVG_STROKE_OPACITY, [](const std::string& val, DOMSvgBase& node) {
            node.strokeState_.SetOpacity(StringToDouble(val));
        } },
        { DOM_SVG_STROKE_WIDTH, [](const std::string& val, DOMSvgBase& node) {
            node.strokeState_.SetLineWidth(StringToDimension(val));
        } },
        { DOM_SVG_FONT_FAMILY, [](const std::string& val, DOMSvgBase& node) {
            node.textStyle_.SetFontFamilies(ConvertStrToFontFamilies(val));
        } },
        { DOM_SVG_FONT_SIZE, [](const std::string& val, DOMSvgBase& node) {
            node.textStyle_.SetFontSize(StringToDimension(val));
        } },
        { DOM_SVG_FONT_STYLE, [](const std::string& val, DOMSvgBase& node) {
            node.textStyle_.SetFontStyle(ConvertStrToFontStyle(val));
        } },
        { DOM_SVG_FONT_WEIGHT, [](const std::string& val, DOMSvgBase& node) {
            node.textStyle_.SetFontWeight(ConvertStrToFontWeight(val));
        } },
        { DOM_SVG_LETTER_SPACING, [](const std::string& val, DOMSvgBase& node) {
            node.textStyle_.SetLetterSpacing(StringToDouble(val));
        } },
        { DOM_SVG_TEXT_DECORATION, [](const std::string& val, DOMSvgBase& node) {
            node.textStyle_.SetTextDecoration(ConvertStrToTextDecoration(val));
        } },
    };
    auto attrIter = presentationAttrs.find(attr.first);
    if (attrIter == presentationAttrs.end()) {
        return false;
    }
    if (!attr.second.empty()) {
        attrIter->second(attr.second, *this);
    }
    return true;
}

void DOMSvgBase::PrepareCommonAttrs(const RefPtr<SvgSharp>& svgSharp)
{
    svgSharp->SetOpacity(std::clamp(opacity_, 0.0, 1.0));
    svgSharp->SetFillState(fillState_);
    svgSharp->SetStrokeState(strokeState_);
    svgSharp->SetTextStyle(textStyle_);
}

void DOMSvgBase::InheritCommonAttrs(const RefPtr<SvgSharp>& svgSharp, const RefPtr<DOMNode>& parentNode)
{
    auto svgNode = AceType::DynamicCast<DOMSvg>(parentNode);
    if (svgNode) {
        fillState_.Inherit(svgNode->GetFillState());
        strokeState_.Inherit(svgNode->GetStrokeState());
        textStyle_.Inherit(svgNode->GetTextStyle());
        svgSharp->SetFillState(fillState_);
        svgSharp->SetStrokeState(strokeState_);
        svgSharp->SetTextStyle(textStyle_);
    }
}

} // namespace OHOS::Ace::Framework
