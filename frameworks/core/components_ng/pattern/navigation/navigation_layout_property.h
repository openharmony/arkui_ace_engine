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
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/property/property.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

constexpr Dimension DEFAULT_NAV_BAR_WIDTH = 240.0_vp;

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
        copy->propUsrNavigationMode_ = CloneUsrNavigationMode();
        copy->propNavBarWidth_ = CloneNavBarWidth();
        copy->propMinNavBarWidth_ = CloneMinNavBarWidth();
        copy->propMaxNavBarWidth_ = CloneMaxNavBarWidth();
        copy->propMinContentWidth_ = CloneMinContentWidth();
        copy->propNavBarPosition_ = CloneNavBarPosition();
        copy->propEnableModeChangeAnimation_ = CloneEnableModeChangeAnimation();
        copy->propHideNavBar_ = CloneHideNavBar();
        copy->propNoPixMap_ = CloneNoPixMap();
        copy->propImageSource_ = CloneImageSource();
        copy->propPixelMap_ = ClonePixelMap();
        return copy;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetNavigationMode();
        ResetUsrNavigationMode();
        ResetNavBarWidth();
        ResetMinNavBarWidth();
        ResetMaxNavBarWidth();
        ResetMinContentWidth();
        ResetNavBarPosition();
        ResetEnableModeChangeAnimation();
        ResetHideNavBar();
        ResetNoPixMap();
        ResetImageSource();
        ResetPixelMap();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        std::string navBarWidthRange = GetMinNavBarWidthValue(DEFAULT_MIN_NAV_BAR_WIDTH).ToString() + ", " +
                                       GetMaxNavBarWidthValue(DEFAULT_MAX_NAV_BAR_WIDTH).ToString();
        json->PutExtAttr("navBarWidth", GetNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH).ToString().c_str(), filter);
        json->PutExtAttr("navBarWidthRange", navBarWidthRange.c_str(), filter);
        json->PutExtAttr("minContentWidth",
            GetMinContentWidthValue(DEFAULT_MIN_CONTENT_WIDTH).ToString().c_str(), filter);
        json->PutExtAttr("navBarPosition", GetNavBarPosition().value_or(NavBarPosition::START) == NavBarPosition::START
                                        ? "NavBarPosition.Start"
                                        : "NavBarPosition.End", filter);
        static const std::array<std::string, 3> NAVIGATION_MODE_TO_STRING = {
            "NavigationMode.STACK",
            "NavigationMode.SPLIT",
            "NavigationMode.AUTO",
        };
        json->PutExtAttr("mode",
            NAVIGATION_MODE_TO_STRING.at(static_cast<int32_t>(GetUsrNavigationMode().value_or(NavigationMode::AUTO)))
                .c_str(), filter);
        json->PutExtAttr("hideNavBar", GetHideNavBarValue(false), filter);
        if (HasImageSource()) {
            json->PutExtAttr("backButtonIcon", GetImageSourceValue().GetSrc().c_str(), filter);
        }
        json->PutExtAttr("enableModeChangeAnimation", GetEnableModeChangeAnimation().value_or(true), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NavigationMode, NavigationMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UsrNavigationMode, NavigationMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NavBarWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MinNavBarWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MaxNavBarWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MinContentWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NavBarPosition, NavBarPosition, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableModeChangeAnimation, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HideNavBar, bool, PROPERTY_UPDATE_MEASURE);
    // back button icon
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NoPixMap, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ImageSource, ImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PixelMap, RefPtr<PixelMap>, PROPERTY_UPDATE_MEASURE);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVIGATION_LAYOUT_PROPERTY_H
