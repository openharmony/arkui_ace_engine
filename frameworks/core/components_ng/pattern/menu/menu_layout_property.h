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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_PROPERTY_H

#include <string>
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MenuLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(MenuLayoutProperty, LayoutProperty);

public:
    MenuLayoutProperty() = default;

    ~MenuLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<MenuLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propTargetId_ = CloneTargetId();
        value->propTargetTag_ = CloneTargetTag();

        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetTargetId();
        ResetTargetTag();
    }

    // target frameNode that this menu belongs to
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TargetId, int32_t, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TargetTag, std::string, PROPERTY_UPDATE_LAYOUT);

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        LayoutProperty::ToJsonValue(json);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto options = host->GetChildren();
        auto jsonDashArray = JsonUtil::CreateArray(true);
        int index = 0;
        // output format
        // {
        //     "bindMenu" : [
        //         <index> : <value>,
        //         ...
        //     ]
        // }
        for (auto && option : options) {
            auto pattern = DynamicCast<FrameNode>(option)->GetPattern<OptionPattern>();
            CHECK_NULL_VOID(pattern);
            auto jsonValue = JsonUtil::Create(true);

            jsonValue->Put("value", pattern->GetText().c_str());
            jsonDashArray->Put(std::to_string(index++).c_str(), jsonValue);
        }
        json->Put("bindMenu", jsonDashArray);
    }

    ACE_DISALLOW_COPY_AND_MOVE(MenuLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_PROPERTY_H
