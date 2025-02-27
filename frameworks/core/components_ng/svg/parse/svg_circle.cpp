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

#include "frameworks/core/components_ng/svg/parse/svg_circle.h"

#include "core/components_ng/svg/parse/svg_animation.h"
#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {

SvgCircle::SvgCircle() : SvgGraphic() {}

RefPtr<SvgNode> SvgCircle::Create()
{
    return AceType::MakeRefPtr<SvgCircle>();
}

RSRecordingPath SvgCircle::AsPath(const Size& viewPort) const
{
    RSRecordingPath path;
    path.AddCircle(ConvertDimensionToPx(circleAttr_.cx, viewPort, SvgLengthType::HORIZONTAL),
        ConvertDimensionToPx(circleAttr_.cy, viewPort, SvgLengthType::VERTICAL),
        ConvertDimensionToPx(circleAttr_.r, viewPort, SvgLengthType::OTHER));
    return path;
}

RSRecordingPath SvgCircle::AsPath(const SvgLengthScaleRule& lengthRule)
{
    /* re-generate the Path for pathTransform(true). AsPath come from clip-path */
    if (path_.has_value() && lengthRule_ == lengthRule && !lengthRule.GetPathTransform()) {
        return path_.value();
    }
    RSRecordingPath path;
    auto cx = GetMeasuredPosition(circleAttr_.cx, lengthRule, SvgLengthType::HORIZONTAL);
    auto cy = GetMeasuredPosition(circleAttr_.cy, lengthRule, SvgLengthType::VERTICAL);
    path.AddCircle(cx, cy, GetMeasuredLength(circleAttr_.r, lengthRule, SvgLengthType::OTHER));
    lengthRule_ = lengthRule;
    path_ = path;
    /* Apply path transform for clip-path only */
    if (lengthRule.GetPathTransform()) {
        ApplyTransform(path);
    }
    return path;
}

void SvgCircle::PrepareAnimation(const RefPtr<SvgAnimation>& animate)
{
    auto attr = animate->GetAttributeName();
    if (attr == SVG_CX) {
        AnimateOnAttribute(animate, circleAttr_.cx);
    } else if (attr == SVG_CY) {
        AnimateOnAttribute(animate, circleAttr_.cy);
    } else if (attr == SVG_R) {
        AnimateOnAttribute(animate, circleAttr_.r);
    } else {
        SvgNode::PrepareAnimation(animate);
    }
}

bool SvgCircle::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgCircleAttribute&)> attrs[] = {
        { SVG_CX,
            [](const std::string& val, SvgCircleAttribute& attr) {
                attr.cx = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_CY,
            [](const std::string& val, SvgCircleAttribute& attr) {
                attr.cy = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_R,
            [](const std::string& val, SvgCircleAttribute& attr) {
                attr.r = SvgAttributesParser::ParseDimension(val);
            } },
    };
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), name.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, circleAttr_);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
