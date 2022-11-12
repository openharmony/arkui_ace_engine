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

#include "core/components/common/properties/color.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

const Dimension DEFAULT_SIDE_LENGTH = 300.0_vp;
const Dimension DEFAULT_CIRCLE_RADIUS = 14.0_vp;
const Color DEFAULT_REGULAR_COLOR = Color::BLACK;
const Color DEFAULT_SELECTED_COLOR = Color::BLACK;
const Color DEFAULT_ACTIVE_COLOR = Color::BLACK;
const Color DEFAULT_PATH_COLOR = Color::BLUE;
const Dimension DEFAULT_PATH_STROKE_WIDTH = 34.0_vp;

class PatternLockPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(PatternLockPaintProperty, PaintProperty)

public:
    PatternLockPaintProperty() = default;
    ~PatternLockPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<PatternLockPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propSideLength_ = CloneSideLength();
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
        ResetSideLength();
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

        json->Put("sideLength", GetSideLength().value_or(DEFAULT_SIDE_LENGTH).ToString().c_str());
        json->Put("circleRadius", GetCircleRadius().value_or(DEFAULT_CIRCLE_RADIUS).ToString().c_str());
        json->Put("regularColor", GetRegularColor().value_or(DEFAULT_REGULAR_COLOR).ColorToString().c_str());
        json->Put("selectedColor", GetSelectedColor().value_or(DEFAULT_SELECTED_COLOR).ColorToString().c_str());
        json->Put("activeColor", GetActiveColor().value_or(DEFAULT_ACTIVE_COLOR).ColorToString().c_str());
        json->Put("pathColor", GetPathColor().value_or(DEFAULT_PATH_COLOR).ColorToString().c_str());
        json->Put("pathStrokeWidth", GetPathStrokeWidth().value_or(DEFAULT_PATH_STROKE_WIDTH).ToString().c_str());
        json->Put("autoReset", GetAutoReset().value_or(true) ? "true" : "false");
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SideLength, Dimension, PROPERTY_UPDATE_RENDER);
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
