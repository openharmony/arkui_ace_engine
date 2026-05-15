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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_PROPERTY_H

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT LazyColumnLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(LazyColumnLayoutProperty, LayoutProperty);

public:
    LazyColumnLayoutProperty() = default;

    ~LazyColumnLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<LazyColumnLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propSpace_ = CloneSpace();
        value->propHorizontalAlign_ = CloneHorizontalAlign();
        value->propStickyStyle_ = CloneStickyStyle();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetSpace();
        ResetHorizontalAlign();
        ResetStickyStyle();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("space", propSpace_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("alignItems",
            propHorizontalAlign_.value_or(HorizontalAlign::CENTER) == HorizontalAlign::START ? "HorizontalAlign.Start"
            : (propHorizontalAlign_.value_or(HorizontalAlign::CENTER) == HorizontalAlign::CENTER
                ? "HorizontalAlign.Center"
                : "HorizontalAlign.End"),
            filter);
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

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Space, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HorizontalAlign, HorizontalAlign, PROPERTY_UPDATE_MEASURE);
    // Sticky behavior for header / footer: NONE / HEADER / FOOTER / BOTH.
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StickyStyle, StickyStyle, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_PROPERTY_H
