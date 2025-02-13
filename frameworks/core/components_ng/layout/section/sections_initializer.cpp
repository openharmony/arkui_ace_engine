/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "sections_initializer.h"

#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_utils.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
class WaterFlowSectionInitializer : public SectionInitializer {
public:
    WaterFlowSectionInitializer(const SizeF& frameSize, Axis axis, int32_t totalCnt)
        : SectionInitializer(frameSize, axis, totalCnt)
    {}
    std::vector<Section> Init(
        const RefPtr<WaterFlowSections>& sectionData, const RefPtr<WaterFlowLayoutProperty>& props);

private:
    std::vector<Section> SingleInit(const RefPtr<WaterFlowLayoutProperty>& props);
};

class ListSectionInitializer : public SectionInitializer {
public:
    ListSectionInitializer(const SizeF& frameSize, Axis axis, int32_t totalCnt)
        : SectionInitializer(frameSize, axis, totalCnt)
    {}
    std::vector<Section> Init()
    {
        Section res;
        res.lanes = std::vector<Lane>(1);
        res.lanes[0].crossLen = frameSize_.CrossSize(axis_);
        res.minItem = 0;
        res.maxItem = totalCnt_ - 1;
        return { res };
    }
};

class SwiperSectionInitializer : public SectionInitializer {
public:
    SwiperSectionInitializer(const SizeF& frameSize, Axis axis, int32_t totalCnt)
        : SectionInitializer(frameSize, axis, totalCnt)
    {}
    std::vector<Section> Init(const RefPtr<SwiperLayoutProperty>& props)
    {
        Section res;
        res.lanes = std::vector<Lane>(1);
        res.lanes[0].crossLen = frameSize_.CrossSize(axis_);
        res.minItem = 0;
        res.maxItem = totalCnt_ - 1;

        res.mainGap = SwiperUtils::GetItemSpace(props);
        return { res };
    }
};

bool SectionInitializer::Compare(const std::vector<Section>& prev, const std::vector<Section>& cur)
{
    if (prev.size() != cur.size()) {
        return false;
    }
    for (size_t i = 0; i < prev.size(); ++i) {
        if (prev[i].lanes.size() == cur[i].lanes.size() && prev[i].mainGap == cur[i].mainGap &&
            prev[i].crossGap == cur[i].crossGap && prev[i].margin == cur[i].margin &&
            prev[i].minItem == cur[i].minItem && prev[i].maxItem == cur[i].maxItem) {
            continue;
        }
        return false;
    }
    return true;
}

std::vector<Section> SectionInitializer::InitSections(
    const RefPtr<LayoutProperty>& props, const SizeF& frameSize, Axis axis, int32_t totalCnt)
{
    // factory method
    if (AceType::InstanceOf<WaterFlowLayoutProperty>(props)) {
        auto pattern = props->GetHost()->GetPattern<WaterFlowPattern>();
        CHECK_NULL_RETURN(pattern, {});
        WaterFlowSectionInitializer initializer(frameSize, axis, totalCnt);
        return initializer.Init(pattern->GetSections(), AceType::DynamicCast<WaterFlowLayoutProperty>(props));
    }
    if (AceType::InstanceOf<ListLayoutProperty>(props)) {
        ListSectionInitializer initializer(frameSize, axis, totalCnt);
        return initializer.Init();
    }
    if (AceType::InstanceOf<SwiperLayoutProperty>(props)) {
        SwiperSectionInitializer initializer(frameSize, axis, totalCnt);
        return initializer.Init(AceType::DynamicCast<SwiperLayoutProperty>(props));
    }
    return {};
}

std::vector<Section> WaterFlowSectionInitializer::Init(
    const RefPtr<WaterFlowSections>& sectionData, const RefPtr<WaterFlowLayoutProperty>& props)
{
    if (!sectionData) {
        return SingleInit(props);
    }

    const auto& sections = sectionData->GetSectionInfo();
    std::vector<Section> res(sections.size());
    int32_t itemIdx = 0;
    for (size_t i = 0; i < sections.size(); ++i) {
        res[i].lanes = std::vector<Lane>(sections[i].crossCount.value_or(1));

        res[i].minItem = itemIdx;
        itemIdx += sections[i].itemsCount;
        res[i].maxItem = itemIdx - 1;

        if (sections[i].rowsGap) {
            res[i].mainGap = sections[i].rowsGap->ConvertToPx();
        }
        if (sections[i].columnsGap) {
            res[i].crossGap = sections[i].columnsGap->ConvertToPx();
        }
        if (sections[i].margin) {
            const auto& constraint = props->GetLayoutConstraint().value_or(LayoutConstraintF {});
            res[i].margin = ConvertToMarginPropertyF(
                *sections[i].margin, constraint.scaleProperty, constraint.percentReference.Width());
        }
        res[i].userDefMainLen = sections[i].onGetItemMainSizeByIndex;
    }
    return res;
}

std::vector<Section> WaterFlowSectionInitializer::SingleInit(const RefPtr<WaterFlowLayoutProperty>& props)
{
    Section res;
    auto scale = props->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(props->GetRowsGap().value_or(0.0_vp), scale, frameSize_.Height()).value_or(0);
    auto columnsGap = ConvertToPx(props->GetColumnsGap().value_or(0.0_vp), scale, frameSize_.Width()).value_or(0);
    res.mainGap = { axis_ == Axis::HORIZONTAL ? columnsGap : rowsGap };
    res.crossGap = { axis_ == Axis::VERTICAL ? columnsGap : rowsGap };

    float crossSize = frameSize_.CrossSize(axis_);
    const auto args = axis_ == Axis::VERTICAL ? props->GetColumnsTemplate().value_or("1fr")
                                              : props->GetRowsTemplate().value_or("1fr");
    auto cross = ParseTemplateArgs(WaterFlowLayoutUtils::PreParseArgs(args), crossSize, res.crossGap, totalCnt_);
    res.crossGap = static_cast<float>(cross.second);
    if (cross.first.empty()) {
        cross.first = { crossSize };
    }
    res.lanes = std::vector<Lane>(cross.first.size());
    for (size_t i = 0; i < cross.first.size(); ++i) {
        res.lanes[i].crossLen = static_cast<float>(cross.first[i]);
    }

    res.minItem = 0;
    res.maxItem = totalCnt_ - 1;
    return { res };
}
} // namespace OHOS::Ace::NG