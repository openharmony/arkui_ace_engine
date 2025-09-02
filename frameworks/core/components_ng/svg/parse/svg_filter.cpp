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

#include "frameworks/core/components_ng/svg/parse/svg_filter.h"

#include "core/components_ng/svg/base/svg_filter_context.h"
#include "core/common/container.h"
#include "frameworks/core/components_ng/svg/parse/svg_constants.h"
#include "frameworks/core/components_ng/svg/parse/svg_fe.h"

namespace OHOS::Ace::NG {

SvgFilter::SvgFilter() : SvgQuote() {}

RefPtr<SvgNode> SvgFilter::Create()
{
    return AceType::MakeRefPtr<SvgFilter>();
}

void SvgFilter::OnInitStyle() {}

void SvgFilter::OnDrawTraversed(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    OnAsPaint();
}

void SvgFilter::OnDrawTraversedBefore(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
}

void SvgFilter::OnDrawTraversedAfter(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color)
{
    RSSaveLayerOps slo(nullptr, &filterBrush_);
    rsCanvas_->SaveLayer(slo);
}

void SvgFilter::OnAsPaint()
{
    filterBrush_.SetAntiAlias(true);
    std::shared_ptr<RSImageFilter> imageFilter = nullptr;
    SvgColorInterpolationType currentColor = SvgColorInterpolationType::SRGB;

    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>> resultHash;

    Rect filterEffectsRegion = GetEffectFilterArea();
    Rect effectFilterArea = {
        filterEffectsRegion.Left() + filterEffectsRegion.Width() * filterAttr_.x.Value(),
        filterEffectsRegion.Top() + filterEffectsRegion.Height() * filterAttr_.y.Value(),
        filterEffectsRegion.Width() * filterAttr_.width.Value(),
        filterEffectsRegion.Height() * filterAttr_.height.Value()
    };

    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        if (filterAttr_.x.Unit() != DimensionUnit::PERCENT) {
            effectFilterArea.SetLeft(filterAttr_.x.Value());
        }
        if (filterAttr_.y.Unit() != DimensionUnit::PERCENT) {
            effectFilterArea.SetTop(filterAttr_.y.Value());
        }
        if (filterAttr_.width.Unit() != DimensionUnit::PERCENT) {
            effectFilterArea.SetWidth(filterAttr_.width.Value());
        }
        if (filterAttr_.height.Unit() != DimensionUnit::PERCENT) {
            effectFilterArea.SetHeight(filterAttr_.height.Value());
        }
    }

    for (const auto& item : children_) {
        auto nodeFe = AceType::DynamicCast<SvgFe>(item);
        if (!nodeFe) {
            continue;
        }
        nodeFe->GetImageFilter(imageFilter, currentColor, resultHash, effectFilterArea);
    }

    SvgFe::ConverImageFilterColor(imageFilter, currentColor, SvgColorInterpolationType::SRGB);
    auto filter = filterBrush_.GetFilter();
    filter.SetImageFilter(imageFilter);
    filterBrush_.SetFilter(filter);
}

void SvgFilter::OnFilterEffect(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext,
    float useOffsetX, float useOffsetY)
{
    auto filterRule = svgCoordinateSystemContext.BuildScaleRule(filterAttr_.filterUnits);
    auto measuredX = GetRegionPosition(filterAttr_.x, filterRule, SvgLengthType::HORIZONTAL);
    auto measuredY = GetRegionPosition(filterAttr_.y, filterRule, SvgLengthType::VERTICAL);
    auto measuredWidth = GetRegionLength(filterAttr_.width, filterRule, SvgLengthType::HORIZONTAL);
    auto measuredHeight = GetRegionLength(filterAttr_.height, filterRule, SvgLengthType::VERTICAL);
    Rect effectFilterArea = {
        measuredX + useOffsetX,
        measuredY + useOffsetY,
        measuredWidth,
        measuredHeight
    };
    std::shared_ptr<RSImageFilter> imageFilter = nullptr;
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>> resultHash;
    auto primitiveRule = svgCoordinateSystemContext.BuildScaleRule(filterAttr_.primitiveUnits);
    SvgFilterContext filterContext(effectFilterArea, filterRule, primitiveRule);
    for (const auto& item : children_) {
        auto nodeFe = AceType::DynamicCast<SvgFe>(item);
        if (!nodeFe) {
            continue;
        }
        nodeFe->SetFilterContext(filterContext);
        nodeFe->GetImageFilter(imageFilter, resultHash);
    }
    auto filter = filterBrush_.GetFilter();
    filter.SetImageFilter(imageFilter);
    filterBrush_.SetAntiAlias(true);
    filterBrush_.SetFilter(filter);
    RSSaveLayerOps slo(nullptr, &filterBrush_);
    canvas.SaveLayer(slo);
}

bool SvgFilter::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgFilterAttribute&)> attrs[] = {
        { SVG_FILTER_UNITS,
            [](const std::string& val, SvgFilterAttribute& attr) {
                attr.filterUnits = (val == "userSpaceOnUse") ? SvgLengthScaleUnit::USER_SPACE_ON_USE :
                    SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
            } },
        { SVG_HEIGHT,
            [](const std::string& val, SvgFilterAttribute& attr) {
                SvgAttributesParser::ParseDimension(val, attr.height, attr.featureEnable);
            } },
        { SVG_PRIMITIVE_UNITS,
            [](const std::string& val, SvgFilterAttribute& attr) {
                attr.primitiveUnits = (val == "objectBoundingBox") ? SvgLengthScaleUnit::OBJECT_BOUNDING_BOX :
                    SvgLengthScaleUnit::USER_SPACE_ON_USE;
            } },
        { SVG_WIDTH,
            [](const std::string& val, SvgFilterAttribute& attr) {
                SvgAttributesParser::ParseDimension(val, attr.width, attr.featureEnable);
            } },
        { SVG_X,
            [](const std::string& val, SvgFilterAttribute& attr) {
                SvgAttributesParser::ParseDimension(val, attr.x, attr.featureEnable);
            } },
        { SVG_Y,
            [](const std::string& val, SvgFilterAttribute& attr) {
                SvgAttributesParser::ParseDimension(val, attr.y, attr.featureEnable);
            } },
    };
    std::string key = name;
    StringUtils::TransformStrCase(key, StringUtils::TEXT_CASE_LOWERCASE);
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), key.c_str());
    if (attrIter != -1) {
        filterAttr_.featureEnable = SvgUtils::IsFeatureEnable(SVG_FEATURE_SUPPORT_TWO, GetUsrConfigVersion());
        attrs[attrIter].value(value, filterAttr_);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
