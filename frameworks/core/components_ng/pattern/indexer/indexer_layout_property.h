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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"

namespace OHOS::Ace::NG {
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
        value->propSelected_ = CloneSelected();
        value->propColor_ = CloneColor();
        value->propSelectedColor_ = CloneSelectedColor();
        value->propPopupColor_ = ClonePopupColor();
        value->propSelectedBackgroundColor_ = CloneSelectedBackgroundColor();
        value->propPopupBackground_ = ClonePopupBackground();
        value->propUsingPopup_ = CloneUsingPopup();
        value->propSelectedFont_ = CloneSelectedFont();
        value->propPopupFont_ = ClonePopupFont();
        value->propFont_ = CloneFont();
        value->propItemSize_ = CloneItemSize();
        value->propAlignStyle_ = CloneAlignStyle();
        value->propPopupPositionX_ = ClonePopupPositionX();
        value->propPopupPositionY_ = ClonePopupPositionY();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetArrayValue();
        ResetSelected();
        ResetColor();
        ResetSelectedColor();
        ResetPopupColor();
        ResetSelectedBackgroundColor();
        ResetPopupBackground();
        ResetUsingPopup();
        ResetSelectedFont();
        ResetPopupFont();
        ResetFont();
        ResetItemSize();
        ResetAlignStyle();
        ResetPopupPositionX();
        ResetPopupPositionY();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrayValue, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Selected, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Color, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupColor, Color, PROPERTY_UPDATE_MEASURE);
    // TODO: selectedBackground和popupBackground需要放到PAINT_PROPERTY
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedBackgroundColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupBackground, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UsingPopup, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedFont, TextStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupFont, TextStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Font, TextStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AlignStyle, NG::AlignStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupPositionX, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PopupPositionY, float, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_LAYOUT_PROPERTY_H
