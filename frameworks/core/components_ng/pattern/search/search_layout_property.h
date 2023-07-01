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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SEARCH_SEARCH_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SEARCH_SEARCH_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/search/search_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SearchLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(SearchLayoutProperty, LayoutProperty);

public:
    SearchLayoutProperty() = default;
    ~SearchLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<SearchLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(AceType::DynamicCast<LayoutProperty>(this));
        value->propSearchButton_ = CloneSearchButton();
        value->propCancelButtonStyle_ = CloneCancelButtonStyle();
        value->propCancelButtonUDSize_ = CloneCancelButtonUDSize();
        value->propSearchIconUDSize_ = CloneSearchIconUDSize();
        value->propCaretUDWidth_ = CloneCaretUDWidth();
        value->propSearchButtonFontSize_ = CloneSearchButtonFontSize();
        value->propContextMenuHidden_ = CloneContextMenuHidden();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetSearchButton();
        ResetCancelButtonStyle();
        ResetCancelButtonUDSize();
        ResetSearchIconUDSize();
        ResetCaretUDWidth();
        ResetSearchButtonFontSize();
        ResetContextMenuHidden();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        LayoutProperty::ToJsonValue(json);
        json->Put("searchButton", GetSearchButton().value_or("")->c_str());
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SearchButton, std::optional<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CancelButtonStyle, CancelButtonStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CancelButtonUDSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SearchIconUDSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CaretUDWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SearchButtonFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ContextMenuHidden, bool, PROPERTY_UPDATE_MEASURE);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SEARCH_SEARCH_LAYOUT_PROPERTY_H
