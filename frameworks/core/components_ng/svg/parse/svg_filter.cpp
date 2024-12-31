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

bool SvgFilter::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgFilterAttribute&)> attrs[] = {
        { SVG_HEIGHT,
            [](const std::string& val, SvgFilterAttribute& attr) {
                attr.height = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_WIDTH,
            [](const std::string& val, SvgFilterAttribute& attr) {
                attr.width = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_X,
            [](const std::string& val, SvgFilterAttribute& attr) {
                attr.x = SvgAttributesParser::ParseDimension(val);
            } },
        { SVG_Y,
            [](const std::string& val, SvgFilterAttribute& attr) {
                attr.y = SvgAttributesParser::ParseDimension(val);
            } },
    };
    std::string key = name;
    StringUtils::TransformStrCase(key, StringUtils::TEXT_CASE_LOWERCASE);
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), key.c_str());
    if (attrIter != -1) {
        attrs[attrIter].value(value, filterAttr_);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
