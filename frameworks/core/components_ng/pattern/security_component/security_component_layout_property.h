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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MYCIRCLE_SECURITY_COMPONENT_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MYCIRCLE_SECURITY_COMPONENT_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/security_component/security_component_common.h"
#include "core/components_ng/property/property.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SecurityComponentLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(SecurityComponentLayoutProperty, LayoutProperty);

public:
    SecurityComponentLayoutProperty() = default;

    ~SecurityComponentLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<SecurityComponentLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propBackgroundLeftPadding_ = CloneBackgroundLeftPadding();
        value->propBackgroundRightPadding_ = CloneBackgroundRightPadding();
        value->propBackgroundTopPadding_ = CloneBackgroundTopPadding();
        value->propBackgroundBottomPadding_ = CloneBackgroundBottomPadding();
        value->propTextIconSpace_ = CloneTextIconSpace();
        value->propSecurityComponentDescription_ = CloneSecurityComponentDescription();
        value->propIconStyle_ = CloneIconStyle();
        value->propIconSize_ = CloneIconSize();
        value->propFontSize_ = CloneFontSize();
        value->propStateEffect_ = CloneStateEffect();
        value->propHoverEffect_ = CloneHoverEffect();
        value->propFontStyle_ = CloneFontStyle();
        value->propFontWeight_ = CloneFontWeight();
        value->propFontFamily_ = CloneFontFamily();
        value->propBackgroundBorderWidth_ = CloneBackgroundBorderWidth();
        value->propBackgroundBorderRadius_ = CloneBackgroundBorderRadius();
        value->propBackgroundType_ = CloneBackgroundType();
        value->propTextStyle_ = CloneTextStyle();
        value->propAlignment_ = CloneAlignment();
        value->propIsArkuiComponent_ = CloneIsArkuiComponent();
        value->propIsFontColorSet_ = CloneIsFontColorSet();
        value->propIsTextLimitExceeded_ = CloneIsTextLimitExceeded();
        value->propTextIconLayoutDirection_ = CloneTextIconLayoutDirection();
        value->propMaxFontScale_ = CloneMaxFontScale();
        value->propMinFontScale_ = CloneMinFontScale();
        value->propMaxLines_ = CloneMaxLines();
        value->propAdaptMaxFontSize_ = CloneAdaptMaxFontSize();
        value->propAdaptMinFontSize_ = CloneAdaptMinFontSize();
        value->propHeightAdaptivePolicy_ = CloneHeightAdaptivePolicy();
        value->propIsMaxLineLimitExceeded_ = CloneIsMaxLineLimitExceeded();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetBackgroundLeftPadding();
        ResetBackgroundRightPadding();
        ResetBackgroundTopPadding();
        ResetBackgroundBottomPadding();
        ResetTextIconSpace();
        ResetSecurityComponentDescription();
        ResetIconStyle();
        ResetIconSize();
        ResetFontSize();
        ResetStateEffect();
        ResetHoverEffect();
        ResetFontStyle();
        ResetFontWeight();
        ResetFontFamily();
        ResetBackgroundBorderWidth();
        ResetBackgroundBorderRadius();
        ResetBackgroundType();
        ResetTextStyle();
        ResetAlignment();
        ResetIsArkuiComponent();
        ResetIsFontColorSet();
        ResetIsTextLimitExceeded();
        ResetTextIconLayoutDirection();
        ResetMaxFontScale();
        ResetMinFontScale();
        ResetMaxLines();
        ResetAdaptMaxFontSize();
        ResetAdaptMinFontSize();
        ResetHeightAdaptivePolicy();
        ResetIsMaxLineLimitExceeded();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundLeftPadding, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundRightPadding, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundTopPadding, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundBottomPadding, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextIconSpace, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LeftSpace, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SecurityComponentDescription, int32_t, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IconStyle, int32_t, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IconSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StateEffect, bool, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HoverEffect, HoverEffectType, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundBorderWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundBorderRadius, NG::BorderRadiusProperty, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundType, int32_t, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextStyle, int32_t, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Alignment, Alignment, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsArkuiComponent, bool, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsFontColorSet, bool, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsTextLimitExceeded, bool, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextIconLayoutDirection,
        SecurityComponentLayoutDirection, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MaxFontScale, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MinFontScale, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MaxLines, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AdaptMaxFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AdaptMinFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HeightAdaptivePolicy, TextHeightAdaptivePolicy, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsMaxLineLimitExceeded, bool, PROPERTY_UPDATE_NORMAL);
    ACE_DISALLOW_COPY_AND_MOVE(SecurityComponentLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MYCIRCLE_SECURITY_COMPONENT_LAYOUT_PROPERTY_H
