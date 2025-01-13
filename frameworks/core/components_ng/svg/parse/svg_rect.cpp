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

#include "frameworks/core/components_ng/svg/parse/svg_rect.h"

#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {

SvgRect::SvgRect() : SvgGraphic() {}

RefPtr<SvgNode> SvgRect::Create()
{
    return AceType::MakeRefPtr<SvgRect>();
}

RSRecordingPath SvgRect::AsPath(const Size& viewPort) const
{
    double rx = 0.0;
    if (GreatOrEqual(rectAttr_.rx.Value(), 0.0)) {
        rx = ConvertDimensionToPx(rectAttr_.rx, viewPort, SvgLengthType::HORIZONTAL);
    } else {
        if (GreatNotEqual(rectAttr_.ry.Value(), 0.0)) {
            rx = ConvertDimensionToPx(rectAttr_.ry, viewPort, SvgLengthType::VERTICAL);
        }
    }
    double ry = 0.0;
    if (GreatOrEqual(rectAttr_.ry.Value(), 0.0)) {
        ry = ConvertDimensionToPx(rectAttr_.ry, viewPort, SvgLengthType::VERTICAL);
    } else {
        if (GreatNotEqual(rectAttr_.rx.Value(), 0.0)) {
            ry = ConvertDimensionToPx(rectAttr_.rx, viewPort, SvgLengthType::HORIZONTAL);
        }
    }
    RSScalar left = ConvertDimensionToPx(rectAttr_.x, viewPort, SvgLengthType::HORIZONTAL);
    RSScalar top = ConvertDimensionToPx(rectAttr_.y, viewPort, SvgLengthType::VERTICAL);
    RSScalar width = ConvertDimensionToPx(rectAttr_.width, viewPort, SvgLengthType::HORIZONTAL);
    RSScalar height = ConvertDimensionToPx(rectAttr_.height, viewPort, SvgLengthType::VERTICAL);
    RSRoundRect roundRect = RSRoundRect(RSRect(left, top, width + left, height + top), rx, ry);
    RSRecordingPath path;
    path.AddRoundRect(roundRect);
    return path;
}

RSRecordingPath SvgRect::AsPath(const SvgLengthScaleRule& lengthRule)
{
    if (path_.has_value() && lengthRule_ == lengthRule) {
        return path_.value();
    }
    auto rx = GreatNotEqual(rectAttr_.rx.Value(), 0.0) ?
              GetMeasuredLength(rectAttr_.rx, lengthRule, SvgLengthType::HORIZONTAL) : 0.0;
    auto ry = GreatNotEqual(rectAttr_.ry.Value(), 0.0) ?
              GetMeasuredLength(rectAttr_.ry, lengthRule, SvgLengthType::VERTICAL) : 0.0;
    rx = GreatNotEqual(rx, 0.0) ? rx : ry;
    ry = GreatNotEqual(ry, 0.0) ? ry : rx;
    RSScalar left, top;
    left = GetMeasuredPosition(rectAttr_.x, lengthRule, SvgLengthType::HORIZONTAL) ;
    top = GetMeasuredPosition(rectAttr_.y, lengthRule, SvgLengthType::VERTICAL) ;
    RSScalar width = GetMeasuredLength(rectAttr_.width, lengthRule, SvgLengthType::HORIZONTAL);
    RSScalar height = GetMeasuredLength(rectAttr_.height, lengthRule, SvgLengthType::VERTICAL);
    RSRoundRect roundRect = RSRoundRect(RSRect(left, top, width + left, height + top), rx, ry);
    RSRecordingPath path;
    path.AddRoundRect(roundRect);
    path_ = path;
    return path;
}

bool SvgRect::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgRectAttribute&)> attrs[] = {
        { SVG_HEIGHT,
            [](const std::string& val, SvgRectAttribute& attr) {
                attr.height = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_RX,
            [](const std::string& val, SvgRectAttribute& attr) {
                attr.rx = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_RY,
            [](const std::string& val, SvgRectAttribute& attr) {
                attr.ry = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_WIDTH,
            [](const std::string& val, SvgRectAttribute& attr) {
                attr.width = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_X,
            [](const std::string& val, SvgRectAttribute& attr) {
                attr.x = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_Y,
            [](const std::string& val, SvgRectAttribute& attr) {
                attr.y = SvgAttributesParser::ParseDimension(val);
            } },
    };
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), name.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, rectAttr_);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
