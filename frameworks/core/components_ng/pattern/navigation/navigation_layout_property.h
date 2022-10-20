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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVIGATION_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVIGATION_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/property/property.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NavigationLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(NavigationLayoutProperty, LayoutProperty);

public:
    NavigationLayoutProperty() = default;

    ~NavigationLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto copy = MakeRefPtr<NavigationLayoutProperty>();
        copy->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        copy->propNavigationMode_ = CloneNavigationMode();
        copy->propNavBarWidth_ = CloneNavBarWidth();
        copy->propNavBarPosition_ = CloneNavBarPosition();
        copy->propHideNavBar_ = CloneHideNavBar();
        copy->propTitleBarHeight_ = CloneTitleBarHeight();
        copy->propNoPixMap_ = CloneNoPixMap();
        copy->propImageSource_ = CloneImageSource();
        copy->propPixelMap_ = ClonePixelMap();
        return copy;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetNavigationMode();
        ResetNavBarWidth();
        ResetNavBarPosition();
        ResetHideNavBar();
        ResetTitleBarHeight();
        ResetNoPixMap();
        ResetImageSource();
        ResetPixelMap();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NavigationMode, NavigationMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NavBarWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NavBarPosition, NavBarPosition, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HideNavBar, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TitleBarHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    // back button icon
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NoPixMap, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ImageSource, ImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PixelMap, RefPtr<PixelMap>, PROPERTY_UPDATE_MEASURE);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVIGATION_LAYOUT_PROPERTY_H
