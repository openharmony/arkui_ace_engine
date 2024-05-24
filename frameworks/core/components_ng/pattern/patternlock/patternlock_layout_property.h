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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_LAYOUT_PROPERTY_H

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
class PatternLockLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(PatternLockLayoutProperty, LayoutProperty)

public:
    PatternLockLayoutProperty() = default;
    ~PatternLockLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto LayoutProperty = MakeRefPtr<PatternLockLayoutProperty>();
        LayoutProperty->UpdateLayoutProperty(this);
        LayoutProperty->propSideLength_ = CloneSideLength();
        return LayoutProperty;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetSideLength();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto patternLockTheme = pipeline->GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_VOID(patternLockTheme);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("sideLength",
            GetSideLength().value_or(patternLockTheme->GetSideLength()).ToString().c_str(), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SideLength, Dimension, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(PatternLockLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_LAYOUT_PROPERTY_H
