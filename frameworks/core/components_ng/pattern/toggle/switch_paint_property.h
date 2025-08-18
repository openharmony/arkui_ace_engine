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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_PAINT_PROPERTY_H

#include "core/components/checkable/checkable_theme.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {

struct SwitchPaintParagraph {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SwitchPointColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(CurrentOffset, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(PointRadius, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(UnselectedColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TrackBorderRadius, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SwitchPointColorSetByUser, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedColorSetByUser, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(UnselectedColorSetByUser, bool);

    void ToJsonValue(
        std::unique_ptr<JsonValue>& json, const InspectorFilter& filter, const RefPtr<FrameNode>& host) const;
};

struct SwitchAnimationStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Duration, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Curve, RefPtr<Curve>);
};

// PaintProperty are used to set paint properties.
class SwitchPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(SwitchPaintProperty, PaintProperty);
public:
    SwitchPaintProperty() = default;
    ~SwitchPaintProperty() override = default;
    RefPtr<PaintProperty> Clone() const override;

    void Reset() override;

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    ACE_DEFINE_PROPERTY_GROUP(SwitchAnimationStyle, SwitchAnimationStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchAnimationStyle, Duration, int32_t, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchAnimationStyle, Curve, RefPtr<Curve>, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_GROUP(SwitchPaintParagraph, SwitchPaintParagraph);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchPaintParagraph, SelectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchPaintParagraph, SwitchPointColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchPaintParagraph, PointRadius, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchPaintParagraph, UnselectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchPaintParagraph, TrackBorderRadius, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchPaintParagraph, SwitchPointColorSetByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchPaintParagraph, SelectedColorSetByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwitchPaintParagraph, UnselectedColorSetByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsOn, bool, PROPERTY_UPDATE_MEASURE);

    ACE_DISALLOW_COPY_AND_MOVE(SwitchPaintProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWITCH_SWITCH_PAINT_PROPERTY_H
