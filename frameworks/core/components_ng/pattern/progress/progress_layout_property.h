/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/common/container.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ProgressLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ProgressLayoutProperty, LayoutProperty);

public:
    ProgressLayoutProperty() = default;

    ~ProgressLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ProgressLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propType_ = CloneType();
        value->propStrokeWidth_ = CloneStrokeWidth();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetType();
        ResetStrokeWidth();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto progressTheme = pipeline->GetTheme<ProgressTheme>(GetThemeScopeId());
        CHECK_NULL_VOID(progressTheme);

        json->PutExtAttr("type",
            (ProgressTypeUtils::ConvertProgressTypeToString(propType_.value_or(ProgressType::LINEAR))).c_str(), filter);
        json->PutExtAttr("strokeWidth",
            propStrokeWidth_.value_or(progressTheme->GetTrackThickness()).ToString().c_str(), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Type, ProgressType, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_MEASURE);

    int32_t GetThemeScopeId() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, 0);
        return host->GetThemeScopeId();
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(ProgressLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_LAYOUT_PROPERTY_H
