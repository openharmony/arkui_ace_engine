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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_STYLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_STYLE_H

#include "core/components/common/layout/constants.h"
#include "core/components/slider/slider_theme.h"
#include "core/components/track/track_component.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

struct SliderLayoutStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SliderMode, SliderMode)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Direction, Axis)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Thickness, Dimension)
};
struct SliderLayoutThemeStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OutsetBlockSize, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OutsetBlockHotSize, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OutsetTrackThickness, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(InsetBlockSize, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(InsetBlockHotSize, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(InsetTrackThickness, Dimension)
};
struct SliderPaintStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Value, float)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Min, float)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Max, float)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Step, float)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Reverse, bool)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockColor, Color)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TrackBackgroundColor, Color)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectColor, Color)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ShowSteps, bool)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ShowTips, bool)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Direction, Axis)
};
struct SliderPaintThemeStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MarkerSize, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockHoverColor, Color)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TipColor, Color)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TipTextColor, Color)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MarkerColor, Color)
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_STYLE_H