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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RENDER_NODE_RENDER_NODE_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RENDER_NODE_RENDER_NODE_LAYOUT_PROPERTY_H

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RenderNodeLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(RenderNodeLayoutProperty, LayoutProperty);

public:
    RenderNodeLayoutProperty() = default;

    ~RenderNodeLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto layoutProperty = MakeRefPtr<RenderNodeLayoutProperty>();
        layoutProperty->UpdateLayoutProperty(this);
        return layoutProperty;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        auto align = Alignment::TOP_LEFT;
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        if (GetPositionProperty()) {
            align = GetPositionProperty()->GetAlignment().value_or(Alignment::TOP_LEFT);
        }
        json->PutExtAttr("alignContent", align.GetAlignmentStr(TextDirection::LTR).c_str(), filter);
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override
    {
        UpdateAlignment(Alignment::GetAlignment(TextDirection::LTR, json->GetString("alignContent")));
        LayoutProperty::FromJson(json);
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(RenderNodeLayoutProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STACK_STACK_LAYOUT_PROPERTY_H
