/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_DIVIDER_MENU_DIVIDER_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_DIVIDER_MENU_DIVIDER_PAINT_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_ng/pattern/select/select_properties.h"

namespace OHOS::Ace::NG {
// PaintProperty are used to set render properties.
class MenuDividerPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(MenuDividerPaintProperty, PaintProperty);
public:
    MenuDividerPaintProperty() = default;
    ~MenuDividerPaintProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<MenuDividerPaintProperty>();
        paintProperty->propStrokeWidth_ = CloneStrokeWidth();
        paintProperty->propDividerColor_ = CloneDividerColor();
        paintProperty->propStartMargin_ = CloneStartMargin();
        paintProperty->propEndMargin_ = CloneEndMargin();
        paintProperty->propNeedDivider_ = CloneNeedDivider();
        paintProperty->propTopHover_ = CloneTopHover();
        paintProperty->propTopPress_ = CloneTopPress();
        paintProperty->propTopSelected_ = CloneTopSelected();
        paintProperty->propBottomHover_ = CloneBottomHover();
        paintProperty->propBottomPress_ = CloneBottomPress();
        paintProperty->propBottomSelected_ = CloneBottomSelected();
        paintProperty->propHasIcon_ = CloneHasIcon();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetStrokeWidth();
        ResetDividerColor();
        ResetStartMargin();
        ResetEndMargin();
        ResetNeedDivider();
        ResetTopHover();
        ResetTopPress();
        ResetTopSelected();
        ResetBottomHover();
        ResetBottomPress();
        ResetBottomSelected();
        ResetHasIcon();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DividerColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartMargin, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndMargin, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NeedDivider, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TopHover, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TopPress, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TopSelected, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BottomHover, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BottomPress, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BottomSelected, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HasIcon, bool, PROPERTY_UPDATE_RENDER);
    ACE_DISALLOW_COPY_AND_MOVE(MenuDividerPaintProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_DIVIDER_MENU_DIVIDER_RENDER_PROPERTY_H
