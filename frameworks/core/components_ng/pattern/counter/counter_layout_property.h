/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COUNTER_COUNTER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COUNTER_COUNTER_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components/counter/counter_theme.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CounterLayoutProperty : public LinearLayoutProperty {
    DECLARE_ACE_TYPE(CounterLayoutProperty, LinearLayoutProperty);

public:
    CounterLayoutProperty() : LinearLayoutProperty(false) {};

    ~CounterLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<CounterLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        return value;
    }

    void Reset() override
    {
        LinearLayoutProperty::Reset();
    }

    ACE_DISALLOW_COPY_AND_MOVE(CounterLayoutProperty);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto context = PipelineBase::GetCurrentContext();
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto counterRenderContext = host->GetRenderContext();
        CHECK_NULL_VOID(counterRenderContext);
        auto theme = context ? context->GetTheme<CounterTheme>(host->GetThemeScopeId()) : nullptr;
        auto defaultForegroundColor = theme ? theme->GetContentTextStyle().GetTextColor() : Color::BLACK;
        Color textColor = counterRenderContext->GetForegroundColor().has_value()
                              ? counterRenderContext->GetForegroundColorValue()
                              : defaultForegroundColor;
        json->PutExtAttr("foregroundColor", textColor.ToString().c_str(), filter);
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COUNTER_COUNTER_LAYOUT_PROPERTY_H
