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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_LAYOUT_PROPERTY_H

#include <string>

#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/select/select_model.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {


class ACE_EXPORT SelectLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(SelectLayoutProperty, LayoutProperty);

public:
    SelectLayoutProperty() = default;
    ~SelectLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<SelectLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propShowInSubWindow_ = CloneShowInSubWindow();
        value->propShowDefaultSelectedIcon_ = CloneShowDefaultSelectedIcon();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetShowInSubWindow();
        ResetShowDefaultSelectedIcon();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowInSubWindow, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowDefaultSelectedIcon, bool, PROPERTY_UPDATE_MEASURE);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        if (filter.IsFastFilter()) {
            return;
        }

        json->PutExtAttr("showInSubWindow", V2::ConvertBoolToString(GetShowInSubWindowValue(false)).c_str(), filter);
        json->PutExtAttr(
            "showDefaultSelectedIcon", V2::ConvertBoolToString(GetShowDefaultSelectedIconValue(false)).c_str(), filter);
    }

    ACE_DISALLOW_COPY_AND_MOVE(SelectLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_LAYOUT_PROPERTY_H
