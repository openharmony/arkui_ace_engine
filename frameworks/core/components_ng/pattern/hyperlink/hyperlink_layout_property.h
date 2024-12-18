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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HYPERLINK_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HYPERLINK_LAYOUT_PROPERTY_H

#include <string>

#include "base/utils/utf_helper.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT HyperlinkLayoutProperty : public TextLayoutProperty {
    DECLARE_ACE_TYPE(HyperlinkLayoutProperty, TextLayoutProperty);

public:
    HyperlinkLayoutProperty() = default;

    ~HyperlinkLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<HyperlinkLayoutProperty>();
        TextLayoutProperty::Clone(value);
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propColor_ = CloneColor();
        value->propContent_ = CloneContent();
        return value;
    }

    void Reset() override
    {
        TextLayoutProperty::Reset();
        ResetColor();
        ResetContent();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        json->PutFixedAttr("content", UtfUtils::Str16ToStr8(propContent_.value_or(u"")).c_str(), filter,
            FIXED_ATTR_CONTENT);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("color", propColor_.value_or(Color::BLUE).ColorToString().c_str(), filter);
        json->PutExtAttr("address", propAddress_.value_or("").c_str(), filter);
    }

    void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const override
    {
        LayoutProperty::ToTreeJson(json, config);
        json->Put(TreeKey::CONTENT, UtfUtils::Str16ToStr8(propContent_.value_or(u"")).c_str());
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Color, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Address, std::string, PROPERTY_UPDATE_NORMAL);

private:
    ACE_DISALLOW_COPY_AND_MOVE(HyperlinkLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_HYPERLINK_LAYOUT_PROPERTY_H
