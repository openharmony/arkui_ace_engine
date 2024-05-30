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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ABILITY_COMPONENT_RENDER_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ABILITY_COMPONENT_RENDER_PROPERTY_H

#include "frameworks/core/components/common/layout/constants.h"
#include "frameworks/core/components_ng/base/inspector_filter.h"
#include "frameworks/core/components_ng/layout/layout_property.h"
#include "frameworks/core/components_ng/property/property.h"
#include "frameworks/core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

// PaintProperty are used to set render properties.
class AbilityComponentRenderProperty : public PaintProperty {
    DECLARE_ACE_TYPE(AbilityComponentRenderProperty, PaintProperty)

public:
    AbilityComponentRenderProperty() = default;
    ~AbilityComponentRenderProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<AbilityComponentRenderProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propWant_ = CloneWant();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetWant();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("want", propWant_->c_str(), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Want, std::string, PROPERTY_UPDATE_RENDER);

private:
    ACE_DISALLOW_COPY_AND_MOVE(AbilityComponentRenderProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ABILITY_COMPONENT_RENDER_PROPERTY_H
