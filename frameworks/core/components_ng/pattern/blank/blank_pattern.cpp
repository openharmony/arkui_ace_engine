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

#include "core/components_ng/pattern/blank/blank_pattern.h"

#include "base/log/dump_log.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

namespace OHOS::Ace::NG {

namespace {
FlexDirection GetFlexDirection(const RefPtr<UINode>& node)
{
    auto tag = node->GetTag();
    if (tag == V2::ROW_ETS_TAG) {
        return FlexDirection::ROW;
    }
    if (tag == V2::COLUMN_ETS_TAG) {
        return FlexDirection::COLUMN;
    }
    if (tag != V2::FLEX_ETS_TAG) {
        return FlexDirection::ROW;
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_RETURN(frameNode, FlexDirection::ROW);
    auto layoutProperty = frameNode->GetLayoutProperty<FlexLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, FlexDirection::ROW);
    return layoutProperty->GetFlexDirection().value_or(FlexDirection::ROW);
}
} // namespace

std::string BlankPattern::GetColorString() const
{
    auto paintProperty = GetPaintProperty<BlankPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, "NA");
    return paintProperty->GetColorValue(Color::TRANSPARENT).ColorToString();
}

void BlankPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("color", GetColorString().c_str(), filter);
}

void BlankPattern::DumpInfo()
{
    auto blankProperty = GetLayoutProperty<BlankLayoutProperty>();
    CHECK_NULL_VOID(blankProperty);
    auto blankMin = blankProperty->GetMinSize().value_or(Dimension());
    DumpLog::GetInstance().AddDesc(std::string("min: ").append(blankMin.ToString().c_str()));
}

void BlankPattern::BeforeCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parent = host->GetAncestorNodeOfFrame();
    CHECK_NULL_VOID(parent);
    auto layoutProp = host->GetLayoutProperty<BlankLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        return;
    }
    const auto& calcConstraint = layoutProp->GetCalcLayoutConstraint();
    auto isParentRow = GetFlexDirection(parent) == FlexDirection::ROW;
    layoutProp->ResetAlignSelf();
    layoutProp->ResetFlexGrow();
    layoutProp->ResetFlexShrink();
    bool mainAxisHasSize = false;
    bool crossAxisHasSize = false;
    if (calcConstraint && calcConstraint->selfIdealSize.has_value()) {
        mainAxisHasSize = (isParentRow && calcConstraint->selfIdealSize.value().Width().has_value()) ||
                          (!isParentRow && calcConstraint->selfIdealSize.value().Height().has_value());
        crossAxisHasSize = (isParentRow && calcConstraint->selfIdealSize.value().Height().has_value()) ||
                           (!isParentRow && calcConstraint->selfIdealSize.value().Width().has_value());
    }
    if (!crossAxisHasSize) {
        layoutProp->UpdateAlignSelf(FlexAlign::STRETCH);
    }
    if (!mainAxisHasSize) {
        layoutProp->UpdateFlexGrow(1.0f);
        layoutProp->UpdateFlexShrink(1.0f);
    }
    CHECK_NULL_VOID(layoutProp->GetMinSize().has_value());
    auto blankMin = layoutProp->GetMinSize().value_or(Dimension(0.0, DimensionUnit::VP));
    if (isParentRow) {
        if (!(calcConstraint && calcConstraint->minSize.has_value() &&
                calcConstraint->minSize.value().Width().has_value())) {
            layoutProp->UpdateCalcMinSize(CalcSize(CalcLength(blankMin), std::nullopt));
        }
    } else {
        if (!(calcConstraint && calcConstraint->minSize.has_value() &&
                calcConstraint->minSize.value().Height().has_value())) {
            layoutProp->UpdateCalcMinSize(CalcSize(std::nullopt, CalcLength(blankMin)));
        }
    }
}

void BlankPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto blankProperty = GetLayoutProperty<BlankLayoutProperty>();
    CHECK_NULL_VOID(blankProperty);
    auto blankMin = blankProperty->GetMinSize().value_or(Dimension());
    json->Put("min", blankMin.ToString().c_str());
}

void BlankPattern::DumpSimplifyInfo(std::unique_ptr<JsonValue>& json)
{
    auto blankProperty = GetLayoutProperty<BlankLayoutProperty>();
    CHECK_NULL_VOID(blankProperty);
    auto blankMin = blankProperty->GetMinSize().value_or(Dimension());
    if (blankMin != Dimension(0.0, blankMin.Unit())) {
        json->Put("Min", blankMin.ToString().c_str());
    }
}
} // namespace OHOS::Ace::NG
