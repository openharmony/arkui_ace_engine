/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVDESTINATION_LAYOUT_PROPERTY_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVDESTINATION_LAYOUT_PROPERTY_BASE_H

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NavDestinationLayoutPropertyBase : public LayoutProperty {
    DECLARE_ACE_TYPE(NavDestinationLayoutPropertyBase, LayoutProperty);

public:
    NavDestinationLayoutPropertyBase() = default;
    ~NavDestinationLayoutPropertyBase() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto copy = MakeRefPtr<NavDestinationLayoutPropertyBase>();
        copy->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        copy->propHideTitleBar_ = CloneHideTitleBar();
        copy->propHideToolBar_ = CloneHideToolBar();
        return copy;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetHideTitleBar();
        ResetHideToolBar();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HideTitleBar, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HideToolBar, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IgnoreLayoutSafeArea, SafeAreaExpandOpts, PROPERTY_UPDATE_MEASURE);

protected:
    void UpdateBaseLayoutProperty(const NavDestinationLayoutPropertyBase* layoutProperty)
    {
        LayoutProperty::UpdateLayoutProperty(layoutProperty);
        propHideTitleBar_ = CloneHideTitleBar();
        propHideToolBar_ = CloneHideToolBar();
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVDESTINATION_LAYOUT_PROPERTY_BASE_H
