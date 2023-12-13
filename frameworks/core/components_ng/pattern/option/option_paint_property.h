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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_OPTION_OPTION_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_OPTION_OPTION_PAINT_PROPERTY_H

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

// PaintProperty are used to set paint properties.
class ACE_EXPORT OptionPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(OptionPaintProperty, PaintProperty)

public:
    OptionPaintProperty() = default;
    ~OptionPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<OptionPaintProperty>();
        paintProperty->propHover_ = CloneHover();
        paintProperty->propPress_ = ClonePress();
        paintProperty->propNeedDivider_ = CloneNeedDivider();
        paintProperty->propHasIcon_ = CloneHasIcon();

        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetHover();
        ResetPress();
        ResetNeedDivider();
        ResetHasIcon();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Hover, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Press, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NeedDivider, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HasIcon, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectModifiedWidth, float, PROPERTY_UPDATE_MEASURE);

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        PaintProperty::ToJsonValue(json);
        json->Put("hover", propHover_.value_or(false) ? "true" : "false");
        json->Put("needDivider", propNeedDivider_.value_or(true) ? "true" : "false");
        json->Put("hasIcon", propHasIcon_.value_or(false) ? "true" : "false");
    }

    ACE_DISALLOW_COPY_AND_MOVE(OptionPaintProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_OPTION_OPTION_PAINT_PROPERTY_H
