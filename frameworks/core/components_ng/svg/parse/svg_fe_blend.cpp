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

#include "core/components_ng/svg/parse/svg_fe_blend.h"

#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {

RefPtr<SvgNode> SvgFeBlend::Create()
{
    return AceType::MakeRefPtr<SvgFeBlend>();
}

SvgFeBlend::SvgFeBlend() : SvgFe() {}

RSBlendMode SvgFeBlend::GetBlendMode(SvgFeBlendMode mode) const
{
    switch (mode) {
        case SvgFeBlendMode::NORMAL:
            return RSBlendMode::SRC_OVER;
        case SvgFeBlendMode::MULTIPLY:
            return RSBlendMode::MULTIPLY;
        case SvgFeBlendMode::SCREEN:
            return RSBlendMode::SCREEN;
        case SvgFeBlendMode::DARKEN:
            return RSBlendMode::DARKEN;
        case SvgFeBlendMode::LIGHTEN:
            return RSBlendMode::LIGHTEN;
        default:
            return RSBlendMode::SRC_OVER;
    };
}

void SvgFeBlend::OnAsImageFilter(std::shared_ptr<RSImageFilter>& imageFilter,
    const SvgColorInterpolationType& srcColor, SvgColorInterpolationType& currentColor,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash, bool cropRect) const
{
    auto blendMode = feBlendAttr_.blendMode;

    auto backImageFilter = MakeImageFilter(feBlendAttr_.in2, imageFilter, resultHash);
    auto foreImageFilter = MakeImageFilter(feAttr_.in, imageFilter, resultHash);
    ConverImageFilterColor(foreImageFilter, srcColor, currentColor);
    ConverImageFilterColor(backImageFilter, srcColor, currentColor);
    RSRect filterRect(effectFilterArea_.Left(), effectFilterArea_.Top(),
        effectFilterArea_.Right(), effectFilterArea_.Bottom());
    if (cropRect) {
        imageFilter = RSRecordingImageFilter::CreateBlendImageFilter(GetBlendMode(blendMode),
            backImageFilter, foreImageFilter, filterRect);
    } else {
        imageFilter = RSRecordingImageFilter::CreateBlendImageFilter(GetBlendMode(blendMode),
            backImageFilter, foreImageFilter);
    }
    ConverImageFilterColor(imageFilter, srcColor, currentColor);
    RegisterResult(feAttr_.result, imageFilter, resultHash);
}

bool SvgFeBlend::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgFeBlendAttribute&)> attrs[] = {
        { SVG_FE_IN2,
            [](const std::string& val, SvgFeBlendAttribute& attr) {
                static const LinearMapNode<SvgFeInType> IN_TABLE[] = {
                    { "BackgroundAlpha", SvgFeInType::BACKGROUND_ALPHA },
                    { "BackgroundImage", SvgFeInType::BACKGROUND_IMAGE },
                    { "FillPaint", SvgFeInType::FILL_PAINT },
                    { "SourceAlpha", SvgFeInType::SOURCE_ALPHA },
                    { "SourceGraphic", SvgFeInType::SOURCE_GRAPHIC },
                    { "StrokePaint", SvgFeInType::STROKE_PAINT },
                };
                int64_t inIndex = BinarySearchFindIndex(IN_TABLE, ArraySize(IN_TABLE), val.c_str());
                if (inIndex != -1) {
                    attr.in2.in = IN_TABLE[inIndex].value;
                } else {
                    attr.in2.id = val;
                }
            } },
        { SVG_FE_MODE,
            [](const std::string& val, SvgFeBlendAttribute& attr) {
                static const LinearMapNode<SvgFeBlendMode> EDGE_MODE_TABLE[] = {
                    { "darken", SvgFeBlendMode::DARKEN },
                    { "lighten", SvgFeBlendMode::LIGHTEN },
                    { "multiply", SvgFeBlendMode::MULTIPLY },
                    { "normal", SvgFeBlendMode::NORMAL },
                    { "screen", SvgFeBlendMode::SCREEN }
                };
                int64_t inIndex = BinarySearchFindIndex(EDGE_MODE_TABLE, ArraySize(EDGE_MODE_TABLE), val.c_str());
                if (inIndex != -1) {
                    attr.blendMode = EDGE_MODE_TABLE[inIndex].value;
                }
            } },
    };
    std::string key = name;
    StringUtils::TransformStrCase(key, StringUtils::TEXT_CASE_LOWERCASE);
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), key.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, feBlendAttr_);
        return true;
    }
    return SvgFe::ParseAndSetSpecializedAttr(name, value);
}

} // namespace OHOS::Ace::NG
