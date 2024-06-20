/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_LAYOUT_PROPERTY_H

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"

namespace OHOS::Ace::NG {
constexpr int32_t HINGES_OFFSET_UP = 16;
constexpr int32_t HINGES_OFFSET_DOWN = 16;
class ACE_EXPORT FolderStackLayoutProperty : public StackLayoutProperty {
    DECLARE_ACE_TYPE(FolderStackLayoutProperty, StackLayoutProperty);

public:
    FolderStackLayoutProperty() = default;

    ~FolderStackLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto layoutProperty = MakeRefPtr<FolderStackLayoutProperty>();
        layoutProperty->UpdateLayoutProperty(this);
        return layoutProperty;
    }

    void Reset() override
    {
        StackLayoutProperty::Reset();
        ResetEnableAnimation();
        ResetAutoHalfFold();
        ResetUpperItems();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto align = Alignment::CENTER;
        if (GetPositionProperty()) {
            align = GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER);
        }
        json->PutExtAttr("alignContent", align.GetAlignmentStr(TextDirection::LTR).c_str(), filter);
        if (HasUpperItems()) {
            auto itemId = GetUpperItemsValue();
            std::string str;
            str.assign("[");
            for (auto& id : itemId) {
                str.append(id);
                str.append(", ");
            }
            str = (itemId.size() > 1) ? str.substr(0, str.size() - 1).append("]") : str.append("]");
            json->PutExtAttr("upperItems", str.c_str(), filter);
            json->PutExtAttr("enableAnimation", propEnableAnimation_.value_or(true) ? "true" : "false", filter);
            json->PutExtAttr("autoHalfFold", propAutoHalfFold_.value_or(true) ? "true" : "false", filter);
        }
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableAnimation, bool, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AutoHalfFold, bool, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UpperItems, std::vector<std::string>, PROPERTY_UPDATE_MEASURE_SELF);

private:
    ACE_DISALLOW_COPY_AND_MOVE(FolderStackLayoutProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_FOLDER_STACK_LAYOUT_PROPERTY_H
