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

#include "frameworks/core/components_ng/svg/parse/svg_fe.h"

#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {
namespace {
static const LinearMapNode<void (*)(const std::string&, SvgFeCommonAttribute&)> FE_ATTRS[] = {
    { SVG_FE_COLOR_INTERPOLATION_FILTERS,
        [](const std::string& val, SvgFeCommonAttribute& attr) {
            static const LinearMapNode<SvgColorInterpolationType> COLOR_INTERPOLATION_TYPE_TABLE[] = {
                { "auto", SvgColorInterpolationType::AUTO },
                { "linearRGB", SvgColorInterpolationType::LINEAR_RGB },
                { "sRGB", SvgColorInterpolationType::SRGB },
            };
            int64_t inIndex = BinarySearchFindIndex(
                COLOR_INTERPOLATION_TYPE_TABLE, ArraySize(COLOR_INTERPOLATION_TYPE_TABLE), val.c_str());
            if (inIndex != -1) {
                attr.colorInterpolationType = COLOR_INTERPOLATION_TYPE_TABLE[inIndex].value;
            }
        } },
    { SVG_HEIGHT,
        [](const std::string& val, SvgFeCommonAttribute& attr) {
            attr.height = SvgAttributesParser::ParseDimension(val);
            if (attr.height.IsValid()) {
                attr.isHeightValid = true;
            }
        } },
    { SVG_FE_IN,
        [](const std::string& val, SvgFeCommonAttribute& attr) {
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
                attr.in.in = IN_TABLE[inIndex].value;
            } else {
                attr.in.id = val;
            }
        } },
    { SVG_FE_RESULT,
        [](const std::string& val, SvgFeCommonAttribute& attr) {
            attr.result = val;
        } },
    { SVG_WIDTH,
        [](const std::string& val, SvgFeCommonAttribute& attr) {
            attr.width = SvgAttributesParser::ParseDimension(val);
            if (attr.width.IsValid()) {
                attr.isWidthValid = true;
            }
        } },
    { SVG_X,
        [](const std::string& val, SvgFeCommonAttribute& attr) {
            attr.x = SvgAttributesParser::ParseDimension(val);
        } },
    { SVG_Y,
        [](const std::string& val, SvgFeCommonAttribute& attr) {
            attr.y = SvgAttributesParser::ParseDimension(val);
        } },
};
}

SvgColorInterpolationType GetColorType(const SvgFeCommonAttribute& fe)
{
    if (fe.in.in == SvgFeInType::SOURCE_GRAPHIC) {
        return SvgColorInterpolationType::SRGB;
    }
    return fe.colorInterpolationType;
}

void InitFilterColor(const SvgFeCommonAttribute& fe, SvgColorInterpolationType& currentColor)
{
    if (fe.in.in == SvgFeInType::SOURCE_GRAPHIC) {
        currentColor = SvgColorInterpolationType::SRGB;
    } else {
        currentColor = fe.colorInterpolationType;
    }
}

void SvgFe::OnInitStyle() {}

void SvgFe::RegisterResult(const std::string& id, std::shared_ptr<RSImageFilter>& imageFilter,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash) const
{
    if (!id.empty()) {
        resultHash[id] = imageFilter;
    }
}

SvgFe::SvgFe() : SvgNode()
{
    InitNoneFlag();
}

void SvgFe::GetImageFilter(std::shared_ptr<RSImageFilter>& imageFilter, SvgColorInterpolationType& currentColor,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash,
    const Rect& effectFilterArea)
{
    SvgColorInterpolationType srcColor = currentColor;
    OnInitStyle();
    InitFilterColor(feAttr_, currentColor);
    Rect effectFeArea = effectFilterArea;
    if (feAttr_.x.Unit() != DimensionUnit::PERCENT) {
        effectFeArea.SetLeft(feAttr_.x.Value());
    }
    if (feAttr_.y.Unit() != DimensionUnit::PERCENT) {
        effectFeArea.SetTop(feAttr_.y.Value());
    }
    effectFeArea.SetWidth(feAttr_.width.ConvertToPxWithSize(effectFilterArea.Width()));
    effectFeArea.SetHeight(feAttr_.height.ConvertToPxWithSize(effectFilterArea.Height()));
    effectFilterArea_ = effectFilterArea.IntersectRect(effectFeArea);
    OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash);
    currentColor = srcColor;
}

void SvgFe::GetImageFilter(std::shared_ptr<RSImageFilter>& imageFilter, std::unordered_map<std::string,
                           std::shared_ptr<RSImageFilter>>& resultHash)
{
    OnInitStyle();
    auto currentColorInterpolation = GetColorType(feAttr_);
    effectFilterArea_ = ResolvePrimitiveSubRegion();
    OnAsImageFilter(imageFilter, SvgColorInterpolationType::SRGB, currentColorInterpolation, resultHash, true);
}

Rect SvgFe::ResolvePrimitiveSubRegion()
{
    auto filterAreaContext = GetFilterContext();
    // if dimension is invalid , just return filter effect area
    if (!(feAttr_.isHeightValid && feAttr_.isWidthValid)) {
        return filterAreaContext.GetFilterArea();
    }
    auto primitiveRule = filterAreaContext.GetPrimitiveRule();
    auto measuredX = GetRegionPosition(feAttr_.x, primitiveRule, SvgLengthType::HORIZONTAL);
    auto measuredY = GetRegionPosition(feAttr_.y, primitiveRule, SvgLengthType::VERTICAL);
    auto measuredWidth = GetRegionLength(feAttr_.width, primitiveRule, SvgLengthType::HORIZONTAL);
    auto measuredHeight = GetRegionLength(feAttr_.height, primitiveRule, SvgLengthType::VERTICAL);

    Rect primitiveArea = {measuredX, measuredY, measuredWidth, measuredHeight};
    return filterAreaContext.GetFilterArea().IntersectRect(primitiveArea);
}

void SvgFe::ConverImageFilterColor(std::shared_ptr<RSImageFilter>& imageFilter,
    const SvgColorInterpolationType& srcColor, const SvgColorInterpolationType& dst)
{
    if (dst == SvgColorInterpolationType::LINEAR_RGB && srcColor == SvgColorInterpolationType::SRGB) {
        auto colorFilter = RSRecordingColorFilter::CreateSrgbGammaToLinear();
        CHECK_NULL_VOID(colorFilter);
        imageFilter = RSRecordingImageFilter::CreateColorFilterImageFilter(*colorFilter, imageFilter);
    } else if (dst == SvgColorInterpolationType::SRGB && srcColor == SvgColorInterpolationType::LINEAR_RGB) {
        auto colorFilter = RSRecordingColorFilter::CreateLinearToSrgbGamma();
        CHECK_NULL_VOID(colorFilter);
        imageFilter = RSRecordingImageFilter::CreateColorFilterImageFilter(*colorFilter, imageFilter);
    }
}

std::shared_ptr<RSImageFilter> SvgFe::MakeImageFilter(const SvgFeIn& in, std::shared_ptr<RSImageFilter>& imageFilter,
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>>& resultHash)
{
    switch (in.in) {
        case SvgFeInType::SOURCE_GRAPHIC:
            return nullptr;
        case SvgFeInType::SOURCE_ALPHA: {
            RSColorMatrix m;
            m.SetScale(0, 0, 0, 1.0f);
            auto colorFilter = RSRecordingColorFilter::CreateMatrixColorFilter(m);
            CHECK_NULL_RETURN(colorFilter, nullptr);
            return RSRecordingImageFilter::CreateColorFilterImageFilter(*colorFilter, nullptr);
        }
        case SvgFeInType::BACKGROUND_IMAGE:
            break;
        case SvgFeInType::BACKGROUND_ALPHA:
            break;
        case SvgFeInType::FILL_PAINT:
            break;
        case SvgFeInType::STROKE_PAINT:
            break;
        case SvgFeInType::PRIMITIVE:
            if (!in.id.empty()) {
                auto it = resultHash.find(in.id);
                if (it != resultHash.end()) {
                    return it->second;
                }
            }
            break;
        default:
            break;
    }
    return imageFilter;
}

bool SvgFe::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    std::string key = name;
    StringUtils::TransformStrCase(key, StringUtils::TEXT_CASE_LOWERCASE);
    auto attrIter = BinarySearchFindIndex(FE_ATTRS, ArraySize(FE_ATTRS), key.c_str());
    if (attrIter != -1) {
        FE_ATTRS[attrIter].value(value, feAttr_);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
