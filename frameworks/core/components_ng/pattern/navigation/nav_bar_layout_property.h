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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAV_BAR_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAV_BAR_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/navigation/navdestination_layout_property_base.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NavBarLayoutProperty : public NavDestinationLayoutPropertyBase {
    DECLARE_ACE_TYPE(NavBarLayoutProperty, NavDestinationLayoutPropertyBase);

public:
    NavBarLayoutProperty() = default;

    ~NavBarLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto copy = MakeRefPtr<NavBarLayoutProperty>();
        copy->NavDestinationLayoutPropertyBase::UpdateBaseLayoutProperty(
            DynamicCast<NavDestinationLayoutPropertyBase>(this));
        copy->propTitleMode_ = CloneTitleMode();
        copy->propHideBackButton_ = CloneHideBackButton();
        return copy;
    }

    void Reset() override
    {
        NavDestinationLayoutPropertyBase::Reset();
        ResetTitleMode();
        ResetHideBackButton();
    }

    std::string GetTitleModeString() const
    {
        switch (GetTitleModeValue(NavigationTitleMode::FREE)) {
            case NavigationTitleMode::FREE:
                return "NavigationTitleMode.Free";
            case NavigationTitleMode::FULL:
                return "NavigationTitleMode.Full";
            case NavigationTitleMode::MINI:
                return "NavigationTitleMode.Mini";
            default:
                return "NavigationTitleMode.Free";
        }
    }
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TitleMode, NavigationTitleMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HideBackButton, bool, PROPERTY_UPDATE_MEASURE);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAV_BAR_LAYOUT_PROPERTY_H
