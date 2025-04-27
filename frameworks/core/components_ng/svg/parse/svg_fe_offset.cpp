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

#include "frameworks/core/components_ng/svg/parse/svg_fe_offset.h"

#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {

RefPtr<SvgNode> SvgFeOffset::Create()
{
    return AceType::MakeRefPtr<SvgFeOffset>();
}

SvgFeOffset::SvgFeOffset() : SvgFe() {}

void SvgFeOffset::OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter,
    const SvgColorInterpolationType& srcColor, SvgColorInterpolationType& currentColor,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash, bool cropRect) const
{
    imageFilter = MakeImageFilter(feAttr_.in, imageFilter, resultHash);
    if (cropRect) {
        float dx = 0.0;
        float dy = 0.0;
        auto filterContext = GetFilterContext();
        auto primitiveRule = filterContext.GetPrimitiveRule();
        if (primitiveRule.GetLengthScaleUnit() == SvgLengthScaleUnit::OBJECT_BOUNDING_BOX) {
            dx = feOffsetAttr_.dx.Value() * primitiveRule.GetContainerRect().Width();
            dy = feOffsetAttr_.dy.Value() * primitiveRule.GetContainerRect().Height();
        } else {
            dx = feOffsetAttr_.dx.Value();
            dy = feOffsetAttr_.dy.Value();
        }
        RSRect filterRect(effectFilterArea_.Left(), effectFilterArea_.Top(),
            effectFilterArea_.Right(), effectFilterArea_.Bottom());
        imageFilter = RSRecordingImageFilter::CreateOffsetImageFilter(dx, dy, imageFilter, filterRect);
    } else {
        imageFilter = RSRecordingImageFilter::CreateOffsetImageFilter(feOffsetAttr_.dx.Value(),
            feOffsetAttr_.dy.Value(), imageFilter);
    }
    ConverImageFilterColor(imageFilter, srcColor, currentColor);
    RegisterResult(feAttr_.result, imageFilter, resultHash);
}

bool SvgFeOffset::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgFeOffsetAttribute&)> attrs[] = {
        { SVG_DX,
            [](const std::string& val, SvgFeOffsetAttribute& attr) {
                attr.dx = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_DY,
            [](const std::string& val, SvgFeOffsetAttribute& attr) {
                attr.dy = SvgAttributesParser::ParseDimension(val);
            } },
    };
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), name.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, feOffsetAttr_);
        return true;
    }
    return SvgFe::ParseAndSetSpecializedAttr(name, value);
}

} // namespace OHOS::Ace::NG
