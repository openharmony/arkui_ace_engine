/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LazyWaterFlowLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(LazyWaterFlowLayoutProperty, LayoutProperty);

public:
    LazyWaterFlowLayoutProperty() = default;
    ~LazyWaterFlowLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = AceType::MakeRefPtr<LazyWaterFlowLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(AceType::DynamicCast<LayoutProperty>(this));
        value->propRowGap_ = CloneRowGap();
        value->propColumnGap_ = CloneColumnGap();
        value->propColumnsTemplate_ = CloneColumnsTemplate();
        value->propItemFillPolicy_ = CloneItemFillPolicy();
        value->propStickyStyle_ = CloneStickyStyle();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetRowGap();
        ResetColumnGap();
        ResetColumnsTemplate();
        ResetItemFillPolicy();
        ResetStickyStyle();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("rowsGap", propRowGap_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr(
            "columnsGap", propColumnGap_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("columnsTemplate", propColumnsTemplate_.value_or("").c_str(), filter);
        if (propItemFillPolicy_.has_value()) {
            json->PutExtAttr("itemFillPolicy", GetItemFillPolicyString().c_str(), filter);
        }
        auto sticky = propStickyStyle_.value_or(StickyStyle::NONE);
        if (sticky == StickyStyle::HEADER) {
            json->PutExtAttr("sticky", "StickyStyle.Header", filter);
        } else if (sticky == StickyStyle::FOOTER) {
            json->PutExtAttr("sticky", "StickyStyle.Footer", filter);
        } else if (sticky == StickyStyle::BOTH) {
            json->PutExtAttr("sticky", "StickyStyle.Header | StickyStyle.Footer", filter);
        } else {
            json->PutExtAttr("sticky", "StickyStyle.None", filter);
        }
    }

    std::string GetItemFillPolicyString() const
    {
        switch (propItemFillPolicy_.value_or(PresetFillType::BREAKPOINT_DEFAULT)) {
            case PresetFillType::BREAKPOINT_SM1MD2LG3:
                return "PresetFillType.BREAKPOINT_SM1MD2LG3";
            case PresetFillType::BREAKPOINT_SM2MD3LG5:
                return "PresetFillType.BREAKPOINT_SM2MD3LG5";
            case PresetFillType::BREAKPOINT_DEFAULT:
            default:
                return "PresetFillType.BREAKPOINT_DEFAULT";
        }
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RowGap, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ColumnGap, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ColumnsTemplate, std::string, PROPERTY_UPDATE_MEASURE);
    // Higher priority than ColumnsTemplate.
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemFillPolicy, PresetFillType, PROPERTY_UPDATE_MEASURE);
    // Sticky behavior for header / footer: NONE / HEADER / FOOTER / BOTH.
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StickyStyle, StickyStyle, PROPERTY_UPDATE_MEASURE);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_PROPERTY_H
