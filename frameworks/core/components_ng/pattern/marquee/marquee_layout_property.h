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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MARQUEE_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MARQUEE_LAYOUT_PROPERTY_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/utf_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MarqueeLayoutProperty final : public LayoutProperty {
    DECLARE_ACE_TYPE(MarqueeLayoutProperty, LayoutProperty);

public:
    MarqueeLayoutProperty() = default;

    ~MarqueeLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<MarqueeLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propPlayerStatus_ = ClonePlayerStatus();
        value->propScrollAmount_ = CloneScrollAmount();
        value->propDirection_ = CloneDirection();
        value->propLoop_ = CloneLoop();
        value->propAllowScale_ = CloneAllowScale();
        value->propSrc_ = CloneSrc();
        value->propFontSize_ = CloneFontSize();
        value->propFontWeight_ = CloneFontWeight();
        value->propFontColor_ = CloneFontColor();
        value->propFontFamily_ = CloneFontFamily();
        value->propMarqueeUpdateStrategy_ = CloneMarqueeUpdateStrategy();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetPlayerStatus();
        ResetScrollAmount();
        ResetDirection();
        ResetLoop();
        ResetAllowScale();
        ResetSrc();
        ResetFontSize();
        ResetFontWeight();
        ResetFontColor();
        ResetFontFamily();
        ResetMarqueeUpdateStrategy();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto textChild = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
        CHECK_NULL_VOID(textChild);
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        json->PutFixedAttr("src", UtfUtils::Str16ToStr8(textLayoutProperty->GetContent().value_or(u"")).c_str(), filter,
            FIXED_ATTR_SRC);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("allowScale", propAllowScale_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("fontSize", propFontSize_.value_or(10.0_vp).ToString().c_str(), filter);
        json->PutExtAttr("fontColor", propFontColor_.value_or(textLayoutProperty->GetTextColor().
            value_or(Color::BLACK)).ColorToString().c_str(), filter);
        json->PutExtAttr("fontWeight",
            V2::ConvertWrapFontWeightToStirng(propFontWeight_.value_or(FontWeight::NORMAL)).c_str(), filter);
        std::vector<std::string> fontFamilyVector =
            propFontFamily_.value_or<std::vector<std::string>>({ "HarmonyOS Sans" });
        if (fontFamilyVector.empty()) {
            fontFamilyVector = std::vector<std::string>({ "HarmonyOS Sans" });
        }
        std::string fontFamily = fontFamilyVector.at(0);
        for (uint32_t i = 1; i < fontFamilyVector.size(); ++i) {
            fontFamily += ',' + fontFamilyVector.at(i);
        }
        json->PutExtAttr("fontFamily", fontFamily.c_str(), filter);
        json->PutExtAttr("marqueeUpdateStrategy", V2::ConvertWrapMarqueeUpdateStrategyToStirng(
            propMarqueeUpdateStrategy_.value_or(MarqueeUpdateStrategy::DEFAULT)).c_str(), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PlayerStatus, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollAmount, double, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Loop, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Direction, MarqueeDirection, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AllowScale, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Src, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MarqueeUpdateStrategy, MarqueeUpdateStrategy, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(MarqueeLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MARQUEE_LAYOUT_PROPERTY_H
