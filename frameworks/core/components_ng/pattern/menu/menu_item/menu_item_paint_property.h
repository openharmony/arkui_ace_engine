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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MENU_ITEM_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MENU_ITEM_PAINT_PROPERTY_H

#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/select/select_properties.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MenuItemPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(MenuItemPaintProperty, PaintProperty)

public:
    MenuItemPaintProperty(bool isOption = false) : isOption_(isOption) {}
    ~MenuItemPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<MenuItemPaintProperty>(isOption_);
        if (isOption_) {
            paintProperty->propHasIcon_ = CloneHasIcon();
            paintProperty->propDivider_ = CloneDivider();
        } else {
            paintProperty->propStrokeWidth_ = CloneStrokeWidth();
            paintProperty->propDividerColor_ = CloneDividerColor();
            paintProperty->propStartMargin_ = CloneStartMargin();
            paintProperty->propEndMargin_ = CloneEndMargin();
        }
        paintProperty->propNeedDivider_ = CloneNeedDivider();
        paintProperty->propHover_ = CloneHover();
        paintProperty->propPress_ = ClonePress();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        if (isOption_) {
            ResetHasIcon();
            ResetDivider();
        } else {
            ResetStrokeWidth();
            ResetDividerColor();
            ResetStartMargin();
            ResetEndMargin();
        }
        ResetNeedDivider();
        ResetHover();
        ResetPress();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DividerColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartMargin, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndMargin, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NeedDivider, bool, isOption_ ? PROPERTY_UPDATE_RENDER :
                                                                          PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Hover, bool, isOption_ ? PROPERTY_UPDATE_RENDER : PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Press, bool, isOption_ ? PROPERTY_UPDATE_RENDER : PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HasIcon, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectModifiedWidth, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Divider, SelectDivider, PROPERTY_UPDATE_RENDER);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("hover", propHover_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("needDivider", propNeedDivider_.value_or(true) ? "true" : "false", filter);
        json->PutExtAttr("hasIcon", propHasIcon_.value_or(false) ? "true" : "false", filter);
    }

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemPaintProperty);

    void SetIdealWidthForWeb(int32_t width)
    {
        idealWidth_ = width;
    }

    float GetIdealWidthForWeb() const
    {
        return idealWidth_;
    }

private:
    bool isOption_ = false;
    float idealWidth_ = -1;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_MENU_ITEM_PAINT_PROPERTY_H
