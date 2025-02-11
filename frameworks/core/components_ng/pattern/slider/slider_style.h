/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
struct SliderLayoutStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SliderMode, SliderModel::SliderMode)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Direction, Axis)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Thickness, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ShowTips, bool)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Reverse, bool)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockSize, SizeT<Dimension>)
};
struct SliderPaintStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Value, float)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Min, float)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Max, float)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Step, float)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Reverse, bool)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockColor, Color)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TrackBackgroundColor, Gradient)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TrackBackgroundIsResourceColor, bool)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectColor, Color)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectGradientColor, Gradient)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectIsResourceColor, bool)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ShowSteps, bool)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Direction, Axis)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockBorderColor, Color)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockBorderWidth, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(StepColor, Color)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TrackBorderRadius, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedBorderRadius, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockSize, SizeT<Dimension>)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockType, SliderModel::BlockStyleType)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockImage, std::string)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockImageBundleName, std::string)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockImageModuleName, std::string)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockShape, RefPtr<BasicShape>)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(StepSize, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SliderMode, SliderModel::SliderMode)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SliderInteractionMode, SliderModel::SliderInteraction)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MinResponsiveDistance, float)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ValidSlideRange, RefPtr<SliderModel::SliderValidRange>)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(EnableHapticFeedback, bool)
#ifdef SUPPORT_DIGITAL_CROWN
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DigitalCrownSensitivity, CrownSensitivity)
#endif
};
struct SliderTipStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ShowTips, bool)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Padding, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Content, std::string)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontSize, Dimension)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextColor, Color)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TipColor, Color)
    ACE_DEFINE_PROPERTY_GROUP_ITEM(CustomContent, std::string)
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_STYLE_H
