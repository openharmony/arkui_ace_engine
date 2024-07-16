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
#include "core/components_ng/base/inspector_filter.h"
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
        value->propFontFeature_ = CloneFontFeature();
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
        ResetFontFeature();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("searchButton", GetSearchButton().value_or("")->c_str(), filter);
    }

    const std::function<void(WeakPtr<NG::FrameNode>)>& GetSearchIconSymbol() const
    {
        return searchIconSymbol_;
    }

    void SetSearchIconSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& searchIconSymbol)
    {
        searchIconSymbol_ = searchIconSymbol;
    }

    const std::function<void(WeakPtr<NG::FrameNode>)>& GetCancelIconSymbol() const
    {
        return cancelIconSymbol_;
    }

    void SetCancelIconSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& cancelIconSymbol)
    {
        cancelIconSymbol_ = cancelIconSymbol;
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SearchButton, std::optional<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CancelButtonStyle, CancelButtonStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CancelButtonUDSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SearchIconUDSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CaretUDWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SearchButtonFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontFeature, FONT_FEATURES_LIST, PROPERTY_UPDATE_MEASURE);

private:
    std::function<void(WeakPtr<NG::FrameNode>)> searchIconSymbol_;
    std::function<void(WeakPtr<NG::FrameNode>)> cancelIconSymbol_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SEARCH_SEARCH_LAYOUT_PROPERTY_H
