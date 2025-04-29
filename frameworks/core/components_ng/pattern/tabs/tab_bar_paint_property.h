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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_BAR_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_BAR_PAINT_PROPERTY_H

#include "base/geometry/ng/rect_t.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

class TabBarPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(TabBarPaintProperty, PaintProperty)

public:
    TabBarPaintProperty() = default;
    ~TabBarPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<TabBarPaintProperty>();
        paintProperty->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        paintProperty->propIndicator_ = CloneIndicator();
        paintProperty->propFadingEdge_ = CloneFadingEdge();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetIndicator();
        ResetFadingEdge();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        if (HasIndicator()) {
            json->PutExtAttr("indicator", GetIndicatorValue(), filter);
        }
        if (HasFadingEdge()) {
            json->PutExtAttr("fadingEdge", GetFadingEdgeValue() ? "true" : "false", filter);
        }
    }

    /* Need to render when indicator has animation */
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Indicator, int32_t, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FadingEdge, bool, PROPERTY_UPDATE_RENDER);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TAB_BAR_PAINT_PROPERTY_H
