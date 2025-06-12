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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_MODEL_STATIC_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SliderModelStatic {
public:
    static void SetThickness(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetStepSize(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetBlockType(FrameNode* frameNode, const std::optional<SliderModel::BlockStyleType>& value);
    static void SetBlockSize(FrameNode* frameNode,
        const std::optional<Dimension>& width, const std::optional<Dimension>& height);
    static void SetTrackBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetStepColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetBlockBorderColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetBlockBorderWidth(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetBlockColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetTrackBackgroundColor(FrameNode* frameNode,
        const std::optional<Gradient>& value, bool isResourceColor = false);
    static void SetSelectColor(FrameNode* frameNode,
        const std::optional<Gradient>& value, bool isResourceColor = false);
    static void SetSelectColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetSliderInteractionMode(
        FrameNode* frameNode, const std::optional<SliderModel::SliderInteraction>& mode);
    static void SetMinResponsiveDistance(FrameNode* frameNode, const std::optional<float>& value);
    static void SetValidSlideRange(FrameNode* frameNode,
        const std::optional<float>& fromValue, const std::optional<float>& toValue);
    static void SetSelectedBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& value);
#ifdef SUPPORT_DIGITAL_CROWN
    static void SetDigitalCrownSensitivity(FrameNode* frameNode, const std::optional<CrownSensitivity>& sensitivity);
#endif

    static void SetSliderValue(FrameNode* frameNode, const std::optional<float>& value);
    static void SetMinLabel(FrameNode* frameNode, const std::optional<float>& value);
    static void SetMaxLabel(FrameNode* frameNode, const std::optional<float>& value);
    static void SetDirection(FrameNode* frameNode, const std::optional<Axis>& value);
    static void SetStep(FrameNode* frameNode, const std::optional<float>& value);
    static void SetReverse(FrameNode* frameNode, const std::optional<bool>& value);
    static void SetSliderMode(FrameNode* frameNode, const std::optional<SliderModel::SliderMode>& value);
    static void SetOnChangeEvent(FrameNode* frameNode, SliderOnValueChangeEvent&& onChangeEvent);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_MODEL_STATIC_H
