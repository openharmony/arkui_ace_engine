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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOX_CHECKBOX_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOX_CHECKBOX_PAINT_PROPERTY_H

#include "core/animation/curve.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class CheckBoxPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(CheckBoxPaintProperty, PaintProperty);

public:
    CheckBoxPaintProperty() = default;

    ~CheckBoxPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<CheckBoxPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->UpdatePaintPropertyHost(this);
        paintProperty->propCheckBoxSelect_ = CloneCheckBoxSelect();
        paintProperty->propCheckBoxSelectedColor_ = CloneCheckBoxSelectedColor();
        paintProperty->propCheckBoxUnSelectedColor_ = CloneCheckBoxUnSelectedColor();
        paintProperty->propCheckBoxCheckMarkColor_ = CloneCheckBoxCheckMarkColor();
        paintProperty->propCheckBoxCheckMarkSize_ = CloneCheckBoxCheckMarkSize();
        paintProperty->propCheckBoxCheckMarkWidth_ = CloneCheckBoxCheckMarkWidth();
        paintProperty->propCheckBoxSelectedStyle_ = CloneCheckBoxSelectedStyle();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetCheckBoxSelect();
        ResetCheckBoxSelectedColor();
        ResetCheckBoxUnSelectedColor();
        ResetCheckBoxCheckMarkColor();
        ResetCheckBoxSelectedColorFlagByUser();
        ResetCheckBoxUnSelectedColorFlagByUser();
        ResetCheckBoxCheckMarkColorFlagByUser();
        ResetCheckBoxCheckMarkSize();
        ResetCheckBoxCheckMarkWidth();
        ResetCheckBoxSelectedStyle();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxSelect, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxSelectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxUnSelectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxCheckMarkColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxSelectedColorFlagByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxUnSelectedColorFlagByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxCheckMarkColorFlagByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxCheckMarkSize, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxCheckMarkWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxSelectedStyle, CheckBoxStyle, PROPERTY_UPDATE_RENDER);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOX_CHECKBOX_PAINT_PROPERTY_H
