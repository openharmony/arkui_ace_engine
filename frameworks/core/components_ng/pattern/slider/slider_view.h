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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_VIEW_H

#include "base/geometry/axis.h"
#include "base/utils/macros.h"
//TODO: In the follow-up, the class in track_component.h need to be extracted, 
// and the header file of the component cannot be directly relied on.
#include "core/components/track/track_component.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SliderView {
public:
    static void Create(float value, float step, float min, float max);
    static void SetSliderMode(const SliderMode& value);
    static void SetDirection(Axis value);
    static void SetReverse(bool value);
    static void SetBlockColor(const Color& value);
    static void SetTrackBackgroundColor(const Color& value);
    static void SetSelectColor(const Color& value);
    static void SetMinLabel(float value);
    static void SetMaxLabel(float value);
    static void SetShowSteps(bool value);
    static void SetShowTips(bool value);
    static void SetThickness(const Dimension& value);
    static void SetOnChange(SliderOnChangeEvent&& eventOnChange);

private:
    static void LoadTheme(const RefPtr<FrameNode>& frameNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_VIEW_H