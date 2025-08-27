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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_CONTENT_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_CONTENT_LAYOUT_PROPERTY_H

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TabContentLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(TabContentLayoutProperty, LayoutProperty);

public:
    TabContentLayoutProperty() = default;
    ~TabContentLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<TabContentLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(AceType::DynamicCast<LayoutProperty>(this));
        value->propIcon_ = CloneIcon();
        value->propText_ = CloneText();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetIcon();
        ResetText();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("icon", propIcon_.value_or("").c_str(), filter);
        json->PutExtAttr("text", propText_.value_or("").c_str(), filter);

        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("icon", propIcon_.value_or("").c_str());
        jsonValue->Put("text", propText_.value_or("").c_str());
        json->PutExtAttr("tabBar", jsonValue->ToString().c_str(), filter);
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override
    {
        UpdateIcon(json->GetString("icon"));
        UpdateText(json->GetString("text"));
        LayoutProperty::FromJson(json);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Icon, std::string, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Text, std::string, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorColorSetByUser, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LabelUnselectedColorSetByUser, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LabelSelectedColorSetByUser, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IconUnselectedColorSetByUser, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IconSelectedColorSetByUser, bool, PROPERTY_UPDATE_LAYOUT);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_CONTENT_LAYOUT_PROPERTY_H
