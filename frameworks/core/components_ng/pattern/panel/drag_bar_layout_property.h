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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_DRAG_BAR_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_DRAG_BAR_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT DragBarLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(DragBarLayoutProperty, LayoutProperty);

public:
    DragBarLayoutProperty() = default;
    ~DragBarLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<DragBarLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(AceType::DynamicCast<LayoutProperty>(this));
        value->propFullScreenMode_ = CloneFullScreenMode();
        value->propHotRegionHeight_ = CloneHotRegionHeight();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetFullScreenMode();
        ResetHotRegionHeight();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FullScreenMode, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HotRegionHeight, float, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(DragBarLayoutProperty);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_DRAG_BAR_LAYOUT_PROPERTY_H
