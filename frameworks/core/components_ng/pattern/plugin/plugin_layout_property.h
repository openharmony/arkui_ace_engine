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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_LAYOUT_PROPERTY_H

#include "base/utils/macros.h"
#include "core/components/plugin/resource/plugin_request_data.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT PluginLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(PluginLayoutProperty, LayoutProperty);

public:
    PluginLayoutProperty() = default;

    ~PluginLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<PluginLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<PluginLayoutProperty>(this));
        value->propRequestPluginInfo_ = CloneRequestPluginInfo();
        value->propData_ = CloneData();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetRequestPluginInfo();
        ResetData();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RequestPluginInfo, RequestPluginInfo, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Data, std::string, PROPERTY_UPDATE_MEASURE);

    ACE_DISALLOW_COPY_AND_MOVE(PluginLayoutProperty);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PLUGIN_PLUGIN_LAYOUT_PROPERTY_H
