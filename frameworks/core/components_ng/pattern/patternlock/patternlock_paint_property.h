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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_PAINT_PROPERTY_H

#include "core/components_ng/render/paint_property.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

class PatternLockPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(PatternLockPaintProperty, PaintProperty)

public:
    PatternLockPaintProperty() = default;
    ~PatternLockPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<PatternLockPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propCircleRadius_ = CloneCircleRadius();
        paintProperty->propRegularColor_ = CloneRegularColor();
        paintProperty->propSelectedColor_ = CloneSelectedColor();
        paintProperty->propActiveColor_ = CloneActiveColor();
        paintProperty->propPathColor_ = ClonePathColor();
        paintProperty->propPathStrokeWidth_ = ClonePathStrokeWidth();
        paintProperty->propAutoReset_ = CloneAutoReset();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetCircleRadius();
        ResetRegularColor();
        ResetSelectedColor();
        ResetActiveColor();
        ResetPathColor();
        ResetPathStrokeWidth();
        ResetAutoReset();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        PaintProperty::ToJsonValue(json);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto patternLockTheme = pipeline->GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_VOID(patternLockTheme);
        json->Put("circleRadius",
            GetCircleRadius().value_or(patternLockTheme->GetCircleRadius()).ToString().c_str());
        json->Put("regularColor",
            GetRegularColor().value_or(patternLockTheme->GetRegularColor()).ColorToString().c_str());
        json->Put("selectedColor",
            GetSelectedColor().value_or(patternLockTheme->GetSelectedColor()).ColorToString().c_str());
        json->Put("activeColor",
            GetActiveColor().value_or(patternLockTheme->GetActiveColor()).ColorToString().c_str());
        json->Put("pathColor",
            GetPathColor().value_or(patternLockTheme->GetPathColor()).ColorToString().c_str());
        json->Put("pathStrokeWidth",
            GetPathStrokeWidth().value_or(patternLockTheme->GetPathStrokeWidth()).ToString().c_str());
        json->Put("autoReset", GetAutoReset().value_or(true) ? "true" : "false");
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CircleRadius, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RegularColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ActiveColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PathColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PathStrokeWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AutoReset, bool, PROPERTY_UPDATE_RENDER);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_PAINT_PROPERTY_H
