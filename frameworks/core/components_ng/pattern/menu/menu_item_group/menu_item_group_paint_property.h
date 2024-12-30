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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_PAINT_PROPERTY_H

#include "core/components/common/properties/text_style.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MenuItemGroupPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(MenuItemGroupPaintProperty, PaintProperty)

public:
    MenuItemGroupPaintProperty() = default;
    ~MenuItemGroupPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<MenuItemGroupPaintProperty>();
        paintProperty->propNeedHeaderPadding_ = CloneNeedHeaderPadding();
        paintProperty->propNeedFooterPadding_ = CloneNeedFooterPadding();
        paintProperty->propNeedHeaderDivider_ = CloneNeedHeaderDivider();
        paintProperty->propNeedFooterDivider_ = CloneNeedFooterDivider();
        paintProperty->propStrokeWidth_ = CloneStrokeWidth();
        paintProperty->propDividerColor_ = CloneDividerColor();
        paintProperty->propStartMargin_ = CloneStartMargin();
        paintProperty->propEndMargin_ = CloneEndMargin();
        paintProperty->propDividerMode_ = CloneDividerMode();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetNeedHeaderPadding();
        ResetNeedFooterPadding();
        ResetNeedHeaderDivider();
        ResetNeedFooterDivider();
        ResetStrokeWidth();
        ResetDividerColor();
        ResetStartMargin();
        ResetEndMargin();
        ResetDividerMode();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NeedHeaderPadding, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NeedFooterPadding, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NeedHeaderDivider, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NeedFooterDivider, bool, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DividerColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartMargin, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndMargin, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DividerMode, DividerMode, PROPERTY_UPDATE_MEASURE);

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemGroupPaintProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_PAINT_PROPERTY_H
