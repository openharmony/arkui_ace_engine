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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT IndexerLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(IndexerLayoutProperty, LayoutProperty);

public:
    IndexerLayoutProperty() = default;

    ~IndexerLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<IndexerLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propArrayValue_ = CloneArrayValue();
        value->propActualArrayValue_ = CloneActualArrayValue();
        value->propSelected_ = CloneSelected();
        value->propColor_ = CloneColor();
        value->propSelectedColor_ = CloneSelectedColor();
        value->propPopupColor_ = ClonePopupColor();
        value->propUsingPopup_ = CloneUsingPopup();
        value->propSelectedFont_ = CloneSelectedFont();
        value->propPopupFont_ = ClonePopupFont();
        value->propFont_ = CloneFont();
        value->propItemSize_ = CloneItemSize();
        value->propAlignStyle_ = CloneAlignStyle();
        value->propPopupPositionX_ = ClonePopupPositionX();
        value->propPopupPositionY_ = ClonePopupPositionY();
        value->propFontSize_ = CloneFontSize();
        value->propFontWeight_ = CloneFontWeight();
        value->propAutoCollapse_ = CloneAutoCollapse();
        value->propPopupHorizontalSpace_ = ClonePopupHorizontalSpace();
        value->propIsPopup_ = CloneIsPopup();
        value->propAdaptiveWidth_ = CloneAdaptiveWidth();
        value->propEnableHapticFeedback_ = CloneEnableHapticFeedback();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetArrayValue();
        ResetActualArrayValue();
        ResetSelected();
        ResetColor();
        ResetSelectedColor();
        ResetPopupColor();
        ResetUsingPopup();
        ResetSelectedFont();
        ResetPopupFont();
        ResetFont();
        ResetItemSize();
        ResetAlignStyle();
        ResetPopupPositionX();
        ResetPopupPositionY();
        ResetFontSize();
        ResetFontWeight();
        ResetAutoCollapse();
        ResetPopupHorizontalSpace();
        ResetIsPopup();
        ResetAdaptiveWidth();
        ResetEnableHapticFeedback();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrayValue, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ActualArrayValue, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Selected, int32_t, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Color, Color, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedColor, Color, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupColor, Color, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UsingPopup, bool, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedFont, TextStyle, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupFont, TextStyle, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Font, TextStyle, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AlignStyle, NG::AlignStyle, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupPositionX, Dimension, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupPositionY, Dimension, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontSize, Dimension, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontWeight, FontWeight, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AutoCollapse, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupHorizontalSpace, Dimension, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsPopup, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AdaptiveWidth, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableHapticFeedback, bool, PROPERTY_UPDATE_MEASURE);

private:
    static std::unique_ptr<JsonValue> ToJsonObjectValue(const TextStyle& textStyle);
    static std::string AlignStyleToString(const AlignStyle& alignStyle);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_LAYOUT_PROPERTY_H
