/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/gauge/gauge_pattern.h"

#include "core/common/container.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/gauge/gauge_layout_algorithm.h"
#include "core/components_ng/pattern/gauge/gauge_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
bool GaugePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool /*skipLayout*/)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    return true;
}

void GaugePattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPositionProperty()) {
        layoutProperty->UpdateAlignment(
            layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER));
    } else {
        layoutProperty->UpdateAlignment(Alignment::CENTER);
    }

    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (host->TotalChildCount() > 0) {
            auto firstChild = host->GetFirstChild();
            CHECK_NULL_VOID(firstChild);
            titleChildId_ = firstChild->GetId();
        }

        auto gaugeLayoutProperty = GetLayoutProperty<GaugeLayoutProperty>();
        CHECK_NULL_VOID(gaugeLayoutProperty);

        if (gaugeLayoutProperty->GetIsShowLimitValueValue(false)) {
            InitLimitValueText(GetMinValueTextId(), true);
            InitLimitValueText(GetMaxValueTextId(), false);
        }
        if (gaugeLayoutProperty->GetIsShowDescriptionValue(false)) {
            InitDescriptionNode();
        }
    }
}

void GaugePattern::InitDescriptionNode()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto linearNode = FrameNode::GetOrCreateFrameNode(V2::GAUGE_DESCRIPTION_TAG, GetDescriptionNodeId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto descriptionRenderContext = linearNode->GetRenderContext();
    CHECK_NULL_VOID(descriptionRenderContext);
    descriptionRenderContext->UpdateClipEdge(true);
    CHECK_NULL_VOID(descriptionNode_);
    descriptionNode_->MountToParent(linearNode);
    auto property = linearNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(property);

    linearNode->MountToParent(frameNode);
    linearNode->MarkModifyDone();
}

void GaugePattern::InitLimitValueText(const int32_t valueTextId, const bool isMin)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto gaugePaintProperty = GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(gaugePaintProperty);
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, valueTextId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(textNode);

    auto limitValue =
        isMin ? gaugePaintProperty->GetMinValue(DEFAULT_MIN_VALUE) : gaugePaintProperty->GetMaxValue(DEFAULT_MAX_VALUE);
    auto limitValueColor = Color::BLACK;
    if (gaugePaintProperty->HasGradientColors()) {
        limitValueColor = isMin ? gaugePaintProperty->GetGradientColorsValue().at(0).at(0).first
                                : GetMaxValueColor(gaugePaintProperty);
    } else {
        limitValueColor = isMin ? (*GAUGE_DEFAULT_COLOR.begin()) : (*GAUGE_DEFAULT_COLOR.rbegin());
    }
    std::ostringstream out;
    out << std::setiosflags(std::ios::fixed) << std::setprecision(0) << limitValue;

    auto limitValueTextProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(limitValueTextProperty);
    limitValueTextProperty->UpdateContent(out.str());
    limitValueTextProperty->UpdateTextColor(limitValueColor);
    limitValueTextProperty->UpdateMaxLines(1);
    limitValueTextProperty->UpdateAdaptMaxFontSize(LIMIT_VALUE_MAX_FONTSIZE);
    limitValueTextProperty->UpdateAdaptMinFontSize(LIMIT_VALUE_MIN_FONTSIZE);
    limitValueTextProperty->UpdateFontWeight(FontWeight::MEDIUM);
    limitValueTextProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    auto textAlign = isMin ? TextAlign::LEFT : TextAlign::RIGHT;
    limitValueTextProperty->UpdateTextAlign(textAlign);

    textNode->MountToParent(frameNode);
    textNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    textNode->MarkModifyDone();
}

Color GaugePattern::GetMaxValueColor(const RefPtr<GaugePaintProperty>& gaugePaintProperty) const
{
    Color color(Color::BLACK);
    CHECK_NULL_RETURN(gaugePaintProperty, color);
    switch (gaugePaintProperty->GetGaugeTypeValue(GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT)) {
        case GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT: {
            color = gaugePaintProperty->GetGradientColorsValue().rbegin()->rbegin()->first;
            break;
        }
        case GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT: {
            color = gaugePaintProperty->GetGradientColorsValue().at(0).rbegin()->first;
            break;
        }
        case GaugeType::TYPE_CIRCULAR_MONOCHROME: {
            color = gaugePaintProperty->GetGradientColorsValue().at(0).at(0).first;
            break;
        }
        default:
            // do nothing.
            break;
    }
    return color;
}
} // namespace OHOS::Ace::NG
