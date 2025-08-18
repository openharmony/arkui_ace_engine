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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOXGROUP_CHECKBOXGROUP_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOXGROUP_CHECKBOXGROUP_PAINT_PROPERTY_H

#include "core/animation/curve.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class CheckBoxGroupPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(CheckBoxGroupPaintProperty, PaintProperty);

public:
    CheckBoxGroupPaintProperty() = default;
    ~CheckBoxGroupPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<CheckBoxGroupPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->UpdatePaintPropertyHost(this);
        paintProperty->propCheckBoxGroupSelect_ = CloneCheckBoxGroupSelect();
        paintProperty->propCheckBoxGroupSelectedColor_ = CloneCheckBoxGroupSelectedColor();
        paintProperty->propCheckBoxGroupUnSelectedColor_ = CloneCheckBoxGroupUnSelectedColor();
        paintProperty->propCheckBoxGroupCheckMarkColor_ = CloneCheckBoxGroupCheckMarkColor();
        paintProperty->propCheckBoxGroupCheckMarkSize_ = CloneCheckBoxGroupCheckMarkSize();
        paintProperty->propCheckBoxGroupCheckMarkWidth_ = CloneCheckBoxGroupCheckMarkWidth();
        paintProperty->propCheckBoxGroupSelectedStyle_ = CloneCheckBoxGroupSelectedStyle();
        paintProperty->propStatus_ = propStatus_;
        paintProperty->SetHost(this->GetHost());
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetCheckBoxGroupSelect();
        ResetCheckBoxGroupSelectedColor();
        ResetCheckBoxGroupUnSelectedColor();
        ResetCheckBoxGroupCheckMarkColor();
        ResetCheckBoxGroupSelectedColorFlagByUser();
        ResetCheckBoxGroupUnSelectedColorFlagByUser();
        ResetCheckBoxGroupCheckMarkColorFlagByUser();
        ResetCheckBoxGroupCheckMarkSize();
        ResetCheckBoxGroupCheckMarkWidth();
        ResetCheckBoxGroupSelectedStyle();

        propStatus_ = SelectStatus::NONE;
    }

    enum class SelectStatus {
        ALL = 0,
        PART,
        NONE,
    };

    SelectStatus& GetSelectStatus()
    {
        return propStatus_;
    }

    void SetSelectStatus(const SelectStatus& status)
    {
        propStatus_ = status;
    }

    bool GetIsCheckBoxCallbackDealed()
    {
        return isCheckBoxCallbackDealed_;
    }

    void SetIsCheckBoxCallbackDealed(bool dealed)
    {
        isCheckBoxCallbackDealed_ = true;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxGroupSelect, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxGroupSelectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxGroupUnSelectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxGroupCheckMarkColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxGroupSelectedColorFlagByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxGroupUnSelectedColorFlagByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxGroupCheckMarkColorFlagByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxGroupCheckMarkSize, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxGroupCheckMarkWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CheckBoxGroupSelectedStyle, CheckBoxStyle, PROPERTY_UPDATE_RENDER);

private:
    SelectStatus propStatus_ = SelectStatus::NONE;
    bool isCheckBoxCallbackDealed_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOXGROUP_CHECKBOXGROUP_PAINT_PROPERTY_H
