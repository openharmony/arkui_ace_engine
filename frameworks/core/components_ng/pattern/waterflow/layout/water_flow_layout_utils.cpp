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
#include "frameworks/core/components_ng/pattern/waterflow/layout/water_flow_layout_utils.h"

#include "core/components_ng/pattern/waterflow/water_flow_item_layout_property.h"
#include "core/components_ng/property/measure_utils.h"
namespace OHOS::Ace::NG {
namespace {
const std::string UNIT_AUTO = "auto";
}
std::string WaterFlowLayoutUtils::PreParseArgs(const std::string& args)
{
    if (args.empty() || args.find(UNIT_AUTO) == std::string::npos) {
        return args;
    }
    std::string rowsArgs;
    std::vector<std::string> strs;
    StringUtils::StringSplitter(args, ' ', strs);
    std::string current;
    size_t rowArgSize = strs.size();
    for (size_t i = 0; i < rowArgSize; ++i) {
        current = strs[i];
        // "auto" means 1fr in waterflow
        if (strs[i] == std::string(UNIT_AUTO)) {
            current = "1fr";
        }
        rowsArgs += ' ' + current;
    }
    return rowsArgs;
}

FlowItemPosition WaterFlowLayoutUtils::GetItemPosition(
    const RefPtr<WaterFlowLayoutInfo>& info, int32_t index, float mainGap)
{
    auto crossIndex = info->GetCrossIndex(index);
    // already in layoutInfo
    if (crossIndex != -1) {
        return { crossIndex, info->GetStartMainPos(crossIndex, index) };
    }
    int32_t segment = info->GetSegment(index);
    auto itemIndex = info->GetCrossIndexForNextItem(segment);
    if (static_cast<int32_t>(info->segmentStartPos_.size()) <= segment) {
        TAG_LOGI(AceLogTag::ACE_WATERFLOW, "The size of segmentStartPos %{public}zu is less than expected %{public}d.",
            info->segmentStartPos_.size(), segment);
        return { itemIndex.crossIndex, 0.0f };
    }
    if (itemIndex.lastItemIndex < 0) {
        return { itemIndex.crossIndex, info->segmentStartPos_[segment] };
    }
    auto mainHeight = info->GetMainHeight(itemIndex.crossIndex, itemIndex.lastItemIndex);
    return { itemIndex.crossIndex, mainHeight + mainGap };
}

LayoutConstraintF WaterFlowLayoutUtils::CreateChildConstraint(
    const ConstraintParams& params, const RefPtr<WaterFlowLayoutProperty>& props, const RefPtr<LayoutWrapper>& child)
{
    auto itemConstraint = props->CreateChildConstraint();
    auto itemMainSize = params.mainSize;
    auto itemIdealSize =
        params.axis == Axis::VERTICAL ? SizeF(params.crossSize, itemMainSize) : SizeF(itemMainSize, params.crossSize);

    itemConstraint.maxSize = itemIdealSize;
    itemConstraint.maxSize.SetMainSize(Infinity<float>(), params.axis);
    itemConstraint.parentIdealSize = OptionalSizeF(itemIdealSize);
    itemConstraint.percentReference = itemIdealSize;

    CHECK_NULL_RETURN(props->HasItemLayoutConstraint() && !params.haveUserDefSize, itemConstraint);

    OptionalSizeF childMinSize;
    OptionalSizeF childMaxSize;
    // Waterflow ItemLayoutConstraint
    auto itemMinSize = props->GetItemMinSize();
    if (itemMinSize.has_value()) {
        childMinSize =
            ConvertToOptionalSize(itemMinSize.value(), props->GetLayoutConstraint()->scaleProperty, itemIdealSize);
    }
    auto itemMaxSize = props->GetItemMaxSize();
    if (itemMaxSize.has_value()) {
        childMaxSize =
            ConvertToOptionalSize(itemMaxSize.value(), props->GetLayoutConstraint()->scaleProperty, itemIdealSize);
    }

    if (childMaxSize.AtLeastOneValid()) {
        itemConstraint.maxSize.UpdateSizeWhenSmaller(childMaxSize.ConvertToSizeT());
    }
    if (childMinSize.AtLeastOneValid()) {
        itemConstraint.minSize.UpdateSizeWhenLarger(childMinSize.ConvertToSizeT());
    }

    // FlowItem layoutConstraint
    CHECK_NULL_RETURN(child, itemConstraint);
    auto childLayoutProperty = AceType::DynamicCast<WaterFlowItemLayoutProperty>(child->GetLayoutProperty());
    CHECK_NULL_RETURN(childLayoutProperty, itemConstraint);
    if (childLayoutProperty->HasLayoutConstraint()) {
        if (childLayoutProperty->GetMaxSize().has_value()) {
            itemConstraint.UpdateMaxSizeWithCheck(ConvertToSize(childLayoutProperty->GetMaxSize().value(),
                itemConstraint.scaleProperty, itemConstraint.percentReference));
        }
        if (childLayoutProperty->GetMinSize().has_value()) {
            itemConstraint.UpdateMinSizeWithCheck(ConvertToSize(childLayoutProperty->GetMinSize().value(),
                itemConstraint.scaleProperty, itemConstraint.percentReference));
        }
    }

    childLayoutProperty->ResetCalcMinSize();
    childLayoutProperty->ResetCalcMaxSize();

    childLayoutProperty->UpdateItemCalcMaxSize(CalcSize(CalcLength(itemConstraint.maxSize.Width(), DimensionUnit::PX),
        CalcLength(itemConstraint.maxSize.Height(), DimensionUnit::PX)));
    childLayoutProperty->UpdateItemCalcMinSize(CalcSize(CalcLength(itemConstraint.minSize.Width(), DimensionUnit::PX),
        CalcLength(itemConstraint.minSize.Height(), DimensionUnit::PX)));

    return itemConstraint;
}

LayoutConstraintF WaterFlowLayoutUtils::CreateChildConstraint(const ConstraintParams& params,
    const ViewPosReference& posRef, const RefPtr<WaterFlowLayoutProperty>& props, const RefPtr<LayoutWrapper>& child)
{
    auto itemConstraint = CreateChildConstraint(params, props, child);
    itemConstraint.viewPosRef = posRef;
    return itemConstraint;
}

std::pair<SizeF, bool> WaterFlowLayoutUtils::PreMeasureSelf(LayoutWrapper* wrapper, Axis axis)
{
    const auto& props = wrapper->GetLayoutProperty();
    auto size = CreateIdealSize(props->GetLayoutConstraint().value(), axis, props->GetMeasureType(), true);
    auto layoutPolicy = props->GetLayoutPolicyProperty();
    auto isMainWrap = false;
    if (layoutPolicy.has_value()) {
        auto isVertical = axis == Axis::VERTICAL;
        auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto isMainFix = (isVertical ? heightLayoutPolicy : widthLayoutPolicy) == LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
        isMainWrap = (isVertical ? heightLayoutPolicy : widthLayoutPolicy) == LayoutCalPolicy::WRAP_CONTENT;
        auto layoutPolicySize = ConstrainIdealSizeByLayoutPolicy(
            props->GetLayoutConstraint().value(), widthLayoutPolicy, heightLayoutPolicy, axis);
        size.UpdateIllegalSizeWithCheck(layoutPolicySize.ConvertToSizeT());
        if (isMainFix) {
            size.SetMainSize(Infinity<float>(), axis);
        }
    }
    auto matchChildren = GreaterOrEqualToInfinity(GetMainAxisSize(size, axis)) || isMainWrap;
    if (!matchChildren) {
        wrapper->GetGeometryNode()->SetFrameSize(size);
    }
    MinusPaddingToSize(props->CreatePaddingAndBorder(), size);
    wrapper->GetGeometryNode()->SetContentSize(size);
    return { size, matchChildren };
}

float WaterFlowLayoutUtils::MeasureFooter(LayoutWrapper* wrapper, Axis axis)
{
    auto footer = wrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(footer, 0.0f);
    auto layoutProperty = wrapper->GetLayoutProperty();
    auto footerConstraint = layoutProperty->CreateChildConstraint();
    footer->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    footer->Measure(footerConstraint);
    auto itemSize = footer->GetGeometryNode()->GetMarginFrameSize();
    return GetMainAxisSize(itemSize, axis);
}

float WaterFlowLayoutUtils::GetUserDefHeight(const RefPtr<WaterFlowSections>& sections, int32_t seg, int32_t idx)
{
    CHECK_NULL_RETURN(sections, -1.0f);
    const auto& section = sections->GetSectionInfo()[seg];
    if (section.onGetItemMainSizeByIndex) {
        Dimension len(section.onGetItemMainSizeByIndex(idx), DimensionUnit::VP);
        if (len.IsNegative()) {
            return 0.0f;
        }
        return len.ConvertToPx();
    }
    return -1.0f;
}

void WaterFlowLayoutUtils::UpdateItemIdealSize(const RefPtr<LayoutWrapper>& item, Axis axis, float userHeight)
{
    auto props = item->GetLayoutProperty();
    // get previously user defined ideal width
    std::optional<CalcLength> crossSize;
    const auto& layoutConstraint = props->GetCalcLayoutConstraint();
    if (layoutConstraint && layoutConstraint->selfIdealSize) {
        crossSize = axis == Axis::VERTICAL ? layoutConstraint->selfIdealSize->Width()
                                           : layoutConstraint->selfIdealSize->Height();
    }
    props->UpdateUserDefinedIdealSize(axis == Axis::VERTICAL ? CalcSize(crossSize, CalcLength(userHeight))
                                                             : CalcSize(CalcLength(userHeight), crossSize));
}

AdjustOffset WaterFlowLayoutUtils::GetAdjustOffset(const RefPtr<LayoutWrapper>& item)
{
    AdjustOffset pos {};
    RefPtr<UINode> child = AceType::DynamicCast<FrameNode>(item);
    do {
        CHECK_NULL_RETURN(child, pos);
        auto frameNode = AceType::DynamicCast<FrameNode>(child);
        if (!frameNode) {
            child = child->GetFirstChild();
            continue;
        }
        if (!frameNode->GetLayoutProperty()->GetNeedLazyLayout()) {
            return pos;
        }
        auto pattern = frameNode->GetPattern<LazyLayoutPattern>();
        if (pattern) {
            return pattern->GetAndResetAdjustOffset();
        }
        child = child->GetFirstChild();
    } while (child);
    return pos;
}
} // namespace OHOS::Ace::NG
