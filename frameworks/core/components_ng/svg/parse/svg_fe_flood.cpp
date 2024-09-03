/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/svg/parse/svg_fe_flood.h"

#include "core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {

RefPtr<SvgNode> SvgFeFlood::Create()
{
    return AceType::MakeRefPtr<SvgFeFlood>();
}

SvgFeFlood::SvgFeFlood() : SvgFe() {}

void SvgFeFlood::OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter,
    const SvgColorInterpolationType& srcColor, SvgColorInterpolationType& currentColor,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash) const
{
    imageFilter = MakeImageFilter(feAttr_.in, imageFilter, resultHash);

    auto floodColor = feFloodAttr_.floodColor;
    auto floodOpacity = feFloodAttr_.floodOpacity;

    floodColor = floodColor.ChangeOpacity(floodOpacity);
    auto shaderFilter = RSRecordingShaderEffect::CreateColorShader(floodColor.GetValue());
    CHECK_NULL_VOID(shaderFilter);
    Rect effectFilterArea = effectFilterArea_;

    imageFilter = RSRecordingImageFilter::CreateShaderImageFilter(shaderFilter,
        { effectFilterArea.Left(), effectFilterArea.Top(), effectFilterArea.Right(), effectFilterArea.Bottom() });

    ConverImageFilterColor(imageFilter, srcColor, currentColor);
    RegisterResult(feAttr_.result, imageFilter, resultHash);
}

bool SvgFeFlood::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgFeFloodAttribute&)> attrs[] = {
        { SVG_FE_FLOOD_COLOR,
            [](const std::string& val, SvgFeFloodAttribute& attr) {
                attr.floodColor = SvgAttributesParser::GetColor(val);
            } },
        { SVG_FE_FLOOD_OPACITY,
            [](const std::string& val, SvgFeFloodAttribute& attr) {
                attr.floodOpacity = SvgAttributesParser::ParseDouble(val);
            } },
    };
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), name.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, feFloodAttr_);
        return true;
    }
    return SvgFe::ParseAndSetSpecializedAttr(name, value);
}

} // namespace OHOS::Ace::NG
